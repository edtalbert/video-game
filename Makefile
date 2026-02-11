# Detect OS
UNAME_S := $(shell uname -s)

# Choose compiler
ifeq ($(UNAME_S),Darwin)
    CXX = clang++
else
    CXX = g++
endif

CXXFLAGS = -std=c++17 $(shell sdl2-config --cflags)
LDFLAGS  = $(shell sdl2-config --libs)

TARGET = simple
SRC = simple.cpp character.cpp gamestate.cpp menustate.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
