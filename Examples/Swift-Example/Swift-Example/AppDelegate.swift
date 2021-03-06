//
//  AppDelegate.swift
//  Swift-Example
//
//  Created by SimranJot Singh on 12/12/18.
//  Copyright © 2018 Simranjot. All rights reserved.
//

import UIKit
import HaptikLib

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        
        // Required at the Initial Launch of the Application
        Haptik.sharedSDK().notify(application, launchedWithOptions: launchOptions)
        
        // Required for Enterprise Clients
        Haptik.sharedSDK().useInbox = false
        
        // If you need the callbacks of the analytics data that haptik sends
        Haptik.sharedSDK().analyticsCallbackObject = self;
        
        // Setup UI Theme for Haptik
        setHaptikTheme()
        
        // Interactive Pop Gesture
        
        // This BOOL controls the functionality of the EdgePanGestureRecognizer feature of UINavigationController
        // that allows to set the slide to go back functionality for Haptik Screens. By default the value will be true.
        
        Haptik.sharedSDK().useInteractivePopGesture = true
        
        return true
    }

    func application(_ app: UIApplication, open url: URL, options: [UIApplication.OpenURLOptionsKey : Any] = [:]) -> Bool {
        
        // Let Haptik handle the redirect if required
        
        let isHandledByHaptik = Haptik.sharedSDK().isRedirectHandled(url, options: options)
        return isHandledByHaptik
    }

    func application(_ application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: Data) {
        
        // You need to pass the Device Token after the user successfully signs up in Haptik. Till that you need to store it in your application.
        
        UserDefaults.standard.set(deviceToken, forKey: "kDeviceToken")
        UserDefaults.standard.synchronize()
    }
    
    func application(_ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable : Any]) {
        
        // Check if the notification received belongs to haptik and take action accordingly
        
        let isHaptikNotification = Haptik.sharedSDK().canHandleNotification(userInfo: userInfo as! [String : Any])
        
        if isHaptikNotification {
            
            print("Do Housekeeping")
            handleNotificationInteraction(userInfo as! [String : Any])
        }
    }
}


//MARK: Helper Methods

extension AppDelegate {
    
    func handleNotificationInteraction(_ userInfo: [String: Any]) {
        
        if let rootVC = self.window?.rootViewController {
            if let controller = rootVC as? UINavigationController {
                
                // You need to pass an instance of a viewController from which the user will be taken to the conversationViewController (where the user will be conversing)
                // on the tap of the Notification
                
                Haptik.sharedSDK().handleNotification(userInfo: userInfo, controller: controller.visibleViewController!)
            }
        }
    }
    
    func setHaptikTheme() {
        
        // NOTE: Haptik only gives instances of viewControllers. When you push them on your stack, the navigationBar is still the yours, hence it's appearance too.
        
        // The following there configuration is the default configuration. If you don't provide one then the SDK will try to adopt the following.
        
        Haptik.sharedSDK().themeConfig = HPThemeService.build { (builder) in
            
            builder?.brandColor = UIColor(hexString: "#2196f3")
            builder?.businessChatBackground = UIColor(hexString: "#f0f0f0")
            builder?.businessChatText = UIColor(hexString: "#333333")
            builder?.messageTimeStamp = UIColor(hexString: "#777777")
            
            // Providing Fonts are Madatory else the SDK will Assert
            
            builder?.lightFont = "SFUIText-Light"
            builder?.regularFont = "SFUIText-Regular"
            builder?.mediumFont = "SFUIText-Medium"
            builder?.boldFont = "SFUIText-Bold"
            builder?.semiBoldFont = "SFUIText-Semibold"
            builder?.italicFont = "SFUIText-Italic"
        }
    }
}


// MARK: - HPAnalytics Service Delegates

extension AppDelegate: HPAnalyticsServiceDelegate {
    
    func eventTracked(_ eventName: String, forParams params: [AnyHashable : Any]?) {
     
        // Get all the events tracked here
    }
    
    func errorTracked(_ errorMessage: String, forError error: Error?) {
     
        // Get all the errors tracked here
    }
}

