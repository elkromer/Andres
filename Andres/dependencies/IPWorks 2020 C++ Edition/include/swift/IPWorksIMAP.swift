
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum ImapAuthMechanisms : Int32 {
  case amUserPassword = 0
  case amCRAMMD5 = 1
  case amNTLM = 2
  case amAPOP = 3
  case amSASLPlain = 4
  case amSASLDigestMD5 = 5
  case amKerberos = 6
  case amXOAUTH2 = 7
}
public enum ImapFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum ImapMessageRecipientTypes : Int32 {
  case rtTo = 0
  case rtCc = 1
  case rtBCc = 2
}
public enum ImapSSLCertStoreTypes : Int32 {
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
public enum ImapSSLStartModes : Int32 {
  case sslAutomatic = 0
  case sslImplicit = 1
  case sslExplicit = 2
  case sslNone = 3
}


public protocol IPWorksIMAPDelegateSwift {
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onHeader(_ field: String, _ value: String)
  func onIdleInfo(_ message: String, _ cancel: inout Int32)
  func onMailboxACL(_ mailbox: String, _ user: String, _ rights: String)
  func onMailboxList(_ mailbox: String, _ separator: String, _ flags: String)
  func onMessageInfo(_ messageId: String, _ subject: String, _ messageDate: String, _ from: String, _ flags: String, _ size: Int64)
  func onMessagePart(_ partId: String, _ size: Int64, _ contentType: String, _ filename: String, _ contentEncoding: String, _ parameters: String, _ multipartMode: String, _ contentId: String, _ contentDisposition: String)
  func onPITrail(_ direction: Int32, _ message: String)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: String)
}

public enum IPWorksIMAPError : Error {
  case Error(Int32, String)
}

public class IPWorksIMAPSwift : NSObject, IPWorksIMAPDelegate {
  public var m_obj: IPWorksIMAP
  var m_delegate: IPWorksIMAPDelegateSwift?

