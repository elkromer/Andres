
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation



public protocol IPWorksMCastDelegateSwift {
  func onDataIn(_ datagram: Data, _ sourceAddress: String, _ sourcePort: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onReadyToSend()
}

public enum IPWorksMCastError : Error {
  case Error(Int32, String)
}

public class IPWorksMCastSwift : NSObject, IPWorksMCastDelegate {
  public var m_obj: IPWorksMCast
  var m_delegate: IPWorksMCastDelegateSwift?

  override init() {
    self.m_obj = IPWorksMCast()
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

  public var delegate: IPWorksMCastDelegateSwift? {
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

  public func onDataIn(_ datagram: Data!, _ sourceAddress: String!, _ sourcePort: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onDataIn(datagram, sourceAddress, sourcePort)
    }
  }

  public func onError(_ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(errorCode, description)
    }
  }

  public func onReadyToSend() {
    if (m_delegate != nil) {
      m_delegate!.onReadyToSend()
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

  public var acceptData: Bool {
    get {
      return m_obj.acceptData
    }
    set {
      m_obj.acceptData = newValue
    }
  }

  public var active: Bool {
    get {
      return m_obj.active
    }
    set {
      m_obj.active = newValue
    }
  }

  public var dataToSend: String {
    get {
      let ret: String? = String(m_obj.dataToSend)
      return unwrapNSString(ret)
    }
    set {
      m_obj.dataToSend = newValue as NSString
    }
  }

  public var dataToSendB: Data {
    get {
      let ret: Data? = m_obj.dataToSendB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.dataToSendB = newValue as NSData
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

  public var localPort: Int32 {
    get {
      return m_obj.localPort
    }
    set {
      m_obj.localPort = newValue
    }
  }

  public var loopback: Bool {
    get {
      return m_obj.loopback
    }
    set {
      m_obj.loopback = newValue
    }
  }

  public var multicastGroup: String {
    get {
      let ret: String? = String(m_obj.multicastGroup)
      return unwrapNSString(ret)
    }
    set {
      m_obj.multicastGroup = newValue as NSString
    }
  }

  public var receiveInterface: String {
    get {
      let ret: String? = String(m_obj.receiveInterface)
      return unwrapNSString(ret)
    }
    set {
      m_obj.receiveInterface = newValue as NSString
    }
  }

  public var remoteHost: String {
    get {
      let ret: String? = String(m_obj.remoteHost)
      return unwrapNSString(ret)
    }
    set {
      m_obj.remoteHost = newValue as NSString
    }
  }

  public var remotePort: Int32 {
    get {
      return m_obj.remotePort
    }
    set {
      m_obj.remotePort = newValue
    }
  }

  public var sendInterface: String {
    get {
      let ret: String? = String(m_obj.sendInterface)
      return unwrapNSString(ret)
    }
    set {
      m_obj.sendInterface = newValue as NSString
    }
  }

  public var timeToLive: Int32 {
    get {
      return m_obj.timeToLive
    }
    set {
      m_obj.timeToLive = newValue
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMCastError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMCastError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMCastError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func send(_ text: Data) throws -> Void {
    m_obj.send(text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMCastError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}