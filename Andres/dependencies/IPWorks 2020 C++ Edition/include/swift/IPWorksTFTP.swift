
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation



public protocol IPWorksTFTPDelegateSwift {
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onStartTransfer(_ direction: Int32)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data)
}

public enum IPWorksTFTPError : Error {
  case Error(Int32, String)
}

public class IPWorksTFTPSwift : NSObject, IPWorksTFTPDelegate {
  public var m_obj: IPWorksTFTP
  var m_delegate: IPWorksTFTPDelegateSwift?

  override init() {
    self.m_obj = IPWorksTFTP()
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

  public var delegate: IPWorksTFTPDelegateSwift? {
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

  public func onEndTransfer(_ direction: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onEndTransfer(direction)
    }
  }

  public func onError(_ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(errorCode, description)
    }
  }

  public func onStartTransfer(_ direction: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onStartTransfer(direction)
    }
  }

  public func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data!) {
    if (m_delegate != nil) {
      m_delegate!.onTransfer(direction, bytesTransferred, percentDone, text)
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

  public var idle: Bool {
    get {
      return m_obj.idle
    }
  }

  public var localFile: String {
    get {
      let ret: String? = String(m_obj.localFile)
      return unwrapNSString(ret)
    }
    set {
      m_obj.localFile = newValue as NSString
    }
  }

  public var localHost: String {
    get {
      let ret: String? = String(m_obj.localHost)
      return unwrapNSString(ret)
    }
    set {
      m_obj.localHost = newValue as NSString
    }
  }

  public var maxRetransmits: Int32 {
    get {
      return m_obj.maxRetransmits
    }
    set {
      m_obj.maxRetransmits = newValue
    }
  }

  public var remoteFile: String {
    get {
      let ret: String? = String(m_obj.remoteFile)
      return unwrapNSString(ret)
    }
    set {
      m_obj.remoteFile = newValue as NSString
    }
  }

  public var retransmitTimeout: Int32 {
    get {
      return m_obj.retransmitTimeout
    }
    set {
      m_obj.retransmitTimeout = newValue
    }
  }

  public var TFTPPort: Int32 {
    get {
      return m_obj.TFTPPort
    }
    set {
      m_obj.TFTPPort = newValue
    }
  }

  public var TFTPServer: String {
    get {
      let ret: String? = String(m_obj.TFTPServer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.TFTPServer = newValue as NSString
    }
  }

  public var timeout: Int32 {
    get {
      return m_obj.timeout
    }
    set {
      m_obj.timeout = newValue
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getFile() throws -> Void {
    m_obj.getFile()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putFile() throws -> Void {
    m_obj.putFile()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}