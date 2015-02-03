#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
//#include "UIWidget.h"

USING_NS_CC;
class GameLayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();


    virtual bool init();
    
	Layer * m_bgLayer;
	Layer * m_skillLayer;
	Layer * m_uiLayer;
	Layer * m_roleLayer;
	Layer * m_touchLayer;

    void menuCloseCallback(cocos2d::Ref* pSender);
    
    
    static void onPause(Ref *pSender);
    Sprite * touchMoveShow;
	bool isPress;
    static bool isPause;
    Label * roleHP;
    
    Vec2 pressPoint;
    Vec2 movePoint;
	Vec2 releasePoint;

    bool isShortTime;
    float jumpInterval;

	long millisecondNow()  ;

    void updateLoop(float delta);

    CREATE_FUNC(GameLayer);
};

#endif // __GAME_LAYER_H__
