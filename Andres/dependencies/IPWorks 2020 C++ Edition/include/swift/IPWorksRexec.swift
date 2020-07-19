
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum RexecFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}


public protocol IPWorksRexecDelegateSwift {
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onError(_ errorCode: Int32, _ description: String)
  func onStderr(_ text: Data, _ EOL: Bool)
  func onStdout(_ text: Data, _ EOL: Bool)
}

public enum IPWorksRexecError : Error {
  case Error(Int32, String)
}

public class IPWorksRexecSwift : NSObject, IPWorksRexecDelegate {
  public var m_obj: IPWorksRexec
  var m_delegate: IPWorksRexecDelegateSwift?

  override init() {
    self.m_obj = IPWorksRexec()
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

  public var delegate: IPWorksRexecDelegateSwift? {
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

  public func onConnected(_ statusCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onConnected(statusCode, description)
    }
  }

  public func onConnectionStatus(_ connectionEvent: String!, _ statusCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onConnectionStatus(connectionEvent, statusCode, description)
    }
  }

  public func onDisconnected(_ statusCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onDisconnected(statusCode, description)
    }
  }

  public func onError(_ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(errorCode, description)
    }
  }

  public func onStderr(_ text: Data!, _ EOL: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onStderr(text, EOL)
    }
  }

  public func onStdout(_ text: Data!, _ EOL: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onStdout(text, EOL)
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

  public var bytesSent: Int32 {
    get {
      return m_obj.bytesSent
    }
  }

  public var command: String {
    get {
      let ret: String? = String(m_obj.command)
      return unwrapNSString(ret)
    }
    set {
      m_obj.command = newValue as NSString
    }
  }

  public var connected: Bool {
    get {
      return m_obj.connected
    }
    set {
      m_obj.connected = newValue
    }
  }

  public var eoF: Bool {
    get {
      return m_obj.eoF
    }
  }

  public var EOL: String {
    get {
      let ret: String? = String(m_obj.EOL)
      return unwrapNSString(ret)
    }
    set {
      m_obj.EOL = newValue as NSString
    }
  }

  public var EOLB: Data {
    get {
      let ret: Data? = m_obj.EOLB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.EOLB = newValue as NSData
    }
  }

  public var errEOL: String {
    get {
      let ret: String? = String(m_obj.errEOL)
      return unwrapNSString(ret)
    }
    set {
      m_obj.errEOL = newValue as NSString
    }
  }

  public var errEOLB: Data {
    get {
      let ret: Data? = m_obj.errEOLB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.errEOLB = newValue as NSData
    }
  }

  public var errorMessage: String {
    get {
      let ret: String? = String(m_obj.errorMessage)
      return unwrapNSString(ret)
    }
  }

  public var firewallAutoDetect: Bool {
    get {
      return m_obj.firewallAutoDetect
    }
    set {
      m_obj.firewallAutoDetect = newValue
    }
  }

  public var firewallType: RexecFirewallTypes {
    get {
      return RexecFirewallTypes(rawValue: m_obj.firewallType)!
    }
    set {
      m_obj.firewallType = newValue.rawValue
    }
  }

  public var firewallHost: String {
    get {
      let ret: String? = String(m_obj.firewallHost)
      return unwrapNSString(ret)
    }
    set {
      m_obj.firewallHost = newValue as NSString
    }
  }

  public var firewallPassword: String {
    get {
      let ret: String? = String(m_obj.firewallPassword)
      return unwrapNSString(ret)
    }
    set {
      m_obj.firewallPassword = newValue as NSString
    }
  }

  public var firewallPort: Int32 {
    get {
      return m_obj.firewallPort
    }
    set {
      m_obj.firewallPort = newValue
    }
  }

  public var firewallUser: String {
    get {
      let ret: String? = String(m_obj.firewallUser)
      return unwrapNSString(ret)
    }
    set {
      m_obj.firewallUser = newValue as NSString
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

  public var remoteHost: String {
    get {
      let ret: String? = String(m_obj.remoteHost)
      return unwrapNSString(ret)
    }
    set {
      m_obj.remoteHost = newValue as NSString
    }
  }

  public var remotePassword: String {
    get {
      let ret: String? = String(m_obj.remotePassword)
      return unwrapNSString(ret)
    }
    set {
      m_obj.remotePassword = newValue as NSString
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

  public var remoteUser: String {
    get {
      let ret: String? = String(m_obj.remoteUser)
      return unwrapNSString(ret)
    }
    set {
      m_obj.remoteUser = newValue as NSString
    }
  }

  public var stderr_: String {
    get {
      let ret: String? = m_obj.stderr_()
      return unwrapNSString(ret)
    }
  }

  public var stderrB: Data {
    get {
      let ret: Data? = m_obj.stderrB as Data
      return unwrapData(ret)
    }

  }

  public var stdin_: String {
    get {
      let ret: String? = m_obj.stdin_()
      return unwrapNSString(ret)
    }
    set {
      m_obj.setStdin_(newValue)
    }
  }

  public var stdinB: Data {
    get {
      let ret: Data? = m_obj.stdinB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.stdinB = newValue as NSData
    }
  }

  public var stdout_: String {
    get {
      let ret: String? = m_obj.stdout_()
      return unwrapNSString(ret)
    }
  }

  public var stdoutB: Data {
    get {
      let ret: Data? = m_obj.stdoutB as Data
      return unwrapData(ret)
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRexecError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func disconnect() throws -> Void {
    m_obj.disconnect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRexecError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRexecError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func execute(_ command: String) throws -> Void {
    m_obj.execute(command)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRexecError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRexecError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRexecError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func send(_ text: Data) throws -> Void {
    m_obj.send(text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRexecError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}