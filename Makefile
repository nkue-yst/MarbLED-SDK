CXX = g++
CXXFLAGS = -Wall $(shell sdl2-config --cflags)
INCLUDE_DIR = -I./include/
OBJECTS = PanelManager.o

all : build

build: $(OBJECTS)
	cd build && \
	ar rcs libTLL.a $(OBJECTS)

%.o : ./src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $< $(INCLUDE_DIR) -c -o ./build/$@

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
