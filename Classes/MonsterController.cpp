#include "MonsterController.h"
#include "Utils/CommonUtils.h"
#include "MainRoleController.h"

#define JUMP_STEP_LEN (100)
#define MOVE_STEP_LEN (2)
#define JUMP_INTERVAL (0.3)
#define JUMP_MAX_TIME (0.3)
#define MIN_MOVE_TOUCH_LEN (50)
#define MAX_ATK_TOUCH_LEN (10)

#define MONSTER_STEP_LEN (2.1)

#define MAX_SCAN_LEN (150)

static MonsterController *s_instance = nullptr;
const string monsterSpImage[4] = {"m1.png","m2.png","m3.png","m4.png"};

MonsterController::MonsterController()
{

	    


    /*
    this->sp = Sprite::create();
    this->lv=1;
    this->hp=100;
    this->def=6;
    this->atk=3;
    this->chance=1;
    this->skLen = 30;
    this->skStart = false;
    this->isActive = false;
    
	m_taget = NULL;
	*/
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

void MonsterController::createMonster(Node * layer)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //创建怪物
    for (int i=0; i< 8; i++) {
		int imgIdx = CommonUtils::RandAmongMinMax(0,3);

        Monster * monster = (Monster *)Monster::create(monsterSpImage[imgIdx]);
        monsters.pushBack(monster);
        monster->setPosition(CommonUtils::RandAmongMinMax(0 + 40 ,visibleSize.width - 40 )
                                 ,CommonUtils::RandAmongMinMax(0 + 40,visibleSize.height - 40));
        layer->addChild(monster);
    }
}

void MonsterController::setTaget(MainRole * role)
{
	for(int i=0;i<monsters.size();i++)
	{
		monsters.at(i)->setTaget(role);
	}
}