#ifndef __MAIN_ROLE_H__
#define __MAIN_ROLE_H__

#include "cocos2d.h"
#include "GameLayer.h"
#include "Monster.h"

USING_NS_CC;
class Monster;
class MainRole : public Sprite
{
public:
    MainRole();
    ~MainRole();

	static MainRole* create(const std::string& filename);

    int hp;
    int mp;
    int def;
    int atk;
    int chance;
    int lv;
    int skID;
    float atkLen ;
    void jump(Vec2 from ,Vec2 to);
	void move(Vec2 from ,Vec2 to);
	void attack();
	
    bool isAtk;
    bool isDead;
    float atkInterval;
//    bool isPause;
	GameLayer * m_gameLayer;
    Monster * m_target;
    
	void setGameLayer(GameLayer *layer);
    
    void setTarget(Monster * monster);
    void updateLoop(float delta);
    void resetAtkStatus(float delta);
//    void pause();
//    void resume();
};

#endif // __MAIN_ROLE_H__
