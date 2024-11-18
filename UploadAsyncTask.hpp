
#pragma once
#include "AsyncTask.hpp"
#include "UploadClient.hpp"
#include <iostream>

using namespace std;

class UploadAsyncTask final : public AsyncTask {
protected:
    void onPreExecute() override {
        cout << "Starting upload task..." << endl;
    }

    string doInBackground() override {
        UploadClient client;
        return client.uploadFile();
    }

    void onPostExecute(string result) override {
        cout << "Upload Task Completed: " << result << endl;
    }
};
