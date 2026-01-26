//
//  FiveAd.h
//  FiveAd
//
//  Created by Yusuke Konishi on 2014/11/12.
//  Copyright © 2024 LY Corporation. All rights reserved.
//
#import <UIKit/UIKit.h>

@protocol FADAdInterface;
@protocol FADLoadDelegate;

@protocol FADInterstitialEventListener;
@protocol FADCustomLayoutEventListener;
@protocol FADVideoRewardEventListener;
@protocol FADNativeEventListener;

typedef NS_ENUM (NSInteger, FADErrorCode) {
  kFADErrorCodeNone = 0,
  kFADErrorCodeNetworkError = 1,
  kFADErrorCodeNoAd = 2,
  kFADErrorCodeNoFill __deprecated_enum_msg("kFADErrorCodeNoFill is no longer used since ver.2.4.20210903") = 3,
  kFADErrorCodeBadAppId = 4,
  kFADErrorCodeStorageError = 5,
  kFADErrorCodeInternalError = 6,
  kFADErrorCodeUnsupportedOsVersion __deprecated_enum_msg("kFADErrorCodeUnsupportedOsVersion is no longer used since ver.2.4.20210903") = 7,
  kFADErrorCodeInvalidState = 8,
  kFADErrorCodeBadSlotId = 9,
  kFADErrorCodeSuppressed = 10,
  kFADErrorCodeContentUnavailable __deprecated_enum_msg("kFADErrorCodeContentUnavailable is no longer used since ver.2.4.20210903") = 11,
  kFADErrorCodePlayerError = 12,
  kFADErrorCodeFormatMismatch = 13
};

static const FADErrorCode kFADErrorNone = kFADErrorCodeNone;
static const FADErrorCode kFADErrorNetworkError = kFADErrorCodeNetworkError;
static const FADErrorCode kFADErrorNoCachedAd = kFADErrorCodeNoAd;
static const FADErrorCode kFADErrorNoFill __deprecated_msg("kFADErrorNoFill is no longer used since ver.2.4.20210903") = kFADErrorCodeNoFill;
static const FADErrorCode kFADErrorBadAppId = kFADErrorCodeBadAppId;
static const FADErrorCode kFADErrorStorageError = kFADErrorCodeStorageError;
static const FADErrorCode kFADErrorInternalError = kFADErrorCodeInternalError;
static const FADErrorCode kFADErrorUnsupportedOsVersion __deprecated_msg("kFADErrorUnsupportedOsVersion is no longer used since ver.2.4.20210903") = kFADErrorCodeUnsupportedOsVersion;
static const FADErrorCode kFADErrorInvalidState = kFADErrorCodeInvalidState;
static const FADErrorCode kFADErrorBadSlotId = kFADErrorCodeBadSlotId;
static const FADErrorCode kFADErrorSuppressed = kFADErrorCodeSuppressed;
static const FADErrorCode kFADErrorContentUnavailable __deprecated_msg("kFADErrorContentUnavailable is no longer used since ver.2.4.20210903") = kFADErrorCodeContentUnavailable;
static const FADErrorCode kFADErrorPlayerError = kFADErrorCodePlayerError;

typedef enum: NSInteger {
  kFADCreativeTypeNotLoaded = 0, // only returns when called before a successful load.
  kFADCreativeTypeMovie = 1,
  kFADCreativeTypeImage = 2,
} FADCreativeType;

typedef NS_ENUM (NSInteger, FADAdAgeRating) {
  kFADAdAgeRatingUnspecified = 0,
  kFADAdAgeRatingAllAge = 1,
  kFADAdAgeRatingAge13AndOver = 2,
  kFADAdAgeRatingAge15AndOver = 3,
  kFADAdAgeRatingAge18AndOver = 4
};

typedef NS_ENUM (NSInteger, FADNeedGdprNonPersonalizedAdsTreatment) {
  kFADNeedGdprNonPersonalizedAdsTreatmentUnspecified = 0,
  kFADNeedGdprNonPersonalizedAdsTreatmentFalse = 1,
  kFADNeedGdprNonPersonalizedAdsTreatmentTrue = 2
};

