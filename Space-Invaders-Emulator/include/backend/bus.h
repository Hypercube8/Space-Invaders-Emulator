#ifndef __BUS_H__
#define __BUS_H__

#include <stdint.h>

#include "core.h"

enum memory_map {
    ROM_START = 0x0000,
    ROM_END = 0x1FFF,

    RAM_START = 0x2000,
    RAM_END = 0x23FF,

    VRAM_START = 0x2400,
    VRAM_END = 0x3FFF,
};

uint8_t space_invaders_read(void *system, uint16_t addr);
void space_invaders_write(void *system, uint16_t addr, uint8_t val);
uint8_t space_invaders_in(void *system, uint8_t port);
void space_invaders_out(void *system, uint8_t port, uint8_t val);

#endif