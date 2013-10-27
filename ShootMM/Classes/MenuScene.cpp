/*******************************************************************
 
Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
Filename: MenuScene.cpp
 
ProjectName: 射你妹
 
Author: P.Joe     Version: 1.0     Date: 13-6-13.
 
Description: 主要功能作用：
                1.初始化选关界面所有按钮
                2.加载获奖动态信息
                3.跳转至各个功能模块
 
FunctionList:
                1.初始化函数群：
                     void initButton();
                     void initSceneChoose();
                     void initUserInfo();
                     void initPrizeBar();
 
                2.动态信息加载及显示函数：
                     void updateDynamicInfo();
                     void getDynamicInfoArrayFromServer();
                     void getDynamicInfoFromArray();
                     void removeOldInfoLabel();
                     void showNewDynamicInfoLabel();
 
                3.按钮跳转函数：
                     void menuCloseCallBack(CCObject *pSender);
                     void menuChoseScene(CCObject *pSender);
                     void transfer();
                     void switchToGameScene(CCTransitionCrossFade* transition);
 
                4.底部动态奖品图片展示函数：
                     void createPrizeSprite();
                     void runPrizeSprite(CCSprite* pSprite);
                     void resetPrizeSpritePosition(CCObject* pSprite);
 
                5.免费获取富币提示函数：
                     void menuCallAcceptFubiYes();
                     void menuCallAcceptFubiNo();
                     void removeFreeFubiAnimation();
 
 
 History: updateTime 8.20
 
********************************************************************/


#include "MenuScene.h"
#include "GameScene.h"
#include "Popularize.h"
#include "PropMarketsLayer.h"
#include "AcceptFreeFubi.h"
#include "GuideScene.h"
#include "UserData.h"
#include "cmath"
#include "SimpleAudioEngine.h"
#include "ColorLayer.h"


using namespace cocos2d;
using namespace extension;
using namespace CocosDenshion;


#define kExserciseTag 2
#define kPeopleTag 0
#define kRichTag 1
#define kScaleRitio 0.83
#define kScaleDuration 0.5
#define kScaleDuration1 0.75
#define kFreeFubi 500


#pragma mark --------------- SystemInitMethod ----------------
//退出
void MenuScene::onExit()
{
    this->unscheduleAllSelectors();
    CCLayer::onExit();
    CCLOG("~~~~~~~~~~~~~~~~MenuScene:onExit()~~~~~~~~~~~~~~~~~**/");
}


void MenuScene::onEnter()
{
    CCNode::onEnter();
}


CCScene *MenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MenuScene *layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}


//初始化开始的主场景
bool MenuScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCLOG("/**~~~~~~~~~~~~~~~~MenuScene:init()~~~~~~~~~~~~~~~~~");
    //取出主屏幕的尺寸，以及初始化数据
    size = CCDirector::sharedDirector()->getVisibleSize();
   
    data.openDatabase();
    //参数,上部按钮,玩家头像和信息,选关,底部奖品图片展示
    this->initVarible();
    this->initButton();
    this->initUserInfo();
    this->initSceneChoose();
    
    
    //如果是第一次登陆，则初始化当前日期，赠送富币
    if(data.getIsFirstLogin())
    {
        this->currentTimeNow();
        data.setCurrentTime(currentDay);
        this->freeToGetFubi();
        data.setIsFirstLogin(0);
    }
    else
    {
        this->currentTimeNow();
        if (currentDay == data.getLastLoginTime()?0:1) {
            this->freeToGetFubi();
        }
        data.setCurrentTime(currentDay);
    }
    
    
    //关闭数据库
    data.closeDatabase();
    return true;
}



