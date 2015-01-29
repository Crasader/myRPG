#ifndef __MAIN_ROLE_H__
#define __MAIN_ROLE_H__

#include "cocos2d.h"

USING_NS_CC;
class MainRole
{
public:
    MainRole();
    ~MainRole();
    
    static MainRole* getInstance();
    Sprite * sp;
    int hp;
    int def;
    int atk;
    int chance;
    int lv;
    int skID;
    
};

#endif // __HELLOWORLD_SCENE_H__
