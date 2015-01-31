#ifndef __MAIN_ROLE_CONTROLLER_H__
#define __MAIN_ROLE_CONTROLLER_H__

#include "cocos2d.h"
#include "MainRole.h"
USING_NS_CC;
class MainRoleController
{
public:
	MainRoleController();
	~MainRoleController();
	MainRole * role;
	
    static MainRoleController* getInstance();

	void createMainRole(Node * layer);

};

#endif // __MAIN_ROLE_CONTROLLER_H__
