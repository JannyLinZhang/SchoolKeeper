#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"




USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //this line make physics body visible
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
    auto backgroundSprite = Sprite::create("bbg_fall_grassland.jpg");
    backgroundSprite->setPosition(Point(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
    this->addChild(backgroundSprite);
    joyStickInitialize();
    
    //initialize button
    label = LabelTTF::create("Number of bomb is 0", "Marker Felt", 32);
    label->setPosition(Point(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height - 20));
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(label);
    
    // Standard method to create a button
    
    auto button1 = MenuItemImage::create(
                                        "Buttons/button.png",
                                        "Buttons/button.png", CC_CALLBACK_1(GameScene::button1CallBack, this));
    button1->setPosition(Point(1000, 80));
    auto button_1 = Menu::create(button1, NULL);
    button_1->setPosition(Point::ZERO);
    this->addChild(button_1, 1);
    
    
    auto button2 = MenuItemImage::create(
                                         "Buttons/button.png",
                                         "Buttons/button.png", CC_CALLBACK_1(GameScene::button2CallBack, this));
    button2->setPosition(Point(800, 80));
    auto button_2 = Menu::create(button2, NULL);
    button_2->setPosition(Point::ZERO);
    this->addChild(button_2, 1);
    
    
    auto button3 = MenuItemImage::create(
                                         "Buttons/button.png",
                                         "Buttons/button.png", CC_CALLBACK_1(GameScene::button3CallBack, this));
    button3->setPosition(Point(600, 80));
    auto button_3 = Menu::create(button3, NULL);
    button_3->setPosition(Point::ZERO);
    this->addChild(button_3, 1);
    
    
    face = true;
    
    //character
    character = Character::create();
    character->InitCharacterSprite("character.png");
    character->setPosition(100, 500);
    auto characterBody = PhysicsBody::createBox(character->GetSprite()->getContentSize());
    characterBody->setRotationEnable(false);;
    characterBody->setCollisionBitmask( CHARACTER_COLLISION_BITMASK );
    characterBody->setCategoryBitmask(1);
    characterBody->setContactTestBitmask( 2 );
    character->setPhysicsBody( characterBody );
    this->addChild(character);
    
    
    //Monster
    InitialMonsters();
    
    
    
    
    //bomb
    numberOfItem = 3;
    items = new Item*[numberOfItem];
    for (int i =0 ; i<numberOfItem; i++) {
        items[i] = new Item(this);
    }
    for(int i=0; i<numberOfItem; i++){
        items[i]->setPosition(300+300*i, 150+150*i);
    }
    canPickUp = new int[numberOfItem];
    for(int i=0; i<numberOfItem; i++){
        canPickUp[i] = 0;
    }
    
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
    progressView->setPosition(Point(150, 620));
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
    Point aPosition = a->getPosition();
    Point bPosition = b->getPosition();
    
    if(CHARACTER_COLLISION_BITMASK==a->getCollisionBitmask()&&ITEM_COLLISION_BITMASK==b->getCollisionBitmask())
    {
        
        if(aPosition.y<=bPosition.y){
            this->reorderChild(character, 75);
        }else{
            this->reorderChild(character, 25);
        }
    }
    
    if(CHARACTER_COLLISION_BITMASK==b->getCollisionBitmask()&&ITEM_COLLISION_BITMASK==a->getCollisionBitmask()){
            if(bPosition.y<=aPosition.y){
                this->reorderChild(character, 75);
            
            }else{
                this->reorderChild(character, 25);
            }
        
    }
    
    if(CHARACTER_COLLISION_BITMASK==a->getCollisionBitmask()&&MONSTER_COLLISION_BITMASK==b->getCollisionBitmask())
    {
        
        if(aPosition.y<=bPosition.y){
            this->reorderChild(character, 75);
        }else{
            this->reorderChild(character, 25);
        }
    }
    
    if(CHARACTER_COLLISION_BITMASK==b->getCollisionBitmask()&&MONSTER_COLLISION_BITMASK==a->getCollisionBitmask()){
        if(bPosition.y<=aPosition.y){
            this->reorderChild(character, 75);
            
        }else{
            this->reorderChild(character, 25);
        }
        
    }
    
    return true;
}
    


bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event){
    character->Jump();
    return true;
}


