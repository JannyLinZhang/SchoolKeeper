//
//  Boss.h
//  schoolKeeper
//
//  Created by Duo Zhao//
//


#include <iostream>
#include "progressview.h"



class Boss:public cocos2d::Node{

public:
    
    void Move(cocos2d::Vec2 vec,cocos2d::Animation *animation,cocos2d::Sprite *character);
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
    
    void InitBullets(cocos2d::Layer *layer);
    void shoot(cocos2d::Layer* layer);
    void shootEnd();


    
    
    
    Boss();
    ~Boss(void);
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
    cocos2d::Sprite* GetSprite();
    CREATE_FUNC(Boss);
    
    
private:
    
    cocos2d::Sprite* boss;//精灵
    cocos2d::Sprite* bullet1; //子弹
    cocos2d::Sprite* bullet2;
    cocos2d::Sprite* bullet3;
    char *Char_name;//用来保存初始状态的精灵图片名称
    int numberOfBomb;
    ProgressView* Boss_health;


};