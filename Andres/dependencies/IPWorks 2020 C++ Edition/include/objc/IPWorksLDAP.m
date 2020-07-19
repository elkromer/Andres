
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksLDAP.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksLDAP()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define LDAP_EXTERN extern "C"
#else
#define LDAP_EXTERN extern
#endif

LDAP_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
LDAP_EXTERN void* IPWorks_LDAP_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
LDAP_EXTERN int   IPWorks_LDAP_Destroy(void* lpObj);
LDAP_EXTERN int   IPWorks_LDAP_CheckIndex(void* lpObj, int propid, int arridx);
LDAP_EXTERN void* IPWorks_LDAP_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
LDAP_EXTERN int   IPWorks_LDAP_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
LDAP_EXTERN int   IPWorks_LDAP_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
LDAP_EXTERN char* IPWorks_LDAP_GetLastError(void* lpObj);
LDAP_EXTERN int   IPWorks_LDAP_GetLastErrorCode(void* lpObj);
LDAP_EXTERN int   IPWorks_LDAP_SetLastErrorAndCode(void* lpObj, int code, char* message);
LDAP_EXTERN char* IPWorks_LDAP_GetEventError(void* lpObj);
LDAP_EXTERN int   IPWorks_LDAP_GetEventErrorCode(void* lpObj);
LDAP_EXTERN int   IPWorks_LDAP_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void LDAP_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_LDAP_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int LDAP_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksLDAP* ctl = (IPWorksLDAP*)lpObj;

  switch (event_id) {
    case 2000 /*EID_IDLE*/: {
#if TARGET_OS_IPHONE
      CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, true);
#else
      double timeout = ((double)((long)param[0]) / 1000.0) / 100.0;
      NSEvent *theEvent;
      while ((theEvent = [NSApp nextEventMatchingMask:
#if __MAC_OS_X_VERSION_MAX_ALLOWED < 101200
        NSAnyEventMask
#else
        NSEventMaskAny
#endif
        untilDate:[NSDate dateWithTimeIntervalSinceNow:timeout]
        inMode:NSDefaultRunLoopMode
        dequeue:YES]))
      {
        [NSApp sendEvent:theEvent];
      }
#endif
      break;
    }
    case 2001 /*EID_ASYNCSELECT*/: {
      CFSocketContext ctx;
      ctx.version = 0;
      ctx.info = (void*)(ctl->m_pObj);
      ctx.retain = NULL;
      ctx.release = NULL;
      ctx.copyDescription = NULL;

      CFOptionFlags evtflags = 0;
      if ((int)((unsigned long)param[1]) & 0x01) evtflags |= kCFSocketReadCallBack;
      if ((int)((unsigned long)param[1]) & 0x02) evtflags |= kCFSocketWriteCallBack;
      if ((int)((unsigned long)param[1]) & 0x08) evtflags |= kCFSocketReadCallBack;
      if ((int)((unsigned long)param[1]) & 0x10) evtflags |= kCFSocketConnectCallBack;

      if (!param[2]) {
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, LDAP_cCallBack, &ctx);

        CFArrayAppendValue(ctl->m_rNotifiers, notifier);
        CFRelease((CFSocketRef)notifier);
        param[2] = notifier;

        CFSocketSetSocketFlags((CFSocketRef)(notifier), kCFSocketAutomaticallyReenableReadCallBack | kCFSocketAutomaticallyReenableAcceptCallBack);

        CFRunLoopSourceRef rls = CFSocketCreateRunLoopSource(NULL, (CFSocketRef)(notifier), 0);
        if (rls != nil) {
          CFRunLoopAddSource(CFRunLoopGetCurrent(), rls, kCFRunLoopDefaultMode);
          CFRelease(rls);
        }
      } else {
        if (param[2]) CFSocketEnableCallBacks((CFSocketRef)(param[2]), evtflags);
      }
      break;
    }
    case 2002 /*EID_DELETENOTIFYOBJECT*/: {
      if (param[0]) {
        CFSocketInvalidate((CFSocketRef)(param[0]));
        if (CFArrayContainsValue(ctl->m_rNotifiers, CFRangeMake(0, CFArrayGetCount(ctl->m_rNotifiers)), param[0]))
          CFArrayRemoveValueAtIndex(ctl->m_rNotifiers, CFArrayGetFirstIndexOfValue(ctl->m_rNotifiers, CFRangeMake(0, CFArrayGetCount(ctl->m_rNotifiers)), param[0]));
      }
      break;
    }
    case 2003 /*EID_SHOWTRAILLICMSGFORIOS*/: {
#if TARGET_OS_IPHONE
      NSString* msg = @"This application uses an evaluation version of the component. You may test it for a period of 30 days as specified in the Licensing Agreement. Further use requires a license. For more information, please visit www.nsoftware.com.";
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (LDAP)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
      [myAlert show];
      return 1;
#else // TARGET_OS_IPHONE
      return 0;
#endif // TARGET_OS_IPHONE
    }

    case 1 /*EID_COMPUTERLIST*/: {
      NSString* nameT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* name = nameT;
      NSString* operatingSystemT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* operatingSystem = operatingSystemT;
      NSString* lastLogonT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* lastLogon = lastLogonT;
      int logonCount = (int)(long)param[3];
      NSString* dnT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* dn = dnT;
      @try {
        [ctl onComputerList :name :operatingSystem :lastLogon :logonCount :dn];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"ComputerList" :YES];
      }
      break;
    }
    case 2 /*EID_CONNECTED*/: {
      int statusCode = (int)(long)param[0];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      @try {
        [ctl onConnected :statusCode :description];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Connected" :YES];
      }
      break;
    }
    case 3 /*EID_CONNECTIONSTATUS*/: {
      NSString* connectionEventT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* connectionEvent = connectionEventT;
      int statusCode = (int)(long)param[1];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      @try {
        [ctl onConnectionStatus :connectionEvent :statusCode :description];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"ConnectionStatus" :YES];
      }
      break;
    }
    case 4 /*EID_DISCONNECTED*/: {
      int statusCode = (int)(long)param[0];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      @try {
        [ctl onDisconnected :statusCode :description];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Disconnected" :YES];
      }
      break;
    }
    case 5 /*EID_ERROR*/: {
      int errorCode = (int)(long)param[0];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      @try {
        [ctl onError :errorCode :description];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Error" :NO];
      }
      break;
    }
    case 6 /*EID_EXTENDEDRESPONSE*/: {
      int messageId = (int)(long)param[0];
      NSString* DNT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* DN = DNT;
      int resultCode = (int)(long)param[2];
      NSString* resultDescriptionT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* resultDescription = resultDescriptionT;
      NSString* responseNameT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* responseName = responseNameT;
      NSData* responseValue = [NSData dataWithBytesNoCopy:param[5] length:cbparam[5] freeWhenDone:NO];
      @try {
        [ctl onExtendedResponse :messageId :DN :resultCode :resultDescription :responseName :responseValue];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"ExtendedResponse" :YES];
      }
      break;
    }
    case 7 /*EID_GROUPLIST*/: {
      NSString* nameT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* name = nameT;
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      NSString* dnT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* dn = dnT;
      @try {
        [ctl onGroupList :name :description :dn];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"GroupList" :YES];
      }
      break;
    }
    case 8 /*EID_PITRAIL*/: {
      int direction = (int)(long)param[0];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      NSString* messageT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* message = messageT;
      @try {
        [ctl onPITrail :direction :description :message];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"PITrail" :YES];
      }
      break;
    }
    case 9 /*EID_RESULT*/: {
      int messageId = (int)(long)param[0];
      NSString* DNT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* DN = DNT;
      int resultCode = (int)(long)param[2];
      NSString* resultDescriptionT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* resultDescription = resultDescriptionT;
      @try {
        [ctl onResult :messageId :DN :resultCode :resultDescription];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Result" :YES];
      }
      break;
    }
    case 10 /*EID_SEARCHCOMPLETE*/: {
      int messageId = (int)(long)param[0];
      NSString* DNT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* DN = DNT;
      int resultCode = (int)(long)param[2];
      NSString* resultDescriptionT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* resultDescription = resultDescriptionT;
      @try {
        [ctl onSearchComplete :messageId :DN :resultCode :resultDescription];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SearchComplete" :YES];
      }
      break;
    }
    case 11 /*EID_SEARCHPAGE*/: {
      int messageId = (int)(long)param[0];
      NSString* DNT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* DN = DNT;
      int resultCode = (int)(long)param[2];
      NSString* resultDescriptionT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* resultDescription = resultDescriptionT;
      int* cancelSearch = (int*)&param[4];
      @try {
        [ctl onSearchPage :messageId :DN :resultCode :resultDescription :cancelSearch];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SearchPage" :YES];
      }
      break;
    }
    case 12 /*EID_SEARCHRESULT*/: {
      int messageId = (int)(long)param[0];
      NSString* DNT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* DN = DNT;
      @try {
        [ctl onSearchResult :messageId :DN];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SearchResult" :YES];
      }
      break;
    }
    case 13 /*EID_SEARCHRESULTREFERENCE*/: {
      int messageId = (int)(long)param[0];
      NSString* ldapUrlT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* ldapUrl = ldapUrlT;
      @try {
        [ctl onSearchResultReference :messageId :ldapUrl];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SearchResultReference" :YES];
      }
      break;
    }
    case 14 /*EID_SSLSERVERAUTHENTICATION*/: {
      NSData* certEncoded = [NSData dataWithBytesNoCopy:param[0] length:cbparam[0] freeWhenDone:NO];
      NSString* certSubjectT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* certSubject = certSubjectT;
      NSString* certIssuerT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* certIssuer = certIssuerT;
      NSString* statusT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* status = statusT;
      int* accept = (int*)&param[4];
      @try {
        [ctl onSSLServerAuthentication :certEncoded :certSubject :certIssuer :status :accept];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SSLServerAuthentication" :YES];
      }
      break;
    }
    case 15 /*EID_SSLSTATUS*/: {
      NSString* messageT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* message = messageT;
      @try {
        [ctl onSSLStatus :message];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SSLStatus" :YES];
      }
      break;
    }
    case 16 /*EID_USERLIST*/: {
      NSString* nameT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* name = nameT;
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      NSString* lastLogonT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* lastLogon = lastLogonT;
      NSString* memberOfT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* memberOf = memberOfT;
      NSString* dnT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* dn = dnT;
      @try {
        [ctl onUserList :name :description :lastLogon :memberOf :dn];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"UserList" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksLDAP

+ (IPWorksLDAP*)ldap
{
#if __has_feature(objc_arc)
  return [[IPWorksLDAP alloc] init];
#else
  return [[[IPWorksLDAP alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_LDAP_Create((void*)LDAP_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_LDAP_Create((void*)LDAP_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_LDAP_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_LDAP_Destroy(m_pObj);
    m_pObj = NULL;
  }
  if (m_rNotifiers) {
    for (int i = 0; i < CFArrayGetCount(m_rNotifiers); i++) {
      const void* notifier = CFArrayGetValueAtIndex(m_rNotifiers, i);
      CFSocketInvalidate((CFSocketRef)notifier);
    }
    CFArrayRemoveAllValues(m_rNotifiers);
    CFRelease(m_rNotifiers);
  }
#if __has_feature(objc_arc)
#else
  [super dealloc];
#endif
}

- (NSString*)lastError
{
  return [NSString stringWithCString:(const char*)IPWorks_LDAP_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_LDAP_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_LDAP_GetEventErrorCode(m_pObj);
}

- (id <IPWorksLDAPDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksLDAPDelegate>)anObject
{
  m_delegateHasComputerList = NO;
  m_delegateHasConnected = NO;
  m_delegateHasConnectionStatus = NO;
  m_delegateHasDisconnected = NO;
  m_delegateHasError = NO;
  m_delegateHasExtendedResponse = NO;
  m_delegateHasGroupList = NO;
  m_delegateHasPITrail = NO;
  m_delegateHasResult = NO;
  m_delegateHasSearchComplete = NO;
  m_delegateHasSearchPage = NO;
  m_delegateHasSearchResult = NO;
  m_delegateHasSearchResultReference = NO;
  m_delegateHasSSLServerAuthentication = NO;
  m_delegateHasSSLStatus = NO;
  m_delegateHasUserList = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onComputerList:::::)]) m_delegateHasComputerList = YES;
    if ([m_delegate respondsToSelector:@selector(onConnected::)]) m_delegateHasConnected = YES;
    if ([m_delegate respondsToSelector:@selector(onConnectionStatus:::)]) m_delegateHasConnectionStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onDisconnected::)]) m_delegateHasDisconnected = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onExtendedResponse::::::)]) m_delegateHasExtendedResponse = YES;
    if ([m_delegate respondsToSelector:@selector(onGroupList:::)]) m_delegateHasGroupList = YES;
    if ([m_delegate respondsToSelector:@selector(onPITrail:::)]) m_delegateHasPITrail = YES;
    if ([m_delegate respondsToSelector:@selector(onResult::::)]) m_delegateHasResult = YES;
    if ([m_delegate respondsToSelector:@selector(onSearchComplete::::)]) m_delegateHasSearchComplete = YES;
    if ([m_delegate respondsToSelector:@selector(onSearchPage:::::)]) m_delegateHasSearchPage = YES;
    if ([m_delegate respondsToSelector:@selector(onSearchResult::)]) m_delegateHasSearchResult = YES;
    if ([m_delegate respondsToSelector:@selector(onSearchResultReference::)]) m_delegateHasSearchResultReference = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLServerAuthentication:::::)]) m_delegateHasSSLServerAuthentication = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLStatus:)]) m_delegateHasSSLStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onUserList:::::)]) m_delegateHasUserList = YES;
  }
}

  /* Events */

