/*******************************************************************

Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.

Filename: MenuScene.h

ProjectName: 射你妹

Author: P.Joe     Version: 1.0     Date: 13-6-13.

Description: 

FunctionList:   


********************************************************************/


#ifndef __Shoot__MenuScene__
#define __Shoot__MenuScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UserData.h"

#include "ColorLayer.h"


using namespace cocos2d;
using namespace extension;


class MenuScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    virtual void onExit();
    virtual void onEnter();
    static CCScene *scene();
    
    void initVarible();
    void initButton();
    void initSceneChoose();
    void initUserInfo();
    void updateUserPhoto();
    void updateFubi();
    void freeToGetFubi();
    
    void menuCloseCallBack(CCObject *pSender);
    void menuChoseScene(CCObject *pSender);
    void transfer();
    void switchToGameScene(CCTransitionCrossFade* transition);
    
    void menuCallAcceptFubiYes();
    void removeFreeFubiAnimation();
    void backToMenu();
    void setMenuButtonTouchFasle();
    void setMenuButtonTouchTrue();
    void promptCallBack(CCObject* pSender);
    
    long currentTimeNow();
    
    CREATE_FUNC(MenuScene);
    
    CCMenu *sceneMenu;
    CCMenu *richMenu;
    CCMenu* headMenu;
private:
    int p_Menu;
    int pSceneNumber;
    int index;
    int systemInfoIndex;
    int dynamicInfoUpdateTime;
    int currentDay;
    
    UserData data;
    ColorLayer* colorLayer;
    
    CCSprite* menuInfoPrompt;
    CCSize size;
    CCSprite* bgSprite;
    CCArray* systemInfo;
    CCLabelTTF* dynamicInfoLable;
    CCArray* prizeArray;
    CCPoint prizeStartPosition;
    CCPoint prizeEndPosition;
    CCPoint dynamicInfoPosition;
    
    CCControlButton* freeToGetCoin;
    CCControlButton* buyCoins;
    CCControlButton* exchangePrize;
    CCControlButton* playerGuide;
    CCControlButton* rankList;
    
    
    string userPhotoNormal[9];
    string userPhotoSelected[9];
    
};



#endif /* defined(__Shoot__MenuScene__) */
