//
//  TranScene2.cpp
//  schoolKeeper
//
//  Created by Duo on 4/19/15.
//
//

#include "TranScene2.h"

using namespace cocos2d;



Scene* TransScene2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TransScene2::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TransScene2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //this->scheduleOnce(schedule_selector(TransScene::GoToNextLevelScene), DISPLAY_TIME_SPLASH_SCENE);
    
    auto backgroundSprite = Sprite::create("TransBackground.jpg");
    backgroundSprite->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    this->addChild(backgroundSprite);
    
    auto label2 = Label::createWithTTF("Level 3", "fonts/Marker Felt.ttf", 256);
    label2->setPosition(Vec2(visibleSize.width / 2,  visibleSize.height / 2));
    this->addChild(label2);
    
    this->scheduleOnce(schedule_selector(TransScene2::GoToNextLevelScene), 2.0);
    
    return true;
}


void TransScene2::GoToNextLevelScene(float dt){
    
    auto scene3 = GameScene3::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene3));
    
}

