## Assignment 2b Client For COMP 3940

### Setup

- In **UploadClient.cpp** in the *uploadFile()* function adjust the variables `host`, `endpoint`, `port`, and `filePath`/`fileName` as necessary
- In the root of the GitHub repo run this command: `g++ -std=c++20 -o Client Activity.cpp AsyncTask.cpp UploadClient.hpp`
- Then enter: `./Client` to run the program

### Issues

- If there is a file reading issue, in **UploadClient.cpp** change `filePath` to the absolute path of **AndroidLogo.png** 
(On Mac if you use XCode's g++ then you must use the absolute file path as the current directory is the root of the GitHub repo)

## Contributors

- Luke Chung