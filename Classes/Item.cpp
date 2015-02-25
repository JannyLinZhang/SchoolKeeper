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
    
    item = Sprite::createWithSpriteFrameName("bear1.png");
    item->setPosition(Point(visibleSize.width/2+ CCRANDOM_0_1()* origin.x,
                               visibleSize.height/2+ CCRANDOM_0_1()*origin.y));
    item->runAction(RepeatForever::create(Animate::create(animation)));
    spriteSheet->addChild(item);
    item->setScale(0.3);
}

void Item::setPosition(Point p){
    //set the Position of Item
    
}
void Item::explode(){
    //explode itself and disapear
}



