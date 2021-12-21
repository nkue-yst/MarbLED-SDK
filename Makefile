CXX = g++
CXXFLAGS     = -Wall -std=c++11 -pthread

TLL_FLAGS    = libTLL.a
SDL_FLAGS    = $(shell sdl2-config --cflags --libs)

ifeq ($(shell uname),Linux)
CXXFLAGS	+= -lwiringPi

OPENCV_FLAGS = -I/usr/include/opencv4/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_freetype
endif

ifeq ($(shell uname), Darwin)
OPENCV_FLAGS = -I/usr/local/Cellar/opencv/4.5.4/include/opencv4/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_freetype
endif

INCLUDE_DIR  = -I./include/ -I./thirdparty/TUIO11_CPP/TUIO/ -I./thirdparty/TUIO11_CPP/oscpack/

TLL_SRC = ./src/Video.cpp ./src/TextRenderer.cpp ./src/Image.cpp ./src/Color.cpp ./src/Event.cpp ./src/PanelManager.cpp ./src/SerialManager.cpp ./src/Simulator.cpp ./src/TLLmain.cpp
TLL_OBJ = $(TLL_SRC:.cpp=.o)

TUIO_SRC = ./thirdparty/TUIO11_CPP/TUIO/TuioTime.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioPoint.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioContainer.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioObject.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioCursor.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioBlob.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioDispatcher.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioManager.cpp  ./thirdparty/TUIO11_CPP/TUIO/OneEuroFilter.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioServer.cpp ./thirdparty/TUIO11_CPP/TUIO/UdpSender.cpp ./thirdparty/TUIO11_CPP/TUIO/TcpSender.cpp ./thirdparty/TUIO11_CPP/TUIO/WebSockSender.cpp ./thirdparty/TUIO11_CPP/TUIO/FlashSender.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioClient.cpp ./thirdparty/TUIO11_CPP/TUIO/OscReceiver.cpp ./thirdparty/TUIO11_CPP/TUIO/UdpReceiver.cpp ./thirdparty/TUIO11_CPP/TUIO/TcpReceiver.cpp
TUIO_OBJ = $(TUIO_SRC:.cpp=.o)

OSC_SRC =  ./thirdparty/TUIO11_CPP/oscpack/osc/OscTypes.cpp ./thirdparty/TUIO11_CPP/oscpack/osc/OscOutboundPacketStream.cpp ./thirdparty/TUIO11_CPP/oscpack/osc/OscReceivedElements.cpp ./thirdparty/TUIO11_CPP/oscpack/osc/OscPrintReceivedElements.cpp ./thirdparty/TUIO11_CPP/oscpack/ip/posix/NetworkingUtils.cpp ./thirdparty/TUIO11_CPP/oscpack/ip/posix/UdpSocket.cpp
OSC_OBJ = $(OSC_SRC:.cpp=.o)

TUIO_FLAGS = $(TUIO_OBJ) $(OSC_OBJ)

TEST_EXAMPLE = Intaractive_24x16

all : build example

build: $(TLL_OBJ) $(TUIO_OBJ) $(OSC_OBJ)
	ar rcs libTLL.a $^
	@echo "\033[1;32mCompleted building the library!!\n\033[0;39m"

example: build
	$(CXX) $(CXXFLAGS) $(TLL_FLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(TUIO_FLAGS) $(INCLUDE_DIR) example/Intaractive_24x16.cpp libTLL.a -o example/Intaractive_24x16
	$(CXX) $(CXXFLAGS) $(TLL_FLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) example/PrintText_24x16.cpp libTLL.a -o example/PrintText_24x16
	#$(CXX) $(CXXFLAGS) $(TLL_FLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) example/PrintTime_24x16.cpp libTLL.a -o example/PrintTime_24x16
	@echo "\033[1;32mCompleted building all sample programs!!\n\033[0;39m"

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $< $(INCLUDE_DIR) -c -o $@

test: all
	./example/$(TEST_EXAMPLE)

doc:
	doxygen
	@rm -rf docs/
	@mkdir docs/
	@cp -r doxygen/html/* docs/

doc-clean:
	rm -rf docs/ doxygen/

clean:
	rm -rf libTLL.a
	rm -rf src/*.o
	rm -rf ./thirdparty/TUIO11_CPP/TUIO/*.o
	rm -rf example/PrintText_24x16 example/Intaractive_24x16 example/PrintTime_24x16
