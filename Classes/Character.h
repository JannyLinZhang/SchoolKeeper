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

#endif /* defined(__schoolKeeper__Character__) */

class Character:public cocos2d::CCNode{

public:
    //Character(cocos2d::Layer *layer);
    //void Fall();
    
    void Move(cocos2d::Vec2 vec,cocos2d::Animation *animation,cocos2d::CCSprite *character);
    void Move1(cocos2d::Vec2 vec);
    void Jump();
    void stop();
    void hit();
    void increaseBomb();
    void decreaseBomb();
    int getNumOfBomb();
    void BombEnd();
    void SetBombAnimation(const char *name_plist,const char *name_png,const char *name_each,const unsigned int num,const char *name_type);
    bool Isbomb;
    bool attactDuration;
    bool beingAttactDuration;
    
    
    
    Character(void);
    ~Character(void);
    //根据图片名创建英雄
    void InitCharacterSprite(char *char_name);
    //设置动画,num为图片数目，run_directon为精灵脸朝向，false朝右,name_each为name_png中每一小张图片的公共名称部分
    void SetRunAnimation(const char *name_plist,const char *name_png,const char *name_each,const unsigned int num,bool run_directon);
    //停止动画
    void StopAnimation(const unsigned int num);
    //判断是否在跑动画
    bool IsRunning;
    //英雄运动的方向
    bool CharDirecton;
    bool IsAttack;
    void SetAnimation(const char *name_plist,const char *name_png,const char *name_each,const unsigned int num,const char *name_type);
    void AttackEnd();
    cocos2d::CCSprite* GetSprite();
    CREATE_FUNC(Character);
    
    
private:
    
    cocos2d::CCSprite* character;//精灵
    char *Char_name;//用来保存初始状态的精灵图片名称
    int numberOfBomb;

};