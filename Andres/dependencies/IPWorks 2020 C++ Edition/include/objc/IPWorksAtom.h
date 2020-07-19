
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

@protocol IPWorksAtomDelegate <NSObject>
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
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text NS_SWIFT_NAME(onTransfer(_:_:_:_:));
@end

@interface IPWorksAtom : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksAtomDelegate> m_delegate;
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

+ (IPWorksAtom*)atom;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksAtomDelegate> delegate;
- (id <IPWorksAtomDelegate>)delegate;
- (void) setDelegate:(id <IPWorksAtomDelegate>)anObject;

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

@property (nonatomic,readwrite,assign,getter=atomData,setter=setAtomData:) NSString* atomData NS_SWIFT_NAME(atomData);
- (NSString*)atomData NS_SWIFT_NAME(atomData());
- (void)setAtomData:(NSString*)newAtomData NS_SWIFT_NAME(setAtomData(_:));

@property (nonatomic,readwrite,assign,getter=atomDataB,setter=setAtomDataB:) NSData* atomDataB NS_SWIFT_NAME(atomDataB);
- (NSData*)atomDataB NS_SWIFT_NAME(atomDataB());
- (void)setAtomDataB :(NSData*)newAtomData NS_SWIFT_NAME(setAtomDataB(_:));

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

@property (nonatomic,readwrite,assign,getter=entryCount,setter=setEntryCount:) int entryCount NS_SWIFT_NAME(entryCount);
- (int)entryCount NS_SWIFT_NAME(entryCount());
- (void)setEntryCount:(int)newEntryCount NS_SWIFT_NAME(setEntryCount(_:));

- (NSString*)entryAuthorEmail:(int)entryIndex NS_SWIFT_NAME(entryAuthorEmail(_:));
- (void)setEntryAuthorEmail:(int)entryIndex:(NSString*)newEntryAuthorEmail NS_SWIFT_NAME(setEntryAuthorEmail(_:_:));

- (NSString*)entryAuthorName:(int)entryIndex NS_SWIFT_NAME(entryAuthorName(_:));
- (void)setEntryAuthorName:(int)entryIndex:(NSString*)newEntryAuthorName NS_SWIFT_NAME(setEntryAuthorName(_:_:));

- (NSString*)entryAuthorUri:(int)entryIndex NS_SWIFT_NAME(entryAuthorUri(_:));
- (void)setEntryAuthorUri:(int)entryIndex:(NSString*)newEntryAuthorUri NS_SWIFT_NAME(setEntryAuthorUri(_:_:));

- (NSString*)entryCategoryLabel:(int)entryIndex NS_SWIFT_NAME(entryCategoryLabel(_:));
- (void)setEntryCategoryLabel:(int)entryIndex:(NSString*)newEntryCategoryLabel NS_SWIFT_NAME(setEntryCategoryLabel(_:_:));

- (NSString*)entryCategoryScheme:(int)entryIndex NS_SWIFT_NAME(entryCategoryScheme(_:));
- (void)setEntryCategoryScheme:(int)entryIndex:(NSString*)newEntryCategoryScheme NS_SWIFT_NAME(setEntryCategoryScheme(_:_:));

- (NSString*)entryCategoryTerm:(int)entryIndex NS_SWIFT_NAME(entryCategoryTerm(_:));
- (void)setEntryCategoryTerm:(int)entryIndex:(NSString*)newEntryCategoryTerm NS_SWIFT_NAME(setEntryCategoryTerm(_:_:));

- (NSString*)entryContent:(int)entryIndex NS_SWIFT_NAME(entryContent(_:));
- (void)setEntryContent:(int)entryIndex:(NSString*)newEntryContent NS_SWIFT_NAME(setEntryContent(_:_:));

- (int)entryContentTextType:(int)entryIndex NS_SWIFT_NAME(entryContentTextType(_:));
- (void)setEntryContentTextType:(int)entryIndex:(int)newEntryContentTextType NS_SWIFT_NAME(setEntryContentTextType(_:_:));

- (NSString*)entryContributorEmail:(int)entryIndex NS_SWIFT_NAME(entryContributorEmail(_:));
- (void)setEntryContributorEmail:(int)entryIndex:(NSString*)newEntryContributorEmail NS_SWIFT_NAME(setEntryContributorEmail(_:_:));

