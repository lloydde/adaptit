/////////////////////////////////////////////////////////////////////////////
/// \project		adaptit
/// \file			ConsistencyCheckDlg.cpp
/// \author			Bill Martin
/// \date_created	11 July 2006
/// \date_revised	15 January 2008
/// \copyright		2008 Bruce Waters, Bill Martin, SIL International
/// \license		The Common Public License or The GNU Lesser General Public License (see license directory)
/// \description	This is the implementation file for the CConsistencyCheckDlg class. 
/// The CConsistencyCheckDlg class allows the user to respond to inconsistencies between
/// the adaptations stored in the document and those stored in the knowledge base. In the
/// dialog the user may accept what is in the document as a KB entry, type a new entry to
/// be stored in the document and KB, accept <no adaptation>, or ignore the inconsistency
/// (to be fixed later). For any fixes the user can also check a box to "Auto-fix later
/// instances the same way." 
/// \derivation		The CConsistencyCheckDlg class is derived from AIModalDialog.
/// BEW 12Apr10, no changes needed for support of doc version 5 in this file
/// BEW 9July10, updated for support of kbVersion 2
/////////////////////////////////////////////////////////////////////////////

// the following improves GCC compilation performance
#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma implementation "ConsistencyCheckDlg.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif

// other includes
#include <wx/docview.h> // needed for classes that reference wxView or wxDocument
#include <wx/valgen.h> // for wxGenericValidator

#include "Adapt_It.h"
#include "ConsistencyCheckDlg.h"
#include "TargetUnit.h"
#include "Adapt_ItView.h"
#include "Adapt_ItCanvas.h"
#include "MainFrm.h"
#include "KB.h"
#include "SourcePhrase.h"
#include "RefString.h"
#include "helpers.h"

// next two are for version 2.0 which includes the option of a 3rd line for glossing

/// This global is defined in Adapt_ItView.cpp.
extern bool	gbIsGlossing; // when TRUE, the phrase box and its line have glossing text

// This global is defined in Adapt_ItView.cpp.
//extern bool	gbGlossingVisible; // TRUE makes Adapt It revert to Shoebox functionality only

/// This global is defined in Adapt_ItView.cpp.
extern bool gbGlossingUsesNavFont;

//extern bool gbRemovePunctuationFromGlosses;

extern bool gbIgnoreIt; // used in CAdapt_ItView::DoConsistencyCheck
						// when the "Ignore it, I will fix it later" button was hit in the dialog

/// This global is defined in Adapt_It.cpp.
extern CAdapt_ItApp* gpApp; // if we want to access it fast

// event handler table
BEGIN_EVENT_TABLE(CConsistencyCheckDlg, AIModalDialog)
	EVT_INIT_DIALOG(CConsistencyCheckDlg::InitDialog)// not strictly necessary for dialogs based on wxDialog
	EVT_BUTTON(wxID_OK, CConsistencyCheckDlg::OnOK)
	EVT_RADIOBUTTON(IDC_RADIO_ACCEPT_HERE, CConsistencyCheckDlg::OnRadioAcceptHere)
	EVT_RADIOBUTTON(IDC_RADIO_CHANGE_INSTEAD, CConsistencyCheckDlg::OnRadioChangeInstead)
	EVT_LISTBOX(IDC_LIST_TRANSLATIONS, CConsistencyCheckDlg::OnSelchangeListTranslations)
	//EVT_TEXT(IDC_EDIT_TYPE_NEW, CConsistencyCheckDlg::OnUpdateEditTypeNew)
END_EVENT_TABLE()


