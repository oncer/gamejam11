CC=g++
SOURCES=$(wildcard *.cpp)
OBJS=$(SOURCES:.cpp=.o)
HDRS=$(shell find . -maxdepth 1 -name "*.h")
#FLAGS=-g
FLAGS=-O2 -g -Wall
LDFLAGS=$(shell pkg-config --libs allegro-5.0 allegro_image-5.0 allegro_primitives-5.0 allegro_ttf-5.0 allegro_audio-5.0 allegro_acodec-5.0)
BIN=./game
RM=rm
EXEC=exec

all: $(BIN)

%.o: %.cpp
	$(CC) $< -c $(FLAGS)

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

run:
	$(EXEC) $(BIN)

clean:
	$(RM) -f $(BIN) $(OBJS)
