
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum IpdaemonSSLCertStoreTypes : Int32 {
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
public enum IpdaemonSSLStartModes : Int32 {
  case sslAutomatic = 0
  case sslImplicit = 1
  case sslExplicit = 2
  case sslNone = 3
}


public protocol IPWorksIPDaemonDelegateSwift {
  func onConnected(_ connectionId: Int32, _ statusCode: Int32, _ description: String)
  func onConnectionRequest(_ address: String, _ port: Int32, _ accept: inout Int32)
  func onDataIn(_ connectionId: Int32, _ text: Data, _ EOL: Bool)
  func onDisconnected(_ connectionId: Int32, _ statusCode: Int32, _ description: String)
  func onError(_ connectionId: Int32, _ errorCode: Int32, _ description: String)
  func onReadyToSend(_ connectionId: Int32)
  func onSSLClientAuthentication(_ connectionId: Int32, _ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLConnectionRequest(_ connectionId: Int32, _ supportedCipherSuites: String, _ supportedSignatureAlgs: String, _ certStoreType: inout Int32, _ certStore: inout NSString?, _ certPassword: inout NSString?, _ certSubject: inout NSString?)
  func onSSLStatus(_ connectionId: Int32, _ message: String)
}

public enum IPWorksIPDaemonError : Error {
  case Error(Int32, String)
}

public class IPWorksIPDaemonSwift : NSObject, IPWorksIPDaemonDelegate {
  public var m_obj: IPWorksIPDaemon
  var m_delegate: IPWorksIPDaemonDelegateSwift?

  override init() {
    self.m_obj = IPWorksIPDaemon()
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

  public var delegate: IPWorksIPDaemonDelegateSwift? {
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

  public func onConnected(_ connectionId: Int32, _ statusCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onConnected(connectionId, statusCode, description)
    }
  }

  public func onConnectionRequest(_ address: String!, _ port: Int32, _ accept: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onConnectionRequest(address, port, &accept.pointee)
    }
  }

  public func onDataIn(_ connectionId: Int32, _ text: Data!, _ EOL: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onDataIn(connectionId, text, EOL)
    }
  }

  public func onDisconnected(_ connectionId: Int32, _ statusCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onDisconnected(connectionId, statusCode, description)
    }
  }

  public func onError(_ connectionId: Int32, _ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(connectionId, errorCode, description)
    }
  }

  public func onReadyToSend(_ connectionId: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onReadyToSend(connectionId)
    }
  }

  public func onSSLClientAuthentication(_ connectionId: Int32, _ certEncoded: Data!, _ certSubject: String!, _ certIssuer: String!, _ status: String!, _ accept: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onSSLClientAuthentication(connectionId, certEncoded, certSubject, certIssuer, status, &accept.pointee)
    }
  }

  public func onSSLConnectionRequest(_ connectionId: Int32, _ supportedCipherSuites: String!, _ supportedSignatureAlgs: String!, _ certStoreType: UnsafeMutablePointer<Int32>, _ certStore: AutoreleasingUnsafeMutablePointer<NSString?>, _ certPassword: AutoreleasingUnsafeMutablePointer<NSString?>, _ certSubject: AutoreleasingUnsafeMutablePointer<NSString?>) {
    if (m_delegate != nil) {
      m_delegate!.onSSLConnectionRequest(connectionId, supportedCipherSuites, supportedSignatureAlgs, &certStoreType.pointee, &certStore.pointee, &certPassword.pointee, &certSubject.pointee)
    }
  }

  public func onSSLStatus(_ connectionId: Int32, _ message: String!) {
    if (m_delegate != nil) {
      m_delegate!.onSSLStatus(connectionId, message)
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

  public var connectionBacklog: Int32 {
    get {
      return m_obj.connectionBacklog
    }
    set {
      m_obj.connectionBacklog = newValue
    }
  }

  public var connectionCount: Int32 {
    get {
      return m_obj.connectionCount
    }
  }

  public func acceptData(connectionId: Int32) throws -> Bool {
    let ret: Bool? = m_obj.acceptData(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func setAcceptData(connectionId: Int32, newAcceptData: Bool) throws -> Void {
    m_obj.setAcceptData(connectionId, newAcceptData)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func bytesSent(connectionId: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.bytesSent(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func connected(connectionId: Int32) throws -> Bool {
    let ret: Bool? = m_obj.connected(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func setConnected(connectionId: Int32, newConnected: Bool) throws -> Void {
    m_obj.setConnected(connectionId, newConnected)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func connectionId(connectionId: Int32) throws -> String {
    let ret: String? = m_obj.connectionId(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setDataToSend(connectionId: Int32, newDataToSend: String) throws -> Void {
    m_obj.setDataToSend(connectionId, newDataToSend)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setDataToSendB(connectionId: Int32, newDataToSend: Data) throws -> Void {
    m_obj.setDataToSendB(connectionId, newDataToSend)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func EOL(connectionId: Int32) throws -> String {
    let ret: String? = m_obj.EOL(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEOL(connectionId: Int32, newEOL: String) throws -> Void {
    m_obj.setEOL(connectionId, newEOL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func EOLB(connectionId: Int32) throws -> Data {
    let ret: Data? = m_obj.EOLB(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapData(ret)
  }

  public func setEOLB(connectionId: Int32, newEOL: Data) throws -> Void {
    m_obj.setEOLB(connectionId, newEOL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func idleTimeout(connectionId: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.idleTimeout(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func setIdleTimeout(connectionId: Int32, newIdleTimeout: Int32) throws -> Void {
    m_obj.setIdleTimeout(connectionId, newIdleTimeout)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func localAddress(connectionId: Int32) throws -> String {
    let ret: String? = m_obj.localAddress(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func readyToSend(connectionId: Int32) throws -> Bool {
    let ret: Bool? = m_obj.readyToSend(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func recordLength(connectionId: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.recordLength(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func setRecordLength(connectionId: Int32, newRecordLength: Int32) throws -> Void {
    m_obj.setRecordLength(connectionId, newRecordLength)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func remoteHost(connectionId: Int32) throws -> String {
    let ret: String? = m_obj.remoteHost(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func remotePort(connectionId: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.remotePort(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func singleLineMode(connectionId: Int32) throws -> Bool {
    let ret: Bool? = m_obj.singleLineMode(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func setSingleLineMode(connectionId: Int32, newSingleLineMode: Bool) throws -> Void {
    m_obj.setSingleLineMode(connectionId, newSingleLineMode)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func timeout(connectionId: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.timeout(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func setTimeout(connectionId: Int32, newTimeout: Int32) throws -> Void {
    m_obj.setTimeout(connectionId, newTimeout)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func userData(connectionId: Int32) throws -> String {
    let ret: String? = m_obj.userData(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setUserData(connectionId: Int32, newUserData: String) throws -> Void {
    m_obj.setUserData(connectionId, newUserData)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func userDataB(connectionId: Int32) throws -> Data {
    let ret: Data? = m_obj.userDataB(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapData(ret)
  }

  public func setUserDataB(connectionId: Int32, newUserData: Data) throws -> Void {
    m_obj.setUserDataB(connectionId, newUserData)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var defaultEOL: String {
    get {
      let ret: String? = String(m_obj.defaultEOL)
      return unwrapNSString(ret)
    }
    set {
      m_obj.defaultEOL = newValue as NSString
    }
  }

  public var defaultEOLB: Data {
    get {
      let ret: Data? = m_obj.defaultEOLB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.defaultEOLB = newValue as NSData
    }
  }

  public var defaultIdleTimeout: Int32 {
    get {
      return m_obj.defaultIdleTimeout
    }
    set {
      m_obj.defaultIdleTimeout = newValue
    }
  }

  public var defaultMaxLineLength: Int32 {
    get {
      return m_obj.defaultMaxLineLength
    }
    set {
      m_obj.defaultMaxLineLength = newValue
    }
  }

  public var defaultSingleLineMode: Bool {
    get {
      return m_obj.defaultSingleLineMode
    }
    set {
      m_obj.defaultSingleLineMode = newValue
    }
  }

  public var defaultTimeout: Int32 {
    get {
      return m_obj.defaultTimeout
    }
    set {
      m_obj.defaultTimeout = newValue
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

  public var listening: Bool {
    get {
      return m_obj.listening
    }
    set {
      m_obj.listening = newValue
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

  public var SSLAuthenticateClients: Bool {
    get {
      return m_obj.SSLAuthenticateClients
    }
    set {
      m_obj.SSLAuthenticateClients = newValue
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

  public var SSLCertStoreType: IpdaemonSSLCertStoreTypes {
    get {
      return IpdaemonSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var SSLStartMode: IpdaemonSSLStartModes {
    get {
      return IpdaemonSSLStartModes(rawValue: m_obj.SSLStartMode)!
    }
    set {
      m_obj.SSLStartMode = newValue.rawValue
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func disconnect(_ connectionId: Int32) throws -> Void {
    m_obj.disconnect(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt(_ connectionId: Int32) throws -> Void {
    m_obj.interrupt(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func send(_ connectionId: Int32, _ text: Data) throws -> Void {
    m_obj.send(connectionId, text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func sendFile(_ connectionId: Int32, _ fileName: String) throws -> Void {
    m_obj.sendFile(connectionId, fileName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func sendLine(_ connectionId: Int32, _ text: String) throws -> Void {
    m_obj.sendLine(connectionId, text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func shutdown() throws -> Void {
    m_obj.shutdown()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func startSSL(_ connectionId: Int32) throws -> Void {
    m_obj.startSSL(connectionId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPDaemonError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}