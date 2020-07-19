
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

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

@protocol IPWorksIPDaemonDelegate <NSObject>
@optional
- (void)onConnected:(int)connectionId :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:_:));
- (void)onConnectionRequest:(NSString*)address :(int)port :(int*)accept NS_SWIFT_NAME(onConnectionRequest(_:_:_:));
- (void)onDataIn:(int)connectionId :(NSData*)text :(BOOL)EOL NS_SWIFT_NAME(onDataIn(_:_:_:));
- (void)onDisconnected:(int)connectionId :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:_:));
- (void)onError:(int)connectionId :(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:_:));
- (void)onReadyToSend:(int)connectionId NS_SWIFT_NAME(onReadyToSend(_:));
- (void)onSSLClientAuthentication:(int)connectionId :(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLClientAuthentication(_:_:_:_:_:_:));
- (void)onSSLConnectionRequest:(int)connectionId :(NSString*)supportedCipherSuites :(NSString*)supportedSignatureAlgs :(int*)certStoreType :(NSString**)certStore :(NSString**)certPassword :(NSString**)certSubject NS_SWIFT_NAME(onSSLConnectionRequest(_:_:_:_:_:_:_:));
- (void)onSSLStatus:(int)connectionId :(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:_:));
@end

@interface IPWorksIPDaemon : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksIPDaemonDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnected;
  BOOL m_delegateHasConnectionRequest;
  BOOL m_delegateHasDataIn;
  BOOL m_delegateHasDisconnected;
  BOOL m_delegateHasError;
  BOOL m_delegateHasReadyToSend;
  BOOL m_delegateHasSSLClientAuthentication;
  BOOL m_delegateHasSSLConnectionRequest;
  BOOL m_delegateHasSSLStatus;
}

+ (IPWorksIPDaemon*)ipdaemon;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksIPDaemonDelegate> delegate;
- (id <IPWorksIPDaemonDelegate>)delegate;
- (void) setDelegate:(id <IPWorksIPDaemonDelegate>)anObject;

  /* Events */

- (void)onConnected:(int)connectionId :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:_:));
- (void)onConnectionRequest:(NSString*)address :(int)port :(int*)accept NS_SWIFT_NAME(onConnectionRequest(_:_:_:));
- (void)onDataIn:(int)connectionId :(NSData*)text :(BOOL)EOL NS_SWIFT_NAME(onDataIn(_:_:_:));
- (void)onDisconnected:(int)connectionId :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:_:));
- (void)onError:(int)connectionId :(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:_:));
- (void)onReadyToSend:(int)connectionId NS_SWIFT_NAME(onReadyToSend(_:));
- (void)onSSLClientAuthentication:(int)connectionId :(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLClientAuthentication(_:_:_:_:_:_:));
- (void)onSSLConnectionRequest:(int)connectionId :(NSString*)supportedCipherSuites :(NSString*)supportedSignatureAlgs :(int*)certStoreType :(NSString**)certStore :(NSString**)certPassword :(NSString**)certSubject NS_SWIFT_NAME(onSSLConnectionRequest(_:_:_:_:_:_:_:));
- (void)onSSLStatus:(int)connectionId :(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=connectionBacklog,setter=setConnectionBacklog:) int connectionBacklog NS_SWIFT_NAME(connectionBacklog);
- (int)connectionBacklog NS_SWIFT_NAME(connectionBacklog());
- (void)setConnectionBacklog:(int)newConnectionBacklog NS_SWIFT_NAME(setConnectionBacklog(_:));

@property (nonatomic,readonly,assign,getter=connectionCount) int connectionCount NS_SWIFT_NAME(connectionCount);
- (int)connectionCount NS_SWIFT_NAME(connectionCount());

- (BOOL)acceptData:(int)connectionId NS_SWIFT_NAME(acceptData(_:));
- (void)setAcceptData:(int)connectionId:(BOOL)newAcceptData NS_SWIFT_NAME(setAcceptData(_:_:));

- (int)bytesSent:(int)connectionId NS_SWIFT_NAME(bytesSent(_:));

- (BOOL)connected:(int)connectionId NS_SWIFT_NAME(connected(_:));
- (void)setConnected:(int)connectionId:(BOOL)newConnected NS_SWIFT_NAME(setConnected(_:_:));

