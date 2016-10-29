TARGET = Pico80
SRC	= src
BUILD = build
INCLUDE = include

CXX	= g++
CC = gcc
FLAGS = -MMD -MP -I $(SRC) -I $(INCLUDE) `sdl2-config --cflags --libs`
CXXFLAGS = $(FLAGS) -std=c++14
CFLAGS = $(FLAGS)
RM = rm
MD = mkdir -p

rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard, $d/, $2) $(filter $(subst *, %, $2), $d))

CSRCS = $(patsubst $(SRC)/%, %, $(call rwildcard, $(SRC)/, *.c))
CXXSRCS = $(patsubst $(SRC)/%, %, $(call rwildcard, $(SRC)/, *.cpp))

OBJECTS = $(CXXSRCS:%.cpp=%.o) $(CSRCS:%.c=%.o)

-include $(OBJECTS:%.o=%.d)

vpath %.o $(BUILD)
vpath %.cpp $(SRC)
vpath %.c $(SRC)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(addprefix $(BUILD)/, $(OBJECTS)) $(FLAGS) -o $@
	
%.o: %.cpp
	$(MD) $(BUILD)/$(dir $@)
	$(CXX) $< $(CXXFLAGS) -c -o $(BUILD)/$@
	
%.o: %.c
	$(MD) $(BUILD)/$(dir $@)
	$(CC) $< $(CFLAGS) -c -o $(BUILD)/$@

clean:
	$(RM) -rf $(BUILD)
	$(RM) -f $(TARGET)
	
.PHONY: all clean