- (NSString*)entryContributorName:(int)entryIndex NS_SWIFT_NAME(entryContributorName(_:));
- (void)setEntryContributorName:(int)entryIndex:(NSString*)newEntryContributorName NS_SWIFT_NAME(setEntryContributorName(_:_:));

- (NSString*)entryContributorUri:(int)entryIndex NS_SWIFT_NAME(entryContributorUri(_:));
- (void)setEntryContributorUri:(int)entryIndex:(NSString*)newEntryContributorUri NS_SWIFT_NAME(setEntryContributorUri(_:_:));

- (NSString*)entryCopyright:(int)entryIndex NS_SWIFT_NAME(entryCopyright(_:));
- (void)setEntryCopyright:(int)entryIndex:(NSString*)newEntryCopyright NS_SWIFT_NAME(setEntryCopyright(_:_:));

- (NSString*)entryCreated:(int)entryIndex NS_SWIFT_NAME(entryCreated(_:));
- (void)setEntryCreated:(int)entryIndex:(NSString*)newEntryCreated NS_SWIFT_NAME(setEntryCreated(_:_:));

- (NSString*)entryXML:(int)entryIndex NS_SWIFT_NAME(entryXML(_:));
- (void)setEntryXML:(int)entryIndex:(NSString*)newEntryXML NS_SWIFT_NAME(setEntryXML(_:_:));

- (NSString*)entryId:(int)entryIndex NS_SWIFT_NAME(entryId(_:));
- (void)setEntryId:(int)entryIndex:(NSString*)newEntryId NS_SWIFT_NAME(setEntryId(_:_:));

- (NSString*)entryIssued:(int)entryIndex NS_SWIFT_NAME(entryIssued(_:));
- (void)setEntryIssued:(int)entryIndex:(NSString*)newEntryIssued NS_SWIFT_NAME(setEntryIssued(_:_:));

- (NSString*)entryLinkHref:(int)entryIndex NS_SWIFT_NAME(entryLinkHref(_:));
- (void)setEntryLinkHref:(int)entryIndex:(NSString*)newEntryLinkHref NS_SWIFT_NAME(setEntryLinkHref(_:_:));

- (NSString*)entryLinkHrefLang:(int)entryIndex NS_SWIFT_NAME(entryLinkHrefLang(_:));
- (void)setEntryLinkHrefLang:(int)entryIndex:(NSString*)newEntryLinkHrefLang NS_SWIFT_NAME(setEntryLinkHrefLang(_:_:));

- (NSString*)entryLinkLength:(int)entryIndex NS_SWIFT_NAME(entryLinkLength(_:));
- (void)setEntryLinkLength:(int)entryIndex:(NSString*)newEntryLinkLength NS_SWIFT_NAME(setEntryLinkLength(_:_:));

- (NSString*)entryLinkRel:(int)entryIndex NS_SWIFT_NAME(entryLinkRel(_:));
- (void)setEntryLinkRel:(int)entryIndex:(NSString*)newEntryLinkRel NS_SWIFT_NAME(setEntryLinkRel(_:_:));

- (NSString*)entryLinkTitle:(int)entryIndex NS_SWIFT_NAME(entryLinkTitle(_:));
- (void)setEntryLinkTitle:(int)entryIndex:(NSString*)newEntryLinkTitle NS_SWIFT_NAME(setEntryLinkTitle(_:_:));

- (NSString*)entryLinkType:(int)entryIndex NS_SWIFT_NAME(entryLinkType(_:));
- (void)setEntryLinkType:(int)entryIndex:(NSString*)newEntryLinkType NS_SWIFT_NAME(setEntryLinkType(_:_:));

- (NSString*)entryModified:(int)entryIndex NS_SWIFT_NAME(entryModified(_:));
- (void)setEntryModified:(int)entryIndex:(NSString*)newEntryModified NS_SWIFT_NAME(setEntryModified(_:_:));

- (NSString*)entryPublished:(int)entryIndex NS_SWIFT_NAME(entryPublished(_:));
- (void)setEntryPublished:(int)entryIndex:(NSString*)newEntryPublished NS_SWIFT_NAME(setEntryPublished(_:_:));

- (NSString*)entryRights:(int)entryIndex NS_SWIFT_NAME(entryRights(_:));
- (void)setEntryRights:(int)entryIndex:(NSString*)newEntryRights NS_SWIFT_NAME(setEntryRights(_:_:));

- (int)entryRightsTextType:(int)entryIndex NS_SWIFT_NAME(entryRightsTextType(_:));
- (void)setEntryRightsTextType:(int)entryIndex:(int)newEntryRightsTextType NS_SWIFT_NAME(setEntryRightsTextType(_:_:));

