
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum XmppBuddySubscriptions : Int32 {
  case stNone = 0
  case stTo = 1
  case stFrom = 2
  case stBoth = 3
  case stRemove = 4
}
public enum XmppFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum XmppMessageTypes : Int32 {
  case mtNormal = 0
  case mtChat = 1
  case mtGroupChat = 2
  case mtHeadline = 3
  case mtError = 4
}
public enum XmppPresences : Int32 {
  case pcOffline = 0
  case pcChat = 1
  case pcAway = 2
  case pcXA = 3
  case pcDND = 4
}
public enum XmppSSLCertStoreTypes : Int32 {
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
public enum XmppSSLStartModes : Int32 {
  case sslAutomatic = 0
  case sslImplicit = 1
  case sslExplicit = 2
  case sslNone = 3
}


public protocol IPWorksXMPPDelegateSwift {
  func onBuddyUpdate(_ buddyIdx: Int32)
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32, _ fileId: String, _ filename: String, _ success: Bool)
  func onError(_ errorCode: Int32, _ description: String)
  func onIQ(_ iq: String, _ id: String, _ from: String, _ iqType: String, _ ignore: inout Int32)
  func onMessageIn(_ messageId: String, _ from: String, _ domain: String, _ resource: String, _ messageType: Int32, _ subject: String, _ messageThread: String, _ messageText: String, _ messageHTML: String, _ other: String)
  func onPITrail(_ direction: Int32, _ pi: String)
  func onPresence(_ user: String, _ domain: String, _ resource: String, _ availability: Int32, _ status: String)
  func onReadyToSend()
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32, _ fileId: String, _ user: String, _ domain: String, _ resource: String, _ filename: inout NSString?, _ datetime: String, _ size: Int64, _ accept: inout Int32)
  func onSubscriptionRequest(_ from: String, _ domain: String, _ accept: inout Int32)
  func onSync()
  func onTransfer(_ direction: Int32, _ fileId: String, _ filename: String, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data, _ cancel: inout Int32)
}

public enum IPWorksXMPPError : Error {
  case Error(Int32, String)
}

public class IPWorksXMPPSwift : NSObject, IPWorksXMPPDelegate {
  public var m_obj: IPWorksXMPP
  var m_delegate: IPWorksXMPPDelegateSwift?

  override init() {
    self.m_obj = IPWorksXMPP()
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

  public var delegate: IPWorksXMPPDelegateSwift? {
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

  public func onBuddyUpdate(_ buddyIdx: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onBuddyUpdate(buddyIdx)
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

  public func onDisconnected(_ statusCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onDisconnected(statusCode, description)
    }
  }

  public func onEndTransfer(_ direction: Int32, _ fileId: String!, _ filename: String!, _ success: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onEndTransfer(direction, fileId, filename, success)
    }
  }

  public func onError(_ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(errorCode, description)
    }
  }

