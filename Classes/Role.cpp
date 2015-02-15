//
//  Role.cpp
//  schoolKeeper
//
//  Created by ZhangLin on 2/13/15.
//
//

#include "Role.h"
#include <stdio.h>
#include "Definitions.h"
#include "cocos2d.h"

using namespace cocos2d;

Role::Role(cocos2d::Layer *layer)
//Role::Role()
{
    visibleSize=Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    SpriteBatchNode* spriteSheet = SpriteBatchNode::create("BearAnimation/bearAnimationSheet.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("BearAnimation/bearAnimation.plist");
    layer->addChild(spriteSheet);
    Vector<SpriteFrame*> animFrames(8);
    char str[100]={0};
    for(int i=1; i<=8; i++){
        sprintf(str, "bear%d.png",i);
        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        animFrames.insert(i-1, frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    
    comrole = Sprite::createWithSpriteFrameName("bear1.png");
    comrole->setPosition(Point(visibleSize.width/2+ CCRANDOM_0_1()* origin.x,
                               visibleSize.height/2+ CCRANDOM_0_1()*origin.y));
    comrole->runAction(RepeatForever::create(Animate::create(animation)));
    spriteSheet->addChild(comrole);
    comrole->setScale(0.3);
    
    //comrole = Sprite::create("StanMarsh.png");
    //comrole->setPosition(Point(visibleSize.width/2+ CCRANDOM_0_1()* origin.x,
     //                       visibleSize.height/2+ CCRANDOM_0_1()*origin.y));
    
    //auto roleBody = PhysicsBody::createCircle(comrole->getContentSize().width/2);
    //roleBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    //roleBody->setContactTestBitmask(true);
    
    //comrole->setPhysicsBody(roleBody);
  //  layer->addChild(comrole, 100);
    
}

void Role::genNextPos(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int minY = comrole->getContentSize().height / 2;
    int maxY = visibleSize.height - comrole->getContentSize().height / 2;
    int minX = comrole->getContentSize().width /2;
    int maxX = visibleSize.width - comrole->getContentSize().width / 2;
    
    int rangeY = maxY - minY;
    int actualY = (CCRANDOM_0_1() * rangeY) + minY;
    int rangeX = maxX - minX;
    int actualX = (CCRANDOM_0_1() *rangeX) + minX;
    
    m_desPoint.x = actualX;
    m_desPoint.y = actualY;
}

/*
void Bird::Fall(){
    if(isFalling == true){
        flappyBird->setPositionX(visibleSize.width/2+origin.x);
        flappyBird->setPositionY(flappyBird->getPositionY()-(BIRD_FALLING_SPEED*visibleSize.height));
    }else{
        flappyBird->setPositionX(visibleSize.width/2+origin.x);
        flappyBird->setPositionY(flappyBird->getPositionY()+(BIRD_FALLING_SPEED*visibleSize.height));
    }
}
*/

void Role::move(){
    int minDuration = 2.0;
    int maxDuration = 5.0;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (CCRANDOM_0_1() * rangeDuration) + minDuration;
    
    genNextPos();
    auto actionMove = MoveTo::create(actualDuration, m_desPoint);
    comrole->runAction(actionMove);
}
/*
void Role::move(){
    //comrole->moveNext();
    //auto MoveCallBack = CallFuncN::create(CC_CALLBACK_0(Role::move, this));
    //comrole->runAction(MoveCallBack);
}
*/
/*
 void Role::update_pos(){
 float distance = ccpDistance(getPosition(), m_desPoint);
 float t = distance / m_speed;
 float speed_x = (m_desPoint.x - getPositionX()) / t;
 float speed_y = (m_desPoint.y - getPositionY()) / t;
 setPositionX(getPositionX() + speed_x);
 setPositionY(getPositionY() + speed_y);
 }
 */



