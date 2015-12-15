#ifndef FONT_FACTORY_CLASS
#define FONT_FACTORY_CLASS
#include "memory_template.h"
#include "ArrayList.h"
#include "gui_Defs.h"



template <typename F, typename Set>
class FontFactory {
    private :
        ArrayList<FontCharSet<DefaultFontStorage, DefaultCharStorage_t> > fontsCollection;
    public :
        FontCharSet<F, Set> *collectFont (const F *f)
        {
            Set *set = (Set *) new Set[256];
            if (set == nullptr) {
                return nullptr;
            }
            FontCharSet<DefaultFontStorage, DefaultCharStorage_t> *fontSet = \
                        (FontCharSet<DefaultFontStorage, DefaultCharStorage_t> *) new \
                                    FontCharSet<DefaultFontStorage, DefaultCharStorage_t>(set, f);
            if (fontSet == nullptr) {
                delete(set);
                return nullptr;
            }
            makeSet(set, f);
            fontsCollection.addFirst(fontSet);
            return fontSet;
        }
        
        
        Set *makeSet (Set *set, const F *f)
        {
                int l = f->elements;
                int i  = 0;
                while (l--) {
                    i = (int) f->imagesSet[l].Code;
                    set[i] = l;
                }
                return set;
        }
};




#endif

/*End of file*/


