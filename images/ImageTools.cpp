#include "ImageTools.h"
#include <cstdint>

Sprite::Sprite(const uint16_t *sprite_pointer, uint8_t sx, uint8_t sy, const uint8_t sw, const uint8_t sh) {
    this->sprite_pointer = sprite_pointer;
    this->x = sx;
    this->y = sy;
    this->width = sw;
    this->height = sh;
}

uint8_t Sprite::get_x() { 
    return this->x;
}

uint8_t Sprite::get_y() {
    return this->y;
}

uint8_t Sprite::get_width() {
    return this->width;
}

uint8_t Sprite::get_height() {
    return this->height;
}

void Sprite::set_x(uint8_t x_pos) {
    this->x = x_pos;
}

void Sprite::set_y(uint8_t y_pos) {
    this->y = y_pos;
}

void Sprite::set_pos(uint8_t x_pos, uint8_t y_pos) {
    this->x = x_pos;
    this->y = y_pos;
}

void Sprite::fill_background(const uint16_t *background, uint16_t *copy) {
    for (uint32_t row = 0; row < this->height; row++) {
        for (uint32_t column = 0; column < this->width; column++) {
            if (this->sprite_pointer[row * this->width + column] == 0xFFFF) {
                copy[row * this->width + column] = background[((160 - this->y + row) * 128) + this->x + column];
            } else {
                copy[row * this->width + column] = this->sprite_pointer[row * this->width + column];
            }
        }
    }
}

uint32_t Sprite::size() {
    return this->width * this->height;
}