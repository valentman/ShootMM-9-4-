/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: Popularize.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-13.
 
 Description: 
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__Popularize__
#define __Shoot__Popularize__

#include "cocos2d.h"
#include "cocos-ext.h"


using namespace cocos2d;
using namespace extension;

class Popularize : public CCLayer 
{
public:
    virtual bool init();
    virtual void onExit();
    
    static cocos2d::CCScene *scene();
    void menuCloseCallBack(CCObject *pSender);
    CCControlButton* backToMenuButton;
    
    
    CREATE_FUNC(Popularize);
    
};

#endif /* defined(__Shoot__Popularize__) */
