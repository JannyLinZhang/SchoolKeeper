//
//  monster.cpp
//  schoolKeeper
//
//  Created by ZhangLin on 3/6/15.
//
//
#include <iostream>
#include "monster.h"
USING_NS_CC;
using namespace std;

Monster::Monster(void)
{
    dead=false;
    injured=false;
    isattack=false;
    isrunning=false;  //do not play running animation
    MonsterDirection = true;  //right
    Monster_blood = NULL;
    speed = 100;
}

Monster::~Monster(void){}

Sprite* Monster::GetSprite(){
    return monstersp;
}

void Monster::InitMonsterSprite(char* name){
    Monster_name = name;
    this->monstersp = Sprite::create(name);
    //monstersp->setFlippedX(MonsterDirection);
    monstersp->setScale(1.0);
    this->addChild(monstersp);
}


void::Monster::InitMonsterSprite(char *name, char *blood_back, char *blood_fore){
    InitMonsterSprite(name);
    Monster_blood = new ProgressView();
    Monster_blood -> setPosition(Point(monstersp->getPositionX()+25, monstersp->getPositionY()+50));
    
    Monster_blood->setBackgroundTexture(blood_back);
    Monster_blood->setForegroundTexture(blood_fore);
    Monster_blood->setTotalProgress(300.0f);
    Monster_blood->setCurrentProgress(300.f);
    this->addChild(Monster_blood);
}

/*Monster itself Animation*/
void Monster:: SetAnimation(const char *name_each, int num, bool run_directon){
    
    monstersp->setFlippedX(run_directon);
    if(isrunning||injured||isattack||dead){
        return;
    }
    
    Animation* animation = Animation::create();
    for(int i=1;i<=num;i++){
        char str[100] = {0};
        sprintf(str,"%s%d.png",name_each,i);
        animation->addSpriteFrameWithFile(str);
    }
    animation->setDelayPerUnit(2.8 / 14.0f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(-1);   //anaimtion loop
    Animate* act = Animate::create(animation);
    monstersp->runAction(act);
    monstersp->setScale(1.0);
    isrunning=true;
}

void Monster::StopAnimation(){
    if(!isrunning)
        return;
    monstersp->stopAllActions();
    this->removeChild(monstersp, true);
    monstersp = Sprite::create(Monster_name);
    if(MonsterDirection == false){
        MonsterDirection = true;
    }
    else{
        MonsterDirection = false;
    }
    monstersp->setScale(1.0);
    this->addChild(monstersp);
    isrunning=false;
}

/*Monster random move animation*/

void Monster:: MonsterSeeRun(){
/*next position*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int minY = monstersp->getContentSize().height / 2;
    int maxY = visibleSize.height - monstersp->getContentSize().height / 2;
    int minX = monstersp->getContentSize().width /2;
    int maxX = visibleSize.width - monstersp->getContentSize().width / 2;
    
    int rangeY = maxY - minY;
    int actualY = (CCRANDOM_0_1() * rangeY) + minY;
    int rangeX = maxX - minX;
    int actualX = (CCRANDOM_0_1() *rangeX) + minX;
    
/*current position*/
    Point currPoint = this->getPosition();
    
/*next move*/
    float dis = currPoint.distance(Point(actualX,actualY));
    float t = dis / speed;
    MoveTo *moveto1;
    moveto1 = MoveTo::create(t, Point(actualX,actualY));
    
    //if((MonsterDirection==false && actualX >= currPoint.x))
    if(actualX >= currPoint.x)
    {
        this->SetAnimation("MonsterAnimation/monster_run", 5, false);
        MonsterDirection = false;
    }
    //else if(MonsterDirection==true && actualX < currPoint.x){
    else
    {
        this->SetAnimation("MonsterAnimation/monster_run", 5, true);
        MonsterDirection = true;
    }

    CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::StopAnimation));
    ActionInterval* rand_walk = Sequence::create(moveto1, callFunc, NULL);
    this->runAction(rand_walk);
}

/*Play injure animation*/
void Monster::InjuredAnimation(const char* name_each, const unsigned int num,bool dir){
    
    if(injured||dead) return;
    
    if(isrunning||isattack){
        this->stopAllActions();  //When being attacked, stop all animation.
        this->removeChild(monstersp,true); //remove current monster
        monstersp = Sprite::create("MonsterAnimation/monster.png");
        monstersp -> setFlippedX(dir);
        this->addChild(monstersp);
        isrunning=false;
        isattack=false;
    }
    Animation* animation = Animation::create();
    for(int i=1;i<=num;i++){
        char str[100] = {0};
        sprintf(str,"%s%d.png",name_each,i);
        animation->addSpriteFrameWithFile(str);
    }
    animation->setDelayPerUnit(2.8 / 14.0f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(1);   //anaimtion loop
    Animate* act = Animate::create(animation);
    
    CallFunc* callFunc=CallFunc::create(this,callfunc_selector(Monster::InjuredEnd));
    ActionInterval* getinjured = Sequence::create(act, callFunc, NULL);
    monstersp->runAction(getinjured);
    injured=true;
}

/*Injured animation end*/
void Monster::InjuredEnd(){
    injured=false;
    Monster_blood->setCurrentProgress(Monster_blood->getCurrentProgress()-250);
    if(Monster_blood->getCurrentProgress()<=0){
        DeadAnimation("MonsterAnimation/monster_fall", 2, MonsterDirection);
    }
}

/*Monster dead animation*/
void Monster::DeadAnimation(const char *name_each,const unsigned int num,bool dir){
    dead=true;
    this->stopAllActions();
    Animation* animation = Animation::create();
    
    for(int i=1;i<=num;i++){
        char str[100] = {0};
        sprintf(str,"%s%d.png",name_each,i);
        animation->addSpriteFrameWithFile(str);
    }
    animation->setDelayPerUnit(2.8 / 14.0f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(1);   //anaimtion loop
    Animate* act = Animate::create(animation);
    
    CallFunc* callFunc=CallFunc::create(this,callfunc_selector(Monster::DeadEnd));
    ActionInterval* getdead = Sequence::create(act, callFunc, NULL);
    monstersp->runAction(getdead);
}

    /*Dead Animation End*/
    void Monster::DeadEnd(){

    this->removeChild(monstersp,true);
    monstersp = Sprite::create("MonsterAnimation/monster_fall2.png");
    monstersp->setFlippedX(MonsterDirection);
    this->addChild(monstersp);
    isrunning=true;
    isattack=false;
    
    /*set monster blood blank*/
    if(Monster_blood!=NULL){
       if(MonsterDirection)
           Monster_blood->setPosition(Point(monstersp->getPositionX()+60, monstersp->getPositionY()));
       else
           Monster_blood->setPosition(Point(monstersp->getPositionX()-60, monstersp->getPositionY()));
    }
    /*monster blink before being removed*/
    Blink* monblink = Blink::create(2,4);
    CallFunc* callFunc = CallFunc::create(this,callfunc_selector(Monster::BlinkEnd));
    ActionInterval* getdead = Sequence::create(monblink, callFunc, NULL);
    monstersp->runAction(getdead);
}

void Monster::BlinkEnd(){
    this->removeAllChildren();
    
}

void Monster::GetInjured(){
    this->InjuredAnimation("MonsterAnimation/monster_fall", 2, false);
}


void Monster::updateMonster(float delta){
    if(dead) return;
    if(!isrunning)
    MonsterSeeRun();
}

void Monster::gamelogic(){
    if(dead) return;
    this->schedule(schedule_selector(Monster::updateMonster), 3.0f);
}

