
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksRSS.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksRSS()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define RSS_EXTERN extern "C"
#else
#define RSS_EXTERN extern
#endif

RSS_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
RSS_EXTERN void* IPWorks_RSS_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
RSS_EXTERN int   IPWorks_RSS_Destroy(void* lpObj);
RSS_EXTERN int   IPWorks_RSS_CheckIndex(void* lpObj, int propid, int arridx);
RSS_EXTERN void* IPWorks_RSS_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
RSS_EXTERN int   IPWorks_RSS_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
RSS_EXTERN int   IPWorks_RSS_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
RSS_EXTERN char* IPWorks_RSS_GetLastError(void* lpObj);
RSS_EXTERN int   IPWorks_RSS_GetLastErrorCode(void* lpObj);
RSS_EXTERN int   IPWorks_RSS_SetLastErrorAndCode(void* lpObj, int code, char* message);
RSS_EXTERN char* IPWorks_RSS_GetEventError(void* lpObj);
RSS_EXTERN int   IPWorks_RSS_GetEventErrorCode(void* lpObj);
RSS_EXTERN int   IPWorks_RSS_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void RSS_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_RSS_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int RSS_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksRSS* ctl = (IPWorksRSS*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, RSS_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (RSS)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
      [myAlert show];
      return 1;
#else // TARGET_OS_IPHONE
      return 0;
#endif // TARGET_OS_IPHONE
    }

    case 1 /*EID_CONNECTED*/: {
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
    case 2 /*EID_CONNECTIONSTATUS*/: {
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
    case 3 /*EID_DISCONNECTED*/: {
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
    case 4 /*EID_ENDTRANSFER*/: {
      int direction = (int)(long)param[0];
      @try {
        [ctl onEndTransfer :direction];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EndTransfer" :YES];
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
    case 6 /*EID_HEADER*/: {
      NSString* fieldT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* field = fieldT;
      NSString* valueT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* value = valueT;
      @try {
        [ctl onHeader :field :value];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Header" :YES];
      }
      break;
    }
    case 7 /*EID_LOG*/: {
      int logLevel = (int)(long)param[0];
      NSString* messageT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* message = messageT;
      NSString* logTypeT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* logType = logTypeT;
      @try {
        [ctl onLog :logLevel :message :logType];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Log" :YES];
      }
      break;
    }
    case 8 /*EID_OPMLHEADER*/: {
      NSString* fieldT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* field = fieldT;
      NSString* valueT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* value = valueT;
      @try {
        [ctl onOPMLHeader :field :value];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"OPMLHeader" :YES];
      }
      break;
    }
    case 9 /*EID_OPMLOUTLINE*/: {
      int level = (int)(long)param[0];
      NSString* textT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* text = textT;
      NSString* typeNameT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* typeName = typeNameT;
      NSString* titleT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* title = titleT;
      NSString* URLT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* URL = URLT;
      NSString* XMLURLT = [NSString stringWithCString:(const char*)param[5] encoding:[ctl innerGetCodePage]];
      NSString* XMLURL = XMLURLT;
      NSString* HTMLURLT = [NSString stringWithCString:(const char*)param[6] encoding:[ctl innerGetCodePage]];
      NSString* HTMLURL = HTMLURLT;
      NSString* createdT = [NSString stringWithCString:(const char*)param[7] encoding:[ctl innerGetCodePage]];
      NSString* created = createdT;
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[8] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      NSString* otherAttrsT = [NSString stringWithCString:(const char*)param[9] encoding:[ctl innerGetCodePage]];
      NSString* otherAttrs = otherAttrsT;
      @try {
        [ctl onOPMLOutline :level :text :typeName :title :URL :XMLURL :HTMLURL :created :description :otherAttrs];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"OPMLOutline" :YES];
      }
      break;
    }
    case 10 /*EID_REDIRECT*/: {
      NSString* locationT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* location = locationT;
      int* accept = (int*)&param[1];
      @try {
        [ctl onRedirect :location :accept];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Redirect" :YES];
      }
      break;
    }
    case 11 /*EID_SETCOOKIE*/: {
      NSString* nameT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* name = nameT;
      NSString* valueT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* value = valueT;
      NSString* expiresT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* expires = expiresT;
      NSString* domainT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* domain = domainT;
      NSString* pathT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* path = pathT;
      BOOL secure = param[5] ? YES : NO;
      @try {
        [ctl onSetCookie :name :value :expires :domain :path :secure];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SetCookie" :YES];
      }
      break;
    }
    case 12 /*EID_SSLSERVERAUTHENTICATION*/: {
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
    case 13 /*EID_SSLSTATUS*/: {
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
    case 14 /*EID_STARTTRANSFER*/: {
      int direction = (int)(long)param[0];
      @try {
        [ctl onStartTransfer :direction];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StartTransfer" :YES];
      }
      break;
    }
    case 15 /*EID_STATUS*/: {
      NSString* HTTPVersionT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* HTTPVersion = HTTPVersionT;
      int statusCode = (int)(long)param[1];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      @try {
        [ctl onStatus :HTTPVersion :statusCode :description];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Status" :YES];
      }
      break;
    }
    case 16 /*EID_TRANSFER*/: {
      int direction = (int)(long)param[0];
      long long bytesTransferred = *(long long*)param[1];
      int percentDone = (int)(long)param[2];
      NSData* text = [NSData dataWithBytesNoCopy:param[3] length:cbparam[3] freeWhenDone:NO];
      @try {
        [ctl onTransfer :direction :bytesTransferred :percentDone :text];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Transfer" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksRSS

+ (IPWorksRSS*)rss
{
#if __has_feature(objc_arc)
  return [[IPWorksRSS alloc] init];
#else
  return [[[IPWorksRSS alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_RSS_Create((void*)RSS_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_RSS_Create((void*)RSS_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_RSS_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_RSS_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_RSS_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_RSS_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_RSS_GetEventErrorCode(m_pObj);
}

- (id <IPWorksRSSDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksRSSDelegate>)anObject
{
  m_delegateHasConnected = NO;
  m_delegateHasConnectionStatus = NO;
  m_delegateHasDisconnected = NO;
  m_delegateHasEndTransfer = NO;
  m_delegateHasError = NO;
  m_delegateHasHeader = NO;
  m_delegateHasLog = NO;
  m_delegateHasOPMLHeader = NO;
  m_delegateHasOPMLOutline = NO;
  m_delegateHasRedirect = NO;
  m_delegateHasSetCookie = NO;
  m_delegateHasSSLServerAuthentication = NO;
  m_delegateHasSSLStatus = NO;
  m_delegateHasStartTransfer = NO;
  m_delegateHasStatus = NO;
  m_delegateHasTransfer = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onConnected::)]) m_delegateHasConnected = YES;
    if ([m_delegate respondsToSelector:@selector(onConnectionStatus:::)]) m_delegateHasConnectionStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onDisconnected::)]) m_delegateHasDisconnected = YES;
    if ([m_delegate respondsToSelector:@selector(onEndTransfer:)]) m_delegateHasEndTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onHeader::)]) m_delegateHasHeader = YES;
    if ([m_delegate respondsToSelector:@selector(onLog:::)]) m_delegateHasLog = YES;
    if ([m_delegate respondsToSelector:@selector(onOPMLHeader::)]) m_delegateHasOPMLHeader = YES;
    if ([m_delegate respondsToSelector:@selector(onOPMLOutline::::::::::)]) m_delegateHasOPMLOutline = YES;
    if ([m_delegate respondsToSelector:@selector(onRedirect::)]) m_delegateHasRedirect = YES;
    if ([m_delegate respondsToSelector:@selector(onSetCookie::::::)]) m_delegateHasSetCookie = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLServerAuthentication:::::)]) m_delegateHasSSLServerAuthentication = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLStatus:)]) m_delegateHasSSLStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onStartTransfer:)]) m_delegateHasStartTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onStatus:::)]) m_delegateHasStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onTransfer::::)]) m_delegateHasTransfer = YES;
  }
}

  /* Events */

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
- (void)onEndTransfer:(int)direction
{
  if (m_delegate != nil && m_delegateHasEndTransfer)
    [m_delegate onEndTransfer:direction];
}
- (void)onError:(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:errorCode :description];
}
- (void)onHeader:(NSString*)field :(NSString*)value
{
  if (m_delegate != nil && m_delegateHasHeader)
    [m_delegate onHeader:field :value];
}
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType
{
  if (m_delegate != nil && m_delegateHasLog)
    [m_delegate onLog:logLevel :message :logType];
}
- (void)onOPMLHeader:(NSString*)field :(NSString*)value
{
  if (m_delegate != nil && m_delegateHasOPMLHeader)
    [m_delegate onOPMLHeader:field :value];
}
- (void)onOPMLOutline:(int)level :(NSString*)text :(NSString*)typeName :(NSString*)title :(NSString*)URL :(NSString*)XMLURL :(NSString*)HTMLURL :(NSString*)created :(NSString*)description :(NSString*)otherAttrs
{
  if (m_delegate != nil && m_delegateHasOPMLOutline)
    [m_delegate onOPMLOutline:level :text :typeName :title :URL :XMLURL :HTMLURL :created :description :otherAttrs];
}
- (void)onRedirect:(NSString*)location :(int*)accept
{
  if (m_delegate != nil && m_delegateHasRedirect)
    [m_delegate onRedirect:location :accept];
}
- (void)onSetCookie:(NSString*)name :(NSString*)value :(NSString*)expires :(NSString*)domain :(NSString*)path :(BOOL)secure
{
  if (m_delegate != nil && m_delegateHasSetCookie)
    [m_delegate onSetCookie:name :value :expires :domain :path :secure];
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
- (void)onStartTransfer:(int)direction
{
  if (m_delegate != nil && m_delegateHasStartTransfer)
    [m_delegate onStartTransfer:direction];
}
- (void)onStatus:(NSString*)HTTPVersion :(int)statusCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasStatus)
    [m_delegate onStatus:HTTPVersion :statusCode :description];
}
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text
{
  if (m_delegate != nil && m_delegateHasTransfer)
    [m_delegate onTransfer:direction :bytesTransferred :percentDone :text];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_RSS_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_RSS_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_RSS_Get(m_pObj, 0, 0, 0, nil);
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

- (NSString*)accept
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAccept:(NSString*)newAccept
{
  void *val = (void*)[self nsstringToCString:newAccept];
  int ret_code = IPWorks_RSS_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)authorization
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAuthorization:(NSString*)newAuthorization
{
  void *val = (void*)[self nsstringToCString:newAuthorization];
  int ret_code = IPWorks_RSS_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)authScheme
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAuthScheme:(int)newAuthScheme
{
  void *val = (void*)(long)newAuthScheme;
  int ret_code = IPWorks_RSS_Set(m_pObj, 3, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelCategory
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelCategory:(NSString*)newChannelCategory
{
  void *val = (void*)[self nsstringToCString:newChannelCategory];
  int ret_code = IPWorks_RSS_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelCategoryDomain
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelCategoryDomain:(NSString*)newChannelCategoryDomain
{
  void *val = (void*)[self nsstringToCString:newChannelCategoryDomain];
  int ret_code = IPWorks_RSS_Set(m_pObj, 5, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelCopyright
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelCopyright:(NSString*)newChannelCopyright
{
  void *val = (void*)[self nsstringToCString:newChannelCopyright];
  int ret_code = IPWorks_RSS_Set(m_pObj, 6, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelDescription
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelDescription:(NSString*)newChannelDescription
{
  void *val = (void*)[self nsstringToCString:newChannelDescription];
  int ret_code = IPWorks_RSS_Set(m_pObj, 7, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelDocs
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelDocs:(NSString*)newChannelDocs
{
  void *val = (void*)[self nsstringToCString:newChannelDocs];
  int ret_code = IPWorks_RSS_Set(m_pObj, 8, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelGenerator
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelGenerator:(NSString*)newChannelGenerator
{
  void *val = (void*)[self nsstringToCString:newChannelGenerator];
  int ret_code = IPWorks_RSS_Set(m_pObj, 9, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelImageDescription
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelImageDescription:(NSString*)newChannelImageDescription
{
  void *val = (void*)[self nsstringToCString:newChannelImageDescription];
  int ret_code = IPWorks_RSS_Set(m_pObj, 10, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelImageHeight
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelImageHeight:(NSString*)newChannelImageHeight
{
  void *val = (void*)[self nsstringToCString:newChannelImageHeight];
  int ret_code = IPWorks_RSS_Set(m_pObj, 11, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelImageLink
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelImageLink:(NSString*)newChannelImageLink
{
  void *val = (void*)[self nsstringToCString:newChannelImageLink];
  int ret_code = IPWorks_RSS_Set(m_pObj, 12, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelImageTitle
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelImageTitle:(NSString*)newChannelImageTitle
{
  void *val = (void*)[self nsstringToCString:newChannelImageTitle];
  int ret_code = IPWorks_RSS_Set(m_pObj, 13, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelImageUrl
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelImageUrl:(NSString*)newChannelImageUrl
{
  void *val = (void*)[self nsstringToCString:newChannelImageUrl];
  int ret_code = IPWorks_RSS_Set(m_pObj, 14, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelImageWidth
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelImageWidth:(NSString*)newChannelImageWidth
{
  void *val = (void*)[self nsstringToCString:newChannelImageWidth];
  int ret_code = IPWorks_RSS_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLanguage
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLanguage:(NSString*)newChannelLanguage
{
  void *val = (void*)[self nsstringToCString:newChannelLanguage];
  int ret_code = IPWorks_RSS_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLastBuildDate
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLastBuildDate:(NSString*)newChannelLastBuildDate
{
  void *val = (void*)[self nsstringToCString:newChannelLastBuildDate];
  int ret_code = IPWorks_RSS_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLink
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLink:(NSString*)newChannelLink
{
  void *val = (void*)[self nsstringToCString:newChannelLink];
  int ret_code = IPWorks_RSS_Set(m_pObj, 18, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelManagingEditor
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelManagingEditor:(NSString*)newChannelManagingEditor
{
  void *val = (void*)[self nsstringToCString:newChannelManagingEditor];
  int ret_code = IPWorks_RSS_Set(m_pObj, 19, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelPubDate
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelPubDate:(NSString*)newChannelPubDate
{
  void *val = (void*)[self nsstringToCString:newChannelPubDate];
  int ret_code = IPWorks_RSS_Set(m_pObj, 20, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelSkipDays
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelSkipDays:(NSString*)newChannelSkipDays
{
  void *val = (void*)[self nsstringToCString:newChannelSkipDays];
  int ret_code = IPWorks_RSS_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelSkipHours
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelSkipHours:(NSString*)newChannelSkipHours
{
  void *val = (void*)[self nsstringToCString:newChannelSkipHours];
  int ret_code = IPWorks_RSS_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelTitle
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelTitle:(NSString*)newChannelTitle
{
  void *val = (void*)[self nsstringToCString:newChannelTitle];
  int ret_code = IPWorks_RSS_Set(m_pObj, 23, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelTtl
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelTtl:(NSString*)newChannelTtl
{
  void *val = (void*)[self nsstringToCString:newChannelTtl];
  int ret_code = IPWorks_RSS_Set(m_pObj, 24, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelWebMaster
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelWebMaster:(NSString*)newChannelWebMaster
{
  void *val = (void*)[self nsstringToCString:newChannelWebMaster];
  int ret_code = IPWorks_RSS_Set(m_pObj, 25, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)connected
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setConnected:(BOOL)newConnected
{
  void *val = (void*)(long)(newConnected ? 1 : 0);
  int ret_code = IPWorks_RSS_Set(m_pObj, 26, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)cookieCount
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setCookieCount:(int)newCookieCount
{
  void *val = (void*)(long)newCookieCount;
  int ret_code = IPWorks_RSS_Set(m_pObj, 27, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookieDomain:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 28, cookieIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieExpiration:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 29, cookieIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieName:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 30, cookieIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieName:(int)cookieIndex:(NSString*)newCookieName
{
  void *val = (void*)[self nsstringToCString:newCookieName];
  int ret_code = IPWorks_RSS_Set(m_pObj, 30, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookiePath:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 31, cookieIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)cookieSecure:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 32, cookieIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)cookieValue:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 33, cookieIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieValue:(int)cookieIndex:(NSString*)newCookieValue
{
  void *val = (void*)[self nsstringToCString:newCookieValue];
  int ret_code = IPWorks_RSS_Set(m_pObj, 33, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)firewallAutoDetect
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 34, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect
{
  void *val = (void*)(long)(newFirewallAutoDetect ? 1 : 0);
  int ret_code = IPWorks_RSS_Set(m_pObj, 34, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallType
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 35, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallType:(int)newFirewallType
{
  void *val = (void*)(long)newFirewallType;
  int ret_code = IPWorks_RSS_Set(m_pObj, 35, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallHost
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 36, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallHost:(NSString*)newFirewallHost
{
  void *val = (void*)[self nsstringToCString:newFirewallHost];
  int ret_code = IPWorks_RSS_Set(m_pObj, 36, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallPassword
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 37, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallPassword:(NSString*)newFirewallPassword
{
  void *val = (void*)[self nsstringToCString:newFirewallPassword];
  int ret_code = IPWorks_RSS_Set(m_pObj, 37, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallPort
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 38, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallPort:(int)newFirewallPort
{
  void *val = (void*)(long)newFirewallPort;
  int ret_code = IPWorks_RSS_Set(m_pObj, 38, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallUser
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 39, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallUser:(NSString*)newFirewallUser
{
  void *val = (void*)[self nsstringToCString:newFirewallUser];
  int ret_code = IPWorks_RSS_Set(m_pObj, 39, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)followRedirects
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 40, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFollowRedirects:(int)newFollowRedirects
{
  void *val = (void*)(long)newFollowRedirects;
  int ret_code = IPWorks_RSS_Set(m_pObj, 40, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 41, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)ifModifiedSince
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 42, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setIfModifiedSince:(NSString*)newIfModifiedSince
{
  void *val = (void*)[self nsstringToCString:newIfModifiedSince];
  int ret_code = IPWorks_RSS_Set(m_pObj, 42, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)itemCount
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 43, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setItemCount:(int)newItemCount
{
  void *val = (void*)(long)newItemCount;
  int ret_code = IPWorks_RSS_Set(m_pObj, 43, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemAuthor:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 44, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemAuthor:(int)itemIndex:(NSString*)newItemAuthor
{
  void *val = (void*)[self nsstringToCString:newItemAuthor];
  int ret_code = IPWorks_RSS_Set(m_pObj, 44, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemCategory:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 45, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemCategory:(int)itemIndex:(NSString*)newItemCategory
{
  void *val = (void*)[self nsstringToCString:newItemCategory];
  int ret_code = IPWorks_RSS_Set(m_pObj, 45, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemCategoryDomain:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 46, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemCategoryDomain:(int)itemIndex:(NSString*)newItemCategoryDomain
{
  void *val = (void*)[self nsstringToCString:newItemCategoryDomain];
  int ret_code = IPWorks_RSS_Set(m_pObj, 46, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemComments:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 47, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemComments:(int)itemIndex:(NSString*)newItemComments
{
  void *val = (void*)[self nsstringToCString:newItemComments];
  int ret_code = IPWorks_RSS_Set(m_pObj, 47, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemDescription:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 48, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemDescription:(int)itemIndex:(NSString*)newItemDescription
{
  void *val = (void*)[self nsstringToCString:newItemDescription];
  int ret_code = IPWorks_RSS_Set(m_pObj, 48, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemEnclosureLength:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 49, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemEnclosureLength:(int)itemIndex:(NSString*)newItemEnclosureLength
{
  void *val = (void*)[self nsstringToCString:newItemEnclosureLength];
  int ret_code = IPWorks_RSS_Set(m_pObj, 49, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemEnclosureType:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 50, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemEnclosureType:(int)itemIndex:(NSString*)newItemEnclosureType
{
  void *val = (void*)[self nsstringToCString:newItemEnclosureType];
  int ret_code = IPWorks_RSS_Set(m_pObj, 50, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemEnclosureUrl:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 51, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemEnclosureUrl:(int)itemIndex:(NSString*)newItemEnclosureUrl
{
  void *val = (void*)[self nsstringToCString:newItemEnclosureUrl];
  int ret_code = IPWorks_RSS_Set(m_pObj, 51, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemGuid:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 52, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemGuid:(int)itemIndex:(NSString*)newItemGuid
{
  void *val = (void*)[self nsstringToCString:newItemGuid];
  int ret_code = IPWorks_RSS_Set(m_pObj, 52, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)itemGuidIsPermaLink:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 53, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setItemGuidIsPermaLink:(int)itemIndex:(BOOL)newItemGuidIsPermaLink
{
  void *val = (void*)(long)(newItemGuidIsPermaLink ? 1 : 0);
  int ret_code = IPWorks_RSS_Set(m_pObj, 53, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemXML:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 54, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemXML:(int)itemIndex:(NSString*)newItemXML
{
  void *val = (void*)[self nsstringToCString:newItemXML];
  int ret_code = IPWorks_RSS_Set(m_pObj, 54, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemLink:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 55, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemLink:(int)itemIndex:(NSString*)newItemLink
{
  void *val = (void*)[self nsstringToCString:newItemLink];
  int ret_code = IPWorks_RSS_Set(m_pObj, 55, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemPubDate:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 56, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemPubDate:(int)itemIndex:(NSString*)newItemPubDate
{
  void *val = (void*)[self nsstringToCString:newItemPubDate];
  int ret_code = IPWorks_RSS_Set(m_pObj, 56, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemSource:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 57, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemSource:(int)itemIndex:(NSString*)newItemSource
{
  void *val = (void*)[self nsstringToCString:newItemSource];
  int ret_code = IPWorks_RSS_Set(m_pObj, 57, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemSourceURL:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 58, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemSourceURL:(int)itemIndex:(NSString*)newItemSourceURL
{
  void *val = (void*)[self nsstringToCString:newItemSourceURL];
  int ret_code = IPWorks_RSS_Set(m_pObj, 58, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)itemTitle:(int)itemIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 59, itemIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setItemTitle:(int)itemIndex:(NSString*)newItemTitle
{
  void *val = (void*)[self nsstringToCString:newItemTitle];
  int ret_code = IPWorks_RSS_Set(m_pObj, 59, itemIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localFile
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 60, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalFile:(NSString*)newLocalFile
{
  void *val = (void*)[self nsstringToCString:newLocalFile];
  int ret_code = IPWorks_RSS_Set(m_pObj, 60, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 61, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_RSS_Set(m_pObj, 61, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)namespaceCount
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 62, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setNamespaceCount:(int)newNamespaceCount
{
  void *val = (void*)(long)newNamespaceCount;
  int ret_code = IPWorks_RSS_Set(m_pObj, 62, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)namespacePrefix:(int)namespaceIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 63, namespaceIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setNamespacePrefix:(int)namespaceIndex:(NSString*)newNamespacePrefix
{
  void *val = (void*)[self nsstringToCString:newNamespacePrefix];
  int ret_code = IPWorks_RSS_Set(m_pObj, 63, namespaceIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)namespaceURI:(int)namespaceIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 64, namespaceIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setNamespaceURI:(int)namespaceIndex:(NSString*)newNamespaceURI
{
  void *val = (void*)[self nsstringToCString:newNamespaceURI];
  int ret_code = IPWorks_RSS_Set(m_pObj, 64, namespaceIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)otherHeaders
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 65, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOtherHeaders:(NSString*)newOtherHeaders
{
  void *val = (void*)[self nsstringToCString:newOtherHeaders];
  int ret_code = IPWorks_RSS_Set(m_pObj, 65, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)parsedHeaderCount
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 66, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)parsedHeaderField:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 67, parsedHeaderIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)parsedHeaderValue:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 68, parsedHeaderIndex, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)password
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 69, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPassword:(NSString*)newPassword
{
  void *val = (void*)[self nsstringToCString:newPassword];
  int ret_code = IPWorks_RSS_Set(m_pObj, 69, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyAuthScheme
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 70, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyAuthScheme:(int)newProxyAuthScheme
{
  void *val = (void*)(long)newProxyAuthScheme;
  int ret_code = IPWorks_RSS_Set(m_pObj, 70, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)proxyAutoDetect
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 71, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setProxyAutoDetect:(BOOL)newProxyAutoDetect
{
  void *val = (void*)(long)(newProxyAutoDetect ? 1 : 0);
  int ret_code = IPWorks_RSS_Set(m_pObj, 71, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyPassword
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 72, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyPassword:(NSString*)newProxyPassword
{
  void *val = (void*)[self nsstringToCString:newProxyPassword];
  int ret_code = IPWorks_RSS_Set(m_pObj, 72, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyPort
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 73, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyPort:(int)newProxyPort
{
  void *val = (void*)(long)newProxyPort;
  int ret_code = IPWorks_RSS_Set(m_pObj, 73, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyServer
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 74, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyServer:(NSString*)newProxyServer
{
  void *val = (void*)[self nsstringToCString:newProxyServer];
  int ret_code = IPWorks_RSS_Set(m_pObj, 74, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxySSL
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 75, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxySSL:(int)newProxySSL
{
  void *val = (void*)(long)newProxySSL;
  int ret_code = IPWorks_RSS_Set(m_pObj, 75, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyUser
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 76, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyUser:(NSString*)newProxyUser
{
  void *val = (void*)[self nsstringToCString:newProxyUser];
  int ret_code = IPWorks_RSS_Set(m_pObj, 76, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)referer
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 77, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReferer:(NSString*)newReferer
{
  void *val = (void*)[self nsstringToCString:newReferer];
  int ret_code = IPWorks_RSS_Set(m_pObj, 77, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)RSSData
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 78, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRSSData:(NSString*)newRSSData
{
  void *val = (void*)[self nsstringToCString:newRSSData];
  int ret_code = IPWorks_RSS_Set(m_pObj, 78, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)RSSVersion
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 79, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setRSSVersion:(int)newRSSVersion
{
  void *val = (void*)(long)newRSSVersion;
  int ret_code = IPWorks_RSS_Set(m_pObj, 79, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLAcceptServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 80, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLAcceptServerCertEncoded];
  int ret_code = IPWorks_RSS_Set(m_pObj, 80, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLAcceptServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_RSS_Get(m_pObj, 80, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded length];
  void *val = (void*)[newSSLAcceptServerCertEncoded bytes];
  int ret_code = IPWorks_RSS_Set(m_pObj, 80, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 81, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_RSS_Set(m_pObj, 81, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_RSS_Get(m_pObj, 81, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_RSS_Set(m_pObj, 81, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 82, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_RSS_Set(m_pObj, 82, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_RSS_Get(m_pObj, 82, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_RSS_Set(m_pObj, 82, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 83, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_RSS_Set(m_pObj, 83, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 84, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_RSS_Set(m_pObj, 84, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 85, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_RSS_Set(m_pObj, 85, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 86, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)SSLServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_RSS_Get(m_pObj, 86, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 87, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_RSS_Set(m_pObj, 87, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)transferredData
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 88, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)transferredDataB
{
  int len = 0;
  void* val = IPWorks_RSS_Get(m_pObj, 88, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (long long)transferredDataLimit
{
  int len = 0;
  long long llVal;
  IPWorks_RSS_Get(m_pObj, 89, 0, &len, &llVal);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (void)setTransferredDataLimit:(long long)newTransferredDataLimit
{
  void *val = (void*)&newTransferredDataLimit;
  int ret_code = IPWorks_RSS_Set(m_pObj, 89, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)transferredHeaders
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 90, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)user
{
  int len = 0;
  void* val=IPWorks_RSS_Get(m_pObj, 91, 0, &len, nil);
  if (IPWorks_RSS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUser:(NSString*)newUser
{
  void *val = (void*)[self nsstringToCString:newUser];
  int ret_code = IPWorks_RSS_Set(m_pObj, 91, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (void)addCookie:(NSString*)cookieName :(NSString*)cookieValue
{
  void *param[2+1] = {(void*)[self nsstringToCString:cookieName], (void*)[self nsstringToCString:cookieValue], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 2, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)addItem:(NSString*)title :(NSString*)description :(NSString*)link
{
  void *param[3+1] = {(void*)[self nsstringToCString:title], (void*)[self nsstringToCString:description], (void*)[self nsstringToCString:link], NULL};
  int cbparam[3+1] = {0, 0, 0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 3, 3, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)addNamespace:(NSString*)prefix :(NSString*)namespaceURI
{
  void *param[2+1] = {(void*)[self nsstringToCString:prefix], (void*)[self nsstringToCString:namespaceURI], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 4, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 5, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 6, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)getFeed:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 7, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)getProperty:(NSString*)propertyName
{
  void *param[1+1] = {(void*)[self nsstringToCString:propertyName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 8, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)getURL:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 9, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 10, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)OPMLAttr:(NSString*)attrName
{
  void *param[1+1] = {(void*)[self nsstringToCString:attrName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 11, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)put:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 12, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)readFile:(NSString*)fileName
{
  void *param[1+1] = {(void*)[self nsstringToCString:fileName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 13, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)readOPML:(NSString*)OPMLFile
{
  void *param[1+1] = {(void*)[self nsstringToCString:OPMLFile], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 14, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 15, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setProperty:(NSString*)propertyName :(NSString*)propertyValue
{
  void *param[2+1] = {(void*)[self nsstringToCString:propertyName], (void*)[self nsstringToCString:propertyValue], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 16, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)writeFile:(NSString*)filename
{
  void *param[1+1] = {(void*)[self nsstringToCString:filename], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_RSS_Do(m_pObj, 17, 1, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_RSS_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_RSS_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end