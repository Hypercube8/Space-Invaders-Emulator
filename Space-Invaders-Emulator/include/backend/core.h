#ifndef __SPACE_INVADERS_CORE__
#define __SPACE_INVADERS_CORE__

#include <stdint.h>
#include <stdlib.h>

#include "i8080.h"
#include "bus.h"
#include "input.h"
#include "shift_register.h"

constexpr unsigned int CPU_SPEED = 2000000;

constexpr uint16_t ROM_SIZE = 0x2000;
constexpr uint16_t RAM_SIZE = 0x400;
constexpr uint16_t VRAM_SIZE = 0x1C00;

typedef struct {
    i8080_cpu_t cpu;
    i8080_reader_t read_bus;
    i8080_writer_t write_bus;
    i8080_input_t input_bus;
    i8080_output_t output_bus;

    uint8_t *rom;
    uint8_t *ram;
    uint8_t *vram;

    shift_register_t shift_reg;
    space_invaders_input_t input;
} space_invaders_core_t;

void space_invaders_core_init(space_invaders_core_t *core);
void space_invaders_core_step(space_invaders_core_t *core);
void space_invaders_core_destroy(space_invaders_core_t *core);

static void create_memory(space_invaders_core_t *core);
static void create_devices(space_invaders_core_t *core);

#endif