
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum RssAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
  case authOAuth = 6
}
public enum RssFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum RssFollowRedirects : Int32 {
  case frNever = 0
  case frAlways = 1
  case frSameScheme = 2
}
public enum RssProxyAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
}
public enum RssProxySSLs : Int32 {
  case psAutomatic = 0
  case psAlways = 1
  case psNever = 2
  case psTunnel = 3
}
public enum RssRSSVersions : Int32 {
  case rssVersionUndefined = 0
  case rssVersion091 = 1
  case rssVersion092 = 2
  case rssVersion200 = 3
}
public enum RssSSLCertStoreTypes : Int32 {
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


public protocol IPWorksRSSDelegateSwift {
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onHeader(_ field: String, _ value: String)
  func onLog(_ logLevel: Int32, _ message: String, _ logType: String)
  func onOPMLHeader(_ field: String, _ value: String)
  func onOPMLOutline(_ level: Int32, _ text: String, _ typeName: String, _ title: String, _ URL: String, _ XMLURL: String, _ HTMLURL: String, _ created: String, _ description: String, _ otherAttrs: String)
  func onRedirect(_ location: String, _ accept: inout Int32)
  func onSetCookie(_ name: String, _ value: String, _ expires: String, _ domain: String, _ path: String, _ secure: Bool)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32)
  func onStatus(_ HTTPVersion: String, _ statusCode: Int32, _ description: String)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data)
}

public enum IPWorksRSSError : Error {
  case Error(Int32, String)
}

public class IPWorksRSSSwift : NSObject, IPWorksRSSDelegate {
  public var m_obj: IPWorksRSS
  var m_delegate: IPWorksRSSDelegateSwift?

