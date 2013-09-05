/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: ArrowSprite.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-7-11.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#include "ArrowSprite.h"

ArrowSprite::ArrowSprite()
{
    CCLog("ArrowSprite:()");
}
ArrowSprite:: ~ArrowSprite()
{
    CCLog("ArrowSprite:().~");
}


void ArrowSprite::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(80, 40));
    CCSprite* arrowSprite = CCSprite::create("ZF_Shoot_Prop_hdWeapon.png");
    arrowSprite->setScale(0.7);
    CCScaleTo* scaleTo1 = CCScaleTo::create(0.7, 0.75);
    CCScaleTo* scaleTo2 = CCScaleTo::create(0.75, 0.7);
    CCSequence* sequence = CCSequence::create(scaleTo1,scaleTo2,NULL);
    CCActionInterval* action = CCRepeatForever::create(sequence);
    arrowSprite->runAction(action);
    addChild(arrowSprite);
}

void ArrowSprite::onExit()
{
    
}