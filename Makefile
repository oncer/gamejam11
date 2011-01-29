CC=gcc
SRC=$(shell find . -name "*.c*")
LDFLAGS=$(shell pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_primitives-5.0)
BIN=./game
RM=rm
EXEC=exec

all: $(BIN)

$(BIN): $(SRC)
	$(CC) -o $(BIN) $(SRC) $(LDFLAGS)

run:
	$(EXEC) $(BIN)

clean:
	$(RM) $(BIN)
