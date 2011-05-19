/////////////////////////////////////////////////////////////////////////////
/// \project		adaptit
/// \file			MergeUpdatedSrc.h
/// \author			Bruce Waters
/// \date_created	12 April 2011
/// \date_revised	
/// \copyright		2011 Bruce Waters, Bill Martin, SIL International
/// \license		The Common Public License or The GNU Lesser General Public License (see license directory)
/// \description	This is a header file containing some helper functions used 
///                 by Adapt It, for merging updated/edited source text in the form
///                 of a list of CSourcePhrase instances with an earlier list of
///                 adapted CSourcePhrase instances for the same span of source text. 
/////////////////////////////////////////////////////////////////////////////
//
#ifndef mergeUpdatedSrc_h
#define mergeUpdatedSrc_h

// the following improves GCC compilation performance
#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "MergeUpdatedSrc.h"
#endif

#include <wx/dynarray.h>

class CSourcePhrase;
WX_DECLARE_OBJARRAY(CSourcePhrase*, SPArray);

#ifndef _string_h_loaded
#define _string_h_loaded
#include "string.h"
#endif
#include "Adapt_It.h"

class CBString;
class SPList;	// declared in SourcePhrase.h WX_DECLARE_LIST(CSourcePhrase, SPList); macro 
				// and defined in SourcePhrase.cpp WX_DEFINE_LIST(SPList); macro
class CSourcePhrase;

//struct Matchup {
//	int oldMatchPos; // index in the oldSPArray at which a common word was matched
//	int newMatchPos; // index in the newSPArray at which a common word was matched
//};

enum SubspanType {
	beforeSpan, // whatever subspan precedes those which are in common
	commonSpan, // the in common subspan (at can be empty, in which case only the 
				// beforeSpan has content)
	afterSpan   // whatever subspan follows those which are in common (this can be 
				// as large as the remaining CSourcePhrase instances in oldSPArray
				// and newSPArray, when the Subspan is at the right edge in the tree
				// -- that is, the yet-to-be-processed instances)
};

struct Subspan {
	int			oldStartPos;		// index in oldSPArray where CSourcePhrase instances commence
	int			oldEndPos;			// index in oldSPArray where CSourcePhrase instances end (inclusive)
	int			newStartPos;		// index in newSPArray where CSourcePhrase instances commence
	int			newEndPos;			// index in newSPArray where CSourcePhrase instances end (inclusive)
	Subspan*	childSubspans[3];	// a set of beforeSpan, commonSpan & afterSpan Subspan instances on the heap
	SubspanType	spanType;			// an enum with values beforeSpan, commonSpan, afterSpan (this member
									// is redundant, but useful for a sanity check when processing
	bool		bClosedEnd;			// default TRUE, but FALSE for the rightmost afterSpan so that
									// in-common matching can match beyond SPAN_LIMIT instances
};

const int tupleSize = 3;


