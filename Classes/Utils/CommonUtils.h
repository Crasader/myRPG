//
//  CommonUtils.h
//  myRPG
//
//  Created by Sandy Liu on 15-1-29.
//
//

#ifndef CommonUtils_h
#define CommonUtils_h
#include "iostream"
#include "cocos2d.h"

#include "CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCSGUIReader.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d::extension;
using namespace cocostudio;
using namespace std;

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512


class CommonUtils
{
public:
    
    static int bigImageCount;
    static int updateBigImageCount;
    
    //距离1970年1月1日的毫秒数
    static long long currentTimeNow();
    //距离1970年1月1日的微秒数
    static long long currentTimeMicroSeconds();
    //在parentLen里面等分的放入childCount个childLen，计算第childIndex个child的位置的中心点
    static float getPositionDivByLen(float parentLen,float childLen,int childCount,int childIndex);

    static int getImagePiexlDataOffset(cocos2d::Point p,Node * node,Image * image);
    static bool isTouchInRealImagePiexl(cocos2d::Point p,Node * node,Image * image);
    
    static void saveFile(char *data, const char *fileName);
    static void deleteFile(const char *fileName);
    static char* getNameByURL(const char *theURL);
    
    static Vec2 getVecByAngleAndLen(Vec2 from,Vec2 to,float len);
    /**
     *获取掉落的物品图标精灵
     *第一个参数是物品的模版ID，第二个参数是显示的尺寸
     */
    static Sprite * getItemIcon(int itemModelID, cocos2d::Size size);
    static Sprite * getItemIcon(int itemModelID);
    
    /**
     *获取阵型的图片创建的精灵
     *参数为阵型的modelID
     */
    static Sprite * getFormationIcon(int formationModelID);
    
    static int getCardQuality(int cardMaxLv);
    static int getCardQualityByModelID(int cardModelID);
    
    
    /**
    *根据NPCID得到NPC名字
     */
    static __String* getNamebyNPCId(int NpcId);
    static void listItemRunMoveAction(Node * listItem,int idx);
    
    /**
     
    static bool createDirectory(const char *path);
    static string getFileMD5(const char *pszFile);
    static bool UnzipFile(string fName,string outPath);
    
    
    /**
     *从一个文件名里面获取最后的数字（如果有扩展名，则截止到“.”之前）
     */
    static int getNumberOfName(const std::string name);
    
    /**
     *创建精灵帧，需要和releaseSpriteFrames()对应,否则会导致内存没有释放
     */
    static void createSpriteFrameCacheByFile(const char * plistName,const char * imageName);
    
    /**
     *获取精灵帧
     */
    static Vector<SpriteFrame*> getSpriteFrameByPlist(const char * name);


    
    /**
     *显示魂石不足，跳转充值页面的提示对话框
     */
    static void showTurnToRechargeDialog(Layer * parentLayer);
    
    /**
     *显示魂石不足，跳转充值页面的提示对话框，对应按钮的回调处理
     */
    void onConfirmBtnClick();
    void onCanclemBtnClick();
    
    static int RandAmongMinMax(int dwMin, int dwMax );
    
    
    /**
     *创建显示提示信息的特效并添加到页面上
     */
    static void showItemTips(Layer * parentLayer, int itemModelID);
    static void showFormationTips(Layer * parentLayer, int formationModelID);

    static void initBigImage();
    static void createBigImageCallBack(Texture2D * taxture2d);
    
    static void updateBigImage(int newModelID,int oldModelID);    
    static void updateBigImageCallBack(Texture2D * taxture2d);
    
    static void removeBigImage(int oldModelID);
    static void addBigImage(int newModelID);    
    static void addBigImageCallBack(Texture2D * taxture2d);
    
    
    static __String * getOfflineTimeText(int offlineTime);//参数为描述
};
#endif
