OUTPUT = bin/chip8emu
CC_FLAGS = -Wall -Wextra -g -std=c11 -lSDL2
CC = gcc 

all:    obj/sprite.o obj/operations.o obj/asmio.o obj/sdlr.o obj/main.o
	${CC} ${CC_FLAGS} -o $(OUTPUT) $^

obj/sdlr.o: sdl/sdlr.c
	${CC} sdl/sdlr.c ${CC_FLAGS} -c -o obj/sdlr.o

obj/main.o: main.c
	${CC} main.c ${CC_FLAGS} -c -o obj/main.o

obj/asmio.o: asmio/asmio.c
	${CC} asmio/asmio.c ${CC_FLAGS} -c -o obj/asmio.o

obj/sprite.o: core/sprite.c
	${CC} core/sprite.c ${CC_FLAGS} -c -o obj/sprite.o

obj/operations.o: asmio/asmio.o operations/operations.c
	${CC} operations/operations.c ${CC_FLAGS} -c -o obj/operations.o

bin/tests: obj/asmio.o obj/operations.o tests/ops_tests.c
	${CC} tests/ops_tests.c ${CC_FLAGS} -o bin/tests $^

tests: bin/tests

clean:
	${RM} obj/*
	${RM} bin/*
