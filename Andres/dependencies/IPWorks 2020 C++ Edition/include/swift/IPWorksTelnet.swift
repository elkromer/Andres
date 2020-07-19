
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum TelnetFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum TelnetSSLCertStoreTypes : Int32 {
  case cstUser = 0
  case cstMachine = 1
  case cstPFXFile = 2
  case cstPFXBlob = 3
  case cstJKSFile = 4
  case cstJKSBlob = 5
  case cstPEMKeyFile = 6
  case cstPEMKeyBlob = 7
  case cstPublicKeyFile = 8
  case cstPublicKeyBlob = 9
  case cstSSHPublicKeyBlob = 10
  case cstP7BFile = 11
  case cstP7BBlob = 12
  case cstSSHPublicKeyFile = 13
  case cstPPKFile = 14
  case cstPPKBlob = 15
  case cstXMLFile = 16
  case cstXMLBlob = 17
  case cstJWKFile = 18
  case cstJWKBlob = 19
  case cstSecurityKey = 20
  case cstAuto = 99
}
public enum TelnetSSLStartModes : Int32 {
  case sslAutomatic = 0
  case sslImplicit = 1
  case sslExplicit = 2
  case sslNone = 3
}


public protocol IPWorksTelnetDelegateSwift {
  func onCommand(_ commandCode: Int32)
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDataIn(_ text: Data)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onDo(_ optionCode: Int32)
  func onDont(_ optionCode: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onReadyToSend()
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onSubOption(_ subOption: Data)
  func onWill(_ optionCode: Int32)
  func onWont(_ optionCode: Int32)
}

public enum IPWorksTelnetError : Error {
  case Error(Int32, String)
}

public class IPWorksTelnetSwift : NSObject, IPWorksTelnetDelegate {
  public var m_obj: IPWorksTelnet
  var m_delegate: IPWorksTelnetDelegateSwift?

  override init() {
    self.m_obj = IPWorksTelnet()
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

  public var delegate: IPWorksTelnetDelegateSwift? {
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

  public func onCommand(_ commandCode: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onCommand(commandCode)
    }
  }

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

  public func onDataIn(_ text: Data!) {
    if (m_delegate != nil) {
      m_delegate!.onDataIn(text)
    }
  }

  public func onDisconnected(_ statusCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onDisconnected(statusCode, description)
    }
  }

  public func onDo(_ optionCode: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onDo(optionCode)
    }
  }

  public func onDont(_ optionCode: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onDont(optionCode)
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

  public func onSSLServerAuthentication(_ certEncoded: Data!, _ certSubject: String!, _ certIssuer: String!, _ status: String!, _ accept: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onSSLServerAuthentication(certEncoded, certSubject, certIssuer, status, &accept.pointee)
    }
  }

  public func onSSLStatus(_ message: String!) {
    if (m_delegate != nil) {
      m_delegate!.onSSLStatus(message)
    }
  }

  public func onSubOption(_ subOption: Data!) {
    if (m_delegate != nil) {
      m_delegate!.onSubOption(subOption)
    }
  }

