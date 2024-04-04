# Compiler and Compiler Flags
CC=gcc
CFLAGS=-Wall -g -Iinclude
# Linker flags
LDFLAGS=-lreadline

# The build target executable:
TARGET=minios

# Source, Object files
SRCS=kernel/20192596/fork.c
OBJS=$(SRCS:.c=.o) 

# Suorce1
#SRCS=kernel/kernel.c kernel/system.c

# Include directory
INCLUDE_DIR=include



all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# To obtain object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up:
clean:
	rm -f $(OBJS) $(TARGET)
