
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum NetclockProtocols : Int32 {
  case tpTime = 0
  case tpSNTP = 1
}


public protocol IPWorksNetClockDelegateSwift {
  func onError(_ errorCode: Int32, _ description: String)
}

public enum IPWorksNetClockError : Error {
  case Error(Int32, String)
}

public class IPWorksNetClockSwift : NSObject, IPWorksNetClockDelegate {
  public var m_obj: IPWorksNetClock
  var m_delegate: IPWorksNetClockDelegateSwift?

  override init() {
    self.m_obj = IPWorksNetClock()
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

  public var delegate: IPWorksNetClockDelegateSwift? {
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

  public var localHost: String {
    get {
      let ret: String? = String(m_obj.localHost)
      return unwrapNSString(ret)
    }
    set {
      m_obj.localHost = newValue as NSString
    }
  }

  public var localTime: String {
    get {
      let ret: String? = String(m_obj.localTime)
      return unwrapNSString(ret)
    }
  }

  public var protocol_: NetclockProtocols {
    get {
      return NetclockProtocols(rawValue: m_obj.protocol_())!
    }
    set {
      m_obj.setProtocol_(newValue.rawValue)
    }
  }

  public var serverTime: String {
    get {
      let ret: String? = String(m_obj.serverTime)
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

  public var timePort: Int32 {
    get {
      return m_obj.timePort
    }
    set {
      m_obj.timePort = newValue
    }
  }

  public var timeServer: String {
    get {
      let ret: String? = String(m_obj.timeServer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timeServer = newValue as NSString
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetClockError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetClockError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getAndSetTime() throws -> Void {
    m_obj.getAndSetTime()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetClockError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getTime() throws -> Void {
    m_obj.getTime()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetClockError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetClockError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNetClockError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}