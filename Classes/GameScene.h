#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "Role.h"
#include "Character.h"
#include "Item.h"
#include <vector>
#include "ProgressView.h"

using namespace std;


class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    void RoleLogic(float dt);
    vector<Role*> roles;
    Character* character;
    Item** items;
    int numberOfItem;
    Role* monster;
    LabelTTF* label; 


    cocos2d::PhysicsWorld *sceneWorld;
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world){sceneWorld = world;}
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event);
    void StopFlying(float dt);
    void update(float dt);
    SneakyJoystick *joyStick;
    void joyStickInitialize();
    ProgressView *progressView;  //血条
    bool isRectCollision (CCRect rect1, CCRect rect2);
    void buttonCallBack(Object* pSender);


    

    
};

#endif // __GAME_SCENE_H__
