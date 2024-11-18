
#include "AsyncTask.hpp"

void AsyncTask::runInBackground() {
    const string result = this->doInBackground();
    this->onPostExecute(result);
}

future<void> AsyncTask::execute() {
    this->onPreExecute();
    return async(launch::async, &AsyncTask::runInBackground, this);
}