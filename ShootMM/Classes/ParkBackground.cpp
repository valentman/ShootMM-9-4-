/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: ParkBackground.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-8-14.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#include "ParkBackground.h"


ParkBackground::ParkBackground()
{
    
}

ParkBackground:: ~ParkBackground()
{
    
}

void ParkBackground::onEnter()
{
    CCNode::onEnter();
    winSize = CCDirector::sharedDirector()->getVisibleSize();
    parkBackground = CCSprite::create("ZF_Shoot_GameScene_BackgroundPark.png");
    parkBackgroundSky = CCSprite::create("ZF_Shoot_GameScene_BackgroundParkSky.png");
    cloud1 = CCSprite::create("ZF_Shoot_GameScene_BackgroundParkCloud1.png");
    cloud2 = CCSprite::create("ZF_Shoot_GameScene_BackgroundParkCloud2.png");
    cloud3 = CCSprite::create("ZF_Shoot_GameScene_BackgroundParkCloud3.png");
    parkBackground->setAnchorPoint(CCPointMake(0.5, 0));
    parkBackground->setPosition(CCPointMake(winSize.width/2, 0));
    parkBackgroundSky->setAnchorPoint(CCPointMake(0.5, 1));
    parkBackgroundSky->setPosition(CCPointMake(winSize.width/2, winSize.height));
    cloud1->setPosition(CCPointMake(400, winSize.height-50));
    cloud2->setPosition(CCPointMake(600, winSize.height-100));
    cloud3->setPosition(CCPointMake(200, winSize.height-150));
    
    addChild(parkBackground,2);
    addChild(parkBackgroundSky,1);
    parkBackgroundSky->addChild(cloud1);
    parkBackgroundSky->addChild(cloud2);
    parkBackgroundSky->addChild(cloud3);
    
    this->schedule(schedule_selector(ParkBackground::addCloud), 1.0f/60.0f);
    
}
void ParkBackground::onExit()
{
    
}


void ParkBackground::addCloud()
{
    float speed1 = 0.3;
    if(cloud1->getPosition().x < -50)
    {
        cloud1->setPositionX(winSize.width+150);
    }
    else
    {
        cloud1->setPositionX(cloud1->getPosition().x-speed1*3);
    }
    
    if(cloud2->getPosition().x>winSize.width+150)
    {
        cloud2->setPositionX(0-50);
    }
    else
    {
        cloud2->setPositionX(cloud2->getPosition().x-speed1);
    }
    
    if(cloud3->getPosition().x>winSize.width+150)
    {
        cloud3->setPositionX(0-50);
    }
    else
    {
        
        cloud3->setPositionX(cloud3->getPosition().x-speed1*2);
    }
}