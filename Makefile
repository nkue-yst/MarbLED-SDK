CXX = g++
CXXFLAGS = -Wall -lwiringPi
SDL_FLAGS = $(shell sdl2-config --cflags --libs)
INCLUDE_DIR = -I./include/
OBJECTS     = TLLmain.o PanelManager.o SerialManager.o Simulator.o

all : build example

build: $(OBJECTS)
	cd build && \
	ar rcs libTLL.a $(OBJECTS)

example: build
	$(CXX) $(CXXFLAGS) $(SDL_FLAGS) $(INCLUDE_DIR) example/example01.cpp build/libTLL.a -o example/example01

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
	rm -f example/example01
