
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation



public protocol IPWorksTraceRouteDelegateSwift {
  func onError(_ errorCode: Int32, _ description: String)
  func onHop(_ hopNumber: Int32, _ hostAddress: String, _ duration: Int32)
  func onHopResolved(_ hopNumber: Int32, _ statusCode: Int32, _ hopHostName: String)
}

public enum IPWorksTraceRouteError : Error {
  case Error(Int32, String)
}

public class IPWorksTraceRouteSwift : NSObject, IPWorksTraceRouteDelegate {
  public var m_obj: IPWorksTraceRoute
  var m_delegate: IPWorksTraceRouteDelegateSwift?

  override init() {
    self.m_obj = IPWorksTraceRoute()
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

  public var delegate: IPWorksTraceRouteDelegateSwift? {
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

  public func onHop(_ hopNumber: Int32, _ hostAddress: String!, _ duration: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onHop(hopNumber, hostAddress, duration)
    }
  }

  public func onHopResolved(_ hopNumber: Int32, _ statusCode: Int32, _ hopHostName: String!) {
    if (m_delegate != nil) {
      m_delegate!.onHopResolved(hopNumber, statusCode, hopHostName)
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

  public var hopLimit: Int32 {
    get {
      return m_obj.hopLimit
    }
    set {
      m_obj.hopLimit = newValue
    }
  }

  public var hopCount: Int32 {
    get {
      return m_obj.hopCount
    }
  }

  public func hopErrorCode(hopIndex: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.hopErrorCode(hopIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTraceRouteError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func hopErrorDescription(hopIndex: Int32) throws -> String {
    let ret: String? = m_obj.hopErrorDescription(hopIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTraceRouteError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func hopHostAddress(hopIndex: Int32) throws -> String {
    let ret: String? = m_obj.hopHostAddress(hopIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTraceRouteError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func hopHostName(hopIndex: Int32) throws -> String {
    let ret: String? = m_obj.hopHostName(hopIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTraceRouteError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func hopTime(hopIndex: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.hopTime(hopIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTraceRouteError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public var hopTimeout: Int32 {
    get {
      return m_obj.hopTimeout
    }
    set {
      m_obj.hopTimeout = newValue
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

  public var remoteHost: String {
    get {
      let ret: String? = String(m_obj.remoteHost)
      return unwrapNSString(ret)
    }
    set {
      m_obj.remoteHost = newValue as NSString
    }
  }

  public var resolveNames: Bool {
    get {
      return m_obj.resolveNames
    }
    set {
      m_obj.resolveNames = newValue
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTraceRouteError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTraceRouteError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTraceRouteError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTraceRouteError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func traceTo(_ host: String) throws -> Void {
    m_obj.traceTo(host)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTraceRouteError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}