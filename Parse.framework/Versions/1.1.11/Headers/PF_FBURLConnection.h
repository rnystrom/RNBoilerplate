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

#include <Foundation/Foundation.h>

@class PF_FBURLConnection;
typedef void (^PF_FBURLConnectionHandler)(PF_FBURLConnection *connection,
                                       NSError *error,
                                       NSURLResponse *response,
                                       NSData *responseData);

@interface PF_FBURLConnection : NSObject

- (PF_FBURLConnection *)initWithURL:(NSURL *)url
               completionHandler:(PF_FBURLConnectionHandler)handler;

- (PF_FBURLConnection *)initWithRequest:(NSURLRequest *)request
               skipRoundTripIfCached:(BOOL)skipRoundtripIfCached
                   completionHandler:(PF_FBURLConnectionHandler)handler;

- (void)cancel;

@end
