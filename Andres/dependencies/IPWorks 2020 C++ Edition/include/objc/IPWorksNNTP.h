
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


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksNNTPDelegate <NSObject>
@optional
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onGroupList:(NSString*)group :(long long)firstArticle :(long long)lastArticle :(BOOL)canPost NS_SWIFT_NAME(onGroupList(_:_:_:_:));
- (void)onGroupOverview:(long long)articleNumber :(NSString*)subject :(NSString*)from :(NSString*)articleDate :(NSString*)messageId :(NSString*)references :(long long)articleSize :(long long)articleLines :(NSString*)otherHeaders NS_SWIFT_NAME(onGroupOverview(_:_:_:_:_:_:_:_:_:));
- (void)onGroupSearch:(long long)articleNumber :(NSString*)header NS_SWIFT_NAME(onGroupSearch(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
- (void)onPITrail:(int)direction :(NSString*)message NS_SWIFT_NAME(onPITrail(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text :(BOOL)EOL NS_SWIFT_NAME(onTransfer(_:_:_:_:_:));
@end

@interface IPWorksNNTP : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksNNTPDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasError;
  BOOL m_delegateHasGroupList;
  BOOL m_delegateHasGroupOverview;
  BOOL m_delegateHasGroupSearch;
  BOOL m_delegateHasHeader;
  BOOL m_delegateHasPITrail;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
  BOOL m_delegateHasStartTransfer;
  BOOL m_delegateHasTransfer;
}

+ (IPWorksNNTP*)nntp;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksNNTPDelegate> delegate;
- (id <IPWorksNNTPDelegate>)delegate;
- (void) setDelegate:(id <IPWorksNNTPDelegate>)anObject;

  /* Events */

- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onGroupList:(NSString*)group :(long long)firstArticle :(long long)lastArticle :(BOOL)canPost NS_SWIFT_NAME(onGroupList(_:_:_:_:));
- (void)onGroupOverview:(long long)articleNumber :(NSString*)subject :(NSString*)from :(NSString*)articleDate :(NSString*)messageId :(NSString*)references :(long long)articleSize :(long long)articleLines :(NSString*)otherHeaders NS_SWIFT_NAME(onGroupOverview(_:_:_:_:_:_:_:_:_:));
- (void)onGroupSearch:(long long)articleNumber :(NSString*)header NS_SWIFT_NAME(onGroupSearch(_:_:));
- (void)onHeader:(NSString*)field :(NSString*)value NS_SWIFT_NAME(onHeader(_:_:));
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

@property (nonatomic,readonly,assign,getter=articleCount) long long articleCount NS_SWIFT_NAME(articleCount);
- (long long)articleCount NS_SWIFT_NAME(articleCount());

@property (nonatomic,readonly,assign,getter=articleDate) NSString* articleDate NS_SWIFT_NAME(articleDate);
- (NSString*)articleDate NS_SWIFT_NAME(articleDate());

@property (nonatomic,readwrite,assign,getter=articleFrom,setter=setArticleFrom:) NSString* articleFrom NS_SWIFT_NAME(articleFrom);
- (NSString*)articleFrom NS_SWIFT_NAME(articleFrom());
- (void)setArticleFrom:(NSString*)newArticleFrom NS_SWIFT_NAME(setArticleFrom(_:));

@property (nonatomic,readonly,assign,getter=articleHeaders) NSString* articleHeaders NS_SWIFT_NAME(articleHeaders);
- (NSString*)articleHeaders NS_SWIFT_NAME(articleHeaders());

@property (nonatomic,readonly,assign,getter=articleId) NSString* articleId NS_SWIFT_NAME(articleId);
- (NSString*)articleId NS_SWIFT_NAME(articleId());

@property (nonatomic,readonly,assign,getter=groupOverviewCount) int groupOverviewCount NS_SWIFT_NAME(groupOverviewCount);
- (int)groupOverviewCount NS_SWIFT_NAME(groupOverviewCount());

- (long long)groupOverviewArticleLines:(int)groupOverviewIndex NS_SWIFT_NAME(groupOverviewArticleLines(_:));

- (long long)groupOverviewArticleNumber:(int)groupOverviewIndex NS_SWIFT_NAME(groupOverviewArticleNumber(_:));

- (long long)groupOverviewArticleSize:(int)groupOverviewIndex NS_SWIFT_NAME(groupOverviewArticleSize(_:));

- (NSString*)groupOverviewDate:(int)groupOverviewIndex NS_SWIFT_NAME(groupOverviewDate(_:));

- (NSString*)groupOverviewFrom:(int)groupOverviewIndex NS_SWIFT_NAME(groupOverviewFrom(_:));

- (NSString*)groupOverviewMessageId:(int)groupOverviewIndex NS_SWIFT_NAME(groupOverviewMessageId(_:));

- (NSString*)groupOverviewOtherHeaders:(int)groupOverviewIndex NS_SWIFT_NAME(groupOverviewOtherHeaders(_:));

- (NSString*)groupOverviewReferences:(int)groupOverviewIndex NS_SWIFT_NAME(groupOverviewReferences(_:));

- (NSString*)groupOverviewSubject:(int)groupOverviewIndex NS_SWIFT_NAME(groupOverviewSubject(_:));

@property (nonatomic,readwrite,assign,getter=articleReferences,setter=setArticleReferences:) NSString* articleReferences NS_SWIFT_NAME(articleReferences);
- (NSString*)articleReferences NS_SWIFT_NAME(articleReferences());
- (void)setArticleReferences:(NSString*)newArticleReferences NS_SWIFT_NAME(setArticleReferences(_:));

@property (nonatomic,readwrite,assign,getter=articleReplyTo,setter=setArticleReplyTo:) NSString* articleReplyTo NS_SWIFT_NAME(articleReplyTo);
- (NSString*)articleReplyTo NS_SWIFT_NAME(articleReplyTo());
- (void)setArticleReplyTo:(NSString*)newArticleReplyTo NS_SWIFT_NAME(setArticleReplyTo(_:));

@property (nonatomic,readwrite,assign,getter=articleSubject,setter=setArticleSubject:) NSString* articleSubject NS_SWIFT_NAME(articleSubject);
- (NSString*)articleSubject NS_SWIFT_NAME(articleSubject());
- (void)setArticleSubject:(NSString*)newArticleSubject NS_SWIFT_NAME(setArticleSubject(_:));

@property (nonatomic,readwrite,assign,getter=articleText,setter=setArticleText:) NSString* articleText NS_SWIFT_NAME(articleText);
- (NSString*)articleText NS_SWIFT_NAME(articleText());
- (void)setArticleText:(NSString*)newArticleText NS_SWIFT_NAME(setArticleText(_:));

@property (nonatomic,readwrite,assign,getter=attachedFile,setter=setAttachedFile:) NSString* attachedFile NS_SWIFT_NAME(attachedFile);
- (NSString*)attachedFile NS_SWIFT_NAME(attachedFile());
- (void)setAttachedFile:(NSString*)newAttachedFile NS_SWIFT_NAME(setAttachedFile(_:));

@property (nonatomic,readwrite,assign,getter=checkDate,setter=setCheckDate:) NSString* checkDate NS_SWIFT_NAME(checkDate);
- (NSString*)checkDate NS_SWIFT_NAME(checkDate());
- (void)setCheckDate:(NSString*)newCheckDate NS_SWIFT_NAME(setCheckDate(_:));

@property (nonatomic,readwrite,assign,getter=command,setter=setCommand:) NSString* command NS_SWIFT_NAME(command);
- (NSString*)command NS_SWIFT_NAME(command());
- (void)setCommand:(NSString*)newCommand NS_SWIFT_NAME(setCommand(_:));

@property (nonatomic,readwrite,assign,getter=connected,setter=setConnected:) BOOL connected NS_SWIFT_NAME(connected);
- (BOOL)connected NS_SWIFT_NAME(connected());
- (void)setConnected:(BOOL)newConnected NS_SWIFT_NAME(setConnected(_:));

@property (nonatomic,readwrite,assign,getter=currentArticle,setter=setCurrentArticle:) NSString* currentArticle NS_SWIFT_NAME(currentArticle);
- (NSString*)currentArticle NS_SWIFT_NAME(currentArticle());
- (void)setCurrentArticle:(NSString*)newCurrentArticle NS_SWIFT_NAME(setCurrentArticle(_:));

@property (nonatomic,readwrite,assign,getter=currentGroup,setter=setCurrentGroup:) NSString* currentGroup NS_SWIFT_NAME(currentGroup);
- (NSString*)currentGroup NS_SWIFT_NAME(currentGroup());
- (void)setCurrentGroup:(NSString*)newCurrentGroup NS_SWIFT_NAME(setCurrentGroup(_:));

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

@property (nonatomic,readonly,assign,getter=firstArticle) long long firstArticle NS_SWIFT_NAME(firstArticle);
- (long long)firstArticle NS_SWIFT_NAME(firstArticle());

@property (nonatomic,readonly,assign,getter=groupListCount) int groupListCount NS_SWIFT_NAME(groupListCount);
- (int)groupListCount NS_SWIFT_NAME(groupListCount());

- (BOOL)groupListCanPost:(int)groupListIndex NS_SWIFT_NAME(groupListCanPost(_:));

- (long long)groupListFirstArticle:(int)groupListIndex NS_SWIFT_NAME(groupListFirstArticle(_:));

- (NSString*)groupListGroup:(int)groupListIndex NS_SWIFT_NAME(groupListGroup(_:));

- (long long)groupListLastArticle:(int)groupListIndex NS_SWIFT_NAME(groupListLastArticle(_:));

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readonly,assign,getter=lastArticle) long long lastArticle NS_SWIFT_NAME(lastArticle);
- (long long)lastArticle NS_SWIFT_NAME(lastArticle());

@property (nonatomic,readonly,assign,getter=lastReply) NSString* lastReply NS_SWIFT_NAME(lastReply);
- (NSString*)lastReply NS_SWIFT_NAME(lastReply());

@property (nonatomic,readwrite,assign,getter=localFile,setter=setLocalFile:) NSString* localFile NS_SWIFT_NAME(localFile);
- (NSString*)localFile NS_SWIFT_NAME(localFile());
- (void)setLocalFile:(NSString*)newLocalFile NS_SWIFT_NAME(setLocalFile(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=maxLines,setter=setMaxLines:) long long maxLines NS_SWIFT_NAME(maxLines);
- (long long)maxLines NS_SWIFT_NAME(maxLines());
- (void)setMaxLines:(long long)newMaxLines NS_SWIFT_NAME(setMaxLines(_:));

@property (nonatomic,readwrite,assign,getter=newsgroups,setter=setNewsgroups:) NSString* newsgroups NS_SWIFT_NAME(newsgroups);
- (NSString*)newsgroups NS_SWIFT_NAME(newsgroups());
- (void)setNewsgroups:(NSString*)newNewsgroups NS_SWIFT_NAME(setNewsgroups(_:));

@property (nonatomic,readwrite,assign,getter=newsPort,setter=setNewsPort:) int newsPort NS_SWIFT_NAME(newsPort);
- (int)newsPort NS_SWIFT_NAME(newsPort());
- (void)setNewsPort:(int)newNewsPort NS_SWIFT_NAME(setNewsPort(_:));

@property (nonatomic,readwrite,assign,getter=newsServer,setter=setNewsServer:) NSString* newsServer NS_SWIFT_NAME(newsServer);
- (NSString*)newsServer NS_SWIFT_NAME(newsServer());
- (void)setNewsServer:(NSString*)newNewsServer NS_SWIFT_NAME(setNewsServer(_:));

@property (nonatomic,readwrite,assign,getter=organization,setter=setOrganization:) NSString* organization NS_SWIFT_NAME(organization);
- (NSString*)organization NS_SWIFT_NAME(organization());
- (void)setOrganization:(NSString*)newOrganization NS_SWIFT_NAME(setOrganization(_:));

@property (nonatomic,readwrite,assign,getter=otherHeaders,setter=setOtherHeaders:) NSString* otherHeaders NS_SWIFT_NAME(otherHeaders);
- (NSString*)otherHeaders NS_SWIFT_NAME(otherHeaders());
- (void)setOtherHeaders:(NSString*)newOtherHeaders NS_SWIFT_NAME(setOtherHeaders(_:));

@property (nonatomic,readwrite,assign,getter=overviewRange,setter=setOverviewRange:) NSString* overviewRange NS_SWIFT_NAME(overviewRange);
- (NSString*)overviewRange NS_SWIFT_NAME(overviewRange());
- (void)setOverviewRange:(NSString*)newOverviewRange NS_SWIFT_NAME(setOverviewRange(_:));

@property (nonatomic,readonly,assign,getter=parsedHeaderCount) int parsedHeaderCount NS_SWIFT_NAME(parsedHeaderCount);
- (int)parsedHeaderCount NS_SWIFT_NAME(parsedHeaderCount());

- (NSString*)parsedHeaderField:(int)parsedHeaderIndex NS_SWIFT_NAME(parsedHeaderField(_:));

- (NSString*)parsedHeaderValue:(int)parsedHeaderIndex NS_SWIFT_NAME(parsedHeaderValue(_:));

@property (nonatomic,readwrite,assign,getter=password,setter=setPassword:) NSString* password NS_SWIFT_NAME(password);
- (NSString*)password NS_SWIFT_NAME(password());
- (void)setPassword:(NSString*)newPassword NS_SWIFT_NAME(setPassword(_:));

@property (nonatomic,readwrite,assign,getter=searchHeader,setter=setSearchHeader:) NSString* searchHeader NS_SWIFT_NAME(searchHeader);
- (NSString*)searchHeader NS_SWIFT_NAME(searchHeader());
- (void)setSearchHeader:(NSString*)newSearchHeader NS_SWIFT_NAME(setSearchHeader(_:));

@property (nonatomic,readwrite,assign,getter=searchPattern,setter=setSearchPattern:) NSString* searchPattern NS_SWIFT_NAME(searchPattern);
- (NSString*)searchPattern NS_SWIFT_NAME(searchPattern());
- (void)setSearchPattern:(NSString*)newSearchPattern NS_SWIFT_NAME(setSearchPattern(_:));

@property (nonatomic,readwrite,assign,getter=searchRange,setter=setSearchRange:) NSString* searchRange NS_SWIFT_NAME(searchRange);
- (NSString*)searchRange NS_SWIFT_NAME(searchRange());
- (void)setSearchRange:(NSString*)newSearchRange NS_SWIFT_NAME(setSearchRange(_:));

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

@property (nonatomic,readwrite,assign,getter=user,setter=setUser:) NSString* user NS_SWIFT_NAME(user);
- (NSString*)user NS_SWIFT_NAME(user());
- (void)setUser:(NSString*)newUser NS_SWIFT_NAME(setUser(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)connect NS_SWIFT_NAME(connect());
- (void)disconnect NS_SWIFT_NAME(disconnect());
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)fetchArticle NS_SWIFT_NAME(fetchArticle());
- (void)fetchArticleBody NS_SWIFT_NAME(fetchArticleBody());
- (void)fetchArticleHeaders NS_SWIFT_NAME(fetchArticleHeaders());
- (void)groupOverview NS_SWIFT_NAME(groupOverview());
- (void)groupSearch NS_SWIFT_NAME(groupSearch());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)listGroups NS_SWIFT_NAME(listGroups());
- (void)listNewGroups NS_SWIFT_NAME(listNewGroups());
- (NSString*)localizeDate:(NSString*)dateTime NS_SWIFT_NAME(localizeDate(_:));
- (void)postArticle NS_SWIFT_NAME(postArticle());
- (void)reset NS_SWIFT_NAME(reset());
- (void)resetHeaders NS_SWIFT_NAME(resetHeaders());

@end


