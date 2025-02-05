#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "monster.h"
#include "Character.h"
#include "Item.h"
#include "bread.h"
#include <vector>
#include "ProgressView.h"
#include "Boss.h"
#include "GameOverScene.h"

using namespace std;


class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void InitialMonsters(int num);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    void GoToGameOverScene(float dt);
    
private:
    void RoleLogic(float dt);
    Character* character;
    Boss* boss;
    Item** items;
    int numberOfItem;
    int* canPickUp;
    LabelTTF* label;
    bool face;
    int numbeOfMonster;
    Bread** breads;
    int numbeOfBread;
    
    int currNumMonsters;
    int batch;

    
    Monster *monster;
    vector<Monster*> monsters;
    Monster *testMonster;


    cocos2d::PhysicsWorld *sceneWorld;
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world){sceneWorld = world;}
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event);
    void StopFlying(float dt);
    void update(float dt);
    SneakyJoystick *joyStick;
    void joyStickInitialize();
    ProgressView *progressView;  //血条
    ProgressView *changeMode;  //血条

    bool isRectCollision (CCRect rect1, CCRect rect2);
    void button1CallBack(Object* pSender);
    void button2CallBack(Object* pSender);
    void button3CallBack(Object* pSender);
    
    void shootFireBall(float delta);
    
    void bossShoot(float delta);
    
    void crazyUpdate(float dt);
    void GoToTransScene(float dt);
    
};

#endif // __GAME_SCENE_H__
