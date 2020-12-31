#include <stdio.h>
#include <stdint.h>

static uint16_t read_from_memory(uint16_t memory[], uint16_t address)
{
	return memory[address];
}

uint16_t ch8_read_with_offset(uint16_t memory[], uint16_t address, int offset)
{
	uint16_t instr = read_from_memory(memory, address);
	return instr >> offset;
}

static uint16_t swap16(uint16_t x)
{
	return (x << 8) | (x >> 8);
}

static void load_image_file(FILE* file, uint16_t memory[])
{
	uint16_t origin;
	fread(&origin, sizeof(origin), 1, file);
	origin = swap16(origin);

	uint16_t max_read = UINT16_MAX - origin;
	uint16_t* p = memory + origin;
	size_t read = fread(p, sizeof(uint16_t), max_read, file);

	while (read-- > 0)
	{
		*p = swap16(*p);
		++p;
	}
}

int ch8_load_image(const char* image_path, uint16_t memory[])
{
	FILE* file = fopen(image_path, "rb");
	if (!file)
	{
		fprintf(stderr, "Couldn't load file: %s", image_path);
		return 1;
	}

	load_image_file(file, memory);
	fclose(file);

	return 0;
}
