/*
 * RNBoilerplate
 *
 * Created by Ryan Nystrom on 10/2/12.
 * Copyright (c) 2012 Ryan Nystrom. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#import "MBProgressHud+UIViewController.h"

@implementation UIView (UIViewWithMBProgressHUD)

- (void)hideHUD
{
    if ([self isKindOfClass:[MBProgressHUD class]]) {
        [(MBProgressHUD*)self show:NO];
        [self removeFromSuperview];
    }
    else if ([self.subviews count] > 0) {
        for (UIView *subview in self.subviews) {
            if ([subview isKindOfClass:[MBProgressHUD class]]) {
                [(MBProgressHUD*)subview show:NO];
                [subview removeFromSuperview];
                break;
            }
            else {
                [subview hideHUD];
            }
        }
    }
}

@end

@implementation UIViewController (UIViewControllerWithMBProgressHUD)

- (void)showHUD
{
    MBProgressHUD *_hud = [[MBProgressHUD alloc] initWithView:self.view];
    [self show:_hud];
}

- (void)showHUDWithText:(NSString*)text
{
    MBProgressHUD *_hud = [[MBProgressHUD alloc] initWithView:self.view];
    [_hud setLabelText:text];
    [self show:_hud];
}

- (void)hideHUD
{
    for (UIView *subview in self.view.subviews) {
        [subview hideHUD];
    }
}

- (BOOL)isHUDHidden
{
    for (UIView *subview in self.view.subviews) {
        if ([subview isKindOfClass:[MBProgressHUD class]]) {
            [(MBProgressHUD*)subview show:NO];
            continue;
            return ((MBProgressHUD*)subview).isHidden;
        }
    }
    return YES;
}

- (void)show:(MBProgressHUD*)hud
{
    [hud setDimBackground:YES];
    [hud setDelegate:self];
    [hud show:YES];
    [self.view addSubview:hud];
}

-(void)hudWasHidden:(MBProgressHUD*)hud
{
    [hud removeFromSuperview];
    hud = nil;
}

@end