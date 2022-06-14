### Setup cmake project ###
cmake_minimum_required(VERSION 3.10)
set(PROJECT TLL)
project(${PROJECT})

### Setup C++ project ###
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Setup TUIO ###
file(GLOB TUIO_SRC thirdparty/TUIO11_CPP/TUIO/*.cpp thirdparty/TUIO11_CPP/TUIO/*.h)
add_library(TUIO STATIC ${TUIO_SRC})
include_directories(thirdparty/TUIO11_CPP/TUIO)
target_link_libraries(TUIO oscpack)

### Setup oscpack ###
include_directories(thirdparty/oscpack)
add_subdirectory(thirdparty/oscpack)

### Setup OpenCV ###
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

### Setup ZeroMQ ###
find_package(GnuTLS REQUIRED)
include_directories(${GNUTLS_INCLUDE_DIR})
add_subdirectory(thirdparty/libzmq)
add_subdirectory(thirdparty/cppzmq)
include_directories(thirdparty/libzmq/include)
include_directories(thirdparty/cppzmq)

### Setup wiringPi ###
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
if(WIRINGPI_LIBRARIES)
    target_link_libraries(${PROJECT} ${WIRINGPI_LIBRARIES})
endif()

### Create TouchLED-Library (main project) ###
file(GLOB TLL_SRC src/*.cpp)
include_directories(include)
add_library(${PROJECT} STATIC ${TLL_SRC})
target_link_libraries(${PROJECT} ${OpenCV_LIBRARIES} ${SDL2_LIBRARIES} cppzmq)

### Setup demo app ###
add_executable(int2022_demo example/int2022_demo.cpp)
add_executable(int2022_demo_1 example/int2022_demo_1.cpp)
target_link_libraries(int2022_demo_1 ${PROJECT} TUIO)

### Setup rpi-rgb-led-matrix (Only on RaspberryPi) ###
if(WIRINGPI_LIBRARIES)
    file(GLOB RPI-RGB_SRC thirdparty/rpi-rgb-led-matrix/lib/*.cc thirdparty/rpi-rgb-led-matrix/lib/*.c thirdparty/rpi-rgb-led-matrix/lib/*.h)
    include_directories(thirdparty/rpi-rgb-led-matrix/include)
    add_library(RPI-RGB STATIC ${RPI-RGB_SRC})
    target_link_libraries(${PROJECT} RPI-RGB ${WIRINGPI_LIBRARIES} "-pthread")
endif()

### Copy engine component files ###
add_custom_command(
    TARGET ${PROJECT} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/ColorPalette.csv" $<TARGET_FILE_DIR:${PROJECT}>
)
add_custom_command(
    TARGET ${PROJECT} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/NotoSansJP-Regular.otf" $<TARGET_FILE_DIR:${PROJECT}>
)
