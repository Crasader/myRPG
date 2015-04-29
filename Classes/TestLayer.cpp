#include "TestLayer.h"
#include "MainMenuLayer.h"
#include "GameConst.h"

Scene* TestLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = TestLayer::create();
    layer->setColor(cocos2d::Color3B::GREEN);
    scene->addChild(layer);
    
    return scene;
}

bool TestLayer::init()
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
    
    pEraser = DrawNode::create();
    pEraser->drawSolidCircle(Vec2(0, 0), 40, CC_DEGREES_TO_RADIANS(360), 50
                        , Color4F(0, 0, 0, 0));
    pEraser->retain();
    
    pRTex = CCRenderTexture::create(visibleSize.width, visibleSize.height);
    pRTex->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(pRTex, 10);
    
    Sprite * bgSp1 = Sprite::create("bg_lgame.png");
    bgSp1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    pRTex->begin();
    bgSp1->visit();
    pRTex->end();
//    m_bgLayer->addChild(bgSp1);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    listener1->onTouchBegan = [this](Touch* touch, Event* event){
        return true;
    };
    listener1->onTouchMoved = [this](Touch* touch, Event* event){
        Vec2 movePoint = touch->getLocation();
//        Vec2 movePoint = touch->getLocationInView();
        
        testFunc(movePoint);
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        Vec2 releasePoint = touch->getLocationInView();
        
    };    
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,this);
    
    
    return true;
}

void TestLayer::testFunc(Vec2 p)
{
//    Sprite * sp = bgSp1;
//
//    unsigned char * data = img->getData();
//    Texture2D::PixelFormat piexFormat =  img->getRenderFormat();
//    bool hasA = img->hasAlpha();
//    if(piexFormat == Texture2D::PixelFormat::RGBA8888 && hasA)
//    {
//        for (int i=0; i < img->getWidth(); i++)
//        {
//            for (int j=0; j < img->getHeight(); j++)
//            {
//                if ((j-p.y )* (j-p.y ) + (i-p.x) * (i-p.x) < 1600) {
//                    
//                    int imageOffset = j * img->getWidth() + i;
//                    unsigned char *  piexData = data;
//                    
////                    piexData[imageOffset * 4 + 0] = 0;
////                    piexData[imageOffset * 4 + 1] = 255;
////                    piexData[imageOffset * 4 + 2] = 0;
//                    piexData[imageOffset * 4 + 3] = 0;
//                }
//            }
//        }
//        
//        texture = new (std::nothrow) Texture2D();
//        texture->initWithImage(img);
//        sp->setTexture(texture);
//    }
    
    
    pEraser->setPosition(p);
    
    // 设置混合模式
    BlendFunc blendFunc = { GL_ONE, GL_ZERO };
    pEraser->setBlendFunc(blendFunc);
    
    // 将橡皮擦的像素渲染到画布上，与原来的像素进行混合
    pRTex->begin();
    pEraser->visit();
    pRTex->end();
    
    
}

void TestLayer::onStart(Ref* sender)
{
}

void TestLayer::onTest(Ref* sender)
{
}

void TestLayer::onSetting(Ref* sender)
{
    Director::getInstance()->popScene();
}
