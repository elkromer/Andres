
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksIPDaemon.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksIPDaemon()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define IPDaemon_EXTERN extern "C"
#else
#define IPDaemon_EXTERN extern
#endif

IPDaemon_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
IPDaemon_EXTERN void* IPWorks_IPDaemon_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
IPDaemon_EXTERN int   IPWorks_IPDaemon_Destroy(void* lpObj);
IPDaemon_EXTERN int   IPWorks_IPDaemon_CheckIndex(void* lpObj, int propid, int arridx);
IPDaemon_EXTERN void* IPWorks_IPDaemon_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
IPDaemon_EXTERN int   IPWorks_IPDaemon_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
IPDaemon_EXTERN int   IPWorks_IPDaemon_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
IPDaemon_EXTERN char* IPWorks_IPDaemon_GetLastError(void* lpObj);
IPDaemon_EXTERN int   IPWorks_IPDaemon_GetLastErrorCode(void* lpObj);
IPDaemon_EXTERN int   IPWorks_IPDaemon_SetLastErrorAndCode(void* lpObj, int code, char* message);
IPDaemon_EXTERN char* IPWorks_IPDaemon_GetEventError(void* lpObj);
IPDaemon_EXTERN int   IPWorks_IPDaemon_GetEventErrorCode(void* lpObj);
IPDaemon_EXTERN int   IPWorks_IPDaemon_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void IPDaemon_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_IPDaemon_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int IPDaemon_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksIPDaemon* ctl = (IPWorksIPDaemon*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, IPDaemon_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (IPDaemon)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
      [myAlert show];
      return 1;
#else // TARGET_OS_IPHONE
      return 0;
#endif // TARGET_OS_IPHONE
    }

    case 1 /*EID_CONNECTED*/: {
      int connectionId = (int)(long)param[0];
      int statusCode = (int)(long)param[1];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      @try {
        [ctl onConnected :connectionId :statusCode :description];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Connected" :YES];
      }
      break;
    }
    case 2 /*EID_CONNECTIONREQUEST*/: {
      NSString* addressT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* address = addressT;
      int port = (int)(long)param[1];
      int* accept = (int*)&param[2];
      @try {
        [ctl onConnectionRequest :address :port :accept];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"ConnectionRequest" :YES];
      }
      break;
    }
    case 3 /*EID_DATAIN*/: {
      int connectionId = (int)(long)param[0];
      NSData* text = [NSData dataWithBytesNoCopy:param[1] length:cbparam[1] freeWhenDone:NO];
      BOOL EOL = param[2] ? YES : NO;
      @try {
        [ctl onDataIn :connectionId :text :EOL];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"DataIn" :YES];
      }
      break;
    }
    case 4 /*EID_DISCONNECTED*/: {
      int connectionId = (int)(long)param[0];
      int statusCode = (int)(long)param[1];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      @try {
        [ctl onDisconnected :connectionId :statusCode :description];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Disconnected" :YES];
      }
      break;
    }
    case 5 /*EID_ERROR*/: {
      int connectionId = (int)(long)param[0];
      int errorCode = (int)(long)param[1];
      NSString* descriptionT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* description = descriptionT;
      @try {
        [ctl onError :connectionId :errorCode :description];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Error" :NO];
      }
      break;
    }
    case 6 /*EID_READYTOSEND*/: {
      int connectionId = (int)(long)param[0];
      @try {
        [ctl onReadyToSend :connectionId];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"ReadyToSend" :YES];
      }
      break;
    }
    case 7 /*EID_SSLCLIENTAUTHENTICATION*/: {
      int connectionId = (int)(long)param[0];
      NSData* certEncoded = [NSData dataWithBytesNoCopy:param[1] length:cbparam[1] freeWhenDone:NO];
      NSString* certSubjectT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* certSubject = certSubjectT;
      NSString* certIssuerT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* certIssuer = certIssuerT;
      NSString* statusT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* status = statusT;
      int* accept = (int*)&param[5];
      @try {
        [ctl onSSLClientAuthentication :connectionId :certEncoded :certSubject :certIssuer :status :accept];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SSLClientAuthentication" :YES];
      }
      break;
    }
    case 8 /*EID_SSLCONNECTIONREQUEST*/: {
      int connectionId = (int)(long)param[0];
      NSString* supportedCipherSuitesT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* supportedCipherSuites = supportedCipherSuitesT;
      NSString* supportedSignatureAlgsT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* supportedSignatureAlgs = supportedSignatureAlgsT;
      int* certStoreType = (int*)&param[3];
      NSString* certStoreT = [NSString stringWithCString:(const char*)IPWorks_EvtStr(param[4], 0, nil, 1) encoding:[ctl innerGetCodePage]];
#if __has_feature(objc_arc)
      __autoreleasing NSString*  certStoreTA = certStoreT;
      __autoreleasing NSString** certStore = &certStoreTA;
#else
      NSString** certStore = &certStoreT;
#endif
      NSString* certPasswordT = [NSString stringWithCString:(const char*)IPWorks_EvtStr(param[5], 0, nil, 1) encoding:[ctl innerGetCodePage]];
#if __has_feature(objc_arc)
      __autoreleasing NSString*  certPasswordTA = certPasswordT;
      __autoreleasing NSString** certPassword = &certPasswordTA;
#else
      NSString** certPassword = &certPasswordT;
#endif
      NSString* certSubjectT = [NSString stringWithCString:(const char*)IPWorks_EvtStr(param[6], 0, nil, 1) encoding:[ctl innerGetCodePage]];
#if __has_feature(objc_arc)
      __autoreleasing NSString*  certSubjectTA = certSubjectT;
      __autoreleasing NSString** certSubject = &certSubjectTA;
#else
      NSString** certSubject = &certSubjectT;
#endif
      @try {
        [ctl onSSLConnectionRequest :connectionId :supportedCipherSuites :supportedSignatureAlgs :certStoreType :certStore :certPassword :certSubject];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SSLConnectionRequest" :YES];
      }
      IPWorks_EvtStr(param[4], 2, (void*)([ctl nsstringToCString:*certStore]), 1);
      IPWorks_EvtStr(param[5], 2, (void*)([ctl nsstringToCString:*certPassword]), 1);
      IPWorks_EvtStr(param[6], 2, (void*)([ctl nsstringToCString:*certSubject]), 1);
      break;
    }
    case 9 /*EID_SSLSTATUS*/: {
      int connectionId = (int)(long)param[0];
      NSString* messageT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* message = messageT;
      @try {
        [ctl onSSLStatus :connectionId :message];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SSLStatus" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksIPDaemon

+ (IPWorksIPDaemon*)ipdaemon
{
#if __has_feature(objc_arc)
  return [[IPWorksIPDaemon alloc] init];
#else
  return [[[IPWorksIPDaemon alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_IPDaemon_Create((void*)IPDaemon_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_IPDaemon_Create((void*)IPDaemon_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_IPDaemon_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_IPDaemon_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_IPDaemon_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_IPDaemon_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_IPDaemon_GetEventErrorCode(m_pObj);
}

- (id <IPWorksIPDaemonDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksIPDaemonDelegate>)anObject
{
  m_delegateHasConnected = NO;
  m_delegateHasConnectionRequest = NO;
  m_delegateHasDataIn = NO;
  m_delegateHasDisconnected = NO;
  m_delegateHasError = NO;
  m_delegateHasReadyToSend = NO;
  m_delegateHasSSLClientAuthentication = NO;
  m_delegateHasSSLConnectionRequest = NO;
  m_delegateHasSSLStatus = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onConnected:::)]) m_delegateHasConnected = YES;
    if ([m_delegate respondsToSelector:@selector(onConnectionRequest:::)]) m_delegateHasConnectionRequest = YES;
    if ([m_delegate respondsToSelector:@selector(onDataIn:::)]) m_delegateHasDataIn = YES;
    if ([m_delegate respondsToSelector:@selector(onDisconnected:::)]) m_delegateHasDisconnected = YES;
    if ([m_delegate respondsToSelector:@selector(onError:::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onReadyToSend:)]) m_delegateHasReadyToSend = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLClientAuthentication::::::)]) m_delegateHasSSLClientAuthentication = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLConnectionRequest:::::::)]) m_delegateHasSSLConnectionRequest = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLStatus::)]) m_delegateHasSSLStatus = YES;
  }
}

  /* Events */

