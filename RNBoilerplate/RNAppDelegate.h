//
//  RNAppDelegate.h
//  RNBoilerplate
//
//  Created by Ryan Nystrom on 10/2/12.
//  Copyright (c) 2012 Ryan Nystrom. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RNAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (readonly, strong, nonatomic) NSManagedObjectContext *managedObjectContext;
@property (readonly, strong, nonatomic) NSManagedObjectModel *managedObjectModel;
@property (readonly, strong, nonatomic) NSPersistentStoreCoordinator *persistentStoreCoordinator;

- (void)saveContext;
- (NSURL *)applicationDocumentsDirectory;

@end
