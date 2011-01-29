CC=g++
OBJS=$(shell find . -maxdepth 1 -name "*.cpp" | sed s/.cpp/.o/)
FLAGS=-g
LDFLAGS=$(shell pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_primitives-5.0)
BIN=./game
RM=rm
EXEC=exec

all: $(BIN)

.cpp.o:
	$(CC) $< -c $(FLAGS)

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

run:
	$(EXEC) $(BIN)

clean:
	$(RM) $(BIN) *.o