  public func onIQ(_ iq: String!, _ id: String!, _ from: String!, _ iqType: String!, _ ignore: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onIQ(iq, id, from, iqType, &ignore.pointee)
    }
  }

  public func onMessageIn(_ messageId: String!, _ from: String!, _ domain: String!, _ resource: String!, _ messageType: Int32, _ subject: String!, _ messageThread: String!, _ messageText: String!, _ messageHTML: String!, _ other: String!) {
    if (m_delegate != nil) {
      m_delegate!.onMessageIn(messageId, from, domain, resource, messageType, subject, messageThread, messageText, messageHTML, other)
    }
  }

  public func onPITrail(_ direction: Int32, _ pi: String!) {
    if (m_delegate != nil) {
      m_delegate!.onPITrail(direction, pi)
    }
  }

  public func onPresence(_ user: String!, _ domain: String!, _ resource: String!, _ availability: Int32, _ status: String!) {
    if (m_delegate != nil) {
      m_delegate!.onPresence(user, domain, resource, availability, status)
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

  public func onStartTransfer(_ direction: Int32, _ fileId: String!, _ user: String!, _ domain: String!, _ resource: String!, _ filename: AutoreleasingUnsafeMutablePointer<NSString?>, _ datetime: String!, _ size: Int64, _ accept: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onStartTransfer(direction, fileId, user, domain, resource, &filename.pointee, datetime, size, &accept.pointee)
    }
  }

  public func onSubscriptionRequest(_ from: String!, _ domain: String!, _ accept: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onSubscriptionRequest(from, domain, &accept.pointee)
    }
  }

  public func onSync() {
    if (m_delegate != nil) {
      m_delegate!.onSync()
    }
  }

  public func onTransfer(_ direction: Int32, _ fileId: String!, _ filename: String!, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data!, _ cancel: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onTransfer(direction, fileId, filename, bytesTransferred, percentDone, text, &cancel.pointee)
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

  public var authDomain: String {
    get {
      let ret: String? = String(m_obj.authDomain)
      return unwrapNSString(ret)
    }
    set {
      m_obj.authDomain = newValue as NSString
    }
  }

  public var authMethods: String {
    get {
      let ret: String? = String(m_obj.authMethods)
      return unwrapNSString(ret)
    }
    set {
      m_obj.authMethods = newValue as NSString
    }
  }

  public var buddyCount: Int32 {
    get {
      return m_obj.buddyCount
    }
  }

  public func buddyGroup(buddyIndex: Int32) throws -> String {
    let ret: String? = m_obj.buddyGroup(buddyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setBuddyGroup(buddyIndex: Int32, newBuddyGroup: String) throws -> Void {
    m_obj.setBuddyGroup(buddyIndex, newBuddyGroup)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func buddyId(buddyIndex: Int32) throws -> String {
    let ret: String? = m_obj.buddyId(buddyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func buddyNickName(buddyIndex: Int32) throws -> String {
    let ret: String? = m_obj.buddyNickName(buddyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setBuddyNickName(buddyIndex: Int32, newBuddyNickName: String) throws -> Void {
    m_obj.setBuddyNickName(buddyIndex, newBuddyNickName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func buddyRealName(buddyIndex: Int32) throws -> String {
    let ret: String? = m_obj.buddyRealName(buddyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func buddySubscription(buddyIndex: Int32) throws -> XmppBuddySubscriptions {
    let ret = XmppBuddySubscriptions(rawValue: m_obj.buddySubscription(buddyIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
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

  public var firewallType: XmppFirewallTypes {
    get {
      return XmppFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var IMPort: Int32 {
    get {
      return m_obj.IMPort
    }
    set {
      m_obj.IMPort = newValue
    }
  }

  public var IMServer: String {
    get {
      let ret: String? = String(m_obj.IMServer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.IMServer = newValue as NSString
    }
  }

  public var localDirectory: String {
    get {
      let ret: String? = String(m_obj.localDirectory)
      return unwrapNSString(ret)
    }
    set {
      m_obj.localDirectory = newValue as NSString
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

  public var messageHTML: String {
    get {
      let ret: String? = String(m_obj.messageHTML)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageHTML = newValue as NSString
    }
  }

  public var messageOtherData: String {
    get {
      let ret: String? = String(m_obj.messageOtherData)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageOtherData = newValue as NSString
    }
  }

  public var messageSubject: String {
    get {
      let ret: String? = String(m_obj.messageSubject)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageSubject = newValue as NSString
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

  public var messageThread: String {
    get {
      let ret: String? = String(m_obj.messageThread)
      return unwrapNSString(ret)
    }
    set {
      m_obj.messageThread = newValue as NSString
    }
  }

  public var messageType: XmppMessageTypes {
    get {
      return XmppMessageTypes(rawValue: m_obj.messageType)!
    }
    set {
      m_obj.messageType = newValue.rawValue
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

  public var presence: XmppPresences {
    get {
      return XmppPresences(rawValue: m_obj.presence)!
    }
    set {
      m_obj.presence = newValue.rawValue
    }
  }

  public var resource: String {
    get {
      let ret: String? = String(m_obj.resource)
      return unwrapNSString(ret)
    }
    set {
      m_obj.resource = newValue as NSString
    }
  }

  public var serverDomain: String {
    get {
      let ret: String? = String(m_obj.serverDomain)
      return unwrapNSString(ret)
    }
    set {
      m_obj.serverDomain = newValue as NSString
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

  public var SSLCertStoreType: XmppSSLCertStoreTypes {
    get {
      return XmppSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var SSLStartMode: XmppSSLStartModes {
    get {
      return XmppSSLStartModes(rawValue: m_obj.SSLStartMode)!
    }
    set {
      m_obj.SSLStartMode = newValue.rawValue
    }
  }

  public var status: String {
    get {
      let ret: String? = String(m_obj.status)
      return unwrapNSString(ret)
    }
    set {
      m_obj.status = newValue as NSString
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

  public var userDomain: String {
    get {
      let ret: String? = String(m_obj.userDomain)
      return unwrapNSString(ret)
    }
    set {
      m_obj.userDomain = newValue as NSString
    }
  }

  public var userInfoCount: Int32 {
    get {
      return m_obj.userInfoCount
    }
    set {
      m_obj.userInfoCount = newValue
    }
  }

  public func userInfoField(fieldIndex: Int32) throws -> String {
    let ret: String? = m_obj.userInfoField(fieldIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setUserInfoField(fieldIndex: Int32, newUserInfoField: String) throws -> Void {
    m_obj.setUserInfoField(fieldIndex, newUserInfoField)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func userInfoValue(fieldIndex: Int32) throws -> String {
    let ret: String? = m_obj.userInfoValue(fieldIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setUserInfoValue(fieldIndex: Int32, newUserInfoValue: String) throws -> Void {
    m_obj.setUserInfoValue(fieldIndex, newUserInfoValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  /* Methods */

  public func add(_ jabberId: String, _ name: String, _ groups: String) throws -> Void {
    m_obj.add(jabberId, name, groups)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func cancel(_ jabberId: String) throws -> Void {
    m_obj.cancel(jabberId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func changePassword(_ password: String) throws -> Void {
    m_obj.changePassword(password)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func changePresence(_ presenceCode: Int32, _ status: String) throws -> Void {
    m_obj.changePresence(presenceCode, status)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func connect(_ user: String, _ password: String) throws -> Void {
    m_obj.connect(user, password)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func disconnect() throws -> Void {
    m_obj.disconnect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func probePresence(_ jabberId: String) throws -> Void {
    m_obj.probePresence(jabberId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func queryRegister(_ XMPPServer: String) throws -> Void {
    m_obj.queryRegister(XMPPServer)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func registerUser(_ XMPPServer: String) throws -> Void {
    m_obj.registerUser(XMPPServer)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func remove(_ jabberId: String, _ name: String, _ group: String) throws -> Void {
    m_obj.remove(jabberId, name, group)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func retrieveRoster() throws -> Void {
    m_obj.retrieveRoster()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func sendCommand(_ command: String) throws -> Void {
    m_obj.sendCommand(command)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func sendFile(_ jabberId: String) throws -> Void {
    m_obj.sendFile(jabberId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func sendMessage(_ jabberId: String) throws -> String {
    let ret: String? = m_obj.sendMessage(jabberId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setUserInfo(_ field: String, _ value: String) throws -> Void {
    m_obj.setUserInfo(field, value)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func subscribeTo(_ jabberId: String) throws -> Void {
    m_obj.subscribeTo(jabberId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func unregister() throws -> Void {
    m_obj.unregister()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func unsubscribeTo(_ jabberId: String) throws -> Void {
    m_obj.unsubscribeTo(jabberId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMPPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}