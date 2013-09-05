/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: GameScene.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-3.
 
 Description: 
 
 FunctionList:
 
 
********************************************************/


#ifndef __Shoot__GameScene__
#define __Shoot__GameScene__

#include "cocos2d.h"
#include "PromptLayer.h"
#include "ColorLayer.h"
#include "TopBarLayer.h"
#include "WeaponNotEnoughLayer.h"
#include "BossBallnoonSprite.h"
#include "PropMarketsLayer.h"
#include "UserData.h"

using namespace cocos2d;
using namespace extension;
using namespace std;

typedef enum
{
	kLayerTagPromptLayer,
    kLayerTagColorLayer,
    kLayerTagtopBarLayer,
    kLayerTagWeaponNotEnoughLayer,
    klayerTagPropMarketsLayer,
    
    kSpriteTaggirl,
    kSpriteTagboy,
    kSpriteTagInfo,
    kMenuTagConfirm,
    
} MultiLayerSceneTags;


class GameScene: public CCLayer,public CCTargetedTouchDelegate
{
public:
    
    //成员函数
#pragma mark --------------- initMethod ---------------
    ~GameScene();

    virtual void onExit();
    
    static GameScene* sharedGameScene();
    
    static cocos2d::CCScene* scene();
    
    void setpMenu(int p_Menu);
    
    void setIsPauseed(int p_Pauseed);
    
    virtual bool init();
    
    void initAll();
    
    void initVariable();
    
    void initBallnoonSprite();
    
    void initAnimation();
    
    void gameReadyPrompt();
    
    void resetPrompt();
    
    void beginScheduleAndActions();
    
    void getDataFromDB();
    
    void update(float dt);
    
#pragma mark --------------- BallnoonInitMethod ---------------
    
    void createBallnoonSprite();
    
    void createExchangeBossBallnoon(int kTag);
    
    void runBossSpriteAction(int kTag);
    
    void bossBallnoonSpritemove();
    
    void exchangeBallnoonSpriteMove();
    
    void runSpriteSequence(CCSprite* pSprite);
    
#pragma mark --------------- WeaponspriteMethod ---------------
    
    void weaponSpriteResetPosition();
    
    void weaponSpriteMoveTo();
    
#pragma mark-----爆出分数和奖品的核心逻辑函数    
    
    void ballnoonBoomEffects(CCSprite* pSprite,int kTag);
    
    void boomEffects(CCSprite* pSprite);
    
    void boomEffectsOfBoss(CCSprite* pSprite);
    
    void thunderBoomEffects();
    
    void thunderEffects();
    
    void stopAllBallnoonAction();
    
    void restarBallnoonAction();
    
    void updatePersonLife(int kLife);
    
    void updateLifespanOfBossBar(CCObject* pSender);
    
    void natureDisappear(CCNode* sernder);
    
    void callback1(CCNode* sender);
    
    void callbackBallnoonSprite(CCNode* sender);
    
    void callbackBossBallnoon();
    
    void callbackExchangeBallnoon();

    
#pragma mark --------------- showPrompt ---------------
#pragma mark -----本级目标达成，写入数据库本关的相关数据信息
    
    void showLevelComplete(int kTag);
    
    void showPrizePic();
    
    void showWeaponNotEnough(int kTag);
    
    void showScore(float i_Score);
    
    void setSpritesUnvisible();
    
    void setButtonTouchFalse();
    
    void setButtonTouchTrue();
    
    void setcolorLayerOpacityUp();
   
#pragma mark -----传参数给提示层(过关提示，武器不足，开始下一关)
    
    void bounceOutPrompt();
    
    void bounceOutWeaponNELayer(int pSceneNO,int kTagOfProps);
    
    void bounceOutShopLayer();
    
#pragma mark -----将本关相关数据post至服务器（重要）
    
    void moveLayer(CCNode* pNode,int kTag);
    
    void removePromptLayerLabels();
    
    void reInitScene();
    
    void backToMenuScene();
    
    void setBlackLightDisappear();
    
    void setcolorLayerOpacityDown();

    
#pragma mark --------------- TouchMehod ---------------
    
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    void checkForCollision();
    
#pragma mark --------------- 备用 ---------------

    void archiveWeaponNumber();

    void setWeaponNumbers(int kTag,int number);
    
    void guidePrompt();
    
    
    //全局成员变量
    CCSprite* propsSprite;
    
    CCPoint propsSpritePosition;
    
    TopBarLayer* topBarLayer;
    
    int pSceneNumber;
    
private:
    
    //成员变量
    CCArray* ballnoonSprites;
    
    CCArray* bossBallnoonSprites;
    
    CCArray* propSprites;
    
    CCString* prizeName;
    
    CCDictionary* activeBallnoonSprites;
    
    UserData data;
    
    PromptLayer* promptLayer;
    
    ColorLayer* colorLayer;
    
    WeaponNotEnoughLayer* weaponNotEnoughLayer;
    
    PropMarketsLayer* propMarketsLayer;
    
    BossBallnoonSprite* bossSprite;
    
    CCSprite* green;
    
    CCSprite* red;
    
    CCSprite* bossBallnoonSprite;
    
    CCSprite* exchangeBallnoonSprite;
    
    CCSprite* light;
    
    CCSprite* boy;
    
    CCSprite* girl;
    
    CCSprite* weaponSprite;
    
    CCSprite* giftBoxopen;
    
    CCSprite* giftBoxclose;
    
    CCSprite* boomSprite;
    
    CCSprite* dartSprite;
    
    CCSprite* fireworkSprite;
    
    CCSprite* indicateSprite;
    
    CCSprite* infoPrompt;
    
    CCPoint startLocation;
    
    CCPoint endLocation;
    
    CCPoint destPosition;
    
    CCPoint giftBoxPosition;
    
    CCPoint disBallnoonPosition;
    
    CCSize size;
    
    CCAnimate* boomAnimate;
    
    CCLabelTTF* scoreSprite;
    
    CCSequence* sequence;
    
    int isSuccess,isPauseed;

    int isPropsSpriteReset;
    
    int numberOfWeapon1,numberOfWeapon2,numberOfWeapon3,numberOfWeapon4;
    
    int integrationScore,targetIntegrationScore;
    
    int isshootedBallnoon,shootDartNumber,shootedBallnoonNumber,isOutOfScreen;
    
    int tempTag,opacity;
    
    float dartSpeedDuration,ratio,ballnoonSpeedDuration,ballnoonSizeRatio;
    
    float ballnoonSpriteRadius,dartSpriteRadius,maxCollisionDistance;
    
    //触摸相关变量
    float offSetX,offSetY,offSetXY,pTan,pSin,pCos,rotateNumber,slipSpeed; 
    
    
    //boss气球的生命值
    const char* bossPicName;
    float lifespanOfBoss,leftLifeSpan,speedOfBoss;
    int isappearBoss,isappearExchange;
    
    //人物生命值
    float lifeSpanOfPerson,leftLifeOfPerson;
    
    
    int excerciseLevelTarget,normalLevelTarget,richLevelTarget,levelTarget;
    double prizeId;
    double prizeValue;
    int prizeType;
    double exchangeableFuBi;
    
    //玩家获得的奖品富币信息变量
    int score;
    int dj,xj;
    int isFuBiEnough;
    
    int exchangeTime,bossTime;
    
    CREATE_FUNC(GameScene);
};


#endif 