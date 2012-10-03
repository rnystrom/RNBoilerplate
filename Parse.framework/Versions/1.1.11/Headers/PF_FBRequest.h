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
#import <CoreLocation/CoreLocation.h>
#import "PF_FBRequestConnection.h"
#import "PF_FBGraphObject.h"

/*! The base URL used for graph requests */
extern NSString* const PF_FBGraphBasePath;

// up-front decl's
@protocol PF_FBRequestDelegate;
@class PF_FBSession;
@class UIImage;

/*!
 @typedef PF_FBRequestState

 @abstract
 Deprecated - do not use in new code.

 @discussion
 PF_FBRequestState is retained from earlier versions of the SDK to give existing
 apps time to remove dependency on this.

 @deprecated
*/
typedef NSUInteger PF_FBRequestState __attribute__((deprecated));

/*!
 @class PF_FBRequest

 @abstract
 The `PF_FBRequest` object is used to setup and manage requests to Facebook Graph
 and REST APIs. This class provides helper methods that simplify the connection
 and response handling.

 @discussion
 An <PF_FBSession> object is required for all authenticated uses of `PF_FBRequest`.
 Requests that do not require an unauthenticated user are also supported and
 do not require an <PF_FBSession> object to be passed in.

 An instance of `PF_FBRequest` represents the arguments and setup for a connection
 to Facebook. After creating an `PF_FBRequest` object it can be used to setup a
 connection to Facebook through the <PF_FBRequestConnection> object. The
 <PF_FBRequestConnection> object is created to manage a single connection. To
 cancel a connection use the instance method in the <PF_FBRequestConnection> class.

 An `PF_FBRequest` object may be reused to issue multiple connections to Facebook.
 However each <PF_FBRequestConnection> instance will manage one connection.

 Class and instance methods prefixed with **start* ** can be used to perform the
 request setup and initiate the connection in a single call.

*/
@interface PF_FBRequest : NSObject {
@private
    id<PF_FBRequestDelegate> _delegate;
    NSString*             _url;
    NSURLConnection*      _connection;
    NSMutableData*        _responseText;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    PF_FBRequestState        _state;
#pragma GCC diagnostic pop
    NSError*              _error;
    BOOL                  _sessionDidExpire;
    id<PF_FBGraphObject>     _graphObject;
}

/*!
 @methodgroup Creating a request

 @method
 Calls <initWithSession:graphPath:parameters:HTTPMethod:> with the default parameters.
*/
- (id)init;

/*!
 @method
 Calls <initWithSession:graphPath:parameters:HTTPMethod:> with default parameters
 except for the ones provided to this method.

 @param session     The session object representing the identity of the Facebook user making
 the request. A nil value indicates a request that requires no token; to
 use the active session pass `[PF_FBSession activeSession]`.

 @param graphPath   The Graph API endpoint to use for the request, for example "me".
*/
- (id)initWithSession:(PF_FBSession*)session
            graphPath:(NSString *)graphPath;

/*!
 @method

 @abstract
 Initializes an `PF_FBRequest` object for a Graph API request call.

 @discussion
 Note that this only sets properties on the `PF_FBRequest` object.

 To send the request, initialize an <PF_FBRequestConnection> object, add this request,
 and send <[PF_FBRequestConnection start]>.  See other methods on this
 class for shortcuts to simplify this process.

 @param session          The session object representing the identity of the Facebook user making
 the request. A nil value indicates a request that requires no token; to
 use the active session pass `[PF_FBSession activeSession]`.

 @param graphPath        The Graph API endpoint to use for the request, for example "me".

 @param parameters       The parameters for the request. A value of nil sends only the automatically handled
 parameters, for example, the access token. The default is nil.

 @param HTTPMethod       The HTTP method to use for the request. The default is value of nil implies a GET.
*/
- (id)initWithSession:(PF_FBSession*)session
            graphPath:(NSString *)graphPath
           parameters:(NSDictionary *)parameters
           HTTPMethod:(NSString *)HTTPMethod;

/*!
 @method
 @abstract
 Initialize a `PF_FBRequest` object that will do a graph request.

 @discussion
 Note that this only sets properties on the `PF_FBRequest`.

 To send the request, initialize a <PF_FBRequestConnection>, add this request,
 and send <[PF_FBRequestConnection start]>.  See other methods on this
 class for shortcuts to simplify this process.

 @param session          The session object representing the identity of the Facebook user making
 the request. A nil value indicates a request that requires no token; to
 use the active session pass `[PF_FBSession activeSession]`.

 @param graphPath        The Graph API endpoint to use for the request, for example "me".

 @param graphObject      An object or open graph action to post.
*/
- (id)initForPostWithSession:(PF_FBSession*)session
                   graphPath:(NSString *)graphPath
                 graphObject:(id<PF_FBGraphObject>)graphObject;

