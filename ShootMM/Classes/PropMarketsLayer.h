/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: ParkBackground.h
 
 ProjectName: 射你妹
 
 Author: Kevin     Version: 1.0     Date: 13-8-8.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#ifndef __Shoot__PropMarketsLayer__
#define __Shoot__PropMarketsLayer__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UserData.h"
#include "TopBarLayer.h"
#include "UserData.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class PropMarketsLayer : public CCLayer ,public CCTableViewDelegate ,public CCTableViewDataSource
{
public:

    virtual bool init();
    void initTableView();
    void initPropsList();
    void initBackground();
    void setPScene(int kScene);
    static cocos2d::CCScene* scene();
    
    //1.tableView
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view);
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    
    
    //3.menu
    void menuItemCall2(CCObject *pSender);
    void menuItemCallToserver(int idx);
    void menuCloseCallBack(CCObject *pSender);
    
    
    void showPurchaseSuccess();
    void showPurchaseFail();
    void callBack(CCObject* pSender);
    void callBackLabel(CCObject* pSender);
    
    void updateCoinsNumber(int pNumber);
    
    CREATE_FUNC(PropMarketsLayer);
    
private:
    //3.coinList
    int coinListSize;
    int coinID[30];
    int coinListPrice[30];
    char* coinName[30];
    char* coinImageName[30];
    
    int tableViewX;
    int tableViewCellHeight;
    int sceneNumber;
    
    CCArray* propSprites;
    CCSize winSize;
    CCSize tableCellSize;
    CCSize bgSize;
    CCSprite *bg;
    CCSprite* successPromptSprite;
    CCSprite* failedPromptSprite;
    CCLabelTTF* coinsNumberLabel;
    CCMenu *menu;
    UserData data;
    string writablePathLocal;

    int reslut;

};


#endif /* defined(__Shoot__PropMarketsLayer__) */
