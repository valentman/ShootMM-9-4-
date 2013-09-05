/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: GameScene.cpp
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-3.
 
 Description: 游戏的主要核心逻辑部分，包括射飞镖，升气球，弹出各种提示等。
 
 FunctionList:
 
 
********************************************************/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "GameScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "DartSprite.h"
#include "FireworkSprite.h"
#include "ArrowSprite.h"
#include "StarSprite.h"
#include "BossBallnoonSprite.h"
#include "CityBackground.h"
#include "ParkBackground.h"
#include "GolfBackground.h"
#include "TopBarLayer.h"
#include "UserData.h"
#include "cocos2d.h"
#include "MenuScene.h"
#include "PropMarketsLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace extension;
using namespace std;

#define kParkBackgroundAudio "ZF_background_park.mp3"
#define kCityBackgroundAudio "ZF_background_city.mp3"
#define kGolfBackgroundAudio "ZF_background_golf.mp3"
#define kScreenSizeOfDevice   1280


//单例模式设置GameScene静态变量
static GameScene* p_sharedGameScene = NULL;



//析构函数
GameScene::~GameScene()
{
    //听到所有定时器和音效引擎
    this->unscheduleAllSelectors();
    CCLog("----------GameScene over ~");
}



void GameScene::onExit()
{
    CCAnimationCache::sharedAnimationCache()->purgeSharedAnimationCache();
    CCDirector::sharedDirector()->purgeCachedData();
    CCLayer::onExit();
    CCLOG("~~~~~~~~~~~~~~~~GameScene:onExit()~~~~~~~~~~~~~~~~~**/");
}



//获取GameScene
GameScene* GameScene::sharedGameScene()
{
    if (!p_sharedGameScene) {
        p_sharedGameScene = new GameScene();
        p_sharedGameScene->init();
    }
    return p_sharedGameScene;
}



#pragma mark --------------- initMethod ---------------
//场景的初始化
CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    
    GameScene* layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}



//接受选关场景传值的传值函数，表明是哪个场景（练习场，平民场，富豪场）
void GameScene::setpMenu(int p_Menu)
{
    pSceneNumber = p_Menu;
    this->initAll();
}


void GameScene::setIsPauseed(int p_Pauseed)
{
    isPauseed = p_Pauseed;
}



//游戏主层的初始化
bool GameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCLOG("/**~~~~~~~~~~~~~~~~GameScene:init()~~~~~~~~~~~~~~~~~");
    
    //单例模式，将本场景曾设置为静态成员变量
    p_sharedGameScene = this;
    return true;
}



