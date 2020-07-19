
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

//TSMPPMESSAGEPRIORITIES
#define SMPP_MESSAGE_PRIORITY_LOW                          0
#define SMPP_MESSAGE_PRIORITY_NORMAL                       1
#define SMPP_MESSAGE_PRIORITY_HIGH                         2
#define SMPP_MESSAGE_PRIORITY_URGENT                       3

//TSMPPPROTOCOLS
#define SMPP_SMPP                                          0
#define SMPP_CIMD2                                         1

//SMPPRECIPIENTTYPES
#define SMPP_RECIPIENT_TYPE_NORMAL                         0
#define SMPP_RECIPIENT_TYPE_LIST                           1

//TSMPPSERVICETYPES
#define SMPP_SERVICE_DEFAULT                               0
#define SMPP_SERVICE_CMT                                   1
#define SMPP_SERVICE_CPT                                   2
#define SMPP_SERVICE_VMN                                   3
#define SMPP_SERVICE_VMA                                   4
#define SMPP_SERVICE_WAP                                   5
#define SMPP_SERVICE_USSD                                  6
#define SMPP_SERVICE_CBS                                   7

//TSMPPVERSIONS
#define SMPP_VERSION_50                                    0
#define SMPP_VERSION_34                                    1
#define SMPP_VERSION_33                                    2

//CERTSTORETYPES
#define CST_USER                                           0
#define CST_MACHINE                                        1
#define CST_PFXFILE                                        2
#define CST_PFXBLOB                                        3
#define CST_JKSFILE                                        4
#define CST_JKSBLOB                                        5
#define CST_PEMKEY_FILE                                    6
#define CST_PEMKEY_BLOB                                    7
#define CST_PUBLIC_KEY_FILE                                8
#define CST_PUBLIC_KEY_BLOB                                9
#define CST_SSHPUBLIC_KEY_BLOB                             10
#define CST_P7BFILE                                        11
#define CST_P7BBLOB                                        12
#define CST_SSHPUBLIC_KEY_FILE                             13
#define CST_PPKFILE                                        14
#define CST_PPKBLOB                                        15
#define CST_XMLFILE                                        16
#define CST_XMLBLOB                                        17
#define CST_JWKFILE                                        18
#define CST_JWKBLOB                                        19
#define CST_SECURITY_KEY                                   20
#define CST_AUTO                                           99

//TSSLSTARTMODE
#define SSL_AUTOMATIC                                      0
#define SSL_IMPLICIT                                       1
#define SSL_EXPLICIT                                       2
#define SSL_NONE                                           3


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksSMPPDelegate <NSObject>
@optional
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onMessageIn:(NSString*)sourceAddress :(NSString*)scheduleDeliveryTime :(NSString*)validityPeriod :(NSString*)message :(int)messagePart :(int)messagePartCount :(int)messagePartReference :(NSString*)destinationAddress :(int*)responseErrorCode NS_SWIFT_NAME(onMessageIn(_:_:_:_:_:_:_:_:_:));
- (void)onMessageStatus:(NSString*)messageId :(int)messageState :(int)messageError :(NSString*)finalDate NS_SWIFT_NAME(onMessageStatus(_:_:_:_:));
- (void)onPITrail:(int)direction :(NSData*)PDU :(int)commandLength :(int)commandId :(NSString*)commandDescription :(NSString*)commandStatus :(int)sequenceNumber NS_SWIFT_NAME(onPITrail(_:_:_:_:_:_:_:));
- (void)onReadyToSend NS_SWIFT_NAME(onReadyToSend());
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
@end

@interface IPWorksSMPP : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksSMPPDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnected;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasDisconnected;
  BOOL m_delegateHasError;
  BOOL m_delegateHasMessageIn;
  BOOL m_delegateHasMessageStatus;
  BOOL m_delegateHasPITrail;
  BOOL m_delegateHasReadyToSend;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
}

+ (IPWorksSMPP*)smpp;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksSMPPDelegate> delegate;
- (id <IPWorksSMPPDelegate>)delegate;
- (void) setDelegate:(id <IPWorksSMPPDelegate>)anObject;

  /* Events */

- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onMessageIn:(NSString*)sourceAddress :(NSString*)scheduleDeliveryTime :(NSString*)validityPeriod :(NSString*)message :(int)messagePart :(int)messagePartCount :(int)messagePartReference :(NSString*)destinationAddress :(int*)responseErrorCode NS_SWIFT_NAME(onMessageIn(_:_:_:_:_:_:_:_:_:));
- (void)onMessageStatus:(NSString*)messageId :(int)messageState :(int)messageError :(NSString*)finalDate NS_SWIFT_NAME(onMessageStatus(_:_:_:_:));
- (void)onPITrail:(int)direction :(NSData*)PDU :(int)commandLength :(int)commandId :(NSString*)commandDescription :(NSString*)commandStatus :(int)sequenceNumber NS_SWIFT_NAME(onPITrail(_:_:_:_:_:_:_:));
- (void)onReadyToSend NS_SWIFT_NAME(onReadyToSend());
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readonly,assign,getter=connected) BOOL connected NS_SWIFT_NAME(connected);
- (BOOL)connected NS_SWIFT_NAME(connected());

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

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=messageExpiration,setter=setMessageExpiration:) NSString* messageExpiration NS_SWIFT_NAME(messageExpiration);
- (NSString*)messageExpiration NS_SWIFT_NAME(messageExpiration());
- (void)setMessageExpiration:(NSString*)newMessageExpiration NS_SWIFT_NAME(setMessageExpiration(_:));

@property (nonatomic,readonly,assign,getter=messageId) NSString* messageId NS_SWIFT_NAME(messageId);
- (NSString*)messageId NS_SWIFT_NAME(messageId());

@property (nonatomic,readwrite,assign,getter=messagePriority,setter=setMessagePriority:) int messagePriority NS_SWIFT_NAME(messagePriority);
- (int)messagePriority NS_SWIFT_NAME(messagePriority());
- (void)setMessagePriority:(int)newMessagePriority NS_SWIFT_NAME(setMessagePriority(_:));

@property (nonatomic,readwrite,assign,getter=password,setter=setPassword:) NSString* password NS_SWIFT_NAME(password);
- (NSString*)password NS_SWIFT_NAME(password());
- (void)setPassword:(NSString*)newPassword NS_SWIFT_NAME(setPassword(_:));

@property (nonatomic,readwrite,assign,getter=protocol,setter=setProtocol:) int protocol NS_SWIFT_NAME(protocol);
- (int)protocol NS_SWIFT_NAME(protocol());
- (int)protocol_ NS_SWIFT_NAME(protocol_());
- (void)setProtocol:(int)newProtocol NS_SWIFT_NAME(setProtocol(_:));
- (void)setProtocol_:(int)newProtocol NS_SWIFT_NAME(setProtocol_(_:));

@property (nonatomic,readwrite,assign,getter=recipientCount,setter=setRecipientCount:) int recipientCount NS_SWIFT_NAME(recipientCount);
- (int)recipientCount NS_SWIFT_NAME(recipientCount());
- (void)setRecipientCount:(int)newRecipientCount NS_SWIFT_NAME(setRecipientCount(_:));

- (NSString*)recipientAddress:(int)recipientIndex NS_SWIFT_NAME(recipientAddress(_:));
- (void)setRecipientAddress:(int)recipientIndex:(NSString*)newRecipientAddress NS_SWIFT_NAME(setRecipientAddress(_:_:));

- (int)recipientType:(int)recipientIndex NS_SWIFT_NAME(recipientType(_:));
- (void)setRecipientType:(int)recipientIndex:(int)newRecipientType NS_SWIFT_NAME(setRecipientType(_:_:));

@property (nonatomic,readwrite,assign,getter=scheduledDelivery,setter=setScheduledDelivery:) NSString* scheduledDelivery NS_SWIFT_NAME(scheduledDelivery);
- (NSString*)scheduledDelivery NS_SWIFT_NAME(scheduledDelivery());
- (void)setScheduledDelivery:(NSString*)newScheduledDelivery NS_SWIFT_NAME(setScheduledDelivery(_:));

