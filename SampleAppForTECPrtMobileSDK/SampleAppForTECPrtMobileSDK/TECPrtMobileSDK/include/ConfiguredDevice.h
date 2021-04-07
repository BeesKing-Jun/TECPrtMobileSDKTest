//
//  ConfiguredDevice.h
//  TECPrtMobileSDK
//
//  Created by RSODM開 on 2019/10/25.
//  Copyright © 2019 RSODMF. All rights reserved.
//

#import <Foundation/Foundation.h>

/// Configured Device information class
@interface ConfiguredDevice : NSObject

// External Properties /////////////////////////////////////////////////////////
@property (nonatomic, strong, nonnull, readonly) NSString *DeviceName;
@property (nonatomic, strong, nonnull, readonly) NSString *LogicalName;
@property (nonatomic, strong, nonnull, readonly) NSString *Description;
@property (nonatomic, strong, nonnull, readonly) NSString *IPAddress;
@property (nonatomic, readonly) NSInteger UDPPort;
@property (nonatomic, readonly) NSInteger TCPPort;
@property (nonatomic, strong, nonnull) NSMutableDictionary<NSString *, NSString *> *OtherParameters;


// External Methods ////////////////////////////////////////////////////////////
/// Constructor
/// @param deviceName Device Name
/// @param logicalName Logical Name
/// @param description Device Description
/// @param ipAddress IP Address
/// @param tcp TCP Number
/// @param udp UDP Number
- (nonnull id) initWithDeviceName : (nonnull NSString *)deviceName
                      LogicalName : (nonnull NSString *)logicalName
                      Description : (nonnull NSString *)description
                        IPAddress : (nonnull NSString *)ipAddress
                          TCPPort : (NSInteger)tcp
                          UDPPort : (NSInteger)udp;

@end
