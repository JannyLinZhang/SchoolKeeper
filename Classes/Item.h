//
//  Role.h
//  schoolKeeper
//
//
//

#ifndef __schoolKeeper__Item__
#define __schoolKeeper__Item__

#include <stdio.h>
#include <iostream>

#include "cocos2d.h"

using namespace cocos2d;
//using namespace std;

class Item : public Sprite
{
public:
    Item(cocos2d::Layer *layer);
    void setPosition(double x, double y);
    void explode();

    float getX();
    float getY();
    void Visible(bool b);
    void explodeEnd();
    bool havePickedUp;
    void throwBomb(Point Start, bool flip);
    bool haveExplode;

    
private:
    cocos2d::Sprite *item;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    };

#endif /* defined(__schoolKeeper__Item__) */