void MenuScene::freeToGetFubi()
{
    //添加免费领取富币的背景,非0为第一次登录，测试显示，0为第一次登录
    CCLog("-------MenuScene:您第一次登陆，获得富币--------");
    this->setMenuButtonTouchFasle();
    //背景框
    CCSprite *acceptFreeFubiImage = CCSprite::create("ZF_Shoot_MenuScene_background_freeFubi.png");
    acceptFreeFubiImage->setPosition(CCPointMake(size.width/2, size.height/2));
    acceptFreeFubiImage->setTag(111);
    this->addChild(acceptFreeFubiImage, 1,111);
    
    //确认或者拒绝
    CCMenuItemImage *yes = CCMenuItemImage::create("ZF_Shoot_MenuScene_background_freeFubi_confirm1.png", "ZF_Shoot_MenuScene_background_freeFubi_confirm1.png", this, menu_selector(MenuScene::menuCallAcceptFubiYes));
    yes->setContentSize(CCSizeMake(200, 100));
    yes->setPosition(CCPointMake(acceptFreeFubiImage->getContentSize().width/2+50, acceptFreeFubiImage->getContentSize().height*0.4));
    
    CCMenu *menu = CCMenu::create(yes,NULL);
    menu->setPosition(CCPointZero);
    menu->setTag(112);
    acceptFreeFubiImage->addChild(menu, 1,112);
}


void MenuScene::initVarible()
{
    //初始头像数组
    userPhotoNormal[0] = "ZF_Shoot_Background_userInfo_person1_n.png";
    userPhotoNormal[1] = "ZF_Shoot_Background_userInfo_person2_n.png";
    userPhotoNormal[2] = "ZF_Shoot_Background_userInfo_person3_n.png";
    userPhotoNormal[3] = "ZF_Shoot_Background_userInfo_person4_n.png";
    userPhotoNormal[4] = "ZF_Shoot_Background_userInfo_person5_n.png";
    userPhotoNormal[5] = "ZF_Shoot_Background_userInfo_person6_n.png";
    userPhotoNormal[6] = "ZF_Shoot_Background_userInfo_person7_n.png";
    userPhotoNormal[7] = "ZF_Shoot_Background_userInfo_person8_n.png";
    userPhotoNormal[8] = "ZF_Shoot_Background_userInfo_person9_n.png";
    
    userPhotoSelected[0] = "ZF_Shoot_Background_userInfo_person1_s.png";
    userPhotoSelected[1] = "ZF_Shoot_Background_userInfo_person2_s.png";
    userPhotoSelected[2] = "ZF_Shoot_Background_userInfo_person3_s.png";
    userPhotoSelected[3] = "ZF_Shoot_Background_userInfo_person4_s.png";
    userPhotoSelected[4] = "ZF_Shoot_Background_userInfo_person5_s.png";
    userPhotoSelected[5] = "ZF_Shoot_Background_userInfo_person6_s.png";
    userPhotoSelected[6] = "ZF_Shoot_Background_userInfo_person7_s.png";
    userPhotoSelected[7] = "ZF_Shoot_Background_userInfo_person8_s.png";
    userPhotoSelected[8] = "ZF_Shoot_Background_userInfo_person9_s.png";
    
    //添加背景主场景
    CCSprite *pSprite = CCSprite::create("ZF_Shoot_Menu_background.png");
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite,0);
    
    //上部菜单按钮背景、动态信息显示背景、底部在线玩家信息显示背景、奖品展示背景
    CCSprite *topBarSprite = CCSprite::create("ZF_Shoot_Menu_topbar.png");
    topBarSprite->setPosition(ccp(size.width/2, size.height-53));
    topBarSprite->setScaleX(size.width/topBarSprite->getContentSize().width);
    this->addChild(topBarSprite,0);

    
    //遮罩层
    colorLayer = ColorLayer::create();
    this->addChild(colorLayer,6);
    colorLayer->setVisible(false);
}


