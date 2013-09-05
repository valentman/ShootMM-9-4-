/******************************************************
 
 Copyright (C), 2013-2014, ZhangFu Tech. Co., Ltd.
 
 Filename: MessageShow.m
 
 ProjectName: 射你妹
 
 Author: P.Joe     Version: 1.0     Date: 13-7-5.
 
 Description:
 
 FunctionList:
 
 
 *******************************************************/

#import "MessageShow.h"

@implementation MessageShow

//短信
-(void)showSMSPicker
{
    Class messageClass = (NSClassFromString(@"MFMessageComposeViewController"));
    if (messageClass != nil) {
        
        // Check whether the current device is configured for sending SMS messages
        if ([messageClass canSendText]) {
            [self displaySMSComposerSheet];
        }
        else {
            UIAlertView *alert=[[UIAlertView alloc] initWithTitle:@""message:@"设备不支持短信功能" delegate:self cancelButtonTitle:@"确定"otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
    }
    else {
    }
}

-(void)displaySMSComposerSheet
{
    MFMessageComposeViewController *picker = [[MFMessageComposeViewController alloc] init];
    picker.messageComposeDelegate =self;
    address = @"brave guy!";
    NSString *smsBody =[NSString stringWithFormat:@"我分享了文件给您，地址是%@",address] ;
    picker.body=smsBody;
    [self presentViewController: picker animated:YES completion:nil];
    [picker release];
    
}

- (void)messageComposeViewController:(MFMessageComposeViewController *)controller didFinishWithResult:(MessageComposeResult)result
{
    switch (result)
    {
        case MessageComposeResultCancelled:
            //LOG_EXPR(@"Result: SMS sending canceled");
            break;
        case MessageComposeResultSent:
        {
//            if (self.orderHistory == nil) {
//                self.orderHistory = [[OrderHistory alloc] init];
//                self.orderHistory.strRecommenderTime = self.orderInfo.strRecommenderTime;
//                self.orderHistory.strRecommenderNum = self.orderInfo.strRecommenderNum;
//            }
//            self.orderHistory.strOrderState = self.orderInfo.strOrderState;
//            self.orderHistory.strAction = @"短信通知";
            NSDateFormatter *dateFormatter = [[NSDateFormatter alloc]init];
            [dateFormatter setDateStyle:NSDateFormatterMediumStyle];
            [dateFormatter setTimeStyle:NSDateFormatterShortStyle];
            [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
            NSString *dateTime = [dateFormatter stringFromDate:[NSDate date]];
//            self.orderHistory.strActionTime = [[NSString alloc] initWithString:dateTime];
            [self saveHistory];
            UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"提示" message:@"发送成功" delegate:self cancelButtonTitle:@"关闭" otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
            break;
        case MessageComposeResultFailed:
        {
            
            UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"提示" message:@"发送失败" delegate:self cancelButtonTitle:@"关闭" otherButtonTitles:nil];
            [alert show];
            [alert release];
            
        }
            break;
        default:
            //LOG_EXPR(@"Result: SMS not sent");
            break;
    }
    [self dismissModalViewControllerAnimated:YES];
    
}



@end
