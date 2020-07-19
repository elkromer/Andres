
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum OauthClientProfiles : Int32 {
  case cfApplication = 0
  case cfWebServer = 1
  case cfDevice = 2
  case cfMobile = 3
  case cfBrowser = 4
  case cfJWT = 5
}
public enum OauthFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum OauthFollowRedirects : Int32 {
  case frNever = 0
  case frAlways = 1
  case frSameScheme = 2
}
public enum OauthGrantTypes : Int32 {
  case ogtAuthorizationCode = 0
  case ogtImplicit = 1
  case ogtPassword = 2
  case ogtClientCredentials = 3
}
public enum OauthProxyAuthSchemes : Int32 {
  case authBasic = 0
  case authDigest = 1
  case authProprietary = 2
  case authNone = 3
  case authNtlm = 4
  case authNegotiate = 5
}
public enum OauthProxySSLs : Int32 {
  case psAutomatic = 0
  case psAlways = 1
  case psNever = 2
  case psTunnel = 3
}
public enum OauthSSLCertStoreTypes : Int32 {
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
public enum OauthWebServerSSLCertStoreTypes : Int32 {
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


public protocol IPWorksOAuthDelegateSwift {
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onHeader(_ field: String, _ value: String)
  func onLaunchBrowser(_ URL: inout NSString?, _ command: inout NSString?)
  func onLog(_ logLevel: Int32, _ message: String, _ logType: String)
  func onRedirect(_ location: String, _ accept: inout Int32)
  func onReturnURL(_ URLPath: String, _ queryString: String, _ responseHeaders: inout NSString?, _ responseBody: inout NSString?)
  func onSetCookie(_ name: String, _ value: String, _ expires: String, _ domain: String, _ path: String, _ secure: Bool)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32)
  func onStatus(_ HTTPVersion: String, _ statusCode: Int32, _ description: String)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data)
}

public enum IPWorksOAuthError : Error {
  case Error(Int32, String)
}

public class IPWorksOAuthSwift : NSObject, IPWorksOAuthDelegate {
  public var m_obj: IPWorksOAuth
  var m_delegate: IPWorksOAuthDelegateSwift?

