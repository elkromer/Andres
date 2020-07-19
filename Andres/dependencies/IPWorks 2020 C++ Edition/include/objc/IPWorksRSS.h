
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

//TRSSVERSION
#define RSS_VERSION_UNDEFINED                              0
#define RSS_VERSION_091                                    1
#define RSS_VERSION_092                                    2
#define RSS_VERSION_200                                    3

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

@protocol IPWorksRSSDelegate <NSObject>
@optional
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType NS_SWIFT_NAME(onLog(_:_:_:));
- (void)onOPMLHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onOPMLHeader(_:_:));
- (void)onOPMLOutline:(int)level :(NSString*)text :(NSString*)typeName :(NSString*)title :(NSString*)URL :(NSString*)XMLURL :(NSString*)HTMLURL :(NSString*)created :(NSString*)description :(NSString*)otherAttrs NS_SWIFT_NAME(onOPMLOutline(_:_:_:_:_:_:_:_:_:_:));
- (void)onRedirect:(NSString*)location :(int*)accept NS_SWIFT_NAME(onRedirect(_:_:));
- (void)onSetCookie:(NSString*)name :(NSString*)value :(NSString*)expires :(NSString*)domain :(NSString*)path :(BOOL)secure NS_SWIFT_NAME(onSetCookie(_:_:_:_:_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onStatus:(NSString*)HTTPVersion :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onStatus(_:_:_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text NS_SWIFT_NAME(onTransfer(_:_:_:_:));
@end

@interface IPWorksRSS : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksRSSDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnected;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasDisconnected;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasError;
  BOOL m_delegateHasHeader;
  BOOL m_delegateHasLog;
  BOOL m_delegateHasOPMLHeader;
  BOOL m_delegateHasOPMLOutline;
  BOOL m_delegateHasRedirect;
  BOOL m_delegateHasSetCookie;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
  BOOL m_delegateHasStartTransfer;
  BOOL m_delegateHasStatus;
  BOOL m_delegateHasTransfer;
}

+ (IPWorksRSS*)rss;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksRSSDelegate> delegate;
- (id <IPWorksRSSDelegate>)delegate;
- (void) setDelegate:(id <IPWorksRSSDelegate>)anObject;

  /* Events */

- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType NS_SWIFT_NAME(onLog(_:_:_:));
- (void)onOPMLHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onOPMLHeader(_:_:));
- (void)onOPMLOutline:(int)level :(NSString*)text :(NSString*)typeName :(NSString*)title :(NSString*)URL :(NSString*)XMLURL :(NSString*)HTMLURL :(NSString*)created :(NSString*)description :(NSString*)otherAttrs NS_SWIFT_NAME(onOPMLOutline(_:_:_:_:_:_:_:_:_:_:));
- (void)onRedirect:(NSString*)location :(int*)accept NS_SWIFT_NAME(onRedirect(_:_:));
- (void)onSetCookie:(NSString*)name :(NSString*)value :(NSString*)expires :(NSString*)domain :(NSString*)path :(BOOL)secure NS_SWIFT_NAME(onSetCookie(_:_:_:_:_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
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

@property (nonatomic,readwrite,assign,getter=channelCategory,setter=setChannelCategory:) NSString* channelCategory NS_SWIFT_NAME(channelCategory);
- (NSString*)channelCategory NS_SWIFT_NAME(channelCategory());
- (void)setChannelCategory:(NSString*)newChannelCategory NS_SWIFT_NAME(setChannelCategory(_:));

@property (nonatomic,readwrite,assign,getter=channelCategoryDomain,setter=setChannelCategoryDomain:) NSString* channelCategoryDomain NS_SWIFT_NAME(channelCategoryDomain);
- (NSString*)channelCategoryDomain NS_SWIFT_NAME(channelCategoryDomain());
- (void)setChannelCategoryDomain:(NSString*)newChannelCategoryDomain NS_SWIFT_NAME(setChannelCategoryDomain(_:));

@property (nonatomic,readwrite,assign,getter=channelCopyright,setter=setChannelCopyright:) NSString* channelCopyright NS_SWIFT_NAME(channelCopyright);
- (NSString*)channelCopyright NS_SWIFT_NAME(channelCopyright());
- (void)setChannelCopyright:(NSString*)newChannelCopyright NS_SWIFT_NAME(setChannelCopyright(_:));

@property (nonatomic,readwrite,assign,getter=channelDescription,setter=setChannelDescription:) NSString* channelDescription NS_SWIFT_NAME(channelDescription);
- (NSString*)channelDescription NS_SWIFT_NAME(channelDescription());
- (void)setChannelDescription:(NSString*)newChannelDescription NS_SWIFT_NAME(setChannelDescription(_:));

@property (nonatomic,readwrite,assign,getter=channelDocs,setter=setChannelDocs:) NSString* channelDocs NS_SWIFT_NAME(channelDocs);
- (NSString*)channelDocs NS_SWIFT_NAME(channelDocs());
- (void)setChannelDocs:(NSString*)newChannelDocs NS_SWIFT_NAME(setChannelDocs(_:));

@property (nonatomic,readwrite,assign,getter=channelGenerator,setter=setChannelGenerator:) NSString* channelGenerator NS_SWIFT_NAME(channelGenerator);
- (NSString*)channelGenerator NS_SWIFT_NAME(channelGenerator());
- (void)setChannelGenerator:(NSString*)newChannelGenerator NS_SWIFT_NAME(setChannelGenerator(_:));

@property (nonatomic,readwrite,assign,getter=channelImageDescription,setter=setChannelImageDescription:) NSString* channelImageDescription NS_SWIFT_NAME(channelImageDescription);
- (NSString*)channelImageDescription NS_SWIFT_NAME(channelImageDescription());
- (void)setChannelImageDescription:(NSString*)newChannelImageDescription NS_SWIFT_NAME(setChannelImageDescription(_:));

@property (nonatomic,readwrite,assign,getter=channelImageHeight,setter=setChannelImageHeight:) NSString* channelImageHeight NS_SWIFT_NAME(channelImageHeight);
- (NSString*)channelImageHeight NS_SWIFT_NAME(channelImageHeight());
- (void)setChannelImageHeight:(NSString*)newChannelImageHeight NS_SWIFT_NAME(setChannelImageHeight(_:));

@property (nonatomic,readwrite,assign,getter=channelImageLink,setter=setChannelImageLink:) NSString* channelImageLink NS_SWIFT_NAME(channelImageLink);
- (NSString*)channelImageLink NS_SWIFT_NAME(channelImageLink());
- (void)setChannelImageLink:(NSString*)newChannelImageLink NS_SWIFT_NAME(setChannelImageLink(_:));

@property (nonatomic,readwrite,assign,getter=channelImageTitle,setter=setChannelImageTitle:) NSString* channelImageTitle NS_SWIFT_NAME(channelImageTitle);
- (NSString*)channelImageTitle NS_SWIFT_NAME(channelImageTitle());
- (void)setChannelImageTitle:(NSString*)newChannelImageTitle NS_SWIFT_NAME(setChannelImageTitle(_:));

@property (nonatomic,readwrite,assign,getter=channelImageUrl,setter=setChannelImageUrl:) NSString* channelImageUrl NS_SWIFT_NAME(channelImageUrl);
- (NSString*)channelImageUrl NS_SWIFT_NAME(channelImageUrl());
- (void)setChannelImageUrl:(NSString*)newChannelImageUrl NS_SWIFT_NAME(setChannelImageUrl(_:));

@property (nonatomic,readwrite,assign,getter=channelImageWidth,setter=setChannelImageWidth:) NSString* channelImageWidth NS_SWIFT_NAME(channelImageWidth);
- (NSString*)channelImageWidth NS_SWIFT_NAME(channelImageWidth());
- (void)setChannelImageWidth:(NSString*)newChannelImageWidth NS_SWIFT_NAME(setChannelImageWidth(_:));

@property (nonatomic,readwrite,assign,getter=channelLanguage,setter=setChannelLanguage:) NSString* channelLanguage NS_SWIFT_NAME(channelLanguage);
- (NSString*)channelLanguage NS_SWIFT_NAME(channelLanguage());
- (void)setChannelLanguage:(NSString*)newChannelLanguage NS_SWIFT_NAME(setChannelLanguage(_:));

@property (nonatomic,readwrite,assign,getter=channelLastBuildDate,setter=setChannelLastBuildDate:) NSString* channelLastBuildDate NS_SWIFT_NAME(channelLastBuildDate);
- (NSString*)channelLastBuildDate NS_SWIFT_NAME(channelLastBuildDate());
- (void)setChannelLastBuildDate:(NSString*)newChannelLastBuildDate NS_SWIFT_NAME(setChannelLastBuildDate(_:));

@property (nonatomic,readwrite,assign,getter=channelLink,setter=setChannelLink:) NSString* channelLink NS_SWIFT_NAME(channelLink);
- (NSString*)channelLink NS_SWIFT_NAME(channelLink());
- (void)setChannelLink:(NSString*)newChannelLink NS_SWIFT_NAME(setChannelLink(_:));

@property (nonatomic,readwrite,assign,getter=channelManagingEditor,setter=setChannelManagingEditor:) NSString* channelManagingEditor NS_SWIFT_NAME(channelManagingEditor);
- (NSString*)channelManagingEditor NS_SWIFT_NAME(channelManagingEditor());
- (void)setChannelManagingEditor:(NSString*)newChannelManagingEditor NS_SWIFT_NAME(setChannelManagingEditor(_:));

@property (nonatomic,readwrite,assign,getter=channelPubDate,setter=setChannelPubDate:) NSString* channelPubDate NS_SWIFT_NAME(channelPubDate);
- (NSString*)channelPubDate NS_SWIFT_NAME(channelPubDate());
- (void)setChannelPubDate:(NSString*)newChannelPubDate NS_SWIFT_NAME(setChannelPubDate(_:));

@property (nonatomic,readwrite,assign,getter=channelSkipDays,setter=setChannelSkipDays:) NSString* channelSkipDays NS_SWIFT_NAME(channelSkipDays);
- (NSString*)channelSkipDays NS_SWIFT_NAME(channelSkipDays());
- (void)setChannelSkipDays:(NSString*)newChannelSkipDays NS_SWIFT_NAME(setChannelSkipDays(_:));

@property (nonatomic,readwrite,assign,getter=channelSkipHours,setter=setChannelSkipHours:) NSString* channelSkipHours NS_SWIFT_NAME(channelSkipHours);
- (NSString*)channelSkipHours NS_SWIFT_NAME(channelSkipHours());
- (void)setChannelSkipHours:(NSString*)newChannelSkipHours NS_SWIFT_NAME(setChannelSkipHours(_:));

@property (nonatomic,readwrite,assign,getter=channelTitle,setter=setChannelTitle:) NSString* channelTitle NS_SWIFT_NAME(channelTitle);
- (NSString*)channelTitle NS_SWIFT_NAME(channelTitle());
- (void)setChannelTitle:(NSString*)newChannelTitle NS_SWIFT_NAME(setChannelTitle(_:));

@property (nonatomic,readwrite,assign,getter=channelTtl,setter=setChannelTtl:) NSString* channelTtl NS_SWIFT_NAME(channelTtl);
- (NSString*)channelTtl NS_SWIFT_NAME(channelTtl());
- (void)setChannelTtl:(NSString*)newChannelTtl NS_SWIFT_NAME(setChannelTtl(_:));

@property (nonatomic,readwrite,assign,getter=channelWebMaster,setter=setChannelWebMaster:) NSString* channelWebMaster NS_SWIFT_NAME(channelWebMaster);
- (NSString*)channelWebMaster NS_SWIFT_NAME(channelWebMaster());
- (void)setChannelWebMaster:(NSString*)newChannelWebMaster NS_SWIFT_NAME(setChannelWebMaster(_:));

@property (nonatomic,readwrite,assign,getter=connected,setter=setConnected:) BOOL connected NS_SWIFT_NAME(connected);
- (BOOL)connected NS_SWIFT_NAME(connected());
- (void)setConnected:(BOOL)newConnected NS_SWIFT_NAME(setConnected(_:));

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

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readwrite,assign,getter=ifModifiedSince,setter=setIfModifiedSince:) NSString* ifModifiedSince NS_SWIFT_NAME(ifModifiedSince);
- (NSString*)ifModifiedSince NS_SWIFT_NAME(ifModifiedSince());
- (void)setIfModifiedSince:(NSString*)newIfModifiedSince NS_SWIFT_NAME(setIfModifiedSince(_:));

@property (nonatomic,readwrite,assign,getter=itemCount,setter=setItemCount:) int itemCount NS_SWIFT_NAME(itemCount);
- (int)itemCount NS_SWIFT_NAME(itemCount());
- (void)setItemCount:(int)newItemCount NS_SWIFT_NAME(setItemCount(_:));

- (NSString*)itemAuthor:(int)itemIndex NS_SWIFT_NAME(itemAuthor(_:));
- (void)setItemAuthor:(int)itemIndex:(NSString*)newItemAuthor NS_SWIFT_NAME(setItemAuthor(_:_:));

- (NSString*)itemCategory:(int)itemIndex NS_SWIFT_NAME(itemCategory(_:));
- (void)setItemCategory:(int)itemIndex:(NSString*)newItemCategory NS_SWIFT_NAME(setItemCategory(_:_:));

- (NSString*)itemCategoryDomain:(int)itemIndex NS_SWIFT_NAME(itemCategoryDomain(_:));
- (void)setItemCategoryDomain:(int)itemIndex:(NSString*)newItemCategoryDomain NS_SWIFT_NAME(setItemCategoryDomain(_:_:));

- (NSString*)itemComments:(int)itemIndex NS_SWIFT_NAME(itemComments(_:));
- (void)setItemComments:(int)itemIndex:(NSString*)newItemComments NS_SWIFT_NAME(setItemComments(_:_:));

- (NSString*)itemDescription:(int)itemIndex NS_SWIFT_NAME(itemDescription(_:));
- (void)setItemDescription:(int)itemIndex:(NSString*)newItemDescription NS_SWIFT_NAME(setItemDescription(_:_:));

- (NSString*)itemEnclosureLength:(int)itemIndex NS_SWIFT_NAME(itemEnclosureLength(_:));
- (void)setItemEnclosureLength:(int)itemIndex:(NSString*)newItemEnclosureLength NS_SWIFT_NAME(setItemEnclosureLength(_:_:));

- (NSString*)itemEnclosureType:(int)itemIndex NS_SWIFT_NAME(itemEnclosureType(_:));
- (void)setItemEnclosureType:(int)itemIndex:(NSString*)newItemEnclosureType NS_SWIFT_NAME(setItemEnclosureType(_:_:));

- (NSString*)itemEnclosureUrl:(int)itemIndex NS_SWIFT_NAME(itemEnclosureUrl(_:));
- (void)setItemEnclosureUrl:(int)itemIndex:(NSString*)newItemEnclosureUrl NS_SWIFT_NAME(setItemEnclosureUrl(_:_:));

- (NSString*)itemGuid:(int)itemIndex NS_SWIFT_NAME(itemGuid(_:));
- (void)setItemGuid:(int)itemIndex:(NSString*)newItemGuid NS_SWIFT_NAME(setItemGuid(_:_:));

- (BOOL)itemGuidIsPermaLink:(int)itemIndex NS_SWIFT_NAME(itemGuidIsPermaLink(_:));
- (void)setItemGuidIsPermaLink:(int)itemIndex:(BOOL)newItemGuidIsPermaLink NS_SWIFT_NAME(setItemGuidIsPermaLink(_:_:));

- (NSString*)itemXML:(int)itemIndex NS_SWIFT_NAME(itemXML(_:));
- (void)setItemXML:(int)itemIndex:(NSString*)newItemXML NS_SWIFT_NAME(setItemXML(_:_:));

- (NSString*)itemLink:(int)itemIndex NS_SWIFT_NAME(itemLink(_:));
- (void)setItemLink:(int)itemIndex:(NSString*)newItemLink NS_SWIFT_NAME(setItemLink(_:_:));

- (NSString*)itemPubDate:(int)itemIndex NS_SWIFT_NAME(itemPubDate(_:));
- (void)setItemPubDate:(int)itemIndex:(NSString*)newItemPubDate NS_SWIFT_NAME(setItemPubDate(_:_:));

- (NSString*)itemSource:(int)itemIndex NS_SWIFT_NAME(itemSource(_:));
- (void)setItemSource:(int)itemIndex:(NSString*)newItemSource NS_SWIFT_NAME(setItemSource(_:_:));

- (NSString*)itemSourceURL:(int)itemIndex NS_SWIFT_NAME(itemSourceURL(_:));
- (void)setItemSourceURL:(int)itemIndex:(NSString*)newItemSourceURL NS_SWIFT_NAME(setItemSourceURL(_:_:));

- (NSString*)itemTitle:(int)itemIndex NS_SWIFT_NAME(itemTitle(_:));
- (void)setItemTitle:(int)itemIndex:(NSString*)newItemTitle NS_SWIFT_NAME(setItemTitle(_:_:));

@property (nonatomic,readwrite,assign,getter=localFile,setter=setLocalFile:) NSString* localFile NS_SWIFT_NAME(localFile);
- (NSString*)localFile NS_SWIFT_NAME(localFile());
- (void)setLocalFile:(NSString*)newLocalFile NS_SWIFT_NAME(setLocalFile(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

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

@property (nonatomic,readonly,assign,getter=parsedHeaderCount) int parsedHeaderCount NS_SWIFT_NAME(parsedHeaderCount);
- (int)parsedHeaderCount NS_SWIFT_NAME(parsedHeaderCount());

- (NSString*)parsedHeaderField:(int)parsedHeaderIndex NS_SWIFT_NAME(parsedHeaderField(_:));

- (NSString*)parsedHeaderValue:(int)parsedHeaderIndex NS_SWIFT_NAME(parsedHeaderValue(_:));

@property (nonatomic,readwrite,assign,getter=password,setter=setPassword:) NSString* password NS_SWIFT_NAME(password);
- (NSString*)password NS_SWIFT_NAME(password());
- (void)setPassword:(NSString*)newPassword NS_SWIFT_NAME(setPassword(_:));

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

@property (nonatomic,readwrite,assign,getter=RSSData,setter=setRSSData:) NSString* RSSData NS_SWIFT_NAME(RSSData);
- (NSString*)RSSData NS_SWIFT_NAME(RSSData());
- (void)setRSSData:(NSString*)newRSSData NS_SWIFT_NAME(setRSSData(_:));

@property (nonatomic,readwrite,assign,getter=RSSVersion,setter=setRSSVersion:) int RSSVersion NS_SWIFT_NAME(RSSVersion);
- (int)RSSVersion NS_SWIFT_NAME(RSSVersion());
- (void)setRSSVersion:(int)newRSSVersion NS_SWIFT_NAME(setRSSVersion(_:));

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

@property (nonatomic,readwrite,assign,getter=user,setter=setUser:) NSString* user NS_SWIFT_NAME(user);
- (NSString*)user NS_SWIFT_NAME(user());
- (void)setUser:(NSString*)newUser NS_SWIFT_NAME(setUser(_:));

  /* Methods */

- (void)addCookie:(NSString*)cookieName :(NSString*)cookieValue NS_SWIFT_NAME(addCookie(_:_:));
- (void)addItem:(NSString*)title :(NSString*)description :(NSString*)link NS_SWIFT_NAME(addItem(_:_:_:));
- (void)addNamespace:(NSString*)prefix :(NSString*)namespaceURI NS_SWIFT_NAME(addNamespace(_:_:));
- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)getFeed:(NSString*)URL NS_SWIFT_NAME(getFeed(_:));
- (NSString*)getProperty:(NSString*)propertyName NS_SWIFT_NAME(getProperty(_:));
- (void)getURL:(NSString*)URL NS_SWIFT_NAME(getURL(_:));
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (NSString*)OPMLAttr:(NSString*)attrName NS_SWIFT_NAME(OPMLAttr(_:));
- (void)put:(NSString*)URL NS_SWIFT_NAME(put(_:));
- (void)readFile:(NSString*)fileName NS_SWIFT_NAME(readFile(_:));
- (void)readOPML:(NSString*)OPMLFile NS_SWIFT_NAME(readOPML(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)setProperty:(NSString*)propertyName :(NSString*)propertyValue NS_SWIFT_NAME(setProperty(_:_:));
- (void)writeFile:(NSString*)filename NS_SWIFT_NAME(writeFile(_:));

@end


