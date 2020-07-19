
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksIPInfo.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksIPInfo()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define IPInfo_EXTERN extern "C"
#else
#define IPInfo_EXTERN extern
#endif

IPInfo_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
IPInfo_EXTERN void* IPWorks_IPInfo_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
IPInfo_EXTERN int   IPWorks_IPInfo_Destroy(void* lpObj);
IPInfo_EXTERN int   IPWorks_IPInfo_CheckIndex(void* lpObj, int propid, int arridx);
IPInfo_EXTERN void* IPWorks_IPInfo_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
IPInfo_EXTERN int   IPWorks_IPInfo_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
IPInfo_EXTERN int   IPWorks_IPInfo_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
IPInfo_EXTERN char* IPWorks_IPInfo_GetLastError(void* lpObj);
IPInfo_EXTERN int   IPWorks_IPInfo_GetLastErrorCode(void* lpObj);
IPInfo_EXTERN int   IPWorks_IPInfo_SetLastErrorAndCode(void* lpObj, int code, char* message);
IPInfo_EXTERN char* IPWorks_IPInfo_GetEventError(void* lpObj);
IPInfo_EXTERN int   IPWorks_IPInfo_GetEventErrorCode(void* lpObj);
IPInfo_EXTERN int   IPWorks_IPInfo_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void IPInfo_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_IPInfo_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int IPInfo_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksIPInfo* ctl = (IPWorksIPInfo*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, IPInfo_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (IPInfo)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
      [myAlert show];
      return 1;
#else // TARGET_OS_IPHONE
      return 0;
#endif // TARGET_OS_IPHONE
    }

    case 1 /*EID_DNSCACHEENTRY*/: {
      NSString* recordNameT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* recordName = recordNameT;
      int recordType = (int)(long)param[1];
      int timeToLive = (int)(long)param[2];
      int dataLength = (int)(long)param[3];
      NSString* sectionT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* section = sectionT;
      NSString* recordValueT = [NSString stringWithCString:(const char*)param[5] encoding:[ctl innerGetCodePage]];
      NSString* recordValue = recordValueT;
      NSString* recordInfoT = [NSString stringWithCString:(const char*)param[6] encoding:[ctl innerGetCodePage]];
      NSString* recordInfo = recordInfoT;
      @try {
        [ctl onDNSCacheEntry :recordName :recordType :timeToLive :dataLength :section :recordValue :recordInfo];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"DNSCacheEntry" :YES];
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
    case 3 /*EID_REQUESTCOMPLETE*/: {
      int requestId = (int)(long)param[0];
      int statusCode = (int)(long)param[1];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      @try {
        [ctl onRequestComplete :requestId :statusCode :description];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"RequestComplete" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksIPInfo

+ (IPWorksIPInfo*)ipinfo
{
#if __has_feature(objc_arc)
  return [[IPWorksIPInfo alloc] init];
#else
  return [[[IPWorksIPInfo alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_IPInfo_Create((void*)IPInfo_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_IPInfo_Create((void*)IPInfo_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_IPInfo_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_IPInfo_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_IPInfo_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_IPInfo_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_IPInfo_GetEventErrorCode(m_pObj);
}

- (id <IPWorksIPInfoDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksIPInfoDelegate>)anObject
{
  m_delegateHasDNSCacheEntry = NO;
  m_delegateHasError = NO;
  m_delegateHasRequestComplete = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onDNSCacheEntry:::::::)]) m_delegateHasDNSCacheEntry = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onRequestComplete:::)]) m_delegateHasRequestComplete = YES;
  }
}

  /* Events */

- (void)onDNSCacheEntry:(NSString*)recordName :(int)recordType :(int)timeToLive :(int)dataLength :(NSString*)section :(NSString*)recordValue :(NSString*)recordInfo
{
  if (m_delegate != nil && m_delegateHasDNSCacheEntry)
    [m_delegate onDNSCacheEntry:recordName :recordType :timeToLive :dataLength :section :recordValue :recordInfo];
}
- (void)onError:(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:errorCode :description];
}
- (void)onRequestComplete:(int)requestId :(int)statusCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasRequestComplete)
    [m_delegate onRequestComplete:requestId :statusCode :description];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_IPInfo_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_IPInfo_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_IPInfo_Get(m_pObj, 0, 0, 0, nil);
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

