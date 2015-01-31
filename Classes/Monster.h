#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
#include "2d/CCNode.h"
#include "MainRole.h"


USING_NS_CC;

class Monster : public Sprite
{
public:
    Monster();
    ~Monster();
	static Monster* create(const std::string& filename);
    void attack();

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
	MainRole * m_taget;
	void setTaget(MainRole *taget);
	void updateLoop(float delta);
};

#endif // __MONSTER_H__
