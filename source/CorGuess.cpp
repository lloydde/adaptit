////////////////////////////////////////////////////////////////
/// \project	adaptit
/// \file		CorGuess.cpp
/// \author		Alan Buseman
/// \date_created 1 May 2004
/// \rcs_id $Id$
/// \copyright	2010 SIL International
/// \license	The Common Public License or the GNU Lesser General Public
///				License (see license directory)
/// \description This is the implementation file for the Correspondence Guesser.
/// The Correspondence Guesser is composed of three classes: Corresp, CorrespList,
/// and the main class Guesser.
////////////////////////////////////////////////////////////////

// For documentation see CorGuess.h


#ifndef _MBCS // 1.6.0ad Update CorGuess.cpp for compiling in Adapt It // 1.6.1ba Update guesser to test _MCBS for non wxWidgets
// ////////////////////////////////////////////////////////////////////////
// whm added standard wxWidgets headers below which includes wx.h
#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma implementation "CorGuess.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif
// whm added standard wxWidgets headers above which includes wx.h
// ////////////////////////////////////////////////////////////////////////
#endif // 1.6.0ad 

#ifdef _MBCS // 1.6.1ba 
#include <string.h> // Only generic string functions used
#endif

#include "CorGuess.h"
#include "Adapt_It.h"

int iStrMatch( const wxChar* pszS, const wxChar* pszMatch ) // 1.6.1dc Utility function to show how far strings match
	{
	int iMatchLen = 0;
	while ( *pszS != 0 && *pszMatch != 0 ) // 1.6.1dc While more in match string, compare char
		{
		if ( *pszS++ != *pszMatch++ ) // 1.6.1dc If chars don't match, return length of match
			return iMatchLen;
		else  // 1.6.1dc If chars match, increment length of match
			iMatchLen++;
		}
	return iMatchLen; // 1.6.1dc If chars matched all the way to the end, return length of match
	}

int iStrMatchBack( const wxChar* pszS, const wxChar* pszMatch ) // 1.6.1dc Utility function to show how far strings match // 1.6.1dn 
	{
	int iLenMatch = 0; // 1.6.1dp Length of match from back
	int iSLen = wxStrlen( pszS ); // 1.6.1dp 
	int iSMatchLen = wxStrlen( pszMatch ); // 1.6.1dp 
	int iMinLen = iSLen; // 1.6.1dp 
	if ( iSLen > iSMatchLen ) // 1.6.1dp 
		iMinLen = iSMatchLen; // 1.6.1dp Get length of shortest of two being matched
	wxChar* pszSEnd = (wxChar*)pszS + iSLen - 1; // 1.6.1dn  // 1.6.1dp 
	wxChar* pszMatchEnd = (wxChar*)pszMatch + iSMatchLen - 1; // 1.6.1dn  // 1.6.1dp 
	for ( int i = 0; i < iMinLen; i++ ) // 1.6.1dc While more in match string, compare char
		{
		if ( *pszSEnd-- != *pszMatchEnd-- ) // 1.6.1dc If chars don't match, return length of match
			return iLenMatch;
		else  // 1.6.1dc If chars match, increment length of match
			iLenMatch++;
		}
	return iLenMatch; // 1.6.1dc If chars matched all the way to the end, return length of match
	}

bool bStrMatch( const wxChar* pszS, const wxChar* pszMatch, int iStart ) // 1.6.1aj Utility function to test for match of pszMatch
	{
	const wxChar* pszT = pszS + iStart; // 1.6.1aj Set starting location
	while ( *pszMatch != 0 ) // 1.6.1aj While more in match
		{
		if ( *pszT++ != *pszMatch++ )
			return false;
		}
	return true;
	}

int iStrFind( const wxChar* pszS, const wxChar* pszFind ) // 1.6.1aj Utility function to find pszFind
	{
	int iLen = wxStrlen( pszS ); // 1.6.1aj Temp var to prevent unsigned mismatch
	for ( int i = 0; i < iLen ; i++ ) // 1.6.1aj At each location, check for match
		if ( bStrMatch( pszS, pszFind, i ) )
			return i; // 1.6.1aj Return place found for success
	return -1; // 1.6.1aj Return -1 for failure
	}

