
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksTraceRoute.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksTraceRoute()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define TraceRoute_EXTERN extern "C"
#else
#define TraceRoute_EXTERN extern
#endif

TraceRoute_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
TraceRoute_EXTERN void* IPWorks_TraceRoute_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
TraceRoute_EXTERN int   IPWorks_TraceRoute_Destroy(void* lpObj);
TraceRoute_EXTERN int   IPWorks_TraceRoute_CheckIndex(void* lpObj, int propid, int arridx);
TraceRoute_EXTERN void* IPWorks_TraceRoute_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
TraceRoute_EXTERN int   IPWorks_TraceRoute_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
TraceRoute_EXTERN int   IPWorks_TraceRoute_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
TraceRoute_EXTERN char* IPWorks_TraceRoute_GetLastError(void* lpObj);
TraceRoute_EXTERN int   IPWorks_TraceRoute_GetLastErrorCode(void* lpObj);
TraceRoute_EXTERN int   IPWorks_TraceRoute_SetLastErrorAndCode(void* lpObj, int code, char* message);
TraceRoute_EXTERN char* IPWorks_TraceRoute_GetEventError(void* lpObj);
TraceRoute_EXTERN int   IPWorks_TraceRoute_GetEventErrorCode(void* lpObj);
TraceRoute_EXTERN int   IPWorks_TraceRoute_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void TraceRoute_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_TraceRoute_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int TraceRoute_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksTraceRoute* ctl = (IPWorksTraceRoute*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, TraceRoute_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (TraceRoute)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
      [myAlert show];
      return 1;
#else // TARGET_OS_IPHONE
      return 0;
#endif // TARGET_OS_IPHONE
    }

    case 1 /*EID_ERROR*/: {
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
    case 2 /*EID_HOP*/: {
      int hopNumber = (int)(long)param[0];
      NSString* hostAddressT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* hostAddress = hostAddressT;
      int duration = (int)(long)param[2];
      @try {
        [ctl onHop :hopNumber :hostAddress :duration];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Hop" :YES];
      }
      break;
    }
    case 3 /*EID_HOPRESOLVED*/: {
      int hopNumber = (int)(long)param[0];
      int statusCode = (int)(long)param[1];
      NSString* hopHostNameT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* hopHostName = hopHostNameT;
      @try {
        [ctl onHopResolved :hopNumber :statusCode :hopHostName];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"HopResolved" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksTraceRoute

+ (IPWorksTraceRoute*)traceroute
{
#if __has_feature(objc_arc)
  return [[IPWorksTraceRoute alloc] init];
#else
  return [[[IPWorksTraceRoute alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_TraceRoute_Create((void*)TraceRoute_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_TraceRoute_Create((void*)TraceRoute_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_TraceRoute_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_TraceRoute_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_TraceRoute_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_TraceRoute_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_TraceRoute_GetEventErrorCode(m_pObj);
}

- (id <IPWorksTraceRouteDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksTraceRouteDelegate>)anObject
{
  m_delegateHasError = NO;
  m_delegateHasHop = NO;
  m_delegateHasHopResolved = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onHop:::)]) m_delegateHasHop = YES;
    if ([m_delegate respondsToSelector:@selector(onHopResolved:::)]) m_delegateHasHopResolved = YES;
  }
}

  /* Events */

- (void)onError:(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:errorCode :description];
}
- (void)onHop:(int)hopNumber :(NSString*)hostAddress :(int)duration
{
  if (m_delegate != nil && m_delegateHasHop)
    [m_delegate onHop:hopNumber :hostAddress :duration];
}
- (void)onHopResolved:(int)hopNumber :(int)statusCode :(NSString*)hopHostName
{
  if (m_delegate != nil && m_delegateHasHopResolved)
    [m_delegate onHopResolved:hopNumber :statusCode :hopHostName];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_TraceRoute_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_TraceRoute_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_TraceRoute_Get(m_pObj, 0, 0, 0, nil);
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

- (int)hopLimit
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setHopLimit:(int)newHopLimit
{
  void *val = (void*)(long)newHopLimit;
  int ret_code = IPWorks_TraceRoute_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)hopCount
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)hopErrorCode:(int)hopIndex
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 3, hopIndex, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)hopErrorDescription:(int)hopIndex
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 4, hopIndex, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)hopHostAddress:(int)hopIndex
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 5, hopIndex, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)hopHostName:(int)hopIndex
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 6, hopIndex, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)hopTime:(int)hopIndex
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 7, hopIndex, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)hopTimeout
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setHopTimeout:(int)newHopTimeout
{
  void *val = (void*)(long)newHopTimeout;
  int ret_code = IPWorks_TraceRoute_Set(m_pObj, 8, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_TraceRoute_Set(m_pObj, 10, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)remoteHost
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRemoteHost:(NSString*)newRemoteHost
{
  void *val = (void*)[self nsstringToCString:newRemoteHost];
  int ret_code = IPWorks_TraceRoute_Set(m_pObj, 11, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)resolveNames
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setResolveNames:(BOOL)newResolveNames
{
  void *val = (void*)(long)(newResolveNames ? 1 : 0);
  int ret_code = IPWorks_TraceRoute_Set(m_pObj, 12, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_TraceRoute_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_TraceRoute_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_TraceRoute_Set(m_pObj, 13, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_TraceRoute_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_TraceRoute_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_TraceRoute_Do(m_pObj, 4, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_TraceRoute_Do(m_pObj, 5, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)traceTo:(NSString*)host
{
  void *param[1+1] = {(void*)[self nsstringToCString:host], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_TraceRoute_Do(m_pObj, 6, 1, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_TraceRoute_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_TraceRoute_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end