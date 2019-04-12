#ifndef MYTHREAD_H
#define MYTHREAD_H

#include "wx/wx.h"
#include "wx/thread.h"
#include <wx/url.h>
#include <wx/stream.h>
#include <wx/sstream.h>

DECLARE_EVENT_TYPE(wxEVT_MY_EVENT, -1)

class MyThread : public wxThread
{
private:
    int start;
    int ending;
    wxURL *url;
    wxString *urlList;
    wxString *wordList;
    wxString *data;
    int *statusList;
    int *wordCount;
    int threadNumber;
    wxEvtHandler *eventHandler;
    wxInputStream *in_stream;

public:
    MyThread(
             wxEvtHandler *eventHandler,
             int start,
             int ending,
             wxURL *url,
             wxString *urlList,
             wxString *wordList,
             int *wordCount,
             int *statusList,
             int);
    virtual void *Entry();
    virtual ~MyThread();
    void Download(wxString wxUrl);
    int GetDataStart();
    int GetDataEnd();
};

#endif // MYTHREAD_H
