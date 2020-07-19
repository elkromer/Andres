
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum AtomAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
  case authOAuth = 6
}
public enum AtomChannelRightsTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum AtomChannelSubtitleTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum AtomChannelTitleTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum AtomEntryContentTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum AtomEntryRightsTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum AtomEntrySummaryTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum AtomEntryTitleTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum AtomFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum AtomFollowRedirects : Int32 {
  case frNever = 0
  case frAlways = 1
  case frSameScheme = 2
}
public enum AtomProxyAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
}
public enum AtomProxySSLs : Int32 {
  case psAutomatic = 0
  case psAlways = 1
  case psNever = 2
  case psTunnel = 3
}
public enum AtomSSLCertStoreTypes : Int32 {
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
public enum AtomUpdateEntryContentTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum AtomUpdateEntryRightsTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum AtomUpdateEntrySummaryTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum AtomUpdateEntryTitleTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}


public protocol IPWorksAtomDelegateSwift {
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
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

public enum IPWorksAtomError : Error {
  case Error(Int32, String)
}

public class IPWorksAtomSwift : NSObject, IPWorksAtomDelegate {
  public var m_obj: IPWorksAtom
  var m_delegate: IPWorksAtomDelegateSwift?

  override init() {
    self.m_obj = IPWorksAtom()
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

  public var delegate: IPWorksAtomDelegateSwift? {
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

  public var accept: String {
    get {
      let ret: String? = String(m_obj.accept)
      return unwrapNSString(ret)
    }
    set {
      m_obj.accept = newValue as NSString
    }
  }

  public var atomData: String {
    get {
      let ret: String? = String(m_obj.atomData)
      return unwrapNSString(ret)
    }
    set {
      m_obj.atomData = newValue as NSString
    }
  }

  public var atomDataB: Data {
    get {
      let ret: Data? = m_obj.atomDataB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.atomDataB = newValue as NSData
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

  public var authScheme: AtomAuthSchemes {
    get {
      return AtomAuthSchemes(rawValue: m_obj.authScheme)!
    }
    set {
      m_obj.authScheme = newValue.rawValue
    }
  }

  public var channelAuthorEmail: String {
    get {
      let ret: String? = String(m_obj.channelAuthorEmail)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelAuthorEmail = newValue as NSString
    }
  }

  public var channelAuthorName: String {
    get {
      let ret: String? = String(m_obj.channelAuthorName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelAuthorName = newValue as NSString
    }
  }

  public var channelAuthorUri: String {
    get {
      let ret: String? = String(m_obj.channelAuthorUri)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelAuthorUri = newValue as NSString
    }
  }

  public var channelCategoryLabel: String {
    get {
      let ret: String? = String(m_obj.channelCategoryLabel)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelCategoryLabel = newValue as NSString
    }
  }

  public var channelCategoryScheme: String {
    get {
      let ret: String? = String(m_obj.channelCategoryScheme)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelCategoryScheme = newValue as NSString
    }
  }

  public var channelCategoryTerm: String {
    get {
      let ret: String? = String(m_obj.channelCategoryTerm)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelCategoryTerm = newValue as NSString
    }
  }

  public var channelContributorEmail: String {
    get {
      let ret: String? = String(m_obj.channelContributorEmail)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelContributorEmail = newValue as NSString
    }
  }

  public var channelContributorName: String {
    get {
      let ret: String? = String(m_obj.channelContributorName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelContributorName = newValue as NSString
    }
  }

  public var channelContributorUri: String {
    get {
      let ret: String? = String(m_obj.channelContributorUri)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelContributorUri = newValue as NSString
    }
  }

  public var channelGenerator: String {
    get {
      let ret: String? = String(m_obj.channelGenerator)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelGenerator = newValue as NSString
    }
  }

  public var channelIcon: String {
    get {
      let ret: String? = String(m_obj.channelIcon)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelIcon = newValue as NSString
    }
  }

  public var channelId: String {
    get {
      let ret: String? = String(m_obj.channelId)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelId = newValue as NSString
    }
  }

  public var channelLinkHref: String {
    get {
      let ret: String? = String(m_obj.channelLinkHref)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelLinkHref = newValue as NSString
    }
  }

  public var channelLinkHrefLang: String {
    get {
      let ret: String? = String(m_obj.channelLinkHrefLang)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelLinkHrefLang = newValue as NSString
    }
  }

  public var channelLinkLength: String {
    get {
      let ret: String? = String(m_obj.channelLinkLength)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelLinkLength = newValue as NSString
    }
  }

  public var channelLinkRel: String {
    get {
      let ret: String? = String(m_obj.channelLinkRel)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelLinkRel = newValue as NSString
    }
  }

  public var channelLinkTitle: String {
    get {
      let ret: String? = String(m_obj.channelLinkTitle)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelLinkTitle = newValue as NSString
    }
  }

  public var channelLinkType: String {
    get {
      let ret: String? = String(m_obj.channelLinkType)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelLinkType = newValue as NSString
    }
  }

  public var channelLogo: String {
    get {
      let ret: String? = String(m_obj.channelLogo)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelLogo = newValue as NSString
    }
  }

  public var channelRights: String {
    get {
      let ret: String? = String(m_obj.channelRights)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelRights = newValue as NSString
    }
  }

  public var channelRightsTextType: AtomChannelRightsTextTypes {
    get {
      return AtomChannelRightsTextTypes(rawValue: m_obj.channelRightsTextType)!
    }
    set {
      m_obj.channelRightsTextType = newValue.rawValue
    }
  }

  public var channelSubtitle: String {
    get {
      let ret: String? = String(m_obj.channelSubtitle)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelSubtitle = newValue as NSString
    }
  }

  public var channelSubtitleTextType: AtomChannelSubtitleTextTypes {
    get {
      return AtomChannelSubtitleTextTypes(rawValue: m_obj.channelSubtitleTextType)!
    }
    set {
      m_obj.channelSubtitleTextType = newValue.rawValue
    }
  }

  public var channelTitle: String {
    get {
      let ret: String? = String(m_obj.channelTitle)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelTitle = newValue as NSString
    }
  }

  public var channelTitleTextType: AtomChannelTitleTextTypes {
    get {
      return AtomChannelTitleTextTypes(rawValue: m_obj.channelTitleTextType)!
    }
    set {
      m_obj.channelTitleTextType = newValue.rawValue
    }
  }

  public var channelUpdated: String {
    get {
      let ret: String? = String(m_obj.channelUpdated)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelUpdated = newValue as NSString
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

  public var contentType: String {
    get {
      let ret: String? = String(m_obj.contentType)
      return unwrapNSString(ret)
    }
    set {
      m_obj.contentType = newValue as NSString
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieExpiration(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieExpiration(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieName(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieName(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieName(cookieIndex: Int32, newCookieName: String) throws -> Void {
    m_obj.setCookieName(cookieIndex, newCookieName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func cookiePath(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookiePath(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieSecure(cookieIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.cookieSecure(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func cookieValue(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieValue(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieValue(cookieIndex: Int32, newCookieValue: String) throws -> Void {
    m_obj.setCookieValue(cookieIndex, newCookieValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var entryCount: Int32 {
    get {
      return m_obj.entryCount
    }
    set {
      m_obj.entryCount = newValue
    }
  }

  public func entryAuthorEmail(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryAuthorEmail(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryAuthorEmail(entryIndex: Int32, newEntryAuthorEmail: String) throws -> Void {
    m_obj.setEntryAuthorEmail(entryIndex, newEntryAuthorEmail)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryAuthorName(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryAuthorName(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryAuthorName(entryIndex: Int32, newEntryAuthorName: String) throws -> Void {
    m_obj.setEntryAuthorName(entryIndex, newEntryAuthorName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryAuthorUri(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryAuthorUri(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryAuthorUri(entryIndex: Int32, newEntryAuthorUri: String) throws -> Void {
    m_obj.setEntryAuthorUri(entryIndex, newEntryAuthorUri)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryCategoryLabel(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryCategoryLabel(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryCategoryLabel(entryIndex: Int32, newEntryCategoryLabel: String) throws -> Void {
    m_obj.setEntryCategoryLabel(entryIndex, newEntryCategoryLabel)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryCategoryScheme(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryCategoryScheme(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryCategoryScheme(entryIndex: Int32, newEntryCategoryScheme: String) throws -> Void {
    m_obj.setEntryCategoryScheme(entryIndex, newEntryCategoryScheme)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryCategoryTerm(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryCategoryTerm(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryCategoryTerm(entryIndex: Int32, newEntryCategoryTerm: String) throws -> Void {
    m_obj.setEntryCategoryTerm(entryIndex, newEntryCategoryTerm)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryContent(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryContent(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryContent(entryIndex: Int32, newEntryContent: String) throws -> Void {
    m_obj.setEntryContent(entryIndex, newEntryContent)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryContentTextType(entryIndex: Int32) throws -> AtomEntryContentTextTypes {
    let ret = AtomEntryContentTextTypes(rawValue: m_obj.entryContentTextType(entryIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func setEntryContentTextType(entryIndex: Int32, newEntryContentTextType: AtomEntryContentTextTypes) throws -> Void {
    m_obj.setEntryContentTextType(entryIndex, newEntryContentTextType.rawValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryContributorEmail(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryContributorEmail(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryContributorEmail(entryIndex: Int32, newEntryContributorEmail: String) throws -> Void {
    m_obj.setEntryContributorEmail(entryIndex, newEntryContributorEmail)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryContributorName(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryContributorName(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryContributorName(entryIndex: Int32, newEntryContributorName: String) throws -> Void {
    m_obj.setEntryContributorName(entryIndex, newEntryContributorName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryContributorUri(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryContributorUri(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryContributorUri(entryIndex: Int32, newEntryContributorUri: String) throws -> Void {
    m_obj.setEntryContributorUri(entryIndex, newEntryContributorUri)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryCopyright(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryCopyright(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryCopyright(entryIndex: Int32, newEntryCopyright: String) throws -> Void {
    m_obj.setEntryCopyright(entryIndex, newEntryCopyright)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryCreated(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryCreated(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryCreated(entryIndex: Int32, newEntryCreated: String) throws -> Void {
    m_obj.setEntryCreated(entryIndex, newEntryCreated)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryXML(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryXML(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryXML(entryIndex: Int32, newEntryXML: String) throws -> Void {
    m_obj.setEntryXML(entryIndex, newEntryXML)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryId(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryId(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryId(entryIndex: Int32, newEntryId: String) throws -> Void {
    m_obj.setEntryId(entryIndex, newEntryId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryIssued(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryIssued(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryIssued(entryIndex: Int32, newEntryIssued: String) throws -> Void {
    m_obj.setEntryIssued(entryIndex, newEntryIssued)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryLinkHref(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryLinkHref(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryLinkHref(entryIndex: Int32, newEntryLinkHref: String) throws -> Void {
    m_obj.setEntryLinkHref(entryIndex, newEntryLinkHref)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryLinkHrefLang(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryLinkHrefLang(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryLinkHrefLang(entryIndex: Int32, newEntryLinkHrefLang: String) throws -> Void {
    m_obj.setEntryLinkHrefLang(entryIndex, newEntryLinkHrefLang)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryLinkLength(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryLinkLength(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryLinkLength(entryIndex: Int32, newEntryLinkLength: String) throws -> Void {
    m_obj.setEntryLinkLength(entryIndex, newEntryLinkLength)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryLinkRel(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryLinkRel(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryLinkRel(entryIndex: Int32, newEntryLinkRel: String) throws -> Void {
    m_obj.setEntryLinkRel(entryIndex, newEntryLinkRel)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryLinkTitle(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryLinkTitle(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryLinkTitle(entryIndex: Int32, newEntryLinkTitle: String) throws -> Void {
    m_obj.setEntryLinkTitle(entryIndex, newEntryLinkTitle)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryLinkType(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryLinkType(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryLinkType(entryIndex: Int32, newEntryLinkType: String) throws -> Void {
    m_obj.setEntryLinkType(entryIndex, newEntryLinkType)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryModified(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryModified(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryModified(entryIndex: Int32, newEntryModified: String) throws -> Void {
    m_obj.setEntryModified(entryIndex, newEntryModified)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryPublished(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryPublished(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryPublished(entryIndex: Int32, newEntryPublished: String) throws -> Void {
    m_obj.setEntryPublished(entryIndex, newEntryPublished)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryRights(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryRights(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryRights(entryIndex: Int32, newEntryRights: String) throws -> Void {
    m_obj.setEntryRights(entryIndex, newEntryRights)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryRightsTextType(entryIndex: Int32) throws -> AtomEntryRightsTextTypes {
    let ret = AtomEntryRightsTextTypes(rawValue: m_obj.entryRightsTextType(entryIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func setEntryRightsTextType(entryIndex: Int32, newEntryRightsTextType: AtomEntryRightsTextTypes) throws -> Void {
    m_obj.setEntryRightsTextType(entryIndex, newEntryRightsTextType.rawValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entrySource(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entrySource(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntrySource(entryIndex: Int32, newEntrySource: String) throws -> Void {
    m_obj.setEntrySource(entryIndex, newEntrySource)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entrySummary(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entrySummary(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntrySummary(entryIndex: Int32, newEntrySummary: String) throws -> Void {
    m_obj.setEntrySummary(entryIndex, newEntrySummary)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entrySummaryTextType(entryIndex: Int32) throws -> AtomEntrySummaryTextTypes {
    let ret = AtomEntrySummaryTextTypes(rawValue: m_obj.entrySummaryTextType(entryIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func setEntrySummaryTextType(entryIndex: Int32, newEntrySummaryTextType: AtomEntrySummaryTextTypes) throws -> Void {
    m_obj.setEntrySummaryTextType(entryIndex, newEntrySummaryTextType.rawValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryTitle(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryTitle(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryTitle(entryIndex: Int32, newEntryTitle: String) throws -> Void {
    m_obj.setEntryTitle(entryIndex, newEntryTitle)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryTitleTextType(entryIndex: Int32) throws -> AtomEntryTitleTextTypes {
    let ret = AtomEntryTitleTextTypes(rawValue: m_obj.entryTitleTextType(entryIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func setEntryTitleTextType(entryIndex: Int32, newEntryTitleTextType: AtomEntryTitleTextTypes) throws -> Void {
    m_obj.setEntryTitleTextType(entryIndex, newEntryTitleTextType.rawValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryUpdated(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryUpdated(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryUpdated(entryIndex: Int32, newEntryUpdated: String) throws -> Void {
    m_obj.setEntryUpdated(entryIndex, newEntryUpdated)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var firewallAutoDetect: Bool {
    get {
      return m_obj.firewallAutoDetect
    }
    set {
      m_obj.firewallAutoDetect = newValue
    }
  }

  public var firewallType: AtomFirewallTypes {
    get {
      return AtomFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var followRedirects: AtomFollowRedirects {
    get {
      return AtomFollowRedirects(rawValue: m_obj.followRedirects)!
    }
    set {
      m_obj.followRedirects = newValue.rawValue
    }
  }

  public var idle: Bool {
    get {
      return m_obj.idle
    }
  }

  public var ifModifiedSince: String {
    get {
      let ret: String? = String(m_obj.ifModifiedSince)
      return unwrapNSString(ret)
    }
    set {
      m_obj.ifModifiedSince = newValue as NSString
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

  public var namespaceCount: Int32 {
    get {
      return m_obj.namespaceCount
    }
    set {
      m_obj.namespaceCount = newValue
    }
  }

  public func namespacePrefix(namespaceIndex: Int32) throws -> String {
    let ret: String? = m_obj.namespacePrefix(namespaceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setNamespacePrefix(namespaceIndex: Int32, newNamespacePrefix: String) throws -> Void {
    m_obj.setNamespacePrefix(namespaceIndex, newNamespacePrefix)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func namespaceURI(namespaceIndex: Int32) throws -> String {
    let ret: String? = m_obj.namespaceURI(namespaceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setNamespaceURI(namespaceIndex: Int32, newNamespaceURI: String) throws -> Void {
    m_obj.setNamespaceURI(namespaceIndex, newNamespaceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func parsedHeaderValue(parsedHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.parsedHeaderValue(parsedHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
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

  public var proxyAuthScheme: AtomProxyAuthSchemes {
    get {
      return AtomProxyAuthSchemes(rawValue: m_obj.proxyAuthScheme)!
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

  public var proxySSL: AtomProxySSLs {
    get {
      return AtomProxySSLs(rawValue: m_obj.proxySSL)!
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

  public var referer: String {
    get {
      let ret: String? = String(m_obj.referer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.referer = newValue as NSString
    }
  }

  public var slug: String {
    get {
      let ret: String? = String(m_obj.slug)
      return unwrapNSString(ret)
    }
    set {
      m_obj.slug = newValue as NSString
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

  public var SSLCertStoreType: AtomSSLCertStoreTypes {
    get {
      return AtomSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var timeout: Int32 {
    get {
      return m_obj.timeout
    }
    set {
      m_obj.timeout = newValue
    }
  }

  public var transferredData: String {
    get {
      let ret: String? = String(m_obj.transferredData)
      return unwrapNSString(ret)
    }
  }

  public var transferredDataB: Data {
    get {
      let ret: Data? = m_obj.transferredDataB as Data
      return unwrapData(ret)
    }

  }

  public var transferredDataLimit: Int64 {
    get {
      return m_obj.transferredDataLimit
    }
    set {
      m_obj.transferredDataLimit = newValue
    }
  }

  public var transferredHeaders: String {
    get {
      let ret: String? = String(m_obj.transferredHeaders)
      return unwrapNSString(ret)
    }
  }

  public var updateEntryAuthorEmail: String {
    get {
      let ret: String? = String(m_obj.updateEntryAuthorEmail)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryAuthorEmail = newValue as NSString
    }
  }

  public var updateEntryAuthorName: String {
    get {
      let ret: String? = String(m_obj.updateEntryAuthorName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryAuthorName = newValue as NSString
    }
  }

  public var updateEntryAuthorUri: String {
    get {
      let ret: String? = String(m_obj.updateEntryAuthorUri)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryAuthorUri = newValue as NSString
    }
  }

  public var updateEntryCategoryLabel: String {
    get {
      let ret: String? = String(m_obj.updateEntryCategoryLabel)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryCategoryLabel = newValue as NSString
    }
  }

  public var updateEntryCategoryScheme: String {
    get {
      let ret: String? = String(m_obj.updateEntryCategoryScheme)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryCategoryScheme = newValue as NSString
    }
  }

  public var updateEntryCategoryTerm: String {
    get {
      let ret: String? = String(m_obj.updateEntryCategoryTerm)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryCategoryTerm = newValue as NSString
    }
  }

  public var updateEntryContent: String {
    get {
      let ret: String? = String(m_obj.updateEntryContent)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryContent = newValue as NSString
    }
  }

  public var updateEntryContentTextType: AtomUpdateEntryContentTextTypes {
    get {
      return AtomUpdateEntryContentTextTypes(rawValue: m_obj.updateEntryContentTextType)!
    }
    set {
      m_obj.updateEntryContentTextType = newValue.rawValue
    }
  }

  public var updateEntryContributorEmail: String {
    get {
      let ret: String? = String(m_obj.updateEntryContributorEmail)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryContributorEmail = newValue as NSString
    }
  }

  public var updateEntryContributorName: String {
    get {
      let ret: String? = String(m_obj.updateEntryContributorName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryContributorName = newValue as NSString
    }
  }

  public var updateEntryContributorUri: String {
    get {
      let ret: String? = String(m_obj.updateEntryContributorUri)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryContributorUri = newValue as NSString
    }
  }

  public var updateEntryCopyright: String {
    get {
      let ret: String? = String(m_obj.updateEntryCopyright)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryCopyright = newValue as NSString
    }
  }

  public var updateEntryCreated: String {
    get {
      let ret: String? = String(m_obj.updateEntryCreated)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryCreated = newValue as NSString
    }
  }

  public var updateEntryXML: String {
    get {
      let ret: String? = String(m_obj.updateEntryXML)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryXML = newValue as NSString
    }
  }

  public var updateEntryId: String {
    get {
      let ret: String? = String(m_obj.updateEntryId)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryId = newValue as NSString
    }
  }

  public var updateEntryIssued: String {
    get {
      let ret: String? = String(m_obj.updateEntryIssued)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryIssued = newValue as NSString
    }
  }

  public var updateEntryLinkHref: String {
    get {
      let ret: String? = String(m_obj.updateEntryLinkHref)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryLinkHref = newValue as NSString
    }
  }

  public var updateEntryLinkHrefLang: String {
    get {
      let ret: String? = String(m_obj.updateEntryLinkHrefLang)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryLinkHrefLang = newValue as NSString
    }
  }

  public var updateEntryLinkLength: String {
    get {
      let ret: String? = String(m_obj.updateEntryLinkLength)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryLinkLength = newValue as NSString
    }
  }

  public var updateEntryLinkRel: String {
    get {
      let ret: String? = String(m_obj.updateEntryLinkRel)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryLinkRel = newValue as NSString
    }
  }

  public var updateEntryLinkTitle: String {
    get {
      let ret: String? = String(m_obj.updateEntryLinkTitle)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryLinkTitle = newValue as NSString
    }
  }

  public var updateEntryLinkType: String {
    get {
      let ret: String? = String(m_obj.updateEntryLinkType)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryLinkType = newValue as NSString
    }
  }

  public var updateEntryModified: String {
    get {
      let ret: String? = String(m_obj.updateEntryModified)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryModified = newValue as NSString
    }
  }

  public var updateEntryPublished: String {
    get {
      let ret: String? = String(m_obj.updateEntryPublished)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryPublished = newValue as NSString
    }
  }

  public var updateEntryRights: String {
    get {
      let ret: String? = String(m_obj.updateEntryRights)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryRights = newValue as NSString
    }
  }

  public var updateEntryRightsTextType: AtomUpdateEntryRightsTextTypes {
    get {
      return AtomUpdateEntryRightsTextTypes(rawValue: m_obj.updateEntryRightsTextType)!
    }
    set {
      m_obj.updateEntryRightsTextType = newValue.rawValue
    }
  }

  public var updateEntrySource: String {
    get {
      let ret: String? = String(m_obj.updateEntrySource)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntrySource = newValue as NSString
    }
  }

  public var updateEntrySummary: String {
    get {
      let ret: String? = String(m_obj.updateEntrySummary)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntrySummary = newValue as NSString
    }
  }

  public var updateEntrySummaryTextType: AtomUpdateEntrySummaryTextTypes {
    get {
      return AtomUpdateEntrySummaryTextTypes(rawValue: m_obj.updateEntrySummaryTextType)!
    }
    set {
      m_obj.updateEntrySummaryTextType = newValue.rawValue
    }
  }

  public var updateEntryTitle: String {
    get {
      let ret: String? = String(m_obj.updateEntryTitle)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryTitle = newValue as NSString
    }
  }

  public var updateEntryTitleTextType: AtomUpdateEntryTitleTextTypes {
    get {
      return AtomUpdateEntryTitleTextTypes(rawValue: m_obj.updateEntryTitleTextType)!
    }
    set {
      m_obj.updateEntryTitleTextType = newValue.rawValue
    }
  }

  public var updateEntryUpdated: String {
    get {
      let ret: String? = String(m_obj.updateEntryUpdated)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateEntryUpdated = newValue as NSString
    }
  }

  public var updateFile: String {
    get {
      let ret: String? = String(m_obj.updateFile)
      return unwrapNSString(ret)
    }
    set {
      m_obj.updateFile = newValue as NSString
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func addNamespace(_ prefix: String, _ namespaceURI: String) throws -> Void {
    m_obj.addNamespace(prefix, namespaceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func deleteResource(_ URL: String) throws -> Void {
    m_obj.deleteResource(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getFeed(_ URL: String) throws -> Void {
    m_obj.getFeed(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getProperty(_ propertyName: String) throws -> String {
    let ret: String? = m_obj.getProperty(propertyName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func getResource(_ URL: String) throws -> Void {
    m_obj.getResource(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func postResource(_ URL: String) throws -> Void {
    m_obj.postResource(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func put(_ URL: String) throws -> Void {
    m_obj.put(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putResource(_ URL: String) throws -> Void {
    m_obj.putResource(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func readFile(_ fileName: String) throws -> Void {
    m_obj.readFile(fileName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setProperty(_ propertyName: String, _ propertyValue: String) throws -> Void {
    m_obj.setProperty(propertyName, propertyValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func writeFile(_ filename: String) throws -> Void {
    m_obj.writeFile(filename)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksAtomError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}