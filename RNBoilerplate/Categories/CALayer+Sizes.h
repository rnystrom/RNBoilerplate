//
//  CALayer+Sizes.h
//  Weathermate
//
//  Created by Ryan Nystrom on 9/25/12.
//  Copyright (c) 2012 Ryan Nystrom. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

@interface CALayer (Sizes)

@property (nonatomic) CGFloat left;
@property (nonatomic) CGFloat top;
@property (nonatomic) CGFloat right;
@property (nonatomic) CGFloat bottom;
@property (nonatomic) CGFloat width;
@property (nonatomic) CGFloat height;

@property (nonatomic) CGPoint origin;
@property (nonatomic) CGSize size;

@end
