#include "MonsterController.h"
#include "Utils/CommonUtils.h"
#include "MainRoleController.h"

static MonsterController *s_instance = nullptr;
const string monsterSpImage[4] = {"m1.png","m2.png","m3.png","m4.png"};

MonsterController::MonsterController()
{

}

MonsterController::~MonsterController()
{
    
}
MonsterController* MonsterController::getInstance()
{
    if (!s_instance)
    {
        s_instance = new (std::nothrow) MonsterController();
        CCASSERT(s_instance, "FATAL: Not enough memory");
    }
    
    return s_instance;
}

void MonsterController::createMonster(GameLayer * layer)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    for (int i=0; i< 8; i++) {
		int imgIdx = CommonUtils::RandAmongMinMax(0,4);

        Monster * monster = (Monster *)Monster::create(monsterSpImage[imgIdx]);
        monsters.pushBack(monster);
        monster->setPosition(CommonUtils::RandAmongMinMax(0 + 40 ,visibleSize.width - 40 )
                                 ,CommonUtils::RandAmongMinMax(0 + 40,visibleSize.height - 40));

		monster->setGameLayer(layer);

		//monster->setScale(0.4);
    }
}

void MonsterController::setTaget(MainRole * role)
{
	for(int i=0;i<monsters.size();i++)
	{
		monsters.at(i)->setTaget(role);
	}
}