CConsistencyCheckDlg::CConsistencyCheckDlg(wxWindow* parent) // dialog constructor
	: AIModalDialog(parent, -1, _("Inconsistency Found"),
				wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	// This dialog function below is generated in wxDesigner, and defines the controls and sizers
	// for the dialog. The first parameter is the parent which should normally be "this".
	// The second and third parameters should both be TRUE to utilize the sizers and create the right
	// size dialog.
	ConsistencyCheckDlgFunc(this, TRUE, TRUE);
	// The declaration is: ConsistencyCheckDlgFunc( wxWindow *parent, bool call_fit, bool set_sizer );
	
	bool bOK;
	bOK = gpApp->ReverseOkCancelButtonsForMac(this);
	
	m_keyStr = _T("");
	m_adaptationStr = _T("");
	m_bDoAutoFix = FALSE;
	m_chVerse = _T("");

	aDifference = 0;
	difference = 0;
	m_bShowItCentered = TRUE;
	
	// Get pointers to the dialog's controls (some of these are the old stuff, renamed)
	m_pEditCtrlChVerse = (wxTextCtrl*)FindWindowById(IDC_EDIT_CH_VERSE); 
	wxASSERT(m_pEditCtrlChVerse != NULL);
	m_pEditCtrlChVerse->SetBackgroundColour(gpApp->sysColorBtnFace); // read only background color
	
	m_pListBox = (wxListBox*)FindWindowById(IDC_LIST_TRANSLATIONS);
	wxASSERT(m_pListBox != NULL);
	
	//m_pEditCtrlNew = (wxTextCtrl*)FindWindowById(IDC_EDIT_TYPE_NEW);
	//wxASSERT(m_pEditCtrlNew != NULL);
	
	m_pEditCtrlAdaptation = (wxTextCtrl*)FindWindowById(IDC_EDIT_ADAPTATION); 
	wxASSERT(m_pEditCtrlAdaptation != NULL);
	// BEW 5Sep11, I want these two wxTextCtrls to be write background for maximum
	// readability, but they do need to be read-only (we'll do that in InitDialog())
	//m_pEditCtrlAdaptation->SetBackgroundColour(gpApp->sysColorBtnFace); // read only background color
	
	m_pEditCtrlKey = (wxTextCtrl*)FindWindowById(IDC_EDIT_KEY);
	wxASSERT(m_pEditCtrlKey != NULL);
	// BEW 5Sep11, I want these two wxTextCtrls to be write background for maximum
	// readability, but they do need to be read-only (we'll do that in InitDialog())
	//m_pEditCtrlKey->SetBackgroundColour(gpApp->sysColorBtnFace); // read only background color

	m_pRadioAcceptHere = (wxRadioButton*)FindWindowById(IDC_RADIO_ACCEPT_HERE);
	wxASSERT(m_pRadioAcceptHere != NULL);

	m_pRadioChangeInstead = (wxRadioButton*)FindWindowById(IDC_RADIO_CHANGE_INSTEAD);
	wxASSERT(m_pRadioChangeInstead != NULL);

	m_pCheckAutoFix = (wxCheckBox*)FindWindowById(IDC_CHECK_DO_SAME); // whm added 31Aug11
	wxASSERT(m_pCheckAutoFix != NULL);
	m_pCheckAutoFix->SetValidator(wxGenericValidator(&m_bDoAutoFix)); // use validator

	// new stuff

	pMainMsg = (wxStaticText*)FindWindowById(ID_TEXT_MAIN_MSG);
	wxASSERT(pMainMsg != NULL);

	pAvailableStatTxt = (wxStaticText*)FindWindowById(ID_TEXT_AVAIL_ADAPT_OR_GLOSS);
	wxASSERT(pAvailableStatTxt != NULL);

	pClickListedStatTxt = (wxStaticText*)FindWindowById(ID_TEXT_CLICK_LISTED);
	wxASSERT(pClickListedStatTxt != NULL);

	pClickAndEditStatTxt = (wxStaticText*)FindWindowById(ID_TEXT_CLICK_EDIT_LISTED);
	wxASSERT(pClickAndEditStatTxt != NULL);

	pIgnoreListStatTxt = (wxStaticText*)FindWindowById(ID_TEXT_TYPE_NEW);
	wxASSERT(pIgnoreListStatTxt != NULL);

	pNoAdaptMsgTxt = (wxStaticText*)FindWindowById(ID_TEXT_NO_ADAPT_MSG);
	wxASSERT(pNoAdaptMsgTxt != NULL);

	// static box sizer at top right
	pTopRightBoxSizer = (wxStaticBoxSizer*)m_topRightBoxLabel;
	wxASSERT(pTopRightBoxSizer != NULL);
	pTopRightBox = pTopRightBoxSizer->GetStaticBox();
	wxASSERT(pTopRightBox != NULL);

	// static box sizer for the 1.2.3. "Do one of the following..." directives
	pDoOneOf_Sizer = (wxStaticBoxSizer*)m_pNumberedPointsStaticBoxSizer;;
	wxASSERT(pDoOneOf_Sizer != NULL);
	pStatBox_DoOneOf = pDoOneOf_Sizer->GetStaticBox();
	wxASSERT(pStatBox_DoOneOf != NULL);

	// use wxValidator for simple dialog data transfer
	m_pEditCtrlChVerse->SetValidator(wxGenericValidator(&m_chVerse));
	m_pEditCtrlAdaptation->SetValidator(wxGenericValidator(&m_adaptationStr));
	m_pEditCtrlKey->SetValidator(wxGenericValidator(&m_keyStr));

}

