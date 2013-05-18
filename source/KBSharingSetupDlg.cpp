/////////////////////////////////////////////////////////////////////////////
/// \project		adaptit
/// \file			KBSharingSetupDlg.h
/// \author			Bruce Waters
/// \date_created	15 January 2013
/// \rcs_id $Id: KBSharingSetupDlg.h 3028 2013-01-15 11:38:00Z jmarsden6@gmail.com $
/// \copyright		2013 Bruce Waters, Bill Martin, SIL International
/// \license		The Common Public License or The GNU Lesser General Public License (see license directory)
/// \description	This is the implementation file for the KBSharingSetupDlg class.
/// The KBSharingSetupDlg class provides two text boxes, the first for the KB server's URL,
/// the second for the username --the user's email address is recommended, but not
/// enforced. It's best because it will be unique. The KB server's password is not
/// entered in the dialog, otherwise it would be visible. Instead, a password dialog is
/// shown when the OK button is clicked. (The password dialog appears at other times too -
/// such as when turning ON KB sharing after it has been off, or when reentering a KB
/// sharing project previously designed as one for sharing of the KB.)
/// \derivation		The KBSharingSetupDlg class is derived from AIModalDialog.
/////////////////////////////////////////////////////////////////////////////
// Pending Implementation Items in KBSharingSetupDlg.cpp (in order of importance): (search for "TODO")
// 1.
//
// Unanswered questions: (search for "???")
// 1.
//
/////////////////////////////////////////////////////////////////////////////

// the following improves GCC compilation performance
#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma implementation "KBSharingSetupDlg.h"
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

#if defined(_KBSERVER)

// other includes
//#include <wx/docview.h> // needed for classes that reference wxView or wxDocument
#include "Adapt_It.h"
#include "MainFrm.h"
#include "KbServer.h"
#include "KBSharingSetupDlg.h"

/// This global is defined in Adapt_It.cpp.
//extern CAdapt_ItApp* gpApp; // if we want to access it fast

// event handler table
BEGIN_EVENT_TABLE(KBSharingSetupDlg, AIModalDialog)
	EVT_INIT_DIALOG(KBSharingSetupDlg::InitDialog)
	EVT_BUTTON(wxID_OK, KBSharingSetupDlg::OnOK)
	EVT_BUTTON(wxID_CANCEL, KBSharingSetupDlg::OnCancel)
	EVT_BUTTON(ID_KB_SHARING_REMOVE_SETUP, KBSharingSetupDlg::OnButtonRemoveSetup)
	EVT_UPDATE_UI(ID_KB_SHARING_REMOVE_SETUP, KBSharingSetupDlg::OnUpdateButtonRemoveSetup)
	//EVT_BUTTON(ID_GET_ALL, KBSharingSetup::OnBtnGetAll)

END_EVENT_TABLE()