/*!
 @method
 @abstract
 Initialize a `PF_FBRequest` object that will do a rest API request.

 @discussion
 Prefer to use graph requests instead of this where possible.

 Note that this only sets properties on the `PF_FBRequest`.

 To send the request, initialize a <PF_FBRequestConnection>, add this request,
 and send <[PF_FBRequestConnection start]>.  See other methods on this
 class for shortcuts to simplify this process.

 @param session          The session object representing the identity of the Facebook user making
 the request. A nil value indicates a request that requires no token; to
 use the active session pass `[PF_FBSession activeSession]`.

 @param restMethod        A valid REST API method.

 @param parameters       The parameters for the request. A value of nil sends only the automatically handled
 parameters, for example, the access token. The default is nil.

 @param HTTPMethod       The HTTP method to use for the request. The default is value of nil implies a GET.

*/
- (id)initWithSession:(PF_FBSession*)session
           restMethod:(NSString *)restMethod
           parameters:(NSDictionary *)parameters
           HTTPMethod:(NSString *)HTTPMethod;

/*!
 @abstract
 The parameters for the request.

 @discussion
 May be used to read the parameters that were automatically set during
 the object initiliazation. Make any required modifications prior to
 sending the request.

 `NSString` parameters are used to generate URL parameter values or JSON
 parameters.  `NSData` and `UIImage` parameters are added as attachments
 to the HTTP body and referenced by name in the URL and/or JSON.
*/
@property(nonatomic, retain, readonly) NSMutableDictionary *parameters;

/*!
 @abstract
 The <PF_FBSession> session object to use for the request.

 @discussion
 May be used to read the session that was automatically set during
 the object initiliazation. Make any required modifications prior to
 sending the request.
*/
@property(nonatomic, retain) PF_FBSession *session;

/*!
 @abstract
 The Graph API endpoint to use for the request, for example "me".

 @discussion
 May be used to read the Graph API endpoint that was automatically set during
 the object initiliazation. Make any required modifications prior to
 sending the request.
*/
@property(nonatomic, copy) NSString *graphPath;

/*!
 @abstract
 A valid REST API method.

 @discussion
 May be used to read the REST method that was automatically set during
 the object initiliazation. Make any required modifications prior to
 sending the request.

 Use the Graph API equivalent of the API if it exists as the REST API
 method is deprecated if there is a Graph API equivalent.
*/
@property(nonatomic, copy) NSString *restMethod;

/*!
 @abstract
 The HTTPMethod to use for the request, for example "GET" or "POST".

 @discussion
 May be used to read the HTTP method that was automatically set during
 the object initiliazation. Make any required modifications prior to
 sending the request.
*/
@property(nonatomic, copy) NSString *HTTPMethod;

/*!
 @abstract
 The graph object to post with the request.

 @discussion
 May be used to read the graph object that was automatically set during
 the object initiliazation. Make any required modifications prior to
 sending the request.
*/
@property(nonatomic, retain) id<PF_FBGraphObject> graphObject;

/*!
 @methodgroup Instance methods
*/

/*!
 @method

 @abstract
 Starts a connection to the Facebook API.

 @discussion
 This is used to start an API call to Facebook and call the block when the
 request completes with a success, error, or cancel.

 @param handler   The handler block to call when the request completes with a success, error, or cancel action.
*/
- (PF_FBRequestConnection*)startWithCompletionHandler:(PF_FBRequestHandler)handler;

/*!
 @methodgroup PF_FBRequestConnection start methods

 @abstract
 These methods start an <PF_FBRequestConnection>.

 @discussion
 These methods simplify the process of preparing a request and starting
 the connection.  The methods handle initializing an `PF_FBRequest` object,
 initializing a <PF_FBRequestConnection> object, adding the `PF_FBRequest`
 object to the to the <PF_FBRequestConnection>, and finally starting the
 connection.
*/

/*!
 @methodgroup PF_FBRequest factory methods

 @abstract
 These methods initialize a `PF_FBRequest` for common scenarios.

 @discussion
 These simplify the process of preparing a request to send.  These
 initialize a `PF_FBRequest` based on strongly typed parameters that are
 specific to the scenario.

 These method do not initialize an <PF_FBRequestConnection> object. To initiate the API
 call first instantiate an <PF_FBRequestConnection> object, add the request to this object,
 then call the `start` method on the connection instance.
*/

// request*
//
// Summary:
// Helper methods used to create common request objects which can be used to create single or batch connections
//
//   session:              - the session object representing the identity of the
//                         Facebook user making the request; nil implies an
//                         unauthenticated request; default=nil

/*!
 @method

 @abstract
 Creates a request representing a Graph API call to the "me" endpoint, using the active session.

 @discussion
 Simplifies preparing a request to retrieve the user's identity.

 This method does not initialize an <PF_FBRequestConnection> object. To initiate the API
 call first instantiate an <PF_FBRequestConnection> object, add the request to this object,
 then call the `start` method on the connection instance.

 A successful Graph API call will return an <PF_FBGraphUser> object representing the
 user's identity.

 Note you may change the session property after construction if a session other than
 the active session is preferred.
*/
+ (PF_FBRequest*)requestForMe;

