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
    havePickedUp = 0;
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
    std::cout<<"111111";

        
    //CallFunc* callFunc1=CallFunc::create(this,callfunc_selector(Item::explodeEnd));
    Sequence* endAct=Sequence::create(act,CallFunc::create( std::bind(&Item::explodeEnd,this) ),NULL);
    item->runAction(endAct);

    }
}



float Item::getX(){
    return item->getPositionX();
}
float Item::getY(){
    return item->getPositionY();
}
void Item::Visible(bool b){
    item->setVisible(b);
}

void Item::explodeEnd(){
    std::cout<<"222222"<<std::endl;
    item->setVisible(false);
}

void Item::throwBomb(Point Start, bool flip){
    item->setPosition(Start);
    item->setVisible(true);
    MoveTo *moveto;
    Point End;
    if(flip == true){
        End = Start+Point(200,-45);
    }else{
        End = Start+Point(-200,-45);
    }
    moveto = MoveTo::create(0.2, End);
    
    std::cout<<"000000";
    //CallFunc* callFunc0=CallFunc::create(this,callfunc_selector(Item::explode));
    Sequence* throwAct=Sequence::create(moveto, CallFunc::create( std::bind(&Item::explode,this) ), NULL);
    item->runAction(throwAct);

}




