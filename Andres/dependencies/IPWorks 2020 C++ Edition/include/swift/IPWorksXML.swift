
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation



public protocol IPWorksXMLDelegateSwift {
  func onCharacters(_ text: String)
  func onComment(_ text: String)
  func onEndElement(_ namespace: String, _ element: String, _ QName: String, _ isEmpty: Bool)
  func onEndPrefixMapping(_ prefix: String)
  func onError(_ errorCode: Int32, _ description: String)
  func onEvalEntity(_ entity: String, _ value: inout NSString?)
  func onIgnorableWhitespace(_ text: String)
  func onMeta(_ text: String)
  func onPI(_ text: String)
  func onSpecialSection(_ sectionId: String, _ text: String)
  func onStartElement(_ namespace: String, _ element: String, _ QName: String, _ isEmpty: Bool)
  func onStartPrefixMapping(_ prefix: String, _ URI: String)
  func onXML(_ text: String)
}

public enum IPWorksXMLError : Error {
  case Error(Int32, String)
}

public class IPWorksXMLSwift : NSObject, IPWorksXMLDelegate {
  public var m_obj: IPWorksXML
  var m_delegate: IPWorksXMLDelegateSwift?

  override init() {
    self.m_obj = IPWorksXML()
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

  public var delegate: IPWorksXMLDelegateSwift? {
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

  public func onIgnorableWhitespace(_ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onIgnorableWhitespace(text)
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

  public func onSpecialSection(_ sectionId: String!, _ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onSpecialSection(sectionId, text)
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

  public func onXML(_ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onXML(text)
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

  public var buildDOM: Bool {
    get {
      return m_obj.buildDOM
    }
    set {
      m_obj.buildDOM = newValue
    }
  }

  public var inputData: String {
    get {
      let ret: String? = String(m_obj.inputData)
      return unwrapNSString(ret)
    }
    set {
      m_obj.inputData = newValue as NSString
    }
  }

  public var inputFile: String {
    get {
      let ret: String? = String(m_obj.inputFile)
      return unwrapNSString(ret)
    }
    set {
      m_obj.inputFile = newValue as NSString
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setNamespacePrefix(namespaceIndex: Int32, newNamespacePrefix: String) throws -> Void {
    m_obj.setNamespacePrefix(namespaceIndex, newNamespacePrefix)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func namespaceURI(namespaceIndex: Int32) throws -> String {
    let ret: String? = m_obj.namespaceURI(namespaceIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setNamespaceURI(namespaceIndex: Int32, newNamespaceURI: String) throws -> Void {
    m_obj.setNamespaceURI(namespaceIndex, newNamespaceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var outputData: String {
    get {
      let ret: String? = String(m_obj.outputData)
      return unwrapNSString(ret)
    }
    set {
      m_obj.outputData = newValue as NSString
    }
  }

  public var outputFile: String {
    get {
      let ret: String? = String(m_obj.outputFile)
      return unwrapNSString(ret)
    }
    set {
      m_obj.outputFile = newValue as NSString
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
    set {
      m_obj.attrCount = newValue
    }
  }

  public func attrName(attrIndex: Int32) throws -> String {
    let ret: String? = m_obj.attrName(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func attrNamespace(attrIndex: Int32) throws -> String {
    let ret: String? = m_obj.attrNamespace(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func attrPrefix(attrIndex: Int32) throws -> String {
    let ret: String? = m_obj.attrPrefix(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func attrValue(attrIndex: Int32) throws -> String {
    let ret: String? = m_obj.attrValue(attrIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var XChildCount: Int32 {
    get {
      return m_obj.XChildCount
    }
    set {
      m_obj.XChildCount = newValue
    }
  }

  public func XChildName(xChildIndex: Int32) throws -> String {
    let ret: String? = m_obj.XChildName(xChildIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func XChildNamespace(xChildIndex: Int32) throws -> String {
    let ret: String? = m_obj.XChildNamespace(xChildIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func XChildPrefix(xChildIndex: Int32) throws -> String {
    let ret: String? = m_obj.XChildPrefix(xChildIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func XChildXText(xChildIndex: Int32) throws -> String {
    let ret: String? = m_obj.XChildXText(xChildIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public var XCommentCount: Int32 {
    get {
      return m_obj.XCommentCount
    }
    set {
      m_obj.XCommentCount = newValue
    }
  }

  public func XCommentText(xCommentIndex: Int32) throws -> String {
    let ret: String? = m_obj.XCommentText(xCommentIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func setXCommentText(xCommentIndex: Int32, newXCommentText: String) throws -> Void {
    m_obj.setXCommentText(xCommentIndex, newXCommentText)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public var XElement: String {
    get {
      let ret: String? = String(m_obj.XElement)
      return unwrapNSString(ret)
    }
    set {
      m_obj.XElement = newValue as NSString
    }
  }

  public var XMLDeclarationEncoding: String {
    get {
      let ret: String? = String(m_obj.XMLDeclarationEncoding)
      return unwrapNSString(ret)
    }
    set {
      m_obj.XMLDeclarationEncoding = newValue as NSString
    }
  }

  public var XMLDeclarationStandalone: Bool {
    get {
      return m_obj.XMLDeclarationStandalone
    }
    set {
      m_obj.XMLDeclarationStandalone = newValue
    }
  }

  public var XMLDeclarationVersion: String {
    get {
      let ret: String? = String(m_obj.XMLDeclarationVersion)
      return unwrapNSString(ret)
    }
    set {
      m_obj.XMLDeclarationVersion = newValue as NSString
    }
  }

  public var XNamespace: String {
    get {
      let ret: String? = String(m_obj.XNamespace)
      return unwrapNSString(ret)
    }
    set {
      m_obj.XNamespace = newValue as NSString
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
    set {
      m_obj.XPrefix = newValue as NSString
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
    set {
      m_obj.XText = newValue as NSString
    }
  }

  /* Methods */

  public func config(_ configurationString: String) throws -> String {
    let ret: String? = m_obj.config(configurationString)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func endElement() throws -> Void {
    m_obj.endElement()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func flush() throws -> Void {
    m_obj.flush()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func getAttr(_ attrName: String) throws -> String {
    let ret: String? = m_obj.getAttr(attrName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func hasXPath(_ XPath: String) throws -> Bool {
    let ret: Bool? = m_obj.hasXPath(XPath)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func loadDOM(_ fileName: String) throws -> Void {
    m_obj.loadDOM(fileName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func loadSchema(_ schema: String) throws -> Void {
    m_obj.loadSchema(schema)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func parse() throws -> Void {
    m_obj.parse()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putAttr(_ name: String, _ namespaceURI: String, _ value: String) throws -> Void {
    m_obj.putAttr(name, namespaceURI, value)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putCData(_ text: String) throws -> Void {
    m_obj.putCData(text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putComment(_ text: String) throws -> Void {
    m_obj.putComment(text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putElement(_ name: String, _ namespaceURI: String, _ value: String) throws -> Void {
    m_obj.putElement(name, namespaceURI, value)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putRaw(_ text: String) throws -> Void {
    m_obj.putRaw(text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putString(_ text: String) throws -> Void {
    m_obj.putString(text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func removeAttr(_ attrName: String) throws -> Void {
    m_obj.removeAttr(attrName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func removeChildren() throws -> Void {
    m_obj.removeChildren()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func removeElement() throws -> Void {
    m_obj.removeElement()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func save() throws -> Void {
    m_obj.save()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func saveDOM(_ fileName: String) throws -> Void {
    m_obj.saveDOM(fileName)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func startElement(_ name: String, _ namespaceURI: String) throws -> Void {
    m_obj.startElement(name, namespaceURI)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func tryXPath(_ xpath: String) throws -> Bool {
    let ret: Bool? = m_obj.tryXPath(xpath)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksXMLError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

}