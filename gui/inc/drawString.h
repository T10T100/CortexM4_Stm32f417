#ifndef DRAW_STRING_INTERFACE
#define DRAW_STRING_INTERFACE

#include "GcontentPaneInterface.h"


namespace print  {
  

template <typename Color>
    class DrawString  : public virtual GPaneInterface<Color> {
    private :
            Dimension<MaxGuiRange> Caret;
            FontCharSet<DefaultFontStorage, DefaultCharStorage_t> *drawCharSet;
    	
            
            Dimension<MaxGuiRange> &putChar (Dimension<MaxGuiRange> box, char c, Color color, const tChar<ColorDepth> *imagesSet)
            {
                const tImage<ColorDepth> *img = imagesSet[drawCharSet->get_UTF8((uint16_t)c)].Image;
                drawChar(box, img, color);
                this->Caret.x = img->W + box.x;
                this->Caret.w -= img->W;
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
                        for (uint32_t yt = box.y + xt, yi = xi, t = S + xi; yi < t; yt++, yi += wm) {
                            if (src[yi] != ColorMaskReference) {
                                dest[yt] = color;   
                            } else {}
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
        }
      
        template <typename Range>
        Dimension<Range> &drawString (Dimension<Range> rect, char *str, Color color)
        {
                this->Caret = rect;
                char C = '0';
                uint32_t __i = 0;
                const tChar<ColorDepth> *imagesSet = drawCharSet->getFont()->imagesSet;
                while (str[__i] != 0) {
                      C = str[__i++];
                  if (this->Caret.x + this->drawCharSet->getW() > (rect.w + rect.x) || (C == '\n')) {
                      this->Caret.x = rect.x;
                      this->Caret.w = rect.w;
                      this->Caret.y += this->drawCharSet->getH();
                      this->Caret.h -= drawCharSet->getH();
                  } else {}
                  if (this->Caret.y + drawCharSet->getH() > rect.h + rect.y) {
                      return this->Caret;
                  } else {}	
                  if ((C != '\n')) {				
                      this->putChar(this->Caret, C, color, imagesSet);		
                  } else {
                      this->Caret.y += this->drawCharSet->getH();
                      this->Caret.h -= drawCharSet->getH();
                  }				
                }
                return this->Caret;
        }
        
        void setDrawCharSet (FontCharSet<DefaultFontStorage, DefaultCharStorage_t> *set)
        {
            this->drawCharSet = set;
        }
        
        
        
};

};
#endif 
