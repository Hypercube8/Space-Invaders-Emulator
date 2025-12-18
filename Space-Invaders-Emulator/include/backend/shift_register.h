#ifndef __SHIFT_REGISTER__
#define __SHIFT_REGISTER__

#include <stdint.h>

typedef struct {
    uint16_t content;
    uint8_t offset;
} shift_register_t;

void shift_register_init(shift_register_t *shift_reg);
void shift_register_data(shift_register_t *shift_reg, uint8_t data);
uint8_t shift_register_read(shift_register_t *shift_reg);

#endif