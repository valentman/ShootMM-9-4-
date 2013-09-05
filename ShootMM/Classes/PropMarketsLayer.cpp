/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: ParkBackground.cpp
 
 ProjectName: 射你妹
 
 Author: Kevin     Version: 1.0     Date: 13-8-8.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#include "PropMarketsLayer.h"
#include "cocos-ext.h"
#include "GameScene.h"
#include "UserData.h"
#include "MenuScene.h"

USING_NS_CC;

#pragma mark--------------- InitMethod ----------------
bool PropMarketsLayer::init()
{
    
    if (!CCLayer::init()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    sceneNumber = 0;
    this->initBackground();
    this->initPropsList();
    this->initTableView();
    return  true;
}


void PropMarketsLayer::setPScene(int kScene)
{
    sceneNumber = kScene;
}


void PropMarketsLayer::initBackground()
{
    bg = CCSprite::create("ZF_Shoot_background_coinList.png");
    bgSize = bg->getContentSize();
    bg->setPosition(ccp(winSize.width/2,winSize.height/2+30));
    this->addChild(bg);
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "ZF_Shoot_button_coinList_back2.png",
                                                          "ZF_Shoot_button_coinList_back1.png",
                                                          this,
                                                          menu_selector(PropMarketsLayer::menuCloseCallBack) );
    pCloseItem->setPosition( CCPointMake(bgSize.width*0.06 , bgSize.height*0.94) );
    pCloseItem->setTag(5);
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    bg->addChild(pMenu);
    
    
    coinsNumberLabel = new CCLabelTTF();
    coinsNumberLabel->init();
    this->addChild(coinsNumberLabel);
    data.openDatabase();
    this->updateCoinsNumber(data.getFubi());
    data.closeDatabase();
}


void PropMarketsLayer::initPropsList()
{
    coinListSize = 3;

    coinID[0] = 1;
    coinID[1] = 2;
    coinID[2] = 3;

    coinListPrice[0] = 10;
    coinListPrice[1] = 20;
    coinListPrice[2] = 40;
    
    coinName[0] = "Fire";
    coinName[1] = "Star";
    coinName[2] = "Crescent";
    
    propSprites = new CCArray();
    propSprites->init();
    CCString* fire = CCString::create("ZF_Shoot_GameScene_fire.png");
    CCString* star = CCString::create("ZF_Shoot_GameScene_star.png");
    CCString* moon = CCString::create("ZF_Shoot_GameScene_moon.png");
    
    propSprites->addObject(fire);
    propSprites->addObject(star);
    propSprites->addObject(moon);
    

       

}


void PropMarketsLayer::initTableView()
{
    //2.init tableView
    this->tableViewX = winSize.width*0.17;
    
    //获取奖品表格的高度
    CCSprite *pSprite = CCSprite::create("ZF_Shoot_Button_gridItem.png");
    
    tableCellSize = pSprite->getContentSize();
    this->tableViewCellHeight = tableCellSize.height;
    
    CCTableView *tableView = CCTableView::create(this, CCSizeMake(bgSize.width*0.998,bgSize.height*0.748));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setAnchorPoint(ccp(0, 0));
    tableView->setPosition( ccp(1,winSize.height*0.1));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    bg->addChild(tableView);
    tableView->reloadData();
}


