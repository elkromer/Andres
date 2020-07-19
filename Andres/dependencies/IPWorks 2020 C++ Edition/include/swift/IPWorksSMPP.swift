
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum SmppFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum SmppMessagePriorities : Int32 {
  case smppMessagePriorityLow = 0
  case smppMessagePriorityNormal = 1
  case smppMessagePriorityHigh = 2
  case smppMessagePriorityUrgent = 3
}
public enum SmppProtocols : Int32 {
  case smppSMPP = 0
  case smppCIMD2 = 1
}
public enum SmppRecipientTypes : Int32 {
  case smppRecipientTypeNormal = 0
  case smppRecipientTypeList = 1
}
public enum SmppServiceTypes : Int32 {
  case smppServiceDefault = 0
  case smppServiceCMT = 1
  case smppServiceCPT = 2
  case smppServiceVMN = 3
  case smppServiceVMA = 4
  case smppServiceWAP = 5
  case smppServiceUSSD = 6
  case smppServiceCBS = 7
}
public enum SmppSMPPVersions : Int32 {
  case smppVersion50 = 0
  case smppVersion34 = 1
  case smppVersion33 = 2
}
public enum SmppSSLCertStoreTypes : Int32 {
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
public enum SmppSSLStartModes : Int32 {
  case sslAutomatic = 0
  case sslImplicit = 1
  case sslExplicit = 2
  case sslNone = 3
}


public protocol IPWorksSMPPDelegateSwift {
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onError(_ errorCode: Int32, _ description: String)
  func onMessageIn(_ sourceAddress: String, _ scheduleDeliveryTime: String, _ validityPeriod: String, _ message: String, _ messagePart: Int32, _ messagePartCount: Int32, _ messagePartReference: Int32, _ destinationAddress: String, _ responseErrorCode: inout Int32)
  func onMessageStatus(_ messageId: String, _ messageState: Int32, _ messageError: Int32, _ finalDate: String)
  func onPITrail(_ direction: Int32, _ PDU: Data, _ commandLength: Int32, _ commandId: Int32, _ commandDescription: String, _ commandStatus: String, _ sequenceNumber: Int32)
  func onReadyToSend()
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
}

public enum IPWorksSMPPError : Error {
  case Error(Int32, String)
}

public class IPWorksSMPPSwift : NSObject, IPWorksSMPPDelegate {
  public var m_obj: IPWorksSMPP
  var m_delegate: IPWorksSMPPDelegateSwift?

