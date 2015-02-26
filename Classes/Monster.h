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
    Monster(int type);
    ~Monster();
	static Monster* create(const std::string& filename,int type);
    void attack();

    int type;
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
    
    bool isDead;
    bool isActive;
//    bool isPause;
	GameLayer * m_gameLayer;
	MainRole * m_taget;
	
    Vec2 skillPos; // 开始攻击的时候，目标的位置（注意：攻击过程中，目标可能会移动）
	
	Sprite * proBg;
	Sprite * skill;
	ProgressTimer * ptSkill;
    
    int setMonsterByType(int type);
    void drawSkillByType(int type);
    bool checkSillHitByType(int type);
    
	void setGameLayer(GameLayer *layer);
	void setTaget(MainRole *taget);
    void updateLoop(float delta);
    void attacked(int damageValue);
    Sprite * focusImg;
    void setFocus();
    void setNoFocus();
//    void pause();
//    void resume();
};

#endif // __MONSTER_H__
