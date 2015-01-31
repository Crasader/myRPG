#include "MainRoleController.h"
#include "Utils/CommonUtils.h"

#define JUMP_STEP_LEN (100)
#define MOVE_STEP_LEN (2)
#define JUMP_INTERVAL (0.3)
#define JUMP_MAX_TIME (0.3)
#define MIN_MOVE_TOUCH_LEN (50)
#define MAX_ATK_TOUCH_LEN (10)

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

void MainRoleController::createMainRole(Node * layer)
{
	this->role = (MainRole *)MainRole::create("f1.png");
	layer->addChild(role);
}