- (void)onConnected:(int)connectionId :(int)statusCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasConnected)
    [m_delegate onConnected:connectionId :statusCode :description];
}
- (void)onConnectionRequest:(NSString*)address :(int)port :(int*)accept
{
  if (m_delegate != nil && m_delegateHasConnectionRequest)
    [m_delegate onConnectionRequest:address :port :accept];
}
- (void)onDataIn:(int)connectionId :(NSData*)text :(BOOL)EOL
{
  if (m_delegate != nil && m_delegateHasDataIn)
    [m_delegate onDataIn:connectionId :text :EOL];
}
- (void)onDisconnected:(int)connectionId :(int)statusCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasDisconnected)
    [m_delegate onDisconnected:connectionId :statusCode :description];
}
- (void)onError:(int)connectionId :(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:connectionId :errorCode :description];
}
- (void)onReadyToSend:(int)connectionId
{
  if (m_delegate != nil && m_delegateHasReadyToSend)
    [m_delegate onReadyToSend:connectionId];
}
- (void)onSSLClientAuthentication:(int)connectionId :(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept
{
  if (m_delegate != nil && m_delegateHasSSLClientAuthentication)
    [m_delegate onSSLClientAuthentication:connectionId :certEncoded :certSubject :certIssuer :status :accept];
}
- (void)onSSLConnectionRequest:(int)connectionId :(NSString*)supportedCipherSuites :(NSString*)supportedSignatureAlgs :(int*)certStoreType :(NSString**)certStore :(NSString**)certPassword :(NSString**)certSubject
{
  if (m_delegate != nil && m_delegateHasSSLConnectionRequest)
    [m_delegate onSSLConnectionRequest:connectionId :supportedCipherSuites :supportedSignatureAlgs :certStoreType :certStore :certPassword :certSubject];
}
- (void)onSSLStatus:(int)connectionId :(NSString*)message
{
  if (m_delegate != nil && m_delegateHasSSLStatus)
    [m_delegate onSSLStatus:connectionId :message];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_IPDaemon_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_IPDaemon_Get(m_pObj, 0, 0, 0, nil);
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

- (int)connectionBacklog
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setConnectionBacklog:(int)newConnectionBacklog
{
  void *val = (void*)(long)newConnectionBacklog;
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)connectionCount
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (BOOL)acceptData:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 3, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setAcceptData:(int)connectionId:(BOOL)newAcceptData
{
  void *val = (void*)(long)(newAcceptData ? 1 : 0);
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 3, connectionId, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)bytesSent:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 4, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (BOOL)connected:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 5, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setConnected:(int)connectionId:(BOOL)newConnected
{
  void *val = (void*)(long)(newConnected ? 1 : 0);
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 5, connectionId, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)connectionId:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 6, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

// Placeholder for writeonly properties.
- (NSString*)dataToSend:(int)connectionId
{
  return nil;
}

- (void)setDataToSend:(int)connectionId:(NSString*)newDataToSend
{
  int len = (int)[newDataToSend lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newDataToSend];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 7, connectionId, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

// Placeholder for writeonly properties.
- (NSData*)dataToSendB:(int)connectionId
{
  return nil;
}

- (void)setDataToSendB:(int)connectionId :(NSData*)newDataToSend
{
  int len = (int)[newDataToSend length];
  void *val = (void*)[newDataToSend bytes];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 7, connectionId, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)EOL:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 8, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setEOL:(int)connectionId:(NSString*)newEOL
{
  int len = (int)[newEOL lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newEOL];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 8, connectionId, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)EOLB:(int)connectionId
{
  int len = 0;
  void* val = IPWorks_IPDaemon_Get(m_pObj, 8, connectionId, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setEOLB:(int)connectionId :(NSData*)newEOL
{
  int len = (int)[newEOL length];
  void *val = (void*)[newEOL bytes];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 8, connectionId, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)idleTimeout:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 9, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setIdleTimeout:(int)connectionId:(int)newIdleTimeout
{
  void *val = (void*)(long)newIdleTimeout;
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 9, connectionId, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localAddress:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 10, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)readyToSend:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 11, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (int)recordLength:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 12, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setRecordLength:(int)connectionId:(int)newRecordLength
{
  void *val = (void*)(long)newRecordLength;
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 12, connectionId, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)remoteHost:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 13, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)remotePort:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 14, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (BOOL)singleLineMode:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 15, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setSingleLineMode:(int)connectionId:(BOOL)newSingleLineMode
{
  void *val = (void*)(long)(newSingleLineMode ? 1 : 0);
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 15, connectionId, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)timeout:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 16, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)connectionId:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 16, connectionId, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)userData:(int)connectionId
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 17, connectionId, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setUserData:(int)connectionId:(NSString*)newUserData
{
  int len = (int)[newUserData lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newUserData];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 17, connectionId, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)userDataB:(int)connectionId
{
  int len = 0;
  void* val = IPWorks_IPDaemon_Get(m_pObj, 17, connectionId, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setUserDataB:(int)connectionId :(NSData*)newUserData
{
  int len = (int)[newUserData length];
  void *val = (void*)[newUserData bytes];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 17, connectionId, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)defaultEOL
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setDefaultEOL:(NSString*)newDefaultEOL
{
  int len = (int)[newDefaultEOL lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newDefaultEOL];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 18, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)defaultEOLB
{
  int len = 0;
  void* val = IPWorks_IPDaemon_Get(m_pObj, 18, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setDefaultEOLB :(NSData*)newDefaultEOL
{
  int len = (int)[newDefaultEOL length];
  void *val = (void*)[newDefaultEOL bytes];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 18, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)defaultIdleTimeout
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setDefaultIdleTimeout:(int)newDefaultIdleTimeout
{
  void *val = (void*)(long)newDefaultIdleTimeout;
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 19, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)defaultMaxLineLength
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setDefaultMaxLineLength:(int)newDefaultMaxLineLength
{
  void *val = (void*)(long)newDefaultMaxLineLength;
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 20, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)defaultSingleLineMode
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setDefaultSingleLineMode:(BOOL)newDefaultSingleLineMode
{
  void *val = (void*)(long)(newDefaultSingleLineMode ? 1 : 0);
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)defaultTimeout
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setDefaultTimeout:(int)newDefaultTimeout
{
  void *val = (void*)(long)newDefaultTimeout;
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)keepAlive
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setKeepAlive:(BOOL)newKeepAlive
{
  void *val = (void*)(long)(newKeepAlive ? 1 : 0);
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 23, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)linger
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setLinger:(BOOL)newLinger
{
  void *val = (void*)(long)(newLinger ? 1 : 0);
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 24, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)listening
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setListening:(BOOL)newListening
{
  void *val = (void*)(long)(newListening ? 1 : 0);
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 25, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 26, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)localPort
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setLocalPort:(int)newLocalPort
{
  void *val = (void*)(long)newLocalPort;
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 27, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)SSLAuthenticateClients
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setSSLAuthenticateClients:(BOOL)newSSLAuthenticateClients
{
  void *val = (void*)(long)(newSSLAuthenticateClients ? 1 : 0);
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 28, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 29, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 29, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_IPDaemon_Get(m_pObj, 29, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 29, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 30, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_IPDaemon_Get(m_pObj, 30, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 30, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 31, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 32, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 33, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 33, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)SSLEnabled
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 34, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setSSLEnabled:(BOOL)newSSLEnabled
{
  void *val = (void*)(long)(newSSLEnabled ? 1 : 0);
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 34, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLStartMode
{
  int len = 0;
  void* val=IPWorks_IPDaemon_Get(m_pObj, 35, 0, &len, nil);
  if (IPWorks_IPDaemon_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLStartMode:(int)newSSLStartMode
{
  void *val = (void*)(long)newSSLStartMode;
  int ret_code = IPWorks_IPDaemon_Set(m_pObj, 35, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IPDaemon_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)disconnect:(int)connectionId
{
  void *param[1+1] = {(void*)(long)connectionId, NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IPDaemon_Do(m_pObj, 3, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IPDaemon_Do(m_pObj, 4, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)interrupt:(int)connectionId
{
  void *param[1+1] = {(void*)(long)connectionId, NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IPDaemon_Do(m_pObj, 5, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IPDaemon_Do(m_pObj, 6, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)send:(int)connectionId :(NSData*)text
{
  void *param[2+1] = {(void*)(long)connectionId, (void*)[text bytes], NULL};
  int cbparam[2+1] = {0, (int)[text length], 0};

  int ret_code = IPWorks_IPDaemon_Do(m_pObj, 7, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)sendFile:(int)connectionId :(NSString*)fileName
{
  void *param[2+1] = {(void*)(long)connectionId, (void*)[self nsstringToCString:fileName], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_IPDaemon_Do(m_pObj, 8, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)sendLine:(int)connectionId :(NSString*)text
{
  void *param[2+1] = {(void*)(long)connectionId, (void*)[self nsstringToCString:text], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_IPDaemon_Do(m_pObj, 9, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)shutdown
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IPDaemon_Do(m_pObj, 10, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)startSSL:(int)connectionId
{
  void *param[1+1] = {(void*)(long)connectionId, NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IPDaemon_Do(m_pObj, 11, 1, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_IPDaemon_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_IPDaemon_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:0 :-1 :msg];
}
@end