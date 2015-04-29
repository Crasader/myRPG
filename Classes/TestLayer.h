#ifndef __TEST_LAYER_H__
#define __TEST_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;
class TestLayer : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    
    
    virtual bool init();
    
    
    Layer * m_bgLayer;
    Layer * m_menuLayer;
    
    void onStart(Ref* sender);
    void onTest(Ref* sender);
    
    void onSetting(Ref* sender);
    
    
    Image * img;
    DrawNode * pEraser;
    
    RenderTexture * pRTex;
    Texture2D * texture;
    
    void testFunc(Vec2 p);
    CREATE_FUNC(TestLayer);
};

#endif // __TEST_LAYER_H__
