#include "backend/input.h"

void space_invaders_input_init(space_invaders_input *input) {
    input.inp0 = 0x00;
    input.inp1 = 0x00;
    input.inp2 = 0x00;

    input.always1 = 0b111;
    input.always1_2 = 0b1;
}