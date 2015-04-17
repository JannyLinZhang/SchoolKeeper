//
//  Boss.cpp
//  schoolKeeper
//
//  Created by Duo Zhao//
//

#include "Boss.h"
#include "Definitions.h"
USING_NS_CC;

Boss::Boss(void)
{
    
    IsRunning=false;
    CharDirecton=false;
    Char_name=NULL;
    IsAttack=false;
    attactDuration = false;
    beingAttactDuration = false;
    }
Boss::~Boss(){

}

Sprite* Boss::GetSprite()
{
    return boss;
}


void Boss::InitBullets(cocos2d::Layer *layer){
    this->bullet1 = Sprite::create("bullet.png");
    this->bullet2 = Sprite::create("bullet.png");
    this->bullet3 = Sprite::create("bullet.png");
    this->bullet1->setRotation(30);
    this->bullet3->setRotation(-30);
    this->bullet1->setPosition(500,200);
    this->bullet2->setPosition(500,250);
    this->bullet3->setPosition(500,300);
    auto b1Body = PhysicsBody::createBox(this->bullet1->getContentSize());
    auto b2Body = PhysicsBody::createBox(this->bullet2->getContentSize());
    auto b3Body = PhysicsBody::createBox(this->bullet3->getContentSize());
    b1Body->setDynamic(false);
    b2Body->setDynamic(false);
    b3Body->setDynamic(false);
    b1Body->setContactTestBitmask(1);
    b2Body->setContactTestBitmask(1);
    b3Body->setContactTestBitmask(1);
    b1Body->setCategoryBitmask(2);
    b2Body->setCategoryBitmask(2);
    b3Body->setCategoryBitmask(2);
    b1Body->setCollisionBitmask(BULLET_COLLISION_BITMASK);
    b2Body->setCollisionBitmask(BULLET_COLLISION_BITMASK);
    b3Body->setCollisionBitmask(BULLET_COLLISION_BITMASK);
    b1Body->setEnable(false);
    b2Body->setEnable(false);
    b3Body->setEnable(false);
    bullet1->setPhysicsBody(b1Body);
    bullet2->setPhysicsBody(b2Body);
    bullet3->setPhysicsBody(b3Body);
    bullet1->setVisible(false);
    bullet2->setVisible(false);
    bullet3->setVisible(false);
    layer->addChild(bullet1);
    layer->addChild(bullet2);
    layer->addChild(bullet3);
}

void Boss::InitCharacterSprite(char* char_name){
    bossAttackCoolDown = true;
    Isbomb=false;
    Char_name=char_name;
    this->boss=Sprite::create(char_name);
    numberOfBomb=0;
    this->addChild(boss);
    
    Boss_health = new ProgressView();
    Boss_health -> setPosition(Point(this->getPositionX(), this->getPositionY()+100));
    Boss_health->setBackgroundTexture("MonsterAnimation/Blood_back.png");
    Boss_health->setForegroundTexture("MonsterAnimation/Blood_fore.png");
    Boss_health->setTotalProgress(600.0f);
    Boss_health->setCurrentProgress(600.f);
    this->addChild(Boss_health);

}

void Boss::StopAnimation(unsigned int num){
    
    if(!IsRunning)
        return;
    
    boss->stopAllActionsByTag(num);//当前精灵停止所有动画
  
    this->removeChild(boss,true);//把原来的精灵删除掉
    boss=CCSprite::create(Char_name);//恢复精灵原来的贴图样子
    boss->setFlipX(CharDirecton);
    this->addChild(boss);
    
    IsRunning=false;

}

void Boss::SetRunAnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num, bool run_directon){
    if(run_directon!=CharDirecton){
        CharDirecton=run_directon;
        boss->setFlippedX(run_directon);
    }
  if(IsRunning)
    return;
    
    CCSpriteFrameCache *m_frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
    m_frameCache->addSpriteFramesWithFile(name_plist,name_png);
    Vector<SpriteFrame*> animFrames(num);
        char str[100]={0};
        for(int i=1; i<=num; i++){
            sprintf(str, "%s%d.png",name_each,i);
            SpriteFrame* frame = m_frameCache->getSpriteFrameByName(str);
            animFrames.insert(i-1, frame);
        }
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(animFrames);

    if(CharDirecton!=run_directon)
    {   CharDirecton=run_directon;
        
    }
    animation->setLoops(-1);//alwasy loop
    animation->setDelayPerUnit(0.1f);
    CCAnimate* act=CCAnimate::create(animation);
     boss->runAction(act);
     act->setTag(10001);
     IsRunning=true;
}




void Boss::SetAnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num,const char *name_type){
    
    if(IsAttack)
        return;
    IsAttack=true;
    attactDuration = true;
    
    CCSpriteFrameCache *m_frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
    m_frameCache->addSpriteFramesWithFile(name_plist,name_png);
    Vector<SpriteFrame*> animFrames(num);
    char str[100]={0};
    for(int i=1; i<=num; i++){
        sprintf(str, "%s%d.png",name_each,i);
        SpriteFrame* frame = m_frameCache->getSpriteFrameByName(str);
        animFrames.insert(i-1, frame);
    }
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(animFrames);
    
    
    
    animation->setLoops(1);//alwasy loop
    animation->setDelayPerUnit(0.1f);
    
    CCAnimate* act=CCAnimate::create(animation);
    CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Boss::AttackEnd));
    CCActionInterval* attackact=CCSequence::create(act,callFunc,NULL);
    
    boss->runAction(attackact);
    act->setTag(10002);
    return;
}



