#ifndef GameTestWalkingMan
#define GameTestWalkingMan

#include "NonPaletteComponentInterface.h"
#include "GraphicComponent.h"
#include "ContentPane.h"

int WalkingManRepaintHook (void *);
void WalkingManThrowingWeaponRepaintHook (void *);

extern const tImage<uint16_t> krummWalk0;

int DefaultWalkingManClickListener (TouchStruct arg);
int DefaultWalkingManTouchListener (TouchStruct arg);
int DefaultWalkingManReleaseListener (TouchStruct arg);


enum WalkingManActionEnum {
    WalkingManWalk = 0, /*or iddle*/
    WalkingManThrow = 1,
    
};

#define WalkingManObjectId 0x0000A00D

template <typename Color>
    class WalkingManObject : public Dimension<int32_t>
{
    private :
        Graphic<Color> *graphic;  
        NonPaletteInterface<Color> *paletteInterface;    
        GraphicObject<ColorDepth> *throwingWeapon;
        int throwingWeaponLifeTime;
    
        friend int WalkingManRepaintHook (void *);
        friend int DefaultWalkingManClickListener (TouchStruct);
        friend int DefaultWalkingManTouchListener (TouchStruct);
        friend int DefaultWalkingManReleaseListener (TouchStruct);
    
        int32_t  tickCount;
        int16_t  neededStepCount;
        int16_t  stepX;
        int16_t  stepY;
        int32_t  xTarget;
        int32_t  yTarget;
        int8_t   action;
        int8_t   direction;
    public :  
        
    WalkingManObject (NonPaletteInterface<Color> *interface ) : Dimension<int32_t>(0, 0, 50, 50)
        {
            this->graphic = interface->getGraphic();
            this->paletteInterface = interface;
            this->paletteInterface->setUserObject(this, WalkingManObjectId);
            this->paletteInterface->setRepaintHook(WalkingManRepaintHook);
            tickCount = 0;
            xTarget = 0;
            xTarget = 0;
            stepX = 0;
            stepY = 0;
            action = 0;
            direction = 0;
            neededStepCount = 0;
            throwingWeapon = nullptr;
            throwingWeaponLifeTime = 0;
            this->paletteInterface-> setForceRepaint(true);
            this->paletteInterface->addClickListener(DefaultWalkingManClickListener);
            this->paletteInterface->addTouchListener(DefaultWalkingManTouchListener);
            this->paletteInterface->addReleaseListener(DefaultWalkingManReleaseListener);
        }
        
        int32_t tick ()
        {
            tickCount++;
            if (throwingWeaponLifeTime > 0) {
                throwingWeaponLifeTime--;
            } else {
                cleanUpThrowWeapon();
            }
            return tickCount;
        }
        
        void throwWeapon (int power, int direction)
        {
            if (throwingWeapon != nullptr) {
                return;
            }
            throwingWeapon = (GraphicObject<ColorDepth> *) new GraphicObject<ColorDepth>(this->graphic);
            throwingWeapon->setSize(this->x, this->y, 50, 50);
            if (direction == 0) {
                throwingWeapon->dx = 10;
            } else if (direction == 2) {
                throwingWeapon->dx = -10;
            }
            throwingWeapon->setRepaintHook(WalkingManThrowingWeaponRepaintHook);
            ((GContentPane<ColorDepth> *)paletteInterface->getContentPane())->addGraphic(throwingWeapon);
            throwingWeaponLifeTime = 20;
        }
        
        void cleanUpThrowWeapon ()
        {
            ((GContentPane<ColorDepth> *)paletteInterface->getContentPane())->removeGraphic(throwingWeapon);
            delete(throwingWeapon);
            throwingWeapon = nullptr;
        }
        
        
                   
};






#endif

/*End of file*/