CConsistencyCheckDlg::~CConsistencyCheckDlg() // destructor
{
	
}

void CConsistencyCheckDlg::InitDialog(wxInitDialogEvent& WXUNUSED(event)) // InitDialog is method of wxWindow
{
	//InitDialog() is not virtual, no call needed to a base class
	wxString s;
	if (gbIsGlossing)
	{
		s = _("<no gloss>"); 
	}
	else
	{
		s = _("<no adaptation>");
	}
	gbIgnoreIt = FALSE; // default

	m_bRadioButtonAction = FALSE;

	// first, use the current source and target language fonts for the list box
	// and edit boxes (in case there are special characters)
	// make the fonts show user's desired point size in the dialog
	#ifdef _RTL_FLAGS
	gpApp->SetFontAndDirectionalityForDialogControl(gpApp->m_pSourceFont, m_pEditCtrlKey, NULL,
								NULL, NULL, gpApp->m_pDlgSrcFont, gpApp->m_bSrcRTL);
	#else // Regular version, only LTR scripts supported, so use default FALSE for last parameter
	gpApp->SetFontAndDirectionalityForDialogControl(gpApp->m_pSourceFont, m_pEditCtrlKey, NULL, 
								NULL, NULL, gpApp->m_pDlgSrcFont);
	#endif

	if (gbIsGlossing && gbGlossingUsesNavFont)
	{
		#ifdef _RTL_FLAGS
		gpApp->SetFontAndDirectionalityForDialogControl(gpApp->m_pNavTextFont, m_pEditCtrlAdaptation, NULL,
									m_pListBox, NULL, gpApp->m_pDlgTgtFont, gpApp->m_bNavTextRTL);
		#else // Regular version, only LTR scripts supported, so use default FALSE for last parameter
		gpApp->SetFontAndDirectionalityForDialogControl(gpApp->m_pNavTextFont, m_pEditCtrlAdaptation, NULL, 
									m_pListBox, NULL, gpApp->m_pDlgTgtFont);
		#endif
	}
	else
	{
		#ifdef _RTL_FLAGS
		gpApp->SetFontAndDirectionalityForDialogControl(gpApp->m_pTargetFont, m_pEditCtrlAdaptation, NULL,
									m_pListBox, NULL, gpApp->m_pDlgTgtFont, gpApp->m_bTgtRTL);
		#else // Regular version, only LTR scripts supported, so use default FALSE for last parameter
		gpApp->SetFontAndDirectionalityForDialogControl(gpApp->m_pTargetFont, m_pEditCtrlAdaptation, NULL, 
									m_pListBox, NULL, gpApp->m_pDlgTgtFont);
		#endif
	}

	// put the key and its translation, or gloss, in their boxes
	// the dialog class's m_adaptationStr can hold either an adaptation, or a gloss - the
	// latter will be the case when glossing is ON
	m_keyStr = m_pSrcPhrase->m_key;
	if (gbIsGlossing)
		m_adaptationStr = m_pSrcPhrase->m_gloss;
	else
		m_adaptationStr = m_pSrcPhrase->m_adaption;
	// the top two boxes are made read-only at the end of this function

	wxString mainStaticTextStr;
	// put in the correct string, for this main message label - either "adaptation" or "gloss"
	wxString msg = pMainMsg->GetLabel();
	if (gbIsGlossing)
	{
		mainStaticTextStr = mainStaticTextStr.Format(msg, gpApp->m_modeWordGloss.c_str());
	}
	else
	{
		mainStaticTextStr = mainStaticTextStr.Format(msg, gpApp->m_modeWordAdapt.c_str());
	}
	pMainMsg->SetLabel(mainStaticTextStr);
	// get the pixel difference in the label's changed text
	aDifference = CalcLabelWidthDifference(msg, mainStaticTextStr, pMainMsg);
	if (aDifference > difference)
	{
		difference = aDifference;
	}

	// set the text of the vertical static box sizer at top right to "Adaptation text:" 
	// or "Gloss text:"
	wxString boxLabel = pTopRightBox->GetLabelText();
	wxString updatedBoxLabel;
	if (gbIsGlossing)
	{
		updatedBoxLabel = updatedBoxLabel.Format(boxLabel, gpApp->m_strGlossText.c_str());
	}
	else
	{
		updatedBoxLabel = mainStaticTextStr.Format(boxLabel, gpApp->m_strAdaptationText.c_str());
	}
	pTopRightBox->SetLabel(updatedBoxLabel);
	// get the pixel difference in the label's changed text
	aDifference = CalcLabelWidthDifference(boxLabel, updatedBoxLabel, pTopRightBox);
	if (aDifference > difference)
	{
		difference = aDifference;
	}

	wxString doOneOfStr = pStatBox_DoOneOf->GetLabelText();
	updatedBoxLabel.Empty();
	if (gbIsGlossing)
	{
		updatedBoxLabel = updatedBoxLabel.Format(doOneOfStr, gpApp->m_modeWordGloss.c_str());
	}
	else
	{
		updatedBoxLabel = mainStaticTextStr.Format(doOneOfStr, gpApp->m_modeWordAdapt.c_str());
	}
	pStatBox_DoOneOf->SetLabel(updatedBoxLabel);
	// get the pixel difference in the label's changed text
	aDifference = CalcLabelWidthDifference(doOneOfStr, updatedBoxLabel, pStatBox_DoOneOf);
	if (aDifference > difference)
	{
		difference = aDifference;
	}

	// set text of top radio button
	wxString radioAcceptHereStr;
	// put in the correct string, for this radio button label;  "adaptation" or "gloss" 
	wxString msg2 = m_pRadioAcceptHere->GetLabel();
	if (gbIsGlossing)
	{
		radioAcceptHereStr = radioAcceptHereStr.Format(msg2, gpApp->m_modeWordGloss.c_str());
	}
	else
	{
		radioAcceptHereStr = radioAcceptHereStr.Format(msg2, gpApp->m_modeWordAdapt.c_str());
	}
	m_pRadioAcceptHere->SetLabel(radioAcceptHereStr);
	// get the pixel difference in the label's changed text
	aDifference = CalcLabelWidthDifference(msg2, radioAcceptHereStr, m_pRadioAcceptHere);
	if (aDifference > difference)
	{
		difference = aDifference;
	}

	// set text of second radio button
	wxString radioChangeToStr;
	// put in the correct string, for this radio button label;  "adaptation" or "gloss" 
	wxString msg3 = m_pRadioChangeInstead->GetLabel();
	if (gbIsGlossing)
	{
		radioChangeToStr = radioChangeToStr.Format(msg3, gpApp->m_modeWordGloss.c_str());
	}
	else
	{
		radioChangeToStr = radioChangeToStr.Format(msg3, gpApp->m_modeWordAdapt.c_str());
	}
	m_pRadioChangeInstead->SetLabel(radioChangeToStr);
	// get the pixel difference in the label's changed text
	aDifference = CalcLabelWidthDifference(msg3, radioChangeToStr, m_pRadioChangeInstead);
	if (aDifference > difference)
	{
		difference = aDifference;
	}

	// Next, the "Available adaptations/glosses in the knowledge base" stat text item at
	// top of the list
	wxString availStatTextStr;
	// put in the correct string, for this main message label - either "adaptation" or "gloss"
	wxString msg4 = pAvailableStatTxt->GetLabel();
	if (gbIsGlossing)
	{
		availStatTextStr = availStatTextStr.Format(msg4, gpApp->m_modeWordGlossPlural.c_str());
	}
	else
	{
		availStatTextStr = availStatTextStr.Format(msg4, gpApp->m_modeWordAdaptPlural.c_str());
	}
	pAvailableStatTxt->SetLabel(availStatTextStr);
	// get the pixel difference in the label's changed text
	aDifference = CalcLabelWidthDifference(msg4, availStatTextStr, pAvailableStatTxt);
	if (aDifference > difference)
	{
		difference = aDifference;
	}

	// Next, the <no adaptation> or <no gloss> paranthesized comment stat text item
	// between the two radio buttons
	wxString noTextStr;
	// put in the correct string, for this main message label - either "adaptation" or "gloss"
	wxString msg8 = pNoAdaptMsgTxt->GetLabel();
	if (gbIsGlossing)
	{
		noTextStr = noTextStr.Format(msg8, gpApp->m_strNoGloss.c_str());
	}
	else
	{
		noTextStr = noTextStr.Format(msg8, gpApp->m_strNoAdapt.c_str());
	}
	pNoAdaptMsgTxt->SetLabel(noTextStr);
	// get the pixel difference in the label's changed text
	aDifference = CalcLabelWidthDifference(msg8, noTextStr, pNoAdaptMsgTxt);
	if (aDifference > difference)
	{
		difference = aDifference;
	}


	// next, the 1. wxStaticText message at bottom right (needs "adaptation" or "gloss")
	wxString clickListedTextStr;
	// put in the correct string, for this main message label - either "adaptation" or "gloss"
	wxString msg5 = pClickListedStatTxt->GetLabel();
	if (gbIsGlossing)
	{
		clickListedTextStr = clickListedTextStr.Format(msg5, gpApp->m_modeWordGloss.c_str(),
														gpApp->m_strGlossText.c_str());
	}
	else
	{
		clickListedTextStr = clickListedTextStr.Format(msg5, gpApp->m_modeWordAdapt.c_str(),
														gpApp->m_strAdaptationText.c_str());
	}
	pClickListedStatTxt->SetLabel(clickListedTextStr);
	// get the pixel difference in the label's changed text
	aDifference = CalcLabelWidthDifference(msg5, clickListedTextStr, pClickListedStatTxt);
	if (aDifference > difference)
	{
		difference = aDifference;
	}

	// next, the 2. wxStaticText message at bottom right (needs "adaptation" or "gloss")
	wxString clickEditTextStr;
	// put in the correct string, for this main message label - either "adaptations" or "glosses"
	wxString msg6 = pClickAndEditStatTxt->GetLabel();
	if (gbIsGlossing)
	{
		clickEditTextStr = clickEditTextStr.Format(msg6, gpApp->m_modeWordGlossPlural.c_str());
	}
	else
	{
		clickEditTextStr = clickEditTextStr.Format(msg6, gpApp->m_modeWordAdaptPlural.c_str());
	}
	pClickAndEditStatTxt->SetLabel(clickEditTextStr);
	// get the pixel difference in the label's changed text
	aDifference = CalcLabelWidthDifference(msg6, clickEditTextStr, pClickAndEditStatTxt);
	if (aDifference > difference)
	{
		difference = aDifference;
	}

	// next, the 3. wxStaticText message at bottom right (needs "adaptation" or "gloss")
	wxString ignoreTextStr;
	// put in the correct string, for this main message label - either "adaptation" or "gloss"
	wxString msg7 = pIgnoreListStatTxt->GetLabel();
	if (gbIsGlossing)
	{
		ignoreTextStr = ignoreTextStr.Format(msg7, gpApp->m_modeWordGloss.c_str());
	}
	else
	{
		ignoreTextStr = ignoreTextStr.Format(msg7, gpApp->m_modeWordAdapt.c_str());
	}
	pIgnoreListStatTxt->SetLabel(ignoreTextStr);
	// get the pixel difference in the label's changed text
	aDifference = CalcLabelWidthDifference(msg7, ignoreTextStr, pIgnoreListStatTxt);
	if (aDifference > difference)
	{
		difference = aDifference;
	}

	// fill the listBox, if there is a targetUnit available
	// BEW 7July10, for kbVersion 2, we only add to the listBox those CRefString
	// instances' m_translation contents when the CRefString instance is a non-deleted
	// one, and beware, it can legally happen that they are all deleted ones, in which
	// case we can't make a selection - so we must protect the SetSelection() call below
	int counter = 0;
	if (m_bFoundTgtUnit)
	{
		wxASSERT(m_pTgtUnit != NULL);
		CRefString* pRefString;
		TranslationsList::Node* pos = m_pTgtUnit->m_pTranslations->GetFirst();
		wxASSERT(pos != NULL);
		while (pos != NULL)
		{
			pRefString = (CRefString*)pos->GetData();
			pos = pos->GetNext();
			// BEW 9July10, added test here
			if (!pRefString->GetDeletedFlag())
			{
				wxString str = pRefString->m_translation;
				if (str.IsEmpty())
				{
					str = s; // user needs to be able to see a "<no adaptation>" or "<no gloss>" entry
				}
				m_pListBox->Append(str);
				counter++;
				// m_pListBox is not sorted but it is safest to call FindListBoxItem before calling SetClientData
				int nNewSel = gpApp->FindListBoxItem(m_pListBox, str, caseSensitive, exactString);
				wxASSERT(nNewSel != -1); // we just added it so it must be there!
				m_pListBox->SetClientData(nNewSel,pRefString);
			}
		}
		// select the first string in the listbox by default, provided there is something
		// there
		if (counter > 0)
		{
			m_pListBox->SetSelection(0,TRUE);
		}
		else
		{
			// the listBox will be empty - but nothing to do here
			;
		}
	}
	else
	{
		// the listBox will be empty - but nothing to do here
		;
	}

	// work out where to place the dialog window
	wxRect rectScreen;
	rectScreen = wxGetClientDisplayRect();

	wxClientDC dc(gpApp->GetMainFrame()->canvas);
	gpApp->GetMainFrame()->canvas->DoPrepareDC(dc);// adjust origin
	gpApp->GetMainFrame()->PrepareDC(dc); // wxWidgets' drawing.cpp sample also calls PrepareDC on the owning frame
	//dc.LPtoDP(&m_ptBoxTopLeft); // now it's device coords
	//int xScrollUnits, yScrollUnits, xOrigin, yOrigin;
	//pApp->GetMainFrame()->canvas->GetViewStart(&xOrigin, &yOrigin); // gets xOrigin and yOrigin in scroll units
	//pApp->GetMainFrame()->canvas->GetScrollPixelsPerUnit(&xScrollUnits, &yScrollUnits); // gets pixels per scroll unit
	//m_ptBoxTopLeft.x = xOrigin * xScrollUnits; // number pixels is ScrollUnits * pixelsPerScrollUnit
	//m_ptBoxTopLeft.y = yOrigin * yScrollUnits;

	int newXPos,newYPos;
	// CalcScrolledPosition translates logical coordinates to device ones. 
	gpApp->GetMainFrame()->canvas->CalcScrolledPosition(m_ptBoxTopLeft.x,m_ptBoxTopLeft.y,&newXPos,&newYPos);
	m_ptBoxTopLeft.x = newXPos;
	m_ptBoxTopLeft.y = newYPos;
	// we leave the width and height the same
	gpApp->GetMainFrame()->canvas->ClientToScreen(&m_ptBoxTopLeft.x,&m_ptBoxTopLeft.y); // now it's screen coords
	int height = m_nTwoLineDepth;
	wxRect rectDlg;
	GetClientSize(&rectDlg.width, &rectDlg.height); // dialog's window
	rectDlg = NormalizeRect(rectDlg); // in case we ever change from MM_TEXT mode // use our own
	int dlgHeight = rectDlg.GetHeight();
	int dlgWidth = rectDlg.GetWidth();
	wxASSERT(dlgHeight > 0);
	int left = (rectScreen.GetWidth() - dlgWidth)/2;
	if (m_ptBoxTopLeft.y + height < rectScreen.GetBottom() - dlgHeight)
	{
		// put dlg near the bottom of screen (BEW modified 28Feb06 to have -80 rather than -30)
		// because the latter value resulted in the bottom buttons of the dialog being hidden
		// by the status bar at the screen bottom
		SetSize(left,rectScreen.GetBottom()-dlgHeight-80,540,132,wxSIZE_USE_EXISTING);
	}
	else
	{
		// put dlg at the top of the screen
		SetSize(left,rectScreen.GetTop()+40,540,132,wxSIZE_USE_EXISTING);
	}
	
	TransferDataToWindow();

	// call this to set up the initial default condition, provided there will be something
	// in the list to select in the first place (which amounts to the targetUnit existing
	// and having at least one undeleted CRefString)
	if (m_bFoundTgtUnit)
	{
		wxCommandEvent levent;
		OnSelchangeListTranslations(levent);
	}
	else
	{
		// no list box content, so second radio button will be disabled, so make the
		// default button in this case be the first one - ie. to accept the existing transl'n
		wxASSERT(m_pRadioAcceptHere != NULL);
		m_finalAdaptation = m_adaptationStr;
		m_pRadioAcceptHere->SetValue(TRUE);
	}

	// get the dialog to resize to the new label string lengths
	int width = 0;
	int myheight = 0;
	this->GetSize(&width, &myheight);
	// use the difference value calculated above to widen the dialog window and then call
	// Layout() to get the attached sizer hierarchy recalculated and laid out
	int sizeFlags = 0;
	sizeFlags |= wxSIZE_USE_EXISTING;
	int clientWidth = 0;
	int clientHeight = 0;
	CMainFrame *pFrame = gpApp->GetMainFrame();
	pFrame->GetClientSize(&clientWidth,&clientHeight);
    // ensure the adjusted width of the dialog won't exceed the client area's width for the
    // frame window
    if (difference < clientWidth - width)
	{
		this->SetSize(wxDefaultCoord, wxDefaultCoord, width + difference, wxDefaultCoord);
	}else
	{
		this->SetSize(wxDefaultCoord, wxDefaultCoord, clientWidth - 2, wxDefaultCoord);
	}
	this->Layout(); // automatically calls Layout() on top level sizer

	// center it (horizontally)
	if (m_bShowItCentered)
	{
		this->Centre(wxHORIZONTAL);
	}

	saveAdaptationOrGloss = m_adaptationStr; // in case we need to restore 
											 // the box contents at top right 
	EnableAdaptOrGlossBox(FALSE); // this one can be turned on or off, depending
								  // on the radio buttons
	EnableSourceBox(FALSE); // keep it disabled
}