  override init() {
    self.m_obj = IPWorksSMPP()
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

  public var delegate: IPWorksSMPPDelegateSwift? {
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

  public func onMessageIn(_ sourceAddress: String!, _ scheduleDeliveryTime: String!, _ validityPeriod: String!, _ message: String!, _ messagePart: Int32, _ messagePartCount: Int32, _ messagePartReference: Int32, _ destinationAddress: String!, _ responseErrorCode: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onMessageIn(sourceAddress, scheduleDeliveryTime, validityPeriod, message, messagePart, messagePartCount, messagePartReference, destinationAddress, &responseErrorCode.pointee)
    }
  }

  public func onMessageStatus(_ messageId: String!, _ messageState: Int32, _ messageError: Int32, _ finalDate: String!) {
    if (m_delegate != nil) {
      m_delegate!.onMessageStatus(messageId, messageState, messageError, finalDate)
    }
  }

  public func onPITrail(_ direction: Int32, _ PDU: Data!, _ commandLength: Int32, _ commandId: Int32, _ commandDescription: String!, _ commandStatus: String!, _ sequenceNumber: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onPITrail(direction, PDU, commandLength, commandId, commandDescription, commandStatus, sequenceNumber)
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

  public var connected: Bool {
    get {
      return m_obj.connected
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

  public var firewallType: SmppFirewallTypes {
    get {
      return SmppFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var localHost: String {
    get {
      let ret: String? = String(m_obj.localHost)
      return unwrapNSString(ret)
    }
    set {
      m_obj.localHost = newValue as NSString
    }
  }

  public var messageExpiration: String {
    get {
      let ret: String? = String(m_obj.messageExpiration)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageExpiration = newValue as NSString
    }
  }

  public var messageId: String {
    get {
      let ret: String? = String(m_obj.messageId)
      return unwrapNSString(ret)
    }
  }

  public var messagePriority: SmppMessagePriorities {
    get {
      return SmppMessagePriorities(rawValue: m_obj.messagePriority)!
    }
    set {
      m_obj.messagePriority = newValue.rawValue
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

  public var protocol_: SmppProtocols {
    get {
      return SmppProtocols(rawValue: m_obj.protocol_())!
    }
    set {
      m_obj.setProtocol_(newValue.rawValue)
    }
  }

  public var recipientCount: Int32 {
    get {
      return m_obj.recipientCount
    }
    set {
      m_obj.recipientCount = newValue
    }
  }

  public func recipientAddress(recipientIndex: Int32) throws -> String {
    let ret: String? = m_obj.recipientAddress(recipientIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setRecipientAddress(recipientIndex: Int32, newRecipientAddress: String) throws -> Void {
    m_obj.setRecipientAddress(recipientIndex, newRecipientAddress)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func recipientType(recipientIndex: Int32) throws -> SmppRecipientTypes {
    let ret = SmppRecipientTypes(rawValue: m_obj.recipientType(recipientIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func setRecipientType(recipientIndex: Int32, newRecipientType: SmppRecipientTypes) throws -> Void {
    m_obj.setRecipientType(recipientIndex, newRecipientType.rawValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var scheduledDelivery: String {
    get {
      let ret: String? = String(m_obj.scheduledDelivery)
      return unwrapNSString(ret)
    }
    set {
      m_obj.scheduledDelivery = newValue as NSString
    }
  }

  public var senderAddress: String {
    get {
      let ret: String? = String(m_obj.senderAddress)
      return unwrapNSString(ret)
    }
    set {
      m_obj.senderAddress = newValue as NSString
    }
  }

  public var serviceType: SmppServiceTypes {
    get {
      return SmppServiceTypes(rawValue: m_obj.serviceType)!
    }
    set {
      m_obj.serviceType = newValue.rawValue
    }
  }

  public var SMPPPort: Int32 {
    get {
      return m_obj.SMPPPort
    }
    set {
      m_obj.SMPPPort = newValue
    }
  }

  public var SMPPServer: String {
    get {
      let ret: String? = String(m_obj.SMPPServer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.SMPPServer = newValue as NSString
    }
  }

  public var SMPPVersion: SmppSMPPVersions {
    get {
      return SmppSMPPVersions(rawValue: m_obj.SMPPVersion)!
    }
    set {
      m_obj.SMPPVersion = newValue.rawValue
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

  public var SSLCertStoreType: SmppSSLCertStoreTypes {
    get {
      return SmppSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var SSLStartMode: SmppSSLStartModes {
    get {
      return SmppSSLStartModes(rawValue: m_obj.SSLStartMode)!
    }
    set {
      m_obj.SSLStartMode = newValue.rawValue
    }
  }

  public var systemType: String {
    get {
      let ret: String? = String(m_obj.systemType)
      return unwrapNSString(ret)
    }
    set {
      m_obj.systemType = newValue as NSString
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

  public var userId: String {
    get {
      let ret: String? = String(m_obj.userId)
      return unwrapNSString(ret)
    }
    set {
      m_obj.userId = newValue as NSString
    }
  }

  /* Methods */

  public func addRecipient(_ recipientType: Int32, _ recipientAddress: String) throws -> Void {
    m_obj.addRecipient(recipientType, recipientAddress)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func cancelMessage(_ messageId: String) throws -> Void {
    m_obj.cancelMessage(messageId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func checkLink() throws -> Void {
    m_obj.checkLink()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func checkMessageStatus(_ messageId: String) throws -> Void {
    m_obj.checkMessageStatus(messageId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func connect(_ userId: String, _ password: String) throws -> Void {
    m_obj.connect(userId, password)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func disconnect() throws -> Void {
    m_obj.disconnect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func replaceMessage(_ messageId: String, _ newMessage: String) throws -> Void {
    m_obj.replaceMessage(messageId, newMessage)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func sendCommand(_ commandId: Int32, _ payload: Data) throws -> Data {
    let ret: Data? = m_obj.sendCommand(commandId, payload)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapData(ret)
  }

  public func sendData(_ data: Data) throws -> String {
    let ret: String? = m_obj.sendData(data)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func sendMessage(_ message: String) throws -> String {
    let ret: String? = m_obj.sendMessage(message)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksSMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

}