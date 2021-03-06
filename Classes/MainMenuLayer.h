#ifndef __MAIN_MENU_LAYER_H__
#define __MAIN_MENU_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;
class MainMenuLayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();


    virtual bool init();
    
	Layer * m_bgLayer;
	Layer * m_menuLayer;

    void onStart(Ref* sender);
    void onTest(Ref* sender);
    
    void onSetting(Ref* sender);

    CREATE_FUNC(MainMenuLayer);
};

#endif // __MAIN_MENU_LAYER_H__