void StrReplace( wxChar* pszS, wxChar* pszReplace, int iLoc, int iNum ) // 1.6.1aj Replace a section of pszS with pszReplace
	{
	wxChar* pszTail = new wxChar[ wxStrlen( pszS ) + 1 ]; // 1.6.1aj Temp storage of tail
	wxStrcpy( pszTail, pszS + iLoc + iNum ); // 1.6.1aj Save tail
	*(pszS + iLoc) = 0; // 1.6.1bb Terminate head // 1.6.1be Change back to pointer arithemetic
//	wxStrcpy( pszS + iLoc, "" ); // 1.6.1aj Shorten source // 1.6.1bb 
	wxStrcat( pszS, pszReplace ); // 1.6.1aj Copy replace in // 1.6.1bb Get rid of pointer arithmetic
	wxStrcat( pszS, pszTail ); // 1.6.1aj Put tail back on // 1.6.1bb 
	delete pszTail;
	}

int iCorrespondenceBack( wxChar* psz1, wxChar* psz2 ) // Return length of correspondence from start // 1.6.1dm Revise correspondence back func
	{
	unsigned int iMatchLen = iStrMatchBack( psz1, psz2 ); // 1.6.1dm See how much of front matches
	if ( iMatchLen == wxStrlen( psz1 ) || iMatchLen == wxStrlen( psz1 ) ) // 1.6.1dm If complete match, no correspondence found
		return 0; // 1.6.1dm 
	if ( iMatchLen < 2 ) // 1.6.1dm If less than 2 chars match as root, no correspondence found
		return 0; // 1.6.1dm 
	return iMatchLen; // 1.6.1dm If an acceptable match length, return it
	}

int iCorrespondenceFront( wxChar* psz1, wxChar* psz2 ) // Return length of correspondence from end // 1.6.1dm Revise correspondence back func
	{
	unsigned int iMatchLen = iStrMatch( psz1, psz2 ); // 1.6.1dm See how much of back matches
	if ( iMatchLen == wxStrlen( psz1 ) || iMatchLen == wxStrlen( psz1 ) ) // 1.6.1dm If complete match, no correspondence found
		return 0; // 1.6.1dm 
	if ( iMatchLen < 2 ) // 1.6.1dm If less than 2 chars match as root, no correspondence found
		return 0; // 1.6.1dm 
	return iMatchLen; // 1.6.1dm If an acceptable match length, return it
	}

#ifdef OLD
int iCorrespondenceBack( wxChar* psz1, wxChar* psz2, int& iStart, int& iEnd1, int& iEnd2 ) // Return length of correspondence from start
	{
	// Find a difference, and return start and end of difference
	//int iDiff; // set but unused
	//iDiff = 0;
	iStart = 0;
	iEnd1 = 0;
	iEnd2 = 0;
	int iLen1 = wxStrlen( psz1 );
	int iLen2 = wxStrlen( psz2 );
	int i1 = iLen1 - 1;
	int i2 = iLen2 - 1;
	while ( i1 > 1 && i2 > 1 ) // Look for first difference
		{
		if ( *(psz1+i1) != *(psz2+i2) ) // If mismatch, note difference
			{
			iStart = i1; // Note start of difference
			bool bSucc = false;
			while ( true ) // Look for end of difference
				{
				if ( i1 < iLen1 - 1 || i2 < iLen2 - 1 ) // If not at the very end, check for one wxChar insert or delete // 1.4bp Allow one letter added at end (made it worse)
					{
					if ( *(psz1+i1-1) == *(psz2+i2) 
							&& *(psz1+i1-2) == *(psz2+i2-1) ) // If match at one wxChar diff, note end of difference
						{
						iEnd1 = i1;
						iEnd2 = i2 + 1;
						bSucc = true;
						break;
						}
					else if ( *(psz1+i1) == *(psz2+i2-1) 
							&& *(psz1+i1-1) == *(psz2+i2-2) ) // If match at one wxChar diff, note end of difference
						{
						iEnd1 = i1 + 1;
						iEnd2 = i2;
						bSucc = true;
						break;
						}
					}
				i1--; // Step to prev wxChar
				i2--;
				if ( *(psz1+i1) == *(psz2+i2) // If match, note end of difference
						&& ( *(psz1+i1-1) == *(psz2+i2-1) // Match two letters
							|| i1 < iLen1 - 3 ) ) // Or have length of at least 3
					{
					iEnd1 = i1 + 1;
					iEnd2 = i2 + 1;
					bSucc = true;
					break;
					}
				else if ( i1 <= 1 || i2 <= 1 ) // If different all the way to front, return failure
					return 0;
				}
			if ( bSucc )
				{
//				if ( iEnd1 > 0 && iEnd1 == iLen1 - 1 ) // If correspondence only matched one wxChar, match 2 instead // 1.6.1dd Allow single char suffixes
//					{
//					iEnd1--;
//					iEnd2--;
//					}
//				if ( iLen1 - iEnd1 > 5 ) // If suffix length longer than max length, don't do it as a back correspondence // 1.6.1dm Remove max affix limit
//					return 0;
				return 1;
				}
			}
		i1--; // Step to next wxChar
		i2--;
		}
	return 0; // Return no correspondence
	}
