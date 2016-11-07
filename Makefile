TARGET := Pico80
SRC	:= src
BUILD := build
INCLUDE := include
RESOURCES := assets

CXX	?= g++
CC ?= gcc
LD ?= ld
ECHO ?= echo
CXXLIBS := glfw3 gdi32 opengl32
FLAGS := -MMD -MP -I $(SRC) -I $(INCLUDE) -I usr/include
CXXFLAGS := $(FLAGS) -std=c++14 $(CXXLIBS:%=-l%)
CFLAGS := $(FLAGS)
RM ?= rm
MD ?= mkdir -p

rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard, $d/, $2) $(filter $(subst *, %, $2), $d))

CSRCS = $(patsubst $(SRC)/%, %, $(call rwildcard, $(SRC)/, *.c))
CXXSRCS = $(patsubst $(SRC)/%, %, $(call rwildcard, $(SRC)/, *.cpp))
RSRCS = $(call rwildcard, $(RESOURCES)/, *)

OBJECTS = $(CXXSRCS:%.cpp=%.o) $(CSRCS:%.c=%.o)
RSRCOBJ = $(patsubst $(RESOURCES)/%, %, $(RSRCS:%=%.rs))

-include $(OBJECTS:%.o=%.d)

vpath %.o $(BUILD)/objects
vpath %.rs $(BUILD)/resources
vpath %.cpp $(SRC)
vpath %.c $(SRC)

TEST = test|grep -ce "\s"

all: $(TARGET)
	@$(ECHO) Done!

$(TARGET): $(RSRCOBJ) $(OBJECTS)
	@$(ECHO) Compiling $@...
	@$(CXX) $(addprefix $(BUILD)/objects/, $(OBJECTS)) $(CXXFLAGS) -o $@
# 	$(addprefix $(BUILD)/resources/, $(RSRCOBJ))
	
%.o: %.cpp
	@$(ECHO) Compiling $<
	@$(MD) $(BUILD)/objects/$(dir $@)
	@$(CXX) $< $(CXXFLAGS) -c -o $(BUILD)/objects/$@
	
%.o: %.c
	@$(ECHO) Compiling $<
	@$(MD) $(BUILD)/objects/$(dir $@)
	@$(CC) $< $(CFLAGS) -c -o $(BUILD)/objects/$@

%.rs: $(RESOURCES)/%
	@$(ECHO) Linking resource $<
	@$(MD) $(BUILD)/resources/$(dir $@)
	@$(LD) -r -b binary -o $(BUILD)/resources/$@ $<

clean:
	@$(ECHO) Cleaning build files.
	@$(RM) -rf $(BUILD)
	@$(RM) -f $(TARGET)
	
.PHONY: all clean