#pragma mark --------------- TableViewMethods ---------------
CCTableViewCell* PropMarketsLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    
    CCSprite *prizePicture = CCSprite::create(((CCString*)propSprites->objectAtIndex(idx))->getCString());
    prizePicture->setPosition(ccp(tableCellSize.width*0.1, tableCellSize.height*0.5));
    prizePicture->setScale(1);
    prizePicture->setTag(122);
    
    if (!pCell) {
        
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        //1.表格背景ZF_Shoot_Button_gridItem
        CCSprite *pSprite = CCSprite::create("ZF_Shoot_Button_gridItem.png");
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setPosition(CCPointZero);
        pSprite->setScaleX(bgSize.width/tableCellSize.width);
        pCell->addChild(pSprite);
        
        //2.prizePicture
        pCell->removeChildByTag(122);
        pCell->addChild(prizePicture);
        
        //3.coinName
        CCLabelTTF *pLabeName = CCLabelTTF::create(coinName[idx], "Arial", 28);
        pLabeName->setPosition(ccp(tableCellSize.width*0.25, tableCellSize.height*0.7));
        pLabeName->setAnchorPoint(ccp(0,0.5));
        pLabeName->setColor(ccc3(234, 160, 0));
        pLabeName->setTag(123);
        pCell->addChild(pLabeName);
        
        
        //number
        CCLabelTTF *pLabelNumber = CCLabelTTF::create("10 Piece", "Arial", 28);
        pLabelNumber->setPosition(ccp(tableCellSize.width*0.5, tableCellSize.height*0.7));
        pLabelNumber->setAnchorPoint(ccp(0,0.5));
        pLabelNumber->setColor(ccc3(234, 160, 0));
        pLabelNumber->setTag(125);
        pCell->addChild(pLabelNumber);
        
        //4.prizePrice
        char priceChar[11];
        sprintf(priceChar, "%d",coinListPrice[idx]);
        string t1 = "Cost:";
        t1 = t1 + priceChar;
        CCLabelTTF *pLabelPrice = CCLabelTTF::create(t1.c_str(), "Arial", 28);
        pLabelPrice->setPosition(ccp(tableCellSize.width*0.25, tableCellSize.height*0.25));
        pLabelPrice->setAnchorPoint(ccp(0,0.5));
        pLabelPrice->setTag(124);
        pLabelPrice->setColor(ccc3(234, 160, 0));
        pCell->addChild(pLabelPrice);
        
        //5.购买按钮
        CCMenuItemImage *itemImage = CCMenuItemImage::create("ZF_Shoot_button_coinList_buy1.png", "ZF_Shoot_button_coinList_buy2.png", this, menu_selector(PropMarketsLayer::menuItemCall2));
        if (itemImage->getTag() == -1) {
            itemImage->setTag(idx);
        }
        itemImage->setPosition(ccp(tableCellSize.width*0.85, tableCellSize.height*0.5));
        menu = CCMenu::create(itemImage,NULL);
        menu->setPosition(CCPointZero);
        pCell->addChild(menu, 1);
        
        
    }else{
        pCell->removeChildByTag(122);
        pCell->addChild(prizePicture);
        
        CCLabelTTF *pLabeName = (CCLabelTTF*)pCell->getChildByTag(123);
        pLabeName->setString(coinName[idx]);
        
        char priceChar[11];
        sprintf(priceChar, "%d",this->coinListPrice[idx]);
        string t1 = "Cost: ";
        string t2 = " coins";
        t1 = t1 + priceChar + t2;
        CCLabelTTF *pLabelPrice = (CCLabelTTF*)pCell->getChildByTag(124);
        pLabelPrice->setString(t1.c_str());
    }
    return pCell;
}


void PropMarketsLayer::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
    
}


CCSize PropMarketsLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(this->tableViewX, this->tableViewCellHeight-5);
}


unsigned int PropMarketsLayer::numberOfCellsInTableView(CCTableView *table)
{
    return this->coinListSize;
    
}


void PropMarketsLayer::scrollViewDidScroll(CCScrollView *view)
{
    
}


void PropMarketsLayer::scrollViewDidZoom(CCScrollView *view)
{
    
}


#pragma mark---------------- TouchEventMethod ---------------

