
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksDNS.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksDNS()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define DNS_EXTERN extern "C"
#else
#define DNS_EXTERN extern
#endif

DNS_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
DNS_EXTERN void* IPWorks_DNS_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
DNS_EXTERN int   IPWorks_DNS_Destroy(void* lpObj);
DNS_EXTERN int   IPWorks_DNS_CheckIndex(void* lpObj, int propid, int arridx);
DNS_EXTERN void* IPWorks_DNS_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
DNS_EXTERN int   IPWorks_DNS_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
DNS_EXTERN int   IPWorks_DNS_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
DNS_EXTERN char* IPWorks_DNS_GetLastError(void* lpObj);
DNS_EXTERN int   IPWorks_DNS_GetLastErrorCode(void* lpObj);
DNS_EXTERN int   IPWorks_DNS_SetLastErrorAndCode(void* lpObj, int code, char* message);
DNS_EXTERN char* IPWorks_DNS_GetEventError(void* lpObj);
DNS_EXTERN int   IPWorks_DNS_GetEventErrorCode(void* lpObj);
DNS_EXTERN int   IPWorks_DNS_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void DNS_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_DNS_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int DNS_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksDNS* ctl = (IPWorksDNS*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, DNS_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (DNS)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
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
    case 2 /*EID_RESPONSE*/: {
      int requestId = (int)(long)param[0];
      NSString* domainT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* domain = domainT;
      int statusCode = (int)(long)param[2];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      BOOL authoritative = param[4] ? YES : NO;
      @try {
        [ctl onResponse :requestId :domain :statusCode :description :authoritative];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Response" :YES];
      }
      break;
    }
    case 3 /*EID_SSLSERVERAUTHENTICATION*/: {
      NSString* remoteAddressT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* remoteAddress = remoteAddressT;
      int remotePort = (int)(long)param[1];
      NSData* certEncoded = [NSData dataWithBytesNoCopy:param[2] length:cbparam[2] freeWhenDone:NO];
      NSString* certSubjectT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* certSubject = certSubjectT;
      NSString* certIssuerT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* certIssuer = certIssuerT;
      NSString* statusT = [NSString stringWithCString:(const char*)param[5] encoding:[ctl innerGetCodePage]];
      NSString* status = statusT;
      int* accept = (int*)&param[6];
      @try {
        [ctl onSSLServerAuthentication :remoteAddress :remotePort :certEncoded :certSubject :certIssuer :status :accept];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SSLServerAuthentication" :YES];
      }
      break;
    }
    case 4 /*EID_SSLSTATUS*/: {
      NSString* remoteAddressT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* remoteAddress = remoteAddressT;
      int remotePort = (int)(long)param[1];
      NSString* messageT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* message = messageT;
      @try {
        [ctl onSSLStatus :remoteAddress :remotePort :message];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SSLStatus" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksDNS

+ (IPWorksDNS*)dns
{
#if __has_feature(objc_arc)
  return [[IPWorksDNS alloc] init];
#else
  return [[[IPWorksDNS alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_DNS_Create((void*)DNS_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_DNS_Create((void*)DNS_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_DNS_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_DNS_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_DNS_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_DNS_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_DNS_GetEventErrorCode(m_pObj);
}

- (id <IPWorksDNSDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksDNSDelegate>)anObject
{
  m_delegateHasError = NO;
  m_delegateHasResponse = NO;
  m_delegateHasSSLServerAuthentication = NO;
  m_delegateHasSSLStatus = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onResponse:::::)]) m_delegateHasResponse = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLServerAuthentication:::::::)]) m_delegateHasSSLServerAuthentication = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLStatus:::)]) m_delegateHasSSLStatus = YES;
  }
}

  /* Events */