#endif // OLD

Corresp::Corresp()
	{
	pszSrc = NULL;
	pszTar = NULL;
	iFreq = 0; // 1.6.1ad 
	iNumInstances = 0;
	iNumExceptions = 0;
	pcorNext = NULL;
	}

Corresp::Corresp( const wxChar* pszSrc1, const wxChar* pszTar1, int iFreq ) // Constructor that allocates strings for source and target
	{
	pszSrc = new wxChar[ wxStrlen( pszSrc1 ) + 1 ];
	wxStrcpy( pszSrc, pszSrc1 );
	pszTar = new wxChar[ wxStrlen( pszTar1 ) + 1 ];
	wxStrcpy( pszTar, pszTar1 );
	iFreq = iFreq; // 1.6.1ad 
	iNumInstances = 1;
	iNumExceptions = 0;
	pcorNext = NULL;
	}

Corresp::~Corresp()
	{
	if ( pszSrc )
		delete pszSrc;
	if ( pszTar )
		delete pszTar;
	}

CorrespList::CorrespList()
	{
	pcorFirst = NULL;
	pcorLast = NULL;
	iLen = 0; // 1.6.1dc Add size to guesser correspondence list
	}

CorrespList::~CorrespList()
	{
	ClearAll(); // 1.4vyd 
	}

void CorrespList::ClearAll() // 1.4vyd Add ClearAll function
	{
	while ( pcorFirst )
		{
		Corresp* pcor = pcorFirst->pcorNext;
		delete pcorFirst;
		pcorFirst = pcor;
		iLen = 0; // 1.6.1dc Add size to guesser correspondence list
		}
	}

void CorrespList::Add( Corresp* pcorNew ) // Add a new correspondence to the end ofthe list // 1.6.1af Change to top of list
	{
	pcorNew->pcorNext = pcorFirst; // 1.6.1af Always add correspondence to top of list
	if ( !pcorFirst ) // 1.6.1af If list was empty, need to set last
		pcorLast = pcorNew; // 1.6.1af New becomes last
	pcorFirst = pcorNew; // 1.6.1af 
	iLen++; // 1.6.1dc Add size to guesser correspondence list
#ifdef AddLast
	if ( !pcorFirst ) // If list was empty, new becomes first
		pcorFirst = pcorNew;
	else // Else, previous last points to new
		pcorLast->pcorNext = pcorNew;
	pcorLast = pcorNew; // New becomes last
#endif
	}

void CorrespList::Add( const wxChar* pszSrc, const wxChar* pszTar, int iFreq ) // Add a new corresponcence to the list
{
	Corresp* pcorF = pcorFind( pszSrc, pszTar ); // See if pair already in list
	if ( pcorF ) // 1.6.1bc If pair already in list, increment count
		pcorF->iNumInstances++;
	else // 1.6.1bc Else (pair not in list) add new
		Add( new Corresp( pszSrc, pszTar, iFreq ) );
	}

void CorrespList::SortLongestLast() // 1.6.1bd Sort longest last // 1.6.1dg In guesser, fix bug in sort longest last
	{
	unsigned int iLongest = 0; // 1.6.1bd 
	CorrespList corlstTemp; // 1.6.1bd Make temp list
	Corresp* pcor;
	for ( pcor = pcorFirst; pcor; pcor = pcor->pcorNext ) // 1.6.1bd Copy all to temp list
		{
		corlstTemp.Add( pcor->pszSrc, pcor->pszTar, pcor->iFreq ); // 1.6.1bd Copy to temp list
		unsigned int iLen = wxStrlen( pcor->pszSrc ); // 1.6.1bd 
		if ( iLen > iLongest ) // 1.6.1bd If longer that previous longest, remember
			iLongest = iLen;
		}
	ClearAll(); // 1.6.1bd Delete all from main list
	for ( unsigned int i = 1; i <= iLongest; i++ ) // 1.6.1bd For each length, copy ones of that length to main list
		for ( pcor = corlstTemp.pcorFirst; pcor; pcor = pcor->pcorNext ) // 1.6.1bd Copy all to temp list
			{
			if ( wxStrlen( pcor->pszSrc ) == i ) // 1.6.1bd If current length, copy
				Add( pcor->pszSrc, pcor->pszTar, pcor->iFreq ); // 1.6.1bd Copy to top of main list
			}
	}

