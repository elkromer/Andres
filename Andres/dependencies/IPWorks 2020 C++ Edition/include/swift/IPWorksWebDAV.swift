
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum WebdavAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
  case authOAuth = 6
}
public enum WebdavDepths : Int32 {
  case dpUnspecified = 0
  case dpResourceOnly = 1
  case dpImmediateChildren = 2
  case dpInfinity = 3
}
public enum WebdavFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum WebdavFollowRedirects : Int32 {
  case frNever = 0
  case frAlways = 1
  case frSameScheme = 2
}
public enum WebdavPropertyOperations : Int32 {
  case opNone = 0
  case opSet = 1
  case opDelete = 2
}
public enum WebdavProxyAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
}
public enum WebdavProxySSLs : Int32 {
  case psAutomatic = 0
  case psAlways = 1
  case psNever = 2
  case psTunnel = 3
}
public enum WebdavSSLCertStoreTypes : Int32 {
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


public protocol IPWorksWebDAVDelegateSwift {
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDirList(_ resourceURI: String, _ displayName: String, _ contentLanguage: String, _ contentLength: String, _ contentType: String, _ lastModified: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onHeader(_ field: String, _ value: String)
  func onLog(_ logLevel: Int32, _ message: String, _ logType: String)
  func onRedirect(_ location: String, _ accept: inout Int32)
  func onResourceProperties(_ resourceURI: String, _ resourceProperties: String)
  func onSetCookie(_ name: String, _ value: String, _ expires: String, _ domain: String, _ path: String, _ secure: Bool)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32)
  func onStatus(_ HTTPVersion: String, _ statusCode: Int32, _ description: String)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data)
}

public enum IPWorksWebDAVError : Error {
  case Error(Int32, String)
}

public class IPWorksWebDAVSwift : NSObject, IPWorksWebDAVDelegate {
  public var m_obj: IPWorksWebDAV
  var m_delegate: IPWorksWebDAVDelegateSwift?

