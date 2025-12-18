#ifndef __INPUT___
#define __INPUT___

#include <stdint.h>

typedef struct {
    union {
        struct {
            // Input port 0
            uint8_t self_test : 1;
            uint8_t always1 : 3;
            uint8_t fire : 1;
            uint8_t left : 1;
            uint8_t right : 1;
            uint8_t demux7 : 1;
            // Input port 1
            uint8_t credit : 1;
            uint8_t two_player_start : 1;
            uint8_t one_player_start : 1;
            uint8_t always1_2 : 1;
            uint8_t p1_shot : 1;
            uint8_t p1_left : 1;
            uint8_t p1_right : 1;
            uint8_t nc : 1;
            // Input port 2
            uint8_t ships : 2;
            uint8_t tilt : 1;
            uint8_t extra_ship: 1;
            uint8_t p2_shot : 1;
            uint8_t p2_left : 1;
            uint8_t p2_right : 1;
            uint8_t coin_info : 1;
        };
        struct {
            uint8_t inp0;
            uint8_t inp1;
            uint8_t inp2;
        };
    };
} space_invaders_input_t;

void space_invaders_input_init(space_invaders_input_t *input);

#endif