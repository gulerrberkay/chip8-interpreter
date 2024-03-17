# A simple Makefile for compiling small SDL projects
INC_DIR = include
SRC_DIR = src
#BUILD_DIR = build

# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := -Wall `sdl2-config --cflags --libs`

# add header files here
HDRS := $(INC_DIR)/chip8-core.h \
		$(INC_DIR)/newlib.h

# add source files here
SRCS := $(SRC_DIR)/chip8-core.c \
		$(SRC_DIR)/main.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := chip8-emulator-app

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean