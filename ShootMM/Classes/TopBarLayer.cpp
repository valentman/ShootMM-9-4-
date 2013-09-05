/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: TopBarLayer.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-7-8.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#include "TopBarLayer.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "DartSprite.h"
#include "ArrowSprite.h"
#include "StarSprite.h"
#include "FireworkSprite.h"

using namespace extension;
using namespace cocos2d;
using namespace CocosDenshion;


#pragma mark --------------- InitMethod ---------------
void TopBarLayer::onEnter()
{
    CCNode::onEnter();
}


void TopBarLayer::onExit()
{
    CCLayer::onExit();
    CCLOG("~~~~~~~~~~~~~~~~TopBarLayer:onExit()~~~~~~~~~~~~~~~~~**/");
}

bool TopBarLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCLOG("/**~~~~~~~~~~~~~~~~TopBarLayer:init()~~~~~~~~~~~~~~~~~");
    size = CCDirector::sharedDirector()->getVisibleSize();
    this->initTopBarBg();
    this->initLabels();
    this->initWeaponButton();
    
    isPauseed = 1;
    return true; 
}


//顶部背景条初始化
void TopBarLayer::initTopBarBg()
{   
    //返回按钮
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "ZF_Shoot_Button_back3.png",
                                                          "ZF_Shoot_Button_back3.png",
                                                          this,
                                                          menu_selector(TopBarLayer::menuCloseCallBack) );
    pCloseItem->setPosition( CCPointMake(this->getContentSize().width/15, this->getContentSize().height-30));
    pCloseItem->setTag(11);
    pPauseItem = CCMenuItemImage::create(
                                                          "ZF_Shoot_GameScene_pause.png",
                                                          "ZF_Shoot_GameScene_pause.png",
                                                          this,
                                                          menu_selector(TopBarLayer::menuCloseCallBack) );
    pPauseItem->setPosition( CCPointMake(this->getContentSize().width*14/15, this->getContentSize().height-35));
    pPauseItem->setTag(12);
    pPlayItem = CCMenuItemImage::create(
                                                          "ZF_Shoot_GameScene_play.png",
                                                          "ZF_Shoot_GameScene_play.png",
                                                          this,
                                                          menu_selector(TopBarLayer::menuCloseCallBack) );
    pPlayItem->setPosition( CCPointMake(this->getContentSize().width*14/15, this->getContentSize().height-35));
    pPlayItem->setTag(13);
    pPlayItem->setVisible(false);
    pMenu = CCMenu::create(pCloseItem,pPauseItem,pPlayItem,NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu,5);
}


//可变数字标签初始化
void TopBarLayer::initLabels()
{
    numberPoint = CCPointMake(90, 70);
    //顶部目标积分和当前积分Label
    targetScoreLabel = new CCLabelTTF;
    targetScoreLabel->init();
    this->addChild(targetScoreLabel);
    levelgradeLabel = new CCLabelTTF;
    levelgradeLabel->init();
    this->addChild(levelgradeLabel);
    scoreLabel = new CCLabelTTF;
    scoreLabel->init();
    this->addChild(scoreLabel);
    
    //底部武器数量Label
    labelOfWeapon1 = new CCLabelTTF;
    labelOfWeapon1->init();
    this->addChild(labelOfWeapon1);
    labelOfWeapon2 = new CCLabelTTF;
    labelOfWeapon2->init();
    this->addChild(labelOfWeapon2);
    labelOfWeapon3 = new CCLabelTTF;
    labelOfWeapon3->init();
    this->addChild(labelOfWeapon3);
    labelOfWeapon4 = new CCLabelTTF;
    labelOfWeapon4->init();
    this->addChild(labelOfWeapon4);
}


#pragma mark --------------- TopbarMethod ---------------

//刚进场景初始当前等级和目标积分（静态）
void TopBarLayer::updateTopTargetScore(int p_TargetScore,int levelGrade)
{
    targetScoreLabel->removeFromParentAndCleanup(true);
    levelgradeLabel->removeFromParentAndCleanup(true);
    this->setTopTargetScore(p_TargetScore,levelGrade);
}


