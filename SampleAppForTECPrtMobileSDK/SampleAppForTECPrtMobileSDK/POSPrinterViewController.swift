//
//  POSPrinterViewController.swift
//  SampleAppForTECPrtMobileSDK
//
//  Created by TOSHIBA TEC Singapore Pte. Ltd on 2019/11/07.
//  Copyright © 2019 TOSHIBA TEC Singapore Pte. Ltd. All rights reserved.
//

import UIKit

class POSPrinterViewController : UIViewController , UINavigationControllerDelegate, UIImagePickerControllerDelegate {
    // External Values /////////////////////////////////////////////////////////
    public var logicalDeviceName: String!
    public var ipAddress: String!
    public var TCP: String!
    public var UDP: String!
    public var printer: TECPOSPrinter!
    
    // GUI Component Values ////////////////////////////////////////////////////
    @IBOutlet weak var statusUpdateLabel: UILabel!
    @IBOutlet weak var printAsciiButton: UIButton!
    @IBOutlet weak var printHButton: UIButton!
    @IBOutlet weak var printBitmapButton: UIButton!
    @IBOutlet weak var setPrintBitmapButton: UIButton!
    @IBOutlet weak var printBarcodeButton: UIButton!
    @IBOutlet weak var feedCutButton: UIButton!
    @IBOutlet weak var sampleReceiptButton: UIButton!
    @IBOutlet weak var kickDrawerButton: UIButton!
    @IBOutlet weak var getDrawerStatusButton: UIButton!
    
    @IBOutlet weak var myImageView: UIImageView!
    //@IBOutlet weak var myImageview: UIImageView!
    
    // Internal Values /////////////////////////////////////////////////////////
    let imagePicker = UIImagePickerController()
    var imagePickedBlock: ((UIImage) -> Void)?
    
    var isSetBitmap = true
    
    let PTR_BM_ASIS = -11 // One pixel per printer dot (bitmap width)
    
