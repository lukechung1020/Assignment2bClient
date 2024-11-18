
#pragma once

#include <string>
#include <future>

using namespace std;

class AsyncTask {
    void runInBackground();

public:
    AsyncTask() = default;
    virtual ~AsyncTask() = default;

    future<void> execute();

protected:
    virtual string doInBackground() = 0;
    virtual void onPreExecute() {};
    virtual void onPostExecute(string result) {};
    virtual void onProgressUpdate(string progress) {};
    virtual void publishProgress(string progress) {};
};
