/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: WeaponNotEnoughLayer.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-7-27.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__WeaponNotEnoughLayer__
#define __Shoot__WeaponNotEnoughLayer__

#include <iostream>
#include "cocos-ext.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace extension;

class WeaponNotEnoughLayer: public CCLayer
{
public:
    virtual void onExit();
    virtual bool init();
    
    void initBackgroundAndButton();
    void transferValueToWeaponNELayer(int pSceneNo,int kTagOfProps);
    void menuCloseCallback(CCObject* pSender);
    void menuPurchaseWeapon(CCObject* pSender);
    void setTouchTime();
    
    
    CREATE_FUNC(WeaponNotEnoughLayer);
private:
    CCSize winSize;
    CCControlButton* goToMallButton;
    CCControlButton* giveUpButton;
    int touchTime;
    
};




#endif /* defined(__Shoot__WeaponNotEnoughLayer__) */
