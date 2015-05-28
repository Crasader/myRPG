#include "ImageExpand.h"

ImageExpand* ImageExpand::create(float duration, int desW)
{
    ImageExpand *ret = new (std::nothrow) ImageExpand();
    ret->initWithDuration(duration, desW);
    ret->autorelease();
    
    return ret;
}

bool ImageExpand::initWithDuration(float duration, int desW)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _desW = desW;
        return true;
    }
    
    return false;
}

ImageExpand* ImageExpand::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) ImageExpand();
    a->initWithDuration(_duration, _desW);
    a->autorelease();
    return a;
}

void ImageExpand::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
    
    exW = 0;
    exflag = true;
    
    _srcImg = sprite2image((Sprite *)target);
    desImg = NULL;
//    _previousPosition = _startPosition = target->getPosition();
}

ImageExpand* ImageExpand::reverse() const
{
    return nullptr;
//    return ImageExpand::create(_duration, Vec2( -_positionDelta.x, -_positionDelta.y));
}


void ImageExpand::update(float t)
{
    if (t == 0) {
        return;
    }
    if (_target)
    {
#if CC_ENABLE_STACKABLE_ACTIONS
        preFrameStepW = _desW / _duration * t;
        
        if (exflag) {
            exW+=preFrameStepW;
            if (exW >_desW) {
                exW = _desW;
                exflag = false;
            }
        } else {
            
            exW-=preFrameStepW;
            if (exW <0) {
                exW = 0;
                exflag = true;
            }
        }
//        CCLOG("update exW = %d",exW);
#else
        exW = _desW;
#endif // CC_ENABLE_STACKABLE_ACTIONS
        
        transformImageSprite((Sprite *)_target);
    }
}


void ImageExpand::transformImage(Image * src,Image * des)
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
            
//            CCLOG("testFunc i = %d,xxx = %d ,xxx+len = %d",i,xxx,xxx + len);
            
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


void ImageExpand::setImage(Sprite * sp1,Image * img)
{
    Sprite * sp =(Sprite *)_target;
    
    Texture2D * texture = new (std::nothrow) Texture2D();
    texture->initWithImage(img);
    
    Rect rect = Rect::ZERO;
    rect.size = texture->getContentSize();
    
    sp->setTexture(texture);
    sp->setTextureRect(rect, false, rect.size);
}

Image* ImageExpand::createEmptyImage(float w,float h)
{
    RenderTexture *render1 = CCRenderTexture::create(w, h, Texture2D::PixelFormat::RGBA8888);

    render1->beginWithClear(0,0,0,0);
    
    render1->end();
    Director::getInstance()->getRenderer()->render();
    render1->retain();
    
    Image * img = render1->newImage();
    return img;
}

Image* ImageExpand::sprite2image(Sprite * sp1)
{
    Sprite * sp =(Sprite *)_target;
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

void ImageExpand::transformImageSprite(Sprite * sp)
{
    if (desImg && desImg->getReferenceCount() > 0) {
        desImg->release();
        desImg = NULL;
    }
    desImg = createEmptyImage(_srcImg->getWidth() + exW * 2, _srcImg->getHeight());
    
    transformImage(_srcImg,desImg);
    setImage(sp,desImg);
}

int ImageExpand::scanStartX(int scanLineIdx)
{
    Sprite * bgSp =(Sprite *)_target;
    Size spSize = bgSp->getContentSize();
    int startX = 0;
    if (exW == 0) {
        return startX;
    }
    
    int x1= circleP[0].x = 0;
    int y1= circleP[0].y = 0;
    int x2= circleP[1].x = -exW;
    int y2= circleP[1].y = _srcImg->getHeight() / 2;
    int x3= circleP[2].x = 0;
    int y3= circleP[2].y = _srcImg->getHeight() ;
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
    int cx = r;
    startX = sqrt(pow(cx, 2) -pow(scanLineIdx-h/2, 2)) + (cx);
    if (startX > cx) {
        startX = cx-(startX-cx);
    }
    return startX;
}


int ImageExpand::scanLenX(int scanLineIdx)
{
//    int h = img2->getHeight();
    int w = desImg->getWidth();
    int len = w - 2 * scanStartX(scanLineIdx);
    return len;
}