void CorrespList::SortLongestFirst() // 1.6.1bf Sort longest first // 1.6.1dg In guesser, fix bug in sort longest last
	{
	unsigned int iLongest = 0; // 1.6.1bd 
	CorrespList corlstTemp; // 1.6.1bd Make temp list
	Corresp* pcor;
	for ( pcor = pcorFirst; pcor; pcor = pcor->pcorNext ) // 1.6.1bd Copy all to temp list
		{
		corlstTemp.Add( pcor->pszSrc, pcor->pszTar, pcor->iFreq ); // 1.6.1bd Copy to temp list
		unsigned int iLen = wxStrlen( pcor->pszSrc ); // 1.6.1bd 
		if ( iLen > iLongest ) // 1.6.1bd If longer that previous longest, remember
			iLongest = iLen;
		}
	ClearAll(); // 1.6.1bd Delete all from main list
	for ( unsigned int i = iLongest; i >= 1; i-- ) // 1.6.1bf For each length, copy ones of that length to main list
		for ( pcor = corlstTemp.pcorFirst; pcor; pcor = pcor->pcorNext ) // 1.6.1bd Copy all to temp list
			{
			if ( wxStrlen( pcor->pszSrc ) == i ) // 1.6.1bd If current length, copy
				Add( pcor->pszSrc, pcor->pszTar, pcor->iFreq ); // 1.6.1bd Copy to top of main list
			}
	}

Corresp* CorrespList::pcorFind( const wxChar* pszSrc, const wxChar* pszTar ) // Find the same pair, return NULL if not found
	{
	for ( Corresp* pcor = pcorFirst; pcor; pcor = pcor->pcorNext )
		{
		if ( !wxStrcmp( pszSrc, pcor->pszSrc ) && !wxStrcmp( pszTar, pcor->pszTar ) )
			return pcor;
		}
	return NULL;
	}

Corresp* CorrespList::pcorDelete( Corresp* pcor, Corresp* pcorPrev ) // Delete a correspondence from the list, return next after deleted one
	{
	Corresp* pcorNext = pcor->pcorNext;
	if ( !pcorPrev ) // If first in list, then point top at next
		pcorFirst = pcorNext;
	else
		pcorPrev->pcorNext = pcorNext; // else point prev at next
	delete pcor;
	return pcorNext;
	}

void CorrespListKB::Add( const wxChar* pszSrc, const wxChar* pszTar, int iFreq ) // Add a new corresponcence to the end of the list // 1.6.1bc
	{
	Corresp* pcorF = pcorFind( pszSrc ); // See if already in list
	if ( pcorF ) // 1.6.1bc If in list, check frequency
		{
		if ( iFreq > pcorF->iFreq ) // 1.6.1ae If higher frequency, replace previous with this
			{
			delete pcorF->pszTar;
			pcorF->pszTar = new wxChar[ wxStrlen( pszTar ) + 1 ];
			wxStrcpy( pcorF->pszTar, pszTar ); // 1.6.1bb Store new target
			pcorF->iFreq = iFreq; // 1.6.1ae Store new frequency
			}
		}
	else // 1.6.1bc Else (not in list) add new
		CorrespList::Add( new Corresp( pszSrc, pszTar, iFreq ) );
	}

Corresp* CorrespList::pcorFind( const wxChar* pszSrc ) // Find the same source, return NULL if not found // 1.6.1bc
	{
	for ( Corresp* pcor = pcorFirst; pcor; pcor = pcor->pcorNext )
		{
		if ( !wxStrcmp( pszSrc, pcor->pszSrc ) ) // 1.6.1bc
			return pcor;
		}
	return NULL;
	}

void CorrespList::DeleteTooFew( int iMinExamples ) // 1.6.1dn Change to function to use for both suff & pref
	{
	Corresp* pcor = pcorFirst;
	Corresp* pcorPrev = NULL;
	while ( pcor != NULL ) // 1.6.1de Change to avoid crash from bug in one compiler
		{
		bool bDelete = false;
		if ( pcor->iNumInstances < iMinExamples ) // Delete all correspondences that occur too few times // 1.5.8va 
			bDelete = true;
		if ( bDelete )				
			pcor = pcorDelete( pcor, pcorPrev );
		else
			{
			pcorPrev = pcor;
			pcor = pcor->pcorNext;
			}
		}
	}

void CorrespList::DeleteTooLowSucess( int iRequiredPercent ) // 1.6.1dn Change to function to use for both suff & pref
	{
	Corresp* pcor = pcorFirst;
	Corresp* pcorPrev = NULL; // Delete correspondences that have less than required success percentage
	while ( pcor != NULL ) // 1.6.1de Change to avoid crash from bug in one compiler
		{
		int iSuccessPercent = ( pcor->iNumInstances * 100 ) / ( pcor->iNumInstances + pcor->iNumExceptions );
		if ( iSuccessPercent < iRequiredPercent ) // 1.4bd Make required success ratio a parameter
			pcor = pcorDelete( pcor, pcorPrev );
		else
			{
			pcorPrev = pcor;
			pcor = pcor->pcorNext;
			}
		}
	}

