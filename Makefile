CXX = g++
CXXFLAGS  = -Wall -lwiringPi
SDL_FLAGS = $(shell sdl2-config --cflags --libs)
INCLUDE_DIR = -I./include/
OBJECTS     = TLLmain.o PanelManager.o SerialManager.o Simulator.o Color.o

all : build example

build: $(OBJECTS)
	cd build && \
	ar rcs libTLL.a $(OBJECTS)

example: build
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(INCLUDE_DIR) example/Rectangles_8x16.cpp build/libTLL.a -o example/Rectangles_8x16
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(INCLUDE_DIR) example/FillSingleColor_8x16.cpp build/libTLL.a -o example/FillSingleColor_8x16

%.o : ./src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $< $(INCLUDE_DIR) -c -o ./build/$@

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
	rm -f example/Rectangles_8x16 example/FillSingleColor_8x16
