
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum LdapAttrModOps : Int32 {
  case amoAdd = 0
  case amoDelete = 1
  case amoReplace = 2
}
public enum LdapAuthMechanisms : Int32 {
  case lamSimple = 0
  case lamDigestMD5 = 1
  case lamNegotiate = 2
  case lamKerberos = 6
}
public enum LdapFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum LdapSearchDerefAliases : Int32 {
  case sdaNever = 0
  case sdaInSearching = 1
  case sdaFindingBaseObject = 2
  case sdaAlways = 3
}
public enum LdapSearchScopes : Int32 {
  case ssBaseObject = 0
  case ssSingleLevel = 1
  case ssWholeSubtree = 2
}
public enum LdapSSLCertStoreTypes : Int32 {
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
public enum LdapSSLStartModes : Int32 {
  case sslAutomatic = 0
  case sslImplicit = 1
  case sslExplicit = 2
  case sslNone = 3
}


public protocol IPWorksLDAPDelegateSwift {
  func onComputerList(_ name: String, _ operatingSystem: String, _ lastLogon: String, _ logonCount: Int32, _ dn: String)
  func onConnected(_ statusCode: Int32, _ description: String)
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDisconnected(_ statusCode: Int32, _ description: String)
  func onError(_ errorCode: Int32, _ description: String)
  func onExtendedResponse(_ messageId: Int32, _ DN: String, _ resultCode: Int32, _ resultDescription: String, _ responseName: String, _ responseValue: Data)
  func onGroupList(_ name: String, _ description: String, _ dn: String)
  func onPITrail(_ direction: Int32, _ description: String, _ message: String)
  func onResult(_ messageId: Int32, _ DN: String, _ resultCode: Int32, _ resultDescription: String)
  func onSearchComplete(_ messageId: Int32, _ DN: String, _ resultCode: Int32, _ resultDescription: String)
  func onSearchPage(_ messageId: Int32, _ DN: String, _ resultCode: Int32, _ resultDescription: String, _ cancelSearch: inout Int32)
  func onSearchResult(_ messageId: Int32, _ DN: String)
  func onSearchResultReference(_ messageId: Int32, _ ldapUrl: String)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onUserList(_ name: String, _ description: String, _ lastLogon: String, _ memberOf: String, _ dn: String)
}

public enum IPWorksLDAPError : Error {
  case Error(Int32, String)
}

public class IPWorksLDAPSwift : NSObject, IPWorksLDAPDelegate {
  public var m_obj: IPWorksLDAP
  var m_delegate: IPWorksLDAPDelegateSwift?

