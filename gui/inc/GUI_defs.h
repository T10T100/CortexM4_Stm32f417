
#ifndef GUI_DEFS_H
#define GUI_DEFS_H

#include <stdint.h>

typedef uint16_t ColorDepth; 
typedef int32_t MaxGuiRange;

#define ColorWhite 0xffff
#define ColorBlack 0x0000

template <typename Color>
struct  tImage {
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
    const uint8_t elements;
    const tChar<Color> *imagesSet;   
    const uint8_t w, h; 
};


#define GUI_min(a, b)  (a < b ? a : b)   
#define GUI_max (a, b)  (a >= b ? a : b)   


#define ColorMaskReference ColorWhite

typedef char DefaultCharStorage_t;
typedef tFont<ColorDepth> DefaultFontStorage;

template <typename F, typename Set>
    class FontCharSet {
        private :
            Set *set;
            const F * font;

            
            
        public :
            FontCharSet (Set *set, const F *f)
            {
                this->set = set;
                this->font = f;
            }
            Set get_UTF8 (uint16_t code)
            {
                return set[(uint8_t)code];
            }
            
            
            
            uint32_t getW ()
            {
                return this->font->w;
            }
            uint32_t getH ()
            {
                return this->font->h;
            }
            const F *getFont ()
            {
                return this->font;
            }
    };

#endif /*GUI_DEFS_H*/
