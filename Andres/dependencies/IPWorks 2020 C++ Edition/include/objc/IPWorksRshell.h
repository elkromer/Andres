
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//FIREWALLTYPES
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksRshellDelegate <NSObject>
@optional
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onStderr:(NSData*)text :(BOOL)EOL NS_SWIFT_NAME(onStderr(_:_:));
- (void)onStdout:(NSData*)text :(BOOL)EOL NS_SWIFT_NAME(onStdout(_:_:));
@end

@interface IPWorksRshell : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksRshellDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnected;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasDisconnected;
  BOOL m_delegateHasError;
  BOOL m_delegateHasStderr;
  BOOL m_delegateHasStdout;
}

+ (IPWorksRshell*)rshell;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksRshellDelegate> delegate;
- (id <IPWorksRshellDelegate>)delegate;
- (void) setDelegate:(id <IPWorksRshellDelegate>)anObject;

  /* Events */

- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onStderr:(NSData*)text :(BOOL)EOL NS_SWIFT_NAME(onStderr(_:_:));
- (void)onStdout:(NSData*)text :(BOOL)EOL NS_SWIFT_NAME(onStdout(_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readonly,assign,getter=bytesSent) int bytesSent NS_SWIFT_NAME(bytesSent);
- (int)bytesSent NS_SWIFT_NAME(bytesSent());

@property (nonatomic,readwrite,assign,getter=command,setter=setCommand:) NSString* command NS_SWIFT_NAME(command);
- (NSString*)command NS_SWIFT_NAME(command());
- (void)setCommand:(NSString*)newCommand NS_SWIFT_NAME(setCommand(_:));

@property (nonatomic,readwrite,assign,getter=connected,setter=setConnected:) BOOL connected NS_SWIFT_NAME(connected);
- (BOOL)connected NS_SWIFT_NAME(connected());
- (void)setConnected:(BOOL)newConnected NS_SWIFT_NAME(setConnected(_:));

@property (nonatomic,readonly,assign,getter=eoF) BOOL eoF NS_SWIFT_NAME(eoF);
- (BOOL)eoF NS_SWIFT_NAME(eoF());

@property (nonatomic,readwrite,assign,getter=EOL,setter=setEOL:) NSString* EOL NS_SWIFT_NAME(EOL);
- (NSString*)EOL NS_SWIFT_NAME(EOL());
- (void)setEOL:(NSString*)newEOL NS_SWIFT_NAME(setEOL(_:));

@property (nonatomic,readwrite,assign,getter=EOLB,setter=setEOLB:) NSData* EOLB NS_SWIFT_NAME(EOLB);
- (NSData*)EOLB NS_SWIFT_NAME(EOLB());
- (void)setEOLB :(NSData*)newEOL NS_SWIFT_NAME(setEOLB(_:));

@property (nonatomic,readwrite,assign,getter=errEOL,setter=setErrEOL:) NSString* errEOL NS_SWIFT_NAME(errEOL);
- (NSString*)errEOL NS_SWIFT_NAME(errEOL());
- (void)setErrEOL:(NSString*)newErrEOL NS_SWIFT_NAME(setErrEOL(_:));

@property (nonatomic,readwrite,assign,getter=errEOLB,setter=setErrEOLB:) NSData* errEOLB NS_SWIFT_NAME(errEOLB);
- (NSData*)errEOLB NS_SWIFT_NAME(errEOLB());
- (void)setErrEOLB :(NSData*)newErrEOL NS_SWIFT_NAME(setErrEOLB(_:));

@property (nonatomic,readonly,assign,getter=errorMessage) NSString* errorMessage NS_SWIFT_NAME(errorMessage);
- (NSString*)errorMessage NS_SWIFT_NAME(errorMessage());

@property (nonatomic,readwrite,assign,getter=firewallAutoDetect,setter=setFirewallAutoDetect:) BOOL firewallAutoDetect NS_SWIFT_NAME(firewallAutoDetect);
- (BOOL)firewallAutoDetect NS_SWIFT_NAME(firewallAutoDetect());
- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect NS_SWIFT_NAME(setFirewallAutoDetect(_:));

@property (nonatomic,readwrite,assign,getter=firewallType,setter=setFirewallType:) int firewallType NS_SWIFT_NAME(firewallType);
- (int)firewallType NS_SWIFT_NAME(firewallType());
- (void)setFirewallType:(int)newFirewallType NS_SWIFT_NAME(setFirewallType(_:));

@property (nonatomic,readwrite,assign,getter=firewallHost,setter=setFirewallHost:) NSString* firewallHost NS_SWIFT_NAME(firewallHost);
- (NSString*)firewallHost NS_SWIFT_NAME(firewallHost());
- (void)setFirewallHost:(NSString*)newFirewallHost NS_SWIFT_NAME(setFirewallHost(_:));

@property (nonatomic,readwrite,assign,getter=firewallPassword,setter=setFirewallPassword:) NSString* firewallPassword NS_SWIFT_NAME(firewallPassword);
- (NSString*)firewallPassword NS_SWIFT_NAME(firewallPassword());
- (void)setFirewallPassword:(NSString*)newFirewallPassword NS_SWIFT_NAME(setFirewallPassword(_:));

@property (nonatomic,readwrite,assign,getter=firewallPort,setter=setFirewallPort:) int firewallPort NS_SWIFT_NAME(firewallPort);
- (int)firewallPort NS_SWIFT_NAME(firewallPort());
- (void)setFirewallPort:(int)newFirewallPort NS_SWIFT_NAME(setFirewallPort(_:));

@property (nonatomic,readwrite,assign,getter=firewallUser,setter=setFirewallUser:) NSString* firewallUser NS_SWIFT_NAME(firewallUser);
- (NSString*)firewallUser NS_SWIFT_NAME(firewallUser());
- (void)setFirewallUser:(NSString*)newFirewallUser NS_SWIFT_NAME(setFirewallUser(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=localPort,setter=setLocalPort:) int localPort NS_SWIFT_NAME(localPort);
- (int)localPort NS_SWIFT_NAME(localPort());
- (void)setLocalPort:(int)newLocalPort NS_SWIFT_NAME(setLocalPort(_:));

@property (nonatomic,readwrite,assign,getter=localUser,setter=setLocalUser:) NSString* localUser NS_SWIFT_NAME(localUser);
- (NSString*)localUser NS_SWIFT_NAME(localUser());
- (void)setLocalUser:(NSString*)newLocalUser NS_SWIFT_NAME(setLocalUser(_:));

@property (nonatomic,readwrite,assign,getter=remoteHost,setter=setRemoteHost:) NSString* remoteHost NS_SWIFT_NAME(remoteHost);
- (NSString*)remoteHost NS_SWIFT_NAME(remoteHost());
- (void)setRemoteHost:(NSString*)newRemoteHost NS_SWIFT_NAME(setRemoteHost(_:));

@property (nonatomic,readwrite,assign,getter=remotePort,setter=setRemotePort:) int remotePort NS_SWIFT_NAME(remotePort);
- (int)remotePort NS_SWIFT_NAME(remotePort());
- (void)setRemotePort:(int)newRemotePort NS_SWIFT_NAME(setRemotePort(_:));

@property (nonatomic,readwrite,assign,getter=remoteUser,setter=setRemoteUser:) NSString* remoteUser NS_SWIFT_NAME(remoteUser);
- (NSString*)remoteUser NS_SWIFT_NAME(remoteUser());
- (void)setRemoteUser:(NSString*)newRemoteUser NS_SWIFT_NAME(setRemoteUser(_:));

@property (nonatomic,readonly,assign,getter=stderr) NSString* stderr NS_SWIFT_NAME(stderr);
- (NSString*)stderr NS_SWIFT_NAME(stderr());
- (NSString*)stderr_ NS_SWIFT_NAME(stderr_());

@property (nonatomic,readonly,assign,getter=stderrB) NSData* stderrB NS_SWIFT_NAME(stderrB);
- (NSData*)stderrB NS_SWIFT_NAME(stderrB());

@property (nonatomic,readwrite,assign,getter=stdin,setter=setStdin:) NSString* stdin NS_SWIFT_NAME(stdin);
- (NSString*)stdin NS_SWIFT_NAME(stdin());
- (NSString*)stdin_ NS_SWIFT_NAME(stdin_());
- (void)setStdin:(NSString*)newStdin NS_SWIFT_NAME(setStdin(_:));
- (void)setStdin_:(NSString*)newStdin NS_SWIFT_NAME(setStdin_(_:));

@property (nonatomic,readwrite,assign,getter=stdinB,setter=setStdinB:) NSData* stdinB NS_SWIFT_NAME(stdinB);
- (NSData*)stdinB NS_SWIFT_NAME(stdinB());
- (void)setStdinB :(NSData*)newStdin NS_SWIFT_NAME(setStdinB(_:));

@property (nonatomic,readonly,assign,getter=stdout) NSString* stdout NS_SWIFT_NAME(stdout);
- (NSString*)stdout NS_SWIFT_NAME(stdout());
- (NSString*)stdout_ NS_SWIFT_NAME(stdout_());

@property (nonatomic,readonly,assign,getter=stdoutB) NSData* stdoutB NS_SWIFT_NAME(stdoutB);
- (NSData*)stdoutB NS_SWIFT_NAME(stdoutB());

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)disconnect NS_SWIFT_NAME(disconnect());
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)execute:(NSString*)command NS_SWIFT_NAME(execute(_:));
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)reset NS_SWIFT_NAME(reset());
- (void)send:(NSData*)text NS_SWIFT_NAME(send(_:));

@end


