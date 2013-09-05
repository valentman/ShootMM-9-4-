/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: GolfBackground.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-8-14.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#include "GolfBackground.h"

GolfBackground::GolfBackground()
{
    
}

GolfBackground:: ~GolfBackground()
{
    
}

void GolfBackground::onEnter()
{
    CCNode::onEnter();
    winSize = CCDirector::sharedDirector()->getVisibleSize();
    golfBackground = CCSprite::create("ZF_Shoot_GameScene_BackgroundGolf.png");
    golfBackgroundSky = CCSprite::create("ZF_Shoot_GameScene_BackgroundGolfSky.png");
    cloud1 = CCSprite::create("ZF_Shoot_GameScene_BackgroundGolfCloud1.png");
    cloud2 = CCSprite::create("ZF_Shoot_GameScene_BackgroundGolfCloud2.png");
    cloud3 = CCSprite::create("ZF_Shoot_GameScene_BackgroundGolfCloud3.png");
    golfBackground->setAnchorPoint(CCPointMake(0.5, 0));
    golfBackground->setPosition(CCPointMake(winSize.width/2, 0));
    golfBackgroundSky->setAnchorPoint(CCPointMake(0.5, 1));
    golfBackgroundSky->setPosition(CCPointMake(winSize.width/2, winSize.height));
    cloud1->setPosition(CCPointMake(400, winSize.height-70));
    cloud2->setPosition(CCPointMake(600, winSize.height-250));
    cloud3->setPosition(CCPointMake(200, winSize.height-170));
    
    addChild(golfBackground,2);
    addChild(golfBackgroundSky,1);
    golfBackgroundSky->addChild(cloud1);
    golfBackgroundSky->addChild(cloud2);
    golfBackgroundSky->addChild(cloud3);
    
    this->schedule(schedule_selector(GolfBackground::addCloud), 1.0f/60.0f);
    
}
void GolfBackground::onExit()
{
    
}


void GolfBackground::addCloud()
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