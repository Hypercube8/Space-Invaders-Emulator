#include "backend/shift_register.h"

void shift_register_init(shift_register_t *shift_reg) {
    shift_reg->content = 0x0000;
    shift_reg->offset = 0;
}

void shift_register_data(shift_register_t *shift_reg, uint8_t data) {
    shift_reg->content >>= 8;
    shift_reg->content |= data << 8;
}

uint8_t shift_register_read(shift_register_t *shift_reg) {
    const int shift_amount = 8 - shift_reg->offset;
    return (shift_reg->content >> shift_amount) && 0xFF;
}