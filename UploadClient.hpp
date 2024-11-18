#pragma once

#include <sstream>
#include <string>


using namespace std;

class UploadClient {
public:
    UploadClient() = default;

    string uploadFile();
    void addFormField(ostringstream& requestBodyStream, const string& fieldName,
                      const string& fieldValue, const string& boundary);
    void addFilePart(ostringstream& requestBodyStream, const string& fieldName,
                     const string& filePath, const string& fileName, const string& boundary, const string& contentType);
};
