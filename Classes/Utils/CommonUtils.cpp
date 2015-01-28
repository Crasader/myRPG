//
//  CommonUtils.cpp
//  jxtczclient3.0
//
//  Created by liuxuandi on 14-5-12.
//
//

#include "CommonUtils.h"



int CommonUtils::bigImageCount = 0;
int CommonUtils::updateBigImageCount = 0;

long long CommonUtils::currentTimeNow()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    
    long long ret1 = (long long)tv.tv_sec * 1000;
    long long ret2 = tv.tv_usec / 1000;
    
    long long ret = ret1 + ret2;
    return ret;
}

long long CommonUtils::currentTimeMicroSeconds()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    
    long long ret1 = (long long)tv.tv_sec * 1000 * 1000;
    long long ret2 = tv.tv_usec;
    
    long long ret = ret1 + ret2;
    return ret;
}


float CommonUtils::getPositionDivByLen(float parentLen,float childLen,int childCount,int childIndex)
{
    return ((parentLen - (childLen * childCount)) / (childCount + 1)) * childIndex  + (childLen / 2) + (childIndex -1) * childLen;
}

int CommonUtils::getImagePiexlDataOffset(Point p,Node * node,Image * image)
{

    Point pointInNode = node->convertToNodeSpace(p);
    
    Point pointInImage = Point(pointInNode.x, image->getHeight() - pointInNode.y);

    int w = image->getWidth();
//    int h = image->getHeight();
    
    int iXInImage = pointInImage.x;
    int iYInImage = pointInImage.y;
    
    if(iXInImage < 0 || iXInImage > image->getWidth() || iYInImage < 0 || iYInImage > image->getWidth())
    {
        return -1;
    }
    int imageOffset = (w * iYInImage + iXInImage);
    return imageOffset;
}

bool CommonUtils::isTouchInRealImagePiexl(Point p,Node * node,Image * image)
{
    int imageOffset = getImagePiexlDataOffset(p,node,image);
    if(imageOffset < 0)
    {
        return false;
    }
    unsigned char * data = image->getData();
//    int bitCountPerPiexl = image->getBitPerPixel();
    Texture2D::PixelFormat piexFormat =  image->getRenderFormat();
    
    if(piexFormat == Texture2D::PixelFormat::RGBA8888)
    {
        unsigned int *RGBA8888Data = (unsigned int *)data;
        unsigned int * touchPiexlData_ = RGBA8888Data + imageOffset;
        unsigned int piexlValue_ = *touchPiexlData_;
        
        unsigned char r = (piexlValue_ ) >> 24;
        unsigned char g = (piexlValue_ << 8) >> 24;
        unsigned char b = (piexlValue_ << 16) >> 24;
        unsigned char alph = (piexlValue_ << 24) >> 24;
        
        CCLOG("CommonUtils::isTouchInRealImagePiexl r = %d g = %d b = %d alph = %d" ,r,g,b,alph);
        if(r > 0)
        {
            return true;
        }
    }
    return  false;
    
}

void CommonUtils::saveFile(char *data, const char *fileName)
{
    char * fileData = data;
    std::string path = FileUtils::getInstance()->getWritablePath() + fileName;
    CCLOG("CommonUtils::saveFile path = %s",path.c_str());
    
    FILE * file = fopen(path.c_str(), "w");
    if (file)
    {
        fputs(fileData, file);
        fclose(file);
        CCLOG("CommonUtils::saveFile Save Succeed");
    }
    else
    {
        CCLOG("CommonUtils::saveFile Save Failed");
    }
}
void CommonUtils::deleteFile(const char *fileName)
{
    std::string path = FileUtils::getInstance()->getWritablePath() + fileName;
    
    CCLOG("CommonUtils::deleteFile path = %s",path.c_str());
    
    if(remove(path.c_str())==0)
    {
        CCLOG("CommonUtils::deleteFile Delete Succeed");
    }
    else
    {
        CCLOG("CommonUtils::deleteFile Delete Failed");
        CCLOG("CommonUtils::%d",errno);
    }
    
}
char* CommonUtils::getNameByURL(const char *theURL)
{
    char * result = (char*)theURL;
    char * result_ = NULL;
    
    int strLen= (int)strlen(theURL);
    
    int idx = 0;
    
    while (idx < strLen)
    {
        if(result[idx] == '/')
        {
            result_= result + idx + 1;
        }
        idx++;
    }
    return result_;
}

