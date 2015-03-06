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
    
    //background
    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    this->addChild(backgroundSprite);
    joyStickInitialize();
    
    //character
    character = Character::create();
    character->InitCharacterSprite("character.png");
    character->setPosition(100, 500);
    auto characterBody = PhysicsBody::createBox(character->GetSprite()->getContentSize()/6);
    characterBody->setDynamic( false );
    characterBody->setCollisionBitmask( CHARACTER_COLLISION_BITMASK );
    characterBody->setContactTestBitmask( true );
    //character->setPhysicsBody( characterBody );

    this->addChild(character);
    
    
    //Enemy
    for (int i =0 ; i<2; i++) {
        Role* role = new Role(this);
        roles.push_back(role);
    }
    
    monster=roles[0];
        
    this->schedule(schedule_selector(GameScene::RoleLogic), 1.0f);
    
    //bomb
    numberOfItem = 3;
    items = new Item*[3];
    for (int i =0 ; i<numberOfItem; i++) {
        items[i] = new Item(this);
    }
    Point pp;
    for(int i=0; i<numberOfItem; i++){
        pp.set(300+300*i, 300);
        items[i]->setPosition(pp);
    }
    
    /*
    auto testBody = PhysicsBody::createBox(item->getContentSize());
    testBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    testBody->setContactTestBitmask(true);
    
    auto testSprite = Sprite::create("bomb.png");
    testSprite->setScale(2.0);
    testSprite->setPhysicsBody(testBody);
    testSprite->setPosition(600, 400);
    this->addChild(testSprite);
    */

    
    
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
    
    
    
    
    //set progress view by Bo Yang
    
    progressView = new ProgressView();
    progressView->setPosition(ccp(150, 500));
    progressView->setScale(2.2f);
    progressView->setBackgroundTexture("xue_back.png");
    progressView->setForegroundTexture("xue_fore.png");
    progressView->setTotalProgress(100.0f);
    progressView->setCurrentProgress(100.0f);
    //下面两个是为了让血条更好好看
    CCSprite *xuekuang=CCSprite::create("kuang.png");//添加血条的框架
    xuekuang->setPosition(ccp(progressView->getPositionX(),progressView->getPositionY()));
    CCSprite *touxiang=CCSprite::create("touxiang.png");//添加英雄的左上角的小头像
    touxiang->setPosition(ccp(progressView->getPositionX()-120,progressView->getPositionY()));
    this->addChild(touxiang,2);
    this->addChild(xuekuang,2);
    this->addChild(progressView, 2);
    
    
    
    this->scheduleUpdate();
    return true;
}



bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact){
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    if(
       (CHARACTER_COLLISION_BITMASK==a->getCollisionBitmask()&&ITEM_COLLISION_BITMASK==b->getCollisionBitmask())||
       (CHARACTER_COLLISION_BITMASK==b->getCollisionBitmask()&&ITEM_COLLISION_BITMASK==a->getCollisionBitmask())
      )
    {
       
    }
 
    return true;
}

bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event){
    
    //character->Jump();
    character->SetAnimation("character/ch_hit-ipadhd.plist", "character/ch_hit-ipadhd.png","hit", 9, "hit");

    return true;
}


