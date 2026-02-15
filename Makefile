# Compiler settings
# CC = clang
# CFLAGS = -Wall -Wextra -std=c11

# # Object files
# OBJS = main.o graph_env.o read_file.o

# # Final executable name
# TARGET = main

# # Default rule
# all: $(TARGET)

# # Link object files into executable
# $(TARGET): $(OBJS)
# 	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# # Compile each .c into .o
# main.o: main.c graph_env.h read_file.h
# 	$(CC) $(CFLAGS) -c main.c

# graph_env.o: graph_env.c graph_env.h
# 	$(CC) $(CFLAGS) -c graph_env.c

# read_file.o: read_file.c read_file.h graph_env.h
# 	$(CC) $(CFLAGS) -c read_file.c

# # Clean rule
# clean:
# 	rm -f $(OBJS) $(TARGET)

# Save this content as lib_build.mk
CC = clang
CFLAGS = -fPIC
LDFLAGS = -shared
TARGET = libgraph.so
OBJECTS = graph.o read_file.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

graph.o: graph_env.c
	$(CC) $(CFLAGS) -c $< -o $@

read_file.o: read_file.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)