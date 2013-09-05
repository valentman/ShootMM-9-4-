/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: PromptLayer.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-27.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__PromptLayer__
#define __Shoot__PromptLayer__

#include "cocos-ext.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace extension;

class PromptLayer:public CCLayer
{
public:
    virtual bool init();
    virtual void onExit();
    void menuCloseCallback(CCObject* pSender);
    void transferPromotedInfo(int pSceneNumber,int levelGrade,int isSuccess,int integration,int shootNumber,int shootedNumber);
    
    //提示文字函数
    void showNextLevel(int levelGrade,int integration); //成功晋级哪个场多少级
    void showShootResult(int shoot,int shooted); //发射了多少次，命中多少次
    void showGoodLuck(int integration);//恭喜过关，将在多少积分后再次过关
    void removeLabels();  //移除所有标签对象
    
    CREATE_FUNC(PromptLayer);
private:
    int m_pSceneNumber;
    int touchTime;
    int isFailed;
    CCLabelTTF* showNextLevelLabel;
    CCLabelTTF* showGainedPrizeLabel;
    CCLabelTTF* showShootResultLabel;
    CCLabelTTF* showGoodLuckLabel1;
    CCLabelTTF* showGoodLuckLabel;
    CCMenuItemImage* nextLevelButton;
    CCMenuItemImage* backToMenuButton;
    CCMenuItemImage* goShopButton;
    CCArray* redBallnoonShooted;
    CCArray* noShooted;
    CCSprite* background;
    CCSize winSize;
    
};




#endif /* defined(__Shoot__PromptLayer__) */
