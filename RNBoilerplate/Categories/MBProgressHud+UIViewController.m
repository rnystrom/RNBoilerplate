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