/////////////////////////////////////////////////////////////////////////////
/// \project		adaptit
/// \file			GuesserSettingsDlg.cpp
/// \author			Bill Martin
/// \date_created	27 January 2010
/// \rcs_id $Id$
/// \copyright		2010 Bruce Waters, Bill Martin, SIL International
/// \license		The Common Public License or The GNU Lesser General Public License (see license directory)
/// \description	This is the implementation file for the CGuesserSettingsDlg class. 
/// The CGuesserSettingsDlg class provides a dialog in which the user can change the basic
/// settings for the Guesser.
/// \derivation		The CGuesserSettingsDlg class is derived from AIModalDialog.
/////////////////////////////////////////////////////////////////////////////
// Pending Implementation Items in GuesserSettingsDlg.cpp (in order of importance): (search for "TODO")
// 1. 
//
// Unanswered questions: (search for "???")
// 1. 
// 
/////////////////////////////////////////////////////////////////////////////

// the following improves GCC compilation performance
#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma implementation "GuesserSettingsDlg.h"
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
#include "Adapt_It.h"
#include <wx/docview.h> // needed for classes that reference wxView or wxDocument
#include <wx/valgen.h> // for wxGenericValidator
//#include <wx/valtext.h> // for wxTextValidator
#include <wx/colordlg.h>
#include "GuesserAffixesListsDlg.h"
#include "GuesserSettingsDlg.h"
#include "KB.h"

// event handler table
BEGIN_EVENT_TABLE(CGuesserSettingsDlg, AIModalDialog)
	EVT_INIT_DIALOG(CGuesserSettingsDlg::InitDialog)
	EVT_BUTTON(ID_BUTTON_GUESS_HIGHLIGHT_COLOR, CGuesserSettingsDlg::OnChooseGuessHighlightColor)
	EVT_BUTTON(wxID_OK, CGuesserSettingsDlg::OnOK)
	EVT_BUTTON(wxID_CANCEL, CGuesserSettingsDlg::OnCancel)
	EVT_BUTTON(ID_BTN_GUESSER_HOW_TO_USE_DLG, CGuesserSettingsDlg::OnSuffixesAndPrefixesListsDlg)	
END_EVENT_TABLE()

CGuesserSettingsDlg::CGuesserSettingsDlg(wxWindow* parent) // dialog constructor
	: AIModalDialog(parent, -1, _("Guesser Settings Dialog"),
				wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	// This dialog function below is generated in wxDesigner, and defines the controls and sizers
	// for the dialog. The first parameter is the parent which should normally be "this".
	// The second and third parameters should both be TRUE to utilize the sizers and create the right
	// size dialog.
	GuesserSettingsDlgFunc(this, TRUE, TRUE);
	// The declaration is: NameFromwxDesignerDlgFunc( wxWindow *parent, bool call_fit, bool set_sizer );
	
	m_pApp = &wxGetApp();

	// use wxValidator for simple dialog data transfer
	// sample text control initialization below:
	pCheckUseGuesser = (wxCheckBox*)FindWindowById(ID_CHECK_USE_GUESSER);
	wxASSERT(pCheckUseGuesser != NULL);
	//pCheckUseGuesser->SetValidator(wxGenericValidator(&bUseAdaptationsGuesser));

	pSlider = (wxSlider*)FindWindowById(ID_SLIDER_GUESSER);
	wxASSERT(pSlider != NULL);
	//pSlider->SetValidator(wxGenericValidator(&nGuessingLevel));

	pAllowGuessertoOperateOnUnchangedOutput = (wxCheckBox*)FindWindowById(ID_CHECK_ALLOW_GUESSER_ON_UNCHANGED_CC_OUTPUT);
	wxASSERT(pAllowGuessertoOperateOnUnchangedOutput != NULL);
	//pAllowGuessertoOperateOnUnchangedOutput->SetValidator(wxGenericValidator(&bAllowGuesseronUnchangedCCOutput));

	pStaticTextNumCorInAdaptationsGuesser = (wxStaticText*)FindWindowById(ID_TEXT_STATIC_NUM_CORRESP_ADAPTATIONS_GUESSER);
	wxASSERT(pStaticTextNumCorInAdaptationsGuesser != NULL);

	pStaticTextNumCorInGlossingGuesser = (wxStaticText*)FindWindowById(ID_TEXT_STATIC_NUM_CORRESP_GLOSSING_GUESSER);
	wxASSERT(pStaticTextNumCorInGlossingGuesser != NULL);

	pPanelGuessColorDisplay = (wxPanel*)FindWindowById(ID_PANEL_GUESS_COLOR_DISPLAY);
	wxASSERT(pPanelGuessColorDisplay != NULL);

	m_pSuffixesAndPrefixesListsDlg = (wxButton*)FindWindowById(ID_BTN_GUESSER_HOW_TO_USE_DLG);
	wxASSERT(m_pSuffixesAndPrefixesListsDlg != NULL);

	bool bOK;
	bOK = m_pApp->ReverseOkCancelButtonsForMac(this);
	bOK = bOK; // avoid warning
	// other attribute initializations
}

