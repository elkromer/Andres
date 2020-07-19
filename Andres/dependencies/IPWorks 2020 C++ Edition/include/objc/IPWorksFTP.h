
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

//TFTPTRANSFERMODES
#define TM_DEFAULT                                         0
#define TM_ASCII                                           1
#define TM_BINARY                                          2


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksFTPDelegate <NSObject>
@optional
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDirList:(NSString*)dirEntry :(NSString*)fileName :(BOOL)isDir :(long long)fileSize :(NSString*)fileTime NS_SWIFT_NAME(onDirList(_:_:_:_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onPITrail:(int)direction :(NSString*)message NS_SWIFT_NAME(onPITrail(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text NS_SWIFT_NAME(onTransfer(_:_:_:_:));
@end

@interface IPWorksFTP : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksFTPDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasDirList;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasError;
  BOOL m_delegateHasPITrail;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
  BOOL m_delegateHasStartTransfer;
  BOOL m_delegateHasTransfer;
}

+ (IPWorksFTP*)ftp;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksFTPDelegate> delegate;
- (id <IPWorksFTPDelegate>)delegate;
- (void) setDelegate:(id <IPWorksFTPDelegate>)anObject;

  /* Events */

- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDirList:(NSString*)dirEntry :(NSString*)fileName :(BOOL)isDir :(long long)fileSize :(NSString*)fileTime NS_SWIFT_NAME(onDirList(_:_:_:_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onPITrail:(int)direction :(NSString*)message NS_SWIFT_NAME(onPITrail(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text NS_SWIFT_NAME(onTransfer(_:_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=account,setter=setAccount:) NSString* account NS_SWIFT_NAME(account);
- (NSString*)account NS_SWIFT_NAME(account());
- (void)setAccount:(NSString*)newAccount NS_SWIFT_NAME(setAccount(_:));

@property (nonatomic,readwrite,assign,getter=command,setter=setCommand:) NSString* command NS_SWIFT_NAME(command);
- (NSString*)command NS_SWIFT_NAME(command());
- (void)setCommand:(NSString*)newCommand NS_SWIFT_NAME(setCommand(_:));

@property (nonatomic,readwrite,assign,getter=connected,setter=setConnected:) BOOL connected NS_SWIFT_NAME(connected);
- (BOOL)connected NS_SWIFT_NAME(connected());
- (void)setConnected:(BOOL)newConnected NS_SWIFT_NAME(setConnected(_:));

@property (nonatomic,readonly,assign,getter=dirListCount) int dirListCount NS_SWIFT_NAME(dirListCount);
- (int)dirListCount NS_SWIFT_NAME(dirListCount());

- (NSString*)dirListEntry:(int)entryIndex NS_SWIFT_NAME(dirListEntry(_:));

- (NSString*)dirListFileName:(int)entryIndex NS_SWIFT_NAME(dirListFileName(_:));

- (long long)dirListFileSize:(int)entryIndex NS_SWIFT_NAME(dirListFileSize(_:));

- (NSString*)dirListFileTime:(int)entryIndex NS_SWIFT_NAME(dirListFileTime(_:));

- (BOOL)dirListIsDir:(int)entryIndex NS_SWIFT_NAME(dirListIsDir(_:));

@property (nonatomic,readonly,assign,getter=fileExists) BOOL fileExists NS_SWIFT_NAME(fileExists);
- (BOOL)fileExists NS_SWIFT_NAME(fileExists());

@property (nonatomic,readonly,assign,getter=fileSize) long long fileSize NS_SWIFT_NAME(fileSize);
- (long long)fileSize NS_SWIFT_NAME(fileSize());

@property (nonatomic,readonly,assign,getter=fileTime) NSString* fileTime NS_SWIFT_NAME(fileTime);
- (NSString*)fileTime NS_SWIFT_NAME(fileTime());

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

@property (nonatomic,readonly,assign,getter=lastReply) NSString* lastReply NS_SWIFT_NAME(lastReply);
- (NSString*)lastReply NS_SWIFT_NAME(lastReply());

@property (nonatomic,readwrite,assign,getter=localFile,setter=setLocalFile:) NSString* localFile NS_SWIFT_NAME(localFile);
- (NSString*)localFile NS_SWIFT_NAME(localFile());
- (void)setLocalFile:(NSString*)newLocalFile NS_SWIFT_NAME(setLocalFile(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=overwrite,setter=setOverwrite:) BOOL overwrite NS_SWIFT_NAME(overwrite);
- (BOOL)overwrite NS_SWIFT_NAME(overwrite());
- (void)setOverwrite:(BOOL)newOverwrite NS_SWIFT_NAME(setOverwrite(_:));

@property (nonatomic,readwrite,assign,getter=passive,setter=setPassive:) BOOL passive NS_SWIFT_NAME(passive);
- (BOOL)passive NS_SWIFT_NAME(passive());
- (void)setPassive:(BOOL)newPassive NS_SWIFT_NAME(setPassive(_:));

@property (nonatomic,readwrite,assign,getter=password,setter=setPassword:) NSString* password NS_SWIFT_NAME(password);
- (NSString*)password NS_SWIFT_NAME(password());
- (void)setPassword:(NSString*)newPassword NS_SWIFT_NAME(setPassword(_:));

@property (nonatomic,readwrite,assign,getter=remoteFile,setter=setRemoteFile:) NSString* remoteFile NS_SWIFT_NAME(remoteFile);
- (NSString*)remoteFile NS_SWIFT_NAME(remoteFile());
- (void)setRemoteFile:(NSString*)newRemoteFile NS_SWIFT_NAME(setRemoteFile(_:));

@property (nonatomic,readwrite,assign,getter=remoteHost,setter=setRemoteHost:) NSString* remoteHost NS_SWIFT_NAME(remoteHost);
- (NSString*)remoteHost NS_SWIFT_NAME(remoteHost());
- (void)setRemoteHost:(NSString*)newRemoteHost NS_SWIFT_NAME(setRemoteHost(_:));

@property (nonatomic,readwrite,assign,getter=remotePath,setter=setRemotePath:) NSString* remotePath NS_SWIFT_NAME(remotePath);
- (NSString*)remotePath NS_SWIFT_NAME(remotePath());
- (void)setRemotePath:(NSString*)newRemotePath NS_SWIFT_NAME(setRemotePath(_:));

@property (nonatomic,readwrite,assign,getter=remotePort,setter=setRemotePort:) int remotePort NS_SWIFT_NAME(remotePort);
- (int)remotePort NS_SWIFT_NAME(remotePort());
- (void)setRemotePort:(int)newRemotePort NS_SWIFT_NAME(setRemotePort(_:));

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

@property (nonatomic,readwrite,assign,getter=startByte,setter=setStartByte:) NSString* startByte NS_SWIFT_NAME(startByte);
- (NSString*)startByte NS_SWIFT_NAME(startByte());
- (void)setStartByte:(NSString*)newStartByte NS_SWIFT_NAME(setStartByte(_:));

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

@property (nonatomic,readwrite,assign,getter=transferMode,setter=setTransferMode:) int transferMode NS_SWIFT_NAME(transferMode);
- (int)transferMode NS_SWIFT_NAME(transferMode());
- (void)setTransferMode:(int)newTransferMode NS_SWIFT_NAME(setTransferMode(_:));

@property (nonatomic,readwrite,assign,getter=user,setter=setUser:) NSString* user NS_SWIFT_NAME(user);
- (NSString*)user NS_SWIFT_NAME(user());
- (void)setUser:(NSString*)newUser NS_SWIFT_NAME(setUser(_:));

  /* Methods */

- (void)abort NS_SWIFT_NAME(abort());
- (void)append NS_SWIFT_NAME(append());
- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)deleteFile:(NSString*)fileName NS_SWIFT_NAME(deleteFile(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)download NS_SWIFT_NAME(download());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)listDirectory NS_SWIFT_NAME(listDirectory());
- (void)listDirectoryLong NS_SWIFT_NAME(listDirectoryLong());
- (void)logoff NS_SWIFT_NAME(logoff());
- (void)logon NS_SWIFT_NAME(logon());
- (void)makeDirectory:(NSString*)newDir NS_SWIFT_NAME(makeDirectory(_:));
- (void)removeDirectory:(NSString*)dirName NS_SWIFT_NAME(removeDirectory(_:));
- (void)renameFile:(NSString*)newName NS_SWIFT_NAME(renameFile(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)storeUnique NS_SWIFT_NAME(storeUnique());
- (void)upload NS_SWIFT_NAME(upload());

@end