//添加顶部按钮
void MenuScene::initButton()
{
    //免费富币
    CCMenuItemImage *freeImage = CCMenuItemImage::create("ZF_Shoot_Button_coin.png", "ZF_Shoot_Button_coin1.png",this,menu_selector(MenuScene::menuCloseCallBack));
    freeImage->setPosition(ccp(size.width/2, size.height-55));
    freeImage->setTag(1);
    CCActionInterval* scaleTofree1 = CCScaleTo::create(kScaleDuration, 1, 0.95);
    CCActionInterval* scaleTofree2 = CCScaleTo::create(kScaleDuration, 0.96, 1);
    CCSequence* sequence1 = CCSequence::create(scaleTofree1,scaleTofree2,NULL);
    CCActionInterval* rotate1 = CCRepeatForever::create(sequence1);
    freeImage->runAction(rotate1);
    
    
    //商城
    CCMenuItemImage *buyImage = CCMenuItemImage::create("ZF_Shoot_Button_shop.png", "ZF_Shoot_Button_shop1.png",this,menu_selector(MenuScene::menuCloseCallBack));
    buyImage->setPosition(ccp(size.width/2+205, size.height-55));
    buyImage->setTag(2);
    CCActionInterval* scaleTobuy1 = CCScaleTo::create(kScaleDuration, 1, 0.95);
    CCActionInterval* scaleTobuy2 = CCScaleTo::create(kScaleDuration, 0.96, 1);
    CCSequence* sequence2 = CCSequence::create(scaleTobuy1,scaleTobuy2,NULL);
    CCActionInterval* rotate2 = CCRepeatForever::create(sequence2);
    buyImage->runAction(rotate2);
    
    
    //玩家指南
    CCMenuItemImage *guideIamge = CCMenuItemImage::create("ZF_Shoot_Button_help.png", "ZF_Shoot_Button_help1.png",this,menu_selector(MenuScene::menuCloseCallBack));
    guideIamge->setPosition(ccp(size.width/2+405, size.height-55));
    guideIamge->setTag(4);
    CCActionInterval* scaleTopl1 = CCScaleTo::create(kScaleDuration, 1, 0.95);
    CCActionInterval* scaleTopl2 = CCScaleTo::create(kScaleDuration, 0.96, 1);
    CCSequence* sequence4 = CCSequence::create(scaleTopl1,scaleTopl2,NULL);
    CCActionInterval* rotate4 = CCRepeatForever::create(sequence4);
    guideIamge->runAction(rotate4);
    
    sceneMenu = CCMenu::create(buyImage,guideIamge,NULL);
    sceneMenu->setPosition(CCPointZero);
    this->addChild(sceneMenu, 1);
}



//添加3个选关按钮
void MenuScene::initSceneChoose()
{
    float pngWidth = 362.0;
    float xSpace = (size.width - pngWidth*3)/4;
    
    //添加练习场菜单项
    CCActionInterval* scaleToex1 = CCScaleTo::create(kScaleDuration1, kScaleRitio, kScaleRitio-0.03);
    CCActionInterval* scaleToex2 = CCScaleTo::create(kScaleDuration1, kScaleRitio-0.02, kScaleRitio);
    CCSequence* sequence1 = CCSequence::create(scaleToex1,scaleToex2,NULL);
    CCActionInterval* rotate1 = CCRepeatForever::create(sequence1);
    
    CCMenuItemImage *exersize = CCMenuItemImage::create("ZF_Shoot_Button_lxc.png", "ZF_Shoot_Button_lxc.png", this, menu_selector(MenuScene::menuChoseScene));
    exersize->setPosition(ccp(xSpace+pngWidth/2, size.height/2));
    exersize->setScale(kScaleRitio);
    exersize->setTag(kExserciseTag);
    exersize->runAction(rotate1);
    
    //添加平民场菜单项
    CCActionInterval* scaleTope1 = CCScaleTo::create(kScaleDuration1, kScaleRitio, kScaleRitio-0.03);
    CCActionInterval* scaleTope2 = CCScaleTo::create(kScaleDuration1, kScaleRitio-0.02, kScaleRitio);
    CCSequence* sequence2 = CCSequence::create(scaleTope1,scaleTope2,NULL);
    CCActionInterval* rotate2 = CCRepeatForever::create(sequence2);
    CCMenuItemImage *people = CCMenuItemImage::create("ZF_Shoot_Button_pmc.png", "ZF_Shoot_Button_pmc.png", this, menu_selector(MenuScene::menuChoseScene));
    people->setPosition(ccp(xSpace*2+pngWidth*1.5, size.height/2));
    people->setScale(kScaleRitio);
    people->setTag(kPeopleTag);
    people->runAction(rotate2);
    
    //添加富豪场菜单项
    CCActionInterval* scaleTori1 = CCScaleTo::create(kScaleDuration1, kScaleRitio, kScaleRitio-0.03);
    CCActionInterval* scaleTori2 = CCScaleTo::create(kScaleDuration1, kScaleRitio-0.02, kScaleRitio);
    CCSequence* sequence3 = CCSequence::create(scaleTori1,scaleTori2,NULL);
    CCActionInterval* rotate3 = CCRepeatForever::create(sequence3);
    CCMenuItemImage *rich = CCMenuItemImage::create("ZF_Shoot_Button_hhc.png", "ZF_Shoot_Button_hhc.png", this, menu_selector(MenuScene::menuChoseScene));
    rich->setPosition(ccp(xSpace*3+pngWidth*2.5, size.height/2));
    rich->setScale(kScaleRitio);
    rich->setTag(kRichTag);
    rich->runAction(rotate3);
    
    //集成到菜单容器
    richMenu = CCMenu::create(rich,people,exersize,NULL);
    richMenu->setPosition(CCPointZero);
    this->addChild(richMenu,1);
}


