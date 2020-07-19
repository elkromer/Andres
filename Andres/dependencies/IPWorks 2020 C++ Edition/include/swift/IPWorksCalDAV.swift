
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum CaldavAlarmActions : Int32 {
  case aNoAlarm = 0
  case aAudio = 1
  case aDisplay = 2
  case aEmail = 3
}
public enum CaldavAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
  case authOAuth = 6
}
public enum CaldavDepths : Int32 {
  case dpUnspecified = 0
  case dpResourceOnly = 1
  case dpImmediateChildren = 2
  case dpInfinity = 3
}
public enum CaldavEventTypes : Int32 {
  case vEvent = 0
  case vTodo = 1
  case vJournal = 2
  case vFreeBusy = 3
}
public enum CaldavFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum CaldavFollowRedirects : Int32 {
  case frNever = 0
  case frAlways = 1
  case frSameScheme = 2
}
public enum CaldavProxyAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
}
public enum CaldavProxySSLs : Int32 {
  case psAutomatic = 0
  case psAlways = 1
  case psNever = 2
  case psTunnel = 3
}
public enum CaldavReportFilterEventTypes : Int32 {
  case vtEvent = 0
  case vtTodo = 1
  case vtJournal = 2
  case vtFreeBusy = 3
  case vtAll = 4
}
public enum CaldavSSLCertStoreTypes : Int32 {
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


public protocol IPWorksCalDAVDelegateSwift {
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onEventDetails(_ resourceURI: String, _ responseStatus: String, _ ETag: String, _ calendarData: String)
  func onFreeBusy(_ busyType: String, _ busyRange: String)
  func onHeader(_ field: String, _ value: String)
  func onLog(_ logLevel: Int32, _ message: String, _ logType: String)
  func onRedirect(_ location: String, _ accept: inout Int32)
  func onSetCookie(_ name: String, _ value: String, _ expires: String, _ domain: String, _ path: String, _ secure: Bool)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32)
  func onStatus(_ HTTPVersion: String, _ statusCode: Int32, _ description: String)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data)
}

public enum IPWorksCalDAVError : Error {
  case Error(Int32, String)
}

public class IPWorksCalDAVSwift : NSObject, IPWorksCalDAVDelegate {
  public var m_obj: IPWorksCalDAV
  var m_delegate: IPWorksCalDAVDelegateSwift?

