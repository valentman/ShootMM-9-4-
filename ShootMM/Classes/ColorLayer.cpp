/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: ColorLayer.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-25.
 
 Description:  定义为一个隔断层，
 
 FunctionList:
 
 
 *******************************************************/

#include "ColorLayer.h"

bool ColorLayer::init()
{
    if (!CCLayerColor::init()) {
        return false;
    }
    CCLog("/**~~~~~~~~~~~~~~~~ColorLayer init()~~~~~~~~~~~~~~~~");
    this->setTouchEnabled(false);
    CCTouchDispatcher* touchdispatcher = new CCTouchDispatcher();
    touchdispatcher->init();
    touchdispatcher->addTargetedDelegate(this, -129, true);
    return true;
}

void ColorLayer::onExit()
{
    CCLayerColor::onExit();
    CCLog("~~~~~~~~~~~~~~~~ColorLayer:onExit()~~~~~~~~~~~~~~~~~**/");
}