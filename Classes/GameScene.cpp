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
                                        "Buttons/attack.png",
                                        "empty.png", CC_CALLBACK_1(GameScene::button1CallBack, this));
    button1->setPosition(Point(1050, 80));
    auto button_1 = Menu::create(button1, NULL);
    button_1->setPosition(Point::ZERO);
    button_1->setOpacity(150);
    this->addChild(button_1, 1);
    
    
    auto button2 = MenuItemImage::create(
                                         "Buttons/loot.png",
                                         "empty.png", CC_CALLBACK_1(GameScene::button2CallBack, this));
    button2->setPosition(Point(940, 80));
    auto button_2 = Menu::create(button2, NULL);
    button_2->setPosition(Point::ZERO);
    button_2->setOpacity(150);
    this->addChild(button_2, 1);
    
    
    auto button3 = MenuItemImage::create(
                                         "Buttons/bombButton.png",
                                         "empty.png", CC_CALLBACK_1(GameScene::button3CallBack, this));
    button3->setPosition(Point(1000, 550));
    auto button_3 = Menu::create(button3, NULL);
    button_3->setPosition(Point::ZERO);
    button_3->setOpacity(150);
    this->addChild(button_3, 1);
    
    
    face = true;
    
    //character
    character = Character::create();
    character->InitCharacterSprite("character.png");
    character->setPosition(100, 500);
    auto characterBody = PhysicsBody::createBox(character->GetSprite()->getContentSize()/1.1);
    characterBody->setRotationEnable(false);
    characterBody->setCollisionBitmask( CHARACTER_COLLISION_BITMASK );
    characterBody->setCategoryBitmask(1);
    characterBody->setContactTestBitmask(2);
    characterBody->setPositionOffset(Point(0,-5));
    character->setPhysicsBody( characterBody );
    this->addChild(character);
    
    
    //Boss
    boss = Boss::create();
    boss->InitBullets(this);
    boss->InitCharacterSprite("character.png");
    boss->setPosition(500, 500);
    this->addChild(boss);
    
    
    
    
    //Monster
    numbeOfMonster = 5;
    InitialMonsters(numbeOfMonster);
    
    //Bread
    numbeOfBread = 2;
    breads = new Bread*[numbeOfBread];
    for(int i=0 ;i<numbeOfBread; i++){
        breads[i] = new Bread(this);
        breads[i]->bread->getPhysicsBody()->setTag(i);
    }
    breads[0]->setPosition(600, 500);
    
    
    
    //bomb
    numberOfItem = 5;
    items = new Item*[numberOfItem];
    for (int i =0 ; i<numberOfItem; i++) {
        items[i] = new Item(this);
    }
    for(int i=0; i<numberOfItem; i++){
        double randomx = CCRANDOM_0_1();
        double randomy = CCRANDOM_0_1();
        
        double xr = 200*randomx+1000*(1-randomx);
        double yr = 150*randomy+400*(1-randomy);
        items[i]->setPosition(xr, yr);
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
    
    if(CHARACTER_COLLISION_BITMASK==a->getCollisionBitmask()&&FIREBALL_COLLISION_BITMASK==b->getCollisionBitmask())
    {
        progressView->setCurrentProgress(progressView->getCurrentProgress()-20);
        b->setEnable(false);
        if(character->beingAttactDuration==false){
        character->GetSprite()->stopAllActions();
        character->stopAllActions();
        character->Isbomb=true;
        character->SetBombAnimation("character/lie/lie-ipadhd.plist", "character/lie/lie-ipadhd.png","lie", 11, "lie");}
    }
    
    if(CHARACTER_COLLISION_BITMASK==b->getCollisionBitmask()&&FIREBALL_COLLISION_BITMASK==a->getCollisionBitmask())
    {
        progressView->setCurrentProgress(progressView->getCurrentProgress()-20);
        a->setEnable(false);
        if(character->beingAttactDuration==false){
        character->GetSprite()->stopAllActions();
        character->stopAllActions();
        character->Isbomb=true;
        character->SetBombAnimation("character/lie/lie-ipadhd.plist", "character/lie/lie-ipadhd.png","lie", 11, "lie");}
    }
    
    if(CHARACTER_COLLISION_BITMASK==a->getCollisionBitmask()&& BREAD_COLLISION_BITMASK==b->getCollisionBitmask())
    {
        progressView->setCurrentProgress(progressView->getCurrentProgress()+20);
        b->setEnable(false);
        int i = b->getTag();
        breads[i]->disappear();
    }
    
    if(CHARACTER_COLLISION_BITMASK==b->getCollisionBitmask()&& BREAD_COLLISION_BITMASK==a->getCollisionBitmask())
    {
        progressView->setCurrentProgress(progressView->getCurrentProgress()+20);
        a->setEnable(false);
        int i = a->getTag();
        breads[i]->disappear();
    }
    
    if(CHARACTER_COLLISION_BITMASK==a->getCollisionBitmask()&& BULLET_COLLISION_BITMASK==b->getCollisionBitmask()){
        progressView->setCurrentProgress(progressView->getCurrentProgress()-10);
        b->setEnable(false);
        if(character->beingAttactDuration==false){
            character->GetSprite()->stopAllActions();
            character->stopAllActions();
            character->Isbomb=true;
            character->SetBombAnimation("character/lie/lie-ipadhd.plist", "character/lie/lie-ipadhd.png","lie", 11, "lie");}
        
    }
    if(CHARACTER_COLLISION_BITMASK==b->getCollisionBitmask()&& BULLET_COLLISION_BITMASK==a->getCollisionBitmask()){
        progressView->setCurrentProgress(progressView->getCurrentProgress()-10);
        a->setEnable(false);
        if(character->beingAttactDuration==false){
            character->GetSprite()->stopAllActions();
            character->stopAllActions();
            character->Isbomb=true;
            character->SetBombAnimation("character/lie/lie-ipadhd.plist", "character/lie/lie-ipadhd.png","lie", 11, "lie");}
    }


    
    
    
    return true;
}
    


bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event){
    if(character->beingAttactDuration==false && character->attactDuration==false)
    character->Jump();
    return true;
}


void GameScene::update(float dt){
    Point poi = ccpMult(joyStick->getVelocity(), 50);
    
    if(character->getPosition().y<10)
        character->setPositionY(10);
    if(character->getPosition().y>500)
        character->setPositionY(500);
    if(character->getPosition().x<5)
        character->setPositionX(5);
    if(character->getPosition().x>1130)
        character->setPositionX(1130);
    
    //boss follow character
    Point distanceVector = character->getPosition()-boss->getPosition();
    float distance = distanceVector.getLength();
    distanceVector.normalize();
    if(distance>200){
        //boss will approach character
        if(distanceVector.x>=0){
            boss->SetRunAnimation("character/ch_go-ipadhd.plist", "character/ch_go-ipadhd.png","run", 6, false);
            boss->setPosition(boss->getPosition().x+distanceVector.x,boss->getPosition().y+distanceVector.y);
        }else{
            boss->SetRunAnimation("character/ch_go-ipadhd.plist", "character/ch_go-ipadhd.png","run", 6, true);
            boss->setPosition(boss->getPosition().x+distanceVector.x,boss->getPosition().y+distanceVector.y);
        }
    }else{
        boss->StopAnimation(10001);
    }
    
    
    
    //control of character
    if(poi.x >0){
        face =true;
    }
    
    if(poi.x <0){
        face =false;
    }
    
    if(character->attactDuration==false && character->beingAttactDuration==false){

    if(poi.x==0 && poi.y==0){
        
        character->StopAnimation(10001);
        
    }else{
        if(character->attactDuration==false && character->beingAttactDuration==false){
        float x_1=abs(poi.x);
        float y_1=abs(poi.y);
        float length=pow(x_1*x_1+y_1*y_1,0.5);
        float x=5*(1/length)*x_1*0.6;
        float y=5*(1/length)*y_1*0.6;
        
        if(poi.x>=0){
            character->SetRunAnimation("character/ch_go-ipadhd.plist", "character/ch_go-ipadhd.png","run", 6, false);
            if(poi.y>=0){
                character->setPosition(character->getPosition().x+x,character->getPosition().y+y);
            }else{
                character->setPosition(character->getPosition().x+x,character->getPosition().y-y);
            }
            
        }else{
            character->SetRunAnimation("character/ch_go-ipadhd.plist", "character/ch_go-ipadhd.png","run", 6, true);
            if(poi.y>=0){
                character->setPosition(character->getPosition().x-x,character->getPosition().y+y);
            }else{
                character->setPosition(character->getPosition().x-x,character->getPosition().y-y);
            }
        }
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
            
            if (this->isRectCollision(
                                      CCRectMake(character->getPositionX(),
                                                 character->getPositionY(),
                                                 character->GetSprite()->getContentSize().width,
                                                 character->GetSprite()->getContentSize().height),
                                      CCRectMake(testMonster->getPositionX(),
                                                 testMonster->getPositionY(),
                                                 testMonster->GetSprite()->getContentSize().width,
                                                 testMonster->GetSprite()->getContentSize().height)))
            {
                testMonster->InjuredAnimation("MonsterAnimation/monster_fall", 2, true);
            }
        }
        }//end of for loop
        
    }//end of control of character
    
   
    //for explode
    for(int i=0; i<numberOfItem; i++){
        if(     abs(character->getPositionX()-items[i]->getX())<100  &&
                ((character->getPositionY()-items[i]->getY())-80)<20 &&
                ((character->getPositionY()-items[i]->getY())-80)>-20){
            if(items[i]->havePickedUp == 0)
                canPickUp[i]=1;
        }else{
                canPickUp[i]=0;
        }
    }
    
    for(int i=0; i<numberOfItem; i++){
        if(items[i]->explodeIndicator == 1){
            items[i]->explodeIndicator = 0;
            Point bombPosition = Point(items[i]->getX(), items[i]->getY());
            for(int j=0; j<numbeOfMonster; j++){
                if(monsters[j]->dead==true)
                    continue;
                Point monsterPosition = monsters[j]->getPosition();
                double length =(bombPosition-monsterPosition).length();
                if(length<150){
                    monsters[j]->InjuredAnimation("MonsterAnimation/monster_fall", 2, true);
                }
            }
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
    joystickSkin->getThumbSprite()->setScale(1.2f);
    joystickSkin->getBackgroundSprite()->setScale(1.2f);
    joystickSkin->setPosition(Point(100,100));
    
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
        return false;
    else if (y1-h1*0.5>y2+h2*0.5)
        return false;
    
    return true;
}


void GameScene::button1CallBack(Object* pSender)
{
    for(int i=0; i<numberOfItem; i++){
        if (canPickUp[i]==1) {
            canPickUp[i]=0;
            items[i]->explode();
            items[i]->havePickedUp=1;
            character->Isbomb=true;
            character->SetBombAnimation("character/lie/lie-ipadhd.plist", "character/lie/lie-ipadhd.png","lie", 11, "lie");
            progressView->setCurrentProgress(progressView->getCurrentProgress()-20);
        }
    }
    
    if(character->Isbomb==false && character->beingAttactDuration == false){
        character->SetAnimation("character/ch_hit-ipadhd.plist", "character/ch_hit-ipadhd.png","hit", 9, "hit");
    }
}






void GameScene::button2CallBack(Object* pSender)
{
   
    for(int i=0; i<numberOfItem; i++){
        if (canPickUp[i]==1) {
            canPickUp[i]=0;
            items[i]->Visible(false);
            items[i]->havePickedUp=1;
            
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
            if(items[i]->havePickedUp==1 && items[i]->haveExplode==0){
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
    character->attactDuration=false;
    character->beingAttactDuration=false;
    
}

void GameScene::InitialMonsters(int num){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    for(int i=0; i<num; i++){
        monster = Monster::create();
        monster-> InitMonsterSprite("MonsterAnimation/monster.png","MonsterAnimation/Blood_back.png","MonsterAnimation/Blood_fore.png");
        int minY = monster->monstersp->getContentSize().height / 2;
        int maxY = (visibleSize.height - monster->monstersp->getContentSize().height / 2)-170;
        int rangeY = maxY-minY;
        monster->setPosition(Point(visibleSize.width*CCRANDOM_0_1(),rangeY/(i+1)));
        monsters.push_back(monster);
        
    }
    
    for(int i=0;i<num;i++){
        auto monsterBody = PhysicsBody::createBox(monsters[i]->GetSprite()->getContentSize());
        monsterBody->setRotationEnable(false);
        monsterBody->setDynamic(false);
        monsterBody->setCollisionBitmask( MONSTER_COLLISION_BITMASK );
        monsterBody->setCategoryBitmask(2);
        monsterBody->setContactTestBitmask(1);
        monsters[i]->setPhysicsBody(monsterBody);
        this->addChild(monsters[i], 50);
        monsters[i]->gamelogic();
        this->addChild(monsters[i]->fireball);
        }
    
    schedule(schedule_selector(GameScene::shootFireBall), 7.0f, 100, 1.0f);
    schedule(schedule_selector(GameScene::bossShoot), 7.0f, 100, 1.0f);
    
    
}

void GameScene::shootFireBall(float delta){
    int j=0;
    for(int i=0; i<numbeOfMonster; i++){
        monsters[i]->fireball->getPhysicsBody()->setEnable(true);
        if(CCRANDOM_0_1()>0.7&& monsters[i]->dead == false){
        monsters[i]->shoot(this);
            j++;
        }
        if(j==2){
            return;
        }
    }
    
}

void GameScene::bossShoot(float delta){
    boss->shoot(this);
}





