#include "GameTestWalkingMan.h"

int globalIntTemp = 0;

int DefaultWalkingManClickListener (TouchStruct arg)
{
    NonPaletteInterface<ColorDepth> *I = (NonPaletteInterface<ColorDepth> *)arg.object;
    WalkingManObject<ColorDepth> *man = (WalkingManObject<ColorDepth> *)I->getUserObject();
        
        int xS = arg.local.x - man->x;
        int yS = arg.local.y - man->y;
        if (xS < 0) {
            man->direction = 2;
        } else {
             man->direction = 0;   
        }
    if (arg.clickCount >= 2) { 
        globalIntTemp = 0;
        man->action = WalkingManThrow;
        man->throwWeapon(10, man->direction);
    } else {
        man->xTarget = arg.local.x;
        man->yTarget = arg.local.y;
        man->action = WalkingManWalk;
        int dir = 0;
        if ((xS > 0 ? xS : -xS) > (yS > 0 ? yS : -yS)) {
            man->stepX = xS > 0 ? 5 : -5;
            man->neededStepCount = xS / man->stepX;
            man->stepY = yS / man->neededStepCount;
        } else {
            man->stepY = yS > 0 ? 5 : -5;
            man->neededStepCount = yS / man->stepY;
            man->stepX = xS / man->neededStepCount; 
        }
    }
    return -1;
}
int DefaultWalkingManTouchListener (TouchStruct arg)
{
    NonPaletteInterface<ColorDepth> *I = (NonPaletteInterface<ColorDepth> *)arg.object;
    WalkingManObject<ColorDepth> *man = (WalkingManObject<ColorDepth> *)I->getUserObject();
    
    return -1;
}
int DefaultWalkingManReleaseListener (TouchStruct arg)
{
    NonPaletteInterface<ColorDepth> *I = (NonPaletteInterface<ColorDepth> *)arg.object;
    WalkingManObject<ColorDepth> *man = (WalkingManObject<ColorDepth> *)I->getUserObject();
    
    return -1;
}


extern tImage<uint16_t> *krummWalkSet[];
extern tImage<uint16_t> *krummThrowSet[];

int WalkingManRepaintHook (void *parent)
{
    NonPaletteInterface<ColorDepth> *I = (NonPaletteInterface<ColorDepth> *)parent;
    WalkingManObject<ColorDepth> *man = (WalkingManObject<ColorDepth> *)I->getUserObject();
    if (man->action > 0) {
        switch (man->action) {
            case WalkingManWalk:
                break;
            case WalkingManThrow:
                if (globalIntTemp < 4) {
                    man->graphic->fill(man->getBox(), krummThrowSet[globalIntTemp], 0x0000, man->direction);
                    globalIntTemp++;
                } else {
                    man->action = WalkingManWalk;
                    man->graphic->fill(man->getBox(), krummWalkSet[1], 0x0000, man->direction);
                }
                break;
            
            default :
                break;
        }
    } else if (man->neededStepCount > 0) {
        man->x += man->stepX;
        man->y += man->stepY;
        man->neededStepCount--;
        man->graphic->fill(man->getBox(), krummWalkSet[man->tick() % 10], 0x0000, man->direction);
    } else {
        man->graphic->fill(man->getBox(), krummWalkSet[1], 0x0000, man->direction);
    }
    return 0;
}

extern const tImage<uint16_t> *krummThrowAmmoSet[];

void WalkingManThrowingWeaponRepaintHook (void *arg)
{
    static int frameCount = 0;
    
    GraphicObject<ColorDepth> *o = (GraphicObject<ColorDepth> *)arg;
    if (frameCount > 3) {
        frameCount = 0;
    }
    o->getGraphic()->fill(o->getBox(), krummThrowAmmoSet[frameCount++], 0);
    o->x += o->dx;
}

