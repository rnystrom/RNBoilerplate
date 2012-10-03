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

#import <UIKit/UIKit.h>
#import "PF_FBGraphObject.h"

@protocol PF_FBGraphObjectViewControllerDelegate;
@protocol PF_FBGraphObjectSelectionQueryDelegate;
@protocol PF_FBGraphObjectDataSourceDataNeededDelegate;
@class PF_FBGraphObjectTableCell;

@interface PF_FBGraphObjectTableDataSource : NSObject<UITableViewDataSource>

@property (nonatomic, retain) UIImage *defaultPicture;
@property (nonatomic, assign) id<PF_FBGraphObjectViewControllerDelegate> controllerDelegate;
@property (nonatomic, copy) NSString *groupByField;
@property (nonatomic) BOOL itemTitleSuffixEnabled;
@property (nonatomic) BOOL itemPicturesEnabled;
@property (nonatomic) BOOL itemSubtitleEnabled;
@property (nonatomic, assign) id<PF_FBGraphObjectSelectionQueryDelegate> selectionDelegate;
@property (nonatomic, assign) id<PF_FBGraphObjectDataSourceDataNeededDelegate> dataNeededDelegate;
@property (nonatomic, copy) NSArray *sortDescriptors;

- (NSString *)fieldsForRequestIncluding:(NSSet *)customFields, ...;

- (void)setSortingBySingleField:(NSString*)fieldName ascending:(BOOL)ascending;
- (void)setSortingByFields:(NSArray*)fieldNames ascending:(BOOL)ascending;

- (void)prepareForNewRequest;
// Clears all graph objects from the data source.
- (void)clearGraphObjects;
// Adds additional graph objects (pass nil to indicate all objects have been added).
- (void)appendGraphObjects:(NSArray *)data;
- (BOOL)hasGraphObjects;

- (void)bindTableView:(UITableView *)tableView;

- (void)cancelPendingRequests;

// Call this when updating any property or if
// delegate.filterIncludesItem would return a different answer now.
- (void)update;

// Returns the graph object at a given indexPath.
- (PF_FBGraphObject *)itemAtIndexPath:(NSIndexPath *)indexPath;

// Returns the indexPath for a given graph object.
- (NSIndexPath *)indexPathForItem:(PF_FBGraphObject *)item;

@end

@protocol PF_FBGraphObjectViewControllerDelegate <NSObject>
@required

- (NSString *)graphObjectTableDataSource:(PF_FBGraphObjectTableDataSource *)dataSource
                             titleOfItem:(id<PF_FBGraphObject>)graphObject;

@optional

- (NSString *)graphObjectTableDataSource:(PF_FBGraphObjectTableDataSource *)dataSource
                       titleSuffixOfItem:(id<PF_FBGraphObject>)graphObject;

- (NSString *)graphObjectTableDataSource:(PF_FBGraphObjectTableDataSource *)dataSource
                          subtitleOfItem:(id<PF_FBGraphObject>)graphObject;

- (NSString *)graphObjectTableDataSource:(PF_FBGraphObjectTableDataSource *)dataSource
                        pictureUrlOfItem:(id<PF_FBGraphObject>)graphObject;

- (BOOL)graphObjectTableDataSource:(PF_FBGraphObjectTableDataSource *)dataSource
                filterIncludesItem:(id<PF_FBGraphObject>)item;

- (void)graphObjectTableDataSource:(PF_FBGraphObjectTableDataSource*)dataSource
                customizeTableCell:(PF_FBGraphObjectTableCell*)cell;
                
@end

@protocol PF_FBGraphObjectSelectionQueryDelegate <NSObject>

- (BOOL)graphObjectTableDataSource:(PF_FBGraphObjectTableDataSource *)dataSource
             selectionIncludesItem:(id<PF_FBGraphObject>)item;

@end

@protocol PF_FBGraphObjectDataSourceDataNeededDelegate <NSObject>

- (void)graphObjectTableDataSourceNeedsData:(PF_FBGraphObjectTableDataSource *)dataSource triggeredByIndexPath:(NSIndexPath*)indexPath;

@end
