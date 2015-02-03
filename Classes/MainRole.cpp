#include "MainRole.h"
#include "Utils/CommonUtils.h"
#include "FailLayer.h"
#include "GameConst.h"

#define JUMP_STEP_LEN (100)
#define MOVE_STEP_LEN (2.9)
#define JUMP_INTERVAL (0.3)
#define ATTACK_LEN (80)


MainRole::MainRole()
{
	this->lv=1;
    this->hp=100;
    this->def=6;
    this->atk=3;
    this->chance=1;
    this->atkLen = ATTACK_LEN;
    this->isDead = false;
    this->m_target = NULL;
//    this->isPause = false;
    
    schedule(schedule_selector(MainRole::updateLoop));
}

MainRole::~MainRole()
{
    
}

MainRole* MainRole::create(const std::string& filename)
{
    MainRole *sprite = new (std::nothrow) MainRole();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void MainRole::setGameLayer(GameLayer *layer)
{
	m_gameLayer = layer;
	m_gameLayer->m_roleLayer->addChild(this);
}

void MainRole::jump(Vec2 from ,Vec2 to)
{
    if(this->isDead == true)
    {
        return;
    }
	Vec2 deltVec = CommonUtils::getVecByAngleAndLen(from, to, JUMP_STEP_LEN);
                
    MoveBy *move = MoveBy::create(JUMP_INTERVAL,Vec2(deltVec.x,deltVec.y));
    this->runAction(move);
}

void MainRole::move(Vec2 from ,Vec2 to)
{
    if(this->isDead == true)
    {
        return;
    }
	Vec2 deltVec = CommonUtils::getVecByAngleAndLen(from, to, MOVE_STEP_LEN);
                
    float spX = this->getPositionX();
    float spY = this->getPositionY();
    this->setPosition(spX + deltVec.x, spY + deltVec.y);
}

void MainRole::attack()
{
    if(this->isDead == true)
    {
        return;
    }
    
    if(this->m_target != NULL)
    {
        Vec2 monsterPos = m_target->getPosition();
        
        Vec2 rolePos = this->getPosition();
        float distance1 = rolePos.distance(monsterPos);
        if(distance1 < atkLen)
        {
            m_target->hp -= 10;
            if(m_target->hp <= 0)
            {
                auto fadeout = CCFadeOut::create(1.5);
                m_target->runAction(fadeout);
            }
            
            {
                __String * hpValue = __String::createWithFormat("怪物生命:%d",m_target->hp);
                m_gameLayer->monsterHP->setString(hpValue->getCString());
            }
        }
        else
        {
            //向目标移动一小段距离
        }
    }
	Blink * blink = Blink::create(1.0f, 5);
    this->runAction(blink);
}

void MainRole::updateLoop(float delta)
{
    if(this->hp <= 0 && this->isDead == false)
    {
        this->isDead = true;
        this->setColor(Color3B(128, 128, 128));
        
        Director::getInstance()->replaceScene(FailLayer::createScene());
        
    }
}

void MainRole::setTarget(Monster * monster)
{
    if(this->m_target != monster)
    {
        if(this->m_target != NULL)
        {
            //颜色设置回去
            this->m_target->setColor(Color3B(255,255,255));
        }
        this->m_target = monster;
        this->m_target->setColor(Color3B::GREEN);
        
        m_gameLayer->monsterHP->setVisible(true);
        
        __String * hpValue = __String::createWithFormat("怪物生命:%d",m_target->hp);
        m_gameLayer->monsterHP->setString(hpValue->getCString());
    }
    
}

//void MainRole::pause()
//{
//    isPause = true;
//}
//
//void MainRole::resume()
//{
//    isPause = false;
//}