/************************************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd. All rights reserved.
 
 FileName: AppController.mm
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-6-13.
 
 Description:
 
 FunctionList:
 
 ************************************************************************/

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;

}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

