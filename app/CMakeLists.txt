### Setup cmake project ###
cmake_minimum_required(VERSION 3.10)

### Setup C++ project ###
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Setup app class generator ###
add_executable(AppGenerator ${CMAKE_SOURCE_DIR}/app/AppGenerator.cpp)

### Setup building apps （アプリ追加時はここに追記する） ###
include_directories(${CMAKE_SOURCE_DIR}/app)
add_library(TestApp SHARED ${CMAKE_SOURCE_DIR}/app/TestApp.gen.cpp)
add_library(OscTestApp SHARED ${CMAKE_SOURCE_DIR}/app/OscTestApp.gen.cpp)
add_library(SimpleScan SHARED ${CMAKE_SOURCE_DIR}/app/SimpleScan.gen.cpp)
