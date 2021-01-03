#include <stdio.h>
#include <stdint.h>

static uint8_t read_from_memory(uint8_t memory[], uint16_t address)
{
	return memory[address];
}

uint16_t ch8_read_with_offset(uint8_t memory[], uint16_t address, int offset)
{
	uint16_t instr = read_from_memory(memory, address) << 8;
	instr |= read_from_memory(memory, address + 1);
	return instr >> offset;
}

static uint16_t fix_endianness(uint16_t x)
{
	return (x << 8) | (x >> 8);
}

static size_t load_image_file(FILE* file, uint8_t memory[])
{
	uint16_t origin = 0x200;
	uint16_t max_read = UINT16_MAX - origin;
	uint8_t* p = memory + origin;
	size_t total_read = fread(p, sizeof(uint8_t), max_read, file);

        if (ferror(file))
        {
            fprintf(stderr, "Error reading image file...\n");
        }

        return (total_read + origin - 1);
}

size_t ch8_load_image(const char* image_path, uint8_t memory[])
{
	FILE* file = fopen(image_path, "rb");
	if (!file)
	{
		fprintf(stderr, "Couldn't load file: %s", image_path);
		return 1;
	}

	size_t last_address = load_image_file(file, memory);
	fclose(file);

	return last_address;
}
