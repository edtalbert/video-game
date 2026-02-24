# Detect OS
ifeq ($(OS),Windows_NT)
	# Windows
	UNAME_S := Windows
	RM = del /Q
	EXE = .exe
else
	# Linux/macOS
	UNAME_S := $(shell uname -s)
	RM = rm -f
	EXE =
endif

# Choose compiler
ifeq ($(UNAME_S),Darwin)
	CXX = clang++
else
	CXX = g++
endif

CXXFLAGS = -std=c++17 -g $(shell sdl2-config --cflags)
LDFLAGS  = $(shell sdl2-config --libs)

TARGET = simple
SRC = simple.cpp character.cpp gamestate.cpp menustate.cpp levelstate.cpp

HEADERS = button.hpp

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)$(EXE) $(LDFLAGS)

run: $(TARGET)
ifeq ($(OS),Windows_NT)
	$(TARGET)$(EXE)
else
	./$(TARGET)
endif

clean:
	$(RM) $(TARGET)$(EXE)
