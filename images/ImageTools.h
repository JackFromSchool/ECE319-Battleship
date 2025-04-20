#ifndef IMAGETOOLS_H
#define IMAGETOOLS_H

#include <stdint.h> 

// Top Left is 0, 0
// Bottom Right is 10, 10
// Switches to pixel coord needed to render sprite.
#define BOARDSPACEX(x) (x*12 + 4)
#define BOARDSPACEY(y, height) (y*12 + 4 + 11)

#define DRAWSPRITE(sprite, sprite_ptr) \
    ST7735_DrawBitmap(sprite.get_x(), sprite.get_y(), sprite_ptr, sprite.get_width(), sprite.get_height())

class Sprite {
    private:
        uint8_t x;
        uint8_t y;
        uint8_t width;
        uint8_t height;
        const uint16_t *sprite_pointer;
    public:
        Sprite(const uint16_t *sprite_pointer, uint8_t sx, uint8_t sy, const uint8_t sw, const uint8_t sh);
        void fill_background(const uint16_t *background, uint16_t *copy);
        void set_pos(uint8_t x_pos, uint8_t y_pos);
        void set_x(uint8_t x_pos);
        void set_y(uint8_t y_pos);
        uint8_t get_x();
        uint8_t get_y();
        uint8_t get_width();
        uint8_t get_height();
        uint32_t size();
};

#endif