- (NSString*)entrySource:(int)entryIndex NS_SWIFT_NAME(entrySource(_:));
- (void)setEntrySource:(int)entryIndex:(NSString*)newEntrySource NS_SWIFT_NAME(setEntrySource(_:_:));

- (NSString*)entrySummary:(int)entryIndex NS_SWIFT_NAME(entrySummary(_:));
- (void)setEntrySummary:(int)entryIndex:(NSString*)newEntrySummary NS_SWIFT_NAME(setEntrySummary(_:_:));

- (int)entrySummaryTextType:(int)entryIndex NS_SWIFT_NAME(entrySummaryTextType(_:));
- (void)setEntrySummaryTextType:(int)entryIndex:(int)newEntrySummaryTextType NS_SWIFT_NAME(setEntrySummaryTextType(_:_:));

- (NSString*)entryTitle:(int)entryIndex NS_SWIFT_NAME(entryTitle(_:));
- (void)setEntryTitle:(int)entryIndex:(NSString*)newEntryTitle NS_SWIFT_NAME(setEntryTitle(_:_:));

- (int)entryTitleTextType:(int)entryIndex NS_SWIFT_NAME(entryTitleTextType(_:));
- (void)setEntryTitleTextType:(int)entryIndex:(int)newEntryTitleTextType NS_SWIFT_NAME(setEntryTitleTextType(_:_:));

- (NSString*)entryUpdated:(int)entryIndex NS_SWIFT_NAME(entryUpdated(_:));
- (void)setEntryUpdated:(int)entryIndex:(NSString*)newEntryUpdated NS_SWIFT_NAME(setEntryUpdated(_:_:));

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

@property (nonatomic,readwrite,assign,getter=slug,setter=setSlug:) NSString* slug NS_SWIFT_NAME(slug);
- (NSString*)slug NS_SWIFT_NAME(slug());
- (void)setSlug:(NSString*)newSlug NS_SWIFT_NAME(setSlug(_:));

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