//更新玩家头像
void MenuScene::updateUserPhoto()
{
    CCMenuItemImage *headProtrait = CCMenuItemImage::create("ZF_Shoot_MenuScene_touxiang.png", "ZF_Shoot_MenuScene_touxiang.png",this,menu_selector(MenuScene::menuCloseCallBack));
    headProtrait->setPosition(ccp(70, size.height-52));
    headProtrait->setTag(6);
    headMenu = CCMenu::create(headProtrait,NULL);
    headMenu->setPosition(CCPointZero);
    this->addChild(headMenu,1,12);
}



void MenuScene::updateFubi()
{
    float i_Fubi = 0;
    if(this->getChildByTag(11) != NULL)
    {
        this->getChildByTag(11)->removeFromParentAndCleanup(true);
    }

    //富币
    data.openDatabase();
    i_Fubi = data.getFubi();
    CCString* c_Fubi = CCString::createWithFormat("Coins:%.0f",i_Fubi);
    CCLabelTTF *l_Fubi = CCLabelTTF::create(c_Fubi->getCString(), "Thonburi", 28);
    l_Fubi->setColor(ccYELLOW);
    l_Fubi->setPosition(ccp(size.width*0.2, size.height-25));
    l_Fubi->setAnchorPoint(ccp(0,0.5));
    this->addChild(l_Fubi,1,11);

}



//添加人物头像
void MenuScene::initUserInfo()
{
    this->updateUserPhoto();
    //添加人物名称
    string userName = data.getUserName();
    CCLabelTTF *name = CCLabelTTF::create((char*)userName.c_str(),"Thonburi" , 28);
    name->setColor(ccc3(0, 0, 0));
    name->setPosition(ccp(110, size.height-25));
    name->setAnchorPoint(ccp(0, 0.5));
    name->setColor(ccWHITE);
    this->addChild(name,1);
    
    //添加等级信息
    CCString* levelInfo;
    if(data.getGateNormalNO() > data.getGateRichNO() ? 1:0)
    {
        levelInfo = CCString::createWithFormat("Civilian%d",data.getGateNormalNO());
    }
    else
    {
        levelInfo = CCString::createWithFormat("Rich%d",data.getGateRichNO());
    }
    CCLabelTTF *level = CCLabelTTF::create(levelInfo->getCString(),"Thonburi" , 28);
    level->setColor(ccc3(0, 0, 0));
    level->setPosition(ccp(110, size.height-75));
    level->setAnchorPoint(ccp(0, 0.5));
    level->setColor(ccBLUE);
    this->addChild(level,1);
    
    this->updateFubi();

}



