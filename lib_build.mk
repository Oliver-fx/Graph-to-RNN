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