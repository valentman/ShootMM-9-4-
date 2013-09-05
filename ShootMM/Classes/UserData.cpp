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


#include "UserData.h"

USING_NS_CC;
using namespace std;


#pragma mark-初始化数据库

//1.0判断数据库是否存在，
void UserData::init()
{
    string path = CCFileUtils::sharedFileUtils()->getWritablePath()+"mySqlite.db";
    
    //remove(path.c_str());
    
    int flag = access(path.c_str(), 0);
    if (flag != 0) {
        this->initDataBase();
    }
}

//1.1初始化数据库mySqlite,全部数据为null
bool UserData::initDataBase()
{
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("userPhoto", 1);
    
    
    //获取salite本地数据库路径
    this->path = CCFileUtils::sharedFileUtils()->getWritablePath()+"mySqlite.db";
    this->result = sqlite3_open(this->path.c_str(), &this->mySqlite);
    
    //SQLITE_OK宏定义为数字0
    if (this->result != SQLITE_OK) {
        CCLOG("UserData:打开数据库失败！");
        
    } else{
        CCLOG("UserData:创建数据库成功！");
        
    }
    
    //1.1创建用户数据表myTable
    this->result = sqlite3_exec(this->mySqlite, "create table myTable (UserName_col TEXT,UserID_col INTERGER, passWord_col TEXT,UserHash_col TEXT,error_col INTERGER,Fubi_col INTERGER,ExchangeFubi_col REAl,exerciseScore_col REAL,normalScore_col REAL,richScore_col REAL,gateExerciseNO_col INTERGER,gateNormalNO_col INTERGER,gateRichNO_col INTERGER,infoTime_col INTERGER,fire_col INTERGER,star_col INTERGER,moon_col INTERGER,lastlogintime_col INTERGER,isTheFirstLogin_col INTERGER,isFirstPlayGame_col INTERGER)", NULL, NULL, NULL);
    if (this->result == SQLITE_OK) {
        CCLOG("UserData:创建用户数据表成功！");
    } else {
        CCLOG("UserData:创建用户数据表失败！");
    }
    
    //1.2用户数据表myTable插入数据,初始化所有数据，用户名称设为""，数字设为0
    this->result = sqlite3_exec(this->mySqlite, "insert into myTable values('Jobs',0,'','',1,1000,0,0,0,0,1,1,1,0,5,5,5,0,1,1)", NULL, NULL, NULL);
    if (this->result != SQLITE_OK) {
        CCLOG("UserData:用户数据表插入数据失败！");
    }else {
        CCLOG("UserData:用户数据表插入数据成功！");
    }
    
    
    sqlite3_close(this->mySqlite);
    return true;
    
}

void UserData::openDatabase()
{
    this->path = CCFileUtils::sharedFileUtils()->getWritablePath()+"mySqlite.db";
    sqlite3_open(this->path.c_str(), &this->mySqlite);
}

#pragma mark-用户信息
#pragma mark-1.设置、取出用户名
//1.设置、取出用户名
void UserData::setUserName(string UserName)
{
    
    this->UserName = UserName;
    string sql = "update myTable set UserName_col =";
    sql = sql+"'"+ this->UserName +"'";
    char *temp= (char *)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户名称成功");
    } else {
        CCLOG("UserData:设置用户名称失败");
    }
    
}
string UserData::getUserName()
{
    
    char **re;
    int r,c;
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select UserName_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户名称失败！");
    }else {
        CCLOG("UserData:取出用户名称成功！");
    }
    
    string UserName = re[1];
    return UserName;
    
}

#pragma mark-2.设置、取出用户ID
//2.设置、取出用户ID
void UserData::setUserID(int UserID)
{
    this->UserID = UserID;
    string sql = "update myTable set UserID_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",this->UserID);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户ID成功");
    } else {
        CCLOG("UserData:设置用户ID失败");
    }
    
}
int UserData::getUserID()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select UserID_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户ID失败！");
    }else {
        CCLOG("UserData:取出用户ID成功！");
    }
    int UserID = atoi(re[1]);
    return UserID;
}

