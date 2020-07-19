
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation



public protocol IPWorksIPInfoDelegateSwift {
  func onDNSCacheEntry(_ recordName: String, _ recordType: Int32, _ timeToLive: Int32, _ dataLength: Int32, _ section: String, _ recordValue: String, _ recordInfo: String)
  func onError(_ errorCode: Int32, _ description: String)
  func onRequestComplete(_ requestId: Int32, _ statusCode: Int32, _ description: String)
}

public enum IPWorksIPInfoError : Error {
  case Error(Int32, String)
}

public class IPWorksIPInfoSwift : NSObject, IPWorksIPInfoDelegate {
  public var m_obj: IPWorksIPInfo
  var m_delegate: IPWorksIPInfoDelegateSwift?

  override init() {
    self.m_obj = IPWorksIPInfo()
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

  public var delegate: IPWorksIPInfoDelegateSwift? {
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

  public func onDNSCacheEntry(_ recordName: String!, _ recordType: Int32, _ timeToLive: Int32, _ dataLength: Int32, _ section: String!, _ recordValue: String!, _ recordInfo: String!) {
    if (m_delegate != nil) {
      m_delegate!.onDNSCacheEntry(recordName, recordType, timeToLive, dataLength, section, recordValue, recordInfo)
    }
  }

  public func onError(_ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(errorCode, description)
    }
  }

  public func onRequestComplete(_ requestId: Int32, _ statusCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onRequestComplete(requestId, statusCode, description)
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

  public var adapterBroadcastAddress: String {
    get {
      let ret: String? = String(m_obj.adapterBroadcastAddress)
      return unwrapNSString(ret)
    }
  }

  public var adapterCount: Int32 {
    get {
      return m_obj.adapterCount
    }
  }

  public var adapterDescription: String {
    get {
      let ret: String? = String(m_obj.adapterDescription)
      return unwrapNSString(ret)
    }
  }

  public var adapterDeviceIndex: Int32 {
    get {
      return m_obj.adapterDeviceIndex
    }
  }

  public var adapterDHCPEnabled: Bool {
    get {
      return m_obj.adapterDHCPEnabled
    }
  }

  public var adapterDHCPServer: String {
    get {
      let ret: String? = String(m_obj.adapterDHCPServer)
      return unwrapNSString(ret)
    }
  }

  public var adapterDNSServers: String {
    get {
      let ret: String? = String(m_obj.adapterDNSServers)
      return unwrapNSString(ret)
    }
  }

  public var adapterGateway: String {
    get {
      let ret: String? = String(m_obj.adapterGateway)
      return unwrapNSString(ret)
    }
  }

  public var adapterIndex: Int32 {
    get {
      return m_obj.adapterIndex
    }
    set {
      m_obj.adapterIndex = newValue
    }
  }

  public var adapterIPAddress: String {
    get {
      let ret: String? = String(m_obj.adapterIPAddress)
      return unwrapNSString(ret)
    }
  }

  public var adapterIPv6Address: String {
    get {
      let ret: String? = String(m_obj.adapterIPv6Address)
      return unwrapNSString(ret)
    }
  }

  public var adapterIPv6LinkLocalAddress: String {
    get {
      let ret: String? = String(m_obj.adapterIPv6LinkLocalAddress)
      return unwrapNSString(ret)
    }
  }

  public var adapterLeaseExpires: String {
    get {
      let ret: String? = String(m_obj.adapterLeaseExpires)
      return unwrapNSString(ret)
    }
  }

  public var adapterLeaseObtained: String {
    get {
      let ret: String? = String(m_obj.adapterLeaseObtained)
      return unwrapNSString(ret)
    }
  }

  public var adapterName: String {
    get {
      let ret: String? = String(m_obj.adapterName)
      return unwrapNSString(ret)
    }
  }

  public var adapterOtherIPAddresses: String {
    get {
      let ret: String? = String(m_obj.adapterOtherIPAddresses)
      return unwrapNSString(ret)
    }
  }

  public var adapterPhysicalAddress: String {
    get {
      let ret: String? = String(m_obj.adapterPhysicalAddress)
      return unwrapNSString(ret)
    }
  }

  public var adapterPrimaryWINSServer: String {
    get {
      let ret: String? = String(m_obj.adapterPrimaryWINSServer)
      return unwrapNSString(ret)
    }
  }

  public var adapterSecondaryWINSServer: String {
    get {
      let ret: String? = String(m_obj.adapterSecondaryWINSServer)
      return unwrapNSString(ret)
    }
  }

  public var adapterStatus: String {
    get {
      let ret: String? = String(m_obj.adapterStatus)
      return unwrapNSString(ret)
    }
  }

  public var adapterSubnetMask: String {
    get {
      let ret: String? = String(m_obj.adapterSubnetMask)
      return unwrapNSString(ret)
    }
  }

  public var adapterType: String {
    get {
      let ret: String? = String(m_obj.adapterType)
      return unwrapNSString(ret)
    }
  }

  public var adapterUsesWINS: Bool {
    get {
      return m_obj.adapterUsesWINS
    }
  }

  public var adapterZoneId: Int32 {
    get {
      return m_obj.adapterZoneId
    }
  }

  public var ARPProxy: Bool {
    get {
      return m_obj.ARPProxy
    }
  }

  public var DHCPScope: String {
    get {
      let ret: String? = String(m_obj.DHCPScope)
      return unwrapNSString(ret)
    }
  }

  public var DNSEnabled: Bool {
    get {
      return m_obj.DNSEnabled
    }
  }

  public var DNSServer: String {
    get {
      let ret: String? = String(m_obj.DNSServer)
      return unwrapNSString(ret)
    }
  }

  public var domainName: String {
    get {
      let ret: String? = String(m_obj.domainName)
      return unwrapNSString(ret)
    }
  }

  public var hostAddress: String {
    get {
      let ret: String? = String(m_obj.hostAddress)
      return unwrapNSString(ret)
    }
    set {
      m_obj.hostAddress = newValue as NSString
    }
  }

  public var hostAliases: String {
    get {
      let ret: String? = String(m_obj.hostAliases)
      return unwrapNSString(ret)
    }
  }

  public var hostName: String {
    get {
      let ret: String? = String(m_obj.hostName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.hostName = newValue as NSString
    }
  }

  public var localHost: String {
    get {
      let ret: String? = String(m_obj.localHost)
      return unwrapNSString(ret)
    }
  }

  public var nodeType: String {
    get {
      let ret: String? = String(m_obj.nodeType)
      return unwrapNSString(ret)
    }
  }

  public var otherAddresses: String {
    get {
      let ret: String? = String(m_obj.otherAddresses)
      return unwrapNSString(ret)
    }
  }

  public var otherDNSServers: String {
    get {
      let ret: String? = String(m_obj.otherDNSServers)
      return unwrapNSString(ret)
    }
  }

  public var pendingRequests: Int32 {
    get {
      return m_obj.pendingRequests
    }
    set {
      m_obj.pendingRequests = newValue
    }
  }

  public var requestId: Int32 {
    get {
      return m_obj.requestId
    }
  }

  public var routingEnabled: Bool {
    get {
      return m_obj.routingEnabled
    }
  }

  public var serviceAliases: String {
    get {
      let ret: String? = String(m_obj.serviceAliases)
      return unwrapNSString(ret)
    }
  }

  public var serviceName: String {
    get {
      let ret: String? = String(m_obj.serviceName)
      return unwrapNSString(ret)
    }
    set {
      m_obj.serviceName = newValue as NSString
    }
  }

  public var servicePort: Int32 {
    get {
      return m_obj.servicePort
    }
    set {
      m_obj.servicePort = newValue
    }
  }

  public var serviceProtocol: String {
    get {
      let ret: String? = String(m_obj.serviceProtocol)
      return unwrapNSString(ret)
    }
    set {
      m_obj.serviceProtocol = newValue as NSString
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPInfoError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func DHCPRelease() throws -> Void {
    m_obj.DHCPRelease()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPInfoError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func DHCPRenew() throws -> Void {
    m_obj.DHCPRenew()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPInfoError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func displayDNSCache() throws -> String {
    let ret: String? = m_obj.displayDNSCache()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPInfoError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func doEvents() throws -> Void {
    m_obj.doEvents()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPInfoError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func flushDNSCache() throws -> Bool {
    let ret: Bool? = m_obj.flushDNSCache()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPInfoError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func getMAC(_ IPAddress: String) throws -> String {
    let ret: String? = m_obj.getMAC(IPAddress)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPInfoError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPInfoError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func resolveAddress(_ hostAddress: String) throws -> String {
    let ret: String? = m_obj.resolveAddress(hostAddress)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPInfoError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func resolveName(_ hostName: String) throws -> String {
    let ret: String? = m_obj.resolveName(hostName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksIPInfoError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

}