@property (nonatomic,readwrite,assign,getter=senderAddress,setter=setSenderAddress:) NSString* senderAddress NS_SWIFT_NAME(senderAddress);
- (NSString*)senderAddress NS_SWIFT_NAME(senderAddress());
- (void)setSenderAddress:(NSString*)newSenderAddress NS_SWIFT_NAME(setSenderAddress(_:));

@property (nonatomic,readwrite,assign,getter=serviceType,setter=setServiceType:) int serviceType NS_SWIFT_NAME(serviceType);
- (int)serviceType NS_SWIFT_NAME(serviceType());
- (void)setServiceType:(int)newServiceType NS_SWIFT_NAME(setServiceType(_:));

@property (nonatomic,readwrite,assign,getter=SMPPPort,setter=setSMPPPort:) int SMPPPort NS_SWIFT_NAME(SMPPPort);
- (int)SMPPPort NS_SWIFT_NAME(SMPPPort());
- (void)setSMPPPort:(int)newSMPPPort NS_SWIFT_NAME(setSMPPPort(_:));

@property (nonatomic,readwrite,assign,getter=SMPPServer,setter=setSMPPServer:) NSString* SMPPServer NS_SWIFT_NAME(SMPPServer);
- (NSString*)SMPPServer NS_SWIFT_NAME(SMPPServer());
- (void)setSMPPServer:(NSString*)newSMPPServer NS_SWIFT_NAME(setSMPPServer(_:));

@property (nonatomic,readwrite,assign,getter=SMPPVersion,setter=setSMPPVersion:) int SMPPVersion NS_SWIFT_NAME(SMPPVersion);
- (int)SMPPVersion NS_SWIFT_NAME(SMPPVersion());
- (void)setSMPPVersion:(int)newSMPPVersion NS_SWIFT_NAME(setSMPPVersion(_:));

@property (nonatomic,readwrite,assign,getter=SSLAcceptServerCertEncoded,setter=setSSLAcceptServerCertEncoded:) NSString* SSLAcceptServerCertEncoded NS_SWIFT_NAME(SSLAcceptServerCertEncoded);
- (NSString*)SSLAcceptServerCertEncoded NS_SWIFT_NAME(SSLAcceptServerCertEncoded());
- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded NS_SWIFT_NAME(setSSLAcceptServerCertEncoded(_:));

