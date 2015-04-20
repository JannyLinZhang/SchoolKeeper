//
//  Character.h
//  schoolKeeper
//
//  Created by YangBo's macbook on 15/2/12.
//
//

#ifndef __schoolKeeper__Character__
#define __schoolKeeper__Character__

#include <iostream>

using namespace cocos2d;
class Character:public cocos2d::CCNode{
    
public:
    //Character(cocos2d::Layer *layer);
    //void Fall();
    
    bool Isbomb;
    bool attactDuration;
    bool beingAttactDuration;
    bool crazyMode;
    bool isJump;
    bool IsRunning;
    //英雄运动的方向
    bool CharDirecton;
    bool IsAttack;
    
    
    Character(void);
    ~Character(void);
    void Move(cocos2d::Vec2 vec,cocos2d::Animation *animation,cocos2d::CCSprite *character);
    void Move1(cocos2d::Vec2 vec);
    void Jump();
    void stop();
    void hit();
    void increaseBomb();
    void decreaseBomb();
    int getNumOfBomb();
    void BombEnd();
    void SetBombAnimation(const char *name_plist,const char *name_png,const char *name_each,const unsigned int num,const char *name_type,bool direction);
    
    
    
    //根据图片名创建英雄
    void InitCharacterSprite(char *char_name);
    //设置动画,num为图片数目，run_directon为精灵脸朝向，false朝右,name_each为name_png中每一小张图片的公共名称部分
    void SetRunAnimation(const char *name_plist,const char *name_png,const char *name_each,const unsigned int num,bool run_directon);
    //停止动画
    void StopAnimation(char* pics,const unsigned int num);
    //判断是否在跑动画
    void StopCrazyAnimation(char* pics,const unsigned int num);
    void SetAnimation(const char *name_plist,const char *name_png,const char *name_each,const unsigned int num,const char *name_type);
    void AttackEnd();
    void crazyStart(char* pics);
    void crazyEnd(char* pics);
    cocos2d::CCSprite* GetSprite();
    cocos2d::CCSprite* GetStormSprite();
    CREATE_FUNC(Character);
    void sendStorm();
    void stormEnd();
    cocos2d::CCSprite* character;//精灵
    Sprite* storm;//技能风暴
    
private:
    
    
    
    char *Char_name;//用来保存初始状态的精灵图片名称
    int numberOfBomb;
    
};

#endif /* defined(__schoolKeeper__Character__) */