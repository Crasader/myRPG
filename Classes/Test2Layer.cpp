#include "Test2Layer.h"
#include "MainMenuLayer.h"
#include "GameConst.h"

Scene* Test2Layer::createScene()
{
    auto scene = Scene::create();
    auto layer = Test2Layer::create();
    layer->setColor(cocos2d::Color3B::GREEN);
    scene->addChild(layer);
    
    return scene;
}

bool Test2Layer::init()
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
    
    Sprite * bgSp = Sprite::create("bg_home.png");
    bgSp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    bgSp->setScale(visibleSize.width / bgSp->getContentSize().width, visibleSize.height / bgSp->getContentSize().height);
    m_bgLayer->addChild(bgSp);
    

    img = new Image();
    img->initWithImageFile("bg_lgame.png");
    
    bgSp1 = Sprite::create("bg_lgame.png");
    bgSp1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    m_bgLayer->addChild(bgSp1);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = [this](Touch* touch, Event* event){
        return true;
    };
    listener1->onTouchMoved = [this](Touch* touch, Event* event){
//        Vec2 movePoint = touch->getLocation();
        Vec2 movePoint = touch->getLocationInView();
        
        testFunc(movePoint);
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        Vec2 releasePoint = touch->getLocationInView();
//        testFunc(releasePoint);
        
    };    
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,this);
    
    
    return true;
}

void Test2Layer::testFunc(Vec2 p)
{
    Sprite * sp = bgSp1;

    unsigned char * data = img->getData();
    Texture2D::PixelFormat piexFormat =  img->getRenderFormat();
    bool hasA = img->hasAlpha();
    if(piexFormat == Texture2D::PixelFormat::RGBA8888 && hasA)
    {
        for (int i=0; i < img->getWidth(); i++)
        {
            for (int j=0; j < img->getHeight(); j++)
            {
                if ((j-p.y )* (j-p.y ) + (i-p.x) * (i-p.x) < 1600) {
                
                    int imageOffset = j * img->getWidth() + i;
                    unsigned char *  piexData = data;
                    
                    int totalRGB = piexData[imageOffset * 4 + 0] + piexData[imageOffset * 4 + 1] + piexData[imageOffset * 4 + 2];
                    int gary = totalRGB / 3;
                    piexData[imageOffset * 4 + 0] = gary;
                    piexData[imageOffset * 4 + 1] = gary;
                    piexData[imageOffset * 4 + 2] = gary;
//                    piexData[imageOffset * 4 + 3] = 0;
                }
            }
        }
        
        texture = new (std::nothrow) Texture2D();
        texture->initWithImage(img);
        sp->setTexture(texture);
    }
    
    
}

void Test2Layer::onStart(Ref* sender)
{
}

void Test2Layer::onTest(Ref* sender)
{
}

void Test2Layer::onSetting(Ref* sender)
{
    Director::getInstance()->popScene();
}
