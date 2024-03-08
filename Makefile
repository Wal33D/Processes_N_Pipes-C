# Define compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Iinclude

# Define the source directory and target binary directory
SRCDIR = src
BINDIR = bin

# Define the C source files (wildcard picks all .c files in the directory)
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Define the C object files 
# (this uses pattern substitution to replace .c with .o for each filename in SOURCES)
OBJECTS = $(patsubst %,$(SRCDIR)/%,$(notdir $(SOURCES:.c=.o)))

# Define the executable file name
TARGET = $(BINDIR)/myprogram

# The first rule is the one executed when no parameters are fed to the Makefile
all: $(TARGET)

# Rule for making the target binary directory
$(BINDIR):
	@mkdir -p $(BINDIR)

# Rule for linking the program
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# Rule for compiling the source files to object files
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean-up operations
clean:
	rm -f $(SRCDIR)/*.o $(TARGET)