Guesser::Guesser()
	{
	iRequiredSuccessPercent = 30; // Init required success percent
//	iMaxSuffLen = 5; // Init max suffix length // 1.6.1dj 
	iMinSuffExamples = 2; // Minimum number of examples of suffix to be considered
	iGuessLevel = 50; // 1.5.8u Default guess level to conservative
//	bInit = true; // 1.6.1df Set for initialization phase // 1.6.1dh Remove calculate at each new word, didn't work
	}

// =========== Start Main Routines
void Guesser::Init( int iGuessLevel1, int iMaxPref1, int iMaxSuff1 ) // 1.4vyd Add ClearAll function // 1.5.8u Change to Init, add guess level // 1.6.1dk Add max pref & suff
	{
	corlstSuffGuess.ClearAll(); // Guessed suffixes
	corlstRootGuess.ClearAll(); // Guessed roots
	corlstPrefGuess.ClearAll(); // Guessed prefixes
	corlstSuffGiven.ClearAll(); // Given suffixes
	corlstRootGiven.ClearAll(); // Given roots
	corlstPrefGiven.ClearAll(); // Given prefixes
	corlstKB.ClearAll(); // Raw correspondences given to guesser
//	bInit = true; // 1.6.1df Set for initialization phase // 1.6.1dh 
	iMaxPref = iMaxPref1; // 1.6.1dk Set max pref
	iMaxSuff = iMaxSuff1; // 1.6.1dk Set max suff
	iGuessLevel = iGuessLevel1; // 1.5.8u Set guess level
	if ( iGuessLevel >= 50 )
//		iRequiredSuccessPercent = 30 - ( ( ( iGuessLevel - 50 ) * 100 ) / 170 ); // 1.5.8va 50=30% up to 100=0%
		iRequiredSuccessPercent = 15 - ( ( ( iGuessLevel - 50 ) * 100 ) / 340 ); // Change to 50=15% up to 100=0% // 1.6.1da 
	else
//		iRequiredSuccessPercent = 30 + ( ( ( 50 - iGuessLevel ) * 100 ) / 72 ); // 1.5.8va 49=31% down to 1=98%
		iRequiredSuccessPercent = 15 + ( ( ( 50 - iGuessLevel ) * 100 ) / 58 ); // Change to 49=16% down to 1=99% // 1.6.1da 
	if ( iGuessLevel >= 50 ) // 1.5.8va  // 1.6.1da Change guesser to allow single example of change at 50+
		iMinSuffExamples = iMinSuffExamples - 1; // 1.5.8va Allow fewer examples
	else if ( iGuessLevel <= 20 ) // 1.5.8va 
		iMinSuffExamples = iMinSuffExamples + 1; // 1.5.8va Require more examples
	}

void Guesser::AddCorrespondence( const wxChar* pszSrc, const wxChar* pszTar, int iFreq ) // Make a correspondence to the list
	{
	if ( iGuessLevel == 0 ) // 1.5.8va If guesser turned off, don't store correspondences
		return; // 1.5.8va 
	if ( iFreq == -1 ) // 1.6.1ad If given prefix store as that
		corlstPrefGiven.Add( pszSrc, pszTar, 10000 ); // 1.6.1ad Store as given prefix // 1.6.1ag Use high freq
	else if ( iFreq == -2 ) // 1.6.1ad If given suffix store as that
		corlstSuffGiven.Add( pszSrc, pszTar, 10000 ); // 1.6.1ad Store as given suffix // 1.6.1ag Use high freq
	else if ( iFreq == 0 ) // 1.6.1ad If given root store as that
		corlstRootGiven.Add( pszSrc, pszTar, 10000 ); // 1.6.1ad Store as given prefix // 1.6.1ag Use high freq
	else
		corlstKB.Add( pszSrc, pszTar, iFreq );
//	if ( !bInit && corlstKB.iLen < 1000 ) // 1.6.1df If kb is small, calculate at each new word // 1.6.1dh 
//		CalculateCorrespondences(); // 1.6.1df  // 1.6.1dh 
	}

