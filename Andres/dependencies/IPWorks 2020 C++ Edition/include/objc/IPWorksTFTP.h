
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksTFTPDelegate <NSObject>
@optional
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text NS_SWIFT_NAME(onTransfer(_:_:_:_:));
@end

@interface IPWorksTFTP : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksTFTPDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasError;
  BOOL m_delegateHasStartTransfer;
  BOOL m_delegateHasTransfer;
}

+ (IPWorksTFTP*)tftp;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksTFTPDelegate> delegate;
- (id <IPWorksTFTPDelegate>)delegate;
- (void) setDelegate:(id <IPWorksTFTPDelegate>)anObject;

  /* Events */

- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text NS_SWIFT_NAME(onTransfer(_:_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readwrite,assign,getter=localFile,setter=setLocalFile:) NSString* localFile NS_SWIFT_NAME(localFile);
- (NSString*)localFile NS_SWIFT_NAME(localFile());
- (void)setLocalFile:(NSString*)newLocalFile NS_SWIFT_NAME(setLocalFile(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=maxRetransmits,setter=setMaxRetransmits:) int maxRetransmits NS_SWIFT_NAME(maxRetransmits);
- (int)maxRetransmits NS_SWIFT_NAME(maxRetransmits());
- (void)setMaxRetransmits:(int)newMaxRetransmits NS_SWIFT_NAME(setMaxRetransmits(_:));

@property (nonatomic,readwrite,assign,getter=remoteFile,setter=setRemoteFile:) NSString* remoteFile NS_SWIFT_NAME(remoteFile);
- (NSString*)remoteFile NS_SWIFT_NAME(remoteFile());
- (void)setRemoteFile:(NSString*)newRemoteFile NS_SWIFT_NAME(setRemoteFile(_:));

@property (nonatomic,readwrite,assign,getter=retransmitTimeout,setter=setRetransmitTimeout:) int retransmitTimeout NS_SWIFT_NAME(retransmitTimeout);
- (int)retransmitTimeout NS_SWIFT_NAME(retransmitTimeout());
- (void)setRetransmitTimeout:(int)newRetransmitTimeout NS_SWIFT_NAME(setRetransmitTimeout(_:));

@property (nonatomic,readwrite,assign,getter=TFTPPort,setter=setTFTPPort:) int TFTPPort NS_SWIFT_NAME(TFTPPort);
- (int)TFTPPort NS_SWIFT_NAME(TFTPPort());
- (void)setTFTPPort:(int)newTFTPPort NS_SWIFT_NAME(setTFTPPort(_:));

@property (nonatomic,readwrite,assign,getter=TFTPServer,setter=setTFTPServer:) NSString* TFTPServer NS_SWIFT_NAME(TFTPServer);
- (NSString*)TFTPServer NS_SWIFT_NAME(TFTPServer());
- (void)setTFTPServer:(NSString*)newTFTPServer NS_SWIFT_NAME(setTFTPServer(_:));

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)getFile NS_SWIFT_NAME(getFile());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)putFile NS_SWIFT_NAME(putFile());
- (void)reset NS_SWIFT_NAME(reset());

@end


