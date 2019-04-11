#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "wx/wx.h"
#include "wx/thread.h"
#include <wx/url.h>
#include <wx/stream.h>
#include <wx/sstream.h>

class MyThread : public wxThread
{
private:
    int start;
    int ending;
    int progress;
    wxString *wordList;
    wxString *dataList;
    int *statusList;

public:
    MyThread(int start, int ending, wxString *dataList, wxString *wordList, int *statusList);
    virtual void *Entry();
    virtual ~MyThread();
    wxString Download(wxString line);
};

#endif // MYTHREAD_H