void CConsistencyCheckDlg::EnableAdaptOrGlossBox(bool bEnable)
{
	if (bEnable)
	{
		// make them enabled
		m_pListBox->Enable(TRUE);
		m_pEditCtrlAdaptation->Enable(TRUE);
	}
	else
	{
		// disable them
		m_pListBox->Enable(FALSE);
		m_pEditCtrlAdaptation->Enable(FALSE);
	}
}

void CConsistencyCheckDlg::EnableSourceBox(bool bEnable)
{
	if (bEnable)
	{
		// make enabled
		m_pEditCtrlKey->Enable(TRUE);
	}
	else
	{
		// disable
		m_pEditCtrlKey->Enable(FALSE);
	}
}

// OnOK() calls wxWindow::Validate, then wxWindow::TransferDataFromWindow.
// If this returns TRUE, the function either calls EndModal(wxID_OK) if the
// dialog is modal, or sets the return value to wxID_OK and calls Show(FALSE)
// if the dialog is modeless.
void CConsistencyCheckDlg::OnOK(wxCommandEvent& event) 
{
	//UpdateData(TRUE); // The equivalent of UpdateData() [TransferDataFromWindow()] is not 
						// needed when using wx's validators because they transfer data from 
						// the variable to the control when the dialog is initialized, and 
						// transfer data from the control to the associated variable when 
						// the dialog is dismissed with OnOK() 
	gbIgnoreIt = FALSE;

	m_finalAdaptation = m_adaptationStr;
	event.Skip();
}


