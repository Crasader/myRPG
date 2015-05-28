#ifndef __IMAGE_EXPAND_LAYER_H__
#define __IMAGE_EXPAND_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;
class ImageExpand : public ActionInterval
{
public:
    /** creates the action */
    static ImageExpand* create(float duration,  int desW);
    
    //
    // Overrides
    //
    virtual ImageExpand* clone() const override;
    virtual ImageExpand* reverse(void) const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    ImageExpand() {}
    virtual ~ImageExpand() {}
    
    /** initializes the action */
    bool initWithDuration(float duration, int desW);
    
protected:
//    Vec2 _positionDelta;
//    Vec2 _startPosition;
//    Vec2 _previousPosition;
    
    int exW;
    int _desW;
    
    
    float inTime;
    float timeCount;
    int preFrameStepW;
    
    bool exflag;
    
    Image * srcImg;
    Image * desImg;
    
    Vec2 circleP[3];
    bool flag;
    void testFunc();
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ImageExpand);
    
    
    //////////
    
    Sprite * bgSp1;
    RenderTexture * pRTex;
    Texture2D * texture;
    
    
    
    
    Image* createEmptyImage(float w,float h);
    
    void setImage(Sprite * sp,Image * img);
    
    
    Image* sprite2image(Sprite * sp);
    void transformImage(Image * src,Image * des);
    void transformImageSprite(Sprite * sp);
    
    int scanStartX(int scanLineIdx);
    
    int scanLenX(int scanLineIdx);
    
  
    
};

#endif // __IMAGE_EXPAND_LAYER_H__