// Rethinking (May 16) on the algorithm, and discussing with Bill, we noted that the
// addition or removal of large chunks of source text (more than the limit value) has the
// potential, due to spurious matches, of messing up the merger - throwing text fragments
// to places where they don't belong. E.g, a chapter which has some of the source text in
// some verses empty, and the user in Paratext adds the missing source text of those
// verses, then the attempt to merge that source text to the AI document will have only
// spurious matches to anything in that additional material, and taking the largest is no
// protection at all, since it would still be a spurious match, and the resulting merger
// would move material where it shouldn't go. Fortunately, because of USFM or SFM markup,
// we have chapter and verse and subheading and introduction milestones on which we can
// rely - so we will add code to divide the legacy and incoming (possibly edited) source
// text material, after tokennization into CSourcePhrase instances, into subranges which
// are either bCorrelatesWithNothing = FALSE, or bCorrelatesWithNothing = TRUE. The former
// ranges have to have MergeUpdatedSourceText() done on such a subrange (with arrOld and
// arrNew restricted to the CSourcePhrase instances in the subrange) to handle any possible
// user-editing that may have been done. The latter ranges, because either the source
// exists in arrOld but not in arrNew (a removal is needed), or the source exists in arrNew
// but not in arrOld (an insertion is needed), don't require MergeUpdatedSourceText() be
// done on such as these, but instead, either the arrOld material is skipped (that is, just
// not put into pMergedList), or the arrNew material is inserted (that is, it is appended
// to pMergedList at the appropriate time), because there is nothing to compare it with.
// Such potentially large chunks of material to be either removed or added in are a problem
// to our recursive algorithm because of the potential of spurious matches within them, so
// we have to pre-process the input lists to remove from contention any such large chunks,
// and only do the merging on chapters, verses, subheadings, etc which exist in both arrOld
// and arrNew. Our approach is to divide the lists (converted into arrays of CSourcePhrase
// instances) into a series of structs which map, via integers, into subspans in arrOld and
// arrNew, and which are stored in a flat array of wxArrayPtrVoid type. Each struct handles
// a verse, or introduction, or subheading, or chapter-initial material which is none of
// the previous - one such set of structs for the whole of the legacy AI document having
// it's m_key source text values compared, and another for the (possibly edited) source
// text coming from Paratext to which comparison is made; and then a third array, using a
// different struct, to break up the associated subspans in the former two in those which
// are to be merged recursively, and those which are not. The structs below are defined so
// as to meet the above needs. The wxArrayPtrVoid instances will be local variables within
// encapsulating functions, and so are not defined as globals here. The arrays we generate
// in order to provide a cover of the whole data array are deliberately kept flag (ie. no
// nesting of structs in structs), to simplify the query and Find...() functions we define
// for obtaining the spans we are interested in.
// The above approach means we can apply the top level function to any sized source text
// data - whether a whole book, or a single verse, and not have to worry about what kind of
// editing, additions or removals may have been done in the incoming new source text. (The
// structs here, and the chunking functions which use them, may also have value in
// decomposing for an OXES export of the document.)

enum SfmChunkType {
	unknownChunkType, // at initialization time & before arriving at a specific type
	bookInitialChunk, // for data like \id line, \mt main title, secondary title, etc
	introductionChunk, // for introductory material, markers beginning \i.... 
	chapterStartChunk, // for stuff at the start of a chapter, and before any subheading
	subheadingChunk, // for a subheading
	verseChunk // for a verse
};
// We do a set of the following stored in wxArrayPtrVoid for the whole existing Adapt It
// document chunk. As for "document chunk", we have agreed to only store single-chapter
// documents when in PT collaboration mode, never the whole of a book, and this way we can
// more easily do robust support of whatever the PT user may do in PT and AI, without
// duplication of data - such actions which would result in the unwelcome possibility of
// having the same CSourcePhrase(s) in both a whole-book document and in a single-chapter
// document; we'll avoid this by never storing a whole book document, only single-chapter
// ones.
// We do a separate set in a different wxArrayPtrVoid for the whole of the (possibly
// edited) source text (chapter) chunk.
// We'll do analysis on those two and arrive at a third wxArrayPtrVoid which defines the
// span associations between the two which require recursive merging, versus those which
// don't - the latter are chunks where wholesale removals or wholesale additions are
// required, because the association is with nothing within a subspan of one of the two
// tokenized source text arrays.
struct SfmChunk {
	SfmChunkType		type; // one of the above types
	bool				bContainsText; // default TRUE, set FALSE if the information in the chunk is
									   // absent (such as a \v marker without any text
									   // following the verse number)
	int					startsAt; // index into an SPArray defining where the chunk starts
	int					endsAt; // index into an SPArray defining where the chunk ends
	// the remaining members pertain to verseChunk type, and store info from the verse
	// reference within the Adapt It document
	wxString			strChapter; // chapter number as a string (always set, except for introduction material)
	int					nChapter; // chapter number (always set, except for introduction material)
	wxString			strDelimiter; // delimiter string used in a range, eg. - in 3-5
	wxString			strStartingVerse; // string version of the verse number or first verse number of a range
	int					nStartingVerse;  // decimal digits converted to a number, eg 6 from 6a-8
	wxChar				charStartingVerseSuffix;  // for the a in something like 6a-8, or 9a
	wxString			strEndingVerse; // string version of the verse number or final verse number of a range
	int					nEndingVerse; // the decimal digits converted to a number, eg. 8 from 6a-8
	wxChar				charEndingVerseSuffix; // for the a in something like 15-17a
};

