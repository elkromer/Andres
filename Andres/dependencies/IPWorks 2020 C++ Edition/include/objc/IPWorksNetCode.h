
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//TFMT
#define FMT_UUENCODE                                       0
#define FMT_BASE_64                                        1
#define FMT_QP                                             2
#define FMT_URL                                            3
#define FMT_JIS                                            4
#define FMT_YENCODE                                        5
#define FMT_MD5HASH                                        6
#define FMT_SHA1HASH                                       7
#define FMT_HEX                                            8
#define FMT_HTML                                           9
#define FMT_HMAC                                           10
#define FMT_UTF8                                           11
#define FMT_UTF7                                           12
#define FMT_BASE_32                                        13
#define FMT_BASE_64URL                                     14
#define FMT_SHA256HASH                                     15
#define FMT_PUNYCODE                                       16


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksNetCodeDelegate <NSObject>
@optional
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onProgress:(int)percentDone NS_SWIFT_NAME(onProgress(_:));
@end

@interface IPWorksNetCode : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksNetCodeDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasError;
  BOOL m_delegateHasProgress;
}

+ (IPWorksNetCode*)netcode;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksNetCodeDelegate> delegate;
- (id <IPWorksNetCodeDelegate>)delegate;
- (void) setDelegate:(id <IPWorksNetCodeDelegate>)anObject;

  /* Events */

- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
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

@property (nonatomic,readwrite,assign,getter=decodedData,setter=setDecodedData:) NSString* decodedData NS_SWIFT_NAME(decodedData);
- (NSString*)decodedData NS_SWIFT_NAME(decodedData());
- (void)setDecodedData:(NSString*)newDecodedData NS_SWIFT_NAME(setDecodedData(_:));

@property (nonatomic,readwrite,assign,getter=decodedDataB,setter=setDecodedDataB:) NSData* decodedDataB NS_SWIFT_NAME(decodedDataB);
- (NSData*)decodedDataB NS_SWIFT_NAME(decodedDataB());
- (void)setDecodedDataB :(NSData*)newDecodedData NS_SWIFT_NAME(setDecodedDataB(_:));

@property (nonatomic,readwrite,assign,getter=decodedFile,setter=setDecodedFile:) NSString* decodedFile NS_SWIFT_NAME(decodedFile);
- (NSString*)decodedFile NS_SWIFT_NAME(decodedFile());
- (void)setDecodedFile:(NSString*)newDecodedFile NS_SWIFT_NAME(setDecodedFile(_:));

@property (nonatomic,readwrite,assign,getter=encodedData,setter=setEncodedData:) NSString* encodedData NS_SWIFT_NAME(encodedData);
- (NSString*)encodedData NS_SWIFT_NAME(encodedData());
- (void)setEncodedData:(NSString*)newEncodedData NS_SWIFT_NAME(setEncodedData(_:));

@property (nonatomic,readwrite,assign,getter=encodedDataB,setter=setEncodedDataB:) NSData* encodedDataB NS_SWIFT_NAME(encodedDataB);
- (NSData*)encodedDataB NS_SWIFT_NAME(encodedDataB());
- (void)setEncodedDataB :(NSData*)newEncodedData NS_SWIFT_NAME(setEncodedDataB(_:));

@property (nonatomic,readwrite,assign,getter=encodedFile,setter=setEncodedFile:) NSString* encodedFile NS_SWIFT_NAME(encodedFile);
- (NSString*)encodedFile NS_SWIFT_NAME(encodedFile());
- (void)setEncodedFile:(NSString*)newEncodedFile NS_SWIFT_NAME(setEncodedFile(_:));

@property (nonatomic,readonly,assign,getter=fileCnt) int fileCnt NS_SWIFT_NAME(fileCnt);
- (int)fileCnt NS_SWIFT_NAME(fileCnt());

@property (nonatomic,readwrite,assign,getter=fileName,setter=setFileName:) NSString* fileName NS_SWIFT_NAME(fileName);
- (NSString*)fileName NS_SWIFT_NAME(fileName());
- (void)setFileName:(NSString*)newFileName NS_SWIFT_NAME(setFileName(_:));

@property (nonatomic,readwrite,assign,getter=format,setter=setFormat:) int format NS_SWIFT_NAME(format);
- (int)format NS_SWIFT_NAME(format());
- (void)setFormat:(int)newFormat NS_SWIFT_NAME(setFormat(_:));

@property (nonatomic,readwrite,assign,getter=mode,setter=setMode:) NSString* mode NS_SWIFT_NAME(mode);
- (NSString*)mode NS_SWIFT_NAME(mode());
- (void)setMode:(NSString*)newMode NS_SWIFT_NAME(setMode(_:));

@property (nonatomic,readwrite,assign,getter=overwrite,setter=setOverwrite:) BOOL overwrite NS_SWIFT_NAME(overwrite);
- (BOOL)overwrite NS_SWIFT_NAME(overwrite());
- (void)setOverwrite:(BOOL)newOverwrite NS_SWIFT_NAME(setOverwrite(_:));

@property (nonatomic,readwrite,assign,getter=progressStep,setter=setProgressStep:) int progressStep NS_SWIFT_NAME(progressStep);
- (int)progressStep NS_SWIFT_NAME(progressStep());
- (void)setProgressStep:(int)newProgressStep NS_SWIFT_NAME(setProgressStep(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)decode NS_SWIFT_NAME(decode());
- (void)encode NS_SWIFT_NAME(encode());
- (void)reset NS_SWIFT_NAME(reset());
- (void)resetData NS_SWIFT_NAME(resetData());

@end


