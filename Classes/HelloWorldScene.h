#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Monster.h"

USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();


    virtual bool init();
    

    void menuCloseCallback(cocos2d::Ref* pSender);
    
	bool isPress;
    
    Vec2 pressPoint;
    Vec2 movePoint;
	Vec2 releasePoint;

    bool isShortTime;
    float jumpInterval;

	long millisecondNow()  ;

    void updateLoop(float delta);
//    Sprite * mainRole;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
