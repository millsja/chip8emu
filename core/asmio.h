#ifndef ASMIO_H
#define ASMIO_H

uint8_t ch8_read_byte(uint8_t* memory, uint16_t address);

uint16_t ch8_read_with_offset(uint8_t* memory, uint16_t address, uint16_t offset);

size_t ch8_load_image(const char* image_path, uint8_t* memory);

#endif
