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
    this->skLen = 30;
    this->skStart = false;
    this->isActive = false;
    
}

Monster::~Monster()
{
    
}

void Monster::startAtk()
{
    isActive = true;
    auto draw = DrawNode::create();
    this->sp->addChild(draw);
    
    // 画10个圆，实际上是画了10个点，指定点的大小，所以看起来就是圆；
//    for( int i=0; i < 10; i++)
    {
        draw->drawDot(Vec2(this->sp->getPositionX(), this->sp->getPositionY()), this->skLen, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }
    draw->setPosition(this->sp->getPositionX(), this->sp->getContentSize().height);
    
    
    // 画多边形
//    Vec2 points[] = { Vec2(s.height/4,0), Vec2(s.width,s.height/5), Vec2(s.width/3*2,s.height) };
//    draw->drawPolygon(points, sizeof(points)/sizeof(points[0]), Color4F(1,0,0,0.5), 4, Color4F(0,0,1,1));
}