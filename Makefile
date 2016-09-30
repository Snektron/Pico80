TARGET = Pico80
SRC	= src
BUILD = build
INCLUDE = include

CXX	= g++
CC = gcc
FLAGS = -I $(SRC) -I $(INCLUDE) -std=c++11 `sdl2-config --cflags --libs`
RM = rm
MD = mkdir -p

rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard, $d/, $2) $(filter $(subst *, %, $2), $d))

CSRCS = $(patsubst $(SRC)/%, %, $(call rwildcard, $(SRC)/, *.c))
CXXSRCS = $(patsubst $(SRC)/%, %, $(call rwildcard, $(SRC)/, *.cpp))

OBJECTS = $(CXXSRCS:%.cpp=%.o) $(CSRCS:%.c=%.o)

vpath %.o $(BUILD)
vpath %.cpp $(SRC)
vpath %.c $(SRC)

all: clean $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(addprefix $(BUILD)/, $(OBJECTS)) $(FLAGS) -o $@
	
%.o: %.cpp
	$(MD) $(BUILD)/$(dir $@)
	$(CXX) $< $(FLAGS) -c -o $(BUILD)/$@
	
%.o: %.c
	$(MD) $(BUILD)/$(dir $@)
	$(CC) $< $(FLAGS) -c -o $(BUILD)/$@

clean: 
	$(RM) -rf $(BUILD)
	$(RM) -f $(TARGET)

.PHONY: all clean