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
    /*
    visibleSize=Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    item = Sprite::create("bomb.png");
    item->setPosition(Point(300,300));
    item->setScale(0.1);
    layer->addChild(item);
     */
    SpriteBatchNode* spriteSheet = SpriteBatchNode::create("numbers/numbers.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("numbers/numbers.plist");
    layer->addChild(spriteSheet);
    /*
    Vector<SpriteFrame*> animFrames(7);
    char str[100]={0};
    for(int i=1; i<=7; i++){
        sprintf(str, "%d.png",i-1);
        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        animFrames.insert(i-1, frame);
    }
     */
    //Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
    item = Sprite::createWithSpriteFrameName("0.png");
    item->setPosition(Point(300,300));
    //item->runAction(RepeatForever::create(Animate::create(animation)));
    item->setScale(1.0);
    spriteSheet->addChild(item);
}

void Item::setPosition(Point p){
    //set the Position of Item
    item->setPosition(p);
}
void Item::explode(){
    //explode itself and disapear
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("numbers/numbers.plist");
    Vector<SpriteFrame*> animFrames(7);
    char str[100]={0};
    for(int i=1; i<=7; i++){
        sprintf(str, "%d.png",i-1);
        SpriteFrame* frame = cache->getSpriteFrameByName(str);
        animFrames.insert(i-1, frame);
    }

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
    item->runAction(RepeatForever::create(Animate::create(animation)));

}



