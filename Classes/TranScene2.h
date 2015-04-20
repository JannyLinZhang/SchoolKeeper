//
//  TranScene2.h
//  schoolKeeper
//
//  Created by Duo on 4/19/15.
//
//

#ifndef __schoolKeeper__TranScene2__
#define __schoolKeeper__TranScene2__

#include <stdio.h>

#include "GameScene3.h"
#include "Definitions.h"


using namespace std;

class TransScene2 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TransScene2);
    
private:
    void GoToNextLevelScene(float dt);
    
 
};



#endif /* defined(__schoolKeeper__TranScene2__) */
