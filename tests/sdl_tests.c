#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>

#include "../sdl/sdlr.h"
#include "../core/resources.h"
#include "../core/operations.h"
#include "../core/sprite.h"

void mess_with_pixels(uint32_t* pixels)
{
    uint8_t sprite[] = {0x3c, 0x62, 0xc0, 0xc0, 0xde, 0xd2, 0xc2, 0x66, 0x3c, 0x00, 0x00};
    ch8_draw_sprite(pixels, 0, 0, sprite, 11);
}

int execute_main(
        struct ch8_resources* resources,
        struct sdlr_resources* sdl_resources)
{
    mess_with_pixels(sdl_resources->texture_pixels);
    sdlr_update_screen(sdl_resources);
    SDL_Delay(1000);
    resources->memory[resources->registers[R_PC]] =
            ((OP_ZER & 0xf) << 12) | // opcode
             (0x0e0 & 0xfff);          // immediate
    ch8_zero(
            resources,
            sdl_resources,
            resources->registers[R_PC],
            sdlr_clear_screen);
    --(resources->registers[R_PC]);
    return 0;
}

int main(void)
{
    struct sdlr_screen screen_info = { "chip8emu", 64, 32, 640, 320 };

    ch8_execute(&screen_info, NULL, execute_main, 0, NULL);

}