- (void)onComputerList:(NSString*)name :(NSString*)operatingSystem :(NSString*)lastLogon :(int)logonCount :(NSString*)dn
{
  if (m_delegate != nil && m_delegateHasComputerList)
    [m_delegate onComputerList:name :operatingSystem :lastLogon :logonCount :dn];
}
- (void)onConnected:(int)statusCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasConnected)
    [m_delegate onConnected:statusCode :description];
}
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasConnectionStatus)
    [m_delegate onConnectionStatus:connectionEvent :statusCode :description];
}
- (void)onDisconnected:(int)statusCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasDisconnected)
    [m_delegate onDisconnected:statusCode :description];
}
- (void)onError:(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:errorCode :description];
}
- (void)onExtendedResponse:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription :(NSString*)responseName :(NSData*)responseValue
{
  if (m_delegate != nil && m_delegateHasExtendedResponse)
    [m_delegate onExtendedResponse:messageId :DN :resultCode :resultDescription :responseName :responseValue];
}
- (void)onGroupList:(NSString*)name :(NSString*)description :(NSString*)dn
{
  if (m_delegate != nil && m_delegateHasGroupList)
    [m_delegate onGroupList:name :description :dn];
}
- (void)onPITrail:(int)direction :(NSString*)description :(NSString*)message
{
  if (m_delegate != nil && m_delegateHasPITrail)
    [m_delegate onPITrail:direction :description :message];
}
- (void)onResult:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription
{
  if (m_delegate != nil && m_delegateHasResult)
    [m_delegate onResult:messageId :DN :resultCode :resultDescription];
}
- (void)onSearchComplete:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription
{
  if (m_delegate != nil && m_delegateHasSearchComplete)
    [m_delegate onSearchComplete:messageId :DN :resultCode :resultDescription];
}
- (void)onSearchPage:(int)messageId :(NSString*)DN :(int)resultCode :(NSString*)resultDescription :(int*)cancelSearch
{
  if (m_delegate != nil && m_delegateHasSearchPage)
    [m_delegate onSearchPage:messageId :DN :resultCode :resultDescription :cancelSearch];
}
- (void)onSearchResult:(int)messageId :(NSString*)DN
{
  if (m_delegate != nil && m_delegateHasSearchResult)
    [m_delegate onSearchResult:messageId :DN];
}
- (void)onSearchResultReference:(int)messageId :(NSString*)ldapUrl
{
  if (m_delegate != nil && m_delegateHasSearchResultReference)
    [m_delegate onSearchResultReference:messageId :ldapUrl];
}
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept
{
  if (m_delegate != nil && m_delegateHasSSLServerAuthentication)
    [m_delegate onSSLServerAuthentication:certEncoded :certSubject :certIssuer :status :accept];
}
- (void)onSSLStatus:(NSString*)message
{
  if (m_delegate != nil && m_delegateHasSSLStatus)
    [m_delegate onSSLStatus:message];
}
- (void)onUserList:(NSString*)name :(NSString*)description :(NSString*)lastLogon :(NSString*)memberOf :(NSString*)dn
{
  if (m_delegate != nil && m_delegateHasUserList)
    [m_delegate onUserList:name :description :lastLogon :memberOf :dn];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_LDAP_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_LDAP_Get(m_pObj, 0, 0, 0, nil);
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)raiseNSException
{
  return m_raiseNSException;
}

