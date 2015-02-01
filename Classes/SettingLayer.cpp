#include "SettingLayer.h"
#include "MainMenuLayer.h"

Scene* SettingLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = SettingLayer::create();
    layer->setColor(cocos2d::Color3B::GREEN);
    scene->addChild(layer);
    
    return scene;
}

bool SettingLayer::init()
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
    
    Sprite * bgSp = Sprite::create("bg2.jpg");
    bgSp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    bgSp->setScale(visibleSize.width / bgSp->getContentSize().width, visibleSize.height / bgSp->getContentSize().height);
    
    m_bgLayer->addChild(bgSp);
    
    ///////
    MenuItemFont::setFontName("fonts/汉仪细行楷简.ttf");
    
    auto item1 = MenuItemFont::create("开始", CC_CALLBACK_1(SettingLayer::onStart, this));
    auto item2= MenuItemFont::create("未确定", CC_CALLBACK_1(SettingLayer::onTest, this));
    auto item3 = MenuItemFont::create("返回", CC_CALLBACK_1(SettingLayer::onSetting, this));
    
    auto menu = Menu::create( item1, item2, item3,  nullptr);
    menu->alignItemsVertically();
    
    menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    menu->setScale(0);
    menu->runAction(ScaleTo::create(1,1));
    
    m_menuLayer->addChild(menu);
    
    return true;
}

void SettingLayer::onStart(Ref* sender)
{
//    Director::getInstance()->replaceScene(GameLayer::createScene());
}

void SettingLayer::onTest(Ref* sender)
{
    
}

void SettingLayer::onSetting(Ref* sender)
{
    Director::getInstance()->replaceScene(MainMenuLayer::createScene());
}
