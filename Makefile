CXX = g++
CXXFLAGS     = -std=c++11 -pthread
WARNING_FRAG = -Wno-unused-command-line-argument
CXXFLAGS    += $(WARNING_FRAG)

TLL_FLAGS    = libTLL.a
SDL_FLAGS    = $(shell sdl2-config --cflags --libs)

ifeq ($(shell uname), Linux)
CXXFLAGS	+= -lwiringPi

OPENCV_FLAGS = -I/usr/include/opencv4/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_freetype
endif

ifeq ($(shell uname), Darwin)
OPENCV_FLAGS = -I/usr/local/Cellar/opencv/4.5.4_4/include/opencv4/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_freetype
endif

# Settings for rpi-rgb-led-matrix library
ifeq ($(shell uname), Linux)
RGB_LIB_DISTRIBUTION = thirdparty/rpi-rgb-led-matrix
RGB_INCDIR = $(RGB_LIB_DISTRIBUTION)/include
INCLUDE_DIR += -I$(RGB_INCDIR)
RGB_LIBDIR = $(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME = rgbmatrix
RGB_LIBRARY = $(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS += -L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread
RGB_CLEAN = $(MAKE) -C $(RGB_LIBDIR) clean
endif

INCLUDE_DIR  += -I./include/ -I./thirdparty/TUIO11_CPP/TUIO/ -I./thirdparty/TUIO11_CPP/oscpack/

TLL_SRC = ./src/Video.cpp ./src/TextRenderer.cpp ./src/Image.cpp ./src/Color.cpp ./src/Event.cpp ./src/PanelManager.cpp ./src/SerialManager.cpp ./src/Simulator.cpp ./src/TLLmain.cpp
TLL_OBJ = $(TLL_SRC:.cpp=.o)

TUIO_SRC = ./thirdparty/TUIO11_CPP/TUIO/TuioTime.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioPoint.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioContainer.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioObject.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioCursor.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioBlob.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioDispatcher.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioManager.cpp  ./thirdparty/TUIO11_CPP/TUIO/OneEuroFilter.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioServer.cpp ./thirdparty/TUIO11_CPP/TUIO/UdpSender.cpp ./thirdparty/TUIO11_CPP/TUIO/TcpSender.cpp ./thirdparty/TUIO11_CPP/TUIO/WebSockSender.cpp ./thirdparty/TUIO11_CPP/TUIO/FlashSender.cpp ./thirdparty/TUIO11_CPP/TUIO/TuioClient.cpp ./thirdparty/TUIO11_CPP/TUIO/OscReceiver.cpp ./thirdparty/TUIO11_CPP/TUIO/UdpReceiver.cpp ./thirdparty/TUIO11_CPP/TUIO/TcpReceiver.cpp
TUIO_OBJ = $(TUIO_SRC:.cpp=.o)

OSC_SRC =  ./thirdparty/TUIO11_CPP/oscpack/osc/OscTypes.cpp ./thirdparty/TUIO11_CPP/oscpack/osc/OscOutboundPacketStream.cpp ./thirdparty/TUIO11_CPP/oscpack/osc/OscReceivedElements.cpp ./thirdparty/TUIO11_CPP/oscpack/osc/OscPrintReceivedElements.cpp ./thirdparty/TUIO11_CPP/oscpack/ip/posix/NetworkingUtils.cpp ./thirdparty/TUIO11_CPP/oscpack/ip/posix/UdpSocket.cpp
OSC_OBJ = $(OSC_SRC:.cpp=.o)

TUIO_FLAGS = $(TUIO_OBJ) #$(OSC_OBJ)

TEST_EXAMPLE = int2022_demo

all : build example

build: $(TLL_OBJ) $(TUIO_OBJ) #$(OSC_OBJ)
	@ar rcs libTLL.a $^
	@echo "---> Make library file."
	@echo "\033[1;32mCompleted building the library!!\n\033[0;39m"

# build rpi-rgb-led-matrix library
$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)

example: build $(RGB_LIBRARY)
	@echo "---> Compile int2022_demo"
	@$(CXX) $(CXXFLAGS) example/int2022_demo.cpp -o example/int2022_demo
	@$(CXX) $(CXXFLAGS) example/int2022_demo_1.cpp -o example/int2022_demo_1 libTLL.a $(TLL_FLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(LDFLAGS) $(INCLUDE_DIR) $(RGB_LIBRARY)  ../oscpack/build/liboscpack.a
	@$(CXX) $(CXXFLAGS) example/int2022_demo_2.cpp -o example/int2022_demo_2 libTLL.a $(TLL_FLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(LDFLAGS) $(INCLUDE_DIR) $(RGB_LIBRARY)  ../oscpack/build/liboscpack.a
	@$(CXX) $(CXXFLAGS) example/int2022_demo_3.cpp -o example/int2022_demo_3 libTLL.a $(TLL_FLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(LDFLAGS) $(INCLUDE_DIR) $(RGB_LIBRARY)  ../oscpack/build/liboscpack.a
	@echo "\033[1;32mCompleted building all sample programs!!\n\033[0;39m"

%.o : %.cpp
	@echo "---> Compile $<"
	@$(CXX) $(CXXFLAGS) $< $(INCLUDE_DIR) -c -o $@ $(SDL_FLAGS) $(LDFLAGS) $(OPENCV_FLAGS)

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
	rm -rf example/int2022_demo_3 example/int2022_demo_2 example/int2022_demo_1 example/int2022_demo
	$(RGB_CLEAN)
