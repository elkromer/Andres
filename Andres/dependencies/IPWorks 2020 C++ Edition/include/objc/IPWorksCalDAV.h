
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//ACTIONS
#define A_NO_ALARM                                         0
#define A_AUDIO                                            1
#define A_DISPLAY                                          2
#define A_EMAIL                                            3

//AUTHSCHEMES
#define AUTH_BASIC                                         0
#define AUTH_DIGEST                                        1
#define AUTH_PROPRIETARY                                   2
#define AUTH_NONE                                          3
#define AUTH_NTLM                                          4
#define AUTH_NEGOTIATE                                     5
#define AUTH_OAUTH                                         6

//TDEPTH
#define DP_UNSPECIFIED                                     0
#define DP_RESOURCE_ONLY                                   1
#define DP_IMMEDIATE_CHILDREN                              2
#define DP_INFINITY                                        3

//EVENTTYPES
#define V_EVENT                                            0
#define V_TODO                                             1
#define V_JOURNAL                                          2
#define V_FREE_BUSY                                        3

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

//VEVENTTYPES
#define VT_EVENT                                           0
#define VT_TODO                                            1
#define VT_JOURNAL                                         2
#define VT_FREE_BUSY                                       3
#define VT_ALL                                             4

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

@protocol IPWorksCalDAVDelegate <NSObject>
@optional
- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onEventDetails:(NSString*)resourceURI :(NSString*)responseStatus :(NSString*)ETag :(NSString*)calendarData NS_SWIFT_NAME(onEventDetails(_:_:_:_:));
- (void)onFreeBusy:(NSString*)busyType :(NSString*)busyRange NS_SWIFT_NAME(onFreeBusy(_:_:));
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

@interface IPWorksCalDAV : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksCalDAVDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnected;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasDisconnected;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasError;
  BOOL m_delegateHasEventDetails;
  BOOL m_delegateHasFreeBusy;
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

+ (IPWorksCalDAV*)caldav;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksCalDAVDelegate> delegate;
- (id <IPWorksCalDAVDelegate>)delegate;
- (void) setDelegate:(id <IPWorksCalDAVDelegate>)anObject;

  /* Events */