//初始化游戏层以上的所有东西
void GameScene::initAll()
{
    //获取设备屏幕大小
    size = CCDirector::sharedDirector()->getVisibleSize();
    data.openDatabase();
    
    
    //设置触摸可用，并设优先级
    this->setTouchEnabled(true);
    this->setTouchPriority(0);
    
    
    //是否第一次进入游戏
//    if (data.getIsFirstPlayGame()) {
//        //导向
        this->guidePrompt();
//        data.openDatabase();
//        data.setIsFirstPlayGame(0);
//    }
    
    
    this->initVariable();
    this->initBallnoonSprite();
    this->initAnimation();
    
    
    //1.init PromptLayer
    promptLayer = PromptLayer::create();
    this->addChild(promptLayer,5,kLayerTagPromptLayer);
    promptLayer->setPosition(ccp(0, size.height*2));
    
    colorLayer = ColorLayer::create();
    this->addChild(colorLayer, 4, kLayerTagColorLayer);
    colorLayer->setColor(ccc3(0, 0, 0));
    colorLayer->setPosition(CCPointZero);
    colorLayer->setOpacity(0);
    
    topBarLayer = TopBarLayer::create();
    this->addChild(topBarLayer,3,kLayerTagtopBarLayer);
    topBarLayer->setPosition(CCPointZero);
    
    
    weaponNotEnoughLayer = WeaponNotEnoughLayer::create();
    this->addChild(weaponNotEnoughLayer,4,kLayerTagWeaponNotEnoughLayer);
    weaponNotEnoughLayer->setPosition(ccp(0, size.height*2));
    
    propMarketsLayer = PropMarketsLayer::create();
    this->addChild(propMarketsLayer,4,klayerTagPropMarketsLayer);
    propMarketsLayer->setPosition(ccp(0, size.height*2));
    
    //下面初始化的东西只有在平民场和富豪场才出现
    if (pSceneNumber == 0 || pSceneNumber == 1) {
        topBarLayer->pMenu->setTouchEnabled(false);
                
        //2.进入游戏提示
        infoPrompt = CCSprite::create("ZF_Shoot_GameScene_dialogueBg1.png");
        infoPrompt->setPosition(ccp(-size.width*0.5,size.height*0.5));
        addChild(infoPrompt,4,kSpriteTagInfo);

        switch (pSceneNumber) {
            case 0:
            {
                CCSprite* normal = CCLabelTTF::create("It will be cost you 10 coins this Level", "Georgia-BoldItalic", 25);
                normal->setPosition(CCPointMake(infoPrompt->getContentSize().width*0.5, infoPrompt->getContentSize().height*0.6));
                infoPrompt->addChild(normal);
                break;
            }
            case 1:
            {
                CCSprite* rich = CCLabelTTF::create("It will be cost you 100 coins this Level", "Georgia-BoldItalic", 25);
                rich->setPosition(CCPointMake(infoPrompt->getContentSize().width*0.5, infoPrompt->getContentSize().height*0.6));
                infoPrompt->addChild(rich);
                break;
            }
        }
    }

    
    //2.initBackgroundSpriteAndBackgroundMusic
    CCSprite* bgSprite;
    
    //预加载音效
    SimpleAudioEngine::sharedEngine()->preloadEffect("ZF_boom1.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("ZF_Shoot_Effects_getPrize.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("ZF_Shoot_Effects_bounceOutPrompt.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("ZF_Shoot_Effects_levelcomplete.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("ZF_Shoot_Effects_bounceBackPrompt.wav");
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7);
    
    //根据场景的不同加载不同的背景图和背景音乐
    switch (pSceneNumber) {
        case 0:
            bgSprite = (CCSprite*)new ParkBackground();
            SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(kParkBackgroundAudio);
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic(kParkBackgroundAudio, true);
            break;
        case 1:
            bgSprite = (CCSprite*)new GolfBackground();
            SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(kGolfBackgroundAudio);
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic(kGolfBackgroundAudio, true);
            break;
        case 2:
            bgSprite = (CCSprite*)new CityBackground();
            
            SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(kCityBackgroundAudio);
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic(kCityBackgroundAudio, true);
            break;
        default:
            break;
    }
    bgSprite->setPosition(CCPointZero );
    this->addChild(bgSprite, 0);
    
    //添加人物
    boy = CCSprite::create("ZF_Shoot_GameScene_boy.png");
    boy->setPosition(ccp(180,180));
    this->addChild(boy,1,kSpriteTagboy);
    girl = CCSprite::create("ZF_Shoot_GameScene_girl.png");
    girl->setPosition(ccp(50,180));
    this->addChild(girl,1,kSpriteTaggirl);
    
    //人物血量
    CCPoint lifespanPosition = CCPointMake(0, boy->getContentSize().height+20);
    green = CCSprite::create("ZF_Shoot_GameScene_person1.png");
    green->setAnchorPoint(ccp(0,0.5));
    green->setPosition(lifespanPosition);
    red = CCSprite::create("ZF_Shoot_GameScene_person2.png");
    red->setAnchorPoint(ccp(0,0));
    red->setPosition(CCPointZero);
    boy->addChild(green,2);
    green->addChild(red,3);
    

    //3.initWeaponAndIndicate()
    propsSpritePosition = ccp(230, 220);
    
    //添加武器发射器
    weaponSprite = CCSprite::create("ZF_Shoot_Game_weapon.png");
    weaponSprite->setAnchorPoint(ccp(0.5, 0.7));
    weaponSprite->setPosition(propsSpritePosition);
    this->addChild(weaponSprite,1);
    
    //添加飞镖
    propsSprite = (CCSprite*)new DartSprite();
    propsSprite->setAnchorPoint(CCPointMake(0.9, 0.5));
    propsSprite->setTag(1);
    propsSprite->setPosition(propsSpritePosition);
    propsSprite->setScale(0.5);
    this->addChild(propsSprite, 1);
    propsSprite->setVisible(false);
    
    //添加一个指示箭头
    indicateSprite = CCSprite::create("ZFIndicate.png");
    indicateSprite->setAnchorPoint(ccp(0, 0.5));
    indicateSprite->setPosition(propsSpritePosition);
    indicateSprite->setScale(0);
    this->addChild(indicateSprite,1);

    //4.readData From DB
    this->getDataFromDB();
    
    //平民场、富豪场需要显示本关的提示信息
    if (pSceneNumber < 2) {
        this->gameReadyPrompt();
    }
    else
    {
        this->schedule(schedule_selector(GameScene::createBallnoonSprite), 1.0f);
        this->scheduleUpdate();
    }
}



void GameScene::initVariable()
{
    //初始化各数据（背景，气球，飞镖道具，提示层，变量，道具切换，加载服务器数据）
    score = 0;
    shootDartNumber = 0;
    isshootedBallnoon = 0;
    isOutOfScreen = 0;
    ballnoonSizeRatio = 1.0;
    ballnoonSpeedDuration = 8;
    isappearExchange = 0;
    isappearBoss = 0;
    leftLifeSpan = 0;
    isFuBiEnough = 0;
    isPauseed = 0;
    exchangeTime = 60;
    bossTime = 60;
    leftLifeOfPerson = 0;
    
    //气球的数组初始化
    ballnoonSprites = new CCArray();
    ballnoonSprites->init();
    
    bossBallnoonSprites = new CCArray();
    bossBallnoonSprites->init();
    
    activeBallnoonSprites = new CCDictionary();
    activeBallnoonSprites->create();
    
    propSprites = new CCArray();
    propSprites->init();
    
    CCString* fire = CCString::create("ZF_Shoot_GameScene_fire.png");
    CCString* star = CCString::create("ZF_Shoot_GameScene_star.png");
    CCString* moon = CCString::create("ZF_Shoot_GameScene_moon.png");
    propSprites->addObject(fire);
    propSprites->addObject(star);
    propSprites->addObject(moon);
    
    CCLog("3. ----------GameScene:initVariable() right!");
}



void GameScene::initBallnoonSprite()
{
    CCSprite* ballnoonSprite;
    CCString* bossBallnoon;
    
    int n = 1;
    
    //通过for循环往气球数组插入12个普通气球对象
    for (int k = 1; k<15; k++) {
        bossBallnoon = CCString::createWithFormat("ZFBoss%d.png",k);
        bossBallnoonSprites->addObject(bossBallnoon);
    }
    
    //通过for循环往气球数组插入12个普通气球对象
    for (int i = 1; i<5; i++) {
        for (int j = 1; j<4; j++) {
            char *ballnoon = new char;
            sprintf(ballnoon, "ZFball%d.png",j);
            ballnoonSprite = CCSprite::create(ballnoon);
            ballnoonSprite->setScale(0);
            ballnoonSprite->setTag(n++);
            ballnoonSprite->setAnchorPoint(ccp(0.5, 0.7));
            ballnoonSprites->addObject(ballnoonSprite);
            ballnoonSpriteRadius = ballnoonSprite->getContentSize().width;
        }
    }
    CCLog("5. ----------GameScene:initBallnoonSprite() right! /ballnoonSprites->count()=%d",ballnoonSprites->count());
}


//初始化动画帧缓存
void GameScene::initAnimation()
{
    CCAnimation* boomAnimation = CCAnimation::create();
    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_boom1.png");
    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_boom2.png");
    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_boom3.png");
    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_boom4.png");
    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_boom5.png");
    boomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_boom6.png");
    boomAnimation->setDelayPerUnit(0.08f);
    boomAnimation->setRestoreOriginalFrame(true);
    CCAnimationCache::sharedAnimationCache()->addAnimation(boomAnimation, "boomAnimation");
    
    CCAnimation* thunderAnimation = CCAnimation::create();
    thunderAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder1.png");
    thunderAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder2.png");
    thunderAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder3.png");
    thunderAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder4.png");
    thunderAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder5.png");
    thunderAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder6.png");
    thunderAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder7.png");
    thunderAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_thunder8.png");
    thunderAnimation->setDelayPerUnit(0.05f);
    thunderAnimation->setRestoreOriginalFrame(true);
    CCAnimationCache::sharedAnimationCache()->addAnimation(thunderAnimation, "thunderAnimation");
    
    CCAnimation* bossBoomAnimation = CCAnimation::create();
    bossBoomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_bossboom1.png");
    bossBoomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_bossboom2.png");
    bossBoomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_bossboom3.png");
    bossBoomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_bossboom4.png");
    bossBoomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_bossboom5.png");
    bossBoomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_bossboom6.png");
    bossBoomAnimation->addSpriteFrameWithFileName("ZF_Shoot_GameScene_bossboom7.png");
    bossBoomAnimation->setDelayPerUnit(0.05f);
    bossBoomAnimation->setRestoreOriginalFrame(true);
    CCAnimationCache::sharedAnimationCache()->addAnimation(bossBoomAnimation, "bossBoomAnimation");
    
}




void GameScene::gameReadyPrompt()
{
    infoPrompt->setVisible(true);
    CCActionInterval* fadeIn = CCFadeIn::create(1.0);
    CCActionInterval* moveIn = CCMoveTo::create(1.0, CCPointMake(size.width/2, size.height/2));
    CCActionInterval* elasticMoveIn = CCEaseElasticInOut::create(moveIn);
    CCActionInterval* action1 =CCSpawn::create(fadeIn,elasticMoveIn,NULL);
    CCCallFuncN* funcnOfPrompt = CCCallFuncN::create(this, callfuncN_selector(GameScene::beginScheduleAndActions));
    CCActionInterval* delayTime = CCDelayTime::create(1.0);
    CCActionInterval* action2 = CCSpawn::create(funcnOfPrompt,delayTime,NULL);
    CCActionInterval* fadeOut = CCFadeOut::create(1.0);
    CCActionInterval* moveBack = CCMoveTo::create(1.0, CCPointMake(size.width*1.5, size.height/2));
    CCActionInterval* elasticMoveBack = CCEaseElasticInOut::create(moveBack);
    CCActionInterval* action3 = CCSpawn::create(fadeOut,elasticMoveBack,NULL);
    CCCallFuncN* funcnOfReset = CCCallFuncN::create(this, callfuncN_selector(GameScene::resetPrompt));
    CCSequence* sequence = CCSequence::create(action1,action2,action3,funcnOfReset,NULL);
    infoPrompt->runAction(sequence);
}



void GameScene::resetPrompt()
{
    infoPrompt->setVisible(false);
    infoPrompt->setPosition(ccp(-size.width/2,size.height/2));
}



void GameScene::beginScheduleAndActions()
{
    data.openDatabase();
    switch (pSceneNumber) {
        case 0:
            data.setFubi(data.getFubi()-10);
            break;
        case 1:
            data.setFubi(data.getFubi()-100);
            break;
            
        default:
            break;
    }
    topBarLayer->pMenu->setTouchEnabled(true);
    this->schedule(schedule_selector(GameScene::createBallnoonSprite), 1.0f);
    this->scheduleUpdate();
}



//从数据库读取更新数据
void GameScene::getDataFromDB()
{
    //根据是哪个场景设置不同的值
    switch (pSceneNumber) {
        case 0:
            normalLevelTarget = data.getGateNormalNO();
            levelTarget = normalLevelTarget;
            ballnoonSpeedDuration = 8;
            ballnoonSizeRatio = 0.9-levelTarget*0.01;
            integrationScore = data.getNormalScore();
            targetIntegrationScore = levelTarget*250 + 100*levelTarget*levelTarget;
            topBarLayer->updateTopTargetScore(targetIntegrationScore,levelTarget);
            lifeSpanOfPerson = 20;
            
            //获取武器数量
            numberOfWeapon1 = 10+levelTarget*5;
            numberOfWeapon2 = data.getFireNumber();
            numberOfWeapon3 = data.getStarNumber();
            numberOfWeapon4 = data.getMoonNumber();
            topBarLayer->initNumberOfWeapon(numberOfWeapon1, numberOfWeapon2, numberOfWeapon3, numberOfWeapon4);

            //每5关出现一个boss气球
            if (levelTarget >1 && levelTarget%5 == 0 )
            {
                this->createExchangeBossBallnoon(5);
            }
            
            break;
        case 1:
            richLevelTarget = data.getGateRichNO();
            levelTarget = richLevelTarget;
            ballnoonSpeedDuration = 10-0.18*levelTarget;
            ballnoonSizeRatio = 0.9-levelTarget*0.008;
            integrationScore = data.getNormalScore();
            targetIntegrationScore = levelTarget*500 + 100*levelTarget*levelTarget;
            topBarLayer->updateTopTargetScore(targetIntegrationScore,levelTarget);
            lifeSpanOfPerson = 30;
            
            //获取武器数量
            numberOfWeapon1 = levelTarget*10+20;
            numberOfWeapon2 = data.getFireNumber();
            numberOfWeapon3 = data.getStarNumber();
            numberOfWeapon4 = data.getMoonNumber();
            topBarLayer->initNumberOfWeapon(numberOfWeapon1, numberOfWeapon2, numberOfWeapon3, numberOfWeapon4);
            
            //每3关出现一个boss气球
            if (levelTarget > 0 && levelTarget%3 == 0)
            {
                this->createExchangeBossBallnoon(3);
            }
            
            break;
        case 2:
            excerciseLevelTarget = data.getGateExerciseNO();
            levelTarget = excerciseLevelTarget;
            ballnoonSpeedDuration = 10-excerciseLevelTarget*0.1;
            ballnoonSizeRatio = 1 - excerciseLevelTarget*0.01;
            integrationScore = data.getExerciseScore();
            targetIntegrationScore = 1000*excerciseLevelTarget + 200 * excerciseLevelTarget*excerciseLevelTarget;
            topBarLayer->updateTopTargetScore(targetIntegrationScore,excerciseLevelTarget);
            lifeSpanOfPerson = 20;

            //预置武器数量
            numberOfWeapon1 = 20+levelTarget;
            numberOfWeapon2 = 5+levelTarget/5;
            numberOfWeapon3 = 5+levelTarget/5;
            numberOfWeapon4 = 5+levelTarget/5;
            topBarLayer->initNumberOfWeapon(numberOfWeapon1, numberOfWeapon2, numberOfWeapon3, numberOfWeapon4);
            
            break;
        default:
            break;
    }
    
    //这里就初始化topBarLayer层的数值（当前分数）
    topBarLayer->updateScore(integrationScore);
    
    //人物生命值初始
    leftLifeOfPerson = lifeSpanOfPerson;
    
    //随着关卡等级的增加，气球运动时间间隔每增一关就降低0.1秒(暂时测试数据为0.5秒)。 当低于2秒时，就不再减少了。
    if (ballnoonSpeedDuration <= 2.0) {
        ballnoonSpeedDuration = 1.0;
    }
    if (ballnoonSizeRatio <= 0.2) {
        ballnoonSizeRatio = 0.2;
    }
    
    CCLog("2. ----------GameScene::getDataFromDB() right!");
}



//每帧都被调用，去检测碰撞
void GameScene::update(float dt)
{
    this->checkForCollision();
}



#pragma mark --------------- BallnoonInitMethod ---------------
//初始化气球的成员函数
void GameScene::createBallnoonSprite()
{
    //获取随机数，把随机的position赋给给随机的气球显示出来，并对气球设置相关参数
    CCSprite* ballnoonSprite;
    CCPoint startPosition;
    do
    {   unsigned int random = 0;
        random = arc4random()%ballnoonSprites->count();
        ballnoonSprite = (CCSprite*)ballnoonSprites->objectAtIndex(random);
    } while (ballnoonSprite->isRunning());
    startPosition = CCPointMake(size.width/2*(1+(arc4random()%10)*0.1), 100+arc4random()%400);
    ballnoonSprite->setPosition(startPosition);
    ballnoonSprite->setScale(0);
    activeBallnoonSprites->setObject(ballnoonSprite, ballnoonSprite->getTag());
    this->addChild(ballnoonSprite,1);
    this->runSpriteSequence(ballnoonSprite);
}



void GameScene::createExchangeBossBallnoon(int kTag)
{
    exchangeableFuBi = 2.0;
    if (5 == kTag) {
        lifespanOfBoss = levelTarget*2 +10;
    }
    else
    {
        lifespanOfBoss = levelTarget*3 +10;
    }
    leftLifeSpan = lifespanOfBoss;
    CCPoint bossBallnoonStartPosition;
    int index = levelTarget/kTag;
    if (index > 14) {
        index = 14;
    }
    bossPicName = ((CCString*)bossBallnoonSprites->objectAtIndex(index))->getCString();
    bossSprite = new BossBallnoonSprite(bossPicName);
    exchangeBallnoonSprite = (CCSprite*) bossSprite;
    ballnoonSprites->addObject(exchangeBallnoonSprite);
    exchangeBallnoonSprite->setTag(18);
    exchangeBallnoonSprite->setScale(0.7);
    bossBallnoonStartPosition = CCPointMake(size.width-50, -200);
    exchangeBallnoonSprite->setPosition(bossBallnoonStartPosition);
    exchangeBallnoonSprite->setScale(0);
    this->addChild(exchangeBallnoonSprite,1);
}



void GameScene::runBossSpriteAction(int kTag)
{
    //淡出变大（气球生成）
    CCActionInterval* scaleTo = CCScaleTo::create(0.1f, 0.6);
    CCActionInterval* fadeIn = CCFadeIn::create(0.1f);
    CCActionInterval* action1 = CCSpawn::create(scaleTo,fadeIn,NULL);

    exchangeBallnoonSprite->runAction(action1);
    this->schedule(schedule_selector(GameScene::exchangeBallnoonSpriteMove), 1.0f/60.0f); 
}



void GameScene::exchangeBallnoonSpriteMove()
{
    exchangeTime++;
    if (exchangeTime > 120) {
        exchangeTime = 0;
        CCPoint bossBallnoonEndPosition;
        float x,y;
        x = size.width/2*(1+(arc4random()%10)*0.1);
        y = 100+arc4random()%400;
        if (x > size.width) {
            x = size.width;
        }
        if (x < size.width/2) {
            x = size.width/2;
        }
        if (y < 0) {
            y = 0;
        }
        if (y > size.height) {
            y = size.height;
        }
        
        bossBallnoonEndPosition = CCPointMake(x, y);
        CCMoveTo* moveTo = CCMoveTo::create(2.0f, bossBallnoonEndPosition);
        
        exchangeBallnoonSprite->runAction(moveTo);
    }
}



//气球从生成、移动到到消失的过程函数
void GameScene::runSpriteSequence(CCSprite* pSprite)
{
    CCPoint endPosition = CCPointMake(pSprite->getPosition().x+(arc4random()%2?-1:1)*arc4random()%100, size.height+10+arc4random()%100);
    
    //淡出变大（气球生成）
    CCActionInterval* scaleTo = CCScaleTo::create(0.5f, ballnoonSizeRatio);
    CCActionInterval* fadeIn = CCFadeIn::create(0.5);
    CCActionInterval* action1 = CCSpawn::create(scaleTo,fadeIn,NULL);
    //移动变小（气球移动）
    CCActionInterval* scaleTo2 = CCScaleTo::create(ballnoonSpeedDuration, ballnoonSizeRatio*0.5);
    CCMoveTo* moveTo = CCMoveTo::create(ballnoonSpeedDuration, endPosition);
    CCActionInterval* action2 = CCSpawn::create(moveTo,scaleTo2,NULL);
    //缩小消失（气球消失）
    CCActionInterval* scaleTo3 = CCScaleTo::create(0.05, 0);
    CCCallFuncN* funcn = CCCallFuncN::create(this, callfuncN_selector(GameScene::natureDisappear));
    CCSequence *sequence = CCSequence::create(action1,action2,scaleTo3,funcn,NULL);
    
    pSprite->runAction(sequence);
}



#pragma mark --------------- WeaponspriteMethod ---------------
// 武器移动
void GameScene::weaponSpriteMoveTo()
{
    propsSprite->setVisible(true);
    CCMoveTo* moveTo = CCMoveTo::create(dartSpeedDuration, destPosition);
    CCActionInterval* move = CCEaseSineOut::create(moveTo);
    CCCallFuncN* funcn = CCCallFuncN::create(this, callfuncN_selector(GameScene::weaponSpriteResetPosition));
    sequence = CCSequence::create(move,funcn,NULL);
    propsSprite->runAction(sequence);
}



//飞镖精灵对象重置于开始位置函数
void GameScene::weaponSpriteResetPosition()
{
    propsSprite->setVisible(false);
    propsSprite->setAnchorPoint(CCPointMake(0.9, 0.5));
    propsSprite->setPosition(propsSpritePosition);
    shootedBallnoonNumber = 0;
    isPropsSpriteReset = 0;
}



#pragma mark-----爆出分数和奖品的核心逻辑函数
//控制分数出现的概率及多少和奖品的出现概率的函数（重要）
void GameScene::ballnoonBoomEffects(CCSprite* pSprite,int kTag)
{
    CCCallFuncN* funcnOfboomEffects = CCCallFuncN::create(this, callfuncN_selector(GameScene::boomEffects));
    CCCallFuncN* funcnOfboomEffectsOfBoss = CCCallFuncN::create(this, callfuncN_selector(GameScene::boomEffectsOfBoss));
    CCCallFuncN* funcnOfThunderEffects = CCCallFuncN::create(this, callfuncN_selector(GameScene::thunderEffects));
    CCCallFuncN* funcnOfshowPrizePic = CCCallFuncN::create(this, callfuncN_selector(GameScene::showPrizePic));
    CCCallFuncN* funcnOfcallback = CCCallFuncN::create(this, callfuncN_selector(GameScene::callbackBallnoonSprite));
    CCCallFuncN* funcnOfcallbackExchange = CCCallFuncN::create(this, callfuncN_selector(GameScene::callbackExchangeBallnoon));
    CCSequence* sequenceOfBallnoon;
    
    //根据Tag的大小来确定是实物奖品的气球还是获取富币的气球
    if ( kTag == 18)
    {
        //1.吞掉武器
        this->weaponSpriteResetPosition();
        propsSprite->stopAction(sequence);
        SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_GameScene_bossShooted.mp3");
        
        //2.boss气球生命值根据不同的道具减相应的值
        switch (propsSprite->getTag()) {
            case 1:
                leftLifeSpan--;
                break;
            case 2:
                leftLifeSpan-=2;
                break;
            case 3:
                leftLifeSpan-=3;
                break;
            case 4:
                break;
            default:
                break;
        }
        
        //3.更新生命值条
        if (leftLifeSpan < 0) {
            leftLifeSpan = 0;
        }
        CCCallFuncN* funcnOfupdateLifespanOfBossBar = CCCallFuncN::create(this, callfuncN_selector(GameScene::updateLifespanOfBossBar));
        
        
        //4.气球左右颤抖状
        CCActionInterval* moveToLeft = CCMoveTo::create(0.05, CCPointMake(exchangeBallnoonSprite->getPositionX()-10, exchangeBallnoonSprite->getPositionY()));
        CCActionInterval* moveToRight = CCMoveTo::create(0.05, CCPointMake(exchangeBallnoonSprite->getPositionX()+10, exchangeBallnoonSprite->getPositionY()));
        CCSequence* sequence = CCSequence::create(moveToLeft,moveToRight,NULL);
        CCRepeat* repeate = CCRepeat::create(sequence, 5);
        CCActionInterval* delayTime = CCDelayTime::create(0.1);

        
        //5.当生命值为0时爆出富币
        if (leftLifeSpan <= 0)
        {
            //如果是圆月弯刀武器，则有闪电特效出现
            if (propsSprite->getTag() ==  4)
            {
                sequenceOfBallnoon = CCSequence::create(funcnOfupdateLifespanOfBossBar,repeate,delayTime,funcnOfboomEffectsOfBoss,funcnOfThunderEffects,funcnOfcallbackExchange,NULL);
                pSprite->runAction(sequenceOfBallnoon);
                return;
            }
            sequenceOfBallnoon = CCSequence::create(funcnOfupdateLifespanOfBossBar,repeate,delayTime,funcnOfboomEffectsOfBoss,funcnOfshowPrizePic,funcnOfcallbackExchange,NULL);
            bossSprite->stopEffects();
        }
        else
        {
            //如果是圆月弯刀武器，则有闪电特效出现
            if (propsSprite->getTag() == 4)
            {
                sequenceOfBallnoon = CCSequence::create(funcnOfThunderEffects,NULL);
                pSprite->runAction(sequenceOfBallnoon);
                return;
            }
            sequenceOfBallnoon = CCSequence::create(funcnOfupdateLifespanOfBossBar,repeate,NULL);
        }
    }
    
    
    //根据射中的气球的颜色给予不同的分数
    else if(kTag >= 1 && kTag <=16)
    {
        int randomScore;
        switch (kTag) {
            case 1:
            case 4:
            case 7:
            case 10:
                randomScore = 200;
                break;
            case 2:
            case 5:
            case 8:
            case 11:
                randomScore = 300;
                break;
            case 3:
            case 6:
            case 9:
            case 12:
                randomScore = 400;
                break;
            default:
                break;
        }
        
        //积分增加
        integrationScore = integrationScore + randomScore;
        topBarLayer->updateScore(integrationScore);
        this->showScore(randomScore);
        
        //如果积分已达目标积分一般，则出现兑换币boss气球
        if (integrationScore >= targetIntegrationScore*0.4 && exchangeableFuBi > 0 && isappearExchange == 0)
        {
            isappearExchange++;
            bossSprite->pauseEffects();
            this->runBossSpriteAction(18);
        }
        
        //如果是圆月弯刀武器，则有闪电特效出现
        if (propsSprite->getTag() == 4)
        {
            sequenceOfBallnoon = CCSequence::create(funcnOfboomEffects,funcnOfThunderEffects,funcnOfcallback,NULL);
            pSprite->runAction(sequenceOfBallnoon);
            return;
        }
        sequenceOfBallnoon = CCSequence::create(funcnOfboomEffects,funcnOfcallback,NULL);
    }
    
    
    //如果已获积分数达到了目标积分数，则执行提示过关动作
    if (integrationScore >= targetIntegrationScore && leftLifeSpan == 0)
    {
        //这里设置背景层透明度参数为0
        opacity = 0;
        
        //分数已达，跳动提示函数
        topBarLayer->showScoreCompleteEffects();
        
        //设置背景触摸不可用
        this->setTouchEnabled(false);
        
        //延时执行操作
        this->scheduleOnce(schedule_selector(GameScene::showLevelComplete), 1.5);
    }
    pSprite->runAction(sequenceOfBallnoon);
}



void GameScene::stopAllBallnoonAction()
{
    //停掉所有定时器及动作
    this->unschedule(schedule_selector(GameScene::createBallnoonSprite));
    this->unscheduleUpdate();
    
    int kTag;
    CCArray* tempArray = new CCArray();
    tempArray->init();
    if (activeBallnoonSprites->allKeys() == NULL) {
        return;
    }
    tempArray = activeBallnoonSprites->allKeys();
    for (int i = 0; i < tempArray->count(); i++) {
        CCInteger* kTagString = (CCInteger*)tempArray->objectAtIndex(i);
        kTag = kTagString->getValue();
        CCSprite* ballnoon = (CCSprite*)activeBallnoonSprites->objectForKey(kTag);
        ballnoon->pauseSchedulerAndActions();
    }
    CCLog("----------GameScene:stopAllBallnoonAction() right!");
}



void GameScene::restarBallnoonAction()
{
    this->schedule(schedule_selector(GameScene::createBallnoonSprite), 1.0f);
    this->scheduleUpdate();
    int kTag;
    CCArray* tempArray = new CCArray();
    tempArray->init();
    if (activeBallnoonSprites->allKeys() == NULL) {
        return;
    }
    tempArray = activeBallnoonSprites->allKeys();
    if (tempArray->count() <= 0) {
        return;
    }
    for (int i = 0; i < tempArray->count(); i++) {
        CCInteger* kTagString = (CCInteger*)tempArray->objectAtIndex(i);
        kTag = kTagString->getValue();
        CCSprite* ballnoon = (CCSprite*)activeBallnoonSprites->objectForKey(kTag);
        ballnoon->resumeSchedulerAndActions();
    }
}



//气球爆炸特效函数
void GameScene::boomEffects(CCSprite* pSprite)
{
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_boom1.mp3");
    CCSprite* boom = CCSprite::create("ZF_Shoot_GameScene_boom1.png");
    boom->setPosition(pSprite->getPosition());
    this->addChild(boom);
    CCAnimation* boomAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("boomAnimation");
    boomAnimate = CCAnimate::create(boomAnimation);
    CCCallFuncN* funcnOfBallnoon = CCCallFuncN::create(this, callfuncN_selector(GameScene::callback1));
    CCSequence* sequence = CCSequence::create(boomAnimate,funcnOfBallnoon,NULL);
    boom->runAction(sequence);
}



void GameScene::thunderEffects()
{
    CCSprite* boom = CCSprite::create("ZF_Shoot_GameScene_thunder1.png");
    boom->setPosition(CCPointMake(size.width, size.height));
    boom->setAnchorPoint(ccp(1.0f,1.0f));
    this->addChild(boom);
    CCAnimation* boomAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("thunderAnimation");
    CCAnimate* thunderAnimate = CCAnimate::create(boomAnimation);
    CCCallFuncN* funcnOfBallnoon = CCCallFuncN::create(this, callfuncN_selector(GameScene::callback1));
    CCSequence* sequence = CCSequence::create(thunderAnimate,funcnOfBallnoon,NULL);
    boom->runAction(sequence);
    
    
    //接着爆炸所有气球
    CCCallFuncN* funcnOfThunderBoomEffects = CCCallFuncN::create(this, callfuncN_selector(GameScene::thunderBoomEffects));
    CCActionInterval* delayTime = CCDelayTime::create(0.1);
    CCSequence* sequence1 = CCSequence::create(delayTime,funcnOfThunderBoomEffects,NULL);
    this->runAction(sequence1);
}



//爆炸所有气球
void GameScene::thunderBoomEffects()
{
    CCCallFuncN* funcnOfboomEffects = CCCallFuncN::create(this, callfuncN_selector(GameScene::boomEffects));
    CCCallFuncN* funcnOfboomEffectsOfBoss = CCCallFuncN::create(this, callfuncN_selector(GameScene::boomEffectsOfBoss));
    CCCallFuncN* funcnOfcallback = CCCallFuncN::create(this, callfuncN_selector(GameScene::callbackBallnoonSprite));
    CCCallFuncN* funcnOfcallbackExchange = CCCallFuncN::create(this, callfuncN_selector(GameScene::callbackExchangeBallnoon));
    CCCallFuncN* funcnOfshowPrizePic = CCCallFuncN::create(this, callfuncN_selector(GameScene::showPrizePic));
    CCSequence* sequenceOfBallnoon;
    int kTag;

    if (activeBallnoonSprites->count() <= 0)
    {
        return;
    }
    
    CCArray* tempArray = new CCArray();
    tempArray->init();
    tempArray = activeBallnoonSprites->allKeys();
    //首先遍历所有气球
    for (int i = 0; i < tempArray->count(); i++)
    {
        CCInteger* kTagString = (CCInteger*)tempArray->objectAtIndex(i);
        kTag = kTagString->getValue();
        CCSprite* ballnoon = (CCSprite*)activeBallnoonSprites->objectForKey(kTag);
        disBallnoonPosition = ballnoon->getPosition();
        
        if(kTag >= 1 && kTag <=16)
        {
            //1.根据射中的气球的颜色给予不同的分数
            int randomScore;
            switch (kTag) {
                case 1:
                case 4:
                case 7:
                case 10:
                    randomScore = 100;
                    break;
                case 2:
                case 5:
                case 8:
                case 11:
                    randomScore = 200;
                    break;
                case 3:
                case 6:
                case 9:
                case 12:
                    randomScore = 400;
                    break;
                default:
                    break;
            }
            
            //2.积分增加
            integrationScore = integrationScore + randomScore;
            topBarLayer->updateScore(integrationScore);
            this->showScore(randomScore);
            
            sequenceOfBallnoon = CCSequence::create(funcnOfboomEffects,funcnOfcallback,NULL);
            
        }
        ballnoon->runAction(sequenceOfBallnoon);
    }
    
    activeBallnoonSprites->removeAllObjects();
    
    if ( exchangeBallnoonSprite != NULL && integrationScore >= targetIntegrationScore*0.4)
    {
        //1.首先生命值减4，更新生命值条
        leftLifeSpan-=4;
        SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_GameScene_bossShooted.mp3");
        
        //2.更新生命值条
        if (leftLifeSpan < 0) {
            //boss气球消失，爆出奖品图片
            leftLifeSpan = 0;
        }
        CCCallFuncN* funcnOfupdateLifespanOfBossBar = CCCallFuncN::create(this, callfuncN_selector(GameScene::updateLifespanOfBossBar));
        
        //3.气球左右颤抖状
        CCActionInterval*  moveToLeft = CCMoveTo::create(0.05, CCPointMake(exchangeBallnoonSprite->getPositionX()-10, exchangeBallnoonSprite->getPositionY()));
        CCActionInterval*  moveToRight = CCMoveTo::create(0.05, CCPointMake(exchangeBallnoonSprite->getPositionX()+10, exchangeBallnoonSprite->getPositionY()));
        CCSequence* sequence = CCSequence::create(moveToLeft,moveToRight,NULL);
        CCRepeat* repeate = CCRepeat::create(sequence, 5);
        CCActionInterval* delayTime = CCDelayTime::create(0.3);
        
        //5.当生命值为0时爆出实物奖品或者兑换币
        if (leftLifeSpan <= 0)
        {
            sequenceOfBallnoon = CCSequence::create(funcnOfupdateLifespanOfBossBar,repeate,funcnOfboomEffectsOfBoss,delayTime,funcnOfshowPrizePic,funcnOfcallbackExchange,NULL);
        }
        else
        {
            sequenceOfBallnoon = CCSequence::create(funcnOfupdateLifespanOfBossBar,repeate,NULL);
        }
        exchangeBallnoonSprite->runAction(sequenceOfBallnoon);
    }
    
    
    //如果达到了目标积分，则过关
    if (integrationScore >= targetIntegrationScore && leftLifeSpan == 0)
    {
        //这里设置背景层透明度参数为0
        opacity = 0;
        
        //分数已达，跳动提示函数
        topBarLayer->showScoreCompleteEffects();
        
        //设置背景触摸不可用
        this->setTouchEnabled(false);
        
        //延时执行操作
        this->scheduleOnce(schedule_selector(GameScene::showLevelComplete), 1.5);
    }
}



void GameScene::boomEffectsOfBoss(CCSprite* pSprite)
{
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_boom1.mp3");
    CCSprite* boom = CCSprite::create("ZF_Shoot_GameScene_bossboom1.png");
    boom->setPosition(pSprite->getPosition());
    this->addChild(boom);
    CCAnimation* boomAnimation = CCAnimationCache::sharedAnimationCache()->animationByName("bossBoomAnimation");
    boomAnimate = CCAnimate::create(boomAnimation);
    CCCallFuncN* funcnOfBallnoon = CCCallFuncN::create(this, callfuncN_selector(GameScene::callback1));
    CCSequence* sequence = CCSequence::create(boomAnimate,funcnOfBallnoon,NULL);
    boom->runAction(sequence);
}



//弹出实物奖品的信息
void GameScene::showPrizePic()
{
    //这个地方需要一个获得大奖的音乐特效
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_getPrize.wav");
    
    
    //如果当前积分小于目标积分，则停止
    if (integrationScore < targetIntegrationScore) {
        this->stopAllBallnoonAction();
    }
    
    
    //背景变暗，操作不可用
    colorLayer->setOpacity(100);
    this->setButtonTouchFalse();
    
    
    //根据场景和等级的不同爆出不同的富币
    unsigned int random = 0;
    switch (pSceneNumber) {
        case 0:
            random = levelTarget*50;
            break;
        case 1:
            random = levelTarget*100;
            break;
            
        default:
            break;
    }
    data.setFubi(data.getFubi()+random);
    
    CCSprite* prizeSprite = CCLabelTTF::create(CCString::createWithFormat("%d",random)->getCString(), "Georgia-BoldItalic", 40);
    prizeSprite->setScale(0);
    prizeSprite->setPosition(CCPointMake(size.width/2, size.height/2));
    this->addChild(prizeSprite,10);
    
    CCSprite* coinPointImage = CCSprite::create("ZF_Shoot_GameScene_coinPointImage.png");
    coinPointImage->setAnchorPoint(ccp(0,0.5));
    coinPointImage->setPosition(CCPointMake(prizeSprite->getContentSize().width, prizeSprite->getContentSize().height*0.5));
    prizeSprite->addChild(coinPointImage);
    
    CCSprite* starRotate = CCSprite::create("ZF_Shoot_GameScene_starrotate.png");
    starRotate->setPosition(CCPointMake(prizeSprite->getContentSize().width*0.3, prizeSprite->getContentSize().height*0.5));
    coinPointImage->addChild(starRotate,1);
    
    CCActionInterval* rotate1 = CCRotateBy::create(1.0, 180);
    CCActionInterval* rotate2 = rotate1->reverse();
    CCActionInterval* sequenceOfStar = CCSequence::create(rotate1,rotate2,NULL);
    CCActionInterval* repeate = CCRepeatForever::create(sequenceOfStar);
    starRotate->runAction(repeate);
    
    
    //背景光的出现
    light = CCSprite::create("ZF_Shoot_GameScene_prizeLight.png");
    light->setPosition(CCPointMake(size.width/2, size.height/2));
    this->addChild(light,3);
    CCActionInterval* rotatebg = CCRotateBy::create(2.0f, 360);
    CCSequence* sequence = CCSequence::create(rotatebg,NULL);
    CCActionInterval* repeat = CCRepeatForever::create(sequence);
    light->runAction(repeat);
    

    CCActionInterval* scaleToOfPrize1 = CCScaleTo::create(0.5f, 2.0f);

    CCActionInterval* interval = CCDelayTime::create(2.0f);

    CCCallFuncN* funcn2 = CCCallFuncN::create(this, callfuncN_selector(GameScene::callback1));
    
    CCCallFuncN* funcn3 = CCCallFuncN::create(this, callfuncN_selector(GameScene::setBlackLightDisappear));

    CCSequence *sequenceOfPrize = CCSequence::create(scaleToOfPrize1,interval,funcn2,funcn3,NULL);

    prizeSprite->runAction(sequenceOfPrize);
}



void GameScene::setBlackLightDisappear()
{
    //如果当前积分小于目标积分，则停止
    if (integrationScore < targetIntegrationScore) {
        this->restarBallnoonAction();
    }
    colorLayer->setOpacity(0);
    this->callback1(light);
    this->setButtonTouchTrue();
}



//动态调整boss气球的生命值
void GameScene::updateLifespanOfBossBar(CCObject* pSender)
{
    CCLog("----------GameScene:updateLifespanOfBossBar() leftLifeSpan:%d",leftLifeSpan);
    float scale = leftLifeSpan/lifespanOfBoss;
    bossSprite->updateLifeSpanOfBoss(scale);
}



void GameScene::natureDisappear(CCNode *sender)
{
    leftLifeOfPerson--;
    if (leftLifeOfPerson < 5) {
        CCActionInterval* scaleTo = CCScaleTo::create(0.2, 1.1);
        CCActionInterval* scaleBack = CCScaleTo::create(0.2, 1.0);
        CCActionInterval* sequence = CCSequence::create(scaleTo,scaleBack,NULL);
        CCActionInterval* repeate = CCRepeatForever::create(sequence);
        green->runAction(repeate);
    }
    
    if (leftLifeOfPerson <= 0) {
        green->stopAllActions();
        leftLifeOfPerson = 0;
        this->showLevelComplete(2); 
    }
    red->setScaleX(leftLifeOfPerson/lifeSpanOfPerson);
    this->callbackBallnoonSprite(sender);
}



//消除精灵对象
void GameScene::callback1(CCNode* sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    sprite->setVisible(false);
    sprite->setPosition(CCPointZero);
    sprite->removeFromParentAndCleanup(true);
}



//气球对象消失
void GameScene::callbackBallnoonSprite(CCNode* sender)
{
    CCSprite *sprite = (CCSprite *)sender;
    int pTagOfSprite = ((CCSprite*)sender)->getTag();
    activeBallnoonSprites->removeObjectForKey(pTagOfSprite);
    sprite->setPosition(CCPointMake(50, size.height/2));
    sprite->removeFromParentAndCleanup(true);
}



//boss气球消失
void GameScene::callbackExchangeBallnoon()
{
    this->unschedule(schedule_selector(GameScene::exchangeBallnoonSpriteMove));
    exchangeBallnoonSprite->setScale(0);
    exchangeBallnoonSprite->setPosition(CCPointZero);
    exchangeBallnoonSprite->removeFromParentAndCleanup(true);
    exchangeBallnoonSprite = NULL;
}



#pragma mark --------------- showPrompt ---------------
#pragma mark -----本级目标达成，写入数据库本关的相关数据信息
void GameScene::showLevelComplete(int kTag)
{
    //音效停止，停掉气球的所有动作
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
    this->stopAllBallnoonAction();
    
    //目标已达文字显示
    CCLabelTTF* levelCompleteLabel;
    
    if (2 == kTag) {
        
        isSuccess = 0;
        SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_GameScene_failed.mp3");
        //失败的场景
        levelCompleteLabel = CCLabelTTF::create("Level failed!", "Georgia-BoldItalic", 40);
        levelCompleteLabel->setColor(ccRED);
        levelCompleteLabel->setScale(0);
        levelCompleteLabel->setPosition(CCPointMake(size.width/2, size.height/2));
        this->addChild(levelCompleteLabel,5);
        
        
        //....失败的逻辑
        //启动黑色遮罩层
        this->schedule(schedule_selector(GameScene::setcolorLayerOpacityUp), 0.01f, 33, 2.0f);
        
    }
    else
    {
        isSuccess = 1;
        //这里也要一个目标已达的音乐音效
        SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_levelcomplete.wav");
        levelCompleteLabel = CCLabelTTF::create("Level cleared!", "Georgia-BoldItalic", 40);
        levelCompleteLabel->setColor(ccRED);
        levelCompleteLabel->setScale(0);
        levelCompleteLabel->setPosition(CCPointMake(size.width/2, size.height/2));
        this->addChild(levelCompleteLabel,4);
        
        //启动黑色遮罩层
        this->schedule(schedule_selector(GameScene::setcolorLayerOpacityUp), 0.01f, 33, 2.0f);
        
        //本级目标达成，写入数据库本关的相关数据信息
        switch (pSceneNumber) {
            case 0:
                data.setNormalScore(0);
                data.setGateNormalNO(normalLevelTarget+1);
                data.setMoonNumber(numberOfWeapon4);
                data.setStarNumber(numberOfWeapon3);
                data.setFireNumber(numberOfWeapon2);
                break;
            case 1:
                data.setRichScore(0);
                data.setGateRichNO(richLevelTarget+1);
                data.setMoonNumber(numberOfWeapon4);
                data.setStarNumber(numberOfWeapon3);
                data.setFireNumber(numberOfWeapon2);
                break;
            case 2:
                data.setExerciseScore(0);
                data.setGateExerciseNO(excerciseLevelTarget+1);
                break;
            default:
                break;
        }
    }
    
    
    //文字出现特效
    CCActionInterval* scaleToOfPrize1 = CCScaleTo::create(0.6, 1.5f);
    CCActionInterval* interval = CCDelayTime::create(1.0);
    CCActionInterval* scaleToOfPrize2 = CCScaleTo::create(0.4, 4.0f);
    CCActionInterval* fadeOutOfPrize = CCFadeOut::create(0.4);
    CCActionInterval* actionOfPrize = CCSpawn::create(scaleToOfPrize2,fadeOutOfPrize,NULL);
    CCCallFuncN* funcn = CCCallFuncN::create(this, callfuncN_selector(GameScene::callback1));
    CCCallFuncN* funcn1 = CCCallFuncN::create(this, callfuncN_selector(GameScene::setSpritesUnvisible));
    CCSequence *sequenceOfPrize = CCSequence::create(scaleToOfPrize1,interval,funcn1,actionOfPrize,funcn,NULL);
    levelCompleteLabel->runAction(sequenceOfPrize);
}



//显示获得多少积分
void GameScene::showScore(float i_Score)
{
    CCString *showScore = CCString::createWithFormat("%d",(int)i_Score);
    scoreSprite = CCLabelTTF::create(showScore->getCString(), "Georgia-BoldItalic", 40);
    scoreSprite->setColor(ccGREEN);
    this->addChild(scoreSprite);
    scoreSprite->setPosition(disBallnoonPosition);
    scoreSprite->setScale(0);
    CCActionInterval* scaleToOfScore = CCScaleTo::create(0.15, 1.0f);
    CCMoveTo* moveToOfScore = CCMoveTo::create(0.5, ccp(disBallnoonPosition.x, disBallnoonPosition.y + 15));
    CCMoveTo* moveToOfScore1 = CCMoveTo::create(0.2, ccp(disBallnoonPosition.x, disBallnoonPosition.y + 20));
    CCActionInterval* fadeOutOfScore = CCFadeOut::create(0.2);
    CCActionInterval* actionOfScore = CCSpawn::create(moveToOfScore1,fadeOutOfScore,NULL);
    CCCallFuncN* funcn = CCCallFuncN::create(this, callfuncN_selector(GameScene::callback1));
    CCSequence *sequence1OfScore = CCSequence::create(scaleToOfScore,moveToOfScore,actionOfScore,funcn,NULL);
    
    scoreSprite->runAction(sequence1OfScore);
}



void GameScene::showWeaponNotEnough(int kTag)
{
    CCPoint point;
    //1.提示精灵的生成
    CCSprite* swopWeapon = CCSprite::create("ZF_Shoot_GameScene_swopWeapon.png");
    this->addChild(swopWeapon,6);
    
    //2.获取出现的position
    switch (kTag) {
        case 1:
            point = ccp(70, 70);
            break;
        case 2:
            point = ccp(190, 70);
            break;
        case 3:
            point = ccp(310, 70);
            break;
        case 4:
            point = ccp(430, 70);
            break;
            
        default:
            break;
    }
    
    //3.出现和消失
    swopWeapon->setPosition(point);
    CCActionInterval* scaleTo = CCScaleTo::create(0.15, 1.0f);
    CCMoveTo* moveTo1 = CCMoveTo::create(1.0, ccp(point.x, point.y + 15));
    CCMoveTo* moveTo2 = CCMoveTo::create(0.2, ccp(point.x, point.y + 20));
    CCActionInterval* fadeOut = CCFadeOut::create(0.2);
    CCActionInterval* action = CCSpawn::create(moveTo2,fadeOut,NULL);
    CCCallFuncN* funcn = CCCallFuncN::create(this, callfuncN_selector(GameScene::callback1));
    CCSequence *sequence = CCSequence::create(scaleTo,moveTo1,action,funcn,NULL);
    swopWeapon->runAction(sequence);
}



//设置背景元素不可见
void GameScene::setSpritesUnvisible()
{
    //设置气球不动
    CCLog("----------GameScene:ballnoonSprites->count() %d",ballnoonSprites->count());
    for (int i = 0; i < ballnoonSprites->count(); i++) {
        CCSprite* ballnoon = (CCSprite*)ballnoonSprites->objectAtIndex(i);
        this->callback1(ballnoon);
    }
    weaponSprite->setVisible(false);
    propsSprite->setVisible(false);
    indicateSprite->setVisible(false);
    topBarLayer->setVisible(false);
    boy->setVisible(false);
    girl->setVisible(false);
}



//设置背景按钮不可用
void GameScene::setButtonTouchFalse()
{
    topBarLayer->weaponButton1->setTouchEnabled(false);
    topBarLayer->weaponButton2->setTouchEnabled(false);
    topBarLayer->weaponButton3->setTouchEnabled(false);
    topBarLayer->weaponButton4->setTouchEnabled(false);
    topBarLayer->pMenu->setTouchEnabled(false);
    this->setTouchEnabled(false);
}



//设置背景按钮可用
void GameScene::setButtonTouchTrue()
{
    topBarLayer->weaponButton1->setTouchEnabled(true);
    topBarLayer->weaponButton2->setTouchEnabled(true);
    topBarLayer->weaponButton3->setTouchEnabled(true);
    topBarLayer->weaponButton4->setTouchEnabled(true);
    topBarLayer->pMenu->setTouchEnabled(true);
    this->setTouchEnabled(true);
}



//1.背景渐黑效果函数
void GameScene::setcolorLayerOpacityUp()
{
    opacity +=3;
    colorLayer->setOpacity(opacity);
    if (opacity >= 66) {
        this->unschedule(schedule_selector(GameScene::setcolorLayerOpacityUp));
        this->bounceOutPrompt();
    }
}



#pragma mark -----传参数给提示层(过关提示，武器不足，开始下一关)
//本关已过提示页面弹出动画函数
void GameScene::bounceOutPrompt()
{
    
    //通过这个函数传值给提示页面
    promptLayer->transferPromotedInfo(pSceneNumber,levelTarget, isSuccess, integrationScore, shootDartNumber, isshootedBallnoon);
    
    //弹出提示层音效
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_bounceOutPrompt.wav");
    
    //提示页面跳出来
    CCMoveTo* moveTo = CCMoveTo::create(0.8, CCPointZero);
    CCEaseElasticInOut* move = CCEaseElasticInOut::create(moveTo, 0.8);
    
    promptLayer->runAction(move);
}



//武器数量不足提示页面层弹出动画函数
void GameScene::bounceOutWeaponNELayer(int pSceneNO,int kTagOfProps)
{
    //设置触摸不可用
    this->setButtonTouchFalse();
    this->stopAllBallnoonAction();
    //传值给武器不足提示页面层
    weaponNotEnoughLayer->transferValueToWeaponNELayer(pSceneNO, kTagOfProps);
    
    //弹出提示层音效
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_bounceOutPrompt.wav");
    
    //提示页面跳出来
    CCMoveTo* moveTo = CCMoveTo::create(0.8, CCPointZero);
    CCEaseElasticInOut* move = CCEaseElasticInOut::create(moveTo, 0.8);
    CCSequence* sequence = CCSequence::create(move,NULL);
    
    weaponNotEnoughLayer->runAction(sequence);
}



void GameScene::bounceOutShopLayer()
{
    //提示页面跳出来
    CCMoveTo* moveTo = CCMoveTo::create(0.8, ccp(0, 0));
    CCEaseElasticInOut* move = CCEaseElasticInOut::create(moveTo, 0.8);
    this->stopAllBallnoonAction();
    propMarketsLayer->runAction(move);
}



//提示层从本场景中间移除的动画效果
void GameScene::moveLayer(CCNode* pNode,int kTag)
{    
    //缩回提示层音效
    SimpleAudioEngine::sharedEngine()->playEffect("ZF_Shoot_Effects_bounceBackPrompt.wav");
    
    CCSequence* sequence;
    CCMoveTo* moveTo = CCMoveTo::create(0.8, CCPointMake(0, size.height*1.2));
    CCEaseElasticInOut* move = CCEaseElasticInOut::create(moveTo, 0.8);
    CCCallFuncN* funBackToGame = CCCallFuncN::create(this, callfuncN_selector(GameScene::reInitScene));
    CCCallFuncN* funBackToMenu = CCCallFuncN::create(this, callfuncN_selector(GameScene::backToMenuScene));
    CCCallFuncN* funGoToShop = CCCallFuncN::create(this, callfuncN_selector(GameScene::bounceOutShopLayer));
    CCCallFuncN* funRemoveLabels = CCCallFuncN::create(this, callfuncN_selector(GameScene::removePromptLayerLabels));
    CCCallFuncN* funSetTouchTrue = CCCallFuncN::create(this, callfuncN_selector(GameScene::setButtonTouchTrue));
    CCCallFuncN* funRestartBallnoonAction = CCCallFuncN::create(this, callfuncN_selector(GameScene::restarBallnoonAction));
    switch (kTag) {
        case 1:
            sequence  = CCSequence::create(move,funRemoveLabels,funBackToGame,NULL);
            break;
        case 2:
            sequence  = CCSequence::create(move,funRemoveLabels,funBackToMenu,NULL);
            break;
        case 3:
            sequence  = CCSequence::create(move,funRemoveLabels,funBackToGame,NULL);
            break;
        case 4:
            sequence  = CCSequence::create(move,funGoToShop,NULL);
            weaponNotEnoughLayer->setTouchTime();
            break;
        case 5:
            sequence  = CCSequence::create(move,funSetTouchTrue,funRestartBallnoonAction,NULL);
            weaponNotEnoughLayer->setTouchTime();
            break;
        default:
            break;
    }
    pNode->runAction(sequence);
}



/**
 *曾尝试直接调用他类函数，这样：CCCallFuncN* funRemoveLabels = CCCallFuncN::create(this, callfuncN_selector(PromptLayer::removeLabels))，
 *但这样貌似一直不行，所以采用在本类函数里面调用他类函数的方法，中转一道。证明可行！
**/
//移除提示层上所有文字标签中转函数
void GameScene::removePromptLayerLabels()
{
    promptLayer->removeLabels();
}



//重新初始化场景相关数据
void GameScene::reInitScene()
{
    exchangeableFuBi = 0;
    //颜色层渐隐函数
    this->schedule(schedule_selector(GameScene::setcolorLayerOpacityDown), 0.01f);
    
    //气球数组
    green->stopAllActions();
    ballnoonSprites->removeAllObjects();
    this->initVariable();
    this->initBallnoonSprite();
    this->setTouchEnabled(true);
    red->setScaleX(1);
    CCLog("-----GameScene：reInitScene right!");
}



//返回选关场景函数
void GameScene::backToMenuScene()
{
    //返回选关场景是存档
    if (pSceneNumber == 0 || pSceneNumber == 1) {
        this->archiveWeaponNumber();
    }
    
    data.closeDatabase();
    CCTransitionFade* transition = CCTransitionFade::create(0.2, MenuScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    CCDirector::sharedDirector()->isSendCleanupToScene();
}



//2.背景渐白效果函数
void GameScene::setcolorLayerOpacityDown()
{
    opacity -=3;
    colorLayer->setOpacity(opacity);
    if (opacity <= 0) {
        
        this->unschedule(schedule_selector(GameScene::setcolorLayerOpacityDown));
        
        if (0 == isFuBiEnough)
        {
            //继续放背景音乐
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7);
            
            //道具选择按钮设置可见可用
            weaponSprite->setVisible(true);
            propsSprite->setVisible(false);
            indicateSprite->setVisible(true);
            boy->setVisible(true);
            girl->setVisible(true);
            
            //显示topbarlayer
            topBarLayer->setVisible(true);
            
            //读取数据库最新从服务器取回的数据（这个是导致内存递增的原因。在添加关闭数据库之后内存递增的问题得以解决）
            this->getDataFromDB();
            
            if (pSceneNumber < 2) {
                //确认按钮不可见
                this->gameReadyPrompt();
            }
            else
            {
                //每隔1秒定时调用初始化方法生成一个随机的气球，并在随机的位置出现
                this->schedule(schedule_selector(GameScene::createBallnoonSprite), 1.0f);
                
                //每帧调用
                this->scheduleUpdate();
            }
        }
        else
        {
            CCSprite* fuBiNotEnough = CCSprite::create("ZF_Shoot_GameScene_dialogueBg.png");
            fuBiNotEnough->setPosition(ccp(size.width*0.5,size.height*0.5));
            addChild(fuBiNotEnough,4,kMenuTagConfirm);
            
            CCMenuItemImage *confirm = CCMenuItemImage::create("ZF_Shoot_GameScene_dialogueConfirm.png", "ZF_Shoot_GameScene_dialogueConfirm.png", this, menu_selector(GameScene::backToMenuScene));
            confirm->setTag(1);
            confirm->setPosition(ccp(fuBiNotEnough->getContentSize().width/2,fuBiNotEnough->getContentSize().height/4));
            CCMenu* confirmMenu = CCMenu::create(confirm,NULL);
            confirmMenu->setPosition(CCPointZero);
            fuBiNotEnough->addChild(confirmMenu);
            
            CCActionInterval* scaleTo = CCScaleTo::create(0.8, 1.0f);
            CCEaseBounceOut* elasticOut = CCEaseBounceOut::create(scaleTo);
            fuBiNotEnough->runAction(elasticOut);
            CCLOG("-----不能进行下一关");
        }
    }
}



#pragma mark --------------- TouchMehod ---------------
//下面是三个触摸函数，开始，移动，和结束。从各个函数中可获取不同点的位置
void GameScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    if (isPauseed) {
        return;
    }
    tempTag = 0;
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocationInView();
    startLocation = CCDirector::sharedDirector()->convertToGL(location);
}