//插入当前等级和目标积分（静态）
void TopBarLayer::setTopTargetScore(int p_TargetScore,int levelGrade)
{
    CCString* targetScore = CCString::createWithFormat(" / %d",p_TargetScore);
    targetScoreLabel = CCLabelTTF::create(targetScore->getCString(), "TimesNewRomanPS-BoldMT", 30);
    targetScoreLabel->setColor(ccBLUE);
    targetScoreLabel->setAnchorPoint(ccp(0, 0.5));
    targetScoreLabel->setPosition(CCPointMake(size.width-250,60));
    this->addChild(targetScoreLabel);
    
    CCString* levelgrade = CCString::createWithFormat("Level:%d",levelGrade);
    levelgradeLabel = CCLabelTTF::create(levelgrade->getCString(), "TimesNewRomanPS-BoldMT", 30);
    levelgradeLabel->setColor(ccBLUE);
    levelgradeLabel->setPosition(CCPointMake(size.width-70,60));
    this->addChild(levelgradeLabel);
}


//更新当前积分（动态）
void TopBarLayer::updateScore(int p_Score)
{
    scoreLabel->removeFromParentAndCleanup(true);
    this->showScore(p_Score);
}


//显示当前积分（动态）
void TopBarLayer::showScore(int p_Score)
{
    Score = CCString::createWithFormat("%d",p_Score);
    scoreLabel= CCLabelTTF::create(Score->getCString(), "TimesNewRomanPS-BoldMT", 35);
    scoreLabel->setColor(ccBLUE);
    scoreLabel->setScale(1.3);
    scoreLabel->setAnchorPoint(ccp(1, 0.5));
    scoreLabel->setPosition(CCPointMake(size.width-250, 60));
    CCScaleTo* scaleTo = CCScaleTo::create(0.3, 1.0f);
    scoreLabel->runAction(scaleTo);
    this->addChild(scoreLabel);
}


//积分达到目标积分抖动的显示特效
void TopBarLayer::showScoreCompleteEffects()
{
    CCScaleTo* scaleTo1 = CCScaleTo::create(0.15, 1.5f);
    CCScaleTo* scaleTo2 = CCScaleTo::create(0.15, 1.0f);
    CCSequence* sequence = CCSequence::create(scaleTo1,scaleTo2,NULL);
    CCRepeat* repeate = CCRepeat::create(sequence, 3);
    scoreLabel->setColor(ccRED);
    scoreLabel->runAction(repeate);
}


//返回选关场景
void TopBarLayer::menuCloseCallBack(CCObject* pSender)
{
    GameScene* game = GameScene::sharedGameScene();
    switch (((CCMenuItemImage*)pSender)->getTag()) {
        case 11:
            game->backToMenuScene();
            break;
        case 12:
            pPauseItem->setScale(0);
            pPauseItem->setVisible(false);
            pPlayItem->setScale(1);
            pPlayItem->setVisible(true);
            game->stopAllBallnoonAction();
            SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
            isPauseed = 0;
            game->setIsPauseed(1);
            break;
                
        case 13:
            pPauseItem->setScale(1);
            pPauseItem->setVisible(true);
            pPlayItem->setScale(0);
            pPlayItem->setVisible(false);
            game->restarBallnoonAction();
            SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
            isPauseed = 1;
            game->setIsPauseed(0);
            break;
            
        default:
            break;
    }
    
}


