CC = g++
INCDIRS = -Iinclude -Iinclude/SDL2 -Iinclude/headers
LIBDIRS = -Llib
LIBS = -lSDL2 -lSDL2main

CFILES = src/*.cpp
OBJECTS = src/*.o

TESTFILES = tests/*.cpp

BINARY = renderer

BINARIES = *.exe

all:
	$(CC) $(INCDIRS) $(LIBDIRS) -o $(BINARY) $(CFILES) $(LIBS)

testshape:
	$(CC) $(INCDIRS) $(LIBDIRS) -o testshape.exe tests/shapetest.cpp src/shape.cpp $(LIBS)

testrasterizer:
	$(CC) $(INCDIRS) $(LIBDIRS) -o testrasterizer.exe tests/rasterizertest.cpp src/rasterizer.cpp src/shape.cpp $(LIBS)

clean:
	del $(BINARIES)