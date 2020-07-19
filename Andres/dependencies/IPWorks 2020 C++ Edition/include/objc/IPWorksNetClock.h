
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//TPROTOCOL
#define TP_TIME                                            0
#define TP_SNTP                                            1


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksNetClockDelegate <NSObject>
@optional
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
@end

@interface IPWorksNetClock : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksNetClockDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasError;
}

+ (IPWorksNetClock*)netclock;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksNetClockDelegate> delegate;
- (id <IPWorksNetClockDelegate>)delegate;
- (void) setDelegate:(id <IPWorksNetClockDelegate>)anObject;

  /* Events */

- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));

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

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readonly,assign,getter=localTime) NSString* localTime NS_SWIFT_NAME(localTime);
- (NSString*)localTime NS_SWIFT_NAME(localTime());

@property (nonatomic,readwrite,assign,getter=protocol,setter=setProtocol:) int protocol NS_SWIFT_NAME(protocol);
- (int)protocol NS_SWIFT_NAME(protocol());
- (int)protocol_ NS_SWIFT_NAME(protocol_());
- (void)setProtocol:(int)newProtocol NS_SWIFT_NAME(setProtocol(_:));
- (void)setProtocol_:(int)newProtocol NS_SWIFT_NAME(setProtocol_(_:));

@property (nonatomic,readonly,assign,getter=serverTime) NSString* serverTime NS_SWIFT_NAME(serverTime);
- (NSString*)serverTime NS_SWIFT_NAME(serverTime());

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

@property (nonatomic,readwrite,assign,getter=timePort,setter=setTimePort:) int timePort NS_SWIFT_NAME(timePort);
- (int)timePort NS_SWIFT_NAME(timePort());
- (void)setTimePort:(int)newTimePort NS_SWIFT_NAME(setTimePort(_:));

@property (nonatomic,readwrite,assign,getter=timeServer,setter=setTimeServer:) NSString* timeServer NS_SWIFT_NAME(timeServer);
- (NSString*)timeServer NS_SWIFT_NAME(timeServer());
- (void)setTimeServer:(NSString*)newTimeServer NS_SWIFT_NAME(setTimeServer(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)getAndSetTime NS_SWIFT_NAME(getAndSetTime());
- (void)getTime NS_SWIFT_NAME(getTime());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)reset NS_SWIFT_NAME(reset());

@end


