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
    int exW;
    int _desW;
    
    int preFrameStepW;
    
    bool exflag;
    
    Image * _srcImg;
    Image * desImg;
    
    Vec2 circleP[3];
    bool flag;
    
    float ttt;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ImageExpand);
    
    Image* createEmptyImage(float w,float h);
    
    void setImage(Sprite * sp,Image * img);
    
    Image* sprite2image(Sprite * sp);
    void transformImage(Image * src,Image * des);
    void transformImageSprite(Sprite * sp);
    int scanStartX(int scanLineIdx);
    int scanLenX(int scanLineIdx);
    
};

#endif // __IMAGE_EXPAND_LAYER_H__
