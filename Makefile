CXX = g++
CXXFLAGS     = -Wall -std=c++11

TLL_FLAGS    = libTLL.a
SDL_FLAGS    = $(shell sdl2-config --cflags --libs)

ifeq ($(shell uname),Linux)
CXXFLAGS	+= -lwiringPi

OPENCV_FLAGS = -I/usr/include/opencv4/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_freetype
endif

ifeq ($(shell uname), Darwin)
OPENCV_FLAGS = -I/usr/local/Cellar/opencv/4.5.3_3/include/opencv4/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_freetype
endif

INCLUDE_DIR  = -I./include/ -I./thirdparty/TUIO20_CPP/TUIO2/ -I./thirdparty/TUIO20_CPP/oscpack/

TLL_SRC = ./src/Video.cpp ./src/TextRenderer.cpp ./src/Image.cpp ./src/Color.cpp ./src/Event.cpp ./src/PanelManager.cpp ./src/SerialManager.cpp ./src/Simulator.cpp ./src/TLLmain.cpp
TLL_OBJ = $(TLL_SRC:.cpp=.o)

TUIO_SRC = ./thirdparty/TUIO20_CPP/TUIO2/TuioTime.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioPoint.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioObject.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioComponent.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioToken.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioPointer.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioBounds.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioSymbol.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioDispatcher.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioManager.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioServer.cpp ./thirdparty/TUIO20_CPP/TUIO2/UdpSender.cpp ./thirdparty/TUIO20_CPP/TUIO2/TcpSender.cpp ./thirdparty/TUIO20_CPP/TUIO2/FlashSender.cpp ./thirdparty/TUIO20_CPP/TUIO2/WebSockSender.cpp ./thirdparty/TUIO20_CPP/TUIO2/TuioClient.cpp ./thirdparty/TUIO20_CPP/TUIO2/OscReceiver.cpp ./thirdparty/TUIO20_CPP/TUIO2/UdpReceiver.cpp ./thirdparty/TUIO20_CPP/TUIO2/TcpReceiver.cpp
TUIO_OBJ = $(TUIO_SRC:.cpp=.o)

OSC_SRC = ./thirdparty/TUIO20_CPP/oscpack/osc/OscTypes.cpp ./thirdparty/TUIO20_CPP/oscpack/osc/OscOutboundPacketStream.cpp ./thirdparty/TUIO20_CPP/oscpack/osc/OscReceivedElements.cpp ./thirdparty/TUIO20_CPP/oscpack/osc/OscPrintReceivedElements.cpp ./thirdparty/TUIO20_CPP/oscpack/ip/posix/NetworkingUtils.cpp ./thirdparty/TUIO20_CPP/oscpack/ip/posix/UdpSocket.cpp
OSC_OBJ = $(OSC_SRC:.cpp=.o)

all : build example

build: $(TLL_OBJ) $(TUIO_OBJ) $(OSC_OBJ)
	ar rcs libTLL.a $^
	@echo "\033[1;32mCompleted building the library!!\n\033[0;39m"

example: build
	$(CXX) $(CXXFLAGS) $(TLL_FLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) example/PrintText_24x16.cpp libTLL.a -o example/PrintText_24x16
	@echo "\033[1;32mCompleted building all sample programs!!\n\033[0;39m"

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $< $(INCLUDE_DIR) -c -o $@

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
	rm -rf ./thirdparty/TUIO20_CPP/TUIO2/*.o
	rm -rf example/PrintText_24x16
