#include "MainRoleController.h"
#include "Utils/CommonUtils.h"
#include "MonsterController.h"

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

void MainRoleController::setTarget(Monster * monster)
{
    this->role->setTarget(monster);
}

void MainRoleController::checkRoleTarget()
{
    float distance = (float)(99999);
    Monster * monster = NULL;
    Vector<Monster *> monsters = MonsterController::getInstance()->monsters;
    for(int i=0;i<monsters.size();i++)
    {
        if(monsters.at(i)->isDead == true)
        {
            continue;
        }
        Vec2 monsterPos = monsters.at(i)->getPosition();
        Vec2 rolePos = MainRoleController::getInstance()->role->getPosition();
        float distance1 = rolePos.distance(monsterPos);
//        CCLOG("checkRoleTarget1 i = %d monsterPos.x  = %f monsterPos.y = %f" ,i,monsterPos.x,monsterPos.y);
//        CCLOG("checkRoleTarget2 i = %d rolePos.x  = %f rolePos.y = %f" ,i,rolePos.x,rolePos.y);
//        CCLOG("checkRoleTarget3 i = %d distance1 = %f" ,i,distance1);
        if(distance1 < distance)
        {
            distance = distance1;
            monster = monsters.at(i);
        }
        
    }
    setTarget(monster);
}


void MainRoleController::pause()
{
    this->role->pause();
}

void MainRoleController::resume()
{
    this->role->resume();
}