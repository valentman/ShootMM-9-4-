/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: GuideScene.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-13.
 
 Description: 
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__GuideScene__
#define __Shoot__GuideScene__

#include <iostream>
#include "cocos-ext.h"

using namespace cocos2d;
using namespace extension;

class GuideScene: public CCLayer,CCScrollViewDelegate
{
public:
    virtual bool init();
    virtual void onExit();
    static CCScene *scene();
    
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    
    void menuCloseCallBack(CCNode* pSender);
    CREATE_FUNC(GuideScene);
    
private:
    CCSize size;
    
    
};



#endif /* defined(__Shoot__GuideScene__) */
