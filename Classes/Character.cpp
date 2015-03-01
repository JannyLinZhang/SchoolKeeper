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
    CharDirecton=false;
    Char_name=NULL;
    }
Character::~Character(){

}

void Character::InitCharacterSprite(char* char_name){
    
    Char_name=char_name;
    this->character=CCSprite::create(char_name);
    this->addChild(character);
    
}

void Character::StopAnimation(){
    if(!IsRunning)
        return;
    
    character->stopAllActionsByTag(10001);//当前精灵停止所有动画
  
    this->removeChild(character,true);//把原来的精灵删除掉
    character=CCSprite::create(Char_name);//恢复精灵原来的贴图样子
    character->setFlipX(CharDirecton);
    this->addChild(character);
    
    IsRunning=false;

}

void Character::SetAnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num, bool run_directon){
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
    printf("=======");
    animation->setDelayPerUnit(0.1f);
    
    CCAnimate* act=CCAnimate::create(animation);
     character->runAction(act);
      printf("&&&&&&&&&&&");
    act->setTag(10001);
   // character->setPosition(ccp(200,200));
   // character->runAction(act);
    IsRunning=true;
    

    
    
}



    
    

//
void Character::Move(cocos2d::Vec2 vec,cocos2d::Animation* animation,cocos2d::CCSprite *character){

     CCMoveTo* move1 = CCMoveTo::create(12,vec);
     character->runAction(RepeatForever::create(Animate::create(animation)));
 //   character->runAction(Repeat::c)
    character->runAction(move1);

}


void Character::Move1(cocos2d::Vec2 vec){
    
    
    
    
    
//    move1 = CCMoveBy::create(12,vec);
//    
//   
//    move1->setTag(100001);
//    
//    character->runAction(move1);
//   
}
void Character::stop(){
    
    character->stopAllActionsByTag(100001);
    
    
}

void Character::Jump(){
    

  CCActionInterval*  actionUp = CCJumpBy::create(0.5, CCPointMake(0,0), 80, 1);

    character->runAction(actionUp);
    
}
