/***************************************************************
 * Name:      Web_ScannerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Javier Vega ()
 * Created:   2019-03-24
 * Copyright: Javier Vega ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "Web_ScannerApp.h"

//(*AppHeaders
#include "Web_ScannerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(Web_ScannerApp);

bool Web_ScannerApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	Web_ScannerFrame* Frame = new Web_ScannerFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
