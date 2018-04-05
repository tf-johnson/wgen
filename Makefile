CC = g++
CFLAGS = -std=c++11 -g

LD = g++

LIBS = -lSDL2 -lGLEW -lGL

SDIR = src
ODIR = build
BDIR = bin

SOURCES := $(shell find $(SDIR) -name "*.cpp")
OBJECTS := $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SOURCES))

TARGET = wgen.x

$(TARGET): $(OBJECTS)
	$(LD) -o $(BDIR)/$@ $(OBJECTS) $(LIBS)
	
$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)