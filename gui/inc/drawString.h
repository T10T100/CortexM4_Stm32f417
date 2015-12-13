#ifndef DRAW_STRING_INTERFACE
#define DRAW_STRING_INTERFACE

#include "GcontentPaneInterface.h"


namespace print  {
  

template <typename Color>
    class DrawString  : public virtual GPaneInterface<Color> {
    private :
           Box<MaxGuiRange> Caret;
           char  drawCharSet[255];
           const tFont <Color>* drawFont;
    
        int GetCharCode (char symbol)
            {
              if (this->font == nullptr) return -1;
              uint32_t code = 0;
              uint32_t quantity = this->font->Quantity;
              while ((code != symbol) && (quantity--))
                    code = this->font->CharArray[quantity].Code;
              return quantity;  
            }	
            
            Box<MaxGuiRange> putChar (Box<MaxGuiRange> box, char c, Color color)
            {
                const tImage<MaxGuiRange> *Img = this->drawFont->CharArray[drawCharSet[(int)c]].Image;
                drawChar( box, Img, color);
                this->Caret.x = Img->W + box.x;
                this->Caret.w -=Img->W;
                return this->Caret;
            }
            
            template <typename img_t>
            int32_t drawChar (Box<MaxGuiRange> box, img_t *image, Color color)
            {

                int32_t wm = GUI_min(image->W, box.w);
                int32_t hm = GUI_min(image->H, box.h);

                Color *dest = this->frame;
                const Color *src = image->Image;
                
               
                int32_t S = hm * wm;
                for (int xi = 0, xt = box.x * this->h; xi < wm; xt += this->h, xi++) {  
                        for (uint32_t yt = box.y + xt, yi = xi, t = S + xi; yi < t; yt++, yi += wm) {
                            if (src[yi] != ColorMaskReference) {
                                dest[yt] = color;   
                            } else {}
                        }
                  }
                  return 0;
            }
            
            void setCharSet (char *set)
            {
                this->charSet = set;
            }
            void setDrawFont (tFont <Color> &font)
            {
                this->font = &font;
            }
    
    public :
        DrawString (GraphicFrame<Color, MaxGuiRange> *frame)
        {
            Caret.x = 0;
            Caret.y = 0;
            Caret.w = 0;
            Caret.h = 0;
            GPaneInterface<Color>::operator () (frame);
        }
        void  setDrawFont (const tFont <Color> &font)
            {
                this->drawFont = &font;
                int l = font.Quantity;
                int i  = 0;
                while (l--) {
                    i = (int) this->drawFont->CharArray[l].Code;
                    drawCharSet[i] = l;
                }
            }
        
        
        Box<MaxGuiRange> drawString (Box<MaxGuiRange> rect, char *str, Color color)
        {
                this->Caret = rect;
                char C = '0';
                uint32_t __i = 0;
                while (str[__i] != 0) {
                        C = str[__i++];
                  if (this->Caret.x + this->drawFont->W > (rect.w + rect.x) || (C == '\n')) {
                      this->Caret.x = rect.x;
                      this->Caret.w = rect.w;
                      this->Caret.y += this->drawFont->H;
                      this->Caret.h -= this->drawFont->H;
                  } else {}
                  if (this->Caret.y + this->drawFont->H > rect.h + rect.y) {
                      return this->Caret;
                  } else {}	
                  if ((C != '\n')) {				
                    this->putChar(this->Caret, C, color);		
                  } else {}				
                }
                return this->Caret;
        }
        
        
        
};

};
#endif 
