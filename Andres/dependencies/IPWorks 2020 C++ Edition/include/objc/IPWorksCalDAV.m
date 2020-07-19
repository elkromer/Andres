
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksCalDAV.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksCalDAV()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define CalDAV_EXTERN extern "C"
#else
#define CalDAV_EXTERN extern
#endif

CalDAV_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
CalDAV_EXTERN void* IPWorks_CalDAV_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
CalDAV_EXTERN int   IPWorks_CalDAV_Destroy(void* lpObj);
CalDAV_EXTERN int   IPWorks_CalDAV_CheckIndex(void* lpObj, int propid, int arridx);
CalDAV_EXTERN void* IPWorks_CalDAV_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
CalDAV_EXTERN int   IPWorks_CalDAV_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
CalDAV_EXTERN int   IPWorks_CalDAV_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
CalDAV_EXTERN char* IPWorks_CalDAV_GetLastError(void* lpObj);
CalDAV_EXTERN int   IPWorks_CalDAV_GetLastErrorCode(void* lpObj);
CalDAV_EXTERN int   IPWorks_CalDAV_SetLastErrorAndCode(void* lpObj, int code, char* message);
CalDAV_EXTERN char* IPWorks_CalDAV_GetEventError(void* lpObj);
CalDAV_EXTERN int   IPWorks_CalDAV_GetEventErrorCode(void* lpObj);
CalDAV_EXTERN int   IPWorks_CalDAV_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void CalDAV_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_CalDAV_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int CalDAV_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksCalDAV* ctl = (IPWorksCalDAV*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, CalDAV_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (CalDAV)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
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
    case 6 /*EID_EVENTDETAILS*/: {
      NSString* resourceURIT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* resourceURI = resourceURIT;
      NSString* responseStatusT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* responseStatus = responseStatusT;
      NSString* ETagT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* ETag = ETagT;
      NSString* calendarDataT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* calendarData = calendarDataT;
      @try {
        [ctl onEventDetails :resourceURI :responseStatus :ETag :calendarData];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EventDetails" :YES];
      }
      break;
    }
    case 7 /*EID_FREEBUSY*/: {
      NSString* busyTypeT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* busyType = busyTypeT;
      NSString* busyRangeT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* busyRange = busyRangeT;
      @try {
        [ctl onFreeBusy :busyType :busyRange];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"FreeBusy" :YES];
      }
      break;
    }
    case 8 /*EID_HEADER*/: {
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
    case 9 /*EID_LOG*/: {
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

@implementation IPWorksCalDAV

+ (IPWorksCalDAV*)caldav
{
#if __has_feature(objc_arc)
  return [[IPWorksCalDAV alloc] init];
#else
  return [[[IPWorksCalDAV alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_CalDAV_Create((void*)CalDAV_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_CalDAV_Create((void*)CalDAV_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_CalDAV_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_CalDAV_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_CalDAV_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_CalDAV_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_CalDAV_GetEventErrorCode(m_pObj);
}

- (id <IPWorksCalDAVDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksCalDAVDelegate>)anObject
{
  m_delegateHasConnected = NO;
  m_delegateHasConnectionStatus = NO;
  m_delegateHasDisconnected = NO;
  m_delegateHasEndTransfer = NO;
  m_delegateHasError = NO;
  m_delegateHasEventDetails = NO;
  m_delegateHasFreeBusy = NO;
  m_delegateHasHeader = NO;
  m_delegateHasLog = NO;
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
    if ([m_delegate respondsToSelector:@selector(onEventDetails::::)]) m_delegateHasEventDetails = YES;
    if ([m_delegate respondsToSelector:@selector(onFreeBusy::)]) m_delegateHasFreeBusy = YES;
    if ([m_delegate respondsToSelector:@selector(onHeader::)]) m_delegateHasHeader = YES;
    if ([m_delegate respondsToSelector:@selector(onLog:::)]) m_delegateHasLog = YES;
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
- (void)onEventDetails:(NSString*)resourceURI :(NSString*)responseStatus :(NSString*)ETag :(NSString*)calendarData
{
  if (m_delegate != nil && m_delegateHasEventDetails)
    [m_delegate onEventDetails:resourceURI :responseStatus :ETag :calendarData];
}
- (void)onFreeBusy:(NSString*)busyType :(NSString*)busyRange
{
  if (m_delegate != nil && m_delegateHasFreeBusy)
    [m_delegate onFreeBusy:busyType :busyRange];
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
  void* val = IPWorks_CalDAV_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_CalDAV_Get(m_pObj, 0, 0, 0, nil);
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

- (int)alarmCount
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAlarmCount:(int)newAlarmCount
{
  void *val = (void*)(long)newAlarmCount;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)alarmAction:(int)alarmIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 2, alarmIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAlarmAction:(int)alarmIndex:(int)newAlarmAction
{
  void *val = (void*)(long)newAlarmAction;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 2, alarmIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)alarmAttachment:(int)alarmIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 3, alarmIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAlarmAttachment:(int)alarmIndex:(NSString*)newAlarmAttachment
{
  void *val = (void*)[self nsstringToCString:newAlarmAttachment];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 3, alarmIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)alarmAttachmentType:(int)alarmIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 4, alarmIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAlarmAttachmentType:(int)alarmIndex:(NSString*)newAlarmAttachmentType
{
  void *val = (void*)[self nsstringToCString:newAlarmAttachmentType];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 4, alarmIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)alarmDuration:(int)alarmIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 5, alarmIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAlarmDuration:(int)alarmIndex:(NSString*)newAlarmDuration
{
  void *val = (void*)[self nsstringToCString:newAlarmDuration];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 5, alarmIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)alarmMessage:(int)alarmIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 6, alarmIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAlarmMessage:(int)alarmIndex:(NSString*)newAlarmMessage
{
  void *val = (void*)[self nsstringToCString:newAlarmMessage];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 6, alarmIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)alarmRecipient:(int)alarmIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 7, alarmIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAlarmRecipient:(int)alarmIndex:(NSString*)newAlarmRecipient
{
  void *val = (void*)[self nsstringToCString:newAlarmRecipient];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 7, alarmIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)alarmRepeat:(int)alarmIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 8, alarmIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAlarmRepeat:(int)alarmIndex:(int)newAlarmRepeat
{
  void *val = (void*)(long)newAlarmRepeat;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 8, alarmIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)alarmSubject:(int)alarmIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 9, alarmIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAlarmSubject:(int)alarmIndex:(NSString*)newAlarmSubject
{
  void *val = (void*)[self nsstringToCString:newAlarmSubject];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 9, alarmIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)alarmTrigger:(int)alarmIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 10, alarmIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAlarmTrigger:(int)alarmIndex:(NSString*)newAlarmTrigger
{
  void *val = (void*)[self nsstringToCString:newAlarmTrigger];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 10, alarmIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)attendees
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAttendees:(NSString*)newAttendees
{
  void *val = (void*)[self nsstringToCString:newAttendees];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 11, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)authorization
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAuthorization:(NSString*)newAuthorization
{
  void *val = (void*)[self nsstringToCString:newAuthorization];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 12, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)authScheme
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAuthScheme:(int)newAuthScheme
{
  void *val = (void*)(long)newAuthScheme;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 13, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)categories
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCategories:(NSString*)newCategories
{
  void *val = (void*)[self nsstringToCString:newCategories];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 14, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)classification
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setClassification:(NSString*)newClassification
{
  void *val = (void*)[self nsstringToCString:newClassification];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)completed
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCompleted:(NSString*)newCompleted
{
  void *val = (void*)[self nsstringToCString:newCompleted];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)connected
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setConnected:(BOOL)newConnected
{
  void *val = (void*)(long)(newConnected ? 1 : 0);
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)cookieCount
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setCookieCount:(int)newCookieCount
{
  void *val = (void*)(long)newCookieCount;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 18, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookieDomain:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 19, cookieIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieExpiration:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 20, cookieIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieName:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 21, cookieIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieName:(int)cookieIndex:(NSString*)newCookieName
{
  void *val = (void*)[self nsstringToCString:newCookieName];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 21, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookiePath:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 22, cookieIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)cookieSecure:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 23, cookieIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)cookieValue:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 24, cookieIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieValue:(int)cookieIndex:(NSString*)newCookieValue
{
  void *val = (void*)[self nsstringToCString:newCookieValue];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 24, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)created
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCreated:(NSString*)newCreated
{
  void *val = (void*)[self nsstringToCString:newCreated];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 25, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)customPropertyCount
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setCustomPropertyCount:(int)newCustomPropertyCount
{
  void *val = (void*)(long)newCustomPropertyCount;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 26, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)customPropertyAttribute:(int)customPropertyIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 27, customPropertyIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCustomPropertyAttribute:(int)customPropertyIndex:(NSString*)newCustomPropertyAttribute
{
  void *val = (void*)[self nsstringToCString:newCustomPropertyAttribute];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 27, customPropertyIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)customPropertyName:(int)customPropertyIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 28, customPropertyIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCustomPropertyName:(int)customPropertyIndex:(NSString*)newCustomPropertyName
{
  void *val = (void*)[self nsstringToCString:newCustomPropertyName];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 28, customPropertyIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)customPropertyValue:(int)customPropertyIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 29, customPropertyIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCustomPropertyValue:(int)customPropertyIndex:(NSString*)newCustomPropertyValue
{
  void *val = (void*)[self nsstringToCString:newCustomPropertyValue];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 29, customPropertyIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)depth
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setDepth:(int)newDepth
{
  void *val = (void*)(long)newDepth;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 30, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)description
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)description_
{
  return [self description];
}

- (void)setDescription:(NSString*)newDescription
{
  void *val = (void*)[self nsstringToCString:newDescription];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 31, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setDescription_:(NSString*)newDescription
{
  return [self setDescription:newDescription];
}

- (NSString*)displayName
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setDisplayName:(NSString*)newDisplayName
{
  void *val = (void*)[self nsstringToCString:newDisplayName];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 32, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)dueDate
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 33, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setDueDate:(NSString*)newDueDate
{
  void *val = (void*)[self nsstringToCString:newDueDate];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 33, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)duration
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 34, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setDuration:(NSString*)newDuration
{
  void *val = (void*)[self nsstringToCString:newDuration];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 34, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)endDate
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 35, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEndDate:(NSString*)newEndDate
{
  void *val = (void*)[self nsstringToCString:newEndDate];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 35, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)ETag
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 36, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setETag:(NSString*)newETag
{
  void *val = (void*)[self nsstringToCString:newETag];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 36, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)eventType
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 37, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setEventType:(int)newEventType
{
  void *val = (void*)(long)newEventType;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 37, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)firewallAutoDetect
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 38, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect
{
  void *val = (void*)(long)(newFirewallAutoDetect ? 1 : 0);
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 38, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallType
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 39, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallType:(int)newFirewallType
{
  void *val = (void*)(long)newFirewallType;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 39, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallHost
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 40, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallHost:(NSString*)newFirewallHost
{
  void *val = (void*)[self nsstringToCString:newFirewallHost];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 40, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallPassword
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 41, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallPassword:(NSString*)newFirewallPassword
{
  void *val = (void*)[self nsstringToCString:newFirewallPassword];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 41, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallPort
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 42, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallPort:(int)newFirewallPort
{
  void *val = (void*)(long)newFirewallPort;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 42, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallUser
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 43, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallUser:(NSString*)newFirewallUser
{
  void *val = (void*)[self nsstringToCString:newFirewallUser];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 43, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)followRedirects
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 44, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFollowRedirects:(int)newFollowRedirects
{
  void *val = (void*)(long)newFollowRedirects;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 44, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)freeBusyCount
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 45, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)freeBusyRange:(int)freeBusyIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 46, freeBusyIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)freeBusyType:(int)freeBusyIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 47, freeBusyIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 48, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)lastModified
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 49, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLastModified:(NSString*)newLastModified
{
  void *val = (void*)[self nsstringToCString:newLastModified];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 49, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 50, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 50, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)location
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 51, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocation:(NSString*)newLocation
{
  void *val = (void*)[self nsstringToCString:newLocation];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 51, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)lockType
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 52, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLockType:(NSString*)newLockType
{
  void *val = (void*)[self nsstringToCString:newLockType];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 52, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)lockOwner
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 53, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLockOwner:(NSString*)newLockOwner
{
  void *val = (void*)[self nsstringToCString:newLockOwner];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 53, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)lockScope
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 54, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLockScope:(NSString*)newLockScope
{
  void *val = (void*)[self nsstringToCString:newLockScope];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 54, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)lockTimeout
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 55, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setLockTimeout:(int)newLockTimeout
{
  void *val = (void*)(long)newLockTimeout;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 55, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)lockTokens
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 56, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLockTokens:(NSString*)newLockTokens
{
  void *val = (void*)[self nsstringToCString:newLockTokens];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 56, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)organizer
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 57, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOrganizer:(NSString*)newOrganizer
{
  void *val = (void*)[self nsstringToCString:newOrganizer];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 57, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)otherHeaders
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 58, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOtherHeaders:(NSString*)newOtherHeaders
{
  void *val = (void*)[self nsstringToCString:newOtherHeaders];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 58, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)parsedHeaderCount
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 59, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)parsedHeaderField:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 60, parsedHeaderIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)parsedHeaderValue:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 61, parsedHeaderIndex, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)password
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 62, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPassword:(NSString*)newPassword
{
  void *val = (void*)[self nsstringToCString:newPassword];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 62, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)priority
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 63, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setPriority:(int)newPriority
{
  void *val = (void*)(long)newPriority;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 63, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyAuthScheme
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 64, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyAuthScheme:(int)newProxyAuthScheme
{
  void *val = (void*)(long)newProxyAuthScheme;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 64, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)proxyAutoDetect
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 65, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setProxyAutoDetect:(BOOL)newProxyAutoDetect
{
  void *val = (void*)(long)(newProxyAutoDetect ? 1 : 0);
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 65, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyPassword
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 66, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyPassword:(NSString*)newProxyPassword
{
  void *val = (void*)[self nsstringToCString:newProxyPassword];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 66, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyPort
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 67, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyPort:(int)newProxyPort
{
  void *val = (void*)(long)newProxyPort;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 67, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyServer
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 68, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyServer:(NSString*)newProxyServer
{
  void *val = (void*)[self nsstringToCString:newProxyServer];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 68, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxySSL
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 69, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxySSL:(int)newProxySSL
{
  void *val = (void*)(long)newProxySSL;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 69, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyUser
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 70, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyUser:(NSString*)newProxyUser
{
  void *val = (void*)[self nsstringToCString:newProxyUser];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 70, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)recurrenceDates
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 71, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRecurrenceDates:(NSString*)newRecurrenceDates
{
  void *val = (void*)[self nsstringToCString:newRecurrenceDates];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 71, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)recurrenceExceptionDates
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 72, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRecurrenceExceptionDates:(NSString*)newRecurrenceExceptionDates
{
  void *val = (void*)[self nsstringToCString:newRecurrenceExceptionDates];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 72, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)recurrenceExceptionRule
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 73, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRecurrenceExceptionRule:(NSString*)newRecurrenceExceptionRule
{
  void *val = (void*)[self nsstringToCString:newRecurrenceExceptionRule];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 73, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)recurrenceId
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 74, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRecurrenceId:(NSString*)newRecurrenceId
{
  void *val = (void*)[self nsstringToCString:newRecurrenceId];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 74, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)recurrenceRule
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 75, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRecurrenceRule:(NSString*)newRecurrenceRule
{
  void *val = (void*)[self nsstringToCString:newRecurrenceRule];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 75, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)reportFilterAlarmEnd
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 76, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReportFilterAlarmEnd:(NSString*)newReportFilterAlarmEnd
{
  void *val = (void*)[self nsstringToCString:newReportFilterAlarmEnd];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 76, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)reportFilterAlarmStart
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 77, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReportFilterAlarmStart:(NSString*)newReportFilterAlarmStart
{
  void *val = (void*)[self nsstringToCString:newReportFilterAlarmStart];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 77, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)reportFilterCustomFilter
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 78, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReportFilterCustomFilter:(NSString*)newReportFilterCustomFilter
{
  void *val = (void*)[self nsstringToCString:newReportFilterCustomFilter];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 78, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)reportFilterEndDate
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 79, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReportFilterEndDate:(NSString*)newReportFilterEndDate
{
  void *val = (void*)[self nsstringToCString:newReportFilterEndDate];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 79, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)reportFilterEventType
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 80, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setReportFilterEventType:(int)newReportFilterEventType
{
  void *val = (void*)(long)newReportFilterEventType;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 80, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)reportFilterProperty
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 81, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReportFilterProperty:(NSString*)newReportFilterProperty
{
  void *val = (void*)[self nsstringToCString:newReportFilterProperty];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 81, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)reportFilterRecurEnd
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 82, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReportFilterRecurEnd:(NSString*)newReportFilterRecurEnd
{
  void *val = (void*)[self nsstringToCString:newReportFilterRecurEnd];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 82, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)reportFilterRecurStart
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 83, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReportFilterRecurStart:(NSString*)newReportFilterRecurStart
{
  void *val = (void*)[self nsstringToCString:newReportFilterRecurStart];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 83, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)reportFilterReturnCalendarData
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 84, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setReportFilterReturnCalendarData:(BOOL)newReportFilterReturnCalendarData
{
  void *val = (void*)(long)(newReportFilterReturnCalendarData ? 1 : 0);
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 84, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)reportFilterStartDate
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 85, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReportFilterStartDate:(NSString*)newReportFilterStartDate
{
  void *val = (void*)[self nsstringToCString:newReportFilterStartDate];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 85, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)reportFilterUID
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 86, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReportFilterUID:(NSString*)newReportFilterUID
{
  void *val = (void*)[self nsstringToCString:newReportFilterUID];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 86, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)sequence
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 87, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSequence:(int)newSequence
{
  void *val = (void*)(long)newSequence;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 87, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLAcceptServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 88, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLAcceptServerCertEncoded];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 88, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLAcceptServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_CalDAV_Get(m_pObj, 88, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded length];
  void *val = (void*)[newSSLAcceptServerCertEncoded bytes];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 88, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 89, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 89, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_CalDAV_Get(m_pObj, 89, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 89, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 90, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 90, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_CalDAV_Get(m_pObj, 90, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 90, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 91, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 91, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 92, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 92, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 93, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 93, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 94, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)SSLServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_CalDAV_Get(m_pObj, 94, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (NSString*)startDate
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 95, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setStartDate:(NSString*)newStartDate
{
  void *val = (void*)[self nsstringToCString:newStartDate];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 95, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)status
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 96, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setStatus:(NSString*)newStatus
{
  void *val = (void*)[self nsstringToCString:newStatus];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 96, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)statusLine
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 97, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)summary
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 98, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSummary:(NSString*)newSummary
{
  void *val = (void*)[self nsstringToCString:newSummary];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 98, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 99, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 99, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timestamp
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 100, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimestamp:(NSString*)newTimestamp
{
  void *val = (void*)[self nsstringToCString:newTimestamp];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 100, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneDSTName
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 101, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneDSTName:(NSString*)newTimezoneDSTName
{
  void *val = (void*)[self nsstringToCString:newTimezoneDSTName];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 101, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneDSTOffsetFrom
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 102, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneDSTOffsetFrom:(NSString*)newTimezoneDSTOffsetFrom
{
  void *val = (void*)[self nsstringToCString:newTimezoneDSTOffsetFrom];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 102, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneDSTOffsetTo
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 103, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneDSTOffsetTo:(NSString*)newTimezoneDSTOffsetTo
{
  void *val = (void*)[self nsstringToCString:newTimezoneDSTOffsetTo];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 103, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneDSTRule
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 104, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneDSTRule:(NSString*)newTimezoneDSTRule
{
  void *val = (void*)[self nsstringToCString:newTimezoneDSTRule];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 104, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneDSTStart
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 105, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneDSTStart:(NSString*)newTimezoneDSTStart
{
  void *val = (void*)[self nsstringToCString:newTimezoneDSTStart];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 105, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneLastModified
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 106, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneLastModified:(NSString*)newTimezoneLastModified
{
  void *val = (void*)[self nsstringToCString:newTimezoneLastModified];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 106, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneStdName
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 107, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneStdName:(NSString*)newTimezoneStdName
{
  void *val = (void*)[self nsstringToCString:newTimezoneStdName];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 107, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneStdOffsetFrom
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 108, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneStdOffsetFrom:(NSString*)newTimezoneStdOffsetFrom
{
  void *val = (void*)[self nsstringToCString:newTimezoneStdOffsetFrom];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 108, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneStdOffsetTo
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 109, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneStdOffsetTo:(NSString*)newTimezoneStdOffsetTo
{
  void *val = (void*)[self nsstringToCString:newTimezoneStdOffsetTo];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 109, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneStdRule
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 110, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneStdRule:(NSString*)newTimezoneStdRule
{
  void *val = (void*)[self nsstringToCString:newTimezoneStdRule];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 110, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneStdStart
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 111, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneStdStart:(NSString*)newTimezoneStdStart
{
  void *val = (void*)[self nsstringToCString:newTimezoneStdStart];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 111, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneId
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 112, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneId:(NSString*)newTimezoneId
{
  void *val = (void*)[self nsstringToCString:newTimezoneId];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 112, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)timezoneURL
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 113, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTimezoneURL:(NSString*)newTimezoneURL
{
  void *val = (void*)[self nsstringToCString:newTimezoneURL];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 113, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)transparency
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 114, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setTransparency:(NSString*)newTransparency
{
  void *val = (void*)[self nsstringToCString:newTransparency];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 114, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)UID
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 115, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUID:(NSString*)newUID
{
  void *val = (void*)[self nsstringToCString:newUID];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 115, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)URL
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 116, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)user
{
  int len = 0;
  void* val=IPWorks_CalDAV_Get(m_pObj, 117, 0, &len, nil);
  if (IPWorks_CalDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUser:(NSString*)newUser
{
  void *val = (void*)[self nsstringToCString:newUser];
  int ret_code = IPWorks_CalDAV_Set(m_pObj, 117, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (void)addCookie:(NSString*)cookieName :(NSString*)cookieValue
{
  void *param[2+1] = {(void*)[self nsstringToCString:cookieName], (void*)[self nsstringToCString:cookieValue], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 2, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)addCustomProperty:(NSString*)varName :(NSString*)varValue
{
  void *param[2+1] = {(void*)[self nsstringToCString:varName], (void*)[self nsstringToCString:varValue], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 3, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 4, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)copyCalendarEvent:(NSString*)sourceResourceURI :(NSString*)destinationResourceURI
{
  void *param[2+1] = {(void*)[self nsstringToCString:sourceResourceURI], (void*)[self nsstringToCString:destinationResourceURI], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 5, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)createCalendar:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 6, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)deleteCalendarEvent:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 7, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 8, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)exportICS
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 9, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[0] encoding:[self innerGetCodePage]];
}

- (void)getCalendarEvent:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 10, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)getCalendarOptions:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 11, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)getCalendarReport:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 12, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)getFreeBusyReport:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 13, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)importICS:(NSString*)calendarData
{
  void *param[1+1] = {(void*)[self nsstringToCString:calendarData], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 14, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 15, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)lockCalendar:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 16, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)moveCalendarEvent:(NSString*)sourceResourceURI :(NSString*)destinationResourceURI
{
  void *param[2+1] = {(void*)[self nsstringToCString:sourceResourceURI], (void*)[self nsstringToCString:destinationResourceURI], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 17, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putCalendarEvent:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 18, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 19, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)unLockCalendar:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CalDAV_Do(m_pObj, 20, 1, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_CalDAV_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_CalDAV_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end