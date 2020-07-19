
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum CertmgrCertStoreTypes : Int32 {
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


public protocol IPWorksCertMgrDelegateSwift {
  func onCertChain(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ certSerialNumber: String, _ trustStatus: Int32, _ trustInfo: Int32)
  func onCertList(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ certSerialNumber: String, _ hasPrivateKey: Bool)
  func onError(_ errorCode: Int32, _ description: String)
  func onKeyList(_ keyContainer: String, _ keyType: Int32, _ algId: String, _ keyLen: Int32)
  func onLog(_ logLevel: Int32, _ message: String, _ logType: String)
  func onStoreList(_ certStore: String)
}

public enum IPWorksCertMgrError : Error {
  case Error(Int32, String)
}

public class IPWorksCertMgrSwift : NSObject, IPWorksCertMgrDelegate {
  public var m_obj: IPWorksCertMgr
  var m_delegate: IPWorksCertMgrDelegateSwift?

  override init() {
    self.m_obj = IPWorksCertMgr()
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

  public var delegate: IPWorksCertMgrDelegateSwift? {
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

  public func onCertChain(_ certEncoded: Data!, _ certSubject: String!, _ certIssuer: String!, _ certSerialNumber: String!, _ trustStatus: Int32, _ trustInfo: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onCertChain(certEncoded, certSubject, certIssuer, certSerialNumber, trustStatus, trustInfo)
    }
  }

  public func onCertList(_ certEncoded: Data!, _ certSubject: String!, _ certIssuer: String!, _ certSerialNumber: String!, _ hasPrivateKey: Bool) {
    if (m_delegate != nil) {
      m_delegate!.onCertList(certEncoded, certSubject, certIssuer, certSerialNumber, hasPrivateKey)
    }
  }

  public func onError(_ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(errorCode, description)
    }
  }

  public func onKeyList(_ keyContainer: String!, _ keyType: Int32, _ algId: String!, _ keyLen: Int32) {
    if (m_delegate != nil) {
      m_delegate!.onKeyList(keyContainer, keyType, algId, keyLen)
    }
  }

  public func onLog(_ logLevel: Int32, _ message: String!, _ logType: String!) {
    if (m_delegate != nil) {
      m_delegate!.onLog(logLevel, message, logType)
    }
  }

  public func onStoreList(_ certStore: String!) {
    if (m_delegate != nil) {
      m_delegate!.onStoreList(certStore)
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

  public var certEffectiveDate: String {
    get {
      let ret: String? = String(m_obj.certEffectiveDate)
      return unwrapNSString(ret)
    }
  }

  public var certEncoded: String {
    get {
      let ret: String? = String(m_obj.certEncoded)
      return unwrapNSString(ret)
    }
    set {
      m_obj.certEncoded = newValue as NSString
    }
  }

  public var certEncodedB: Data {
    get {
      let ret: Data? = m_obj.certEncodedB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.certEncodedB = newValue as NSData
    }
  }

  public var certExpirationDate: String {
    get {
      let ret: String? = String(m_obj.certExpirationDate)
      return unwrapNSString(ret)
    }
  }

  public var certExtendedKeyUsage: String {
    get {
      let ret: String? = String(m_obj.certExtendedKeyUsage)
      return unwrapNSString(ret)
    }
    set {
      m_obj.certExtendedKeyUsage = newValue as NSString
    }
  }

  public var certFingerprint: String {
    get {
      let ret: String? = String(m_obj.certFingerprint)
      return unwrapNSString(ret)
    }
  }

  public var certIssuer: String {
    get {
      let ret: String? = String(m_obj.certIssuer)
      return unwrapNSString(ret)
    }
  }

  public var certKeyPassword: String {
    get {
      let ret: String? = String(m_obj.certKeyPassword)
      return unwrapNSString(ret)
    }
    set {
      m_obj.certKeyPassword = newValue as NSString
    }
  }

  public var certPrivateKey: String {
    get {
      let ret: String? = String(m_obj.certPrivateKey)
      return unwrapNSString(ret)
    }
  }

  public var certPrivateKeyAvailable: Bool {
    get {
      return m_obj.certPrivateKeyAvailable
    }
  }

  public var certPrivateKeyContainer: String {
    get {
      let ret: String? = String(m_obj.certPrivateKeyContainer)
      return unwrapNSString(ret)
    }
  }

  public var certPublicKey: String {
    get {
      let ret: String? = String(m_obj.certPublicKey)
      return unwrapNSString(ret)
    }
  }

  public var certPublicKeyAlgorithm: String {
    get {
      let ret: String? = String(m_obj.certPublicKeyAlgorithm)
      return unwrapNSString(ret)
    }
    set {
      m_obj.certPublicKeyAlgorithm = newValue as NSString
    }
  }

  public var certPublicKeyLength: Int32 {
    get {
      return m_obj.certPublicKeyLength
    }
  }

  public var certSerialNumber: String {
    get {
      let ret: String? = String(m_obj.certSerialNumber)
      return unwrapNSString(ret)
    }
  }

  public var certSignatureAlgorithm: String {
    get {
      let ret: String? = String(m_obj.certSignatureAlgorithm)
      return unwrapNSString(ret)
    }
  }

  public var certSubject: String {
    get {
      let ret: String? = String(m_obj.certSubject)
      return unwrapNSString(ret)
    }
    set {
      m_obj.certSubject = newValue as NSString
    }
  }

  public var certSubjectAltNames: String {
    get {
      let ret: String? = String(m_obj.certSubjectAltNames)
      return unwrapNSString(ret)
    }
  }

  public var certThumbprintMD5: String {
    get {
      let ret: String? = String(m_obj.certThumbprintMD5)
      return unwrapNSString(ret)
    }
  }

  public var certThumbprintSHA1: String {
    get {
      let ret: String? = String(m_obj.certThumbprintSHA1)
      return unwrapNSString(ret)
    }
  }

  public var certThumbprintSHA256: String {
    get {
      let ret: String? = String(m_obj.certThumbprintSHA256)
      return unwrapNSString(ret)
    }
  }

  public var certUsage: String {
    get {
      let ret: String? = String(m_obj.certUsage)
      return unwrapNSString(ret)
    }
    set {
      m_obj.certUsage = newValue as NSString
    }
  }

  public var certUsageFlags: Int32 {
    get {
      return m_obj.certUsageFlags
    }
    set {
      m_obj.certUsageFlags = newValue
    }
  }

  public var certVersion: String {
    get {
      let ret: String? = String(m_obj.certVersion)
      return unwrapNSString(ret)
    }
  }

  public var certExtensionCount: Int32 {
    get {
      return m_obj.certExtensionCount
    }
    set {
      m_obj.certExtensionCount = newValue
    }
  }

  public func certExtensionCritical(certExtensionIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.certExtensionCritical(certExtensionIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func certExtensionOID(certExtensionIndex: Int32) throws -> String {
    let ret: String? = m_obj.certExtensionOID(certExtensionIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func certExtensionValue(certExtensionIndex: Int32) throws -> String {
    let ret: String? = m_obj.certExtensionValue(certExtensionIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func certExtensionValueB(certExtensionIndex: Int32) throws -> Data {
    let ret: Data? = m_obj.certExtensionValueB(certExtensionIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapData(ret)
  }

  public var certStore: String {
    get {
      let ret: String? = String(m_obj.certStore)
      return unwrapNSString(ret)
    }
    set {
      m_obj.certStore = newValue as NSString
    }
  }

  public var certStoreB: Data {
    get {
      let ret: Data? = m_obj.certStoreB as Data
      return unwrapData(ret)
    }
    set {
      m_obj.certStoreB = newValue as NSData
    }
  }

  public var certStorePassword: String {
    get {
      let ret: String? = String(m_obj.certStorePassword)
      return unwrapNSString(ret)
    }
    set {
      m_obj.certStorePassword = newValue as NSString
    }
  }

  public var certStoreType: CertmgrCertStoreTypes {
    get {
      return CertmgrCertStoreTypes(rawValue: m_obj.certStoreType)!
    }
    set {
      m_obj.certStoreType = newValue.rawValue
    }
  }

  public var exportedCert: String {
    get {
      let ret: String? = String(m_obj.exportedCert)
      return unwrapNSString(ret)
    }
  }

  public var exportedCertB: Data {
    get {
      let ret: Data? = m_obj.exportedCertB as Data
      return unwrapData(ret)
    }

  }

  public var exportFormat: String {
    get {
      let ret: String? = String(m_obj.exportFormat)
      return unwrapNSString(ret)
    }
    set {
      m_obj.exportFormat = newValue as NSString
    }
  }

  public var exportPrivateKey: Bool {
    get {
      return m_obj.exportPrivateKey
    }
    set {
      m_obj.exportPrivateKey = newValue
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func createCertificate(_ certSubject: String, _ serialNumber: Int32) throws -> Void {
    m_obj.createCertificate(certSubject, serialNumber)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func createKey(_ keyName: String) throws -> Void {
    m_obj.createKey(keyName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func deleteCertificate() throws -> Void {
    m_obj.deleteCertificate()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func deleteKey(_ keyName: String) throws -> Void {
    m_obj.deleteKey(keyName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func exportCertificate(_ certFile: String, _ password: String) throws -> Void {
    m_obj.exportCertificate(certFile, password)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func generateCSR(_ certSubject: String, _ keyName: String) throws -> String {
    let ret: String? = m_obj.generateCSR(certSubject, keyName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func importCertificate(_ certFile: String, _ password: String, _ subject: String) throws -> Void {
    m_obj.importCertificate(certFile, password, subject)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func importSignedCSR(_ signedCSR: Data, _ keyName: String) throws -> Void {
    m_obj.importSignedCSR(signedCSR, keyName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func issueCertificate(_ certSubject: String, _ serialNumber: Int32) throws -> Void {
    m_obj.issueCertificate(certSubject, serialNumber)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listCertificateStores() throws -> String {
    let ret: String? = m_obj.listCertificateStores()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func listKeys() throws -> String {
    let ret: String? = m_obj.listKeys()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func listMachineStores() throws -> String {
    let ret: String? = m_obj.listMachineStores()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func listStoreCertificates() throws -> String {
    let ret: String? = m_obj.listStoreCertificates()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func readCertificate(_ fileName: String) throws -> Void {
    m_obj.readCertificate(fileName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func readCSR(_ CSR: String) throws -> String {
    let ret: String? = m_obj.readCSR(CSR)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func saveCertificate(_ fileName: String) throws -> Void {
    m_obj.saveCertificate(fileName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func showCertificateChain() throws -> String {
    let ret: String? = m_obj.showCertificateChain()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func signCSR(_ CSR: Data, _ serialNumber: Int32) throws -> String {
    let ret: String? = m_obj.signCSR(CSR, serialNumber)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksCertMgrError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

}