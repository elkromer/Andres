
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation



public protocol IPWorksICMPPortDelegateSwift {
  func onDataIn(_ messageType: Int32, _ messageSubType: Int32, _ messageData: Data, _ checksum: Int32, _ sourceAddress: String)
  func onError(_ errorCode: Int32, _ description: String)
  func onReadyToSend()
}

public enum IPWorksICMPPortError : Error {
  case Error(Int32, String)
}

public class IPWorksICMPPortSwift : NSObject, IPWorksICMPPortDelegate {
  public var m_obj: IPWorksICMPPort
  var m_delegate: IPWorksICMPPortDelegateSwift?

  override init() {
    self.m_obj = IPWorksICMPPort()
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

  public var delegate: IPWorksICMPPortDelegateSwift? {
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

  public func onDataIn(_ messageType: Int32, _ messageSubType: Int32, _ messageData: Data!, _ checksum: Int32, _ sourceAddress: String!) {
    if (m_delegate != nil) {
      m_delegate!.onDataIn(messageType, messageSubType, messageData, checksum, sourceAddress)
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

  public var dontRoute: Bool {
    get {
      return m_obj.dontRoute
    }
    set {
      m_obj.dontRoute = newValue
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

  public var messageSubType: Int32 {
    get {
      return m_obj.messageSubType
    }
    set {
      m_obj.messageSubType = newValue
    }
  }

  public var messageType: Int32 {
    get {
      return m_obj.messageType
    }
    set {
      m_obj.messageType = newValue
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

  public var timeout: Int32 {
    get {
      return m_obj.timeout
    }
    set {
      m_obj.timeout = newValue
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksICMPPortError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksICMPPortError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksICMPPortError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func send(_ text: Data) throws -> Void {
    m_obj.send(text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksICMPPortError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}