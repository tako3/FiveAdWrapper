//
//  FADGADMediationAdapterConstants.h
//  FiveGADAdapter
//
//  Created by Nishiyama Shun on 2020/06/18.
//  Copyright © 2020 LINE Inc. All rights reserved.
//

#ifndef FADGADMediationAdapterConstants_h
#define FADGADMediationAdapterConstants_h

#import <Foundation/Foundation.h>
#import <GoogleMobileAds/GoogleMobileAds.h>

extern NSString * _Nonnull const kFADGADAdapterVersion;
extern GADVersionNumber const kFADGADAdapterVersionNumber;

static NSString * _Nonnull const kFADGADAdapterExtraLabel = @"FIVE_GAD_EXTRA_LABEL";

static NSString * _Nonnull const kFADGADAdapterExtraVideoViewWidthKey = @"FIVE_VIDEO_VIEW_WIDTH";

typedef NS_ENUM(NSInteger, FADGADErrorCode) {
  kFADGADErrorWithFADError = 101,
  kFADGADErrorInitializationFailed = 102,
  kFADGADErrorLoadFailed = 103,
  kFADGADErrorEnteringFullScreenFailed = 104,
  kFADGADErrorInvalidRequest = 105,
};

#endif /* FADGADMediationAdapterConstants_h */