- (NSString*)adapterBroadcastAddress
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)adapterCount
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)adapterDescription
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)adapterDeviceIndex
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (BOOL)adapterDHCPEnabled
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)adapterDHCPServer
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterDNSServers
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterGateway
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)adapterIndex
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAdapterIndex:(int)newAdapterIndex
{
  void *val = (void*)(long)newAdapterIndex;
  int ret_code = IPWorks_IPInfo_Set(m_pObj, 9, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)adapterIPAddress
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterIPv6Address
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterIPv6LinkLocalAddress
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterLeaseExpires
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterLeaseObtained
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterName
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterOtherIPAddresses
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterPhysicalAddress
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterPrimaryWINSServer
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterSecondaryWINSServer
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterStatus
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterSubnetMask
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)adapterType
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)adapterUsesWINS
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (int)adapterZoneId
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (BOOL)ARPProxy
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)DHCPScope
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)DNSEnabled
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)DNSServer
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)domainName
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 29, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)hostAddress
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setHostAddress:(NSString*)newHostAddress
{
  void *val = (void*)[self nsstringToCString:newHostAddress];
  int ret_code = IPWorks_IPInfo_Set(m_pObj, 30, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)hostAliases
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)hostName
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setHostName:(NSString*)newHostName
{
  void *val = (void*)[self nsstringToCString:newHostName];
  int ret_code = IPWorks_IPInfo_Set(m_pObj, 32, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 33, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)nodeType
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 34, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)otherAddresses
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 35, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)otherDNSServers
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 36, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)pendingRequests
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 37, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setPendingRequests:(int)newPendingRequests
{
  void *val = (void*)(long)newPendingRequests;
  int ret_code = IPWorks_IPInfo_Set(m_pObj, 37, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)requestId
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 38, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (BOOL)routingEnabled
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 39, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)serviceAliases
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 40, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)serviceName
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 41, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setServiceName:(NSString*)newServiceName
{
  void *val = (void*)[self nsstringToCString:newServiceName];
  int ret_code = IPWorks_IPInfo_Set(m_pObj, 41, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)servicePort
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 42, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setServicePort:(int)newServicePort
{
  void *val = (void*)(long)newServicePort;
  int ret_code = IPWorks_IPInfo_Set(m_pObj, 42, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)serviceProtocol
{
  int len = 0;
  void* val=IPWorks_IPInfo_Get(m_pObj, 43, 0, &len, nil);
  if (IPWorks_IPInfo_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setServiceProtocol:(NSString*)newServiceProtocol
{
  void *val = (void*)[self nsstringToCString:newServiceProtocol];
  int ret_code = IPWorks_IPInfo_Set(m_pObj, 43, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IPInfo_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)DHCPRelease
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IPInfo_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)DHCPRenew
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IPInfo_Do(m_pObj, 4, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)displayDNSCache
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IPInfo_Do(m_pObj, 5, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[0] encoding:[self innerGetCodePage]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IPInfo_Do(m_pObj, 6, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)flushDNSCache
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IPInfo_Do(m_pObj, 7, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return param[0] ? YES : NO;
}

- (NSString*)getMAC:(NSString*)IPAddress
{
  void *param[1+1] = {(void*)[self nsstringToCString:IPAddress], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IPInfo_Do(m_pObj, 8, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IPInfo_Do(m_pObj, 9, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)resolveAddress:(NSString*)hostAddress
{
  void *param[1+1] = {(void*)[self nsstringToCString:hostAddress], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IPInfo_Do(m_pObj, 10, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (NSString*)resolveName:(NSString*)hostName
{
  void *param[1+1] = {(void*)[self nsstringToCString:hostName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IPInfo_Do(m_pObj, 11, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
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
  int codePage = (int)(long)IPWorks_IPInfo_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_IPInfo_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end