void Guesser::CalculateCorrespondences() // Calculate correspondences // 1.6.1aj Make this a function
	{
	if ( corlstSuffGuess.bIsEmpty() ) // If suffix correspondences have not been calculated, do it now
		{
		Corresp* pcor = NULL;
		for ( pcor = corlstKB.pcorFirst; pcor != NULL; pcor = pcor->pcorNext ) // Make and store all suffix correspondences // 1.6.1de Change to avoid crash from bug in one compiler
			{
			wxChar* pszS = pcor->pszSrc;
			wxChar* pszT = pcor->pszTar;
			int iCorrBack = iCorrespondenceFront( pszS, pszT ); // 1.6.1dm See if there is a suffix difference 
			if ( iCorrBack ) // If there is a correspondence, store it
				{
				pszS += iCorrBack; // 1.6.1dm Move to unmatched tail
				pszT += iCorrBack; // 1.6.1dm Move to unmatched tail
				corlstSuffGuess.Add( pszS, pszT, 0 ); // Add to list, count if already there
				}
			}
		corlstSuffGuess.DeleteTooFew( iMinSuffExamples ); // 1.6.1dn 

		for ( Corresp* pcorSuff = corlstSuffGuess.pcorFirst; pcorSuff; pcorSuff = pcorSuff->pcorNext ) // Count exceptions for each correspondence
			{
			wxChar* pszSuffSrc = pcorSuff->pszSrc;
			wxChar* pszSuffTar = pcorSuff->pszTar;
			int iLenSrc = wxStrlen( pszSuffSrc );
			for ( pcor = corlstKB.pcorFirst; pcor; pcor = pcor->pcorNext ) // Look at each knowledge base pair to see if it is an exception
				{
				wxChar* pszEndSrc = pcor->pszSrc; // Get end of source of kb pair
				pszEndSrc += wxStrlen( pszEndSrc ) - iLenSrc;
				if ( !wxStrcmp( pszSuffSrc, pszEndSrc ) ) // If source matches, see if target matches, if not this is an exception
					{
					wxChar* pszEndTar = pcor->pszTar; // Get end of target of kb pair
					pszEndTar += wxStrlen( pszEndTar ) - iLenSrc;
					if ( wxStrcmp( pszSuffTar, pszEndTar ) ) // If exception, count it
						pcorSuff->iNumExceptions++;
					}
				}
			}
		corlstSuffGuess.DeleteTooLowSucess( iRequiredSuccessPercent ); // 1.6.1dn 

		// Calculate prefix correspondences // 1.6.1dn 
		wxChar pszSFront[300]; // 1.6.1dn // 1.6.1dp 
		wxChar pszTFront[300]; // 1.6.1dn  // 1.6.1dp 
		for ( pcor = corlstKB.pcorFirst; pcor != NULL; pcor = pcor->pcorNext ) // Make and store all prefix correspondences // 1.6.1de Change to avoid crash from bug in one compiler
			{
			wxChar* pszS = pcor->pszSrc;
			wxChar* pszT = pcor->pszTar;
			int iCorrBack = iCorrespondenceBack( pszS, pszT ); // 1.6.1dm See if there is a prefix difference // 1.6.1dn  // 1.6.1dp 
			if ( iCorrBack ) // If there is a correspondence, store it // 1.6.1dp 
				{
				wxStrcpy( pszSFront, pszS ); // 1.6.1dn 
				int iSPrefLen = wxStrlen( pszSFront) - iCorrBack; // 1.6.1dp 
				*(pszSFront + iSPrefLen) = 0; // 1.6.1dn  // 1.6.1dp 
				wxStrcpy( pszTFront, pszT ); // 1.6.1dn 
				int iTPrefLen = wxStrlen( pszTFront) - iCorrBack; // 1.6.1dp 
				*(pszTFront + iTPrefLen) = 0; // 1.6.1dn  // 1.6.1dp 
				corlstPrefGuess.Add( pszSFront, pszTFront, 0 ); // Add to list, count if already there // 1.6.1dn 
				}
			}
		corlstPrefGuess.DeleteTooFew( iMinSuffExamples ); // 1.6.1dn 

		for ( Corresp* pcorPref = corlstPrefGuess.pcorFirst; pcorPref; pcorPref = pcorPref->pcorNext ) // Count exceptions for each correspondence
			{
			wxChar* pszPrefSrc = pcorPref->pszSrc;
			wxChar* pszPrefTar = pcorPref->pszTar;
			int iLenSrc = wxStrlen( pszPrefSrc );
			int iLenTar = wxStrlen( pszPrefTar );
			for ( pcor = corlstKB.pcorFirst; pcor; pcor = pcor->pcorNext ) // Look at each knowledge base pair to see if it is an exception
				{
				int iLenMatchSrc = iStrMatch( pszPrefSrc, pcor->pszSrc ); // 1.6.1dp Get length of front match of src word to pref
				if ( iLenMatchSrc == iLenSrc ) // 1.6.1dp If match full length of pref, see if tar matches
					{
					int iLenMatchTar = iStrMatch( pszPrefTar, pcor->pszTar ); // 1.6.1dp Get length of front match of tar word to tar pref
					if ( iLenMatchTar < iLenTar ) // 1.6.1dp If not front match of tar pref, count as exception
						pcorPref->iNumExceptions++; // 1.6.1dp 
					}
				}
			}
		corlstPrefGuess.DeleteTooLowSucess( iRequiredSuccessPercent ); // 1.6.1dn 

		corlstSuffGiven.SortLongestLast(); // 1.6.1bd Sort given affixes and roots by length // 1.6.1bf Sort longest last so it will be first in guess list
		corlstPrefGiven.SortLongestLast(); // 1.6.1bd Sort given affixes and roots by length // 1.6.1bf 
		corlstRootGiven.SortLongestLast(); // 1.6.1bd Sort given affixes and roots by length
		for ( pcor = corlstSuffGiven.pcorFirst; pcor; pcor = pcor->pcorNext )  // 1.6.1ag Add given affixes to guess list
			corlstSuffGuess.Add( pcor->pszSrc, pcor->pszTar, pcor->iFreq ); // 1.6.1ag 
		for ( pcor = corlstPrefGiven.pcorFirst; pcor; pcor = pcor->pcorNext )  // 1.6.1ag Add given affixes to guess list
			corlstPrefGuess.Add( pcor->pszSrc, pcor->pszTar, pcor->iFreq ); // 1.6.1ag 
		for ( pcor = corlstRootGiven.pcorFirst; pcor; pcor = pcor->pcorNext )  // 1.6.1ag Add given affixes to guess list
			corlstRootGuess.Add( pcor->pszSrc, pcor->pszTar, pcor->iFreq ); // 1.6.1ag 
		}
	}