#pragma mark --------------- ButtomWeaponMethod ---------------
//初始武器按钮
void TopBarLayer::initWeaponButton()
{
    //添加武器选择按钮
    //1.
    CCScale9Sprite* weaponframe1 = CCScale9Sprite::create("ZF_Shoot_Prop_fire.png");
    weaponButton1 = CCControlButton::create(weaponframe1);
    weaponButton1->setPosition(ccp(70, 55));
    weaponButton1->setAnchorPoint(ccp(0.5, 0.5));
    weaponButton1->setPreferredSize(CCSizeMake(100, 75));
    weaponButton1->addTargetWithActionForControlEvents(this, cccontrol_selector(TopBarLayer::switchWeapon), CCControlEventTouchUpInside);
    weaponButton1->setTag(1);
    weaponButton1->setTouchEnabled(true);
    this->addChild(weaponButton1,4);
    
    //2.
    CCScale9Sprite* weaponframe2 = CCScale9Sprite::create("ZF_Shoot_Prop_hd.png");
    weaponButton2 = CCControlButton::create(weaponframe2);
    weaponButton2->setPosition(ccp(190, 55));
    weaponButton2->setAnchorPoint(ccp(0.5, 0.5));
    weaponButton2->setPreferredSize(CCSizeMake(100, 75));
    weaponButton2->addTargetWithActionForControlEvents(this, cccontrol_selector(TopBarLayer::switchWeapon), CCControlEventTouchUpInside);
    weaponButton2->setTag(2);
    weaponButton2->setTouchEnabled(true);
    this->addChild(weaponButton2,4);
    
    //3.
    CCScale9Sprite* weaponframe3 = CCScale9Sprite::create("ZF_Shoot_Prop_hjt.png");
    weaponButton3 = CCControlButton::create(weaponframe3);
    weaponButton3->setPosition(ccp(310, 55));
    weaponButton3->setAnchorPoint(ccp(0.5, 0.5));
    weaponButton3->setPreferredSize(CCSizeMake(100, 75));
    weaponButton3->addTargetWithActionForControlEvents(this, cccontrol_selector(TopBarLayer::switchWeapon), CCControlEventTouchUpInside);
    weaponButton3->setTag(3);
    weaponButton3->setTouchEnabled(true);
    this->addChild(weaponButton3,4);
    
    //4.
    CCScale9Sprite* weaponframe4 = CCScale9Sprite::create("ZF_Shoot_Prop_laser.png");
    weaponButton4 = CCControlButton::create(weaponframe4);
    weaponButton4->setPosition(ccp(430, 55));
    weaponButton4->setAnchorPoint(ccp(0.5, 0.5));
    weaponButton4->setPreferredSize(CCSizeMake(100, 75));
    weaponButton4->addTargetWithActionForControlEvents(this, cccontrol_selector(TopBarLayer::switchWeapon), CCControlEventTouchUpInside);
    weaponButton4->setTag(4);
    weaponButton4->setTouchEnabled(true);
    this->addChild(weaponButton4,4);
}


//武器数量初始
void TopBarLayer::initNumberOfWeapon(int numberOfWeapon1,int numberOfWeapon2,int numberOfWeapon3,int numberOfWeapon4)
{
    //首先移除之前的标签
    labelOfWeapon1->removeFromParentAndCleanup(true);
    labelOfWeapon2->removeFromParentAndCleanup(true);
    labelOfWeapon3->removeFromParentAndCleanup(true);
    labelOfWeapon4->removeFromParentAndCleanup(true);
    
    if (numberOfWeapon1 > 0) {
        weaponButton1->setTouchEnabled(true);
    }
    else
    {
        weaponButton1->setTouchEnabled(false);
    }
    if (numberOfWeapon2 > 0) {
        weaponButton2->setTouchEnabled(true);
    }
    else
    {
        weaponButton2->setTouchEnabled(false);
    }
    if (numberOfWeapon3 > 0) {
        weaponButton3->setTouchEnabled(true);
    }
    else
    {
        weaponButton3->setTouchEnabled(false);
    }
    if (numberOfWeapon4 > 0) {
        weaponButton4->setTouchEnabled(true);
    }
    else
    {
        weaponButton4->setTouchEnabled(false);
    }
    
    //再初始化标签
    CCString* numberOfWeapon1String = CCString::createWithFormat("%d",numberOfWeapon1);
    labelOfWeapon1 = CCLabelTTF::create(numberOfWeapon1String->getCString(), "TimesNewRomanPS-BoldMT", 30);
    labelOfWeapon1->setPosition(numberPoint);
    labelOfWeapon1->setColor(ccRED);
    weaponButton1->addChild(labelOfWeapon1,1);
    
    CCString* numberOfWeapon2String = CCString::createWithFormat("%d",numberOfWeapon2);
    labelOfWeapon2 = CCLabelTTF::create(numberOfWeapon2String->getCString(), "TimesNewRomanPS-BoldMT", 30);
    labelOfWeapon2->setPosition(numberPoint);
    labelOfWeapon2->setColor(ccRED);
    weaponButton2->addChild(labelOfWeapon2,1);
    
    CCString* numberOfWeapon3String = CCString::createWithFormat("%d",numberOfWeapon3);
    labelOfWeapon3 = CCLabelTTF::create(numberOfWeapon3String->getCString(), "TimesNewRomanPS-BoldMT", 30);
    labelOfWeapon3->setPosition(numberPoint);
    labelOfWeapon3->setColor(ccRED);
    weaponButton3->addChild(labelOfWeapon3,1);
    
    
    CCString* numberOfWeapon4String = CCString::createWithFormat("%d",numberOfWeapon4);
    labelOfWeapon4 = CCLabelTTF::create(numberOfWeapon4String->getCString(), "TimesNewRomanPS-BoldMT", 30);
    labelOfWeapon4->setPosition(numberPoint);
    labelOfWeapon4->setColor(ccRED);
    weaponButton4->addChild(labelOfWeapon4,1);
}


