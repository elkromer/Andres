
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksICMPPort.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksICMPPort()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define ICMPPort_EXTERN extern "C"
#else
#define ICMPPort_EXTERN extern
#endif

ICMPPort_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
ICMPPort_EXTERN void* IPWorks_ICMPPort_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
ICMPPort_EXTERN int   IPWorks_ICMPPort_Destroy(void* lpObj);
ICMPPort_EXTERN int   IPWorks_ICMPPort_CheckIndex(void* lpObj, int propid, int arridx);
ICMPPort_EXTERN void* IPWorks_ICMPPort_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
ICMPPort_EXTERN int   IPWorks_ICMPPort_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
ICMPPort_EXTERN int   IPWorks_ICMPPort_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
ICMPPort_EXTERN char* IPWorks_ICMPPort_GetLastError(void* lpObj);
ICMPPort_EXTERN int   IPWorks_ICMPPort_GetLastErrorCode(void* lpObj);
ICMPPort_EXTERN int   IPWorks_ICMPPort_SetLastErrorAndCode(void* lpObj, int code, char* message);
ICMPPort_EXTERN char* IPWorks_ICMPPort_GetEventError(void* lpObj);
ICMPPort_EXTERN int   IPWorks_ICMPPort_GetEventErrorCode(void* lpObj);
ICMPPort_EXTERN int   IPWorks_ICMPPort_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void ICMPPort_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_ICMPPort_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int ICMPPort_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksICMPPort* ctl = (IPWorksICMPPort*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, ICMPPort_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (ICMPPort)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
      [myAlert show];
      return 1;
#else // TARGET_OS_IPHONE
      return 0;
#endif // TARGET_OS_IPHONE
    }

    case 1 /*EID_DATAIN*/: {
      int messageType = (int)(long)param[0];
      int messageSubType = (int)(long)param[1];
      NSData* messageData = [NSData dataWithBytesNoCopy:param[2] length:cbparam[2] freeWhenDone:NO];
      int checksum = (int)(long)param[3];
      NSString* sourceAddressT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* sourceAddress = sourceAddressT;
      @try {
        [ctl onDataIn :messageType :messageSubType :messageData :checksum :sourceAddress];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"DataIn" :YES];
      }
      break;
    }
    case 2 /*EID_ERROR*/: {
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
    case 3 /*EID_READYTOSEND*/: {
      @try {
        [ctl onReadyToSend ];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"ReadyToSend" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksICMPPort

+ (IPWorksICMPPort*)icmpport
{
#if __has_feature(objc_arc)
  return [[IPWorksICMPPort alloc] init];
#else
  return [[[IPWorksICMPPort alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_ICMPPort_Create((void*)ICMPPort_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_ICMPPort_Create((void*)ICMPPort_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_ICMPPort_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_ICMPPort_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_ICMPPort_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_ICMPPort_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_ICMPPort_GetEventErrorCode(m_pObj);
}

- (id <IPWorksICMPPortDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksICMPPortDelegate>)anObject
{
  m_delegateHasDataIn = NO;
  m_delegateHasError = NO;
  m_delegateHasReadyToSend = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onDataIn:::::)]) m_delegateHasDataIn = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onReadyToSend)]) m_delegateHasReadyToSend = YES;
  }
}

  /* Events */

- (void)onDataIn:(int)messageType :(int)messageSubType :(NSData*)messageData :(int)checksum :(NSString*)sourceAddress
{
  if (m_delegate != nil && m_delegateHasDataIn)
    [m_delegate onDataIn:messageType :messageSubType :messageData :checksum :sourceAddress];
}
- (void)onError:(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:errorCode :description];
}
- (void)onReadyToSend
{
  if (m_delegate != nil && m_delegateHasReadyToSend)
    [m_delegate onReadyToSend];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_ICMPPort_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_ICMPPort_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_ICMPPort_Get(m_pObj, 0, 0, 0, nil);
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
  void* val=IPWorks_ICMPPort_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_ICMPPort_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setAcceptData:(BOOL)newAcceptData
{
  void *val = (void*)(long)(newAcceptData ? 1 : 0);
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)active
{
  int len = 0;
  void* val=IPWorks_ICMPPort_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_ICMPPort_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setActive:(BOOL)newActive
{
  void *val = (void*)(long)(newActive ? 1 : 0);
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

// Placeholder for writeonly properties.
- (NSString*)dataToSend
{
  return nil;
}

- (void)setDataToSend:(NSString*)newDataToSend
{
  int len = (int)[newDataToSend lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newDataToSend];
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 3, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

// Placeholder for writeonly properties.
- (NSData*)dataToSendB
{
  return nil;
}

- (void)setDataToSendB :(NSData*)newDataToSend
{
  int len = (int)[newDataToSend length];
  void *val = (void*)[newDataToSend bytes];
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 3, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)dontRoute
{
  int len = 0;
  void* val=IPWorks_ICMPPort_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_ICMPPort_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setDontRoute:(BOOL)newDontRoute
{
  void *val = (void*)(long)(newDontRoute ? 1 : 0);
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_ICMPPort_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_ICMPPort_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 5, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)messageSubType
{
  int len = 0;
  void* val=IPWorks_ICMPPort_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_ICMPPort_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setMessageSubType:(int)newMessageSubType
{
  void *val = (void*)(long)newMessageSubType;
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 6, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)messageType
{
  int len = 0;
  void* val=IPWorks_ICMPPort_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_ICMPPort_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setMessageType:(int)newMessageType
{
  void *val = (void*)(long)newMessageType;
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 7, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)remoteHost
{
  int len = 0;
  void* val=IPWorks_ICMPPort_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_ICMPPort_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRemoteHost:(NSString*)newRemoteHost
{
  void *val = (void*)[self nsstringToCString:newRemoteHost];
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 8, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_ICMPPort_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_ICMPPort_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 9, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)timeToLive
{
  int len = 0;
  void* val=IPWorks_ICMPPort_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_ICMPPort_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeToLive:(int)newTimeToLive
{
  void *val = (void*)(long)newTimeToLive;
  int ret_code = IPWorks_ICMPPort_Set(m_pObj, 10, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_ICMPPort_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_ICMPPort_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_ICMPPort_Do(m_pObj, 4, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)send:(NSData*)text
{
  void *param[1+1] = {(void*)[text bytes], NULL};
  int cbparam[1+1] = {(int)[text length], 0};

  int ret_code = IPWorks_ICMPPort_Do(m_pObj, 5, 1, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_ICMPPort_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_ICMPPort_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end