// other class methods
/*
void CConsistencyCheckDlg::OnRadioListSelect(wxCommandEvent& WXUNUSED(event)) 
{
	wxString s = _("<no adaptation>");
	
	if (!ListBoxPassesSanityCheck((wxControlWithItems*)m_pListBox))
	{
		wxMessageBox(
_("List box error: probably nothing is selected yet. If so, then select the translation you want to use."), 
		_T(""), wxICON_EXCLAMATION);
	}
	
	int nSel;
	nSel = m_pListBox->GetSelection();
	wxString str = _T("");
	if (nSel != wxNOT_FOUND)
		str = m_pListBox->GetStringSelection();
	if (str == s)
		str = _T(""); // restore null string
	m_finalAdaptation = str;
	
	// also make the relevant radio button be turned on
	wxASSERT(m_pRadioAcceptHere != NULL);
	m_pRadioAcceptHere->SetValue(FALSE);
	wxASSERT(m_pRadioChangeInstead != NULL);
	m_pRadioChangeInstead->SetValue(FALSE);
}
*/

void CConsistencyCheckDlg::OnRadioAcceptHere(wxCommandEvent& WXUNUSED(event)) 
{
	m_adaptationStr = saveAdaptationOrGloss; // restore original adaptation or gloss
	
	// also make the relevant radio button be turned on
	wxASSERT(m_pRadioAcceptHere != NULL);
	m_pRadioAcceptHere->SetValue(TRUE);
	wxASSERT(m_pRadioChangeInstead != NULL);
	m_pRadioChangeInstead->SetValue(FALSE);

	TransferDataToWindow();

	// disable the list and top right text box so it can't be changed from the original
	// value
	EnableAdaptOrGlossBox(FALSE);
}

