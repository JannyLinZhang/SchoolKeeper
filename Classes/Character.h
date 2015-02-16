//
//  Character.h
//  schoolKeeper
//
//  Created by YangBo's macbook on 15/2/12.
//
//

#ifndef __schoolKeeper__Character__
#define __schoolKeeper__Character__

#include <iostream>
#include "cocos2d.h"

#endif /* defined(__schoolKeeper__Character__) */

class Character{

public:
    Character(cocos2d::Layer *layer);
    void Fall();
    void Move(cocos2d::Vec2 vec,cocos2d::Animation *animation,cocos2d::Sprite *character);
    void Move1(cocos2d::Vec2 vec);
    void Jump();
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Sprite *character;
    //bool isFalling;

};