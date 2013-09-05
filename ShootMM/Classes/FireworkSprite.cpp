/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: FireworkSprite.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-22.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#include "FireworkSprite.h"


FireworkSprite::FireworkSprite()
{
    CCLog("FireworkSprite:()");
}
FireworkSprite:: ~FireworkSprite()
{
    CCLog("FireworkSprite:().~");
}

void FireworkSprite::onEnter()
{
    CCNode::onEnter();
    this->setContentSize(CCSizeMake(80, 40));
    CCSprite* fireworkSprite = CCSprite::create("ZF_Shoot_Prop_laserWeapon.png");
    fireworkSprite->setScale(0.7);
    CCScaleTo* scaleTo1 = CCScaleTo::create(0.7, 0.75);
    CCScaleTo* scaleTo2 = CCScaleTo::create(0.75, 0.7);
    CCSequence* sequence = CCSequence::create(scaleTo1,scaleTo2,NULL);
    CCActionInterval* action = CCRepeatForever::create(sequence);
    fireworkSprite->runAction(action);
    addChild(fireworkSprite);
    
//    CCSprite* boom = CCSprite::create("ZF_Shoot_GameScene_thunder1.png");
//    boom->setPosition(CCPointMake(size.width, size.height));
//    boom->setAnchorPoint(ccp(1.0f,1.0f));
//    this->addChild(boom);
//    CCAnimation* boomAnimation = CCAnimation::create();
//    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder1.png");
//    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder2.png");
//    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder3.png");
//    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder4.png");
//    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder5.png");
//    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder6.png");
//    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder7.png");
//    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder8.png");
//    boomAnimation->setDelayPerUnit(0.08f);
//    boomAnimation->setRestoreOriginalFrame(true);
//    CCAnimate* fireworkAnimate = CCAnimate::create(boomAnimation);
//    boom->runAction(fireworkAnimate);

    
    
}

void FireworkSprite::onExit()
{
    
}