  override init() {
    self.m_obj = IPWorksRSS()
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

  public var delegate: IPWorksRSSDelegateSwift? {
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

  public func onOPMLHeader(_ field: String!, _ value: String!) {
    if (m_delegate != nil) {
      m_delegate!.onOPMLHeader(field, value)
    }
  }

  public func onOPMLOutline(_ level: Int32, _ text: String!, _ typeName: String!, _ title: String!, _ URL: String!, _ XMLURL: String!, _ HTMLURL: String!, _ created: String!, _ description: String!, _ otherAttrs: String!) {
    if (m_delegate != nil) {
      m_delegate!.onOPMLOutline(level, text, typeName, title, URL, XMLURL, HTMLURL, created, description, otherAttrs)
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

  public var authorization: String {
    get {
      let ret: String? = String(m_obj.authorization)
      return unwrapNSString(ret)
    }
    set {
      m_obj.authorization = newValue as NSString
    }
  }

  public var authScheme: RssAuthSchemes {
    get {
      return RssAuthSchemes(rawValue: m_obj.authScheme)!
    }
    set {
      m_obj.authScheme = newValue.rawValue
    }
  }

  public var channelCategory: String {
    get {
      let ret: String? = String(m_obj.channelCategory)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelCategory = newValue as NSString
    }
  }

  public var channelCategoryDomain: String {
    get {
      let ret: String? = String(m_obj.channelCategoryDomain)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelCategoryDomain = newValue as NSString
    }
  }

  public var channelCopyright: String {
    get {
      let ret: String? = String(m_obj.channelCopyright)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelCopyright = newValue as NSString
    }
  }

  public var channelDescription: String {
    get {
      let ret: String? = String(m_obj.channelDescription)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelDescription = newValue as NSString
    }
  }

  public var channelDocs: String {
    get {
      let ret: String? = String(m_obj.channelDocs)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelDocs = newValue as NSString
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

  public var channelImageDescription: String {
    get {
      let ret: String? = String(m_obj.channelImageDescription)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelImageDescription = newValue as NSString
    }
  }

  public var channelImageHeight: String {
    get {
      let ret: String? = String(m_obj.channelImageHeight)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelImageHeight = newValue as NSString
    }
  }

  public var channelImageLink: String {
    get {
      let ret: String? = String(m_obj.channelImageLink)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelImageLink = newValue as NSString
    }
  }

  public var channelImageTitle: String {
    get {
      let ret: String? = String(m_obj.channelImageTitle)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelImageTitle = newValue as NSString
    }
  }

  public var channelImageUrl: String {
    get {
      let ret: String? = String(m_obj.channelImageUrl)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelImageUrl = newValue as NSString
    }
  }

  public var channelImageWidth: String {
    get {
      let ret: String? = String(m_obj.channelImageWidth)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelImageWidth = newValue as NSString
    }
  }

  public var channelLanguage: String {
    get {
      let ret: String? = String(m_obj.channelLanguage)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelLanguage = newValue as NSString
    }
  }

  public var channelLastBuildDate: String {
    get {
      let ret: String? = String(m_obj.channelLastBuildDate)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelLastBuildDate = newValue as NSString
    }
  }

  public var channelLink: String {
    get {
      let ret: String? = String(m_obj.channelLink)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelLink = newValue as NSString
    }
  }

  public var channelManagingEditor: String {
    get {
      let ret: String? = String(m_obj.channelManagingEditor)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelManagingEditor = newValue as NSString
    }
  }

  public var channelPubDate: String {
    get {
      let ret: String? = String(m_obj.channelPubDate)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelPubDate = newValue as NSString
    }
  }

  public var channelSkipDays: String {
    get {
      let ret: String? = String(m_obj.channelSkipDays)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelSkipDays = newValue as NSString
    }
  }

  public var channelSkipHours: String {
    get {
      let ret: String? = String(m_obj.channelSkipHours)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelSkipHours = newValue as NSString
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

  public var channelTtl: String {
    get {
      let ret: String? = String(m_obj.channelTtl)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelTtl = newValue as NSString
    }
  }

  public var channelWebMaster: String {
    get {
      let ret: String? = String(m_obj.channelWebMaster)
      return unwrapNSString(ret)
    }
    set {
      m_obj.channelWebMaster = newValue as NSString
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieExpiration(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieExpiration(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieName(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieName(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieName(cookieIndex: Int32, newCookieName: String) throws -> Void {
    m_obj.setCookieName(cookieIndex, newCookieName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func cookiePath(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookiePath(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieSecure(cookieIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.cookieSecure(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func cookieValue(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieValue(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieValue(cookieIndex: Int32, newCookieValue: String) throws -> Void {
    m_obj.setCookieValue(cookieIndex, newCookieValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var firewallAutoDetect: Bool {
    get {
      return m_obj.firewallAutoDetect
    }
    set {
      m_obj.firewallAutoDetect = newValue
    }
  }

  public var firewallType: RssFirewallTypes {
    get {
      return RssFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var followRedirects: RssFollowRedirects {
    get {
      return RssFollowRedirects(rawValue: m_obj.followRedirects)!
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

  public var itemCount: Int32 {
    get {
      return m_obj.itemCount
    }
    set {
      m_obj.itemCount = newValue
    }
  }

  public func itemAuthor(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemAuthor(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemAuthor(itemIndex: Int32, newItemAuthor: String) throws -> Void {
    m_obj.setItemAuthor(itemIndex, newItemAuthor)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemCategory(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemCategory(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemCategory(itemIndex: Int32, newItemCategory: String) throws -> Void {
    m_obj.setItemCategory(itemIndex, newItemCategory)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemCategoryDomain(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemCategoryDomain(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemCategoryDomain(itemIndex: Int32, newItemCategoryDomain: String) throws -> Void {
    m_obj.setItemCategoryDomain(itemIndex, newItemCategoryDomain)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemComments(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemComments(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemComments(itemIndex: Int32, newItemComments: String) throws -> Void {
    m_obj.setItemComments(itemIndex, newItemComments)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemDescription(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemDescription(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemDescription(itemIndex: Int32, newItemDescription: String) throws -> Void {
    m_obj.setItemDescription(itemIndex, newItemDescription)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemEnclosureLength(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemEnclosureLength(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemEnclosureLength(itemIndex: Int32, newItemEnclosureLength: String) throws -> Void {
    m_obj.setItemEnclosureLength(itemIndex, newItemEnclosureLength)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemEnclosureType(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemEnclosureType(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemEnclosureType(itemIndex: Int32, newItemEnclosureType: String) throws -> Void {
    m_obj.setItemEnclosureType(itemIndex, newItemEnclosureType)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemEnclosureUrl(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemEnclosureUrl(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemEnclosureUrl(itemIndex: Int32, newItemEnclosureUrl: String) throws -> Void {
    m_obj.setItemEnclosureUrl(itemIndex, newItemEnclosureUrl)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemGuid(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemGuid(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemGuid(itemIndex: Int32, newItemGuid: String) throws -> Void {
    m_obj.setItemGuid(itemIndex, newItemGuid)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemGuidIsPermaLink(itemIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.itemGuidIsPermaLink(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func setItemGuidIsPermaLink(itemIndex: Int32, newItemGuidIsPermaLink: Bool) throws -> Void {
    m_obj.setItemGuidIsPermaLink(itemIndex, newItemGuidIsPermaLink)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemXML(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemXML(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemXML(itemIndex: Int32, newItemXML: String) throws -> Void {
    m_obj.setItemXML(itemIndex, newItemXML)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemLink(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemLink(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemLink(itemIndex: Int32, newItemLink: String) throws -> Void {
    m_obj.setItemLink(itemIndex, newItemLink)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemPubDate(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemPubDate(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemPubDate(itemIndex: Int32, newItemPubDate: String) throws -> Void {
    m_obj.setItemPubDate(itemIndex, newItemPubDate)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemSource(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemSource(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemSource(itemIndex: Int32, newItemSource: String) throws -> Void {
    m_obj.setItemSource(itemIndex, newItemSource)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemSourceURL(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemSourceURL(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemSourceURL(itemIndex: Int32, newItemSourceURL: String) throws -> Void {
    m_obj.setItemSourceURL(itemIndex, newItemSourceURL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func itemTitle(itemIndex: Int32) throws -> String {
    let ret: String? = m_obj.itemTitle(itemIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setItemTitle(itemIndex: Int32, newItemTitle: String) throws -> Void {
    m_obj.setItemTitle(itemIndex, newItemTitle)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setNamespacePrefix(namespaceIndex: Int32, newNamespacePrefix: String) throws -> Void {
    m_obj.setNamespacePrefix(namespaceIndex, newNamespacePrefix)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func namespaceURI(namespaceIndex: Int32) throws -> String {
    let ret: String? = m_obj.namespaceURI(namespaceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setNamespaceURI(namespaceIndex: Int32, newNamespaceURI: String) throws -> Void {
    m_obj.setNamespaceURI(namespaceIndex, newNamespaceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func parsedHeaderValue(parsedHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.parsedHeaderValue(parsedHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
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

  public var proxyAuthScheme: RssProxyAuthSchemes {
    get {
      return RssProxyAuthSchemes(rawValue: m_obj.proxyAuthScheme)!
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

  public var proxySSL: RssProxySSLs {
    get {
      return RssProxySSLs(rawValue: m_obj.proxySSL)!
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

  public var RSSData: String {
    get {
      let ret: String? = String(m_obj.RSSData)
      return unwrapNSString(ret)
    }
    set {
      m_obj.RSSData = newValue as NSString
    }
  }

  public var RSSVersion: RssRSSVersions {
    get {
      return RssRSSVersions(rawValue: m_obj.RSSVersion)!
    }
    set {
      m_obj.RSSVersion = newValue.rawValue
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

  public var SSLCertStoreType: RssSSLCertStoreTypes {
    get {
      return RssSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func addItem(_ title: String, _ description: String, _ link: String) throws -> Void {
    m_obj.addItem(title, description, link)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func addNamespace(_ prefix: String, _ namespaceURI: String) throws -> Void {
    m_obj.addNamespace(prefix, namespaceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getFeed(_ URL: String) throws -> Void {
    m_obj.getFeed(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getProperty(_ propertyName: String) throws -> String {
    let ret: String? = m_obj.getProperty(propertyName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func getURL(_ URL: String) throws -> Void {
    m_obj.getURL(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func OPMLAttr(_ attrName: String) throws -> String {
    let ret: String? = m_obj.OPMLAttr(attrName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func put(_ URL: String) throws -> Void {
    m_obj.put(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func readFile(_ fileName: String) throws -> Void {
    m_obj.readFile(fileName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func readOPML(_ OPMLFile: String) throws -> Void {
    m_obj.readOPML(OPMLFile)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setProperty(_ propertyName: String, _ propertyValue: String) throws -> Void {
    m_obj.setProperty(propertyName, propertyValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func writeFile(_ filename: String) throws -> Void {
    m_obj.writeFile(filename)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRSSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}