@property (nonatomic,readwrite,assign,getter=updateEntryAuthorEmail,setter=setUpdateEntryAuthorEmail:) NSString* updateEntryAuthorEmail NS_SWIFT_NAME(updateEntryAuthorEmail);
- (NSString*)updateEntryAuthorEmail NS_SWIFT_NAME(updateEntryAuthorEmail());
- (void)setUpdateEntryAuthorEmail:(NSString*)newUpdateEntryAuthorEmail NS_SWIFT_NAME(setUpdateEntryAuthorEmail(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryAuthorName,setter=setUpdateEntryAuthorName:) NSString* updateEntryAuthorName NS_SWIFT_NAME(updateEntryAuthorName);
- (NSString*)updateEntryAuthorName NS_SWIFT_NAME(updateEntryAuthorName());
- (void)setUpdateEntryAuthorName:(NSString*)newUpdateEntryAuthorName NS_SWIFT_NAME(setUpdateEntryAuthorName(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryAuthorUri,setter=setUpdateEntryAuthorUri:) NSString* updateEntryAuthorUri NS_SWIFT_NAME(updateEntryAuthorUri);
- (NSString*)updateEntryAuthorUri NS_SWIFT_NAME(updateEntryAuthorUri());
- (void)setUpdateEntryAuthorUri:(NSString*)newUpdateEntryAuthorUri NS_SWIFT_NAME(setUpdateEntryAuthorUri(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryCategoryLabel,setter=setUpdateEntryCategoryLabel:) NSString* updateEntryCategoryLabel NS_SWIFT_NAME(updateEntryCategoryLabel);
- (NSString*)updateEntryCategoryLabel NS_SWIFT_NAME(updateEntryCategoryLabel());
- (void)setUpdateEntryCategoryLabel:(NSString*)newUpdateEntryCategoryLabel NS_SWIFT_NAME(setUpdateEntryCategoryLabel(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryCategoryScheme,setter=setUpdateEntryCategoryScheme:) NSString* updateEntryCategoryScheme NS_SWIFT_NAME(updateEntryCategoryScheme);
- (NSString*)updateEntryCategoryScheme NS_SWIFT_NAME(updateEntryCategoryScheme());
- (void)setUpdateEntryCategoryScheme:(NSString*)newUpdateEntryCategoryScheme NS_SWIFT_NAME(setUpdateEntryCategoryScheme(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryCategoryTerm,setter=setUpdateEntryCategoryTerm:) NSString* updateEntryCategoryTerm NS_SWIFT_NAME(updateEntryCategoryTerm);
- (NSString*)updateEntryCategoryTerm NS_SWIFT_NAME(updateEntryCategoryTerm());
- (void)setUpdateEntryCategoryTerm:(NSString*)newUpdateEntryCategoryTerm NS_SWIFT_NAME(setUpdateEntryCategoryTerm(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryContent,setter=setUpdateEntryContent:) NSString* updateEntryContent NS_SWIFT_NAME(updateEntryContent);
- (NSString*)updateEntryContent NS_SWIFT_NAME(updateEntryContent());
- (void)setUpdateEntryContent:(NSString*)newUpdateEntryContent NS_SWIFT_NAME(setUpdateEntryContent(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryContentTextType,setter=setUpdateEntryContentTextType:) int updateEntryContentTextType NS_SWIFT_NAME(updateEntryContentTextType);
- (int)updateEntryContentTextType NS_SWIFT_NAME(updateEntryContentTextType());
- (void)setUpdateEntryContentTextType:(int)newUpdateEntryContentTextType NS_SWIFT_NAME(setUpdateEntryContentTextType(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryContributorEmail,setter=setUpdateEntryContributorEmail:) NSString* updateEntryContributorEmail NS_SWIFT_NAME(updateEntryContributorEmail);
- (NSString*)updateEntryContributorEmail NS_SWIFT_NAME(updateEntryContributorEmail());
- (void)setUpdateEntryContributorEmail:(NSString*)newUpdateEntryContributorEmail NS_SWIFT_NAME(setUpdateEntryContributorEmail(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryContributorName,setter=setUpdateEntryContributorName:) NSString* updateEntryContributorName NS_SWIFT_NAME(updateEntryContributorName);
- (NSString*)updateEntryContributorName NS_SWIFT_NAME(updateEntryContributorName());
- (void)setUpdateEntryContributorName:(NSString*)newUpdateEntryContributorName NS_SWIFT_NAME(setUpdateEntryContributorName(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryContributorUri,setter=setUpdateEntryContributorUri:) NSString* updateEntryContributorUri NS_SWIFT_NAME(updateEntryContributorUri);
- (NSString*)updateEntryContributorUri NS_SWIFT_NAME(updateEntryContributorUri());
- (void)setUpdateEntryContributorUri:(NSString*)newUpdateEntryContributorUri NS_SWIFT_NAME(setUpdateEntryContributorUri(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryCopyright,setter=setUpdateEntryCopyright:) NSString* updateEntryCopyright NS_SWIFT_NAME(updateEntryCopyright);
- (NSString*)updateEntryCopyright NS_SWIFT_NAME(updateEntryCopyright());
- (void)setUpdateEntryCopyright:(NSString*)newUpdateEntryCopyright NS_SWIFT_NAME(setUpdateEntryCopyright(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryCreated,setter=setUpdateEntryCreated:) NSString* updateEntryCreated NS_SWIFT_NAME(updateEntryCreated);
- (NSString*)updateEntryCreated NS_SWIFT_NAME(updateEntryCreated());
- (void)setUpdateEntryCreated:(NSString*)newUpdateEntryCreated NS_SWIFT_NAME(setUpdateEntryCreated(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryXML,setter=setUpdateEntryXML:) NSString* updateEntryXML NS_SWIFT_NAME(updateEntryXML);
- (NSString*)updateEntryXML NS_SWIFT_NAME(updateEntryXML());
- (void)setUpdateEntryXML:(NSString*)newUpdateEntryXML NS_SWIFT_NAME(setUpdateEntryXML(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryId,setter=setUpdateEntryId:) NSString* updateEntryId NS_SWIFT_NAME(updateEntryId);
- (NSString*)updateEntryId NS_SWIFT_NAME(updateEntryId());
- (void)setUpdateEntryId:(NSString*)newUpdateEntryId NS_SWIFT_NAME(setUpdateEntryId(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryIssued,setter=setUpdateEntryIssued:) NSString* updateEntryIssued NS_SWIFT_NAME(updateEntryIssued);
- (NSString*)updateEntryIssued NS_SWIFT_NAME(updateEntryIssued());
- (void)setUpdateEntryIssued:(NSString*)newUpdateEntryIssued NS_SWIFT_NAME(setUpdateEntryIssued(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryLinkHref,setter=setUpdateEntryLinkHref:) NSString* updateEntryLinkHref NS_SWIFT_NAME(updateEntryLinkHref);
- (NSString*)updateEntryLinkHref NS_SWIFT_NAME(updateEntryLinkHref());
- (void)setUpdateEntryLinkHref:(NSString*)newUpdateEntryLinkHref NS_SWIFT_NAME(setUpdateEntryLinkHref(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryLinkHrefLang,setter=setUpdateEntryLinkHrefLang:) NSString* updateEntryLinkHrefLang NS_SWIFT_NAME(updateEntryLinkHrefLang);
- (NSString*)updateEntryLinkHrefLang NS_SWIFT_NAME(updateEntryLinkHrefLang());
- (void)setUpdateEntryLinkHrefLang:(NSString*)newUpdateEntryLinkHrefLang NS_SWIFT_NAME(setUpdateEntryLinkHrefLang(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryLinkLength,setter=setUpdateEntryLinkLength:) NSString* updateEntryLinkLength NS_SWIFT_NAME(updateEntryLinkLength);
- (NSString*)updateEntryLinkLength NS_SWIFT_NAME(updateEntryLinkLength());
- (void)setUpdateEntryLinkLength:(NSString*)newUpdateEntryLinkLength NS_SWIFT_NAME(setUpdateEntryLinkLength(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryLinkRel,setter=setUpdateEntryLinkRel:) NSString* updateEntryLinkRel NS_SWIFT_NAME(updateEntryLinkRel);
- (NSString*)updateEntryLinkRel NS_SWIFT_NAME(updateEntryLinkRel());
- (void)setUpdateEntryLinkRel:(NSString*)newUpdateEntryLinkRel NS_SWIFT_NAME(setUpdateEntryLinkRel(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryLinkTitle,setter=setUpdateEntryLinkTitle:) NSString* updateEntryLinkTitle NS_SWIFT_NAME(updateEntryLinkTitle);
- (NSString*)updateEntryLinkTitle NS_SWIFT_NAME(updateEntryLinkTitle());
- (void)setUpdateEntryLinkTitle:(NSString*)newUpdateEntryLinkTitle NS_SWIFT_NAME(setUpdateEntryLinkTitle(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryLinkType,setter=setUpdateEntryLinkType:) NSString* updateEntryLinkType NS_SWIFT_NAME(updateEntryLinkType);
- (NSString*)updateEntryLinkType NS_SWIFT_NAME(updateEntryLinkType());
- (void)setUpdateEntryLinkType:(NSString*)newUpdateEntryLinkType NS_SWIFT_NAME(setUpdateEntryLinkType(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryModified,setter=setUpdateEntryModified:) NSString* updateEntryModified NS_SWIFT_NAME(updateEntryModified);
- (NSString*)updateEntryModified NS_SWIFT_NAME(updateEntryModified());
- (void)setUpdateEntryModified:(NSString*)newUpdateEntryModified NS_SWIFT_NAME(setUpdateEntryModified(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryPublished,setter=setUpdateEntryPublished:) NSString* updateEntryPublished NS_SWIFT_NAME(updateEntryPublished);
- (NSString*)updateEntryPublished NS_SWIFT_NAME(updateEntryPublished());
- (void)setUpdateEntryPublished:(NSString*)newUpdateEntryPublished NS_SWIFT_NAME(setUpdateEntryPublished(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryRights,setter=setUpdateEntryRights:) NSString* updateEntryRights NS_SWIFT_NAME(updateEntryRights);
- (NSString*)updateEntryRights NS_SWIFT_NAME(updateEntryRights());
- (void)setUpdateEntryRights:(NSString*)newUpdateEntryRights NS_SWIFT_NAME(setUpdateEntryRights(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryRightsTextType,setter=setUpdateEntryRightsTextType:) int updateEntryRightsTextType NS_SWIFT_NAME(updateEntryRightsTextType);
- (int)updateEntryRightsTextType NS_SWIFT_NAME(updateEntryRightsTextType());
- (void)setUpdateEntryRightsTextType:(int)newUpdateEntryRightsTextType NS_SWIFT_NAME(setUpdateEntryRightsTextType(_:));

@property (nonatomic,readwrite,assign,getter=updateEntrySource,setter=setUpdateEntrySource:) NSString* updateEntrySource NS_SWIFT_NAME(updateEntrySource);
- (NSString*)updateEntrySource NS_SWIFT_NAME(updateEntrySource());
- (void)setUpdateEntrySource:(NSString*)newUpdateEntrySource NS_SWIFT_NAME(setUpdateEntrySource(_:));

@property (nonatomic,readwrite,assign,getter=updateEntrySummary,setter=setUpdateEntrySummary:) NSString* updateEntrySummary NS_SWIFT_NAME(updateEntrySummary);
- (NSString*)updateEntrySummary NS_SWIFT_NAME(updateEntrySummary());
- (void)setUpdateEntrySummary:(NSString*)newUpdateEntrySummary NS_SWIFT_NAME(setUpdateEntrySummary(_:));

@property (nonatomic,readwrite,assign,getter=updateEntrySummaryTextType,setter=setUpdateEntrySummaryTextType:) int updateEntrySummaryTextType NS_SWIFT_NAME(updateEntrySummaryTextType);
- (int)updateEntrySummaryTextType NS_SWIFT_NAME(updateEntrySummaryTextType());
- (void)setUpdateEntrySummaryTextType:(int)newUpdateEntrySummaryTextType NS_SWIFT_NAME(setUpdateEntrySummaryTextType(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryTitle,setter=setUpdateEntryTitle:) NSString* updateEntryTitle NS_SWIFT_NAME(updateEntryTitle);
- (NSString*)updateEntryTitle NS_SWIFT_NAME(updateEntryTitle());
- (void)setUpdateEntryTitle:(NSString*)newUpdateEntryTitle NS_SWIFT_NAME(setUpdateEntryTitle(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryTitleTextType,setter=setUpdateEntryTitleTextType:) int updateEntryTitleTextType NS_SWIFT_NAME(updateEntryTitleTextType);
- (int)updateEntryTitleTextType NS_SWIFT_NAME(updateEntryTitleTextType());
- (void)setUpdateEntryTitleTextType:(int)newUpdateEntryTitleTextType NS_SWIFT_NAME(setUpdateEntryTitleTextType(_:));

@property (nonatomic,readwrite,assign,getter=updateEntryUpdated,setter=setUpdateEntryUpdated:) NSString* updateEntryUpdated NS_SWIFT_NAME(updateEntryUpdated);
- (NSString*)updateEntryUpdated NS_SWIFT_NAME(updateEntryUpdated());
- (void)setUpdateEntryUpdated:(NSString*)newUpdateEntryUpdated NS_SWIFT_NAME(setUpdateEntryUpdated(_:));

@property (nonatomic,readwrite,assign,getter=updateFile,setter=setUpdateFile:) NSString* updateFile NS_SWIFT_NAME(updateFile);
- (NSString*)updateFile NS_SWIFT_NAME(updateFile());
- (void)setUpdateFile:(NSString*)newUpdateFile NS_SWIFT_NAME(setUpdateFile(_:));

@property (nonatomic,readwrite,assign,getter=user,setter=setUser:) NSString* user NS_SWIFT_NAME(user);
- (NSString*)user NS_SWIFT_NAME(user());
- (void)setUser:(NSString*)newUser NS_SWIFT_NAME(setUser(_:));

  /* Methods */

- (void)addCookie:(NSString*)cookieName :(NSString*)cookieValue NS_SWIFT_NAME(addCookie(_:_:));
- (void)addNamespace:(NSString*)prefix :(NSString*)namespaceURI NS_SWIFT_NAME(addNamespace(_:_:));
- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)deleteResource:(NSString*)URL NS_SWIFT_NAME(deleteResource(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)getFeed:(NSString*)URL NS_SWIFT_NAME(getFeed(_:));
- (NSString*)getProperty:(NSString*)propertyName NS_SWIFT_NAME(getProperty(_:));
- (void)getResource:(NSString*)URL NS_SWIFT_NAME(getResource(_:));
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)postResource:(NSString*)URL NS_SWIFT_NAME(postResource(_:));
- (void)put:(NSString*)URL NS_SWIFT_NAME(put(_:));
- (void)putResource:(NSString*)URL NS_SWIFT_NAME(putResource(_:));
- (void)readFile:(NSString*)fileName NS_SWIFT_NAME(readFile(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)setProperty:(NSString*)propertyName :(NSString*)propertyValue NS_SWIFT_NAME(setProperty(_:_:));
- (void)writeFile:(NSString*)filename NS_SWIFT_NAME(writeFile(_:));

@end


