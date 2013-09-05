/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: DartSprite.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-13.
 
 Description: 
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__DartSprite__
#define __Shoot__DartSprite__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;

class DartSprite : public CCNode, public CCTargetedTouchDelegate
{
public:
    DartSprite(void);              // 构造函数
    virtual ~DartSprite(void);     // 析构函数
    
    virtual void onEnter();
    virtual void onExit();
    
    
    
    
};



#endif /* defined(__Shoot__DartSprite__) */