    // GUI Common Methods //////////////////////////////////////////////////////
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        printer.statusUpdateEventDelegate = self
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
		if(isMovingFromParent){
			// Close
			while true {
				guard !popUpError(errorCode: printer.close()) else { break }
				break
			}
		}
    }
    
    @IBAction func buttonsClick(_ sender: UIButton) {
        if sender == printAsciiButton {
            printAscii()
        } else if sender == printHButton {
            printHCharacters()
        } else if sender == printBitmapButton {
            printBitmap()
        } else if sender == setPrintBitmapButton {
            setAndPrintBitmap()
        } else if sender == printBarcodeButton {
            printBarcode()
        } else if sender == feedCutButton {
            feed()
            cutPaper()
        } else if sender == sampleReceiptButton {
            sampleReceipt()
            feed()
            cutPaper()
        } else if sender == kickDrawerButton {
            kickDrawer()
        } else if sender == getDrawerStatusButton {
            getDrawerStatus()
        }
    }
    
    // Internal Methods ////////////////////////////////////////////////////////
    /// Print the All ASCII Characters. (0x20 - 0x7E) and Line Feed.
    private func printAscii() {
        // LF + (All ASCII Characters) + LF
        let data = "\n!\"#$%&'()*+,-./ 0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[¥]^_abcdefghijklmnopqrstuvwxyz{|}~\n"
        _ = popUpError(errorCode: printer.printNormal(.PTR_S_RECEIPT, data:data))
    }
    
    /// Print 'H' characters for one Line
    private func printHCharacters() {
        // Create One Line H characters.
        let chars = printer.getRecLineChars()
        guard chars != nil else { return }
        var hLine = ""
        for _ in 0..<chars {
            hLine.append("H")
        }
        hLine.append("\n")
        
        // Print out
        _ = popUpError(errorCode: printer.printNormal(.PTR_S_RECEIPT, data: hLine))
    }
    
    private func printBitmap() {
        isSetBitmap = false;
        if UIImagePickerController.isSourceTypeAvailable(.photoLibrary){
            imagePicker.delegate = self
            imagePicker.sourceType = .photoLibrary
            imagePicker.allowsEditing = false
            
            present(imagePicker, animated: true, completion: nil)
        }
    }
    
    private func setAndPrintBitmap() {
        isSetBitmap = true;
        if UIImagePickerController.isSourceTypeAvailable(.photoLibrary){
            imagePicker.delegate = self
            imagePicker.sourceType = .photoLibrary
            imagePicker.allowsEditing = false
            
            present(imagePicker, animated: true, completion: nil)
        }
    }
    
    private func printBarcode() {
        _ = popUpError(errorCode: printer.printBarcode(.PTR_S_RECEIPT, data: "12345678901", symbology:.PTR_BCS_UPCA, height: 140, width: 400, alignment: .PTR_BC_CENTER, textPosition: .PTR_BC_TEXT_BELOW))
    }
    
    private func feed() {
        _ = popUpError(errorCode: printer.printNormal(.PTR_S_RECEIPT, data: "\u{001b}|5lF"))  //use escape sequence to feed line
    }
    
    /// Cut the Paper
    private func cutPaper() {
        _ = popUpError(errorCode: printer.cutPaper(100))
        
        // In the case of DirectIo method with Cut Command
         //var sendCmd : NSMutableArray? = NSMutableArray(array: [0x1B, 0x69])
         //_ = popUpError(errorCode: printer.directIo(.TPTR_CMD_DIRECT_OUTPUT, data: nil, object: &sendCmd))
    }
    
    /// Print Sample Receipt
    private func sampleReceipt() {
        printer.transactionPrint(.PTR_S_RECEIPT, control: .PTR_TP_TRANSACTION)
        
        // Set bitmap
        let bitmap = UIImage(named: "logo")
        _ = popUpError(errorCode: printer.setBitmap(1, station: .PTR_S_RECEIPT, bitmap: bitmap!, width: 500, alignment: .PTR_BM_CENTER))
        
        // Print set bitmap
        _ = popUpError(errorCode: printer.printNormal(.PTR_S_RECEIPT, data:"\u{001b}|1B"))
        
        // Print receipt
        var message = "Receipt No: 26500\n\n" + "5 x Item1        @ $5.00            $25.00\n"
        for x in 1...8 {
            message += "    Item" + String(x+1) + "                           $10.00\n"
        }
        message += "\u{001b}|3C\u{001b}|1uC                         TOTAL :  $ 125.00\n\n" + "\u{001b}|N************************ Receipt No: 26500\n" + "\u{001b}|4C\u{001b}|cAThank You!\n\n"
        
        _ = popUpError(errorCode: printer.printNormal(.PTR_S_RECEIPT, data:message))

        // Print barcode
        _ = popUpError(errorCode: printer.printBarcode(.PTR_S_RECEIPT, data: "1234567890128", symbology:.PTR_BCS_EAN13, height: 160, width: 200, alignment: .PTR_BC_CENTER, textPosition: .PTR_BC_TEXT_NONE))
        
        printer.transactionPrint(.PTR_S_RECEIPT, control: .PTR_TP_NORMAL)
    }
    
    /// Kick the Drawer using DirectIo method
    private func kickDrawer() {
         _ = popUpError(errorCode: printer.directIo(.TPTR_CMD_DIRECT_DRAWER_OPEN, data: nil, object: nil))
    }
    
    /// Get current Drawer Status using DirectIo method
    private func getDrawerStatus() {
        var drawerStatus: Int32 = 10
        _ = popUpError(errorCode: printer.directIo(.TPTR_CMD_DIRECT_DRAWER_STATUS, data: &drawerStatus, object: nil))
        
        // 1: Drawer Closed, 0: Drawer Opened.
        if drawerStatus == 0 || drawerStatus == 1 {
            let alert = UIAlertController(title: "Drawer Status",
                                          message: "Drawer \(drawerStatus == 0 ? "Opened" : "Closed")",
                                          preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .cancel, handler: nil))
            present(alert, animated: true)
        }
    }
        
    /// Popup Error Message if need
    /// - Parameter errorCode: Error Code
    private func popUpError(errorCode: Int?) -> Bool {
        guard errorCode != nil else {
            return true
        }
        guard errorCode != PosError.POS_SUCCESS.rawValue else {
            return true
        }

        let eCodeStr =
                errorCode == PosError.POS_E_CLOSED.rawValue ? "POS_E_CLOSED, Error Code: " + String(PosError.POS_E_CLOSED.rawValue) :
                errorCode == PosError.POS_E_CLAIMED.rawValue ? "POS_E_CLAIMED, Error Code: " + String(PosError.POS_E_CLAIMED.rawValue) :
                errorCode == PosError.POS_E_NOTCLAIMED.rawValue ? "POS_E_NOTCLAIMED, Error Code: " + String(PosError.POS_E_NOTCLAIMED.rawValue) :
                errorCode == PosError.POS_E_NOSERVICE.rawValue ? "POS_E_NOSERVICE, Error Code: " + String(PosError.POS_E_NOSERVICE.rawValue) :
                errorCode == PosError.POS_E_DISABLED.rawValue ? "POS_E_DISABLED, Error Code: " + String(PosError.POS_E_DISABLED.rawValue) :
                errorCode == PosError.POS_E_ILLEGAL.rawValue ? "POS_E_ILLEGAL, Error Code: " + String(PosError.POS_E_ILLEGAL.rawValue) :
                errorCode == PosError.POS_E_NOHARDWARE.rawValue ? "POS_E_NOHARDWARE, Error Code: " + String(PosError.POS_E_NOHARDWARE.rawValue) :
                errorCode == PosError.POS_E_OFFLINE.rawValue ? "POS_E_OFFLINE, Error Code: " + String(PosError.POS_E_OFFLINE.rawValue) :
                errorCode == PosError.POS_E_NOEXIST.rawValue ? "POS_E_NOEXIST, Error Code: " + String(PosError.POS_E_NOEXIST.rawValue) :
                errorCode == PosError.POS_E_EXISTS.rawValue ? "POS_E_EXISTS, Error Code: " + String(PosError.POS_E_EXISTS.rawValue) :
                errorCode == PosError.POS_E_FAILURE.rawValue ? "POS_E_FAILURE, Error Code: " + String(PosError.POS_E_FAILURE.rawValue) :
                errorCode == PosError.POS_E_TIMEOUT.rawValue ? "POS_E_TIMEOUT, Error Code: " + String(PosError.POS_E_TIMEOUT.rawValue) :
                errorCode == PosError.POS_E_BUSY.rawValue ? "POS_E_BUSY, Error Code: " + String(PosError.POS_E_BUSY.rawValue) :
                errorCode == PosError.POS_E_EXTENDED.rawValue ? "POS_E_EXTENDED, Error Code: " + String(PosError.POS_E_EXTENDED.rawValue) :
                errorCode == PosError.POS_E_DEPRECATED.rawValue ? "POS_E_DEPRECATED" : String(format: "Unknown: %d", errorCode!)
        
        let alert = UIAlertController(title: "PosException",
                                      message: eCodeStr,
                                      preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "OK", style: .cancel, handler: nil))
        present(alert, animated: true)
        return false
    }
                            
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {

        //test
        let imgUrl = info[UIImagePickerController.InfoKey.imageURL] as? URL
        let imgName = imgUrl!.lastPathComponent
       
        // Copy the selected image to application folder
        let fileManager = FileManager.default
        let documentsPath = fileManager.urls(for: .documentDirectory, in: .userDomainMask).first
        let imagePath = documentsPath?.appendingPathComponent(imgName)
        
        // Extract image from picker and save it
        if let pickedImage = info[UIImagePickerController.InfoKey.originalImage] as? UIImage {
            let imageData = pickedImage.jpegData(compressionQuality: 0.75)
            try! imageData?.write(to: imagePath!)
        }
            
        // Check whether path is exist
        if ((imagePath!.isFileURL) && (try! imagePath!.checkResourceIsReachable()))
        {
            print("File exists")
        } else {
            print("File not found")
        }
        
        // Print out
        dismiss(animated: true)
        
        if(isSetBitmap == false){
            // Print bitmap
            _ = popUpError(errorCode: printer.printBitmap(.PTR_S_RECEIPT, filePath: imagePath!.absoluteString, width: 300, alignment: .PTR_BM_CENTER))
            let coverOpenStatus = printer.getCoverOpen();
            let claimStatus = printer.getClaimed();
            NSLog("after print image Data, coverOpenStatus = %d, claimStatus = %d ", coverOpenStatus, claimStatus);
        }else{
            // Set bitmap and print the preloaded bitmap (set on bitmap no:1)
            printer.transactionPrint(.PTR_S_RECEIPT, control: .PTR_TP_TRANSACTION)
            _ = popUpError(errorCode: printer.setBitmap(1, station: .PTR_S_RECEIPT, fileName: imagePath!.absoluteString, width: 300, alignment: .PTR_BM_CENTER))
            _ = popUpError(errorCode: printer.printNormal(.PTR_S_RECEIPT, data:"\u{001b}|1B"))
            printer.transactionPrint(.PTR_S_RECEIPT, control: .PTR_TP_NORMAL)
        }
        
        print(imagePath!.absoluteString)
    }

    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        dismiss(animated: true, completion: nil)
    }
    
    func getDocumentsDirectory() -> URL {
        let documentsDirectory = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!
        let dataPath = documentsDirectory.appendingPathComponent("FolderName")
        
        do{
            try FileManager.default.createDirectory(atPath: dataPath.path, withIntermediateDirectories: true, attributes: nil)
        }catch let error as NSError{
            print("Error creating directory: \(error.localizedDescription)")
        }
        return dataPath
    }
}

// Status Update Event Callback ////////////////////////////////////////////////
extension POSPrinterViewController: TECPOSPrinterStatusUpdateEventDelegate {
    func posStatusUpdateEvent(_ status: Int, message: String) {
        var str = "Printer Status: "
        
        if(printer.getCoverOpen() == true){
            str += "Cover Open, "
        } else {
            str += "Cover Close, "
        }

        if(printer.getRecEmpty() == true){
            str += "Receipt End"
        } else if(printer.getRecNearEnd() == true){
            str += "Receipt Near End"
        } else {
            str += "Receipt OK"
        }
        
        statusUpdateLabel.text = str
        let coverOpenStatus = printer.getCoverOpen();
        let claimStatus = printer.getClaimed();
        NSLog("status change delegate call back, coverOpenStatus = %d, claimStatus = %d ", coverOpenStatus, claimStatus);
    }
}
