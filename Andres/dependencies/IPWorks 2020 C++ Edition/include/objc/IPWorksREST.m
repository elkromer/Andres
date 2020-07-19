
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksREST.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksREST()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define REST_EXTERN extern "C"
#else
#define REST_EXTERN extern
#endif

REST_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
REST_EXTERN void* IPWorks_REST_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
REST_EXTERN int   IPWorks_REST_Destroy(void* lpObj);
REST_EXTERN int   IPWorks_REST_CheckIndex(void* lpObj, int propid, int arridx);
REST_EXTERN void* IPWorks_REST_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
REST_EXTERN int   IPWorks_REST_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
REST_EXTERN int   IPWorks_REST_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
REST_EXTERN char* IPWorks_REST_GetLastError(void* lpObj);
REST_EXTERN int   IPWorks_REST_GetLastErrorCode(void* lpObj);
REST_EXTERN int   IPWorks_REST_SetLastErrorAndCode(void* lpObj, int code, char* message);
REST_EXTERN char* IPWorks_REST_GetEventError(void* lpObj);
REST_EXTERN int   IPWorks_REST_GetEventErrorCode(void* lpObj);
REST_EXTERN int   IPWorks_REST_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void REST_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_REST_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int REST_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksREST* ctl = (IPWorksREST*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, REST_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (REST)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
      [myAlert show];
      return 1;
#else // TARGET_OS_IPHONE
      return 0;
#endif // TARGET_OS_IPHONE
    }

    case 1 /*EID_CHARACTERS*/: {
      NSString* textT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* text = textT;
      @try {
        [ctl onCharacters :text];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Characters" :YES];
      }
      break;
    }
    case 2 /*EID_COMMENT*/: {
      NSString* textT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* text = textT;
      @try {
        [ctl onComment :text];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Comment" :YES];
      }
      break;
    }
    case 3 /*EID_CONNECTED*/: {
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
    case 4 /*EID_CONNECTIONSTATUS*/: {
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
    case 5 /*EID_DISCONNECTED*/: {
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
    case 6 /*EID_ENDELEMENT*/: {
      NSString* namespaceT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* namespace = namespaceT;
      NSString* elementT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* element = elementT;
      NSString* QNameT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* QName = QNameT;
      BOOL isEmpty = param[3] ? YES : NO;
      @try {
        [ctl onEndElement :namespace :element :QName :isEmpty];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EndElement" :YES];
      }
      break;
    }
    case 7 /*EID_ENDPREFIXMAPPING*/: {
      NSString* prefixT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* prefix = prefixT;
      @try {
        [ctl onEndPrefixMapping :prefix];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EndPrefixMapping" :YES];
      }
      break;
    }
    case 8 /*EID_ENDTRANSFER*/: {
      int direction = (int)(long)param[0];
      @try {
        [ctl onEndTransfer :direction];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EndTransfer" :YES];
      }
      break;
    }
    case 9 /*EID_ERROR*/: {
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
    case 10 /*EID_EVALENTITY*/: {
      NSString* entityT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* entity = entityT;
      NSString* valueT = [NSString stringWithCString:(const char*)IPWorks_EvtStr(param[1], 0, nil, 1) encoding:[ctl innerGetCodePage]];
#if __has_feature(objc_arc)
      __autoreleasing NSString*  valueTA = valueT;
      __autoreleasing NSString** value = &valueTA;
#else
      NSString** value = &valueT;
#endif
      @try {
        [ctl onEvalEntity :entity :value];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EvalEntity" :YES];
      }
      IPWorks_EvtStr(param[1], 2, (void*)([ctl nsstringToCString:*value]), 1);
      break;
    }
    case 11 /*EID_HEADER*/: {
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
    case 12 /*EID_IGNORABLEWHITESPACE*/: {
      NSString* textT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* text = textT;
      @try {
        [ctl onIgnorableWhitespace :text];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"IgnorableWhitespace" :YES];
      }
      break;
    }
    case 13 /*EID_LOG*/: {
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
    case 14 /*EID_META*/: {
      NSString* textT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* text = textT;
      @try {
        [ctl onMeta :text];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Meta" :YES];
      }
      break;
    }
    case 15 /*EID_PI*/: {
      NSString* textT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* text = textT;
      @try {
        [ctl onPI :text];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"PI" :YES];
      }
      break;
    }
    case 16 /*EID_REDIRECT*/: {
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
    case 17 /*EID_SETCOOKIE*/: {
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
    case 18 /*EID_SPECIALSECTION*/: {
      NSString* sectionIdT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* sectionId = sectionIdT;
      NSString* textT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* text = textT;
      @try {
        [ctl onSpecialSection :sectionId :text];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SpecialSection" :YES];
      }
      break;
    }
    case 19 /*EID_SSLSERVERAUTHENTICATION*/: {
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
    case 20 /*EID_SSLSTATUS*/: {
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
    case 21 /*EID_STARTELEMENT*/: {
      NSString* namespaceT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* namespace = namespaceT;
      NSString* elementT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* element = elementT;
      NSString* QNameT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* QName = QNameT;
      BOOL isEmpty = param[3] ? YES : NO;
      @try {
        [ctl onStartElement :namespace :element :QName :isEmpty];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StartElement" :YES];
      }
      break;
    }
    case 22 /*EID_STARTPREFIXMAPPING*/: {
      NSString* prefixT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* prefix = prefixT;
      NSString* URIT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* URI = URIT;
      @try {
        [ctl onStartPrefixMapping :prefix :URI];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StartPrefixMapping" :YES];
      }
      break;
    }
    case 23 /*EID_STARTTRANSFER*/: {
      int direction = (int)(long)param[0];
      @try {
        [ctl onStartTransfer :direction];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StartTransfer" :YES];
      }
      break;
    }
    case 24 /*EID_STATUS*/: {
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
    case 25 /*EID_TRANSFER*/: {
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

@implementation IPWorksREST

+ (IPWorksREST*)rest
{
#if __has_feature(objc_arc)
  return [[IPWorksREST alloc] init];
#else
  return [[[IPWorksREST alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_REST_Create((void*)REST_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_REST_Create((void*)REST_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_REST_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_REST_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_REST_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_REST_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_REST_GetEventErrorCode(m_pObj);
}

- (id <IPWorksRESTDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksRESTDelegate>)anObject
{
  m_delegateHasCharacters = NO;
  m_delegateHasComment = NO;
  m_delegateHasConnected = NO;
  m_delegateHasConnectionStatus = NO;
  m_delegateHasDisconnected = NO;
  m_delegateHasEndElement = NO;
  m_delegateHasEndPrefixMapping = NO;
  m_delegateHasEndTransfer = NO;
  m_delegateHasError = NO;
  m_delegateHasEvalEntity = NO;
  m_delegateHasHeader = NO;
  m_delegateHasIgnorableWhitespace = NO;
  m_delegateHasLog = NO;
  m_delegateHasMeta = NO;
  m_delegateHasPI = NO;
  m_delegateHasRedirect = NO;
  m_delegateHasSetCookie = NO;
  m_delegateHasSpecialSection = NO;
  m_delegateHasSSLServerAuthentication = NO;
  m_delegateHasSSLStatus = NO;
  m_delegateHasStartElement = NO;
  m_delegateHasStartPrefixMapping = NO;
  m_delegateHasStartTransfer = NO;
  m_delegateHasStatus = NO;
  m_delegateHasTransfer = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onCharacters:)]) m_delegateHasCharacters = YES;
    if ([m_delegate respondsToSelector:@selector(onComment:)]) m_delegateHasComment = YES;
    if ([m_delegate respondsToSelector:@selector(onConnected::)]) m_delegateHasConnected = YES;
    if ([m_delegate respondsToSelector:@selector(onConnectionStatus:::)]) m_delegateHasConnectionStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onDisconnected::)]) m_delegateHasDisconnected = YES;
    if ([m_delegate respondsToSelector:@selector(onEndElement::::)]) m_delegateHasEndElement = YES;
    if ([m_delegate respondsToSelector:@selector(onEndPrefixMapping:)]) m_delegateHasEndPrefixMapping = YES;
    if ([m_delegate respondsToSelector:@selector(onEndTransfer:)]) m_delegateHasEndTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onEvalEntity::)]) m_delegateHasEvalEntity = YES;
    if ([m_delegate respondsToSelector:@selector(onHeader::)]) m_delegateHasHeader = YES;
    if ([m_delegate respondsToSelector:@selector(onIgnorableWhitespace:)]) m_delegateHasIgnorableWhitespace = YES;
    if ([m_delegate respondsToSelector:@selector(onLog:::)]) m_delegateHasLog = YES;
    if ([m_delegate respondsToSelector:@selector(onMeta:)]) m_delegateHasMeta = YES;
    if ([m_delegate respondsToSelector:@selector(onPI:)]) m_delegateHasPI = YES;
    if ([m_delegate respondsToSelector:@selector(onRedirect::)]) m_delegateHasRedirect = YES;
    if ([m_delegate respondsToSelector:@selector(onSetCookie::::::)]) m_delegateHasSetCookie = YES;
    if ([m_delegate respondsToSelector:@selector(onSpecialSection::)]) m_delegateHasSpecialSection = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLServerAuthentication:::::)]) m_delegateHasSSLServerAuthentication = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLStatus:)]) m_delegateHasSSLStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onStartElement::::)]) m_delegateHasStartElement = YES;
    if ([m_delegate respondsToSelector:@selector(onStartPrefixMapping::)]) m_delegateHasStartPrefixMapping = YES;
    if ([m_delegate respondsToSelector:@selector(onStartTransfer:)]) m_delegateHasStartTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onStatus:::)]) m_delegateHasStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onTransfer::::)]) m_delegateHasTransfer = YES;
  }
}

  /* Events */

