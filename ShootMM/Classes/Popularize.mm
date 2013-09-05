/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: Popularize.mm
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-13.
 
 Description: 
 
 FunctionList:
 
 
 *******************************************************/

#include "Popularize.h"
#include "cocos-ext.h"
#include "MenuScene.h"
#import "MessageShow.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace extension;
using namespace CocosDenshion;


//static int choose = 1;
CCScene *Popularize::scene()
{
    CCScene *scene = CCScene::create();
    Popularize *layer = Popularize::create();
    scene->addChild(layer);
    return scene;
}

void Popularize::onExit()
{
    CCLayer::onExit();
    CCLog("Popularize:onExit()");
}

bool Popularize::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    //1.取出主屏幕的尺寸
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //2.背景
    CCSprite *background = CCSprite::create("ZF_Shoot_Background_popularize.png");
    background->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(background,0);
    
    
    //3.推广各类按钮
    CCScale9Sprite* buttonBackground = CCScale9Sprite::create("ZF_Shoot_Button_bg3.png");
    backToMenuButton = CCControlButton::create(CCLabelTTF::create("新浪微博","Georgia-BoldItalic", 25), buttonBackground);
    backToMenuButton->setPosition(ccp(120, 100));
    backToMenuButton->setAnchorPoint(ccp(0.5, 0.5));
    backToMenuButton->setPreferredSize(CCSizeMake(150, 65));
    backToMenuButton->addTargetWithActionForControlEvents(this, cccontrol_selector(Popularize::menuCloseCallBack), CCControlEventTouchUpInside);
    backToMenuButton->setTag(1);
    backToMenuButton->setTouchEnabled(true);
    this->addChild(backToMenuButton,1);
    
    
    //4.返回按钮
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "ZF_Shoot_Button_back3.png",
                                                          "ZF_Shoot_Button_back3.png",
                                                          this,
                                                          menu_selector(Popularize::menuCloseCallBack) );
    pCloseItem->setPosition( CCPointMake(this->getContentSize().width/2-400, 600) );
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);
    
    
    return true;
}


void Popularize::menuCloseCallBack(CCObject *pSender)
{
//    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"sms://800888"]];
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_touchButton.wav");
    CCControlButton* button = (CCControlButton*)pSender;
    if (1 == button->getTag()) {
        MessageShow* message = [[MessageShow alloc]init];
        [message showSMSPicker];
    }
    else
    {
        CCTransitionFade* transition = CCTransitionFade::create(0.5, MenuScene::scene());
        CCDirector::sharedDirector()->popScene();
    }

}
