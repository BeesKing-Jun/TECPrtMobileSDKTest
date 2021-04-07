//
//  TECPOSPrinter.h
//  TECPrtMobileSDK
//
//  Created by RSODM開 on 2019/10/25.
//  Copyright © 2019 RSODMF. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import "TECPOSDevice.h"
#import "TECPOSResource.h"
#import "ConfiguredDevice.h"
#import "TECCommon.h"
#import "TECLog.h"
#import "Resource.h"
#import "TECInterface.h"


// Delegate Methods
@protocol TECPOSPrinterStatusUpdateEventDelegate <NSObject>

/// POS Status Update Event Delegate Method
/// @param status Status
/// @param message Message
@optional
- (void) posStatusUpdateEvent : (NSInteger)status
                   Message : (nonnull NSString *)message;

@end

/// TECPOS Printer Class to control the Common Methods and POS Printer Special Methods.
@interface TECPOSPrinter : TECPOSDevice {
    // Internal Values /////////////////////////////////////////////////////////
    // UPOS Common Properties
    BOOL mIsOpened;
    BOOL mIsClaimed;
    BOOL mIsDeviceEnabled;
    NSString *mPhysicalDeviceName;
    PosError mPosError;
    PosErrorEx mPosErrorEx;
    NSString *mPhyDeviceName;
    
    // POSPrinter UPOS Special Properties
    NSInteger mCharacterSet;
    NSMutableArray<NSNumber *> *mCharacterSetList;
    BOOL mIsCoverOpen;
    NSInteger mErrorLevel;
    BOOL mIsRecEmpty;
    BOOL mIsRecNearEmpty;
    NSInteger mRecLineChars;
    NSMutableArray<NSNumber *> *mRecLineCharsList;
    NSInteger mRecLineHeight;
    NSInteger mRecLineWidth;
    NSInteger mRecLineSpacing;
    NSInteger mRecSideWaysMaxChars;
    NSInteger mPtrCharWidth;
    NSInteger mPtrCharHeight;
    
    // TODO: Add Important parameter for each PosPrinter Class. (TRST-P1X, P2X)
    TransactionControl mPrintMode;
    NSURL *mTransactionFilePath;
    BOOL mIsDrawerOpen;
    NSArray<NSNumber *> *mCmdFullCut;
    NSArray<NSNumber *> *mCmdPartialCut;
    NSArray<NSNumber *> *mCmdGetStatus;
    NSUInteger mCmdGetStatusCount;
    NSArray<NSNumber *> *mCmdKickDrawer;
    NSArray<NSNumber *> *mCmdAlignment;
    NSArray<NSNumber *> *mCmdStoreBitmap;
    NSArray<NSNumber *> *mCmdPrintBitmap;
    
    // Printer Hardware Capability
    NSInteger mResolution;
    NSArray<NSNumber *> *mPaperWidthSupport;
    NSArray<NSNumber *> *mFontSizeSupport;
    NSArray<NSNumber *> *mFontTypeSupport;
    NSArray<NSArray<NSArray<NSNumber *>*>*> *mRecPrintableArea;
    NSArray<NSArray<NSArray<NSNumber *>*>*> *mRecCharPerLines;
    NSArray<NSArray<NSNumber *>*> *mRecGraphicArea;
    NSArray<NSNumber *> *mCodePageList;
    NSInteger mSetBMPType;
    NSInteger mPrintBMPType;
    NSInteger mRtsType;
    NSInteger mPageMaxHeight;
    NSArray<NSNumber *> *mRecCharHeight;
    NSArray<NSArray<NSNumber *>*> *mRecCharWidth;
    NSArray<NSNumber *> *mRecCharSpacing;
    
    // Barcode Default Parameters
    NSString *mCode128Default;              // Code128 Default CodeSet (@"A", @"B" or @"C")
    NSInteger mQrCorrectionLevelDefault;    // QRCode Erroc Correction Level Default (L:48, M:49, Q:50, H:51)
    NSInteger mPDF417OptionDefault;         // PDF417 Option Default (0:Standard or 1:Truncated)
    NSInteger mPDF417ColumnNumDefault;      // PDF417 Column Number Default (0-30)
    NSInteger mPDF417RowNumDefault;         // PDF417 Row Number Default (0, 3-90)
    NSInteger mPDF417CorrectionLevelDefault;// PDF417 Error Correction Level Default (48-53)
    NSInteger mPDF417MaxHeight;             // PDF417 MAX Height Size
    
    // Common variable
    NSInteger paperWidth;
    NSInteger fontSize;
    NSInteger fontType;
}

struct POSProperties{
    NSString * _Nullable mPropName; /*Properties name*/
    NSInteger mPropAccess; /*Properties access level*/
    NSInteger mPropValue; /*Properties value*/
    //TODO: declare all base properties here
};

// External Properties /////////////////////////////////////////////////////////
@property (weak, nonatomic, nullable) id <TECPOSPrinterStatusUpdateEventDelegate> StatusUpdateEventDelegate;

// External Methods ////////////////////////////////////////////////////////////
/// Open logical device which exist in current configuration devices.
/// @param logicalDeviceName Logical Device Name
- (NSInteger) open : (nonnull NSString *)logicalDeviceName;

/// Close opened logical device
- (NSInteger) close;

/// Claim logical device access by provided timing. -1 means infinite
/// @param timeout Timeout Value
- (NSInteger) claimDevice : (NSInteger)timeout;