void GameScene::update(float dt){
    
    //control of character
    Point poi = ccpMult(joyStick->getVelocity(), 50);
    if(poi.x >0){
        face =true;
    }
    
    if(poi.x <0){
        face =false;
    }
    
    
    
    if(poi.x==0 && poi.y==0){
        
        character->StopAnimation(10001);
        
    }else{
        float x_1=abs(poi.x);
        float y_1=abs(poi.y);
        float length=pow(x_1*x_1+y_1*y_1,0.5);
        float x=5*(1/length)*x_1;
        float y=5*(1/length)*y_1;
        
        if(poi.x>=0){
            
            character->SetRunAnimation("character/ch_go-ipadhd.plist", "character/ch_go-ipadhd.png","run", 6, false);

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
        
        character->IsAttack=false;
        
        for(int i=0; i<5; i++){
            if(monsters[i]->dead==true)
            continue;
            
        testMonster=monsters[i];
        if(abs(character->getPositionY()-testMonster->getPositionY())<40)
        {
            
            if (this->isRectCollision(CCRectMake(character->getPositionX(), character->getPositionY(), character->GetSprite()->getContentSize().width-150, character->GetSprite()->getContentSize().height), CCRectMake(testMonster->getPositionX(), testMonster->getPositionY(), testMonster->GetSprite()->getContentSize().width,testMonster->GetSprite()->getContentSize().height)))
            {
                //progressView->setCurrentProgress(progressView->getCurrentProgress()-0.4); //更改血量//
                testMonster->InjuredAnimation("MonsterAnimation/monster_fall", 2, true);
            }
        }
        }//end of for loop
        
    }//end of control of character
    
   
    //for explode
    for(int i=0; i<numberOfItem; i++){
    if(abs(character->getPositionX()-items[i]->getX())<100 &&
       ((character->getPositionY()-items[i]->getY())-80)<20 &&
       ((character->getPositionY()-items[i]->getY())-80)>-20){
        if(items[i]->isPicked()==false)
        canPickUp[i]=1;
    }else{
        canPickUp[i]=0;
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
    joystickSkin->setPosition(Point(80,80));
    
    joystickSkin->setJoystick(joyStick);
    
    this->addChild(joystickSkin);
}





bool GameScene::isRectCollision (CCRect rect1, CCRect rect2)
{
    float x1 = rect1.origin.x;
    float y1 = rect1.origin.y;
    float w1 = rect1.size.width;
    float h1 = rect1.size.height;
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

void GameScene::button1CallBack(Object* pSender)
{
    character->SetAnimation("character/ch_hit-ipadhd.plist", "character/ch_hit-ipadhd.png","hit", 9, "hit");
    for(int i=0; i<numberOfItem; i++){
        if (canPickUp[i]==1) {
            canPickUp[i]=0;
            items[i]->explode();
            items[i]->havePickedUp=true;
        }
    }
}


void GameScene::button2CallBack(Object* pSender)
{
   
    for(int i=0; i<numberOfItem; i++){
        if (canPickUp[i]==1) {
            canPickUp[i]=0;
            items[i]->Visible(false);
            items[i]->havePickedUp=true;
            
            
            character->increaseBomb();
            int temp = character->getNumOfBomb();
            string temps = std::to_string(temp);
            temps = "number of Bomb "+temps;
            label->setString(temps);
        }
    }
}

void GameScene::button3CallBack(Object* pSender)
{
    if(character->getNumOfBomb()>0){
        for(int i=0; i<numberOfItem; i++){
            if(items[i]->havePickedUp==true){
                items[i]->havePickedUp=false;
                items[i]->throwBomb(character->getPosition(), face);
                
                character->decreaseBomb();
                int temp = character->getNumOfBomb();
                string temps = std::to_string(temp);
                temps = "number of Bomb "+temps;
                label->setString(temps);
                return;
            }
        }
    }
    
}


void GameScene::InitialMonsters(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    monster = Monster::create();
    monster-> InitMonsterSprite("MonsterAnimation/monster.png","MonsterAnimation/Blood_back.png","MonsterAnimation/Blood_fore.png");
    monster->setPosition(Point(visibleSize.width-150,visibleSize.height/2));
    //this->addChild(monster);
    monsters.push_back(monster);
    
    
    monster = Monster::create();
    monster-> InitMonsterSprite("MonsterAnimation/monster.png","MonsterAnimation/Blood_back.png","MonsterAnimation/Blood_fore.png");
    monster->setPosition(Point(visibleSize.width-100,visibleSize.height/4));
    //this->addChild(monster);
    monsters.push_back(monster);
    
    monster = Monster::create();
    monster-> InitMonsterSprite("MonsterAnimation/monster.png","MonsterAnimation/Blood_back.png","MonsterAnimation/Blood_fore.png");
    monster->setPosition(Point(visibleSize.width-30,visibleSize.height/5));
    //this->addChild(monster);
    monsters.push_back(monster);
    
    monster = Monster::create();
    monster-> InitMonsterSprite("MonsterAnimation/monster.png","MonsterAnimation/Blood_back.png","MonsterAnimation/Blood_fore.png");
    monster->setPosition(Point(visibleSize.width-120,visibleSize.height/2));
    //this->addChild(monster);
    monsters.push_back(monster);
    
    monster = Monster::create();
    monster-> InitMonsterSprite("MonsterAnimation/monster.png","MonsterAnimation/Blood_back.png","MonsterAnimation/Blood_fore.png");
    monster->setPosition(Point(visibleSize.width-120,visibleSize.height/2));
    //this->addChild(monster);
    monsters.push_back(monster);

    
    
    for(int i=0;i<5;i++){
        auto monsterBody = PhysicsBody::createBox(monsters[i]->GetSprite()->getContentSize());
        monsterBody->setRotationEnable(false);
        monsterBody->setDynamic(false);
        monsterBody->setCollisionBitmask( MONSTER_COLLISION_BITMASK );
        monsterBody->setCategoryBitmask(2);
        monsterBody->setContactTestBitmask(1);
        monsters[i]->setPhysicsBody(monsterBody);
        
        this->addChild(monsters[i], 50);
        monsters[i]->gamelogic();
    }
    
}






