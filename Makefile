CXX = g++
CXXFLAGS     = -Wall -lwiringPi
SDL_FLAGS    = $(shell sdl2-config --cflags --libs)
OPENCV_FLAGS = -I/usr/include/opencv4/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
INCLUDE_DIR  = -I./include/
OBJECTS      = Image.o Color.o Event.o PanelManager.o SerialManager.o Simulator.o TLLmain.o

all : build example

build: $(OBJECTS)
	cd build && \
	ar rcs libTLL.a $(OBJECTS)
	@echo "\033[1;32mCompleted building the library!!\n\033[0;39m"

example: build
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) example/Image_8x16.cpp build/libTLL.a -o example/Image_8x16
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) example/Rectangles_8x16.cpp build/libTLL.a -o example/Rectangles_8x16
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) example/FillSingleColor_8x16.cpp build/libTLL.a -o example/FillSingleColor_8x16
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) example/MovingRect_8x16.cpp build/libTLL.a -o example/MovingRect_8x16
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) example/Intaractive_8x16.cpp build/libTLL.a -o example/Intaractive_8x16
	@echo "\033[1;32mCompleted building all sample programs!!\n\033[0;39m"

%.o : ./src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $< $(INCLUDE_DIR) -c -o ./build/$@

doc:
	doxygen
	@rm -rf docs/
	@mkdir docs/
	@cp -r doxygen/html/* docs/

doc-clean:
	rm -rf docs/ doxygen/

clean:
	rm -f *.o
	rm -rf build/
	rm -f example/Rectangles_8x16 example/FillSingleColor_8x16 example/MovingRect_8x16 example/Intaractive_8x16 example/Image_8x16