//切换武器道具
void TopBarLayer::switchWeapon(cocos2d::CCObject *sender, CCControlEvent controlEvent)
{
    //切换道具时的音效
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_swicthWeapon.wav");
    GameScene* gameScene = GameScene::sharedGameScene();
    gameScene->propsSprite->removeFromParentAndCleanup(true);
    gameScene->propsSprite->release();
    switch (((CCControlButton*)sender)->getTag()) {
        case 1:
            gameScene->propsSprite = (CCSprite*)new DartSprite();
            gameScene->propsSprite->setTag(1);
            break;
        case 2:
            gameScene->propsSprite = (CCSprite*)new ArrowSprite();
            gameScene->propsSprite->setTag(2);
            break;
        case 3:
            gameScene->propsSprite = (CCSprite*)new StarSprite();
            gameScene->propsSprite->setTag(3);
            break;
        case 4:
            gameScene->propsSprite = (CCSprite*)new FireworkSprite();
            gameScene->propsSprite->setTag(4);
            break;
        default:
            break;
    }
    gameScene->propsSprite->setAnchorPoint(CCPointMake(0.9, 0.5));
    gameScene->propsSprite->setPosition(gameScene->propsSpritePosition);
    gameScene->propsSprite->setScale(0.5);
    gameScene->propsSprite->setVisible(false);
    addChild(gameScene->propsSprite, 1);
    CCLog("switch,tag:%d",((CCControlButton*)sender)->getTag());
}


//武器数量更新
void TopBarLayer::updateNumberOfWeapon(int kTag,int numberOfWeapon)
{
    CCString* number = CCString::createWithFormat("%d",numberOfWeapon);
    
    switch (kTag) {
        case 1:
            labelOfWeapon1->removeFromParentAndCleanup(true);
            labelOfWeapon1 = CCLabelTTF::create(number->getCString(), "TimesNewRomanPS-BoldMT", 30);
            labelOfWeapon1->setPosition(numberPoint);
            labelOfWeapon1->setColor(ccRED);
            weaponButton1->addChild(labelOfWeapon1);
            if (numberOfWeapon > 0) {
                weaponButton1->setTouchEnabled(true);
            }
            else
            {
                weaponButton1->setTouchEnabled(false);
            }
            
            
            break;
        case 2:
            labelOfWeapon2->removeFromParentAndCleanup(true);
            labelOfWeapon2 = CCLabelTTF::create(number->getCString(), "TimesNewRomanPS-BoldMT", 30);
            labelOfWeapon2->setPosition(numberPoint);
            labelOfWeapon2->setColor(ccRED);
            weaponButton2->addChild(labelOfWeapon2);
            if (numberOfWeapon > 0) {
                weaponButton2->setTouchEnabled(true);
            }
            else
            {
                weaponButton2->setTouchEnabled(false);
            }
            break;
        case 3:
            labelOfWeapon3->removeFromParentAndCleanup(true);
            labelOfWeapon3 = CCLabelTTF::create(number->getCString(), "TimesNewRomanPS-BoldMT", 30);
            labelOfWeapon3->setPosition(numberPoint);
            labelOfWeapon3->setColor(ccRED);
            weaponButton3->addChild(labelOfWeapon3);
            if (numberOfWeapon > 0) {
                weaponButton3->setTouchEnabled(true);
            }
            else
            {
                weaponButton3->setTouchEnabled(false);
            }
            break;
        case 4:
            labelOfWeapon4->removeFromParentAndCleanup(true);
            labelOfWeapon4 = CCLabelTTF::create(number->getCString(), "TimesNewRomanPS-BoldMT", 30);
            labelOfWeapon4->setPosition(numberPoint);
            labelOfWeapon4->setColor(ccRED);
            weaponButton4->addChild(labelOfWeapon4);
            if (numberOfWeapon > 0) {
                weaponButton4->setTouchEnabled(true);
            }
            else
            {
                weaponButton4->setTouchEnabled(false);
            }
            break;
        default:
            break;
    }
}