- (void)onConnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnected(_:_:));
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onDisconnected:(int)statusCode :(NSString*)description NS_SWIFT_NAME(onDisconnected(_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onEventDetails:(NSString*)resourceURI :(NSString*)responseStatus :(NSString*)ETag :(NSString*)calendarData NS_SWIFT_NAME(onEventDetails(_:_:_:_:));
- (void)onFreeBusy:(NSString*)busyType :(NSString*)busyRange NS_SWIFT_NAME(onFreeBusy(_:_:));
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

@property (nonatomic,readwrite,assign,getter=alarmCount,setter=setAlarmCount:) int alarmCount NS_SWIFT_NAME(alarmCount);
- (int)alarmCount NS_SWIFT_NAME(alarmCount());
- (void)setAlarmCount:(int)newAlarmCount NS_SWIFT_NAME(setAlarmCount(_:));

- (int)alarmAction:(int)alarmIndex NS_SWIFT_NAME(alarmAction(_:));
- (void)setAlarmAction:(int)alarmIndex:(int)newAlarmAction NS_SWIFT_NAME(setAlarmAction(_:_:));

- (NSString*)alarmAttachment:(int)alarmIndex NS_SWIFT_NAME(alarmAttachment(_:));
- (void)setAlarmAttachment:(int)alarmIndex:(NSString*)newAlarmAttachment NS_SWIFT_NAME(setAlarmAttachment(_:_:));

- (NSString*)alarmAttachmentType:(int)alarmIndex NS_SWIFT_NAME(alarmAttachmentType(_:));
- (void)setAlarmAttachmentType:(int)alarmIndex:(NSString*)newAlarmAttachmentType NS_SWIFT_NAME(setAlarmAttachmentType(_:_:));

- (NSString*)alarmDuration:(int)alarmIndex NS_SWIFT_NAME(alarmDuration(_:));
- (void)setAlarmDuration:(int)alarmIndex:(NSString*)newAlarmDuration NS_SWIFT_NAME(setAlarmDuration(_:_:));

- (NSString*)alarmMessage:(int)alarmIndex NS_SWIFT_NAME(alarmMessage(_:));
- (void)setAlarmMessage:(int)alarmIndex:(NSString*)newAlarmMessage NS_SWIFT_NAME(setAlarmMessage(_:_:));

- (NSString*)alarmRecipient:(int)alarmIndex NS_SWIFT_NAME(alarmRecipient(_:));
- (void)setAlarmRecipient:(int)alarmIndex:(NSString*)newAlarmRecipient NS_SWIFT_NAME(setAlarmRecipient(_:_:));

- (int)alarmRepeat:(int)alarmIndex NS_SWIFT_NAME(alarmRepeat(_:));
- (void)setAlarmRepeat:(int)alarmIndex:(int)newAlarmRepeat NS_SWIFT_NAME(setAlarmRepeat(_:_:));

- (NSString*)alarmSubject:(int)alarmIndex NS_SWIFT_NAME(alarmSubject(_:));
- (void)setAlarmSubject:(int)alarmIndex:(NSString*)newAlarmSubject NS_SWIFT_NAME(setAlarmSubject(_:_:));

- (NSString*)alarmTrigger:(int)alarmIndex NS_SWIFT_NAME(alarmTrigger(_:));
- (void)setAlarmTrigger:(int)alarmIndex:(NSString*)newAlarmTrigger NS_SWIFT_NAME(setAlarmTrigger(_:_:));

@property (nonatomic,readwrite,assign,getter=attendees,setter=setAttendees:) NSString* attendees NS_SWIFT_NAME(attendees);
- (NSString*)attendees NS_SWIFT_NAME(attendees());
- (void)setAttendees:(NSString*)newAttendees NS_SWIFT_NAME(setAttendees(_:));

@property (nonatomic,readwrite,assign,getter=authorization,setter=setAuthorization:) NSString* authorization NS_SWIFT_NAME(authorization);
- (NSString*)authorization NS_SWIFT_NAME(authorization());
- (void)setAuthorization:(NSString*)newAuthorization NS_SWIFT_NAME(setAuthorization(_:));

@property (nonatomic,readwrite,assign,getter=authScheme,setter=setAuthScheme:) int authScheme NS_SWIFT_NAME(authScheme);
- (int)authScheme NS_SWIFT_NAME(authScheme());
- (void)setAuthScheme:(int)newAuthScheme NS_SWIFT_NAME(setAuthScheme(_:));

@property (nonatomic,readwrite,assign,getter=categories,setter=setCategories:) NSString* categories NS_SWIFT_NAME(categories);
- (NSString*)categories NS_SWIFT_NAME(categories());
- (void)setCategories:(NSString*)newCategories NS_SWIFT_NAME(setCategories(_:));

@property (nonatomic,readwrite,assign,getter=classification,setter=setClassification:) NSString* classification NS_SWIFT_NAME(classification);
- (NSString*)classification NS_SWIFT_NAME(classification());
- (void)setClassification:(NSString*)newClassification NS_SWIFT_NAME(setClassification(_:));

@property (nonatomic,readwrite,assign,getter=completed,setter=setCompleted:) NSString* completed NS_SWIFT_NAME(completed);
- (NSString*)completed NS_SWIFT_NAME(completed());
- (void)setCompleted:(NSString*)newCompleted NS_SWIFT_NAME(setCompleted(_:));

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

@property (nonatomic,readwrite,assign,getter=created,setter=setCreated:) NSString* created NS_SWIFT_NAME(created);
- (NSString*)created NS_SWIFT_NAME(created());
- (void)setCreated:(NSString*)newCreated NS_SWIFT_NAME(setCreated(_:));

@property (nonatomic,readwrite,assign,getter=customPropertyCount,setter=setCustomPropertyCount:) int customPropertyCount NS_SWIFT_NAME(customPropertyCount);
- (int)customPropertyCount NS_SWIFT_NAME(customPropertyCount());
- (void)setCustomPropertyCount:(int)newCustomPropertyCount NS_SWIFT_NAME(setCustomPropertyCount(_:));

- (NSString*)customPropertyAttribute:(int)customPropertyIndex NS_SWIFT_NAME(customPropertyAttribute(_:));
- (void)setCustomPropertyAttribute:(int)customPropertyIndex:(NSString*)newCustomPropertyAttribute NS_SWIFT_NAME(setCustomPropertyAttribute(_:_:));

- (NSString*)customPropertyName:(int)customPropertyIndex NS_SWIFT_NAME(customPropertyName(_:));
- (void)setCustomPropertyName:(int)customPropertyIndex:(NSString*)newCustomPropertyName NS_SWIFT_NAME(setCustomPropertyName(_:_:));

- (NSString*)customPropertyValue:(int)customPropertyIndex NS_SWIFT_NAME(customPropertyValue(_:));
- (void)setCustomPropertyValue:(int)customPropertyIndex:(NSString*)newCustomPropertyValue NS_SWIFT_NAME(setCustomPropertyValue(_:_:));

@property (nonatomic,readwrite,assign,getter=depth,setter=setDepth:) int depth NS_SWIFT_NAME(depth);
- (int)depth NS_SWIFT_NAME(depth());
- (void)setDepth:(int)newDepth NS_SWIFT_NAME(setDepth(_:));

@property (nonatomic,readwrite,assign,getter=description,setter=setDescription:) NSString* description NS_SWIFT_NAME(description);
- (NSString*)description NS_SWIFT_NAME(description());
- (NSString*)description_ NS_SWIFT_NAME(description_());
- (void)setDescription:(NSString*)newDescription NS_SWIFT_NAME(setDescription(_:));
- (void)setDescription_:(NSString*)newDescription NS_SWIFT_NAME(setDescription_(_:));

@property (nonatomic,readwrite,assign,getter=displayName,setter=setDisplayName:) NSString* displayName NS_SWIFT_NAME(displayName);
- (NSString*)displayName NS_SWIFT_NAME(displayName());
- (void)setDisplayName:(NSString*)newDisplayName NS_SWIFT_NAME(setDisplayName(_:));

@property (nonatomic,readwrite,assign,getter=dueDate,setter=setDueDate:) NSString* dueDate NS_SWIFT_NAME(dueDate);
- (NSString*)dueDate NS_SWIFT_NAME(dueDate());
- (void)setDueDate:(NSString*)newDueDate NS_SWIFT_NAME(setDueDate(_:));

@property (nonatomic,readwrite,assign,getter=duration,setter=setDuration:) NSString* duration NS_SWIFT_NAME(duration);
- (NSString*)duration NS_SWIFT_NAME(duration());
- (void)setDuration:(NSString*)newDuration NS_SWIFT_NAME(setDuration(_:));

@property (nonatomic,readwrite,assign,getter=endDate,setter=setEndDate:) NSString* endDate NS_SWIFT_NAME(endDate);
- (NSString*)endDate NS_SWIFT_NAME(endDate());
- (void)setEndDate:(NSString*)newEndDate NS_SWIFT_NAME(setEndDate(_:));

@property (nonatomic,readwrite,assign,getter=ETag,setter=setETag:) NSString* ETag NS_SWIFT_NAME(ETag);
- (NSString*)ETag NS_SWIFT_NAME(ETag());
- (void)setETag:(NSString*)newETag NS_SWIFT_NAME(setETag(_:));

@property (nonatomic,readwrite,assign,getter=eventType,setter=setEventType:) int eventType NS_SWIFT_NAME(eventType);
- (int)eventType NS_SWIFT_NAME(eventType());
- (void)setEventType:(int)newEventType NS_SWIFT_NAME(setEventType(_:));

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

@property (nonatomic,readonly,assign,getter=freeBusyCount) int freeBusyCount NS_SWIFT_NAME(freeBusyCount);
- (int)freeBusyCount NS_SWIFT_NAME(freeBusyCount());

- (NSString*)freeBusyRange:(int)freeBusyIndex NS_SWIFT_NAME(freeBusyRange(_:));

- (NSString*)freeBusyType:(int)freeBusyIndex NS_SWIFT_NAME(freeBusyType(_:));

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readwrite,assign,getter=lastModified,setter=setLastModified:) NSString* lastModified NS_SWIFT_NAME(lastModified);
- (NSString*)lastModified NS_SWIFT_NAME(lastModified());
- (void)setLastModified:(NSString*)newLastModified NS_SWIFT_NAME(setLastModified(_:));

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=location,setter=setLocation:) NSString* location NS_SWIFT_NAME(location);
- (NSString*)location NS_SWIFT_NAME(location());
- (void)setLocation:(NSString*)newLocation NS_SWIFT_NAME(setLocation(_:));

