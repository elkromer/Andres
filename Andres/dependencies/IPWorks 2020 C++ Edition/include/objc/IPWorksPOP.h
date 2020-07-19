
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//AUTHMECHANISMS
#define AM_USER_PASSWORD                                   0
#define AM_CRAMMD5                                         1
#define AM_NTLM                                            2
#define AM_APOP                                            3
#define AM_SASLPLAIN                                       4
#define AM_SASLDIGEST_MD5                                  5
#define AM_KERBEROS                                        6
#define AM_XOAUTH2                                         7

//FIREWALLTYPES
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//EMAILRECIPIENTTYPES
#define RT_TO                                              0
#define RT_CC                                              1
#define RT_BCC                                             2

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

@protocol IPWorksPOPDelegate <NSObject>
@optional
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onMessageList:(int)messageNumber :(NSString*)messageUID :(int)messageSize NS_SWIFT_NAME(onMessageList(_:_:_:));
- (void)onPITrail:(int)direction :(NSString*)message NS_SWIFT_NAME(onPITrail(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text :(BOOL)EOL NS_SWIFT_NAME(onTransfer(_:_:_:_:_:));
@end

@interface IPWorksPOP : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksPOPDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasError;
  BOOL m_delegateHasHeader;
  BOOL m_delegateHasMessageList;
  BOOL m_delegateHasPITrail;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
  BOOL m_delegateHasStartTransfer;
  BOOL m_delegateHasTransfer;
}

+ (IPWorksPOP*)pop;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksPOPDelegate> delegate;
- (id <IPWorksPOPDelegate>)delegate;
- (void) setDelegate:(id <IPWorksPOPDelegate>)anObject;

  /* Events */

- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onMessageList:(int)messageNumber :(NSString*)messageUID :(int)messageSize NS_SWIFT_NAME(onMessageList(_:_:_:));
- (void)onPITrail:(int)direction :(NSString*)message NS_SWIFT_NAME(onPITrail(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text :(BOOL)EOL NS_SWIFT_NAME(onTransfer(_:_:_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=authMechanism,setter=setAuthMechanism:) int authMechanism NS_SWIFT_NAME(authMechanism);
- (int)authMechanism NS_SWIFT_NAME(authMechanism());
- (void)setAuthMechanism:(int)newAuthMechanism NS_SWIFT_NAME(setAuthMechanism(_:));

@property (nonatomic,readwrite,assign,getter=command,setter=setCommand:) NSString* command NS_SWIFT_NAME(command);
- (NSString*)command NS_SWIFT_NAME(command());
- (void)setCommand:(NSString*)newCommand NS_SWIFT_NAME(setCommand(_:));

@property (nonatomic,readwrite,assign,getter=connected,setter=setConnected:) BOOL connected NS_SWIFT_NAME(connected);
- (BOOL)connected NS_SWIFT_NAME(connected());
- (void)setConnected:(BOOL)newConnected NS_SWIFT_NAME(setConnected(_:));

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

@property (nonatomic,readwrite,assign,getter=includeHeaders,setter=setIncludeHeaders:) BOOL includeHeaders NS_SWIFT_NAME(includeHeaders);
- (BOOL)includeHeaders NS_SWIFT_NAME(includeHeaders());
- (void)setIncludeHeaders:(BOOL)newIncludeHeaders NS_SWIFT_NAME(setIncludeHeaders(_:));

@property (nonatomic,readonly,assign,getter=lastReply) NSString* lastReply NS_SWIFT_NAME(lastReply);
- (NSString*)lastReply NS_SWIFT_NAME(lastReply());

@property (nonatomic,readwrite,assign,getter=localFile,setter=setLocalFile:) NSString* localFile NS_SWIFT_NAME(localFile);
- (NSString*)localFile NS_SWIFT_NAME(localFile());
- (void)setLocalFile:(NSString*)newLocalFile NS_SWIFT_NAME(setLocalFile(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=mailPort,setter=setMailPort:) int mailPort NS_SWIFT_NAME(mailPort);
- (int)mailPort NS_SWIFT_NAME(mailPort());
- (void)setMailPort:(int)newMailPort NS_SWIFT_NAME(setMailPort(_:));

@property (nonatomic,readwrite,assign,getter=mailServer,setter=setMailServer:) NSString* mailServer NS_SWIFT_NAME(mailServer);
- (NSString*)mailServer NS_SWIFT_NAME(mailServer());
- (void)setMailServer:(NSString*)newMailServer NS_SWIFT_NAME(setMailServer(_:));

@property (nonatomic,readwrite,assign,getter=maxLines,setter=setMaxLines:) int maxLines NS_SWIFT_NAME(maxLines);
- (int)maxLines NS_SWIFT_NAME(maxLines());
- (void)setMaxLines:(int)newMaxLines NS_SWIFT_NAME(setMaxLines(_:));

@property (nonatomic,readonly,assign,getter=message) NSString* message NS_SWIFT_NAME(message);
- (NSString*)message NS_SWIFT_NAME(message());

@property (nonatomic,readonly,assign,getter=messageB) NSData* messageB NS_SWIFT_NAME(messageB);
- (NSData*)messageB NS_SWIFT_NAME(messageB());

@property (nonatomic,readonly,assign,getter=messageCc) NSString* messageCc NS_SWIFT_NAME(messageCc);
- (NSString*)messageCc NS_SWIFT_NAME(messageCc());

@property (nonatomic,readonly,assign,getter=messageCount) int messageCount NS_SWIFT_NAME(messageCount);
- (int)messageCount NS_SWIFT_NAME(messageCount());

@property (nonatomic,readonly,assign,getter=messageDate) NSString* messageDate NS_SWIFT_NAME(messageDate);
- (NSString*)messageDate NS_SWIFT_NAME(messageDate());

@property (nonatomic,readonly,assign,getter=messageFrom) NSString* messageFrom NS_SWIFT_NAME(messageFrom);
- (NSString*)messageFrom NS_SWIFT_NAME(messageFrom());

@property (nonatomic,readonly,assign,getter=messageHeaderCount) int messageHeaderCount NS_SWIFT_NAME(messageHeaderCount);
- (int)messageHeaderCount NS_SWIFT_NAME(messageHeaderCount());

- (NSString*)messageHeaderField:(int)messageHeaderIndex NS_SWIFT_NAME(messageHeaderField(_:));

- (NSString*)messageHeaderValue:(int)messageHeaderIndex NS_SWIFT_NAME(messageHeaderValue(_:));

@property (nonatomic,readonly,assign,getter=messageHeadersString) NSString* messageHeadersString NS_SWIFT_NAME(messageHeadersString);
- (NSString*)messageHeadersString NS_SWIFT_NAME(messageHeadersString());

@property (nonatomic,readwrite,assign,getter=messageNumber,setter=setMessageNumber:) int messageNumber NS_SWIFT_NAME(messageNumber);
- (int)messageNumber NS_SWIFT_NAME(messageNumber());
- (void)setMessageNumber:(int)newMessageNumber NS_SWIFT_NAME(setMessageNumber(_:));

@property (nonatomic,readonly,assign,getter=messageRecipientCount) int messageRecipientCount NS_SWIFT_NAME(messageRecipientCount);
- (int)messageRecipientCount NS_SWIFT_NAME(messageRecipientCount());

- (NSString*)messageRecipientAddress:(int)recipientIndex NS_SWIFT_NAME(messageRecipientAddress(_:));

- (NSString*)messageRecipientName:(int)recipientIndex NS_SWIFT_NAME(messageRecipientName(_:));

- (NSString*)messageRecipientOptions:(int)recipientIndex NS_SWIFT_NAME(messageRecipientOptions(_:));

- (int)messageRecipientType:(int)recipientIndex NS_SWIFT_NAME(messageRecipientType(_:));

@property (nonatomic,readonly,assign,getter=messageReplyTo) NSString* messageReplyTo NS_SWIFT_NAME(messageReplyTo);
- (NSString*)messageReplyTo NS_SWIFT_NAME(messageReplyTo());

@property (nonatomic,readonly,assign,getter=messageSize) int messageSize NS_SWIFT_NAME(messageSize);
- (int)messageSize NS_SWIFT_NAME(messageSize());

@property (nonatomic,readonly,assign,getter=messageSubject) NSString* messageSubject NS_SWIFT_NAME(messageSubject);
- (NSString*)messageSubject NS_SWIFT_NAME(messageSubject());

@property (nonatomic,readonly,assign,getter=messageText) NSString* messageText NS_SWIFT_NAME(messageText);
- (NSString*)messageText NS_SWIFT_NAME(messageText());

@property (nonatomic,readonly,assign,getter=messageTo) NSString* messageTo NS_SWIFT_NAME(messageTo);
- (NSString*)messageTo NS_SWIFT_NAME(messageTo());

@property (nonatomic,readonly,assign,getter=messageUID) NSString* messageUID NS_SWIFT_NAME(messageUID);
- (NSString*)messageUID NS_SWIFT_NAME(messageUID());

@property (nonatomic,readwrite,assign,getter=password,setter=setPassword:) NSString* password NS_SWIFT_NAME(password);
- (NSString*)password NS_SWIFT_NAME(password());
- (void)setPassword:(NSString*)newPassword NS_SWIFT_NAME(setPassword(_:));

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

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

@property (nonatomic,readonly,assign,getter=totalSize) long long totalSize NS_SWIFT_NAME(totalSize);
- (long long)totalSize NS_SWIFT_NAME(totalSize());

@property (nonatomic,readwrite,assign,getter=user,setter=setUser:) NSString* user NS_SWIFT_NAME(user);
- (NSString*)user NS_SWIFT_NAME(user());
- (void)setUser:(NSString*)newUser NS_SWIFT_NAME(setUser(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)connect NS_SWIFT_NAME(connect());
- (void)delete NS_SWIFT_NAME(delete());
- (void)disconnect NS_SWIFT_NAME(disconnect());
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)listMessageSizes NS_SWIFT_NAME(listMessageSizes());
- (void)listMessageUIDs NS_SWIFT_NAME(listMessageUIDs());
- (NSString*)localizeDate:(NSString*)dateTime NS_SWIFT_NAME(localizeDate(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)retrieve NS_SWIFT_NAME(retrieve());
- (void)retrieveHeaders NS_SWIFT_NAME(retrieveHeaders());

@end


