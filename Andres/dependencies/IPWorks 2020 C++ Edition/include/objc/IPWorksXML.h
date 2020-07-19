
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksXMLDelegate <NSObject>
@optional
- (void)onCharacters:(NSString*)text NS_SWIFT_NAME(onCharacters(_:));
- (void)onComment:(NSString*)text NS_SWIFT_NAME(onComment(_:));
- (void)onEndElement:(NSString*)namespace :(NSString*)element :(NSString*)QName :(BOOL)isEmpty NS_SWIFT_NAME(onEndElement(_:_:_:_:));
- (void)onEndPrefixMapping:(NSString*)prefix NS_SWIFT_NAME(onEndPrefixMapping(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onEvalEntity:(NSString*)entity :(NSString**)value NS_SWIFT_NAME(onEvalEntity(_:_:));
- (void)onIgnorableWhitespace:(NSString*)text NS_SWIFT_NAME(onIgnorableWhitespace(_:));
- (void)onMeta:(NSString*)text NS_SWIFT_NAME(onMeta(_:));
- (void)onPI:(NSString*)text NS_SWIFT_NAME(onPI(_:));
- (void)onSpecialSection:(NSString*)sectionId :(NSString*)text NS_SWIFT_NAME(onSpecialSection(_:_:));
- (void)onStartElement:(NSString*)namespace :(NSString*)element :(NSString*)QName :(BOOL)isEmpty NS_SWIFT_NAME(onStartElement(_:_:_:_:));
- (void)onStartPrefixMapping:(NSString*)prefix :(NSString*)URI NS_SWIFT_NAME(onStartPrefixMapping(_:_:));
- (void)onXML:(NSString*)text NS_SWIFT_NAME(onXML(_:));
@end

@interface IPWorksXML : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksXMLDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasCharacters;
  BOOL m_delegateHasComment;
  BOOL m_delegateHasEndElement;
  BOOL m_delegateHasEndPrefixMapping;
  BOOL m_delegateHasError;
  BOOL m_delegateHasEvalEntity;
  BOOL m_delegateHasIgnorableWhitespace;
  BOOL m_delegateHasMeta;
  BOOL m_delegateHasPI;
  BOOL m_delegateHasSpecialSection;
  BOOL m_delegateHasStartElement;
  BOOL m_delegateHasStartPrefixMapping;
  BOOL m_delegateHasXML;
}

+ (IPWorksXML*)xml;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksXMLDelegate> delegate;
- (id <IPWorksXMLDelegate>)delegate;
- (void) setDelegate:(id <IPWorksXMLDelegate>)anObject;

  /* Events */

- (void)onCharacters:(NSString*)text NS_SWIFT_NAME(onCharacters(_:));
- (void)onComment:(NSString*)text NS_SWIFT_NAME(onComment(_:));
- (void)onEndElement:(NSString*)namespace :(NSString*)element :(NSString*)QName :(BOOL)isEmpty NS_SWIFT_NAME(onEndElement(_:_:_:_:));
- (void)onEndPrefixMapping:(NSString*)prefix NS_SWIFT_NAME(onEndPrefixMapping(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onEvalEntity:(NSString*)entity :(NSString**)value NS_SWIFT_NAME(onEvalEntity(_:_:));
- (void)onIgnorableWhitespace:(NSString*)text NS_SWIFT_NAME(onIgnorableWhitespace(_:));
- (void)onMeta:(NSString*)text NS_SWIFT_NAME(onMeta(_:));
- (void)onPI:(NSString*)text NS_SWIFT_NAME(onPI(_:));
- (void)onSpecialSection:(NSString*)sectionId :(NSString*)text NS_SWIFT_NAME(onSpecialSection(_:_:));
- (void)onStartElement:(NSString*)namespace :(NSString*)element :(NSString*)QName :(BOOL)isEmpty NS_SWIFT_NAME(onStartElement(_:_:_:_:));
- (void)onStartPrefixMapping:(NSString*)prefix :(NSString*)URI NS_SWIFT_NAME(onStartPrefixMapping(_:_:));
- (void)onXML:(NSString*)text NS_SWIFT_NAME(onXML(_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=buildDOM,setter=setBuildDOM:) BOOL buildDOM NS_SWIFT_NAME(buildDOM);
- (BOOL)buildDOM NS_SWIFT_NAME(buildDOM());
- (void)setBuildDOM:(BOOL)newBuildDOM NS_SWIFT_NAME(setBuildDOM(_:));

@property (nonatomic,readwrite,assign,getter=inputData,setter=setInputData:) NSString* inputData NS_SWIFT_NAME(inputData);
- (NSString*)inputData NS_SWIFT_NAME(inputData());
- (void)setInputData:(NSString*)newInputData NS_SWIFT_NAME(setInputData(_:));

@property (nonatomic,readwrite,assign,getter=inputFile,setter=setInputFile:) NSString* inputFile NS_SWIFT_NAME(inputFile);
- (NSString*)inputFile NS_SWIFT_NAME(inputFile());
- (void)setInputFile:(NSString*)newInputFile NS_SWIFT_NAME(setInputFile(_:));

@property (nonatomic,readwrite,assign,getter=namespaceCount,setter=setNamespaceCount:) int namespaceCount NS_SWIFT_NAME(namespaceCount);
- (int)namespaceCount NS_SWIFT_NAME(namespaceCount());
- (void)setNamespaceCount:(int)newNamespaceCount NS_SWIFT_NAME(setNamespaceCount(_:));

- (NSString*)namespacePrefix:(int)namespaceIndex NS_SWIFT_NAME(namespacePrefix(_:));
- (void)setNamespacePrefix:(int)namespaceIndex:(NSString*)newNamespacePrefix NS_SWIFT_NAME(setNamespacePrefix(_:_:));

- (NSString*)namespaceURI:(int)namespaceIndex NS_SWIFT_NAME(namespaceURI(_:));
- (void)setNamespaceURI:(int)namespaceIndex:(NSString*)newNamespaceURI NS_SWIFT_NAME(setNamespaceURI(_:_:));

@property (nonatomic,readwrite,assign,getter=outputData,setter=setOutputData:) NSString* outputData NS_SWIFT_NAME(outputData);
- (NSString*)outputData NS_SWIFT_NAME(outputData());
- (void)setOutputData:(NSString*)newOutputData NS_SWIFT_NAME(setOutputData(_:));

@property (nonatomic,readwrite,assign,getter=outputFile,setter=setOutputFile:) NSString* outputFile NS_SWIFT_NAME(outputFile);
- (NSString*)outputFile NS_SWIFT_NAME(outputFile());
- (void)setOutputFile:(NSString*)newOutputFile NS_SWIFT_NAME(setOutputFile(_:));

@property (nonatomic,readwrite,assign,getter=overwrite,setter=setOverwrite:) BOOL overwrite NS_SWIFT_NAME(overwrite);
- (BOOL)overwrite NS_SWIFT_NAME(overwrite());
- (void)setOverwrite:(BOOL)newOverwrite NS_SWIFT_NAME(setOverwrite(_:));

@property (nonatomic,readwrite,assign,getter=validate,setter=setValidate:) BOOL validate NS_SWIFT_NAME(validate);
- (BOOL)validate NS_SWIFT_NAME(validate());
- (void)setValidate:(BOOL)newValidate NS_SWIFT_NAME(setValidate(_:));

@property (nonatomic,readwrite,assign,getter=attrCount,setter=setAttrCount:) int attrCount NS_SWIFT_NAME(attrCount);
- (int)attrCount NS_SWIFT_NAME(attrCount());
- (void)setAttrCount:(int)newAttrCount NS_SWIFT_NAME(setAttrCount(_:));

- (NSString*)attrName:(int)attrIndex NS_SWIFT_NAME(attrName(_:));

- (NSString*)attrNamespace:(int)attrIndex NS_SWIFT_NAME(attrNamespace(_:));

- (NSString*)attrPrefix:(int)attrIndex NS_SWIFT_NAME(attrPrefix(_:));

- (NSString*)attrValue:(int)attrIndex NS_SWIFT_NAME(attrValue(_:));

@property (nonatomic,readwrite,assign,getter=XChildCount,setter=setXChildCount:) int XChildCount NS_SWIFT_NAME(XChildCount);
- (int)XChildCount NS_SWIFT_NAME(XChildCount());
- (void)setXChildCount:(int)newXChildCount NS_SWIFT_NAME(setXChildCount(_:));

- (NSString*)XChildName:(int)xChildIndex NS_SWIFT_NAME(XChildName(_:));

- (NSString*)XChildNamespace:(int)xChildIndex NS_SWIFT_NAME(XChildNamespace(_:));

- (NSString*)XChildPrefix:(int)xChildIndex NS_SWIFT_NAME(XChildPrefix(_:));

- (NSString*)XChildXText:(int)xChildIndex NS_SWIFT_NAME(XChildXText(_:));

@property (nonatomic,readwrite,assign,getter=XCommentCount,setter=setXCommentCount:) int XCommentCount NS_SWIFT_NAME(XCommentCount);
- (int)XCommentCount NS_SWIFT_NAME(XCommentCount());
- (void)setXCommentCount:(int)newXCommentCount NS_SWIFT_NAME(setXCommentCount(_:));

- (NSString*)XCommentText:(int)xCommentIndex NS_SWIFT_NAME(XCommentText(_:));
- (void)setXCommentText:(int)xCommentIndex:(NSString*)newXCommentText NS_SWIFT_NAME(setXCommentText(_:_:));

@property (nonatomic,readwrite,assign,getter=XElement,setter=setXElement:) NSString* XElement NS_SWIFT_NAME(XElement);
- (NSString*)XElement NS_SWIFT_NAME(XElement());
- (void)setXElement:(NSString*)newXElement NS_SWIFT_NAME(setXElement(_:));

@property (nonatomic,readwrite,assign,getter=XMLDeclarationEncoding,setter=setXMLDeclarationEncoding:) NSString* XMLDeclarationEncoding NS_SWIFT_NAME(XMLDeclarationEncoding);
- (NSString*)XMLDeclarationEncoding NS_SWIFT_NAME(XMLDeclarationEncoding());
- (void)setXMLDeclarationEncoding:(NSString*)newXMLDeclarationEncoding NS_SWIFT_NAME(setXMLDeclarationEncoding(_:));

@property (nonatomic,readwrite,assign,getter=XMLDeclarationStandalone,setter=setXMLDeclarationStandalone:) BOOL XMLDeclarationStandalone NS_SWIFT_NAME(XMLDeclarationStandalone);
- (BOOL)XMLDeclarationStandalone NS_SWIFT_NAME(XMLDeclarationStandalone());
- (void)setXMLDeclarationStandalone:(BOOL)newXMLDeclarationStandalone NS_SWIFT_NAME(setXMLDeclarationStandalone(_:));

@property (nonatomic,readwrite,assign,getter=XMLDeclarationVersion,setter=setXMLDeclarationVersion:) NSString* XMLDeclarationVersion NS_SWIFT_NAME(XMLDeclarationVersion);
- (NSString*)XMLDeclarationVersion NS_SWIFT_NAME(XMLDeclarationVersion());
- (void)setXMLDeclarationVersion:(NSString*)newXMLDeclarationVersion NS_SWIFT_NAME(setXMLDeclarationVersion(_:));

@property (nonatomic,readwrite,assign,getter=XNamespace,setter=setXNamespace:) NSString* XNamespace NS_SWIFT_NAME(XNamespace);
- (NSString*)XNamespace NS_SWIFT_NAME(XNamespace());
- (void)setXNamespace:(NSString*)newXNamespace NS_SWIFT_NAME(setXNamespace(_:));

@property (nonatomic,readonly,assign,getter=XParent) NSString* XParent NS_SWIFT_NAME(XParent);
- (NSString*)XParent NS_SWIFT_NAME(XParent());

@property (nonatomic,readwrite,assign,getter=XPath,setter=setXPath:) NSString* XPath NS_SWIFT_NAME(XPath);
- (NSString*)XPath NS_SWIFT_NAME(XPath());
- (void)setXPath:(NSString*)newXPath NS_SWIFT_NAME(setXPath(_:));

@property (nonatomic,readwrite,assign,getter=XPrefix,setter=setXPrefix:) NSString* XPrefix NS_SWIFT_NAME(XPrefix);
- (NSString*)XPrefix NS_SWIFT_NAME(XPrefix());
- (void)setXPrefix:(NSString*)newXPrefix NS_SWIFT_NAME(setXPrefix(_:));

@property (nonatomic,readonly,assign,getter=XSubTree) NSString* XSubTree NS_SWIFT_NAME(XSubTree);
- (NSString*)XSubTree NS_SWIFT_NAME(XSubTree());

@property (nonatomic,readwrite,assign,getter=XText,setter=setXText:) NSString* XText NS_SWIFT_NAME(XText);
- (NSString*)XText NS_SWIFT_NAME(XText());
- (void)setXText:(NSString*)newXText NS_SWIFT_NAME(setXText(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)endElement NS_SWIFT_NAME(endElement());
- (void)flush NS_SWIFT_NAME(flush());
- (NSString*)getAttr:(NSString*)attrName NS_SWIFT_NAME(getAttr(_:));
- (BOOL)hasXPath:(NSString*)XPath NS_SWIFT_NAME(hasXPath(_:));
- (void)loadDOM:(NSString*)fileName NS_SWIFT_NAME(loadDOM(_:));
- (void)loadSchema:(NSString*)schema NS_SWIFT_NAME(loadSchema(_:));
- (void)parse NS_SWIFT_NAME(parse());
- (void)putAttr:(NSString*)name :(NSString*)namespaceURI :(NSString*)value NS_SWIFT_NAME(putAttr(_:_:_:));
- (void)putCData:(NSString*)text NS_SWIFT_NAME(putCData(_:));
- (void)putComment:(NSString*)text NS_SWIFT_NAME(putComment(_:));
- (void)putElement:(NSString*)name :(NSString*)namespaceURI :(NSString*)value NS_SWIFT_NAME(putElement(_:_:_:));
- (void)putRaw:(NSString*)text NS_SWIFT_NAME(putRaw(_:));
- (void)putString:(NSString*)text NS_SWIFT_NAME(putString(_:));
- (void)removeAttr:(NSString*)attrName NS_SWIFT_NAME(removeAttr(_:));
- (void)removeChildren NS_SWIFT_NAME(removeChildren());
- (void)removeElement NS_SWIFT_NAME(removeElement());
- (void)reset NS_SWIFT_NAME(reset());
- (void)save NS_SWIFT_NAME(save());
- (void)saveDOM:(NSString*)fileName NS_SWIFT_NAME(saveDOM(_:));
- (void)startElement:(NSString*)name :(NSString*)namespaceURI NS_SWIFT_NAME(startElement(_:_:));
- (BOOL)tryXPath:(NSString*)xpath NS_SWIFT_NAME(tryXPath(_:));

@end


