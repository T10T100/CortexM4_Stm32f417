
#ifndef GUI_DEFS_H
#define GUI_DEFS_H

#include <stdint.h>

typedef uint16_t ColorDepth; 
typedef uint16_t MaxGuiRange;

#define ColorWhite 0xffff
#define ColorBlack 0x0000

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


#define GUI_min(a, b)  (a < b ? a : b)   
#define GUI_max (a, b)  (a >= b ? a : b)   

#endif /*GUI_DEFS_H*/
