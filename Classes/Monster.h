#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
#include "2d/CCNode.h"
#include "MainRole.h"
#include "GameLayer.h"

USING_NS_CC;
class MainRole;
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
    float skIv;//技能吟唱时间
    bool isAtk;
	float atkTime;
    
    bool isActive;
//    bool isPause;
	GameLayer * m_gameLayer;
	MainRole * m_taget;
	
    Vec2 skillPos;
	
	Sprite * proBg;
	Sprite * skill;
	ProgressTimer * ptSkill;

	void setGameLayer(GameLayer *layer);
	void setTaget(MainRole *taget);
	void updateLoop(float delta);
//    void pause();
//    void resume();
};

#endif // __MONSTER_H__
