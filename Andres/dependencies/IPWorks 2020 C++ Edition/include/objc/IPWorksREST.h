
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//AUTHSCHEMES
#define AUTH_BASIC                                         0
#define AUTH_DIGEST                                        1
#define AUTH_PROPRIETARY                                   2
#define AUTH_NONE                                          3
#define AUTH_NTLM                                          4
#define AUTH_NEGOTIATE                                     5
#define AUTH_OAUTH                                         6

//FIREWALLTYPES
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TFOLLOWREDIRECTS
#define FR_NEVER                                           0
#define FR_ALWAYS                                          1
#define FR_SAME_SCHEME                                     2

//PROXYSSLTYPES
#define PS_AUTOMATIC                                       0
#define PS_ALWAYS                                          1
#define PS_NEVER                                           2
#define PS_TUNNEL                                          3

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


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksRESTDelegate <NSObject>
@optional
- (void)onCharacters:(NSString*)text NS_SWIFT_NAME(onCharacters(_:));
- (void)onComment:(NSString*)text NS_SWIFT_NAME(onComment(_:));
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndElement:(NSString*)namespace :(NSString*)element :(NSString*)QName :(BOOL)isEmpty NS_SWIFT_NAME(onEndElement(_:_:_:_:));
- (void)onEndPrefixMapping:(NSString*)prefix NS_SWIFT_NAME(onEndPrefixMapping(_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onEvalEntity:(NSString*)entity :(NSString**)value NS_SWIFT_NAME(onEvalEntity(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onIgnorableWhitespace:(NSString*)text NS_SWIFT_NAME(onIgnorableWhitespace(_:));
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType NS_SWIFT_NAME(onLog(_:_:_:));
- (void)onMeta:(NSString*)text NS_SWIFT_NAME(onMeta(_:));
- (void)onPI:(NSString*)text NS_SWIFT_NAME(onPI(_:));
- (void)onRedirect:(NSString*)location :(int*)accept NS_SWIFT_NAME(onRedirect(_:_:));
- (void)onSetCookie:(NSString*)name :(NSString*)value :(NSString*)expires :(NSString*)domain :(NSString*)path :(BOOL)secure NS_SWIFT_NAME(onSetCookie(_:_:_:_:_:_:));
- (void)onSpecialSection:(NSString*)sectionId :(NSString*)text NS_SWIFT_NAME(onSpecialSection(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartElement:(NSString*)namespace :(NSString*)element :(NSString*)QName :(BOOL)isEmpty NS_SWIFT_NAME(onStartElement(_:_:_:_:));
- (void)onStartPrefixMapping:(NSString*)prefix :(NSString*)URI NS_SWIFT_NAME(onStartPrefixMapping(_:_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onStatus:(NSString*)HTTPVersion :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onStatus(_:_:_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text NS_SWIFT_NAME(onTransfer(_:_:_:_:));
@end

@interface IPWorksREST : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksRESTDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasCharacters;
  BOOL m_delegateHasComment;
  BOOL m_delegateHasConnected;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasDisconnected;
  BOOL m_delegateHasEndElement;
  BOOL m_delegateHasEndPrefixMapping;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasError;
  BOOL m_delegateHasEvalEntity;
  BOOL m_delegateHasHeader;
  BOOL m_delegateHasIgnorableWhitespace;
  BOOL m_delegateHasLog;
  BOOL m_delegateHasMeta;
  BOOL m_delegateHasPI;
  BOOL m_delegateHasRedirect;
  BOOL m_delegateHasSetCookie;
  BOOL m_delegateHasSpecialSection;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
  BOOL m_delegateHasStartElement;
  BOOL m_delegateHasStartPrefixMapping;
  BOOL m_delegateHasStartTransfer;
  BOOL m_delegateHasStatus;
  BOOL m_delegateHasTransfer;
}

+ (IPWorksREST*)rest;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksRESTDelegate> delegate;
- (id <IPWorksRESTDelegate>)delegate;
- (void) setDelegate:(id <IPWorksRESTDelegate>)anObject;

  /* Events */

- (void)onCharacters:(NSString*)text NS_SWIFT_NAME(onCharacters(_:));
- (void)onComment:(NSString*)text NS_SWIFT_NAME(onComment(_:));
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndElement:(NSString*)namespace :(NSString*)element :(NSString*)QName :(BOOL)isEmpty NS_SWIFT_NAME(onEndElement(_:_:_:_:));
- (void)onEndPrefixMapping:(NSString*)prefix NS_SWIFT_NAME(onEndPrefixMapping(_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onEvalEntity:(NSString*)entity :(NSString**)value NS_SWIFT_NAME(onEvalEntity(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onIgnorableWhitespace:(NSString*)text NS_SWIFT_NAME(onIgnorableWhitespace(_:));
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType NS_SWIFT_NAME(onLog(_:_:_:));
- (void)onMeta:(NSString*)text NS_SWIFT_NAME(onMeta(_:));
- (void)onPI:(NSString*)text NS_SWIFT_NAME(onPI(_:));
- (void)onRedirect:(NSString*)location :(int*)accept NS_SWIFT_NAME(onRedirect(_:_:));
- (void)onSetCookie:(NSString*)name :(NSString*)value :(NSString*)expires :(NSString*)domain :(NSString*)path :(BOOL)secure NS_SWIFT_NAME(onSetCookie(_:_:_:_:_:_:));
- (void)onSpecialSection:(NSString*)sectionId :(NSString*)text NS_SWIFT_NAME(onSpecialSection(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartElement:(NSString*)namespace :(NSString*)element :(NSString*)QName :(BOOL)isEmpty NS_SWIFT_NAME(onStartElement(_:_:_:_:));
- (void)onStartPrefixMapping:(NSString*)prefix :(NSString*)URI NS_SWIFT_NAME(onStartPrefixMapping(_:_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onStatus:(NSString*)HTTPVersion :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onStatus(_:_:_:));
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

@property (nonatomic,readwrite,assign,getter=accept,setter=setAccept:) NSString* accept NS_SWIFT_NAME(accept);
- (NSString*)accept NS_SWIFT_NAME(accept());
- (void)setAccept:(NSString*)newAccept NS_SWIFT_NAME(setAccept(_:));

@property (nonatomic,readwrite,assign,getter=authorization,setter=setAuthorization:) NSString* authorization NS_SWIFT_NAME(authorization);
- (NSString*)authorization NS_SWIFT_NAME(authorization());
- (void)setAuthorization:(NSString*)newAuthorization NS_SWIFT_NAME(setAuthorization(_:));

@property (nonatomic,readwrite,assign,getter=authScheme,setter=setAuthScheme:) int authScheme NS_SWIFT_NAME(authScheme);
- (int)authScheme NS_SWIFT_NAME(authScheme());
- (void)setAuthScheme:(int)newAuthScheme NS_SWIFT_NAME(setAuthScheme(_:));

@property (nonatomic,readwrite,assign,getter=buildDOM,setter=setBuildDOM:) BOOL buildDOM NS_SWIFT_NAME(buildDOM);
- (BOOL)buildDOM NS_SWIFT_NAME(buildDOM());
- (void)setBuildDOM:(BOOL)newBuildDOM NS_SWIFT_NAME(setBuildDOM(_:));

@property (nonatomic,readwrite,assign,getter=connected,setter=setConnected:) BOOL connected NS_SWIFT_NAME(connected);
- (BOOL)connected NS_SWIFT_NAME(connected());
- (void)setConnected:(BOOL)newConnected NS_SWIFT_NAME(setConnected(_:));

@property (nonatomic,readwrite,assign,getter=contentType,setter=setContentType:) NSString* contentType NS_SWIFT_NAME(contentType);
- (NSString*)contentType NS_SWIFT_NAME(contentType());
- (void)setContentType:(NSString*)newContentType NS_SWIFT_NAME(setContentType(_:));

@property (nonatomic,readwrite,assign,getter=cookieCount,setter=setCookieCount:) int cookieCount NS_SWIFT_NAME(cookieCount);
- (int)cookieCount NS_SWIFT_NAME(cookieCount());
- (void)setCookieCount:(int)newCookieCount NS_SWIFT_NAME(setCookieCount(_:));

- (NSString*)cookieDomain:(int)cookieIndex NS_SWIFT_NAME(cookieDomain(_:));

- (NSString*)cookieExpiration:(int)cookieIndex NS_SWIFT_NAME(cookieExpiration(_:));

- (NSString*)cookieName:(int)cookieIndex NS_SWIFT_NAME(cookieName(_:));
- (void)setCookieName:(int)cookieIndex:(NSString*)newCookieName NS_SWIFT_NAME(setCookieName(_:_:));

- (NSString*)cookiePath:(int)cookieIndex NS_SWIFT_NAME(cookiePath(_:));

- (BOOL)cookieSecure:(int)cookieIndex NS_SWIFT_NAME(cookieSecure(_:));

- (NSString*)cookieValue:(int)cookieIndex NS_SWIFT_NAME(cookieValue(_:));
- (void)setCookieValue:(int)cookieIndex:(NSString*)newCookieValue NS_SWIFT_NAME(setCookieValue(_:_:));

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

@property (nonatomic,readwrite,assign,getter=followRedirects,setter=setFollowRedirects:) int followRedirects NS_SWIFT_NAME(followRedirects);
- (int)followRedirects NS_SWIFT_NAME(followRedirects());
- (void)setFollowRedirects:(int)newFollowRedirects NS_SWIFT_NAME(setFollowRedirects(_:));

@property (nonatomic,readwrite,assign,getter=from,setter=setFrom:) NSString* from NS_SWIFT_NAME(from);
- (NSString*)from NS_SWIFT_NAME(from());
- (void)setFrom:(NSString*)newFrom NS_SWIFT_NAME(setFrom(_:));

@property (nonatomic,readwrite,assign,getter=HTTPMethod,setter=setHTTPMethod:) NSString* HTTPMethod NS_SWIFT_NAME(HTTPMethod);
- (NSString*)HTTPMethod NS_SWIFT_NAME(HTTPMethod());
- (void)setHTTPMethod:(NSString*)newHTTPMethod NS_SWIFT_NAME(setHTTPMethod(_:));

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readwrite,assign,getter=ifModifiedSince,setter=setIfModifiedSince:) NSString* ifModifiedSince NS_SWIFT_NAME(ifModifiedSince);
- (NSString*)ifModifiedSince NS_SWIFT_NAME(ifModifiedSince());
- (void)setIfModifiedSince:(NSString*)newIfModifiedSince NS_SWIFT_NAME(setIfModifiedSince(_:));

@property (nonatomic,readwrite,assign,getter=localFile,setter=setLocalFile:) NSString* localFile NS_SWIFT_NAME(localFile);
- (NSString*)localFile NS_SWIFT_NAME(localFile());
- (void)setLocalFile:(NSString*)newLocalFile NS_SWIFT_NAME(setLocalFile(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readonly,assign,getter=namespaceCount) int namespaceCount NS_SWIFT_NAME(namespaceCount);
- (int)namespaceCount NS_SWIFT_NAME(namespaceCount());

- (NSString*)namespacePrefix:(int)namespaceIndex NS_SWIFT_NAME(namespacePrefix(_:));

- (NSString*)namespaceURI:(int)namespaceIndex NS_SWIFT_NAME(namespaceURI(_:));

@property (nonatomic,readwrite,assign,getter=otherHeaders,setter=setOtherHeaders:) NSString* otherHeaders NS_SWIFT_NAME(otherHeaders);
- (NSString*)otherHeaders NS_SWIFT_NAME(otherHeaders());
- (void)setOtherHeaders:(NSString*)newOtherHeaders NS_SWIFT_NAME(setOtherHeaders(_:));

@property (nonatomic,readonly,assign,getter=parsedHeaderCount) int parsedHeaderCount NS_SWIFT_NAME(parsedHeaderCount);
- (int)parsedHeaderCount NS_SWIFT_NAME(parsedHeaderCount());

- (NSString*)parsedHeaderField:(int)parsedHeaderIndex NS_SWIFT_NAME(parsedHeaderField(_:));

- (NSString*)parsedHeaderValue:(int)parsedHeaderIndex NS_SWIFT_NAME(parsedHeaderValue(_:));

@property (nonatomic,readwrite,assign,getter=password,setter=setPassword:) NSString* password NS_SWIFT_NAME(password);
- (NSString*)password NS_SWIFT_NAME(password());
- (void)setPassword:(NSString*)newPassword NS_SWIFT_NAME(setPassword(_:));

@property (nonatomic,readwrite,assign,getter=postData,setter=setPostData:) NSString* postData NS_SWIFT_NAME(postData);
- (NSString*)postData NS_SWIFT_NAME(postData());
- (void)setPostData:(NSString*)newPostData NS_SWIFT_NAME(setPostData(_:));

@property (nonatomic,readwrite,assign,getter=postDataB,setter=setPostDataB:) NSData* postDataB NS_SWIFT_NAME(postDataB);
- (NSData*)postDataB NS_SWIFT_NAME(postDataB());
- (void)setPostDataB :(NSData*)newPostData NS_SWIFT_NAME(setPostDataB(_:));

@property (nonatomic,readwrite,assign,getter=proxyAuthScheme,setter=setProxyAuthScheme:) int proxyAuthScheme NS_SWIFT_NAME(proxyAuthScheme);
- (int)proxyAuthScheme NS_SWIFT_NAME(proxyAuthScheme());
- (void)setProxyAuthScheme:(int)newProxyAuthScheme NS_SWIFT_NAME(setProxyAuthScheme(_:));

@property (nonatomic,readwrite,assign,getter=proxyAutoDetect,setter=setProxyAutoDetect:) BOOL proxyAutoDetect NS_SWIFT_NAME(proxyAutoDetect);
- (BOOL)proxyAutoDetect NS_SWIFT_NAME(proxyAutoDetect());
- (void)setProxyAutoDetect:(BOOL)newProxyAutoDetect NS_SWIFT_NAME(setProxyAutoDetect(_:));

@property (nonatomic,readwrite,assign,getter=proxyPassword,setter=setProxyPassword:) NSString* proxyPassword NS_SWIFT_NAME(proxyPassword);
- (NSString*)proxyPassword NS_SWIFT_NAME(proxyPassword());
- (void)setProxyPassword:(NSString*)newProxyPassword NS_SWIFT_NAME(setProxyPassword(_:));

@property (nonatomic,readwrite,assign,getter=proxyPort,setter=setProxyPort:) int proxyPort NS_SWIFT_NAME(proxyPort);
- (int)proxyPort NS_SWIFT_NAME(proxyPort());
- (void)setProxyPort:(int)newProxyPort NS_SWIFT_NAME(setProxyPort(_:));

@property (nonatomic,readwrite,assign,getter=proxyServer,setter=setProxyServer:) NSString* proxyServer NS_SWIFT_NAME(proxyServer);
- (NSString*)proxyServer NS_SWIFT_NAME(proxyServer());
- (void)setProxyServer:(NSString*)newProxyServer NS_SWIFT_NAME(setProxyServer(_:));

@property (nonatomic,readwrite,assign,getter=proxySSL,setter=setProxySSL:) int proxySSL NS_SWIFT_NAME(proxySSL);
- (int)proxySSL NS_SWIFT_NAME(proxySSL());
- (void)setProxySSL:(int)newProxySSL NS_SWIFT_NAME(setProxySSL(_:));

@property (nonatomic,readwrite,assign,getter=proxyUser,setter=setProxyUser:) NSString* proxyUser NS_SWIFT_NAME(proxyUser);
- (NSString*)proxyUser NS_SWIFT_NAME(proxyUser());
- (void)setProxyUser:(NSString*)newProxyUser NS_SWIFT_NAME(setProxyUser(_:));

@property (nonatomic,readwrite,assign,getter=referer,setter=setReferer:) NSString* referer NS_SWIFT_NAME(referer);
- (NSString*)referer NS_SWIFT_NAME(referer());
- (void)setReferer:(NSString*)newReferer NS_SWIFT_NAME(setReferer(_:));

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

@property (nonatomic,readonly,assign,getter=SSLServerCertEncoded) NSString* SSLServerCertEncoded NS_SWIFT_NAME(SSLServerCertEncoded);
- (NSString*)SSLServerCertEncoded NS_SWIFT_NAME(SSLServerCertEncoded());

@property (nonatomic,readonly,assign,getter=SSLServerCertEncodedB) NSData* SSLServerCertEncodedB NS_SWIFT_NAME(SSLServerCertEncodedB);
- (NSData*)SSLServerCertEncodedB NS_SWIFT_NAME(SSLServerCertEncodedB());

@property (nonatomic,readonly,assign,getter=statusLine) NSString* statusLine NS_SWIFT_NAME(statusLine);
- (NSString*)statusLine NS_SWIFT_NAME(statusLine());

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

@property (nonatomic,readonly,assign,getter=transferredData) NSString* transferredData NS_SWIFT_NAME(transferredData);
- (NSString*)transferredData NS_SWIFT_NAME(transferredData());

@property (nonatomic,readonly,assign,getter=transferredDataB) NSData* transferredDataB NS_SWIFT_NAME(transferredDataB);
- (NSData*)transferredDataB NS_SWIFT_NAME(transferredDataB());

@property (nonatomic,readwrite,assign,getter=transferredDataLimit,setter=setTransferredDataLimit:) long long transferredDataLimit NS_SWIFT_NAME(transferredDataLimit);
- (long long)transferredDataLimit NS_SWIFT_NAME(transferredDataLimit());
- (void)setTransferredDataLimit:(long long)newTransferredDataLimit NS_SWIFT_NAME(setTransferredDataLimit(_:));

@property (nonatomic,readonly,assign,getter=transferredHeaders) NSString* transferredHeaders NS_SWIFT_NAME(transferredHeaders);
- (NSString*)transferredHeaders NS_SWIFT_NAME(transferredHeaders());

@property (nonatomic,readwrite,assign,getter=URL,setter=setURL:) NSString* URL NS_SWIFT_NAME(URL);
- (NSString*)URL NS_SWIFT_NAME(URL());
- (void)setURL:(NSString*)newURL NS_SWIFT_NAME(setURL(_:));

@property (nonatomic,readwrite,assign,getter=user,setter=setUser:) NSString* user NS_SWIFT_NAME(user);
- (NSString*)user NS_SWIFT_NAME(user());
- (void)setUser:(NSString*)newUser NS_SWIFT_NAME(setUser(_:));

@property (nonatomic,readwrite,assign,getter=validate,setter=setValidate:) BOOL validate NS_SWIFT_NAME(validate);
- (BOOL)validate NS_SWIFT_NAME(validate());
- (void)setValidate:(BOOL)newValidate NS_SWIFT_NAME(setValidate(_:));

@property (nonatomic,readonly,assign,getter=attrCount) int attrCount NS_SWIFT_NAME(attrCount);
- (int)attrCount NS_SWIFT_NAME(attrCount());

- (NSString*)attrName:(int)attrIndex NS_SWIFT_NAME(attrName(_:));

- (NSString*)attrNamespace:(int)attrIndex NS_SWIFT_NAME(attrNamespace(_:));

- (NSString*)attrPrefix:(int)attrIndex NS_SWIFT_NAME(attrPrefix(_:));

- (NSString*)attrValue:(int)attrIndex NS_SWIFT_NAME(attrValue(_:));

@property (nonatomic,readonly,assign,getter=XChildCount) int XChildCount NS_SWIFT_NAME(XChildCount);
- (int)XChildCount NS_SWIFT_NAME(XChildCount());

- (NSString*)XChildName:(int)xChildIndex NS_SWIFT_NAME(XChildName(_:));

- (NSString*)XChildNamespace:(int)xChildIndex NS_SWIFT_NAME(XChildNamespace(_:));

- (NSString*)XChildPrefix:(int)xChildIndex NS_SWIFT_NAME(XChildPrefix(_:));

- (NSString*)XChildXText:(int)xChildIndex NS_SWIFT_NAME(XChildXText(_:));

@property (nonatomic,readonly,assign,getter=XElement) NSString* XElement NS_SWIFT_NAME(XElement);
- (NSString*)XElement NS_SWIFT_NAME(XElement());

@property (nonatomic,readwrite,assign,getter=XErrorPath,setter=setXErrorPath:) NSString* XErrorPath NS_SWIFT_NAME(XErrorPath);
- (NSString*)XErrorPath NS_SWIFT_NAME(XErrorPath());
- (void)setXErrorPath:(NSString*)newXErrorPath NS_SWIFT_NAME(setXErrorPath(_:));

@property (nonatomic,readonly,assign,getter=XNamespace) NSString* XNamespace NS_SWIFT_NAME(XNamespace);
- (NSString*)XNamespace NS_SWIFT_NAME(XNamespace());

@property (nonatomic,readonly,assign,getter=XParent) NSString* XParent NS_SWIFT_NAME(XParent);
- (NSString*)XParent NS_SWIFT_NAME(XParent());

@property (nonatomic,readwrite,assign,getter=XPath,setter=setXPath:) NSString* XPath NS_SWIFT_NAME(XPath);
- (NSString*)XPath NS_SWIFT_NAME(XPath());
- (void)setXPath:(NSString*)newXPath NS_SWIFT_NAME(setXPath(_:));

@property (nonatomic,readonly,assign,getter=XPrefix) NSString* XPrefix NS_SWIFT_NAME(XPrefix);
- (NSString*)XPrefix NS_SWIFT_NAME(XPrefix());

@property (nonatomic,readonly,assign,getter=XSubTree) NSString* XSubTree NS_SWIFT_NAME(XSubTree);
- (NSString*)XSubTree NS_SWIFT_NAME(XSubTree());

@property (nonatomic,readonly,assign,getter=XText) NSString* XText NS_SWIFT_NAME(XText);
- (NSString*)XText NS_SWIFT_NAME(XText());

  /* Methods */

- (void)addCookie:(NSString*)cookieName :(NSString*)cookieValue NS_SWIFT_NAME(addCookie(_:_:));
- (NSString*)attr:(NSString*)attrName NS_SWIFT_NAME(attr(_:));
- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)delete:(NSString*)URL NS_SWIFT_NAME(delete(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)get:(NSString*)URL NS_SWIFT_NAME(get(_:));
- (BOOL)hasXPath:(NSString*)XPath NS_SWIFT_NAME(hasXPath(_:));
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)post:(NSString*)URL NS_SWIFT_NAME(post(_:));
- (void)put:(NSString*)URL NS_SWIFT_NAME(put(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (BOOL)tryXPath:(NSString*)xpath NS_SWIFT_NAME(tryXPath(_:));

@end