- (NSString*)connectionId:(int)connectionId NS_SWIFT_NAME(connectionId(_:));

- (NSString*)dataToSend:(int)connectionId NS_SWIFT_NAME(dataToSend(_:));
- (void)setDataToSend:(int)connectionId:(NSString*)newDataToSend NS_SWIFT_NAME(setDataToSend(_:_:));

- (NSData*)dataToSendB:(int)connectionId NS_SWIFT_NAME(dataToSendB(_:));
- (void)setDataToSendB:(int)connectionId :(NSData*)newDataToSend NS_SWIFT_NAME(setDataToSendB(_:_:));

- (NSString*)EOL:(int)connectionId NS_SWIFT_NAME(EOL(_:));
- (void)setEOL:(int)connectionId:(NSString*)newEOL NS_SWIFT_NAME(setEOL(_:_:));

- (NSData*)EOLB:(int)connectionId NS_SWIFT_NAME(EOLB(_:));
- (void)setEOLB:(int)connectionId :(NSData*)newEOL NS_SWIFT_NAME(setEOLB(_:_:));

- (int)idleTimeout:(int)connectionId NS_SWIFT_NAME(idleTimeout(_:));
- (void)setIdleTimeout:(int)connectionId:(int)newIdleTimeout NS_SWIFT_NAME(setIdleTimeout(_:_:));

- (NSString*)localAddress:(int)connectionId NS_SWIFT_NAME(localAddress(_:));

- (BOOL)readyToSend:(int)connectionId NS_SWIFT_NAME(readyToSend(_:));

- (int)recordLength:(int)connectionId NS_SWIFT_NAME(recordLength(_:));
- (void)setRecordLength:(int)connectionId:(int)newRecordLength NS_SWIFT_NAME(setRecordLength(_:_:));

- (NSString*)remoteHost:(int)connectionId NS_SWIFT_NAME(remoteHost(_:));

- (int)remotePort:(int)connectionId NS_SWIFT_NAME(remotePort(_:));

- (BOOL)singleLineMode:(int)connectionId NS_SWIFT_NAME(singleLineMode(_:));
- (void)setSingleLineMode:(int)connectionId:(BOOL)newSingleLineMode NS_SWIFT_NAME(setSingleLineMode(_:_:));

- (int)timeout:(int)connectionId NS_SWIFT_NAME(timeout(_:));
- (void)setTimeout:(int)connectionId:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:_:));

- (NSString*)userData:(int)connectionId NS_SWIFT_NAME(userData(_:));
- (void)setUserData:(int)connectionId:(NSString*)newUserData NS_SWIFT_NAME(setUserData(_:_:));

- (NSData*)userDataB:(int)connectionId NS_SWIFT_NAME(userDataB(_:));
- (void)setUserDataB:(int)connectionId :(NSData*)newUserData NS_SWIFT_NAME(setUserDataB(_:_:));

@property (nonatomic,readwrite,assign,getter=defaultEOL,setter=setDefaultEOL:) NSString* defaultEOL NS_SWIFT_NAME(defaultEOL);
- (NSString*)defaultEOL NS_SWIFT_NAME(defaultEOL());
- (void)setDefaultEOL:(NSString*)newDefaultEOL NS_SWIFT_NAME(setDefaultEOL(_:));

@property (nonatomic,readwrite,assign,getter=defaultEOLB,setter=setDefaultEOLB:) NSData* defaultEOLB NS_SWIFT_NAME(defaultEOLB);
- (NSData*)defaultEOLB NS_SWIFT_NAME(defaultEOLB());
- (void)setDefaultEOLB :(NSData*)newDefaultEOL NS_SWIFT_NAME(setDefaultEOLB(_:));

@property (nonatomic,readwrite,assign,getter=defaultIdleTimeout,setter=setDefaultIdleTimeout:) int defaultIdleTimeout NS_SWIFT_NAME(defaultIdleTimeout);
- (int)defaultIdleTimeout NS_SWIFT_NAME(defaultIdleTimeout());
- (void)setDefaultIdleTimeout:(int)newDefaultIdleTimeout NS_SWIFT_NAME(setDefaultIdleTimeout(_:));

