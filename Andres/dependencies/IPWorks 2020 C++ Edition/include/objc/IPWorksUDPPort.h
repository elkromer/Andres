
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksUDPPortDelegate <NSObject>
@optional
- (void)onDataIn:(NSData*)datagram :(NSString*)sourceAddress :(int)sourcePort NS_SWIFT_NAME(onDataIn(_:_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onReadyToSend NS_SWIFT_NAME(onReadyToSend());
@end

@interface IPWorksUDPPort : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksUDPPortDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasDataIn;
  BOOL m_delegateHasError;
  BOOL m_delegateHasReadyToSend;
}

+ (IPWorksUDPPort*)udpport;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksUDPPortDelegate> delegate;
- (id <IPWorksUDPPortDelegate>)delegate;
- (void) setDelegate:(id <IPWorksUDPPortDelegate>)anObject;

  /* Events */

- (void)onDataIn:(NSData*)datagram :(NSString*)sourceAddress :(int)sourcePort NS_SWIFT_NAME(onDataIn(_:_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onReadyToSend NS_SWIFT_NAME(onReadyToSend());

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=acceptData,setter=setAcceptData:) BOOL acceptData NS_SWIFT_NAME(acceptData);
- (BOOL)acceptData NS_SWIFT_NAME(acceptData());
- (void)setAcceptData:(BOOL)newAcceptData NS_SWIFT_NAME(setAcceptData(_:));

@property (nonatomic,readwrite,assign,getter=active,setter=setActive:) BOOL active NS_SWIFT_NAME(active);
- (BOOL)active NS_SWIFT_NAME(active());
- (void)setActive:(BOOL)newActive NS_SWIFT_NAME(setActive(_:));

@property (nonatomic,readwrite,assign,getter=dataToSend,setter=setDataToSend:) NSString* dataToSend NS_SWIFT_NAME(dataToSend);
- (NSString*)dataToSend NS_SWIFT_NAME(dataToSend());
- (void)setDataToSend:(NSString*)newDataToSend NS_SWIFT_NAME(setDataToSend(_:));

@property (nonatomic,readwrite,assign,getter=dataToSendB,setter=setDataToSendB:) NSData* dataToSendB NS_SWIFT_NAME(dataToSendB);
- (NSData*)dataToSendB NS_SWIFT_NAME(dataToSendB());
- (void)setDataToSendB :(NSData*)newDataToSend NS_SWIFT_NAME(setDataToSendB(_:));

@property (nonatomic,readwrite,assign,getter=dontRoute,setter=setDontRoute:) BOOL dontRoute NS_SWIFT_NAME(dontRoute);
- (BOOL)dontRoute NS_SWIFT_NAME(dontRoute());
- (void)setDontRoute:(BOOL)newDontRoute NS_SWIFT_NAME(setDontRoute(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=localPort,setter=setLocalPort:) int localPort NS_SWIFT_NAME(localPort);
- (int)localPort NS_SWIFT_NAME(localPort());
- (void)setLocalPort:(int)newLocalPort NS_SWIFT_NAME(setLocalPort(_:));

@property (nonatomic,readwrite,assign,getter=remoteHost,setter=setRemoteHost:) NSString* remoteHost NS_SWIFT_NAME(remoteHost);
- (NSString*)remoteHost NS_SWIFT_NAME(remoteHost());
- (void)setRemoteHost:(NSString*)newRemoteHost NS_SWIFT_NAME(setRemoteHost(_:));

@property (nonatomic,readwrite,assign,getter=remotePort,setter=setRemotePort:) int remotePort NS_SWIFT_NAME(remotePort);
- (int)remotePort NS_SWIFT_NAME(remotePort());
- (void)setRemotePort:(int)newRemotePort NS_SWIFT_NAME(setRemotePort(_:));

@property (nonatomic,readwrite,assign,getter=timeToLive,setter=setTimeToLive:) int timeToLive NS_SWIFT_NAME(timeToLive);
- (int)timeToLive NS_SWIFT_NAME(timeToLive());
- (void)setTimeToLive:(int)newTimeToLive NS_SWIFT_NAME(setTimeToLive(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)reset NS_SWIFT_NAME(reset());
- (void)send:(NSData*)text NS_SWIFT_NAME(send(_:));

@end


