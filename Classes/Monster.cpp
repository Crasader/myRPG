#include "Monster.h"
#include "CommonUtils.h"

#define JUMP_STEP_LEN (100)
#define MOVE_STEP_LEN (2)
#define JUMP_INTERVAL (0.3)
#define JUMP_MAX_TIME (0.3)
#define MIN_MOVE_TOUCH_LEN (50)
#define MAX_ATK_TOUCH_LEN (10)

const string monsterSpImage[4] = {"m1.png","m2.png","m3.png","m4.png"};

Monster::Monster()
{
    int imgIdx = CommonUtils::RandAmongMinMax(0,3);
    this->sp = Sprite::create(monsterSpImage[imgIdx]);
    this->lv=1;
    this->hp=100;
    this->def=6;
    this->atk=3;
    this->chance=1;
    
    this->isActive = false;
    
}

Monster::~Monster()
{
    
}
