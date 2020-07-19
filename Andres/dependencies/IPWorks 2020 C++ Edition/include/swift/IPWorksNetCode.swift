
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum NetcodeFormats : Int32 {
  case fmtUUEncode = 0
  case fmtBase64 = 1
  case fmtQP = 2
  case fmtURL = 3
  case fmtJIS = 4
  case fmtYEncode = 5
  case fmtMD5Hash = 6
  case fmtSHA1Hash = 7
  case fmtHex = 8
  case fmtHTML = 9
  case fmtHMAC = 10
  case fmtUTF8 = 11
  case fmtUTF7 = 12
  case fmtBase32 = 13
  case fmtBase64URL = 14
  case fmtSHA256Hash = 15
  case fmtPunycode = 16
}


public protocol IPWorksNetCodeDelegateSwift {
  func onError(_ errorCode: Int32, _ description: String)
  func onProgress(_ percentDone: Int32)
}

public enum IPWorksNetCodeError : Error {
  case Error(Int32, String)
}

public class IPWorksNetCodeSwift : NSObject, IPWorksNetCodeDelegate {
  public var m_obj: IPWorksNetCode
  var m_delegate: IPWorksNetCodeDelegateSwift?

  override init() {
    self.m_obj = IPWorksNetCode()
    self.m_delegate = nil
    super.init()
    self.m_obj.delegate = self
    self.m_obj.raiseNSException = false
  }

  deinit {
    self.m_delegate = nil
    self.m_obj.delegate = nil
  }

  public var lastError: String {
    get {
      let err: String? = m_obj.lastError()
      return unwrapNSString(err)
    }
  }
  
  public var lastErrorCode: Int32 {
    get {
      return m_obj.lastErrorCode()
    }
  }

  public var delegate: IPWorksNetCodeDelegateSwift? {
    get {
      return m_delegate
    }
    set {
      m_delegate = newValue
    }
  }

  private func unwrapNSString(_ str: String?) -> String {
    if (str != nil) {
      return str!
    } else {
      return ""
    }
  }

  private func unwrapNSDate(_ date: Date?) -> Date {
    if (date != nil) {
      return date!
    } else {
      return Date(timeIntervalSince1970: 0.0)
    }
  }

  private func unwrapData(_ data: Data?) -> Data {
    if (data != nil) {
      return data!
    } else {
      return Data()
    }
  }

  /* Events */

  public func onError(_ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(errorCode, description)
    }
  }

  public func onProgress(_ percentDone: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onProgress(percentDone)
    }
  }

  /* Properties */

  public var runtimeLicense: String {
    get {
      let ret: String? = String(m_obj.RuntimeLicense)
      return unwrapNSString(ret)  
    }
    set {
      m_obj.RuntimeLicense = newValue as NSString
    }
  }

  public var VERSION: String {
    get {
      let ret: String? = String(m_obj.VERSION)
      return unwrapNSString(ret)  
    }
  }

  public var decodedData: String {
    get {
      let ret: String? = String(m_obj.decodedData)
      return unwrapNSString(ret)
    }
    set {
      m_obj.decodedData = newValue as NSString
    }
  }

  public var decodedDataB: Data {
    get {
      let ret: Data? = m_obj.decodedDataB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.decodedDataB = newValue as NSData
    }
  }

  public var decodedFile: String {
    get {
      let ret: String? = String(m_obj.decodedFile)
      return unwrapNSString(ret)
    }
    set {
      m_obj.decodedFile = newValue as NSString
    }
  }

  public var encodedData: String {
    get {
      let ret: String? = String(m_obj.encodedData)
      return unwrapNSString(ret)
    }
    set {
      m_obj.encodedData = newValue as NSString
    }
  }

  public var encodedDataB: Data {
    get {
      let ret: Data? = m_obj.encodedDataB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.encodedDataB = newValue as NSData
    }
  }

  public var encodedFile: String {
    get {
      let ret: String? = String(m_obj.encodedFile)
      return unwrapNSString(ret)
    }
    set {
      m_obj.encodedFile = newValue as NSString
    }
  }

  public var fileCnt: Int32 {
    get {
      return m_obj.fileCnt
    }
  }

  public var fileName: String {
    get {
      let ret: String? = String(m_obj.fileName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.fileName = newValue as NSString
    }
  }

  public var format: NetcodeFormats {
    get {
      return NetcodeFormats(rawValue: m_obj.format)!
    }
    set {
      m_obj.format = newValue.rawValue
    }
  }

  public var mode: String {
    get {
      let ret: String? = String(m_obj.mode)
      return unwrapNSString(ret)
    }
    set {
      m_obj.mode = newValue as NSString
    }
  }

  public var overwrite: Bool {
    get {
      return m_obj.overwrite
    }
    set {
      m_obj.overwrite = newValue
    }
  }

  public var progressStep: Int32 {
    get {
      return m_obj.progressStep
    }
    set {
      m_obj.progressStep = newValue
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetCodeError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func decode() throws -> Void {
    m_obj.decode()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetCodeError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func encode_() throws -> Void {
    m_obj.encode()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetCodeError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetCodeError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func resetData() throws -> Void {
    m_obj.resetData()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetCodeError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}