KBSharingSetupDlg::KBSharingSetupDlg(wxWindow* parent) // dialog constructor
	: AIModalDialog(parent, -1, _("Setup Or Remove Knowledge Base Sharing"),
				wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{

	// This dialog function below is generated in wxDesigner, and defines the controls and sizers
	// for the dialog. The first parameter is the parent which should normally be "this".
	// The second and third parameters should both be TRUE to utilize the sizers and create the right
	// size dialog.
	kb_sharing_setup_func(this, TRUE, TRUE);
	// The declaration is: functionname( wxWindow *parent, bool call_fit, bool set_sizer );
	m_pApp = &wxGetApp();
	bool bOK;
	bOK = m_pApp->ReverseOkCancelButtonsForMac(this);
	bOK = bOK; // avoid warning

}

KBSharingSetupDlg::~KBSharingSetupDlg() // destructor
{

}

void KBSharingSetupDlg::InitDialog(wxInitDialogEvent& WXUNUSED(event))
{
	m_saveOldURLStr = m_pApp->m_strKbServerURL; // save existing value (could be empty)
	m_saveOldUsernameStr = m_pApp->m_strUserID; // ditto
	m_savePassword = m_pApp->GetMainFrame()->GetKBSvrPassword(); // might be empty
	m_saveIsONflag = m_pApp->m_bIsKBServerProject;

	m_pURLCtrl = (wxTextCtrl*)FindWindowById(ID_TEXTCTRL_SERVER_URL);
	m_pUsernameCtrl = (wxTextCtrl*)FindWindowById(ID_TEXTCTRL_USERNAME);

	// if the app members have values for the url and username already (from having been
	// just set earlier, or from the project config file, then reinstate them so that if
	// the kb sharing was turned off it can be quickly re-enabled
	if (!m_pApp->m_strKbServerURL.IsEmpty())
	{
		m_pURLCtrl->ChangeValue(m_pApp->m_strKbServerURL);
	}
	if (!m_pApp->m_strUserID.IsEmpty())
	{
		m_pUsernameCtrl->ChangeValue(m_pApp->m_strUserID);
	}
}

void KBSharingSetupDlg::OnOK(wxCommandEvent& myevent)
{
	wxString strURL;
	strURL = m_pURLCtrl->GetValue();
	if (strURL.IsEmpty())
	{
		wxString msg = _("The URL text box at the top is empty, please type the address of the server.");
		wxString title = _("Type URL");
		wxMessageBox(msg, title, wxICON_EXCLAMATION | wxOK);
		return;
	}

	wxString strUsername;
	strUsername = m_pUsernameCtrl->GetValue();
	if (strUsername.IsEmpty())
	{
		wxString msg = _("The username text box is empty, please type the username you have been given.");
		wxString title = _("Type Username");
		wxMessageBox(msg, title, wxICON_EXCLAMATION | wxOK);
		return;
	}

	// Get the server password. Returns an empty string if nothing is typed, or if the
	// user Cancels from the dialog
	CMainFrame* pFrame = m_pApp->GetMainFrame();
	wxString pwd = pFrame->GetKBSvrPasswordFromUser();
	// there will be a beep if no password was typed, or it the user cancelled; and an
	// empty string is returned if so
	if (!pwd.IsEmpty())
	{
		pFrame->SetKBSvrPassword(pwd); // store the password in CMainFrame's instance,
									   // ready for SetupForKBServer() below to use it

		// What we do next will depend on what the current state is for KB Sharing within
		// this project. There are 3 possibilities. 
		// 1. This server url and username are already in effect and this project is a kb
		// sharing one already - that is, there was no point in the user opening the
		// dialog unless he misspelled the password and needs to make a second attempt at it.
		// 2. This project is not a KB sharing one yet, or KB sharing was previously
		// defined for it, but whichever is the case, KB sharing is turned off (ie. 
		// m_bIsKBServerProject is currently FALSE. This setup therefore turns it on with
		// the credentials supplied. (If the credentials have typos, error messages when
		// transmissions are done will indicate the problem. It would be good to have a
		// URL checker from somewhere if we can find one, too.
		// 3. There was a different server connected to before the dialog was opened, and
		// the user wants to use a different KB server - in this case, detect that the
		// settings have changed, and if so, shut down the old setup and establish the new
		// one with the new credentials just typed.
		
		// set the url and username into the app's member variables for these, so that the
		// project configuration file can store them permanently, and SetupForKBServer()
		// will need to call them too
		m_pApp->m_strKbServerURL = strURL;
		m_pApp->m_strUserID = strUsername;

		if (m_saveOldURLStr == strURL && m_saveOldUsernameStr == strUsername)
		{
			// user has unchanged credentials, maybe he needs to retype the password; so
			// clobber the old setting and setup again with the newer one
			if (m_pApp->m_bIsKBServerProject)
			{
				// there's an attempted share already defined for this project, so remove
				// it and re-establish it
				m_pApp->ReleaseKBServer(1); // the adaptations one
				m_pApp->ReleaseKBServer(2); // the glossings one
			}
			m_pApp->m_bIsKBServerProject = TRUE;
			m_pApp->LogUserAction(_T("SetupForKBServer() re-attempted in setup dialog"));
			// instantiate an adapting and a glossing KbServer class instance
			if (!m_pApp->SetupForKBServer(1) || !m_pApp->SetupForKBServer(2))
			{
				// an error message will have been shown, so just log the failure
				m_pApp->LogUserAction(_T("SetupForKBServer() failed on this re-attempt)"));
				return;
			}
		}
		else if(m_pApp->m_bIsKBServerProject)
		{
			// This project is a KB sharing one, and the settings wanted have changed, so
			// remove the old settings and set up with the new credentials
			m_pApp->ReleaseKBServer(1); // the adaptations one
			m_pApp->ReleaseKBServer(2); // the glossings one
			m_pApp->LogUserAction(_T("Switching server or correcting mistyped credentials: SetupForKBServer() is about to be called"));
			// instantiate an adapting and a glossing KbServer class instance
			if (!m_pApp->SetupForKBServer(1) || !m_pApp->SetupForKBServer(2))
			{
				// an error message will have been shown, so just log the failure
				m_pApp->LogUserAction(_T("SetupForKBServer(): setup failed"));
				return;
			}
		}
		else
		{
			// This project is not currently one designated for KB sharing, so use the
			// credentials supplied to turn KB sharing ON
			m_pApp->m_bIsKBServerProject = TRUE;
			m_pApp->LogUserAction(_T("Not currently sharing, and SetupForKBServer() is about to be called"));
			// instantiate an adapting and a glossing KbServer class instance
			if (!m_pApp->SetupForKBServer(1) || !m_pApp->SetupForKBServer(2))
			{
				// an error message will have been shown, so just log the failure
				m_pApp->LogUserAction(_T("SetupForKBServer(): setup failed"));
				return;
			}
		}

		// ensure sharing starts off enabled
		m_pApp->GetKbServer(1)->EnableKBSharing(TRUE);
		m_pApp->GetKbServer(2)->EnableKBSharing(TRUE);

		myevent.Skip(); // the dialog will be exited now
	}
	else
	{
		// tell the user that a password is needed
		wxString msg = _("No password was typed. Setup is incomplete without a correct password\nIf you do not know the password, click the Remove Setup button, then ask your administrator to help you setup.");
		wxString title = _("Type The Password");
		wxMessageBox(msg, title, wxICON_EXCLAMATION | wxOK);
		return;
	}
}

void KBSharingSetupDlg::OnCancel(wxCommandEvent& myevent)
{
	// Do nothing, change no settings; so restore what was saved
	m_pApp->m_strKbServerURL = m_saveOldURLStr;
	m_pApp->m_strUserID = m_saveOldUsernameStr;
	m_pApp->GetMainFrame()->SetKBSvrPassword(m_savePassword);
	m_pApp->m_bIsKBServerProject = m_saveIsONflag;

	myevent.Skip();
}

void KBSharingSetupDlg::OnUpdateButtonRemoveSetup(wxUpdateUIEvent& event)
{
	if (m_pApp->m_bIsKBServerProject)
	{
		event.Enable(TRUE);
	}
	else
	{
		event.Enable(FALSE);
	}
}

void KBSharingSetupDlg::OnButtonRemoveSetup(wxCommandEvent& WXUNUSED(event))
{
	m_pApp->m_bIsKBServerProject = FALSE;
	m_pApp->ReleaseKBServer(1); // the adaptations one
	m_pApp->ReleaseKBServer(2); // the glossings one

    // Removal of the sharing status for this Adapt It project may not be permanent, so
    // removal should not clear the server's url, nor the username for access. So the next
    // two lines are commented out. If we change this protocol, then uncomment them out.
    // For temporary removal & later re-enabling it is better to use the Disable Sharing /
    // Enable Sharing button though, because the password doesn't need to be retyped
	//m_pApp->m_strKbServerURL.Empty();
	//m_pApp->m_strUserID.Empty();
	
	// While we don't change the app members, the removal should clear the text boxes in
	// the dialog so that the user has feedback that the removal has been effected. To
	// reinstate the setup immediately he either must retype the information into the text
	// boxes, or click OK and then reopen the dialog (the text boxes will be filled with
	// the earlier values automatically) and click OK (and give the password of course)
	m_pURLCtrl->Clear();
	m_pUsernameCtrl->Clear();

	// make the dialog close (a good way to say, "it's been done";
	// also, we don't want a subsequent OK button click, because the user would then see a
	// message about the empty top editctrl, etc
	EndModal(wxID_OK);
}

#endif
