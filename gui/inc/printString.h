#ifndef PRINTSTR_CLASS
#define PRINTSTR_CLASS
#include "String.h"
#include "Dimensions.h"
#include "graphicFrameClass.h"
#include "gui_defs.h"

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
    class Print  : public virtual Dimension<MaxGuiRange> {
    private :
           Color *__buffer;
           uint16_t lineCount;
           uint16_t charCount;
           char  charSet[255];
            const tFont <Color>*font;
    
        int GetCharCode (char symbol)
            {
              if (this->font == nullptr) return -1;
              uint32_t code = 0;
              uint32_t quantity = this->font->Quantity;
              while ((code != symbol) && (quantity--))
                    code = this->font->CharArray[quantity].Code;
              return quantity;  
            }	
            
            void putChar (char c, Color color)
            {
                if (this->font == nullptr) return ;
                switch (c) {
                    case nlPad :
                            lineCount +=font->H;      
                            charCount = 0;
                                return;
                            //break;
                    default :
                        break;
                }
                const tImage<MaxGuiRange> *Img = this->font->CharArray[charSet[(int)c]].Image;
                printChar( charCount, lineCount, Img, color);
                charCount += this->font->W;
                if (charCount >= this->w) {
                    charCount = 0;
                    lineCount += this->font->H;
                }
            }
            
            template <typename img_t>
            int32_t printChar (int32_t x0, int32_t y0, img_t *image, Color color)
            {
                int32_t wm = image->W;
                int32_t hm = image->H;

                Color *dest = this->__buffer;
                const Color *src = image->Image;
                
               
                int32_t S = hm * wm;
                for (int xi = 0, xt = x0 * this->h; xi < wm; xt += this->h, xi++) {  
                        for (uint32_t yt = y0 + xt, yi = xi, t = S + xi; yi < t; yt++, yi += wm) {
                            if (src[yi] != ColorMaskReference) {
                                dest[yt] = color;   
                            } else {}
                        }
                  }
                  return 0;
            }
            char *reverseChars (char *charSequence)
            {
                  char *j;
                  int32_t c;
                 
                  j = charSequence + strlen(charSequence) - 1;
                  while(charSequence < j) {
                    c = *charSequence;
                    *charSequence++ = *j;
                    *j-- = c;
                  }	
                  return j;	
            }    
            char *stringifyInt (char *buffer, int32_t value, int32_t base)
            {
                  int32_t i, sign;
                  if ((sign = value) < 0)              /* record sign */
                      value = -value;                    /* make n positive */
                  i = 0;
                  do {                               /* generate digits in reverse order */
                      buffer[i++] = value % base + '0';   /* get next digit */
                  } while ((value /= base) > 0);       /* delete it */
                  if (sign < 0)
                      buffer[i++] = '-';
                  buffer[i] = '\0';
                  return reverseChars(buffer);
            }
            char *stringifyInt (char *buffer, uint32_t value, int32_t base)
            {
                  int32_t i;                   /* make n positive */
                  i = 0;
                  do {                               /* generate digits in reverse order */
                      buffer[i++] = value % base + '0';   /* get next digit */
                  } while ((value /= base) > 0);       /* delete it */
                  buffer[i] = '\0';
                  return reverseChars(buffer);
            }
    
    public :
        Print (GraphicFrame<Color, MaxGuiRange> *frame)
        {
            __buffer = frame->getBuffer();
            lineCount = 0;
            charCount = 0;
            this->setSize(frame->getBox());
        }
        void  setFont (const tFont <Color> &font)
            {
                this->font = &font;
                int l = font.Quantity;
                int i  = 0;
                while (l--) {
                    i = (int) this->font->CharArray[l].Code;
                    charSet[i] = l;
                }
            }
        
        void setText (char *text, Color color)
        {
               int i = 0;
               lineCount = 0;
               charCount = 0;
               while (text[i] != 0) {
                   putChar(text[i], color);     
                   i++;
               }
        }
        void apendText (char *text, Color color)
        {
               int i = 0;
               while (text[i] != 0) {
                   putChar(text[i], color);     
                   i++;
               }
        }
        
        
        
        char *toString (int32_t value)
        {
            static char buf[12];
            stringifyInt(buf, value, 10);
            return buf;
        }
        
        char *toHexString (uint32_t value)
        {
            static char buf[15] = "0x";
            stringifyInt(buf + 2, value, 16);
            return buf;
        }
        
};

};
#endif 


/*End of file*/

