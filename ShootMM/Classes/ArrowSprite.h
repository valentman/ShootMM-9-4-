/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: ArrowSprite.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-7-11.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__ArrowSprite__
#define __Shoot__ArrowSprite__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;


class ArrowSprite : public CCNode, public CCTargetedTouchDelegate
{
public:
    ArrowSprite(void);              // 构造函数
    virtual ~ArrowSprite(void);     // 析构函数
    
    virtual void onEnter();
    virtual void onExit();
};


#endif /* defined(__Shoot__ArrowSprite__) */
