//
//  Item.cpp
//  schoolKeeper
//
//  Created by DuoZhao on 2/13/15.
//
//

#include "Item.h"
#include <stdio.h>
#include "Definitions.h"
#include "cocos2d.h"

using namespace cocos2d;

Item::Item(cocos2d::Layer *layer)
{
    item = Sprite::create("bomb.png");
    auto itemBody = PhysicsBody::createBox( item->getContentSize());
    itemBody->setDynamic(false);
    itemBody->setCollisionBitmask( ITEM_COLLISION_BITMASK );
    itemBody->setCategoryBitmask(2);
    itemBody->setContactTestBitmask( 1 );

    item->setScale(1.5);
    item->setPosition(600, 200);
    item->setPhysicsBody( itemBody );
    layer->addChild(item, 50);
    haveExplode = 0;
}

void Item::setPosition(double x, double y){
    item->setPosition(x, y);
}

void Item::explode(){
    //play the explode animation
    if(haveExplode == 0){
    haveExplode=1;
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("explode/explode.plist");
    Vector<SpriteFrame*> animFrames(14);
    char str[100]={0};
    for(int i=1; i<=14; i++){
        sprintf(str, "exp%d.png",i);
        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        animFrames.insert(i-1, frame);
    }

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    Animate* act = Animate::create(animation);
    item->runAction(act);

    }
}

float Item::getX(){
    return item->getPositionX();
}
float Item::getY(){
    return item->getPositionY();
}




