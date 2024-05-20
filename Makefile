# Compiler and Compiler Flags
CC=gcc
CFLAGS=-Wall -g -Iinclude
# Linker flags
LDFLAGS=-lreadline

# The build target executable:
TARGET=minios

# Source, Object files
SRCS=kernel/kernel.c kernel/system.c kernel/20192596/shm.c kernel/20192596/ipc_pipe.c kernel/20192596/pi.c kernel/20192596/round_robin.c kernel/20192596/sync_pi.c kernel/20192596/RR_proc.c
OBJS=$(SRCS:.c=.o) 

# Source1(~week4)
#SRCS=kernel/kernel.c kernel/system.c

#Source2(week5)
#SRCS=kernel/20192596/fork.c

#Source3(week7)
#SRCS=kernel/kernel.c kernel/system.c kernel/20192596/shm.c kernel/20192596/ipc_pipe.c  kernel/20192596/pi.c

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
	
	

