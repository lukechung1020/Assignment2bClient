
#include "Activity.hpp"
#include "UploadAsyncTask.hpp"

void Activity::onCreate() {
    cout << "Creating Activity..." << endl;

    UploadAsyncTask uploadTask;
    auto future = uploadTask.execute();

    cout << "Waiting for Callback..." << endl;

    future.get();
}

int main() {
    Activity activity;
    activity.onCreate();

    return 0;
}
