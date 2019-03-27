/***************************************************************
 * Name:      Web_ScannerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Javier Vega ()
 * Created:   2019-03-24
 * Copyright: Javier Vega ()
 * License:
 **************************************************************/

#ifndef WEB_SCANNERMAIN_H
#define WEB_SCANNERMAIN_H

//(*Headers(Web_ScannerFrame)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
//*)


class Web_ScannerFrame: public wxFrame
{
    public:

        Web_ScannerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Web_ScannerFrame();

    private:
        wxString urlFileName;
        wxString wordFileName;

        //(*Handlers(Web_ScannerFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnRichTextCtrl1Text(wxCommandEvent& event);
        void OnGo_ButtonClick(wxCommandEvent& event);
        void OnLoad_Url_ButtonClick(wxCommandEvent& event);
        void OnLoad_Word_ButtonClick(wxCommandEvent& event);
        void OnListBoxSelect(wxCommandEvent& event);
        //*)

        //(*Identifiers(Web_ScannerFrame)
        static const long ID_GO_BUTTON;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_QUIT_BUTTON;
        static const long ID_TEXTCTRL1;
        static const long ID_WORD_TEXTCTRL;
        static const long ID_LISTBOX;
        static const long ID_MAIN_PANEL;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(Web_ScannerFrame)
        wxListBox* ListBox;
        wxStatusBar* StatusBar1;
        wxPanel* Main_Panel;
        wxTextCtrl* Word_TextCtrl;
        wxButton* Quit_Button;
        wxButton* Load_Url_Button;
        wxButton* Go_Button;
        wxTextCtrl* URL_TextCtrl;
        wxButton* Load_Word_Button;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WEB_SCANNERMAIN_H
