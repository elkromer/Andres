
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksFTP.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksFTP()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define FTP_EXTERN extern "C"
#else
#define FTP_EXTERN extern
#endif

FTP_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
FTP_EXTERN void* IPWorks_FTP_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
FTP_EXTERN int   IPWorks_FTP_Destroy(void* lpObj);
FTP_EXTERN int   IPWorks_FTP_CheckIndex(void* lpObj, int propid, int arridx);
FTP_EXTERN void* IPWorks_FTP_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
FTP_EXTERN int   IPWorks_FTP_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
FTP_EXTERN int   IPWorks_FTP_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
FTP_EXTERN char* IPWorks_FTP_GetLastError(void* lpObj);
FTP_EXTERN int   IPWorks_FTP_GetLastErrorCode(void* lpObj);
FTP_EXTERN int   IPWorks_FTP_SetLastErrorAndCode(void* lpObj, int code, char* message);
FTP_EXTERN char* IPWorks_FTP_GetEventError(void* lpObj);
FTP_EXTERN int   IPWorks_FTP_GetEventErrorCode(void* lpObj);
FTP_EXTERN int   IPWorks_FTP_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void FTP_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_FTP_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int FTP_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksFTP* ctl = (IPWorksFTP*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, FTP_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (FTP)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
      [myAlert show];
      return 1;
#else // TARGET_OS_IPHONE
      return 0;
#endif // TARGET_OS_IPHONE
    }

    case 1 /*EID_CONNECTIONSTATUS*/: {
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
    case 2 /*EID_DIRLIST*/: {
      NSString* dirEntryT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* dirEntry = dirEntryT;
      NSString* fileNameT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* fileName = fileNameT;
      BOOL isDir = param[2] ? YES : NO;
      long long fileSize = *(long long*)param[3];
      NSString* fileTimeT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* fileTime = fileTimeT;
      @try {
        [ctl onDirList :dirEntry :fileName :isDir :fileSize :fileTime];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"DirList" :YES];
      }
      break;
    }
    case 3 /*EID_ENDTRANSFER*/: {
      int direction = (int)(long)param[0];
      @try {
        [ctl onEndTransfer :direction];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EndTransfer" :YES];
      }
      break;
    }
    case 4 /*EID_ERROR*/: {
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
    case 5 /*EID_PITRAIL*/: {
      int direction = (int)(long)param[0];
      NSString* messageT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* message = messageT;
      @try {
        [ctl onPITrail :direction :message];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"PITrail" :YES];
      }
      break;
    }
    case 6 /*EID_SSLSERVERAUTHENTICATION*/: {
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
    case 7 /*EID_SSLSTATUS*/: {
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
    case 8 /*EID_STARTTRANSFER*/: {
      int direction = (int)(long)param[0];
      @try {
        [ctl onStartTransfer :direction];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StartTransfer" :YES];
      }
      break;
    }
    case 9 /*EID_TRANSFER*/: {
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

@implementation IPWorksFTP

+ (IPWorksFTP*)ftp
{
#if __has_feature(objc_arc)
  return [[IPWorksFTP alloc] init];
#else
  return [[[IPWorksFTP alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_FTP_Create((void*)FTP_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_FTP_Create((void*)FTP_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_FTP_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_FTP_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_FTP_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_FTP_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_FTP_GetEventErrorCode(m_pObj);
}

- (id <IPWorksFTPDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksFTPDelegate>)anObject
{
  m_delegateHasConnectionStatus = NO;
  m_delegateHasDirList = NO;
  m_delegateHasEndTransfer = NO;
  m_delegateHasError = NO;
  m_delegateHasPITrail = NO;
  m_delegateHasSSLServerAuthentication = NO;
  m_delegateHasSSLStatus = NO;
  m_delegateHasStartTransfer = NO;
  m_delegateHasTransfer = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onConnectionStatus:::)]) m_delegateHasConnectionStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onDirList:::::)]) m_delegateHasDirList = YES;
    if ([m_delegate respondsToSelector:@selector(onEndTransfer:)]) m_delegateHasEndTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onPITrail::)]) m_delegateHasPITrail = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLServerAuthentication:::::)]) m_delegateHasSSLServerAuthentication = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLStatus:)]) m_delegateHasSSLStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onStartTransfer:)]) m_delegateHasStartTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onTransfer::::)]) m_delegateHasTransfer = YES;
  }
}

  /* Events */

- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasConnectionStatus)
    [m_delegate onConnectionStatus:connectionEvent :statusCode :description];
}
- (void)onDirList:(NSString*)dirEntry :(NSString*)fileName :(BOOL)isDir :(long long)fileSize :(NSString*)fileTime
{
  if (m_delegate != nil && m_delegateHasDirList)
    [m_delegate onDirList:dirEntry :fileName :isDir :fileSize :fileTime];
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
- (void)onPITrail:(int)direction :(NSString*)message
{
  if (m_delegate != nil && m_delegateHasPITrail)
    [m_delegate onPITrail:direction :message];
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
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSData*)text
{
  if (m_delegate != nil && m_delegateHasTransfer)
    [m_delegate onTransfer:direction :bytesTransferred :percentDone :text];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_FTP_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_FTP_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_FTP_Get(m_pObj, 0, 0, 0, nil);
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

- (NSString*)account
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAccount:(NSString*)newAccount
{
  void *val = (void*)[self nsstringToCString:newAccount];
  int ret_code = IPWorks_FTP_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

// Placeholder for writeonly properties.
- (NSString*)command
{
  return nil;
}

- (void)setCommand:(NSString*)newCommand
{
  void *val = (void*)[self nsstringToCString:newCommand];
  int ret_code = IPWorks_FTP_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)connected
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setConnected:(BOOL)newConnected
{
  void *val = (void*)(long)(newConnected ? 1 : 0);
  int ret_code = IPWorks_FTP_Set(m_pObj, 3, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)dirListCount
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)dirListEntry:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 5, entryIndex, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)dirListFileName:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 6, entryIndex, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (long long)dirListFileSize:(int)entryIndex
{
  int len = 0;
  long long llVal;
  IPWorks_FTP_Get(m_pObj, 7, entryIndex, &len, &llVal);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (NSString*)dirListFileTime:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 8, entryIndex, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)dirListIsDir:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 9, entryIndex, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (BOOL)fileExists
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (long long)fileSize
{
  int len = 0;
  long long llVal;
  IPWorks_FTP_Get(m_pObj, 11, 0, &len, &llVal);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (NSString*)fileTime
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)firewallAutoDetect
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect
{
  void *val = (void*)(long)(newFirewallAutoDetect ? 1 : 0);
  int ret_code = IPWorks_FTP_Set(m_pObj, 13, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallType
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallType:(int)newFirewallType
{
  void *val = (void*)(long)newFirewallType;
  int ret_code = IPWorks_FTP_Set(m_pObj, 14, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallHost
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallHost:(NSString*)newFirewallHost
{
  void *val = (void*)[self nsstringToCString:newFirewallHost];
  int ret_code = IPWorks_FTP_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallPassword
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallPassword:(NSString*)newFirewallPassword
{
  void *val = (void*)[self nsstringToCString:newFirewallPassword];
  int ret_code = IPWorks_FTP_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallPort
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallPort:(int)newFirewallPort
{
  void *val = (void*)(long)newFirewallPort;
  int ret_code = IPWorks_FTP_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallUser
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallUser:(NSString*)newFirewallUser
{
  void *val = (void*)[self nsstringToCString:newFirewallUser];
  int ret_code = IPWorks_FTP_Set(m_pObj, 18, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)lastReply
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)localFile
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalFile:(NSString*)newLocalFile
{
  void *val = (void*)[self nsstringToCString:newLocalFile];
  int ret_code = IPWorks_FTP_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_FTP_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)overwrite
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setOverwrite:(BOOL)newOverwrite
{
  void *val = (void*)(long)(newOverwrite ? 1 : 0);
  int ret_code = IPWorks_FTP_Set(m_pObj, 23, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)passive
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setPassive:(BOOL)newPassive
{
  void *val = (void*)(long)(newPassive ? 1 : 0);
  int ret_code = IPWorks_FTP_Set(m_pObj, 24, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)password
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPassword:(NSString*)newPassword
{
  void *val = (void*)[self nsstringToCString:newPassword];
  int ret_code = IPWorks_FTP_Set(m_pObj, 25, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)remoteFile
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRemoteFile:(NSString*)newRemoteFile
{
  void *val = (void*)[self nsstringToCString:newRemoteFile];
  int ret_code = IPWorks_FTP_Set(m_pObj, 26, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)remoteHost
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRemoteHost:(NSString*)newRemoteHost
{
  void *val = (void*)[self nsstringToCString:newRemoteHost];
  int ret_code = IPWorks_FTP_Set(m_pObj, 27, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)remotePath
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRemotePath:(NSString*)newRemotePath
{
  void *val = (void*)[self nsstringToCString:newRemotePath];
  int ret_code = IPWorks_FTP_Set(m_pObj, 28, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)remotePort
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 29, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setRemotePort:(int)newRemotePort
{
  void *val = (void*)(long)newRemotePort;
  int ret_code = IPWorks_FTP_Set(m_pObj, 29, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLAcceptServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLAcceptServerCertEncoded];
  int ret_code = IPWorks_FTP_Set(m_pObj, 30, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLAcceptServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_FTP_Get(m_pObj, 30, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded length];
  void *val = (void*)[newSSLAcceptServerCertEncoded bytes];
  int ret_code = IPWorks_FTP_Set(m_pObj, 30, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_FTP_Set(m_pObj, 31, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_FTP_Get(m_pObj, 31, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_FTP_Set(m_pObj, 31, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_FTP_Set(m_pObj, 32, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_FTP_Get(m_pObj, 32, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_FTP_Set(m_pObj, 32, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 33, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_FTP_Set(m_pObj, 33, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 34, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_FTP_Set(m_pObj, 34, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 35, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_FTP_Set(m_pObj, 35, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)SSLEnabled
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 36, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setSSLEnabled:(BOOL)newSSLEnabled
{
  void *val = (void*)(long)(newSSLEnabled ? 1 : 0);
  int ret_code = IPWorks_FTP_Set(m_pObj, 36, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 37, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)SSLServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_FTP_Get(m_pObj, 37, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (int)SSLStartMode
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 38, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLStartMode:(int)newSSLStartMode
{
  void *val = (void*)(long)newSSLStartMode;
  int ret_code = IPWorks_FTP_Set(m_pObj, 38, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)startByte
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 39, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setStartByte:(NSString*)newStartByte
{
  void *val = (void*)[self nsstringToCString:newStartByte];
  int ret_code = IPWorks_FTP_Set(m_pObj, 39, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 40, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_FTP_Set(m_pObj, 40, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)transferMode
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 41, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTransferMode:(int)newTransferMode
{
  void *val = (void*)(long)newTransferMode;
  int ret_code = IPWorks_FTP_Set(m_pObj, 41, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)user
{
  int len = 0;
  void* val=IPWorks_FTP_Get(m_pObj, 42, 0, &len, nil);
  if (IPWorks_FTP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUser:(NSString*)newUser
{
  void *val = (void*)[self nsstringToCString:newUser];
  int ret_code = IPWorks_FTP_Set(m_pObj, 42, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (void)abort
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 2, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)append
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 4, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)deleteFile:(NSString*)fileName
{
  void *param[1+1] = {(void*)[self nsstringToCString:fileName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 5, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 6, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)download
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 7, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 8, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)listDirectory
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 9, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)listDirectoryLong
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 10, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)logoff
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 11, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)logon
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 12, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)makeDirectory:(NSString*)newDir
{
  void *param[1+1] = {(void*)[self nsstringToCString:newDir], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 13, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)removeDirectory:(NSString*)dirName
{
  void *param[1+1] = {(void*)[self nsstringToCString:dirName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 14, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)renameFile:(NSString*)newName
{
  void *param[1+1] = {(void*)[self nsstringToCString:newName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 15, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 16, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)storeUnique
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 19, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)upload
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_FTP_Do(m_pObj, 20, 0, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_FTP_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_FTP_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end