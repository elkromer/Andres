
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

//ATOMTEXTTYPES
#define TT_TEXT                                            0
#define TT_HTML                                            1
#define TT_XHTML                                           2

//FIREWALLTYPES
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TODATAVERSION
#define OD_V2                                              0
#define OD_V3                                              1
#define OD_V4                                              2
#define OD_AUTO                                            3

//PROXYSSLTYPES
#define PS_AUTOMATIC                                       0
#define PS_ALWAYS                                          1
#define PS_NEVER                                           2
#define PS_TUNNEL                                          3

//ASSOCIATIONMULTIPLICITIES
#define NM_ZERO_ONE                                        0
#define NM_ONE                                             1
#define NM_MANY                                            2

//ASSOCIATIONDELETEACTIONS
#define DA_NONE                                            0
#define DA_CASCADE                                         1
#define DA_SET_NULL                                        2
#define DA_SET_DEFAULT                                     3

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

@protocol IPWorksODataDelegate <NSObject>
@optional
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onEntity:(NSString*)name NS_SWIFT_NAME(onEntity(_:));
- (void)onEntry:(NSString*)id :(NSString*)title :(NSString*)summary :(NSString*)ETag NS_SWIFT_NAME(onEntry(_:_:_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType NS_SWIFT_NAME(onLog(_:_:_:));
- (void)onProperty:(NSString*)name :(NSString*)typeName :(BOOL)nullable NS_SWIFT_NAME(onProperty(_:_:_:));
- (void)onSetCookie:(NSString*)name :(NSString*)value :(NSString*)expires :(NSString*)domain :(NSString*)path :(BOOL)secure NS_SWIFT_NAME(onSetCookie(_:_:_:_:_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onStatus:(NSString*)HTTPVersion :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onStatus(_:_:_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text NS_SWIFT_NAME(onTransfer(_:_:_:_:));
@end

@interface IPWorksOData : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksODataDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnected;
  BOOL m_delegateHasDisconnected;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasEntity;
  BOOL m_delegateHasEntry;
  BOOL m_delegateHasError;
  BOOL m_delegateHasHeader;
  BOOL m_delegateHasLog;
  BOOL m_delegateHasProperty;
  BOOL m_delegateHasSetCookie;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
  BOOL m_delegateHasStartTransfer;
  BOOL m_delegateHasStatus;
  BOOL m_delegateHasTransfer;
}

+ (IPWorksOData*)odata;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksODataDelegate> delegate;
- (id <IPWorksODataDelegate>)delegate;
- (void) setDelegate:(id <IPWorksODataDelegate>)anObject;

  /* Events */

- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onEntity:(NSString*)name NS_SWIFT_NAME(onEntity(_:));
- (void)onEntry:(NSString*)id :(NSString*)title :(NSString*)summary :(NSString*)ETag NS_SWIFT_NAME(onEntry(_:_:_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType NS_SWIFT_NAME(onLog(_:_:_:));
- (void)onProperty:(NSString*)name :(NSString*)typeName :(BOOL)nullable NS_SWIFT_NAME(onProperty(_:_:_:));
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

@property (nonatomic,readwrite,assign,getter=authorization,setter=setAuthorization:) NSString* authorization NS_SWIFT_NAME(authorization);
- (NSString*)authorization NS_SWIFT_NAME(authorization());
- (void)setAuthorization:(NSString*)newAuthorization NS_SWIFT_NAME(setAuthorization(_:));

@property (nonatomic,readwrite,assign,getter=authScheme,setter=setAuthScheme:) int authScheme NS_SWIFT_NAME(authScheme);
- (int)authScheme NS_SWIFT_NAME(authScheme());
- (void)setAuthScheme:(int)newAuthScheme NS_SWIFT_NAME(setAuthScheme(_:));

@property (nonatomic,readwrite,assign,getter=channelAuthorEmail,setter=setChannelAuthorEmail:) NSString* channelAuthorEmail NS_SWIFT_NAME(channelAuthorEmail);
- (NSString*)channelAuthorEmail NS_SWIFT_NAME(channelAuthorEmail());
- (void)setChannelAuthorEmail:(NSString*)newChannelAuthorEmail NS_SWIFT_NAME(setChannelAuthorEmail(_:));

@property (nonatomic,readwrite,assign,getter=channelAuthorName,setter=setChannelAuthorName:) NSString* channelAuthorName NS_SWIFT_NAME(channelAuthorName);
- (NSString*)channelAuthorName NS_SWIFT_NAME(channelAuthorName());
- (void)setChannelAuthorName:(NSString*)newChannelAuthorName NS_SWIFT_NAME(setChannelAuthorName(_:));

@property (nonatomic,readwrite,assign,getter=channelAuthorUri,setter=setChannelAuthorUri:) NSString* channelAuthorUri NS_SWIFT_NAME(channelAuthorUri);
- (NSString*)channelAuthorUri NS_SWIFT_NAME(channelAuthorUri());
- (void)setChannelAuthorUri:(NSString*)newChannelAuthorUri NS_SWIFT_NAME(setChannelAuthorUri(_:));

@property (nonatomic,readwrite,assign,getter=channelCategoryLabel,setter=setChannelCategoryLabel:) NSString* channelCategoryLabel NS_SWIFT_NAME(channelCategoryLabel);
- (NSString*)channelCategoryLabel NS_SWIFT_NAME(channelCategoryLabel());
- (void)setChannelCategoryLabel:(NSString*)newChannelCategoryLabel NS_SWIFT_NAME(setChannelCategoryLabel(_:));

@property (nonatomic,readwrite,assign,getter=channelCategoryScheme,setter=setChannelCategoryScheme:) NSString* channelCategoryScheme NS_SWIFT_NAME(channelCategoryScheme);
- (NSString*)channelCategoryScheme NS_SWIFT_NAME(channelCategoryScheme());
- (void)setChannelCategoryScheme:(NSString*)newChannelCategoryScheme NS_SWIFT_NAME(setChannelCategoryScheme(_:));

@property (nonatomic,readwrite,assign,getter=channelCategoryTerm,setter=setChannelCategoryTerm:) NSString* channelCategoryTerm NS_SWIFT_NAME(channelCategoryTerm);
- (NSString*)channelCategoryTerm NS_SWIFT_NAME(channelCategoryTerm());
- (void)setChannelCategoryTerm:(NSString*)newChannelCategoryTerm NS_SWIFT_NAME(setChannelCategoryTerm(_:));

@property (nonatomic,readwrite,assign,getter=channelContributorEmail,setter=setChannelContributorEmail:) NSString* channelContributorEmail NS_SWIFT_NAME(channelContributorEmail);
- (NSString*)channelContributorEmail NS_SWIFT_NAME(channelContributorEmail());
- (void)setChannelContributorEmail:(NSString*)newChannelContributorEmail NS_SWIFT_NAME(setChannelContributorEmail(_:));

@property (nonatomic,readwrite,assign,getter=channelContributorName,setter=setChannelContributorName:) NSString* channelContributorName NS_SWIFT_NAME(channelContributorName);
- (NSString*)channelContributorName NS_SWIFT_NAME(channelContributorName());
- (void)setChannelContributorName:(NSString*)newChannelContributorName NS_SWIFT_NAME(setChannelContributorName(_:));

@property (nonatomic,readwrite,assign,getter=channelContributorUri,setter=setChannelContributorUri:) NSString* channelContributorUri NS_SWIFT_NAME(channelContributorUri);
- (NSString*)channelContributorUri NS_SWIFT_NAME(channelContributorUri());
- (void)setChannelContributorUri:(NSString*)newChannelContributorUri NS_SWIFT_NAME(setChannelContributorUri(_:));

@property (nonatomic,readwrite,assign,getter=channelGenerator,setter=setChannelGenerator:) NSString* channelGenerator NS_SWIFT_NAME(channelGenerator);
- (NSString*)channelGenerator NS_SWIFT_NAME(channelGenerator());
- (void)setChannelGenerator:(NSString*)newChannelGenerator NS_SWIFT_NAME(setChannelGenerator(_:));

@property (nonatomic,readwrite,assign,getter=channelIcon,setter=setChannelIcon:) NSString* channelIcon NS_SWIFT_NAME(channelIcon);
- (NSString*)channelIcon NS_SWIFT_NAME(channelIcon());
- (void)setChannelIcon:(NSString*)newChannelIcon NS_SWIFT_NAME(setChannelIcon(_:));

@property (nonatomic,readwrite,assign,getter=channelId,setter=setChannelId:) NSString* channelId NS_SWIFT_NAME(channelId);
- (NSString*)channelId NS_SWIFT_NAME(channelId());
- (void)setChannelId:(NSString*)newChannelId NS_SWIFT_NAME(setChannelId(_:));

@property (nonatomic,readwrite,assign,getter=channelLinkHref,setter=setChannelLinkHref:) NSString* channelLinkHref NS_SWIFT_NAME(channelLinkHref);
- (NSString*)channelLinkHref NS_SWIFT_NAME(channelLinkHref());
- (void)setChannelLinkHref:(NSString*)newChannelLinkHref NS_SWIFT_NAME(setChannelLinkHref(_:));

@property (nonatomic,readwrite,assign,getter=channelLinkHrefLang,setter=setChannelLinkHrefLang:) NSString* channelLinkHrefLang NS_SWIFT_NAME(channelLinkHrefLang);
- (NSString*)channelLinkHrefLang NS_SWIFT_NAME(channelLinkHrefLang());
- (void)setChannelLinkHrefLang:(NSString*)newChannelLinkHrefLang NS_SWIFT_NAME(setChannelLinkHrefLang(_:));

@property (nonatomic,readwrite,assign,getter=channelLinkLength,setter=setChannelLinkLength:) NSString* channelLinkLength NS_SWIFT_NAME(channelLinkLength);
- (NSString*)channelLinkLength NS_SWIFT_NAME(channelLinkLength());
- (void)setChannelLinkLength:(NSString*)newChannelLinkLength NS_SWIFT_NAME(setChannelLinkLength(_:));

@property (nonatomic,readwrite,assign,getter=channelLinkRel,setter=setChannelLinkRel:) NSString* channelLinkRel NS_SWIFT_NAME(channelLinkRel);
- (NSString*)channelLinkRel NS_SWIFT_NAME(channelLinkRel());
- (void)setChannelLinkRel:(NSString*)newChannelLinkRel NS_SWIFT_NAME(setChannelLinkRel(_:));

@property (nonatomic,readwrite,assign,getter=channelLinkTitle,setter=setChannelLinkTitle:) NSString* channelLinkTitle NS_SWIFT_NAME(channelLinkTitle);
- (NSString*)channelLinkTitle NS_SWIFT_NAME(channelLinkTitle());
- (void)setChannelLinkTitle:(NSString*)newChannelLinkTitle NS_SWIFT_NAME(setChannelLinkTitle(_:));

@property (nonatomic,readwrite,assign,getter=channelLinkType,setter=setChannelLinkType:) NSString* channelLinkType NS_SWIFT_NAME(channelLinkType);
- (NSString*)channelLinkType NS_SWIFT_NAME(channelLinkType());
- (void)setChannelLinkType:(NSString*)newChannelLinkType NS_SWIFT_NAME(setChannelLinkType(_:));

@property (nonatomic,readwrite,assign,getter=channelLogo,setter=setChannelLogo:) NSString* channelLogo NS_SWIFT_NAME(channelLogo);
- (NSString*)channelLogo NS_SWIFT_NAME(channelLogo());
- (void)setChannelLogo:(NSString*)newChannelLogo NS_SWIFT_NAME(setChannelLogo(_:));

@property (nonatomic,readwrite,assign,getter=channelRights,setter=setChannelRights:) NSString* channelRights NS_SWIFT_NAME(channelRights);
- (NSString*)channelRights NS_SWIFT_NAME(channelRights());
- (void)setChannelRights:(NSString*)newChannelRights NS_SWIFT_NAME(setChannelRights(_:));

@property (nonatomic,readwrite,assign,getter=channelRightsTextType,setter=setChannelRightsTextType:) int channelRightsTextType NS_SWIFT_NAME(channelRightsTextType);
- (int)channelRightsTextType NS_SWIFT_NAME(channelRightsTextType());
- (void)setChannelRightsTextType:(int)newChannelRightsTextType NS_SWIFT_NAME(setChannelRightsTextType(_:));

@property (nonatomic,readwrite,assign,getter=channelSubtitle,setter=setChannelSubtitle:) NSString* channelSubtitle NS_SWIFT_NAME(channelSubtitle);
- (NSString*)channelSubtitle NS_SWIFT_NAME(channelSubtitle());
- (void)setChannelSubtitle:(NSString*)newChannelSubtitle NS_SWIFT_NAME(setChannelSubtitle(_:));

@property (nonatomic,readwrite,assign,getter=channelSubtitleTextType,setter=setChannelSubtitleTextType:) int channelSubtitleTextType NS_SWIFT_NAME(channelSubtitleTextType);
- (int)channelSubtitleTextType NS_SWIFT_NAME(channelSubtitleTextType());
- (void)setChannelSubtitleTextType:(int)newChannelSubtitleTextType NS_SWIFT_NAME(setChannelSubtitleTextType(_:));

@property (nonatomic,readwrite,assign,getter=channelTitle,setter=setChannelTitle:) NSString* channelTitle NS_SWIFT_NAME(channelTitle);
- (NSString*)channelTitle NS_SWIFT_NAME(channelTitle());
- (void)setChannelTitle:(NSString*)newChannelTitle NS_SWIFT_NAME(setChannelTitle(_:));

@property (nonatomic,readwrite,assign,getter=channelTitleTextType,setter=setChannelTitleTextType:) int channelTitleTextType NS_SWIFT_NAME(channelTitleTextType);
- (int)channelTitleTextType NS_SWIFT_NAME(channelTitleTextType());
- (void)setChannelTitleTextType:(int)newChannelTitleTextType NS_SWIFT_NAME(setChannelTitleTextType(_:));

@property (nonatomic,readwrite,assign,getter=channelUpdated,setter=setChannelUpdated:) NSString* channelUpdated NS_SWIFT_NAME(channelUpdated);
- (NSString*)channelUpdated NS_SWIFT_NAME(channelUpdated());
- (void)setChannelUpdated:(NSString*)newChannelUpdated NS_SWIFT_NAME(setChannelUpdated(_:));

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

@property (nonatomic,readwrite,assign,getter=entryAuthor,setter=setEntryAuthor:) NSString* entryAuthor NS_SWIFT_NAME(entryAuthor);
- (NSString*)entryAuthor NS_SWIFT_NAME(entryAuthor());
- (void)setEntryAuthor:(NSString*)newEntryAuthor NS_SWIFT_NAME(setEntryAuthor(_:));

@property (nonatomic,readonly,assign,getter=entryCount) int entryCount NS_SWIFT_NAME(entryCount);
- (int)entryCount NS_SWIFT_NAME(entryCount());

@property (nonatomic,readwrite,assign,getter=entryETag,setter=setEntryETag:) NSString* entryETag NS_SWIFT_NAME(entryETag);
- (NSString*)entryETag NS_SWIFT_NAME(entryETag());
- (void)setEntryETag:(NSString*)newEntryETag NS_SWIFT_NAME(setEntryETag(_:));

@property (nonatomic,readwrite,assign,getter=entryId,setter=setEntryId:) NSString* entryId NS_SWIFT_NAME(entryId);
- (NSString*)entryId NS_SWIFT_NAME(entryId());
- (void)setEntryId:(NSString*)newEntryId NS_SWIFT_NAME(setEntryId(_:));

@property (nonatomic,readwrite,assign,getter=entryIndex,setter=setEntryIndex:) int entryIndex NS_SWIFT_NAME(entryIndex);
- (int)entryIndex NS_SWIFT_NAME(entryIndex());
- (void)setEntryIndex:(int)newEntryIndex NS_SWIFT_NAME(setEntryIndex(_:));

@property (nonatomic,readwrite,assign,getter=entryLinksCount,setter=setEntryLinksCount:) int entryLinksCount NS_SWIFT_NAME(entryLinksCount);
- (int)entryLinksCount NS_SWIFT_NAME(entryLinksCount());
- (void)setEntryLinksCount:(int)newEntryLinksCount NS_SWIFT_NAME(setEntryLinksCount(_:));

- (NSString*)entryLinksResourcePath:(int)entryLinksIndex NS_SWIFT_NAME(entryLinksResourcePath(_:));

- (NSString*)entryLinksTitle:(int)entryLinksIndex NS_SWIFT_NAME(entryLinksTitle(_:));

@property (nonatomic,readwrite,assign,getter=entryPropertiesCount,setter=setEntryPropertiesCount:) int entryPropertiesCount NS_SWIFT_NAME(entryPropertiesCount);
- (int)entryPropertiesCount NS_SWIFT_NAME(entryPropertiesCount());
- (void)setEntryPropertiesCount:(int)newEntryPropertiesCount NS_SWIFT_NAME(setEntryPropertiesCount(_:));

- (NSString*)entryPropertiesAttributes:(int)entryPropertiesIndex NS_SWIFT_NAME(entryPropertiesAttributes(_:));
- (void)setEntryPropertiesAttributes:(int)entryPropertiesIndex:(NSString*)newEntryPropertiesAttributes NS_SWIFT_NAME(setEntryPropertiesAttributes(_:_:));

- (BOOL)entryPropertiesIsNull:(int)entryPropertiesIndex NS_SWIFT_NAME(entryPropertiesIsNull(_:));
- (void)setEntryPropertiesIsNull:(int)entryPropertiesIndex:(BOOL)newEntryPropertiesIsNull NS_SWIFT_NAME(setEntryPropertiesIsNull(_:_:));

- (NSString*)entryPropertiesName:(int)entryPropertiesIndex NS_SWIFT_NAME(entryPropertiesName(_:));
- (void)setEntryPropertiesName:(int)entryPropertiesIndex:(NSString*)newEntryPropertiesName NS_SWIFT_NAME(setEntryPropertiesName(_:_:));

- (NSString*)entryPropertiesType:(int)entryPropertiesIndex NS_SWIFT_NAME(entryPropertiesType(_:));
- (void)setEntryPropertiesType:(int)entryPropertiesIndex:(NSString*)newEntryPropertiesType NS_SWIFT_NAME(setEntryPropertiesType(_:_:));

- (NSString*)entryPropertiesValue:(int)entryPropertiesIndex NS_SWIFT_NAME(entryPropertiesValue(_:));
- (void)setEntryPropertiesValue:(int)entryPropertiesIndex:(NSString*)newEntryPropertiesValue NS_SWIFT_NAME(setEntryPropertiesValue(_:_:));

- (NSString*)entryPropertiesXPath:(int)entryPropertiesIndex NS_SWIFT_NAME(entryPropertiesXPath(_:));

@property (nonatomic,readwrite,assign,getter=entrySummary,setter=setEntrySummary:) NSString* entrySummary NS_SWIFT_NAME(entrySummary);
- (NSString*)entrySummary NS_SWIFT_NAME(entrySummary());
- (void)setEntrySummary:(NSString*)newEntrySummary NS_SWIFT_NAME(setEntrySummary(_:));

@property (nonatomic,readwrite,assign,getter=entryTitle,setter=setEntryTitle:) NSString* entryTitle NS_SWIFT_NAME(entryTitle);
- (NSString*)entryTitle NS_SWIFT_NAME(entryTitle());
- (void)setEntryTitle:(NSString*)newEntryTitle NS_SWIFT_NAME(setEntryTitle(_:));

@property (nonatomic,readwrite,assign,getter=entryType,setter=setEntryType:) NSString* entryType NS_SWIFT_NAME(entryType);
- (NSString*)entryType NS_SWIFT_NAME(entryType());
- (void)setEntryType:(NSString*)newEntryType NS_SWIFT_NAME(setEntryType(_:));

@property (nonatomic,readonly,assign,getter=entryUpdated) NSString* entryUpdated NS_SWIFT_NAME(entryUpdated);
- (NSString*)entryUpdated NS_SWIFT_NAME(entryUpdated());

@property (nonatomic,readwrite,assign,getter=entryXML,setter=setEntryXML:) NSString* entryXML NS_SWIFT_NAME(entryXML);
- (NSString*)entryXML NS_SWIFT_NAME(entryXML());
- (void)setEntryXML:(NSString*)newEntryXML NS_SWIFT_NAME(setEntryXML(_:));

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

@property (nonatomic,readwrite,assign,getter=ODataVersion,setter=setODataVersion:) int ODataVersion NS_SWIFT_NAME(ODataVersion);
- (int)ODataVersion NS_SWIFT_NAME(ODataVersion());
- (void)setODataVersion:(int)newODataVersion NS_SWIFT_NAME(setODataVersion(_:));

@property (nonatomic,readwrite,assign,getter=otherHeaders,setter=setOtherHeaders:) NSString* otherHeaders NS_SWIFT_NAME(otherHeaders);
- (NSString*)otherHeaders NS_SWIFT_NAME(otherHeaders());
- (void)setOtherHeaders:(NSString*)newOtherHeaders NS_SWIFT_NAME(setOtherHeaders(_:));

@property (nonatomic,readwrite,assign,getter=otherQueryOptions,setter=setOtherQueryOptions:) NSString* otherQueryOptions NS_SWIFT_NAME(otherQueryOptions);
- (NSString*)otherQueryOptions NS_SWIFT_NAME(otherQueryOptions());
- (void)setOtherQueryOptions:(NSString*)newOtherQueryOptions NS_SWIFT_NAME(setOtherQueryOptions(_:));

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

@property (nonatomic,readwrite,assign,getter=queryFilter,setter=setQueryFilter:) NSString* queryFilter NS_SWIFT_NAME(queryFilter);
- (NSString*)queryFilter NS_SWIFT_NAME(queryFilter());
- (void)setQueryFilter:(NSString*)newQueryFilter NS_SWIFT_NAME(setQueryFilter(_:));

@property (nonatomic,readwrite,assign,getter=queryOrderBy,setter=setQueryOrderBy:) NSString* queryOrderBy NS_SWIFT_NAME(queryOrderBy);
- (NSString*)queryOrderBy NS_SWIFT_NAME(queryOrderBy());
- (void)setQueryOrderBy:(NSString*)newQueryOrderBy NS_SWIFT_NAME(setQueryOrderBy(_:));

@property (nonatomic,readwrite,assign,getter=querySelect,setter=setQuerySelect:) NSString* querySelect NS_SWIFT_NAME(querySelect);
- (NSString*)querySelect NS_SWIFT_NAME(querySelect());
- (void)setQuerySelect:(NSString*)newQuerySelect NS_SWIFT_NAME(setQuerySelect(_:));

@property (nonatomic,readwrite,assign,getter=querySkip,setter=setQuerySkip:) NSString* querySkip NS_SWIFT_NAME(querySkip);
- (NSString*)querySkip NS_SWIFT_NAME(querySkip());
- (void)setQuerySkip:(NSString*)newQuerySkip NS_SWIFT_NAME(setQuerySkip(_:));

@property (nonatomic,readwrite,assign,getter=querySkipToken,setter=setQuerySkipToken:) NSString* querySkipToken NS_SWIFT_NAME(querySkipToken);
- (NSString*)querySkipToken NS_SWIFT_NAME(querySkipToken());
- (void)setQuerySkipToken:(NSString*)newQuerySkipToken NS_SWIFT_NAME(setQuerySkipToken(_:));

@property (nonatomic,readwrite,assign,getter=queryTop,setter=setQueryTop:) NSString* queryTop NS_SWIFT_NAME(queryTop);
- (NSString*)queryTop NS_SWIFT_NAME(queryTop());
- (void)setQueryTop:(NSString*)newQueryTop NS_SWIFT_NAME(setQueryTop(_:));

@property (nonatomic,readwrite,assign,getter=resourcePath,setter=setResourcePath:) NSString* resourcePath NS_SWIFT_NAME(resourcePath);
- (NSString*)resourcePath NS_SWIFT_NAME(resourcePath());
- (void)setResourcePath:(NSString*)newResourcePath NS_SWIFT_NAME(setResourcePath(_:));

@property (nonatomic,readonly,assign,getter=schemaAssociationContainsTarget) BOOL schemaAssociationContainsTarget NS_SWIFT_NAME(schemaAssociationContainsTarget);
- (BOOL)schemaAssociationContainsTarget NS_SWIFT_NAME(schemaAssociationContainsTarget());

@property (nonatomic,readonly,assign,getter=schemaAssociationDescription) NSString* schemaAssociationDescription NS_SWIFT_NAME(schemaAssociationDescription);
- (NSString*)schemaAssociationDescription NS_SWIFT_NAME(schemaAssociationDescription());

@property (nonatomic,readonly,assign,getter=schemaAssociationFromRole) NSString* schemaAssociationFromRole NS_SWIFT_NAME(schemaAssociationFromRole);
- (NSString*)schemaAssociationFromRole NS_SWIFT_NAME(schemaAssociationFromRole());

@property (nonatomic,readonly,assign,getter=schemaAssociationFromRoleDescription) NSString* schemaAssociationFromRoleDescription NS_SWIFT_NAME(schemaAssociationFromRoleDescription);
- (NSString*)schemaAssociationFromRoleDescription NS_SWIFT_NAME(schemaAssociationFromRoleDescription());

@property (nonatomic,readonly,assign,getter=schemaAssociationFromRoleEntity) NSString* schemaAssociationFromRoleEntity NS_SWIFT_NAME(schemaAssociationFromRoleEntity);
- (NSString*)schemaAssociationFromRoleEntity NS_SWIFT_NAME(schemaAssociationFromRoleEntity());

@property (nonatomic,readonly,assign,getter=schemaAssociationFromRoleMultiplicity) int schemaAssociationFromRoleMultiplicity NS_SWIFT_NAME(schemaAssociationFromRoleMultiplicity);
- (int)schemaAssociationFromRoleMultiplicity NS_SWIFT_NAME(schemaAssociationFromRoleMultiplicity());

@property (nonatomic,readonly,assign,getter=schemaAssociationFromRoleSummary) NSString* schemaAssociationFromRoleSummary NS_SWIFT_NAME(schemaAssociationFromRoleSummary);
- (NSString*)schemaAssociationFromRoleSummary NS_SWIFT_NAME(schemaAssociationFromRoleSummary());

@property (nonatomic,readonly,assign,getter=schemaAssociationName) NSString* schemaAssociationName NS_SWIFT_NAME(schemaAssociationName);
- (NSString*)schemaAssociationName NS_SWIFT_NAME(schemaAssociationName());

@property (nonatomic,readonly,assign,getter=schemaAssociationNullable) BOOL schemaAssociationNullable NS_SWIFT_NAME(schemaAssociationNullable);
- (BOOL)schemaAssociationNullable NS_SWIFT_NAME(schemaAssociationNullable());

@property (nonatomic,readonly,assign,getter=schemaAssociationOnDelete) int schemaAssociationOnDelete NS_SWIFT_NAME(schemaAssociationOnDelete);
- (int)schemaAssociationOnDelete NS_SWIFT_NAME(schemaAssociationOnDelete());

@property (nonatomic,readonly,assign,getter=schemaAssociationPartner) NSString* schemaAssociationPartner NS_SWIFT_NAME(schemaAssociationPartner);
- (NSString*)schemaAssociationPartner NS_SWIFT_NAME(schemaAssociationPartner());

@property (nonatomic,readonly,assign,getter=schemaAssociationRefConstraintCount) int schemaAssociationRefConstraintCount NS_SWIFT_NAME(schemaAssociationRefConstraintCount);
- (int)schemaAssociationRefConstraintCount NS_SWIFT_NAME(schemaAssociationRefConstraintCount());

@property (nonatomic,readwrite,assign,getter=schemaAssociationRefConstraintIndex,setter=setSchemaAssociationRefConstraintIndex:) int schemaAssociationRefConstraintIndex NS_SWIFT_NAME(schemaAssociationRefConstraintIndex);
- (int)schemaAssociationRefConstraintIndex NS_SWIFT_NAME(schemaAssociationRefConstraintIndex());
- (void)setSchemaAssociationRefConstraintIndex:(int)newSchemaAssociationRefConstraintIndex NS_SWIFT_NAME(setSchemaAssociationRefConstraintIndex(_:));

@property (nonatomic,readonly,assign,getter=schemaAssociationRefConstraintProperty) NSString* schemaAssociationRefConstraintProperty NS_SWIFT_NAME(schemaAssociationRefConstraintProperty);
- (NSString*)schemaAssociationRefConstraintProperty NS_SWIFT_NAME(schemaAssociationRefConstraintProperty());

@property (nonatomic,readonly,assign,getter=schemaAssociationRefConstraintReferencedProperty) NSString* schemaAssociationRefConstraintReferencedProperty NS_SWIFT_NAME(schemaAssociationRefConstraintReferencedProperty);
- (NSString*)schemaAssociationRefConstraintReferencedProperty NS_SWIFT_NAME(schemaAssociationRefConstraintReferencedProperty());

@property (nonatomic,readonly,assign,getter=schemaAssociationRelationship) NSString* schemaAssociationRelationship NS_SWIFT_NAME(schemaAssociationRelationship);
- (NSString*)schemaAssociationRelationship NS_SWIFT_NAME(schemaAssociationRelationship());

@property (nonatomic,readonly,assign,getter=schemaAssociationSummary) NSString* schemaAssociationSummary NS_SWIFT_NAME(schemaAssociationSummary);
- (NSString*)schemaAssociationSummary NS_SWIFT_NAME(schemaAssociationSummary());

@property (nonatomic,readonly,assign,getter=schemaAssociationToRole) NSString* schemaAssociationToRole NS_SWIFT_NAME(schemaAssociationToRole);
- (NSString*)schemaAssociationToRole NS_SWIFT_NAME(schemaAssociationToRole());

@property (nonatomic,readonly,assign,getter=schemaAssociationToRoleDescription) NSString* schemaAssociationToRoleDescription NS_SWIFT_NAME(schemaAssociationToRoleDescription);
- (NSString*)schemaAssociationToRoleDescription NS_SWIFT_NAME(schemaAssociationToRoleDescription());

@property (nonatomic,readonly,assign,getter=schemaAssociationToRoleEntity) NSString* schemaAssociationToRoleEntity NS_SWIFT_NAME(schemaAssociationToRoleEntity);
- (NSString*)schemaAssociationToRoleEntity NS_SWIFT_NAME(schemaAssociationToRoleEntity());

@property (nonatomic,readonly,assign,getter=schemaAssociationToRoleMultiplicity) int schemaAssociationToRoleMultiplicity NS_SWIFT_NAME(schemaAssociationToRoleMultiplicity);
- (int)schemaAssociationToRoleMultiplicity NS_SWIFT_NAME(schemaAssociationToRoleMultiplicity());

@property (nonatomic,readonly,assign,getter=schemaAssociationToRoleSummary) NSString* schemaAssociationToRoleSummary NS_SWIFT_NAME(schemaAssociationToRoleSummary);
- (NSString*)schemaAssociationToRoleSummary NS_SWIFT_NAME(schemaAssociationToRoleSummary());

@property (nonatomic,readonly,assign,getter=schemaAssociationType) NSString* schemaAssociationType NS_SWIFT_NAME(schemaAssociationType);
- (NSString*)schemaAssociationType NS_SWIFT_NAME(schemaAssociationType());

@property (nonatomic,readonly,assign,getter=schemaAssociationCount) int schemaAssociationCount NS_SWIFT_NAME(schemaAssociationCount);
- (int)schemaAssociationCount NS_SWIFT_NAME(schemaAssociationCount());

@property (nonatomic,readwrite,assign,getter=schemaAssociationIndex,setter=setSchemaAssociationIndex:) int schemaAssociationIndex NS_SWIFT_NAME(schemaAssociationIndex);
- (int)schemaAssociationIndex NS_SWIFT_NAME(schemaAssociationIndex());
- (void)setSchemaAssociationIndex:(int)newSchemaAssociationIndex NS_SWIFT_NAME(setSchemaAssociationIndex(_:));

@property (nonatomic,readonly,assign,getter=schemaEntityDescription) NSString* schemaEntityDescription NS_SWIFT_NAME(schemaEntityDescription);
- (NSString*)schemaEntityDescription NS_SWIFT_NAME(schemaEntityDescription());

@property (nonatomic,readonly,assign,getter=schemaEntityName) NSString* schemaEntityName NS_SWIFT_NAME(schemaEntityName);
- (NSString*)schemaEntityName NS_SWIFT_NAME(schemaEntityName());

@property (nonatomic,readonly,assign,getter=schemaEntitySummary) NSString* schemaEntitySummary NS_SWIFT_NAME(schemaEntitySummary);
- (NSString*)schemaEntitySummary NS_SWIFT_NAME(schemaEntitySummary());

@property (nonatomic,readonly,assign,getter=schemaEntityCount) int schemaEntityCount NS_SWIFT_NAME(schemaEntityCount);
- (int)schemaEntityCount NS_SWIFT_NAME(schemaEntityCount());

@property (nonatomic,readwrite,assign,getter=schemaEntityIndex,setter=setSchemaEntityIndex:) int schemaEntityIndex NS_SWIFT_NAME(schemaEntityIndex);
- (int)schemaEntityIndex NS_SWIFT_NAME(schemaEntityIndex());
- (void)setSchemaEntityIndex:(int)newSchemaEntityIndex NS_SWIFT_NAME(setSchemaEntityIndex(_:));

@property (nonatomic,readonly,assign,getter=schemaKeysCount) int schemaKeysCount NS_SWIFT_NAME(schemaKeysCount);
- (int)schemaKeysCount NS_SWIFT_NAME(schemaKeysCount());

- (NSString*)schemaKeys:(int)schemaKeysIndex NS_SWIFT_NAME(schemaKeys(_:));

@property (nonatomic,readonly,assign,getter=schemaPropertyAttributes) NSString* schemaPropertyAttributes NS_SWIFT_NAME(schemaPropertyAttributes);
- (NSString*)schemaPropertyAttributes NS_SWIFT_NAME(schemaPropertyAttributes());

@property (nonatomic,readonly,assign,getter=schemaPropertyDescription) NSString* schemaPropertyDescription NS_SWIFT_NAME(schemaPropertyDescription);
- (NSString*)schemaPropertyDescription NS_SWIFT_NAME(schemaPropertyDescription());

@property (nonatomic,readonly,assign,getter=schemaPropertyIsComplexType) BOOL schemaPropertyIsComplexType NS_SWIFT_NAME(schemaPropertyIsComplexType);
- (BOOL)schemaPropertyIsComplexType NS_SWIFT_NAME(schemaPropertyIsComplexType());

@property (nonatomic,readonly,assign,getter=schemaPropertyName) NSString* schemaPropertyName NS_SWIFT_NAME(schemaPropertyName);
- (NSString*)schemaPropertyName NS_SWIFT_NAME(schemaPropertyName());

@property (nonatomic,readonly,assign,getter=schemaPropertyNullable) BOOL schemaPropertyNullable NS_SWIFT_NAME(schemaPropertyNullable);
- (BOOL)schemaPropertyNullable NS_SWIFT_NAME(schemaPropertyNullable());

@property (nonatomic,readonly,assign,getter=schemaPropertySummary) NSString* schemaPropertySummary NS_SWIFT_NAME(schemaPropertySummary);
- (NSString*)schemaPropertySummary NS_SWIFT_NAME(schemaPropertySummary());

@property (nonatomic,readonly,assign,getter=schemaPropertyType) NSString* schemaPropertyType NS_SWIFT_NAME(schemaPropertyType);
- (NSString*)schemaPropertyType NS_SWIFT_NAME(schemaPropertyType());

@property (nonatomic,readonly,assign,getter=schemaPropertyCount) int schemaPropertyCount NS_SWIFT_NAME(schemaPropertyCount);
- (int)schemaPropertyCount NS_SWIFT_NAME(schemaPropertyCount());

@property (nonatomic,readwrite,assign,getter=schemaPropertyIndex,setter=setSchemaPropertyIndex:) int schemaPropertyIndex NS_SWIFT_NAME(schemaPropertyIndex);
- (int)schemaPropertyIndex NS_SWIFT_NAME(schemaPropertyIndex());
- (void)setSchemaPropertyIndex:(int)newSchemaPropertyIndex NS_SWIFT_NAME(setSchemaPropertyIndex(_:));

@property (nonatomic,readonly,assign,getter=schemaTypeFieldAttributes) NSString* schemaTypeFieldAttributes NS_SWIFT_NAME(schemaTypeFieldAttributes);
- (NSString*)schemaTypeFieldAttributes NS_SWIFT_NAME(schemaTypeFieldAttributes());

@property (nonatomic,readonly,assign,getter=schemaTypeFieldDescription) NSString* schemaTypeFieldDescription NS_SWIFT_NAME(schemaTypeFieldDescription);
- (NSString*)schemaTypeFieldDescription NS_SWIFT_NAME(schemaTypeFieldDescription());

@property (nonatomic,readonly,assign,getter=schemaTypeFieldIsComplexType) BOOL schemaTypeFieldIsComplexType NS_SWIFT_NAME(schemaTypeFieldIsComplexType);
- (BOOL)schemaTypeFieldIsComplexType NS_SWIFT_NAME(schemaTypeFieldIsComplexType());

@property (nonatomic,readonly,assign,getter=schemaTypeFieldName) NSString* schemaTypeFieldName NS_SWIFT_NAME(schemaTypeFieldName);
- (NSString*)schemaTypeFieldName NS_SWIFT_NAME(schemaTypeFieldName());

@property (nonatomic,readonly,assign,getter=schemaTypeFieldNullable) BOOL schemaTypeFieldNullable NS_SWIFT_NAME(schemaTypeFieldNullable);
- (BOOL)schemaTypeFieldNullable NS_SWIFT_NAME(schemaTypeFieldNullable());

@property (nonatomic,readonly,assign,getter=schemaTypeFieldSummary) NSString* schemaTypeFieldSummary NS_SWIFT_NAME(schemaTypeFieldSummary);
- (NSString*)schemaTypeFieldSummary NS_SWIFT_NAME(schemaTypeFieldSummary());

@property (nonatomic,readonly,assign,getter=schemaTypeFieldType) NSString* schemaTypeFieldType NS_SWIFT_NAME(schemaTypeFieldType);
- (NSString*)schemaTypeFieldType NS_SWIFT_NAME(schemaTypeFieldType());

@property (nonatomic,readonly,assign,getter=schemaTypeFieldCount) int schemaTypeFieldCount NS_SWIFT_NAME(schemaTypeFieldCount);
- (int)schemaTypeFieldCount NS_SWIFT_NAME(schemaTypeFieldCount());

@property (nonatomic,readwrite,assign,getter=schemaTypeFieldIndex,setter=setSchemaTypeFieldIndex:) int schemaTypeFieldIndex NS_SWIFT_NAME(schemaTypeFieldIndex);
- (int)schemaTypeFieldIndex NS_SWIFT_NAME(schemaTypeFieldIndex());
- (void)setSchemaTypeFieldIndex:(int)newSchemaTypeFieldIndex NS_SWIFT_NAME(setSchemaTypeFieldIndex(_:));

@property (nonatomic,readwrite,assign,getter=serviceRootURI,setter=setServiceRootURI:) NSString* serviceRootURI NS_SWIFT_NAME(serviceRootURI);
- (NSString*)serviceRootURI NS_SWIFT_NAME(serviceRootURI());
- (void)setServiceRootURI:(NSString*)newServiceRootURI NS_SWIFT_NAME(setServiceRootURI(_:));

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

@property (nonatomic,readwrite,assign,getter=user,setter=setUser:) NSString* user NS_SWIFT_NAME(user);
- (NSString*)user NS_SWIFT_NAME(user());
- (void)setUser:(NSString*)newUser NS_SWIFT_NAME(setUser(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)createEntry NS_SWIFT_NAME(createEntry());
- (void)customRequest:(NSString*)HTTPMethod :(NSString*)URL :(NSString*)postData NS_SWIFT_NAME(customRequest(_:_:_:));
- (void)deleteEntry NS_SWIFT_NAME(deleteEntry());
- (NSString*)getEntryProperty:(NSString*)XPath NS_SWIFT_NAME(getEntryProperty(_:));
- (void)getSchema NS_SWIFT_NAME(getSchema());
- (BOOL)hasXPath:(NSString*)XPath NS_SWIFT_NAME(hasXPath(_:));
- (void)queryService NS_SWIFT_NAME(queryService());
- (void)reset NS_SWIFT_NAME(reset());
- (void)setEntryProperty:(NSString*)XPath :(NSString*)value NS_SWIFT_NAME(setEntryProperty(_:_:));
- (void)setSchemaEntity:(NSString*)name NS_SWIFT_NAME(setSchemaEntity(_:));
- (void)setSchemaProperty:(NSString*)name NS_SWIFT_NAME(setSchemaProperty(_:));
- (void)setSchemaType:(NSString*)name NS_SWIFT_NAME(setSchemaType(_:));
- (void)updateEntry NS_SWIFT_NAME(updateEntry());
- (void)updateProperty:(NSString*)XPath :(NSString*)value NS_SWIFT_NAME(updateProperty(_:_:));

@end


