#include "MainRole.h"
#include "Utils/CommonUtils.h"
#include "FailLayer.h"

#define JUMP_STEP_LEN (100)
#define MOVE_STEP_LEN (2.9)
#define JUMP_INTERVAL (0.3)


MainRole::MainRole()
{
	this->lv=1;
    this->hp=100;
    this->def=6;
    this->atk=3;
    this->chance=1;
    this->isDead = false;
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
