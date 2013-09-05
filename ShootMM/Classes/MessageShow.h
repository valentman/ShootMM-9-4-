/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: MessageShow.h
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-7-5.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#import <Foundation/Foundation.h>
#import <MessageUI/MessageUI.h>

@interface MessageShow : UIViewController<MFMessageComposeViewControllerDelegate>
{
    NSString* address;
}
- (void)showSMSPicker;
- (void)displaySMSComposerSheet;
- (void)messageComposeViewController:(MFMessageComposeViewController *)controller didFinishWithResult:(MessageComposeResult)result;

@end
