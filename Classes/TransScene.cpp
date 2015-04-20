//
//  TransScene.cpp
//  schoolKeeper
//
//  Created by ZhangLin on 4/7/15.
//
//

#include "TransScene.h"
#include "Definitions.h"

using namespace cocos2d;

Scene* TransScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TransScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TransScene::init()
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
    
    auto label2 = Label::createWithTTF("Level 2", "fonts/Marker Felt.ttf", 256);
    label2->setPosition(Vec2(visibleSize.width / 2,  visibleSize.height / 2));
    this->addChild(label2);

    this->scheduleOnce(schedule_selector(TransScene::GoToNextLevelScene), 2.0);
    
    return true;
}


void TransScene::GoToNextLevelScene(float dt){
    
        auto scene2 = GameScene2::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene2));
    
}