CGuesserSettingsDlg::~CGuesserSettingsDlg() // destructor
{
	
}

void CGuesserSettingsDlg::OnCancel(wxCommandEvent& event)
{
	event.Skip();
}

void CGuesserSettingsDlg::InitDialog(wxInitDialogEvent& WXUNUSED(event)) // InitDialog is method of wxWindow
{
	//CAdapt_ItApp* pApp = &wxGetApp();
	//InitDialog() is not virtual, no call needed to a base class
	bUseAdaptationsGuesser = m_pApp->m_bUseAdaptationsGuesser;
	if (bUseAdaptationsGuesser)
	{
		// If turned on, make sure that the app variables are initialized...
		// Guesser support - initialize the current counts for each KB  (first 4 maps only)
		// if guessing is already on.
		if (m_pApp->m_bUseAdaptationsGuesser)
		{
			if (m_pApp->m_pKB != NULL && m_pApp->m_bKBReady)
			{
				m_pApp->m_pKB->GetMinimumExtras(m_pApp->m_numLastEntriesAggregate); // ignore returned minimumExtras value
			}
			if (m_pApp->m_pGlossingKB != NULL && m_pApp->m_bGlossingKBReady)
			{
				m_pApp->m_pGlossingKB->GetMinimumExtras(m_pApp->m_numLastGlossingEntriesAggregate); // ignore returned minimumExtras value
			}
		}
	}
	nGuessingLevel = m_pApp->m_nGuessingLevel;
	bAllowGuesseronUnchangedCCOutput = m_pApp->m_bAllowGuesseronUnchangedCCOutput;
	pCheckUseGuesser->SetValue(bUseAdaptationsGuesser);
	pSlider->SetValue(nGuessingLevel);
	pAllowGuessertoOperateOnUnchangedOutput->SetValue(bAllowGuesseronUnchangedCCOutput);
	tempGuessHighlightColor = m_pApp->m_GuessHighlightColor;
	nCorrespondencesLoadedInAdaptationsGuesser = m_pApp->m_nCorrespondencesLoadedInAdaptationsGuesser;
	nCorrespondencesLoadedInGlossingGuesser = m_pApp->m_nCorrespondencesLoadedInGlossingGuesser;
	wxString nCAStr;
	nCAStr.Empty();
	nCAStr << nCorrespondencesLoadedInAdaptationsGuesser;
	wxString nCGStr;
	nCGStr.Empty();
	nCGStr << nCorrespondencesLoadedInGlossingGuesser;
	pStaticTextNumCorInAdaptationsGuesser->SetLabel(nCAStr);
	pStaticTextNumCorInGlossingGuesser->SetLabel(nCGStr);
	pPanelGuessColorDisplay->SetBackgroundColour(m_pApp->m_GuessHighlightColor);
	pPanelGuessColorDisplay->Refresh();
}

