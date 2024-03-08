# Define compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Iinclude

# Define the source directory, object directory inside build, and target binary directory
SRCDIR = src
BUILDDIR = build
OBJDIR = $(BUILDDIR)/object

# Define the C source files (wildcard picks all .c files in the directory)
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Exclude main.c from the sources to avoid duplicate definitions
SOURCES := $(filter-out $(SRCDIR)/main.c, $(SOURCES))

# Add parent.c and child.c to sources
SOURCES += $(SRCDIR)/parent.c $(SRCDIR)/child.c

# Define the C object files (placing them in the OBJDIR directory)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Define the executable file name, reflecting the repo name
TARGET = $(BUILDDIR)/processes-n-pipes

all: build $(TARGET)

# Rule for making the necessary directories
build:
	@mkdir -p $(BUILDDIR) $(OBJDIR)

# Rule for linking the program
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for compiling the source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
