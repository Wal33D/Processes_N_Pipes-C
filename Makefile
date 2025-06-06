# Define compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=c11 -Iinclude

# Define the source directory, object directory inside build, and target binary directory
SRCDIR = src
BUILDDIR = build
OBJDIR = $(BUILDDIR)/object

.PHONY: build $(OBJDIR) clean

# Define the C source files (wildcard picks all .c files in the directory)
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Define the C object files (placing them in the OBJDIR directory)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Define the executable file name, reflecting the repo name
TARGET = $(BUILDDIR)/processes-n-pipes

all: build $(TARGET)

# Rule for making the necessary directories
build:
	@mkdir -p $(BUILDDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Rule for linking the program
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for compiling the source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET) tests/test_menu tests/test_operations tests/test_io
tests/test_operations: tests/test_operations.c src/utilities.c | build
	$(CC) $(CFLAGS) -o $@ $^

tests/test_io: tests/test_io.c src/utilities.c | build
	$(CC) $(CFLAGS) -o $@ $^

tests/test_menu: tests/test_menu.c | build $(TARGET)
	$(CC) $(CFLAGS) -o $@ tests/test_menu.c

.PHONY: test

test: $(TARGET) tests/test_operations tests/test_menu tests/test_io
	./tests/test_operations
	./tests/test_menu
	./tests/test_io
