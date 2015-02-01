#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;
class PauseLayer : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    
    
    virtual bool init();
    
    Layer * m_bgLayer;
    Layer * m_menuLayer;
    
    void onStart(Ref* sender);
    void onTest(Ref* sender);
    
    void onSetting(Ref* sender);
    
    CREATE_FUNC(PauseLayer);
};

#endif // __PAUSE_LAYER_H__
