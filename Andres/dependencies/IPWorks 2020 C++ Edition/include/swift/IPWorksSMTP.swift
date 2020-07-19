
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum SmtpAuthMechanisms : Int32 {
  case amUserPassword = 0
  case amCRAMMD5 = 1
  case amNTLM = 2
  case amAPOP = 3
  case amSASLPlain = 4
  case amSASLDigestMD5 = 5
  case amKerberos = 6
  case amXOAUTH2 = 7
}
public enum SmtpFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum SmtpImportances : Int32 {
  case miUnspecified = 0
  case miHigh = 1
  case miNormal = 2
  case miLow = 3
}
public enum SmtpMessageRecipientTypes : Int32 {
  case rtTo = 0
  case rtCc = 1
  case rtBCc = 2
}
public enum SmtpPriorities : Int32 {
  case epUnspecified = 0
  case epNormal = 1
  case epUrgent = 2
  case epNonUrgent = 3
}
public enum SmtpSensitivities : Int32 {
  case esUnspecified = 0
  case esPersonal = 1
  case esPrivate = 2
  case esCompanyConfidential = 3
}
public enum SmtpSSLCertStoreTypes : Int32 {
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
public enum SmtpSSLStartModes : Int32 {
  case sslAutomatic = 0
  case sslImplicit = 1
  case sslExplicit = 2
  case sslNone = 3
}


public protocol IPWorksSMTPDelegateSwift {
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onExpand(_ address: String)
  func onPITrail(_ direction: Int32, _ message: String)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32)
}

public enum IPWorksSMTPError : Error {
  case Error(Int32, String)
}

public class IPWorksSMTPSwift : NSObject, IPWorksSMTPDelegate {
  public var m_obj: IPWorksSMTP
  var m_delegate: IPWorksSMTPDelegateSwift?

