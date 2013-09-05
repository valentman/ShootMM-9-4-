/*******************************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd. All rights reserved.
 
 Filename: AppDelegate.cpp 
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-13.
 
 Description:
 
 FunctionList:
 
 
********************************************************************/


#include "AppDelegate.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "LoadingGameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCEGLView *pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    pEGLView->setDesignResolutionSize(size.width, size.height, kResolutionShowAll);
    
    // create a scene. it's an autorelease object
    CCScene *pScene = LoadingGameScene::scene();
    CCTransitionCrossFade* transition = CCTransitionCrossFade::create(0.3, pScene);
    
    // run
    pDirector->runWithScene(transition);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
