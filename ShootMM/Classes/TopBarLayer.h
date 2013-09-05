/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: TopBarLayer.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-7-8.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__TopBarLayer__
#define __Shoot__TopBarLayer__

#include <iostream>
#include "cocos-ext.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace extension;

class TopBarLayer:public CCLayer
{
public:
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    void initTopBarBg();
    void initSysInfo();
    void initLabels();
    
    void updateScore(int p_Score);
    void showScore(int p_Score);
    void updateTopTargetScore(int p_TargetScore,int levelGrade);
    void setTopTargetScore(int p_TargetScore,int levelGrade);
    void showScoreCompleteEffects();
    void menuCloseCallBack(CCObject* pSender);
    void updateDynamicInfo();
    void getDynamicInfoArrayFromServer();
    void getDynamicInfoFromArray();
    void removeOldInfoLabel();
    void showNewDynamicInfoLabel();
    
    
    //武器切换、数量增减函数
    void initWeaponButton();
    void switchWeapon(CCObject *sender,CCControlEvent controlEvent);
    
    void initNumberOfWeapon(int numberOfWeapon1,int numberOfWeapon2,int numberOfWeapon3,int numberOfWeapon4);
    void updateNumberOfWeapon(int kTag,int numberOfWeapon);
    
    CREATE_FUNC(TopBarLayer);
    
    //武器按钮
    CCControlButton *weaponButton1;
    
    CCControlButton *weaponButton2;
    
    CCControlButton *weaponButton3;
    
    CCControlButton *weaponButton4;
    
    CCMenu* pMenu;
private:
    CCArray* systemInfo;
    int systemInfoIndex;
    CCLabelTTF* scoreLabel;
    CCLabelTTF* dynamicInfoLable;
    CCLabelTTF* targetScoreLabel;
    CCLabelTTF* levelgradeLabel;
    CCString *Score;
    CCSize size;
    CCSprite* topBarBg1;
    CCSprite* topBarBg2;
    
    CCPoint numberPoint;
    
    
    //武器数量标签
    CCLabelTTF* labelOfWeapon1;
    
    CCLabelTTF* labelOfWeapon2;
    
    CCLabelTTF* labelOfWeapon3;
    
    CCLabelTTF* labelOfWeapon4;
    
    CCMenuItemImage *pPauseItem;
    CCMenuItemImage *pPlayItem;
    
    //武器数量变量
    int numberOfWeapon1,numberOfWeapon2,numberOfWeapon3,numberOfWeapon4;
    
    int isPauseed;
    
};

#endif /* defined(__Shoot__TopBarLayer__) */
