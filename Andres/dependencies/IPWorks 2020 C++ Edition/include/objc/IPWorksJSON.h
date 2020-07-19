
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//TXELEMENTTYPE
#define ET_OBJECT                                          0
#define ET_ARRAY                                           1
#define ET_STRING                                          2
#define ET_NUMBER                                          3
#define ET_BOOL                                            4
#define ET_NULL                                            5


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksJSONDelegate <NSObject>
@optional
- (void)onCharacters:(NSString*)text NS_SWIFT_NAME(onCharacters(_:));
- (void)onEndDocument NS_SWIFT_NAME(onEndDocument());
- (void)onEndElement:(NSString*)element NS_SWIFT_NAME(onEndElement(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onIgnorableWhitespace:(NSString*)text NS_SWIFT_NAME(onIgnorableWhitespace(_:));
- (void)onJSON:(NSString*)text NS_SWIFT_NAME(onJSON(_:));
- (void)onStartDocument NS_SWIFT_NAME(onStartDocument());
- (void)onStartElement:(NSString*)element NS_SWIFT_NAME(onStartElement(_:));
@end

@interface IPWorksJSON : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksJSONDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasCharacters;
  BOOL m_delegateHasEndDocument;
  BOOL m_delegateHasEndElement;
  BOOL m_delegateHasError;
  BOOL m_delegateHasIgnorableWhitespace;
  BOOL m_delegateHasJSON;
  BOOL m_delegateHasStartDocument;
  BOOL m_delegateHasStartElement;
}

+ (IPWorksJSON*)json;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksJSONDelegate> delegate;
- (id <IPWorksJSONDelegate>)delegate;
- (void) setDelegate:(id <IPWorksJSONDelegate>)anObject;

  /* Events */

- (void)onCharacters:(NSString*)text NS_SWIFT_NAME(onCharacters(_:));
- (void)onEndDocument NS_SWIFT_NAME(onEndDocument());
- (void)onEndElement:(NSString*)element NS_SWIFT_NAME(onEndElement(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onIgnorableWhitespace:(NSString*)text NS_SWIFT_NAME(onIgnorableWhitespace(_:));
- (void)onJSON:(NSString*)text NS_SWIFT_NAME(onJSON(_:));
- (void)onStartDocument NS_SWIFT_NAME(onStartDocument());
- (void)onStartElement:(NSString*)element NS_SWIFT_NAME(onStartElement(_:));

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

@property (nonatomic,readwrite,assign,getter=XChildCount,setter=setXChildCount:) int XChildCount NS_SWIFT_NAME(XChildCount);
- (int)XChildCount NS_SWIFT_NAME(XChildCount());
- (void)setXChildCount:(int)newXChildCount NS_SWIFT_NAME(setXChildCount(_:));

- (NSString*)XChildName:(int)xChildIndex NS_SWIFT_NAME(XChildName(_:));

- (NSString*)XChildXText:(int)xChildIndex NS_SWIFT_NAME(XChildXText(_:));

@property (nonatomic,readwrite,assign,getter=XElement,setter=setXElement:) NSString* XElement NS_SWIFT_NAME(XElement);
- (NSString*)XElement NS_SWIFT_NAME(XElement());
- (void)setXElement:(NSString*)newXElement NS_SWIFT_NAME(setXElement(_:));

@property (nonatomic,readonly,assign,getter=XElementType) int XElementType NS_SWIFT_NAME(XElementType);
- (int)XElementType NS_SWIFT_NAME(XElementType());

@property (nonatomic,readwrite,assign,getter=XErrorPath,setter=setXErrorPath:) NSString* XErrorPath NS_SWIFT_NAME(XErrorPath);
- (NSString*)XErrorPath NS_SWIFT_NAME(XErrorPath());
- (void)setXErrorPath:(NSString*)newXErrorPath NS_SWIFT_NAME(setXErrorPath(_:));

@property (nonatomic,readonly,assign,getter=XParent) NSString* XParent NS_SWIFT_NAME(XParent);
- (NSString*)XParent NS_SWIFT_NAME(XParent());

@property (nonatomic,readwrite,assign,getter=XPath,setter=setXPath:) NSString* XPath NS_SWIFT_NAME(XPath);
- (NSString*)XPath NS_SWIFT_NAME(XPath());
- (void)setXPath:(NSString*)newXPath NS_SWIFT_NAME(setXPath(_:));

@property (nonatomic,readonly,assign,getter=XSubTree) NSString* XSubTree NS_SWIFT_NAME(XSubTree);
- (NSString*)XSubTree NS_SWIFT_NAME(XSubTree());

@property (nonatomic,readwrite,assign,getter=XText,setter=setXText:) NSString* XText NS_SWIFT_NAME(XText);
- (NSString*)XText NS_SWIFT_NAME(XText());
- (void)setXText:(NSString*)newXText NS_SWIFT_NAME(setXText(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)endArray NS_SWIFT_NAME(endArray());
- (void)endObject NS_SWIFT_NAME(endObject());
- (void)flush NS_SWIFT_NAME(flush());
- (BOOL)hasXPath:(NSString*)XPath NS_SWIFT_NAME(hasXPath(_:));
- (void)insertProperty:(NSString*)name :(NSString*)value :(int)valueType :(int)position NS_SWIFT_NAME(insertProperty(_:_:_:_:));
- (void)insertValue:(NSString*)value :(int)valueType :(int)position NS_SWIFT_NAME(insertValue(_:_:_:));
- (void)loadSchema:(NSString*)schema NS_SWIFT_NAME(loadSchema(_:));
- (void)parse NS_SWIFT_NAME(parse());
- (void)putName:(NSString*)name NS_SWIFT_NAME(putName(_:));
- (void)putProperty:(NSString*)name :(NSString*)value :(int)valueType NS_SWIFT_NAME(putProperty(_:_:_:));
- (void)putRaw:(NSString*)text NS_SWIFT_NAME(putRaw(_:));
- (void)putValue:(NSString*)value :(int)valueType NS_SWIFT_NAME(putValue(_:_:));
- (void)remove NS_SWIFT_NAME(remove());
- (void)reset NS_SWIFT_NAME(reset());
- (void)save NS_SWIFT_NAME(save());
- (void)setName:(NSString*)name NS_SWIFT_NAME(setName(_:));
- (void)setValue:(NSString*)value :(int)valueType NS_SWIFT_NAME(setValue(_:_:));
- (void)startArray NS_SWIFT_NAME(startArray());
- (void)startObject NS_SWIFT_NAME(startObject());
- (BOOL)tryXPath:(NSString*)xpath NS_SWIFT_NAME(tryXPath(_:));

@end


