/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: GuideScene.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-13.
 
 Description: 
 
 FunctionList:
 
 
 *******************************************************/

#include "GuideScene.h"
#include "MenuScene.h"

CCScene *GuideScene::scene()
{
    CCScene *scene = CCScene::create();
    GuideScene *layer = GuideScene::create();
    scene->addChild(layer);
    return scene;
}


void GuideScene::onExit()
{
    CCLayer::onExit();
}


bool GuideScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCLOG("/**~~~~~~~~~~~~~~~~GuideScene:init()~~~~~~~~~~~~~~~~~");
    //取出主屏幕的尺寸，以及初始化数据
    size = CCDirector::sharedDirector()->getVisibleSize();
//    CCSprite* whiteBg = CCSprite::create("ZF_Shoot_whiteBg.png",CCRectMake(0,0,size.width,size.height));
//    whiteBg->setPosition(ccp(size.width*0.5,size.height*0.5));
//    whiteBg->setContentSize(size);
//    this->addChild(whiteBg,0);
    
    CCSprite* helpBg = CCSprite::create("ZF_Shoot_help.png");
    helpBg->setAnchorPoint(ccp(0.5,0.5));
    helpBg->setPosition(ccp(size.width*0.5,size.height*0.5));
    this->addChild(helpBg,0);
    
    //1.create a container
    CCLayer* container = CCLayer::create();
    CCSprite* guide = CCSprite::create("ZF_Shoot_guide.png");
    guide->setAnchorPoint(ccp(0.5,1));
    guide->setPosition(ccp(size.width*0.5,size.height));
    container->addChild(guide,1);
    container->setContentSize(size);
    
    
    //2.create a scrollView
    CCScrollView* scrollView = CCScrollView::create(CCSizeMake(size.width*0.5, size.height*3));
    addChild(scrollView);
    scrollView->setAnchorPoint(ccp(0.5,0.5));
    scrollView->setPosition(ccp(10,size.height*0.23));
    
    //3.setOption
    scrollView->setBounceable(true);
    scrollView->setViewSize(CCSizeMake(size.width, size.height*0.55));
    scrollView->setContainer(container);
    scrollView->setDirection(kCCScrollViewDirectionVertical);
    scrollView->setTouchEnabled(true);
    scrollView->setDelegate(this);
    scrollView->unscheduleAllSelectors();
    
    
    //4.closeMenu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "ZF_Shoot_button_coinList_back2.png",
                                                          "ZF_Shoot_button_coinList_back1.png",
                                                          this,
                                                          menu_selector(GuideScene::menuCloseCallBack) );
    pCloseItem->setPosition( CCPointMake(size.width*0.5-235 , size.height*0.92) );
    pCloseItem->setTag(5);
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    addChild(pMenu);
    
    
    return true;
}


void GuideScene::scrollViewDidScroll(CCScrollView* view)
{
    CCLog("move");
    
}
void GuideScene:: scrollViewDidZoom(CCScrollView* view)
{
    CCLog("zoom");
}


void GuideScene::menuCloseCallBack(CCNode* pSender)
{
    ((MenuScene*)this->getParent())->sceneMenu->setTouchEnabled(true);
    ((MenuScene*)this->getParent())->richMenu->setTouchEnabled(true);
    ((MenuScene*)this->getParent())->headMenu->setTouchEnabled(true);
    this->removeFromParentAndCleanup(true);
}

