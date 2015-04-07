//
//  monster.h
//  schoolKeeper
//
//  Created by ZhangLin on 3/6/15.
//
//

#ifndef __schoolKeeper__monster__
#define __schoolKeeper__monster__

#include <stdio.h>
#include "cocos2d.h"
#include "progressview.h"
using namespace cocos2d;
//using namespace std;

class Monster : public cocos2d::Node{
public:
    Monster(void);
    ~Monster(void);
    
    /*initialize the monster without blood*/
    void InitMonsterSprite(char* name);
    void InitMonsterSprite(char *name, char *blood_back, char *blood_fore);
    
    /*set animation*/
    void SetAnimation(const char *name_each,int num, bool run_directon);
    void StopAnimation();
    
    /*return monster */
    Sprite* GetSprite();
    
    /*sprite random move*/
    void MonsterSeeRun();
    
    /*injured and dead*/
    void GetInjured();
    void InjuredAnimation(const char* name_each, const unsigned int num,bool dir);
    void InjuredEnd();
    
    void DeadAnimation(const char *name_each,const unsigned int num,bool dir);
    void BlinkEnd();
    void DeadEnd();
    
    //void update(float delta);
    void updateMonster(float delta);
    void gamelogic();
    void shoot(cocos2d::Layer *layer);
    void shootEnd();
    CREATE_FUNC(Monster);
    
    
public:
    bool isrunning;
    bool isattack;
    bool injured;
    bool dead;
    bool MonsterDirection;
    Sprite* monstersp;
    Sprite* fireball;
    bool isAdded=false;

    
   
private:    
    char *Monster_name;
    int speed;
    ProgressView* Monster_blood;
};


#endif /* defined(__schoolKeeper__monster__) */
