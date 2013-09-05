/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: CityBackground.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-8-13.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#include "CityBackground.h"


CityBackground::CityBackground()
{
    
}

CityBackground:: ~CityBackground()
{
    
}

void CityBackground::onEnter()
{
    CCNode::onEnter();
    winSize = CCDirector::sharedDirector()->getVisibleSize();
    cityBackground = CCSprite::create("ZF_Shoot_GameScene_BackgroundCity.png");
    cityBackgroundSky = CCSprite::create("ZF_Shoot_GameScene_BackgroundCitySky.png");
    cloud1 = CCSprite::create("ZF_Shoot_GameScene_BackgroundCityCloud1.png");
    cloud2 = CCSprite::create("ZF_Shoot_GameScene_BackgroundCityCloud2.png");
    cloud3 = CCSprite::create("ZF_Shoot_GameScene_BackgroundCityCloud3.png");
    cityBackground->setAnchorPoint(CCPointMake(0.5, 0));
    cityBackground->setPosition(CCPointMake(winSize.width/2, 0));
    cityBackgroundSky->setAnchorPoint(CCPointMake(0.5, 1));
    cityBackgroundSky->setPosition(CCPointMake(winSize.width/2, winSize.height));
    cloud1->setPosition(CCPointMake(400, winSize.height-70));
    cloud2->setPosition(CCPointMake(600, winSize.height-250));
    cloud3->setPosition(CCPointMake(200, winSize.height-170));
    
    addChild(cityBackground,2);
    addChild(cityBackgroundSky,1);
    cityBackgroundSky->addChild(cloud1);
    cityBackgroundSky->addChild(cloud2);
    cityBackgroundSky->addChild(cloud3);
    
    this->schedule(schedule_selector(CityBackground::addCloud), 1.0f/60.0f);

}
void CityBackground::onExit()
{
    
}


void CityBackground::addCloud()
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
