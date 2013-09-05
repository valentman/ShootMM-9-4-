/*******************************************************************

Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.

Filename: LoadingGameScene.h

ProjectName: 射你妹

Author: P.Joe     Version: 1.0     Date: 13-6-27.

Description:

FunctionList:


********************************************************************/


#ifndef __Shoot__LoadingGameScene__
#define __Shoot__LoadingGameScene__

#include <iostream>
#include "cocos2d.h"
#include "MenuScene.h"
using namespace cocos2d;
USING_NS_CC;
using namespace std;

typedef enum
{
    kLabelTag,
    
}multiSpriteTags;

class LoadingGameScene : public cocos2d::CCLayer
{
    
public:
    virtual bool init();
    virtual void onExit();
    static CCScene* scene();
    
    void timerStep();
    void connectNetwork();
    void switchToMenuScene();
    
    
    
    CREATE_FUNC(LoadingGameScene);
    
private:
    CCSize size;
    CCSprite* promptSprite;
    CCSprite* bgSprite;
    
    int timeNo;
    int status_Network;
    
    
};




#endif /* defined(__Shoot__LoadingGameScene__) */
