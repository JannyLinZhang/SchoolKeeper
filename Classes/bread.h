
#ifndef __schoolKeeper__Bread__
#define __schoolKeeper__Bread__

#include <stdio.h>
#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;

class Bread : public Sprite
{
public:
    Bread(cocos2d::Layer *layer);
    void setPosition(double x, double y);
    void disappear();
    cocos2d::Sprite *bread;

    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    };

#endif /* defined(__schoolKeeper__Bread__) */
