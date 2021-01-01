#ifndef CH8RESOURCES_H
#define CH8RESOURCES_H

#define CH8_INSTALLED_MEMORY 4096 // bytes

#include "../utilities/stack.h"
#include "../sdl/sdlr.h"

enum ch8_registers_enum
{
	R_V0 = 0,
	R_V1,
	R_V2,
	R_V3,
	R_V4,
	R_V5,
	R_V6,
	R_V7,
	R_V8,
	R_V9,
	R_VA,
	R_VB,
	R_VC,
	R_VD,
	R_VE,
	R_VF,
	R_PC,
	R_COUNT,
};

struct ch8_resources
{
    uint16_t registers[R_COUNT];
    uint16_t* memory;
    struct stk_stack stack;
};

void ch8_execute(
        struct sdlr_screen* screen_info,
        void (*set_up)(struct ch8_resources*, struct sdlr_resources*, int, char**),
        int (*execute)(struct ch8_resources*, struct sdlr_resources*),
        int argc,
        char* argv[]);

#endif
