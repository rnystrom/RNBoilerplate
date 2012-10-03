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
#import "PF_FBGraphObjectTableDataSource.h"

@class PF_FBSession;
@class PF_FBRequest;
@protocol PF_FBGraphObjectPagingLoaderDelegate;

typedef enum {
    // Paging links will be followed as soon as one set of results is loaded
    PF_FBGraphObjectPagingModeImmediate,
    // Paging links will be followed as soon as one set of results is loaded, even without a view
    PF_FBGraphObjectPagingModeImmediateViewless,
    // Paging links will be followed only when the user scrolls to the bottom of the table
    PF_FBGraphObjectPagingModeAsNeeded
} PF_FBGraphObjectPagingMode;

@interface PF_FBGraphObjectPagingLoader : NSObject<PF_FBGraphObjectDataSourceDataNeededDelegate>

@property (nonatomic, retain) UITableView *tableView;
@property (nonatomic, retain) PF_FBGraphObjectTableDataSource *dataSource;
@property (nonatomic, retain) PF_FBSession *session;
@property (nonatomic, assign) id<PF_FBGraphObjectPagingLoaderDelegate> delegate;
@property (nonatomic, readonly) PF_FBGraphObjectPagingMode pagingMode;
@property (nonatomic, readonly) BOOL isResultFromCache;
 
- (id)initWithDataSource:(PF_FBGraphObjectTableDataSource*)aDataSource
              pagingMode:(PF_FBGraphObjectPagingMode)pagingMode;
- (void)startLoadingWithRequest:(PF_FBRequest*)request
                  cacheIdentity:(NSString*)cacheIdentity 
          skipRoundtripIfCached:(BOOL)skipRoundtripIfCached;
- (void)addResultsAndUpdateView:(NSDictionary*)results;
- (void)cancel;
- (void)reset;

@end

@protocol PF_FBGraphObjectPagingLoaderDelegate <NSObject>

@optional

- (void)pagingLoader:(PF_FBGraphObjectPagingLoader*)pagingLoader willLoadURL:(NSString*)url;
- (void)pagingLoader:(PF_FBGraphObjectPagingLoader*)pagingLoader didLoadData:(NSDictionary*)results;
- (void)pagingLoaderDidFinishLoading:(PF_FBGraphObjectPagingLoader*)pagingLoader;
- (void)pagingLoader:(PF_FBGraphObjectPagingLoader*)pagingLoader handleError:(NSError*)error;
- (void)pagingLoaderWasCancelled:(PF_FBGraphObjectPagingLoader*)pagingLoader;

@end
