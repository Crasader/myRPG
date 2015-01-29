#include "HelloWorldScene.h"
#include "CommonUtils.h"
#include "MainRole.h"

#define JUMP_STEP_LEN (100)
#define MOVE_STEP_LEN (2)
#define JUMP_INTERVAL (0.3)
#define JUMP_MAX_TIME (0.3)
#define MIN_MOVE_TOUCH_LEN (50)
#define MAX_ATK_TOUCH_LEN (10)

#define MAX_SCAN_LEN (150)
bool isPress = false;

const string bgImage[2] = {"bg1.jpg","bg2.jpg"};
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	layer->setColor(cocos2d::Color3B::GREEN);
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Layer * bg = Layer::create();
    int bgImgIdx = CommonUtils::RandAmongMinMax(0, 1);
    Sprite * bgSp = Sprite::create(bgImage[bgImgIdx]);
    bgSp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    bgSp->setScale(visibleSize.width / bgSp->getContentSize().width, visibleSize.height / bgSp->getContentSize().height);
    
//    bg->setColor(Color3B::BLUE);
    
    bg->addChild(bgSp);
    
    this->addChild(bg);

	this->setColor(cocos2d::Color3B::GREEN);

    // add "HelloWorld" splash screen"
    MainRole::getInstance()->sp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(MainRole::getInstance()->sp, 0);
    
    isShortTime = false;
    jumpInterval = 0;
	 auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = [this](Touch* touch, Event* event){   
        CCLOG("touch menu");  
		pressPoint = touch->getLocation();
		isPress = true;
        jumpInterval = 0;
        isShortTime = false;
//		CCLOG("onTouchBegan pressTime = %ld pressPoint x = %f pressPoint y = %f",pressTime ,pressPoint.x,pressPoint.y);
        return true;
    };
    listener1->onTouchMoved = [this](Touch* touch, Event* event){
        movePoint = touch->getLocation();
        
    };    
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){    
		releasePoint = touch->getLocation();

        
//        CCLOG("onTouchEnded releasePoint x = %f releasePoint y = %f" ,releasePoint.x,releasePoint.y);

		if(isShortTime == true)
		{
            float delt_x = releasePoint.x - pressPoint.x;
            float delt_y = releasePoint.y - pressPoint.y;
            if( (delt_x * delt_x + delt_y * delt_y) < MAX_ATK_TOUCH_LEN * MAX_ATK_TOUCH_LEN)
            {
                Blink * blink = Blink::create(1.0f, 5);
                MainRole::getInstance()->sp->runAction(blink);
            }
            else
            {
                Vec2 deltVec = CommonUtils::getVecByAngleAndLen(pressPoint, releasePoint, JUMP_STEP_LEN);
                
                MoveBy *move = MoveBy::create(JUMP_INTERVAL,Vec2(deltVec.x,deltVec.y));
                MainRole::getInstance()->sp->runAction(move);
            }
		}

		isPress = false;
    };    
      
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,this);  

    schedule(schedule_selector(HelloWorld::updateLoop));
    
    //创建怪物
    for (int i=0; i< 8; i++) {
        Monster * monster = new Monster();
        monsters.push_back(monster);
        monster->sp->setPosition(CommonUtils::RandAmongMinMax(0 + 40 ,visibleSize.width - 40 )
                                 ,CommonUtils::RandAmongMinMax(0 + 40,visibleSize.height - 40));
        this->addChild(monster->sp);
    }
    
    //
    auto s = Director::getInstance()->getWinSize();
    
    auto draw = DrawNode::create();
    addChild(draw, 10);
    
    // 画10个圆，实际上是画了10个点，指定点的大小，所以看起来就是圆；
    for( int i=0; i < 10; i++)
    {
        draw->drawDot(Vec2(s.width/2, s.height/2), 10*(10-i), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }
    
    // 画多边形
    Vec2 points[] = { Vec2(s.height/4,0), Vec2(s.width,s.height/5), Vec2(s.width/3*2,s.height) };
    draw->drawPolygon(points, sizeof(points)/sizeof(points[0]), Color4F(1,0,0,0.5), 4, Color4F(0,0,1,1));
    
    
    return true;
}

void HelloWorld::updateLoop(float delta)
{
    if(isPress)
    {
        jumpInterval += delta;
        
        if(jumpInterval < JUMP_INTERVAL)
        {
            isShortTime = true;
        }
        else
        {
            isShortTime = false ;
        }
        
        if(isShortTime == false)
        {
            float delt_x = movePoint.x - pressPoint.x;
            float delt_y = movePoint.y - pressPoint.y;
            if( (delt_x * delt_x + delt_y * delt_y) > MIN_MOVE_TOUCH_LEN * MIN_MOVE_TOUCH_LEN)
            {
                
                Vec2 deltVec = CommonUtils::getVecByAngleAndLen(pressPoint, movePoint, MOVE_STEP_LEN);
                
                float spX = MainRole::getInstance()->sp->getPositionX();
                float spY = MainRole::getInstance()->sp->getPositionY();
                MainRole::getInstance()->sp->setPosition(spX + deltVec.x, spY + deltVec.y);
            }
            
        }
    }
    
    //怪物AI
    if(true)
    {
        unsigned long count = monsters.size();
        int i=0;
        vector<Monster *>::iterator it = monsters.begin();
        for (it = monsters.begin(), i=0; it != monsters.end(), i<count; ++it , i++) {
            Sprite * monsterSp = monsters[i]->sp;
            Sprite * roleSp = MainRole::getInstance()->sp;
            
            float delt_x = monsterSp->getPositionX() - roleSp->getPositionX();
            float delt_y = monsterSp->getPositionY() - roleSp->getPositionY();
            if( (monsters[i]->isActive == false) && (delt_x * delt_x + delt_y * delt_y) < MAX_SCAN_LEN * MAX_SCAN_LEN)
            {
                monsters[i]->isActive = true;
                
            }
            
            bool skLenReady = (delt_x * delt_x + delt_y * delt_y) < monsters[i]->skLen;
            
            if (monsters[i]->isActive == true) {
                
                if(skLenReady == false)
                {
                    Vec2 deltVec = CommonUtils::getVecByAngleAndLen(monsterSp->getPosition(), roleSp->getPosition(), MOVE_STEP_LEN);
                    
                    //                CCLOG("HelloWorld::updateLoop monsterSp x = %f monsterSp y = %f" ,monsterSp->getPositionX(),monsterSp->getPositionY());
                    //                CCLOG("HelloWorld::updateLoop roleSp x = %f roleSp y = %f" ,roleSp->getPositionX(),roleSp->getPositionY());
                    
                    float spX = monsterSp->getPositionX();
                    float spY = monsterSp->getPositionY();
                    monsterSp->setPosition(spX + deltVec.x, spY + deltVec.y);
                    //                CCLOG("HelloWorld::updateLoop spX + deltVec.x x = %f spY + deltVec.y y = %f" ,spX + deltVec.x,spY + deltVec.y);
                    
                }
                else
                {
                    
                }
                
            }

            
            Size visibleSize = Director::getInstance()->getVisibleSize();
            if(monsterSp->getPositionX() < -40 || monsterSp->getPositionX() > visibleSize.width + 40
               || monsterSp->getPositionY() < -40 || monsterSp->getPositionY() > visibleSize.height + 40)
            {
                monsters.erase(it);
            }
        }
    }
    
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

long HelloWorld::millisecondNow()  
{ 
struct timeval tv; 
  gettimeofday(&tv,NULL);   
return ((long)(tv.tv_sec * 1000) + (long)(tv.tv_usec / 1000)); 
} 