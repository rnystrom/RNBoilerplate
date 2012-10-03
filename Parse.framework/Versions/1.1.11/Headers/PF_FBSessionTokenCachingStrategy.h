/*
 * Copyright 2012 Facebook
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>

/*! 
 @class
 
 @abstract
 The `PF_FBSessionTokenCachingStrategy` class is responsible for persisting and retrieving cached data related to
 an <PF_FBSession> object, including the user's Facebook access token. 
 
 @discussion
 `PF_FBSessionTokenCachingStrategy` is designed to be instantiated directly or used as a base class. Usually default
 token caching behavior is sufficient, and you do not need to interface directly with `PF_FBSessionTokenCachingStrategy` objects.
 However, if you need to control where or how `PF_FBSession` information is cached, then you may take one of two approaches.
 
 The first and simplest approach is to instantiate an instance of `PF_FBSessionTokenCachingStrategy`, and then pass
 the instance to `PF_FBSession` class' `init` method. This enables your application to control the key name used in
 `NSUserDefaults` to store session information. You may consider this approach if you plan to cache session information
 for multiple users.
 
 The second and more advanced approached is to derive a custom class from `PF_FBSessionTokenCachingStrategy`, which will
 be responsible for caching behavior of your application. This approach is useful if you need to change where the 
 information is cached, for example if you prefer to use the filesystem or make a network connection to fetch and
 persist cached tokens.  Inheritors should override the cacheTokenInformation, fetchTokenInformation, and clearToken methods.
 Doing this enables your application to implement any token caching scheme, including no caching at all.
 
 Direct use of `PF_FBSessionTokenCachingStrategy`is an advanced technique. Most applications use <PF_FBSession> objects without
 passing an `PF_FBSessionTokenCachingStrategy`, which yields default caching to `NSUserDefaults`.
 */
@interface PF_FBSessionTokenCachingStrategy : NSObject

/*!
 @abstract Initializes and returns an instance
 */
- (id)init;

/*!
 @abstract 
 Initializes and returns an instance
 
 @param tokenInformationKeyName     Specifies a key name to use for cached token information in NSUserDefaults, nil
 indicates a default value of @"PF_FBAccessTokenInformationKey"
 */
- (id)initWithUserDefaultTokenInformationKeyName:(NSString*)tokenInformationKeyName;

/*!
 @abstract 
 Called by <PF_FBSession> (and overridden by inheritors), in order to cache token information.
 
 @param tokenInformation            Dictionary containing token information to be cached by the method
 */
- (void)cacheTokenInformation:(NSDictionary*)tokenInformation;

/*!
 @abstract 
 Called by <PF_FBSession> (and overridden by inheritors), in order to fetch cached token information
 
 @discussion
 An overriding implementation should only return a token if it
 can also return an expiration date, otherwise return nil
 */
- (NSDictionary*)fetchTokenInformation;

/*!
 @abstract 
 Called by <PF_FBSession> (and overridden by inheritors), in order delete any cached information for the current token
 */
- (void)clearToken;

/*!
 @abstract 
 Helper function called by the SDK as well as apps, in order to fetch the default strategy instance.
 */
+ (PF_FBSessionTokenCachingStrategy*)defaultInstance;

/*!
 @abstract 
 Helper function called by the SDK as well as application code, used to determine whether a given dictionary
 contains the minimum token information usable by the <PF_FBSession>.
 
 @param tokenInformation            Dictionary containing token information to be validated
 */
+ (BOOL)isValidTokenInformation:(NSDictionary*)tokenInformation;

@end

// The key to use with token information dictionaries to get and set the token value
extern NSString *const PF_FBTokenInformationTokenKey;

// The to use with token information dictionaries to get and set the expiration date
extern NSString *const PF_FBTokenInformationExpirationDateKey;

// The to use with token information dictionaries to get and set the refresh date
extern NSString *const PF_FBTokenInformationRefreshDateKey;

// The key to use with token information dictionaries to get the related user's fbid
extern NSString *const PF_FBTokenInformationUserFBIDKey;

// The key to use with token information dictionaries to determine whether the token was fetched via Facebook Login
extern NSString *const PF_FBTokenInformationIsFacebookLoginKey;

// The key to use with token information dictionaries to determine whether the token was fetched via the OS
extern NSString *const PF_FBTokenInformationLoginTypeLoginKey;

// The key to use with token information dictionaries to get the latest known permissions
extern NSString *const PF_FBTokenInformationPermissionsKey;