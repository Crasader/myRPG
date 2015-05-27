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
    
    ////
    
    Sprite * bgSp_ = Sprite::create("bg_home.png");
    bgSp_->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    bgSp_->setScale(visibleSize.width / bgSp_->getContentSize().width, visibleSize.height / bgSp_->getContentSize().height);
    m_bgLayer->addChild(bgSp_);
    ///
    
//    exW = 40;
    
    Sprite * bgSp = Sprite::create("bg_lgame.png");
    bgSp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    Sprite * f1 = Sprite::create("m1.png");
    f1->setPosition(Vec2(visibleSize.width/2 + origin.x - 200, visibleSize.height/2 + origin.y - 300));
    
    bgSp->addChild(f1);
    bgSp->retain();

    srcImg = sprite2image(bgSp);
    
//    desImg = createEmptyImage(bgSp->getContentSize().width + exW * 2, bgSp->getContentSize().height);
    
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
            
            flag = true;
        }
        else
        {
            setImage(bgSp1,srcImg);
            flag = false;
        }
        
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,this);
    
    
    schedule(schedule_selector(Test3Layer::updateLoop));
    
    inTime = 2.0;
    desW = 40;
    timeCount = 0;
    return true;
}

void Test3Layer::updateLoop(float delta)
{
    timeCount += delta;
    
    exW = (desW * timeCount) /(inTime);
    
    if (exW > desW) {
        exW = desW;
    }
    testFunc();
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
                    int srcOffset = (i*w1 + srcLen) * bytePrePixel;
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
    
    Rect rect = Rect::ZERO;
    rect.size = texture->getContentSize();
    
    sp->setTexture(texture);
    sp->setTextureRect(rect, false, rect.size);
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
    
    
//    Sprite * bgSp = Sprite::create("bg_lgame.png");
    
    Size spSize = sp->getContentSize();
    sp->setPosition(Vec2(spSize.width / 2, spSize.height / 2));
    RenderTexture *render = RenderTexture::create(spSize.width, spSize.height, Texture2D::PixelFormat::RGBA8888);

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
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Image * img1 = createEmptyImage(visibleSize.width, visibleSize.height);
//    Image * img2 = sprite2image(sp);
    
    
    Sprite * bgSp = Sprite::create("bg_lgame.png");
    
    
    desImg = createEmptyImage(bgSp->getContentSize().width + exW * 2, bgSp->getContentSize().height);
    
    transformImage(srcImg,desImg);
    setImage(sp,desImg);
}

int Test3Layer::scanStartX(int scanLineIdx)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int w = srcImg->getWidth();
    int ww = desImg->getWidth();
    
    Sprite * bgSp = Sprite::create("bg_lgame.png");
    Size spSize = bgSp->getContentSize();
    int spW =spSize.width;
    int startX = 0;
    if (exW == 0) {
        return startX;
    }
    
    int x1= circleP[0].x = 0;
    int y1= circleP[0].y = 0;
    int x2= circleP[1].x = -exW;
    int y2= circleP[1].y = srcImg->getHeight() / 2;
    int x3= circleP[2].x = 0;
    int y3= circleP[2].y = srcImg->getHeight() ;
    int a = 2*(x2-x1);
    int b = 2 *(y2-y1);
    int c = x2*x2 + y2*y2-x1*x1-y1*y1;
    int d = 2*(x3-x2);
    int e = 2*(y3-y2);
    int f = x3*x3+y3*y3-x2*x2-y2*y2;
    
    int x=(b*f-e*c) / (b*d-e*a);
    int y=(d*c-a*f)/(b*d-e*a);
    int r=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
    
    
    int h = desImg->getHeight();
    //    int w = img2->getWidth();
//    int cx = (h / 2) * 2;
    int cx = r;
    startX = sqrt(pow(cx, 2) -pow(scanLineIdx-h/2, 2)) + (cx);
    if (startX > cx) {
        startX = cx-(startX-cx);
    }
    return startX;
}


int Test3Layer::scanLenX(int scanLineIdx)
{
//    int h = img2->getHeight();
    int w = desImg->getWidth();
    int len = w - 2 * scanStartX(scanLineIdx);
    return len;
}

