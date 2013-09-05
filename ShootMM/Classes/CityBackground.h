/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: CityBackground.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-8-13.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__CityBackground__
#define __Shoot__CityBackground__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;

class CityBackground : public CCNode
{
public:
    CityBackground(void);              // 构造函数
    virtual ~CityBackground(void);     // 析构函数
    
    virtual void onEnter();
    virtual void onExit();
    
    void addCloud();
    
private:
    CCSprite* cityBackground;
    CCSprite* cityBackgroundSky;
    CCSprite* cloud1;
    CCSprite* cloud2;
    CCSprite* cloud3;
    CCSize winSize;
};





#endif /* defined(__Shoot__CityBackground__) */
