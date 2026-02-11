CXX = g++
CFLAGS = $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs)

simple: simple.cpp gamestate.cpp menustate.cpp character.cpp
	$(CXX) simple.cpp gamestate.cpp menustate.cpp character.cpp -o simple $(CFLAGS) $(LIBS)

run: simple
	./simple

clean:
	rm -f simple