void GameScene::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    if (isPauseed) {
        return;
    }
    float ratio; //系数
    //如果点击区域在右半部，则返回
    if (startLocation.x > size.width/2) {
        return;
    }
    
    //否则为左半部
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocationInView();
    endLocation = CCDirector::sharedDirector()->convertToGL(location);

    offSetX = endLocation.x - startLocation.x;
    offSetY = endLocation.y - startLocation.y;
    offSetXY = sqrtf(offSetX*offSetX + offSetY*offSetY);
    ratio = offSetXY/400;
    pTan = offSetY/offSetX;
    rotateNumber = 0 - atan(pTan)*180/3.1415;
    if (rotateNumber > 60) {
        rotateNumber  = 60;
    }
    else if (rotateNumber < -60) {
        rotateNumber  = -60;
    }
    if (ratio < 0.15) {
        ratio = 0.15;
    }
    else if(ratio > 0.55)
    {
        ratio = 0.55;
    }
    dartSpeedDuration = 1.0 - ratio;
    //这里设置一个触摸范围，在这个范围内才显示引导箭头
    if (startLocation.x < size.width/2) {
        if (offSetX < 0) {
            indicateSprite->setScale(ratio);
            indicateSprite->setRotation(rotateNumber);
        }
        weaponSprite->setRotation(rotateNumber);
        propsSprite->setRotation(rotateNumber);
    }
}