#pragma mark --------------- TouchButtonMethd ---------------
//根据按钮跳转到相应的场景中
void MenuScene::menuCloseCallBack(CCObject* pSender)
{
    //点击音效
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_touchButton.wav");
    
    CCControlButton* button = (CCControlButton*)pSender;
    CCTransitionFade* transition;
    switch (button->getTag()) {
        case 1:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            transition = CCTransitionFade::create(0.2, Popularize::scene());
            CCDirector::sharedDirector()->pushScene(transition);
#endif
            break;
            
            
        case 2:
        {
            PropMarketsLayer* mallMarketsLayer = PropMarketsLayer::create();
            mallMarketsLayer->setPosition(CCPointZero);
            mallMarketsLayer->setPScene(1);
            this->addChild(mallMarketsLayer,4);
            this->setMenuButtonTouchFasle();
            break;
        }

        case 4:
            GuideScene* guide = GuideScene::create();
            guide->setPosition(CCPointZero);
            this->addChild(guide,4);
            this->setMenuButtonTouchFasle();
            break;
    }
    
}


//进入不同的游戏场景（平民，富豪）
void MenuScene::menuChoseScene(CCObject* pSender)
{
    //点击音效
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_touchButton.wav");
    pSceneNumber = ((CCMenuItemImage*)pSender)->getTag();
    
    //蒙板层
    colorLayer->setVisible(true);
    colorLayer->setOpacity(150);
    CCLabelTTF* pLabel = CCLabelTTF::create("Loading...", "MarkerFelt-Thin", 50);
    pLabel->setPosition( ccp(size.width / 2, size.height/2-30) );
    colorLayer->addChild(pLabel, 1);

    data.openDatabase();
    switch (pSceneNumber) {
        case 0:
            if (data.getFubi() < 10) {
                this->setMenuButtonTouchFasle();
                //富币不足，不能进入平民场
                menuInfoPrompt = CCSprite::create("ZF_Shoot_GameScene_dialogueBg.png");
                menuInfoPrompt->setPosition(ccp(size.width*0.5,size.height*0.5));
                this->addChild(menuInfoPrompt,7);
                CCMenuItemImage *confirm = CCMenuItemImage::create("ZF_Shoot_GameScene_dialogueConfirm.png", "ZF_Shoot_GameScene_dialogueConfirm.png", this, menu_selector(MenuScene::promptCallBack));
                confirm->setTag(1);
                confirm->setPosition(ccp(menuInfoPrompt->getContentSize().width/2,menuInfoPrompt->getContentSize().height/4));
                CCMenu* confirmMenu = CCMenu::create(confirm,NULL);
                confirmMenu->setPosition(CCPointZero);
                menuInfoPrompt->addChild(confirmMenu,5);
                
                CCSprite* normal = CCLabelTTF::create("Coins not Enough,can't get in Civilian", "Georgia-BoldItalic", 25);
                normal->setPosition(CCPointMake(menuInfoPrompt->getContentSize().width*0.5, menuInfoPrompt->getContentSize().height*0.7));
                menuInfoPrompt->addChild(normal);
            }
            else
            {
                //设置按钮不可用
                this->setMenuButtonTouchFasle();
                
                this->scheduleOnce(schedule_selector(MenuScene::transfer), 1);
            }
            break;
        case 1:
            if (data.getFubi() < 100) {
                this->setMenuButtonTouchFasle();
                //富币不足，不能进入富豪场
                menuInfoPrompt = CCSprite::create("ZF_Shoot_GameScene_dialogueBg.png");
                menuInfoPrompt->setPosition(ccp(size.width*0.5,size.height*0.5));
                this->addChild(menuInfoPrompt,7);
                CCMenuItemImage *confirm = CCMenuItemImage::create("ZF_Shoot_GameScene_dialogueConfirm.png", "ZF_Shoot_GameScene_dialogueConfirm.png", this, menu_selector(MenuScene::promptCallBack));
                confirm->setTag(1);
                confirm->setPosition(ccp(menuInfoPrompt->getContentSize().width/2,menuInfoPrompt->getContentSize().height/4));
                CCMenu* confirmMenu = CCMenu::create(confirm,NULL);
                confirmMenu->setPosition(CCPointZero);
                menuInfoPrompt->addChild(confirmMenu,5);
                
                CCSprite* normal = CCLabelTTF::create("Coins not Enough,can't get in Rich", "Georgia-BoldItalic", 25);
                normal->setPosition(CCPointMake(menuInfoPrompt->getContentSize().width*0.5, menuInfoPrompt->getContentSize().height*0.7));
                menuInfoPrompt->addChild(normal);
            }
            else
            {
                //设置按钮不可用
                this->setMenuButtonTouchFasle();
                
                this->scheduleOnce(schedule_selector(MenuScene::transfer), 1);
            }
            break;
            
        default:
            //设置按钮不可用
            this->setMenuButtonTouchFasle();
            this->scheduleOnce(schedule_selector(MenuScene::transfer), 1);
            
            break;
    }
    data.closeDatabase();
}


