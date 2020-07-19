
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksPingDelegate <NSObject>
@optional
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onResponse:(int)requestId :(NSString*)responseSource :(NSString*)responseStatus :(int)responseTime NS_SWIFT_NAME(onResponse(_:_:_:_:));
@end

@interface IPWorksPing : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksPingDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasError;
  BOOL m_delegateHasResponse;
}

+ (IPWorksPing*)ping;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksPingDelegate> delegate;
- (id <IPWorksPingDelegate>)delegate;
- (void) setDelegate:(id <IPWorksPingDelegate>)anObject;

  /* Events */

- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onResponse:(int)requestId :(NSString*)responseSource :(NSString*)responseStatus :(int)responseTime NS_SWIFT_NAME(onResponse(_:_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=active,setter=setActive:) BOOL active NS_SWIFT_NAME(active);
- (BOOL)active NS_SWIFT_NAME(active());
- (void)setActive:(BOOL)newActive NS_SWIFT_NAME(setActive(_:));

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=packetSize,setter=setPacketSize:) int packetSize NS_SWIFT_NAME(packetSize);
- (int)packetSize NS_SWIFT_NAME(packetSize());
- (void)setPacketSize:(int)newPacketSize NS_SWIFT_NAME(setPacketSize(_:));

@property (nonatomic,readwrite,assign,getter=remoteHost,setter=setRemoteHost:) NSString* remoteHost NS_SWIFT_NAME(remoteHost);
- (NSString*)remoteHost NS_SWIFT_NAME(remoteHost());
- (void)setRemoteHost:(NSString*)newRemoteHost NS_SWIFT_NAME(setRemoteHost(_:));

@property (nonatomic,readonly,assign,getter=requestId) int requestId NS_SWIFT_NAME(requestId);
- (int)requestId NS_SWIFT_NAME(requestId());

@property (nonatomic,readonly,assign,getter=responseSource) NSString* responseSource NS_SWIFT_NAME(responseSource);
- (NSString*)responseSource NS_SWIFT_NAME(responseSource());

@property (nonatomic,readonly,assign,getter=responseTime) int responseTime NS_SWIFT_NAME(responseTime);
- (int)responseTime NS_SWIFT_NAME(responseTime());

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

@property (nonatomic,readwrite,assign,getter=timeToLive,setter=setTimeToLive:) int timeToLive NS_SWIFT_NAME(timeToLive);
- (int)timeToLive NS_SWIFT_NAME(timeToLive());
- (void)setTimeToLive:(int)newTimeToLive NS_SWIFT_NAME(setTimeToLive(_:));

@property (nonatomic,readwrite,assign,getter=typeOfService,setter=setTypeOfService:) int typeOfService NS_SWIFT_NAME(typeOfService);
- (int)typeOfService NS_SWIFT_NAME(typeOfService());
- (void)setTypeOfService:(int)newTypeOfService NS_SWIFT_NAME(setTypeOfService(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)pingHost:(NSString*)host NS_SWIFT_NAME(pingHost(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)wakeOnLAN:(NSString*)remoteHost :(NSString*)MACAddress NS_SWIFT_NAME(wakeOnLAN(_:_:));

@end


