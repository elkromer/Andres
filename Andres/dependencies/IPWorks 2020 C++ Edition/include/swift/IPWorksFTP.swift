
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum FtpFirewallTypes : Int32 {
  case fwNone = 0
  case fwTunnel = 1
  case fwSOCKS4 = 2
  case fwSOCKS5 = 3
}
public enum FtpSSLCertStoreTypes : Int32 {
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
public enum FtpSSLStartModes : Int32 {
  case sslAutomatic = 0
  case sslImplicit = 1
  case sslExplicit = 2
  case sslNone = 3
}
public enum FtpTransferModes : Int32 {
  case tmDefault = 0
  case tmASCII = 1
  case tmBinary = 2
}


public protocol IPWorksFTPDelegateSwift {
  func onConnectionStatus(_ connectionEvent: String, _ statusCode: Int32, _ description: String)
  func onDirList(_ dirEntry: String, _ fileName: String, _ isDir: Bool, _ fileSize: Int64, _ fileTime: String)
  func onEndTransfer(_ direction: Int32)
  func onError(_ errorCode: Int32, _ description: String)
  func onPITrail(_ direction: Int32, _ message: String)
  func onSSLServerAuthentication(_ certEncoded: Data, _ certSubject: String, _ certIssuer: String, _ status: String, _ accept: inout Int32)
  func onSSLStatus(_ message: String)
  func onStartTransfer(_ direction: Int32)
  func onTransfer(_ direction: Int32, _ bytesTransferred: Int64, _ percentDone: Int32, _ text: Data)
}

public enum IPWorksFTPError : Error {
  case Error(Int32, String)
}

public class IPWorksFTPSwift : NSObject, IPWorksFTPDelegate {
  public var m_obj: IPWorksFTP
  var m_delegate: IPWorksFTPDelegateSwift?

  override init() {
    self.m_obj = IPWorksFTP()
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

  public var delegate: IPWorksFTPDelegateSwift? {
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

  public func onDirList(_ dirEntry: String!, _ fileName: String!, _ isDir: Bool, _ fileSize: Int64, _ fileTime: String!) {
    if (m_delegate != nil) {
      m_delegate!.onDirList(dirEntry, fileName, isDir, fileSize, fileTime)
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

  public var account: String {
    get {
      let ret: String? = String(m_obj.account)
      return unwrapNSString(ret)
    }
    set {
      m_obj.account = newValue as NSString
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

  public var dirListCount: Int32 {
    get {
      return m_obj.dirListCount
    }
  }

  public func dirListEntry(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.dirListEntry(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func dirListFileName(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.dirListFileName(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func dirListFileSize(entryIndex: Int32) throws -> Int64 {
    let ret: Int64? = m_obj.dirListFileSize(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func dirListFileTime(entryIndex: Int32) throws -> String {
    let ret: String? = m_obj.dirListFileTime(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func dirListIsDir(entryIndex: Int32) throws -> Bool {
    let ret: Bool? = m_obj.dirListIsDir(entryIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public var fileExists: Bool {
    get {
      return m_obj.fileExists
    }
  }

  public var fileSize: Int64 {
    get {
      return m_obj.fileSize
    }
  }

  public var fileTime: String {
    get {
      let ret: String? = String(m_obj.fileTime)
      return unwrapNSString(ret)
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

  public var firewallType: FtpFirewallTypes {
    get {
      return FtpFirewallTypes(rawValue: m_obj.firewallType)!
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

  public var overwrite: Bool {
    get {
      return m_obj.overwrite
    }
    set {
      m_obj.overwrite = newValue
    }
  }

  public var passive: Bool {
    get {
      return m_obj.passive
    }
    set {
      m_obj.passive = newValue
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

  public var remoteFile: String {
    get {
      let ret: String? = String(m_obj.remoteFile)
      return unwrapNSString(ret)
    }
    set {
      m_obj.remoteFile = newValue as NSString
    }
  }

  public var remoteHost: String {
    get {
      let ret: String? = String(m_obj.remoteHost)
      return unwrapNSString(ret)
    }
    set {
      m_obj.remoteHost = newValue as NSString
    }
  }

  public var remotePath: String {
    get {
      let ret: String? = String(m_obj.remotePath)
      return unwrapNSString(ret)
    }
    set {
      m_obj.remotePath = newValue as NSString
    }
  }

  public var remotePort: Int32 {
    get {
      return m_obj.remotePort
    }
    set {
      m_obj.remotePort = newValue
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

  public var SSLCertStoreType: FtpSSLCertStoreTypes {
    get {
      return FtpSSLCertStoreTypes(rawValue: m_obj.SSLCertStoreType)!
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

  public var SSLStartMode: FtpSSLStartModes {
    get {
      return FtpSSLStartModes(rawValue: m_obj.SSLStartMode)!
    }
    set {
      m_obj.SSLStartMode = newValue.rawValue
    }
  }

  public var startByte: String {
    get {
      let ret: String? = String(m_obj.startByte)
      return unwrapNSString(ret)
    }
    set {
      m_obj.startByte = newValue as NSString
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

  public var transferMode: FtpTransferModes {
    get {
      return FtpTransferModes(rawValue: m_obj.transferMode)!
    }
    set {
      m_obj.transferMode = newValue.rawValue
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

  public func abort() throws -> Void {
    m_obj.abort()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func append() throws -> Void {
    m_obj.append()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func deleteFile(_ fileName: String) throws -> Void {
    m_obj.deleteFile(fileName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func download() throws -> Void {
    m_obj.download()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func interrupt() throws -> Void {
    m_obj.interrupt()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listDirectory() throws -> Void {
    m_obj.listDirectory()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func listDirectoryLong() throws -> Void {
    m_obj.listDirectoryLong()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func logoff() throws -> Void {
    m_obj.logoff()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func logon() throws -> Void {
    m_obj.logon()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func makeDirectory(_ newDir: String) throws -> Void {
    m_obj.makeDirectory(newDir)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func removeDirectory(_ dirName: String) throws -> Void {
    m_obj.removeDirectory(dirName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func renameFile(_ newName: String) throws -> Void {
    m_obj.renameFile(newName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func storeUnique() throws -> Void {
    m_obj.storeUnique()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func upload() throws -> Void {
    m_obj.upload()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksFTPError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

}