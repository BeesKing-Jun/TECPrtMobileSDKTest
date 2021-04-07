//
//  TECLog.h
//  TECPrtMobileSDK
//
//  Created by RSODM開 on 2019/10/25.
//  Copyright © 2019 RSODMF. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TECCommon.h"
#import "TECFile.h"

/// TECFile class to control the File
@interface TECLog : NSObject

/// Log Level
typedef NS_ENUM(NSUInteger, Level) {
    allDisable = 0x00,              // Disable all Log Level (No Logging)
    criticalErr = 0x01,             // Critical Error
    generalErr = 0x02,              // General Error
    warning = 0x04,                 // Warning
    trace = 0x08,                   // Trace Log
    info = 0x10,                    // Information
    verbose = 0x20,                 // Verbose
    debug = 0x40,                   // Debug Log
    allEnable = 0x3F,               // Enable All Log without Debug
    allEnableWithDebug = 0x7F,      // Enable All Log with Debug
};

/// Sign Character
typedef NS_ENUM(NSInteger, Sign) {
    extFuncStart,                   // "->" External Method is Started
    extFuncEnd,                     // "<-" External Method is End
    intFuncStart,                   // ">>" Internal Method is Started
    intFuncEnd,                     // "<<" Internal Method is End
    crtErr,                         // "XX" Critical Error is occurred
    genErr,                         // "xx" General Error is occurred
    other,                          // "  " Other Log
};


// External Properties /////////////////////////////////////////////////////////
@property (nonatomic, class, strong, nullable, getter=getLogFilePath, setter=setLogFilePath:) NSString *LogFilePath;
@property (nonatomic, class, getter=getLogLevel, setter=setLogLevel:) uint8_t LogLevel;


// External Methods ////////////////////////////////////////////////////////////
/// Write Log Message as Critical Error
/// @param funcNumber Function Number
/// @param sign Sign Character
/// @param message Logging message
+ (void) crtErr : (NSUInteger)funcNumber
           Sign : (Sign)sign
        Message : (nonnull NSString *)message;

/// Write Log Message as General Error
/// @param funcNumber Function Number
/// @param sign Sign Character
/// @param message Logging message
+ (void) genErr : (NSUInteger)funcNumber
           Sign : (Sign)sign
        Message : (nonnull NSString *)message;

/// Write Log Message as Warning
/// @param funcNumber Function Number
/// @param sign Sign Character
/// @param message Logging message
+ (void) warning : (NSUInteger)funcNumber
            Sign : (Sign)sign
         Message : (nonnull NSString *)message;

/// Write Log Message as Trace
/// @param funcNumber Function Number
/// @param sign Sign Character
/// @param message Logging message
+ (void) trace : (NSUInteger)funcNumber
          Sign : (Sign)sign
       Message : (nonnull NSString *)message;

/// Write Log Message as Information
/// @param funcNumber Function Number
/// @param sign Sign Character
/// @param message Logging message
+ (void) info : (NSUInteger)funcNumber
         Sign : (Sign)sign
      Message : (nonnull NSString *)message;

/// Write Log Message as Verbose
/// @param funcNumber Function Number
/// @param sign Sign Character
/// @param message Logging message
+ (void) verbose : (NSUInteger)funcNumber
            Sign : (Sign)sign
         Message : (nonnull NSString *)message;

/// Write Log Message as Debug
/// @param funcNumber Function Number
/// @param sign Sign Character
/// @param message Logging message
+ (void) debug : (NSUInteger)funcNumber
          Sign : (Sign)sign
       Message : (nonnull NSString *)message;

@end