@property (nonatomic,readwrite,assign,getter=defaultMaxLineLength,setter=setDefaultMaxLineLength:) int defaultMaxLineLength NS_SWIFT_NAME(defaultMaxLineLength);
- (int)defaultMaxLineLength NS_SWIFT_NAME(defaultMaxLineLength());
- (void)setDefaultMaxLineLength:(int)newDefaultMaxLineLength NS_SWIFT_NAME(setDefaultMaxLineLength(_:));

@property (nonatomic,readwrite,assign,getter=defaultSingleLineMode,setter=setDefaultSingleLineMode:) BOOL defaultSingleLineMode NS_SWIFT_NAME(defaultSingleLineMode);
- (BOOL)defaultSingleLineMode NS_SWIFT_NAME(defaultSingleLineMode());
- (void)setDefaultSingleLineMode:(BOOL)newDefaultSingleLineMode NS_SWIFT_NAME(setDefaultSingleLineMode(_:));

@property (nonatomic,readwrite,assign,getter=defaultTimeout,setter=setDefaultTimeout:) int defaultTimeout NS_SWIFT_NAME(defaultTimeout);
- (int)defaultTimeout NS_SWIFT_NAME(defaultTimeout());
- (void)setDefaultTimeout:(int)newDefaultTimeout NS_SWIFT_NAME(setDefaultTimeout(_:));

@property (nonatomic,readwrite,assign,getter=keepAlive,setter=setKeepAlive:) BOOL keepAlive NS_SWIFT_NAME(keepAlive);
- (BOOL)keepAlive NS_SWIFT_NAME(keepAlive());
- (void)setKeepAlive:(BOOL)newKeepAlive NS_SWIFT_NAME(setKeepAlive(_:));

@property (nonatomic,readwrite,assign,getter=linger,setter=setLinger:) BOOL linger NS_SWIFT_NAME(linger);
- (BOOL)linger NS_SWIFT_NAME(linger());
- (void)setLinger:(BOOL)newLinger NS_SWIFT_NAME(setLinger(_:));

@property (nonatomic,readwrite,assign,getter=listening,setter=setListening:) BOOL listening NS_SWIFT_NAME(listening);
- (BOOL)listening NS_SWIFT_NAME(listening());
- (void)setListening:(BOOL)newListening NS_SWIFT_NAME(setListening(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=localPort,setter=setLocalPort:) int localPort NS_SWIFT_NAME(localPort);
- (int)localPort NS_SWIFT_NAME(localPort());
- (void)setLocalPort:(int)newLocalPort NS_SWIFT_NAME(setLocalPort(_:));

@property (nonatomic,readwrite,assign,getter=SSLAuthenticateClients,setter=setSSLAuthenticateClients:) BOOL SSLAuthenticateClients NS_SWIFT_NAME(SSLAuthenticateClients);
- (BOOL)SSLAuthenticateClients NS_SWIFT_NAME(SSLAuthenticateClients());
- (void)setSSLAuthenticateClients:(BOOL)newSSLAuthenticateClients NS_SWIFT_NAME(setSSLAuthenticateClients(_:));

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

@property (nonatomic,readwrite,assign,getter=SSLStartMode,setter=setSSLStartMode:) int SSLStartMode NS_SWIFT_NAME(SSLStartMode);
- (int)SSLStartMode NS_SWIFT_NAME(SSLStartMode());
- (void)setSSLStartMode:(int)newSSLStartMode NS_SWIFT_NAME(setSSLStartMode(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)disconnect:(int)connectionId NS_SWIFT_NAME(disconnect(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)interrupt:(int)connectionId NS_SWIFT_NAME(interrupt(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)send:(int)connectionId :(NSData*)text NS_SWIFT_NAME(send(_:_:));
- (void)sendFile:(int)connectionId :(NSString*)fileName NS_SWIFT_NAME(sendFile(_:_:));
- (void)sendLine:(int)connectionId :(NSString*)text NS_SWIFT_NAME(sendLine(_:_:));
- (void)shutdown NS_SWIFT_NAME(shutdown());
- (void)startSSL:(int)connectionId NS_SWIFT_NAME(startSSL(_:));

@end


