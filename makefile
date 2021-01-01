OUTPUT = bin/chip8emu
CC_FLAGS = -Wall -Wextra -g -std=c11 -lSDL2
CC = gcc 

all:    obj/sprite.o obj/operations.o obj/asmio.o obj/sdlr.o obj/main.o obj/stack.o obj/resources.o
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

obj/resources.o: core/resources.c
	${CC} core/resources.c ${CC_FLAGS} -c -o obj/resources.o

obj/operations.o: core/operations.c obj/sdlr.o
	${CC} core/operations.c obj/sdlr.o ${CC_FLAGS} -c -o obj/operations.o

bin/sdl_tests: tests/sdl_tests.c obj/resources.o obj/sdlr.o obj/sprite.o obj/operations.o obj/asmio.o obj/stack.o
	${CC} tests/sdl_tests.c obj/resources.o obj/sdlr.o obj/sprite.o obj/operations.o obj/asmio.o obj/stack.o ${CC_FLAGS} -o bin/sdl_tests

bin/ops_tests: tests/ops_tests.c
	${CC} tests/ops_tests.c core/asmio.c utilities/stack.c core/operations.c ${CC_FLAGS} -o bin/ops_tests

bin/stk_tests: tests/stk_tests.c obj/stack.o
	${CC} tests/stk_tests.c obj/stack.o ${CC_FLAGS} -o bin/stk_tests

tests: bin/ops_tests bin/stk_tests bin/sdl_tests

clean:
	${RM} obj/*
	${RM} bin/*