  override init() {
    self.m_obj = IPWorksWebDAV()
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

  public var delegate: IPWorksWebDAVDelegateSwift? {
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

  public func onDirList(_ resourceURI: String!, _ displayName: String!, _ contentLanguage: String!, _ contentLength: String!, _ contentType: String!, _ lastModified: String!) {
    if (m_delegate != nil) {
      m_delegate!.onDirList(resourceURI, displayName, contentLanguage, contentLength, contentType, lastModified)
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

  public func onResourceProperties(_ resourceURI: String!, _ resourceProperties: String!) {
    if (m_delegate != nil) {
      m_delegate!.onResourceProperties(resourceURI, resourceProperties)
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

  public var authScheme: WebdavAuthSchemes {
    get {
      return WebdavAuthSchemes(rawValue: m_obj.authScheme)!
    }
    set {
      m_obj.authScheme = newValue.rawValue
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieExpiration(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieExpiration(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieName(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieName(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieName(cookieIndex: Int32, newCookieName: String) throws -> Void {
    m_obj.setCookieName(cookieIndex, newCookieName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func cookiePath(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookiePath(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieSecure(cookieIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.cookieSecure(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func cookieValue(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieValue(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieValue(cookieIndex: Int32, newCookieValue: String) throws -> Void {
    m_obj.setCookieValue(cookieIndex, newCookieValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var depth: WebdavDepths {
    get {
      return WebdavDepths(rawValue: m_obj.depth)!
    }
    set {
      m_obj.depth = newValue.rawValue
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

  public var firewallType: WebdavFirewallTypes {
    get {
      return WebdavFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var followRedirects: WebdavFollowRedirects {
    get {
      return WebdavFollowRedirects(rawValue: m_obj.followRedirects)!
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

  public var lockType: String {
    get {
      let ret: String? = String(m_obj.lockType)
      return unwrapNSString(ret)
    }
    set {
      m_obj.lockType = newValue as NSString
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setNamespacePrefix(namespaceIndex: Int32, newNamespacePrefix: String) throws -> Void {
    m_obj.setNamespacePrefix(namespaceIndex, newNamespacePrefix)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func namespaceURI(namespaceIndex: Int32) throws -> String {
    let ret: String? = m_obj.namespaceURI(namespaceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setNamespaceURI(namespaceIndex: Int32, newNamespaceURI: String) throws -> Void {
    m_obj.setNamespaceURI(namespaceIndex, newNamespaceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func parsedHeaderValue(parsedHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.parsedHeaderValue(parsedHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
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

  public var propertyCount: Int32 {
    get {
      return m_obj.propertyCount
    }
    set {
      m_obj.propertyCount = newValue
    }
  }

  public func propertyAttr(propertyIndex: Int32) throws -> String {
    let ret: String? = m_obj.propertyAttr(propertyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPropertyAttr(propertyIndex: Int32, newPropertyAttr: String) throws -> Void {
    m_obj.setPropertyAttr(propertyIndex, newPropertyAttr)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func propertyName(propertyIndex: Int32) throws -> String {
    let ret: String? = m_obj.propertyName(propertyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPropertyName(propertyIndex: Int32, newPropertyName: String) throws -> Void {
    m_obj.setPropertyName(propertyIndex, newPropertyName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func propertyNamespaceURI(propertyIndex: Int32) throws -> String {
    let ret: String? = m_obj.propertyNamespaceURI(propertyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPropertyNamespaceURI(propertyIndex: Int32, newPropertyNamespaceURI: String) throws -> Void {
    m_obj.setPropertyNamespaceURI(propertyIndex, newPropertyNamespaceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func propertyOperation(propertyIndex: Int32) throws -> WebdavPropertyOperations {
    let ret = WebdavPropertyOperations(rawValue: m_obj.propertyOperation(propertyIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func setPropertyOperation(propertyIndex: Int32, newPropertyOperation: WebdavPropertyOperations) throws -> Void {
    m_obj.setPropertyOperation(propertyIndex, newPropertyOperation.rawValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func propertyStatus(propertyIndex: Int32) throws -> String {
    let ret: String? = m_obj.propertyStatus(propertyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func propertyValue(propertyIndex: Int32) throws -> String {
    let ret: String? = m_obj.propertyValue(propertyIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setPropertyValue(propertyIndex: Int32, newPropertyValue: String) throws -> Void {
    m_obj.setPropertyValue(propertyIndex, newPropertyValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var proxyAuthScheme: WebdavProxyAuthSchemes {
    get {
      return WebdavProxyAuthSchemes(rawValue: m_obj.proxyAuthScheme)!
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

  public var proxySSL: WebdavProxySSLs {
    get {
      return WebdavProxySSLs(rawValue: m_obj.proxySSL)!
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

  public var resourceCount: Int32 {
    get {
      return m_obj.resourceCount
    }
  }

  public func resourceContentLanguage(resourceIndex: Int32) throws -> String {
    let ret: String? = m_obj.resourceContentLanguage(resourceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func resourceContentLength(resourceIndex: Int32) throws -> String {
    let ret: String? = m_obj.resourceContentLength(resourceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func resourceContentType(resourceIndex: Int32) throws -> String {
    let ret: String? = m_obj.resourceContentType(resourceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func resourceDisplayName(resourceIndex: Int32) throws -> String {
    let ret: String? = m_obj.resourceDisplayName(resourceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func resourceLastModified(resourceIndex: Int32) throws -> String {
    let ret: String? = m_obj.resourceLastModified(resourceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func resourceURI(resourceIndex: Int32) throws -> String {
    let ret: String? = m_obj.resourceURI(resourceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
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

  public var SSLCertStoreType: WebdavSSLCertStoreTypes {
    get {
      return WebdavSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func addNamespace(_ prefix: String, _ namespaceURI: String) throws -> Void {
    m_obj.addNamespace(prefix, namespaceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func copyResource(_ sourceResourceURI: String, _ destinationResourceURI: String) throws -> Void {
    m_obj.copyResource(sourceResourceURI, destinationResourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func deleteResource(_ resourceURI: String) throws -> Void {
    m_obj.deleteResource(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func findProperties(_ resourceURI: String) throws -> Void {
    m_obj.findProperties(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func findPropertyNames(_ resourceURI: String) throws -> Void {
    m_obj.findPropertyNames(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getProperty(_ propertyName: String) throws -> String {
    let ret: String? = m_obj.getProperty(propertyName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func getResource(_ resourceURI: String) throws -> Void {
    m_obj.getResource(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listDirectory(_ resourceURI: String) throws -> Void {
    m_obj.listDirectory(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func lockResource(_ resourceURI: String) throws -> Void {
    m_obj.lockResource(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func makeDirectory(_ resourceURI: String) throws -> Void {
    m_obj.makeDirectory(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func moveResource(_ sourceResourceURI: String, _ destinationResourceURI: String) throws -> Void {
    m_obj.moveResource(sourceResourceURI, destinationResourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func patchProperties(_ resourceURI: String) throws -> Void {
    m_obj.patchProperties(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func postToResource(_ resourceURI: String, _ postData: Data) throws -> Void {
    m_obj.postToResource(resourceURI, postData)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putResource(_ resourceURI: String) throws -> Void {
    m_obj.putResource(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setProperty(_ propertyName: String, _ propertyValue: String) throws -> Void {
    m_obj.setProperty(propertyName, propertyValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func unLockResource(_ resourceURI: String) throws -> Void {
    m_obj.unLockResource(resourceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksWebDAVError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}