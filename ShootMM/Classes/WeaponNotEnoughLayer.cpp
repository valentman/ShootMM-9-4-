/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: WeaponNotEnoughLayer.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-7-27.
 
 Description:
 
 FunctionList:
                void WeaponNotEnoughLayer::initBackgroundAndButton()
 
 
 *******************************************************/

#include "WeaponNotEnoughLayer.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace extension;
using namespace cocos2d;
using namespace CocosDenshion;



#pragma mark --------------- SystemInitMethod ---------------
void WeaponNotEnoughLayer::onExit()
{
    CCLayer::onExit();
    CCLog("~~~~~~~~~~~~~~~~WeaponNotEnoughLayer::onExit()~~~~~~~~~~~~~~~~~~**/");
    
}
bool WeaponNotEnoughLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCLOG("/**~~~~~~~~~~~~~~~~WeaponNotEnoughLayer:init()~~~~~~~~~~~~~~~~~");
    winSize = CCDirector::sharedDirector()->getVisibleSize();
    this->initBackgroundAndButton();
    
    this->setTouchEnabled(true);
    this->setTouchPriority(-1);
    
    return true;
}


//初始化背景图片和按钮
void WeaponNotEnoughLayer::initBackgroundAndButton()
{
    CCSprite* background = CCSprite::create("ZF_Shoot_GameScene_weaponNE.png");
    background->setPosition(CCPointMake(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(background);
    
    //添加相应的按钮
    CCScale9Sprite* buttonBackground1 = CCScale9Sprite::create("ZF_Shoot_Button_bg3.png");
    goToMallButton = CCControlButton::create(CCLabelTTF::create("Go shop","Georgia-BoldItalic", 25), buttonBackground1);
    goToMallButton->setPosition(ccp(background->getContentSize().width/4, 100));
    goToMallButton->setAnchorPoint(ccp(0.5, 0.5));
    goToMallButton->setPreferredSize(CCSizeMake(250, 100));
    goToMallButton->addTargetWithActionForControlEvents(this, cccontrol_selector(WeaponNotEnoughLayer::menuCloseCallback), CCControlEventTouchUpInside);
    goToMallButton->setTag(4);
    goToMallButton->setTouchEnabled(true);
    background->addChild(goToMallButton,1);
    
    CCScale9Sprite* buttonBackground2 = CCScale9Sprite::create("ZF_Shoot_Button_bg3.png");
    giveUpButton = CCControlButton::create(CCLabelTTF::create("Never mind","Georgia-BoldItalic", 25), buttonBackground2);
    giveUpButton->setPosition(ccp(background->getContentSize().width*3/4, 100));
    giveUpButton->setAnchorPoint(ccp(0.5, 0.5));
    giveUpButton->setPreferredSize(CCSizeMake(250, 100));
    giveUpButton->addTargetWithActionForControlEvents(this, cccontrol_selector(WeaponNotEnoughLayer::menuCloseCallback), CCControlEventTouchUpInside);
    giveUpButton->setTag(5);
    giveUpButton->setTouchEnabled(true);
    background->addChild(giveUpButton,1);
}




#pragma mark --------------- TouchEvent ---------------
void WeaponNotEnoughLayer::menuCloseCallback(CCObject* pSender)
{
    touchTime++;
    CCLog("touchTime:%d",touchTime);
    if (1 == touchTime) {
        //按钮音效
        SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_touchButton.wav");
        
        //根据按钮tag决定返回哪个场景
        GameScene* sharedLayer = GameScene::sharedGameScene();
        sharedLayer->moveLayer(this, ((CCControlButton*)pSender)->getTag());
    }
    else
    {
        return;
    }
}


void WeaponNotEnoughLayer::menuPurchaseWeapon(CCObject *pSender)
{
    
}

void WeaponNotEnoughLayer::setTouchTime()
{
    touchTime = 0;
}


//接收从GameScene传来的值 （重要）
void WeaponNotEnoughLayer::transferValueToWeaponNELayer(int pSceneNo, int kTagOfProps)
{
    
}





