
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

import Foundation

public enum JsonXElementTypes : Int32 {
  case etObject = 0
  case etArray = 1
  case etString = 2
  case etNumber = 3
  case etBool = 4
  case etNull = 5
}


public protocol IPWorksJSONDelegateSwift {
  func onCharacters(_ text: String)
  func onEndDocument()
  func onEndElement(_ element: String)
  func onError(_ errorCode: Int32, _ description: String)
  func onIgnorableWhitespace(_ text: String)
  func onJSON(_ text: String)
  func onStartDocument()
  func onStartElement(_ element: String)
}

public enum IPWorksJSONError : Error {
  case Error(Int32, String)
}

public class IPWorksJSONSwift : NSObject, IPWorksJSONDelegate {
  public var m_obj: IPWorksJSON
  var m_delegate: IPWorksJSONDelegateSwift?

  override init() {
    self.m_obj = IPWorksJSON()
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

  public var delegate: IPWorksJSONDelegateSwift? {
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

  public func onEndDocument() {
    if (m_delegate != nil) {
      m_delegate!.onEndDocument()
    }
  }

  public func onEndElement(_ element: String!) {
    if (m_delegate != nil) {
      m_delegate!.onEndElement(element)
    }
  }

  public func onError(_ errorCode: Int32, _ description: String!) {
    if (m_delegate != nil) {
      m_delegate!.onError(errorCode, description)
    }
  }

  public func onIgnorableWhitespace(_ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onIgnorableWhitespace(text)
    }
  }

  public func onJSON(_ text: String!) {
    if (m_delegate != nil) {
      m_delegate!.onJSON(text)
    }
  }

  public func onStartDocument() {
    if (m_delegate != nil) {
      m_delegate!.onStartDocument()
    }
  }

  public func onStartElement(_ element: String!) {
    if (m_delegate != nil) {
      m_delegate!.onStartElement(element)
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func XChildXText(xChildIndex: Int32) throws -> String {
    let ret: String? = m_obj.XChildXText(xChildIndex)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
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

  public var XElementType: JsonXElementTypes {
    get {
      return JsonXElementTypes(rawValue: m_obj.XElementType)!
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
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return unwrapNSString(ret)
  }

  public func endArray() throws -> Void {
    m_obj.endArray()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func endObject() throws -> Void {
    m_obj.endObject()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func flush() throws -> Void {
    m_obj.flush()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func hasXPath(_ XPath: String) throws -> Bool {
    let ret: Bool? = m_obj.hasXPath(XPath)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

  public func insertProperty(_ name: String, _ value: String, _ valueType: Int32, _ position: Int32) throws -> Void {
    m_obj.insertProperty(name, value, valueType, position)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func insertValue(_ value: String, _ valueType: Int32, _ position: Int32) throws -> Void {
    m_obj.insertValue(value, valueType, position)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func loadSchema(_ schema: String) throws -> Void {
    m_obj.loadSchema(schema)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func parse() throws -> Void {
    m_obj.parse()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putName(_ name: String) throws -> Void {
    m_obj.putName(name)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putProperty(_ name: String, _ value: String, _ valueType: Int32) throws -> Void {
    m_obj.putProperty(name, value, valueType)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putRaw(_ text: String) throws -> Void {
    m_obj.putRaw(text)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func putValue(_ value: String, _ valueType: Int32) throws -> Void {
    m_obj.putValue(value, valueType)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func remove() throws -> Void {
    m_obj.remove()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func reset() throws -> Void {
    m_obj.reset()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func save() throws -> Void {
    m_obj.save()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setName(_ name: String) throws -> Void {
    m_obj.setName(name)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func setValue(_ value: String, _ valueType: Int32) throws -> Void {
    m_obj.setValue(value, valueType)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func startArray() throws -> Void {
    m_obj.startArray()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func startObject() throws -> Void {
    m_obj.startObject()
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
  }

  public func tryXPath(_ xpath: String) throws -> Bool {
    let ret: Bool? = m_obj.tryXPath(xpath)
    if (m_obj.lastErrorCode() != 0) { throw IPWorksJSONError.Error(m_obj.lastErrorCode(), m_obj.lastError()) }
    return ret!
  }

}