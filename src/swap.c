#include "nm.h"

uint16_t swap16(uint16_t x)
{
	return (x >> 8) | (x << 8);
}

uint32_t swap32(uint32_t x)
{
	return ((x & 0x000000FFU) << 24) |
		((x & 0x0000FF00U) << 8)  |
		((x & 0x00FF0000U) >> 8)  |
		((x & 0xFF000000U) >> 24);
}

uint64_t swap64(uint64_t x)
{
	return ((uint64_t)swap32(x & 0xFFFFFFFFULL) << 32) |
		(uint64_t)swap32(x >> 32);
}
