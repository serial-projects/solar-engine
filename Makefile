# This makefile was adquired from the "Makefile Cookbook" & Adapted for Solar
# Engine by Fujita Scale Team, original source can be found on:
# https://makefiletutorial.com/#makefile-cookbook

# KSKS

# Thanks to Job Vranish:
# (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)

TARGET_EXEC := SE

BUILD_DIR 	:= ./bin
SRC_DIRS 	:= ./src

# Required libraries:
LINKWITH 	:= -lSDL2 -lSDL2_image -lGL -lm -lGLEW

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. 
# The shell will incorrectly expand these otherwise,
# but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.cxx' -or -name '*.c' -or -name '*.s')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header
# files. NOTE: since we just need ONE include, just set it to ./include!
INC_DIRS := ./include

# Pass the single directory to the flags:
INC_FLAGS := -I$(INC_DIRS)

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) $(LINKWITH) -g

# The final build step.
# ADDED: CPPFLAGS due library requirement (aka. SDL2):
$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(CPPFLAGS)

# Build step for C++ source
$(BUILD_DIR)/%.cxx.o: %.cxx
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean test debug
clean:
	rm -r $(BUILD_DIR)
	
# Add Quick Testing Unit:
test: $(TARGET_EXEC)
	./SE

debug: $(TARGET_EXEC)
	gdb ./SE
