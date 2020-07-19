
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum RestAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
  case authOAuth = 6
}
public enum RestFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum RestFollowRedirects : Int32 {
  case frNever = 0
  case frAlways = 1
  case frSameScheme = 2
}
public enum RestProxyAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
}
public enum RestProxySSLs : Int32 {
  case psAutomatic = 0
  case psAlways = 1
  case psNever = 2
  case psTunnel = 3
}
public enum RestSSLCertStoreTypes : Int32 {
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


public protocol IPWorksRESTDelegateSwift {
  func onCharacters(_ text: String)
  func onComment(_ text: String)
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onEndElement(_ namespace: String, _ element: String, _ QName: String, _ isEmpty: Bool)
  func onEndPrefixMapping(_ prefix: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onEvalEntity(_ entity: String, _ value: inout NSString?)
  func onHeader(_ field: String, _ value: String)
  func onIgnorableWhitespace(_ text: String)
  func onLog(_ logLevel: Int32, _ message: String, _ logType: String)
  func onMeta(_ text: String)
  func onPI(_ text: String)
  func onRedirect(_ location: String, _ accept: inout Int32)
  func onSetCookie(_ name: String, _ value: String, _ expires: String, _ domain: String, _ path: String, _ secure: Bool)
  func onSpecialSection(_ sectionId: String, _ text: String)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartElement(_ namespace: String, _ element: String, _ QName: String, _ isEmpty: Bool)
  func onStartPrefixMapping(_ prefix: String, _ URI: String)
  func onStartTransfer(_ direction: Int32)
  func onStatus(_ HTTPVersion: String, _ statusCode: Int32, _ description: String)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data)
}

public enum IPWorksRESTError : Error {
  case Error(Int32, String)
}

public class IPWorksRESTSwift : NSObject, IPWorksRESTDelegate {
  public var m_obj: IPWorksREST
  var m_delegate: IPWorksRESTDelegateSwift?

