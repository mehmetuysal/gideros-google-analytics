#include "ganalytics.h"
#import <Google/Analytics.h>

static NSDictionary *getDictionary(const char **parameters)
{
    if (parameters == NULL)
        return nil;
    
    NSMutableDictionary *parameters2 = [NSMutableDictionary dictionaryWithCapacity:5];
    while (true)
    {
        if (*parameters == NULL)
            break;
        NSString *key = [NSString stringWithUTF8String:*parameters++];
        
        if (*parameters == NULL)
            break;
        NSString *value = [NSString stringWithUTF8String:*parameters++];
        
        [parameters2 setObject:value forKey:key];
    }
    
    return parameters2;
}

void ganalytics_SendEvent(const char *eventCategory, const char *action, const char *label, int eventValue)
{
    NSString *eventCategory2 = [NSString stringWithUTF8String:eventCategory];
    NSString *action2 = [NSString stringWithUTF8String:action];
    NSString *label2 = [NSString stringWithUTF8String:label];
    NSNumber *eventValue2 = [NSNumber numberWithInt:eventValue];

    id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
    [tracker send:[[GAIDictionaryBuilder createEventWithCategory:eventCategory2
                                                          action:action2
                                                           label:label2
                                                           value:eventValue2] build]];
}

void ganalytics_StartAnalytics(const char *apiKey, const bool crash)
{
    // Configure tracker from GoogleService-Info.plist.
    NSError *configureError;
    [[GGLContext sharedInstance] configureWithError:&configureError];
    NSCAssert(!configureError, @"Error configuring Google services: %@", configureError);
    //    id<GAITracker> tracker = [[GAI sharedInstance] trackerWithTrackingId:@"UA-50097603-16"];
    
    
    // Optional: configure GAI options.
    GAI *gai = [GAI sharedInstance];
    gai.trackUncaughtExceptions = YES;  // report uncaught exceptions
    gai.logger.logLevel = kGAILogLevelVerbose;  // remove before app release
    
    if(crash == true){
        [[GAI sharedInstance] setTrackUncaughtExceptions:YES];
    }
}

void ganalytics_SendScreen(const char *screenName)
{

    NSString *screenName2 = [NSString stringWithUTF8String:screenName];
    id<GAITracker> tracker = [[GAI sharedInstance] defaultTracker];
    [tracker set:kGAIScreenName value:screenName2];
    [tracker send:[[GAIDictionaryBuilder createScreenView] build]];

    
}