// The two int members in the struct below are for indexing into the first two of the
// wxArrayPtrVoid arrays described above. Each chunk is typed (see above). A correlation
// with "nothing" occurs when, in analysing left to right through arrOld and arrNew, the
// next chunk exists in either arrOld but not in arrNew, or exists in arrNew but not in
// arrOld. When either of those happens we set bCorrelatesWithNothing to TRUE. When that
// doesn't happen, we'll have a valid correlation between the two of arrOld and arrNew,
// which will define a subspan within each which constitute a correlated pair of subspans
// (ie. milestones in common, such as verses 3 to 5 of a chapter exist in both arrOld and
// arrNew) and so we will input those subranges to the MergeUpdatedSourceText() function -
// this ensures we catch any user-source-text-editing that may have been done in Paratext
// unbeknown to Adapt It since this particular chapter was lasted worked on in Adapt It (in
// collaborative mode) and merge it into the AI document so that the user can adapt
// anything which is different before he tries to transfer the finished chapter back to
// Paratext. But bCorrelatesWithNothing == TRUE means that either milestoned data is to be
// removed from arrOld, or milestoned data is to be inserted from arrNew, unilaterally
// (i.e. without any attempt at a recursive merger), since correlation with nothing means,
// by definition, that there cannot be any group of CSourcePhrase instances in whichever
// subspan exists which is "in-common" with the non-existing ones in a "nothing" subspan.
// Such subspans can be dealt with by either ignoring the data to be removed (when data in
// arrOld correlates with "nothing" in arrNew for some range of milestones), or by
// apppending it to pMergedList (when data in arrNew correlates with "nothing" in arrOld)
// which is the case when it is to be added in as new material not hitherto seen within
// Adapt It's document.
// Note: if, in arrOld or arrNew, SFM or USFM markup occurs but the source text is absent,
// (e.g. \v 3 exists but no text for verse three occurs following the verse number) our
// code will treat this as as a "nothing" location; "nothing" locations would also be
// things like (1) a discontinuity in the verses within a chapter (we take verse ranges
// start and end numbers into account, e.g. \v 3-5 where there is text following, those are
// not discontinuities) -- but if verses 5 to 9 are absent within a chapter, that would be
// a "nothing" location/subspan. Or (2)a suheading is empty in arrOld, but has content in
// arrNew - the arrOld location would be considered a "nothing" subspan, and the code would
// just flow the arrNew subheading text in at the appropriate location to pMergedList,
// without attempting the unnecessary MergeUpdatedSourceText() call, or (3) other
// information types where something is contrasted with it's absence in the other array.
struct SfmChunksCorrelation 
{
	bool				bCorrelatesWithNothing; // default FALSE, only TRUE if the previous & after
											    // chunks have consecutive +ve int values, for one of
											    // the legacy (arrOld) or incoming (arrNew) data arrays
	int					indexSfmChunkOld; // indexes into the SfmChunk set from arrOld
	int					indexSfmChunkNew; // indexes into the SfmChunk set from arrNew, -1 if absent
};

bool	AnalyseChapterVerseRef(wxString& strChapVerse, wxString& strChapter, int& nChapter, 
						wxString& strDelimiter, wxString& strStartingVerse, int& nStartingVerse,
						wxChar& charStartingVerseSuffix, wxString& strEndingVerse,
						int& nEndingVerse, wxChar& charEndingVerseSuffix);
bool	AnalyseSPArrayChunks(SPArray* pInputArray, wxArrayPtrVoid* pChunkSpecifiers);
bool	DoesChunkContainSourceText(SPArray* pArray, int startsAt, int endsAt);
void	EraseAdaptationsFromRetranslationTruncations(SPList* pMergedList);
int		FindNextInArray(wxString& word, SPArray& arr, int startFrom, int endAt, wxString& phrase); 
bool	GetAllCommonSubspansFromOneParentSpan(SPArray& arrOld, SPArray& arrNew, Subspan* pParentSubspan, 
				wxArrayString* pUniqueCommonWordsArray, wxArrayPtrVoid* pSubspansArray, 
				wxArrayInt* pWidthsArray, bool bClosedEnd);
bool	GetBookInitialChunk(SPArray* arrP, int& startsAt, int& endsAt);
int		GetKeysAsAString_KeepDuplicates(SPArray& arr, Subspan* pSubspan, bool bShowOld, 
										wxString& keysStr, int limit);
