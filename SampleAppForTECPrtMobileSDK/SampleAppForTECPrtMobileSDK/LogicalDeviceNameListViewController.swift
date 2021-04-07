//
//  LogicalDeviceNameListViewController.swift
//  SampleAppForTECPrtMobileSDK
//
//  Created by TOSHIBA TEC Singapore Pte. Ltd on 2019/11/07.
//  Copyright © 2019 TOSHIBA TEC Singapore Pte. Ltd. All rights reserved.
//

import UIKit

class LogicalDeviceNameListViewController : UIViewController, UITextFieldDelegate {
    public enum CallClass {
        case TRSTP1X
        case TRSTP2X
    }
    
    // GUI Component Values ////////////////////////////////////////////////////
    @IBOutlet weak var configurationFileTextField: UITextField!
    @IBOutlet weak var ipAddressTextField: UITextField!
    @IBOutlet weak var TCPTextField: UITextField!
    @IBOutlet weak var UDPTextField: UITextField!
    @IBOutlet weak var configuredDeviceTableView: UITableView!
    var pickerView: UIPickerView!
    @IBOutlet weak var manualSwitch: UISwitch!
    @IBOutlet weak var ipAddressLabel: UILabel!
    @IBOutlet weak var TCPLabel: UILabel!
    @IBOutlet weak var UDPLabel: UILabel!
    
    // Internal Values /////////////////////////////////////////////////////////
    var fileList: [String]! = []
    var deviceList: [ConfiguredDevice] = []
    
    // GUI Common Methods //////////////////////////////////////////////////////
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Initialize the Log Level
        TECPOSDevice.setLogLevel(0x3F)  // All Log without Debug
        
        // Initialize the Log File. If set nil, Output message as the XCode Debug Message.
        TECPOSDevice.setLogFilePath(FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!.appendingPathComponent("TECPrtMobileSDKLog.txt").absoluteString)
                
        // Create Picker View for File List
        pickerView = UIPickerView()
        pickerView.delegate = self
        pickerView.dataSource = self
        
        // Create ToolBar for File List Picker
        let toolbar = UIToolbar(frame: CGRect(x: 0, y: 0, width: 0, height: 40))
        let doneItem = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(done))
        toolbar.setItems([doneItem], animated: true)
        
        // Add ToolBar and PickerView
        configurationFileTextField.inputView = pickerView
        configurationFileTextField.inputAccessoryView = toolbar
        
        // Add SDK Version
        navigationItem.title = "SDK Version " + TECPOSDevice.getVersion()
        
        // Add text field for ip address
        ipAddressTextField.delegate = self
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        // List the file
        fileList = list(FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!, extensions: ["xml"])
        fileList.insert("InternalSample.xml", at: 0)
    }
    
    @objc func done() {
        configurationFileTextField.text = fileList[pickerView.selectedRow(inComponent: 0)]
        configurationFileTextField.endEditing(true)
        
        // Update the TableView
        loadConfigurationFile()
        configuredDeviceTableView.reloadData()
    }

    // Function to enable or disable manual device configuration part
    private func enabled(isOn: Bool) {
        ipAddressLabel.isEnabled = isOn
        TCPLabel.isEnabled = isOn
        UDPLabel.isEnabled = isOn
        ipAddressTextField.isEnabled = isOn
        TCPTextField.isEnabled = isOn
        UDPTextField.isEnabled = isOn
    }

    // To handle manual device configuration.
    @IBAction func manualSwitch(_ sender: Any) {
        if manualSwitch.isOn == true{
            enabled(isOn: true)
            configurationFileTextField.text = ""
            // Add default value to display the 2 printer logical name
            deviceList.removeAll()
            deviceList.append(ConfiguredDevice(deviceName: "TRST-P1XL", logicalName: "TRSTP1XL", description: "TRST-P1X LAN Printer", ipAddress: ipAddressTextField.text ?? "", tcpPort: Int(TCPTextField?.text ?? "9100") ?? 9100, udpPort: Int(UDPTextField.text ?? "3000") ?? 3000))
            deviceList.append(ConfiguredDevice(deviceName: "TRST-P2XL", logicalName: "TRSTP2XL", description: "TRST-P2X LAN Printer", ipAddress: ipAddressTextField.text ?? "192.168.1.99", tcpPort: Int(TCPTextField?.text ?? "9100") ?? 9100, udpPort: Int(UDPTextField.text ?? "3000") ?? 3000))
            configuredDeviceTableView.reloadData()
        } else {
            enabled(isOn: false)
            if configurationFileTextField.text == "" {  // If manual is disabled and no xml file browsed
                deviceList.removeAll()                  // Empty table view
                configuredDeviceTableView.reloadData()
            }
        }
    }
    
    // Hide keyboard after pressing whitespace
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.view.endEditing(true)
    }
    
    // Internal Methods ////////////////////////////////////////////////////////
    private func loadConfigurationFile() {
        var filePath = ""
        if configurationFileTextField.text == "InternalSample.xml" {
            // Get Internal File
            filePath = Bundle.main.path(forResource: "InternalSample", ofType: "xml")!
            // Disable Manual Switch
            manualSwitch.isOn = false
            enabled(isOn: false)
        } else {
            filePath = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!.appendingPathComponent(configurationFileTextField.text!).absoluteString
        }
        
        TECPOSDevice.loadConfigurationFile(filePath)
        deviceList = TECPOSDevice.configuredDeviceList as! [ConfiguredDevice]
    }
    
    /// Returns the File List in specified folder
    ///
    /// - Parameters:
    ///   - url: Folder URL
    ///   - extensions: Extension Filter List. If the file extension includes in this list, the returns list has this.
    /// - Returns: File List
    private func list(_ url: URL, extensions: [String]?) -> [String] {
        // Get All File Name List
        var allFiles: [String] = []
        do {
            try allFiles = FileManager.default.contentsOfDirectory(atPath: url.path)
        } catch let error {
            print("list: " + error.localizedDescription)
            return []
        }
        
        // Filtering using extension List
        var files: [String] = []
        if extensions == nil || extensions!.isEmpty {
            return allFiles
        }
        for fileName in allFiles {
            for ext in extensions! {
                if fileName.lowercased().matches("\(ext)$") {
                    files.append(fileName)
                    break
                }
            }
        }
        return files
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
    
    /// Show POSPrinter ViewController with
    /// - Parameters:
    ///   - indexPath: Selected Item in list
    ///   - callTo: POSPrinter Type.
    private func executePosSDK(indexPath: IndexPath, callTo: CallClass) {
        // Move to next View
        let view = storyboard?.instantiateViewController(withIdentifier: "POSPrinterViewController") as! POSPrinterViewController
        view.logicalDeviceName = deviceList[indexPath.row].logicalName
        if configurationFileTextField.text != "" {  // For xml file
            view.ipAddress  = deviceList[indexPath.row].ipAddress
            view.TCP        = String(deviceList[indexPath.row].tcpPort)
            view.UDP        = String(deviceList[indexPath.row].udpPort)
            
        } else {    // For manual configuration
            view.ipAddress = ipAddressTextField.text
            view.TCP = TCPTextField.text
            view.UDP = UDPTextField.text
        }
        
        var printer: TECPOSPrinter
        if callTo == .TRSTP1X {
            printer = TRSTP1XPrinter()
        } else {
            printer = TRSTP2XPrinter()
        }
        
        // Perform Open
        if ((configurationFileTextField.text != "") && (manualSwitch.isOn == false)){
            _ = popUpError(errorCode: printer.open(deviceList[indexPath.row].logicalName))
        }else{
            _ = popUpError(errorCode: printer.open("LAN;"+view.ipAddress+";"+view.TCP+";"+view.UDP))
        }
//        let coverOpenStatus = printer.getCoverOpen();
//        let claimStatus = printer.getClaimed();
//        NSLog("before claim device, coverOpenStatus = %d, claimStatus = %d ", coverOpenStatus, claimStatus);
        // Perform Claim and DeviceEnabled
        if (popUpError(errorCode: printer.claimDevice(1000)) == true  && popUpError(errorCode: printer.setDeviceEnabled(true))) == true{
            view.printer = printer
            navigationController?.pushViewController(view, animated: true)
            let coverOpenStatus = printer.getCoverOpen();
            let claimStatus = printer.getClaimed();
            NSLog("after claim device, coverOpenStatus = %d, claimStatus = %d ", coverOpenStatus, claimStatus);
        }
    }
}

