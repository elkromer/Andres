
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation



public protocol IPWorksPingDelegateSwift {
  func onError(_ errorCode: Int32, _ description: String)
  func onResponse(_ requestId: Int32, _ responseSource: String, _ responseStatus: String, _ responseTime: Int32)
}

public enum IPWorksPingError : Error {
  case Error(Int32, String)
}

public class IPWorksPingSwift : NSObject, IPWorksPingDelegate {
  public var m_obj: IPWorksPing
  var m_delegate: IPWorksPingDelegateSwift?

  override init() {
    self.m_obj = IPWorksPing()
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

  public var delegate: IPWorksPingDelegateSwift? {
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

  public func onResponse(_ requestId: Int32, _ responseSource: String!, _ responseStatus: String!, _ responseTime: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onResponse(requestId, responseSource, responseStatus, responseTime)
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

  public var active: Bool {
    get {
      return m_obj.active
    }
    set {
      m_obj.active = newValue
    }
  }

  public var idle: Bool {
    get {
      return m_obj.idle
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

  public var packetSize: Int32 {
    get {
      return m_obj.packetSize
    }
    set {
      m_obj.packetSize = newValue
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

  public var requestId: Int32 {
    get {
      return m_obj.requestId
    }
  }

  public var responseSource: String {
    get {
      let ret: String? = String(m_obj.responseSource)
      return unwrapNSString(ret)
    }
  }

  public var responseTime: Int32 {
    get {
      return m_obj.responseTime
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

  public var typeOfService: Int32 {
    get {
      return m_obj.typeOfService
    }
    set {
      m_obj.typeOfService = newValue
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPingError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPingError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPingError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func pingHost(_ host: String) throws -> Void {
    m_obj.pingHost(host)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPingError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPingError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func wakeOnLAN(_ remoteHost: String, _ MACAddress: String) throws -> Void {
    m_obj.wakeOnLAN(remoteHost, MACAddress)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPingError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}