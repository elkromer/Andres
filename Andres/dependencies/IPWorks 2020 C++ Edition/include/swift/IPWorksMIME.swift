
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum MimePartEncodings : Int32 {
  case pe7Bit = 0
  case peQuotedPrintable = 1
  case peBase64 = 2
  case pe8Bit = 3
  case peBinary = 4
  case peUUEncode = 5
}


public protocol IPWorksMIMEDelegateSwift {
  func onError(_ errorCode: Int32, _ description: String)
  func onHeader(_ partIndex: Int32, _ field: String, _ value: Data)
  func onProgress(_ percentDone: Int32)
}

public enum IPWorksMIMEError : Error {
  case Error(Int32, String)
}

public class IPWorksMIMESwift : NSObject, IPWorksMIMEDelegate {
  public var m_obj: IPWorksMIME
  var m_delegate: IPWorksMIMEDelegateSwift?

  override init() {
    self.m_obj = IPWorksMIME()
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

  public var delegate: IPWorksMIMEDelegateSwift? {
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

  public func onHeader(_ partIndex: Int32, _ field: String!, _ value: Data!) {
    if (m_delegate != nil) {
      m_delegate!.onHeader(partIndex, field, value)
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

  public var boundary: String {
    get {
      let ret: String? = String(m_obj.boundary)
      return unwrapNSString(ret)
    }
    set {
      m_obj.boundary = newValue as NSString
    }
  }

  public var contentType: String {
    get {
      let ret: String? = String(m_obj.contentType)
      return unwrapNSString(ret)
    }
    set {
      m_obj.contentType = newValue as NSString
    }
  }

  public var contentTypeAttr: String {
    get {
      let ret: String? = String(m_obj.contentTypeAttr)
      return unwrapNSString(ret)
    }
    set {
      m_obj.contentTypeAttr = newValue as NSString
    }
  }

  public var message: String {
    get {
      let ret: String? = String(m_obj.message)
      return unwrapNSString(ret)
    }
    set {
      m_obj.message = newValue as NSString
    }
  }

  public var messageB: Data {
    get {
      let ret: Data? = m_obj.messageB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.messageB = newValue as NSData
    }
  }

  public var messageHeaderCount: Int32 {
    get {
      return m_obj.messageHeaderCount
    }
    set {
      m_obj.messageHeaderCount = newValue
    }
  }

  public func messageHeaderField(messageHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageHeaderField(messageHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setMessageHeaderField(messageHeaderIndex: Int32, newMessageHeaderField: String) throws -> Void {
    m_obj.setMessageHeaderField(messageHeaderIndex, newMessageHeaderField)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func messageHeaderValue(messageHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageHeaderValue(messageHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setMessageHeaderValue(messageHeaderIndex: Int32, newMessageHeaderValue: String) throws -> Void {
    m_obj.setMessageHeaderValue(messageHeaderIndex, newMessageHeaderValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var messageHeadersString: String {
    get {
      let ret: String? = String(m_obj.messageHeadersString)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageHeadersString = newValue as NSString
    }
  }

  public var partCount: Int32 {
    get {
      return m_obj.partCount
    }
    set {
      m_obj.partCount = newValue
    }
  }

  public func partContentDisposition(partIdx: Int32) throws -> String {
    let ret: String? = m_obj.partContentDisposition(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPartContentDisposition(partIdx: Int32, newPartContentDisposition: String) throws -> Void {
    m_obj.setPartContentDisposition(partIdx, newPartContentDisposition)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partContentDispositionAttr(partIdx: Int32) throws -> String {
    let ret: String? = m_obj.partContentDispositionAttr(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPartContentDispositionAttr(partIdx: Int32, newPartContentDispositionAttr: String) throws -> Void {
    m_obj.setPartContentDispositionAttr(partIdx, newPartContentDispositionAttr)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partContentId(partIdx: Int32) throws -> String {
    let ret: String? = m_obj.partContentId(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPartContentId(partIdx: Int32, newPartContentId: String) throws -> Void {
    m_obj.setPartContentId(partIdx, newPartContentId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partContentType(partIdx: Int32) throws -> String {
    let ret: String? = m_obj.partContentType(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPartContentType(partIdx: Int32, newPartContentType: String) throws -> Void {
    m_obj.setPartContentType(partIdx, newPartContentType)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partContentTypeAttr(partIdx: Int32) throws -> String {
    let ret: String? = m_obj.partContentTypeAttr(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPartContentTypeAttr(partIdx: Int32, newPartContentTypeAttr: String) throws -> Void {
    m_obj.setPartContentTypeAttr(partIdx, newPartContentTypeAttr)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partDecodedFile(partIdx: Int32) throws -> String {
    let ret: String? = m_obj.partDecodedFile(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPartDecodedFile(partIdx: Int32, newPartDecodedFile: String) throws -> Void {
    m_obj.setPartDecodedFile(partIdx, newPartDecodedFile)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partDecodedString(partIdx: Int32) throws -> String {
    let ret: String? = m_obj.partDecodedString(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPartDecodedString(partIdx: Int32, newPartDecodedString: String) throws -> Void {
    m_obj.setPartDecodedString(partIdx, newPartDecodedString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partDecodedStringB(partIdx: Int32) throws -> Data {
    let ret: Data? = m_obj.partDecodedStringB(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapData(ret)
  }

  public func setPartDecodedStringB(partIdx: Int32, newPartDecodedString: Data) throws -> Void {
    m_obj.setPartDecodedStringB(partIdx, newPartDecodedString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partEncoding(partIdx: Int32) throws -> MimePartEncodings {
    let ret = MimePartEncodings(rawValue: m_obj.partEncoding(partIdx))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func setPartEncoding(partIdx: Int32, newPartEncoding: MimePartEncodings) throws -> Void {
    m_obj.setPartEncoding(partIdx, newPartEncoding.rawValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partFilename(partIdx: Int32) throws -> String {
    let ret: String? = m_obj.partFilename(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPartFilename(partIdx: Int32, newPartFilename: String) throws -> Void {
    m_obj.setPartFilename(partIdx, newPartFilename)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partHeaders(partIdx: Int32) throws -> String {
    let ret: String? = m_obj.partHeaders(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPartHeaders(partIdx: Int32, newPartHeaders: String) throws -> Void {
    m_obj.setPartHeaders(partIdx, newPartHeaders)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partName(partIdx: Int32) throws -> String {
    let ret: String? = m_obj.partName(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPartName(partIdx: Int32, newPartName: String) throws -> Void {
    m_obj.setPartName(partIdx, newPartName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func partSize(partIdx: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.partSize(partIdx)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func decodeFromFile() throws -> Void {
    m_obj.decodeFromFile()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func decodeFromString() throws -> Void {
    m_obj.decodeFromString()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func encodeToFile() throws -> Void {
    m_obj.encodeToFile()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func encodeToString() throws -> Void {
    m_obj.encodeToString()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func resetData() throws -> Void {
    m_obj.resetData()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMIMEError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}