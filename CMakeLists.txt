cmake_minimum_required(VERSION 3.29)
project(Assignment2bClient)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment2bClient
    UploadClient.cpp
    UploadClient.hpp
        AsyncTask.hpp
        UploadAsyncTask.hpp
        Activity.hpp
        Activity.cpp
        AsyncTask.cpp)
