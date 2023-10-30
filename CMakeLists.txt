### Setup cmake project ###
cmake_minimum_required(VERSION 3.10)
set(PROJECT TLL)
project(${PROJECT})

### Setup C++ project ###
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fPIC -g -O3 -pthread")

### Setup TUIO ###
file(GLOB TUIO_SRC thirdparty/TUIO11_CPP/TUIO/*.cpp thirdparty/TUIO11_CPP/TUIO/*.h)
add_library(TUIO STATIC ${TUIO_SRC})
include_directories(thirdparty/TUIO11_CPP/TUIO)
target_link_libraries(TUIO oscpack)

### Setup oscpack ###
set(OSCPACK_DIR ${CMAKE_SOURCE_DIR}/thirdparty/TUIO11_CPP/oscpack)
include_directories(${OSCPACK_DIR})
if(WIN32)
    set(IpSystemTypePath ip/win32)
else(WIN32)
    set(IpSystemTypePath ip/posix)
endif(WIN32)
add_library(oscpack
    ${OSCPACK_DIR}/ip/IpEndpointName.h
    ${OSCPACK_DIR}/ip/IpEndpointName.cpp
    ${OSCPACK_DIR}/ip/NetworkingUtils.h
    ${OSCPACK_DIR}/${IpSystemTypePath}/NetworkingUtils.cpp
    ${OSCPACK_DIR}/ip/UdpSocket.h
    ${OSCPACK_DIR}/${IpSystemTypePath}/UdpSocket.cpp
    ${OSCPACK_DIR}/ip/PacketListener.h
    ${OSCPACK_DIR}/ip/TimerListener.h
    ${OSCPACK_DIR}/osc/OscTypes.h
    ${OSCPACK_DIR}/osc/OscTypes.cpp 
    ${OSCPACK_DIR}/osc/OscHostEndianness.h
    ${OSCPACK_DIR}/osc/OscException.h
    ${OSCPACK_DIR}/osc/OscPacketListener.h
    ${OSCPACK_DIR}/osc/MessageMappingOscPacketListener.h
    ${OSCPACK_DIR}/osc/OscReceivedElements.h
    ${OSCPACK_DIR}/osc/OscReceivedElements.cpp
    ${OSCPACK_DIR}/osc/OscPrintReceivedElements.h
    ${OSCPACK_DIR}/osc/OscPrintReceivedElements.cpp
    ${OSCPACK_DIR}/osc/OscOutboundPacketStream.h
    ${OSCPACK_DIR}/osc/OscOutboundPacketStream.cpp
)

### Setup OpenCV ###
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

### Setup ZeroMQ ###
option(WITH_TLS OFF)
option(WITH_LIBSODIUM OFF)
option(BUILD_TESTS OFF)
option(CPPZMQ_BUILD_TESTS OFF)
add_subdirectory(thirdparty/libzmq)
set(ZeroMQ_DIR ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/libzmq)
add_subdirectory(thirdparty/cppzmq)
include_directories(thirdparty/libzmq/include)
include_directories(thirdparty/cppzmq)

### Create TouchLED-Library (main project) ###
file(GLOB TLL_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/Runtime/Runtime.cpp)
include_directories(include ${CMAKE_SOURCE_DIR}/src/Runtime)
add_library(${PROJECT} SHARED ${TLL_SRC})
target_link_libraries(${PROJECT} ${OpenCV_LIBRARIES} cppzmq oscpack TUIO)

### Setup building applications ###
option(TLL_BUILD_APP "Build applications using TLL" ON)
if(TLL_BUILD_APP)
    add_subdirectory(${CMAKE_SOURCE_DIR}/app)
endif()

### Setup building runtime test ###
option(MARBLED_BUILD_RUNTIME_TEST "Build mini runtime for app test" OFF)
if (MARBLED_BUILD_RUNTIME_TEST)
    include_directories(${CMAKE_SOURCE_DIR}/src/Runtime)
    add_executable(MarbLED_Runtime ${CMAKE_SOURCE_DIR}/src/Runtime/Runtime.cpp)
    target_link_libraries(MarbLED_Runtime ${CMAKE_DL_LIBS} ${PROJECT} TUIO)
endif()

### Copy engine component files ###
add_custom_command(
    TARGET ${PROJECT} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/NotoSansJP-Regular.otf" $<TARGET_FILE_DIR:${PROJECT}>
)
