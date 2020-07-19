
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksMXDelegate <NSObject>
@optional
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onResponse:(int)requestId :(NSString*)domain :(NSString*)mailServer :(int)precedence :(int)timeToLive :(int)statusCode :(NSString*)description :(BOOL)authoritative NS_SWIFT_NAME(onResponse(_:_:_:_:_:_:_:_:));
@end

@interface IPWorksMX : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksMXDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasError;
  BOOL m_delegateHasResponse;
}

+ (IPWorksMX*)mx;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksMXDelegate> delegate;
- (id <IPWorksMXDelegate>)delegate;
- (void) setDelegate:(id <IPWorksMXDelegate>)anObject;

  /* Events */

- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onResponse:(int)requestId :(NSString*)domain :(NSString*)mailServer :(int)precedence :(int)timeToLive :(int)statusCode :(NSString*)description :(BOOL)authoritative NS_SWIFT_NAME(onResponse(_:_:_:_:_:_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=DNSPort,setter=setDNSPort:) int DNSPort NS_SWIFT_NAME(DNSPort);
- (int)DNSPort NS_SWIFT_NAME(DNSPort());
- (void)setDNSPort:(int)newDNSPort NS_SWIFT_NAME(setDNSPort(_:));

@property (nonatomic,readwrite,assign,getter=DNSServer,setter=setDNSServer:) NSString* DNSServer NS_SWIFT_NAME(DNSServer);
- (NSString*)DNSServer NS_SWIFT_NAME(DNSServer());
- (void)setDNSServer:(NSString*)newDNSServer NS_SWIFT_NAME(setDNSServer(_:));

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readonly,assign,getter=mailServer) NSString* mailServer NS_SWIFT_NAME(mailServer);
- (NSString*)mailServer NS_SWIFT_NAME(mailServer());

@property (nonatomic,readwrite,assign,getter=requestId,setter=setRequestId:) int requestId NS_SWIFT_NAME(requestId);
- (int)requestId NS_SWIFT_NAME(requestId());
- (void)setRequestId:(int)newRequestId NS_SWIFT_NAME(setRequestId(_:));

@property (nonatomic,readonly,assign,getter=status) NSString* status NS_SWIFT_NAME(status);
- (NSString*)status NS_SWIFT_NAME(status());

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)reset NS_SWIFT_NAME(reset());
- (void)resolve:(NSString*)emailAddress NS_SWIFT_NAME(resolve(_:));

@end