Vec2 CommonUtils::getVecByAngleAndLen(Vec2 from,Vec2 to,float len)
{
    float x_len = to.x - from.x;
    float y_len = -(to.y - from.y);

    
    float delt_y = sqrtf((float)len * (float)len * y_len * y_len / (x_len * x_len + y_len * y_len));
    float delt_x = x_len * delt_y  / y_len;
    
    if(x_len > 0)
    {
        delt_x = abs(delt_x);
    }
    else
    {
        delt_x = -abs(delt_x);
    }
    
    if(y_len > 0)
    {
        delt_y = abs(delt_y);
    }
    else
    {
        delt_y = -abs(delt_y);
    }
    return Vec2(delt_x, delt_y);
}

void CommonUtils::createSpriteFrameCacheByFile(const char * plistName,const char * imageName)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistName,imageName);
}


Vector<SpriteFrame*> CommonUtils::getSpriteFrameByPlist(const char * name)
{
    Vector<SpriteFrame*> frames;
    
//    __String * skillPlistFileName = __String::createWithFormat("effect/%s/%s.plist",name,name);
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(name);
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fullPath);
    
    ValueMap& framesDict = dict["frames"].asValueMap();
    int format = 0;
    
    // get the format
    if (dict.find("metadata") != dict.end())
    {
        ValueMap& metadataDict = dict["metadata"].asValueMap();
        format = metadataDict["format"].asInt();
    }
    
    // check the format
    CCASSERT(format >=0 && format <= 3, "format is not supported for SpriteFrameCache CommonUtils::getSpriteFrameByPlist:");
    
    if(format != 2)
    {
        return frames;
    }
    
    std::vector<std::string> orderName;
    
    for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
    {
        std::string spriteFrameName = iter->first;
        orderName.push_back(spriteFrameName);
    }
    
    int count = orderName.size();
    
    //冒泡法排序
    for(int i=0;i<count; i++)
    {
        int a = getNumberOfName(orderName.at(i));
        for(int j = i + 1; j < count; j++)
        {
            int b = getNumberOfName(orderName.at(j));
            if(a > b)
            {
                int t = a;
                a = b;
                b = t;
                
                std::swap(orderName[i],orderName[j]);
            }
        }
    }
    
    for(auto &e :orderName)
    {
        SpriteFrame* sf = CCSpriteFrameCache::getInstance()->getSpriteFrameByName(e);
        frames.pushBack(sf);
    }
    
    return frames;
}




int CommonUtils::getNumberOfName(const std::string name)
{
    char numStr[8];
    const char * c = name.c_str();
    int start = 0;
    int end = 0;
    int i = 0;
    while(c[i++] != 0 )
    {
        if(start == 0)
        {
            if(c[i] > '0' && c[i] <= '9')
            {
                start = i;
            }
        }
        if(start > 0)
        {
            if(!(c[i] >= '0' && c[i] <= '9'))
            {
                end = i;
                break;
            }
        }
    }
    
    memset(numStr,0,sizeof(numStr));
    
    int len = end - start;
    if(len > sizeof(numStr))
    {
        len = sizeof(numStr);
    }
    memcpy(numStr, c+start, len);
    
    int ret  = atoi(numStr);
    return ret;
}



int CommonUtils::RandAmongMinMax(int dwMin, int dwMax )
{
	if ( dwMin == dwMax )
		return dwMax;
    
	if ( dwMin > dwMax )
	{
		return dwMin;
	}
    
	int  dwValue = dwMax - dwMin ;
    
	return dwMin + abs(( ( rand() << 15 ) | ( rand() ) ) % dwValue);
}


__String * CommonUtils::getOfflineTimeText(int offlineTime)
{
    __String * str = NULL;
    int loginTime = (int)(CommonUtils::currentTimeNow()/1000 - offlineTime);
    if (loginTime < 60)
    {
        str = __String::createWithFormat("%d秒前",loginTime);
    }
    else if (loginTime <60*60)
    {
        str = __String::createWithFormat("%d分钟前",loginTime/60);
    }
    else if (loginTime < 60*60*24)
    {
        str = __String::createWithFormat("%d小时前",loginTime/(60*60));
    }
    else if (loginTime < 60*60*24*30)
    {
        str = __String::createWithFormat("%d天前",loginTime/(60*60*24));
    }
    else
    {
        str = __String::createWithFormat("%d月前",loginTime/(60*60*24*30));
    }
    return str;
}