/// Configuration File List Picker
extension LogicalDeviceNameListViewController : UIPickerViewDelegate, UIPickerViewDataSource {
    /// [Necessary] Returns Row count
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    /// [Necessary] Returns Item count in this component
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return fileList.count
    }
    
    /// [Optional] Returns Item value
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return fileList[row]
    }
    
    /// [Optional] Select any item
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        configurationFileTextField.text = fileList[row]
    }
}

/// Device List in the Configuration File
extension LogicalDeviceNameListViewController : UITableViewDelegate, UITableViewDataSource {
    /// [Necessary] Returns Row Count in this section
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return deviceList.count
    }
    
    /// [Necessary] Returns Cell Data
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        // Get Prototype Cell
        let prototypeCell = tableView.dequeueReusableCell(withIdentifier: "LogicalNameTableCell")
        let bgView = prototypeCell?.viewWithTag(1)
        let label = prototypeCell?.viewWithTag(2) as! UILabel
        
        // Set Shadow
        bgView?.layer.shadowColor = UIColor.darkGray.cgColor
        bgView?.layer.shadowOffset = CGSize(width: 1.0, height: 3.0)
        bgView?.layer.shadowOpacity = 1.0
        bgView?.layer.masksToBounds = false
        
        // Update Label
        let dev = deviceList[indexPath.row]
        if configurationFileTextField.text != "" {  // xml file
            label.text = dev.logicalName + "\n" + String(format: "%@, tcp=%d, udp=%d", dev.ipAddress, dev.tcpPort, dev.udpPort)
        } else {                                    // manual device configuration
            label.text = dev.logicalName
        }
        return prototypeCell!
    }
    
    /// [Optional] Returns the cell height
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 80
    }
    
    /// [Optional] Selects the cell
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        // Set selected printer to their respective class (TRSTP1 -> TRSTP1X) or (TRSTP2 -> TRSTP2X)
        // Logical name of the printer
        let logicalName = deviceList[indexPath.row].logicalName
        // For TRSTP1 printer
        if logicalName.contains("TRSTP1") {
            executePosSDK(indexPath: indexPath, callTo: .TRSTP1X)
        } else {    // For TRSTP2 printer
            executePosSDK(indexPath: indexPath, callTo: .TRSTP2X)
        }
        tableView.deselectRow(at: indexPath, animated: true)
    }
}