Subspan* GetMaxInCommonSubspan(SPArray& arrOld, SPArray& arrNew, Subspan* pParentSubspan, int limit);
bool	GetNextMatchup(wxString& word, SPArray& arrOld, SPArray& arrNew, int oldStartAt, int newStartAt,
					   int oldStartFrom, int oldEndAt, int newStartFrom, int newEndAt, int& oldMatchedStart, 
					   int& oldMatchedEnd, int & newMatchedStart, int& newMatchedEnd, int& oldLastIndex,
					   int& newLastIndex);
bool	GetNextCommonSpan(wxString& word, SPArray& arrOld, SPArray& arrNew, int oldStartAt, 
					   int newStartAt, int oldStartFrom, int oldEndAt, int newStartFrom, int newEndAt, 
					   int& oldMatchedStart, int& oldMatchedEnd, int & newMatchedStart, 
					   int& newMatchedEnd, int& oldLastIndex, int& newLastIndex, bool bClosedEnd, 
					   wxArrayPtrVoid* pCommonSpans, wxArrayInt* pWidthsArray);
int		GetNextNonemptyMarkers(SPArray* pArray, int& startFrom, bool& bReachedEndOfArray);
int		GetUniqueOldSrcKeysAsAString(SPArray& arr, Subspan* pSubspan, wxString& oldSrcKeysStr, int limit);
int		GetWordsInCommon(SPArray& arr, Subspan* pSubspan, wxString& uniqueKeysStr, wxArrayString& strArray,
						 int limit);
int		GetWordsInCommon(SPArray& arrOld, SPArray& arrNew, Subspan* pSubspan, wxArrayString& strArray,
						 int limit); // overload which encapsulates the GetUniqueSrcKeysAsAString() call
void	InitializeUsfmMkrs();
void	InitializeSubspan(Subspan* pSubspan, SubspanType spanType, int oldStartPos, 
						  int oldEndPos, int newStartPos, int newEndPos, bool bClosedEnd = TRUE);
bool	IsLeftAssociatedPlaceholder(CSourcePhrase* pSrcPhrase);
bool	IsMatchupWithinAnyStoredSpanPair(int oldPosStart, int oldPosEnd, int newPosStart, 
						int newPosEnd, wxArrayPtrVoid* pSubspansArray);
bool	IsMergerAMatch(SPArray& arrOld, SPArray& arrNew, int oldLoc, int newFirstLoc);
bool	IsRightAssociatedPlaceholder(CSourcePhrase* pSrcPhrase);
void	MergeOldAndNew(SPArray& arrOld, SPArray& arrNew, Subspan* pSubspan, SPList* pMergedList);
void	MergeUpdatedSourceText(SPList& oldList, SPList& newList, SPList* pMergedList, int limit);
void	RecursiveTupleProcessor(SPArray& arrOld, SPArray& arrNew, SPList* pMergedList,
						int limit, Subspan* tuple[]); // the array size is always 3, so 
													  // we don't need a parameter for it
void	InitializeNonVerseChunk(SfmChunk* pStruct);
bool	SetupChildTuple(SPArray& arrOld, SPArray& arrNew, Subspan* pParentSubspan, Subspan* tuple[],
						int limit);
//void	SetEndIndices(SPArray& arrOld, SPArray& arrNew, int oldStartAt, int newStartAt, int& oldEndAt,
//					  int& newEndAt, int limit, bool bClosedEnd); <<-- not needed yet
void	SetEndIndices(SPArray& arrOld, SPArray& arrNew, Subspan* pSubspan, int limit); // overload
bool	WidenLeftwardsOnce(SPArray& arrOld, SPArray& arrNew, int oldStartAt, int oldEndAt,
				int newStartAt, int newEndAt, int oldStartingPos, int newStartingPos,
				int& oldCount, int& newCount);
bool	WidenRightwardsOnce(SPArray& arrOld, SPArray& arrNew, int oldStartAt, int oldEndAt,
				int newStartAt, int newEndAt, int oldStartingPos, int newStartingPos,
				int& oldCount, int& newCount);

#endif	// mergeUpdatedSrc_h
