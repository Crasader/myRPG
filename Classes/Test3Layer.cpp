#include "Test3Layer.h"
#include "MainMenuLayer.h"
#include "GameConst.h"
#include "ImageExpand.h"

Scene* Test3Layer::createScene()
{
    auto scene = Scene::create();
    auto layer = Test3Layer::create();
    layer->setColor(cocos2d::Color3B::GREEN);
    scene->addChild(layer);
    
    return scene;
}

bool Test3Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    m_bgLayer = Layer::create();
    m_menuLayer = Layer::create();
    
    
    this->addChild(m_bgLayer,1);
    this->addChild(m_menuLayer,2);
    
    ////
    
    Sprite * bgSp_ = Sprite::create("bg_home.png");
    bgSp_->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    bgSp_->setScale(visibleSize.width / bgSp_->getContentSize().width, visibleSize.height / bgSp_->getContentSize().height);
    m_bgLayer->addChild(bgSp_);
    ///
    
    
    Sprite *bgSp1 = Sprite::create("bg_lgame.png");
    bgSp1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    Sprite * f1 = Sprite::create("m1.png");
    f1->setPosition(Vec2(visibleSize.width/2 + origin.x - 200, visibleSize.height/2 + origin.y - 300));
    
    bgSp1->addChild(f1);
    
    m_bgLayer->addChild(bgSp1);

    flag = false;
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = [this](Touch* touch, Event* event){
        return true;
    };
    listener1->onTouchMoved = [this](Touch* touch, Event* event){
        //        Vec2 movePoint = touch->getLocation();
        Vec2 movePoint = touch->getLocationInView();
        
        //        testFunc(movePoint);
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        Vec2 releasePoint = touch->getLocationInView();
        
            ImageExpand * action = ImageExpand::create(2.0,40);
            bgSp1->runAction(action);
            
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,this);
    

    return true;
}
void Test3Layer::onStart(Ref* sender)
{
}

void Test3Layer::onTest(Ref* sender)
{
}

void Test3Layer::onSetting(Ref* sender)
{
    Director::getInstance()->popScene();
}
