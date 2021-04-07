//
//  StringExtension.swift
//  SampleAppForTECPrtMobileSDK
//
//  Created by RSODM開 on 2019/11/07.
//  Copyright © 2019 RSODMF. All rights reserved.
//

import Foundation

// MARK: - String Extension
extension String {
    /// Check the string is match or not using Regular Expression
    ///
    /// - Parameters:
    ///   - pattern: Regular Expression Pattern
    ///   - options: Regular Expression Option
    /// - Returns: Match or Not Match
    public func matches (_ pattern: String, options: NSRegularExpression.Options = []) -> Bool {
        guard let regex = try? NSRegularExpression(pattern: pattern, options: options) else {
            return false
        }
        let matches = regex.matches(in: self, options: [], range: NSRange(location: 0, length: (self as NSString).length))
        return 0 < matches.count
    }
}
