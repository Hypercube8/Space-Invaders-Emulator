#include "backend/bus.h"

uint8_t space_invaders_read(void *system, uint16_t addr) {
    if (addr >= ROM_START && addr <= ROM_END) {
        return system->rom[addr]; 
    } else if (addr >= RAM_START && addr <= RAM_END) {
        return system->ram[addr];
    } else if (addr >= VRAM_END && addr <= VRAM_END) {
        return system->vram[addr];
    } else {
        return space_invaders_read(system, RAM_START + addr % RAM_SIZE);
    }
}

void space_invaders_write(void *system, uint16_t addr, uint8_t val) {
    if (addr >= ROM_START && addr <= ROM_END) {
        // attempted rom write, should fail.
        return;
    } else if (addr >= RAM_START && addr <= RAM_END) {
        system->ram[addr] = val;
    } else if (addr >= VRAM_END && addr <= VRAM_END) {
        system->vram[addr] = val;
    } else {
        space_invaders_write(system, RAM_START + addr % RAM_SIZE, val);
    }
}

enum io_map_read {
    INP0 = 0x00,
    INP1 = 0x01,
    INP2 = 0x02,
    SHFT_IN = 0x03,
}

enum io_map_write {
    SHFTAMNT = 0x02,
    SOUND1 = 0x03,
    SHFT_DATA = 0x04,
    SOUND2 = 0x05,
    WATCHDOG = 0x06
}

uint8_t space_invaders_in(void *system, uint8_t port) {
    switch (port) {
        case INP0: 
            return system->input.inp0;
        case INP1:
            return system->input.inp1;
        case INP2:
            return system->input.inp2;
        case SHFT_IN: 
            return shift_register_read(&system->shift_reg);
        default: 
            return 0x00;
    }
}

constexpr uint8_t OFFSET_BIT_MASK = 0b00000111;

void space_invaders_out(void *system, uint8_t port, uint8_t val) {
    switch (port) {
        case SHFTAMNT: 
            system->shift_reg.offset = val & OFFSET_BIT_MASK;
            break;
        case SOUND1: break;
        case SHFT_DATA: 
            shift_register_data(&system->shift_reg, val);
            break;
        case SOUND2: break;
        case WATCHDOG: break;
    }
}