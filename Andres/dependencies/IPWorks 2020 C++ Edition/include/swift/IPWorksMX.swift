
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation



public protocol IPWorksMXDelegateSwift {
  func onError(_ errorCode: Int32, _ description: String)
  func onResponse(_ requestId: Int32, _ domain: String, _ mailServer: String, _ precedence: Int32, _ timeToLive: Int32, _ statusCode: Int32, _ description: String, _ authoritative: Bool)
}

public enum IPWorksMXError : Error {
  case Error(Int32, String)
}

public class IPWorksMXSwift : NSObject, IPWorksMXDelegate {
  public var m_obj: IPWorksMX
  var m_delegate: IPWorksMXDelegateSwift?

  override init() {
    self.m_obj = IPWorksMX()
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

  public var delegate: IPWorksMXDelegateSwift? {
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

  public func onResponse(_ requestId: Int32, _ domain: String!, _ mailServer: String!, _ precedence: Int32, _ timeToLive: Int32, _ statusCode: Int32, _ description: String!, _ authoritative: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onResponse(requestId, domain, mailServer, precedence, timeToLive, statusCode, description, authoritative)
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

  public var DNSPort: Int32 {
    get {
      return m_obj.DNSPort
    }
    set {
      m_obj.DNSPort = newValue
    }
  }

  public var DNSServer: String {
    get {
      let ret: String? = String(m_obj.DNSServer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.DNSServer = newValue as NSString
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

  public var mailServer: String {
    get {
      let ret: String? = String(m_obj.mailServer)
      return unwrapNSString(ret)
    }
  }

  public var requestId: Int32 {
    get {
      return m_obj.requestId
    }
    set {
      m_obj.requestId = newValue
    }
  }

  public var status: String {
    get {
      let ret: String? = String(m_obj.status)
      return unwrapNSString(ret)
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMXError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMXError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMXError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMXError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func resolve(_ emailAddress: String) throws -> Void {
    m_obj.resolve(emailAddress)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksMXError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}