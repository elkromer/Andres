
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksTraceRouteDelegate <NSObject>
@optional
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHop:(int)hopNumber :(NSString*)hostAddress :(int)duration NS_SWIFT_NAME(onHop(_:_:_:));
- (void)onHopResolved:(int)hopNumber :(int)statusCode :(NSString*)hopHostName NS_SWIFT_NAME(onHopResolved(_:_:_:));
@end

@interface IPWorksTraceRoute : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksTraceRouteDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasError;
  BOOL m_delegateHasHop;
  BOOL m_delegateHasHopResolved;
}

+ (IPWorksTraceRoute*)traceroute;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksTraceRouteDelegate> delegate;
- (id <IPWorksTraceRouteDelegate>)delegate;
- (void) setDelegate:(id <IPWorksTraceRouteDelegate>)anObject;

  /* Events */

- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHop:(int)hopNumber :(NSString*)hostAddress :(int)duration NS_SWIFT_NAME(onHop(_:_:_:));
- (void)onHopResolved:(int)hopNumber :(int)statusCode :(NSString*)hopHostName NS_SWIFT_NAME(onHopResolved(_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=hopLimit,setter=setHopLimit:) int hopLimit NS_SWIFT_NAME(hopLimit);
- (int)hopLimit NS_SWIFT_NAME(hopLimit());
- (void)setHopLimit:(int)newHopLimit NS_SWIFT_NAME(setHopLimit(_:));

@property (nonatomic,readonly,assign,getter=hopCount) int hopCount NS_SWIFT_NAME(hopCount);
- (int)hopCount NS_SWIFT_NAME(hopCount());

- (int)hopErrorCode:(int)hopIndex NS_SWIFT_NAME(hopErrorCode(_:));

- (NSString*)hopErrorDescription:(int)hopIndex NS_SWIFT_NAME(hopErrorDescription(_:));

- (NSString*)hopHostAddress:(int)hopIndex NS_SWIFT_NAME(hopHostAddress(_:));

- (NSString*)hopHostName:(int)hopIndex NS_SWIFT_NAME(hopHostName(_:));

- (int)hopTime:(int)hopIndex NS_SWIFT_NAME(hopTime(_:));

@property (nonatomic,readwrite,assign,getter=hopTimeout,setter=setHopTimeout:) int hopTimeout NS_SWIFT_NAME(hopTimeout);
- (int)hopTimeout NS_SWIFT_NAME(hopTimeout());
- (void)setHopTimeout:(int)newHopTimeout NS_SWIFT_NAME(setHopTimeout(_:));

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=remoteHost,setter=setRemoteHost:) NSString* remoteHost NS_SWIFT_NAME(remoteHost);
- (NSString*)remoteHost NS_SWIFT_NAME(remoteHost());
- (void)setRemoteHost:(NSString*)newRemoteHost NS_SWIFT_NAME(setRemoteHost(_:));

@property (nonatomic,readwrite,assign,getter=resolveNames,setter=setResolveNames:) BOOL resolveNames NS_SWIFT_NAME(resolveNames);
- (BOOL)resolveNames NS_SWIFT_NAME(resolveNames());
- (void)setResolveNames:(BOOL)newResolveNames NS_SWIFT_NAME(setResolveNames(_:));

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)reset NS_SWIFT_NAME(reset());
- (void)traceTo:(NSString*)host NS_SWIFT_NAME(traceTo(_:));

@end


