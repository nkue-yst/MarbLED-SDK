### Setup cmake project ###
cmake_minimum_required(VERSION 3.10)

### Setup C++ project ###
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_libraries(oscpack)

add_executable(Run_MusicVisualizer Run_MusicVisualizer.cpp)
add_executable(Run_Rain Run_Rain.cpp)
add_executable(Run_SimpleScan Run_SimpleScan.cpp)
add_executable(Run_Theremin Run_Theremin.cpp)
add_executable(Run_Timer Run_Timer.cpp)
add_executable(Run_MultiTouchLine Run_MultiTouchLine.cpp)
add_executable(Run_Pong Run_Pong.cpp)
add_executable(Run_CockroachShooting Run_CockroachShooting.cpp)
add_executable(Run_ImageViewer Run_ImageViewer.cpp)
add_executable(Run_ADIR01P_Light Run_ADIR01P_Light.cpp)
add_executable(Run_ADIR01P_Television Run_ADIR01P_Television.cpp)
add_executable(Run_ADIR01P_AirConditioner Run_ADIR01P_AirConditioner.cpp)