@property (nonatomic,readwrite,assign,getter=lockType,setter=setLockType:) NSString* lockType NS_SWIFT_NAME(lockType);
- (NSString*)lockType NS_SWIFT_NAME(lockType());
- (void)setLockType:(NSString*)newLockType NS_SWIFT_NAME(setLockType(_:));

@property (nonatomic,readwrite,assign,getter=lockOwner,setter=setLockOwner:) NSString* lockOwner NS_SWIFT_NAME(lockOwner);
- (NSString*)lockOwner NS_SWIFT_NAME(lockOwner());
- (void)setLockOwner:(NSString*)newLockOwner NS_SWIFT_NAME(setLockOwner(_:));

@property (nonatomic,readwrite,assign,getter=lockScope,setter=setLockScope:) NSString* lockScope NS_SWIFT_NAME(lockScope);
- (NSString*)lockScope NS_SWIFT_NAME(lockScope());
- (void)setLockScope:(NSString*)newLockScope NS_SWIFT_NAME(setLockScope(_:));

@property (nonatomic,readwrite,assign,getter=lockTimeout,setter=setLockTimeout:) int lockTimeout NS_SWIFT_NAME(lockTimeout);
- (int)lockTimeout NS_SWIFT_NAME(lockTimeout());
- (void)setLockTimeout:(int)newLockTimeout NS_SWIFT_NAME(setLockTimeout(_:));

