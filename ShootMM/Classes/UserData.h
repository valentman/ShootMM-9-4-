/*******************************************************************
 
 Copyright (C), 2013-2014, zhangfu Tech. Co., Ltd.
 
 Filename: UserData.m
 
 Author: Kevin     Version: 1.0     Date: 13-6-24.
 
 Description: The main userData of this game.
 
 FunctionList:
 
 void init();
 virtual bool initDataBase();
 
 //数据库开关的1个内联函数
 void openDatabase();
 
 void closeDatabase()
 {
 sqlite3_close(mySqlite);
 }
 
 //1.用户信息
 void setUserName(string UserName);
 string getUserName();
 
 void setUserID(int UserID);
 int getUserID();
 
 void setPassWord(string PassWord);
 string getPassWord();
 
 void setUserHash(string UserHash);
 string getUserHash();
 
 void setError(int error);
 int getError();
 
 void setFubi(double Fubi);
 double getFubi();
 
 void setExchangeFubi(double ExchangeFubi);
 double getExchangeFubi();
 
 void setExerciseScore(double score);
 double getExerciseScore();
 
 void setNormalScore(double score);
 double getNormalScore();
 
 void setRichScore(double score);
 double getRichScore();

  void setGateExerciseNO(int gateExerciseNO);
 int getGateExerciseNO();
 
 void setGateNormalNO(int gateNormalNO);
 int getGateNormalNO();
 
 void setGateRichNO(int gateRichNO);
 int getGateRichNO();
 
 void setName(string Name);
 string getName();
 
 void setAddress(string Address);
 string getAddress();
 
 void setPhoneNumber(string PhoneNumber);
 string getPhoneNumber();
 
 //2.奖品信息
 void setGateNO(int GateNO);
 int getGateNO();
 
 void setTargetPrice(int GateNO,double TargetPrice);
 double getTargetPrice(int GateNO);
 
 void setTopPrice(int GateNO,double TopPrice);
 double getTopPrice(int GateNO);
 
 void setEntityAmount(int GateNO,double EntityAmount);
 double getEntityAmount(int GateNO);
 
 void setGateExchangeFubi(int GateNO,double GateExchangeFubi);
 double getGateExchangeFubi(int GateNO);
 
 void setGateCostFubi(int GateNO,double GateCostFubi);
 double getGateCostFubi(int GateNO);
 
 //3.奖品列表信息
 void setPrizeList(int PrizeID,string PrizeName,double PrizeWorth,string picName,int PrizeType);
 char** getPrizeList();
 
 bool isExsitedPrizeList();
 
 void deletePrizeList();
 void createPrizList();
 ********************************************************************/

#ifndef __jsonCurlTest__UserData__
#define __jsonCurlTest__UserData__

#include <iostream>
#include <cocos2d.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


using namespace std;
USING_NS_CC;


class UserData {
private:
    
    //初始化数据库
    sqlite3 *mySqlite ;
    //sql语句执行后的返回结果
    int    result;
    string path;
    
    //1.用户信息
    string UserName;
    int    UserID;
    string passWord;
    string UserHash;
    //登陆信息判断
    int    error;
    double Fubi;
    double ExchangeFubi;

    //练习场、平民场、富豪场分数
    double exerciseScore;
    double normalScore;
    double richScore;
    
    //练习场、平民场、富豪场关卡等级
    int    gateExerciseNO;
    int    gateNormalNO;
    int    gateRichNO;
    //兑奖信息中的用户名称、地址和手机号码
    string name;
    string address;
    string phoneNmber;
    //infoTime,服务器访问时间间隔
    int infoTime;
    
    
    //2.奖品信息和关卡信息
    int     GateNO;
    double  TargetPrice;
    double  TopPrice;
    double  EntityAmount;
    double  GateExchangeFubi;
    double  GateCostFubi;
    /*dx表示气球大小参数(float)------ballnoonSpriteSize
     jf表示目标积分参数(int)---------targetIntegration
     sd表示速度参数（float）---------ballnoonSpriteSpeed
     js表示免费子弹参数(int) ---------freeBulletNumber*/
    double ballnoonSpriteSize;
    double ballnoonSpriteSpeed;
    int    targetIntegration;
    int    freeBulletNumber;
    
