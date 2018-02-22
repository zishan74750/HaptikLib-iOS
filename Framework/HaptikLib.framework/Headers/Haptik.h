//
//  Haptik.h
//  HaptikLib - Haptik Personal Assistant SDK for iOS
//
//  Copyright © 2018 Haptik. All rights reserved.
//
//  Usage of this SDK is subject to the Haptik Terms of
//  Service: https://haptik.ai/terms-conditions
//


#import <UIKit/UIKit.h>

@class HPInitObject;
@class HPSignUpObject;
@class HPThemeService;


NS_ASSUME_NONNULL_BEGIN


#pragma mark - Run Environment

typedef NS_ENUM(NSUInteger, HaptikLibRunEnvironment) {
    
    HaptikLibEnvProduction = 0,
    HaptikLibEnvStage,
    HaptikLibEnvDevelopment
};


#pragma mark - User Authentication Type

typedef NS_ENUM(NSUInteger, HaptikLibAuthType) {
    
    HaptikLibAuthTypeBasic = 0,
    HaptikLibAuthTypeOTP,
    HaptikLibAuthTypeSSO
};


#pragma mark - Analytics Service

@protocol HPAnalyticsServiceDelegate <NSObject>
@optional
- (void)eventTracked:(NSString *)eventName forParams:(nullable NSDictionary *)params;
- (void)errorTracked:(NSString *)errorMessage forError:(nullable NSError *)error;
@end


#pragma mark - Share Haptik

@protocol HPShareAndEarnDelegate <NSObject>
@optional
- (void)shareAndEarnTapped;
@end


#pragma mark -

/*!
    Everytime wallet balance is updated a notification is fired by HaptikLib for observing wallet balance updates.
    Updated balance can also be fetched from `getHaptikWalletBalance()`
 */
UIKIT_EXTERN NSNotificationName const HPWalletBalanceUpdated;


/*!
    Everytime available offers count is updated a notification is fired by HaptikLib
    Updated available offers count can also be fetched from `getOffersCount()`
 */
UIKIT_EXTERN NSNotificationName const HPOffersUpdatedNotification;



@interface Haptik : NSObject

/*!
    Returns the Haptik singleton object
 */
+ (instancetype)sharedSDK;


- (instancetype)init NS_UNAVAILABLE;


#pragma mark - Configuration Attributes

/*!
 Sets HPThemeService Object used for applying Theming Configurations
 */
@property (nonatomic) HPThemeService *themeConfig;


/*!
 Set Show Banners BOOL
 This BOOL controls the visibility of Banners on the Inbox Screen of Haptik. By default the value will be true.
 */
@property (nonatomic, assign) BOOL showBanners;


/*!
 Set Use Referrals BOOL
 This BOOL controls the use of Referral Flows in Haptik. By default the value will be false.
 */
@property (nonatomic, assign) BOOL shouldUseReferrals;


/*!
 Analytics Callback Object
 If provided, Analytics Service Class will send delegate callbacks to the provided delegate self.
 */
@property (nullable, nonatomic, weak) id <HPAnalyticsServiceDelegate> analyticsCallbackObject;


/*!
 Sets the Custom Title text to be shown on the Loading Screen. If not provided, default text will be shown.
 */
@property (nullable, nonatomic) NSString *loadingTitleText;


/*!
 Sets the Custom Subtitle text to be shown on the Loading Screen. If not provided, default text will be shown.
 */
@property (nullable, nonatomic) NSString *loadingSubtitleText;


/*!
 Gets the API key for the current app. This should only be called after the SDK has been initialized otherwise will return nil
 */
@property (nonatomic, readonly) NSString *apiKey;


/*!
 Gets the base endpoint to use. This should only be called after the SDK has been initialized otherwise will return nil
 */
@property (nonatomic, readonly) NSString *baseUrl;


/*!
 Gets the client id for the current app. This should only be called after the SDK has been initialized otherwise will return nil
 */
@property (nonatomic, readonly) NSString *clientID;


/*!
 Gets the run environment of the SDK. This should only be called after the SDK has been initialized otherwise will return HaptikLibEnvProduction(== 0)
 */
@property (nonatomic, readonly) HaptikLibRunEnvironment runEnvironment;


#pragma mark - SDK Signup Helpers

/*!
 @method
 SignIn the User with SignUp Data.
 
 @param signUpData   Object of HPSignUpObject
 @param completion   Completion Handler which will have the success or error information.
 */
- (void)signUpWith:(HPSignUpObject *)signUpData
        completion:(void (^)(BOOL success,__kindof UIViewController * _Nullable initialVC, NSError * _Nullable error))completion;


/*
 @abstract
 SignIn the User with SignUp Data.
 
 @discussion
 -  This function immediately returns the Initial View Controller. The loading view will be shown till the inital data is synced.
 -  If an error comes up, the user will be popped back.
 
 @param signUpData  Object of HPSignUpObject
 @param completion  Completion Handler which will have the success or error information.
 */
