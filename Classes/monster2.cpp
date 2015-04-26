//
//  monster.cpp
//  schoolKeeper
//
//  Created by ZhangLin on 3/6/15.
//
//
#include <iostream>
#include "monster2.h"
#include "Definitions.h"
USING_NS_CC;
using namespace std;


Monster2::Monster2(void)
{
    dead=false;
    injured=false;
    isattack=false;
    isrunning=false;  //do not play running animation
    MonsterDirection = true;  //right
    Monster_blood = NULL;
    speed = 100;
    isAdded = false;
    isShooting=false;
}

Monster2::~Monster2(void){}

Sprite* Monster2::GetSprite(){
    return monstersp;
}

void Monster2::InitMonsterSprite(char* name){
    Monster_name = name;
    this->monstersp = Sprite::create(name);
    //monstersp->setFlippedX(MonsterDirection);
    monstersp->setScale(1.0);
    
    //initialize it's fireball
    fireball = Sprite::create("arrow.png");
    fireball->setVisible(false);
    fireball->setScale(0.3);
    auto fireBody = PhysicsBody::createBox( fireball->getContentSize()/5);
    //fireBody->setDynamic(false);
    fireBody->setCollisionBitmask(FIREBALL_COLLISION_BITMASK);
    fireBody->setCategoryBitmask(8);
    fireBody->setContactTestBitmask(1);
    fireball->setPhysicsBody(fireBody);
    this->addChild(monstersp);
}