// event handling functions

void CGuesserSettingsDlg::OnChooseGuessHighlightColor(wxCommandEvent& WXUNUSED(event))
{
	// Invoke the wxColorDlg
	wxColourData colorData;
	colorData.SetColour(tempGuessHighlightColor);
	colorData.SetChooseFull(TRUE);
	wxColourDialog colorDlg(this,&colorData);
	colorDlg.Centre();
	if(colorDlg.ShowModal() == wxID_OK)
	{
		colorData = colorDlg.GetColourData();
		tempGuessHighlightColor  = colorData.GetColour();
		pPanelGuessColorDisplay->SetBackgroundColour(tempGuessHighlightColor);
		pPanelGuessColorDisplay->Refresh();
	}	
}

void CGuesserSettingsDlg::OnSuffixesAndPrefixesListsDlg(wxCommandEvent& WXUNUSED(event))
{
	GuesserAffixesListsDlg guesserListsDlg(this); // make the CGuesserSettingsDlg the parent in this case
	guesserListsDlg.Center();
	int returnValue = guesserListsDlg.ShowModal();
	if (returnValue == wxID_CANCEL)
	{
		// user cancelled
		return;
	}
	else
	{
		// all was well
		return;
	}
}

//CGuesserSettingsDlg::OnUpdateDoSomething(wxUpdateUIEvent& event)
//{
//	if (SomeCondition == TRUE)
//		event.Enable(TRUE);
//	else
//		event.Enable(FALSE);	
//}

// OnOK() calls wxWindow::Validate, then wxWindow::TransferDataFromWindow.
// If this returns TRUE, the function either calls EndModal(wxID_OK) if the
// dialog is modal, or sets the return value to wxID_OK and calls Show(FALSE)
// if the dialog is modeless.
// 
void CGuesserSettingsDlg::OnOK(wxCommandEvent& event) 
{
    // BEW 23May13, Added next line because if the user unticked the checkbox, the new
    // value of FALSE was not picked up, and the setting stayed TRUE
	bUseAdaptationsGuesser = pCheckUseGuesser->GetValue();

	// If it was just turned on, then we have to initialize the app's aggregate counts...
	// so that OnIdle()'s support of the guesser works right
	if (bUseAdaptationsGuesser)
	{
		// Guesser support - initialize the current counts for each KB  (first 4 maps only)
		// if guessing is to be on
		if (m_pApp->m_bUseAdaptationsGuesser)
		{
			if (m_pApp->m_pKB != NULL && m_pApp->m_bKBReady)
			{
				m_pApp->m_pKB->GetMinimumExtras(m_pApp->m_numLastEntriesAggregate); // ignore returned minimumExtras value
			}
			if (m_pApp->m_pGlossingKB != NULL && m_pApp->m_bGlossingKBReady)
			{
				m_pApp->m_pGlossingKB->GetMinimumExtras(m_pApp->m_numLastGlossingEntriesAggregate); // ignore returned minimumExtras value
			}
		}
	}
	// BEW added 27Nov14, there was no setting m_bGuessingLevel using the final value of
	// nGuessingLevel, and so when the dialog was closed, the default 50% was immediately
	// reinstated! So fix this here, if use of the guesser is still wanted
	if (bUseAdaptationsGuesser)
	{
		nGuessingLevel = pSlider->GetValue();
		// m_nGuessingLevel is what gets written to the project config file. Don't set it
		// here because the success block in the caller must compare old and potentially new
		// value to see if they are different, and if they are, to have LoadGuesser() called
		// twice again, once on the adapting kb, and again on the glossing kb
	}

	// Note: The App's member values are updated in CAdapt_ItView::OnButtonGuesserSettings()
	// and LoadGuesser() called if necessary, by comparing this local class' values with 
	// those on the App (for detecting changes made in this dialog class).
	event.Skip(); //EndModal(wxID_OK); //AIModalDialog::OnOK(event); // not virtual in wxDialog
}



// other class methods

