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
    playMusic = true;
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
    
    //////////
    
    TTFConfig config2("fonts/汉仪细行楷简.ttf",60);//初始化TTFConfig，第一个参数为字库的路径，第二个参数为字体大小
    auto failString = Label::createWithTTF(config2,"设置",TextHAlignment::LEFT);//创建label，并向左对其
    failString->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2 +  200));
    failString->setAnchorPoint(Vec2::ANCHOR_MIDDLE);//设置锚点居中
    m_bgLayer->addChild(failString);
    failString->enableShadow(Color4B::RED,Size(2,-2),0);
    //////////
    
    
    ///////
    MenuItemFont::setFontName("fonts/汉仪细行楷简.ttf");
    MenuItemFont::setFontSize(80);
    auto item1 = MenuItemFont::create("音乐：开", CC_CALLBACK_1(SettingLayer::onStart, this));
    auto item2= MenuItemFont::create("未确定", CC_CALLBACK_1(SettingLayer::onTest, this));
    auto item3 = MenuItemFont::create("返回", CC_CALLBACK_1(SettingLayer::onSetting, this));
    
    auto menu = Menu::create( item1, item2, item3,  nullptr);
    menu->alignItemsVertically();
    
    menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    
    m_menuLayer->addChild(menu);
    
    return true;
}

void SettingLayer::onStart(Ref* sender)
{
    MenuItemFont * item1 = (MenuItemFont *)sender ;
    
    if(playMusic == true)
    {
        playMusic = false;
        item1->setString("音乐：关");
    }
    else
    {
        playMusic = true;
        item1->setString("音乐：开");
    }
    
}

void SettingLayer::onTest(Ref* sender)
{
    
}

void SettingLayer::onSetting(Ref* sender)
{
    Director::getInstance()->popScene();
}
