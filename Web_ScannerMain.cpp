/***************************************************************
 * Name:      Web_ScannerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Javier Vega ()
 * Created:   2019-03-24
 * Copyright: Javier Vega ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "Web_ScannerMain.h"
#include <wx/msgdlg.h>
#include <wx/url.h>
#include <wx/stream.h>
#include <wx/sstream.h>
#include <wx/textfile.h>

//(*InternalHeaders(Web_ScannerFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(Web_ScannerFrame)
const long Web_ScannerFrame::ID_GO_BUTTON = wxNewId();
const long Web_ScannerFrame::ID_BUTTON1 = wxNewId();
const long Web_ScannerFrame::ID_BUTTON2 = wxNewId();
const long Web_ScannerFrame::ID_QUIT_BUTTON = wxNewId();
const long Web_ScannerFrame::ID_TEXTCTRL1 = wxNewId();
const long Web_ScannerFrame::ID_WORD_TEXTCTRL = wxNewId();
const long Web_ScannerFrame::ID_LISTBOX = wxNewId();
const long Web_ScannerFrame::ID_PROGRESS = wxNewId();
const long Web_ScannerFrame::ID_STATICTEXT1 = wxNewId();
const long Web_ScannerFrame::ID_MAIN_PANEL = wxNewId();
const long Web_ScannerFrame::idMenuQuit = wxNewId();
const long Web_ScannerFrame::idMenuAbout = wxNewId();
const long Web_ScannerFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Web_ScannerFrame,wxFrame)
    //(*EventTable(Web_ScannerFrame)
    //*)
END_EVENT_TABLE()

Web_ScannerFrame::Web_ScannerFrame(wxWindow* parent,wxWindowID id)
{
    urlFileName = "";
    wordFileName = "";

    //(*Initialize(Web_ScannerFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Main_Panel = new wxPanel(this, ID_MAIN_PANEL, wxDefaultPosition, wxSize(550,380), wxTAB_TRAVERSAL, _T("ID_MAIN_PANEL"));
    Go_Button = new wxButton(Main_Panel, ID_GO_BUTTON, _("GO"), wxPoint(24,340), wxDefaultSize, 0, wxDefaultValidator, _T("ID_GO_BUTTON"));
    Load_Url_Button = new wxButton(Main_Panel, ID_BUTTON1, _("URL"), wxPoint(432,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Load_Url_Button->SetToolTip(_("Load URL List"));
    Load_Word_Button = new wxButton(Main_Panel, ID_BUTTON2, _("Word"), wxPoint(432,104), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Load_Word_Button->SetToolTip(_("Load Word List"));
    Quit_Button = new wxButton(Main_Panel, ID_QUIT_BUTTON, _("Quit"), wxPoint(152,340), wxDefaultSize, 0, wxDefaultValidator, _T("ID_QUIT_BUTTON"));
    URL_TextCtrl = new wxTextCtrl(Main_Panel, ID_TEXTCTRL1, wxEmptyString, wxPoint(24,50), wxSize(344,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    Word_TextCtrl = new wxTextCtrl(Main_Panel, ID_WORD_TEXTCTRL, wxEmptyString, wxPoint(24,100), wxSize(345,27), 0, wxDefaultValidator, _T("ID_WORD_TEXTCTRL"));
    ListBox = new wxListBox(Main_Panel, ID_LISTBOX, wxPoint(24,150), wxSize(344,170), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX"));
    Progress = new wxGauge(Main_Panel, ID_PROGRESS, 100, wxPoint(320,340), wxSize(200,28), 0, wxDefaultValidator, _T("ID_PROGRESS"));
    StaticText1 = new wxStaticText(Main_Panel, ID_STATICTEXT1, _("Web Scanner"), wxPoint(248,16), wxSize(96,16), 0, _T("ID_STATICTEXT1"));
    BoxSizer1->Add(Main_Panel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_GO_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Web_ScannerFrame::OnGo_ButtonClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Web_ScannerFrame::OnLoad_Url_ButtonClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Web_ScannerFrame::OnLoad_Word_ButtonClick);
    Connect(ID_QUIT_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Web_ScannerFrame::OnQuit);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Web_ScannerFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Web_ScannerFrame::OnAbout);
    //*)
}

Web_ScannerFrame::~Web_ScannerFrame()
{
    //(*Destroy(Web_ScannerFrame)
    //*)
}

void Web_ScannerFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Web_ScannerFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void Web_ScannerFrame::OnGo_ButtonClick(wxCommandEvent& event)
{
    // checks if the files have been selected
    if(urlFileName != "" && wordFileName != "")
    {
        wxTextFile urlFile;
        wxTextFile wordFile;

        urlFile.Open(urlFileName);
        wordFile.Open(wordFileName);

        wxString line = urlFile.GetFirstLine();
        wxArrayString strings;

        int urlCount = 1;
        int linePercent = Progress->GetRange() / urlFile.GetLineCount();
        Progress->SetValue(0);

        do
        {
            wxURL url(line);

            // checks if there is any error with url
            if (url.GetError() == wxURL_NOERR)
            {
                int wordCount = 0;
                wxString data;
                urlCount++;

                wxInputStream *in_stream = url.GetInputStream();

                if(in_stream && in_stream->IsOk())
                {
                    wordFile.GoToLine(0);
                    wxString word = wordFile.GetFirstLine();

                    wxStringOutputStream html_stream(&data);
                    in_stream->Read(html_stream);

                    do
                    {
                        size_t pos = 0;

                        while(pos < data.Length())
                        {
                            pos = data.find(word, pos + word.Length());

                            if(pos != wxNOT_FOUND){
                                wordCount++;
                            }
                        }

                        word = wordFile.GetNextLine();

                    } while(!wordFile.Eof());

                    strings.Add(line  + "\t" + word + "\t" + wxString::Format(wxT("%i"), wordCount));
                }
                delete in_stream;
            }

            Progress->SetValue((Progress->GetValue() + linePercent));

            line = urlFile.GetNextLine();

        } while(!urlFile.Eof());

        urlFile.Close();
        wordFile.Close();

        this->Progress->SetValue(Progress->GetRange());
        this->ListBox->Append(strings);
    }
    else if(urlFileName == "" && wordFileName != "")
    {
         wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("No URL File Selected."),
                                                     wxT("Error"), wxOK | wxICON_ERROR);
        dial->ShowModal();
    }
    else if(urlFileName != "" && wordFileName == "")
    {
         wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("No Word File Selected."),
                                                     wxT("Error"), wxOK | wxICON_ERROR);
        dial->ShowModal();
    }
    else {
         wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("No File Selected."),
                                                     wxT("Error"), wxOK | wxICON_ERROR);
        dial->ShowModal();
    }
}

void Web_ScannerFrame::OnLoad_Url_ButtonClick(wxCommandEvent& event)
{
    wxString caption = wxT("Load URL File");
    wxString wildcard = wxT("TEXT files (*.txt)|*.txt");
    wxString defaultDir = wxGetCwd();
    wxString defaultFilename = wxEmptyString;

    wxFileDialog dialog(this, caption, defaultDir, defaultFilename,
        wildcard, wxFC_OPEN);

    //checks if the user wants to load a drawing.
    if(dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();

        urlFileName = path;
        this->URL_TextCtrl->AppendText(urlFileName);
    }
    dialog.Close();
}

void Web_ScannerFrame::OnLoad_Word_ButtonClick(wxCommandEvent& event)
{
    wxString caption = wxT("Load Word File");
    wxString wildcard = wxT("TEXT files (*.txt)|*.txt");
    wxString defaultDir = wxGetCwd();
    wxString defaultFilename = wxEmptyString;

    wxFileDialog dialog(this, caption, defaultDir, defaultFilename,
        wildcard, wxFC_OPEN);

    //checks if the user wants to load a drawing.
    if(dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();

        wordFileName = path;
        this->Word_TextCtrl->AppendText(wordFileName);
    }
    dialog.Close();
}
