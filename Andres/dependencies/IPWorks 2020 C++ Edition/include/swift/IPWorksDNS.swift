
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum DnsProtocols : Int32 {
  case ptUDP = 0
  case ptTCP = 1
  case ptTLS = 2
  case ptHTTPS = 3
}
public enum DnsQueryTypes : Int32 {
  case qtAddress = 1
  case qtNS = 2
  case qtMD = 3
  case qtMF = 4
  case qtCName = 5
  case qtSOA = 6
  case qtMailBox = 7
  case qtMailGroup = 8
  case qtMR = 9
  case qtNULL = 10
  case qtWKS = 11
  case qtPointer = 12
  case qtHostInfo = 13
  case qtMailInfo = 14
  case qtMX = 15
  case qtText = 16
  case qtRP = 17
  case qtAFSDB = 18
  case qtX25 = 19
  case qtISDN = 20
  case qtRT = 21
  case qtAAAA = 28
  case qtSRV = 33
  case qtNAPTR = 35
  case qtCERT = 37
  case qtRevLookup = 100
}
public enum DnsRecordTypes : Int32 {
  case rtAddress = 1
  case rtNS = 2
  case rtMD = 3
  case rtMF = 4
  case rtCName = 5
  case rtSOA = 6
  case rtMailBox = 7
  case rtMailGroup = 8
  case rtMR = 9
  case rtNULL = 10
  case rtWKS = 11
  case rtPointer = 12
  case rtHostInfo = 13
  case rtMailInfo = 14
  case rtMX = 15
  case rtText = 16
  case rtRP = 17
  case rtAFSDB = 18
  case rtX25 = 19
  case rtISDN = 20
  case rtRT = 21
  case rtAAAA = 28
  case rtSRV = 33
  case rtNAPTR = 35
}
public enum DnsRecordSources : Int32 {
  case rsAnswerSection = 0
  case rsNameServerSection = 1
  case rsAdditionalRecordsSection = 2
}


public protocol IPWorksDNSDelegateSwift {
  func onError(_ errorCode: Int32, _ description: String)
  func onResponse(_ requestId: Int32, _ domain: String, _ statusCode: Int32, _ description: String, _ authoritative: Bool)
  func onSSLServerAuthentication(_ remoteAddress: String, _ remotePort: Int32, _ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ remoteAddress: String, _ remotePort: Int32, _ message: String)
}

public enum IPWorksDNSError : Error {
  case Error(Int32, String)
}

public class IPWorksDNSSwift : NSObject, IPWorksDNSDelegate {
  public var m_obj: IPWorksDNS
  var m_delegate: IPWorksDNSDelegateSwift?

  override init() {
    self.m_obj = IPWorksDNS()
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

  public var delegate: IPWorksDNSDelegateSwift? {
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

  public func onError(_ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(errorCode, description)
    }
  }

  public func onResponse(_ requestId: Int32, _ domain: String!, _ statusCode: Int32, _ description: String!, _ authoritative: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onResponse(requestId, domain, statusCode, description, authoritative)
    }
  }

  public func onSSLServerAuthentication(_ remoteAddress: String!, _ remotePort: Int32, _ certEncoded: Data!, _ certSubject: String!, _ certIssuer: String!, _ status: String!, _ accept: UnsafeMutablePointer<Int32>) {
    if (m_delegate != nil) {
      m_delegate!.onSSLServerAuthentication(remoteAddress, remotePort, certEncoded, certSubject, certIssuer, status, &accept.pointee)
    }
  }

  public func onSSLStatus(_ remoteAddress: String!, _ remotePort: Int32, _ message: String!) {
    if (m_delegate != nil) {
      m_delegate!.onSSLStatus(remoteAddress, remotePort, message)
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

  public var DNSPort: Int32 {
    get {
      return m_obj.DNSPort
    }
    set {
      m_obj.DNSPort = newValue
    }
  }

  public var DNSServer: String {
    get {
      let ret: String? = String(m_obj.DNSServer)
      return unwrapNSString(ret)
    }
    set {
      m_obj.DNSServer = newValue as NSString
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

  public var protocol_: DnsProtocols {
    get {
      return DnsProtocols(rawValue: m_obj.protocol_())!
    }
    set {
      m_obj.setProtocol_(newValue.rawValue)
    }
  }

  public var queryType: DnsQueryTypes {
    get {
      return DnsQueryTypes(rawValue: m_obj.queryType)!
    }
    set {
      m_obj.queryType = newValue.rawValue
    }
  }

  public var recordCount: Int32 {
    get {
      return m_obj.recordCount
    }
  }

  public func recordDomain(recordIndex: Int32) throws -> String {
    let ret: String? = m_obj.recordDomain(recordIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func recordFieldCount(recordIndex: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.recordFieldCount(recordIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func recordFieldIndex(recordIndex: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.recordFieldIndex(recordIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func setRecordFieldIndex(recordIndex: Int32, newRecordFieldIndex: Int32) throws -> Void {
    m_obj.setRecordFieldIndex(recordIndex, newRecordFieldIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func recordFieldName(recordIndex: Int32) throws -> String {
    let ret: String? = m_obj.recordFieldName(recordIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func recordFieldValue(recordIndex: Int32) throws -> String {
    let ret: String? = m_obj.recordFieldValue(recordIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func recordFieldValueB(recordIndex: Int32) throws -> Data {
    let ret: Data? = m_obj.recordFieldValueB(recordIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapData(ret)
  }

  public func recordData(recordIndex: Int32) throws -> String {
    let ret: String? = m_obj.recordData(recordIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func recordDataB(recordIndex: Int32) throws -> Data {
    let ret: Data? = m_obj.recordDataB(recordIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapData(ret)
  }

  public func recordType(recordIndex: Int32) throws -> DnsRecordTypes {
    let ret = DnsRecordTypes(rawValue: m_obj.recordType(recordIndex))!
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret
  }

  public func recordTypeName(recordIndex: Int32) throws -> String {
    let ret: String? = m_obj.recordTypeName(recordIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func recordTTL(recordIndex: Int32) throws -> Int32 {
    let ret: Int32? = m_obj.recordTTL(recordIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public var recordSource: DnsRecordSources {
    get {
      return DnsRecordSources(rawValue: m_obj.recordSource)!
    }
    set {
      m_obj.recordSource = newValue.rawValue
    }
  }

  public var recursive: Bool {
    get {
      return m_obj.recursive
    }
    set {
      m_obj.recursive = newValue
    }
  }

  public var requestId: Int32 {
    get {
      return m_obj.requestId
    }
    set {
      m_obj.requestId = newValue
    }
  }

  public var status: String {
    get {
      let ret: String? = String(m_obj.status)
      return unwrapNSString(ret)
    }
  }

  public var statusCode: Int32 {
    get {
      return m_obj.statusCode
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

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getFieldValue(_ recordIndex: Int32, _ fieldName: String) throws -> String {
    let ret: String? = m_obj.getFieldValue(recordIndex, fieldName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func query(_ domain: String) throws -> Void {
    m_obj.query(domain)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksDNSError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}