/*!
 @method

 @abstract
 Creates a request representing a Graph API call to the "me/friends" endpoint using the active session.

 @discussion
 Simplifies preparing a request to retrieve the user's friends.

 This method does not initialize an <PF_FBRequestConnection> object. To initiate the API
 call first instantiate an <PF_FBRequestConnection> object, add the request to this object,
 then call the `start` method on the connection instance.

 A successful Graph API call will return an array of <PF_FBGraphUser> objects representing the
 user's friends.
*/
+ (PF_FBRequest*)requestForMyFriends;

/*!
 @method

 @abstract
 Creates a request representing a Graph API call to upload a photo to the app's album using the active session.

 @discussion
 Simplifies preparing a request to post a photo.

 To post a photo to a specific album, get the `PF_FBRequest` returned from this method
 call, then modify the request parameters by adding the album ID to an "album" key.

 This method does not initialize an <PF_FBRequestConnection> object. To initiate the API
 call first instantiate an <PF_FBRequestConnection> object, add the request to this object,
 then call the `start` method on the connection instance.

 @param photo            A `UIImage` for the photo to upload.
*/
+ (PF_FBRequest*)requestForUploadPhoto:(UIImage *)photo;

/*!
 @method
 
 @abstract
 Creates a request representing a status update.
 
 @discussion
 Simplifies preparing a request to post a status update.
 
 This method does not initialize an <PF_FBRequestConnection> object. To initiate the API
 call first instantiate an <PF_FBRequestConnection> object, add the request to this object,
 then call the `start` method on the connection instance.
 
 @param message         The message to post.
 */
+ (PF_FBRequest *)requestForPostStatusUpdate:(NSString *)message;

/*!
 @method
 
 @abstract
 Creates a request representing a status update.
 
 @discussion
 Simplifies preparing a request to post a status update.
 
 This method does not initialize an <PF_FBRequestConnection> object. To initiate the API
 call first instantiate an <PF_FBRequestConnection> object, add the request to this object,
 then call the `start` method on the connection instance.
 
 @param message         The message to post.
 @param place           The place to checkin with, or nil. Place may be an fbid or a 
 graph object representing a place.
 @param tags            Array of friends to tag in the status update, each element 
 may be an fbid or a graph object representing a user.
 */
+ (PF_FBRequest *)requestForPostStatusUpdate:(NSString *)message
                                    place:(id)place
                                     tags:(id<NSFastEnumeration>)tags;

/*!
 @method

 @abstract
 Creates a request representing a Graph API call to the "search" endpoint
 for a given location using the active session.

 @discussion
 Simplifies preparing a request to search for places near a coordinate.

 This method does not initialize an <PF_FBRequestConnection> object. To initiate the API
 call first instantiate an <PF_FBRequestConnection> object, add the request to this object,
 then call the `start` method on the connection instance.

 A successful Graph API call will return an array of <PF_FBGraphPlace> objects representing
 the nearby locations.

 @param coordinate       The search coordinates.

 @param radius           The search radius in meters.

 @param limit            The maxiumum number of results to return.  It is
 possible to receive fewer than this because of the radius and because of server limits.

 @param searchText       The text to use in the query to narrow the set of places
 returned.
*/
+ (PF_FBRequest*)requestForPlacesSearchAtCoordinate:(CLLocationCoordinate2D)coordinate
                                  radiusInMeters:(NSInteger)radius
                                    resultsLimit:(NSInteger)limit
                                      searchText:(NSString*)searchText;

/*!
 @method
 
 @abstract
 Returns a newly initialized request object that can be used to make a Graph API call for the active session.
 
 @discussion
 This method simplifies the preparation of a Graph API call.
 
 This method does not initialize an <PF_FBRequestConnection> object. To initiate the API
 call first instantiate an <PF_FBRequestConnection> object, add the request to this object,
 then call the `start` method on the connection instance.
 
 @param graphPath        The Graph API endpoint to use for the request, for example "me".
 */
+ (PF_FBRequest*)requestForGraphPath:(NSString*)graphPath;

/*!
 @method
 
 @abstract
 Creates a request representing a POST for a graph object.
 
 @param graphPath        The Graph API endpoint to use for the request, for example "me".
 
 @param graphObject      An object or open graph action to post.
 */
+ (PF_FBRequest*)requestForPostWithGraphPath:(NSString*)graphPath
                              graphObject:(id<PF_FBGraphObject>)graphObject;

/*!
 @method
 
 @abstract
 Returns a newly initialized request object that can be used to make a Graph API call for the active session.
 
 @discussion
 This method simplifies the preparation of a Graph API call.
 
 This method does not initialize an <PF_FBRequestConnection> object. To initiate the API
 call first instantiate an <PF_FBRequestConnection> object, add the request to this object,
 then call the `start` method on the connection instance.
 
 @param graphPath        The Graph API endpoint to use for the request, for example "me".
 
 @param parameters       The parameters for the request. A value of nil sends only the automatically handled parameters, for example, the access token. The default is nil.
 
 @param HTTPMethod       The HTTP method to use for the request. A nil value implies a GET.
 */
+ (PF_FBRequest*)requestWithGraphPath:(NSString*)graphPath
                        parameters:(NSDictionary*)parameters
                        HTTPMethod:(NSString*)HTTPMethod;
@end
