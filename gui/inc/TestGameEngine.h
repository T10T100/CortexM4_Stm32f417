#ifndef TEST_GAME_ENGINE
#define TEST_GAME_ENGINE

#include "ContentPane.h"
#include "NonPaletteComponentInterface.h"
#include "GameTestWalkingMan.h"


class  TestGameEngine {
    private :
        GContentPane<ColorDepth> *contentPane;
        WalkingManObject<ColorDepth> *mainHero;   
        int32_t tick;
    public :
        TestGameEngine (GContentPane<ColorDepth> *contentPane)
        {
            this->contentPane = contentPane;
            NonPaletteInterface<ColorDepth>  *c = contentPane->createComponent<NonPaletteInterface<ColorDepth> >(0, 0, 700, 340);
            contentPane->addNonPalette( c );
            mainHero = (WalkingManObject<ColorDepth> *) new WalkingManObject<ColorDepth>( c ) ;
            tick = 0;
        }
        
        
        WalkingManObject<ColorDepth> *getMainHero()
        {
            return mainHero;
        }
        
        
        
        void repaint (ViewPort &w)
        {
            static int sw = 0;
            tick++;
            mainHero->tick();
        }
        
    
    
    
};



#endif