- (void)onError:(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:errorCode :description];
}
- (void)onResponse:(int)requestId :(NSString*)domain :(int)statusCode :(NSString*)description :(BOOL)authoritative
{
  if (m_delegate != nil && m_delegateHasResponse)
    [m_delegate onResponse:requestId :domain :statusCode :description :authoritative];
}
- (void)onSSLServerAuthentication:(NSString*)remoteAddress :(int)remotePort :(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept
{
  if (m_delegate != nil && m_delegateHasSSLServerAuthentication)
    [m_delegate onSSLServerAuthentication:remoteAddress :remotePort :certEncoded :certSubject :certIssuer :status :accept];
}
- (void)onSSLStatus:(NSString*)remoteAddress :(int)remotePort :(NSString*)message
{
  if (m_delegate != nil && m_delegateHasSSLStatus)
    [m_delegate onSSLStatus:remoteAddress :remotePort :message];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_DNS_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_DNS_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_DNS_Get(m_pObj, 0, 0, 0, nil);
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

- (int)DNSPort
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setDNSPort:(int)newDNSPort
{
  void *val = (void*)(long)newDNSPort;
  int ret_code = IPWorks_DNS_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)DNSServer
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setDNSServer:(NSString*)newDNSServer
{
  void *val = (void*)[self nsstringToCString:newDNSServer];
  int ret_code = IPWorks_DNS_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_DNS_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)protocol
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)protocol_
{
  return [self protocol];
}

- (void)setProtocol:(int)newProtocol
{
  void *val = (void*)(long)newProtocol;
  int ret_code = IPWorks_DNS_Set(m_pObj, 5, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setProtocol_:(int)newProtocol
{
  return [self setProtocol:newProtocol];
}

- (int)queryType
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setQueryType:(int)newQueryType
{
  void *val = (void*)(long)newQueryType;
  int ret_code = IPWorks_DNS_Set(m_pObj, 6, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)recordCount
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)recordDomain:(int)recordIndex
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 8, recordIndex, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)recordFieldCount:(int)recordIndex
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 9, recordIndex, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)recordFieldIndex:(int)recordIndex
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 10, recordIndex, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setRecordFieldIndex:(int)recordIndex:(int)newRecordFieldIndex
{
  void *val = (void*)(long)newRecordFieldIndex;
  int ret_code = IPWorks_DNS_Set(m_pObj, 10, recordIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)recordFieldName:(int)recordIndex
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 11, recordIndex, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)recordFieldValue:(int)recordIndex
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 12, recordIndex, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)recordFieldValueB:(int)recordIndex
{
  int len = 0;
  void* val = IPWorks_DNS_Get(m_pObj, 12, recordIndex, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (NSString*)recordData:(int)recordIndex
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 13, recordIndex, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)recordDataB:(int)recordIndex
{
  int len = 0;
  void* val = IPWorks_DNS_Get(m_pObj, 13, recordIndex, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (int)recordType:(int)recordIndex
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 14, recordIndex, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)recordTypeName:(int)recordIndex
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 15, recordIndex, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)recordTTL:(int)recordIndex
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 16, recordIndex, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)recordSource
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setRecordSource:(int)newRecordSource
{
  void *val = (void*)(long)newRecordSource;
  int ret_code = IPWorks_DNS_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)recursive
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setRecursive:(BOOL)newRecursive
{
  void *val = (void*)(long)(newRecursive ? 1 : 0);
  int ret_code = IPWorks_DNS_Set(m_pObj, 18, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)requestId
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setRequestId:(int)newRequestId
{
  void *val = (void*)(long)newRequestId;
  int ret_code = IPWorks_DNS_Set(m_pObj, 19, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)status
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)statusCode
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_DNS_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_DNS_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_DNS_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_DNS_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_DNS_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)getFieldValue:(int)recordIndex :(NSString*)fieldName
{
  void *param[2+1] = {(void*)(long)recordIndex, (void*)[self nsstringToCString:fieldName], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_DNS_Do(m_pObj, 4, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[2] encoding:[self innerGetCodePage]];
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_DNS_Do(m_pObj, 5, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)query:(NSString*)domain
{
  void *param[1+1] = {(void*)[self nsstringToCString:domain], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_DNS_Do(m_pObj, 6, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_DNS_Do(m_pObj, 7, 0, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_DNS_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_DNS_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end