void MenuScene::transfer()
{
    CCTransitionCrossFade* transition = CCTransitionCrossFade::create(0.2, GameScene::sharedGameScene()->scene());
    //传值给游戏场景
    GameScene::sharedGameScene()->setpMenu(pSceneNumber);
    this->switchToGameScene(transition);
}


//根据参数跳转到不同的场景
void MenuScene::switchToGameScene(CCTransitionCrossFade* transition)
{
    CCDirector::sharedDirector()->replaceScene(transition);
    colorLayer->setVisible(false);
    this->setMenuButtonTouchTrue();
}


#pragma mark--------------- FreeToGetFubi ----------------
//同意领取富币
void MenuScene::menuCallAcceptFubiYes()
{
    this->setMenuButtonTouchTrue();
    this->getChildByTag(111)->setVisible(false);
    CCLog("-------MenuScene:同意领取富币--------");
    AcceptFreeFubi *freeFubiLayer = AcceptFreeFubi::create();
    this->addChild(freeFubiLayer, 1,113);
    this->scheduleOnce(schedule_selector(MenuScene::removeFreeFubiAnimation), 2.5);
    data.openDatabase();
    data.setFubi(data.getFubi()+kFreeFubi);
    this->updateFubi();
    data.closeDatabase();
}


//移除免费富币相关东西
void MenuScene::removeFreeFubiAnimation()
{
    this->removeChildByTag(111);
    this->removeChildByTag(113);
    
}


//从Layer层移除本身
void MenuScene::backToMenu()
{
    this->getChildByTag(kMenuTagConfirm)->removeFromParentAndCleanup(true);
}


//获取系统当前时间
long MenuScene::currentTimeNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    struct tm *tm;
    tm = localtime(&now.tv_sec);
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;
    int day = tm->tm_mday;
    int hour=tm->tm_hour;
    int minute=tm->tm_min;
    int second=tm->tm_sec;
    long millSecond=now.tv_sec * 1000 + now.tv_usec / 1000;
    currentDay = day;
    std::stringstream currentTime;
    currentTime<<year<<"-"<<month<<"-"<<day<<"  "<<hour<<":"<<minute<<":"<<second<<"   "<<millSecond;
    CCLog("currentTime is %s ",currentTime.str().c_str());
    return millSecond;
}


void MenuScene::setMenuButtonTouchFasle()
{
    sceneMenu->setTouchEnabled(false);
    richMenu->setTouchEnabled(false);
    headMenu->setTouchEnabled(false);
}

void MenuScene::setMenuButtonTouchTrue()
{
    sceneMenu->setTouchEnabled(true);
    richMenu->setTouchEnabled(true);
    headMenu->setTouchEnabled(true);
}


void MenuScene::promptCallBack(CCObject* pSender)
{
    CCActionInterval* scaleTo = CCScaleTo::create(0.2, 1.0, 0);
    menuInfoPrompt->runAction(scaleTo);
    menuInfoPrompt->removeFromParentAndCleanup(true);
    colorLayer->setVisible(false);
    this->setMenuButtonTouchTrue();
}