@property (nonatomic,readwrite,assign,getter=lockTokens,setter=setLockTokens:) NSString* lockTokens NS_SWIFT_NAME(lockTokens);
- (NSString*)lockTokens NS_SWIFT_NAME(lockTokens());
- (void)setLockTokens:(NSString*)newLockTokens NS_SWIFT_NAME(setLockTokens(_:));

@property (nonatomic,readwrite,assign,getter=organizer,setter=setOrganizer:) NSString* organizer NS_SWIFT_NAME(organizer);
- (NSString*)organizer NS_SWIFT_NAME(organizer());
- (void)setOrganizer:(NSString*)newOrganizer NS_SWIFT_NAME(setOrganizer(_:));

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

@property (nonatomic,readwrite,assign,getter=priority,setter=setPriority:) int priority NS_SWIFT_NAME(priority);
- (int)priority NS_SWIFT_NAME(priority());
- (void)setPriority:(int)newPriority NS_SWIFT_NAME(setPriority(_:));

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

@property (nonatomic,readwrite,assign,getter=recurrenceDates,setter=setRecurrenceDates:) NSString* recurrenceDates NS_SWIFT_NAME(recurrenceDates);
- (NSString*)recurrenceDates NS_SWIFT_NAME(recurrenceDates());
- (void)setRecurrenceDates:(NSString*)newRecurrenceDates NS_SWIFT_NAME(setRecurrenceDates(_:));

@property (nonatomic,readwrite,assign,getter=recurrenceExceptionDates,setter=setRecurrenceExceptionDates:) NSString* recurrenceExceptionDates NS_SWIFT_NAME(recurrenceExceptionDates);
- (NSString*)recurrenceExceptionDates NS_SWIFT_NAME(recurrenceExceptionDates());
- (void)setRecurrenceExceptionDates:(NSString*)newRecurrenceExceptionDates NS_SWIFT_NAME(setRecurrenceExceptionDates(_:));

@property (nonatomic,readwrite,assign,getter=recurrenceExceptionRule,setter=setRecurrenceExceptionRule:) NSString* recurrenceExceptionRule NS_SWIFT_NAME(recurrenceExceptionRule);
- (NSString*)recurrenceExceptionRule NS_SWIFT_NAME(recurrenceExceptionRule());
- (void)setRecurrenceExceptionRule:(NSString*)newRecurrenceExceptionRule NS_SWIFT_NAME(setRecurrenceExceptionRule(_:));

