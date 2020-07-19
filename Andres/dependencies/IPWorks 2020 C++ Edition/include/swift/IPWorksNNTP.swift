
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum NntpFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum NntpSSLCertStoreTypes : Int32 {
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
public enum NntpSSLStartModes : Int32 {
  case sslAutomatic = 0
  case sslImplicit = 1
  case sslExplicit = 2
  case sslNone = 3
}


public protocol IPWorksNNTPDelegateSwift {
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onGroupList(_ group: String, _ firstArticle: Int64, _ lastArticle: Int64, _ canPost: Bool)
  func onGroupOverview(_ articleNumber: Int64, _ subject: String, _ from: String, _ articleDate: String, _ messageId: String, _ references: String, _ articleSize: Int64, _ articleLines: Int64, _ otherHeaders: String)
  func onGroupSearch(_ articleNumber: Int64, _ header: String)
  func onHeader(_ field: String, _ value: String)
  func onPITrail(_ direction: Int32, _ message: String)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data, _ EOL: Bool)
}

public enum IPWorksNNTPError : Error {
  case Error(Int32, String)
}

public class IPWorksNNTPSwift : NSObject, IPWorksNNTPDelegate {
  public var m_obj: IPWorksNNTP
  var m_delegate: IPWorksNNTPDelegateSwift?

