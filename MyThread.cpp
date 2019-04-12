#include "MyThread.h"

DEFINE_EVENT_TYPE(wxEVT_MY_EVENT)

MyThread::MyThread(
                   wxEvtHandler *eventHandler,
                   int start,
                   int ending,
                   wxURL *url,
                   wxString *urlList,
                   wxString *wordList,
                   int *wordCount,
                   int *statusList,
                   int threadNumber)
    : wxThread()
{
    this->start = start;
    this->ending = ending;
    this->url = url;
    this->urlList = urlList;
    this->wordList = wordList;
    this->statusList = statusList;
    this->wordCount = wordCount;
    this->threadNumber = threadNumber;
    this->eventHandler = eventHandler;
}

MyThread::~MyThread()
{
}

void *MyThread::Entry()
{
    for(size_t i = start; i < ending - 1; i++)
    {
        wxString u = urlList[i];
        int wordCount = 0;
        Download(urlList[i]);
        for(size_t j = 0; j < wordList->length(); j++)
        {
            wxString word = wordList[j];
            size_t pos = 0;

            while(pos < data->Length())
            {
                pos = data->find(word, pos + word.Length());

                if(pos != wxNOT_FOUND){
                    wordCount++;
                }
            }
        }
        this->wordCount[i] = wordCount;
    }
    statusList[threadNumber] = 1;

    delete data;
    data = NULL;

    wxThreadEvent *event = new wxThreadEvent();
    eventHandler->AddPendingEvent(*event);

    return NULL;
}

int MyThread::GetDataStart()
{
    return start;
}

int MyThread::GetDataEnd()
{
    return ending;
}

void MyThread::Download(wxString theUrl)
{
    url->SetURL(theUrl);

    if (this->url->GetError() == wxURL_NOERR)
    {
         data = new wxString();

         in_stream = url->GetInputStream();

         if(in_stream && in_stream->IsOk())
         {
             wxStringOutputStream html_stream(data);
             in_stream->Read(html_stream);
         }
    }
}
