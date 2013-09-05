/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: ParkBackground.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-8-14.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__ParkBackground__
#define __Shoot__ParkBackground__

#include <iostream>


#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;

class ParkBackground : public CCNode
{
public:
    ParkBackground(void);              // 构造函数
    virtual ~ParkBackground(void);     // 析构函数
    
    virtual void onEnter();
    virtual void onExit();
    
    void addCloud();
    
private:
    CCSprite* parkBackground;
    CCSprite* parkBackgroundSky;
    CCSprite* cloud1;
    CCSprite* cloud2;
    CCSprite* cloud3;
    CCSize winSize;
};



#endif /* defined(__Shoot__ParkBackground__) */
