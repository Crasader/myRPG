#ifndef __MAIN_ROLE_CONTROLLER_H__
#define __MAIN_ROLE_CONTROLLER_H__

#include "cocos2d.h"
#include "MainRole.h"
#include "GameLayer.h"
#include "Monster.h"

USING_NS_CC;
class MainRoleController
{
public:
	MainRoleController();
	~MainRoleController();
	MainRole * role;
    static MainRoleController* getInstance();

    void createMainRole(GameLayer * layer);
    void setTarget(Monster * monster);
    void pause();
    
    void checkRoleTarget();
    void resume();
};

#endif // __MAIN_ROLE_CONTROLLER_H__
