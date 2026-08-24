CC       = g++
CXXFLAGS = -O3 -Wall -fPIC -Iinclude -Ibase -Ithings -fopenmp
LDFLAGS  = -lglut -lGLU -lGL -lm -fopenmp

TARGET   = JingYinHung_5

SRC_THINGS = $(wildcard things/*.C)
SRC_BASE   = $(wildcard base/*.C)
SOURCES = $(SRC_THINGS) $(SRC_BASE)

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean