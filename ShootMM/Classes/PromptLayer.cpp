/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: PromptLayer.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-27.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#include "PromptLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace extension;
using namespace CocosDenshion;



#pragma mark ---------------- SystemInitMethod ---------------
void PromptLayer::onExit()
{
    CCLayer::onExit();
    CCLOG("~~~~~~~~~~~~~~~~PromptLayer:onExit()~~~~~~~~~~~~~~~~~**/");
}


//移除提示称所有文字标签
void PromptLayer::removeLabels()
{
    showNextLevelLabel->removeFromParentAndCleanup(true);
    showShootResultLabel->removeFromParentAndCleanup(true);
    if (isFailed) {
        showGoodLuckLabel->removeFromParentAndCleanup(true);
    }
}


bool PromptLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCLOG("/**~~~~~~~~~~~~~~~~PromptLayer:init()~~~~~~~~~~~~~~~~~");
    this->setTouchEnabled(true);
    this->setTouchPriority(-1);

    winSize = CCDirector::sharedDirector()->getVisibleSize();
    
    //添加相应的按钮
    nextLevelButton = CCMenuItemImage::create("ZF_Shoot_Prompt_next1.png", "ZF_Shoot_Prompt_next2.png", this, menu_selector(PromptLayer::menuCloseCallback));
    nextLevelButton->setTag(1);

    backToMenuButton = CCMenuItemImage::create("ZF_Shoot_Prompt_Menu1.png", "ZF_Shoot_Prompt_Menu2.png", this, menu_selector(PromptLayer::menuCloseCallback));
    backToMenuButton->setTag(2);
    
    goShopButton = CCMenuItemImage::create("ZF_Shoot_Prompt_replay1.png", "ZF_Shoot_Prompt_replay2.png", this, menu_selector(PromptLayer::menuCloseCallback));
    goShopButton->setTag(3);

    CCMenu *pMenu = CCMenu::create(nextLevelButton,backToMenuButton,goShopButton,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);
    
    //仿candy按钮呼吸效果 
    CCActionInterval* scaleTo1 = CCScaleTo::create(1.2, 1.0, 0.95);
    CCActionInterval* scaleTo2 = CCScaleTo::create(1.2, 0.95, 1.0);
    CCSequence* sequence1 = CCSequence::create(scaleTo2,scaleTo1,NULL);
    CCRepeatForever* repeate1 = CCRepeatForever::create(sequence1);
    nextLevelButton->runAction(repeate1);
    
    CCActionInterval* scaleTo3 = CCScaleTo::create(1.2, 1.0, 0.95);
    CCActionInterval* scaleTo4 = CCScaleTo::create(1.2, 0.95, 1.0);
    CCSequence* sequence2 = CCSequence::create(scaleTo3,scaleTo4,NULL);
    CCRepeatForever* repeate2 = CCRepeatForever::create(sequence2);
    backToMenuButton->runAction(repeate2);
    
    CCActionInterval* scaleTo5 = CCScaleTo::create(1.2, 1.0, 0.95);
    CCActionInterval* scaleTo6 = CCScaleTo::create(1.2, 0.95, 1.0);
    CCSequence* sequence3 = CCSequence::create(scaleTo5,scaleTo6,NULL);
    CCRepeatForever* repeate3 = CCRepeatForever::create(sequence3);
    goShopButton->runAction(repeate3);
    
    
    return true;
}


//响应按钮的函数
void PromptLayer::menuCloseCallback(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_touchButton.wav");
    touchTime++;
    CCLog("touchTime:%d",touchTime);
    if (1 == touchTime) {
        //根据按钮tag决定返回哪个场景
        int kTag = ((CCControlButton*)pSender)->getTag();
        CCLOG("Promptlayer:%d",kTag);
        GameScene* sharedLayer = GameScene::sharedGameScene();
        sharedLayer->moveLayer(this, kTag);
    }
    else
    {
        return;
    }
}


#pragma mark -------------- ShowPromptInfoMethod ---------------
//接收从GameScene传来的值 （重要）
void PromptLayer::transferPromotedInfo(int pSceneNumber,int levelGrade,int isSuccess,int integration,int shootNumber,int shootedNumber)
{
    touchTime = 0;
    isFailed = isSuccess;
    CCLog("关卡等级:%d,奖品名称:%d,积分:%d,射了:%d次,射中:%d次",levelGrade,isSuccess,integration,shootNumber,shootedNumber);
    this->showShootResult(shootNumber, shootedNumber);
    this->showNextLevel(levelGrade,integration);
    if (isSuccess) {
        nextLevelButton->setPosition(ccp(this->getContentSize().width*0.4, 120));
        backToMenuButton->setPosition(ccp(this->getContentSize().width*0.6, 120));
        goShopButton->setVisible(false);
        nextLevelButton->setVisible(true);
        switch (pSceneNumber){
            case 0:
                this->showGoodLuck(250*levelGrade+100*levelGrade*levelGrade);
                break;
            case 1:
                this->showGoodLuck(500*levelGrade + 100*levelGrade*levelGrade);
                break;
            case 2:
                this->showGoodLuck(1000*levelGrade+200*levelGrade*levelGrade);
                break;
            default:
                break;
        }
        
    }
    else
    {
        goShopButton->setVisible(true);
        nextLevelButton->setVisible(false);
        backToMenuButton->setPosition(ccp(this->getContentSize().width*0.4, 120));
        goShopButton->setPosition(ccp(this->getContentSize().width*0.6, 120));
    }
    
    /**
     *
     */
}



//恭喜成功晋级
void PromptLayer::showNextLevel(int levelGrade,int integration)
{
    CCString* showNextLevelString = CCString::createWithFormat("Level:%d, ",levelGrade);
    CCString* score = CCString::createWithFormat("%d",integration);
    char* scoreChar = (char*)score->getCString();
    char prifix2[50] = "Score:";
    strcat(prifix2, scoreChar);
    char prifix1[50] = " ";
    char* levelGradeChar = (char*)showNextLevelString->getCString();
    strcat(prifix1,levelGradeChar);
    strcat(prifix1, prifix2);

    CCLog("%s",prifix1);
    showNextLevelLabel = CCLabelTTF::create(prifix1, "TimesNewRomanPS-BoldMT", 35);
    showNextLevelLabel->setPosition(CCPointMake(winSize.width/2, winSize.height*0.7));
    this->addChild(showNextLevelLabel,1);
}


//发射了多少次，命中多少次
void PromptLayer::showShootResult(int shoot,int shooted)
{
    CCString* showShootResult = CCString::createWithFormat("Shooted:%d, Hits:%d",shoot,shooted);
    showShootResultLabel = CCLabelTTF::create(showShootResult->getCString(),"TimesNewRomanPS-BoldMT", 35);
    showShootResultLabel->setPosition(ccp(winSize.width/2, winSize.height*0.6));
    this->addChild(showShootResultLabel,1);
}


//恭喜过关，将在多少积分后再次过关
void PromptLayer::showGoodLuck(int integration)
{
    CCString* showGoodLuck = CCString::createWithFormat("Next Level Target : %d ",integration);
    showGoodLuckLabel = CCLabelTTF::create(showGoodLuck->getCString(), "TimesNewRomanPS-BoldMT", 35);
    showGoodLuckLabel->setPosition(ccp(winSize.width/2, winSize.height*0.5));
    this->addChild(showGoodLuckLabel);
}