void Boss::Jump(){
    CCActionInterval*  actionUp = CCJumpBy::create(0.5, CCPointMake(0,0), 80, 1);
    boss->runAction(actionUp);
}


void Boss::AttackEnd(){
    this->removeChild(boss,true);//把原来的精灵删除掉
    boss=CCSprite::create(Char_name);//恢复精灵原来的贴图样子
    boss->setFlipX(CharDirecton);
    this->addChild(boss);
    IsAttack=false;
    IsRunning=false;
    Isbomb=false;
    attactDuration =false;
    beingAttactDuration =false;
    bossAttackCoolDown = true;
}

void Boss::increaseBomb(){
    numberOfBomb++;
    
}
void Boss::decreaseBomb(){
    numberOfBomb--;
}

int Boss::getNumOfBomb(){
    return numberOfBomb;
}



void Boss::SetBombAnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num,const char *name_type){
    beingAttactDuration =true;
    
    CCSpriteFrameCache *m_frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
    m_frameCache->addSpriteFramesWithFile(name_plist,name_png);
    Vector<SpriteFrame*> animFrames(num);
    char str[100]={0};
    for(int i=1; i<=num; i++){
        sprintf(str, "%s%d.png",name_each,i);
        SpriteFrame* frame = m_frameCache->getSpriteFrameByName(str);
        animFrames.insert(i-1, frame);
    }
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(animFrames);
    
    
    
    animation->setLoops(1);//alwasy loop
    // animation->se
    animation->setDelayPerUnit(0.1f);
    
    CCAnimate* act=CCAnimate::create(animation);
    CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Boss::BombEnd));
    CCActionInterval* attackact=CCSequence::create(act,callFunc,NULL);
    
    boss->runAction(attackact);
    act->setTag(10003);
    return;
}


void Boss::BombEnd(){
    Boss_health->setCurrentProgress(Boss_health->getCurrentProgress()-100);
    boss->stopActionByTag(10001);
    this->removeChild(boss,true);//把原来的精灵删除掉
    boss=CCSprite::create(Char_name);//恢复精灵原来的贴图样子
    boss->setFlipX(CharDirecton);
    this->addChild(boss);
    Isbomb=false;
    IsRunning=false;
    beingAttactDuration =false;
    attactDuration =false;
}


void Boss::shoot(cocos2d::Layer* layer){
    this->bullet1->setPosition(this->getPosition());
    this->bullet2->setPosition(this->getPosition());
    this->bullet3->setPosition(this->getPosition());
    this->bullet1->setVisible(true);
    this->bullet2->setVisible(true);
    this->bullet3->setVisible(true);
    this->bullet1->getPhysicsBody()->setEnable(true);
    this->bullet2->getPhysicsBody()->setEnable(true);
    this->bullet3->getPhysicsBody()->setEnable(true);
    
    Point direction;
    if(CharDirecton==true){
        direction = Point(-1, 0);
    }else{
        direction = Point(1, 0);
        this->bullet1->setFlippedX(true);
        this->bullet2->setFlippedX(true);
        this->bullet3->setFlippedX(true);
           }
    direction.normalize();
    Point destination1 = this->getPosition()+1200*direction+Point(0,600);
    Point destination2 = this->getPosition()+1200*direction;
    Point destination3 = this->getPosition()+1200*direction-Point(0,600);
    
    MoveTo *moveto1 = MoveTo::create(6, destination1);
    MoveTo *moveto2 = MoveTo::create(6, destination2);
    MoveTo *moveto3 = MoveTo::create(6, destination3);
    Sequence* shoot1=Sequence::create(moveto1, CallFunc::create( std::bind(&Boss::shootEnd,this) ), NULL);
    Sequence* shoot2=Sequence::create(moveto2, CallFunc::create( std::bind(&Boss::shootEnd,this) ), NULL);
    Sequence* shoot3=Sequence::create(moveto3, CallFunc::create( std::bind(&Boss::shootEnd,this) ), NULL);
    if(CharDirecton==true){
        this->bullet1->runAction(shoot1);
        this->bullet2->runAction(shoot2);
        this->bullet3->runAction(shoot3);
    }else{
        this->bullet1->runAction(shoot3);
        this->bullet2->runAction(shoot2);
        this->bullet3->runAction(shoot1);
    }
}

void Boss::shootEnd(){
    this->bullet1->setVisible(false);
    this->bullet2->setVisible(false);
    this->bullet3->setVisible(false);
    this->bullet1->getPhysicsBody()->setEnable(false);
    this->bullet2->getPhysicsBody()->setEnable(false);
    this->bullet3->getPhysicsBody()->setEnable(false);
    this->bullet1->setFlippedX(false);
    this->bullet2->setFlippedX(false);
    this->bullet3->setFlippedX(false);
   }
