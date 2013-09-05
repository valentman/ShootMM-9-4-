/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: BossBallnoonSprite.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-8-1.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__BossBallnoonSprite__
#define __Shoot__BossBallnoonSprite__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;

class BossBallnoonSprite : public CCNode, public CCTargetedTouchDelegate
{
public:
    BossBallnoonSprite(const char *profileName);              // 构造函数
    virtual ~BossBallnoonSprite(void);     // 析构函数
    

    virtual void onEnter();
    virtual void onExit();
    void playEffects();
    void pauseEffects();
    void stopEffects();
    
    void updateLifeSpanOfBoss(float kScale);
private:
    CCSprite* bossBallnoonSprite;
    CCSprite* green;
    CCSprite* red;
    
};




#endif /* defined(__Shoot__BossBallnoonSprite__) */