@property (nonatomic,readwrite,assign,getter=SSLAcceptServerCertEncodedB,setter=setSSLAcceptServerCertEncodedB:) NSData* SSLAcceptServerCertEncodedB NS_SWIFT_NAME(SSLAcceptServerCertEncodedB);
- (NSData*)SSLAcceptServerCertEncodedB NS_SWIFT_NAME(SSLAcceptServerCertEncodedB());
- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded NS_SWIFT_NAME(setSSLAcceptServerCertEncodedB(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertEncoded,setter=setSSLCertEncoded:) NSString* SSLCertEncoded NS_SWIFT_NAME(SSLCertEncoded);
- (NSString*)SSLCertEncoded NS_SWIFT_NAME(SSLCertEncoded());
- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded NS_SWIFT_NAME(setSSLCertEncoded(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertEncodedB,setter=setSSLCertEncodedB:) NSData* SSLCertEncodedB NS_SWIFT_NAME(SSLCertEncodedB);
- (NSData*)SSLCertEncodedB NS_SWIFT_NAME(SSLCertEncodedB());
- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded NS_SWIFT_NAME(setSSLCertEncodedB(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertStore,setter=setSSLCertStore:) NSString* SSLCertStore NS_SWIFT_NAME(SSLCertStore);
- (NSString*)SSLCertStore NS_SWIFT_NAME(SSLCertStore());
- (void)setSSLCertStore:(NSString*)newSSLCertStore NS_SWIFT_NAME(setSSLCertStore(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertStoreB,setter=setSSLCertStoreB:) NSData* SSLCertStoreB NS_SWIFT_NAME(SSLCertStoreB);
- (NSData*)SSLCertStoreB NS_SWIFT_NAME(SSLCertStoreB());
- (void)setSSLCertStoreB :(NSData*)newSSLCertStore NS_SWIFT_NAME(setSSLCertStoreB(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertStorePassword,setter=setSSLCertStorePassword:) NSString* SSLCertStorePassword NS_SWIFT_NAME(SSLCertStorePassword);
- (NSString*)SSLCertStorePassword NS_SWIFT_NAME(SSLCertStorePassword());
- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword NS_SWIFT_NAME(setSSLCertStorePassword(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertStoreType,setter=setSSLCertStoreType:) int SSLCertStoreType NS_SWIFT_NAME(SSLCertStoreType);
- (int)SSLCertStoreType NS_SWIFT_NAME(SSLCertStoreType());
- (void)setSSLCertStoreType:(int)newSSLCertStoreType NS_SWIFT_NAME(setSSLCertStoreType(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertSubject,setter=setSSLCertSubject:) NSString* SSLCertSubject NS_SWIFT_NAME(SSLCertSubject);
- (NSString*)SSLCertSubject NS_SWIFT_NAME(SSLCertSubject());
- (void)setSSLCertSubject:(NSString*)newSSLCertSubject NS_SWIFT_NAME(setSSLCertSubject(_:));

@property (nonatomic,readwrite,assign,getter=SSLEnabled,setter=setSSLEnabled:) BOOL SSLEnabled NS_SWIFT_NAME(SSLEnabled);
- (BOOL)SSLEnabled NS_SWIFT_NAME(SSLEnabled());
- (void)setSSLEnabled:(BOOL)newSSLEnabled NS_SWIFT_NAME(setSSLEnabled(_:));

@property (nonatomic,readonly,assign,getter=SSLServerCertEncoded) NSString* SSLServerCertEncoded NS_SWIFT_NAME(SSLServerCertEncoded);
- (NSString*)SSLServerCertEncoded NS_SWIFT_NAME(SSLServerCertEncoded());

@property (nonatomic,readonly,assign,getter=SSLServerCertEncodedB) NSData* SSLServerCertEncodedB NS_SWIFT_NAME(SSLServerCertEncodedB);
- (NSData*)SSLServerCertEncodedB NS_SWIFT_NAME(SSLServerCertEncodedB());

@property (nonatomic,readwrite,assign,getter=SSLStartMode,setter=setSSLStartMode:) int SSLStartMode NS_SWIFT_NAME(SSLStartMode);
- (int)SSLStartMode NS_SWIFT_NAME(SSLStartMode());
- (void)setSSLStartMode:(int)newSSLStartMode NS_SWIFT_NAME(setSSLStartMode(_:));

@property (nonatomic,readwrite,assign,getter=systemType,setter=setSystemType:) NSString* systemType NS_SWIFT_NAME(systemType);
- (NSString*)systemType NS_SWIFT_NAME(systemType());
- (void)setSystemType:(NSString*)newSystemType NS_SWIFT_NAME(setSystemType(_:));

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

@property (nonatomic,readwrite,assign,getter=userId,setter=setUserId:) NSString* userId NS_SWIFT_NAME(userId);
- (NSString*)userId NS_SWIFT_NAME(userId());
- (void)setUserId:(NSString*)newUserId NS_SWIFT_NAME(setUserId(_:));

  /* Methods */

- (void)addRecipient:(int)recipientType :(NSString*)recipientAddress NS_SWIFT_NAME(addRecipient(_:_:));
- (void)cancelMessage:(NSString*)messageId NS_SWIFT_NAME(cancelMessage(_:));
- (void)checkLink NS_SWIFT_NAME(checkLink());
- (void)checkMessageStatus:(NSString*)messageId NS_SWIFT_NAME(checkMessageStatus(_:));
- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)connect:(NSString*)userId :(NSString*)password NS_SWIFT_NAME(connect(_:_:));
- (void)disconnect NS_SWIFT_NAME(disconnect());
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)replaceMessage:(NSString*)messageId :(NSString*)newMessage NS_SWIFT_NAME(replaceMessage(_:_:));
- (void)reset NS_SWIFT_NAME(reset());
- (NSData*)sendCommand:(int)commandId :(NSData*)payload NS_SWIFT_NAME(sendCommand(_:_:));
- (NSString*)sendData:(NSData*)data NS_SWIFT_NAME(sendData(_:));
- (NSString*)sendMessage:(NSString*)message NS_SWIFT_NAME(sendMessage(_:));

@end


