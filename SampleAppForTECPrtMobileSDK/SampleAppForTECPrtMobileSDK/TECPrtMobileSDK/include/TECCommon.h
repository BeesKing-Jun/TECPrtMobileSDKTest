//
//  TECCommon.h
//  TECPrtMobileSDK
//
//  Created by RSODM開 on 2019/10/28.
//  Copyright © 2019 RSODMF. All rights reserved.
//

#import <Foundation/Foundation.h>

// iOS10 NSLog is limited to 1024 chars strings.
// The NSLog is same as "print" method of Swift.
#define NSLOG(FORMAT, ...) printf("%s\n", [[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);

/// Common Methods
@interface TECCommon : NSObject

// External Methods ////////////////////////////////////////////////////////////
/// Check the string is match or not using Regular Expression
/// @param target Target String
/// @param pattern Regular Expression Pattern
+ (BOOL) isMatchesAtString : (nonnull NSString *)target
                   Pattern : (nonnull NSString *)pattern;

/// Check the string is match or not using Regular Expression
/// @param target Target String
/// @param pattern Regular Expression Pattern
/// @param options Regular Expression Option
+ (BOOL) isMatchesAtString  : (nonnull NSString *)target
                    Pattern : (nonnull NSString *)pattern
                    Options : (NSRegularExpressionOptions)options;

/// Replace the string using Regular Expression
/// @param target Target String
/// @param pattern Regular Expression Pattern
/// @param replace Replace Pattern
+ (nonnull NSString *) replaceAtString : (nonnull NSString *)target
                               Pattern : (nonnull NSString *)pattern
                               Replace : (nonnull NSString *)replace;

/// Check the string is IP Address or not
/// @param ipAddress IP Address String
+ (BOOL) isIPAddressAtString : (nonnull NSString *)ipAddress;

/// Check the string is ASCII or not
/// @param target Target String
+ (BOOL) isAsciiAtString : (nonnull NSString *)target;

/// Get Current Date Time using format
/// @param format Format String. If nil, uses "yyyyMMddHHmmss"
+ (nonnull NSString *) getDateTimeWithFormat : (nullable NSString *)format;

/// Judge the value is in Range or not
/// @param target Target Value
/// @param min Minimum Value
/// @param max Maximum Value
+ (BOOL) isWithRangeAtInteger : (NSInteger)target
                      Minimum : (NSInteger)min
                      Maximum : (NSInteger)max;

/// Judge the value is in Range or not
/// @param target Target Value
/// @param min Minimum Value
/// @param max Maximum Value
+ (BOOL) isWithRangeAtUInteger : (NSUInteger)target
                       Minimum : (NSUInteger)min
                       Maximum : (NSUInteger)max;

/// Judge the value is in Range or not
/// @param target Target Value
/// @param min Minimum Value
/// @param max Maximum Value
+ (BOOL) isWithRangeAtUIniChar : (unichar)target
                       Minimum : (unichar)min
                       Maximum : (unichar)max;

/// Judge the target bit is On Bit or not.
/// @param bit Target Bit
/// @param num Target Index (0 - 7)
+ (BOOL) isOnBit : (UInt8)bit
           Index : (UInt8)num;

@end
