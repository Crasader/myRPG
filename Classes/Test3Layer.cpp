#include "Test3Layer.h"
#include "MainMenuLayer.h"
#include "GameConst.h"

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
    
    //    Sprite * bgSp = Sprite::create("bg_home.png");
    //    bgSp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //    bgSp->setScale(visibleSize.width / bgSp->getContentSize().width, visibleSize.height / bgSp->getContentSize().height);
    //    m_bgLayer->addChild(bgSp);
    
    
    img = new Image();
    img->initWithImageFile("bg_lgame.png");
    
    img2 = new Image();
    img2->initWithImageFile("bg_lgame.png");
    
    bgSp1 = Sprite::create("bg_lgame.png");
    bgSp1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
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
        if (flag==false) {
            
            testFunc(releasePoint);
            flag = true;
        }else{
            
            Sprite * sp = bgSp1;
            texture = new (std::nothrow) Texture2D();
            texture->initWithImage(img);
            sp->setTexture(texture);
            flag = false;
        }
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,this);
    
    
    return true;
}

void Test3Layer::testFunc(Vec2 p)
{
    Sprite * sp = bgSp1;
    
    unsigned char * data = img->getData();
    unsigned char * data2 = img2->getData();
    Texture2D::PixelFormat piexFormat =  img->getRenderFormat();
    bool hasA = img->hasAlpha();
    if(piexFormat == Texture2D::PixelFormat::RGBA8888 && hasA)
    {
        
        int h = img->getHeight();
        int w = img->getWidth();
        
        int c = (h / 2) * 2;
        
        unsigned char *  piexData = data;
        unsigned char *  piexData2 = data2;
        
        int k = 0;
        
        for (int i=0; i < h; i++)
        {
            for (int j=0; j < w; j++)
            {
                int offset = (i*w + j) * 4;
                piexData2[offset+0] = 0;
                piexData2[offset+1] = 0;
                piexData2[offset+2] = 0;
                piexData2[offset+3] = 0;
            }
        }
        
        for (int i=0; i < h; i++)
        {
            k = 0;
            int xxx = sqrt(pow(c, 2) -pow(i-h/2, 2)) + (c);
            if (xxx > c) {
                xxx = c-(xxx-c);
            }
            int len = w-2*xxx;
            
            int left = xxx;
            int right = xxx + len;
            
            CCLOG("testFunc i = %d,xxx = %d ,xxx+len = %d",i,xxx,xxx + len);
            
            for (int j=0; j < w; j++)
            {
                int offset = (i*w + j) * 4;
                if (j<left || j > right) {
                    
                    piexData2[offset+0] = 0;
                    piexData2[offset+1] = 0;
                    piexData2[offset+2] = 0;
                    piexData2[offset+3] = 0;
                    continue;
                }else{
                    float scaleX = ((float)w / (float)len);
                    
                    int srcLen = (int)(k * scaleX + scaleX /2);
                    int srcOffset = (i*w + srcLen) * 4;
                    piexData2[offset+0]=piexData[srcOffset + 0];
                    piexData2[offset+1]=piexData[srcOffset + 1];
                    piexData2[offset+2]=piexData[srcOffset + 2];
                    piexData2[offset+3]=piexData[srcOffset + 3];
                    k++;
                    
                }
                
            }
        }
        
        texture = new (std::nothrow) Texture2D();
        texture->initWithImage(img2);
        sp->setTexture(texture);
    }
    
    
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