  public func onWill(_ optionCode: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onWill(optionCode)
    }
  }

  public func onWont(_ optionCode: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onWont(optionCode)
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

  public var bytesSent: Int32 {
    get {
      return m_obj.bytesSent
    }
  }

  public var command: Int32 {
    get {
      return m_obj.command
    }
    set {
      m_obj.command = newValue
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

  public var dontOption: Int32 {
    get {
      return m_obj.dontOption
    }
    set {
      m_obj.dontOption = newValue
    }
  }

  public var doOption: Int32 {
    get {
      return m_obj.doOption
    }
    set {
      m_obj.doOption = newValue
    }
  }

  public var doSubOption: String {
    get {
      let ret: String? = String(m_obj.doSubOption)
      return unwrapNSString(ret)
    }
    set {
      m_obj.doSubOption = newValue as NSString
    }
  }

  public var doSubOptionB: Data {
    get {
      let ret: Data? = m_obj.doSubOptionB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.doSubOptionB = newValue as NSData
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

  public var firewallType: TelnetFirewallTypes {
    get {
      return TelnetFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var keepAlive: Bool {
    get {
      return m_obj.keepAlive
    }
    set {
      m_obj.keepAlive = newValue
    }
  }

  public var linger: Bool {
    get {
      return m_obj.linger
    }
    set {
      m_obj.linger = newValue
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

  public var remotePort: Int32 {
    get {
      return m_obj.remotePort
    }
    set {
      m_obj.remotePort = newValue
    }
  }

  public var SSLAcceptServerCertEncoded: String {
    get {
      let ret: String? = String(m_obj.SSLAcceptServerCertEncoded)
      return unwrapNSString(ret)
    }
    set {
      m_obj.SSLAcceptServerCertEncoded = newValue as NSString
    }
  }

  public var SSLAcceptServerCertEncodedB: Data {
    get {
      let ret: Data? = m_obj.SSLAcceptServerCertEncodedB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.SSLAcceptServerCertEncodedB = newValue as NSData
    }
  }

  public var SSLCertEncoded: String {
    get {
      let ret: String? = String(m_obj.SSLCertEncoded)
      return unwrapNSString(ret)
    }
    set {
      m_obj.SSLCertEncoded = newValue as NSString
    }
  }

  public var SSLCertEncodedB: Data {
    get {
      let ret: Data? = m_obj.SSLCertEncodedB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.SSLCertEncodedB = newValue as NSData
    }
  }

  public var SSLCertStore: String {
    get {
      let ret: String? = String(m_obj.SSLCertStore)
      return unwrapNSString(ret)
    }
    set {
      m_obj.SSLCertStore = newValue as NSString
    }
  }

  public var SSLCertStoreB: Data {
    get {
      let ret: Data? = m_obj.SSLCertStoreB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.SSLCertStoreB = newValue as NSData
    }
  }

  public var SSLCertStorePassword: String {
    get {
      let ret: String? = String(m_obj.SSLCertStorePassword)
      return unwrapNSString(ret)
    }
    set {
      m_obj.SSLCertStorePassword = newValue as NSString
    }
  }

  public var SSLCertStoreType: TelnetSSLCertStoreTypes {
    get {
      return TelnetSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
    }
    set {
      m_obj.SSLCertStoreType = newValue.rawValue
    }
  }

  public var SSLCertSubject: String {
    get {
      let ret: String? = String(m_obj.SSLCertSubject)
      return unwrapNSString(ret)
    }
    set {
      m_obj.SSLCertSubject = newValue as NSString
    }
  }

  public var SSLEnabled: Bool {
    get {
      return m_obj.SSLEnabled
    }
    set {
      m_obj.SSLEnabled = newValue
    }
  }

  public var SSLServerCertEncoded: String {
    get {
      let ret: String? = String(m_obj.SSLServerCertEncoded)
      return unwrapNSString(ret)
    }
  }

  public var SSLServerCertEncodedB: Data {
    get {
      let ret: Data? = m_obj.SSLServerCertEncodedB as Data
      return unwrapData(ret)
    }

  }

  public var SSLStartMode: TelnetSSLStartModes {
    get {
      return TelnetSSLStartModes(rawValue: m_obj.SSLStartMode)!
    }
    set {
      m_obj.SSLStartMode = newValue.rawValue
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

  public var transparent: Bool {
    get {
      return m_obj.transparent
    }
    set {
      m_obj.transparent = newValue
    }
  }

  public var urgentData: String {
    get {
      let ret: String? = String(m_obj.urgentData)
      return unwrapNSString(ret)
    }
    set {
      m_obj.urgentData = newValue as NSString
    }
  }

  public var urgentDataB: Data {
    get {
      let ret: Data? = m_obj.urgentDataB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.urgentDataB = newValue as NSData
    }
  }

  public var willOption: Int32 {
    get {
      return m_obj.willOption
    }
    set {
      m_obj.willOption = newValue
    }
  }

  public var wontOption: Int32 {
    get {
      return m_obj.wontOption
    }
    set {
      m_obj.wontOption = newValue
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTelnetError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func connect(_ host: String) throws -> Void {
    m_obj.connect(host)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTelnetError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func disconnect() throws -> Void {
    m_obj.disconnect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTelnetError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTelnetError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTelnetError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func send(_ text: Data) throws -> Void {
    m_obj.send(text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksTelnetError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}