void GameScene::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    if (isPauseed) {
        return;
    }
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocationInView();
    endLocation = CCDirector::sharedDirector()->convertToGL(location);
    shootDartNumber++;
    indicateSprite->setScale(0);
    
    //点击射击（取消）
    if (startLocation.x > size.width/2) {
        return;
    }
    else
    {
        if (offSetXY < 20) {
            return;
        }
        //为滑动射击(取消)
        if (offSetX > 0) {
            return;
        }
        //为后拉射击
        else
        {
            destPosition.x = labs(offSetX*kScreenSizeOfDevice/offSetXY);
            destPosition.y = 200-offSetY*kScreenSizeOfDevice/offSetXY;
            if (offSetY/offSetXY < -0.866) {
                destPosition.x = kScreenSizeOfDevice/2;
                destPosition.y = 200+kScreenSizeOfDevice*0.866;
            }
            else if (offSetY/offSetXY > 0.866)
            {
                destPosition.x = kScreenSizeOfDevice/2;
                destPosition.y = 200-kScreenSizeOfDevice*0.866;
            }
        }
    }
    
    //这里是判断飞镖是否已回原处
    if (propsSprite->getPosition().x == propsSpritePosition.x) {
        
        //在这里需要判断玩家当前选择的武器数量是否大于0，如果大于0则可以发射，如果不大于0，则弹出武器不足是否需要购买的提示层
        switch (propsSprite->getTag()) {
            case 1:
                if (numberOfWeapon1 > 0) {
                    numberOfWeapon1--;
                    topBarLayer->updateNumberOfWeapon(1, numberOfWeapon1);
                    this->weaponSpriteMoveTo();
                }
                else if ( numberOfWeapon2 <=0 && numberOfWeapon3 <= 0 && numberOfWeapon4 <= 0 )
                {
                    if (integrationScore <= targetIntegrationScore || exchangeBallnoonSprite != NULL)
                    {
                        this->bounceOutWeaponNELayer(pSceneNumber, 1);
                    }
                }
                else
                {
                    this->showWeaponNotEnough(1);
                }

                break;
            case 2:
                if (numberOfWeapon2 > 0) {
                    numberOfWeapon2--;
                    topBarLayer->updateNumberOfWeapon(2, numberOfWeapon2);
                    data.setFireNumber(numberOfWeapon2);
                    this->weaponSpriteMoveTo();
                }
                else if (numberOfWeapon1 <= 0 &&  numberOfWeapon3 <= 0 && numberOfWeapon4 <= 0 )
                {
                    if (integrationScore <= targetIntegrationScore || exchangeBallnoonSprite != NULL )
                    {
                        this->bounceOutWeaponNELayer(pSceneNumber, 1);
                    }
                }
                else
                {
                    this->showWeaponNotEnough(2);
                }
                break;
            case 3:
                if (numberOfWeapon3 > 0) {
                    numberOfWeapon3--;
                    topBarLayer->updateNumberOfWeapon(3, numberOfWeapon3);
                    data.setStarNumber(numberOfWeapon3);
                    this->weaponSpriteMoveTo();
                }
                else if (numberOfWeapon1 <= 0 && numberOfWeapon2 <=0 && numberOfWeapon4 <= 0 )
                {
                    if (integrationScore <= targetIntegrationScore || exchangeBallnoonSprite != NULL)
                    {
                        this->bounceOutWeaponNELayer(pSceneNumber, 1);
                    }
                }
                else
                {
                    this->showWeaponNotEnough(3);
                }
                break;
            case 4:
                if (numberOfWeapon4 > 0) {
                    numberOfWeapon4--;
                    topBarLayer->updateNumberOfWeapon(4, numberOfWeapon4);
                    data.setMoonNumber(numberOfWeapon4);
                    this->weaponSpriteMoveTo();
                }
                else if (numberOfWeapon1 <= 0 && numberOfWeapon2 <=0 && numberOfWeapon3 <= 0 )
                {
                    if (integrationScore <= targetIntegrationScore || exchangeBallnoonSprite != NULL )
                    {
                        this->bounceOutWeaponNELayer(pSceneNumber, 1);
                    }
                }
                else
                {
                    this->showWeaponNotEnough(4);
                }
                break;
            default:
                break;
        }
    }
    offSetXY = 0;
}