#pragma mark-3.设置、取出用户密码
//3.设置、取出用户密码
void UserData::setPassWord(string PassWord)
{
    this->passWord = PassWord;
    string sql = "update myTable set passWord_col =";
    sql = sql+"'"+ this->passWord +"'";
    char *temp= (char *)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置密码成功");
    } else {
        CCLOG("UserData:设置密码失败");
    }
    
}
string UserData::getPassWord()
{
    char **re;
    int r,c;
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select passWord_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出密码失败！");
    }else {
        CCLOG("UserData:取出密码成功！");
    }
    
    
    string passWord = re[1];
    return passWord;
}

#pragma mark-4.设置、取出用户哈希值
//4.设置、取出用户哈希值
void UserData::setUserHash(string UserHash)
{
    this->UserHash = UserHash;
    string sql = "update myTable set UserHash_col =";
    sql = sql+"'"+ this->UserHash +"'";
    char *temp= (char *)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户hash成功");
    } else {
        CCLOG("UserData:设置用户hash失败");
    }
    
}
string UserData::getUserHash()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select UserHash_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户hash失败！");
    }else {
        CCLOG("UserData:取出用户hash成功！");
    }
    string UserHash = re[1];
    return UserHash;
}

#pragma mark-5.设置、取出用户登录信息判断
//5.用户登录信息判断
void UserData::setError(int error)
{
    this->error = error;
    string sql = "update myTable set error_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",this->error);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户登录信息成功");
    } else {
        CCLOG("UserData:设置用户登录信息失败");
    }
    
}
int UserData::getError()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select error_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:查询用户登录信息失败！");
    }else {
        CCLOG("UserData:查询用户登录信息成功！");
    }
    int error = atoi(re[1]);
    return error;
}

#pragma mark-6.设置、取出用户富币信息
//6.设置、取出用户富币信息
void UserData::setFubi(int Fubi)
{
    this->Fubi = Fubi;
    string sql = "update myTable set Fubi_col =";
    char tempChar[11];
    sprintf(tempChar,"%.0f",this->Fubi);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户富币信息成功");
    } else {
        CCLOG("UserData:设置用户富币信息失败");
    }
    
}
int UserData::getFubi()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select Fubi_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户富币信息失败！");
    }else {
        CCLOG("UserData:取出用户富币信息成功！");
    }
    
    int Fubi = atoi(re[1]);
    return Fubi;
}

#pragma mark-7.设置、取出用户可兑换富币信息
//7.设置、取出可兑换用户富币信息
void UserData::setExchangeFubi(double ExchangeFubi)
{
    this->ExchangeFubi = ExchangeFubi;
    string sql = "update myTable set ExchangeFubi_col =";
    char tempChar[11];
    sprintf(tempChar,"%.0f",this->ExchangeFubi);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户可兑换富币信息成功");
    } else {
        CCLOG("UserData:设置用户可兑换富币信息失败");
    }
    
}
double UserData::getExchangeFubi()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select ExchangeFubi_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户可兑换富币信息失败！");
    }else {
        CCLOG("UserData:取出用户可兑换富币信息成功");
    }
    double ExchangeFubi = atof(re[1]);
    return ExchangeFubi;
}


#pragma mark-8.设置、取出用户练习场分数信息
//8.设置、取出用户练习场分数信息
void UserData::setExerciseScore(double score)
{
    this->exerciseScore = score;
    string sql = "update myTable set exerciseScore_col =";
    char tempChar[11];
    sprintf(tempChar,"%.0f",this->exerciseScore);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户练习场分数信息成功");
    } else {
        CCLOG("UserData:设置用户练习场分数信息失败");
    }
    
}
double UserData::getExerciseScore()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select exerciseScore_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户练习场分数信息失败！");
    }else {
        CCLOG("UserData:取出用户练习场分数信息成功！");
    }
    double exerciseScore = atof(re[1]);
    return exerciseScore;
}


