
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum PopAuthMechanisms : Int32 {
  case amUserPassword = 0
  case amCRAMMD5 = 1
  case amNTLM = 2
  case amAPOP = 3
  case amSASLPlain = 4
  case amSASLDigestMD5 = 5
  case amKerberos = 6
  case amXOAUTH2 = 7
}
public enum PopFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum PopMessageRecipientTypes : Int32 {
  case rtTo = 0
  case rtCc = 1
  case rtBCc = 2
}
public enum PopSSLCertStoreTypes : Int32 {
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
public enum PopSSLStartModes : Int32 {
  case sslAutomatic = 0
  case sslImplicit = 1
  case sslExplicit = 2
  case sslNone = 3
}


public protocol IPWorksPOPDelegateSwift {
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onHeader(_ field: String, _ value: String)
  func onMessageList(_ messageNumber: Int32, _ messageUID: String, _ messageSize: Int32)
  func onPITrail(_ direction: Int32, _ message: String)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data, _ EOL: Bool)
}

public enum IPWorksPOPError : Error {
  case Error(Int32, String)
}

public class IPWorksPOPSwift : NSObject, IPWorksPOPDelegate {
  public var m_obj: IPWorksPOP
  var m_delegate: IPWorksPOPDelegateSwift?

  override init() {
    self.m_obj = IPWorksPOP()
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

  public var delegate: IPWorksPOPDelegateSwift? {
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

  public func onHeader(_ field: String!, _ value: String!) {
    if (m_delegate != nil) {
      m_delegate!.onHeader(field, value)
    }
  }

  public func onMessageList(_ messageNumber: Int32, _ messageUID: String!, _ messageSize: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onMessageList(messageNumber, messageUID, messageSize)
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

  public func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data!, _ EOL: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onTransfer(direction, bytesTransferred, percentDone, text, EOL)
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

  public var authMechanism: PopAuthMechanisms {
    get {
      return PopAuthMechanisms(rawValue: m_obj.authMechanism)!
    }
    set {
      m_obj.authMechanism = newValue.rawValue
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

  public var firewallAutoDetect: Bool {
    get {
      return m_obj.firewallAutoDetect
    }
    set {
      m_obj.firewallAutoDetect = newValue
    }
  }

  public var firewallType: PopFirewallTypes {
    get {
      return PopFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var idle: Bool {
    get {
      return m_obj.idle
    }
  }

  public var includeHeaders: Bool {
    get {
      return m_obj.includeHeaders
    }
    set {
      m_obj.includeHeaders = newValue
    }
  }

  public var lastReply: String {
    get {
      let ret: String? = String(m_obj.lastReply)
      return unwrapNSString(ret)
    }
  }

  public var localFile: String {
    get {
      let ret: String? = String(m_obj.localFile)
      return unwrapNSString(ret)
    }
    set {
      m_obj.localFile = newValue as NSString
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

  public var maxLines: Int32 {
    get {
      return m_obj.maxLines
    }
    set {
      m_obj.maxLines = newValue
    }
  }

  public var message: String {
    get {
      let ret: String? = String(m_obj.message)
      return unwrapNSString(ret)
    }
  }

  public var messageB: Data {
    get {
      let ret: Data? = m_obj.messageB as Data
      return unwrapData(ret)
    }

  }

  public var messageCc: String {
    get {
      let ret: String? = String(m_obj.messageCc)
      return unwrapNSString(ret)
    }
  }

  public var messageCount: Int32 {
    get {
      return m_obj.messageCount
    }
  }

  public var messageDate: String {
    get {
      let ret: String? = String(m_obj.messageDate)
      return unwrapNSString(ret)
    }
  }

  public var messageFrom: String {
    get {
      let ret: String? = String(m_obj.messageFrom)
      return unwrapNSString(ret)
    }
  }

  public var messageHeaderCount: Int32 {
    get {
      return m_obj.messageHeaderCount
    }
  }

  public func messageHeaderField(messageHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageHeaderField(messageHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageHeaderValue(messageHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageHeaderValue(messageHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var messageHeadersString: String {
    get {
      let ret: String? = String(m_obj.messageHeadersString)
      return unwrapNSString(ret)
    }
  }

  public var messageNumber: Int32 {
    get {
      return m_obj.messageNumber
    }
    set {
      m_obj.messageNumber = newValue
    }
  }

  public var messageRecipientCount: Int32 {
    get {
      return m_obj.messageRecipientCount
    }
  }

  public func messageRecipientAddress(recipientIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageRecipientAddress(recipientIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageRecipientName(recipientIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageRecipientName(recipientIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageRecipientOptions(recipientIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageRecipientOptions(recipientIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageRecipientType(recipientIndex: Int32) throws -> PopMessageRecipientTypes {
    let ret = PopMessageRecipientTypes(rawValue: m_obj.messageRecipientType(recipientIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public var messageReplyTo: String {
    get {
      let ret: String? = String(m_obj.messageReplyTo)
      return unwrapNSString(ret)
    }
  }

  public var messageSize: Int32 {
    get {
      return m_obj.messageSize
    }
  }

  public var messageSubject: String {
    get {
      let ret: String? = String(m_obj.messageSubject)
      return unwrapNSString(ret)
    }
  }

  public var messageText: String {
    get {
      let ret: String? = String(m_obj.messageText)
      return unwrapNSString(ret)
    }
  }

  public var messageTo: String {
    get {
      let ret: String? = String(m_obj.messageTo)
      return unwrapNSString(ret)
    }
  }

  public var messageUID: String {
    get {
      let ret: String? = String(m_obj.messageUID)
      return unwrapNSString(ret)
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

  public var SSLCertStoreType: PopSSLCertStoreTypes {
    get {
      return PopSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var SSLStartMode: PopSSLStartModes {
    get {
      return PopSSLStartModes(rawValue: m_obj.SSLStartMode)!
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

  public var totalSize: Int64 {
    get {
      return m_obj.totalSize
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func connect() throws -> Void {
    m_obj.connect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func delete_() throws -> Void {
    m_obj.delete()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func disconnect() throws -> Void {
    m_obj.disconnect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listMessageSizes() throws -> Void {
    m_obj.listMessageSizes()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listMessageUIDs() throws -> Void {
    m_obj.listMessageUIDs()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func localizeDate(_ dateTime: String) throws -> String {
    let ret: String? = m_obj.localizeDate(dateTime)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func retrieve() throws -> Void {
    m_obj.retrieve()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func retrieveHeaders() throws -> Void {
    m_obj.retrieveHeaders()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksPOPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}