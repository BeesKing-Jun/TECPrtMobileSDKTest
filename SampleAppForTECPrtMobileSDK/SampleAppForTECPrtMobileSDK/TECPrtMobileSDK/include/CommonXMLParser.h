//
//  CommonXMLParser.h
//  TECPrtMobileSDK
//
//  Created by RSODM開 on 2019/11/05.
//  Copyright © 2019 RSODMF. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TECCommon.h"
#import "TECLog.h"

/// Parser Status
typedef NS_ENUM(NSUInteger, ParserStatus) {
    None = 0,               // No Parser
    Element = 1,            // "element" is found
    ChildElement = 2,       // "childElement" is found
    ChildAttribute = 3,     // "childAttributeKey/Value" is found
};

/// Common XML Parser Class.
@interface CommonXMLParser : NSObject<NSXMLParserDelegate> {
    // Internal Values /////////////////////////////////////////////////////////
    BOOL mIsParsed;
    NSString * mElement;
    NSString * mChildElement;
    NSString * mChildAttributeKey;
    NSString * mChildAttributeValue;
    ParserStatus mParserStatus;
    ParserStatus mTargetParserStatus;
}


// External Methods ////////////////////////////////////////////////////////////
/// [Override Method] Execute the parsing. When get any data, this method is called.
/// @param element Element Name
/// @param attribute Attribute Key Values.
/// @param isStartElement Start Element Timing or End Element Timing
- (void) parsing : (nonnull NSString *)element
       Attribute : (nonnull NSDictionary<NSString *,NSString *> *)attribute
  IsStartElement : (BOOL)isStartElement;

/// Set the Information for Parsing.
/// @param filePath File Path
/// @param element Target Element Name
- (BOOL) parseAtFilePath : (nonnull NSString *)filePath
           TargetElement : (nonnull NSString *)element;

/// Set the Information for Parsing.
/// @param filePath File Path
/// @param element Target Element Name
/// @param childElement Target Child Element
- (BOOL) parseAtFilePath : (nonnull NSString *)filePath
           TargetElement : (nonnull NSString *)element
      TargetChildElement : (nonnull NSString *)childElement;

/// Set the Information for Parsing.
/// @param filePath File Path
/// @param element Target Element Name
/// @param childElement Target Child Element
/// @param childAttributeKey Target Attribute Key
/// @param childAttributeValue Target Attribute Value
- (BOOL) parseAtFilePath : (nonnull NSString *)filePath
           TargetElement : (nonnull NSString *)element
      TargetChildElement : (nonnull NSString *)childElement
      TargetAttributeKey : (nonnull NSString *)childAttributeKey
    TargetAttributeValue : (nonnull NSString *)childAttributeValue;

@end
