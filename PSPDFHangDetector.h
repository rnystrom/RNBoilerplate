// Smart little helper to find main thread hangs. Enable in appDidFinishLaunching.
// Only available with source code in DEBUG mode.
@interface PSPDFHangDetector : NSObject
+ (void)startHangDetector;
@end


@implementation PSPDFHangDetector
+ (void)startHangDetector {
#ifdef DEBUG
    NSThread *hangDetectionThread = [[NSThread alloc] initWithTarget:self selector:@selector(deadThreadMain) object:nil];
    [hangDetectionThread start];
#endif
}

#ifdef DEBUG
static volatile NSInteger DEAD_SIGNAL = 0;
+ (void)deadThreadTick {
    if (DEAD_SIGNAL == 1) {
        NSLog(@"Main Thread doesn't answer...");
    }
    DEAD_SIGNAL = 1;
    dispatch_async(dispatch_get_main_queue(), ^{DEAD_SIGNAL = 0;});
}

+ (void)deadThreadMain {
    [NSThread currentThread].name = @"PSPDFHangDetection";
    @autoreleasepool {
        [NSTimer scheduledTimerWithTimeInterval:0.5 target:self selector:@selector(deadThreadTick) userInfo:nil repeats:YES];
        [[NSRunLoop currentRunLoop] runUntilDate:[NSDate distantFuture]];
    }
}
#endif

@end