void CConsistencyCheckDlg::OnRadioChangeInstead(wxCommandEvent& WXUNUSED(event)) 
{
	m_bRadioButtonAction = TRUE;
	
	// also make the relevant radio button be turned on
	wxASSERT(m_pRadioAcceptHere != NULL);
	m_pRadioAcceptHere->SetValue(FALSE);
	wxASSERT(m_pRadioChangeInstead != NULL);
	m_pRadioChangeInstead->SetValue(TRUE);

	EnableAdaptOrGlossBox(TRUE); // turns on both list and top right wxTextCtrl
	
	TransferDataToWindow();

    // BEW added 13Jun09, clicking the radio button should put the input focus in the
    // wxTextCtrl for the "Adaptation text" or "Gloss text"
    wxString s = m_pEditCtrlAdaptation->GetValue();
	long length = (long)s.Len();
	m_pEditCtrlAdaptation->SetSelection(length,length);
	m_pEditCtrlAdaptation->SetFocus();
}

void CConsistencyCheckDlg::OnSelchangeListTranslations(wxCommandEvent& WXUNUSED(event)) 
{
	// wx note: Under Linux/GTK ...Selchanged... listbox events can be triggered after a call to Clear()
	// so we must check to see if the listbox contains no items and if so return immediately
	//if (m_pListBox->GetCount() == 0)
	if (!ListBoxPassesSanityCheck((wxControlWithItems*)m_pListBox))
		return;

	wxString s;
	if (gbIsGlossing)
	{
		s = _("<no gloss>");
	}
	else
	{
		s = _("<no adaptation>");
	}
	int nSel;
	nSel = m_pListBox->GetSelection();
	wxString str = _T("");
	if (nSel != wxNOT_FOUND)
		str = m_pListBox->GetStringSelection();
	if (str == s)
		str = _T(""); // restore null string
	m_adaptationStr = str;

	// also ensure the relevant radio button is turned on
	wxASSERT(m_pRadioAcceptHere != NULL);
	m_pRadioAcceptHere->SetValue(FALSE);
	wxASSERT(m_pRadioChangeInstead != NULL);
	m_pRadioChangeInstead->SetValue(TRUE);

	TransferDataToWindow();
}

