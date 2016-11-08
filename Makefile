TARGET := Pico80
SRC := src
BUILD := build
INCLUDES := include

CC ?= gcc
CXX ?= g++
RM ?= rm
MD ?= mkdir -p

CXXLIBS := glfw3 nanovg
ifeq ($(OS),Windows_NT)
	CXXLIBS += gdi32 opengl32
else
    CXXLIBS += GL X11 dl Xxf86vm pthread Xrandr Xcursor Xinerama
endif

FLAGS := -MMD -MP -I$(SRC) $(INCLUDES:%=-I%)
CXXFLAGS := $(FLAGS) -std=c++14 $(CXXLIBS:%=-l%)
CFLAGS := $(FLAGS)

rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard, $d/, $2) $(filter $(subst *, %, $2), $d))

CSRCS = $(patsubst $(SRC)/%, %, $(call rwildcard, $(SRC)/, *.c))
CXXSRCS = $(patsubst $(SRC)/%, %, $(call rwildcard, $(SRC)/, *.cpp))

OBJECTS = $(CXXSRCS:%.cpp=%.o) $(CSRCS:%.c=%.o)

-include $(OBJECTS:%.o=%.d)

vpath %.o $(BUILD)/objects
vpath %.cpp $(SRC)
vpath %.c $(SRC)

all: $(TARGET)

test:
	@echo $(OBJECTS)

$(TARGET): $(OBJECTS)
	@echo Compiling $@...
	@$(CXX) $(addprefix $(BUILD)/objects/, $(OBJECTS)) $(CXXFLAGS) -o $@
	
%.o: %.cpp
	@echo Compiling $<
	@$(MD) $(BUILD)/objects/$(dir $@)
	@$(CXX) $< $(CXXFLAGS) -c -o $(BUILD)/objects/$@
	
%.o: %.c
	@echo Compiling $<
	@$(MD) $(BUILD)/objects/$(dir $@)
	@$(CC) $< $(CFLAGS) -c -o $(BUILD)/objects/$@

glad:
	@echo Updating glad...
	@glad --generator="c" --out-path="." --profile="core" --api="gl=3.3" --spec="gl" --no-loader --extensions="" --omit-khrplatform 2> /dev/null
	
clean:
	@echo Cleaning build files...
	@$(RM) -rf $(BUILD)
	@$(RM) -f $(TARGET)
	
help:
	@echo Possible options:
	@echo make Pico80 - Compile the main project.
	@echo make help - Display this message.
	@echo make glad - Update glad. Requires glad installed, see https://github.com/Dav1dde/glad.
	@echo make clean - Remove build directory.
	
.PHONY: all glad clean help