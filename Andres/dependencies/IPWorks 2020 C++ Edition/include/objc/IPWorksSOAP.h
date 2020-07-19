
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

//TVALUEFORMAT
#define VF_TEXT                                            0
#define VF_XML                                             1
#define VF_FULL_XML                                        2


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksSOAPDelegate <NSObject>
@optional
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType NS_SWIFT_NAME(onLog(_:_:_:));
- (void)onRedirect:(NSString*)location :(int*)accept NS_SWIFT_NAME(onRedirect(_:_:));
- (void)onSetCookie:(NSString*)name :(NSString*)value :(NSString*)expires :(NSString*)domain :(NSString*)path :(BOOL)secure NS_SWIFT_NAME(onSetCookie(_:_:_:_:_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onStatus:(NSString*)HTTPVersion :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onStatus(_:_:_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone NS_SWIFT_NAME(onTransfer(_:_:_:));
@end

@interface IPWorksSOAP : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksSOAPDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnected;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasDisconnected;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasError;
  BOOL m_delegateHasHeader;
  BOOL m_delegateHasLog;
  BOOL m_delegateHasRedirect;
  BOOL m_delegateHasSetCookie;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
  BOOL m_delegateHasStartTransfer;
  BOOL m_delegateHasStatus;
  BOOL m_delegateHasTransfer;
}

+ (IPWorksSOAP*)soap;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksSOAPDelegate> delegate;
- (id <IPWorksSOAPDelegate>)delegate;
- (void) setDelegate:(id <IPWorksSOAPDelegate>)anObject;

  /* Events */

- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType NS_SWIFT_NAME(onLog(_:_:_:));
- (void)onRedirect:(NSString*)location :(int*)accept NS_SWIFT_NAME(onRedirect(_:_:));
- (void)onSetCookie:(NSString*)name :(NSString*)value :(NSString*)expires :(NSString*)domain :(NSString*)path :(BOOL)secure NS_SWIFT_NAME(onSetCookie(_:_:_:_:_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onStatus:(NSString*)HTTPVersion :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onStatus(_:_:_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone NS_SWIFT_NAME(onTransfer(_:_:_:));

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

@property (nonatomic,readwrite,assign,getter=actionURI,setter=setActionURI:) NSString* actionURI NS_SWIFT_NAME(actionURI);
- (NSString*)actionURI NS_SWIFT_NAME(actionURI());
- (void)setActionURI:(NSString*)newActionURI NS_SWIFT_NAME(setActionURI(_:));

@property (nonatomic,readwrite,assign,getter=authorization,setter=setAuthorization:) NSString* authorization NS_SWIFT_NAME(authorization);
- (NSString*)authorization NS_SWIFT_NAME(authorization());
- (void)setAuthorization:(NSString*)newAuthorization NS_SWIFT_NAME(setAuthorization(_:));

@property (nonatomic,readwrite,assign,getter=authScheme,setter=setAuthScheme:) int authScheme NS_SWIFT_NAME(authScheme);
- (int)authScheme NS_SWIFT_NAME(authScheme());
- (void)setAuthScheme:(int)newAuthScheme NS_SWIFT_NAME(setAuthScheme(_:));

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

@property (nonatomic,readonly,assign,getter=faultActor) NSString* faultActor NS_SWIFT_NAME(faultActor);
- (NSString*)faultActor NS_SWIFT_NAME(faultActor());

@property (nonatomic,readonly,assign,getter=faultCode) NSString* faultCode NS_SWIFT_NAME(faultCode);
- (NSString*)faultCode NS_SWIFT_NAME(faultCode());

@property (nonatomic,readonly,assign,getter=faultString) NSString* faultString NS_SWIFT_NAME(faultString);
- (NSString*)faultString NS_SWIFT_NAME(faultString());

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

@property (nonatomic,readwrite,assign,getter=method,setter=setMethod:) NSString* method NS_SWIFT_NAME(method);
- (NSString*)method NS_SWIFT_NAME(method());
- (void)setMethod:(NSString*)newMethod NS_SWIFT_NAME(setMethod(_:));

@property (nonatomic,readwrite,assign,getter=methodURI,setter=setMethodURI:) NSString* methodURI NS_SWIFT_NAME(methodURI);
- (NSString*)methodURI NS_SWIFT_NAME(methodURI());
- (void)setMethodURI:(NSString*)newMethodURI NS_SWIFT_NAME(setMethodURI(_:));

@property (nonatomic,readwrite,assign,getter=namespaceCount,setter=setNamespaceCount:) int namespaceCount NS_SWIFT_NAME(namespaceCount);
- (int)namespaceCount NS_SWIFT_NAME(namespaceCount());
- (void)setNamespaceCount:(int)newNamespaceCount NS_SWIFT_NAME(setNamespaceCount(_:));

- (NSString*)namespacePrefix:(int)namespaceIndex NS_SWIFT_NAME(namespacePrefix(_:));
- (void)setNamespacePrefix:(int)namespaceIndex:(NSString*)newNamespacePrefix NS_SWIFT_NAME(setNamespacePrefix(_:_:));

- (NSString*)namespaceURI:(int)namespaceIndex NS_SWIFT_NAME(namespaceURI(_:));
- (void)setNamespaceURI:(int)namespaceIndex:(NSString*)newNamespaceURI NS_SWIFT_NAME(setNamespaceURI(_:_:));

@property (nonatomic,readwrite,assign,getter=otherHeaders,setter=setOtherHeaders:) NSString* otherHeaders NS_SWIFT_NAME(otherHeaders);
- (NSString*)otherHeaders NS_SWIFT_NAME(otherHeaders());
- (void)setOtherHeaders:(NSString*)newOtherHeaders NS_SWIFT_NAME(setOtherHeaders(_:));

@property (nonatomic,readwrite,assign,getter=paramCount,setter=setParamCount:) int paramCount NS_SWIFT_NAME(paramCount);
- (int)paramCount NS_SWIFT_NAME(paramCount());
- (void)setParamCount:(int)newParamCount NS_SWIFT_NAME(setParamCount(_:));

- (NSString*)paramAttrs:(int)paramIndex NS_SWIFT_NAME(paramAttrs(_:));
- (void)setParamAttrs:(int)paramIndex:(NSString*)newParamAttrs NS_SWIFT_NAME(setParamAttrs(_:_:));

- (NSString*)paramName:(int)paramIndex NS_SWIFT_NAME(paramName(_:));
- (void)setParamName:(int)paramIndex:(NSString*)newParamName NS_SWIFT_NAME(setParamName(_:_:));

- (NSString*)paramValue:(int)paramIndex NS_SWIFT_NAME(paramValue(_:));
- (void)setParamValue:(int)paramIndex:(NSString*)newParamValue NS_SWIFT_NAME(setParamValue(_:_:));

@property (nonatomic,readonly,assign,getter=parsedHeaderCount) int parsedHeaderCount NS_SWIFT_NAME(parsedHeaderCount);
- (int)parsedHeaderCount NS_SWIFT_NAME(parsedHeaderCount());

- (NSString*)parsedHeaderField:(int)parsedHeaderIndex NS_SWIFT_NAME(parsedHeaderField(_:));

- (NSString*)parsedHeaderValue:(int)parsedHeaderIndex NS_SWIFT_NAME(parsedHeaderValue(_:));

@property (nonatomic,readwrite,assign,getter=password,setter=setPassword:) NSString* password NS_SWIFT_NAME(password);
- (NSString*)password NS_SWIFT_NAME(password());
- (void)setPassword:(NSString*)newPassword NS_SWIFT_NAME(setPassword(_:));

@property (nonatomic,readwrite,assign,getter=pragma,setter=setPragma:) NSString* pragma NS_SWIFT_NAME(pragma);
- (NSString*)pragma NS_SWIFT_NAME(pragma());
- (void)setPragma:(NSString*)newPragma NS_SWIFT_NAME(setPragma(_:));

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

@property (nonatomic,readonly,assign,getter=returnValue) NSString* returnValue NS_SWIFT_NAME(returnValue);
- (NSString*)returnValue NS_SWIFT_NAME(returnValue());

@property (nonatomic,readwrite,assign,getter=SOAPEncoding,setter=setSOAPEncoding:) NSString* SOAPEncoding NS_SWIFT_NAME(SOAPEncoding);
- (NSString*)SOAPEncoding NS_SWIFT_NAME(SOAPEncoding());
- (void)setSOAPEncoding:(NSString*)newSOAPEncoding NS_SWIFT_NAME(setSOAPEncoding(_:));

@property (nonatomic,readwrite,assign,getter=SOAPHeader,setter=setSOAPHeader:) NSString* SOAPHeader NS_SWIFT_NAME(SOAPHeader);
- (NSString*)SOAPHeader NS_SWIFT_NAME(SOAPHeader());
- (void)setSOAPHeader:(NSString*)newSOAPHeader NS_SWIFT_NAME(setSOAPHeader(_:));

@property (nonatomic,readwrite,assign,getter=SOAPPacket,setter=setSOAPPacket:) NSString* SOAPPacket NS_SWIFT_NAME(SOAPPacket);
- (NSString*)SOAPPacket NS_SWIFT_NAME(SOAPPacket());
- (void)setSOAPPacket:(NSString*)newSOAPPacket NS_SWIFT_NAME(setSOAPPacket(_:));

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

@property (nonatomic,readwrite,assign,getter=valueFormat,setter=setValueFormat:) int valueFormat NS_SWIFT_NAME(valueFormat);
- (int)valueFormat NS_SWIFT_NAME(valueFormat());
- (void)setValueFormat:(int)newValueFormat NS_SWIFT_NAME(setValueFormat(_:));

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

@property (nonatomic,readonly,assign,getter=XNamespace) NSString* XNamespace NS_SWIFT_NAME(XNamespace);
- (NSString*)XNamespace NS_SWIFT_NAME(XNamespace());

@property (nonatomic,readonly,assign,getter=XParent) NSString* XParent NS_SWIFT_NAME(XParent);
- (NSString*)XParent NS_SWIFT_NAME(XParent());

@property (nonatomic,readwrite,assign,getter=XPath,setter=setXPath:) NSString* XPath NS_SWIFT_NAME(XPath);
- (NSString*)XPath NS_SWIFT_NAME(XPath());
- (void)setXPath:(NSString*)newXPath NS_SWIFT_NAME(setXPath(_:));

@property (nonatomic,readonly,assign,getter=XPrefix) NSString* XPrefix NS_SWIFT_NAME(XPrefix);
- (NSString*)XPrefix NS_SWIFT_NAME(XPrefix());

@property (nonatomic,readonly,assign,getter=XText) NSString* XText NS_SWIFT_NAME(XText);
- (NSString*)XText NS_SWIFT_NAME(XText());

  /* Methods */

- (void)addCookie:(NSString*)cookieName :(NSString*)cookieValue NS_SWIFT_NAME(addCookie(_:_:));
- (void)addNamespace:(NSString*)prefix :(NSString*)namespaceURI NS_SWIFT_NAME(addNamespace(_:_:));
- (void)addParam:(NSString*)paramName :(NSString*)paramValue NS_SWIFT_NAME(addParam(_:_:));
- (NSString*)attr:(NSString*)attrName NS_SWIFT_NAME(attr(_:));
- (void)buildPacket NS_SWIFT_NAME(buildPacket());
- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)evalPacket NS_SWIFT_NAME(evalPacket());
- (BOOL)hasXPath:(NSString*)XPath NS_SWIFT_NAME(hasXPath(_:));
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)reset NS_SWIFT_NAME(reset());
- (void)sendPacket NS_SWIFT_NAME(sendPacket());
- (void)sendRequest NS_SWIFT_NAME(sendRequest());
- (BOOL)tryXPath:(NSString*)xpath NS_SWIFT_NAME(tryXPath(_:));
- (NSString*)value:(NSString*)paramName NS_SWIFT_NAME(value(_:));

@end


