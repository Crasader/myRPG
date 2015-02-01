#ifndef __MAIN_ROLE_CONTROLLER_H__
#define __MAIN_ROLE_CONTROLLER_H__

#include "cocos2d.h"
#include "MainRole.h"
#include "GameLayer.h"

USING_NS_CC;
class MainRoleController
{
public:
	MainRoleController();
	~MainRoleController();
	MainRole * role;
	
    static MainRoleController* getInstance();

	void createMainRole(GameLayer * layer);

};

#endif // __MAIN_ROLE_CONTROLLER_H__
