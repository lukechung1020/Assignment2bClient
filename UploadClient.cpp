//
// Created by Luke Chung on 2024-11-17.
//

#include "UploadClient.hpp"
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <fstream>

string UploadClient::uploadFile() {
        const string boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW";
        const string host = "localhost";  // Change this to your target host
        const string endpoint = "/upload/upload";
        const string filePath = "../AndroidLogo.png";
        const string fileName = "AndroidLogo.png";
        const int port = 8081;  // UploadServer port

        ostringstream requestBodyStream;

        try {
            // Create socket
            int sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock < 0) {
                perror("Socket creation failed");
                return "";
            }

            // Resolve hostname
            hostent* server = gethostbyname(host.c_str());
            if (!server) {
                cerr << "Error: No such host." << endl;
                close(sock);
                return "";
            }

            // Configure server address
            sockaddr_in server_addr{};
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(port);
            memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

            // Connect to the server
            if (connect(sock, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) < 0) {
                perror("Connection failed");
                close(sock);
                return "";
            }

            // Add form fields
            addFormField(requestBodyStream, "caption", "logo", boundary);
            addFormField(requestBodyStream, "date", "10_16_2024", boundary);

            // Add file part
            addFilePart(requestBodyStream, "File", filePath, fileName, boundary, "image/png");

            // Close the multipart boundary
            requestBodyStream << "--" << boundary << "--\r\n";

            // Convert the request body to a string and get its length
            string requestBody = requestBodyStream.str();
            size_t contentLength = requestBody.size();

            // Construct HTTP headers
            ostringstream headers;
            headers << "POST " << endpoint << " HTTP/1.1\r\n"
                    << "Host: " << host << "\r\n"
                    << "Content-Type: multipart/form-data; boundary=" << boundary << "\r\n"
                    << "Content-Length: " << contentLength << "\r\n"
                    << "Connection: close\r\n"
                    << "\r\n";

            // Send headers and body to the server
            string httpRequest = headers.str() + requestBody;
            if (send(sock, httpRequest.c_str(), httpRequest.size(), 0) < 0) {
                perror("Send failed");
                close(sock);
                return "";
            }

            // Read server's response
            char buffer[4096];
            cout << "Server Response:\n";
            ssize_t bytesRead;
            while ((bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
                buffer[bytesRead] = '\0';  // Null-terminate the response
                cout << buffer;
            }

            if (bytesRead < 0) {
                perror("Receive failed");
            } else if (bytesRead == 0) {
                cout << "Connection closed." << endl;
            }

            // Close socket
            close(sock);
        } catch (const exception& e) {
            cerr << "Exception: " << e.what() << endl;
        }

        return requestBodyStream.str();
}

void UploadClient::addFormField(ostringstream& requestBodyStream, const string& fieldName,
                  const string& fieldValue, const string& boundary) {
    requestBodyStream << "--" << boundary << "\r\n"
                  << "Content-Disposition: form-data; name=\"" << fieldName << "\"\r\n"
                  << "\r\n"
                  << fieldValue << "\r\n";
}

void UploadClient::addFilePart(ostringstream& requestBodyStream, const string& fieldName,
                 const string& filePath, const string& fileName, const string& boundary, const string& contentType) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << endl;
        return;
    }

    requestBodyStream << "--" << boundary << "\r\n"
                      << "Content-Disposition: form-data; name=\"" << fieldName << "\"; filename=\"" << fileName << "\"\r\n"
                      << "Content-Type: " << contentType << "\r\n"
                      << "\r\n";

    // Read file content and write it to the request body
    vector<char> buffer(4096);
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        requestBodyStream.write(buffer.data(), file.gcount());
    }

    requestBodyStream << "\r\n";
}