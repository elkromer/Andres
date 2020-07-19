
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksIMAP.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksIMAP()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define IMAP_EXTERN extern "C"
#else
#define IMAP_EXTERN extern
#endif

IMAP_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
IMAP_EXTERN void* IPWorks_IMAP_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
IMAP_EXTERN int   IPWorks_IMAP_Destroy(void* lpObj);
IMAP_EXTERN int   IPWorks_IMAP_CheckIndex(void* lpObj, int propid, int arridx);
IMAP_EXTERN void* IPWorks_IMAP_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
IMAP_EXTERN int   IPWorks_IMAP_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
IMAP_EXTERN int   IPWorks_IMAP_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
IMAP_EXTERN char* IPWorks_IMAP_GetLastError(void* lpObj);
IMAP_EXTERN int   IPWorks_IMAP_GetLastErrorCode(void* lpObj);
IMAP_EXTERN int   IPWorks_IMAP_SetLastErrorAndCode(void* lpObj, int code, char* message);
IMAP_EXTERN char* IPWorks_IMAP_GetEventError(void* lpObj);
IMAP_EXTERN int   IPWorks_IMAP_GetEventErrorCode(void* lpObj);
IMAP_EXTERN int   IPWorks_IMAP_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void IMAP_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_IMAP_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int IMAP_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksIMAP* ctl = (IPWorksIMAP*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, IMAP_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (IMAP)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
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
    case 2 /*EID_ENDTRANSFER*/: {
      int direction = (int)(long)param[0];
      @try {
        [ctl onEndTransfer :direction];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EndTransfer" :YES];
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
    case 4 /*EID_HEADER*/: {
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
    case 5 /*EID_IDLEINFO*/: {
      NSString* messageT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* message = messageT;
      int* cancel = (int*)&param[1];
      @try {
        [ctl onIdleInfo :message :cancel];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"IdleInfo" :YES];
      }
      break;
    }
    case 6 /*EID_MAILBOXACL*/: {
      NSString* mailboxT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* mailbox = mailboxT;
      NSString* userT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* user = userT;
      NSString* rightsT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* rights = rightsT;
      @try {
        [ctl onMailboxACL :mailbox :user :rights];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"MailboxACL" :YES];
      }
      break;
    }
    case 7 /*EID_MAILBOXLIST*/: {
      NSString* mailboxT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* mailbox = mailboxT;
      NSString* separatorT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* separator = separatorT;
      NSString* flagsT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* flags = flagsT;
      @try {
        [ctl onMailboxList :mailbox :separator :flags];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"MailboxList" :YES];
      }
      break;
    }
    case 8 /*EID_MESSAGEINFO*/: {
      NSString* messageIdT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* messageId = messageIdT;
      NSString* subjectT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* subject = subjectT;
      NSString* messageDateT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* messageDate = messageDateT;
      NSString* fromT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* from = fromT;
      NSString* flagsT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* flags = flagsT;
      long long size = *(long long*)param[5];
      @try {
        [ctl onMessageInfo :messageId :subject :messageDate :from :flags :size];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"MessageInfo" :YES];
      }
      break;
    }
    case 9 /*EID_MESSAGEPART*/: {
      NSString* partIdT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* partId = partIdT;
      long long size = *(long long*)param[1];
      NSString* contentTypeT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* contentType = contentTypeT;
      NSString* filenameT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* filename = filenameT;
      NSString* contentEncodingT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* contentEncoding = contentEncodingT;
      NSString* parametersT = [NSString stringWithCString:(const char*)param[5] encoding:[ctl innerGetCodePage]];
      NSString* parameters = parametersT;
      NSString* multipartModeT = [NSString stringWithCString:(const char*)param[6] encoding:[ctl innerGetCodePage]];
      NSString* multipartMode = multipartModeT;
      NSString* contentIdT = [NSString stringWithCString:(const char*)param[7] encoding:[ctl innerGetCodePage]];
      NSString* contentId = contentIdT;
      NSString* contentDispositionT = [NSString stringWithCString:(const char*)param[8] encoding:[ctl innerGetCodePage]];
      NSString* contentDisposition = contentDispositionT;
      @try {
        [ctl onMessagePart :partId :size :contentType :filename :contentEncoding :parameters :multipartMode :contentId :contentDisposition];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"MessagePart" :YES];
      }
      break;
    }
    case 10 /*EID_PITRAIL*/: {
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
    case 14 /*EID_TRANSFER*/: {
      int direction = (int)(long)param[0];
      long long bytesTransferred = *(long long*)param[1];
      int percentDone = (int)(long)param[2];
      NSString* textT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* text = textT;
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

@implementation IPWorksIMAP

+ (IPWorksIMAP*)imap
{
#if __has_feature(objc_arc)
  return [[IPWorksIMAP alloc] init];
#else
  return [[[IPWorksIMAP alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_IMAP_Create((void*)IMAP_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_IMAP_Create((void*)IMAP_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_IMAP_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_IMAP_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_IMAP_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_IMAP_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_IMAP_GetEventErrorCode(m_pObj);
}

- (id <IPWorksIMAPDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksIMAPDelegate>)anObject
{
  m_delegateHasConnectionStatus = NO;
  m_delegateHasEndTransfer = NO;
  m_delegateHasError = NO;
  m_delegateHasHeader = NO;
  m_delegateHasIdleInfo = NO;
  m_delegateHasMailboxACL = NO;
  m_delegateHasMailboxList = NO;
  m_delegateHasMessageInfo = NO;
  m_delegateHasMessagePart = NO;
  m_delegateHasPITrail = NO;
  m_delegateHasSSLServerAuthentication = NO;
  m_delegateHasSSLStatus = NO;
  m_delegateHasStartTransfer = NO;
  m_delegateHasTransfer = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onConnectionStatus:::)]) m_delegateHasConnectionStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onEndTransfer:)]) m_delegateHasEndTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onHeader::)]) m_delegateHasHeader = YES;
    if ([m_delegate respondsToSelector:@selector(onIdleInfo::)]) m_delegateHasIdleInfo = YES;
    if ([m_delegate respondsToSelector:@selector(onMailboxACL:::)]) m_delegateHasMailboxACL = YES;
    if ([m_delegate respondsToSelector:@selector(onMailboxList:::)]) m_delegateHasMailboxList = YES;
    if ([m_delegate respondsToSelector:@selector(onMessageInfo::::::)]) m_delegateHasMessageInfo = YES;
    if ([m_delegate respondsToSelector:@selector(onMessagePart:::::::::)]) m_delegateHasMessagePart = YES;
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
- (void)onIdleInfo:(NSString*)message :(int*)cancel
{
  if (m_delegate != nil && m_delegateHasIdleInfo)
    [m_delegate onIdleInfo:message :cancel];
}
- (void)onMailboxACL:(NSString*)mailbox :(NSString*)user :(NSString*)rights
{
  if (m_delegate != nil && m_delegateHasMailboxACL)
    [m_delegate onMailboxACL:mailbox :user :rights];
}
- (void)onMailboxList:(NSString*)mailbox :(NSString*)separator :(NSString*)flags
{
  if (m_delegate != nil && m_delegateHasMailboxList)
    [m_delegate onMailboxList:mailbox :separator :flags];
}
- (void)onMessageInfo:(NSString*)messageId :(NSString*)subject :(NSString*)messageDate :(NSString*)from :(NSString*)flags :(long long)size
{
  if (m_delegate != nil && m_delegateHasMessageInfo)
    [m_delegate onMessageInfo:messageId :subject :messageDate :from :flags :size];
}
- (void)onMessagePart:(NSString*)partId :(long long)size :(NSString*)contentType :(NSString*)filename :(NSString*)contentEncoding :(NSString*)parameters :(NSString*)multipartMode :(NSString*)contentId :(NSString*)contentDisposition
{
  if (m_delegate != nil && m_delegateHasMessagePart)
    [m_delegate onMessagePart:partId :size :contentType :filename :contentEncoding :parameters :multipartMode :contentId :contentDisposition];
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
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone :(NSString*)text
{
  if (m_delegate != nil && m_delegateHasTransfer)
    [m_delegate onTransfer:direction :bytesTransferred :percentDone :text];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_IMAP_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_IMAP_Get(m_pObj, 0, 0, 0, nil);
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

- (int)authMechanism
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAuthMechanism:(int)newAuthMechanism
{
  void *val = (void*)(long)newAuthMechanism;
  int ret_code = IPWorks_IMAP_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)autoDecodeParts
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setAutoDecodeParts:(BOOL)newAutoDecodeParts
{
  void *val = (void*)(long)(newAutoDecodeParts ? 1 : 0);
  int ret_code = IPWorks_IMAP_Set(m_pObj, 2, 0, val, 0);
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
  int ret_code = IPWorks_IMAP_Set(m_pObj, 3, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)connected
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setConnected:(BOOL)newConnected
{
  void *val = (void*)(long)(newConnected ? 1 : 0);
  int ret_code = IPWorks_IMAP_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (long long)endByte
{
  int len = 0;
  long long llVal;
  IPWorks_IMAP_Get(m_pObj, 5, 0, &len, &llVal);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (void)setEndByte:(long long)newEndByte
{
  void *val = (void*)&newEndByte;
  int ret_code = IPWorks_IMAP_Set(m_pObj, 5, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)firewallAutoDetect
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect
{
  void *val = (void*)(long)(newFirewallAutoDetect ? 1 : 0);
  int ret_code = IPWorks_IMAP_Set(m_pObj, 6, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallType
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallType:(int)newFirewallType
{
  void *val = (void*)(long)newFirewallType;
  int ret_code = IPWorks_IMAP_Set(m_pObj, 7, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallHost
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallHost:(NSString*)newFirewallHost
{
  void *val = (void*)[self nsstringToCString:newFirewallHost];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 8, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallPassword
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallPassword:(NSString*)newFirewallPassword
{
  void *val = (void*)[self nsstringToCString:newFirewallPassword];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 9, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallPort
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallPort:(int)newFirewallPort
{
  void *val = (void*)(long)newFirewallPort;
  int ret_code = IPWorks_IMAP_Set(m_pObj, 10, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallUser
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallUser:(NSString*)newFirewallUser
{
  void *val = (void*)[self nsstringToCString:newFirewallUser];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 11, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)idle
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (NSString*)lastReply
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)localFile
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalFile:(NSString*)newLocalFile
{
  void *val = (void*)[self nsstringToCString:newLocalFile];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 14, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)mailbox
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMailbox:(NSString*)newMailbox
{
  void *val = (void*)[self nsstringToCString:newMailbox];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)mailboxFlags
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)mailboxListCount
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)mailboxListFlags:(int)mailboxListIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 19, mailboxListIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)mailboxListName:(int)mailboxListIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 20, mailboxListIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)mailboxListSeparator:(int)mailboxListIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 21, mailboxListIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)mailPort
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setMailPort:(int)newMailPort
{
  void *val = (void*)(long)newMailPort;
  int ret_code = IPWorks_IMAP_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)mailServer
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMailServer:(NSString*)newMailServer
{
  void *val = (void*)[self nsstringToCString:newMailServer];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 23, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)message
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setMessage:(NSString*)newMessage
{
  int len = (int)[newMessage lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newMessage];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 24, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)messageB
{
  int len = 0;
  void* val = IPWorks_IMAP_Get(m_pObj, 24, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setMessageB :(NSData*)newMessage
{
  int len = (int)[newMessage length];
  void *val = (void*)[newMessage bytes];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 24, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageContentEncoding
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageContentType
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)messageCount
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)messageDate
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageDeliveryTime
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 29, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageFlags
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageFlags:(NSString*)newMessageFlags
{
  void *val = (void*)[self nsstringToCString:newMessageFlags];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 30, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageFrom
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)messageHeaderCount
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setMessageHeaderCount:(int)newMessageHeaderCount
{
  void *val = (void*)(long)newMessageHeaderCount;
  int ret_code = IPWorks_IMAP_Set(m_pObj, 32, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageHeaderField:(int)messageHeaderIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 33, messageHeaderIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageHeaderField:(int)messageHeaderIndex:(NSString*)newMessageHeaderField
{
  void *val = (void*)[self nsstringToCString:newMessageHeaderField];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 33, messageHeaderIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageHeaderValue:(int)messageHeaderIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 34, messageHeaderIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageHeaderValue:(int)messageHeaderIndex:(NSString*)newMessageHeaderValue
{
  void *val = (void*)[self nsstringToCString:newMessageHeaderValue];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 34, messageHeaderIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageHeadersString
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 35, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageHeadersString:(NSString*)newMessageHeadersString
{
  void *val = (void*)[self nsstringToCString:newMessageHeadersString];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 35, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageId
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 36, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)messageInfoCount
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 37, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)messageInfoDate:(int)messageInfoIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 38, messageInfoIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageInfoFlags:(int)messageInfoIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 39, messageInfoIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageInfoFrom:(int)messageInfoIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 40, messageInfoIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageInfoMessageId:(int)messageInfoIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 41, messageInfoIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (long long)messageInfoSize:(int)messageInfoIndex
{
  int len = 0;
  long long llVal;
  IPWorks_IMAP_Get(m_pObj, 42, messageInfoIndex, &len, &llVal);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (NSString*)messageInfoSubject:(int)messageInfoIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 43, messageInfoIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageInReplyTo
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 44, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageNetId
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 45, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)messagePartCount
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 46, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)messagePartContentDisposition:(int)messagePartIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 47, messagePartIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messagePartContentEncoding:(int)messagePartIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 48, messagePartIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messagePartContentId:(int)messagePartIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 49, messagePartIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messagePartContentType:(int)messagePartIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 50, messagePartIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messagePartFilename:(int)messagePartIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 51, messagePartIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messagePartId:(int)messagePartIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 52, messagePartIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messagePartMultipartMode:(int)messagePartIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 53, messagePartIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messagePartParameters:(int)messagePartIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 54, messagePartIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (long long)messagePartSize:(int)messagePartIndex
{
  int len = 0;
  long long llVal;
  IPWorks_IMAP_Get(m_pObj, 55, messagePartIndex, &len, &llVal);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (int)messageRecipientCount
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 56, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)messageRecipientAddress:(int)recipientIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 57, recipientIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageRecipientName:(int)recipientIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 58, recipientIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageRecipientOptions:(int)recipientIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 59, recipientIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)messageRecipientType:(int)recipientIndex
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 60, recipientIndex, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)messageReplyTo
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 61, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageSender
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 62, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageSet
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 63, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageSet:(NSString*)newMessageSet
{
  void *val = (void*)[self nsstringToCString:newMessageSet];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 63, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (long long)messageSize
{
  int len = 0;
  long long llVal;
  IPWorks_IMAP_Get(m_pObj, 64, 0, &len, &llVal);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (NSString*)messageSubject
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 65, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)messageText
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 66, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageText:(NSString*)newMessageText
{
  void *val = (void*)[self nsstringToCString:newMessageText];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 66, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)overwrite
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 67, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setOverwrite:(BOOL)newOverwrite
{
  void *val = (void*)(long)(newOverwrite ? 1 : 0);
  int ret_code = IPWorks_IMAP_Set(m_pObj, 67, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)password
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 68, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPassword:(NSString*)newPassword
{
  void *val = (void*)[self nsstringToCString:newPassword];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 68, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)peekMode
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 69, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setPeekMode:(BOOL)newPeekMode
{
  void *val = (void*)(long)(newPeekMode ? 1 : 0);
  int ret_code = IPWorks_IMAP_Set(m_pObj, 69, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)recentMessageCount
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 70, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)sortCriteria
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 71, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSortCriteria:(NSString*)newSortCriteria
{
  void *val = (void*)[self nsstringToCString:newSortCriteria];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 71, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLAcceptServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 72, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLAcceptServerCertEncoded];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 72, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLAcceptServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_IMAP_Get(m_pObj, 72, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded length];
  void *val = (void*)[newSSLAcceptServerCertEncoded bytes];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 72, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 73, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 73, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_IMAP_Get(m_pObj, 73, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 73, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 74, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 74, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_IMAP_Get(m_pObj, 74, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 74, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 75, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 75, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 76, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_IMAP_Set(m_pObj, 76, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 77, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 77, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)SSLEnabled
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 78, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setSSLEnabled:(BOOL)newSSLEnabled
{
  void *val = (void*)(long)(newSSLEnabled ? 1 : 0);
  int ret_code = IPWorks_IMAP_Set(m_pObj, 78, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 79, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)SSLServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_IMAP_Get(m_pObj, 79, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (int)SSLStartMode
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 80, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLStartMode:(int)newSSLStartMode
{
  void *val = (void*)(long)newSSLStartMode;
  int ret_code = IPWorks_IMAP_Set(m_pObj, 80, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (long long)startByte
{
  int len = 0;
  long long llVal;
  IPWorks_IMAP_Get(m_pObj, 81, 0, &len, &llVal);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return llVal;
}

- (void)setStartByte:(long long)newStartByte
{
  void *val = (void*)&newStartByte;
  int ret_code = IPWorks_IMAP_Set(m_pObj, 81, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 82, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_IMAP_Set(m_pObj, 82, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)UIDMode
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 83, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setUIDMode:(BOOL)newUIDMode
{
  void *val = (void*)(long)(newUIDMode ? 1 : 0);
  int ret_code = IPWorks_IMAP_Set(m_pObj, 83, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)UIDValidity
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 84, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)user
{
  int len = 0;
  void* val=IPWorks_IMAP_Get(m_pObj, 85, 0, &len, nil);
  if (IPWorks_IMAP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUser:(NSString*)newUser
{
  void *val = (void*)[self nsstringToCString:newUser];
  int ret_code = IPWorks_IMAP_Set(m_pObj, 85, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (void)addMessageFlags:(NSString*)flags
{
  void *param[1+1] = {(void*)[self nsstringToCString:flags], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)appendToMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)checkMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 4, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)closeMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 5, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 6, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)connect
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 7, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)copyToMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 8, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)createMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 9, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)deleteFromMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 10, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)deleteMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 11, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)deleteMailboxACL:(NSString*)user
{
  void *param[1+1] = {(void*)[self nsstringToCString:user], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 12, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)disconnect
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 13, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 14, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)examineMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 15, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)expungeMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 16, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)fetchMessageHeaders
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 17, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)fetchMessageInfo
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 18, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)fetchMessagePart:(NSString*)partId
{
  void *param[1+1] = {(void*)[self nsstringToCString:partId], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 19, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)fetchMessagePartHeaders:(NSString*)partId
{
  void *param[1+1] = {(void*)[self nsstringToCString:partId], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 20, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)fetchMessageText
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 21, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)getMailboxACL
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 22, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 23, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)listMailboxes
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 24, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)listSubscribedMailboxes
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 25, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localizeDate:(NSString*)dateTime
{
  void *param[1+1] = {(void*)[self nsstringToCString:dateTime], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 26, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)moveToMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 27, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)noop
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 28, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)renameMailbox:(NSString*)newName
{
  void *param[1+1] = {(void*)[self nsstringToCString:newName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 29, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 30, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)resetMessageFlags
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 31, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)searchMailbox:(NSString*)searchCriteria
{
  void *param[1+1] = {(void*)[self nsstringToCString:searchCriteria], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 32, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)selectMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 33, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setMailboxACL:(NSString*)user :(NSString*)rights
{
  void *param[2+1] = {(void*)[self nsstringToCString:user], (void*)[self nsstringToCString:rights], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 34, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)startIdle
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 36, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)stopIdle
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 37, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)subscribeMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 38, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)unsetMessageFlags
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 39, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)unsubscribeMailbox
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_IMAP_Do(m_pObj, 40, 0, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_IMAP_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_IMAP_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end