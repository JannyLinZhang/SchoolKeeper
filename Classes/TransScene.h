//
//  TransScene.h
//  schoolKeeper
//
//  Created by ZhangLin on 4/7/15.
//
//

#ifndef __schoolKeeper__TransScene__
#define __schoolKeeper__TransScene__

#include <stdio.h>

#include "GameScene2.h"



using namespace std;

class TransScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TransScene);
    
private:
    void GoToNextLevelScene(float dt);
    
};

#endif /* defined(__schoolKeeper__TransScene__) */
