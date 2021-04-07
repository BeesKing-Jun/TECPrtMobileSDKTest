//
//  TECInterface.h
//  TECPrtMobileSDK
//
//  Created by RSODM開 on 2019/10/25.
//  Copyright © 2019 RSODMF. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <sys/socket.h>
#import <sys/types.h>
#import <sys/ioctl.h>
#import <netinet/in.h>
#import <arpa/inet.h>
#import "TECCommon.h"
#import "TECLog.h"

/// Sign Character
typedef NS_ENUM(NSInteger, ResultValue) {
    success = 0,                    // Success
    failed = -1,                    // Failed
    timeout = -2,                   // Timeout
    notOpened = -3,                 // Not Opened
};

/// TECInterface class to communicate with Ethernet Printer
/*
 Note: This class is internal use.
 */
@interface TECInterface : NSObject {
    // Internal Values /////////////////////////////////////////////////////////
    NSInputStream *mTCPInStream;
    NSOutputStream *mTCPOutStream;
    int mUDPSocket;
    struct sockaddr_in mUDPAddress;
}


// External Properties /////////////////////////////////////////////////////////
@property (nonatomic, strong, nonnull, readonly) NSString *IPAddress;
@property (nonatomic, readonly) NSInteger TCPNumber;
@property (nonatomic, readonly) NSInteger UDPNumber;


// External Methods ////////////////////////////////////////////////////////////
/// Constructor
/// @param ipAddress IP Address
/// @param tcp TCP Number
/// @param udp UDP Number
- (nullable id) initWithIPAddress : (nonnull NSString *)ipAddress
                           TCPNum : (NSInteger)tcp
                           UDPNum : (NSInteger)udp;

/// Lock and Open the communication. After that, the others class can't access.
/// @param timeout Timeout Value
- (NSInteger) lock : (NSUInteger)timeout;

/// Unlock the communication. After that, the others class can access.
//- (NSInteger) unlock;

/// Close the communication. After that, the others class can access.
- (NSInteger) closeCommunication;

/// Send Data
/// @param data Pointer of Sending Data
/// @param size Size of Sending Data
/// @param timeout Timeout Value
- (NSInteger) sendWithData : (nonnull uint8_t *)data
                      Size : (NSUInteger)size
                   Timeout : (NSUInteger)timeout;

/// Receive any data
/// @param size Size of Receiving Data
/// @param timeout Timeout Value
- (nonnull NSArray<NSNumber *> *) receiveWithSize : (NSUInteger)size
                                          Timeout : (NSUInteger)timeout;

/// Real Time Command
/// @param data Pointer of Sending Data
/// @param sendSize Size of Sending Data
/// @param receiveSize Size of Receiving Data
/// @param timeout Timeout Value
- (nonnull NSArray<NSNumber *> *) realTimeCommandWithSendData : (nonnull uint8_t *)data
                                                     SendSize : (NSUInteger)sendSize
                                                  ReceiveSize : (NSUInteger)receiveSize
                                                      Timeout : (NSUInteger)timeout;

@end