- (__kindof UIViewController *_Nullable)signUpWithLoadingScreenFor:(HPSignUpObject *)signUpData
                                                        completion:(void (^)(BOOL success, NSError * _Nullable error))completion;


/*!
 @method
 Returns a Bool indicating if the user is already signed up or not.
 */
- (BOOL)isUserSignedUp;


/*!
 @method
 Returns the Initial View Controller if the User has already signed up.
 */
- (__kindof UIViewController * _Nullable)getInitialVC;


/*!
 @method
 Notify the Haptik SDK of application launch
 @param application Your singleton app object
 @param launchOptions A dictionary indicating the reason the app was launched (if any). The contents of this dictionary may be empty in situations where the user launched the app directly.
 
 @code
 
 #import "AppDelegate.h"
 
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    ...
    [[Haptik sharedSDK] notifyApplication:application launchedWithOptions:launchOptions];
 }
 
 @endcode
 */
- (void)notifyApplication:(UIApplication *)application launchedWithOptions:(nullable NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions;


#pragma mark - Haptik Wallet

/*!
 @method
 Returns boolean value indicating if User's Haptik Wallet has been created or not.
 */
- (BOOL)isHaptikWalletCreated;


/*!
 @method
 Returns String value of User's Haptik Wallet Balance. Will return nil if:
 - User's wallet has not been created yet.
 - Haptik Wallet Servers are currently down.
 */
- (NSString *)getHaptikWalletBalance;


/*!
    @method
    By calling this method you will get an instance of Haptik Wallet Screen.

    @param defaultsToHistory    A boolean indicating whether the wallet history tab should be selected by default or not.
    @param delegate     If shouldUseReferrals property of Haptik is set to true, then the delegate will pass the callbacks when the Share and Earn View is Tapped in the Wallet Scene.
 
 */
- (void)getHaptikWalletViewController:(BOOL)defaultsToHistory
                 shareAndEarnDelegate:(nullable id <HPShareAndEarnDelegate>)delegate
                           controller:(__kindof UIViewController *__weak)controller
                           completion:(void(^)(BOOL success, __kindof UIViewController *_Nullable haptikWalletVC))completion;


#pragma mark - Current Offers

/*!
 @method
 By calling this method you will get current offers count
 */
- (NSUInteger)getOffersCount;


/*!
    @method
    By calling this method you will get an instance of Offers Screen.
 */
- (__kindof UIViewController *_Nullable)getOffersViewContoller;


#pragma mark - Remote Notifications

/*!
 @method
 
 @abstract
 Register the device to receive push notifications.
 
 @discussion
 This will associate the device token with the current user to allow push notifications to the user.
 
 @param deviceToken  device token as returned from application:didRegisterForRemoteNotificationsWithDeviceToken:
 */
- (void)setDeviceToken:(NSData *)deviceToken;


/*!
 @method
 
 @abstract
 Informs the caller whether passed notification userinfo payload can be handled by HaptikLib.
 If YES, the payload is processed by HaptikLib.
 
 @param userInfo     The received remote notification payload to be processed
 @return    Returns a BOOL indicating indicating the payload will be handled by HaptikLib
 */
- (BOOL)handleNotificationWithUserInfo:(NSDictionary<NSString *, id> *)userInfo;


#pragma mark -

/*!
 Allows you to take user to a specific channel.
 @param viaName Represents the string key used to uniquely specify channel inside Haptik
 @param message String message to be sent from user-side on opening channel screen
 @param controller The current view controller over which the channel is expected to be pushed
 
 @code
 
 #import "MyViewController.h"
 
 - (void)openChannelInHaptik {
 
    [[Haptik sharedSDK] launchChannelWith:@"mychannelinhaptik"
                                  message:@"We wish you have a good time using this SDK"
                               controller:self];
 }
 
 @endcode
 */
- (void)launchChannelWith:(NSString *)viaName
                  message:(nullable NSString *)message
               controller:(__kindof UIViewController *)controller;


/*!
 Specifies whether Haptik Lib will handle URL redirects
 @param url  The url expected to be handled
 @param options  A dictionary of URL handling options
 */
- (BOOL)isRedirectHandled:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options;


/*!
 @method
 By calling this method you will get an instance of Transaction History Screen.
 */
- (void)getTransactionHistoryFor:(__kindof UIViewController *__weak)controller
                      completion:(void(^)(BOOL success, __kindof UIViewController *_Nullable transactionsVC))completion;


/*!
 @method
 By calling this method you will get the Unread Count of the Users Inbox Chats.
 */
- (void)getUnreadCountWithCompletion:(void(^)(NSUInteger unreadCount))completion;

@end


NS_ASSUME_NONNULL_END

