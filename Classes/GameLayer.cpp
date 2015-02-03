#include "GameLayer.h"
#include "Utils/CommonUtils.h"
#include "MainRole.h"
#include "MainRole.h"
#include "MainRoleController.h"
#include "MonsterController.h"
#include "PauseLayer.h"
#include "GameConst.h"

#define JUMP_TOUCH_MOVE_INTERVAL (0.3)
#define MIN_MOVE_TOUCH_LEN (50)
#define MAX_ATK_TOUCH_LEN (10)

const string bgImage[2] = {"bg1.jpg","bg2.jpg"};
bool GameLayer::isPause = false;
Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
	layer->setColor(cocos2d::Color3B::GREEN);
    scene->addChild(layer);

    return scene;
}

bool GameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    isPress = false;
    touchMoveShow = NULL;
    isPause = false;
    
    isShortTime = false;
    jumpInterval = 0;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_bgLayer = Layer::create();
	m_skillLayer = Layer::create();
	m_roleLayer = Layer::create();
	m_uiLayer = Layer::create();
	m_touchLayer = Layer::create();

	this->addChild(m_bgLayer,1);
	this->addChild(m_skillLayer,2);
	this->addChild(m_roleLayer,3);
	this->addChild(m_touchLayer,4);
	this->addChild(m_uiLayer,1000);

    int bgImgIdx = CommonUtils::RandAmongMinMax(0, 2);
    Sprite * bgSp = Sprite::create(bgImage[bgImgIdx]);
    bgSp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    bgSp->setScale(visibleSize.width / bgSp->getContentSize().width, visibleSize.height / bgSp->getContentSize().height);
    
    m_bgLayer->addChild(bgSp);

	this->setColor(cocos2d::Color3B::GREEN);

    
    //touch move show
    {
        touchMoveShow = Sprite::create("slider_track.png");
        touchMoveShow->setVisible(false);
        touchMoveShow->setOpacity(100);
        touchMoveShow->setAnchorPoint(Vec2(0,0.5));
        m_touchLayer->addChild(touchMoveShow);
        
    }
    //hp label
    {
        
        TTFConfig config2(FONT_NAME,60);//初始化TTFConfig，第一个参数为字库的路径，第二个参数为字体大小
        roleHP = Label::createWithTTF(config2,"生命:100",TextHAlignment::LEFT);//创建label，并向左对其
        roleHP->setPosition(Vec2(40,visibleSize.height - 40));
        roleHP->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);//设置锚点居中
        m_uiLayer->addChild(roleHP);
        roleHP->enableShadow(Color4B::RED,Size(2,-2),0);
    }
    //pause btn
    {
        Button *pauseBtn = Button::create("btn_pause.png","btn_pause_p.png");
        pauseBtn->setPosition(Vec2(visibleSize.width - 40,visibleSize.height - 40));
        pauseBtn->addClickEventListener(GameLayer::onPause);
        m_uiLayer->addChild(pauseBtn);
        
    }
    //////////////
    
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
        touchMoveShow->setVisible(false);

		isPress = false;
    };    
      
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,m_touchLayer);  

    schedule(schedule_selector(GameLayer::updateLoop));
    
	
	MainRoleController::getInstance()->createMainRole(this);
    MainRoleController::getInstance()->role->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	MonsterController::getInstance()->createMonster(this);
	MonsterController::getInstance()->setTaget(MainRoleController::getInstance()->role);


    
    return true;
}

void GameLayer::onPause(Ref *pSender)
{
//    if(isPause == false)
    {
        
        Director::getInstance()->pushScene(PauseLayer::createScene());
//        MonsterController::getInstance()->pause();
//        MainRoleController::getInstance()->pause();
//        isPause = true;
    }
//    else
    {
        //Director::getInstance()->popScene();
//        MonsterController::getInstance()->resume();
//        MainRoleController::getInstance()->resume();
//        isPause = false;
    }
}

void GameLayer::updateLoop(float delta)
{
    if(isPress)
    {
        jumpInterval += delta;
        
        if(jumpInterval < JUMP_TOUCH_MOVE_INTERVAL)
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
				
                touchMoveShow->setVisible(true);
                touchMoveShow->setScale(sqrtf(delt_x * delt_x + delt_y * delt_y) / touchMoveShow->getContentSize().width , 1);
                touchMoveShow->setPosition(pressPoint);
                
                float angle = CommonUtils::getAngleBy2Point(pressPoint,movePoint);
                angle = -angle;
                //解析几何里面，旋转是逆时针，而 setRotation 逆时针旋转，需要是负整数
                touchMoveShow->setRotation(angle);
                
            }
        }
    }
    
    __String * hpValue = __String::createWithFormat("生命:%d",MainRoleController::getInstance()->role->hp);
    roleHP->setString(hpValue->getCString());
}

void GameLayer::menuCloseCallback(Ref* pSender)
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
