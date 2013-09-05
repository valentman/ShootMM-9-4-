/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: DartSprite.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-13.
 
 Description: 
 
 FunctionList:
 
 
*******************************************************/


#include "DartSprite.h"

DartSprite::DartSprite()
{
    CCLog("DartSprite:()");
}
DartSprite:: ~DartSprite()
{
     CCLog("DartSprite:().~");
}
void DartSprite::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(80, 40));
    CCSprite* dartSprite = CCSprite::create("ZF_Shoot_Prop_fireWeapon.png");
    CCScaleTo* scaleTo1 = CCScaleTo::create(1, 1.1);
    CCScaleTo* scaleTo2 = CCScaleTo::create(1.1, 1);
    CCSequence* sequence = CCSequence::create(scaleTo1,scaleTo2,NULL);
    CCActionInterval* action = CCRepeatForever::create(sequence);
    dartSprite->runAction(action);
    addChild(dartSprite);
}

void DartSprite::onExit()
{
    
}

