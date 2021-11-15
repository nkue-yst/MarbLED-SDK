CXX = g++
CXXFLAGS     = -Wall -lwiringPi
SDL_FLAGS    = $(shell sdl2-config --cflags --libs)
OPENCV_FLAGS = -I/usr/include/opencv4/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_freetype
INCLUDE_DIR  = -I./include/
OBJECTS      = Video.o TextRenderer.o Image.o Color.o Event.o PanelManager.o SerialManager.o Simulator.o TLLmain.o

TUIO_STATIC = -L./thirdparty/TUIO20_CPP/demos/ -lTUIO2

all : build example

build: $(OBJECTS)
	cd build && \
	ar rcs libTLL.a $(OBJECTS)
	@echo "\033[1;32mCompleted building the library!!\n\033[0;39m"

example: build
	@#$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/Video_24x16.cpp -Lbuild -lTLL -o example/Video_24x16
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/PrintText_24x16.cpp -Lbuild -lTLL -o example/PrintText_24x16
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/PrintTime_24x16.cpp -Lbuild -lTLL -o example/PrintTime_24x16
	@#$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/LineCircle_24x16.cpp -Lbuild -lTLL -o example/LineCircle_24x16
	@#$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/Image_24x16.cpp -Lbuild -lTLL -o example/Image_24x16
	@#$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/Rectangles_8x16.cpp -Lbuild -lTLL -o example/Rectangles_8x16
	@#$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/FillSingleColor_8x16.cpp -Lbuild -lTLL -o example/FillSingleColor_8x16
	@#$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/MovingRect_8x16.cpp -Lbuild -lTLL -o example/MovingRect_8x16
	@#$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/MovingRect_24x16.cpp -Lbuild -lTLL -o example/MovingRect_24x16
	@#$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/Intaractive_8x16.cpp -Lbuild -lTLL -o example/Intaractive_8x16
	@#$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(INCLUDE_DIR) $(TUIO_STATIC) example/Intaractive_24x16.cpp -Lbuild -lTLL -o example/Intaractive_24x16
	@echo "\033[1;32mCompleted building all sample programs!!\n\033[0;39m"

%.o : ./src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(OPENCV_FLAGS) $(TUIO_STATIC) $< $(INCLUDE_DIR) -c -o ./build/$@

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
	rm -f example/Rectangles_8x16 example/FillSingleColor_8x16 example/MovingRect_8x16 example/Intaractive_8x16 example/Image_24x16 example/Intaractive_24x16 example/MovingRect_24x16 example/LineCircle_24x16 example/PrintText_24x16 example/Video_24x16 example/PrintTime_24x16
