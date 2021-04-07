//
//  TECPOSResource.h
//  TECPrtMobileSDK
//
//  Created by RSODM開 on 2019/11/06.
//  Copyright © 2019 RSODMF. All rights reserved.
//

/// POS Result Code Values
typedef NS_ENUM(NSInteger, PosError) {
    POS_SUCCESS         = 0,
    POS_E_CLOSED        = 101,
    POS_E_CLAIMED       = 102,
    POS_E_NOTCLAIMED    = 103,
    POS_E_NOSERVICE     = 104,
    POS_E_DISABLED      = 105,
    POS_E_ILLEGAL       = 106,
    POS_E_NOHARDWARE    = 107,
    POS_E_OFFLINE       = 108,
    POS_E_NOEXIST       = 109,
    POS_E_EXISTS        = 110,
    POS_E_FAILURE       = 111,
    POS_E_TIMEOUT       = 112,
    POS_E_BUSY          = 113,
    POS_E_EXTENDED      = 114,
    POS_E_DEPRECATED    = 115,
};

/// POS Extended Result Code Values
typedef NS_ENUM(NSInteger, PosErrorEx) {
    POS_NO_EXERR            = 0,
    POS_ESTATS_ERROR        = 280,
    POS_EFIRMWARE_BAD_FILE  = 281,
    POS_ESTATS_DEPENDENCY   = 282,
};

/// Direct IO Command
typedef NS_ENUM(NSInteger, DirectIoCommands) {
    TPTR_CMD_DIRECT_OUTPUT,         // Direct Output Data
    TPTR_CMD_DIRECT_DRAWER_OPEN,    // Kick the Cash Drawer
    TPTR_CMD_DIRECT_DRAWER_STATUS,  // Get Drawer Status
};

/// POS Printer Station Values
typedef NS_ENUM(NSInteger, PrinterStation) {
    PTR_S_RECEIPT,
    PTR_S_SLIP,
    PTR_S_JOURNAL,
};

/// POS Printer Barcode Alignment Values
typedef NS_ENUM(NSInteger, PrinterBarcodeAlignment) {
    PTR_BC_LEFT = -1,
    PTR_BC_CENTER = -2,
    PTR_BC_RIGHT = -3,
};

/// POS Printer Barcode text position Values
typedef NS_ENUM(NSInteger, PrinterBarcodeTextPosition) {
    PTR_BC_TEXT_NONE = 0,
    PTR_BC_TEXT_ABOVE = 1,
    PTR_BC_TEXT_BELOW = 2,
};

/// POS Printer Barcode type Values
typedef NS_ENUM(NSInteger, PrinterBarcodeType) {
    PTR_BCS_UPCA = 65,
    PTR_BCS_UPCE = 66,
    PTR_BCS_EAN8 = 68,
    PTR_BCS_EAN13 = 67,
    PTR_BCS_ITF = 70,
    PTR_BCS_Codabar = 71,
    PTR_BCS_Code39 = 69,
    PTR_BCS_Code93 = 72,
    PTR_BCS_Code128 = 73,
    PTR_BCS_Code128_Parsed = 74,    // m is same as Code128.
    PTR_BCS_GS1DATABAR = 75,
    PTR_BCS_GS1DATABAR_S = 173,
    PTR_BCS_GS1DATABAR_E = 78,
    PTR_BCS_GS1DATABAR_E_S = 176,
    PTR_BCS_PDF417 = 102,
    PTR_BCS_QRCODE = 103,
    PTR_BCS_UQRCODE = 104,
};

/// POS Printer Bitmap Alignment Values
typedef NS_ENUM(NSInteger, PrinterBitmapAlignment) {
    PTR_BM_LEFT = -1,
    PTR_BM_CENTER = -2,
    PTR_BM_RIGHT = -3,
};

/// POS Printer Bitmap Width Values
typedef NS_ENUM(NSInteger, PrinterBitmapWidth) {
    PTR_BM_ASIS = -11,
};

/// POS Printer Status Update Event Values
typedef NS_ENUM(NSInteger, PrinterStatusUpdate) {
    PTR_SUE_COVER_OPEN,
    PTR_SUE_COVER_OK,
    PTR_SUE_REC_EMPTY,
    PTR_SUE_REC_NEAREMPTY,
    PTR_SUE_REC_PAPEROK,
};

/// POS Printer Transaction Control
typedef NS_ENUM(NSInteger, TransactionControl) {
    PTR_TP_NORMAL,
    PTR_TP_TRANSACTION,
};