  override init() {
    self.m_obj = IPWorksOAuth()
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

  public var delegate: IPWorksOAuthDelegateSwift? {
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

  public func onLaunchBrowser(_ URL: AutoreleasingUnsafeMutablePointer<NSString?>, _ command: AutoreleasingUnsafeMutablePointer<NSString?>) {
    if (m_delegate != nil) {
      m_delegate!.onLaunchBrowser(&URL.pointee, &command.pointee)
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

  public func onReturnURL(_ URLPath: String!, _ queryString: String!, _ responseHeaders: AutoreleasingUnsafeMutablePointer<NSString?>, _ responseBody: AutoreleasingUnsafeMutablePointer<NSString?>) {
    if (m_delegate != nil) {
      m_delegate!.onReturnURL(URLPath, queryString, &responseHeaders.pointee, &responseBody.pointee)
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

  public var accessToken: String {
    get {
      let ret: String? = String(m_obj.accessToken)
      return unwrapNSString(ret)
    }
    set {
      m_obj.accessToken = newValue as NSString
    }
  }

  public var authorizationCode: String {
    get {
      let ret: String? = String(m_obj.authorizationCode)
      return unwrapNSString(ret)
    }
    set {
      m_obj.authorizationCode = newValue as NSString
    }
  }

  public var authorizationScope: String {
    get {
      let ret: String? = String(m_obj.authorizationScope)
      return unwrapNSString(ret)
    }
    set {
      m_obj.authorizationScope = newValue as NSString
    }
  }

  public var clientId: String {
    get {
      let ret: String? = String(m_obj.clientId)
      return unwrapNSString(ret)
    }
    set {
      m_obj.clientId = newValue as NSString
    }
  }

  public var clientProfile: OauthClientProfiles {
    get {
      return OauthClientProfiles(rawValue: m_obj.clientProfile)!
    }
    set {
      m_obj.clientProfile = newValue.rawValue
    }
  }

  public var clientSecret: String {
    get {
      let ret: String? = String(m_obj.clientSecret)
      return unwrapNSString(ret)
    }
    set {
      m_obj.clientSecret = newValue as NSString
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieExpiration(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieExpiration(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieName(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieName(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieName(cookieIndex: Int32, newCookieName: String) throws -> Void {
    m_obj.setCookieName(cookieIndex, newCookieName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func cookiePath(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookiePath(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func cookieSecure(cookieIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.cookieSecure(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func cookieValue(cookieIndex: Int32) throws -> String {
    let ret: String? = m_obj.cookieValue(cookieIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setCookieValue(cookieIndex: Int32, newCookieValue: String) throws -> Void {
    m_obj.setCookieValue(cookieIndex, newCookieValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var firewallAutoDetect: Bool {
    get {
      return m_obj.firewallAutoDetect
    }
    set {
      m_obj.firewallAutoDetect = newValue
    }
  }

  public var firewallType: OauthFirewallTypes {
    get {
      return OauthFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var followRedirects: OauthFollowRedirects {
    get {
      return OauthFollowRedirects(rawValue: m_obj.followRedirects)!
    }
    set {
      m_obj.followRedirects = newValue.rawValue
    }
  }

  public var grantType: OauthGrantTypes {
    get {
      return OauthGrantTypes(rawValue: m_obj.grantType)!
    }
    set {
      m_obj.grantType = newValue.rawValue
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

  public var otherHeaders: String {
    get {
      let ret: String? = String(m_obj.otherHeaders)
      return unwrapNSString(ret)
    }
    set {
      m_obj.otherHeaders = newValue as NSString
    }
  }

  public var paramCount: Int32 {
    get {
      return m_obj.paramCount
    }
    set {
      m_obj.paramCount = newValue
    }
  }

  public func paramName(paramIndex: Int32) throws -> String {
    let ret: String? = m_obj.paramName(paramIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setParamName(paramIndex: Int32, newParamName: String) throws -> Void {
    m_obj.setParamName(paramIndex, newParamName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func paramValue(paramIndex: Int32) throws -> String {
    let ret: String? = m_obj.paramValue(paramIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setParamValue(paramIndex: Int32, newParamValue: String) throws -> Void {
    m_obj.setParamValue(paramIndex, newParamValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var proxyAuthScheme: OauthProxyAuthSchemes {
    get {
      return OauthProxyAuthSchemes(rawValue: m_obj.proxyAuthScheme)!
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

  public var proxySSL: OauthProxySSLs {
    get {
      return OauthProxySSLs(rawValue: m_obj.proxySSL)!
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

  public var refreshToken: String {
    get {
      let ret: String? = String(m_obj.refreshToken)
      return unwrapNSString(ret)
    }
    set {
      m_obj.refreshToken = newValue as NSString
    }
  }

  public var returnURL: String {
    get {
      let ret: String? = String(m_obj.returnURL)
      return unwrapNSString(ret)
    }
    set {
      m_obj.returnURL = newValue as NSString
    }
  }

  public var serverAuthURL: String {
    get {
      let ret: String? = String(m_obj.serverAuthURL)
      return unwrapNSString(ret)
    }
    set {
      m_obj.serverAuthURL = newValue as NSString
    }
  }

  public var serverTokenURL: String {
    get {
      let ret: String? = String(m_obj.serverTokenURL)
      return unwrapNSString(ret)
    }
    set {
      m_obj.serverTokenURL = newValue as NSString
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

  public var SSLCertStoreType: OauthSSLCertStoreTypes {
    get {
      return OauthSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var transferredHeaders: String {
    get {
      let ret: String? = String(m_obj.transferredHeaders)
      return unwrapNSString(ret)
    }
  }

  public var webServerPort: Int32 {
    get {
      return m_obj.webServerPort
    }
    set {
      m_obj.webServerPort = newValue
    }
  }

  public var webServerSSLCertStore: String {
    get {
      let ret: String? = String(m_obj.webServerSSLCertStore)
      return unwrapNSString(ret)
    }
    set {
      m_obj.webServerSSLCertStore = newValue as NSString
    }
  }

  public var webServerSSLCertStoreB: Data {
    get {
      let ret: Data? = m_obj.webServerSSLCertStoreB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.webServerSSLCertStoreB = newValue as NSData
    }
  }

  public var webServerSSLCertStorePassword: String {
    get {
      let ret: String? = String(m_obj.webServerSSLCertStorePassword)
      return unwrapNSString(ret)
    }
    set {
      m_obj.webServerSSLCertStorePassword = newValue as NSString
    }
  }

  public var webServerSSLCertStoreType: OauthWebServerSSLCertStoreTypes {
    get {
      return OauthWebServerSSLCertStoreTypes(rawValue: m_obj.webServerSSLCertStoreType)!
    }
    set {
      m_obj.webServerSSLCertStoreType = newValue.rawValue
    }
  }

  public var webServerSSLCertSubject: String {
    get {
      let ret: String? = String(m_obj.webServerSSLCertSubject)
      return unwrapNSString(ret)
    }
    set {
      m_obj.webServerSSLCertSubject = newValue as NSString
    }
  }

  public var webServerSSLEnabled: Bool {
    get {
      return m_obj.webServerSSLEnabled
    }
    set {
      m_obj.webServerSSLEnabled = newValue
    }
  }

  /* Methods */

  public func addCookie(_ cookieName: String, _ cookieValue: String) throws -> Void {
    m_obj.addCookie(cookieName, cookieValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func addParam(_ paramName: String, _ paramValue: String) throws -> Void {
    m_obj.addParam(paramName, paramValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getAuthorization() throws -> String {
    let ret: String? = m_obj.getAuthorization()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func getAuthorizationURL() throws -> String {
    let ret: String? = m_obj.getAuthorizationURL()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func startWebServer() throws -> Void {
    m_obj.startWebServer()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func stopWebServer() throws -> Void {
    m_obj.stopWebServer()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksOAuthError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}