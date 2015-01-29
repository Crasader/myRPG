#include "MainRole.h"
#include "CommonUtils.h"

#define JUMP_STEP_LEN (100)
#define MOVE_STEP_LEN (2)
#define JUMP_INTERVAL (0.3)
#define JUMP_MAX_TIME (0.3)
#define MIN_MOVE_TOUCH_LEN (50)
#define MAX_ATK_TOUCH_LEN (10)

// singleton stuff
static MainRole *s_instance = nullptr;
MainRole::MainRole()
{
    this->sp = Sprite::create("f1.png");
    this->lv=1;
    this->hp=100;
    this->def=6;
    this->atk=3;
    this->chance=1;
    
}

MainRole::~MainRole()
{
    
}

MainRole* MainRole::getInstance()
{
    if (!s_instance)
    {
        s_instance = new (std::nothrow) MainRole();
        CCASSERT(s_instance, "FATAL: Not enough memory");
    }
    
    return s_instance;
}