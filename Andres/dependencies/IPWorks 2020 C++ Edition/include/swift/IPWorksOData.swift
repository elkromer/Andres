
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum OdataAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
  case authOAuth = 6
}
public enum OdataChannelRightsTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum OdataChannelSubtitleTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum OdataChannelTitleTextTypes : Int32 {
  case ttText = 0
  case ttHTML = 1
  case ttXHTML = 2
}
public enum OdataFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum OdataODataVersions : Int32 {
  case odV2 = 0
  case odV3 = 1
  case odV4 = 2
  case odAuto = 3
}
public enum OdataProxyAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
}
public enum OdataProxySSLs : Int32 {
  case psAutomatic = 0
  case psAlways = 1
  case psNever = 2
  case psTunnel = 3
}
public enum OdataSchemaAssociationFromRoleMultiplicities : Int32 {
  case nmZeroOne = 0
  case nmOne = 1
  case nmMany = 2
}
public enum OdataSchemaAssociationOnDeletes : Int32 {
  case daNone = 0
  case daCascade = 1
  case daSetNull = 2
  case daSetDefault = 3
}
public enum OdataSchemaAssociationToRoleMultiplicities : Int32 {
  case nmZeroOne = 0
  case nmOne = 1
  case nmMany = 2
}
public enum OdataSSLCertStoreTypes : Int32 {
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


public protocol IPWorksODataDelegateSwift {
  func onConnected(_ statusCode: Int32, _ description: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32)
  func onEntity(_ name: String)
  func onEntry(_ id: String, _ title: String, _ summary: String, _ ETag: String)
  func onError(_ errorCode: Int32, _ description: String)
  func onHeader(_ field: String, _ value: String)
  func onLog(_ logLevel: Int32, _ message: String, _ logType: String)
  func onProperty(_ name: String, _ typeName: String, _ nullable: Bool)
  func onSetCookie(_ name: String, _ value: String, _ expires: String, _ domain: String, _ path: String, _ secure: Bool)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32)
  func onStatus(_ HTTPVersion: String, _ statusCode: Int32, _ description: String)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data)
}

public enum IPWorksODataError : Error {
  case Error(Int32, String)
}

public class IPWorksODataSwift : NSObject, IPWorksODataDelegate {
  public var m_obj: IPWorksOData
  var m_delegate: IPWorksODataDelegateSwift?

