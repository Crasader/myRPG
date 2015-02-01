#ifndef __MONSTER_CONTROLLER_H__
#define __MONSTER_CONTROLLER_H__

#include "cocos2d.h"
#include "Monster.h"
#include "GameLayer.h"

USING_NS_CC;

class MonsterController
{
public:
    MonsterController();
	~MonsterController();
	
    static MonsterController* getInstance();

	Vector<Monster *> monsters;
	void createMonster(GameLayer * layer);
	
	void setTaget(MainRole * role);
};

#endif // __MONSTER_CONTROLLER_H__
