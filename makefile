OUTPUT = bin/sdl_test
CC_FLAGS = -Wall -Wextra -g -std=c11 -lSDL2
CC = gcc 

all:    obj/sdlr.o obj/main.o
	${CC} ${CC_FLAGS} -o $(OUTPUT) $^

obj/sdlr.o:
	${CC} sdl/sdlr.c ${CC_FLAGS} -c -o obj/sdlr.o

obj/main.o: obj/sdlr.o
	${CC} main.c ${CC_FLAGS} -c -o obj/main.o

clean:
	${RM} obj/*
	${RM} bin/*
