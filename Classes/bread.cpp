//
//  Bread.cpp
//  schoolKeeper
//
//  Created by DuoZhao on 2/13/15.
//
//

#include "bread.h"
#include <stdio.h>
#include "Definitions.h"
#include "cocos2d.h"

using namespace cocos2d;

Bread::Bread(cocos2d::Layer *layer)
{
    bread = Sprite::create("health.png");
    auto breadBody = PhysicsBody::createBox( bread->getContentSize());
    breadBody->setDynamic(true);
    breadBody->setCollisionBitmask( BREAD_COLLISION_BITMASK );
    breadBody->setCategoryBitmask(2);
    breadBody->setContactTestBitmask( 1 );
    bread->setScale(1.0);
    bread->setPosition(300, 500);
    bread->setPhysicsBody( breadBody );
    layer->addChild(bread);
    }

void Bread::setPosition(double x, double y){
    bread->setPosition(x, y);
}

void Bread::disappear(){
    bread->setVisible(false);
}

