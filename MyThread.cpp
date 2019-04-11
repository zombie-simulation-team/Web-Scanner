#include "MyThread.h"

MyThread::MyThread(int start, int ending, wxString *dataList, wxString *wordList, int *wordCount, int *statusList, int threadNumber)
    : wxThread(wxTHREAD_JOINABLE)
{
    this->start = start;
    this->ending = ending;
    this->dataList = dataList;
    this->wordList = wordList;
    this->statusList = statusList;
    this->wordCount = wordCount;
    this->threadNumber = threadNumber;
}

MyThread::~MyThread()
{
}

void *MyThread::Entry()
{
    int wordCount = 0;

    for(size_t i = start; i < ending; i++)
    {
        wxString data = dataList[i];
        for(size_t j = 0; j < wordList->length(); j++)
        {
            wxString word = wordList[j];
            size_t pos = 0;

            while(pos < data.Length())
            {
                pos = data.find(word, pos + word.Length());

                if(pos != wxNOT_FOUND){
                    wordCount++;
                }
            }
        }
        this->wordCount[i] = wordCount;
    }
    statusList[threadNumber] = 1;

    return 0;
}

wxString MyThread::Download(wxString urlLine)
{
    wxURL *url = new wxURL(urlLine);

    if (url->GetError() == wxURL_NOERR)
    {
         wxString data;

         wxInputStream *in_stream = url->GetInputStream();

         if(in_stream && in_stream->IsOk())
         {
             wxStringOutputStream html_stream(&data);
             in_stream->Read(html_stream);

             return data;
         }
    }

    return "";
}
