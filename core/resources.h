#ifndef CH8RESOURCES_H
#define CH8RESOURCES_H

#define CH8_INSTALLED_MEMORY 4096 // bytes
#define CH8_CLOCK_RATE 600 // hz 

#include "../utilities/stack.h"
#include "../sdl/sdlr.h"

enum ch8_pcenum
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
	R_COUNT,
};

struct ch8_resources
{
    uint16_t pc;
    uint8_t registers[R_COUNT];
    uint8_t* memory;
    struct stk_stack stack;
    uint16_t address_pointer;
    uint32_t keyboard_buffer;
    uint8_t keyboard_flag;
    unsigned int clock_rate;
    uint32_t timer_tick;
};

// name: ch8_execute
// desc: sets up an emulator environment which includes sdl
//       and other emulator resources, and runs the set_up
//       and execute functions provided by the end dev
void ch8_execute(
        struct sdlr_screen* screen_info,
        void (*set_up)(struct ch8_resources*, struct sdlr_resources*, int, char**),
        int (*execute)(struct ch8_resources*, struct sdlr_resources*),
        int argc,
        char* argv[]);

// name: ch8_get_key_as_hex
// desc: takes key off the keyboard buffer. does NOT
//       clear the buffer. see ch8_clear_keys.
uint8_t ch8_get_key_as_hex(struct ch8_resources* resources);

// name: ch8_set_key
// desc: adds key to the keyboard buffer and sets the
//       keyboard_flag to true;
void ch8_set_key(struct ch8_resources* resources, uint32_t key);

// name: ch8_clear_keys
// desc: sets keyboard_flag to false. however, it 
//       doesn't actually do anything to values in
//       buffer otherwise
void ch8_clear_keys(struct ch8_resources* resources);

uint16_t ch8_get_timer(struct ch8_resources* resources);

void ch8_set_timer(struct ch8_resources* resources, uint16_t timer_val);

#endif