  override init() {
    self.m_obj = IPWorksNNTP()
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

  public var delegate: IPWorksNNTPDelegateSwift? {
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

  public func onGroupList(_ group: String!, _ firstArticle: Int64, _ lastArticle: Int64, _ canPost: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onGroupList(group, firstArticle, lastArticle, canPost)
    }
  }

  public func onGroupOverview(_ articleNumber: Int64, _ subject: String!, _ from: String!, _ articleDate: String!, _ messageId: String!, _ references: String!, _ articleSize: Int64, _ articleLines: Int64, _ otherHeaders: String!) {
    if (m_delegate != nil) {
      m_delegate!.onGroupOverview(articleNumber, subject, from, articleDate, messageId, references, articleSize, articleLines, otherHeaders)
    }
  }

  public func onGroupSearch(_ articleNumber: Int64, _ header: String!) {
    if (m_delegate != nil) {
      m_delegate!.onGroupSearch(articleNumber, header)
    }
  }

  public func onHeader(_ field: String!, _ value: String!) {
    if (m_delegate != nil) {
      m_delegate!.onHeader(field, value)
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

  public func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data!, _ EOL: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onTransfer(direction, bytesTransferred, percentDone, text, EOL)
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

  public var articleCount: Int64 {
    get {
      return m_obj.articleCount
    }
  }

  public var articleDate: String {
    get {
      let ret: String? = String(m_obj.articleDate)
      return unwrapNSString(ret)
    }
  }

  public var articleFrom: String {
    get {
      let ret: String? = String(m_obj.articleFrom)
      return unwrapNSString(ret)
    }
    set {
      m_obj.articleFrom = newValue as NSString
    }
  }

  public var articleHeaders: String {
    get {
      let ret: String? = String(m_obj.articleHeaders)
      return unwrapNSString(ret)
    }
  }

  public var articleId: String {
    get {
      let ret: String? = String(m_obj.articleId)
      return unwrapNSString(ret)
    }
  }

  public var groupOverviewCount: Int32 {
    get {
      return m_obj.groupOverviewCount
    }
  }

  public func groupOverviewArticleLines(groupOverviewIndex: Int32) throws -> Int64 {
    let ret: Int64? = m_obj.groupOverviewArticleLines(groupOverviewIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func groupOverviewArticleNumber(groupOverviewIndex: Int32) throws -> Int64 {
    let ret: Int64? = m_obj.groupOverviewArticleNumber(groupOverviewIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func groupOverviewArticleSize(groupOverviewIndex: Int32) throws -> Int64 {
    let ret: Int64? = m_obj.groupOverviewArticleSize(groupOverviewIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func groupOverviewDate(groupOverviewIndex: Int32) throws -> String {
    let ret: String? = m_obj.groupOverviewDate(groupOverviewIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func groupOverviewFrom(groupOverviewIndex: Int32) throws -> String {
    let ret: String? = m_obj.groupOverviewFrom(groupOverviewIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func groupOverviewMessageId(groupOverviewIndex: Int32) throws -> String {
    let ret: String? = m_obj.groupOverviewMessageId(groupOverviewIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func groupOverviewOtherHeaders(groupOverviewIndex: Int32) throws -> String {
    let ret: String? = m_obj.groupOverviewOtherHeaders(groupOverviewIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func groupOverviewReferences(groupOverviewIndex: Int32) throws -> String {
    let ret: String? = m_obj.groupOverviewReferences(groupOverviewIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func groupOverviewSubject(groupOverviewIndex: Int32) throws -> String {
    let ret: String? = m_obj.groupOverviewSubject(groupOverviewIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var articleReferences: String {
    get {
      let ret: String? = String(m_obj.articleReferences)
      return unwrapNSString(ret)
    }
    set {
      m_obj.articleReferences = newValue as NSString
    }
  }

  public var articleReplyTo: String {
    get {
      let ret: String? = String(m_obj.articleReplyTo)
      return unwrapNSString(ret)
    }
    set {
      m_obj.articleReplyTo = newValue as NSString
    }
  }

  public var articleSubject: String {
    get {
      let ret: String? = String(m_obj.articleSubject)
      return unwrapNSString(ret)
    }
    set {
      m_obj.articleSubject = newValue as NSString
    }
  }

  public var articleText: String {
    get {
      let ret: String? = String(m_obj.articleText)
      return unwrapNSString(ret)
    }
    set {
      m_obj.articleText = newValue as NSString
    }
  }

  public var attachedFile: String {
    get {
      let ret: String? = String(m_obj.attachedFile)
      return unwrapNSString(ret)
    }
    set {
      m_obj.attachedFile = newValue as NSString
    }
  }

  public var checkDate: String {
    get {
      let ret: String? = String(m_obj.checkDate)
      return unwrapNSString(ret)
    }
    set {
      m_obj.checkDate = newValue as NSString
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

  public var currentArticle: String {
    get {
      let ret: String? = String(m_obj.currentArticle)
      return unwrapNSString(ret)
    }
    set {
      m_obj.currentArticle = newValue as NSString
    }
  }

  public var currentGroup: String {
    get {
      let ret: String? = String(m_obj.currentGroup)
      return unwrapNSString(ret)
    }
    set {
      m_obj.currentGroup = newValue as NSString
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

  public var firewallType: NntpFirewallTypes {
    get {
      return NntpFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var firstArticle: Int64 {
    get {
      return m_obj.firstArticle
    }
  }

  public var groupListCount: Int32 {
    get {
      return m_obj.groupListCount
    }
  }

  public func groupListCanPost(groupListIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.groupListCanPost(groupListIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func groupListFirstArticle(groupListIndex: Int32) throws -> Int64 {
    let ret: Int64? = m_obj.groupListFirstArticle(groupListIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func groupListGroup(groupListIndex: Int32) throws -> String {
    let ret: String? = m_obj.groupListGroup(groupListIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func groupListLastArticle(groupListIndex: Int32) throws -> Int64 {
    let ret: Int64? = m_obj.groupListLastArticle(groupListIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public var idle: Bool {
    get {
      return m_obj.idle
    }
  }

  public var lastArticle: Int64 {
    get {
      return m_obj.lastArticle
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

  public var maxLines: Int64 {
    get {
      return m_obj.maxLines
    }
    set {
      m_obj.maxLines = newValue
    }
  }

  public var newsgroups: String {
    get {
      let ret: String? = String(m_obj.newsgroups)
      return unwrapNSString(ret)
    }
    set {
      m_obj.newsgroups = newValue as NSString
    }
  }

  public var newsPort: Int32 {
    get {
      return m_obj.newsPort
    }
    set {
      m_obj.newsPort = newValue
    }
  }

  public var newsServer: String {
    get {
      let ret: String? = String(m_obj.newsServer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.newsServer = newValue as NSString
    }
  }

  public var organization: String {
    get {
      let ret: String? = String(m_obj.organization)
      return unwrapNSString(ret)
    }
    set {
      m_obj.organization = newValue as NSString
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

  public var overviewRange: String {
    get {
      let ret: String? = String(m_obj.overviewRange)
      return unwrapNSString(ret)
    }
    set {
      m_obj.overviewRange = newValue as NSString
    }
  }

  public var parsedHeaderCount: Int32 {
    get {
      return m_obj.parsedHeaderCount
    }
  }

  public func parsedHeaderField(parsedHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.parsedHeaderField(parsedHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func parsedHeaderValue(parsedHeaderIndex: Int32) throws -> String {
    let ret: String? = m_obj.parsedHeaderValue(parsedHeaderIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
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

  public var searchHeader: String {
    get {
      let ret: String? = String(m_obj.searchHeader)
      return unwrapNSString(ret)
    }
    set {
      m_obj.searchHeader = newValue as NSString
    }
  }

  public var searchPattern: String {
    get {
      let ret: String? = String(m_obj.searchPattern)
      return unwrapNSString(ret)
    }
    set {
      m_obj.searchPattern = newValue as NSString
    }
  }

  public var searchRange: String {
    get {
      let ret: String? = String(m_obj.searchRange)
      return unwrapNSString(ret)
    }
    set {
      m_obj.searchRange = newValue as NSString
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

  public var SSLCertStoreType: NntpSSLCertStoreTypes {
    get {
      return NntpSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var SSLStartMode: NntpSSLStartModes {
    get {
      return NntpSSLStartModes(rawValue: m_obj.SSLStartMode)!
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func connect() throws -> Void {
    m_obj.connect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func disconnect() throws -> Void {
    m_obj.disconnect()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func fetchArticle() throws -> Void {
    m_obj.fetchArticle()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func fetchArticleBody() throws -> Void {
    m_obj.fetchArticleBody()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func fetchArticleHeaders() throws -> Void {
    m_obj.fetchArticleHeaders()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func groupOverview() throws -> Void {
    m_obj.groupOverview()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func groupSearch() throws -> Void {
    m_obj.groupSearch()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listGroups() throws -> Void {
    m_obj.listGroups()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listNewGroups() throws -> Void {
    m_obj.listNewGroups()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func localizeDate(_ dateTime: String) throws -> String {
    let ret: String? = m_obj.localizeDate(dateTime)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func postArticle() throws -> Void {
    m_obj.postArticle()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func resetHeaders() throws -> Void {
    m_obj.resetHeaders()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksNNTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}