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
link_libraries(TLL)
add_library(SimpleScan SHARED ${CMAKE_SOURCE_DIR}/app/SimpleScan.gen.cpp)
add_library(MusicVisualizer SHARED ${CMAKE_SOURCE_DIR}/app/MusicVisualizer.gen.cpp)
add_library(Rain SHARED ${CMAKE_SOURCE_DIR}/app/Rain.gen.cpp)
add_library(VoiceRecognition SHARED ${CMAKE_SOURCE_DIR}/app/VoiceRecognition.gen.cpp)
add_custom_command(TARGET VoiceRecognition POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/example/video/bomb.mp4" $<TARGET_FILE_DIR:${PROJECT}>)
add_library(Timer SHARED ${CMAKE_SOURCE_DIR}/app/Timer.gen.cpp)
file(GLOB TIMER_IMAGES ${CMAKE_SOURCE_DIR}/app/TimerImage/*.png)
add_custom_command(TARGET Timer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TIMER_IMAGES} $<TARGET_FILE_DIR:Timer>)
add_library(Theremin SHARED ${CMAKE_SOURCE_DIR}/app/Theremin.gen.cpp)
