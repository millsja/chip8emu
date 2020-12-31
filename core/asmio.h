#ifndef ASMIO_H
#define ASMIO_H

uint16_t ch8_read_with_offset(uint16_t** memory, uint16_t address, uint16_t offset);

int ch8_load_image(const char* image_path, uint16_t** memory);

#endif
