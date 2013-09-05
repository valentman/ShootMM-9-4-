/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: FireworkSprite.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-22.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__FireworkSprite__
#define __Shoot__FireworkSprite__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;


class FireworkSprite : public CCNode, public CCTargetedTouchDelegate
{
public:
    FireworkSprite(void);              // 构造函数
    virtual ~FireworkSprite(void);     // 析构函数
    
    virtual void onEnter();
    virtual void onExit();
};




#endif /* defined(__Shoot__FireworkSprite__) */