/// Release claimed device
- (NSInteger) releaseDevice;

/// Configure setting value
- (NSInteger) configureSetting : (nonnull NSString *)name
                         Value : (nonnull NSString *)value;

/// Perform direct control to the device
/// @param command Direct IO Command index
/// @param data Inout Data Value
/// @param object Inout Data Value Array
- (NSInteger) directIo : (DirectIoCommands)command
                  Data : (nullable int *)data
                Object : (NSMutableArray<NSNumber *> * _Nullable * _Nullable)object;

/// Clear any buffered print data.
- (NSInteger) clearOutput;

/// Cut the Paper
/// @param percentage Cutting Percentage
- (NSInteger) cutPaper : (NSInteger)percentage;

/// Print any text and Escape Sequence Data
/// @param station Printer Station
/// @param data Printing Data
- (NSInteger) printNormal : (PrinterStation)station
                     Data : (nonnull NSString *)data;

/// Print the Barcode
/// @param station Printer Station
/// @param data Character string to be barcode
/// @param symbology Barcode symbol type
/// @param height Barcode height
/// @param width Barcode width
/// @param alignment Placement of the barcode. If the value is more than 0, the value means "start position "DOT" from left-most"
/// @param textPosition Placement of the readable character string
- (NSInteger) printBarcode : (PrinterStation)station
                      Data : (nonnull NSString *)data
                 Symbology : (PrinterBarcodeType)symbology
                    Height : (NSInteger)height
                     Width : (NSInteger)width
                 Alignment : (PrinterBarcodeAlignment)alignment
              TextPosition : (PrinterBarcodeTextPosition)textPosition;

/// Print the Image File
/// @param station Printer Station
/// @param filePath Image File Absolute Path
/// @param width Printing Image Width
/// @param alignment Placement of the Image
- (NSInteger) printBitmap : (PrinterStation)station
                 FilePath : (nonnull NSString *)filePath
                    Width : (NSInteger)width
                Alignment : (PrinterBitmapAlignment)alignment;

/// Print the Image Class
/// @param station Printer Station
/// @param bmp Image Class
/// @param width Printing Image Width
/// @param alignment Placement of the Image
- (NSInteger) printBitmap : (PrinterStation)station
                   Bitmap : (nonnull UIImage *)bmp
                    Width : (NSInteger)width
                Alignment : (PrinterBitmapAlignment)alignment;

/// Set the Image
/// @param bitmapNum Storing Number
/// @param station Printer Station
/// @param filePath Image File Absolute Path
/// @param width Printing Image Width
/// @param alignment Placement of the Image
- (NSInteger) setBitmap : (NSInteger)bitmapNum
                Station : (PrinterStation)station
               FileName : (nonnull NSString *)filePath
                  Width : (NSInteger)width
              Alignment : (PrinterBitmapAlignment)alignment;

/// Set the Image
/// @param bitmapNum Storing Number
/// @param station Printer Station
/// @param bmp Image Class
/// @param width Printing Image Width
/// @param alignment Placement of the Image
- (NSInteger) setBitmap : (NSInteger)bitmapNum
                Station : (PrinterStation)station
                 Bitmap : (nonnull UIImage *)bmp
                  Width : (NSInteger)width
              Alignment : (PrinterBitmapAlignment)alignment;

/// Transaction Printing
/// @param station Printer Station
/// @param control Transaction Control
- (NSInteger) transactionPrint : (PrinterStation)station
                       Control : (TransactionControl)control;


// Parameters Get/Set Methods //////////////////////////////////////////////////
/// Returns Opened Property
- (BOOL) getOpened;

/// Returns Claimed Property
- (BOOL) getClaimed;

/// Returns DeviceEnabled Property
- (BOOL) getDeviceEnabled;

/// Store the DeviceEnabled Property
/// @param deviceEnabled set parameter
- (NSInteger) setDeviceEnabled : (BOOL)deviceEnabled;

/// Returns PhysicalDeviceName Property
- (nonnull NSString *) getPhysicalDeviceName;

/// Return Extended Error Code
- (NSInteger) getErrorCodeExtended;

/// Returns CharacterSet Property
- (NSInteger) getCharacterSet;

/// Store the CharacterSet Property
/// @param characterSet set parameter
- (NSInteger) setCharacterSet : (NSInteger)characterSet;

/// Returns CharacterSetList Property
- (nonnull NSString *) getCharacterSetList;

/// Returns CoverOpen Property
- (BOOL) getCoverOpen;

/// Returns ErrorLevel Property
- (NSInteger) getErrorLevel;

/// Returns RecEmpty Property
- (BOOL) getRecEmpty;

/// Returns RecNearEnd Property
- (BOOL) getRecNearEnd;

/// Returns RecLineChars Property
- (NSInteger) getRecLineChars;

/// Store the RecLineChars Property
/// @param recLineChars set parameter
- (NSInteger) setRecLineChars : (NSInteger)recLineChars;

/// Returns RecLineCharsList Property
- (nonnull NSString *) getRecLineCharsList;

/// Returns RecLineHeight Property
- (NSInteger) getRecLineHeight;

/// Returns RecLineWidth Property
- (NSInteger) getRecLineWidth;

/// Returns RecLineSpacing Property
- (NSInteger) getRecLineSpacing;

/// Store the RecLineSpacing Property
/// @param recLineSpacing set parameter
- (NSInteger) setRecLineSpacing : (NSInteger)recLineSpacing;
@end