  override init() {
    self.m_obj = IPWorksIMAP()
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

  public var delegate: IPWorksIMAPDelegateSwift? {
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

  public func onIdleInfo(_ message: String!, _ cancel: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onIdleInfo(message, &cancel.pointee)
    }
  }

  public func onMailboxACL(_ mailbox: String!, _ user: String!, _ rights: String!) {
    if (m_delegate != nil) {
      m_delegate!.onMailboxACL(mailbox, user, rights)
    }
  }

  public func onMailboxList(_ mailbox: String!, _ separator: String!, _ flags: String!) {
    if (m_delegate != nil) {
      m_delegate!.onMailboxList(mailbox, separator, flags)
    }
  }

  public func onMessageInfo(_ messageId: String!, _ subject: String!, _ messageDate: String!, _ from: String!, _ flags: String!, _ size: Int64) {
    if (m_delegate != nil) {
      m_delegate!.onMessageInfo(messageId, subject, messageDate, from, flags, size)
    }
  }

  public func onMessagePart(_ partId: String!, _ size: Int64, _ contentType: String!, _ filename: String!, _ contentEncoding: String!, _ parameters: String!, _ multipartMode: String!, _ contentId: String!, _ contentDisposition: String!) {
    if (m_delegate != nil) {
      m_delegate!.onMessagePart(partId, size, contentType, filename, contentEncoding, parameters, multipartMode, contentId, contentDisposition)
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

  public func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onTransfer(direction, bytesTransferred, percentDone, text)
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

  public var authMechanism: ImapAuthMechanisms {
    get {
      return ImapAuthMechanisms(rawValue: m_obj.authMechanism)!
    }
    set {
      m_obj.authMechanism = newValue.rawValue
    }
  }

  public var autoDecodeParts: Bool {
    get {
      return m_obj.autoDecodeParts
    }
    set {
      m_obj.autoDecodeParts = newValue
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

  public var endByte: Int64 {
    get {
      return m_obj.endByte
    }
    set {
      m_obj.endByte = newValue
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

  public var firewallType: ImapFirewallTypes {
    get {
      return ImapFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var mailbox: String {
    get {
      let ret: String? = String(m_obj.mailbox)
      return unwrapNSString(ret)
    }
    set {
      m_obj.mailbox = newValue as NSString
    }
  }

  public var mailboxFlags: String {
    get {
      let ret: String? = String(m_obj.mailboxFlags)
      return unwrapNSString(ret)
    }
  }

  public var mailboxListCount: Int32 {
    get {
      return m_obj.mailboxListCount
    }
  }

  public func mailboxListFlags(mailboxListIndex: Int32) throws -> String {
    let ret: String? = m_obj.mailboxListFlags(mailboxListIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func mailboxListName(mailboxListIndex: Int32) throws -> String {
    let ret: String? = m_obj.mailboxListName(mailboxListIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func mailboxListSeparator(mailboxListIndex: Int32) throws -> String {
    let ret: String? = m_obj.mailboxListSeparator(mailboxListIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
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

  public var messageContentEncoding: String {
    get {
      let ret: String? = String(m_obj.messageContentEncoding)
      return unwrapNSString(ret)
    }
  }

  public var messageContentType: String {
    get {
      let ret: String? = String(m_obj.messageContentType)
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

  public var messageDeliveryTime: String {
    get {
      let ret: String? = String(m_obj.messageDeliveryTime)
      return unwrapNSString(ret)
    }
  }

  public var messageFlags: String {
    get {
      let ret: String? = String(m_obj.messageFlags)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageFlags = newValue as NSString
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
    set {
      m_obj.messageHeaderCount = newValue
    }
  }

  public func messageHeaderField(messageHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageHeaderField(messageHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setMessageHeaderField(messageHeaderIndex: Int32, newMessageHeaderField: String) throws -> Void {
    m_obj.setMessageHeaderField(messageHeaderIndex, newMessageHeaderField)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func messageHeaderValue(messageHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageHeaderValue(messageHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setMessageHeaderValue(messageHeaderIndex: Int32, newMessageHeaderValue: String) throws -> Void {
    m_obj.setMessageHeaderValue(messageHeaderIndex, newMessageHeaderValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var messageHeadersString: String {
    get {
      let ret: String? = String(m_obj.messageHeadersString)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageHeadersString = newValue as NSString
    }
  }

  public var messageId: String {
    get {
      let ret: String? = String(m_obj.messageId)
      return unwrapNSString(ret)
    }
  }

  public var messageInfoCount: Int32 {
    get {
      return m_obj.messageInfoCount
    }
  }

  public func messageInfoDate(messageInfoIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageInfoDate(messageInfoIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageInfoFlags(messageInfoIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageInfoFlags(messageInfoIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageInfoFrom(messageInfoIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageInfoFrom(messageInfoIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageInfoMessageId(messageInfoIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageInfoMessageId(messageInfoIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageInfoSize(messageInfoIndex: Int32) throws -> Int64 {
    let ret: Int64? = m_obj.messageInfoSize(messageInfoIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func messageInfoSubject(messageInfoIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageInfoSubject(messageInfoIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var messageInReplyTo: String {
    get {
      let ret: String? = String(m_obj.messageInReplyTo)
      return unwrapNSString(ret)
    }
  }

  public var messageNetId: String {
    get {
      let ret: String? = String(m_obj.messageNetId)
      return unwrapNSString(ret)
    }
  }

  public var messagePartCount: Int32 {
    get {
      return m_obj.messagePartCount
    }
  }

  public func messagePartContentDisposition(messagePartIndex: Int32) throws -> String {
    let ret: String? = m_obj.messagePartContentDisposition(messagePartIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messagePartContentEncoding(messagePartIndex: Int32) throws -> String {
    let ret: String? = m_obj.messagePartContentEncoding(messagePartIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messagePartContentId(messagePartIndex: Int32) throws -> String {
    let ret: String? = m_obj.messagePartContentId(messagePartIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messagePartContentType(messagePartIndex: Int32) throws -> String {
    let ret: String? = m_obj.messagePartContentType(messagePartIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messagePartFilename(messagePartIndex: Int32) throws -> String {
    let ret: String? = m_obj.messagePartFilename(messagePartIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messagePartId(messagePartIndex: Int32) throws -> String {
    let ret: String? = m_obj.messagePartId(messagePartIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messagePartMultipartMode(messagePartIndex: Int32) throws -> String {
    let ret: String? = m_obj.messagePartMultipartMode(messagePartIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messagePartParameters(messagePartIndex: Int32) throws -> String {
    let ret: String? = m_obj.messagePartParameters(messagePartIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messagePartSize(messagePartIndex: Int32) throws -> Int64 {
    let ret: Int64? = m_obj.messagePartSize(messagePartIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public var messageRecipientCount: Int32 {
    get {
      return m_obj.messageRecipientCount
    }
  }

  public func messageRecipientAddress(recipientIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageRecipientAddress(recipientIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageRecipientName(recipientIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageRecipientName(recipientIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageRecipientOptions(recipientIndex: Int32) throws -> String {
    let ret: String? = m_obj.messageRecipientOptions(recipientIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func messageRecipientType(recipientIndex: Int32) throws -> ImapMessageRecipientTypes {
    let ret = ImapMessageRecipientTypes(rawValue: m_obj.messageRecipientType(recipientIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public var messageReplyTo: String {
    get {
      let ret: String? = String(m_obj.messageReplyTo)
      return unwrapNSString(ret)
    }
  }

  public var messageSender: String {
    get {
      let ret: String? = String(m_obj.messageSender)
      return unwrapNSString(ret)
    }
  }

  public var messageSet: String {
    get {
      let ret: String? = String(m_obj.messageSet)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageSet = newValue as NSString
    }
  }

  public var messageSize: Int64 {
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
    set {
      m_obj.messageText = newValue as NSString
    }
  }

  public var overwrite: Bool {
    get {
      return m_obj.overwrite
    }
    set {
      m_obj.overwrite = newValue
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

  public var peekMode: Bool {
    get {
      return m_obj.peekMode
    }
    set {
      m_obj.peekMode = newValue
    }
  }

  public var recentMessageCount: Int32 {
    get {
      return m_obj.recentMessageCount
    }
  }

  public var sortCriteria: String {
    get {
      let ret: String? = String(m_obj.sortCriteria)
      return unwrapNSString(ret)
    }
    set {
      m_obj.sortCriteria = newValue as NSString
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

  public var SSLCertStoreType: ImapSSLCertStoreTypes {
    get {
      return ImapSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var SSLStartMode: ImapSSLStartModes {
    get {
      return ImapSSLStartModes(rawValue: m_obj.SSLStartMode)!
    }
    set {
      m_obj.SSLStartMode = newValue.rawValue
    }
  }

  public var startByte: Int64 {
    get {
      return m_obj.startByte
    }
    set {
      m_obj.startByte = newValue
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

  public var UIDMode: Bool {
    get {
      return m_obj.UIDMode
    }
    set {
      m_obj.UIDMode = newValue
    }
  }

  public var UIDValidity: String {
    get {
      let ret: String? = String(m_obj.UIDValidity)
      return unwrapNSString(ret)
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

  public func addMessageFlags(_ flags: String) throws -> Void {
    m_obj.addMessageFlags(flags)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func appendToMailbox() throws -> Void {
    m_obj.appendToMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func checkMailbox() throws -> Void {
    m_obj.checkMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func closeMailbox() throws -> Void {
    m_obj.closeMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func connect() throws -> Void {
    m_obj.connect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func copyToMailbox() throws -> Void {
    m_obj.copyToMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func createMailbox() throws -> Void {
    m_obj.createMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func deleteFromMailbox() throws -> Void {
    m_obj.deleteFromMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func deleteMailbox() throws -> Void {
    m_obj.deleteMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func deleteMailboxACL(_ user: String) throws -> Void {
    m_obj.deleteMailboxACL(user)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func disconnect() throws -> Void {
    m_obj.disconnect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func examineMailbox() throws -> Void {
    m_obj.examineMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func expungeMailbox() throws -> Void {
    m_obj.expungeMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func fetchMessageHeaders() throws -> Void {
    m_obj.fetchMessageHeaders()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func fetchMessageInfo() throws -> Void {
    m_obj.fetchMessageInfo()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func fetchMessagePart(_ partId: String) throws -> Void {
    m_obj.fetchMessagePart(partId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func fetchMessagePartHeaders(_ partId: String) throws -> Void {
    m_obj.fetchMessagePartHeaders(partId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func fetchMessageText() throws -> Void {
    m_obj.fetchMessageText()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getMailboxACL() throws -> Void {
    m_obj.getMailboxACL()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listMailboxes() throws -> Void {
    m_obj.listMailboxes()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listSubscribedMailboxes() throws -> Void {
    m_obj.listSubscribedMailboxes()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func localizeDate(_ dateTime: String) throws -> String {
    let ret: String? = m_obj.localizeDate(dateTime)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func moveToMailbox() throws -> Void {
    m_obj.moveToMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func noop() throws -> Void {
    m_obj.noop()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func renameMailbox(_ newName: String) throws -> Void {
    m_obj.renameMailbox(newName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func resetMessageFlags() throws -> Void {
    m_obj.resetMessageFlags()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func searchMailbox(_ searchCriteria: String) throws -> Void {
    m_obj.searchMailbox(searchCriteria)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func selectMailbox() throws -> Void {
    m_obj.selectMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setMailboxACL(_ user: String, _ rights: String) throws -> Void {
    m_obj.setMailboxACL(user, rights)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func startIdle() throws -> Void {
    m_obj.startIdle()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func stopIdle() throws -> Void {
    m_obj.stopIdle()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func subscribeMailbox() throws -> Void {
    m_obj.subscribeMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func unsetMessageFlags() throws -> Void {
    m_obj.unsetMessageFlags()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func unsubscribeMailbox() throws -> Void {
    m_obj.unsubscribeMailbox()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIMAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}