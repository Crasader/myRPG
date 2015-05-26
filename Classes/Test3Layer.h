#ifndef __TEST3_LAYER_H__
#define __TEST3_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;
class Test3Layer : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    
    
    virtual bool init();
    
    
    Layer * m_bgLayer;
    Layer * m_menuLayer;
    
    void onStart(Ref* sender);
    void onTest(Ref* sender);
    
    void onSetting(Ref* sender);
    
    
    Image * srcImg;
    Image * desImg;
    DrawNode * pEraser;
    Sprite * bgSp1;
    RenderTexture * pRTex;
    Texture2D * texture;
    bool flag;
    void testFunc();
    
    
    
    Image* createEmptyImage(float w,float h);
    
    void setImage(Sprite * sp,Image * img);
    
    
    Image* sprite2image(Sprite * sp);
    void transformImage(Image * src,Image * des);
    void transformImageSprite(Sprite * sp);
    
    int scanStartX(int scanLineIdx);
    
    int scanLenX(int scanLineIdx);
    
    CREATE_FUNC(Test3Layer);
};

#endif // __TEST3_LAYER_H__
