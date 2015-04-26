//
//  GameOverSceneWin.h
//  schoolKeeper
//
//  Created by ZhangLin on 4/23/15.
//
//

#ifndef __schoolKeeper__GameOverSceneWin__
#define __schoolKeeper__GameOverSceneWin__

#include <stdio.h>
#include "Definitions.h"
#include "MainMenuScene.h"
class GameOverSceneWin : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverSceneWin);
    
private:
    void GoToMainMenuScene(float dt);
};








#endif /* defined(__schoolKeeper__GameOverSceneWin__) */
