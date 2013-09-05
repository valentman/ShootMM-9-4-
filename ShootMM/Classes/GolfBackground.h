/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: GolfBackground.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-8-14.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__GolfBackground__
#define __Shoot__GolfBackground__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;

class GolfBackground : public CCNode
{
public:
    GolfBackground(void);              // 构造函数
    virtual ~GolfBackground(void);     // 析构函数
    
    virtual void onEnter();
    virtual void onExit();
    
    void addCloud();
    
private:
    CCSprite* golfBackground;
    CCSprite* golfBackgroundSky;
    CCSprite* cloud1;
    CCSprite* cloud2;
    CCSprite* cloud3;
    CCSize winSize;

};

#endif /* defined(__Shoot__GolfBackground__) */
