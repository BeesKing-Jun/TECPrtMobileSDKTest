//
//  TECPOSDevice.h
//  TECPrtMobileSDK
//
//  Created by RSODM開 on 2019/10/25.
//  Copyright © 2019 RSODMF. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ConfiguredDevice.h"
#import "ConfiguredDeviceXMLParser.h"
#import "TECFile.h"
#import "TECLog.h"
#import "Resource.h"
#import "TECInterface.h"
#import "TECPOSResource.h"


/// TEC POS Device UPOS Common method / property Class
@interface TECPOSDevice : NSObject {
    // Internal Values /////////////////////////////////////////////////////////
    ConfiguredDevice *mDevice;
    TECInterface *mTecIf;
}

/// POS Access Stage
typedef NS_ENUM(NSInteger, AccessStage) {
    AccessOpen,             // Accept After Open.
    AccessClaim,            // Accept After Claim.
    AccessDeviceEnabled,    // Accept After Device Enabled.
    AccessOpenClaim,        // Accept After Open and before Claim
};


// External Properties //////////////////////////////////////////////////////////
@property (nonatomic, class, strong, nonnull, getter=getDevices, setter=setConfigureDeviceList:) NSMutableArray<ConfiguredDevice *> *ConfiguredDeviceList;
@property (nonatomic, class, strong, nonnull, getter=getClaimedList, setter=setClaimedList:) NSMutableArray<NSString *> *ClaimedList;


// External Methods ////////////////////////////////////////////////////////////
/// Obtain current SDK version
+ (nonnull NSString *) getVersion;

/// Set the logging path
/// @param filePath Full Path of Log stored file.
+ (void) setLogFilePath : (nonnull NSString *)filePath;

/// Set the Logging Level
/// @param logLevel Leg Level (0x00 - 0xFF)
+ (void) setLogLevel : (uint8_t)logLevel;

/// Get the Logging Level
+ (uint8_t) getLogLevel;

/// Obtain the list of Configured Device in the API's
/// @param filePath Full Path of Configured Devices File
+ (void) loadConfigurationFile : (nonnull NSString *)filePath;

@end
