/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: StarSprite.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-7-19.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/
#ifndef __Shoot__StarSprite__
#define __Shoot__StarSprite__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;


class StarSprite : public CCNode, public CCTargetedTouchDelegate
{
public:
    StarSprite(void);              // 构造函数
    virtual ~StarSprite(void);     // 析构函数
    
    virtual void onEnter();
    virtual void onExit();
};



#endif /* defined(__Shoot__StarSprite__) */
