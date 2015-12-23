#ifndef DRAW_STRING_INTERFACE
#define DRAW_STRING_INTERFACE

#include "GcontentPaneInterface.h"


namespace print  {
  

template <typename Color>
    class DrawString  : public virtual GPaneInterface<Color> {
    private :
            Dimension<MaxGuiRange> Caret;
            FontCharSet<DefaultFontStorage, DefaultCharStorage_t> *drawCharSet;
            
            int8_t scaleX;
            int8_t scaleY;
            
            Dimension<MaxGuiRange> &putChar (Dimension<MaxGuiRange> box, char c, Color color, const tChar<ColorDepth> *imagesSet, bool scaled)
            {
                const tImage<ColorDepth> *img = imagesSet[ drawCharSet->get_UTF8( (uint16_t)c ) ].Image;
                if (scaled == false) {
                    drawChar(box, img, color);
                } else {
                    drawScaledChar(box, img, color);
                }
                this->Caret.x = img->W * scaleX + box.x;
                this->Caret.w -= img->W * scaleX;
                return this->Caret;
            }
            
            template <typename img_t>
            int32_t drawChar (Dimension<MaxGuiRange> box, img_t *image, Color color)
            {

                int32_t wm = GUI_min(image->W, box.w);
                int32_t hm = GUI_min(image->H, box.h);

                Color *dest = this->frame;
                const Color *src = image->Image;
                
               
                int32_t S = hm * wm;
                for (int xi = 0, xt = box.x * this->h; xi < wm; xt += this->h, xi++) {  
                        for (int32_t yt = box.y + xt, yi = S + xi - wm; yi >= xi; yt++, yi -= wm) {
                            if (src[yi] != ColorMaskReference) {
                                dest[yt] = color;   
                            } else {}
                        }
                  }
                  return 0;
            }
            
            template <typename img_t>
            int32_t drawScaledChar (Dimension<MaxGuiRange> rect, img_t *image, Color color)
            {
                rect.w = image->W * scaleX;
                rect.h = image->H * scaleY;
                
                register int32_t h  = this->h;
                register int32_t ys = this->scaleY;
                register int32_t xs = this->scaleX;
                register int32_t xt = rect.w / xs;
                register int32_t yt = rect.h / ys;	
                
                register int32_t S = yt * image->W;
                register Color *target = this->frame;
                register const Color* source = image->Image;
                Color targ = 0xffff;
                register uint32_t ws = image->W;
                if ( 0 ) {
                    for (int32_t xi = 0, x = rect.x * h; xi < xt; xi++) { 
                            for (int32_t d = x + xs * h; x < d; x += h) {
                                    for (int32_t y = rect.y + 1, yi = 0; yi < S; yi+= ws) {
                                            for (int32_t d = y + ys; y < d; y++) {
                                                 target[y + x] = source[xi + yi]; 
                                            }
                                    }
                            }
                    }	
              }	else {
                    for (uint32_t xi = 0, x = rect.x * h; xi < xt; xi++) { 
                            for (uint32_t d = x + xs * h; x < d; x += h) {
                                    for (uint32_t y = rect.y + 1, yi = S; yi < S; yi += ws) {
                                            for (uint32_t d = y + ys; y < d; y++) {
                                                  if (source[xi + yi] != targ) {
                                                        target[y + x] = color;
                                                    } else {}	
                                            }
                                    }
                            }
                    }			
                }
                return 0;
            }
            
    
    public :
        DrawString (GraphicFrame<Color, MaxGuiRange> *frame)
        {
            Caret.x = 0;
            Caret.y = 0;
            Caret.w = 0;
            Caret.h = 0;
            GPaneInterface<Color>::operator () (frame);
            scaleX = 1;
            scaleY = 1;
        }
      
        template <typename Range>
        Dimension<Range> &drawString (Dimension<Range> rect, char *str, Color color, bool scaled = false, bool oneLine = false)
        {
                this->Caret = rect;
                char C = '0';
                uint32_t __i = 0;
                const tChar<ColorDepth> *imagesSet = drawCharSet->getFont()->imagesSet;
                while (str[__i] != 0) {
                      C = str[__i++];
                  if (this->Caret.x + drawCharSet->getW() * scaleX > (rect.w + rect.x) || (C == '\n')) {
                      if (oneLine = true) {
                          return this->Caret;
                      }
                      this->Caret.x = rect.x;
                      this->Caret.w = rect.w;
                      this->Caret.y += drawCharSet->getH() * scaleY;
                      this->Caret.h -= drawCharSet->getH() * scaleY;
                      
                  } else {}
                  if (this->Caret.y + drawCharSet->getH() * scaleY > rect.h + rect.y) {
                      return this->Caret;
                  } else {}	
                  if ((C != '\n')) {				
                      this->putChar(this->Caret, C, color, imagesSet, scaled);		
                  } else {
                      this->Caret.y += drawCharSet->getH() * scaleY;
                      this->Caret.h -= drawCharSet->getH() * scaleY;
                  }				
                }
                return this->Caret;
        }
        
        template <typename Range>
        Dimension<Range> &drawScaledString (Dimension<Range> rect, char *str, Color color, int8_t sX = 2, int8_t sY = 2, bool oneLine = false)
        {
                scaleX = sX;
                scaleY = sY;
                Dimension<int32_t> &d = drawString(rect, str, color, true, oneLine);
                scaleX = 1;
                scaleY = 1;
        }

        void drawScaledString (char *str, Color color, int8_t sX = 2, int8_t sY = 2, bool oneLine = false)
        {
                scaleX = sX;
                scaleY = sY;
                Dimension<int32_t> rect(this->x, this->y, this->w, this->h);
                drawScaledString<int32_t>(rect, str, color, true, oneLine);
                scaleX = 1;
                scaleY = 1;
        }
        
        void setDrawCharSet (FontCharSet<DefaultFontStorage, DefaultCharStorage_t> *set)
        {
            this->drawCharSet = set;
        }
        
        uint32_t getFontWidth ()
        {
            return drawCharSet->getW();
        }
        
        
        
};

};
#endif 
