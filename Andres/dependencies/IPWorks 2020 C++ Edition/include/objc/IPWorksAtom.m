
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksAtom.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksAtom()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define Atom_EXTERN extern "C"
#else
#define Atom_EXTERN extern
#endif

Atom_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
Atom_EXTERN void* IPWorks_Atom_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
Atom_EXTERN int   IPWorks_Atom_Destroy(void* lpObj);
Atom_EXTERN int   IPWorks_Atom_CheckIndex(void* lpObj, int propid, int arridx);
Atom_EXTERN void* IPWorks_Atom_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
Atom_EXTERN int   IPWorks_Atom_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
Atom_EXTERN int   IPWorks_Atom_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
Atom_EXTERN char* IPWorks_Atom_GetLastError(void* lpObj);
Atom_EXTERN int   IPWorks_Atom_GetLastErrorCode(void* lpObj);
Atom_EXTERN int   IPWorks_Atom_SetLastErrorAndCode(void* lpObj, int code, char* message);
Atom_EXTERN char* IPWorks_Atom_GetEventError(void* lpObj);
Atom_EXTERN int   IPWorks_Atom_GetEventErrorCode(void* lpObj);
Atom_EXTERN int   IPWorks_Atom_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void Atom_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_Atom_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int Atom_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksAtom* ctl = (IPWorksAtom*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, Atom_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (Atom)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
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
    case 8 /*EID_REDIRECT*/: {
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
    case 9 /*EID_SETCOOKIE*/: {
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
    case 10 /*EID_SSLSERVERAUTHENTICATION*/: {
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
    case 11 /*EID_SSLSTATUS*/: {
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
    case 12 /*EID_STARTTRANSFER*/: {
      int direction = (int)(long)param[0];
      @try {
        [ctl onStartTransfer :direction];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StartTransfer" :YES];
      }
      break;
    }
    case 13 /*EID_STATUS*/: {
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
    case 14 /*EID_TRANSFER*/: {
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

@implementation IPWorksAtom

+ (IPWorksAtom*)atom
{
#if __has_feature(objc_arc)
  return [[IPWorksAtom alloc] init];
#else
  return [[[IPWorksAtom alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_Atom_Create((void*)Atom_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_Atom_Create((void*)Atom_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_Atom_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_Atom_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_Atom_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_Atom_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_Atom_GetEventErrorCode(m_pObj);
}

- (id <IPWorksAtomDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksAtomDelegate>)anObject
{
  m_delegateHasConnected = NO;
  m_delegateHasConnectionStatus = NO;
  m_delegateHasDisconnected = NO;
  m_delegateHasEndTransfer = NO;
  m_delegateHasError = NO;
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
  void* val = IPWorks_Atom_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_Atom_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_Atom_Get(m_pObj, 0, 0, 0, nil);
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
  void* val=IPWorks_Atom_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAccept:(NSString*)newAccept
{
  void *val = (void*)[self nsstringToCString:newAccept];
  int ret_code = IPWorks_Atom_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)atomData
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setAtomData:(NSString*)newAtomData
{
  int len = (int)[newAtomData lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newAtomData];
  int ret_code = IPWorks_Atom_Set(m_pObj, 2, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)atomDataB
{
  int len = 0;
  void* val = IPWorks_Atom_Get(m_pObj, 2, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setAtomDataB :(NSData*)newAtomData
{
  int len = (int)[newAtomData length];
  void *val = (void*)[newAtomData bytes];
  int ret_code = IPWorks_Atom_Set(m_pObj, 2, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)authorization
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAuthorization:(NSString*)newAuthorization
{
  void *val = (void*)[self nsstringToCString:newAuthorization];
  int ret_code = IPWorks_Atom_Set(m_pObj, 3, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)authScheme
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAuthScheme:(int)newAuthScheme
{
  void *val = (void*)(long)newAuthScheme;
  int ret_code = IPWorks_Atom_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelAuthorEmail
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelAuthorEmail:(NSString*)newChannelAuthorEmail
{
  void *val = (void*)[self nsstringToCString:newChannelAuthorEmail];
  int ret_code = IPWorks_Atom_Set(m_pObj, 5, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelAuthorName
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelAuthorName:(NSString*)newChannelAuthorName
{
  void *val = (void*)[self nsstringToCString:newChannelAuthorName];
  int ret_code = IPWorks_Atom_Set(m_pObj, 6, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelAuthorUri
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelAuthorUri:(NSString*)newChannelAuthorUri
{
  void *val = (void*)[self nsstringToCString:newChannelAuthorUri];
  int ret_code = IPWorks_Atom_Set(m_pObj, 7, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelCategoryLabel
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelCategoryLabel:(NSString*)newChannelCategoryLabel
{
  void *val = (void*)[self nsstringToCString:newChannelCategoryLabel];
  int ret_code = IPWorks_Atom_Set(m_pObj, 8, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelCategoryScheme
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelCategoryScheme:(NSString*)newChannelCategoryScheme
{
  void *val = (void*)[self nsstringToCString:newChannelCategoryScheme];
  int ret_code = IPWorks_Atom_Set(m_pObj, 9, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelCategoryTerm
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelCategoryTerm:(NSString*)newChannelCategoryTerm
{
  void *val = (void*)[self nsstringToCString:newChannelCategoryTerm];
  int ret_code = IPWorks_Atom_Set(m_pObj, 10, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelContributorEmail
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelContributorEmail:(NSString*)newChannelContributorEmail
{
  void *val = (void*)[self nsstringToCString:newChannelContributorEmail];
  int ret_code = IPWorks_Atom_Set(m_pObj, 11, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelContributorName
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelContributorName:(NSString*)newChannelContributorName
{
  void *val = (void*)[self nsstringToCString:newChannelContributorName];
  int ret_code = IPWorks_Atom_Set(m_pObj, 12, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelContributorUri
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelContributorUri:(NSString*)newChannelContributorUri
{
  void *val = (void*)[self nsstringToCString:newChannelContributorUri];
  int ret_code = IPWorks_Atom_Set(m_pObj, 13, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelGenerator
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelGenerator:(NSString*)newChannelGenerator
{
  void *val = (void*)[self nsstringToCString:newChannelGenerator];
  int ret_code = IPWorks_Atom_Set(m_pObj, 14, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelIcon
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelIcon:(NSString*)newChannelIcon
{
  void *val = (void*)[self nsstringToCString:newChannelIcon];
  int ret_code = IPWorks_Atom_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelId
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelId:(NSString*)newChannelId
{
  void *val = (void*)[self nsstringToCString:newChannelId];
  int ret_code = IPWorks_Atom_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkHref
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkHref:(NSString*)newChannelLinkHref
{
  void *val = (void*)[self nsstringToCString:newChannelLinkHref];
  int ret_code = IPWorks_Atom_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkHrefLang
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkHrefLang:(NSString*)newChannelLinkHrefLang
{
  void *val = (void*)[self nsstringToCString:newChannelLinkHrefLang];
  int ret_code = IPWorks_Atom_Set(m_pObj, 18, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkLength
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkLength:(NSString*)newChannelLinkLength
{
  void *val = (void*)[self nsstringToCString:newChannelLinkLength];
  int ret_code = IPWorks_Atom_Set(m_pObj, 19, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkRel
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkRel:(NSString*)newChannelLinkRel
{
  void *val = (void*)[self nsstringToCString:newChannelLinkRel];
  int ret_code = IPWorks_Atom_Set(m_pObj, 20, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkTitle
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkTitle:(NSString*)newChannelLinkTitle
{
  void *val = (void*)[self nsstringToCString:newChannelLinkTitle];
  int ret_code = IPWorks_Atom_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkType:(NSString*)newChannelLinkType
{
  void *val = (void*)[self nsstringToCString:newChannelLinkType];
  int ret_code = IPWorks_Atom_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLogo
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLogo:(NSString*)newChannelLogo
{
  void *val = (void*)[self nsstringToCString:newChannelLogo];
  int ret_code = IPWorks_Atom_Set(m_pObj, 23, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelRights
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelRights:(NSString*)newChannelRights
{
  void *val = (void*)[self nsstringToCString:newChannelRights];
  int ret_code = IPWorks_Atom_Set(m_pObj, 24, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)channelRightsTextType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setChannelRightsTextType:(int)newChannelRightsTextType
{
  void *val = (void*)(long)newChannelRightsTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 25, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelSubtitle
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelSubtitle:(NSString*)newChannelSubtitle
{
  void *val = (void*)[self nsstringToCString:newChannelSubtitle];
  int ret_code = IPWorks_Atom_Set(m_pObj, 26, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)channelSubtitleTextType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setChannelSubtitleTextType:(int)newChannelSubtitleTextType
{
  void *val = (void*)(long)newChannelSubtitleTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 27, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelTitle
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelTitle:(NSString*)newChannelTitle
{
  void *val = (void*)[self nsstringToCString:newChannelTitle];
  int ret_code = IPWorks_Atom_Set(m_pObj, 28, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)channelTitleTextType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 29, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setChannelTitleTextType:(int)newChannelTitleTextType
{
  void *val = (void*)(long)newChannelTitleTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 29, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelUpdated
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelUpdated:(NSString*)newChannelUpdated
{
  void *val = (void*)[self nsstringToCString:newChannelUpdated];
  int ret_code = IPWorks_Atom_Set(m_pObj, 30, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)connected
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setConnected:(BOOL)newConnected
{
  void *val = (void*)(long)(newConnected ? 1 : 0);
  int ret_code = IPWorks_Atom_Set(m_pObj, 31, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)contentType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setContentType:(NSString*)newContentType
{
  void *val = (void*)[self nsstringToCString:newContentType];
  int ret_code = IPWorks_Atom_Set(m_pObj, 32, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)cookieCount
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 33, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setCookieCount:(int)newCookieCount
{
  void *val = (void*)(long)newCookieCount;
  int ret_code = IPWorks_Atom_Set(m_pObj, 33, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookieDomain:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 34, cookieIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieExpiration:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 35, cookieIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieName:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 36, cookieIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieName:(int)cookieIndex:(NSString*)newCookieName
{
  void *val = (void*)[self nsstringToCString:newCookieName];
  int ret_code = IPWorks_Atom_Set(m_pObj, 36, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookiePath:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 37, cookieIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)cookieSecure:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 38, cookieIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)cookieValue:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 39, cookieIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieValue:(int)cookieIndex:(NSString*)newCookieValue
{
  void *val = (void*)[self nsstringToCString:newCookieValue];
  int ret_code = IPWorks_Atom_Set(m_pObj, 39, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)entryCount
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 40, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setEntryCount:(int)newEntryCount
{
  void *val = (void*)(long)newEntryCount;
  int ret_code = IPWorks_Atom_Set(m_pObj, 40, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryAuthorEmail:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 41, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryAuthorEmail:(int)entryIndex:(NSString*)newEntryAuthorEmail
{
  void *val = (void*)[self nsstringToCString:newEntryAuthorEmail];
  int ret_code = IPWorks_Atom_Set(m_pObj, 41, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryAuthorName:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 42, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryAuthorName:(int)entryIndex:(NSString*)newEntryAuthorName
{
  void *val = (void*)[self nsstringToCString:newEntryAuthorName];
  int ret_code = IPWorks_Atom_Set(m_pObj, 42, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryAuthorUri:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 43, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryAuthorUri:(int)entryIndex:(NSString*)newEntryAuthorUri
{
  void *val = (void*)[self nsstringToCString:newEntryAuthorUri];
  int ret_code = IPWorks_Atom_Set(m_pObj, 43, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryCategoryLabel:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 44, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryCategoryLabel:(int)entryIndex:(NSString*)newEntryCategoryLabel
{
  void *val = (void*)[self nsstringToCString:newEntryCategoryLabel];
  int ret_code = IPWorks_Atom_Set(m_pObj, 44, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryCategoryScheme:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 45, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryCategoryScheme:(int)entryIndex:(NSString*)newEntryCategoryScheme
{
  void *val = (void*)[self nsstringToCString:newEntryCategoryScheme];
  int ret_code = IPWorks_Atom_Set(m_pObj, 45, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryCategoryTerm:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 46, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryCategoryTerm:(int)entryIndex:(NSString*)newEntryCategoryTerm
{
  void *val = (void*)[self nsstringToCString:newEntryCategoryTerm];
  int ret_code = IPWorks_Atom_Set(m_pObj, 46, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryContent:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 47, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryContent:(int)entryIndex:(NSString*)newEntryContent
{
  void *val = (void*)[self nsstringToCString:newEntryContent];
  int ret_code = IPWorks_Atom_Set(m_pObj, 47, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)entryContentTextType:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 48, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setEntryContentTextType:(int)entryIndex:(int)newEntryContentTextType
{
  void *val = (void*)(long)newEntryContentTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 48, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryContributorEmail:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 49, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryContributorEmail:(int)entryIndex:(NSString*)newEntryContributorEmail
{
  void *val = (void*)[self nsstringToCString:newEntryContributorEmail];
  int ret_code = IPWorks_Atom_Set(m_pObj, 49, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryContributorName:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 50, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryContributorName:(int)entryIndex:(NSString*)newEntryContributorName
{
  void *val = (void*)[self nsstringToCString:newEntryContributorName];
  int ret_code = IPWorks_Atom_Set(m_pObj, 50, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryContributorUri:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 51, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryContributorUri:(int)entryIndex:(NSString*)newEntryContributorUri
{
  void *val = (void*)[self nsstringToCString:newEntryContributorUri];
  int ret_code = IPWorks_Atom_Set(m_pObj, 51, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryCopyright:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 52, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryCopyright:(int)entryIndex:(NSString*)newEntryCopyright
{
  void *val = (void*)[self nsstringToCString:newEntryCopyright];
  int ret_code = IPWorks_Atom_Set(m_pObj, 52, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryCreated:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 53, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryCreated:(int)entryIndex:(NSString*)newEntryCreated
{
  void *val = (void*)[self nsstringToCString:newEntryCreated];
  int ret_code = IPWorks_Atom_Set(m_pObj, 53, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryXML:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 54, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryXML:(int)entryIndex:(NSString*)newEntryXML
{
  void *val = (void*)[self nsstringToCString:newEntryXML];
  int ret_code = IPWorks_Atom_Set(m_pObj, 54, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryId:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 55, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryId:(int)entryIndex:(NSString*)newEntryId
{
  void *val = (void*)[self nsstringToCString:newEntryId];
  int ret_code = IPWorks_Atom_Set(m_pObj, 55, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryIssued:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 56, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryIssued:(int)entryIndex:(NSString*)newEntryIssued
{
  void *val = (void*)[self nsstringToCString:newEntryIssued];
  int ret_code = IPWorks_Atom_Set(m_pObj, 56, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryLinkHref:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 57, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryLinkHref:(int)entryIndex:(NSString*)newEntryLinkHref
{
  void *val = (void*)[self nsstringToCString:newEntryLinkHref];
  int ret_code = IPWorks_Atom_Set(m_pObj, 57, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryLinkHrefLang:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 58, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryLinkHrefLang:(int)entryIndex:(NSString*)newEntryLinkHrefLang
{
  void *val = (void*)[self nsstringToCString:newEntryLinkHrefLang];
  int ret_code = IPWorks_Atom_Set(m_pObj, 58, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryLinkLength:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 59, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryLinkLength:(int)entryIndex:(NSString*)newEntryLinkLength
{
  void *val = (void*)[self nsstringToCString:newEntryLinkLength];
  int ret_code = IPWorks_Atom_Set(m_pObj, 59, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryLinkRel:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 60, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryLinkRel:(int)entryIndex:(NSString*)newEntryLinkRel
{
  void *val = (void*)[self nsstringToCString:newEntryLinkRel];
  int ret_code = IPWorks_Atom_Set(m_pObj, 60, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryLinkTitle:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 61, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryLinkTitle:(int)entryIndex:(NSString*)newEntryLinkTitle
{
  void *val = (void*)[self nsstringToCString:newEntryLinkTitle];
  int ret_code = IPWorks_Atom_Set(m_pObj, 61, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryLinkType:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 62, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryLinkType:(int)entryIndex:(NSString*)newEntryLinkType
{
  void *val = (void*)[self nsstringToCString:newEntryLinkType];
  int ret_code = IPWorks_Atom_Set(m_pObj, 62, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryModified:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 63, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryModified:(int)entryIndex:(NSString*)newEntryModified
{
  void *val = (void*)[self nsstringToCString:newEntryModified];
  int ret_code = IPWorks_Atom_Set(m_pObj, 63, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryPublished:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 64, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryPublished:(int)entryIndex:(NSString*)newEntryPublished
{
  void *val = (void*)[self nsstringToCString:newEntryPublished];
  int ret_code = IPWorks_Atom_Set(m_pObj, 64, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryRights:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 65, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryRights:(int)entryIndex:(NSString*)newEntryRights
{
  void *val = (void*)[self nsstringToCString:newEntryRights];
  int ret_code = IPWorks_Atom_Set(m_pObj, 65, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)entryRightsTextType:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 66, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setEntryRightsTextType:(int)entryIndex:(int)newEntryRightsTextType
{
  void *val = (void*)(long)newEntryRightsTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 66, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entrySource:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 67, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntrySource:(int)entryIndex:(NSString*)newEntrySource
{
  void *val = (void*)[self nsstringToCString:newEntrySource];
  int ret_code = IPWorks_Atom_Set(m_pObj, 67, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entrySummary:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 68, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntrySummary:(int)entryIndex:(NSString*)newEntrySummary
{
  void *val = (void*)[self nsstringToCString:newEntrySummary];
  int ret_code = IPWorks_Atom_Set(m_pObj, 68, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)entrySummaryTextType:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 69, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setEntrySummaryTextType:(int)entryIndex:(int)newEntrySummaryTextType
{
  void *val = (void*)(long)newEntrySummaryTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 69, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryTitle:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 70, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryTitle:(int)entryIndex:(NSString*)newEntryTitle
{
  void *val = (void*)[self nsstringToCString:newEntryTitle];
  int ret_code = IPWorks_Atom_Set(m_pObj, 70, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)entryTitleTextType:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 71, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setEntryTitleTextType:(int)entryIndex:(int)newEntryTitleTextType
{
  void *val = (void*)(long)newEntryTitleTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 71, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryUpdated:(int)entryIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 72, entryIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryUpdated:(int)entryIndex:(NSString*)newEntryUpdated
{
  void *val = (void*)[self nsstringToCString:newEntryUpdated];
  int ret_code = IPWorks_Atom_Set(m_pObj, 72, entryIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)firewallAutoDetect
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 73, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect
{
  void *val = (void*)(long)(newFirewallAutoDetect ? 1 : 0);
  int ret_code = IPWorks_Atom_Set(m_pObj, 73, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 74, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallType:(int)newFirewallType
{
  void *val = (void*)(long)newFirewallType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 74, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallHost
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 75, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallHost:(NSString*)newFirewallHost
{
  void *val = (void*)[self nsstringToCString:newFirewallHost];
  int ret_code = IPWorks_Atom_Set(m_pObj, 75, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallPassword
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 76, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallPassword:(NSString*)newFirewallPassword
{
  void *val = (void*)[self nsstringToCString:newFirewallPassword];
  int ret_code = IPWorks_Atom_Set(m_pObj, 76, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallPort
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 77, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallPort:(int)newFirewallPort
{
  void *val = (void*)(long)newFirewallPort;
  int ret_code = IPWorks_Atom_Set(m_pObj, 77, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallUser
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 78, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallUser:(NSString*)newFirewallUser
{
  void *val = (void*)[self nsstringToCString:newFirewallUser];
  int ret_code = IPWorks_Atom_Set(m_pObj, 78, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)followRedirects
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 79, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFollowRedirects:(int)newFollowRedirects
{
  void *val = (void*)(long)newFollowRedirects;
  int ret_code = IPWorks_Atom_Set(m_pObj, 79, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 80, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)ifModifiedSince
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 81, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setIfModifiedSince:(NSString*)newIfModifiedSince
{
  void *val = (void*)[self nsstringToCString:newIfModifiedSince];
  int ret_code = IPWorks_Atom_Set(m_pObj, 81, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localFile
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 82, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalFile:(NSString*)newLocalFile
{
  void *val = (void*)[self nsstringToCString:newLocalFile];
  int ret_code = IPWorks_Atom_Set(m_pObj, 82, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 83, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_Atom_Set(m_pObj, 83, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)namespaceCount
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 84, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setNamespaceCount:(int)newNamespaceCount
{
  void *val = (void*)(long)newNamespaceCount;
  int ret_code = IPWorks_Atom_Set(m_pObj, 84, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)namespacePrefix:(int)namespaceIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 85, namespaceIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setNamespacePrefix:(int)namespaceIndex:(NSString*)newNamespacePrefix
{
  void *val = (void*)[self nsstringToCString:newNamespacePrefix];
  int ret_code = IPWorks_Atom_Set(m_pObj, 85, namespaceIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)namespaceURI:(int)namespaceIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 86, namespaceIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setNamespaceURI:(int)namespaceIndex:(NSString*)newNamespaceURI
{
  void *val = (void*)[self nsstringToCString:newNamespaceURI];
  int ret_code = IPWorks_Atom_Set(m_pObj, 86, namespaceIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)otherHeaders
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 87, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOtherHeaders:(NSString*)newOtherHeaders
{
  void *val = (void*)[self nsstringToCString:newOtherHeaders];
  int ret_code = IPWorks_Atom_Set(m_pObj, 87, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)parsedHeaderCount
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 88, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)parsedHeaderField:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 89, parsedHeaderIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)parsedHeaderValue:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 90, parsedHeaderIndex, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)password
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 91, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPassword:(NSString*)newPassword
{
  void *val = (void*)[self nsstringToCString:newPassword];
  int ret_code = IPWorks_Atom_Set(m_pObj, 91, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyAuthScheme
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 92, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyAuthScheme:(int)newProxyAuthScheme
{
  void *val = (void*)(long)newProxyAuthScheme;
  int ret_code = IPWorks_Atom_Set(m_pObj, 92, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)proxyAutoDetect
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 93, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setProxyAutoDetect:(BOOL)newProxyAutoDetect
{
  void *val = (void*)(long)(newProxyAutoDetect ? 1 : 0);
  int ret_code = IPWorks_Atom_Set(m_pObj, 93, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyPassword
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 94, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyPassword:(NSString*)newProxyPassword
{
  void *val = (void*)[self nsstringToCString:newProxyPassword];
  int ret_code = IPWorks_Atom_Set(m_pObj, 94, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyPort
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 95, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyPort:(int)newProxyPort
{
  void *val = (void*)(long)newProxyPort;
  int ret_code = IPWorks_Atom_Set(m_pObj, 95, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyServer
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 96, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyServer:(NSString*)newProxyServer
{
  void *val = (void*)[self nsstringToCString:newProxyServer];
  int ret_code = IPWorks_Atom_Set(m_pObj, 96, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxySSL
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 97, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxySSL:(int)newProxySSL
{
  void *val = (void*)(long)newProxySSL;
  int ret_code = IPWorks_Atom_Set(m_pObj, 97, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyUser
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 98, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyUser:(NSString*)newProxyUser
{
  void *val = (void*)[self nsstringToCString:newProxyUser];
  int ret_code = IPWorks_Atom_Set(m_pObj, 98, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)referer
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 99, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReferer:(NSString*)newReferer
{
  void *val = (void*)[self nsstringToCString:newReferer];
  int ret_code = IPWorks_Atom_Set(m_pObj, 99, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)slug
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 100, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSlug:(NSString*)newSlug
{
  void *val = (void*)[self nsstringToCString:newSlug];
  int ret_code = IPWorks_Atom_Set(m_pObj, 100, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLAcceptServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 101, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLAcceptServerCertEncoded];
  int ret_code = IPWorks_Atom_Set(m_pObj, 101, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLAcceptServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_Atom_Get(m_pObj, 101, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded length];
  void *val = (void*)[newSSLAcceptServerCertEncoded bytes];
  int ret_code = IPWorks_Atom_Set(m_pObj, 101, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 102, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_Atom_Set(m_pObj, 102, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_Atom_Get(m_pObj, 102, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_Atom_Set(m_pObj, 102, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 103, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_Atom_Set(m_pObj, 103, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_Atom_Get(m_pObj, 103, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_Atom_Set(m_pObj, 103, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 104, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_Atom_Set(m_pObj, 104, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 105, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 105, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 106, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_Atom_Set(m_pObj, 106, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 107, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)SSLServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_Atom_Get(m_pObj, 107, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 108, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_Atom_Set(m_pObj, 108, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)transferredData
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 109, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)transferredDataB
{
  int len = 0;
  void* val = IPWorks_Atom_Get(m_pObj, 109, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (long long)transferredDataLimit
{
  int len = 0;
  long long llVal;
  IPWorks_Atom_Get(m_pObj, 110, 0, &len, &llVal);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (void)setTransferredDataLimit:(long long)newTransferredDataLimit
{
  void *val = (void*)&newTransferredDataLimit;
  int ret_code = IPWorks_Atom_Set(m_pObj, 110, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)transferredHeaders
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 111, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)updateEntryAuthorEmail
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 112, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryAuthorEmail:(NSString*)newUpdateEntryAuthorEmail
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryAuthorEmail];
  int ret_code = IPWorks_Atom_Set(m_pObj, 112, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryAuthorName
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 113, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryAuthorName:(NSString*)newUpdateEntryAuthorName
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryAuthorName];
  int ret_code = IPWorks_Atom_Set(m_pObj, 113, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryAuthorUri
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 114, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryAuthorUri:(NSString*)newUpdateEntryAuthorUri
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryAuthorUri];
  int ret_code = IPWorks_Atom_Set(m_pObj, 114, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryCategoryLabel
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 115, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryCategoryLabel:(NSString*)newUpdateEntryCategoryLabel
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryCategoryLabel];
  int ret_code = IPWorks_Atom_Set(m_pObj, 115, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryCategoryScheme
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 116, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryCategoryScheme:(NSString*)newUpdateEntryCategoryScheme
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryCategoryScheme];
  int ret_code = IPWorks_Atom_Set(m_pObj, 116, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryCategoryTerm
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 117, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryCategoryTerm:(NSString*)newUpdateEntryCategoryTerm
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryCategoryTerm];
  int ret_code = IPWorks_Atom_Set(m_pObj, 117, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryContent
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 118, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryContent:(NSString*)newUpdateEntryContent
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryContent];
  int ret_code = IPWorks_Atom_Set(m_pObj, 118, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)updateEntryContentTextType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 119, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setUpdateEntryContentTextType:(int)newUpdateEntryContentTextType
{
  void *val = (void*)(long)newUpdateEntryContentTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 119, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryContributorEmail
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 120, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryContributorEmail:(NSString*)newUpdateEntryContributorEmail
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryContributorEmail];
  int ret_code = IPWorks_Atom_Set(m_pObj, 120, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryContributorName
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 121, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryContributorName:(NSString*)newUpdateEntryContributorName
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryContributorName];
  int ret_code = IPWorks_Atom_Set(m_pObj, 121, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryContributorUri
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 122, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryContributorUri:(NSString*)newUpdateEntryContributorUri
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryContributorUri];
  int ret_code = IPWorks_Atom_Set(m_pObj, 122, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryCopyright
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 123, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryCopyright:(NSString*)newUpdateEntryCopyright
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryCopyright];
  int ret_code = IPWorks_Atom_Set(m_pObj, 123, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryCreated
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 124, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryCreated:(NSString*)newUpdateEntryCreated
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryCreated];
  int ret_code = IPWorks_Atom_Set(m_pObj, 124, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryXML
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 125, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryXML:(NSString*)newUpdateEntryXML
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryXML];
  int ret_code = IPWorks_Atom_Set(m_pObj, 125, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryId
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 126, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryId:(NSString*)newUpdateEntryId
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryId];
  int ret_code = IPWorks_Atom_Set(m_pObj, 126, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryIssued
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 127, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryIssued:(NSString*)newUpdateEntryIssued
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryIssued];
  int ret_code = IPWorks_Atom_Set(m_pObj, 127, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryLinkHref
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 128, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryLinkHref:(NSString*)newUpdateEntryLinkHref
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryLinkHref];
  int ret_code = IPWorks_Atom_Set(m_pObj, 128, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryLinkHrefLang
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 129, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryLinkHrefLang:(NSString*)newUpdateEntryLinkHrefLang
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryLinkHrefLang];
  int ret_code = IPWorks_Atom_Set(m_pObj, 129, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryLinkLength
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 130, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryLinkLength:(NSString*)newUpdateEntryLinkLength
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryLinkLength];
  int ret_code = IPWorks_Atom_Set(m_pObj, 130, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryLinkRel
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 131, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryLinkRel:(NSString*)newUpdateEntryLinkRel
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryLinkRel];
  int ret_code = IPWorks_Atom_Set(m_pObj, 131, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryLinkTitle
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 132, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryLinkTitle:(NSString*)newUpdateEntryLinkTitle
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryLinkTitle];
  int ret_code = IPWorks_Atom_Set(m_pObj, 132, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryLinkType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 133, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryLinkType:(NSString*)newUpdateEntryLinkType
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryLinkType];
  int ret_code = IPWorks_Atom_Set(m_pObj, 133, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryModified
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 134, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryModified:(NSString*)newUpdateEntryModified
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryModified];
  int ret_code = IPWorks_Atom_Set(m_pObj, 134, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryPublished
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 135, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryPublished:(NSString*)newUpdateEntryPublished
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryPublished];
  int ret_code = IPWorks_Atom_Set(m_pObj, 135, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryRights
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 136, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryRights:(NSString*)newUpdateEntryRights
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryRights];
  int ret_code = IPWorks_Atom_Set(m_pObj, 136, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)updateEntryRightsTextType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 137, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setUpdateEntryRightsTextType:(int)newUpdateEntryRightsTextType
{
  void *val = (void*)(long)newUpdateEntryRightsTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 137, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntrySource
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 138, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntrySource:(NSString*)newUpdateEntrySource
{
  void *val = (void*)[self nsstringToCString:newUpdateEntrySource];
  int ret_code = IPWorks_Atom_Set(m_pObj, 138, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntrySummary
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 139, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntrySummary:(NSString*)newUpdateEntrySummary
{
  void *val = (void*)[self nsstringToCString:newUpdateEntrySummary];
  int ret_code = IPWorks_Atom_Set(m_pObj, 139, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)updateEntrySummaryTextType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 140, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setUpdateEntrySummaryTextType:(int)newUpdateEntrySummaryTextType
{
  void *val = (void*)(long)newUpdateEntrySummaryTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 140, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryTitle
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 141, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryTitle:(NSString*)newUpdateEntryTitle
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryTitle];
  int ret_code = IPWorks_Atom_Set(m_pObj, 141, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)updateEntryTitleTextType
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 142, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setUpdateEntryTitleTextType:(int)newUpdateEntryTitleTextType
{
  void *val = (void*)(long)newUpdateEntryTitleTextType;
  int ret_code = IPWorks_Atom_Set(m_pObj, 142, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateEntryUpdated
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 143, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateEntryUpdated:(NSString*)newUpdateEntryUpdated
{
  void *val = (void*)[self nsstringToCString:newUpdateEntryUpdated];
  int ret_code = IPWorks_Atom_Set(m_pObj, 143, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)updateFile
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 144, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUpdateFile:(NSString*)newUpdateFile
{
  void *val = (void*)[self nsstringToCString:newUpdateFile];
  int ret_code = IPWorks_Atom_Set(m_pObj, 144, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)user
{
  int len = 0;
  void* val=IPWorks_Atom_Get(m_pObj, 145, 0, &len, nil);
  if (IPWorks_Atom_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUser:(NSString*)newUser
{
  void *val = (void*)[self nsstringToCString:newUser];
  int ret_code = IPWorks_Atom_Set(m_pObj, 145, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (void)addCookie:(NSString*)cookieName :(NSString*)cookieValue
{
  void *param[2+1] = {(void*)[self nsstringToCString:cookieName], (void*)[self nsstringToCString:cookieValue], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 2, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)addNamespace:(NSString*)prefix :(NSString*)namespaceURI
{
  void *param[2+1] = {(void*)[self nsstringToCString:prefix], (void*)[self nsstringToCString:namespaceURI], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 3, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 4, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)deleteResource:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 5, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 6, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)getFeed:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 7, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)getProperty:(NSString*)propertyName
{
  void *param[1+1] = {(void*)[self nsstringToCString:propertyName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 8, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)getResource:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 9, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 10, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)postResource:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 11, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)put:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 12, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putResource:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 13, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)readFile:(NSString*)fileName
{
  void *param[1+1] = {(void*)[self nsstringToCString:fileName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 14, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 15, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setProperty:(NSString*)propertyName :(NSString*)propertyValue
{
  void *param[2+1] = {(void*)[self nsstringToCString:propertyName], (void*)[self nsstringToCString:propertyValue], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 16, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)writeFile:(NSString*)filename
{
  void *param[1+1] = {(void*)[self nsstringToCString:filename], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_Atom_Do(m_pObj, 17, 1, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_Atom_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_Atom_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end