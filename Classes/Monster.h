#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"

USING_NS_CC;
class Monster
{
public:
    Monster();
    ~Monster();
    void startAtk();
    Sprite * sp;
    int hp;
    int def;
    int atk;
    int chance;
    int lv;
    int skID;
    int skLen;//技能释放长度
    int skIv;//技能吟唱时间
    bool skStart;
    
    bool isActive;
};

#endif // __HELLOWORLD_SCENE_H__
