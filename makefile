OUTPUT = bin/chip8emu
CC_FLAGS = -Wall -Wextra -g -std=c11 -lSDL2
CC = gcc 

all:    obj/sprite.o obj/operations.o obj/asmio.o obj/sdlr.o obj/main.o
	${CC} ${CC_FLAGS} -o $(OUTPUT) $^

obj/sdlr.o: sdl/sdlr.c
	${CC} sdl/sdlr.c ${CC_FLAGS} -c -o obj/sdlr.o

obj/main.o: main.c
	${CC} main.c ${CC_FLAGS} -c -o obj/main.o

obj/asmio.o: core/asmio.c
	${CC} core/asmio.c ${CC_FLAGS} -c -o obj/asmio.o

obj/sprite.o: core/sprite.c
	${CC} core/sprite.c ${CC_FLAGS} -c -o obj/sprite.o

obj/stack.o: utilities/stack.c
	${CC} utilities/stack.c ${CC_FLAGS} -c -o obj/stack.o

obj/operations.o: core/operations.c
	${CC} core/operations.c ${CC_FLAGS} -c -o obj/operations.o

bin/ops_tests: obj/asmio.o obj/operations.o tests/ops_tests.c
	${CC} tests/ops_tests.c obj/asmio.o obj/operations.o ${CC_FLAGS} -o bin/ops_tests

bin/stk_tests: tests/stk_tests.c obj/stack.o
	${CC} tests/stk_tests.c obj/stack.o ${CC_FLAGS} -o bin/stk_tests

tests: bin/ops_tests bin/stk_tests

clean:
	${RM} obj/*
	${RM} bin/*