#pragma mark-9.设置、取出用户平民场分数信息
//9.设置、取出用户平民场分数信息
void UserData::setNormalScore(double score)
{
    this->normalScore = score;
    string sql = "update myTable set normalScore_col =";
    char tempChar[11];
    sprintf(tempChar,"%.0f",this->normalScore);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户平民场分数信息成功");
    } else {
        CCLOG("UserData:设置用户平民场分数信息失败");
    }
    
}
double UserData::getNormalScore()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select normalScore_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户平民场分数信息失败！");
    }else {
        CCLOG("UserData:取出用户平民场分数信息成功！");
    }
    double normalScore = atof(re[1]);
    return normalScore;
}



#pragma mark-10.设置、取出用户富豪场分数信息
//8.设置、取出用户富豪场分数信息
void UserData::setRichScore(double score)
{
    this->richScore = score;
    string sql = "update myTable set richScore_col =";
    char tempChar[11];
    sprintf(tempChar,"%.0f",this->richScore);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户富豪场分数信息成功");
    } else {
        CCLOG("UserData:设置用户富豪场分数信息失败");
    }
    
}
double UserData::getRichScore()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select richScore_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户富豪场分数信息失败！");
    }else {
        CCLOG("UserData:取出用户富豪场分数信息成功！");
    }
    double richScore = atof(re[1]);
    return richScore;
}


#pragma mark-11.设置、取出用户练习场关卡数目
//11.设置、取出用户练习场关卡数目
void UserData::setGateExerciseNO(int gateExerciseNO)
{
    this->gateExerciseNO = gateExerciseNO;
    string sql = "update myTable set gateExerciseNO_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",this->gateExerciseNO);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户练习场关卡数目成功");
    } else {
        CCLOG("UserData:设置用户练习场关卡数目失败");
    }
    
}
int UserData::getGateExerciseNO()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select gateExerciseNO_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户练习场关卡数目失败！");
    }else {
        CCLOG("UserData:取出用户练习场关卡数目成功！");
    }
    int gateExerciseNO = atoi(re[1]);
    return gateExerciseNO;
}

#pragma mark-12.设置、取出用户平民场关卡数目
//12.设置、取出用户平民场关卡数目
void UserData::setGateNormalNO(int gateNormalNO)
{
    this->gateNormalNO = gateNormalNO;
    string sql = "update myTable set gateNormalNO_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",this->gateNormalNO);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户平民场关卡数目成功");
    } else {
        CCLOG("UserData:设置用户平民场关卡数目失败");
    }
    
}
int UserData::getGateNormalNO()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select gateNormalNO_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户平民场关卡数目失败！");
    }else {
        CCLOG("UserData:取出用户平民场关卡数目成功！");
    }
    int gateNormalNO = atoi(re[1]);
    return gateNormalNO;
}

#pragma mark-13.设置、取出用户富豪场关卡数目
//13.设置、取出用户富豪场关卡数目
void UserData::setGateRichNO(int gateRichNO)
{
    this->gateRichNO = gateRichNO;
    string sql = "update myTable set gateRichNO_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",this->gateRichNO);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户富豪场关卡数目成功");
    } else {
        CCLOG("UserData:设置用户富豪场关卡数目失败");
    }
    
}
int UserData::getGateRichNO()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select gateRichNO_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户富豪场关卡数目失败！");
    }else {
        CCLOG("UserData:取出用户富豪场关卡数目成功！");
    }
    int gateRichNO = atoi(re[1]);
    return gateRichNO;
}



#pragma mark-14.设置、取出用户火球数目
void UserData::setFireNumber(int FireNumber)
{
    string sql = "update myTable set fire_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",FireNumber);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户火球数目成功");
    } else {
        CCLOG("UserData:设置用户火球数目失败");
    }

}

