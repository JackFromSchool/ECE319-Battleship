// images.h
// contains image buffers for simple space invaders
// Jonathan Valvano, March 5, 2018
// Capture image dimensions from BMP files

#ifndef __images_h
#define __images_h
#include <stdint.h>

#define BOARD_BG 0x38B7
#define BOARD_TEXT 0x0061
#define MENU_BG 0x53E3
#define MENU_TEXT 0x0903
extern const uint16_t battleship_board[];

extern const uint16_t two_space_battleship1[];
extern const uint16_t two_space_battleship2[];
extern const uint16_t three_space_battleship[];
extern const uint16_t four_space_battleship[];
extern const uint16_t five_space_battleship[];

extern const uint16_t two_space_battleship190[];
extern const uint16_t two_space_battleship290[];
extern const uint16_t three_space_battleship90[];
extern const uint16_t four_space_battleship90[];
extern const uint16_t five_space_battleship90[];

extern const uint16_t miss_marker[];
extern const uint16_t hit_marker[];
extern const uint16_t cursor_marker[];

extern const uint16_t explosion1[];
extern const uint16_t explosion2[];
extern const uint16_t explosion3[];

extern const uint16_t battleship_logo[];

#endif /* __images_h */
