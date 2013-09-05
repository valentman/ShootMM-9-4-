/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: BossBallnoonSprite.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-8-1.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#include "BossBallnoonSprite.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

BossBallnoonSprite::BossBallnoonSprite(const char *profileName)
{
    bossBallnoonSprite = CCSprite::create(profileName);
    CCLog("profileName: %s",profileName);
    //血量
    CCPoint lifespanPosition = CCPointMake(0, bossBallnoonSprite->getContentSize().height+20);
    green = CCSprite::create("ZF_Shoot_GameScene_lifespangreen.png");
    green->setAnchorPoint(ccp(0,0.5));
    green->setPosition(lifespanPosition);
    red = CCSprite::create("ZF_Shoot_GameScene_lifespanred.png");
    red->setAnchorPoint(ccp(0,0.5));
    red->setPosition(lifespanPosition);
    
    
    bossBallnoonSprite->addChild(green,2);
    bossBallnoonSprite->addChild(red,3);
    
    addChild(bossBallnoonSprite);
    CCLog("BossBallnoonSprite:()");
}
BossBallnoonSprite:: ~BossBallnoonSprite(void)
{
    CCLog("BossBallnoonSprite:().~");
}


void BossBallnoonSprite::onEnter()
{
    CCNode::onEnter();
    
    //气球的抖动
    CCActionInterval* rotate1 = CCRotateBy::create(0.2, 5);
    CCActionInterval* rotate2 = rotate1->reverse();
    CCSequence* sequence1 = CCSequence::create(rotate1,rotate2,NULL);
    
    CCActionInterval* moveToUp = CCMoveTo::create(0.2, CCPointMake(bossBallnoonSprite->getPositionX(), bossBallnoonSprite->getPositionY()+5));
    CCActionInterval* moveToDown = CCMoveTo::create(0.2, CCPointMake(bossBallnoonSprite->getPositionX(), bossBallnoonSprite->getPositionY()-5));
    CCSequence* sequence2 = CCSequence::create(moveToUp,moveToDown,NULL);
    CCRepeatForever* repeate2 = CCRepeatForever::create(sequence2);
    
    CCActionInterval* spwan = CCSpawn::create(sequence1,sequence2,NULL);
    CCRepeatForever* repeate3 = CCRepeatForever::create(spwan);
    
    bossBallnoonSprite->setAnchorPoint(ccp(0.5,0.5));
    
    bossBallnoonSprite->runAction(repeate2);
    
    
    
}


void BossBallnoonSprite::playEffects()
{
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_GameScene_Effects_boss.mp3");
    
}

void BossBallnoonSprite::pauseEffects()
{
    this->schedule(schedule_selector(BossBallnoonSprite::playEffects), 2.5f);
}


void BossBallnoonSprite::stopEffects()
{
    this->unschedule(schedule_selector(BossBallnoonSprite::playEffects));
}

void BossBallnoonSprite::onExit()
{
    CCLog("BossBallnoonSprite::onExit()");
}

void BossBallnoonSprite::updateLifeSpanOfBoss(float kScale)
{
    CCLog("scale:%f",kScale);
    red->setScaleX(kScale);
}