int UserData::getFireNumber()
{
    char **re;
    int r,c;
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select fire_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户火球数目失败！");
    }else {
        CCLOG("UserData:取出用户火球数目成功！");
    }
    int getFireNO = atoi(re[1]);
    return getFireNO;
}


#pragma mark-15.设置、取出用户星光数目
void UserData::setStarNumber(int StarNumber)
{
    string sql = "update myTable set star_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",StarNumber);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户星光数目成功");
    } else {
        CCLOG("UserData:设置用户星光数目失败");
    }
}


int UserData::getStarNumber()
{
    char **re;
    int r,c;
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select star_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户星光数目失败！");
    }else {
        CCLOG("UserData:取出用户星光数目成功！");
    }
    int getStarNO = atoi(re[1]);
    return getStarNO;
}


#pragma mark-16.设置、取出用户月牙数目
void UserData::setMoonNumber(int MoonNumber)
{
    string sql = "update myTable set moon_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",MoonNumber);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户月牙数目成功");
    } else {
        CCLOG("UserData:设置用户月牙数目失败");
    }
}


int UserData::getMoonNumber()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select moon_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户月牙数目失败！");
    }else {
        CCLOG("UserData:取出用户月牙数目成功！");
    }
    int getMoonNO = atoi(re[1]);
    return getMoonNO;
}



#pragma mark-17.设置、取出用户上次登录时间
void UserData::setCurrentTime(int currentTime)
{
    string sql = "update myTable set lastlogintime_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",currentTime);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户当前时间成功");
    } else {
        CCLOG("UserData:设置用户当前时间失败");
    }
}


int UserData::getLastLoginTime()
{
    char **re;
    int r,c;
    
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select lastlogintime_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户当前时间失败！");
    }else {
        CCLOG("UserData:取出用户当前时间成功！");
    }
    int getLastLoginTime = atoi(re[1]);
    return getLastLoginTime;
}



#pragma mark-18.设置、取出用户是否第一次登陆
void UserData::setIsFirstLogin(int isFirst)
{
    string sql = "update myTable set isTheFirstLogin_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",isFirst);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户是否第一次登陆成功");
    } else {
        CCLOG("UserData:设置用户是否第一次登陆失败");
    }
}

int UserData::getIsFirstLogin()
{
    char **re;
    int r,c;
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select isTheFirstLogin_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户是否第一次登陆失败！");
    }else {
        CCLOG("UserData:取出用户是否第一次登陆成功！");
    }
    int  getIsFirstLogin = atoi(re[1]);
    return getIsFirstLogin;
}



#pragma mark-19.设置、取出用户是否第一次进游戏场景
void UserData::setIsFirstPlayGame(int isFirst)
{
    string sql = "update myTable set isFirstPlayGame_col =";
    char tempChar[11];
    sprintf(tempChar,"%d",isFirst);
    string tempString = tempChar;
    sql = sql+tempString;
    char *temp = (char*)sql.c_str();
    int resultThis = sqlite3_exec(this->mySqlite, temp, NULL, NULL, NULL);
    if (resultThis==SQLITE_OK) {
        CCLOG("UserData:设置用户是否第一次进游戏场景成功");
    } else {
        CCLOG("UserData:设置用户是否第一次进游戏场景失败");
    }
}


int UserData::getIsFirstPlayGame()
{
    char **re;
    int r,c;
    
    int resultThis = sqlite3_get_table(this->mySqlite, "select isFirstPlayGame_col from myTable", &re, &r, &c, NULL);
    
    if (resultThis != SQLITE_OK) {
        CCLOG("UserData:取出用户是否第一次进游戏场景失败！");
    }else {
        CCLOG("UserData:取出用户是否第一次进游戏场景成功！");
    }
    int  getIsFirstPlayGame = atoi(re[1]);
    return getIsFirstPlayGame;
}
