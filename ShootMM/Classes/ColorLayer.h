/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: ColorLayer.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-25.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __myTest__ColorLayer__
#define __myTest__ColorLayer__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class ColorLayer: public CCLayerColor
{
public:
    virtual bool init();
    virtual void onExit();
    
    CREATE_FUNC(ColorLayer);
    
};




#endif /* defined(__myTest__ColorLayer__) */
