#ifndef SPRITE_H
#define SPRITE_H

// name: draw_sprite
// desc: takes an SDL_Texture's pixel array and writes a
//       sprite to that array. Sprite takes the form of
//       a series of 8-bit rows, which describe whether
//       the corresponding pixel is set or unset.
int ch8_load_sprite_row(
        uint32_t* pixels,
        int offset_x,
        int offset_y,
        uint8_t sprite);

#endif
