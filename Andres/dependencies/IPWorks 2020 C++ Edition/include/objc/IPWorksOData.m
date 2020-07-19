
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksOData.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksOData()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define OData_EXTERN extern "C"
#else
#define OData_EXTERN extern
#endif

OData_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
OData_EXTERN void* IPWorks_OData_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
OData_EXTERN int   IPWorks_OData_Destroy(void* lpObj);
OData_EXTERN int   IPWorks_OData_CheckIndex(void* lpObj, int propid, int arridx);
OData_EXTERN void* IPWorks_OData_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
OData_EXTERN int   IPWorks_OData_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
OData_EXTERN int   IPWorks_OData_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
OData_EXTERN char* IPWorks_OData_GetLastError(void* lpObj);
OData_EXTERN int   IPWorks_OData_GetLastErrorCode(void* lpObj);
OData_EXTERN int   IPWorks_OData_SetLastErrorAndCode(void* lpObj, int code, char* message);
OData_EXTERN char* IPWorks_OData_GetEventError(void* lpObj);
OData_EXTERN int   IPWorks_OData_GetEventErrorCode(void* lpObj);
OData_EXTERN int   IPWorks_OData_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void OData_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_OData_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int OData_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksOData* ctl = (IPWorksOData*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, OData_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (OData)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
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
    case 2 /*EID_DISCONNECTED*/: {
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
    case 4 /*EID_ENTITY*/: {
      NSString* nameT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* name = nameT;
      @try {
        [ctl onEntity :name];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Entity" :YES];
      }
      break;
    }
    case 5 /*EID_ENTRY*/: {
      NSString* idT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* id = idT;
      NSString* titleT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* title = titleT;
      NSString* summaryT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* summary = summaryT;
      NSString* ETagT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* ETag = ETagT;
      @try {
        [ctl onEntry :id :title :summary :ETag];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Entry" :YES];
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
    case 9 /*EID_PROPERTY*/: {
      NSString* nameT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* name = nameT;
      NSString* typeNameT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* typeName = typeNameT;
      BOOL nullable = param[2] ? YES : NO;
      @try {
        [ctl onProperty :name :typeName :nullable];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Property" :YES];
      }
      break;
    }
    case 10 /*EID_SETCOOKIE*/: {
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
    case 11 /*EID_SSLSERVERAUTHENTICATION*/: {
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
    case 12 /*EID_SSLSTATUS*/: {
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
    case 13 /*EID_STARTTRANSFER*/: {
      int direction = (int)(long)param[0];
      @try {
        [ctl onStartTransfer :direction];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StartTransfer" :YES];
      }
      break;
    }
    case 14 /*EID_STATUS*/: {
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
    case 15 /*EID_TRANSFER*/: {
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

@implementation IPWorksOData

+ (IPWorksOData*)odata
{
#if __has_feature(objc_arc)
  return [[IPWorksOData alloc] init];
#else
  return [[[IPWorksOData alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_OData_Create((void*)OData_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_OData_Create((void*)OData_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_OData_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_OData_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_OData_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_OData_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_OData_GetEventErrorCode(m_pObj);
}

- (id <IPWorksODataDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksODataDelegate>)anObject
{
  m_delegateHasConnected = NO;
  m_delegateHasDisconnected = NO;
  m_delegateHasEndTransfer = NO;
  m_delegateHasEntity = NO;
  m_delegateHasEntry = NO;
  m_delegateHasError = NO;
  m_delegateHasHeader = NO;
  m_delegateHasLog = NO;
  m_delegateHasProperty = NO;
  m_delegateHasSetCookie = NO;
  m_delegateHasSSLServerAuthentication = NO;
  m_delegateHasSSLStatus = NO;
  m_delegateHasStartTransfer = NO;
  m_delegateHasStatus = NO;
  m_delegateHasTransfer = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onConnected::)]) m_delegateHasConnected = YES;
    if ([m_delegate respondsToSelector:@selector(onDisconnected::)]) m_delegateHasDisconnected = YES;
    if ([m_delegate respondsToSelector:@selector(onEndTransfer:)]) m_delegateHasEndTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onEntity:)]) m_delegateHasEntity = YES;
    if ([m_delegate respondsToSelector:@selector(onEntry::::)]) m_delegateHasEntry = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onHeader::)]) m_delegateHasHeader = YES;
    if ([m_delegate respondsToSelector:@selector(onLog:::)]) m_delegateHasLog = YES;
    if ([m_delegate respondsToSelector:@selector(onProperty:::)]) m_delegateHasProperty = YES;
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
- (void)onEntity:(NSString*)name
{
  if (m_delegate != nil && m_delegateHasEntity)
    [m_delegate onEntity:name];
}
- (void)onEntry:(NSString*)id :(NSString*)title :(NSString*)summary :(NSString*)ETag
{
  if (m_delegate != nil && m_delegateHasEntry)
    [m_delegate onEntry:id :title :summary :ETag];
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
- (void)onProperty:(NSString*)name :(NSString*)typeName :(BOOL)nullable
{
  if (m_delegate != nil && m_delegateHasProperty)
    [m_delegate onProperty:name :typeName :nullable];
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
  void* val = IPWorks_OData_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_OData_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_OData_Get(m_pObj, 0, 0, 0, nil);
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

- (NSString*)authorization
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAuthorization:(NSString*)newAuthorization
{
  void *val = (void*)[self nsstringToCString:newAuthorization];
  int ret_code = IPWorks_OData_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)authScheme
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAuthScheme:(int)newAuthScheme
{
  void *val = (void*)(long)newAuthScheme;
  int ret_code = IPWorks_OData_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelAuthorEmail
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelAuthorEmail:(NSString*)newChannelAuthorEmail
{
  void *val = (void*)[self nsstringToCString:newChannelAuthorEmail];
  int ret_code = IPWorks_OData_Set(m_pObj, 3, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelAuthorName
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelAuthorName:(NSString*)newChannelAuthorName
{
  void *val = (void*)[self nsstringToCString:newChannelAuthorName];
  int ret_code = IPWorks_OData_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelAuthorUri
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelAuthorUri:(NSString*)newChannelAuthorUri
{
  void *val = (void*)[self nsstringToCString:newChannelAuthorUri];
  int ret_code = IPWorks_OData_Set(m_pObj, 5, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelCategoryLabel
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelCategoryLabel:(NSString*)newChannelCategoryLabel
{
  void *val = (void*)[self nsstringToCString:newChannelCategoryLabel];
  int ret_code = IPWorks_OData_Set(m_pObj, 6, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelCategoryScheme
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelCategoryScheme:(NSString*)newChannelCategoryScheme
{
  void *val = (void*)[self nsstringToCString:newChannelCategoryScheme];
  int ret_code = IPWorks_OData_Set(m_pObj, 7, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelCategoryTerm
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelCategoryTerm:(NSString*)newChannelCategoryTerm
{
  void *val = (void*)[self nsstringToCString:newChannelCategoryTerm];
  int ret_code = IPWorks_OData_Set(m_pObj, 8, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelContributorEmail
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelContributorEmail:(NSString*)newChannelContributorEmail
{
  void *val = (void*)[self nsstringToCString:newChannelContributorEmail];
  int ret_code = IPWorks_OData_Set(m_pObj, 9, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelContributorName
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelContributorName:(NSString*)newChannelContributorName
{
  void *val = (void*)[self nsstringToCString:newChannelContributorName];
  int ret_code = IPWorks_OData_Set(m_pObj, 10, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelContributorUri
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelContributorUri:(NSString*)newChannelContributorUri
{
  void *val = (void*)[self nsstringToCString:newChannelContributorUri];
  int ret_code = IPWorks_OData_Set(m_pObj, 11, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelGenerator
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelGenerator:(NSString*)newChannelGenerator
{
  void *val = (void*)[self nsstringToCString:newChannelGenerator];
  int ret_code = IPWorks_OData_Set(m_pObj, 12, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelIcon
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelIcon:(NSString*)newChannelIcon
{
  void *val = (void*)[self nsstringToCString:newChannelIcon];
  int ret_code = IPWorks_OData_Set(m_pObj, 13, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelId
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelId:(NSString*)newChannelId
{
  void *val = (void*)[self nsstringToCString:newChannelId];
  int ret_code = IPWorks_OData_Set(m_pObj, 14, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkHref
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkHref:(NSString*)newChannelLinkHref
{
  void *val = (void*)[self nsstringToCString:newChannelLinkHref];
  int ret_code = IPWorks_OData_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkHrefLang
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkHrefLang:(NSString*)newChannelLinkHrefLang
{
  void *val = (void*)[self nsstringToCString:newChannelLinkHrefLang];
  int ret_code = IPWorks_OData_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkLength
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkLength:(NSString*)newChannelLinkLength
{
  void *val = (void*)[self nsstringToCString:newChannelLinkLength];
  int ret_code = IPWorks_OData_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkRel
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkRel:(NSString*)newChannelLinkRel
{
  void *val = (void*)[self nsstringToCString:newChannelLinkRel];
  int ret_code = IPWorks_OData_Set(m_pObj, 18, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkTitle
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkTitle:(NSString*)newChannelLinkTitle
{
  void *val = (void*)[self nsstringToCString:newChannelLinkTitle];
  int ret_code = IPWorks_OData_Set(m_pObj, 19, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLinkType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLinkType:(NSString*)newChannelLinkType
{
  void *val = (void*)[self nsstringToCString:newChannelLinkType];
  int ret_code = IPWorks_OData_Set(m_pObj, 20, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelLogo
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelLogo:(NSString*)newChannelLogo
{
  void *val = (void*)[self nsstringToCString:newChannelLogo];
  int ret_code = IPWorks_OData_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelRights
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelRights:(NSString*)newChannelRights
{
  void *val = (void*)[self nsstringToCString:newChannelRights];
  int ret_code = IPWorks_OData_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)channelRightsTextType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setChannelRightsTextType:(int)newChannelRightsTextType
{
  void *val = (void*)(long)newChannelRightsTextType;
  int ret_code = IPWorks_OData_Set(m_pObj, 23, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelSubtitle
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelSubtitle:(NSString*)newChannelSubtitle
{
  void *val = (void*)[self nsstringToCString:newChannelSubtitle];
  int ret_code = IPWorks_OData_Set(m_pObj, 24, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)channelSubtitleTextType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setChannelSubtitleTextType:(int)newChannelSubtitleTextType
{
  void *val = (void*)(long)newChannelSubtitleTextType;
  int ret_code = IPWorks_OData_Set(m_pObj, 25, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelTitle
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelTitle:(NSString*)newChannelTitle
{
  void *val = (void*)[self nsstringToCString:newChannelTitle];
  int ret_code = IPWorks_OData_Set(m_pObj, 26, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)channelTitleTextType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setChannelTitleTextType:(int)newChannelTitleTextType
{
  void *val = (void*)(long)newChannelTitleTextType;
  int ret_code = IPWorks_OData_Set(m_pObj, 27, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)channelUpdated
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setChannelUpdated:(NSString*)newChannelUpdated
{
  void *val = (void*)[self nsstringToCString:newChannelUpdated];
  int ret_code = IPWorks_OData_Set(m_pObj, 28, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)cookieCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 29, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setCookieCount:(int)newCookieCount
{
  void *val = (void*)(long)newCookieCount;
  int ret_code = IPWorks_OData_Set(m_pObj, 29, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookieDomain:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 30, cookieIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieExpiration:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 31, cookieIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieName:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 32, cookieIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieName:(int)cookieIndex:(NSString*)newCookieName
{
  void *val = (void*)[self nsstringToCString:newCookieName];
  int ret_code = IPWorks_OData_Set(m_pObj, 32, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookiePath:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 33, cookieIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)cookieSecure:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 34, cookieIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)cookieValue:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 35, cookieIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieValue:(int)cookieIndex:(NSString*)newCookieValue
{
  void *val = (void*)[self nsstringToCString:newCookieValue];
  int ret_code = IPWorks_OData_Set(m_pObj, 35, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryAuthor
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 36, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryAuthor:(NSString*)newEntryAuthor
{
  void *val = (void*)[self nsstringToCString:newEntryAuthor];
  int ret_code = IPWorks_OData_Set(m_pObj, 36, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)entryCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 37, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)entryETag
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 38, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryETag:(NSString*)newEntryETag
{
  void *val = (void*)[self nsstringToCString:newEntryETag];
  int ret_code = IPWorks_OData_Set(m_pObj, 38, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryId
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 39, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryId:(NSString*)newEntryId
{
  void *val = (void*)[self nsstringToCString:newEntryId];
  int ret_code = IPWorks_OData_Set(m_pObj, 39, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)entryIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 40, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setEntryIndex:(int)newEntryIndex
{
  void *val = (void*)(long)newEntryIndex;
  int ret_code = IPWorks_OData_Set(m_pObj, 40, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)entryLinksCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 41, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setEntryLinksCount:(int)newEntryLinksCount
{
  void *val = (void*)(long)newEntryLinksCount;
  int ret_code = IPWorks_OData_Set(m_pObj, 41, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryLinksResourcePath:(int)entryLinksIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 42, entryLinksIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)entryLinksTitle:(int)entryLinksIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 43, entryLinksIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)entryPropertiesCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 44, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setEntryPropertiesCount:(int)newEntryPropertiesCount
{
  void *val = (void*)(long)newEntryPropertiesCount;
  int ret_code = IPWorks_OData_Set(m_pObj, 44, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryPropertiesAttributes:(int)entryPropertiesIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 45, entryPropertiesIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryPropertiesAttributes:(int)entryPropertiesIndex:(NSString*)newEntryPropertiesAttributes
{
  void *val = (void*)[self nsstringToCString:newEntryPropertiesAttributes];
  int ret_code = IPWorks_OData_Set(m_pObj, 45, entryPropertiesIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)entryPropertiesIsNull:(int)entryPropertiesIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 46, entryPropertiesIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setEntryPropertiesIsNull:(int)entryPropertiesIndex:(BOOL)newEntryPropertiesIsNull
{
  void *val = (void*)(long)(newEntryPropertiesIsNull ? 1 : 0);
  int ret_code = IPWorks_OData_Set(m_pObj, 46, entryPropertiesIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryPropertiesName:(int)entryPropertiesIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 47, entryPropertiesIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryPropertiesName:(int)entryPropertiesIndex:(NSString*)newEntryPropertiesName
{
  void *val = (void*)[self nsstringToCString:newEntryPropertiesName];
  int ret_code = IPWorks_OData_Set(m_pObj, 47, entryPropertiesIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryPropertiesType:(int)entryPropertiesIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 48, entryPropertiesIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryPropertiesType:(int)entryPropertiesIndex:(NSString*)newEntryPropertiesType
{
  void *val = (void*)[self nsstringToCString:newEntryPropertiesType];
  int ret_code = IPWorks_OData_Set(m_pObj, 48, entryPropertiesIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryPropertiesValue:(int)entryPropertiesIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 49, entryPropertiesIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryPropertiesValue:(int)entryPropertiesIndex:(NSString*)newEntryPropertiesValue
{
  void *val = (void*)[self nsstringToCString:newEntryPropertiesValue];
  int ret_code = IPWorks_OData_Set(m_pObj, 49, entryPropertiesIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryPropertiesXPath:(int)entryPropertiesIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 50, entryPropertiesIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)entrySummary
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 51, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntrySummary:(NSString*)newEntrySummary
{
  void *val = (void*)[self nsstringToCString:newEntrySummary];
  int ret_code = IPWorks_OData_Set(m_pObj, 51, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryTitle
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 52, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryTitle:(NSString*)newEntryTitle
{
  void *val = (void*)[self nsstringToCString:newEntryTitle];
  int ret_code = IPWorks_OData_Set(m_pObj, 52, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 53, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryType:(NSString*)newEntryType
{
  void *val = (void*)[self nsstringToCString:newEntryType];
  int ret_code = IPWorks_OData_Set(m_pObj, 53, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)entryUpdated
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 54, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)entryXML
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 55, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setEntryXML:(NSString*)newEntryXML
{
  void *val = (void*)[self nsstringToCString:newEntryXML];
  int ret_code = IPWorks_OData_Set(m_pObj, 55, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)firewallAutoDetect
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 56, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect
{
  void *val = (void*)(long)(newFirewallAutoDetect ? 1 : 0);
  int ret_code = IPWorks_OData_Set(m_pObj, 56, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 57, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallType:(int)newFirewallType
{
  void *val = (void*)(long)newFirewallType;
  int ret_code = IPWorks_OData_Set(m_pObj, 57, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallHost
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 58, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallHost:(NSString*)newFirewallHost
{
  void *val = (void*)[self nsstringToCString:newFirewallHost];
  int ret_code = IPWorks_OData_Set(m_pObj, 58, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallPassword
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 59, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallPassword:(NSString*)newFirewallPassword
{
  void *val = (void*)[self nsstringToCString:newFirewallPassword];
  int ret_code = IPWorks_OData_Set(m_pObj, 59, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallPort
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 60, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallPort:(int)newFirewallPort
{
  void *val = (void*)(long)newFirewallPort;
  int ret_code = IPWorks_OData_Set(m_pObj, 60, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallUser
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 61, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallUser:(NSString*)newFirewallUser
{
  void *val = (void*)[self nsstringToCString:newFirewallUser];
  int ret_code = IPWorks_OData_Set(m_pObj, 61, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 62, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 63, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_OData_Set(m_pObj, 63, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)ODataVersion
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 64, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setODataVersion:(int)newODataVersion
{
  void *val = (void*)(long)newODataVersion;
  int ret_code = IPWorks_OData_Set(m_pObj, 64, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)otherHeaders
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 65, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOtherHeaders:(NSString*)newOtherHeaders
{
  void *val = (void*)[self nsstringToCString:newOtherHeaders];
  int ret_code = IPWorks_OData_Set(m_pObj, 65, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)otherQueryOptions
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 66, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOtherQueryOptions:(NSString*)newOtherQueryOptions
{
  void *val = (void*)[self nsstringToCString:newOtherQueryOptions];
  int ret_code = IPWorks_OData_Set(m_pObj, 66, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)parsedHeaderCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 67, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)parsedHeaderField:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 68, parsedHeaderIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)parsedHeaderValue:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 69, parsedHeaderIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)password
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 70, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPassword:(NSString*)newPassword
{
  void *val = (void*)[self nsstringToCString:newPassword];
  int ret_code = IPWorks_OData_Set(m_pObj, 70, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyAuthScheme
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 71, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyAuthScheme:(int)newProxyAuthScheme
{
  void *val = (void*)(long)newProxyAuthScheme;
  int ret_code = IPWorks_OData_Set(m_pObj, 71, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)proxyAutoDetect
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 72, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setProxyAutoDetect:(BOOL)newProxyAutoDetect
{
  void *val = (void*)(long)(newProxyAutoDetect ? 1 : 0);
  int ret_code = IPWorks_OData_Set(m_pObj, 72, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyPassword
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 73, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyPassword:(NSString*)newProxyPassword
{
  void *val = (void*)[self nsstringToCString:newProxyPassword];
  int ret_code = IPWorks_OData_Set(m_pObj, 73, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyPort
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 74, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyPort:(int)newProxyPort
{
  void *val = (void*)(long)newProxyPort;
  int ret_code = IPWorks_OData_Set(m_pObj, 74, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyServer
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 75, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyServer:(NSString*)newProxyServer
{
  void *val = (void*)[self nsstringToCString:newProxyServer];
  int ret_code = IPWorks_OData_Set(m_pObj, 75, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxySSL
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 76, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxySSL:(int)newProxySSL
{
  void *val = (void*)(long)newProxySSL;
  int ret_code = IPWorks_OData_Set(m_pObj, 76, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyUser
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 77, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyUser:(NSString*)newProxyUser
{
  void *val = (void*)[self nsstringToCString:newProxyUser];
  int ret_code = IPWorks_OData_Set(m_pObj, 77, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)queryFilter
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 78, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setQueryFilter:(NSString*)newQueryFilter
{
  void *val = (void*)[self nsstringToCString:newQueryFilter];
  int ret_code = IPWorks_OData_Set(m_pObj, 78, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)queryOrderBy
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 79, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setQueryOrderBy:(NSString*)newQueryOrderBy
{
  void *val = (void*)[self nsstringToCString:newQueryOrderBy];
  int ret_code = IPWorks_OData_Set(m_pObj, 79, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)querySelect
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 80, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setQuerySelect:(NSString*)newQuerySelect
{
  void *val = (void*)[self nsstringToCString:newQuerySelect];
  int ret_code = IPWorks_OData_Set(m_pObj, 80, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)querySkip
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 81, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setQuerySkip:(NSString*)newQuerySkip
{
  void *val = (void*)[self nsstringToCString:newQuerySkip];
  int ret_code = IPWorks_OData_Set(m_pObj, 81, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)querySkipToken
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 82, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setQuerySkipToken:(NSString*)newQuerySkipToken
{
  void *val = (void*)[self nsstringToCString:newQuerySkipToken];
  int ret_code = IPWorks_OData_Set(m_pObj, 82, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)queryTop
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 83, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setQueryTop:(NSString*)newQueryTop
{
  void *val = (void*)[self nsstringToCString:newQueryTop];
  int ret_code = IPWorks_OData_Set(m_pObj, 83, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)resourcePath
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 84, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setResourcePath:(NSString*)newResourcePath
{
  void *val = (void*)[self nsstringToCString:newResourcePath];
  int ret_code = IPWorks_OData_Set(m_pObj, 84, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)schemaAssociationContainsTarget
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 85, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)schemaAssociationDescription
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 86, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationFromRole
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 87, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationFromRoleDescription
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 88, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationFromRoleEntity
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 89, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)schemaAssociationFromRoleMultiplicity
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 90, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)schemaAssociationFromRoleSummary
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 91, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationName
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 92, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)schemaAssociationNullable
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 93, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (int)schemaAssociationOnDelete
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 94, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)schemaAssociationPartner
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 95, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)schemaAssociationRefConstraintCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 96, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)schemaAssociationRefConstraintIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 97, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSchemaAssociationRefConstraintIndex:(int)newSchemaAssociationRefConstraintIndex
{
  void *val = (void*)(long)newSchemaAssociationRefConstraintIndex;
  int ret_code = IPWorks_OData_Set(m_pObj, 97, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)schemaAssociationRefConstraintProperty
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 98, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationRefConstraintReferencedProperty
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 99, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationRelationship
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 100, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationSummary
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 101, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationToRole
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 102, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationToRoleDescription
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 103, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationToRoleEntity
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 104, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)schemaAssociationToRoleMultiplicity
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 105, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)schemaAssociationToRoleSummary
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 106, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaAssociationType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 107, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)schemaAssociationCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 108, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)schemaAssociationIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 109, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSchemaAssociationIndex:(int)newSchemaAssociationIndex
{
  void *val = (void*)(long)newSchemaAssociationIndex;
  int ret_code = IPWorks_OData_Set(m_pObj, 109, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)schemaEntityDescription
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 110, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaEntityName
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 111, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaEntitySummary
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 112, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)schemaEntityCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 113, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)schemaEntityIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 114, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSchemaEntityIndex:(int)newSchemaEntityIndex
{
  void *val = (void*)(long)newSchemaEntityIndex;
  int ret_code = IPWorks_OData_Set(m_pObj, 114, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)schemaKeysCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 115, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)schemaKeys:(int)schemaKeysIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 116, schemaKeysIndex, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaPropertyAttributes
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 117, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaPropertyDescription
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 118, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)schemaPropertyIsComplexType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 119, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)schemaPropertyName
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 120, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)schemaPropertyNullable
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 121, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)schemaPropertySummary
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 122, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaPropertyType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 123, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)schemaPropertyCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 124, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)schemaPropertyIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 125, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSchemaPropertyIndex:(int)newSchemaPropertyIndex
{
  void *val = (void*)(long)newSchemaPropertyIndex;
  int ret_code = IPWorks_OData_Set(m_pObj, 125, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)schemaTypeFieldAttributes
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 126, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaTypeFieldDescription
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 127, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)schemaTypeFieldIsComplexType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 128, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)schemaTypeFieldName
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 129, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)schemaTypeFieldNullable
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 130, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)schemaTypeFieldSummary
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 131, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)schemaTypeFieldType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 132, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)schemaTypeFieldCount
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 133, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (int)schemaTypeFieldIndex
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 134, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSchemaTypeFieldIndex:(int)newSchemaTypeFieldIndex
{
  void *val = (void*)(long)newSchemaTypeFieldIndex;
  int ret_code = IPWorks_OData_Set(m_pObj, 134, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)serviceRootURI
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 135, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setServiceRootURI:(NSString*)newServiceRootURI
{
  void *val = (void*)[self nsstringToCString:newServiceRootURI];
  int ret_code = IPWorks_OData_Set(m_pObj, 135, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLAcceptServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 136, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLAcceptServerCertEncoded];
  int ret_code = IPWorks_OData_Set(m_pObj, 136, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLAcceptServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_OData_Get(m_pObj, 136, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded length];
  void *val = (void*)[newSSLAcceptServerCertEncoded bytes];
  int ret_code = IPWorks_OData_Set(m_pObj, 136, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 137, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_OData_Set(m_pObj, 137, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_OData_Get(m_pObj, 137, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_OData_Set(m_pObj, 137, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 138, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_OData_Set(m_pObj, 138, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_OData_Get(m_pObj, 138, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_OData_Set(m_pObj, 138, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 139, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_OData_Set(m_pObj, 139, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 140, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_OData_Set(m_pObj, 140, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 141, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_OData_Set(m_pObj, 141, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 142, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)SSLServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_OData_Get(m_pObj, 142, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 143, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_OData_Set(m_pObj, 143, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)transferredData
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 144, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)transferredDataB
{
  int len = 0;
  void* val = IPWorks_OData_Get(m_pObj, 144, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (NSString*)user
{
  int len = 0;
  void* val=IPWorks_OData_Get(m_pObj, 145, 0, &len, nil);
  if (IPWorks_OData_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUser:(NSString*)newUser
{
  void *val = (void*)[self nsstringToCString:newUser];
  int ret_code = IPWorks_OData_Set(m_pObj, 145, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_OData_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)createEntry
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_OData_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)customRequest:(NSString*)HTTPMethod :(NSString*)URL :(NSString*)postData
{
  void *param[3+1] = {(void*)[self nsstringToCString:HTTPMethod], (void*)[self nsstringToCString:URL], (void*)[self nsstringToCString:postData], NULL};
  int cbparam[3+1] = {0, 0, 0, 0};

  int ret_code = IPWorks_OData_Do(m_pObj, 4, 3, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)deleteEntry
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_OData_Do(m_pObj, 5, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)getEntryProperty:(NSString*)XPath
{
  void *param[1+1] = {(void*)[self nsstringToCString:XPath], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_OData_Do(m_pObj, 6, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)getSchema
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_OData_Do(m_pObj, 7, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)hasXPath:(NSString*)XPath
{
  void *param[1+1] = {(void*)[self nsstringToCString:XPath], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_OData_Do(m_pObj, 8, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return param[1] ? YES : NO;
}

- (void)queryService
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_OData_Do(m_pObj, 9, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_OData_Do(m_pObj, 10, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setEntryProperty:(NSString*)XPath :(NSString*)value
{
  void *param[2+1] = {(void*)[self nsstringToCString:XPath], (void*)[self nsstringToCString:value], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_OData_Do(m_pObj, 11, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setSchemaEntity:(NSString*)name
{
  void *param[1+1] = {(void*)[self nsstringToCString:name], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_OData_Do(m_pObj, 12, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setSchemaProperty:(NSString*)name
{
  void *param[1+1] = {(void*)[self nsstringToCString:name], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_OData_Do(m_pObj, 13, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setSchemaType:(NSString*)name
{
  void *param[1+1] = {(void*)[self nsstringToCString:name], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_OData_Do(m_pObj, 14, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)updateEntry
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_OData_Do(m_pObj, 15, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)updateProperty:(NSString*)XPath :(NSString*)value
{
  void *param[2+1] = {(void*)[self nsstringToCString:XPath], (void*)[self nsstringToCString:value], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_OData_Do(m_pObj, 16, 2, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_OData_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_OData_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end