bool Guesser::bRootReplace( const wxChar* pszSrc, wxChar** ppszTar ) // Try to replace a root // 1.6.1aj 
	{
	wxStrcpy( *ppszTar, pszSrc ); // Copy source to target, so caller can use it if no replace // 1.6.1dc Fix guesser bug of no guess if no root list
	/* This for loop gives spurious replacements of substrings within a word, so the code is not ready for prime time
	for ( Corresp* pcorRoot = corlstRootGuess.pcorFirst; pcorRoot; pcorRoot = pcorRoot->pcorNext ) // See if a guess is possible for this string
		{
		wxChar* pszRootSrc = pcorRoot->pszSrc; // Pointer to root to match
		wxChar* pszRootTar = pcorRoot->pszTar; // 1.6.1aj Pointer to target root
		int iFind = iStrFind( pszSrc, pszRootSrc ); // 1.6.1aj See if root found
		if ( iFind >= 0 ) // 1.6.1aj If root found, replace it
			{
			StrReplace( *ppszTar, pszRootTar, iFind, wxStrlen( pszRootSrc ) ); // 1.6.1aj Replace root
			return true;
			}
		}
	*/
	return false;
	}

bool Guesser::bSuffReplace( const wxChar* pszSrc, wxChar** ppszTar, int iLevel ) // Try to replace a suffix // 1.6.1aj  // 1.6.1dk Add level arg to limit number
	{
	int iLenSrc = wxStrlen( pszSrc ); // 1.6.1dm 
	wxStrcpy( *ppszTar, pszSrc ); // Copy source to target, so caller can use it if no replace // 1.6.1dc Fix guesser bug of no guess if no root list
	if ( iLevel >= iMaxSuff ) // 1.6.1aj If no replace, return target same as source // 1.6.1dk Stop if max number reached
		return false;
	if ( iLenSrc <= 2 ) // 1.6.1dm Don't try affix if only 2 letters of root left
		return false; // 1.6.1dm 
	iLevel++; // 1.6.1dk Count how many this is
	for ( Corresp* pcorSuff = corlstSuffGuess.pcorFirst; pcorSuff; pcorSuff = pcorSuff->pcorNext ) // See if a guess is possible for this string
		{
		wxChar* pszSuffSrc = pcorSuff->pszSrc; // Pointer to suffix to match
		int iLenSuffSrc = wxStrlen( pszSuffSrc ); // Get length of suffix to match
		if ( ( iLenSrc - iLenSuffSrc ) >= 2 ) // 1.6.1dm Don't replace suff if it leaves less than 2 letters of root
			{
			const wxChar* pszEndSrc = pszSrc + iLenSrc - iLenSuffSrc; // Get start of end of source for match
			if ( !wxStrcmp( pszSuffSrc, pszEndSrc ) ) // If source matches, replace it with target
				{
				wxChar* pszSrcShortened = new wxChar[ wxStrlen( pszSrc ) + 1 ]; // 1.6.1aj Shortened source to try further suff
				wxStrcpy( pszSrcShortened, pszSrc ); // Copy source to shortened source
				*(pszSrcShortened + wxStrlen( pszSrc ) - iLenSuffSrc) = 0; // 1.6.1aj Shorten source // 1.6.1be Change back to pointer arithmetic
				bSuffReplace( pszSrcShortened, ppszTar, iLevel ); // 1.6.1aj Try replace suff on shortened source, but only if guess level 40 or more // 1.6.1dk Pass in level
				wxStrcat( *ppszTar, pcorSuff->pszTar ); // 1.6.1aj Append target suff to end of target
				delete pszSrcShortened; // 1.6.1aj 
				return true;
				}
			}
		}
	return false;
	}

