
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//MIMEPARTENCODINGS
#define PE_7BIT                                            0
#define PE_QUOTED_PRINTABLE                                1
#define PE_BASE_64                                         2
#define PE_8BIT                                            3
#define PE_BINARY                                          4
#define PE_UUENCODE                                        5


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksMIMEDelegate <NSObject>
@optional
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHeader:(int)partIndex :(NSString*)field :(NSData*)value NS_SWIFT_NAME(onHeader(_:_:_:));
- (void)onProgress:(int)percentDone NS_SWIFT_NAME(onProgress(_:));
@end

@interface IPWorksMIME : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksMIMEDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasError;
  BOOL m_delegateHasHeader;
  BOOL m_delegateHasProgress;
}

+ (IPWorksMIME*)mime;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksMIMEDelegate> delegate;
- (id <IPWorksMIMEDelegate>)delegate;
- (void) setDelegate:(id <IPWorksMIMEDelegate>)anObject;

  /* Events */

- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHeader:(int)partIndex :(NSString*)field :(NSData*)value NS_SWIFT_NAME(onHeader(_:_:_:));
- (void)onProgress:(int)percentDone NS_SWIFT_NAME(onProgress(_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=boundary,setter=setBoundary:) NSString* boundary NS_SWIFT_NAME(boundary);
- (NSString*)boundary NS_SWIFT_NAME(boundary());
- (void)setBoundary:(NSString*)newBoundary NS_SWIFT_NAME(setBoundary(_:));

@property (nonatomic,readwrite,assign,getter=contentType,setter=setContentType:) NSString* contentType NS_SWIFT_NAME(contentType);
- (NSString*)contentType NS_SWIFT_NAME(contentType());
- (void)setContentType:(NSString*)newContentType NS_SWIFT_NAME(setContentType(_:));

@property (nonatomic,readwrite,assign,getter=contentTypeAttr,setter=setContentTypeAttr:) NSString* contentTypeAttr NS_SWIFT_NAME(contentTypeAttr);
- (NSString*)contentTypeAttr NS_SWIFT_NAME(contentTypeAttr());
- (void)setContentTypeAttr:(NSString*)newContentTypeAttr NS_SWIFT_NAME(setContentTypeAttr(_:));

@property (nonatomic,readwrite,assign,getter=message,setter=setMessage:) NSString* message NS_SWIFT_NAME(message);
- (NSString*)message NS_SWIFT_NAME(message());
- (void)setMessage:(NSString*)newMessage NS_SWIFT_NAME(setMessage(_:));

@property (nonatomic,readwrite,assign,getter=messageB,setter=setMessageB:) NSData* messageB NS_SWIFT_NAME(messageB);
- (NSData*)messageB NS_SWIFT_NAME(messageB());
- (void)setMessageB :(NSData*)newMessage NS_SWIFT_NAME(setMessageB(_:));

@property (nonatomic,readwrite,assign,getter=messageHeaderCount,setter=setMessageHeaderCount:) int messageHeaderCount NS_SWIFT_NAME(messageHeaderCount);
- (int)messageHeaderCount NS_SWIFT_NAME(messageHeaderCount());
- (void)setMessageHeaderCount:(int)newMessageHeaderCount NS_SWIFT_NAME(setMessageHeaderCount(_:));

- (NSString*)messageHeaderField:(int)messageHeaderIndex NS_SWIFT_NAME(messageHeaderField(_:));
- (void)setMessageHeaderField:(int)messageHeaderIndex:(NSString*)newMessageHeaderField NS_SWIFT_NAME(setMessageHeaderField(_:_:));

- (NSString*)messageHeaderValue:(int)messageHeaderIndex NS_SWIFT_NAME(messageHeaderValue(_:));
- (void)setMessageHeaderValue:(int)messageHeaderIndex:(NSString*)newMessageHeaderValue NS_SWIFT_NAME(setMessageHeaderValue(_:_:));

@property (nonatomic,readwrite,assign,getter=messageHeadersString,setter=setMessageHeadersString:) NSString* messageHeadersString NS_SWIFT_NAME(messageHeadersString);
- (NSString*)messageHeadersString NS_SWIFT_NAME(messageHeadersString());
- (void)setMessageHeadersString:(NSString*)newMessageHeadersString NS_SWIFT_NAME(setMessageHeadersString(_:));

@property (nonatomic,readwrite,assign,getter=partCount,setter=setPartCount:) int partCount NS_SWIFT_NAME(partCount);
- (int)partCount NS_SWIFT_NAME(partCount());
- (void)setPartCount:(int)newPartCount NS_SWIFT_NAME(setPartCount(_:));

- (NSString*)partContentDisposition:(int)partIdx NS_SWIFT_NAME(partContentDisposition(_:));
- (void)setPartContentDisposition:(int)partIdx:(NSString*)newPartContentDisposition NS_SWIFT_NAME(setPartContentDisposition(_:_:));

- (NSString*)partContentDispositionAttr:(int)partIdx NS_SWIFT_NAME(partContentDispositionAttr(_:));
- (void)setPartContentDispositionAttr:(int)partIdx:(NSString*)newPartContentDispositionAttr NS_SWIFT_NAME(setPartContentDispositionAttr(_:_:));

- (NSString*)partContentId:(int)partIdx NS_SWIFT_NAME(partContentId(_:));
- (void)setPartContentId:(int)partIdx:(NSString*)newPartContentId NS_SWIFT_NAME(setPartContentId(_:_:));

- (NSString*)partContentType:(int)partIdx NS_SWIFT_NAME(partContentType(_:));
- (void)setPartContentType:(int)partIdx:(NSString*)newPartContentType NS_SWIFT_NAME(setPartContentType(_:_:));

- (NSString*)partContentTypeAttr:(int)partIdx NS_SWIFT_NAME(partContentTypeAttr(_:));
- (void)setPartContentTypeAttr:(int)partIdx:(NSString*)newPartContentTypeAttr NS_SWIFT_NAME(setPartContentTypeAttr(_:_:));

- (NSString*)partDecodedFile:(int)partIdx NS_SWIFT_NAME(partDecodedFile(_:));
- (void)setPartDecodedFile:(int)partIdx:(NSString*)newPartDecodedFile NS_SWIFT_NAME(setPartDecodedFile(_:_:));

- (NSString*)partDecodedString:(int)partIdx NS_SWIFT_NAME(partDecodedString(_:));
- (void)setPartDecodedString:(int)partIdx:(NSString*)newPartDecodedString NS_SWIFT_NAME(setPartDecodedString(_:_:));

- (NSData*)partDecodedStringB:(int)partIdx NS_SWIFT_NAME(partDecodedStringB(_:));
- (void)setPartDecodedStringB:(int)partIdx :(NSData*)newPartDecodedString NS_SWIFT_NAME(setPartDecodedStringB(_:_:));

- (int)partEncoding:(int)partIdx NS_SWIFT_NAME(partEncoding(_:));
- (void)setPartEncoding:(int)partIdx:(int)newPartEncoding NS_SWIFT_NAME(setPartEncoding(_:_:));

- (NSString*)partFilename:(int)partIdx NS_SWIFT_NAME(partFilename(_:));
- (void)setPartFilename:(int)partIdx:(NSString*)newPartFilename NS_SWIFT_NAME(setPartFilename(_:_:));

- (NSString*)partHeaders:(int)partIdx NS_SWIFT_NAME(partHeaders(_:));
- (void)setPartHeaders:(int)partIdx:(NSString*)newPartHeaders NS_SWIFT_NAME(setPartHeaders(_:_:));

- (NSString*)partName:(int)partIdx NS_SWIFT_NAME(partName(_:));
- (void)setPartName:(int)partIdx:(NSString*)newPartName NS_SWIFT_NAME(setPartName(_:_:));

- (int)partSize:(int)partIdx NS_SWIFT_NAME(partSize(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)decodeFromFile NS_SWIFT_NAME(decodeFromFile());
- (void)decodeFromString NS_SWIFT_NAME(decodeFromString());
- (void)encodeToFile NS_SWIFT_NAME(encodeToFile());
- (void)encodeToString NS_SWIFT_NAME(encodeToString());
- (void)reset NS_SWIFT_NAME(reset());
- (void)resetData NS_SWIFT_NAME(resetData());

@end


