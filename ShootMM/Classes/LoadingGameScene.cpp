/*******************************************************************

Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.

Filename: LoadingGameScene.cpp

ProjectName: 射你妹

Author: P.Joe     Version: 1.0     Date: 13-6-27.

Description: 作为启动页面和选关页面之间的一个过渡页面，但在过渡页面中做了两件事：
                1.检测网络连接状况
                2.有网络则连接服务器，取回相关数据信息

FunctionList:
                1.过渡函数
                void timerStep();
 
                2.检测网络
                void connectNetwork();
 
                3.跳转
                void switchToMenuScene();
 
 History: update 8.20 delete Network()


********************************************************************/

#include "LoadingGameScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "UserData.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* LoadingGameScene::scene()
{
    CCScene *scene = CCScene::create();
    
    LoadingGameScene *layer = LoadingGameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}


void LoadingGameScene::onExit()
{
    CCLayer::onExit();
    CCLOG("~~~~~~~~~~~~~~~~LoadingGameScene:onExit()~~~~~~~~~~~~~~~~~**/");
}


// on "init" you need to initialize your instance
bool LoadingGameScene::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCLOG("/**~~~~~~~~~~~~~~~~LoadingGameScene:init()~~~~~~~~~~~~~~~~~");
    
    size = CCDirector::sharedDirector()->getVisibleSize();
    
    //判断是iPhone5还是iPhone4、4s，适配不同的背景图片。
    if (size.width > 960) {
        bgSprite = CCSprite::create("ZF_Shoot_welcome1.png");
    }
    else
    {
        bgSprite = CCSprite::create("ZF_Shoot_welcome2.png");
    }
    bgSprite->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(bgSprite, 0);
    
    //Loading字样
    CCLabelTTF* pLabel = CCLabelTTF::create("Loading...", "Thonburi", 34);
    pLabel->setPosition( ccp(size.width / 2, 120) );
    pLabel->setColor(ccBLACK);
    this->addChild(pLabel, 1,kLabelTag);
    
    
    
    //数据库数据的初始化
    UserData userData;
    string path = CCFileUtils::sharedFileUtils()->getWritablePath()+"mySqlite.db";
    
    int flag = access(path.c_str(), 0);
    if (flag != 0) {
        userData.init();
    }

    
    timeNo = 0;
    this->schedule(schedule_selector(LoadingGameScene::timerStep), 0.5f);
    
    
    
    return true;
}


//过渡函数
void LoadingGameScene::timerStep()
{
    timeNo++;
    if (timeNo > 5) {
        this->scheduleOnce(schedule_selector(LoadingGameScene::switchToMenuScene), 1.0f);
    }
}


//跳转到选关界面
void LoadingGameScene::switchToMenuScene()
{
    CCTransitionCrossFade* transition = CCTransitionCrossFade::create(0.5, MenuScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}








