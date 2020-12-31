#ifndef ASMIO_H
#define ASMIO_H

uint16_t read_from_memory(uint16_t** memory, uint16_t address);

uint16_t read_with_offset(uint16_t** memory, uint16_t address, uint16_t offset);

uint16_t swap16(uint16_t x);

void load_image_file(FILE* file, uint16_t** memory);

int load_image(const char* image_path, uint16_t** memory);

#endif