  override init() {
    self.m_obj = IPWorksSMTP()
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

  public var delegate: IPWorksSMTPDelegateSwift? {
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

  public func onConnectionStatus(_ connectionEvent: String!, _ statusCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onConnectionStatus(connectionEvent, statusCode, description)
    }
  }

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

  public func onExpand(_ address: String!) {
    if (m_delegate != nil) {
      m_delegate!.onExpand(address)
    }
  }

  public func onPITrail(_ direction: Int32, _ message: String!) {
    if (m_delegate != nil) {
      m_delegate!.onPITrail(direction, message)
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

  public func onStartTransfer(_ direction: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onStartTransfer(direction)
    }
  }

  public func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onTransfer(direction, bytesTransferred, percentDone)
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

  public var allowExtensions: Bool {
    get {
      return m_obj.allowExtensions
    }
    set {
      m_obj.allowExtensions = newValue
    }
  }

  public var authMechanism: SmtpAuthMechanisms {
    get {
      return SmtpAuthMechanisms(rawValue: m_obj.authMechanism)!
    }
    set {
      m_obj.authMechanism = newValue.rawValue
    }
  }

  public var BCc: String {
    get {
      let ret: String? = String(m_obj.BCc)
      return unwrapNSString(ret)
    }
    set {
      m_obj.BCc = newValue as NSString
    }
  }

  public var cc: String {
    get {
      let ret: String? = String(m_obj.cc)
      return unwrapNSString(ret)
    }
    set {
      m_obj.cc = newValue as NSString
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

  public var deliveryNotificationTo: String {
    get {
      let ret: String? = String(m_obj.deliveryNotificationTo)
      return unwrapNSString(ret)
    }
    set {
      m_obj.deliveryNotificationTo = newValue as NSString
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

  public var firewallType: SmtpFirewallTypes {
    get {
      return SmtpFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var from: String {
    get {
      let ret: String? = String(m_obj.from)
      return unwrapNSString(ret)
    }
    set {
      m_obj.from = newValue as NSString
    }
  }

  public var idle: Bool {
    get {
      return m_obj.idle
    }
  }

  public var importance: SmtpImportances {
    get {
      return SmtpImportances(rawValue: m_obj.importance)!
    }
    set {
      m_obj.importance = newValue.rawValue
    }
  }

  public var lastReply: String {
    get {
      let ret: String? = String(m_obj.lastReply)
      return unwrapNSString(ret)
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

  public var mailPort: Int32 {
    get {
      return m_obj.mailPort
    }
    set {
      m_obj.mailPort = newValue
    }
  }

  public var mailServer: String {
    get {
      let ret: String? = String(m_obj.mailServer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.mailServer = newValue as NSString
    }
  }

  public var message: String {
    get {
      let ret: String? = String(m_obj.message)
      return unwrapNSString(ret)
    }
    set {
      m_obj.message = newValue as NSString
    }
  }

  public var messageB: Data {
    get {
      let ret: Data? = m_obj.messageB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.messageB = newValue as NSData
    }
  }

  public var messageDate: String {
    get {
      let ret: String? = String(m_obj.messageDate)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageDate = newValue as NSString
    }
  }

  public var messageHeaderCount: Int32 {
    get {
      return m_obj.messageHeaderCount
    }
  }

  public func messageHeaderField(messageHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageHeaderField(messageHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageHeaderValue(messageHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageHeaderValue(messageHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var messageHeadersString: String {
    get {
      let ret: String? = String(m_obj.messageHeadersString)
      return unwrapNSString(ret)
    }
  }

  public var messageId: String {
    get {
      let ret: String? = String(m_obj.messageId)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageId = newValue as NSString
    }
  }

  public var messageRecipientCount: Int32 {
    get {
      return m_obj.messageRecipientCount
    }
    set {
      m_obj.messageRecipientCount = newValue
    }
  }

  public func messageRecipientAddress(recipientIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageRecipientAddress(recipientIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setMessageRecipientAddress(recipientIndex: Int32, newMessageRecipientAddress: String) throws -> Void {
    m_obj.setMessageRecipientAddress(recipientIndex, newMessageRecipientAddress)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func messageRecipientName(recipientIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageRecipientName(recipientIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setMessageRecipientName(recipientIndex: Int32, newMessageRecipientName: String) throws -> Void {
    m_obj.setMessageRecipientName(recipientIndex, newMessageRecipientName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func messageRecipientOptions(recipientIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageRecipientOptions(recipientIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setMessageRecipientOptions(recipientIndex: Int32, newMessageRecipientOptions: String) throws -> Void {
    m_obj.setMessageRecipientOptions(recipientIndex, newMessageRecipientOptions)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func messageRecipientType(recipientIndex: Int32) throws -> SmtpMessageRecipientTypes {
    let ret = SmtpMessageRecipientTypes(rawValue: m_obj.messageRecipientType(recipientIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func setMessageRecipientType(recipientIndex: Int32, newMessageRecipientType: SmtpMessageRecipientTypes) throws -> Void {
    m_obj.setMessageRecipientType(recipientIndex, newMessageRecipientType.rawValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var messageText: String {
    get {
      let ret: String? = String(m_obj.messageText)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageText = newValue as NSString
    }
  }

  public var otherHeaders: String {
    get {
      let ret: String? = String(m_obj.otherHeaders)
      return unwrapNSString(ret)
    }
    set {
      m_obj.otherHeaders = newValue as NSString
    }
  }

  public var password: String {
    get {
      let ret: String? = String(m_obj.password)
      return unwrapNSString(ret)
    }
    set {
      m_obj.password = newValue as NSString
    }
  }

  public var priority: SmtpPriorities {
    get {
      return SmtpPriorities(rawValue: m_obj.priority)!
    }
    set {
      m_obj.priority = newValue.rawValue
    }
  }

  public var readReceiptTo: String {
    get {
      let ret: String? = String(m_obj.readReceiptTo)
      return unwrapNSString(ret)
    }
    set {
      m_obj.readReceiptTo = newValue as NSString
    }
  }

  public var replyTo: String {
    get {
      let ret: String? = String(m_obj.replyTo)
      return unwrapNSString(ret)
    }
    set {
      m_obj.replyTo = newValue as NSString
    }
  }

  public var returnPath: String {
    get {
      let ret: String? = String(m_obj.returnPath)
      return unwrapNSString(ret)
    }
    set {
      m_obj.returnPath = newValue as NSString
    }
  }

  public var sendTo: String {
    get {
      let ret: String? = String(m_obj.sendTo)
      return unwrapNSString(ret)
    }
    set {
      m_obj.sendTo = newValue as NSString
    }
  }

  public var sensitivity: SmtpSensitivities {
    get {
      return SmtpSensitivities(rawValue: m_obj.sensitivity)!
    }
    set {
      m_obj.sensitivity = newValue.rawValue
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

  public var SSLCertStoreType: SmtpSSLCertStoreTypes {
    get {
      return SmtpSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var SSLStartMode: SmtpSSLStartModes {
    get {
      return SmtpSSLStartModes(rawValue: m_obj.SSLStartMode)!
    }
    set {
      m_obj.SSLStartMode = newValue.rawValue
    }
  }

  public var subject: String {
    get {
      let ret: String? = String(m_obj.subject)
      return unwrapNSString(ret)
    }
    set {
      m_obj.subject = newValue as NSString
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

  public var user: String {
    get {
      let ret: String? = String(m_obj.user)
      return unwrapNSString(ret)
    }
    set {
      m_obj.user = newValue as NSString
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func connect() throws -> Void {
    m_obj.connect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func disconnect() throws -> Void {
    m_obj.disconnect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func expand(_ emailAddress: String) throws -> Void {
    m_obj.expand(emailAddress)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func processQueue(_ queueDir: String) throws -> Void {
    m_obj.processQueue(queueDir)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func queue(_ queueDir: String) throws -> String {
    let ret: String? = m_obj.queue(queueDir)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func resetHeaders() throws -> Void {
    m_obj.resetHeaders()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func send() throws -> Void {
    m_obj.send()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func sendToTerminalAndEmail() throws -> Void {
    m_obj.sendToTerminalAndEmail()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func sendToTerminalOnly() throws -> Void {
    m_obj.sendToTerminalOnly()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func sendToTerminalOrEmail() throws -> Void {
    m_obj.sendToTerminalOrEmail()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func verify(_ emailAddress: String) throws -> Void {
    m_obj.verify(emailAddress)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}