/* BEW removed it's wxTextCtrl, use the top right one instead
void CConsistencyCheckDlg::OnUpdateEditTypeNew(wxCommandEvent& event)
{
    // whm 13Jun09 added this OnUpdateEditTypeNew() handler, which is tripped whenever the
    // user types something in the IDC_EDIT_TYPE_NEW wxTextCtrl. It mainly insures that the
    // "No. Instead... different entry ..." radio button is selected as soon as the user
    // starts to type in the edit box.
    // 
    // Make the relevant radio button be turned on, but only if something has been typed
    // into the edit box. If the user deleted everything from the edit box,
	if (m_bRadioButtonAction || m_pEditCtrlNew->GetValue().Length() > 0)
	{
		// The edit control has something in it so ensure the "Type a new one:" radio button is
		// selected and other radio buttons are not selected.
		wxASSERT(m_pRadioAcceptHere != NULL);
		if (m_pRadioAcceptHere->GetValue() != FALSE)
			m_pRadioAcceptHere->SetValue(FALSE);
		wxASSERT(m_pRadioChangeInstead != NULL);
		if (m_pRadioChangeInstead->GetValue() != TRUE)
			m_pRadioChangeInstead->SetValue(TRUE);
		m_bRadioButtonAction = FALSE;
	}
	else
	{
		// The edit control is now empty, so select one of the other radio buttons appropriate to the
		// initial default condition of the data/lists
		if (m_bFoundTgtUnit)
		{
			//wxCommandEvent levent;
			//OnSelchangeListTranslations(levent); // selects top radio button, un-selects bottom two
			wxASSERT(m_pRadioAcceptHere != NULL);
			if (m_pRadioAcceptHere->GetValue() != FALSE)
				m_pRadioAcceptHere->SetValue(FALSE);
			wxASSERT(m_pRadioChangeInstead != NULL);
			if (m_pRadioChangeInstead->GetValue() != FALSE)
				m_pRadioChangeInstead->SetValue(FALSE);
		}
		else
		{
            // No list box content, nevertheless ensure that the lower radiobutton is on
            // i.e., to accept the existing translation.
			wxASSERT(m_pRadioAcceptHere != NULL);
			if (m_pRadioAcceptHere->GetValue() != FALSE)
				m_pRadioAcceptHere->SetValue(FALSE);
			wxASSERT(m_pRadioChangeInstead != NULL);
			if (m_pRadioChangeInstead->GetValue() != TRUE)
				m_pRadioChangeInstead->SetValue(TRUE);
		}
	}

	TransferDataFromWindow();

	// The docs for wxActivateEvent say skip should be called somewhere in the handler,
	// otherwise strange behavior may occur.
	event.Skip();
}
*/