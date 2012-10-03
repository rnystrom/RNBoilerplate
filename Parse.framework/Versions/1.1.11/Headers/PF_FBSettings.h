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

/*
 * Constants defining logging behavior.  Use with <[PF_FBSettings setLoggingBehavior]>.
 */

/*! Log requests from PF_FBRequest* classes */
extern NSString *const PF_FBLoggingBehaviorFBRequests;

/*! Log requests from PF_FBURLConnection* classes */
extern NSString *const PF_FBLoggingBehaviorFBURLConnections;

/*! Include access token in logging. */
extern NSString *const PF_FBLoggingBehaviorAccessTokens;

/*! Log session state transitions. */
extern NSString *const PF_FBLoggingBehaviorSessionStateTransitions;

/*! Log performance characteristics */
extern NSString *const PF_FBLoggingBehaviorPerformanceCharacteristics;

@interface PF_FBSettings : NSObject

/*!
 @method
 
 @abstract Retrieve the current Facebook SDK logging behavior.
 
 */
+ (NSSet *)loggingBehavior;

/*!
 @method

 @abstract Set the current Facebook SDK logging behavior.  This should consist of strings defined as
 constants with PF_FBLogBehavior*, and can be constructed with [NSSet initWithObjects:].

 @param loggingBehavior A set of strings indicating what information should be logged.
 */
+ (void)setLoggingBehavior:(NSSet *)loggingBehavior;

/*! @abstract Retreive the current auto publish behavior.  Defaults to YES. */
+ (BOOL)shouldAutoPublishInstall;

/*!
 @method

 @abstract Sets whether the SDK will automatically publish an install to Facebook during first PF_FBSession init
 or on first network request to Facebook.

 @param autoPublishInstall      If YES, automatically publish the install; if NO, do not.
 */
+ (void)setShouldAutoPublishInstall:(BOOL)autoPublishInstall;

// For best results, call this function during app activation.
/*!
 @method

 @abstract Manually publish an attributed install to the facebook graph.  Use this method if you have disabled
 auto publish and wish to manually send an install from your code.  This method acquires the current attribution
 id from the facebook application, queries the graph API to determine if the application has install
 attribution enabled, publishes the id, and records success to avoid reporting more than once.

 @param appID A specific appID to publish an install for.  If nil, uses [PF_FBSession defaultAppID].
 */
+ (void) publishInstall:(NSString *)appID;

@end