void GameScene::update(float dt){
    
    //control of character
    Point poi = ccpMult(joyStick->getVelocity(), 50);
    //right
    if(poi.x==0 && poi.y==0){
        
        character->StopAnimation(10001);
        
    }else{
        
        printf("%f,%f/n",poi.x,poi.y);
        float x_1=abs(poi.x);
        float y_1=abs(poi.y);
        float length=pow(x_1*x_1+y_1*y_1,0.5);
        float x=5*(1/length)*x_1;
        float y=5*(1/length)*y_1;
        
        if(poi.x>=0){
            
            character->SetRunAnimation("character/ch_go-ipadhd.plist", "character/ch_go-ipadhd.png","run", 6, false);
            printf("?????");
            if(poi.y>=0){
                
                character->setPosition(character->getPosition().x+x,character->getPosition().y+y );
                
            }else{
                character->setPosition(character->getPosition().x+x,character->getPosition().y-y );
                
            }
            
        }else{
            character->SetRunAnimation("character/ch_go-ipadhd.plist", "character/ch_go-ipadhd.png","run", 6, true);
            if(poi.y>=0){
                character->setPosition(character->getPosition().x-x,character->getPosition().y+y );
            }else{
                character->setPosition(character->getPosition().x-x,character->getPosition().y-y );
            }
        }
        
    }
    
    
    if(character->IsAttack){
        //
        //        printf("zezezz4");
        //        cout<<character->getContentSize().width <<"," << character->getContentSize().height<<endl;
        //        printf("%f",character->getContentSize().width);
        cout<< character->GetSprite()->getContentSize().width<<"," <<  character->GetSprite()->getContentSize().height<<endl;
        cout<< monster->GetSprite()->getContentSize().width <<"," <<  monster->GetSprite()->getContentSize().height<<endl;
    
        cout<< character->getPositionX()<<"," <<  character->getPositionY()<<endl;
        cout<< monster->GetSprite()->getPositionX() <<"," <<  monster->GetSprite()->getPositionY()<<endl;
        if(abs(character->getPositionY()-monster->GetSprite()->getPositionY())<40)//
        {
            
            //                    cout<< character->GetSprite()->getContentSize().width <<"," <<  character->GetSprite()->getContentSize().height<<endl;
            
            if (this->isRectCollision(CCRectMake(character->getPositionX(), character->getPositionY(), character->GetSprite()->getContentSize().width-150, character->GetSprite()->getContentSize().height), CCRectMake(monster->GetSprite()->getPositionX(), monster->GetSprite()->getPositionY(), monster->GetSprite()->getContentSize().width-500,monster->GetSprite()->getContentSize().height-400)))
            {
                
                
                //monster1->HurtAnimation("monster_hurt",2,monster1->MonsterDirecton);// ‹…À
                progressView->setCurrentProgress(progressView->getCurrentProgress()-0.4); //更改血量
            }
        }
    }//end of control of character
    
   
    
    for(int i=0; i<numberOfItem; i++){
    if(abs(character->getPositionX()-items[i]->getX())<100 &&
       ((character->getPositionY()-items[i]->getY())-50)<20 &&
       ((character->getPositionY()-items[i]->getY())-50)>-20){
        items[i]->explode();
    }
    }
    
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
    joystickSkin->getBackgroundSprite()->setOpacity(100);
    joystickSkin->getThumbSprite()->setOpacity(20);
    joystickSkin->getThumbSprite()->setScale(0.8f);
    joystickSkin->getBackgroundSprite()->setScale(0.8f);
    joystickSkin->setPosition(Point(joystickRadius-100,joystickRadius-100));
    
    joystickSkin->setJoystick(joyStick);
    
    this->addChild(joystickSkin);
}


void GameScene::RoleLogic(float dt){
    for(int i=0; i<2; i++){
        //roles[i]->move();
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
//write by Bo Yang


bool GameScene::isRectCollision (CCRect rect1, CCRect rect2)
{
    float x1 = rect1.origin.x;//æÿ–Œ1÷––ƒµ„µƒ∫·◊¯±Í
    float y1 = rect1.origin.y;//æÿ–Œ1÷––ƒµ„µƒ◊›◊¯±Í
    float w1 = rect1.size.width;//æÿ–Œ1µƒøÌ∂»
    float h1 = rect1.size.height;//æÿ–Œ1µƒ∏ﬂ∂»
    float x2 = rect2.origin.x;
    float y2 = rect2.origin.y;
    float w2 = rect2.size.width;
    float h2 = rect2.size.height;
    
    if (x1+w1*0.5<x2-w2*0.5)
        return false;
    else if (x1-w1*0.5>x2+w2*0.5)
        return false;
    else if (y1+h1*0.5<y2-h2*0.5)
        return false;//
    else if (y1-h1*0.5>y2+h2*0.5)
        return false;//
    
    return true;
}








