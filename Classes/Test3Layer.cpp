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
    
    Sprite * bgSp = Sprite::create("bg_lgame.png");
    bgSp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    Sprite * f1 = Sprite::create("m1.png");
    f1->setPosition(Vec2(visibleSize.width/2 + origin.x - 200, visibleSize.height/2 + origin.y - 300));
    
    bgSp->addChild(f1);
    bgSp->retain();

    srcImg = sprite2image(bgSp);

    desImg = createEmptyImage(visibleSize.width, visibleSize.height);
    
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
            
            testFunc();
            
            bgSp1->setScale(1.3, 1.0);
            flag = true;
        }
        else
        {
            setImage(bgSp1,srcImg);
            bgSp1->setScale(1.0, 1.0);
            flag = false;
        }
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,this);
    
    
    return true;
}

void Test3Layer::testFunc()
{
    transformImageSprite(bgSp1);
}


void Test3Layer::transformImage(Image * src,Image * des)
{
    Image * img = src;
    
    Image * img2 = des;
    
    unsigned char * data = img->getData();
    unsigned char * data2 = img2->getData();
    Texture2D::PixelFormat piexFormat =  img->getRenderFormat();
    bool hasA = img->hasAlpha();
    int bitPrePixel = img->getBitPerPixel();
    int bytePrePixel = bitPrePixel >>3;
    if(piexFormat == Texture2D::PixelFormat::RGBA8888 && hasA)
    {
        int h = img2->getHeight();
        int w = img2->getWidth();
        
        int w1 = img->getWidth();
        
        unsigned char *  piexData = data;
        unsigned char *  piexData2 = data2;
        
        int k = 0;
        
        for (int i=0; i < h; i++)
        {
            for (int j=0; j < w; j++)
            {
                int offset = (i*w + j) * bytePrePixel;
                memset(piexData2 + offset, 0, bytePrePixel);
            }
        }
        
        for (int i=0; i < h; i++)
        {
            k = 0;
            int xxx = scanStartX(i);
            int len = scanLenX(i);
            
            int left = xxx;
            int right = xxx + len;
            
            CCLOG("testFunc i = %d,xxx = %d ,xxx+len = %d",i,xxx,xxx + len);
            
            for (int j=0; j < w; j++)
            {
                int offset = (i*w + j) * bytePrePixel;
                if (j<left || j > right)
                {
                    memset(piexData2 + offset, 0, bytePrePixel);
                    continue;
                }
                else
                {
                    float scaleX = ((float)w1 / (float)len);
                    
                    int srcLen = (int)(k * scaleX + scaleX /2);
                    int srcOffset = (i*w + srcLen) * bytePrePixel;
                    memcpy(piexData2 + offset, piexData + srcOffset, bytePrePixel);
                    k++;
                    
                }
            }
        }
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

void Test3Layer::setImage(Sprite * sp,Image * img)
{
    Texture2D * texture = new (std::nothrow) Texture2D();
    texture->initWithImage(img);
    sp->setTexture(texture);
}

Image* Test3Layer::createEmptyImage(float w,float h)
{
    RenderTexture *render1 = CCRenderTexture::create(w, h, Texture2D::PixelFormat::RGBA8888);

    render1->beginWithClear(0,0,0,0);
    
    render1->end();
    Director::getInstance()->getRenderer()->render();
    render1->retain();
    
    Image * img = render1->newImage();
    return img;
}

Image* Test3Layer::sprite2image(Sprite * sp)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    RenderTexture *render = CCRenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);

    render->beginWithClear(0,0,0,0);
    sp->visit();
    render->end();
    Director::getInstance()->getRenderer()->render();
    render->retain();
    
    Image * img = render->newImage();
    
    return img;
}

void Test3Layer::transformImageSprite(Sprite * sp)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Image * img1 = createEmptyImage(visibleSize.width, visibleSize.height);
//    Image * img2 = sprite2image(sp);
    transformImage(srcImg,desImg);
    setImage(sp,desImg);
}

int Test3Layer::scanStartX(int scanLineIdx)
{
    int h = desImg->getHeight();
//    int w = img2->getWidth();
    int c = (h / 2) * 2;
    int x = sqrt(pow(c, 2) -pow(scanLineIdx-h/2, 2)) + (c);
    if (x > c) {
        x = c-(x-c);
    }
    return x;
}


int Test3Layer::scanLenX(int scanLineIdx)
{
//    int h = img2->getHeight();
    int w = desImg->getWidth();
    int len = w - 2 * scanStartX(scanLineIdx);
    return len;
}

