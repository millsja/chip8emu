#include <stdint.h>

static int set_pixel(uint32_t* pixels, int x, int y)
{
    uint32_t* pixel = &pixels[y * 64 + x];
    uint32_t temp = *pixel;
    *pixel ^= 0xffffffff;
    return temp && *pixel;
}

int ch8_load_sprite_row(
        uint32_t* pixels,
        int offset_x,
        int offset_y,
        uint8_t sprite)
{
    int flip_occurred = 0;
    uint8_t is_pixel_set = 0;
    for (int x = 0; x < 8; x++)
    {
        is_pixel_set = (sprite >> (7 - x)) & 0x01;
        if (is_pixel_set)
        {
            flip_occurred |= set_pixel(pixels, x + offset_x, offset_y);
        }
    }

    return flip_occurred;
}
