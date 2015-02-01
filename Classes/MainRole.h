#ifndef __MAIN_ROLE_H__
#define __MAIN_ROLE_H__

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;
class MainRole : public Sprite
{
public:
    MainRole();
    ~MainRole();

	static MainRole* create(const std::string& filename);

    int hp;
    int def;
    int atk;
    int chance;
    int lv;
    int skID;
    void jump(Vec2 from ,Vec2 to);
	void move(Vec2 from ,Vec2 to);
	void attack();
	
    bool isDead;
	GameLayer * m_gameLayer;
	
	void setGameLayer(GameLayer *layer);
    
    void updateLoop(float delta);
};

#endif // __MAIN_ROLE_H__
