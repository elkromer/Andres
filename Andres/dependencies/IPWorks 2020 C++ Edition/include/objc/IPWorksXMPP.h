
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//XMPPBUDDYSUBSCRIPTIONS
#define ST_NONE                                            0
#define ST_TO                                              1
#define ST_FROM                                            2
#define ST_BOTH                                            3
#define ST_REMOVE                                          4

//FIREWALLTYPES
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TJABBERMESSAGETYPES
#define MT_NORMAL                                          0
#define MT_CHAT                                            1
#define MT_GROUP_CHAT                                      2
#define MT_HEADLINE                                        3
#define MT_ERROR                                           4

//TJABBERPRESENCECODES
#define PC_OFFLINE                                         0
#define PC_CHAT                                            1
#define PC_AWAY                                            2
#define PC_XA                                              3
#define PC_DND                                             4

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

@protocol IPWorksXMPPDelegate <NSObject>
@optional
- (void)onBuddyUpdate:(int)buddyIdx NS_SWIFT_NAME(onBuddyUpdate(_:));
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndTransfer:(int)direction :(NSString*)fileId :(NSString*)filename :(BOOL)success NS_SWIFT_NAME(onEndTransfer(_:_:_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onIQ:(NSString*)iq :(NSString*)id :(NSString*)from :(NSString*)iqType :(int*)ignore NS_SWIFT_NAME(onIQ(_:_:_:_:_:));
- (void)onMessageIn:(NSString*)messageId :(NSString*)from :(NSString*)domain :(NSString*)resource :(int)messageType :(NSString*)subject :(NSString*)messageThread :(NSString*)messageText :(NSString*)messageHTML :(NSString*)other NS_SWIFT_NAME(onMessageIn(_:_:_:_:_:_:_:_:_:_:));
- (void)onPITrail:(int)direction :(NSString*)pi NS_SWIFT_NAME(onPITrail(_:_:));
- (void)onPresence:(NSString*)user :(NSString*)domain :(NSString*)resource :(int)availability :(NSString*)status NS_SWIFT_NAME(onPresence(_:_:_:_:_:));
- (void)onReadyToSend NS_SWIFT_NAME(onReadyToSend());
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction :(NSString*)fileId :(NSString*)user :(NSString*)domain :(NSString*)resource :(NSString**)filename :(NSString*)datetime :(long long)size :(int*)accept NS_SWIFT_NAME(onStartTransfer(_:_:_:_:_:_:_:_:_:));
- (void)onSubscriptionRequest:(NSString*)from :(NSString*)domain :(int*)accept NS_SWIFT_NAME(onSubscriptionRequest(_:_:_:));
- (void)onSync NS_SWIFT_NAME(onSync());
- (void)onTransfer:(int)direction :(NSString*)fileId :(NSString*)filename :(long long)bytesTransferred :(int)percentDone :(NSData*)text :(int*)cancel NS_SWIFT_NAME(onTransfer(_:_:_:_:_:_:_:));
@end

@interface IPWorksXMPP : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksXMPPDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasBuddyUpdate;
  BOOL m_delegateHasConnected;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasDisconnected;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasError;
  BOOL m_delegateHasIQ;
  BOOL m_delegateHasMessageIn;
  BOOL m_delegateHasPITrail;
  BOOL m_delegateHasPresence;
  BOOL m_delegateHasReadyToSend;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
  BOOL m_delegateHasStartTransfer;
  BOOL m_delegateHasSubscriptionRequest;
  BOOL m_delegateHasSync;
  BOOL m_delegateHasTransfer;
}

+ (IPWorksXMPP*)xmpp;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksXMPPDelegate> delegate;
- (id <IPWorksXMPPDelegate>)delegate;
- (void) setDelegate:(id <IPWorksXMPPDelegate>)anObject;

  /* Events */

- (void)onBuddyUpdate:(int)buddyIdx NS_SWIFT_NAME(onBuddyUpdate(_:));
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndTransfer:(int)direction :(NSString*)fileId :(NSString*)filename :(BOOL)success NS_SWIFT_NAME(onEndTransfer(_:_:_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onIQ:(NSString*)iq :(NSString*)id :(NSString*)from :(NSString*)iqType :(int*)ignore NS_SWIFT_NAME(onIQ(_:_:_:_:_:));
- (void)onMessageIn:(NSString*)messageId :(NSString*)from :(NSString*)domain :(NSString*)resource :(int)messageType :(NSString*)subject :(NSString*)messageThread :(NSString*)messageText :(NSString*)messageHTML :(NSString*)other NS_SWIFT_NAME(onMessageIn(_:_:_:_:_:_:_:_:_:_:));
- (void)onPITrail:(int)direction :(NSString*)pi NS_SWIFT_NAME(onPITrail(_:_:));
- (void)onPresence:(NSString*)user :(NSString*)domain :(NSString*)resource :(int)availability :(NSString*)status NS_SWIFT_NAME(onPresence(_:_:_:_:_:));
- (void)onReadyToSend NS_SWIFT_NAME(onReadyToSend());
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction :(NSString*)fileId :(NSString*)user :(NSString*)domain :(NSString*)resource :(NSString**)filename :(NSString*)datetime :(long long)size :(int*)accept NS_SWIFT_NAME(onStartTransfer(_:_:_:_:_:_:_:_:_:));
- (void)onSubscriptionRequest:(NSString*)from :(NSString*)domain :(int*)accept NS_SWIFT_NAME(onSubscriptionRequest(_:_:_:));
- (void)onSync NS_SWIFT_NAME(onSync());
- (void)onTransfer:(int)direction :(NSString*)fileId :(NSString*)filename :(long long)bytesTransferred :(int)percentDone :(NSData*)text :(int*)cancel NS_SWIFT_NAME(onTransfer(_:_:_:_:_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=authDomain,setter=setAuthDomain:) NSString* authDomain NS_SWIFT_NAME(authDomain);
- (NSString*)authDomain NS_SWIFT_NAME(authDomain());
- (void)setAuthDomain:(NSString*)newAuthDomain NS_SWIFT_NAME(setAuthDomain(_:));

@property (nonatomic,readwrite,assign,getter=authMethods,setter=setAuthMethods:) NSString* authMethods NS_SWIFT_NAME(authMethods);
- (NSString*)authMethods NS_SWIFT_NAME(authMethods());
- (void)setAuthMethods:(NSString*)newAuthMethods NS_SWIFT_NAME(setAuthMethods(_:));

@property (nonatomic,readonly,assign,getter=buddyCount) int buddyCount NS_SWIFT_NAME(buddyCount);
- (int)buddyCount NS_SWIFT_NAME(buddyCount());

- (NSString*)buddyGroup:(int)buddyIndex NS_SWIFT_NAME(buddyGroup(_:));
- (void)setBuddyGroup:(int)buddyIndex:(NSString*)newBuddyGroup NS_SWIFT_NAME(setBuddyGroup(_:_:));

- (NSString*)buddyId:(int)buddyIndex NS_SWIFT_NAME(buddyId(_:));

- (NSString*)buddyNickName:(int)buddyIndex NS_SWIFT_NAME(buddyNickName(_:));
- (void)setBuddyNickName:(int)buddyIndex:(NSString*)newBuddyNickName NS_SWIFT_NAME(setBuddyNickName(_:_:));

- (NSString*)buddyRealName:(int)buddyIndex NS_SWIFT_NAME(buddyRealName(_:));

- (int)buddySubscription:(int)buddyIndex NS_SWIFT_NAME(buddySubscription(_:));

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

@property (nonatomic,readwrite,assign,getter=IMPort,setter=setIMPort:) int IMPort NS_SWIFT_NAME(IMPort);
- (int)IMPort NS_SWIFT_NAME(IMPort());
- (void)setIMPort:(int)newIMPort NS_SWIFT_NAME(setIMPort(_:));

@property (nonatomic,readwrite,assign,getter=IMServer,setter=setIMServer:) NSString* IMServer NS_SWIFT_NAME(IMServer);
- (NSString*)IMServer NS_SWIFT_NAME(IMServer());
- (void)setIMServer:(NSString*)newIMServer NS_SWIFT_NAME(setIMServer(_:));

@property (nonatomic,readwrite,assign,getter=localDirectory,setter=setLocalDirectory:) NSString* localDirectory NS_SWIFT_NAME(localDirectory);
- (NSString*)localDirectory NS_SWIFT_NAME(localDirectory());
- (void)setLocalDirectory:(NSString*)newLocalDirectory NS_SWIFT_NAME(setLocalDirectory(_:));

@property (nonatomic,readwrite,assign,getter=localFile,setter=setLocalFile:) NSString* localFile NS_SWIFT_NAME(localFile);
- (NSString*)localFile NS_SWIFT_NAME(localFile());
- (void)setLocalFile:(NSString*)newLocalFile NS_SWIFT_NAME(setLocalFile(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=messageHTML,setter=setMessageHTML:) NSString* messageHTML NS_SWIFT_NAME(messageHTML);
- (NSString*)messageHTML NS_SWIFT_NAME(messageHTML());
- (void)setMessageHTML:(NSString*)newMessageHTML NS_SWIFT_NAME(setMessageHTML(_:));

@property (nonatomic,readwrite,assign,getter=messageOtherData,setter=setMessageOtherData:) NSString* messageOtherData NS_SWIFT_NAME(messageOtherData);
- (NSString*)messageOtherData NS_SWIFT_NAME(messageOtherData());
- (void)setMessageOtherData:(NSString*)newMessageOtherData NS_SWIFT_NAME(setMessageOtherData(_:));

@property (nonatomic,readwrite,assign,getter=messageSubject,setter=setMessageSubject:) NSString* messageSubject NS_SWIFT_NAME(messageSubject);
- (NSString*)messageSubject NS_SWIFT_NAME(messageSubject());
- (void)setMessageSubject:(NSString*)newMessageSubject NS_SWIFT_NAME(setMessageSubject(_:));

@property (nonatomic,readwrite,assign,getter=messageText,setter=setMessageText:) NSString* messageText NS_SWIFT_NAME(messageText);
- (NSString*)messageText NS_SWIFT_NAME(messageText());
- (void)setMessageText:(NSString*)newMessageText NS_SWIFT_NAME(setMessageText(_:));

@property (nonatomic,readwrite,assign,getter=messageThread,setter=setMessageThread:) NSString* messageThread NS_SWIFT_NAME(messageThread);
- (NSString*)messageThread NS_SWIFT_NAME(messageThread());
- (void)setMessageThread:(NSString*)newMessageThread NS_SWIFT_NAME(setMessageThread(_:));

@property (nonatomic,readwrite,assign,getter=messageType,setter=setMessageType:) int messageType NS_SWIFT_NAME(messageType);
- (int)messageType NS_SWIFT_NAME(messageType());
- (void)setMessageType:(int)newMessageType NS_SWIFT_NAME(setMessageType(_:));

@property (nonatomic,readwrite,assign,getter=password,setter=setPassword:) NSString* password NS_SWIFT_NAME(password);
- (NSString*)password NS_SWIFT_NAME(password());
- (void)setPassword:(NSString*)newPassword NS_SWIFT_NAME(setPassword(_:));

@property (nonatomic,readwrite,assign,getter=presence,setter=setPresence:) int presence NS_SWIFT_NAME(presence);
- (int)presence NS_SWIFT_NAME(presence());
- (void)setPresence:(int)newPresence NS_SWIFT_NAME(setPresence(_:));

@property (nonatomic,readwrite,assign,getter=resource,setter=setResource:) NSString* resource NS_SWIFT_NAME(resource);
- (NSString*)resource NS_SWIFT_NAME(resource());
- (void)setResource:(NSString*)newResource NS_SWIFT_NAME(setResource(_:));

@property (nonatomic,readwrite,assign,getter=serverDomain,setter=setServerDomain:) NSString* serverDomain NS_SWIFT_NAME(serverDomain);
- (NSString*)serverDomain NS_SWIFT_NAME(serverDomain());
- (void)setServerDomain:(NSString*)newServerDomain NS_SWIFT_NAME(setServerDomain(_:));

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

@property (nonatomic,readwrite,assign,getter=status,setter=setStatus:) NSString* status NS_SWIFT_NAME(status);
- (NSString*)status NS_SWIFT_NAME(status());
- (void)setStatus:(NSString*)newStatus NS_SWIFT_NAME(setStatus(_:));

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

@property (nonatomic,readwrite,assign,getter=user,setter=setUser:) NSString* user NS_SWIFT_NAME(user);
- (NSString*)user NS_SWIFT_NAME(user());
- (void)setUser:(NSString*)newUser NS_SWIFT_NAME(setUser(_:));

@property (nonatomic,readwrite,assign,getter=userDomain,setter=setUserDomain:) NSString* userDomain NS_SWIFT_NAME(userDomain);
- (NSString*)userDomain NS_SWIFT_NAME(userDomain());
- (void)setUserDomain:(NSString*)newUserDomain NS_SWIFT_NAME(setUserDomain(_:));

@property (nonatomic,readwrite,assign,getter=userInfoCount,setter=setUserInfoCount:) int userInfoCount NS_SWIFT_NAME(userInfoCount);
- (int)userInfoCount NS_SWIFT_NAME(userInfoCount());
- (void)setUserInfoCount:(int)newUserInfoCount NS_SWIFT_NAME(setUserInfoCount(_:));

- (NSString*)userInfoField:(int)fieldIndex NS_SWIFT_NAME(userInfoField(_:));
- (void)setUserInfoField:(int)fieldIndex:(NSString*)newUserInfoField NS_SWIFT_NAME(setUserInfoField(_:_:));

- (NSString*)userInfoValue:(int)fieldIndex NS_SWIFT_NAME(userInfoValue(_:));
- (void)setUserInfoValue:(int)fieldIndex:(NSString*)newUserInfoValue NS_SWIFT_NAME(setUserInfoValue(_:_:));

  /* Methods */

- (void)add:(NSString*)jabberId :(NSString*)name :(NSString*)groups NS_SWIFT_NAME(add(_:_:_:));
- (void)cancel:(NSString*)jabberId NS_SWIFT_NAME(cancel(_:));
- (void)changePassword:(NSString*)password NS_SWIFT_NAME(changePassword(_:));
- (void)changePresence:(int)presenceCode :(NSString*)status NS_SWIFT_NAME(changePresence(_:_:));
- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)connect:(NSString*)user :(NSString*)password NS_SWIFT_NAME(connect(_:_:));
- (void)disconnect NS_SWIFT_NAME(disconnect());
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)probePresence:(NSString*)jabberId NS_SWIFT_NAME(probePresence(_:));
- (void)queryRegister:(NSString*)XMPPServer NS_SWIFT_NAME(queryRegister(_:));
- (void)registerUser:(NSString*)XMPPServer NS_SWIFT_NAME(registerUser(_:));
- (void)remove:(NSString*)jabberId :(NSString*)name :(NSString*)group NS_SWIFT_NAME(remove(_:_:_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)retrieveRoster NS_SWIFT_NAME(retrieveRoster());
- (void)sendCommand:(NSString*)command NS_SWIFT_NAME(sendCommand(_:));
- (void)sendFile:(NSString*)jabberId NS_SWIFT_NAME(sendFile(_:));
- (NSString*)sendMessage:(NSString*)jabberId NS_SWIFT_NAME(sendMessage(_:));
- (void)setUserInfo:(NSString*)field :(NSString*)value NS_SWIFT_NAME(setUserInfo(_:_:));
- (void)subscribeTo:(NSString*)jabberId NS_SWIFT_NAME(subscribeTo(_:));
- (void)unregister NS_SWIFT_NAME(unregister());
- (void)unsubscribeTo:(NSString*)jabberId NS_SWIFT_NAME(unsubscribeTo(_:));

@end