// 碰撞检测
void GameScene::checkForCollision()
{
    dartSpriteRadius = propsSprite->getContentSize().width;
    switch (propsSprite->getTag()) {
        case 1:
            ratio = 0.5;
            break;
        case 2:
            ratio = 1.0;
            break;
        case 3:
            ratio = 1.0;
            break;
        case 4:
            ratio = 1.0;
            break;
        default:
            break;
    }
    
    for (int i = 0; i < ballnoonSprites->count(); i++) {
        CCSprite* ballnoon = (CCSprite*)ballnoonSprites->objectAtIndex(i);
        maxCollisionDistance = dartSpriteRadius*ratio + ballnoon->getContentSize().width*0.5;
        float actualDistance = ccpDistance(ballnoon->getPosition(), propsSprite->getPosition());
        if (actualDistance < maxCollisionDistance) {
            if (tempTag==ballnoon->getTag()) {
                return;
            }
            isshootedBallnoon++;
            tempTag = ballnoon->getTag();
            disBallnoonPosition = ballnoon->getPosition();
            this->ballnoonBoomEffects(ballnoon,tempTag);
            
            shootedBallnoonNumber++;
            switch (propsSprite->getTag()) {
                case 1:
                    if (shootedBallnoonNumber > 0) {
                        propsSprite->stopAction(sequence);
                        this->weaponSpriteResetPosition();
                    }
                    break;
                case 2:
                    if (shootedBallnoonNumber > 1) {
                        propsSprite->stopAction(sequence);
                        this->weaponSpriteResetPosition();
                    }
                    break;
                case 3:
                    if (shootedBallnoonNumber > 2) {
                        propsSprite->stopAction(sequence);
                        this->weaponSpriteResetPosition();
                    }
                    break;
                case 4:
                    if (shootedBallnoonNumber > 0) {
                        propsSprite->stopAction(sequence);
                        this->weaponSpriteResetPosition();
                    }
                    break;
                default:
                    break;
            }
            break;
        }
    }
}



