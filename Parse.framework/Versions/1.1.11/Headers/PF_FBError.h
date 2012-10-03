/*
 * Copyright 2012 Facebook
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <Foundation/Foundation.h>

/// The error domain of all error codes returned by the Facebook SDK
extern NSString *const PF_FacebookSDKDomain;

// ----------------------------------------------------------------------------
// Keys in the userInfo NSDictionary of NSError where you can find additional
// information about the error.  All are optional.

/// The key for an inner NSError.
extern NSString *const PF_FBErrorInnerErrorKey;

/// The key for parsed JSON response from the server. In case of a batch, 
/// includes the JSON for a single PF_FBRequest.
extern NSString *const PF_FBErrorParsedJSONResponseKey;

/// The key for HTTP status code.
extern NSString *const PF_FBErrorHTTPStatusCodeKey;

// ----------------------------------------------------------------------------
/*!
 @abstract Error codes returned by the Facebook SDK in NSError.  
 
 @discussion
 These are valid only in the scope of FacebookSDKDomain.
 */
typedef enum PF_FBErrorCode {
    /*! 
     Like nil for PF_FBErrorCode values, represents an error code that
     has not been initialized yet.
     */
    PF_FBErrorInvalid = 0,

    /// The operation failed because it was cancelled.
    PF_FBErrorOperationCancelled,
    
    /// A login attempt failed
    PF_FBErrorLoginFailedOrCancelled,

    /// The graph API returned an error for this operation.
    PF_FBErrorRequestConnectionApi,

    /*!
     The operation failed because the server returned an unexpected
     response.  You can get this error if you are not using the most
     recent SDK, or if you set your application's migration settings
     incorrectly for the version of the SDK you are using.
    
     If this occurs on the current SDK with proper app migration
     settings, you may need to try changing to one request per batch.
     */
    PF_FBErrorProtocolMismatch,

    /// Non-success HTTP status code was returned from the operation.
    PF_FBErrorHTTPError,
    
    /// An endpoint that returns a binary response was used with PF_FBRequestConnection;
    /// endpoints that return image/jpg, etc. should be accessed using NSURLRequest
    PF_FBErrorNonTextMimeTypeReturned,

    // An error occurred while trying to display a native dialog
    PF_FBErrorNativeDialog,
} PF_FBErrorCode;

/*!
 The key in the userInfo NSDictionary of NSError where you can find
 the inner NSError (if any).
 */
extern NSString *const PF_FBErrorInnerErrorKey;

/// The NSError key used by session to capture login failure reason
extern NSString *const PF_FBErrorLoginFailedReason;

/// the NSError key used by session to capture login failure error code
extern NSString *const PF_FBErrorLoginFailedOriginalErrorCode;

/// used by session when an inline dialog fails
extern NSString *const PF_FBErrorLoginFailedReasonInlineCancelledValue;
extern NSString *const PF_FBErrorLoginFailedReasonInlineNotCancelledValue;
extern NSString *const PF_FBErrorLoginFailedReasonUnitTestResponseUnrecognized;

/// used by session when a reauthorize fails
extern NSString *const PF_FBErrorReauthorizeFailedReasonSessionClosed;
extern NSString *const PF_FBErrorReauthorizeFailedReasonUserCancelled;
extern NSString *const PF_FBErrorReauthorizeFailedReasonWrongUser;

/// The key to retrieve the reason for a native dialog error
extern NSString *const PF_FBErrorNativeDialogReasonKey;

/// indicates that a native dialog is not supported in the current OS
extern NSString *const PF_FBErrorNativeDialogNotSupported;
/// indicates that a native dialog can't be displayed because it is not appropriate for the current session
extern NSString *const PF_FBErrorNativeDialogInvalidForSession;
/// indicates that a native dialog can't be displayed for some other reason
extern NSString *const PF_FBErrorNativeDialogCantBeDisplayed;

// Exception strings raised by the Facebook SDK

/*!
 This exception is raised by methods in the Facebook SDK to indicate
 that an attempted operation is invalid
 */
extern NSString *const PF_FBInvalidOperationException;

// Facebook SDK also raises exceptions the following common exceptions:
//  NSInvalidArgumentException

