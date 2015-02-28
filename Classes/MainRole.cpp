#include "MainRole.h"
#include "Utils/CommonUtils.h"
#include "FailLayer.h"
#include "GameConst.h"

#define JUMP_STEP_LEN (100)
#define MOVE_STEP_LEN (2.9)
#define JUMP_INTERVAL (0.3)
#define ATTACK_LEN (80)
#define ATTACK_INTERVAL (1)
#define JUMP_USE_MP (35.0)


MainRole::MainRole()
{
	this->lv=1;
    this->hp=100;
    this->mp = 100.0;
    this->def=6;
    this->atk=25;
    this->chance=1;
    this->atkLen = ATTACK_LEN;
    this->mpRecover = 6.5;
    this->isDead = false;
    this->isAtk = false;
    this->atkInterval = ATTACK_INTERVAL;
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
    if(this->isDead == true || isAtk == true)
    {
        return;
    }
    
    float remainMP = mp - JUMP_USE_MP;
    if(remainMP < 0 )
    {
        //提示魔法值不足
        return;
    }
    mp = remainMP;
    
//    __String * mpValue = __String::createWithFormat("魔法值:%d",(int)floor(mp));
//    m_gameLayer->roleMP->setString(mpValue->getCString());
    
	Vec2 deltVec = CommonUtils::getVecByAngleAndLen(from, to, JUMP_STEP_LEN);
                
    MoveBy *move = MoveBy::create(JUMP_INTERVAL,Vec2(deltVec.x,deltVec.y));
    this->runAction(move);
}

void MainRole::move(Vec2 from ,Vec2 to)
{
    if(this->isDead == true || isAtk == true)
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
    if(this->isDead == true || isAtk == true)
    {
        return;
    }
    
    isAtk = true;
        
    scheduleOnce(schedule_selector(MainRole::resetAtkStatus),atkInterval);

    if(this->m_target != NULL && m_target->isDead == false)
    {
        Vec2 monsterPos = m_target->getPosition();
        
        Vec2 rolePos = this->getPosition();
        float distance1 = rolePos.distance(monsterPos);
        if(distance1 < atkLen)
        {
            m_target->attacked(atk);

        }
        else
        {
            //向目标移动一小段距离
        }
    }
    
    Vec2 atkDir = CommonUtils::getVecByAngleAndLen(getPosition(), m_target->getPosition(), ATTACK_LEN);
    
//    TintBy * tint = TintBy::create(1.0f, 255, 0, 0);
//    Sequence * reverseseq = Sequence::create(tint,tint->reverse(),NULL);
//    this->runAction(reverseseq);
    
    
    ParticleSystem* ps = ParticleExplosion::create();
    ps->setTexture(Director::getInstance()->getTextureCache()->addImage("skill.png"));
    ps->setPosition(Point(this->getPosition().x +  this->getContentSize().width / 2,this->getPosition().y + this->getContentSize().height));
    m_gameLayer->m_skillLayer->addChild(ps);
    ps->setLife(0.03);
    ps->setEmissionRate(250);
    ps->setSpeed(400);
    ps->setAutoRemoveOnFinish(true);
}

void MainRole::updateLoop(float delta)
{
    if(mp < 100.0)
    {
        float incMp = mpRecover * delta;
        mp += incMp;
    }
    else
    {
        mp = 100.0;
    }
}

void MainRole::resetAtkStatus(float delta)
{
    isAtk = false;
}

void MainRole::setTarget(Monster * monster)
{
    if(this->m_target != monster)
    {
        if(this->m_target != NULL)
        {
            //颜色设置回去
            this->m_target->setNoFocus();
        }
        this->m_target = monster;
        this->m_target->setFocus();
        
        m_gameLayer->monsterHP->setVisible(true);
        
        __String * hpValue = __String::createWithFormat("怪物生命:%d",m_target->hp);
        m_gameLayer->monsterHP->setString(hpValue->getCString());
    }
    
}

void MainRole::attacked(int damageValue)
{
    if( this->isDead == true)
    {
        return;
    }
    this->hp -= 20;
    if(this->hp <= 0 )
    {
        this->isDead = true;
        this->hp = 0;
        this->setColor(Color3B(128, 128, 128));
        
        Director::getInstance()->replaceScene(FailLayer::createScene());
        
    }
    else
    {
//        TintBy * tintby = TintBy::create(1.5, 20, 0, 0);
//        Sequence * seq = Sequence::create(tintby,tintby->reverse(),NULL);
        
        auto blink = CCBlink::create(0.5,3);
        this->runAction(blink);
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