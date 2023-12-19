### Setup cmake project ###
cmake_minimum_required(VERSION 3.10)

### Setup C++ project ###
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Setup app class generator ###
add_executable(AppGenerator ${CMAKE_SOURCE_DIR}/app/AppGenerator.cpp)

add_subdirectory(AppRunner)

### Setup building apps （アプリ追加時はここに追記する） ###
include_directories(${CMAKE_SOURCE_DIR}/app)
link_libraries(TLL)

#add_library(SimpleScan SHARED ${CMAKE_SOURCE_DIR}/app/SimpleScan.gen.cpp)
#add_library(Timer SHARED ${CMAKE_SOURCE_DIR}/app/Timer.gen.cpp)
#file(GLOB TIMER_IMAGES ${CMAKE_SOURCE_DIR}/app/TimerImage/*.png)
#add_custom_command(TARGET Timer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${TIMER_IMAGES} $<TARGET_FILE_DIR:Timer>)
#add_library(Pong SHARED ${CMAKE_SOURCE_DIR}/app/Pong.gen.cpp)
#add_library(ImageViewer SHARED ${CMAKE_SOURCE_DIR}/app/ImageViewer.gen.cpp)
#add_library(Swipe SHARED ${CMAKE_SOURCE_DIR}/app/Swipe.gen.cpp)

#add_library(ADIR01P_Light SHARED ${CMAKE_SOURCE_DIR}/app/ADIR01P_Light.gen.cpp)
#add_library(ADIR01P_Television SHARED ${CMAKE_SOURCE_DIR}/app/ADIR01P_Television.gen.cpp)
#add_library(ADIR01P_AirConditioner SHARED ${CMAKE_SOURCE_DIR}/app/ADIR01P_AirConditioner.gen.cpp)

#add_library(MultiTouchLine SHARED ${CMAKE_SOURCE_DIR}/app/MultiTouchLine.gen.cpp)
#add_library(CockroachShooting SHARED ${CMAKE_SOURCE_DIR}/app/CockroachShooting.gen.cpp)
#add_custom_command(TARGET CockroachShooting POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/example/image/Button_Start.jpg" $<TARGET_FILE_DIR:${PROJECT}>)
#add_custom_command(TARGET CockroachShooting POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/example/sound/start.wav" $<TARGET_FILE_DIR:${PROJECT}>)
#add_library(TouchPoints SHARED ${CMAKE_SOURCE_DIR}/app/TouchPoints.gen.cpp)

###########################
### New app build setup ###
###########################
message(STATUS "Setup building applications")

message(STATUS "  MarbleTower")
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/app/MarbleTower.mled)
add_library(MarbleTower SHARED ${CMAKE_SOURCE_DIR}/app/MarbleTower.gen.cpp)
add_custom_command(TARGET MarbleTower POST_BUILD COMMAND ${CMAKE_COMMAND} -E sha256sum ${CMAKE_SOURCE_DIR}/app/MarbleTower.gen.cpp > ${CMAKE_BINARY_DIR}/app/MarbleTower.mled/MarbleTower.sha256)
add_custom_command(TARGET MarbleTower POST_BUILD COMMAND mv $<TARGET_FILE:MarbleTower> ${CMAKE_BINARY_DIR}/app/MarbleTower.mled/)
add_custom_command(TARGET MarbleTower POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/app/DefaultIcon.png ${CMAKE_BINARY_DIR}/app/MarbleTower.mled/icon.png)

message(STATUS "  Theremin")
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/app/Theremin.mled)
add_library(Theremin SHARED ${CMAKE_SOURCE_DIR}/app/Theremin.gen.cpp)
add_custom_command(TARGET Theremin POST_BUILD COMMAND ${CMAKE_COMMAND} -E sha256sum ${CMAKE_SOURCE_DIR}/app/Theremin.gen.cpp > ${CMAKE_BINARY_DIR}/app/Theremin.mled/Theremin.sha256)
add_custom_command(TARGET Theremin POST_BUILD COMMAND mv $<TARGET_FILE:Theremin> ${CMAKE_BINARY_DIR}/app/Theremin.mled/)
add_custom_command(TARGET Theremin POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/app/DefaultIcon.png ${CMAKE_BINARY_DIR}/app/Theremin.mled/icon.png)

message(STATUS "  MusicVisualizer")
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/app/MusicVisualizer.mled)
add_library(MusicVisualizer SHARED ${CMAKE_SOURCE_DIR}/app/MusicVisualizer.gen.cpp)
add_custom_command(TARGET MusicVisualizer POST_BUILD COMMAND ${CMAKE_COMMAND} -E sha256sum ${CMAKE_SOURCE_DIR}/app/MusicVisualizer.gen.cpp > ${CMAKE_BINARY_DIR}/app/MusicVisualizer.mled/MusicVisualizer.sha256)
add_custom_command(TARGET MusicVisualizer POST_BUILD COMMAND mv $<TARGET_FILE:MusicVisualizer> ${CMAKE_BINARY_DIR}/app/MusicVisualizer.mled/)
add_custom_command(TARGET MusicVisualizer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/app/DefaultIcon.png ${CMAKE_BINARY_DIR}/app/MusicVisualizer.mled/icon.png)

message(STATUS "  Rain")
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/app/Rain.mled)
add_library(Rain SHARED ${CMAKE_SOURCE_DIR}/app/Rain.gen.cpp)
add_custom_command(TARGET Rain POST_BUILD COMMAND ${CMAKE_COMMAND} -E sha256sum ${CMAKE_SOURCE_DIR}/app/Rain.gen.cpp > ${CMAKE_BINARY_DIR}/app/Rain.mled/Rain.sha256)
add_custom_command(TARGET Rain POST_BUILD COMMAND mv $<TARGET_FILE:Rain> ${CMAKE_BINARY_DIR}/app/Rain.mled/)
add_custom_command(TARGET Rain POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/app/DefaultIcon.png ${CMAKE_BINARY_DIR}/app/Rain.mled/icon.png)