- (void)setRaiseNSException:(BOOL)newRaiseNSException
{
  m_raiseNSException = newRaiseNSException;
}

- (BOOL)acceptData
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setAcceptData:(BOOL)newAcceptData
{
  void *val = (void*)(long)(newAcceptData ? 1 : 0);
  int ret_code = IPWorks_LDAP_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)attrCount
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAttrCount:(int)newAttrCount
{
  void *val = (void*)(long)newAttrCount;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)attrType:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 3, attrIndex, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAttrType:(int)attrIndex:(NSString*)newAttrType
{
  void *val = (void*)[self nsstringToCString:newAttrType];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 3, attrIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)attrModOp:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 4, attrIndex, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAttrModOp:(int)attrIndex:(int)newAttrModOp
{
  void *val = (void*)(long)newAttrModOp;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 4, attrIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)attrValue:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 5, attrIndex, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setAttrValue:(int)attrIndex:(NSString*)newAttrValue
{
  int len = (int)[newAttrValue lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newAttrValue];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 5, attrIndex, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)attrValueB:(int)attrIndex
{
  int len = 0;
  void* val = IPWorks_LDAP_Get(m_pObj, 5, attrIndex, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setAttrValueB:(int)attrIndex :(NSData*)newAttrValue
{
  int len = (int)[newAttrValue length];
  void *val = (void*)[newAttrValue bytes];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 5, attrIndex, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)authMechanism
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAuthMechanism:(int)newAuthMechanism
{
  void *val = (void*)(long)newAuthMechanism;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 6, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)connected
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setConnected:(BOOL)newConnected
{
  void *val = (void*)(long)(newConnected ? 1 : 0);
  int ret_code = IPWorks_LDAP_Set(m_pObj, 7, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)deleteOldRDN
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setDeleteOldRDN:(BOOL)newDeleteOldRDN
{
  void *val = (void*)(long)(newDeleteOldRDN ? 1 : 0);
  int ret_code = IPWorks_LDAP_Set(m_pObj, 8, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)DN
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setDN:(NSString*)newDN
{
  void *val = (void*)[self nsstringToCString:newDN];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 9, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)firewallAutoDetect
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect
{
  void *val = (void*)(long)(newFirewallAutoDetect ? 1 : 0);
  int ret_code = IPWorks_LDAP_Set(m_pObj, 10, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallType
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallType:(int)newFirewallType
{
  void *val = (void*)(long)newFirewallType;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 11, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallHost
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallHost:(NSString*)newFirewallHost
{
  void *val = (void*)[self nsstringToCString:newFirewallHost];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 12, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallPassword
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallPassword:(NSString*)newFirewallPassword
{
  void *val = (void*)[self nsstringToCString:newFirewallPassword];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 13, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallPort
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallPort:(int)newFirewallPort
{
  void *val = (void*)(long)newFirewallPort;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 14, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallUser
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallUser:(NSString*)newFirewallUser
{
  void *val = (void*)[self nsstringToCString:newFirewallUser];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (int)LDAPVersion
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setLDAPVersion:(int)newLDAPVersion
{
  void *val = (void*)(long)newLDAPVersion;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 18, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)messageId
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setMessageId:(int)newMessageId
{
  void *val = (void*)(long)newMessageId;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 19, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)pageSize
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setPageSize:(int)newPageSize
{
  void *val = (void*)(long)newPageSize;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 20, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)password
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPassword:(NSString*)newPassword
{
  void *val = (void*)[self nsstringToCString:newPassword];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)referenceCount
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)referenceURL:(int)referenceIndex
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 23, referenceIndex, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)resultCode
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)resultDescription
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)resultDN
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)searchDerefAliases
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSearchDerefAliases:(int)newSearchDerefAliases
{
  void *val = (void*)(long)newSearchDerefAliases;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 27, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)searchReturnValues
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setSearchReturnValues:(BOOL)newSearchReturnValues
{
  void *val = (void*)(long)(newSearchReturnValues ? 1 : 0);
  int ret_code = IPWorks_LDAP_Set(m_pObj, 28, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)searchScope
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 29, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSearchScope:(int)newSearchScope
{
  void *val = (void*)(long)newSearchScope;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 29, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)searchSizeLimit
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSearchSizeLimit:(int)newSearchSizeLimit
{
  void *val = (void*)(long)newSearchSizeLimit;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 30, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)searchTimeLimit
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSearchTimeLimit:(int)newSearchTimeLimit
{
  void *val = (void*)(long)newSearchTimeLimit;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 31, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)serverName
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setServerName:(NSString*)newServerName
{
  void *val = (void*)[self nsstringToCString:newServerName];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 32, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)serverPort
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 33, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setServerPort:(int)newServerPort
{
  void *val = (void*)(long)newServerPort;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 33, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)sortAttributes
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 34, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSortAttributes:(NSString*)newSortAttributes
{
  void *val = (void*)[self nsstringToCString:newSortAttributes];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 34, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLAcceptServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 35, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLAcceptServerCertEncoded];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 35, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLAcceptServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_LDAP_Get(m_pObj, 35, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded length];
  void *val = (void*)[newSSLAcceptServerCertEncoded bytes];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 35, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 36, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 36, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_LDAP_Get(m_pObj, 36, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 36, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 37, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 37, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_LDAP_Get(m_pObj, 37, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 37, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 38, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 38, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 39, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 39, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 40, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_LDAP_Set(m_pObj, 40, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)SSLEnabled
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 41, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setSSLEnabled:(BOOL)newSSLEnabled
{
  void *val = (void*)(long)(newSSLEnabled ? 1 : 0);
  int ret_code = IPWorks_LDAP_Set(m_pObj, 41, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 42, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)SSLServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_LDAP_Get(m_pObj, 42, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (int)SSLStartMode
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 43, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLStartMode:(int)newSSLStartMode
{
  void *val = (void*)(long)newSSLStartMode;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 43, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_LDAP_Get(m_pObj, 44, 0, &len, nil);
  if (IPWorks_LDAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_LDAP_Set(m_pObj, 44, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (void)abandon:(int)messageId
{
  void *param[1+1] = {(void*)(long)messageId, NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)add
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)attr:(NSString*)attrType
{
  void *param[1+1] = {(void*)[self nsstringToCString:attrType], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 4, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)bind
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 5, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)changePassword:(NSString*)user :(NSString*)oldPassword :(NSString*)newPassword
{
  void *param[3+1] = {(void*)[self nsstringToCString:user], (void*)[self nsstringToCString:oldPassword], (void*)[self nsstringToCString:newPassword], NULL};
  int cbparam[3+1] = {0, 0, 0, 0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 6, 3, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)compare
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 7, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 8, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)delete
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 9, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 10, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)extendedRequest:(NSString*)requestName :(NSData*)requestValue
{
  void *param[2+1] = {(void*)[self nsstringToCString:requestName], (void*)[requestValue bytes], NULL};
  int cbparam[2+1] = {0, (int)[requestValue length], 0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 11, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 12, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)listComputers
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 13, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)listGroupMembers:(NSString*)group
{
  void *param[1+1] = {(void*)[self nsstringToCString:group], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 14, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)listGroups
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 15, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)listUserGroups:(NSString*)user
{
  void *param[1+1] = {(void*)[self nsstringToCString:user], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 16, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)modify
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 17, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)modifyRDN:(NSString*)newRDN
{
  void *param[1+1] = {(void*)[self nsstringToCString:newRDN], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 18, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)moveToDN:(NSString*)newSuperior
{
  void *param[1+1] = {(void*)[self nsstringToCString:newSuperior], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 19, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 20, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)search:(NSString*)searchFilter
{
  void *param[1+1] = {(void*)[self nsstringToCString:searchFilter], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 21, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)unbind
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_LDAP_Do(m_pObj, 22, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}


- (const char*)nsstringToCString:(NSString*)str {
  const char* cstr = [str cStringUsingEncoding:[self innerGetCodePage]];
  if (cstr == NULL && m_raiseNSException) [NSException raise:ENCODING_CONVERSION_ERROR format:@"%@", ENCODING_CONVERSION_ERROR];
  return cstr;
}

- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen {
  NSStringEncoding enc = [self innerGetCodePage];
  if (![str canBeConvertedToEncoding:enc])
    [NSException raise:ENCODING_CONVERSION_ERROR format:@"%@", ENCODING_CONVERSION_ERROR];
  if (![str getCString:dest maxLength:(unsigned long)destLen encoding:enc])
    [NSException raise:BUFFER_TOO_SMALL_CONVERSION_ERROR format:@"%@", BUFFER_TOO_SMALL_CONVERSION_ERROR];
  return [str lengthOfBytesUsingEncoding:enc];
}

- (NSDate*)longLongToNSDate:(long long)secsSince1970 {
  NSNumber* n = [NSNumber numberWithLongLong:secsSince1970];
  return [NSDate dateWithTimeIntervalSince1970:[n doubleValue]];
}

- (long long)nsdateToLongLong:(NSDate*)date {
  NSNumber* n = [NSNumber numberWithDouble:[date timeIntervalSince1970]];
  return [n longLongValue];
}

- (NSStringEncoding)innerGetCodePage {
  int len = 0;
  int codePage = (int)(long)IPWorks_LDAP_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_LDAP_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end