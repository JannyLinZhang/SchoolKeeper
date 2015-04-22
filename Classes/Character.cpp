//
//  Character.cpp
//  schoolKeeper
//
//  Created by YangBo's macbook on 15/2/12.
//
//

#include "Character.h"
#include "Definitions.h"
USING_NS_CC;

Character::Character(void)
{
    
    
    IsRunning=false;
    CharDirecton=true;
    Char_name=NULL;
    IsAttack=false;
    attactDuration = false;
    beingAttactDuration = false;
    crazyMode=false;
}
Character::~Character(){
    
}

CCSprite* Character::GetSprite()
{
    return character;
}

CCSprite* Character::GetStormSprite()
{
    return storm;
}

void Character::InitCharacterSprite(char* char_name){
    Isbomb=false;
    Char_name=char_name;
    this->character=CCSprite::create(char_name);
    
    
    
    storm = Sprite::create("fireball.png");
    storm->setVisible(false);
    storm->setScale(1.0f);
    auto stormBody = PhysicsBody::createBox( storm->getContentSize());
    // stormBody->setDynamic(false);
    stormBody->setCollisionBitmask( STORM_COLLISION_BITMASK );
    stormBody->setCategoryBitmask(8);
    stormBody->setContactTestBitmask(1);
    //    //stormBody->
    storm->setPhysicsBody(stormBody);
    //stormBody->
    
    
    numberOfBomb=0;
    
    this->addChild(storm);
    this->addChild(character);
}

void Character::StopAnimation(char* pics,const unsigned int num){
    
    if(!IsRunning)
        return;
    
    character->stopAllActionsByTag(num);//当前精灵停止所有动画
    // character->setScale(2.0f);;
    this->removeChild(character,true);//把原来的精灵删除掉
    character=CCSprite::create(pics);//恢复精灵原来的贴图样子
    character->setFlipX(CharDirecton);
    this->addChild(character);
    
    IsRunning=false;
    
}
void Character::StopCrazyAnimation(char* pics,const unsigned int num){
    
    if(!IsRunning)
        return;
    
    character->stopAllActionsByTag(num);//当前精灵停止所有动画
    
    this->removeChild(character,true);//把原来的精灵删除掉
    character=CCSprite::create(pics);//恢复精灵原来的贴图样子
    character->setFlipX(CharDirecton);
    this->addChild(character);;
    
    IsRunning=false;
    
}

void Character::SetRunAnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num, bool run_directon){
    if(run_directon!=CharDirecton){
        CharDirecton=run_directon;
        character->setFlippedX(run_directon);
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
    character->runAction(act);
    act->setTag(10001);
    IsRunning=true;
}




void Character::SetAnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num,const char *name_type){
    
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
    CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Character::AttackEnd));
    CCActionInterval* attackact=CCSequence::create(act,callFunc,NULL);
    
    character->runAction(attackact);
    act->setTag(10002);
    return;
}




void Character::Jump(){
    CCActionInterval*  actionUp = CCJumpBy::create(0.5, CCPointMake(0,0), 80, 1);
    character->runAction(actionUp);
}


void Character::AttackEnd(){
    this->removeChild(character,true);//把原来的精灵删除掉
    character=CCSprite::create(Char_name);//恢复精灵原来的贴图样子
    character->setFlipX(CharDirecton);
    this->addChild(character);
    IsAttack=false;
    IsRunning=false;
    Isbomb=false;
    attactDuration =false;
    beingAttactDuration =false;
}

void Character::crazyStart(char* pics){
    this->removeChild(character,true);//把原来的精灵删除掉
    character=CCSprite::create(pics);//恢复精灵原来的贴图样子
    character->setFlipX(CharDirecton);
    this->addChild(character);
    IsAttack=false;
    // IsRunning=false;
    Isbomb=false;
    attactDuration =false;
    beingAttactDuration =false;
}


void Character::crazyEnd(char* pics){
    
    //character->stopAllActionsByTag(num);//当前精灵停止所有动画
    
    this->removeChild(character,true);//把原来的精灵删除掉
    character=CCSprite::create(pics);//恢复精灵原来的贴图样子
    character->setFlipX(CharDirecton);
    this->addChild(character);
    
    IsRunning=false;
    crazyMode=false;
    
}

void Character::increaseBomb(){
    numberOfBomb++;
    
}
void Character::decreaseBomb(){
    numberOfBomb--;
}

int Character::getNumOfBomb(){
    return numberOfBomb;
}



void Character::SetBombAnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num,const char *name_type,bool direction){
    beingAttactDuration =true;
    character->setFlipX(direction);
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
    CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Character::BombEnd));
    CCActionInterval* attackact=CCSequence::create(act,callFunc,NULL);
    
    character->runAction(attackact);
    act->setTag(10003);
    return;
}


void Character::BombEnd(){
    character->stopActionByTag(10001);
    this->removeChild(character,true);//把原来的精灵删除掉
    character=CCSprite::create(Char_name);//恢复精灵原来的贴图样子
    character->setFlipX(CharDirecton);
    this->addChild(character);
    Isbomb=false;
    IsRunning=false;
    beingAttactDuration =false;
    attactDuration =false;
}



void Character::sendStorm(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num,const char *name_type){

    IsAttack=true;
    attactDuration = true;
    storm->setVisible(true);
    if(CharDirecton==false){
        storm->setPositionX(character->getPosition().x+100);
    }else{
        storm->setPositionX(character->getPosition().x-100);
    }
    storm->setPositionY(character->getPosition().y);
    //   storm->setPosition(character->getPosition());
    //    printf("XXX%f",storm->getPositionX());
    //    printf("YYYY%f",storm->getPositionY());
    
    storm->getPhysicsBody()->setEnable(true);
    
    
    
    int x=0;
    int y=storm->getPosition().y;
    MoveTo *moveto ;
    
    if(CharDirecton==false){
        // x =storm->getPosition().x+800;
        moveto = MoveTo::create(1, ccp(storm->getPosition().x+800,storm->getPosition().y));
        //         MoveTo *moveto = MoveTo::create(6, ccp());
    }else{
        moveto = MoveTo::create(1, ccp(storm->getPosition().x-800,storm->getPosition().y));
    }
    
    
    //MoveBy *moveto = MoveBy::create(6, ccp(800,0));
    Sequence* shoot=Sequence::create(moveto, CallFunc::create( std::bind(&Character::stormEnd,this) ), NULL);
    
    // CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Character::stormEnd));
    //CCActionInterval* attackact=CCSequence::create(moveto,callFunc,NULL);
    
    storm->runAction(shoot);
    
    
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
    CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Character::stormEnd));
    CCActionInterval* attackact=CCSequence::create(act,callFunc,NULL);
    
    character->runAction(attackact);
    act->setTag(10002);
    
    return;
    
    
}

void Character::stormEnd(){
    
    storm->getPhysicsBody()->setEnable(false);
    storm->cocos2d::Node::setPosition(character->getPosition());
    storm->setVisible(false);
    IsAttack=false;
    IsRunning=false;
    Isbomb=false;
    attactDuration =false;
    beingAttactDuration =false;
    
}
