#include <stdint.h>

static int set_pixel(uint32_t* pixels, int x, int y)
{
    uint32_t* pixel = &pixels[y * 64 + x];
    uint32_t temp = *pixel;
    *pixel ^= 0xffffffff;
    return temp && *pixel;
}

int ch8_draw_sprite(
        uint32_t* pixels,
        int offset_x,
        int offset_y,
        uint8_t* sprite,
        int len)
{
    int flip_occurred = 0;
    uint8_t is_pixel_set = 0;
    for (int y = 0; y < len; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            is_pixel_set = (sprite[y] >> (7 - x)) & 0x01;
            if (is_pixel_set)
            {
                flip_occurred |= set_pixel(pixels, x + offset_x, y + offset_y);
            }
        }
    }

    return flip_occurred;
}
