#include "Monster.h"
#include "Utils/CommonUtils.h"

#define JUMP_STEP_LEN (100)
#define MOVE_STEP_LEN (2)
#define JUMP_INTERVAL (0.3)
#define JUMP_MAX_TIME (0.3)
#define MIN_MOVE_TOUCH_LEN (50)
#define MAX_ATK_TOUCH_LEN (10)

#define MONSTER_STEP_LEN (1.8)

#define MAX_SCAN_LEN (150)


#define SKILL_PRO_W (60)
#define SKILL_PRO_H (16)

const string monsterSpImage[4] = {"m1.png","m2.png","m3.png","m4.png"};

Monster::Monster()
{
	this->lv=1;
    this->hp=100;
    this->def=6;
    this->atk=3;
    this->chance=1;
    this->skLen = 30;
	this->skIv = 1.5;
	this->isAtk = false;
    this->isActive = false;
    this->atkTime = 0;
	m_taget = NULL;
	schedule(schedule_selector(Monster::updateLoop));
}

Monster::~Monster()
{
    
}

Monster* Monster::create(const std::string& filename)
{
    Monster *sprite = new (std::nothrow) Monster();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Monster::attack()
{
	if(isAtk == true)
	{
		return;
	}
    isAtk = true;
    skillDrawNode = DrawNode::create();
	
    skillProcessDrawNode = DrawNode::create();
	
	this->m_gameLayer->m_skillLayer->addChild(skillDrawNode);
	this->addChild(skillProcessDrawNode);
    
    auto s = Director::getInstance()->getWinSize();

	Vec2 rolePos = m_taget->getPosition();
	Vec2 thisPos = this->getPosition();

	skillProcessDrawNode->drawRect(
		Vec2(this->getContentSize().width / 2 - SKILL_PRO_W / 2, this->getContentSize().height + SKILL_PRO_H / 2)
		,Vec2(this->getContentSize().width / 2 + SKILL_PRO_W / 2, this->getContentSize().height - SKILL_PRO_H / 2)
		,Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

	skillDrawNode->drawDot(Vec2(rolePos.x, rolePos.y), this->skLen, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    

	CCLOG("attack getPositionY = %f getPositionY = %f",getPositionX(),getPositionY());
    //
	/*
    auto s = Director::getInstance()->getWinSize();
    
    auto draw = DrawNode::create();
    addChild(draw, 10);
    
    // 画10个圆，实际上是画了10个点，指定点的大小，所以看起来就是圆；
    for( int i=0; i < 10; i++)
    {
        draw->drawDot(Vec2(s.width/2, s.height/2), 10*(10-i), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }
    
    // 画多边形
    Vec2 points[] = { Vec2(s.height/4,0), Vec2(s.width,s.height/5), Vec2(s.width/3*2,s.height) };
    draw->drawPolygon(points, sizeof(points)/sizeof(points[0]), Color4F(1,0,0,0.5), 4, Color4F(0,0,1,1));
    */
}

void Monster::setTaget(MainRole *taget)
{
	m_taget = taget;
}

void Monster::setGameLayer(GameLayer *layer)
{
	m_gameLayer = layer;
	m_gameLayer->m_roleLayer->addChild(this);
}

void Monster::updateLoop(float delta)
{
	if(m_taget != NULL)
	{
		Sprite * monsterSp = this;
        Sprite * roleSp = m_taget;
        
        float delt_x = monsterSp->getPositionX() - roleSp->getPositionX();
        float delt_y = monsterSp->getPositionY() - roleSp->getPositionY();
        if( (this->isActive == false) && (delt_x * delt_x + delt_y * delt_y) < MAX_SCAN_LEN * MAX_SCAN_LEN)
        {
            this->isActive = true;
        }
        bool skLenReady = (delt_x * delt_x + delt_y * delt_y) < this->skLen;
           
        if (this->isActive == true) {
			if(skLenReady == false && isAtk == false)
            {
                Vec2 deltVec = CommonUtils::getVecByAngleAndLen(monsterSp->getPosition(), roleSp->getPosition(), MONSTER_STEP_LEN);
                    
//                CCLOG("HelloWorld::updateLoop monsterSp x = %f monsterSp y = %f" ,monsterSp->getPositionX(),monsterSp->getPositionY());
//                CCLOG("HelloWorld::updateLoop roleSp x = %f roleSp y = %f" ,roleSp->getPositionX(),roleSp->getPositionY());
                    
                float spX = monsterSp->getPositionX();
                float spY = monsterSp->getPositionY();
                monsterSp->setPosition(spX + deltVec.x, spY + deltVec.y);
//                CCLOG("HelloWorld::updateLoop spX + deltVec.x x = %f spY + deltVec.y y = %f" ,spX + deltVec.x,spY + deltVec.y);
                    
            }
            else
            {
				attack();
            }

			if(isAtk == true)
			{
				this->atkTime += delta;

				if(atkTime >= this->skIv)
				{
					isAtk =  false;
					atkTime = 0;
					skillProcessDrawNode->removeFromParent();
				}
			}

        }
		/*
        Size visibleSize = Director::getInstance()->getVisibleSize();
        if(monsterSp->getPositionX() < -40 || monsterSp->getPositionX() > visibleSize.width + 40
            || monsterSp->getPositionY() < -40 || monsterSp->getPositionY() > visibleSize.height + 40)
        {
			this->removeFromParent();
        }
		*/
	}
}