  override init() {
    self.m_obj = IPWorksCalDAV()
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

  public var delegate: IPWorksCalDAVDelegateSwift? {
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

  public func onEventDetails(_ resourceURI: String!, _ responseStatus: String!, _ ETag: String!, _ calendarData: String!) {
    if (m_delegate != nil) {
      m_delegate!.onEventDetails(resourceURI, responseStatus, ETag, calendarData)
    }
  }

  public func onFreeBusy(_ busyType: String!, _ busyRange: String!) {
    if (m_delegate != nil) {
      m_delegate!.onFreeBusy(busyType, busyRange)
    }
  }

  public func onHeader(_ field: String!, _ value: String!) {
    if (m_delegate != nil) {
      m_delegate!.onHeader(field, value)
    }
  }

  public func onLog(_ logLevel: Int32, _ message: String!, _ logType: String!) {
    if (m_delegate != nil) {
      m_delegate!.onLog(logLevel, message, logType)
    }
  }

  public func onRedirect(_ location: String!, _ accept: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onRedirect(location, &accept.pointee)
    }
  }

  public func onSetCookie(_ name: String!, _ value: String!, _ expires: String!, _ domain: String!, _ path: String!, _ secure: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onSetCookie(name, value, expires, domain, path, secure)
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

  public func onStatus(_ HTTPVersion: String!, _ statusCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onStatus(HTTPVersion, statusCode, description)
    }
  }

  public func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data!) {
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

  public var alarmCount: Int32 {
    get {
      return m_obj.alarmCount
    }
    set {
      m_obj.alarmCount = newValue
    }
  }

  public func alarmAction(alarmIndex: Int32) throws -> CaldavAlarmActions {
    let ret = CaldavAlarmActions(rawValue: m_obj.alarmAction(alarmIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func setAlarmAction(alarmIndex: Int32, newAlarmAction: CaldavAlarmActions) throws -> Void {
    m_obj.setAlarmAction(alarmIndex, newAlarmAction.rawValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func alarmAttachment(alarmIndex: Int32) throws -> String {
    let ret: String? = m_obj.alarmAttachment(alarmIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setAlarmAttachment(alarmIndex: Int32, newAlarmAttachment: String) throws -> Void {
    m_obj.setAlarmAttachment(alarmIndex, newAlarmAttachment)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func alarmAttachmentType(alarmIndex: Int32) throws -> String {
    let ret: String? = m_obj.alarmAttachmentType(alarmIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setAlarmAttachmentType(alarmIndex: Int32, newAlarmAttachmentType: String) throws -> Void {
    m_obj.setAlarmAttachmentType(alarmIndex, newAlarmAttachmentType)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func alarmDuration(alarmIndex: Int32) throws -> String {
    let ret: String? = m_obj.alarmDuration(alarmIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setAlarmDuration(alarmIndex: Int32, newAlarmDuration: String) throws -> Void {
    m_obj.setAlarmDuration(alarmIndex, newAlarmDuration)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func alarmMessage(alarmIndex: Int32) throws -> String {
    let ret: String? = m_obj.alarmMessage(alarmIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setAlarmMessage(alarmIndex: Int32, newAlarmMessage: String) throws -> Void {
    m_obj.setAlarmMessage(alarmIndex, newAlarmMessage)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func alarmRecipient(alarmIndex: Int32) throws -> String {
    let ret: String? = m_obj.alarmRecipient(alarmIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setAlarmRecipient(alarmIndex: Int32, newAlarmRecipient: String) throws -> Void {
    m_obj.setAlarmRecipient(alarmIndex, newAlarmRecipient)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func alarmRepeat(alarmIndex: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.alarmRepeat(alarmIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func setAlarmRepeat(alarmIndex: Int32, newAlarmRepeat: Int32) throws -> Void {
    m_obj.setAlarmRepeat(alarmIndex, newAlarmRepeat)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func alarmSubject(alarmIndex: Int32) throws -> String {
    let ret: String? = m_obj.alarmSubject(alarmIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setAlarmSubject(alarmIndex: Int32, newAlarmSubject: String) throws -> Void {
    m_obj.setAlarmSubject(alarmIndex, newAlarmSubject)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func alarmTrigger(alarmIndex: Int32) throws -> String {
    let ret: String? = m_obj.alarmTrigger(alarmIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setAlarmTrigger(alarmIndex: Int32, newAlarmTrigger: String) throws -> Void {
    m_obj.setAlarmTrigger(alarmIndex, newAlarmTrigger)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var attendees: String {
    get {
      let ret: String? = String(m_obj.attendees)
      return unwrapNSString(ret)
    }
    set {
      m_obj.attendees = newValue as NSString
    }
  }

  public var authorization: String {
    get {
      let ret: String? = String(m_obj.authorization)
      return unwrapNSString(ret)
    }
    set {
      m_obj.authorization = newValue as NSString
    }
  }

  public var authScheme: CaldavAuthSchemes {
    get {
      return CaldavAuthSchemes(rawValue: m_obj.authScheme)!
    }
    set {
      m_obj.authScheme = newValue.rawValue
    }
  }

  public var categories: String {
    get {
      let ret: String? = String(m_obj.categories)
      return unwrapNSString(ret)
    }
    set {
      m_obj.categories = newValue as NSString
    }
  }

  public var classification: String {
    get {
      let ret: String? = String(m_obj.classification)
      return unwrapNSString(ret)
    }
    set {
      m_obj.classification = newValue as NSString
    }
  }

  public var completed: String {
    get {
      let ret: String? = String(m_obj.completed)
      return unwrapNSString(ret)
    }
    set {
      m_obj.completed = newValue as NSString
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

  public var cookieCount: Int32 {
    get {
      return m_obj.cookieCount
    }
    set {
      m_obj.cookieCount = newValue
    }
  }

  public func cookieDomain(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieDomain(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieExpiration(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieExpiration(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieName(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieName(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieName(cookieIndex: Int32, newCookieName: String) throws -> Void {
    m_obj.setCookieName(cookieIndex, newCookieName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func cookiePath(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookiePath(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieSecure(cookieIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.cookieSecure(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func cookieValue(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieValue(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieValue(cookieIndex: Int32, newCookieValue: String) throws -> Void {
    m_obj.setCookieValue(cookieIndex, newCookieValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var created: String {
    get {
      let ret: String? = String(m_obj.created)
      return unwrapNSString(ret)
    }
    set {
      m_obj.created = newValue as NSString
    }
  }

  public var customPropertyCount: Int32 {
    get {
      return m_obj.customPropertyCount
    }
    set {
      m_obj.customPropertyCount = newValue
    }
  }

  public func customPropertyAttribute(customPropertyIndex: Int32) throws -> String {
    let ret: String? = m_obj.customPropertyAttribute(customPropertyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCustomPropertyAttribute(customPropertyIndex: Int32, newCustomPropertyAttribute: String) throws -> Void {
    m_obj.setCustomPropertyAttribute(customPropertyIndex, newCustomPropertyAttribute)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func customPropertyName(customPropertyIndex: Int32) throws -> String {
    let ret: String? = m_obj.customPropertyName(customPropertyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCustomPropertyName(customPropertyIndex: Int32, newCustomPropertyName: String) throws -> Void {
    m_obj.setCustomPropertyName(customPropertyIndex, newCustomPropertyName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func customPropertyValue(customPropertyIndex: Int32) throws -> String {
    let ret: String? = m_obj.customPropertyValue(customPropertyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCustomPropertyValue(customPropertyIndex: Int32, newCustomPropertyValue: String) throws -> Void {
    m_obj.setCustomPropertyValue(customPropertyIndex, newCustomPropertyValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var depth: CaldavDepths {
    get {
      return CaldavDepths(rawValue: m_obj.depth)!
    }
    set {
      m_obj.depth = newValue.rawValue
    }
  }

  public var description_: String {
    get {
      let ret: String? = m_obj.description_()
      return unwrapNSString(ret)
    }
    set {
      m_obj.setDescription_(newValue)
    }
  }

  public var displayName: String {
    get {
      let ret: String? = String(m_obj.displayName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.displayName = newValue as NSString
    }
  }

  public var dueDate: String {
    get {
      let ret: String? = String(m_obj.dueDate)
      return unwrapNSString(ret)
    }
    set {
      m_obj.dueDate = newValue as NSString
    }
  }

  public var duration: String {
    get {
      let ret: String? = String(m_obj.duration)
      return unwrapNSString(ret)
    }
    set {
      m_obj.duration = newValue as NSString
    }
  }

  public var endDate: String {
    get {
      let ret: String? = String(m_obj.endDate)
      return unwrapNSString(ret)
    }
    set {
      m_obj.endDate = newValue as NSString
    }
  }

  public var ETag: String {
    get {
      let ret: String? = String(m_obj.ETag)
      return unwrapNSString(ret)
    }
    set {
      m_obj.ETag = newValue as NSString
    }
  }

  public var eventType: CaldavEventTypes {
    get {
      return CaldavEventTypes(rawValue: m_obj.eventType)!
    }
    set {
      m_obj.eventType = newValue.rawValue
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

  public var firewallType: CaldavFirewallTypes {
    get {
      return CaldavFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var followRedirects: CaldavFollowRedirects {
    get {
      return CaldavFollowRedirects(rawValue: m_obj.followRedirects)!
    }
    set {
      m_obj.followRedirects = newValue.rawValue
    }
  }

  public var freeBusyCount: Int32 {
    get {
      return m_obj.freeBusyCount
    }
  }

  public func freeBusyRange(freeBusyIndex: Int32) throws -> String {
    let ret: String? = m_obj.freeBusyRange(freeBusyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func freeBusyType(freeBusyIndex: Int32) throws -> String {
    let ret: String? = m_obj.freeBusyType(freeBusyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var idle: Bool {
    get {
      return m_obj.idle
    }
  }

  public var lastModified: String {
    get {
      let ret: String? = String(m_obj.lastModified)
      return unwrapNSString(ret)
    }
    set {
      m_obj.lastModified = newValue as NSString
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

  public var location: String {
    get {
      let ret: String? = String(m_obj.location)
      return unwrapNSString(ret)
    }
    set {
      m_obj.location = newValue as NSString
    }
  }

  public var lockType: String {
    get {
      let ret: String? = String(m_obj.lockType)
      return unwrapNSString(ret)
    }
    set {
      m_obj.lockType = newValue as NSString
    }
  }

  public var lockOwner: String {
    get {
      let ret: String? = String(m_obj.lockOwner)
      return unwrapNSString(ret)
    }
    set {
      m_obj.lockOwner = newValue as NSString
    }
  }

  public var lockScope: String {
    get {
      let ret: String? = String(m_obj.lockScope)
      return unwrapNSString(ret)
    }
    set {
      m_obj.lockScope = newValue as NSString
    }
  }

  public var lockTimeout: Int32 {
    get {
      return m_obj.lockTimeout
    }
    set {
      m_obj.lockTimeout = newValue
    }
  }

  public var lockTokens: String {
    get {
      let ret: String? = String(m_obj.lockTokens)
      return unwrapNSString(ret)
    }
    set {
      m_obj.lockTokens = newValue as NSString
    }
  }

  public var organizer: String {
    get {
      let ret: String? = String(m_obj.organizer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.organizer = newValue as NSString
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

  public var parsedHeaderCount: Int32 {
    get {
      return m_obj.parsedHeaderCount
    }
  }

  public func parsedHeaderField(parsedHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.parsedHeaderField(parsedHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func parsedHeaderValue(parsedHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.parsedHeaderValue(parsedHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
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

  public var priority: Int32 {
    get {
      return m_obj.priority
    }
    set {
      m_obj.priority = newValue
    }
  }

  public var proxyAuthScheme: CaldavProxyAuthSchemes {
    get {
      return CaldavProxyAuthSchemes(rawValue: m_obj.proxyAuthScheme)!
    }
    set {
      m_obj.proxyAuthScheme = newValue.rawValue
    }
  }

  public var proxyAutoDetect: Bool {
    get {
      return m_obj.proxyAutoDetect
    }
    set {
      m_obj.proxyAutoDetect = newValue
    }
  }

  public var proxyPassword: String {
    get {
      let ret: String? = String(m_obj.proxyPassword)
      return unwrapNSString(ret)
    }
    set {
      m_obj.proxyPassword = newValue as NSString
    }
  }

  public var proxyPort: Int32 {
    get {
      return m_obj.proxyPort
    }
    set {
      m_obj.proxyPort = newValue
    }
  }

  public var proxyServer: String {
    get {
      let ret: String? = String(m_obj.proxyServer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.proxyServer = newValue as NSString
    }
  }

  public var proxySSL: CaldavProxySSLs {
    get {
      return CaldavProxySSLs(rawValue: m_obj.proxySSL)!
    }
    set {
      m_obj.proxySSL = newValue.rawValue
    }
  }

  public var proxyUser: String {
    get {
      let ret: String? = String(m_obj.proxyUser)
      return unwrapNSString(ret)
    }
    set {
      m_obj.proxyUser = newValue as NSString
    }
  }

  public var recurrenceDates: String {
    get {
      let ret: String? = String(m_obj.recurrenceDates)
      return unwrapNSString(ret)
    }
    set {
      m_obj.recurrenceDates = newValue as NSString
    }
  }

  public var recurrenceExceptionDates: String {
    get {
      let ret: String? = String(m_obj.recurrenceExceptionDates)
      return unwrapNSString(ret)
    }
    set {
      m_obj.recurrenceExceptionDates = newValue as NSString
    }
  }

  public var recurrenceExceptionRule: String {
    get {
      let ret: String? = String(m_obj.recurrenceExceptionRule)
      return unwrapNSString(ret)
    }
    set {
      m_obj.recurrenceExceptionRule = newValue as NSString
    }
  }

  public var recurrenceId: String {
    get {
      let ret: String? = String(m_obj.recurrenceId)
      return unwrapNSString(ret)
    }
    set {
      m_obj.recurrenceId = newValue as NSString
    }
  }

  public var recurrenceRule: String {
    get {
      let ret: String? = String(m_obj.recurrenceRule)
      return unwrapNSString(ret)
    }
    set {
      m_obj.recurrenceRule = newValue as NSString
    }
  }

  public var reportFilterAlarmEnd: String {
    get {
      let ret: String? = String(m_obj.reportFilterAlarmEnd)
      return unwrapNSString(ret)
    }
    set {
      m_obj.reportFilterAlarmEnd = newValue as NSString
    }
  }

  public var reportFilterAlarmStart: String {
    get {
      let ret: String? = String(m_obj.reportFilterAlarmStart)
      return unwrapNSString(ret)
    }
    set {
      m_obj.reportFilterAlarmStart = newValue as NSString
    }
  }

  public var reportFilterCustomFilter: String {
    get {
      let ret: String? = String(m_obj.reportFilterCustomFilter)
      return unwrapNSString(ret)
    }
    set {
      m_obj.reportFilterCustomFilter = newValue as NSString
    }
  }

  public var reportFilterEndDate: String {
    get {
      let ret: String? = String(m_obj.reportFilterEndDate)
      return unwrapNSString(ret)
    }
    set {
      m_obj.reportFilterEndDate = newValue as NSString
    }
  }

  public var reportFilterEventType: CaldavReportFilterEventTypes {
    get {
      return CaldavReportFilterEventTypes(rawValue: m_obj.reportFilterEventType)!
    }
    set {
      m_obj.reportFilterEventType = newValue.rawValue
    }
  }

  public var reportFilterProperty: String {
    get {
      let ret: String? = String(m_obj.reportFilterProperty)
      return unwrapNSString(ret)
    }
    set {
      m_obj.reportFilterProperty = newValue as NSString
    }
  }

  public var reportFilterRecurEnd: String {
    get {
      let ret: String? = String(m_obj.reportFilterRecurEnd)
      return unwrapNSString(ret)
    }
    set {
      m_obj.reportFilterRecurEnd = newValue as NSString
    }
  }

  public var reportFilterRecurStart: String {
    get {
      let ret: String? = String(m_obj.reportFilterRecurStart)
      return unwrapNSString(ret)
    }
    set {
      m_obj.reportFilterRecurStart = newValue as NSString
    }
  }

  public var reportFilterReturnCalendarData: Bool {
    get {
      return m_obj.reportFilterReturnCalendarData
    }
    set {
      m_obj.reportFilterReturnCalendarData = newValue
    }
  }

  public var reportFilterStartDate: String {
    get {
      let ret: String? = String(m_obj.reportFilterStartDate)
      return unwrapNSString(ret)
    }
    set {
      m_obj.reportFilterStartDate = newValue as NSString
    }
  }

  public var reportFilterUID: String {
    get {
      let ret: String? = String(m_obj.reportFilterUID)
      return unwrapNSString(ret)
    }
    set {
      m_obj.reportFilterUID = newValue as NSString
    }
  }

  public var sequence: Int32 {
    get {
      return m_obj.sequence
    }
    set {
      m_obj.sequence = newValue
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

  public var SSLCertStoreType: CaldavSSLCertStoreTypes {
    get {
      return CaldavSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var startDate: String {
    get {
      let ret: String? = String(m_obj.startDate)
      return unwrapNSString(ret)
    }
    set {
      m_obj.startDate = newValue as NSString
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

  public var statusLine: String {
    get {
      let ret: String? = String(m_obj.statusLine)
      return unwrapNSString(ret)
    }
  }

  public var summary: String {
    get {
      let ret: String? = String(m_obj.summary)
      return unwrapNSString(ret)
    }
    set {
      m_obj.summary = newValue as NSString
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

  public var timestamp: String {
    get {
      let ret: String? = String(m_obj.timestamp)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timestamp = newValue as NSString
    }
  }

  public var timezoneDSTName: String {
    get {
      let ret: String? = String(m_obj.timezoneDSTName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneDSTName = newValue as NSString
    }
  }

  public var timezoneDSTOffsetFrom: String {
    get {
      let ret: String? = String(m_obj.timezoneDSTOffsetFrom)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneDSTOffsetFrom = newValue as NSString
    }
  }

  public var timezoneDSTOffsetTo: String {
    get {
      let ret: String? = String(m_obj.timezoneDSTOffsetTo)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneDSTOffsetTo = newValue as NSString
    }
  }

  public var timezoneDSTRule: String {
    get {
      let ret: String? = String(m_obj.timezoneDSTRule)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneDSTRule = newValue as NSString
    }
  }

  public var timezoneDSTStart: String {
    get {
      let ret: String? = String(m_obj.timezoneDSTStart)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneDSTStart = newValue as NSString
    }
  }

  public var timezoneLastModified: String {
    get {
      let ret: String? = String(m_obj.timezoneLastModified)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneLastModified = newValue as NSString
    }
  }

  public var timezoneStdName: String {
    get {
      let ret: String? = String(m_obj.timezoneStdName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneStdName = newValue as NSString
    }
  }

  public var timezoneStdOffsetFrom: String {
    get {
      let ret: String? = String(m_obj.timezoneStdOffsetFrom)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneStdOffsetFrom = newValue as NSString
    }
  }

  public var timezoneStdOffsetTo: String {
    get {
      let ret: String? = String(m_obj.timezoneStdOffsetTo)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneStdOffsetTo = newValue as NSString
    }
  }

  public var timezoneStdRule: String {
    get {
      let ret: String? = String(m_obj.timezoneStdRule)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneStdRule = newValue as NSString
    }
  }

  public var timezoneStdStart: String {
    get {
      let ret: String? = String(m_obj.timezoneStdStart)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneStdStart = newValue as NSString
    }
  }

  public var timezoneId: String {
    get {
      let ret: String? = String(m_obj.timezoneId)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneId = newValue as NSString
    }
  }

  public var timezoneURL: String {
    get {
      let ret: String? = String(m_obj.timezoneURL)
      return unwrapNSString(ret)
    }
    set {
      m_obj.timezoneURL = newValue as NSString
    }
  }

  public var transparency: String {
    get {
      let ret: String? = String(m_obj.transparency)
      return unwrapNSString(ret)
    }
    set {
      m_obj.transparency = newValue as NSString
    }
  }

  public var UID: String {
    get {
      let ret: String? = String(m_obj.UID)
      return unwrapNSString(ret)
    }
    set {
      m_obj.UID = newValue as NSString
    }
  }

  public var URL: String {
    get {
      let ret: String? = String(m_obj.URL)
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

  public func addCookie(_ cookieName: String, _ cookieValue: String) throws -> Void {
    m_obj.addCookie(cookieName, cookieValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func addCustomProperty(_ varName: String, _ varValue: String) throws -> Void {
    m_obj.addCustomProperty(varName, varValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func copyCalendarEvent(_ sourceResourceURI: String, _ destinationResourceURI: String) throws -> Void {
    m_obj.copyCalendarEvent(sourceResourceURI, destinationResourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func createCalendar(_ resourceURI: String) throws -> Void {
    m_obj.createCalendar(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func deleteCalendarEvent(_ resourceURI: String) throws -> Void {
    m_obj.deleteCalendarEvent(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func exportICS() throws -> String {
    let ret: String? = m_obj.exportICS()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func getCalendarEvent(_ resourceURI: String) throws -> Void {
    m_obj.getCalendarEvent(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getCalendarOptions(_ resourceURI: String) throws -> Void {
    m_obj.getCalendarOptions(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getCalendarReport(_ resourceURI: String) throws -> Void {
    m_obj.getCalendarReport(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getFreeBusyReport(_ resourceURI: String) throws -> Void {
    m_obj.getFreeBusyReport(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func importICS(_ calendarData: String) throws -> Void {
    m_obj.importICS(calendarData)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func lockCalendar(_ resourceURI: String) throws -> Void {
    m_obj.lockCalendar(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func moveCalendarEvent(_ sourceResourceURI: String, _ destinationResourceURI: String) throws -> Void {
    m_obj.moveCalendarEvent(sourceResourceURI, destinationResourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putCalendarEvent(_ resourceURI: String) throws -> Void {
    m_obj.putCalendarEvent(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func unLockCalendar(_ resourceURI: String) throws -> Void {
    m_obj.unLockCalendar(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCalDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}