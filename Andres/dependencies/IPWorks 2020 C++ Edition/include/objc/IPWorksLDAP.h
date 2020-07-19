
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//LDAPATTRIBUTEMODOPS
#define AMO_ADD                                            0
#define AMO_DELETE                                         1
#define AMO_REPLACE                                        2

//LDAPAUTHMECHANISMS
#define LAM_SIMPLE                                         0
#define LAM_DIGEST_MD5                                     1
#define LAM_NEGOTIATE                                      2
#define LAM_KERBEROS                                       6

//FIREWALLTYPES
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TLDAPDEREFALIASES
#define SDA_NEVER                                          0
#define SDA_IN_SEARCHING                                   1
#define SDA_FINDING_BASE_OBJECT                            2
#define SDA_ALWAYS                                         3

//TLDAPSEARCHSCOPE
#define SS_BASE_OBJECT                                     0
#define SS_SINGLE_LEVEL                                    1
#define SS_WHOLE_SUBTREE                                   2

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

@protocol IPWorksLDAPDelegate <NSObject>
@optional
- (void)onComputerList:(NSString*)name :(NSString*)operatingSystem :(NSString*)lastLogon :(int)logonCount :(NSString*)dn NS_SWIFT_NAME(onComputerList(_:_:_:_:_:));
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onExtendedResponse:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription :(NSString*)responseName :(NSData*)responseValue NS_SWIFT_NAME(onExtendedResponse(_:_:_:_:_:_:));
- (void)onGroupList:(NSString*)name :(NSString*)description :(NSString*)dn NS_SWIFT_NAME(onGroupList(_:_:_:));
- (void)onPITrail:(int)direction :(NSString*)description :(NSString*)message NS_SWIFT_NAME(onPITrail(_:_:_:));
- (void)onResult:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription NS_SWIFT_NAME(onResult(_:_:_:_:));
- (void)onSearchComplete:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription NS_SWIFT_NAME(onSearchComplete(_:_:_:_:));
- (void)onSearchPage:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription :(int*)cancelSearch NS_SWIFT_NAME(onSearchPage(_:_:_:_:_:));
- (void)onSearchResult:(int)messageId :(NSString*)DN NS_SWIFT_NAME(onSearchResult(_:_:));
- (void)onSearchResultReference:(int)messageId :(NSString*)ldapUrl NS_SWIFT_NAME(onSearchResultReference(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onUserList:(NSString*)name :(NSString*)description :(NSString*)lastLogon :(NSString*)memberOf :(NSString*)dn NS_SWIFT_NAME(onUserList(_:_:_:_:_:));
@end

@interface IPWorksLDAP : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksLDAPDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasComputerList;
  BOOL m_delegateHasConnected;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasDisconnected;
  BOOL m_delegateHasError;
  BOOL m_delegateHasExtendedResponse;
  BOOL m_delegateHasGroupList;
  BOOL m_delegateHasPITrail;
  BOOL m_delegateHasResult;
  BOOL m_delegateHasSearchComplete;
  BOOL m_delegateHasSearchPage;
  BOOL m_delegateHasSearchResult;
  BOOL m_delegateHasSearchResultReference;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
  BOOL m_delegateHasUserList;
}

+ (IPWorksLDAP*)ldap;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksLDAPDelegate> delegate;
- (id <IPWorksLDAPDelegate>)delegate;
- (void) setDelegate:(id <IPWorksLDAPDelegate>)anObject;

  /* Events */

- (void)onComputerList:(NSString*)name :(NSString*)operatingSystem :(NSString*)lastLogon :(int)logonCount :(NSString*)dn NS_SWIFT_NAME(onComputerList(_:_:_:_:_:));
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onExtendedResponse:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription :(NSString*)responseName :(NSData*)responseValue NS_SWIFT_NAME(onExtendedResponse(_:_:_:_:_:_:));
- (void)onGroupList:(NSString*)name :(NSString*)description :(NSString*)dn NS_SWIFT_NAME(onGroupList(_:_:_:));
- (void)onPITrail:(int)direction :(NSString*)description :(NSString*)message NS_SWIFT_NAME(onPITrail(_:_:_:));
- (void)onResult:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription NS_SWIFT_NAME(onResult(_:_:_:_:));
- (void)onSearchComplete:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription NS_SWIFT_NAME(onSearchComplete(_:_:_:_:));
- (void)onSearchPage:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription :(int*)cancelSearch NS_SWIFT_NAME(onSearchPage(_:_:_:_:_:));
- (void)onSearchResult:(int)messageId :(NSString*)DN NS_SWIFT_NAME(onSearchResult(_:_:));
- (void)onSearchResultReference:(int)messageId :(NSString*)ldapUrl NS_SWIFT_NAME(onSearchResultReference(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onUserList:(NSString*)name :(NSString*)description :(NSString*)lastLogon :(NSString*)memberOf :(NSString*)dn NS_SWIFT_NAME(onUserList(_:_:_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=acceptData,setter=setAcceptData:) BOOL acceptData NS_SWIFT_NAME(acceptData);
- (BOOL)acceptData NS_SWIFT_NAME(acceptData());
- (void)setAcceptData:(BOOL)newAcceptData NS_SWIFT_NAME(setAcceptData(_:));

@property (nonatomic,readwrite,assign,getter=attrCount,setter=setAttrCount:) int attrCount NS_SWIFT_NAME(attrCount);
- (int)attrCount NS_SWIFT_NAME(attrCount());
- (void)setAttrCount:(int)newAttrCount NS_SWIFT_NAME(setAttrCount(_:));

- (NSString*)attrType:(int)attrIndex NS_SWIFT_NAME(attrType(_:));
- (void)setAttrType:(int)attrIndex:(NSString*)newAttrType NS_SWIFT_NAME(setAttrType(_:_:));

- (int)attrModOp:(int)attrIndex NS_SWIFT_NAME(attrModOp(_:));
- (void)setAttrModOp:(int)attrIndex:(int)newAttrModOp NS_SWIFT_NAME(setAttrModOp(_:_:));

- (NSString*)attrValue:(int)attrIndex NS_SWIFT_NAME(attrValue(_:));
- (void)setAttrValue:(int)attrIndex:(NSString*)newAttrValue NS_SWIFT_NAME(setAttrValue(_:_:));

- (NSData*)attrValueB:(int)attrIndex NS_SWIFT_NAME(attrValueB(_:));
- (void)setAttrValueB:(int)attrIndex :(NSData*)newAttrValue NS_SWIFT_NAME(setAttrValueB(_:_:));

@property (nonatomic,readwrite,assign,getter=authMechanism,setter=setAuthMechanism:) int authMechanism NS_SWIFT_NAME(authMechanism);
- (int)authMechanism NS_SWIFT_NAME(authMechanism());
- (void)setAuthMechanism:(int)newAuthMechanism NS_SWIFT_NAME(setAuthMechanism(_:));

@property (nonatomic,readwrite,assign,getter=connected,setter=setConnected:) BOOL connected NS_SWIFT_NAME(connected);
- (BOOL)connected NS_SWIFT_NAME(connected());
- (void)setConnected:(BOOL)newConnected NS_SWIFT_NAME(setConnected(_:));

@property (nonatomic,readwrite,assign,getter=deleteOldRDN,setter=setDeleteOldRDN:) BOOL deleteOldRDN NS_SWIFT_NAME(deleteOldRDN);
- (BOOL)deleteOldRDN NS_SWIFT_NAME(deleteOldRDN());
- (void)setDeleteOldRDN:(BOOL)newDeleteOldRDN NS_SWIFT_NAME(setDeleteOldRDN(_:));

@property (nonatomic,readwrite,assign,getter=DN,setter=setDN:) NSString* DN NS_SWIFT_NAME(DN);
- (NSString*)DN NS_SWIFT_NAME(DN());
- (void)setDN:(NSString*)newDN NS_SWIFT_NAME(setDN(_:));

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

@property (nonatomic,readwrite,assign,getter=LDAPVersion,setter=setLDAPVersion:) int LDAPVersion NS_SWIFT_NAME(LDAPVersion);
- (int)LDAPVersion NS_SWIFT_NAME(LDAPVersion());
- (void)setLDAPVersion:(int)newLDAPVersion NS_SWIFT_NAME(setLDAPVersion(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=messageId,setter=setMessageId:) int messageId NS_SWIFT_NAME(messageId);
- (int)messageId NS_SWIFT_NAME(messageId());
- (void)setMessageId:(int)newMessageId NS_SWIFT_NAME(setMessageId(_:));

@property (nonatomic,readwrite,assign,getter=pageSize,setter=setPageSize:) int pageSize NS_SWIFT_NAME(pageSize);
- (int)pageSize NS_SWIFT_NAME(pageSize());
- (void)setPageSize:(int)newPageSize NS_SWIFT_NAME(setPageSize(_:));

@property (nonatomic,readwrite,assign,getter=password,setter=setPassword:) NSString* password NS_SWIFT_NAME(password);
- (NSString*)password NS_SWIFT_NAME(password());
- (void)setPassword:(NSString*)newPassword NS_SWIFT_NAME(setPassword(_:));

@property (nonatomic,readonly,assign,getter=referenceCount) int referenceCount NS_SWIFT_NAME(referenceCount);
- (int)referenceCount NS_SWIFT_NAME(referenceCount());

- (NSString*)referenceURL:(int)referenceIndex NS_SWIFT_NAME(referenceURL(_:));

@property (nonatomic,readonly,assign,getter=resultCode) int resultCode NS_SWIFT_NAME(resultCode);
- (int)resultCode NS_SWIFT_NAME(resultCode());

@property (nonatomic,readonly,assign,getter=resultDescription) NSString* resultDescription NS_SWIFT_NAME(resultDescription);
- (NSString*)resultDescription NS_SWIFT_NAME(resultDescription());

@property (nonatomic,readonly,assign,getter=resultDN) NSString* resultDN NS_SWIFT_NAME(resultDN);
- (NSString*)resultDN NS_SWIFT_NAME(resultDN());

@property (nonatomic,readwrite,assign,getter=searchDerefAliases,setter=setSearchDerefAliases:) int searchDerefAliases NS_SWIFT_NAME(searchDerefAliases);
- (int)searchDerefAliases NS_SWIFT_NAME(searchDerefAliases());
- (void)setSearchDerefAliases:(int)newSearchDerefAliases NS_SWIFT_NAME(setSearchDerefAliases(_:));

@property (nonatomic,readwrite,assign,getter=searchReturnValues,setter=setSearchReturnValues:) BOOL searchReturnValues NS_SWIFT_NAME(searchReturnValues);
- (BOOL)searchReturnValues NS_SWIFT_NAME(searchReturnValues());
- (void)setSearchReturnValues:(BOOL)newSearchReturnValues NS_SWIFT_NAME(setSearchReturnValues(_:));

@property (nonatomic,readwrite,assign,getter=searchScope,setter=setSearchScope:) int searchScope NS_SWIFT_NAME(searchScope);
- (int)searchScope NS_SWIFT_NAME(searchScope());
- (void)setSearchScope:(int)newSearchScope NS_SWIFT_NAME(setSearchScope(_:));

@property (nonatomic,readwrite,assign,getter=searchSizeLimit,setter=setSearchSizeLimit:) int searchSizeLimit NS_SWIFT_NAME(searchSizeLimit);
- (int)searchSizeLimit NS_SWIFT_NAME(searchSizeLimit());
- (void)setSearchSizeLimit:(int)newSearchSizeLimit NS_SWIFT_NAME(setSearchSizeLimit(_:));

@property (nonatomic,readwrite,assign,getter=searchTimeLimit,setter=setSearchTimeLimit:) int searchTimeLimit NS_SWIFT_NAME(searchTimeLimit);
- (int)searchTimeLimit NS_SWIFT_NAME(searchTimeLimit());
- (void)setSearchTimeLimit:(int)newSearchTimeLimit NS_SWIFT_NAME(setSearchTimeLimit(_:));

@property (nonatomic,readwrite,assign,getter=serverName,setter=setServerName:) NSString* serverName NS_SWIFT_NAME(serverName);
- (NSString*)serverName NS_SWIFT_NAME(serverName());
- (void)setServerName:(NSString*)newServerName NS_SWIFT_NAME(setServerName(_:));

@property (nonatomic,readwrite,assign,getter=serverPort,setter=setServerPort:) int serverPort NS_SWIFT_NAME(serverPort);
- (int)serverPort NS_SWIFT_NAME(serverPort());
- (void)setServerPort:(int)newServerPort NS_SWIFT_NAME(setServerPort(_:));

@property (nonatomic,readwrite,assign,getter=sortAttributes,setter=setSortAttributes:) NSString* sortAttributes NS_SWIFT_NAME(sortAttributes);
- (NSString*)sortAttributes NS_SWIFT_NAME(sortAttributes());
- (void)setSortAttributes:(NSString*)newSortAttributes NS_SWIFT_NAME(setSortAttributes(_:));

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

  /* Methods */

- (void)abandon:(int)messageId NS_SWIFT_NAME(abandon(_:));
- (void)add NS_SWIFT_NAME(add());
- (NSString*)attr:(NSString*)attrType NS_SWIFT_NAME(attr(_:));
- (void)bind NS_SWIFT_NAME(bind());
- (void)changePassword:(NSString*)user :(NSString*)oldPassword :(NSString*)newPassword NS_SWIFT_NAME(changePassword(_:_:_:));
- (void)compare NS_SWIFT_NAME(compare());
- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)delete NS_SWIFT_NAME(delete());
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)extendedRequest:(NSString*)requestName :(NSData*)requestValue NS_SWIFT_NAME(extendedRequest(_:_:));
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)listComputers NS_SWIFT_NAME(listComputers());
- (void)listGroupMembers:(NSString*)group NS_SWIFT_NAME(listGroupMembers(_:));
- (void)listGroups NS_SWIFT_NAME(listGroups());
- (void)listUserGroups:(NSString*)user NS_SWIFT_NAME(listUserGroups(_:));
- (void)modify NS_SWIFT_NAME(modify());
- (void)modifyRDN:(NSString*)newRDN NS_SWIFT_NAME(modifyRDN(_:));
- (void)moveToDN:(NSString*)newSuperior NS_SWIFT_NAME(moveToDN(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)search:(NSString*)searchFilter NS_SWIFT_NAME(search(_:));
- (void)unbind NS_SWIFT_NAME(unbind());

@end


