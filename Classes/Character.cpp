//
//  Character.cpp
//  schoolKeeper
//
//  Created by YangBo's macbook on 15/2/12.
//
//

#include "Character.h"
#include "Definitions.h"
USING_NS_CC;


Character::Character(cocos2d::Layer *layer)
{
    
    

    
    
    
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("BearAnimation/bearAnimation.plist");
    
    
    Vector<SpriteFrame*> animFrames(8);
    char str[100]={0};
    for(int i=1; i<=8; i++){
        sprintf(str, "bear%d.png",i);
        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        animFrames.insert(i-1, frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    
    visibleSize=Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    character = CCSprite::createWithSpriteFrameName("bear1.png");
    character->setScale(0.2);

    
    
    
    //Move(Vec2(900,100),animation,character);
    
    //Move(Vec2(0,100),animation,character);
    
    layer->addChild(character, 100);
    
    
    
}
//
void Character::Move(cocos2d::Vec2 vec,cocos2d::Animation *animation,cocos2d::CCSprite *character){

    
    
    
     CCMoveTo* move1 = CCMoveTo::create(12,vec);
     character->runAction(RepeatForever::create(Animate::create(animation)));

    character->runAction(move1);

}

void Character::Move1(cocos2d::Vec2 vec){
    
    
    
    
    CCMoveBy* move1 = CCMoveBy::create(12,vec);
   
    
    character->runAction(move1);
    
}

void Character::Jump(){
    

  CCActionInterval*  actionUp = CCJumpBy::create(0.5, CCPointMake(0,0), 80, 1);

 
 
    character->runAction(actionUp);
    
}

void Character::Fall(){

}