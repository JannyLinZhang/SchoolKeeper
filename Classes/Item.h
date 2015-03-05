//
//  Role.h
//  schoolKeeper
//
//
//

#ifndef __schoolKeeper__Item__
#define __schoolKeeper__Item__

#include <stdio.h>

#include "cocos2d.h"

using namespace cocos2d;
//using namespace std;

class Item : public Sprite
{
public:
    Item(cocos2d::Layer *layer);
    void setPosition(Point p);
    void explode();
    float getX();
    float getY();
    
private:
    cocos2d::Sprite *item;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    bool haveExplode;
};

#endif /* defined(__schoolKeeper__Item__) */
