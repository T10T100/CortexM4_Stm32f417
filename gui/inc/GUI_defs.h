
#ifndef GUI_DEFS_H
#define GUI_DEFS_H

#include <stdint.h>


template <typename Color>
struct  tImage{
    const Color *Image;
    uint16_t W, H;
    
};

template <typename Color>
struct tChar {
    const uint8_t Code;
    const tImage<Color> *Image;       
};

template <typename Color>
struct tFont {
    const uint8_t Quantity;
    const tChar<Color> *CharArray;   
    const uint8_t W, H;    
};




#endif /*GUI_DEFS_H*/