#pragma mark --------------- 备用 ---------------
//保存用户武器数量
void GameScene::archiveWeaponNumber()
{
    data.openDatabase();
    
    data.setFireNumber(numberOfWeapon2);
    data.setStarNumber(numberOfWeapon3);
    data.setMoonNumber(numberOfWeapon4);

    data.closeDatabase();
}



void GameScene::setWeaponNumbers(int kTag, int number)
{
    switch (kTag) {
        case 2:
            numberOfWeapon2 = number;
            break;
        case 3:
            numberOfWeapon3 = number;
            break;
        case 4:
            numberOfWeapon4 = number;
            break;
            
        default:
            break;
    }
}



void GameScene::guidePrompt()
{
    CCSprite* guideGesture = CCSprite::create("ZF_Shoot_GameScene_guide.png");
    guideGesture->setPosition(CCPointMake(280, 220));
    this->addChild(guideGesture,3);
    
    CCCallFuncN* funcnOfcallback = CCCallFuncN::create(this, callfuncN_selector(GameScene::callback1));
    CCActionInterval* moveTo = CCMoveTo::create(1.0, CCPointMake(180, 220));
    CCActionInterval* fadeOut = CCFadeOut::create(0.1);
    CCActionInterval* moveBack = CCMoveTo::create(0.2,CCPointMake(280, 220));
    CCActionInterval* fadeIn = CCFadeIn::create(0.1);
    CCSequence* sequence = CCSequence::create(fadeIn,moveTo,fadeOut,moveBack,NULL);
    CCActionInterval* repeate = CCRepeat::create(sequence, 3);
    CCSequence* sequence2 = CCSequence::create(repeate,funcnOfcallback,NULL);
    guideGesture->runAction(sequence2);
}










