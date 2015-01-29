#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"

USING_NS_CC;
class Monster
{
public:
    Monster();
    ~Monster();

    Sprite * sp;
    int hp;
    int def;
    int atk;
    int chance;
    int lv;
    int skID;
    bool isActive;
};

#endif // __HELLOWORLD_SCENE_H__