  override init() {
    self.m_obj = IPWorksOData()
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

  public var delegate: IPWorksODataDelegateSwift? {
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

  public func onEntity(_ name: String!) {
    if (m_delegate != nil) {
      m_delegate!.onEntity(name)
    }
  }

  public func onEntry(_ id: String!, _ title: String!, _ summary: String!, _ ETag: String!) {
    if (m_delegate != nil) {
      m_delegate!.onEntry(id, title, summary, ETag)
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

  public func onProperty(_ name: String!, _ typeName: String!, _ nullable: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onProperty(name, typeName, nullable)
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

  public var authorization: String {
    get {
      let ret: String? = String(m_obj.authorization)
      return unwrapNSString(ret)
    }
    set {
      m_obj.authorization = newValue as NSString
    }
  }

  public var authScheme: OdataAuthSchemes {
    get {
      return OdataAuthSchemes(rawValue: m_obj.authScheme)!
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

  public var channelRightsTextType: OdataChannelRightsTextTypes {
    get {
      return OdataChannelRightsTextTypes(rawValue: m_obj.channelRightsTextType)!
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

  public var channelSubtitleTextType: OdataChannelSubtitleTextTypes {
    get {
      return OdataChannelSubtitleTextTypes(rawValue: m_obj.channelSubtitleTextType)!
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

  public var channelTitleTextType: OdataChannelTitleTextTypes {
    get {
      return OdataChannelTitleTextTypes(rawValue: m_obj.channelTitleTextType)!
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieExpiration(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieExpiration(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieName(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieName(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieName(cookieIndex: Int32, newCookieName: String) throws -> Void {
    m_obj.setCookieName(cookieIndex, newCookieName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func cookiePath(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookiePath(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieSecure(cookieIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.cookieSecure(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func cookieValue(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieValue(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieValue(cookieIndex: Int32, newCookieValue: String) throws -> Void {
    m_obj.setCookieValue(cookieIndex, newCookieValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var entryAuthor: String {
    get {
      let ret: String? = String(m_obj.entryAuthor)
      return unwrapNSString(ret)
    }
    set {
      m_obj.entryAuthor = newValue as NSString
    }
  }

  public var entryCount: Int32 {
    get {
      return m_obj.entryCount
    }
  }

  public var entryETag: String {
    get {
      let ret: String? = String(m_obj.entryETag)
      return unwrapNSString(ret)
    }
    set {
      m_obj.entryETag = newValue as NSString
    }
  }

  public var entryId: String {
    get {
      let ret: String? = String(m_obj.entryId)
      return unwrapNSString(ret)
    }
    set {
      m_obj.entryId = newValue as NSString
    }
  }

  public var entryIndex: Int32 {
    get {
      return m_obj.entryIndex
    }
    set {
      m_obj.entryIndex = newValue
    }
  }

  public var entryLinksCount: Int32 {
    get {
      return m_obj.entryLinksCount
    }
    set {
      m_obj.entryLinksCount = newValue
    }
  }

  public func entryLinksResourcePath(entryLinksIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryLinksResourcePath(entryLinksIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func entryLinksTitle(entryLinksIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryLinksTitle(entryLinksIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var entryPropertiesCount: Int32 {
    get {
      return m_obj.entryPropertiesCount
    }
    set {
      m_obj.entryPropertiesCount = newValue
    }
  }

  public func entryPropertiesAttributes(entryPropertiesIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryPropertiesAttributes(entryPropertiesIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryPropertiesAttributes(entryPropertiesIndex: Int32, newEntryPropertiesAttributes: String) throws -> Void {
    m_obj.setEntryPropertiesAttributes(entryPropertiesIndex, newEntryPropertiesAttributes)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryPropertiesIsNull(entryPropertiesIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.entryPropertiesIsNull(entryPropertiesIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func setEntryPropertiesIsNull(entryPropertiesIndex: Int32, newEntryPropertiesIsNull: Bool) throws -> Void {
    m_obj.setEntryPropertiesIsNull(entryPropertiesIndex, newEntryPropertiesIsNull)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryPropertiesName(entryPropertiesIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryPropertiesName(entryPropertiesIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryPropertiesName(entryPropertiesIndex: Int32, newEntryPropertiesName: String) throws -> Void {
    m_obj.setEntryPropertiesName(entryPropertiesIndex, newEntryPropertiesName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryPropertiesType(entryPropertiesIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryPropertiesType(entryPropertiesIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryPropertiesType(entryPropertiesIndex: Int32, newEntryPropertiesType: String) throws -> Void {
    m_obj.setEntryPropertiesType(entryPropertiesIndex, newEntryPropertiesType)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryPropertiesValue(entryPropertiesIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryPropertiesValue(entryPropertiesIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setEntryPropertiesValue(entryPropertiesIndex: Int32, newEntryPropertiesValue: String) throws -> Void {
    m_obj.setEntryPropertiesValue(entryPropertiesIndex, newEntryPropertiesValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func entryPropertiesXPath(entryPropertiesIndex: Int32) throws -> String {
    let ret: String? = m_obj.entryPropertiesXPath(entryPropertiesIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var entrySummary: String {
    get {
      let ret: String? = String(m_obj.entrySummary)
      return unwrapNSString(ret)
    }
    set {
      m_obj.entrySummary = newValue as NSString
    }
  }

  public var entryTitle: String {
    get {
      let ret: String? = String(m_obj.entryTitle)
      return unwrapNSString(ret)
    }
    set {
      m_obj.entryTitle = newValue as NSString
    }
  }

  public var entryType: String {
    get {
      let ret: String? = String(m_obj.entryType)
      return unwrapNSString(ret)
    }
    set {
      m_obj.entryType = newValue as NSString
    }
  }

  public var entryUpdated: String {
    get {
      let ret: String? = String(m_obj.entryUpdated)
      return unwrapNSString(ret)
    }
  }

  public var entryXML: String {
    get {
      let ret: String? = String(m_obj.entryXML)
      return unwrapNSString(ret)
    }
    set {
      m_obj.entryXML = newValue as NSString
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

  public var firewallType: OdataFirewallTypes {
    get {
      return OdataFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var ODataVersion: OdataODataVersions {
    get {
      return OdataODataVersions(rawValue: m_obj.ODataVersion)!
    }
    set {
      m_obj.ODataVersion = newValue.rawValue
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

  public var otherQueryOptions: String {
    get {
      let ret: String? = String(m_obj.otherQueryOptions)
      return unwrapNSString(ret)
    }
    set {
      m_obj.otherQueryOptions = newValue as NSString
    }
  }

  public var parsedHeaderCount: Int32 {
    get {
      return m_obj.parsedHeaderCount
    }
  }

  public func parsedHeaderField(parsedHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.parsedHeaderField(parsedHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func parsedHeaderValue(parsedHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.parsedHeaderValue(parsedHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
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

  public var proxyAuthScheme: OdataProxyAuthSchemes {
    get {
      return OdataProxyAuthSchemes(rawValue: m_obj.proxyAuthScheme)!
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

  public var proxySSL: OdataProxySSLs {
    get {
      return OdataProxySSLs(rawValue: m_obj.proxySSL)!
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

  public var queryFilter: String {
    get {
      let ret: String? = String(m_obj.queryFilter)
      return unwrapNSString(ret)
    }
    set {
      m_obj.queryFilter = newValue as NSString
    }
  }

  public var queryOrderBy: String {
    get {
      let ret: String? = String(m_obj.queryOrderBy)
      return unwrapNSString(ret)
    }
    set {
      m_obj.queryOrderBy = newValue as NSString
    }
  }

  public var querySelect: String {
    get {
      let ret: String? = String(m_obj.querySelect)
      return unwrapNSString(ret)
    }
    set {
      m_obj.querySelect = newValue as NSString
    }
  }

  public var querySkip: String {
    get {
      let ret: String? = String(m_obj.querySkip)
      return unwrapNSString(ret)
    }
    set {
      m_obj.querySkip = newValue as NSString
    }
  }

  public var querySkipToken: String {
    get {
      let ret: String? = String(m_obj.querySkipToken)
      return unwrapNSString(ret)
    }
    set {
      m_obj.querySkipToken = newValue as NSString
    }
  }

  public var queryTop: String {
    get {
      let ret: String? = String(m_obj.queryTop)
      return unwrapNSString(ret)
    }
    set {
      m_obj.queryTop = newValue as NSString
    }
  }

  public var resourcePath: String {
    get {
      let ret: String? = String(m_obj.resourcePath)
      return unwrapNSString(ret)
    }
    set {
      m_obj.resourcePath = newValue as NSString
    }
  }

  public var schemaAssociationContainsTarget: Bool {
    get {
      return m_obj.schemaAssociationContainsTarget
    }
  }

  public var schemaAssociationDescription: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationDescription)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationFromRole: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationFromRole)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationFromRoleDescription: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationFromRoleDescription)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationFromRoleEntity: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationFromRoleEntity)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationFromRoleMultiplicity: OdataSchemaAssociationFromRoleMultiplicities {
    get {
      return OdataSchemaAssociationFromRoleMultiplicities(rawValue: m_obj.schemaAssociationFromRoleMultiplicity)!
    }
  }

  public var schemaAssociationFromRoleSummary: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationFromRoleSummary)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationName: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationName)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationNullable: Bool {
    get {
      return m_obj.schemaAssociationNullable
    }
  }

  public var schemaAssociationOnDelete: OdataSchemaAssociationOnDeletes {
    get {
      return OdataSchemaAssociationOnDeletes(rawValue: m_obj.schemaAssociationOnDelete)!
    }
  }

  public var schemaAssociationPartner: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationPartner)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationRefConstraintCount: Int32 {
    get {
      return m_obj.schemaAssociationRefConstraintCount
    }
  }

  public var schemaAssociationRefConstraintIndex: Int32 {
    get {
      return m_obj.schemaAssociationRefConstraintIndex
    }
    set {
      m_obj.schemaAssociationRefConstraintIndex = newValue
    }
  }

  public var schemaAssociationRefConstraintProperty: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationRefConstraintProperty)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationRefConstraintReferencedProperty: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationRefConstraintReferencedProperty)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationRelationship: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationRelationship)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationSummary: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationSummary)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationToRole: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationToRole)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationToRoleDescription: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationToRoleDescription)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationToRoleEntity: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationToRoleEntity)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationToRoleMultiplicity: OdataSchemaAssociationToRoleMultiplicities {
    get {
      return OdataSchemaAssociationToRoleMultiplicities(rawValue: m_obj.schemaAssociationToRoleMultiplicity)!
    }
  }

  public var schemaAssociationToRoleSummary: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationToRoleSummary)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationType: String {
    get {
      let ret: String? = String(m_obj.schemaAssociationType)
      return unwrapNSString(ret)
    }
  }

  public var schemaAssociationCount: Int32 {
    get {
      return m_obj.schemaAssociationCount
    }
  }

  public var schemaAssociationIndex: Int32 {
    get {
      return m_obj.schemaAssociationIndex
    }
    set {
      m_obj.schemaAssociationIndex = newValue
    }
  }

  public var schemaEntityDescription: String {
    get {
      let ret: String? = String(m_obj.schemaEntityDescription)
      return unwrapNSString(ret)
    }
  }

  public var schemaEntityName: String {
    get {
      let ret: String? = String(m_obj.schemaEntityName)
      return unwrapNSString(ret)
    }
  }

  public var schemaEntitySummary: String {
    get {
      let ret: String? = String(m_obj.schemaEntitySummary)
      return unwrapNSString(ret)
    }
  }

  public var schemaEntityCount: Int32 {
    get {
      return m_obj.schemaEntityCount
    }
  }

  public var schemaEntityIndex: Int32 {
    get {
      return m_obj.schemaEntityIndex
    }
    set {
      m_obj.schemaEntityIndex = newValue
    }
  }

  public var schemaKeysCount: Int32 {
    get {
      return m_obj.schemaKeysCount
    }
  }

  public func schemaKeys(schemaKeysIndex: Int32) throws -> String {
    let ret: String? = m_obj.schemaKeys(schemaKeysIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var schemaPropertyAttributes: String {
    get {
      let ret: String? = String(m_obj.schemaPropertyAttributes)
      return unwrapNSString(ret)
    }
  }

  public var schemaPropertyDescription: String {
    get {
      let ret: String? = String(m_obj.schemaPropertyDescription)
      return unwrapNSString(ret)
    }
  }

  public var schemaPropertyIsComplexType: Bool {
    get {
      return m_obj.schemaPropertyIsComplexType
    }
  }

  public var schemaPropertyName: String {
    get {
      let ret: String? = String(m_obj.schemaPropertyName)
      return unwrapNSString(ret)
    }
  }

  public var schemaPropertyNullable: Bool {
    get {
      return m_obj.schemaPropertyNullable
    }
  }

  public var schemaPropertySummary: String {
    get {
      let ret: String? = String(m_obj.schemaPropertySummary)
      return unwrapNSString(ret)
    }
  }

  public var schemaPropertyType: String {
    get {
      let ret: String? = String(m_obj.schemaPropertyType)
      return unwrapNSString(ret)
    }
  }

  public var schemaPropertyCount: Int32 {
    get {
      return m_obj.schemaPropertyCount
    }
  }

  public var schemaPropertyIndex: Int32 {
    get {
      return m_obj.schemaPropertyIndex
    }
    set {
      m_obj.schemaPropertyIndex = newValue
    }
  }

  public var schemaTypeFieldAttributes: String {
    get {
      let ret: String? = String(m_obj.schemaTypeFieldAttributes)
      return unwrapNSString(ret)
    }
  }

  public var schemaTypeFieldDescription: String {
    get {
      let ret: String? = String(m_obj.schemaTypeFieldDescription)
      return unwrapNSString(ret)
    }
  }

  public var schemaTypeFieldIsComplexType: Bool {
    get {
      return m_obj.schemaTypeFieldIsComplexType
    }
  }

  public var schemaTypeFieldName: String {
    get {
      let ret: String? = String(m_obj.schemaTypeFieldName)
      return unwrapNSString(ret)
    }
  }

  public var schemaTypeFieldNullable: Bool {
    get {
      return m_obj.schemaTypeFieldNullable
    }
  }

  public var schemaTypeFieldSummary: String {
    get {
      let ret: String? = String(m_obj.schemaTypeFieldSummary)
      return unwrapNSString(ret)
    }
  }

  public var schemaTypeFieldType: String {
    get {
      let ret: String? = String(m_obj.schemaTypeFieldType)
      return unwrapNSString(ret)
    }
  }

  public var schemaTypeFieldCount: Int32 {
    get {
      return m_obj.schemaTypeFieldCount
    }
  }

  public var schemaTypeFieldIndex: Int32 {
    get {
      return m_obj.schemaTypeFieldIndex
    }
    set {
      m_obj.schemaTypeFieldIndex = newValue
    }
  }

  public var serviceRootURI: String {
    get {
      let ret: String? = String(m_obj.serviceRootURI)
      return unwrapNSString(ret)
    }
    set {
      m_obj.serviceRootURI = newValue as NSString
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

  public var SSLCertStoreType: OdataSSLCertStoreTypes {
    get {
      return OdataSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func createEntry() throws -> Void {
    m_obj.createEntry()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func customRequest(_ HTTPMethod: String, _ URL: String, _ postData: String) throws -> Void {
    m_obj.customRequest(HTTPMethod, URL, postData)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func deleteEntry() throws -> Void {
    m_obj.deleteEntry()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getEntryProperty(_ XPath: String) throws -> String {
    let ret: String? = m_obj.getEntryProperty(XPath)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func getSchema() throws -> Void {
    m_obj.getSchema()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func hasXPath(_ XPath: String) throws -> Bool {
    let ret: Bool? = m_obj.hasXPath(XPath)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func queryService() throws -> Void {
    m_obj.queryService()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setEntryProperty(_ XPath: String, _ value: String) throws -> Void {
    m_obj.setEntryProperty(XPath, value)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setSchemaEntity(_ name: String) throws -> Void {
    m_obj.setSchemaEntity(name)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setSchemaProperty(_ name: String) throws -> Void {
    m_obj.setSchemaProperty(name)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setSchemaType(_ name: String) throws -> Void {
    m_obj.setSchemaType(name)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func updateEntry() throws -> Void {
    m_obj.updateEntry()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func updateProperty(_ XPath: String, _ value: String) throws -> Void {
    m_obj.updateProperty(XPath, value)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksODataError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}