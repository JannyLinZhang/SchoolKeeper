#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"




USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vect(0,0));
    
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool GameScene::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    this->addChild(backgroundSprite);
    joyStickInitialize();
    
    character = new Character(this);
    
    
    
    for (int i =0 ; i<2; i++) {
        Role* role = new Role(this);
        roles.push_back(role);
        
    }
    this->schedule(schedule_selector(GameScene::RoleLogic), 1.0f);


    
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT,3);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);
    
    
    
    auto edgeNode =Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    this->scheduleUpdate();
    return true;
}



bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact){
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    if(
       (BIRD_COLLISION_BITMASK==a->getCollisionBitmask()&&OBSTACLE_COLLISION_BITMASK==b->getCollisionBitmask())||
       (BIRD_COLLISION_BITMASK==b->getCollisionBitmask()&&OBSTACLE_COLLISION_BITMASK==a->getCollisionBitmask())
      )
    {
        auto scene = GameOverScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }

    return true;
}

bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event){
    
    character->Jump();
    return true;
}


void GameScene::update(float dt){
  
    Point poi = joyStick->getVelocity()*30;
     character->Move1(Vec2(poi.x, poi.y));
    if(poi.x!=0 && poi.y!=0){
    //stop the character if joystick is at rest position
    }
    
    //printf("%f, %f\n", poi.x, poi.y);
                    }

void GameScene::joyStickInitialize(){
    float joystickRadius = 220;
    joyStick=new SneakyJoystick();
    joyStick->autorelease();
    joyStick->initWithRect(CCRectZero);
    joyStick->setAutoCenter(true);
    joyStick->setHasDeadzone(true);
    joyStick->setDeadRadius(10);
    SneakyJoystickSkinnedBase *joystickSkin=new SneakyJoystickSkinnedBase();
    joystickSkin->autorelease();
    joystickSkin->init();
    joystickSkin->setBackgroundSprite(CCSprite::create("Virtual Joystick/VJ2.png"));
    joystickSkin->setThumbSprite(CCSprite::create("Virtual Joystick/VJ1.png"));
    joystickSkin->getThumbSprite()->setScale(1.0f);
    joystickSkin->setPosition(Point(joystickRadius,joystickRadius));
    joystickSkin->setJoystick(joyStick);
    this->addChild(joystickSkin);
}


void GameScene::RoleLogic(float dt){
    for(int i=0; i<2; i++){
        roles[i]->move();
    }
    
}





/*
 
 //code for animation Bear
 SpriteBatchNode* spriteSheet = SpriteBatchNode::create("BearAnimation/bearAnimationSheet.png");
 SpriteFrameCache* cache = SpriteFrameCache::getInstance();
 cache->addSpriteFramesWithFile("BearAnimation/bearAnimation.plist");
 this->addChild(spriteSheet);
 Vector<SpriteFrame*> animFrames(8);
 char str[100]={0};
 for(int i=1; i<=8; i++){
 sprintf(str, "bear%d.png",i);
 SpriteFrame* frame = cache->getSpriteFrameByName(str);
 animFrames.insert(i-1, frame);
 }
 Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
 Sprite* bear1 = Sprite::createWithSpriteFrameName("bear1.png");
 bear1->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
 bear1->runAction(RepeatForever::create(Animate::create(animation)));
 bear1->setScale(0.3);
 spriteSheet->addChild(bear1);
 */







