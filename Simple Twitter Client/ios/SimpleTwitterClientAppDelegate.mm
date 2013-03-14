/*
 *  NO2 Web and Mobile Applications, S.L CONFIDENTIAL
 *
 *  Strawberry SDK ( OpenGL + HTML + CSS  cross-platform framework )
 *  Copyright 2010-2012 NO2 Web and Mobile Applications, S.L. All rights reserved.
 *
 * 
 *  NOTICE:  All information contained herein is, and remains
 *  the property of NO2 Web and Mobile Applications, S.L and its suppliers,
 *  if any.  The intellectual and technical concepts contained
 *  herein are proprietary to NO2 Web and Mobile Applications, S.L
 *  and its suppliers, and are protected by trade secret or copyright law.
 *  Dissemination of this information or reproduction of this material
 *  is strictly forbidden unless prior written permission is obtained
 *  from NO2 Web and Mobile Applications, S.L.
 */ 

#import "SimpleTwitterClientAppDelegate.h"

@implementation SimpleTwitterClientAppDelegate

@synthesize window = _window;
@synthesize viewController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.viewController = getStrawberryViewController();
    [self.window setRootViewController:self.viewController];
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)dealloc
{
    self.viewController = nil;
    [_window release];
    [super dealloc];
}

@end