bool Guesser::bPrefReplace( const wxChar* pszSrc, wxChar** ppszTar, int iLevel ) // Try to replace a prefix // 1.6.1aj  // 1.6.1dk Add level arg to limit number
	{
	int iLenSrc = wxStrlen( pszSrc ); // 1.6.1dm 
	wxStrcpy( *ppszTar, pszSrc ); // Copy source to target, so caller can use it if no replace // 1.6.1dc Fix guesser bug of no guess if no root list
	if ( iLevel >= iMaxPref ) // 1.6.1aj If no replace, return target same as source // 1.6.1dk Stop if max number reached
		return false;
	if ( iLenSrc <= 2 ) // 1.6.1dm Don't try affix if only 2 letters of root left
		return false; // 1.6.1dm 
	iLevel++; // 1.6.1dk Count how many this is
	for ( Corresp* pcorPref = corlstPrefGuess.pcorFirst; pcorPref; pcorPref = pcorPref->pcorNext ) // See if a guess is possible for this string
		{
		wxChar* pszPrefSrc = pcorPref->pszSrc; // Pointer to prefix to match
		int iLenPrefSrc = wxStrlen( pszPrefSrc ); // Get length of prefix to match
		if ( ( iLenSrc - iLenPrefSrc ) >= 2 ) // 1.6.1dm Don't replace pref if it leaves less than 2 letters of root
			{
			if ( bStrMatch( pszSrc, pszPrefSrc, 0 ) ) // If source matches, replace it with target
				{
				wxChar* pszSrcShortened = new wxChar[ iLenSrc + 1 ]; // 1.6.1aj Shortened source to try further pref
				wxStrcpy( pszSrcShortened, pszSrc + iLenPrefSrc ); // Copy source to shortened source
				bPrefReplace( pszSrcShortened, ppszTar, iLevel ); // 1.6.1aj Try replace pref on shortened source, but only if guess level 40 or more // 1.6.1dk Pass in level
				StrReplace( *ppszTar, pcorPref->pszTar, 0, 0 ); // 1.6.1aj Prepend target pref to front of target
				delete pszSrcShortened; // 1.6.1aj 
				return true;
				}
			}
		}
	return false;
	}

bool Guesser::bTargetGuess( const wxChar* pszSrc, wxChar** ppszTar ) // Return target guess
	{
	if ( corlstSuffGuess.bIsEmpty() ) // If correspondences have not been calculated, do it now
		CalculateCorrespondences(); // 1.6.1aj 
	bool bSucc = false; // 1.6.1aj 
	if ( bRootReplace( pszSrc, ppszTar ) ) // 1.6.1aj 
		bSucc = true;
	if ( bSuffReplace( *ppszTar, ppszTar ) ) // 1.6.1aj 
		bSucc = true;
	if ( bPrefReplace( *ppszTar, ppszTar ) ) // 1.6.1aj 
		bSucc = true;
	return bSucc; // 1.6.1aj 
	}

void Guesser::DoCalcCorrespondences() // a public accessor, BEW added 3Dec14
{
	this->CalculateCorrespondences();
}

// supplies the app's m_iMaxPrefixes value to the 2nd param of Init()
int Guesser::GetUserMaxPrefixesValue()
{
	CAdapt_ItApp* pApp = (CAdapt_ItApp*)&wxGetApp();
	return pApp->m_iMaxPrefixes;
}

// supplies the app's m_iMaxSuffixes value to the 3rd param of Init()
int Guesser::GetUserMaxSuffixesValue()
{
	CAdapt_ItApp* pApp = (CAdapt_ItApp*)&wxGetApp();
	return pApp->m_iMaxSuffixes;
}
