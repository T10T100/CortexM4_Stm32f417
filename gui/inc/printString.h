#ifndef PRINTSTR_CLASS
#define PRINTSTR_CLASS
#include "String.h"
#include "GcontentPaneInterface.h"

#define ColorMaskReference ColorWhite


namespace print  {

enum Format {
	StrFormatTabOnly      = 0,
	StrFormatSpaceOnly    = 1,
	StrFormatTimeOnly     = 2,
};  

enum spacePad {
    nlPad = '\n',
    tPad   =  '\t',
    
    
};
    
template <typename Color>
extern bool putChar (char c, uint32_t x, uint32_t  y,  Color color, uint32_t scaleX, uint32_t scaleY);

template <typename Color>
    class Print  : public virtual GPaneInterface<Color> {
    private :
           uint16_t lineCount;
           uint16_t charCount;
           FontCharSet<DefaultFontStorage, DefaultCharStorage_t> *charSet;

    
            
            void putChar (char c, Color color, const tChar<ColorDepth> *imagesSet)
            {
                switch (c) {
                    case nlPad :
                            lineCount += charSet->getH();      
                            charCount = 0;
                            return;
                            //break;
                    default :
                        break;
                }
                printChar( charCount, \
                           lineCount, \
                           imagesSet[charSet->get_UTF8((uint16_t)c)].Image, \
                           color );
                
                charCount += this->charSet->getW();
                if (charCount >= this->w) {
                    charCount = 0;
                    lineCount += this->charSet->getH();
                }
            }
            
            template <typename img_t>
            int32_t printChar (int32_t x0, int32_t y0, img_t *image, Color color)
            {
                int32_t wm = image->W;
                int32_t hm = image->H;

                Color *dest = this->frame;
                const Color *src = image->Image;
                
               
                int32_t S = hm * wm;
                for (int xi = 0, xt = x0 * this->h; xi < wm; xt += this->h, xi++) {  
                        for (uint32_t yt = y0 + xt, yi = S - wm + xi; yi >= xi; yt++, yi -= wm) {
                            if (src[yi] != ColorMaskReference) {
                                dest[yt] = color;   
                            } else {}
                        }
                  }
                  return 0;
            }
    
    public :
        Print (GraphicFrame<Color, MaxGuiRange> *frame)
        {
            
            lineCount = 0;
            charCount = 0;
            GPaneInterface<Color>::operator () (frame);
        }
        
        void setCharSet (FontCharSet<DefaultFontStorage, DefaultCharStorage_t> *set)
        {
            this->charSet = set;
        }
        
   
        void setText (char *text, Color color)
        {
               int i = 0;
               lineCount = 0;
               charCount = 0;
               const tChar<ColorDepth> *imagesSet = charSet->getFont()->imagesSet;
               while (text[i] != 0) {
                   putChar(text[i], color, imagesSet);     
                   i++;
               }
        }
        void apendText (char *text, Color color)
        {
               int i = 0;
               const tChar<ColorDepth> *imagesSet = charSet->getFont()->imagesSet;
               while (text[i] != 0) {
                   putChar(text[i], color, imagesSet);     
                   i++;
               }
        }
        
        
        
};

};
#endif 


/*End of file*/

