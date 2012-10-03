RNBoilerplate
======

RNBoilerplate is my solution to reusing structure, categories, configs, and third-party libraries/frameworks. It should be pretty straight forward on how to use. I'll explain what all is included and why.

## Setup

Slowly double-click on the project name to rename your working project.

<div style="text-align:center"><img src="https://github.com/rnystrom/RNBoilerplate/blob/public/images/rename.png?raw=true" /></div>

Click on your scheme and click Manage Schemes. Add a new scheme using your newly named project and remove the old one.

<div style="text-align:center"><img src="https://github.com/rnystrom/RNBoilerplate/blob/public/images/scheme.png?raw=true" /></div>

If the physical folder structure bothers you, take a look at [this SO question](http://stackoverflow.com/questions/8262613/renaming-xcode-4-project-and-the-actual-folder) for instructions on how to change it. Make sure you rename your unit test files if you do this or else you will run into headaches.

## Frameworks

### Parse

I use [ Parse ](https://parse.com) as often as I can, though sometimes client requests remove them as an option. If I'm ever able to make the call on who/how we are doing networking, its Parse. Checkout [ their site ](https://parse.com), get an API key, and get rolling. I've included SDK version 1.1.11. I can't update via git or anything, its manual through their service. However, this version should be good for a while. I'll keep this project updated with major releases.

### Testflight

[ Testflight ](https://testflightapp.com/dashboard/) is a god-send. It makes beta-testing and distributing so effortless and simple. Just like Parse, the SDK is manual-update only. Included in this bundle is version 1.1 (they have a v1.2 beta available). Grab an API key to get rolling with them in this project as well.

### Flurry

I haven't used [Flurry](http://www.flurry.com) as much as I should, but recently iTunesConnect has been either too slow to update or doesn't contain enough information. Plus, who doesn't like analytics? This is another SDK + API key required project. The current SDK is version 3.1.2. 

*Quick note. The libraries mentioned thus far require API keys. I have setup <code>#error</code> flags in my config file to let you know to either get an API key or comment that portion out. If an API key is not provided, the library is not loaded.*

## Submodules

### [CocoaLumberjack](https://github.com/robbiehanson/CocoaLumberjack)

I've only experimented with this project a little bit, but I LOVE what I've seen. Logging is fast, has loads of options, and even let's you [use colors](https://github.com/robbiehanson/CocoaLumberjack/wiki/XcodeColors) in log statements! Pretty nifty.

### [AFNetworking](https://github.com/AFNetworking/AFNetworking)

I never leave home without this project. You're a good man [@mattt](https://github.com/mattt). If you've never used, or heard of this project, give it a whirl. It basically makes HTTP requests, downloading/uploading, and streaming a breeze. It's well built, well maintained, and fails graciously.

### [MBProgressHUD](https://github.com/jdg/MBProgressHUD)

This is likely one of the most popular progress HUD projects out there. I use it in any project that uses network requests. Remember not to use it too much as it's a UX interupter, but when you need to cover up a view until a task is finished, its awesome.

### [SkyLab](https://github.com/mattt/SkyLab)

Another great project from [@mattt](https://github.com/mattt). Paired with Testflight you can do some great A/B user testing remotely. This is a fairly new project but extremely useful. Its incredibly easy to use and provides great feedback.

### [specta](https://github.com/petejkim/specta)

I've included the files for this tool, but not included it in the actual project as it can be included via [CocoaPods](https://github.com/CocoaPods/CocoaPods). However, if you need to install it manually the resources are there. Check out [the docs](https://github.com/petejkim/specta) for instructions. Unit tests are included by default and this extends the utility of doing those tests.

## Categories

I added a few useful categories that have helped me out tremendously. It's likely that I'll add more and more categories as I discover them. I recommend you think about what you need in your project when including categories. Just dropping in and importing hundres is not really a useful thing to do as you will become prone to difficult debugging challenges. I have a master category import file <code>RNCategories.h</code> that is included in the prefix-header. Here you can decide what should be included in the project. You can also add your own categories the same way.

### UIView+Sizes

Credit goes to [@steipete](https://github.com/steipete).

``` objective-c
@interface UIView (Sizes)

@property (nonatomic) CGFloat left;
@property (nonatomic) CGFloat top;
@property (nonatomic) CGFloat right;
@property (nonatomic) CGFloat bottom;
@property (nonatomic) CGFloat width;
@property (nonatomic) CGFloat height;

@property (nonatomic) CGPoint origin;
@property (nonatomic) CGSize size;

@end
```

### CALayer+Sizes

Again credit goes to [@steipete](https://github.com/steipete) as I just copied UIView+Sizes for this.

``` objective-c
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
```

### MBProgressHud+UIViewController

``` objective-c
@interface UIView (UIViewWithMBProgressHUD)

- (void)hideHUD;

@end

@interface UIViewController (UIViewControllerWithMBProgressHUD)
<MBProgressHUDDelegate>

- (void)showHUD;
- (void)showHUDWithText:(NSString*)text;
- (void)hideHUD;
- (BOOL)isHUDHidden;
- (void)show:(MBProgressHUD*)hud;

@end
```

### UIImage+AlteringUtilities

``` objective-c
@interface UIImage (AlteringUtilities)

- (UIImage *)crop:(CGRect)rect;
- (UIImage *)resize:(CGSize)size;

@end
```

## Contact

* [@nystrorm](https://twitter.com/nystrorm) on Twitter
* [@rnystrom](https://github.com/rnystrom) on Github
* <a href="mailTo:rnystrom@whoisryannystrom.com">rnystrom [at] whoisryannystrom [dot] com</a>

## License

Copyright (c) 2012 Ryan Nystrom (http://whoisryannystrom.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.