//
//  AcceptFreeFubi.cpp
//  Shoot
//
//  Created by Kevin on 13-7-29.
//
//

#include "AcceptFreeFubi.h"

CCScene* AcceptFreeFubi::scene()
{
    CCScene *scene = CCScene::create();
    AcceptFreeFubi *layer = AcceptFreeFubi::create();
    scene->addChild(layer);
    return scene;
    
}

bool AcceptFreeFubi::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    
    CCSprite *light = CCSprite::create("ZF_Shoot_MenuScene_background_freeFubi_light.png");
    light->setPosition(CCPointMake(winSize.width/3, winSize.height/2));
    CCActionInterval *actionLight1 = CCRotateBy::create(1, 200);
    CCActionInterval *actionLight2 = actionLight1->reverse();
    CCActionInterval *actionLight3 = CCRepeatForever::create(actionLight2);
    light->setAnchorPoint(CCPointMake(0.45, 0.5));
    light->runAction(actionLight3);
    this->addChild(light,1);
    
    
    CCSprite *box = CCSprite::create("ZF_Shoot_MenuScene_background_freeFubi_box.png");
    box->setPosition(CCPointMake(winSize.width/3, winSize.height/2));
    CCActionInterval *actionBox1 = CCSkewTo::create(2.0, 15, 0);
    CCActionInterval *actionBox2 = CCSkewTo::create(2.0, 0, 15);
    CCSequence *seq = CCSequence::create(actionBox1,actionBox2,NULL);
    CCActionInterval *repeat = CCRepeatForever::create(seq);
    box->runAction(repeat);
    this->addChild(box,1);
    
    
    CCParticleSystem *coin[4];
    string pictureArray[2] = {"ZF_Shoot_MenuScene_background_freeFubi_coin1.png","ZF_Shoot_MenuScene_background_freeFubi_coin2.png"};
    int TotalParticles = 100;
    int StartSize[2] = {70,90};
    int EndSize[2] = {65,85};
    int StartSpin = 20;
    int StartSpinVar = 10;
    int EndSpin = 280;
    int EndSpinVar = 10;
    int EmissionRate = 5;
    int Speed = 600;
    ccColor4F cc1;
    cc1.a=253.0f;
    cc1.b=185.0f;
    cc1.g=255.0f;
    cc1.r=255.0f;
    

    
    for (int i=0; i<3; i++) {
        
        coin[i] = CCParticleRain::create();
        coin[i]->setTotalParticles(TotalParticles);
        coin[i]->setEmitterMode(kCCParticleModeGravity);
        coin[i]->setStartColor(cc1);
        coin[i]->setEndColor(cc1);
        coin[i]->setSpeed(Speed);
        

        if ( i%2 == 0) {
            coin[i]->setTexture(CCTextureCache::sharedTextureCache()->addImage(pictureArray[0].c_str()));
            coin[i]->setStartSize(StartSize[0]);
            coin[i]->setEndSize(EndSize[0]);
        }else{
            coin[i]->setTexture(CCTextureCache::sharedTextureCache()->addImage(pictureArray[1].c_str()));
            coin[i]->setStartSize(StartSize[1]);
            coin[i]->setEndSize(EndSize[1]);
        }
        
        coin[i]->setStartSpin(StartSpin);
        coin[i]->setStartSpinVar(StartSpinVar);
        coin[i]->setEndSpin(EndSpin);
        coin[i]->setEndSpinVar(EndSpinVar);
        coin[i]->setEmissionRate(EmissionRate);
        this->addChild(coin[i], 1);
    }
    
   

    return true;
}








