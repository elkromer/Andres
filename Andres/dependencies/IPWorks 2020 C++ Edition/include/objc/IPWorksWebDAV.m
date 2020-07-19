
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksWebDAV.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksWebDAV()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define WebDAV_EXTERN extern "C"
#else
#define WebDAV_EXTERN extern
#endif

WebDAV_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
WebDAV_EXTERN void* IPWorks_WebDAV_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
WebDAV_EXTERN int   IPWorks_WebDAV_Destroy(void* lpObj);
WebDAV_EXTERN int   IPWorks_WebDAV_CheckIndex(void* lpObj, int propid, int arridx);
WebDAV_EXTERN void* IPWorks_WebDAV_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
WebDAV_EXTERN int   IPWorks_WebDAV_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
WebDAV_EXTERN int   IPWorks_WebDAV_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
WebDAV_EXTERN char* IPWorks_WebDAV_GetLastError(void* lpObj);
WebDAV_EXTERN int   IPWorks_WebDAV_GetLastErrorCode(void* lpObj);
WebDAV_EXTERN int   IPWorks_WebDAV_SetLastErrorAndCode(void* lpObj, int code, char* message);
WebDAV_EXTERN char* IPWorks_WebDAV_GetEventError(void* lpObj);
WebDAV_EXTERN int   IPWorks_WebDAV_GetEventErrorCode(void* lpObj);
WebDAV_EXTERN int   IPWorks_WebDAV_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void WebDAV_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_WebDAV_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int WebDAV_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksWebDAV* ctl = (IPWorksWebDAV*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, WebDAV_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (WebDAV)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
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
    case 3 /*EID_DIRLIST*/: {
      NSString* resourceURIT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* resourceURI = resourceURIT;
      NSString* displayNameT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* displayName = displayNameT;
      NSString* contentLanguageT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* contentLanguage = contentLanguageT;
      NSString* contentLengthT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* contentLength = contentLengthT;
      NSString* contentTypeT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* contentType = contentTypeT;
      NSString* lastModifiedT = [NSString stringWithCString:(const char*)param[5] encoding:[ctl innerGetCodePage]];
      NSString* lastModified = lastModifiedT;
      @try {
        [ctl onDirList :resourceURI :displayName :contentLanguage :contentLength :contentType :lastModified];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"DirList" :YES];
      }
      break;
    }
    case 4 /*EID_DISCONNECTED*/: {
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
    case 5 /*EID_ENDTRANSFER*/: {
      int direction = (int)(long)param[0];
      @try {
        [ctl onEndTransfer :direction];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EndTransfer" :YES];
      }
      break;
    }
    case 6 /*EID_ERROR*/: {
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
    case 7 /*EID_HEADER*/: {
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
    case 8 /*EID_LOG*/: {
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
    case 9 /*EID_REDIRECT*/: {
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
    case 10 /*EID_RESOURCEPROPERTIES*/: {
      NSString* resourceURIT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* resourceURI = resourceURIT;
      NSString* resourcePropertiesT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* resourceProperties = resourcePropertiesT;
      @try {
        [ctl onResourceProperties :resourceURI :resourceProperties];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"ResourceProperties" :YES];
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

@implementation IPWorksWebDAV

+ (IPWorksWebDAV*)webdav
{
#if __has_feature(objc_arc)
  return [[IPWorksWebDAV alloc] init];
#else
  return [[[IPWorksWebDAV alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_WebDAV_Create((void*)WebDAV_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_WebDAV_Create((void*)WebDAV_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_WebDAV_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_WebDAV_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_WebDAV_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_WebDAV_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_WebDAV_GetEventErrorCode(m_pObj);
}

- (id <IPWorksWebDAVDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksWebDAVDelegate>)anObject
{
  m_delegateHasConnected = NO;
  m_delegateHasConnectionStatus = NO;
  m_delegateHasDirList = NO;
  m_delegateHasDisconnected = NO;
  m_delegateHasEndTransfer = NO;
  m_delegateHasError = NO;
  m_delegateHasHeader = NO;
  m_delegateHasLog = NO;
  m_delegateHasRedirect = NO;
  m_delegateHasResourceProperties = NO;
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
    if ([m_delegate respondsToSelector:@selector(onDirList::::::)]) m_delegateHasDirList = YES;
    if ([m_delegate respondsToSelector:@selector(onDisconnected::)]) m_delegateHasDisconnected = YES;
    if ([m_delegate respondsToSelector:@selector(onEndTransfer:)]) m_delegateHasEndTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onHeader::)]) m_delegateHasHeader = YES;
    if ([m_delegate respondsToSelector:@selector(onLog:::)]) m_delegateHasLog = YES;
    if ([m_delegate respondsToSelector:@selector(onRedirect::)]) m_delegateHasRedirect = YES;
    if ([m_delegate respondsToSelector:@selector(onResourceProperties::)]) m_delegateHasResourceProperties = YES;
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
- (void)onDirList:(NSString*)resourceURI :(NSString*)displayName :(NSString*)contentLanguage :(NSString*)contentLength :(NSString*)contentType :(NSString*)lastModified
{
  if (m_delegate != nil && m_delegateHasDirList)
    [m_delegate onDirList:resourceURI :displayName :contentLanguage :contentLength :contentType :lastModified];
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
- (void)onResourceProperties:(NSString*)resourceURI :(NSString*)resourceProperties
{
  if (m_delegate != nil && m_delegateHasResourceProperties)
    [m_delegate onResourceProperties:resourceURI :resourceProperties];
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
  void* val = IPWorks_WebDAV_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_WebDAV_Get(m_pObj, 0, 0, 0, nil);
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
  void* val=IPWorks_WebDAV_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAccept:(NSString*)newAccept
{
  void *val = (void*)[self nsstringToCString:newAccept];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)authorization
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAuthorization:(NSString*)newAuthorization
{
  void *val = (void*)[self nsstringToCString:newAuthorization];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)authScheme
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAuthScheme:(int)newAuthScheme
{
  void *val = (void*)(long)newAuthScheme;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 3, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)connected
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setConnected:(BOOL)newConnected
{
  void *val = (void*)(long)(newConnected ? 1 : 0);
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)cookieCount
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setCookieCount:(int)newCookieCount
{
  void *val = (void*)(long)newCookieCount;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 5, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookieDomain:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 6, cookieIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieExpiration:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 7, cookieIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieName:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 8, cookieIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieName:(int)cookieIndex:(NSString*)newCookieName
{
  void *val = (void*)[self nsstringToCString:newCookieName];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 8, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookiePath:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 9, cookieIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)cookieSecure:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 10, cookieIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)cookieValue:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 11, cookieIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieValue:(int)cookieIndex:(NSString*)newCookieValue
{
  void *val = (void*)[self nsstringToCString:newCookieValue];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 11, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)depth
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setDepth:(int)newDepth
{
  void *val = (void*)(long)newDepth;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 12, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)firewallAutoDetect
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect
{
  void *val = (void*)(long)(newFirewallAutoDetect ? 1 : 0);
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 13, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallType
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallType:(int)newFirewallType
{
  void *val = (void*)(long)newFirewallType;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 14, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallHost
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallHost:(NSString*)newFirewallHost
{
  void *val = (void*)[self nsstringToCString:newFirewallHost];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallPassword
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallPassword:(NSString*)newFirewallPassword
{
  void *val = (void*)[self nsstringToCString:newFirewallPassword];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallPort
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallPort:(int)newFirewallPort
{
  void *val = (void*)(long)newFirewallPort;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallUser
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallUser:(NSString*)newFirewallUser
{
  void *val = (void*)[self nsstringToCString:newFirewallUser];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 18, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)followRedirects
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFollowRedirects:(int)newFollowRedirects
{
  void *val = (void*)(long)newFollowRedirects;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 19, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)localFile
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalFile:(NSString*)newLocalFile
{
  void *val = (void*)[self nsstringToCString:newLocalFile];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)lockOwner
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLockOwner:(NSString*)newLockOwner
{
  void *val = (void*)[self nsstringToCString:newLockOwner];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 23, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)lockScope
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLockScope:(NSString*)newLockScope
{
  void *val = (void*)[self nsstringToCString:newLockScope];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 24, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)lockTimeout
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setLockTimeout:(int)newLockTimeout
{
  void *val = (void*)(long)newLockTimeout;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 25, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)lockTokens
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLockTokens:(NSString*)newLockTokens
{
  void *val = (void*)[self nsstringToCString:newLockTokens];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 26, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)lockType
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLockType:(NSString*)newLockType
{
  void *val = (void*)[self nsstringToCString:newLockType];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 27, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)namespaceCount
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setNamespaceCount:(int)newNamespaceCount
{
  void *val = (void*)(long)newNamespaceCount;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 28, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)namespacePrefix:(int)namespaceIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 29, namespaceIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setNamespacePrefix:(int)namespaceIndex:(NSString*)newNamespacePrefix
{
  void *val = (void*)[self nsstringToCString:newNamespacePrefix];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 29, namespaceIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)namespaceURI:(int)namespaceIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 30, namespaceIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setNamespaceURI:(int)namespaceIndex:(NSString*)newNamespaceURI
{
  void *val = (void*)[self nsstringToCString:newNamespaceURI];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 30, namespaceIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)otherHeaders
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOtherHeaders:(NSString*)newOtherHeaders
{
  void *val = (void*)[self nsstringToCString:newOtherHeaders];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 31, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)parsedHeaderCount
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)parsedHeaderField:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 33, parsedHeaderIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)parsedHeaderValue:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 34, parsedHeaderIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)password
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 35, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPassword:(NSString*)newPassword
{
  void *val = (void*)[self nsstringToCString:newPassword];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 35, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)propertyCount
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 36, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setPropertyCount:(int)newPropertyCount
{
  void *val = (void*)(long)newPropertyCount;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 36, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)propertyAttr:(int)propertyIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 37, propertyIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPropertyAttr:(int)propertyIndex:(NSString*)newPropertyAttr
{
  void *val = (void*)[self nsstringToCString:newPropertyAttr];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 37, propertyIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)propertyName:(int)propertyIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 38, propertyIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPropertyName:(int)propertyIndex:(NSString*)newPropertyName
{
  void *val = (void*)[self nsstringToCString:newPropertyName];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 38, propertyIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)propertyNamespaceURI:(int)propertyIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 39, propertyIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPropertyNamespaceURI:(int)propertyIndex:(NSString*)newPropertyNamespaceURI
{
  void *val = (void*)[self nsstringToCString:newPropertyNamespaceURI];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 39, propertyIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)propertyOperation:(int)propertyIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 40, propertyIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setPropertyOperation:(int)propertyIndex:(int)newPropertyOperation
{
  void *val = (void*)(long)newPropertyOperation;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 40, propertyIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)propertyStatus:(int)propertyIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 41, propertyIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)propertyValue:(int)propertyIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 42, propertyIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPropertyValue:(int)propertyIndex:(NSString*)newPropertyValue
{
  void *val = (void*)[self nsstringToCString:newPropertyValue];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 42, propertyIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyAuthScheme
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 43, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyAuthScheme:(int)newProxyAuthScheme
{
  void *val = (void*)(long)newProxyAuthScheme;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 43, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)proxyAutoDetect
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 44, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setProxyAutoDetect:(BOOL)newProxyAutoDetect
{
  void *val = (void*)(long)(newProxyAutoDetect ? 1 : 0);
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 44, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyPassword
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 45, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyPassword:(NSString*)newProxyPassword
{
  void *val = (void*)[self nsstringToCString:newProxyPassword];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 45, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyPort
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 46, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyPort:(int)newProxyPort
{
  void *val = (void*)(long)newProxyPort;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 46, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyServer
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 47, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyServer:(NSString*)newProxyServer
{
  void *val = (void*)[self nsstringToCString:newProxyServer];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 47, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxySSL
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 48, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxySSL:(int)newProxySSL
{
  void *val = (void*)(long)newProxySSL;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 48, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyUser
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 49, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyUser:(NSString*)newProxyUser
{
  void *val = (void*)[self nsstringToCString:newProxyUser];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 49, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)referer
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 50, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReferer:(NSString*)newReferer
{
  void *val = (void*)[self nsstringToCString:newReferer];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 50, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)resourceCount
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 51, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)resourceContentLanguage:(int)resourceIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 52, resourceIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)resourceContentLength:(int)resourceIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 53, resourceIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)resourceContentType:(int)resourceIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 54, resourceIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)resourceDisplayName:(int)resourceIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 55, resourceIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)resourceLastModified:(int)resourceIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 56, resourceIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)resourceURI:(int)resourceIndex
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 57, resourceIndex, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)SSLAcceptServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 58, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLAcceptServerCertEncoded];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 58, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLAcceptServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_WebDAV_Get(m_pObj, 58, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded length];
  void *val = (void*)[newSSLAcceptServerCertEncoded bytes];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 58, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 59, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 59, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_WebDAV_Get(m_pObj, 59, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 59, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 60, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 60, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_WebDAV_Get(m_pObj, 60, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 60, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 61, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 61, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 62, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 62, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 63, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 63, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 64, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)SSLServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_WebDAV_Get(m_pObj, 64, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (NSString*)statusLine
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 65, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 66, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 66, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)transferredData
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 67, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)transferredDataB
{
  int len = 0;
  void* val = IPWorks_WebDAV_Get(m_pObj, 67, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (long long)transferredDataLimit
{
  int len = 0;
  long long llVal;
  IPWorks_WebDAV_Get(m_pObj, 68, 0, &len, &llVal);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (void)setTransferredDataLimit:(long long)newTransferredDataLimit
{
  void *val = (void*)&newTransferredDataLimit;
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 68, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)transferredHeaders
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 69, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)user
{
  int len = 0;
  void* val=IPWorks_WebDAV_Get(m_pObj, 70, 0, &len, nil);
  if (IPWorks_WebDAV_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUser:(NSString*)newUser
{
  void *val = (void*)[self nsstringToCString:newUser];
  int ret_code = IPWorks_WebDAV_Set(m_pObj, 70, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (void)addCookie:(NSString*)cookieName :(NSString*)cookieValue
{
  void *param[2+1] = {(void*)[self nsstringToCString:cookieName], (void*)[self nsstringToCString:cookieValue], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 2, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)addNamespace:(NSString*)prefix :(NSString*)namespaceURI
{
  void *param[2+1] = {(void*)[self nsstringToCString:prefix], (void*)[self nsstringToCString:namespaceURI], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 3, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 4, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)copyResource:(NSString*)sourceResourceURI :(NSString*)destinationResourceURI
{
  void *param[2+1] = {(void*)[self nsstringToCString:sourceResourceURI], (void*)[self nsstringToCString:destinationResourceURI], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 5, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)deleteResource:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 6, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 7, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)findProperties:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 8, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)findPropertyNames:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 9, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)getProperty:(NSString*)propertyName
{
  void *param[1+1] = {(void*)[self nsstringToCString:propertyName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 10, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)getResource:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 11, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 12, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)listDirectory:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 13, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)lockResource:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 14, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)makeDirectory:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 15, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)moveResource:(NSString*)sourceResourceURI :(NSString*)destinationResourceURI
{
  void *param[2+1] = {(void*)[self nsstringToCString:sourceResourceURI], (void*)[self nsstringToCString:destinationResourceURI], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 16, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)patchProperties:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 17, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)postToResource:(NSString*)resourceURI :(NSData*)postData
{
  void *param[2+1] = {(void*)[self nsstringToCString:resourceURI], (void*)[postData bytes], NULL};
  int cbparam[2+1] = {0, (int)[postData length], 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 18, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putResource:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 19, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 20, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setProperty:(NSString*)propertyName :(NSString*)propertyValue
{
  void *param[2+1] = {(void*)[self nsstringToCString:propertyName], (void*)[self nsstringToCString:propertyValue], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 22, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)unLockResource:(NSString*)resourceURI
{
  void *param[1+1] = {(void*)[self nsstringToCString:resourceURI], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_WebDAV_Do(m_pObj, 24, 1, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_WebDAV_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_WebDAV_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end