  override init() {
    self.m_obj = IPWorksLDAP()
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

  public var delegate: IPWorksLDAPDelegateSwift? {
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

  public func onComputerList(_ name: String!, _ operatingSystem: String!, _ lastLogon: String!, _ logonCount: Int32, _ dn: String!) {
    if (m_delegate != nil) {
      m_delegate!.onComputerList(name, operatingSystem, lastLogon, logonCount, dn)
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

  public func onError(_ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(errorCode, description)
    }
  }

  public func onExtendedResponse(_ messageId: Int32, _ DN: String!, _ resultCode: Int32, _ resultDescription: String!, _ responseName: String!, _ responseValue: Data!) {
    if (m_delegate != nil) {
      m_delegate!.onExtendedResponse(messageId, DN, resultCode, resultDescription, responseName, responseValue)
    }
  }

  public func onGroupList(_ name: String!, _ description: String!, _ dn: String!) {
    if (m_delegate != nil) {
      m_delegate!.onGroupList(name, description, dn)
    }
  }

  public func onPITrail(_ direction: Int32, _ description: String!, _ message: String!) {
    if (m_delegate != nil) {
      m_delegate!.onPITrail(direction, description, message)
    }
  }

  public func onResult(_ messageId: Int32, _ DN: String!, _ resultCode: Int32, _ resultDescription: String!) {
    if (m_delegate != nil) {
      m_delegate!.onResult(messageId, DN, resultCode, resultDescription)
    }
  }

  public func onSearchComplete(_ messageId: Int32, _ DN: String!, _ resultCode: Int32, _ resultDescription: String!) {
    if (m_delegate != nil) {
      m_delegate!.onSearchComplete(messageId, DN, resultCode, resultDescription)
    }
  }

  public func onSearchPage(_ messageId: Int32, _ DN: String!, _ resultCode: Int32, _ resultDescription: String!, _ cancelSearch: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onSearchPage(messageId, DN, resultCode, resultDescription, &cancelSearch.pointee)
    }
  }

  public func onSearchResult(_ messageId: Int32, _ DN: String!) {
    if (m_delegate != nil) {
      m_delegate!.onSearchResult(messageId, DN)
    }
  }

  public func onSearchResultReference(_ messageId: Int32, _ ldapUrl: String!) {
    if (m_delegate != nil) {
      m_delegate!.onSearchResultReference(messageId, ldapUrl)
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

  public func onUserList(_ name: String!, _ description: String!, _ lastLogon: String!, _ memberOf: String!, _ dn: String!) {
    if (m_delegate != nil) {
      m_delegate!.onUserList(name, description, lastLogon, memberOf, dn)
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

  public var acceptData: Bool {
    get {
      return m_obj.acceptData
    }
    set {
      m_obj.acceptData = newValue
    }
  }

  public var attrCount: Int32 {
    get {
      return m_obj.attrCount
    }
    set {
      m_obj.attrCount = newValue
    }
  }

  public func attrType(attrIndex: Int32) throws -> String {
    let ret: String? = m_obj.attrType(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setAttrType(attrIndex: Int32, newAttrType: String) throws -> Void {
    m_obj.setAttrType(attrIndex, newAttrType)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func attrModOp(attrIndex: Int32) throws -> LdapAttrModOps {
    let ret = LdapAttrModOps(rawValue: m_obj.attrModOp(attrIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func setAttrModOp(attrIndex: Int32, newAttrModOp: LdapAttrModOps) throws -> Void {
    m_obj.setAttrModOp(attrIndex, newAttrModOp.rawValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func attrValue(attrIndex: Int32) throws -> String {
    let ret: String? = m_obj.attrValue(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setAttrValue(attrIndex: Int32, newAttrValue: String) throws -> Void {
    m_obj.setAttrValue(attrIndex, newAttrValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func attrValueB(attrIndex: Int32) throws -> Data {
    let ret: Data? = m_obj.attrValueB(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapData(ret)
  }

  public func setAttrValueB(attrIndex: Int32, newAttrValue: Data) throws -> Void {
    m_obj.setAttrValueB(attrIndex, newAttrValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var authMechanism: LdapAuthMechanisms {
    get {
      return LdapAuthMechanisms(rawValue: m_obj.authMechanism)!
    }
    set {
      m_obj.authMechanism = newValue.rawValue
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

  public var deleteOldRDN: Bool {
    get {
      return m_obj.deleteOldRDN
    }
    set {
      m_obj.deleteOldRDN = newValue
    }
  }

  public var DN: String {
    get {
      let ret: String? = String(m_obj.DN)
      return unwrapNSString(ret)
    }
    set {
      m_obj.DN = newValue as NSString
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

  public var firewallType: LdapFirewallTypes {
    get {
      return LdapFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var LDAPVersion: Int32 {
    get {
      return m_obj.LDAPVersion
    }
    set {
      m_obj.LDAPVersion = newValue
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

  public var messageId: Int32 {
    get {
      return m_obj.messageId
    }
    set {
      m_obj.messageId = newValue
    }
  }

  public var pageSize: Int32 {
    get {
      return m_obj.pageSize
    }
    set {
      m_obj.pageSize = newValue
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

  public var referenceCount: Int32 {
    get {
      return m_obj.referenceCount
    }
  }

  public func referenceURL(referenceIndex: Int32) throws -> String {
    let ret: String? = m_obj.referenceURL(referenceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var resultCode: Int32 {
    get {
      return m_obj.resultCode
    }
  }

  public var resultDescription: String {
    get {
      let ret: String? = String(m_obj.resultDescription)
      return unwrapNSString(ret)
    }
  }

  public var resultDN: String {
    get {
      let ret: String? = String(m_obj.resultDN)
      return unwrapNSString(ret)
    }
  }

  public var searchDerefAliases: LdapSearchDerefAliases {
    get {
      return LdapSearchDerefAliases(rawValue: m_obj.searchDerefAliases)!
    }
    set {
      m_obj.searchDerefAliases = newValue.rawValue
    }
  }

  public var searchReturnValues: Bool {
    get {
      return m_obj.searchReturnValues
    }
    set {
      m_obj.searchReturnValues = newValue
    }
  }

  public var searchScope: LdapSearchScopes {
    get {
      return LdapSearchScopes(rawValue: m_obj.searchScope)!
    }
    set {
      m_obj.searchScope = newValue.rawValue
    }
  }

  public var searchSizeLimit: Int32 {
    get {
      return m_obj.searchSizeLimit
    }
    set {
      m_obj.searchSizeLimit = newValue
    }
  }

  public var searchTimeLimit: Int32 {
    get {
      return m_obj.searchTimeLimit
    }
    set {
      m_obj.searchTimeLimit = newValue
    }
  }

  public var serverName: String {
    get {
      let ret: String? = String(m_obj.serverName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.serverName = newValue as NSString
    }
  }

  public var serverPort: Int32 {
    get {
      return m_obj.serverPort
    }
    set {
      m_obj.serverPort = newValue
    }
  }

  public var sortAttributes: String {
    get {
      let ret: String? = String(m_obj.sortAttributes)
      return unwrapNSString(ret)
    }
    set {
      m_obj.sortAttributes = newValue as NSString
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

  public var SSLCertStoreType: LdapSSLCertStoreTypes {
    get {
      return LdapSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var SSLStartMode: LdapSSLStartModes {
    get {
      return LdapSSLStartModes(rawValue: m_obj.SSLStartMode)!
    }
    set {
      m_obj.SSLStartMode = newValue.rawValue
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

  /* Methods */

  public func abandon(_ messageId: Int32) throws -> Void {
    m_obj.abandon(messageId)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func add() throws -> Void {
    m_obj.add()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func attr(_ attrType: String) throws -> String {
    let ret: String? = m_obj.attr(attrType)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func bind() throws -> Void {
    m_obj.bind()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func changePassword(_ user: String, _ oldPassword: String, _ newPassword: String) throws -> Void {
    m_obj.changePassword(user, oldPassword, newPassword)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func compare() throws -> Void {
    m_obj.compare()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func delete_() throws -> Void {
    m_obj.delete()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func extendedRequest(_ requestName: String, _ requestValue: Data) throws -> Void {
    m_obj.extendedRequest(requestName, requestValue)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listComputers() throws -> Void {
    m_obj.listComputers()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listGroupMembers(_ group: String) throws -> Void {
    m_obj.listGroupMembers(group)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listGroups() throws -> Void {
    m_obj.listGroups()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listUserGroups(_ user: String) throws -> Void {
    m_obj.listUserGroups(user)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func modify() throws -> Void {
    m_obj.modify()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func modifyRDN(_ newRDN: String) throws -> Void {
    m_obj.modifyRDN(newRDN)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func moveToDN(_ newSuperior: String) throws -> Void {
    m_obj.moveToDN(newSuperior)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func search(_ searchFilter: String) throws -> Void {
    m_obj.search(searchFilter)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func unbind() throws -> Void {
    m_obj.unbind()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksLDAPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}