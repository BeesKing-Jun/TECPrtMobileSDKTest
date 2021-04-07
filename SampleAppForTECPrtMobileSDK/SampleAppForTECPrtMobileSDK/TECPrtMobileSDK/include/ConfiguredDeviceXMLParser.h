//
//  ConfiguredDeviceXMLParser.h
//  TECPrtMobileSDK
//
//  Created by RSODM開 on 2019/11/05.
//  Copyright © 2019 RSODMF. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TECLog.h"
#import "CommonXMLParser.h"
#import "ConfiguredDevice.h"

@interface ConfiguredDeviceXMLParser : CommonXMLParser {
    BOOL mIsLANPrinter;
    
    NSString *mLogicalDeviceName;
    NSString *mPhysicalDeviceName;
    NSString *mDescription;
    NSString *mIPAddress;
    NSInteger mTCPNumber;
    NSInteger mUDPNumber;
    NSMutableDictionary<NSString *, NSString *> *mParameters;
}

@property (nonatomic, strong, readonly, nullable) NSMutableArray<ConfiguredDevice *> *DeviceList;

@end
