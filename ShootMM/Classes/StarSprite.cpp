/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: StarSprite.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-7-19.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#include "StarSprite.h"

StarSprite::StarSprite()
{
    CCLog("StarSprite:()");
}
StarSprite:: ~StarSprite()
{
    CCLog("StarSprite:().~");
}


void StarSprite::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(80, 40));
    CCSprite* arrowSprite = CCSprite::create("ZF_Shoot_Prop_hjtWeapon.png");
    CCScaleTo* scaleTo1 = CCScaleTo::create(1, 1.1);
    CCScaleTo* scaleTo2 = CCScaleTo::create(1.1, 1);
    CCSequence* sequence = CCSequence::create(scaleTo1,scaleTo2,NULL);
    CCActionInterval* action = CCRepeatForever::create(sequence);
    arrowSprite->runAction(action);
    addChild(arrowSprite);
}

void StarSprite::onExit()
{
    
}