//点击了购买按钮
void PropMarketsLayer::menuItemCall2(CCObject *pSender)
{
    //获取点击的是第几行单元格
    CCTableViewCell *cell = (CCTableViewCell*)(((CCMenuItemImage*)pSender)->getParent()->getParent());
    int indexOfCell = cell->getIdx();
    char* propsSpriteName = coinName[indexOfCell];
    CCLog(propsSpriteName);
    int price = coinListPrice[indexOfCell];
    CCLog("price:%d",price);
    int propID = this->coinID[indexOfCell];
    CCLog("propID:%d",propID);
    int fireNO,starNO,moonNO,fuBiNO,isFuBiEnough = 0;
    
    
    data.openDatabase();
    //这里更新数据库，同时更新topbarlayer里的武器数量
    switch (indexOfCell) {
        case 0:
            if (data.getFubi() < 10) {
                isFuBiEnough = 1;
                break;
            }
            fireNO = 10+data.getFireNumber();
            fuBiNO = data.getFubi()-10;
            data.setFireNumber(fireNO);
            if (sceneNumber != 1) {
                GameScene* game = GameScene::sharedGameScene();
                game->topBarLayer->updateNumberOfWeapon(2, fireNO);
                game->setWeaponNumbers(2, fireNO);
            }
            break;
        case 1:
            if (data.getFubi() < 20) {
                isFuBiEnough = 1;
                break;
            }
            starNO = 10+data.getStarNumber();
            fuBiNO = data.getFubi()-20;
            data.setStarNumber(starNO);
            if (sceneNumber != 1) {
                GameScene* game = GameScene::sharedGameScene();
                game->topBarLayer->updateNumberOfWeapon(3, starNO);
                game->setWeaponNumbers(3, starNO);
            }
            
            break;
        case 2:
            if (data.getFubi() < 40) {
                isFuBiEnough = 1;
                break;
            }
            moonNO = 10+data.getMoonNumber();
            fuBiNO = data.getFubi()-40;
            data.setMoonNumber(moonNO);
            if (sceneNumber != 1) {
                GameScene* game = GameScene::sharedGameScene();
                game->topBarLayer->updateNumberOfWeapon(4, moonNO);
                game->setWeaponNumbers(4, moonNO);
            }
            
            break;
            
        default:
            break;
    }
    data.setFubi(fuBiNO);
    this->updateCoinsNumber(fuBiNO);
    if (sceneNumber == 1) {
        ((MenuScene*)this->getParent())->updateFubi();
    }
    

    if (isFuBiEnough) {
        //fubi not enough prompt
        CCString *showScore = CCString::createWithFormat("Coin no enough!");
        CCSprite* scoreSprite = CCLabelTTF::create(showScore->getCString(), "Georgia-BoldItalic", 40);
        scoreSprite->setColor(ccRED);
        scoreSprite->setTag(22);
        this->addChild(scoreSprite);
        scoreSprite->setPosition(ccp(bg->getContentSize().width/2,bg->getContentSize().height*0.57));
        scoreSprite->setScale(0);
        CCActionInterval* scaleToOfScore = CCScaleTo::create(0.15, 1.0f);
        CCMoveTo* moveToOfScore = CCMoveTo::create(1, ccp(bg->getContentSize().width/2,bg->getContentSize().height*0.57 + 15));
        CCMoveTo* moveToOfScore1 = CCMoveTo::create(0.5, ccp(bg->getContentSize().width/2,bg->getContentSize().height*0.57 + 20));
        CCActionInterval* fadeOutOfScore = CCFadeOut::create(0.5);
        CCActionInterval* actionOfScore = CCSpawn::create(moveToOfScore1,fadeOutOfScore,NULL);
        CCCallFuncN* funcn = CCCallFuncN::create(this, callfuncN_selector(PropMarketsLayer::callBackLabel));
        CCSequence *sequence1OfScore = CCSequence::create(scaleToOfScore,moveToOfScore,actionOfScore,funcn,NULL);
        
        scoreSprite->runAction(sequence1OfScore);
    }
}


void PropMarketsLayer::menuCloseCallBack(cocos2d::CCObject *pSender)
{
    if (1 == sceneNumber) {
        ((MenuScene*)this->getParent())->sceneMenu->setTouchEnabled(true);
        ((MenuScene*)this->getParent())->richMenu->setTouchEnabled(true);
        ((MenuScene*)this->getParent())->headMenu->setTouchEnabled(true);
        this->removeFromParentAndCleanup(true);
    }
    else
    {
        GameScene::sharedGameScene()->moveLayer(this, ((CCControlButton*)pSender)->getTag());
    }
    
}