@property (nonatomic,readwrite,assign,getter=recurrenceId,setter=setRecurrenceId:) NSString* recurrenceId NS_SWIFT_NAME(recurrenceId);
- (NSString*)recurrenceId NS_SWIFT_NAME(recurrenceId());
- (void)setRecurrenceId:(NSString*)newRecurrenceId NS_SWIFT_NAME(setRecurrenceId(_:));

@property (nonatomic,readwrite,assign,getter=recurrenceRule,setter=setRecurrenceRule:) NSString* recurrenceRule NS_SWIFT_NAME(recurrenceRule);
- (NSString*)recurrenceRule NS_SWIFT_NAME(recurrenceRule());
- (void)setRecurrenceRule:(NSString*)newRecurrenceRule NS_SWIFT_NAME(setRecurrenceRule(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterAlarmEnd,setter=setReportFilterAlarmEnd:) NSString* reportFilterAlarmEnd NS_SWIFT_NAME(reportFilterAlarmEnd);
- (NSString*)reportFilterAlarmEnd NS_SWIFT_NAME(reportFilterAlarmEnd());
- (void)setReportFilterAlarmEnd:(NSString*)newReportFilterAlarmEnd NS_SWIFT_NAME(setReportFilterAlarmEnd(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterAlarmStart,setter=setReportFilterAlarmStart:) NSString* reportFilterAlarmStart NS_SWIFT_NAME(reportFilterAlarmStart);
- (NSString*)reportFilterAlarmStart NS_SWIFT_NAME(reportFilterAlarmStart());
- (void)setReportFilterAlarmStart:(NSString*)newReportFilterAlarmStart NS_SWIFT_NAME(setReportFilterAlarmStart(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterCustomFilter,setter=setReportFilterCustomFilter:) NSString* reportFilterCustomFilter NS_SWIFT_NAME(reportFilterCustomFilter);
- (NSString*)reportFilterCustomFilter NS_SWIFT_NAME(reportFilterCustomFilter());
- (void)setReportFilterCustomFilter:(NSString*)newReportFilterCustomFilter NS_SWIFT_NAME(setReportFilterCustomFilter(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterEndDate,setter=setReportFilterEndDate:) NSString* reportFilterEndDate NS_SWIFT_NAME(reportFilterEndDate);
- (NSString*)reportFilterEndDate NS_SWIFT_NAME(reportFilterEndDate());
- (void)setReportFilterEndDate:(NSString*)newReportFilterEndDate NS_SWIFT_NAME(setReportFilterEndDate(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterEventType,setter=setReportFilterEventType:) int reportFilterEventType NS_SWIFT_NAME(reportFilterEventType);
- (int)reportFilterEventType NS_SWIFT_NAME(reportFilterEventType());
- (void)setReportFilterEventType:(int)newReportFilterEventType NS_SWIFT_NAME(setReportFilterEventType(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterProperty,setter=setReportFilterProperty:) NSString* reportFilterProperty NS_SWIFT_NAME(reportFilterProperty);
- (NSString*)reportFilterProperty NS_SWIFT_NAME(reportFilterProperty());
- (void)setReportFilterProperty:(NSString*)newReportFilterProperty NS_SWIFT_NAME(setReportFilterProperty(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterRecurEnd,setter=setReportFilterRecurEnd:) NSString* reportFilterRecurEnd NS_SWIFT_NAME(reportFilterRecurEnd);
- (NSString*)reportFilterRecurEnd NS_SWIFT_NAME(reportFilterRecurEnd());
- (void)setReportFilterRecurEnd:(NSString*)newReportFilterRecurEnd NS_SWIFT_NAME(setReportFilterRecurEnd(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterRecurStart,setter=setReportFilterRecurStart:) NSString* reportFilterRecurStart NS_SWIFT_NAME(reportFilterRecurStart);
- (NSString*)reportFilterRecurStart NS_SWIFT_NAME(reportFilterRecurStart());
- (void)setReportFilterRecurStart:(NSString*)newReportFilterRecurStart NS_SWIFT_NAME(setReportFilterRecurStart(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterReturnCalendarData,setter=setReportFilterReturnCalendarData:) BOOL reportFilterReturnCalendarData NS_SWIFT_NAME(reportFilterReturnCalendarData);
- (BOOL)reportFilterReturnCalendarData NS_SWIFT_NAME(reportFilterReturnCalendarData());
- (void)setReportFilterReturnCalendarData:(BOOL)newReportFilterReturnCalendarData NS_SWIFT_NAME(setReportFilterReturnCalendarData(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterStartDate,setter=setReportFilterStartDate:) NSString* reportFilterStartDate NS_SWIFT_NAME(reportFilterStartDate);
- (NSString*)reportFilterStartDate NS_SWIFT_NAME(reportFilterStartDate());
- (void)setReportFilterStartDate:(NSString*)newReportFilterStartDate NS_SWIFT_NAME(setReportFilterStartDate(_:));

@property (nonatomic,readwrite,assign,getter=reportFilterUID,setter=setReportFilterUID:) NSString* reportFilterUID NS_SWIFT_NAME(reportFilterUID);
- (NSString*)reportFilterUID NS_SWIFT_NAME(reportFilterUID());
- (void)setReportFilterUID:(NSString*)newReportFilterUID NS_SWIFT_NAME(setReportFilterUID(_:));

@property (nonatomic,readwrite,assign,getter=sequence,setter=setSequence:) int sequence NS_SWIFT_NAME(sequence);
- (int)sequence NS_SWIFT_NAME(sequence());
- (void)setSequence:(int)newSequence NS_SWIFT_NAME(setSequence(_:));

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

@property (nonatomic,readwrite,assign,getter=startDate,setter=setStartDate:) NSString* startDate NS_SWIFT_NAME(startDate);
- (NSString*)startDate NS_SWIFT_NAME(startDate());
- (void)setStartDate:(NSString*)newStartDate NS_SWIFT_NAME(setStartDate(_:));

@property (nonatomic,readwrite,assign,getter=status,setter=setStatus:) NSString* status NS_SWIFT_NAME(status);
- (NSString*)status NS_SWIFT_NAME(status());
- (void)setStatus:(NSString*)newStatus NS_SWIFT_NAME(setStatus(_:));

@property (nonatomic,readonly,assign,getter=statusLine) NSString* statusLine NS_SWIFT_NAME(statusLine);
- (NSString*)statusLine NS_SWIFT_NAME(statusLine());

@property (nonatomic,readwrite,assign,getter=summary,setter=setSummary:) NSString* summary NS_SWIFT_NAME(summary);
- (NSString*)summary NS_SWIFT_NAME(summary());
- (void)setSummary:(NSString*)newSummary NS_SWIFT_NAME(setSummary(_:));

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

@property (nonatomic,readwrite,assign,getter=timestamp,setter=setTimestamp:) NSString* timestamp NS_SWIFT_NAME(timestamp);
- (NSString*)timestamp NS_SWIFT_NAME(timestamp());
- (void)setTimestamp:(NSString*)newTimestamp NS_SWIFT_NAME(setTimestamp(_:));

@property (nonatomic,readwrite,assign,getter=timezoneDSTName,setter=setTimezoneDSTName:) NSString* timezoneDSTName NS_SWIFT_NAME(timezoneDSTName);
- (NSString*)timezoneDSTName NS_SWIFT_NAME(timezoneDSTName());
- (void)setTimezoneDSTName:(NSString*)newTimezoneDSTName NS_SWIFT_NAME(setTimezoneDSTName(_:));

@property (nonatomic,readwrite,assign,getter=timezoneDSTOffsetFrom,setter=setTimezoneDSTOffsetFrom:) NSString* timezoneDSTOffsetFrom NS_SWIFT_NAME(timezoneDSTOffsetFrom);
- (NSString*)timezoneDSTOffsetFrom NS_SWIFT_NAME(timezoneDSTOffsetFrom());
- (void)setTimezoneDSTOffsetFrom:(NSString*)newTimezoneDSTOffsetFrom NS_SWIFT_NAME(setTimezoneDSTOffsetFrom(_:));

@property (nonatomic,readwrite,assign,getter=timezoneDSTOffsetTo,setter=setTimezoneDSTOffsetTo:) NSString* timezoneDSTOffsetTo NS_SWIFT_NAME(timezoneDSTOffsetTo);
- (NSString*)timezoneDSTOffsetTo NS_SWIFT_NAME(timezoneDSTOffsetTo());
- (void)setTimezoneDSTOffsetTo:(NSString*)newTimezoneDSTOffsetTo NS_SWIFT_NAME(setTimezoneDSTOffsetTo(_:));

@property (nonatomic,readwrite,assign,getter=timezoneDSTRule,setter=setTimezoneDSTRule:) NSString* timezoneDSTRule NS_SWIFT_NAME(timezoneDSTRule);
- (NSString*)timezoneDSTRule NS_SWIFT_NAME(timezoneDSTRule());
- (void)setTimezoneDSTRule:(NSString*)newTimezoneDSTRule NS_SWIFT_NAME(setTimezoneDSTRule(_:));

@property (nonatomic,readwrite,assign,getter=timezoneDSTStart,setter=setTimezoneDSTStart:) NSString* timezoneDSTStart NS_SWIFT_NAME(timezoneDSTStart);
- (NSString*)timezoneDSTStart NS_SWIFT_NAME(timezoneDSTStart());
- (void)setTimezoneDSTStart:(NSString*)newTimezoneDSTStart NS_SWIFT_NAME(setTimezoneDSTStart(_:));

@property (nonatomic,readwrite,assign,getter=timezoneLastModified,setter=setTimezoneLastModified:) NSString* timezoneLastModified NS_SWIFT_NAME(timezoneLastModified);
- (NSString*)timezoneLastModified NS_SWIFT_NAME(timezoneLastModified());
- (void)setTimezoneLastModified:(NSString*)newTimezoneLastModified NS_SWIFT_NAME(setTimezoneLastModified(_:));

@property (nonatomic,readwrite,assign,getter=timezoneStdName,setter=setTimezoneStdName:) NSString* timezoneStdName NS_SWIFT_NAME(timezoneStdName);
- (NSString*)timezoneStdName NS_SWIFT_NAME(timezoneStdName());
- (void)setTimezoneStdName:(NSString*)newTimezoneStdName NS_SWIFT_NAME(setTimezoneStdName(_:));

@property (nonatomic,readwrite,assign,getter=timezoneStdOffsetFrom,setter=setTimezoneStdOffsetFrom:) NSString* timezoneStdOffsetFrom NS_SWIFT_NAME(timezoneStdOffsetFrom);
- (NSString*)timezoneStdOffsetFrom NS_SWIFT_NAME(timezoneStdOffsetFrom());
- (void)setTimezoneStdOffsetFrom:(NSString*)newTimezoneStdOffsetFrom NS_SWIFT_NAME(setTimezoneStdOffsetFrom(_:));

@property (nonatomic,readwrite,assign,getter=timezoneStdOffsetTo,setter=setTimezoneStdOffsetTo:) NSString* timezoneStdOffsetTo NS_SWIFT_NAME(timezoneStdOffsetTo);
- (NSString*)timezoneStdOffsetTo NS_SWIFT_NAME(timezoneStdOffsetTo());
- (void)setTimezoneStdOffsetTo:(NSString*)newTimezoneStdOffsetTo NS_SWIFT_NAME(setTimezoneStdOffsetTo(_:));

@property (nonatomic,readwrite,assign,getter=timezoneStdRule,setter=setTimezoneStdRule:) NSString* timezoneStdRule NS_SWIFT_NAME(timezoneStdRule);
- (NSString*)timezoneStdRule NS_SWIFT_NAME(timezoneStdRule());
- (void)setTimezoneStdRule:(NSString*)newTimezoneStdRule NS_SWIFT_NAME(setTimezoneStdRule(_:));

@property (nonatomic,readwrite,assign,getter=timezoneStdStart,setter=setTimezoneStdStart:) NSString* timezoneStdStart NS_SWIFT_NAME(timezoneStdStart);
- (NSString*)timezoneStdStart NS_SWIFT_NAME(timezoneStdStart());
- (void)setTimezoneStdStart:(NSString*)newTimezoneStdStart NS_SWIFT_NAME(setTimezoneStdStart(_:));

@property (nonatomic,readwrite,assign,getter=timezoneId,setter=setTimezoneId:) NSString* timezoneId NS_SWIFT_NAME(timezoneId);
- (NSString*)timezoneId NS_SWIFT_NAME(timezoneId());
- (void)setTimezoneId:(NSString*)newTimezoneId NS_SWIFT_NAME(setTimezoneId(_:));

@property (nonatomic,readwrite,assign,getter=timezoneURL,setter=setTimezoneURL:) NSString* timezoneURL NS_SWIFT_NAME(timezoneURL);
- (NSString*)timezoneURL NS_SWIFT_NAME(timezoneURL());
- (void)setTimezoneURL:(NSString*)newTimezoneURL NS_SWIFT_NAME(setTimezoneURL(_:));

@property (nonatomic,readwrite,assign,getter=transparency,setter=setTransparency:) NSString* transparency NS_SWIFT_NAME(transparency);
- (NSString*)transparency NS_SWIFT_NAME(transparency());
- (void)setTransparency:(NSString*)newTransparency NS_SWIFT_NAME(setTransparency(_:));

@property (nonatomic,readwrite,assign,getter=UID,setter=setUID:) NSString* UID NS_SWIFT_NAME(UID);
- (NSString*)UID NS_SWIFT_NAME(UID());
- (void)setUID:(NSString*)newUID NS_SWIFT_NAME(setUID(_:));

@property (nonatomic,readonly,assign,getter=URL) NSString* URL NS_SWIFT_NAME(URL);
- (NSString*)URL NS_SWIFT_NAME(URL());

@property (nonatomic,readwrite,assign,getter=user,setter=setUser:) NSString* user NS_SWIFT_NAME(user);
- (NSString*)user NS_SWIFT_NAME(user());
- (void)setUser:(NSString*)newUser NS_SWIFT_NAME(setUser(_:));

  /* Methods */

- (void)addCookie:(NSString*)cookieName :(NSString*)cookieValue NS_SWIFT_NAME(addCookie(_:_:));
- (void)addCustomProperty:(NSString*)varName :(NSString*)varValue NS_SWIFT_NAME(addCustomProperty(_:_:));
- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)copyCalendarEvent:(NSString*)sourceResourceURI :(NSString*)destinationResourceURI NS_SWIFT_NAME(copyCalendarEvent(_:_:));
- (void)createCalendar:(NSString*)resourceURI NS_SWIFT_NAME(createCalendar(_:));
- (void)deleteCalendarEvent:(NSString*)resourceURI NS_SWIFT_NAME(deleteCalendarEvent(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (NSString*)exportICS NS_SWIFT_NAME(exportICS());
- (void)getCalendarEvent:(NSString*)resourceURI NS_SWIFT_NAME(getCalendarEvent(_:));
- (void)getCalendarOptions:(NSString*)resourceURI NS_SWIFT_NAME(getCalendarOptions(_:));
- (void)getCalendarReport:(NSString*)resourceURI NS_SWIFT_NAME(getCalendarReport(_:));
- (void)getFreeBusyReport:(NSString*)resourceURI NS_SWIFT_NAME(getFreeBusyReport(_:));
- (void)importICS:(NSString*)calendarData NS_SWIFT_NAME(importICS(_:));
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)lockCalendar:(NSString*)resourceURI NS_SWIFT_NAME(lockCalendar(_:));
- (void)moveCalendarEvent:(NSString*)sourceResourceURI :(NSString*)destinationResourceURI NS_SWIFT_NAME(moveCalendarEvent(_:_:));
- (void)putCalendarEvent:(NSString*)resourceURI NS_SWIFT_NAME(putCalendarEvent(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)unLockCalendar:(NSString*)resourceURI NS_SWIFT_NAME(unLockCalendar(_:));

@end


