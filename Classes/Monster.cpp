#include "Monster.h"
#include "Utils/CommonUtils.h"
#include "GameConst.h"

#define MONSTER_STEP_LEN (1.8)

#define MAX_SCAN_LEN (150)


#define SKILL_PRO_W (60)
#define SKILL_PRO_H (16)

const string monsterSpImage[4] = {"m1.png","m2.png","m3.png","m4.png"};

Monster::Monster(int type)
{
    this->type = type;
	this->lv=1;
    this->hp=100;
    this->def=6;
    this->atk=3;
    this->chance=1;
    this->skLen = setMonsterByType(type);


	this->skIv = 1.8;
	this->isAtk = false;
    this->isActive = false;
    this->atkTime = 0;
    this->isDead = false;
	
    this->proBg = NULL;
    this->skill = NULL;
    this->ptSkill = NULL;
	m_taget = NULL;
	schedule(schedule_selector(Monster::updateLoop));
}

Monster::~Monster()
{
    
}

Monster* Monster::create(const std::string& filename,int type)
{
    Monster *sprite = new (std::nothrow) Monster(type);
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

    //绘制技能
    skillPos = m_taget->getPosition();
    drawSkillByType(type);
    //绘制释放进度
	proBg = Sprite::create("skProgressBg.png");
	proBg->setPosition(this->getContentSize().width / 2,this->getContentSize().height / 2 + 50);
	
	ProgressTo* progressTo = CCProgressTo::create(this->skIv,100);
	//创建进度条渲染器，载体为精灵
	ptSkill = ProgressTimer::create(Sprite::create("skProgress.png"));
	ptSkill->setType(ProgressTimer::Type::BAR);
	ptSkill->setBarChangeRate(Vec2(1,0));//高为100%  
    ptSkill->setMidpoint(Vec2(0,0));//设置增长中心
	ptSkill->runAction(progressTo);
	ptSkill->setPosition(this->getContentSize().width / 2 ,this->getContentSize().height / 2 + 50);
    
    this->addChild(proBg);
    this->m_gameLayer->m_skillLayer->addChild(skill);
	this->addChild(ptSkill);
	
	//CCLOG("attack getPositionY = %f getPositionY = %f",getPositionX(),getPositionY());
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
    if(isDead == true)
    {
        this->setColor(Color3B::GRAY);
        
        if(ptSkill != NULL)
        {
            ptSkill->removeFromParent();
            ptSkill = NULL;
        }
        if(skill != NULL)
        {
            skill->removeFromParent();
            skill = NULL;
        }
        if(proBg != NULL)
        {
            proBg->removeFromParent();
            proBg = NULL;
        }
        
        return;
    }
	if(m_taget != NULL)
	{
        if(m_taget->isDead == false)
        {
		Sprite * monsterSp = this;
        Sprite * roleSp = m_taget;
        
        float delt_x = monsterSp->getPositionX() - roleSp->getPositionX();
        float delt_y = monsterSp->getPositionY() - roleSp->getPositionY();
        if( (this->isActive == false) && (delt_x * delt_x + delt_y * delt_y) < MAX_SCAN_LEN * MAX_SCAN_LEN)
        {
            this->isActive = true;
        }
        bool skLenReady = (delt_x * delt_x + delt_y * delt_y) < this->skLen *  this->skLen;
           
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

				float present = 0.5 + this->atkTime / this->skIv / 2;

				GLubyte opacity= present * 255;

				skill->setOpacity(opacity);
				

				if(atkTime >= this->skIv)
				{
                    if(checkSillHitByType(type) == true)
                    {
                        m_taget->hp -= 20;
                    }
                    
					isAtk =  false;
					atkTime = 0;
                    
					ptSkill->removeFromParent();
                    ptSkill = NULL;
                    skill->removeFromParent();
                    skill = NULL;
                    proBg->removeFromParent();
                    proBg = NULL;
                    
				}
			}
        }
        }
        else
        {
            if(isAtk == true)
            {
            isAtk =  false;
            atkTime = 0;
            if(ptSkill != NULL)
            {
                //ptSkill->stopAllActions();
                
                ptSkill->removeFromParent();
                ptSkill = NULL;
            }
            
            if(skill != NULL)
            {
                skill->removeFromParent();
                skill = NULL;
            }
            
            if(proBg != NULL)
            {
                proBg->removeFromParent();
                proBg = NULL;
            }
            }
        }
	}
}

int Monster::setMonsterByType(int type)
{
    int result = 0;
    switch (type)
    {
        case 0:
        {
            result = 80;
        }
            break;
        case 1:
        {
            
            result = 180;
        }
            break;
            
        default:
        {
            
            result = 180;
        }
            break;
    }
    
    return result;
}

void Monster::drawSkillByType(int type)
{
    switch (type)
    {
        case 0:
        {
            skill = Sprite::create("skill.png");
            skill->setPosition(skillPos.x, skillPos.y);
        }
            break;
        case 1:
        {
            skill = Sprite::create("slider_gauge.png");
            skill->cocos2d::Node::setAnchorPoint(Vec2(0,0.5));
            skill->setPosition(getPosition().x, getPosition().y);
            
            float angle = CommonUtils::getAngleBy2Point(getPosition(),skillPos);
            angle = -angle;
            //解析几何里面，旋转是逆时针，而 setRotation 逆时针旋转，需要是负整数
            skill->setRotation(angle);
            
        }
            break;
            
        default:
        {
            skill = Sprite::create("slider_gauge.png");
            skill->cocos2d::Node::setAnchorPoint(Vec2(0,0.5));
            skill->setPosition(getPosition().x, getPosition().y);
            
            float angle = CommonUtils::getAngleBy2Point(getPosition(),skillPos);
            angle = -angle;
            //解析几何里面，旋转是逆时针，而 setRotation 逆时针旋转，需要是负整数
            skill->setRotation(angle);
        }
            break;
    }

}

bool Monster::checkSillHitByType(int type)
{
    bool result = false;
    switch (type)
    {
        case 0:
        {
            Vec2 rolePos = m_taget->getPosition();
            Vec2 deltPos = rolePos - skillPos;
            float distance = rolePos.distance(skillPos);
            if(distance < this->skLen)
            {
                result = true;
            }
        }
            break;
        case 1:
        {
            float angle = CommonUtils::getAngleBy2Point(getPosition(),skillPos);
            float distance = CommonUtils::getDistanceOfPoint2Line(getPosition(), angle,m_taget->getPosition());
            
            if(distance <= (skill->getContentSize().height / 2))
            {
                result = true;
            }
        }
            break;
            
        default:
        {
            float angle = CommonUtils::getAngleBy2Point(getPosition(),skillPos);
            float distance = CommonUtils::getDistanceOfPoint2Line(getPosition(), angle,m_taget->getPosition());
            
            if(distance <= (skill->getContentSize().height / 2))
            {
                result = true;
            }
        }
            break;
    }
    
    return result;
}
//void Monster::pause()
//{
//    isPause = true;
//}
//void Monster::resume()
//{
//    isPause = false;
//}