- (void)onCharacters:(NSString*)text
{
  if (m_delegate != nil && m_delegateHasCharacters)
    [m_delegate onCharacters:text];
}
- (void)onComment:(NSString*)text
{
  if (m_delegate != nil && m_delegateHasComment)
    [m_delegate onComment:text];
}
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
- (void)onEndElement:(NSString*)namespace :(NSString*)element :(NSString*)QName :(BOOL)isEmpty
{
  if (m_delegate != nil && m_delegateHasEndElement)
    [m_delegate onEndElement:namespace :element :QName :isEmpty];
}
- (void)onEndPrefixMapping:(NSString*)prefix
{
  if (m_delegate != nil && m_delegateHasEndPrefixMapping)
    [m_delegate onEndPrefixMapping:prefix];
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
- (void)onEvalEntity:(NSString*)entity :(NSString**)value
{
  if (m_delegate != nil && m_delegateHasEvalEntity)
    [m_delegate onEvalEntity:entity :value];
}
- (void)onHeader:(NSString*)field :(NSString*)value
{
  if (m_delegate != nil && m_delegateHasHeader)
    [m_delegate onHeader:field :value];
}
- (void)onIgnorableWhitespace:(NSString*)text
{
  if (m_delegate != nil && m_delegateHasIgnorableWhitespace)
    [m_delegate onIgnorableWhitespace:text];
}
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType
{
  if (m_delegate != nil && m_delegateHasLog)
    [m_delegate onLog:logLevel :message :logType];
}
- (void)onMeta:(NSString*)text
{
  if (m_delegate != nil && m_delegateHasMeta)
    [m_delegate onMeta:text];
}
- (void)onPI:(NSString*)text
{
  if (m_delegate != nil && m_delegateHasPI)
    [m_delegate onPI:text];
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
- (void)onSpecialSection:(NSString*)sectionId :(NSString*)text
{
  if (m_delegate != nil && m_delegateHasSpecialSection)
    [m_delegate onSpecialSection:sectionId :text];
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
- (void)onStartElement:(NSString*)namespace :(NSString*)element :(NSString*)QName :(BOOL)isEmpty
{
  if (m_delegate != nil && m_delegateHasStartElement)
    [m_delegate onStartElement:namespace :element :QName :isEmpty];
}
- (void)onStartPrefixMapping:(NSString*)prefix :(NSString*)URI
{
  if (m_delegate != nil && m_delegateHasStartPrefixMapping)
    [m_delegate onStartPrefixMapping:prefix :URI];
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
  void* val = IPWorks_REST_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_REST_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_REST_Get(m_pObj, 0, 0, 0, nil);
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
  void* val=IPWorks_REST_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAccept:(NSString*)newAccept
{
  void *val = (void*)[self nsstringToCString:newAccept];
  int ret_code = IPWorks_REST_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)authorization
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAuthorization:(NSString*)newAuthorization
{
  void *val = (void*)[self nsstringToCString:newAuthorization];
  int ret_code = IPWorks_REST_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)authScheme
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAuthScheme:(int)newAuthScheme
{
  void *val = (void*)(long)newAuthScheme;
  int ret_code = IPWorks_REST_Set(m_pObj, 3, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)buildDOM
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setBuildDOM:(BOOL)newBuildDOM
{
  void *val = (void*)(long)(newBuildDOM ? 1 : 0);
  int ret_code = IPWorks_REST_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)connected
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setConnected:(BOOL)newConnected
{
  void *val = (void*)(long)(newConnected ? 1 : 0);
  int ret_code = IPWorks_REST_Set(m_pObj, 5, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)contentType
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setContentType:(NSString*)newContentType
{
  void *val = (void*)[self nsstringToCString:newContentType];
  int ret_code = IPWorks_REST_Set(m_pObj, 6, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)cookieCount
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setCookieCount:(int)newCookieCount
{
  void *val = (void*)(long)newCookieCount;
  int ret_code = IPWorks_REST_Set(m_pObj, 7, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookieDomain:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 8, cookieIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieExpiration:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 9, cookieIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)cookieName:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 10, cookieIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieName:(int)cookieIndex:(NSString*)newCookieName
{
  void *val = (void*)[self nsstringToCString:newCookieName];
  int ret_code = IPWorks_REST_Set(m_pObj, 10, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)cookiePath:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 11, cookieIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (BOOL)cookieSecure:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 12, cookieIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)cookieValue:(int)cookieIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 13, cookieIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setCookieValue:(int)cookieIndex:(NSString*)newCookieValue
{
  void *val = (void*)[self nsstringToCString:newCookieValue];
  int ret_code = IPWorks_REST_Set(m_pObj, 13, cookieIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)firewallAutoDetect
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect
{
  void *val = (void*)(long)(newFirewallAutoDetect ? 1 : 0);
  int ret_code = IPWorks_REST_Set(m_pObj, 14, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallType
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallType:(int)newFirewallType
{
  void *val = (void*)(long)newFirewallType;
  int ret_code = IPWorks_REST_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallHost
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallHost:(NSString*)newFirewallHost
{
  void *val = (void*)[self nsstringToCString:newFirewallHost];
  int ret_code = IPWorks_REST_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallPassword
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallPassword:(NSString*)newFirewallPassword
{
  void *val = (void*)[self nsstringToCString:newFirewallPassword];
  int ret_code = IPWorks_REST_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallPort
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallPort:(int)newFirewallPort
{
  void *val = (void*)(long)newFirewallPort;
  int ret_code = IPWorks_REST_Set(m_pObj, 18, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallUser
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallUser:(NSString*)newFirewallUser
{
  void *val = (void*)[self nsstringToCString:newFirewallUser];
  int ret_code = IPWorks_REST_Set(m_pObj, 19, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)followRedirects
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFollowRedirects:(int)newFollowRedirects
{
  void *val = (void*)(long)newFollowRedirects;
  int ret_code = IPWorks_REST_Set(m_pObj, 20, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)from
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFrom:(NSString*)newFrom
{
  void *val = (void*)[self nsstringToCString:newFrom];
  int ret_code = IPWorks_REST_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)HTTPMethod
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setHTTPMethod:(NSString*)newHTTPMethod
{
  void *val = (void*)[self nsstringToCString:newHTTPMethod];
  int ret_code = IPWorks_REST_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)ifModifiedSince
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setIfModifiedSince:(NSString*)newIfModifiedSince
{
  void *val = (void*)[self nsstringToCString:newIfModifiedSince];
  int ret_code = IPWorks_REST_Set(m_pObj, 24, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localFile
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalFile:(NSString*)newLocalFile
{
  void *val = (void*)[self nsstringToCString:newLocalFile];
  int ret_code = IPWorks_REST_Set(m_pObj, 25, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_REST_Set(m_pObj, 26, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)namespaceCount
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)namespacePrefix:(int)namespaceIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 28, namespaceIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)namespaceURI:(int)namespaceIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 29, namespaceIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)otherHeaders
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOtherHeaders:(NSString*)newOtherHeaders
{
  void *val = (void*)[self nsstringToCString:newOtherHeaders];
  int ret_code = IPWorks_REST_Set(m_pObj, 30, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)parsedHeaderCount
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)parsedHeaderField:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 32, parsedHeaderIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)parsedHeaderValue:(int)parsedHeaderIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 33, parsedHeaderIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)password
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 34, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPassword:(NSString*)newPassword
{
  void *val = (void*)[self nsstringToCString:newPassword];
  int ret_code = IPWorks_REST_Set(m_pObj, 34, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)postData
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 35, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setPostData:(NSString*)newPostData
{
  int len = (int)[newPostData lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newPostData];
  int ret_code = IPWorks_REST_Set(m_pObj, 35, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)postDataB
{
  int len = 0;
  void* val = IPWorks_REST_Get(m_pObj, 35, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setPostDataB :(NSData*)newPostData
{
  int len = (int)[newPostData length];
  void *val = (void*)[newPostData bytes];
  int ret_code = IPWorks_REST_Set(m_pObj, 35, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyAuthScheme
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 36, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyAuthScheme:(int)newProxyAuthScheme
{
  void *val = (void*)(long)newProxyAuthScheme;
  int ret_code = IPWorks_REST_Set(m_pObj, 36, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)proxyAutoDetect
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 37, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setProxyAutoDetect:(BOOL)newProxyAutoDetect
{
  void *val = (void*)(long)(newProxyAutoDetect ? 1 : 0);
  int ret_code = IPWorks_REST_Set(m_pObj, 37, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyPassword
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 38, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyPassword:(NSString*)newProxyPassword
{
  void *val = (void*)[self nsstringToCString:newProxyPassword];
  int ret_code = IPWorks_REST_Set(m_pObj, 38, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxyPort
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 39, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxyPort:(int)newProxyPort
{
  void *val = (void*)(long)newProxyPort;
  int ret_code = IPWorks_REST_Set(m_pObj, 39, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyServer
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 40, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyServer:(NSString*)newProxyServer
{
  void *val = (void*)[self nsstringToCString:newProxyServer];
  int ret_code = IPWorks_REST_Set(m_pObj, 40, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)proxySSL
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 41, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setProxySSL:(int)newProxySSL
{
  void *val = (void*)(long)newProxySSL;
  int ret_code = IPWorks_REST_Set(m_pObj, 41, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)proxyUser
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 42, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setProxyUser:(NSString*)newProxyUser
{
  void *val = (void*)[self nsstringToCString:newProxyUser];
  int ret_code = IPWorks_REST_Set(m_pObj, 42, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)referer
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 43, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setReferer:(NSString*)newReferer
{
  void *val = (void*)[self nsstringToCString:newReferer];
  int ret_code = IPWorks_REST_Set(m_pObj, 43, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLAcceptServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 44, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLAcceptServerCertEncoded];
  int ret_code = IPWorks_REST_Set(m_pObj, 44, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLAcceptServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_REST_Get(m_pObj, 44, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded length];
  void *val = (void*)[newSSLAcceptServerCertEncoded bytes];
  int ret_code = IPWorks_REST_Set(m_pObj, 44, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 45, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_REST_Set(m_pObj, 45, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_REST_Get(m_pObj, 45, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_REST_Set(m_pObj, 45, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 46, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_REST_Set(m_pObj, 46, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_REST_Get(m_pObj, 46, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_REST_Set(m_pObj, 46, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 47, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_REST_Set(m_pObj, 47, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 48, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_REST_Set(m_pObj, 48, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 49, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_REST_Set(m_pObj, 49, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 50, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)SSLServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_REST_Get(m_pObj, 50, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (NSString*)statusLine
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 51, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 52, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_REST_Set(m_pObj, 52, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)transferredData
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 53, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)transferredDataB
{
  int len = 0;
  void* val = IPWorks_REST_Get(m_pObj, 53, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (long long)transferredDataLimit
{
  int len = 0;
  long long llVal;
  IPWorks_REST_Get(m_pObj, 54, 0, &len, &llVal);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (void)setTransferredDataLimit:(long long)newTransferredDataLimit
{
  void *val = (void*)&newTransferredDataLimit;
  int ret_code = IPWorks_REST_Set(m_pObj, 54, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)transferredHeaders
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 55, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)URL
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 56, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setURL:(NSString*)newURL
{
  void *val = (void*)[self nsstringToCString:newURL];
  int ret_code = IPWorks_REST_Set(m_pObj, 56, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)user
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 57, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUser:(NSString*)newUser
{
  void *val = (void*)[self nsstringToCString:newUser];
  int ret_code = IPWorks_REST_Set(m_pObj, 57, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)validate
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 58, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setValidate:(BOOL)newValidate
{
  void *val = (void*)(long)(newValidate ? 1 : 0);
  int ret_code = IPWorks_REST_Set(m_pObj, 58, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)attrCount
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 59, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)attrName:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 60, attrIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)attrNamespace:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 61, attrIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)attrPrefix:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 62, attrIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)attrValue:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 63, attrIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)XChildCount
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 64, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)XChildName:(int)xChildIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 65, xChildIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XChildNamespace:(int)xChildIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 66, xChildIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XChildPrefix:(int)xChildIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 67, xChildIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XChildXText:(int)xChildIndex
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 68, xChildIndex, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XElement
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 69, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XErrorPath
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 70, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXErrorPath:(NSString*)newXErrorPath
{
  void *val = (void*)[self nsstringToCString:newXErrorPath];
  int ret_code = IPWorks_REST_Set(m_pObj, 70, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XNamespace
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 71, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XParent
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 72, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XPath
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 73, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXPath:(NSString*)newXPath
{
  void *val = (void*)[self nsstringToCString:newXPath];
  int ret_code = IPWorks_REST_Set(m_pObj, 73, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XPrefix
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 74, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XSubTree
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 75, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XText
{
  int len = 0;
  void* val=IPWorks_REST_Get(m_pObj, 76, 0, &len, nil);
  if (IPWorks_REST_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

  /* Methods */

- (void)addCookie:(NSString*)cookieName :(NSString*)cookieValue
{
  void *param[2+1] = {(void*)[self nsstringToCString:cookieName], (void*)[self nsstringToCString:cookieValue], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_REST_Do(m_pObj, 2, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)attr:(NSString*)attrName
{
  void *param[1+1] = {(void*)[self nsstringToCString:attrName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_REST_Do(m_pObj, 3, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_REST_Do(m_pObj, 4, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)delete:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_REST_Do(m_pObj, 5, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_REST_Do(m_pObj, 6, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)get:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_REST_Do(m_pObj, 7, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)hasXPath:(NSString*)XPath
{
  void *param[1+1] = {(void*)[self nsstringToCString:XPath], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_REST_Do(m_pObj, 8, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return param[1] ? YES : NO;
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_REST_Do(m_pObj, 9, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)post:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_REST_Do(m_pObj, 10, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)put:(NSString*)URL
{
  void *param[1+1] = {(void*)[self nsstringToCString:URL], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_REST_Do(m_pObj, 11, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_REST_Do(m_pObj, 12, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)tryXPath:(NSString*)xpath
{
  void *param[1+1] = {(void*)[self nsstringToCString:xpath], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_REST_Do(m_pObj, 13, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return param[1] ? YES : NO;
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
  int codePage = (int)(long)IPWorks_REST_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_REST_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end