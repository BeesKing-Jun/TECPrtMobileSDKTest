//
//  TECFile.h
//  TECPrtMobileSDK
//
//  Created by RSODM開 on 2019/10/25.
//  Copyright © 2019 RSODMF. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TECCommon.h"

/// TECFile class to control the File
/*
 Note: In order to use the File Access for Local, please add the following values in Info.plist
 - "Application supports iTunes file sharing" -> YES
 - "Supports opening documents in place" -> YES
 
 Note: In order to use the File Access for iCloud, please set following.
 1. [Capabilities] iCloud Document should be ON. It needs Apple Developer Program Account.
 2. [Info.plist]
    - "NSUbiquitousContainers" (Dictionary)
      <Container Full Name> (Dictionary)
        NSUbiquitousContainerIsDocumentScopePublic (Boolean) -> YES
        NSUbiquitousContainerName (String) -> <Application Name>
        NSUbiquitousContainerSupportedFolderLevels (String) -> Any
 */
@interface TECFile : NSObject

/// File Location List
typedef NS_ENUM(NSInteger, Location) {
    iCloudDrive = 0,        /// iCould Drive Document (from iOS 9)
    iCloudDriveShare = 1,   /// iCould Document using Application Folder (from iOS 10)
    localFile = 2,          /// Local File
    localFileShare = 3,     /// Local File using Share Folder (from iOS11)
    localInBox = 4,         /// Local File for Import from other application
};

// External Methods ////////////////////////////////////////////////////////////
/// Get Current Directory Path
/// @param location Directory Path Category
+ (nonnull NSURL *) getCurrentDirectoryAtLocation : (Location)location;

/// Creates the specified Folder
/// @param url Folder Path
+ (nonnull NSURL *) createFolderAtUrl : (nonnull NSURL *)url;

/// Delete the specified File
/// @param url File URL
+ (BOOL) deleteFileAtUrl : (nonnull NSURL *)url;

/// Rename the File
/// @param from Original File Path
/// @param to new File Path
+ (BOOL) renameWithFromUrl : (nonnull NSURL *)from
                        To : (nonnull NSURL *)to;

/// Returns the File List in specified folder
/// @param url Folder URL
/// @param extensions Extension Flter List. If the file extension includes in this list, the returns list has this.
+ (nonnull NSArray<NSString *> *) listAtUrl : (nonnull NSURL *)url
                                 Extensions : (nullable NSArray<NSString *> *)extensions;

/// Count File Data Size
/// @param url File Path
+ (NSUInteger) sizeAtUrl : (nonnull NSURL *)url;

/// Read String data in specified file
/// @param url File Address
/// @param encoding Encoding option
+ (nonnull NSString *) readStringAtUrl : (nonnull NSURL *)url
                              Encoding : (NSStringEncoding)encoding;

/// Read the file as Binary Data
/// @param url File Address
+ (nonnull NSArray<NSNumber *> *) readBinaryAtUrl : (nonnull NSURL *)url;

/// Read the file as Binary Data
/// @param url File Address
/// @param index Start Index
/// @param size Reading Size
+ (nonnull NSArray<NSNumber *> *) readBinaryAtUrl : (nonnull NSURL *)url
                                            Index : (NSUInteger)index
                                             Size : (NSUInteger)size;

/// Write the data to specified file
/// @param url File Address
/// @param data Writing Data
/// @param encoding Writing Data Encoding option
/// @param isAppend Append or Override
+ (NSUInteger) writeStringAtUrl : (nonnull NSURL *)url
                           Data : (nonnull NSString *)data
                       Encoding : (NSStringEncoding)encoding
                       IsAppend : (BOOL)isAppend;

/// Write the data to specified file as Binary Data
/// @param url File Address
/// @param data Pointer of Writing Binary Data
/// @param size Size of Writing Binary Data
/// @param isAppend Append or Override
+ (NSUInteger) writeBinaryAtUrl : (nonnull NSURL *)url
                           Data : (nonnull uint8_t *)data
                           Size : (NSUInteger)size
                       IsAppend : (BOOL)isAppend;

@end