void::Monster2::InitMonsterSprite(char *name, char *blood_back, char *blood_fore){
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
void Monster2:: SetAnimation(const char *name_each, int num, bool run_directon){
    
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
    animation->setDelayPerUnit(2.8 / 50.0f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(-1);   //anaimtion loop
    Animate* act = Animate::create(animation);
    monstersp->runAction(act);
    monstersp->setScale(1.0);
    isrunning=true;
}

void Monster2::StopAnimation(){
    if(!isrunning)
        return;
    monstersp->stopAllActions();
    this->removeChild(monstersp, true);
    monstersp = Sprite::create(Monster_name);
    /*
    if(MonsterDirection == false){
        MonsterDirection = true;
    }
    else{
        MonsterDirection = false;
    }*/
    if(MonsterDirection == true){
        
        monstersp->setFlippedX(true);
        
    }
    monstersp->setScale(1.0);
    this->addChild(monstersp);
    isrunning=false;
}

/*Monster random move animation*/

void Monster2:: MonsterSeeRun(){
/*next position*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int minY = monstersp->getContentSize().height / 2;
    int maxY = (visibleSize.height - monstersp->getContentSize().height / 2)-170;
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
        this->SetAnimation("MonsterAnimation2/monster2_run", 8, false);
        MonsterDirection = false;
    }
    //else if(MonsterDirection==true && actualX < currPoint.x){
    else
    {
        this->SetAnimation("MonsterAnimation2/monster2_run", 8, true);
        MonsterDirection = true;
    }

    CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster2::StopAnimation));
    ActionInterval* rand_walk = Sequence::create(moveto1, callFunc, NULL);
    this->runAction(rand_walk);
}

/*Play injure animation*/
void Monster2::InjuredAnimation(const char* name_each, const unsigned int num,bool dir){
    
    if(injured||dead) return;
    
    injured=true;
    if(isrunning||isattack){
        this->stopAllActions();  //When being attacked, stop all animation.
        this->removeChild(monstersp,true); //remove current monster
        monstersp = Sprite::create("MonsterAnimation2/monster2.png");
        monstersp -> setFlippedX(dir);
        this->addChild(monstersp);
        isrunning=false;
        isattack=false;
    }
    
    this->unschedule(schedule_selector(Monster2::updateMonster));
 
    Animation* animation = Animation::create();
    for(int i=1;i<=num;i++){
        char str[100] = {0};
        sprintf(str,"%s%d.png",name_each,i);
        animation->addSpriteFrameWithFile(str);
    }
    animation->setDelayPerUnit(2.8 / 50.0f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(1);   //anaimtion loop
    Animate* act = Animate::create(animation);
    
    CallFunc* callFunc=CallFunc::create(this,callfunc_selector(Monster2::InjuredEnd));
    ActionInterval* getinjured = Sequence::create(act, callFunc, NULL);
    monstersp->runAction(getinjured);
}

/*Injured animation end
void Monster::InjuredEnd(){
    injured=false;
    Monster_blood->setCurrentProgress(Monster_blood->getCurrentProgress()-250);
    if(Monster_blood->getCurrentProgress()<=0){
        DeadAnimation("MonsterAnimation/monster_fall", 2, MonsterDirection);
    }
}
*/
void Monster2::InjuredEnd(){

    Monster_blood->setCurrentProgress(Monster_blood->getCurrentProgress()-250);
    if(Monster_blood->getCurrentProgress()<=0){
        
        DeadAnimation("MonsterAnimation2/monster2_dead", 2, MonsterDirection);
    }
    else{
        injured = false;
        this->schedule(schedule_selector(Monster2::updateMonster), 0.2f);
        this->stopAllActions();
    }
}

/*Monster dead animation*/
void Monster2::DeadAnimation(const char *name_each,const unsigned int num,bool dir){
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
    
    CallFunc* callFunc=CallFunc::create(this,callfunc_selector(Monster2::DeadEnd));
    ActionInterval* getdead = Sequence::create(act, callFunc, NULL);
    monstersp->runAction(getdead);
}

    /*Dead Animation End*/
    void Monster2::DeadEnd(){

    this->removeChild(monstersp,true);
    monstersp = Sprite::create("MonsterAnimation2/monster2_dead2.png");
    monstersp->setFlippedX(!MonsterDirection);
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
    CallFunc* callFunc = CallFunc::create(this,callfunc_selector(Monster2::BlinkEnd));
    ActionInterval* getdead = Sequence::create(monblink, callFunc, NULL);
    monstersp->runAction(getdead);
}

void Monster2::BlinkEnd(){
    this->removeAllChildren();
    
}

void Monster2::GetInjured(){
    this->InjuredAnimation("MonsterAnimation2/monster_dead", 2, false);
}


void Monster2::updateMonster(float delta){
    if(dead) return;
    if(!isrunning)
    MonsterSeeRun();
}

void Monster2::gamelogic(){
    if(dead) return;
    this->schedule(schedule_selector(Monster2::updateMonster), 0.2f);
}
/*
void Monster2::shoot(cocos2d::Layer* layer){
    fireball->setPosition(this->getPosition());
    fireball->setVisible(true);
    
    Point direction;
    if(this->MonsterDirection==true){
        direction = Point(-1, 0);
    }else{
        direction = Point(1, 0);
    }
    direction.normalize();
    Point destination = this->getPosition()+1200*direction;
    MoveTo *moveto = MoveTo::create(6, destination);
    Sequence* shoot=Sequence::create(moveto, CallFunc::create( std::bind(&Monster2::shootEnd,this) ), NULL);
    fireball->runAction(shoot);    
}

void Monster2::shootEnd(){
    fireball->setVisible(false);
}*/

void Monster2::shoot(const char* name_each, const unsigned int num,bool dir)
{
    isShooting=true;
    this->stopAllActions();  //When being attacked, stop all animation.
    this->removeChild(monstersp,true); //remove current monster
    this->unschedule(schedule_selector(Monster2::updateMonster));
    monstersp = Sprite::create("MonsterAnimation2/monster2.png");
    monstersp -> setFlippedX(!(this->MonsterDirection));
    this->addChild(monstersp);
    
    Animation* animation = Animation::create();
    for(int i=1;i<=num;i++){
        char str[100] = {0};
        sprintf(str,"%s%d.png",name_each,i);
        animation->addSpriteFrameWithFile(str);
    }
    animation->setDelayPerUnit(2.8 / 40.0f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(1);   //anaimtion loop
    Animate* act = Animate::create(animation);
    
    CallFunc* callFunc=CallFunc::create(this,callfunc_selector(Monster2::shootInprocess));
    ActionInterval* startshoot = Sequence::create(act, callFunc, NULL);
    monstersp->runAction(startshoot);
 
}

void Monster2::shootInprocess()
{
    isShooting=false;
    isrunning = false;
    this->schedule(schedule_selector(Monster2::updateMonster), 0.2f);

    fireball->getPhysicsBody()->setEnable(true);
    fireball->setPosition(this->getPosition());
    fireball->setVisible(true);
    
    Point direction;
    if(this->MonsterDirection==true){
        direction = Point(1, 0);
    }else{
        direction = Point(-1, 0);
        fireball->setFlippedX(true);
    }
    direction.normalize();
    Point destination = this->getPosition()+1200*direction;
    MoveTo *moveto = MoveTo::create(6, destination);
    Sequence* shoot=Sequence::create(moveto, CallFunc::create( std::bind(&Monster2::shootEnd,this) ), NULL);
    
    fireball->runAction(shoot);
}

void Monster2::shootEnd(){
    fireball->setVisible(false);
}

void Monster2::shootAnimationEnd(){
}