//显示购买成功，同时去更新武器数量
void PropMarketsLayer::showPurchaseSuccess()
{
    //显示购买成功提示框
    CCActionInterval* scaleTo1 = CCScaleTo::create(1.0, 1.0, 0.95);
    CCActionInterval* scaleTo2 = CCScaleTo::create(1.0, 0.95, 1.0);
    CCSequence* sequence = CCSequence::create(scaleTo2,scaleTo1,NULL);
    CCRepeatForever* rotate = CCRepeatForever::create(sequence);
    
    successPromptSprite = CCSprite::create("ZF_Shoot_GameScene_purchaseWeaponBg.png");
    successPromptSprite->setPosition(ccp(bg->getContentSize().width/2,bg->getContentSize().height*0.57));
    bg->addChild(successPromptSprite,1);
    CCMenuItemImage *confirm = CCMenuItemImage::create("ZF_Shoot_GameScene_purchaseWeaponConfirm.png", "ZF_Shoot_GameScene_purchaseWeaponConfirm.png", this, menu_selector(PropMarketsLayer::callBackLabel));
    confirm->setTag(1);
    confirm->setPosition(ccp(successPromptSprite->getContentSize().width/2,successPromptSprite->getContentSize().height/4));
    CCMenu* confirmMenu = CCMenu::create(confirm,NULL);
    confirmMenu->setPosition(CCPointZero);
    confirm->runAction(rotate);
    successPromptSprite->addChild(confirmMenu,1);
    
    //调用TopBarLayer的武器更新函数更新武器数量
    
}


void PropMarketsLayer::showPurchaseFail()
{
    CCActionInterval* scaleTo1 = CCScaleTo::create(1.0, 1.0, 0.95);
    CCActionInterval* scaleTo2 = CCScaleTo::create(1.0, 0.95, 1.0);
    CCSequence* sequence = CCSequence::create(scaleTo2,scaleTo1,NULL);
    CCRepeatForever* rotate = CCRepeatForever::create(sequence);
    
    failedPromptSprite = CCSprite::create("ZF_Shoot_Loading_prompt.png");
    failedPromptSprite->setPosition(ccp(bg->getContentSize().width/2,bg->getContentSize().height*0.4));
    this->addChild(failedPromptSprite,1);
    CCMenuItemImage *confirm = CCMenuItemImage::create("ZF_Shoot_Loading_confirm.png", "ZF_Shoot_Loading_confirm.png", this, menu_selector(PropMarketsLayer::callBack));
    confirm->setTag(2);
    confirm->setPosition(ccp(failedPromptSprite->getContentSize().width/2,failedPromptSprite->getContentSize().height/4));
    CCMenu* confirmMenu = CCMenu::create(confirm,NULL);
    confirmMenu->setPosition(CCPointZero);
    confirm->runAction(rotate);
    failedPromptSprite->addChild(confirmMenu,1);
}

void PropMarketsLayer::callBack(CCObject* pSender)
{
    switch (((CCMenuItemImage*)pSender)->getTag()) {
        case 1:
            this->menu->setTouchEnabled(true);
            successPromptSprite->removeFromParentAndCleanup(true);
            break;
        case 2:
            failedPromptSprite->removeFromParentAndCleanup(true);
            break;
        case 22:
            failedPromptSprite->removeFromParentAndCleanup(true);
            break;
        default:
            break;
    }

}


void PropMarketsLayer::callBackLabel(CCObject *pSender)
{
    CCSprite* pSprite = (CCSprite*)pSender;
    pSprite->setScale(0);
    this->removeChild(pSprite, true);
}


void PropMarketsLayer::updateCoinsNumber(int pNumber)
{
    coinsNumberLabel->removeFromParentAndCleanup(true);
    coinsNumberLabel = CCLabelTTF::create((CCString::createWithFormat("%d",pNumber))->getCString(), "Arial", 30);
    coinsNumberLabel->setPosition(CCPointMake(bgSize.width*0.3 , bgSize.height*0.055) );
    coinsNumberLabel->setScale(1);
    bg->addChild(coinsNumberLabel);
    
}


