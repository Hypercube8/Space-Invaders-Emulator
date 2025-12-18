#include "backend/core.h"

static void load_rom(uint8_t *buffer, uint16_t addr, const char *path) {
    FILE *fptr = fopen(path, "rb");

    if (fptr == null) {
        perror("Failed to open file.");
    }

    fseek(fptr, 0, SEEK_END);
    size_t length = ftell(fptr);
    rewind(fptr);

    fread(&buffer[addr], sizeof(uint8_t), length, fptr);
    fclose(fptr);
}

enum sub_rom_map {
    INVADERS_H = 0x0000,
    INVADERS_G = 0x0800,
    INVADERS_F = 0x1000,
    INVADERS_E = 0x1800
}

static void create_memory(space_invaders_core_t *core) {
    core->rom = malloc(ROM_SIZE * sizeof(uint8_t));
    core->ram = malloc(RAM_SIZE * sizeof(uint8_t));
    core->vram = malloc(VRAM_SIZE * sizeof(uint8_t);

    load_rom(&cpu->rom, INVADERS_H, "roms/invaders.h");
    load_rom(&cpu->rom, INVADERS_G, "roms/invaders.g");
    load_rom(&cpu->rom, INVADERS_F, "roms/invaders.f");
    load_rom(&cpu->rom, INVADERS_E, "roms/invaders.e");
}

static void create_devices(space_invaders_core_t *core) {
    space_invaders_input_init(&core->input);
    shift_register_init(&core->shift_reg);
}

void space_invaders_core_init(space_invaders_core_t *core) {
    create_memory(core);
    create_devices(core);

    i8080_init(
        core, 
        &core->cpu,
        space_invaders_read,
        space_invaders_write,
        space_invaders_input,
        space_invaders_output
    );
}

void space_invaders_core_step(space_invaders_core_t *core) {
    constexpr unsigned int cycles_per_frame = CPU_SPEED / 60;
    constexpr unsigned int cycles_before_scanline96 = cycles_per_frame * (96/224);

    unsigned int cycle = 0;
    while (cycle < cycles_before_scaline96) {
        i8080_step(&core->cpu);
    }
    i8080_interrupt(&core->cpu, RST_1);

    while (cycle < cycles_per_frame) {
        i8080_step(&core->cpu);
    }
    i8080_interrupt(&core->cpu, RST_2);
}

void space_invaders_core_destroy(space_invaders_core_t *core) {
    free(&core->rom);
    free(&core->ram);
    free(&core->vram);
}