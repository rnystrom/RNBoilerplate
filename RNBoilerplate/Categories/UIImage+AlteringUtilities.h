//
//  UIImage+CropToRect.h
//  Crateless
//
//  Created by Ryan Nystrom on 8/8/12.
//  Copyright (c) 2012 Ryan Nystrom. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIImage (AlteringUtilities)

- (UIImage *)crop:(CGRect)rect;
- (UIImage *)resize:(CGSize)size;

@end
