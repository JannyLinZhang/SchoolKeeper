//
//  GameOverSceneWin.cpp
//  schoolKeeper
//
//  Created by ZhangLin on 4/23/15.
//
//

#include "GameOverSceneWin.h"
USING_NS_CC;

Scene* GameOverSceneWin::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverSceneWin::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverSceneWin::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    //this->scheduleOnce(schedule_selector(TransScene::GoToNextLevelScene), DISPLAY_TIME_SPLASH_SCENE);
    
    auto backgroundSprite = Sprite::create("TransBackground.jpg");
    backgroundSprite->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    this->addChild(backgroundSprite);
    
    auto label2 = Label::createWithTTF("You Win!", "fonts/Marker Felt.ttf", 256);
    label2->setPosition(Vec2(visibleSize.width / 2,  visibleSize.height / 2));
    this->addChild(label2);
    
    this->scheduleOnce(schedule_selector(GameOverSceneWin::GoToMainMenuScene), 2.0);
    
    return true;
}

void GameOverSceneWin:: GoToMainMenuScene(float dt){
    auto scenewin = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scenewin));
}


