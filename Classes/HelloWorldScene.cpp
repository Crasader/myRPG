#include "HelloWorldScene.h"
#include "CommonUtils.h"

#define JUMP_LEN (80)
#define JUMP_INTERVAL (0.5)

bool isPress = false;
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

	/*
	LayerColor *base = LayerColor::create();
	base->setColor(cocos2d::Color3B::GREEN);
	
    base->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(base);
	*/
	this->setColor(cocos2d::Color3B::GREEN);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("f1.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    

	 auto listener1 = EventListenerTouchOneByOne::create();//¥¥Ω®“ª∏ˆ¥•√˛º‡Ã˝    
    listener1->setSwallowTouches(true);//…Ë÷√≤ªœÎœÚœ¬¥´µ›¥•√˛  true «≤ªœÎ ƒ¨»œŒ™false  
    listener1->onTouchBegan = [this](Touch* touch, Event* event){   
        CCLOG("touch menu");  
		pressPoint = touch->getLocationInView();
		isPress = true;
		pressTime = millisecondNow();
		CCLOG("onTouchBegan pressTime = %ld pressPoint x = %f pressPoint y = %f",pressTime ,pressPoint.x,pressPoint.y);
        return true;   
    };
    listener1->onTouchMoved = [](Touch* touch, Event* event){      
    };    
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){    
		releasePoint = touch->getLocationInView();

		long now = millisecondNow();
        
        CCLOG("onTouchEnded now = %ld releasePoint x = %f releasePoint y = %f",now ,releasePoint.x,releasePoint.y);
		long delt_time = now - pressTime;
		if(delt_time < 1000)
		{
            Vec2 deltVec = CommonUtils::getVecByAngleAndLen(pressPoint, releasePoint, JUMP_LEN);
			
			MoveBy *move = MoveBy::create(JUMP_INTERVAL,Vec2(deltVec.x,deltVec.y));
			sprite->runAction(move);
		}

		isPress = false;
    };    
      
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,this);  


    return true;
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