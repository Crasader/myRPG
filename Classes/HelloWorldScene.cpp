#include "HelloWorldScene.h"
#include "Utils/CommonUtils.h"
#include "MainRole.h"
#include "MainRole.h"
#include "MainRoleController.h"
#include "MonsterController.h"

#define JUMP_STEP_LEN (100)
#define MOVE_STEP_LEN (2.9)
#define MONSTER_STEP_LEN (2.1)

#define JUMP_INTERVAL (0.3)
#define JUMP_MAX_TIME (0.3)
#define MIN_MOVE_TOUCH_LEN (50)
#define MAX_ATK_TOUCH_LEN (10)

#define MAX_SCAN_LEN (150)
//bool isPress = false;

const string bgImage[2] = {"bg1.jpg","bg2.jpg"};
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
	layer->setColor(cocos2d::Color3B::GREEN);
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    isPress = false;
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
				MainRoleController::getInstance()->role->attack();
            }
            else
            {
				MainRoleController::getInstance()->role->jump(pressPoint, releasePoint);

            }
		}

		isPress = false;
    };    
      
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,this);  

    schedule(schedule_selector(HelloWorld::updateLoop));
    
	
	MainRoleController::getInstance()->createMainRole(this);
    MainRoleController::getInstance()->role->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	MonsterController::getInstance()->createMonster(this);
	MonsterController::getInstance()->setTaget(MainRoleController::getInstance()->role);


    
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
                MainRoleController::getInstance()->role->move(pressPoint,movePoint);
				
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