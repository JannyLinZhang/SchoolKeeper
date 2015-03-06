//
//  Role.h
//  schoolKeeper
//
//  Created by ZhangLin on 2/13/15.
//
//

#ifndef __schoolKeeper__Role__
#define __schoolKeeper__Role__

#include <stdio.h>

#include "cocos2d.h"

using namespace cocos2d;
//using namespace std;

class Role : public Sprite
{
public:
    Role(cocos2d::Layer *layer);
    cocos2d::Sprite* GetSprite();
    //Role();
   // static Role* create(const std::string& name, FlightLayer* layer);
    //virtual bool init(const std:: string& name, FlightLayer* layer);
    
  //  void setControlable(bool b);
  //  virtual Rect getBoundingBox();
    
protected:
   // virtual void update(float dt);
  //  virtual void update_pos();

    
public:
/*Operation about Ontouch, temporary using those three function, please modify them by Bo Yang*/
    
    //virtual bool onTouchBegan(Touch* touch, Event *event);
    //virtual void onTouchMoved(Touch* touch, Event *event);
    //virtual void onTouchEnded(Touch* touch, Event *event);
    
protected:
/*related show in the screen*/
    
    // bool m_controlable;
    // Armature* m_arm;
    // int m_arm_offsetX;
    // int m_arm_offsetY;
    // bool m_armFaceTo;
    
public:
    /*external call API*/
    //virtual inline void setDesPoint(const Point& p){m_desPoint = p;}
    void genNextPos();
    //ID
    //virtual inline int getId(){return m_id;}
    virtual void move();
  //  virtual void moveNext();
    
protected:
    /*related data about monster*/
    int m_id;
    Point m_desPoint; // Target position
    
    int m_speed;      //move speed
    int m_initSpeed;
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Sprite * comrole;
};

#endif /* defined(__schoolKeeper__Role__) */