typedef NS_ENUM (NSInteger, FADNeedChildDirectedTreatment) {
  kFADNeedChildDirectedTreatmentUnspecified = 0,
  kFADNeedChildDirectedTreatmentFalse = 1,
  kFADNeedChildDirectedTreatmentTrue = 2
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"

static NSString* const kFADConfigAppIdKey = @"FIVE_APP_ID";
static NSString* const kFADConfigIsTestKey = @"FIVE_IS_TEST";

#pragma mark - configuration object of FiveSDK.
/**
 FADConfig is a configuration object for FiveSDK.
 FiveSDK uses this object for initialization.
 @see `FADSettings`
 */
@interface FADConfig : NSObject

/// build `FADConfig` object from Info.plist data.
/// If you want to use this method, you should register the following key-values in Info.plist.
///
/// | Key        | Type  | Value                            |
/// |------------|-------|----------------------------------|
/// |FIVE_APP_ID |String |your app id                       |
/// |FIVE_IS_TEST|Boolean|test (true) or production (false) |
/// 
+ (FADConfig*) loadFromInfoDictionary;

/// This method initializes `FADConfig` with the given app id.
/// @param appId You should register your app to our web system for generating your app id. It must not be null.
- (instancetype) initWithAppId:(NSString*)appId;

/// This method enables or disables sound by default.
/// This setting has a priority to the same setting on the server-side.
/// `-[FADAdInterface enableSound:]` can override this setting.
/// @param isSoundEnabled `YES`: enable, `NO`: disable
- (void) enableSoundByDefault:(BOOL)isSoundEnabled;

/// If this application is a pre-release version, you should set this property to `YES`.
/// If it is `YES`, our ad server delivers only sample ads.
///
/// default value: `NO`
@property (nonatomic) BOOL isTest;

@property (nonatomic, readonly) NSString* appId;

@property (nonatomic) FADAdAgeRating maxAdAgeRating;
@property (nonatomic) FADNeedGdprNonPersonalizedAdsTreatment needGdprNonPersonalizedAdsTreatment __deprecated_msg("needGdprNonPersonalizedAdsTreatment is no longer used since ver.2.9.20250507.");
@property (nonatomic) FADNeedChildDirectedTreatment needChildDirectedTreatment;
@end

__deprecated_msg("FADSettings is deprecated since ver.3.0.0. Use FADAdLoader instead. We might delete this API in a future release.")
@interface FADSettings : NSObject
/// :nodoc:
- (id)init NS_UNAVAILABLE;

/// Before using FiveSDK, you should call this method once.
/// This method initialize FiveSDK based on the given `FADConfig`.
/// @note First-time initialization might take some time.
/// You may fail to load an ad if you load an ad just after calling this method at the first time launch.
/// @param config a configuration object for FiveSDK. It must not be null.
+ (void)registerConfig:(FADConfig *)config;

/// Once registerConfig is called with valid config argument, this returns true. Otherwise, this returns false.
+ (BOOL)isConfigRegistered;

+ (NSString *)version __deprecated_msg("version is deprecated since ver.2.7.20240318. Use semanticVersion instead.");
+ (NSString *)semanticVersion;

+ (void)enableSound:(BOOL)enabled __deprecated_msg("enableSound is deprecated since ver.2.4.20210903. use `-[FADConfig enableSoundByDefault:]` instead.");
+ (BOOL)isSoundEnabled __deprecated_msg("isSoundEnabled is deprecated since ver.2.4.20210903.");
@end

/**
 * Base interface of ad objects.
 */
@protocol FADAdInterface <NSObject>
/// This method sets the sound to enable or disable.
/// You should call this method before showing the ad.
/// This setting has a priority to other sound settings.
/// @param enabled `YES`: enable, `NO`: disable
- (void) enableSound:(BOOL)enabled;

/// This method returns whether sound is enabled or disabled.
/// @note This method could return `YES` even if you call `-[FADAdInterface enableSound:]` with `NO` because users can enable sound by themselves.
- (BOOL) isSoundEnabled;

/// This method registers a callback object for receiving the result of `-[FADAdInterface loadAdAsync]`.
/// You MUST call this method before calling `-[FADAdInterface loadAdAsync]`.
/// @param loadDelegate callback object. FiveSDK only saves the weak reference.
- (void) setLoadDelegate:(id<FADLoadDelegate>)loadDelegate __deprecated_msg("setLoadDelegate is deprecated since ver.3.0.0. We might delete this API in a future release.");

/// This method tries to load ad.
/// The result is notified via `FADLoadDelegate`.
/// You must register `FADLoadDelegate` by `-[FADAdInterface setLoadDelegate:]` before calling this method.
- (void)loadAdAsync __deprecated_msg("loadAdAsync is deprecated since ver.3.0.0. Use FADAdLoader instead.");
- (void)loadAdAsyncWithTimeoutInterval:(NSTimeInterval)timeout __deprecated_msg("loadAdAsyncWithTimeoutInterval is deprecated since ver.2.9.20241105. We might delete this API in a future release.");

@property (nonatomic, readonly) NSString *slotId;
@property (nonatomic, readonly) FADCreativeType creativeType;

/// Media developer can use this property for distinguishing each ad object.
/// This property is not used for reporting. SDK does not read/write this property.
@property (nonatomic) NSString* fiveAdTag;

@end

/**
 * Ad object for interstitial ads.
 */
@interface FADInterstitial: NSObject<FADAdInterface>
/// This method initializes `FADInterstitial` with the given slot id.
/// @param slotId You should register an ad slot to our web system for generating your slot id. It must not be null.
- (instancetype)initWithSlotId:(NSString *)slotId __deprecated_msg("initWithSlotId is deprecated since ver.3.0.0. Use FADAdLoader.loadInterstitialAdWithConfig instead.");

/// :nodoc:
- (instancetype)init NS_UNAVAILABLE;

#pragma clang diagnostic pop  // ignored "-Wnullability-completeness"

/// Start to display the loaded interstitial ad.
/// Only available after the ad is successfully loaded.
/// Return value is always YES.
/// Use fiveInterstitialAdFullScreenDidOpen and fiveInterstitialAd:ad didFailedToShowAdWithError
/// for detecting interstitial ad is successfully opened or not.
- (BOOL) show __deprecated_msg("show is deprecated since ver.2.7.20240318. Use showWithViewController instead.");

- (void) showWithViewController:(nullable UIViewController*)viewController;

/// Force close the displaying interstitial ad.
- (void) close;

- (void) setEventListener:(nullable id<FADInterstitialEventListener>)listener;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"

@end

/**
 * Basic ad object of FiveAd.
 * This ad object is used for banner ads.
 */
@interface FADAdViewCustomLayout: UIView<FADAdInterface>
/// This method initializes `FADAdViewCustomLayout` with the given slot id.
/// @param slotId You should register an ad slot to our web system for generating your slot id. It must not be null.
/// @param width  The initial width of ad view. The aspect ratio of an ad view is managed in our web system.
- (instancetype)initWithSlotId:(NSString *)slotId width:(float)width __deprecated_msg("initWithSlotId:width: is deprecated since ver.3.0.0. Use FADAdLoader.loadBannerAdWithConfig instead.");;

/// :nodoc:
- (instancetype)init NS_UNAVAILABLE;
/// :nodoc:
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_UNAVAILABLE;
/// :nodoc:
- (instancetype)initWithFrame:(CGRect)frame NS_UNAVAILABLE;

/// Only available after the ad is successfully loaded.
/// This may returns empty string i.e. @""
- (NSString *)getAdvertiserName __deprecated_msg("getAdvertiserName is deprecated since ver.3.0.0. We might delete this API in a future release.");

#pragma clang diagnostic pop  // ignored "-Wnullability-completeness"

- (void) setEventListener:(nullable id<FADCustomLayoutEventListener>)listener;

/// Using this method requires a review.
/// If the review has not been passed, this method will have no effect.
- (void) registerFriendlyObstructionView:(nonnull UIView*)view;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"

@end

/**
 * Ad object for reward ads.
 */
@interface FADVideoReward: NSObject<FADAdInterface>
/// This method initializes `FADVideoReward` with the given slot id.
/// @param slotId You should register an ad slot to our web system for generating your slot id. It must not be null.
- (instancetype)initWithSlotId:(NSString *)slotId __deprecated_msg("initWithSlotId is deprecated since ver.3.0.0. Use FADAdLoader.loadRewardAdWithConfig instead.");

/// :nodoc:
- (instancetype)init NS_UNAVAILABLE;

#pragma clang diagnostic pop  // ignored "-Wnullability-completeness"
/// Start to display the loaded reward ad.
/// Only available after the ad is successfully loaded.
/// Return value is always YES.
/// Use fiveVideoRewardAdFullScreenDidOpen and fiveVideoRewardAd:ad didFailedToShowAdWithError
/// for detecting video reward ad is successfully opened or not.
- (BOOL) show __deprecated_msg("show is deprecated since ver.2.7.20240318. Use showWithViewController instead.");

- (void) showWithViewController:(nullable UIViewController*)viewController;

- (void) setEventListener:(nullable id<FADVideoRewardEventListener>)listener;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"

@end

@interface FADNative: NSObject<FADAdInterface>
- (instancetype)initWithSlotId:(NSString *)slotId videoViewWidth:(float)videoViewWidth __deprecated_msg("initWithSlotId:videoViewWidth: is deprecated since ver.3.0.0. Use FADAdLoader.loadNativeAdWithConfig instead.");

/// :nodoc:
- (instancetype)init NS_UNAVAILABLE;

// The methods below are only available after ad is loaded.
- (void) registerViewForInteraction:(UIView*)nativeAdView
            withInformationIconView:(UIView*)informationIconView
                 withClickableViews:(NSArray<UIView*>*)clickableViews;
- (void) registerFriendlyObstructionView:(nonnull UIView*)view;

- (UIView*)getAdMainView;

// return values are non-nil, but NSString may be empty string i.e. @""
- (NSString*)getButtonText;
- (NSString*)getDescriptionText __deprecated_msg("getDescriptionText is deprecated since ver.3.0.0. Use getLongDescriptionText or getAdTitle instead.");
- (NSString*)getLongDescriptionText;
- (NSString*)getAdvertiserName;
- (NSString*)getAdTitle;

- (void) loadIconImageAsyncWithBlock:(void (^) (UIImage*))block;
- (void) loadInformationIconImageAsyncWithBlock:(void (^) (UIImage*))block;

#pragma clang diagnostic pop  // ignored "-Wnullability-completeness"

- (void) setEventListener:(nullable id<FADNativeEventListener>)listener;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnullability-completeness"

@end

#pragma mark - delegates

__deprecated_msg("FADLoadDelegate is deprecated since ver.3.0.0. We might delete this API in a future release.")
@protocol FADLoadDelegate <NSObject>
- (void) fiveAdDidLoad:(id<FADAdInterface>)ad;
- (void) fiveAd:(id<FADAdInterface>)ad didFailedToReceiveAdWithError:(FADErrorCode) errorCode;
@end

#pragma clang diagnostic pop  // ignored "-Wnullability-completeness"

@protocol FADInterstitialEventListener <NSObject>
- (void) fiveInterstitialAd:(nonnull FADInterstitial*)ad didFailedToShowAdWithError:(FADErrorCode) errorCode;

@optional
- (void) fiveInterstitialAdDidClick:(nonnull FADInterstitial*)ad;
- (void) fiveInterstitialAdDidImpression:(nonnull FADInterstitial*)ad;
- (void) fiveInterstitialAdFullScreenDidOpen:(nonnull FADInterstitial*)ad;
- (void) fiveInterstitialAdFullScreenDidClose:(nonnull FADInterstitial*)ad;
- (void) fiveInterstitialAdDidPlay:(nonnull FADInterstitial*)ad;
- (void) fiveInterstitialAdDidPause:(nonnull FADInterstitial*)ad;
- (void) fiveInterstitialAdDidViewThrough:(nonnull FADInterstitial*)ad;
@end

@protocol FADCustomLayoutEventListener <NSObject>
- (void) fiveCustomLayoutAd:(nonnull FADAdViewCustomLayout*)ad didFailedToShowAdWithError:(FADErrorCode) errorCode;

@optional
- (void) fiveCustomLayoutAdDidClick:(nonnull FADAdViewCustomLayout*)ad;
- (void) fiveCustomLayoutAdDidImpression:(nonnull FADAdViewCustomLayout*)ad;
- (void) fiveCustomLayoutAdViewDidRemove:(nonnull FADAdViewCustomLayout*)ad;
- (void) fiveCustomLayoutAdDidPlay:(nonnull FADAdViewCustomLayout*)ad;
- (void) fiveCustomLayoutAdDidPause:(nonnull FADAdViewCustomLayout*)ad;
- (void) fiveCustomLayoutAdDidViewThrough:(nonnull FADAdViewCustomLayout*)ad;
@end

@protocol FADVideoRewardEventListener <NSObject>
- (void) fiveVideoRewardAd:(nonnull FADVideoReward*)ad didFailedToShowAdWithError:(FADErrorCode) errorCode;
- (void) fiveVideoRewardAdDidReward:(nonnull FADVideoReward*)ad;

@optional
- (void) fiveVideoRewardAdDidClick:(nonnull FADVideoReward*)ad;
- (void) fiveVideoRewardAdDidImpression:(nonnull FADVideoReward*)ad;
- (void) fiveVideoRewardAdFullScreenDidOpen:(nonnull FADVideoReward*)ad;
- (void) fiveVideoRewardAdFullScreenDidClose:(nonnull FADVideoReward*)ad;
- (void) fiveVideoRewardAdDidPlay:(nonnull FADVideoReward*)ad;
- (void) fiveVideoRewardAdDidPause:(nonnull FADVideoReward*)ad;
- (void) fiveVideoRewardAdDidViewThrough:(nonnull FADVideoReward*)ad;
@end

@protocol FADNativeEventListener <NSObject>
- (void) fiveNativeAd:(nonnull FADNative*)ad didFailedToShowAdWithError:(FADErrorCode) errorCode;

@optional
- (void) fiveNativeAdDidClick:(nonnull FADNative*)ad;
- (void) fiveNativeAdDidImpression:(nonnull FADNative*)ad;
- (void) fiveNativeAdViewDidRemove:(nonnull FADNative*)ad;
- (void) fiveNativeAdDidPlay:(nonnull FADNative*)ad;
- (void) fiveNativeAdDidPause:(nonnull FADNative*)ad;
- (void) fiveNativeAdDidViewThrough:(nonnull FADNative*)ad;
@end

@interface FADAdSlotConfig : NSObject
- (nonnull instancetype) init NS_UNAVAILABLE;

+ (nonnull FADAdSlotConfig*) configWithSlotId:(nonnull NSString*)slotId;
@end

@interface FADBidData : NSObject
@property (nonatomic, nonnull, readonly) NSString* bidResponse;
@property (nonatomic, nullable, readonly) NSString* watermark;

- (nonnull instancetype) init NS_UNAVAILABLE;
- (nonnull instancetype) initWithBidResponse:(nonnull NSString*)bidResponse
                               withWatermark:(nullable NSString*)watermark;
@end

@protocol FADThirdPartyIdProvider <NSObject>

- (nonnull NSString*) providerName;
- (nullable id) userInfo;

@end

/**
 * Core API for FiveSDK version 3.*
 */
@interface FADAdLoader : NSObject
+ (nonnull NSString*) semanticVersion;

+ (nullable FADAdLoader*) adLoaderForConfig:(nonnull FADConfig*)config
                                   outError:(out NSError* _Nullable * _Nullable)outError;

- (nonnull instancetype) init NS_UNAVAILABLE;

- (BOOL) registerThirdPartyIdProvider:(nonnull id<FADThirdPartyIdProvider>)idProvider;

- (void) loadBannerAdWithConfig:(nonnull FADAdSlotConfig*)config
               withInitialWidth:(double)width
               withLoadCallback:(void (^_Nonnull)(FADAdViewCustomLayout*_Nullable, NSError*_Nullable))callback;
- (void) loadInterstitialAdWithConfig:(nonnull FADAdSlotConfig*)config
                     withLoadCallback:(void (^_Nonnull)(FADInterstitial*_Nullable, NSError*_Nullable))callback;
- (void) loadRewardAdWithConfig:(nonnull FADAdSlotConfig*)config
               withLoadCallback:(void (^_Nonnull)(FADVideoReward*_Nullable, NSError*_Nullable))callback;
- (void) loadNativeAdWithConfig:(nonnull FADAdSlotConfig*)config
               withInitialWidth:(double)width
               withLoadCallback:(void (^_Nonnull)(FADNative*_Nullable, NSError*_Nullable))callback;

// APIs for bidder
- (void) collectSignalWithSlotId:(nonnull NSString*)slotId
              withSignalCallback:(void (^_Nonnull)(NSString*_Nullable, NSError*_Nullable))callback;
- (void) collectSignalWithConfig:(nonnull FADAdSlotConfig*)config
              withSignalCallback:(void (^_Nonnull)(NSString*_Nullable, NSError*_Nullable))callback;

- (void) loadBannerAdWithBidData:(nonnull FADBidData*)bidData
                withLoadCallback:(void (^_Nonnull)(FADAdViewCustomLayout*_Nullable, NSError*_Nullable))callback __deprecated_msg("loadBannerAdWithBidData:withLoadCallback: is deprecated since ver.2.9.20241105. Use loadBannerAdWithBidData:withInitialWidth:withLoadCallback: instead.");
- (void) loadBannerAdWithBidData:(nonnull FADBidData*)bidData
                withInitialWidth:(double)width
                withLoadCallback:(void (^_Nonnull)(FADAdViewCustomLayout*_Nullable, NSError*_Nullable))callback;
- (void) loadInterstitialAdWithBidData:(nonnull FADBidData*)bidData
                      withLoadCallback:(void (^_Nonnull)(FADInterstitial*_Nullable, NSError*_Nullable))callback;
- (void) loadRewardAdWithBidData:(nonnull FADBidData*)bidData
                withLoadCallback:(void (^_Nonnull)(FADVideoReward*_Nullable, NSError*_Nullable))callback;
- (void) loadNativeAdWithBidData:(nonnull FADBidData*)bidData
                withLoadCallback:(void (^_Nonnull)(FADNative*_Nullable, NSError*_Nullable))callback;
- (void) loadNativeAdWithBidData:(nonnull FADBidData*)bidData
                withInitialWidth:(double)width
                withLoadCallback:(void (^_Nonnull)(FADNative*_Nullable, NSError*_Nullable))callback;
@end
