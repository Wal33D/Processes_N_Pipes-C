# Define compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Iinclude

# Define any directories containing header files other than /usr/include
INCLUDES = -Iinclude

# Define the source directory and target binary directory
SRCDIR = src
BINDIR = bin

# Define the C source files (wildcard picks all .c files in the directory)
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Define the C object files 
# (this translates the .c files in SOURCES to .o files in the same directory)
OBJECTS = $(SOURCES:.c=.o)

# Define the executable file name
TARGET = $(BINDIR)/myprogram

# The first rule is the one executed when no parameters are fed to the Makefile
all: build $(TARGET)

# Rule for making the bin directory
build:
	@mkdir -p $(BINDIR)

# Rule for linking the program
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for compiling the source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean-up operations
clean:
	rm -f $(SRCDIR)/*.o $(TARGET)
