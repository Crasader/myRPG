#include "MainRoleController.h"
#include "Utils/CommonUtils.h"

// singleton stuff
static MainRoleController *s_instance = nullptr;
MainRoleController::MainRoleController()
{

}

MainRoleController::~MainRoleController()
{
    
}

MainRoleController* MainRoleController::getInstance()
{
    if (!s_instance)
    {
        s_instance = new (std::nothrow) MainRoleController();
        CCASSERT(s_instance, "FATAL: Not enough memory");
    }
    
    return s_instance;
}

void MainRoleController::createMainRole(GameLayer * layer)
{
	this->role = (MainRole *)MainRole::create("f1.png");
	this->role->setGameLayer(layer);
}