    //3.奖品列表信息
    int     PrizeID;
    string  PrizeName;
    double  PrizeWorth;
    string  picName;
    int     PrizeType;
    //boss气球信息
    string  BossPicName;
    double  BossSpeed;
    double  BossLife;
        
public:
    
    UserData()
    {
        mySqlite = NULL;
    }
    
    void init();
    virtual bool initDataBase();
    
    //数据库开关的1个内联函数
    void openDatabase();
    
    void closeDatabase()
    {
        sqlite3_close(mySqlite);
    }
    
    //1.用户信息
    void setUserName(string UserName);
    string getUserName();
    
    void setUserID(int UserID);
    int getUserID();
    
    void setPassWord(string PassWord);
    string getPassWord();
    
    void setUserHash(string UserHash);
    string getUserHash();
    
    void setError(int error);
    int getError();
    
    void setFubi(int Fubi);
    int getFubi();
    
    void setExchangeFubi(double ExchangeFubi);
    double getExchangeFubi();

    
    void setExerciseScore(double score);
    double getExerciseScore();

    void setNormalScore(double score);
    double getNormalScore();

    void setRichScore(double score);
    double getRichScore();

    void setGateExerciseNO(int gateExerciseNO);
    int getGateExerciseNO();
    
    void setGateNormalNO(int gateNormalNO);
    int getGateNormalNO();
    
    void setGateRichNO(int gateRichNO);
    int getGateRichNO();
    
    void setName(string Name);
    string getName();
    
    void setAddress(string Address);
    string getAddress();
    
    void setPhoneNumber(string PhoneNumber);
    string getPhoneNumber();
    
    void setInfoTime(int infoTime);
    int getInfoTime();
    
    
    //2.奖品信息
    void setGateNO(int GateNO);
    int getGateNO();
    
    void setTargetPrice(int GateNO,double TargetPrice);
    double getTargetPrice(int GateNO);
    
    void setTopPrice(int GateNO,double TopPrice);
    double getTopPrice(int GateNO);
    
    void setEntityAmount(int GateNO,double EntityAmount);
    double getEntityAmount(int GateNO);
    
    void setGateExchangeFubi(int GateNO,double GateExchangeFubi);
    double getGateExchangeFubi(int GateNO);
    
    void setGateCostFubi(int GateNO,double GateCostFubi);
    double getGateCostFubi(int GateNO);
    
    void setBallnoonSpriteSize(int GateNO,double ballnoonSpriteSize);
    double getBallnoonSpriteSize(int GateNO);
    
    void setBallnoonSpriteSpeed(int GateNO,double ballnoonSpriteSpeed);
    double getBallnoonSpriteSpeed(int GateNO);
    
    void seTtargetIntegration(int GateNO,double targetIntegration);
    int getTtargetIntegration(int GateNO);
    
    void setFreeBulletNumber(int GateNO,double freeBulletNumber);
    int getFreeBulletNumber(int GateNO);
    
    void setFireNumber(int FireNumber);
    int getFireNumber();
    
    void setStarNumber(int StarNumber);
    int getStarNumber();
    
    void setMoonNumber(int MoonNumber);
    int getMoonNumber();
    
    void setCurrentTime(int currentTime);
    int getLastLoginTime();
    
    void setIsFirstLogin(int isFirst);
    int getIsFirstLogin();
    
    void setIsFirstPlayGame(int isFirst);
    int getIsFirstPlayGame();
    
    //3.奖品列表信息和boss信息
    void setPrizeList(int PrizeID,string PrizeName,double PrizeWorth,string picName,int PrizeType ,string BossPicName,double BossSpeed ,double BossLife);
    char** getPrizeList();
    
    bool isExsitedPrizeList();
    
    void deletePrizeList();
    void createPrizList();

};
#endif /* defined(__jsonCurlTest__UserData__) */











