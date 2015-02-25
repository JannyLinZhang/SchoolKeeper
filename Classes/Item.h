//
//  Role.h
//  schoolKeeper
//
//  Created by ZhangLin on 2/13/15.
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
    
private:
    cocos2d::Sprite *item;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

#endif /* defined(__schoolKeeper__Item__) */
