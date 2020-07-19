
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksCertMgr.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksCertMgr()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define CertMgr_EXTERN extern "C"
#else
#define CertMgr_EXTERN extern
#endif

CertMgr_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
CertMgr_EXTERN void* IPWorks_CertMgr_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
CertMgr_EXTERN int   IPWorks_CertMgr_Destroy(void* lpObj);
CertMgr_EXTERN int   IPWorks_CertMgr_CheckIndex(void* lpObj, int propid, int arridx);
CertMgr_EXTERN void* IPWorks_CertMgr_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
CertMgr_EXTERN int   IPWorks_CertMgr_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
CertMgr_EXTERN int   IPWorks_CertMgr_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
CertMgr_EXTERN char* IPWorks_CertMgr_GetLastError(void* lpObj);
CertMgr_EXTERN int   IPWorks_CertMgr_GetLastErrorCode(void* lpObj);
CertMgr_EXTERN int   IPWorks_CertMgr_SetLastErrorAndCode(void* lpObj, int code, char* message);
CertMgr_EXTERN char* IPWorks_CertMgr_GetEventError(void* lpObj);
CertMgr_EXTERN int   IPWorks_CertMgr_GetEventErrorCode(void* lpObj);
CertMgr_EXTERN int   IPWorks_CertMgr_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void CertMgr_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_CertMgr_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int CertMgr_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksCertMgr* ctl = (IPWorksCertMgr*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, CertMgr_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (CertMgr)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
      [myAlert show];
      return 1;
#else // TARGET_OS_IPHONE
      return 0;
#endif // TARGET_OS_IPHONE
    }

    case 1 /*EID_CERTCHAIN*/: {
      NSData* certEncoded = [NSData dataWithBytesNoCopy:param[0] length:cbparam[0] freeWhenDone:NO];
      NSString* certSubjectT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* certSubject = certSubjectT;
      NSString* certIssuerT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* certIssuer = certIssuerT;
      NSString* certSerialNumberT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* certSerialNumber = certSerialNumberT;
      int trustStatus = (int)(long)param[4];
      int trustInfo = (int)(long)param[5];
      @try {
        [ctl onCertChain :certEncoded :certSubject :certIssuer :certSerialNumber :trustStatus :trustInfo];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"CertChain" :YES];
      }
      break;
    }
    case 2 /*EID_CERTLIST*/: {
      NSData* certEncoded = [NSData dataWithBytesNoCopy:param[0] length:cbparam[0] freeWhenDone:NO];
      NSString* certSubjectT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* certSubject = certSubjectT;
      NSString* certIssuerT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* certIssuer = certIssuerT;
      NSString* certSerialNumberT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* certSerialNumber = certSerialNumberT;
      BOOL hasPrivateKey = param[4] ? YES : NO;
      @try {
        [ctl onCertList :certEncoded :certSubject :certIssuer :certSerialNumber :hasPrivateKey];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"CertList" :YES];
      }
      break;
    }
    case 3 /*EID_ERROR*/: {
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
    case 4 /*EID_KEYLIST*/: {
      NSString* keyContainerT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* keyContainer = keyContainerT;
      int keyType = (int)(long)param[1];
      NSString* algIdT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* algId = algIdT;
      int keyLen = (int)(long)param[3];
      @try {
        [ctl onKeyList :keyContainer :keyType :algId :keyLen];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"KeyList" :YES];
      }
      break;
    }
    case 5 /*EID_LOG*/: {
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
    case 6 /*EID_STORELIST*/: {
      NSString* certStoreT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* certStore = certStoreT;
      @try {
        [ctl onStoreList :certStore];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StoreList" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksCertMgr

+ (IPWorksCertMgr*)certmgr
{
#if __has_feature(objc_arc)
  return [[IPWorksCertMgr alloc] init];
#else
  return [[[IPWorksCertMgr alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_CertMgr_Create((void*)CertMgr_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_CertMgr_Create((void*)CertMgr_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_CertMgr_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_CertMgr_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_CertMgr_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_CertMgr_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_CertMgr_GetEventErrorCode(m_pObj);
}

- (id <IPWorksCertMgrDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksCertMgrDelegate>)anObject
{
  m_delegateHasCertChain = NO;
  m_delegateHasCertList = NO;
  m_delegateHasError = NO;
  m_delegateHasKeyList = NO;
  m_delegateHasLog = NO;
  m_delegateHasStoreList = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onCertChain::::::)]) m_delegateHasCertChain = YES;
    if ([m_delegate respondsToSelector:@selector(onCertList:::::)]) m_delegateHasCertList = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onKeyList::::)]) m_delegateHasKeyList = YES;
    if ([m_delegate respondsToSelector:@selector(onLog:::)]) m_delegateHasLog = YES;
    if ([m_delegate respondsToSelector:@selector(onStoreList:)]) m_delegateHasStoreList = YES;
  }
}

  /* Events */

- (void)onCertChain:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)certSerialNumber :(int)trustStatus :(int)trustInfo
{
  if (m_delegate != nil && m_delegateHasCertChain)
    [m_delegate onCertChain:certEncoded :certSubject :certIssuer :certSerialNumber :trustStatus :trustInfo];
}
- (void)onCertList:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)certSerialNumber :(BOOL)hasPrivateKey
{
  if (m_delegate != nil && m_delegateHasCertList)
    [m_delegate onCertList:certEncoded :certSubject :certIssuer :certSerialNumber :hasPrivateKey];
}
- (void)onError:(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:errorCode :description];
}
- (void)onKeyList:(NSString*)keyContainer :(int)keyType :(NSString*)algId :(int)keyLen
{
  if (m_delegate != nil && m_delegateHasKeyList)
    [m_delegate onKeyList:keyContainer :keyType :algId :keyLen];
}
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType
{
  if (m_delegate != nil && m_delegateHasLog)
    [m_delegate onLog:logLevel :message :logType];
}
- (void)onStoreList:(NSString*)certStore
{
  if (m_delegate != nil && m_delegateHasStoreList)
    [m_delegate onStoreList:certStore];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_CertMgr_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_CertMgr_Get(m_pObj, 0, 0, 0, nil);
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

- (NSString*)certEffectiveDate
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certEncoded
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setCertEncoded:(NSString*)newCertEncoded
{
  int len = (int)[newCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newCertEncoded];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 2, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)certEncodedB
{
  int len = 0;
  void* val = IPWorks_CertMgr_Get(m_pObj, 2, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setCertEncodedB :(NSData*)newCertEncoded
{
  int len = (int)[newCertEncoded length];
  void *val = (void*)[newCertEncoded bytes];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 2, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)certExpirationDate
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certExtendedKeyUsage
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCertExtendedKeyUsage:(NSString*)newCertExtendedKeyUsage
{
  void *val = (void*)[self nsstringToCString:newCertExtendedKeyUsage];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)certFingerprint
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certIssuer
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certKeyPassword
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCertKeyPassword:(NSString*)newCertKeyPassword
{
  void *val = (void*)[self nsstringToCString:newCertKeyPassword];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 7, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)certPrivateKey
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)certPrivateKeyAvailable
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)certPrivateKeyContainer
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certPublicKey
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certPublicKeyAlgorithm
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCertPublicKeyAlgorithm:(NSString*)newCertPublicKeyAlgorithm
{
  void *val = (void*)[self nsstringToCString:newCertPublicKeyAlgorithm];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 12, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)certPublicKeyLength
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)certSerialNumber
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certSignatureAlgorithm
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certSubject
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCertSubject:(NSString*)newCertSubject
{
  void *val = (void*)[self nsstringToCString:newCertSubject];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)certSubjectAltNames
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certThumbprintMD5
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certThumbprintSHA1
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certThumbprintSHA256
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certUsage
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCertUsage:(NSString*)newCertUsage
{
  void *val = (void*)[self nsstringToCString:newCertUsage];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)certUsageFlags
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setCertUsageFlags:(int)newCertUsageFlags
{
  void *val = (void*)(long)newCertUsageFlags;
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)certVersion
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)certExtensionCount
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setCertExtensionCount:(int)newCertExtensionCount
{
  void *val = (void*)(long)newCertExtensionCount;
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 24, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)certExtensionCritical:(int)certExtensionIndex
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 25, certExtensionIndex, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)certExtensionOID:(int)certExtensionIndex
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 26, certExtensionIndex, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)certExtensionValue:(int)certExtensionIndex
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 27, certExtensionIndex, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)certExtensionValueB:(int)certExtensionIndex
{
  int len = 0;
  void* val = IPWorks_CertMgr_Get(m_pObj, 27, certExtensionIndex, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (NSString*)certStore
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setCertStore:(NSString*)newCertStore
{
  int len = (int)[newCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newCertStore];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 28, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)certStoreB
{
  int len = 0;
  void* val = IPWorks_CertMgr_Get(m_pObj, 28, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setCertStoreB :(NSData*)newCertStore
{
  int len = (int)[newCertStore length];
  void *val = (void*)[newCertStore bytes];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 28, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)certStorePassword
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 29, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCertStorePassword:(NSString*)newCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newCertStorePassword];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 29, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)certStoreType
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setCertStoreType:(int)newCertStoreType
{
  void *val = (void*)(long)newCertStoreType;
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 30, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)exportedCert
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)exportedCertB
{
  int len = 0;
  void* val = IPWorks_CertMgr_Get(m_pObj, 31, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (NSString*)exportFormat
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setExportFormat:(NSString*)newExportFormat
{
  void *val = (void*)[self nsstringToCString:newExportFormat];
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 32, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)exportPrivateKey
{
  int len = 0;
  void* val=IPWorks_CertMgr_Get(m_pObj, 33, 0, &len, nil);
  if (IPWorks_CertMgr_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setExportPrivateKey:(BOOL)newExportPrivateKey
{
  void *val = (void*)(long)(newExportPrivateKey ? 1 : 0);
  int ret_code = IPWorks_CertMgr_Set(m_pObj, 33, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)createCertificate:(NSString*)certSubject :(int)serialNumber
{
  void *param[2+1] = {(void*)[self nsstringToCString:certSubject], (void*)(long)serialNumber, NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 3, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)createKey:(NSString*)keyName
{
  void *param[1+1] = {(void*)[self nsstringToCString:keyName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 4, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)deleteCertificate
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 5, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)deleteKey:(NSString*)keyName
{
  void *param[1+1] = {(void*)[self nsstringToCString:keyName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 6, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)exportCertificate:(NSString*)certFile :(NSString*)password
{
  void *param[2+1] = {(void*)[self nsstringToCString:certFile], (void*)[self nsstringToCString:password], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 7, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)generateCSR:(NSString*)certSubject :(NSString*)keyName
{
  void *param[2+1] = {(void*)[self nsstringToCString:certSubject], (void*)[self nsstringToCString:keyName], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 8, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[2] encoding:[self innerGetCodePage]];
}

- (void)importCertificate:(NSString*)certFile :(NSString*)password :(NSString*)subject
{
  void *param[3+1] = {(void*)[self nsstringToCString:certFile], (void*)[self nsstringToCString:password], (void*)[self nsstringToCString:subject], NULL};
  int cbparam[3+1] = {0, 0, 0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 9, 3, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)importSignedCSR:(NSData*)signedCSR :(NSString*)keyName
{
  void *param[2+1] = {(void*)[signedCSR bytes], (void*)[self nsstringToCString:keyName], NULL};
  int cbparam[2+1] = {(int)[signedCSR length], 0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 10, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)issueCertificate:(NSString*)certSubject :(int)serialNumber
{
  void *param[2+1] = {(void*)[self nsstringToCString:certSubject], (void*)(long)serialNumber, NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 11, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)listCertificateStores
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 12, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[0] encoding:[self innerGetCodePage]];
}

- (NSString*)listKeys
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 13, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[0] encoding:[self innerGetCodePage]];
}

- (NSString*)listMachineStores
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 14, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[0] encoding:[self innerGetCodePage]];
}

- (NSString*)listStoreCertificates
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 15, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[0] encoding:[self innerGetCodePage]];
}

- (void)readCertificate:(NSString*)fileName
{
  void *param[1+1] = {(void*)[self nsstringToCString:fileName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 16, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)readCSR:(NSString*)CSR
{
  void *param[1+1] = {(void*)[self nsstringToCString:CSR], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 17, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 18, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)saveCertificate:(NSString*)fileName
{
  void *param[1+1] = {(void*)[self nsstringToCString:fileName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 19, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)showCertificateChain
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 20, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[0] encoding:[self innerGetCodePage]];
}

- (NSString*)signCSR:(NSData*)CSR :(int)serialNumber
{
  void *param[2+1] = {(void*)[CSR bytes], (void*)(long)serialNumber, NULL};
  int cbparam[2+1] = {(int)[CSR length], 0, 0};

  int ret_code = IPWorks_CertMgr_Do(m_pObj, 21, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[2] encoding:[self innerGetCodePage]];
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
  int codePage = (int)(long)IPWorks_CertMgr_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_CertMgr_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end