  override init() {
    self.m_obj = IPWorksREST()
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

  public var delegate: IPWorksRESTDelegateSwift? {
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

  public func onCharacters(_ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onCharacters(text)
    }
  }

  public func onComment(_ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onComment(text)
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

  public func onEndElement(_ namespace: String!, _ element: String!, _ QName: String!, _ isEmpty: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onEndElement(namespace, element, QName, isEmpty)
    }
  }

  public func onEndPrefixMapping(_ prefix: String!) {
    if (m_delegate != nil) {
      m_delegate!.onEndPrefixMapping(prefix)
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

  public func onEvalEntity(_ entity: String!, _ value: AutoreleasingUnsafeMutablePointer<NSString?>) {
    if (m_delegate != nil) {
      m_delegate!.onEvalEntity(entity, &value.pointee)
    }
  }

  public func onHeader(_ field: String!, _ value: String!) {
    if (m_delegate != nil) {
      m_delegate!.onHeader(field, value)
    }
  }

  public func onIgnorableWhitespace(_ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onIgnorableWhitespace(text)
    }
  }

  public func onLog(_ logLevel: Int32, _ message: String!, _ logType: String!) {
    if (m_delegate != nil) {
      m_delegate!.onLog(logLevel, message, logType)
    }
  }

  public func onMeta(_ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onMeta(text)
    }
  }

  public func onPI(_ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onPI(text)
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

  public func onSpecialSection(_ sectionId: String!, _ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onSpecialSection(sectionId, text)
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

  public func onStartElement(_ namespace: String!, _ element: String!, _ QName: String!, _ isEmpty: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onStartElement(namespace, element, QName, isEmpty)
    }
  }

  public func onStartPrefixMapping(_ prefix: String!, _ URI: String!) {
    if (m_delegate != nil) {
      m_delegate!.onStartPrefixMapping(prefix, URI)
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

  public var authScheme: RestAuthSchemes {
    get {
      return RestAuthSchemes(rawValue: m_obj.authScheme)!
    }
    set {
      m_obj.authScheme = newValue.rawValue
    }
  }

  public var buildDOM: Bool {
    get {
      return m_obj.buildDOM
    }
    set {
      m_obj.buildDOM = newValue
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieExpiration(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieExpiration(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieName(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieName(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieName(cookieIndex: Int32, newCookieName: String) throws -> Void {
    m_obj.setCookieName(cookieIndex, newCookieName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func cookiePath(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookiePath(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieSecure(cookieIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.cookieSecure(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func cookieValue(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieValue(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieValue(cookieIndex: Int32, newCookieValue: String) throws -> Void {
    m_obj.setCookieValue(cookieIndex, newCookieValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var firewallAutoDetect: Bool {
    get {
      return m_obj.firewallAutoDetect
    }
    set {
      m_obj.firewallAutoDetect = newValue
    }
  }

  public var firewallType: RestFirewallTypes {
    get {
      return RestFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var followRedirects: RestFollowRedirects {
    get {
      return RestFollowRedirects(rawValue: m_obj.followRedirects)!
    }
    set {
      m_obj.followRedirects = newValue.rawValue
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

  public var HTTPMethod: String {
    get {
      let ret: String? = String(m_obj.HTTPMethod)
      return unwrapNSString(ret)
    }
    set {
      m_obj.HTTPMethod = newValue as NSString
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
  }

  public func namespacePrefix(namespaceIndex: Int32) throws -> String {
    let ret: String? = m_obj.namespacePrefix(namespaceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func namespaceURI(namespaceIndex: Int32) throws -> String {
    let ret: String? = m_obj.namespaceURI(namespaceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func parsedHeaderValue(parsedHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.parsedHeaderValue(parsedHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
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

  public var postData: String {
    get {
      let ret: String? = String(m_obj.postData)
      return unwrapNSString(ret)
    }
    set {
      m_obj.postData = newValue as NSString
    }
  }

  public var postDataB: Data {
    get {
      let ret: Data? = m_obj.postDataB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.postDataB = newValue as NSData
    }
  }

  public var proxyAuthScheme: RestProxyAuthSchemes {
    get {
      return RestProxyAuthSchemes(rawValue: m_obj.proxyAuthScheme)!
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

  public var proxySSL: RestProxySSLs {
    get {
      return RestProxySSLs(rawValue: m_obj.proxySSL)!
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

  public var SSLCertStoreType: RestSSLCertStoreTypes {
    get {
      return RestSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var statusLine: String {
    get {
      let ret: String? = String(m_obj.statusLine)
      return unwrapNSString(ret)
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

  public var URL: String {
    get {
      let ret: String? = String(m_obj.URL)
      return unwrapNSString(ret)
    }
    set {
      m_obj.URL = newValue as NSString
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

  public var validate: Bool {
    get {
      return m_obj.validate
    }
    set {
      m_obj.validate = newValue
    }
  }

  public var attrCount: Int32 {
    get {
      return m_obj.attrCount
    }
  }

  public func attrName(attrIndex: Int32) throws -> String {
    let ret: String? = m_obj.attrName(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func attrNamespace(attrIndex: Int32) throws -> String {
    let ret: String? = m_obj.attrNamespace(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func attrPrefix(attrIndex: Int32) throws -> String {
    let ret: String? = m_obj.attrPrefix(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func attrValue(attrIndex: Int32) throws -> String {
    let ret: String? = m_obj.attrValue(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var XChildCount: Int32 {
    get {
      return m_obj.XChildCount
    }
  }

  public func XChildName(xChildIndex: Int32) throws -> String {
    let ret: String? = m_obj.XChildName(xChildIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func XChildNamespace(xChildIndex: Int32) throws -> String {
    let ret: String? = m_obj.XChildNamespace(xChildIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func XChildPrefix(xChildIndex: Int32) throws -> String {
    let ret: String? = m_obj.XChildPrefix(xChildIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func XChildXText(xChildIndex: Int32) throws -> String {
    let ret: String? = m_obj.XChildXText(xChildIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var XElement: String {
    get {
      let ret: String? = String(m_obj.XElement)
      return unwrapNSString(ret)
    }
  }

  public var XErrorPath: String {
    get {
      let ret: String? = String(m_obj.XErrorPath)
      return unwrapNSString(ret)
    }
    set {
      m_obj.XErrorPath = newValue as NSString
    }
  }

  public var XNamespace: String {
    get {
      let ret: String? = String(m_obj.XNamespace)
      return unwrapNSString(ret)
    }
  }

  public var XParent: String {
    get {
      let ret: String? = String(m_obj.XParent)
      return unwrapNSString(ret)
    }
  }

  public var XPath: String {
    get {
      let ret: String? = String(m_obj.XPath)
      return unwrapNSString(ret)
    }
    set {
      m_obj.XPath = newValue as NSString
    }
  }

  public var XPrefix: String {
    get {
      let ret: String? = String(m_obj.XPrefix)
      return unwrapNSString(ret)
    }
  }

  public var XSubTree: String {
    get {
      let ret: String? = String(m_obj.XSubTree)
      return unwrapNSString(ret)
    }
  }

  public var XText: String {
    get {
      let ret: String? = String(m_obj.XText)
      return unwrapNSString(ret)
    }
  }

  /* Methods */

  public func addCookie(_ cookieName: String, _ cookieValue: String) throws -> Void {
    m_obj.addCookie(cookieName, cookieValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func attr(_ attrName: String) throws -> String {
    let ret: String? = m_obj.attr(attrName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func delete_(_ URL: String) throws -> Void {
    m_obj.delete(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func get(_ URL: String) throws -> Void {
    m_obj.get(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func hasXPath(_ XPath: String) throws -> Bool {
    let ret: Bool? = m_obj.hasXPath(XPath)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func post(_ URL: String) throws -> Void {
    m_obj.post(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func put(_ URL: String) throws -> Void {
    m_obj.put(URL)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func tryXPath(_ xpath: String) throws -> Bool {
    let ret: Bool? = m_obj.tryXPath(xpath)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksRESTError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

}