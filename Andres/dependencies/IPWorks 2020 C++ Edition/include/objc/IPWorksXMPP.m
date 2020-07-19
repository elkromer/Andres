
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksXMPP.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksXMPP()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define XMPP_EXTERN extern "C"
#else
#define XMPP_EXTERN extern
#endif

XMPP_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
XMPP_EXTERN void* IPWorks_XMPP_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
XMPP_EXTERN int   IPWorks_XMPP_Destroy(void* lpObj);
XMPP_EXTERN int   IPWorks_XMPP_CheckIndex(void* lpObj, int propid, int arridx);
XMPP_EXTERN void* IPWorks_XMPP_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
XMPP_EXTERN int   IPWorks_XMPP_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
XMPP_EXTERN int   IPWorks_XMPP_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
XMPP_EXTERN char* IPWorks_XMPP_GetLastError(void* lpObj);
XMPP_EXTERN int   IPWorks_XMPP_GetLastErrorCode(void* lpObj);
XMPP_EXTERN int   IPWorks_XMPP_SetLastErrorAndCode(void* lpObj, int code, char* message);
XMPP_EXTERN char* IPWorks_XMPP_GetEventError(void* lpObj);
XMPP_EXTERN int   IPWorks_XMPP_GetEventErrorCode(void* lpObj);
XMPP_EXTERN int   IPWorks_XMPP_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void XMPP_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_XMPP_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int XMPP_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksXMPP* ctl = (IPWorksXMPP*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, XMPP_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (XMPP)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
      [myAlert show];
      return 1;
#else // TARGET_OS_IPHONE
      return 0;
#endif // TARGET_OS_IPHONE
    }

    case 1 /*EID_BUDDYUPDATE*/: {
      int buddyIdx = (int)(long)param[0];
      @try {
        [ctl onBuddyUpdate :buddyIdx];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"BuddyUpdate" :YES];
      }
      break;
    }
    case 2 /*EID_CONNECTED*/: {
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
    case 3 /*EID_CONNECTIONSTATUS*/: {
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
      NSString* fileIdT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* fileId = fileIdT;
      NSString* filenameT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* filename = filenameT;
      BOOL success = param[3] ? YES : NO;
      @try {
        [ctl onEndTransfer :direction :fileId :filename :success];
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
    case 7 /*EID_IQ*/: {
      NSString* iqT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* iq = iqT;
      NSString* idT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* id = idT;
      NSString* fromT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* from = fromT;
      NSString* iqTypeT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* iqType = iqTypeT;
      int* ignore = (int*)&param[4];
      @try {
        [ctl onIQ :iq :id :from :iqType :ignore];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"IQ" :YES];
      }
      break;
    }
    case 8 /*EID_MESSAGEIN*/: {
      NSString* messageIdT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* messageId = messageIdT;
      NSString* fromT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* from = fromT;
      NSString* domainT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* domain = domainT;
      NSString* resourceT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* resource = resourceT;
      int messageType = (int)(long)param[4];
      NSString* subjectT = [NSString stringWithCString:(const char*)param[5] encoding:[ctl innerGetCodePage]];
      NSString* subject = subjectT;
      NSString* messageThreadT = [NSString stringWithCString:(const char*)param[6] encoding:[ctl innerGetCodePage]];
      NSString* messageThread = messageThreadT;
      NSString* messageTextT = [NSString stringWithCString:(const char*)param[7] encoding:[ctl innerGetCodePage]];
      NSString* messageText = messageTextT;
      NSString* messageHTMLT = [NSString stringWithCString:(const char*)param[8] encoding:[ctl innerGetCodePage]];
      NSString* messageHTML = messageHTMLT;
      NSString* otherT = [NSString stringWithCString:(const char*)param[9] encoding:[ctl innerGetCodePage]];
      NSString* other = otherT;
      @try {
        [ctl onMessageIn :messageId :from :domain :resource :messageType :subject :messageThread :messageText :messageHTML :other];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"MessageIn" :YES];
      }
      break;
    }
    case 9 /*EID_PITRAIL*/: {
      int direction = (int)(long)param[0];
      NSString* piT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* pi = piT;
      @try {
        [ctl onPITrail :direction :pi];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"PITrail" :YES];
      }
      break;
    }
    case 10 /*EID_PRESENCE*/: {
      NSString* userT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* user = userT;
      NSString* domainT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* domain = domainT;
      NSString* resourceT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* resource = resourceT;
      int availability = (int)(long)param[3];
      NSString* statusT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* status = statusT;
      @try {
        [ctl onPresence :user :domain :resource :availability :status];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Presence" :YES];
      }
      break;
    }
    case 11 /*EID_READYTOSEND*/: {
      @try {
        [ctl onReadyToSend ];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"ReadyToSend" :YES];
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
      NSString* fileIdT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* fileId = fileIdT;
      NSString* userT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* user = userT;
      NSString* domainT = [NSString stringWithCString:(const char*)param[3] encoding:[ctl innerGetCodePage]];
      NSString* domain = domainT;
      NSString* resourceT = [NSString stringWithCString:(const char*)param[4] encoding:[ctl innerGetCodePage]];
      NSString* resource = resourceT;
      NSString* filenameT = [NSString stringWithCString:(const char*)IPWorks_EvtStr(param[5], 0, nil, 1) encoding:[ctl innerGetCodePage]];
#if __has_feature(objc_arc)
      __autoreleasing NSString*  filenameTA = filenameT;
      __autoreleasing NSString** filename = &filenameTA;
#else
      NSString** filename = &filenameT;
#endif
      NSString* datetimeT = [NSString stringWithCString:(const char*)param[6] encoding:[ctl innerGetCodePage]];
      NSString* datetime = datetimeT;
      long long size = *(long long*)param[7];
      int* accept = (int*)&param[8];
      @try {
        [ctl onStartTransfer :direction :fileId :user :domain :resource :filename :datetime :size :accept];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StartTransfer" :YES];
      }
      IPWorks_EvtStr(param[5], 2, (void*)([ctl nsstringToCString:*filename]), 1);
      break;
    }
    case 15 /*EID_SUBSCRIPTIONREQUEST*/: {
      NSString* fromT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* from = fromT;
      NSString* domainT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* domain = domainT;
      int* accept = (int*)&param[2];
      @try {
        [ctl onSubscriptionRequest :from :domain :accept];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"SubscriptionRequest" :YES];
      }
      break;
    }
    case 16 /*EID_SYNC*/: {
      @try {
        [ctl onSync ];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Sync" :YES];
      }
      break;
    }
    case 17 /*EID_TRANSFER*/: {
      int direction = (int)(long)param[0];
      NSString* fileIdT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* fileId = fileIdT;
      NSString* filenameT = [NSString stringWithCString:(const char*)param[2] encoding:[ctl innerGetCodePage]];
      NSString* filename = filenameT;
      long long bytesTransferred = *(long long*)param[3];
      int percentDone = (int)(long)param[4];
      NSData* text = [NSData dataWithBytesNoCopy:param[5] length:cbparam[5] freeWhenDone:NO];
      int* cancel = (int*)&param[6];
      @try {
        [ctl onTransfer :direction :fileId :filename :bytesTransferred :percentDone :text :cancel];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Transfer" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksXMPP

+ (IPWorksXMPP*)xmpp
{
#if __has_feature(objc_arc)
  return [[IPWorksXMPP alloc] init];
#else
  return [[[IPWorksXMPP alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_XMPP_Create((void*)XMPP_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_XMPP_Create((void*)XMPP_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_XMPP_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_XMPP_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_XMPP_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_XMPP_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_XMPP_GetEventErrorCode(m_pObj);
}

- (id <IPWorksXMPPDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksXMPPDelegate>)anObject
{
  m_delegateHasBuddyUpdate = NO;
  m_delegateHasConnected = NO;
  m_delegateHasConnectionStatus = NO;
  m_delegateHasDisconnected = NO;
  m_delegateHasEndTransfer = NO;
  m_delegateHasError = NO;
  m_delegateHasIQ = NO;
  m_delegateHasMessageIn = NO;
  m_delegateHasPITrail = NO;
  m_delegateHasPresence = NO;
  m_delegateHasReadyToSend = NO;
  m_delegateHasSSLServerAuthentication = NO;
  m_delegateHasSSLStatus = NO;
  m_delegateHasStartTransfer = NO;
  m_delegateHasSubscriptionRequest = NO;
  m_delegateHasSync = NO;
  m_delegateHasTransfer = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onBuddyUpdate:)]) m_delegateHasBuddyUpdate = YES;
    if ([m_delegate respondsToSelector:@selector(onConnected::)]) m_delegateHasConnected = YES;
    if ([m_delegate respondsToSelector:@selector(onConnectionStatus:::)]) m_delegateHasConnectionStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onDisconnected::)]) m_delegateHasDisconnected = YES;
    if ([m_delegate respondsToSelector:@selector(onEndTransfer::::)]) m_delegateHasEndTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onIQ:::::)]) m_delegateHasIQ = YES;
    if ([m_delegate respondsToSelector:@selector(onMessageIn::::::::::)]) m_delegateHasMessageIn = YES;
    if ([m_delegate respondsToSelector:@selector(onPITrail::)]) m_delegateHasPITrail = YES;
    if ([m_delegate respondsToSelector:@selector(onPresence:::::)]) m_delegateHasPresence = YES;
    if ([m_delegate respondsToSelector:@selector(onReadyToSend)]) m_delegateHasReadyToSend = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLServerAuthentication:::::)]) m_delegateHasSSLServerAuthentication = YES;
    if ([m_delegate respondsToSelector:@selector(onSSLStatus:)]) m_delegateHasSSLStatus = YES;
    if ([m_delegate respondsToSelector:@selector(onStartTransfer:::::::::)]) m_delegateHasStartTransfer = YES;
    if ([m_delegate respondsToSelector:@selector(onSubscriptionRequest:::)]) m_delegateHasSubscriptionRequest = YES;
    if ([m_delegate respondsToSelector:@selector(onSync)]) m_delegateHasSync = YES;
    if ([m_delegate respondsToSelector:@selector(onTransfer:::::::)]) m_delegateHasTransfer = YES;
  }
}

  /* Events */

- (void)onBuddyUpdate:(int)buddyIdx
{
  if (m_delegate != nil && m_delegateHasBuddyUpdate)
    [m_delegate onBuddyUpdate:buddyIdx];
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
- (void)onEndTransfer:(int)direction :(NSString*)fileId :(NSString*)filename :(BOOL)success
{
  if (m_delegate != nil && m_delegateHasEndTransfer)
    [m_delegate onEndTransfer:direction :fileId :filename :success];
}
- (void)onError:(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:errorCode :description];
}
- (void)onIQ:(NSString*)iq :(NSString*)id :(NSString*)from :(NSString*)iqType :(int*)ignore
{
  if (m_delegate != nil && m_delegateHasIQ)
    [m_delegate onIQ:iq :id :from :iqType :ignore];
}
- (void)onMessageIn:(NSString*)messageId :(NSString*)from :(NSString*)domain :(NSString*)resource :(int)messageType :(NSString*)subject :(NSString*)messageThread :(NSString*)messageText :(NSString*)messageHTML :(NSString*)other
{
  if (m_delegate != nil && m_delegateHasMessageIn)
    [m_delegate onMessageIn:messageId :from :domain :resource :messageType :subject :messageThread :messageText :messageHTML :other];
}
- (void)onPITrail:(int)direction :(NSString*)pi
{
  if (m_delegate != nil && m_delegateHasPITrail)
    [m_delegate onPITrail:direction :pi];
}
- (void)onPresence:(NSString*)user :(NSString*)domain :(NSString*)resource :(int)availability :(NSString*)status
{
  if (m_delegate != nil && m_delegateHasPresence)
    [m_delegate onPresence:user :domain :resource :availability :status];
}
- (void)onReadyToSend
{
  if (m_delegate != nil && m_delegateHasReadyToSend)
    [m_delegate onReadyToSend];
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
- (void)onStartTransfer:(int)direction :(NSString*)fileId :(NSString*)user :(NSString*)domain :(NSString*)resource :(NSString**)filename :(NSString*)datetime :(long long)size :(int*)accept
{
  if (m_delegate != nil && m_delegateHasStartTransfer)
    [m_delegate onStartTransfer:direction :fileId :user :domain :resource :filename :datetime :size :accept];
}
- (void)onSubscriptionRequest:(NSString*)from :(NSString*)domain :(int*)accept
{
  if (m_delegate != nil && m_delegateHasSubscriptionRequest)
    [m_delegate onSubscriptionRequest:from :domain :accept];
}
- (void)onSync
{
  if (m_delegate != nil && m_delegateHasSync)
    [m_delegate onSync];
}
- (void)onTransfer:(int)direction :(NSString*)fileId :(NSString*)filename :(long long)bytesTransferred :(int)percentDone :(NSData*)text :(int*)cancel
{
  if (m_delegate != nil && m_delegateHasTransfer)
    [m_delegate onTransfer:direction :fileId :filename :bytesTransferred :percentDone :text :cancel];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_XMPP_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_XMPP_Get(m_pObj, 0, 0, 0, nil);
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

- (NSString*)authDomain
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAuthDomain:(NSString*)newAuthDomain
{
  void *val = (void*)[self nsstringToCString:newAuthDomain];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)authMethods
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setAuthMethods:(NSString*)newAuthMethods
{
  void *val = (void*)[self nsstringToCString:newAuthMethods];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)buddyCount
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)buddyGroup:(int)buddyIndex
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 4, buddyIndex, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setBuddyGroup:(int)buddyIndex:(NSString*)newBuddyGroup
{
  void *val = (void*)[self nsstringToCString:newBuddyGroup];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 4, buddyIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)buddyId:(int)buddyIndex
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 5, buddyIndex, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)buddyNickName:(int)buddyIndex
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 6, buddyIndex, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setBuddyNickName:(int)buddyIndex:(NSString*)newBuddyNickName
{
  void *val = (void*)[self nsstringToCString:newBuddyNickName];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 6, buddyIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)buddyRealName:(int)buddyIndex
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 7, buddyIndex, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)buddySubscription:(int)buddyIndex
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 8, buddyIndex, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (BOOL)connected
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setConnected:(BOOL)newConnected
{
  void *val = (void*)(long)(newConnected ? 1 : 0);
  int ret_code = IPWorks_XMPP_Set(m_pObj, 9, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)firewallAutoDetect
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect
{
  void *val = (void*)(long)(newFirewallAutoDetect ? 1 : 0);
  int ret_code = IPWorks_XMPP_Set(m_pObj, 10, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallType
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallType:(int)newFirewallType
{
  void *val = (void*)(long)newFirewallType;
  int ret_code = IPWorks_XMPP_Set(m_pObj, 11, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallHost
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallHost:(NSString*)newFirewallHost
{
  void *val = (void*)[self nsstringToCString:newFirewallHost];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 12, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallPassword
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallPassword:(NSString*)newFirewallPassword
{
  void *val = (void*)[self nsstringToCString:newFirewallPassword];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 13, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)firewallPort
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setFirewallPort:(int)newFirewallPort
{
  void *val = (void*)(long)newFirewallPort;
  int ret_code = IPWorks_XMPP_Set(m_pObj, 14, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)firewallUser
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setFirewallUser:(NSString*)newFirewallUser
{
  void *val = (void*)[self nsstringToCString:newFirewallUser];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)IMPort
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setIMPort:(int)newIMPort
{
  void *val = (void*)(long)newIMPort;
  int ret_code = IPWorks_XMPP_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)IMServer
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setIMServer:(NSString*)newIMServer
{
  void *val = (void*)[self nsstringToCString:newIMServer];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localDirectory
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 18, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalDirectory:(NSString*)newLocalDirectory
{
  void *val = (void*)[self nsstringToCString:newLocalDirectory];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 18, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localFile
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 19, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalFile:(NSString*)newLocalFile
{
  void *val = (void*)[self nsstringToCString:newLocalFile];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 19, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)localHost
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 20, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setLocalHost:(NSString*)newLocalHost
{
  void *val = (void*)[self nsstringToCString:newLocalHost];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 20, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageHTML
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageHTML:(NSString*)newMessageHTML
{
  void *val = (void*)[self nsstringToCString:newMessageHTML];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageOtherData
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 22, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageOtherData:(NSString*)newMessageOtherData
{
  void *val = (void*)[self nsstringToCString:newMessageOtherData];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 22, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageSubject
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageSubject:(NSString*)newMessageSubject
{
  void *val = (void*)[self nsstringToCString:newMessageSubject];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 23, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageText
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageText:(NSString*)newMessageText
{
  void *val = (void*)[self nsstringToCString:newMessageText];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 24, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageThread
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageThread:(NSString*)newMessageThread
{
  void *val = (void*)[self nsstringToCString:newMessageThread];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 25, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)messageType
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setMessageType:(int)newMessageType
{
  void *val = (void*)(long)newMessageType;
  int ret_code = IPWorks_XMPP_Set(m_pObj, 26, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)password
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPassword:(NSString*)newPassword
{
  void *val = (void*)[self nsstringToCString:newPassword];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 27, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)presence
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setPresence:(int)newPresence
{
  void *val = (void*)(long)newPresence;
  int ret_code = IPWorks_XMPP_Set(m_pObj, 28, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)resource
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 29, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setResource:(NSString*)newResource
{
  void *val = (void*)[self nsstringToCString:newResource];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 29, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)serverDomain
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setServerDomain:(NSString*)newServerDomain
{
  void *val = (void*)[self nsstringToCString:newServerDomain];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 30, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLAcceptServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLAcceptServerCertEncoded];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 31, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLAcceptServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_XMPP_Get(m_pObj, 31, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded
{
  int len = (int)[newSSLAcceptServerCertEncoded length];
  void *val = (void*)[newSSLAcceptServerCertEncoded bytes];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 31, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertEncoded
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertEncoded];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 32, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertEncodedB
{
  int len = 0;
  void* val = IPWorks_XMPP_Get(m_pObj, 32, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded
{
  int len = (int)[newSSLCertEncoded length];
  void *val = (void*)[newSSLCertEncoded bytes];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 32, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStore
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 33, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStore:(NSString*)newSSLCertStore
{
  int len = (int)[newSSLCertStore lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newSSLCertStore];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 33, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)SSLCertStoreB
{
  int len = 0;
  void* val = IPWorks_XMPP_Get(m_pObj, 33, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setSSLCertStoreB :(NSData*)newSSLCertStore
{
  int len = (int)[newSSLCertStore length];
  void *val = (void*)[newSSLCertStore bytes];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 33, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertStorePassword
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 34, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword
{
  void *val = (void*)[self nsstringToCString:newSSLCertStorePassword];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 34, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)SSLCertStoreType
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 35, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLCertStoreType:(int)newSSLCertStoreType
{
  void *val = (void*)(long)newSSLCertStoreType;
  int ret_code = IPWorks_XMPP_Set(m_pObj, 35, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLCertSubject
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 36, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setSSLCertSubject:(NSString*)newSSLCertSubject
{
  void *val = (void*)[self nsstringToCString:newSSLCertSubject];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 36, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)SSLEnabled
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 37, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setSSLEnabled:(BOOL)newSSLEnabled
{
  void *val = (void*)(long)(newSSLEnabled ? 1 : 0);
  int ret_code = IPWorks_XMPP_Set(m_pObj, 37, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)SSLServerCertEncoded
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 38, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (NSData*)SSLServerCertEncodedB
{
  int len = 0;
  void* val = IPWorks_XMPP_Get(m_pObj, 38, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (int)SSLStartMode
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 39, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setSSLStartMode:(int)newSSLStartMode
{
  void *val = (void*)(long)newSSLStartMode;
  int ret_code = IPWorks_XMPP_Set(m_pObj, 39, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)status
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 40, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setStatus:(NSString*)newStatus
{
  void *val = (void*)[self nsstringToCString:newStatus];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 40, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)timeout
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 41, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setTimeout:(int)newTimeout
{
  void *val = (void*)(long)newTimeout;
  int ret_code = IPWorks_XMPP_Set(m_pObj, 41, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)user
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 42, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUser:(NSString*)newUser
{
  void *val = (void*)[self nsstringToCString:newUser];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 42, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)userDomain
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 43, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUserDomain:(NSString*)newUserDomain
{
  void *val = (void*)[self nsstringToCString:newUserDomain];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 43, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)userInfoCount
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 44, 0, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setUserInfoCount:(int)newUserInfoCount
{
  void *val = (void*)(long)newUserInfoCount;
  int ret_code = IPWorks_XMPP_Set(m_pObj, 44, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)userInfoField:(int)fieldIndex
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 45, fieldIndex, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUserInfoField:(int)fieldIndex:(NSString*)newUserInfoField
{
  void *val = (void*)[self nsstringToCString:newUserInfoField];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 45, fieldIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)userInfoValue:(int)fieldIndex
{
  int len = 0;
  void* val=IPWorks_XMPP_Get(m_pObj, 46, fieldIndex, &len, nil);
  if (IPWorks_XMPP_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setUserInfoValue:(int)fieldIndex:(NSString*)newUserInfoValue
{
  void *val = (void*)[self nsstringToCString:newUserInfoValue];
  int ret_code = IPWorks_XMPP_Set(m_pObj, 46, fieldIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (void)add:(NSString*)jabberId :(NSString*)name :(NSString*)groups
{
  void *param[3+1] = {(void*)[self nsstringToCString:jabberId], (void*)[self nsstringToCString:name], (void*)[self nsstringToCString:groups], NULL};
  int cbparam[3+1] = {0, 0, 0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 2, 3, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)cancel:(NSString*)jabberId
{
  void *param[1+1] = {(void*)[self nsstringToCString:jabberId], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 3, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)changePassword:(NSString*)password
{
  void *param[1+1] = {(void*)[self nsstringToCString:password], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 4, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)changePresence:(int)presenceCode :(NSString*)status
{
  void *param[2+1] = {(void*)(long)presenceCode, (void*)[self nsstringToCString:status], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 5, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 6, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)connect:(NSString*)user :(NSString*)password
{
  void *param[2+1] = {(void*)[self nsstringToCString:user], (void*)[self nsstringToCString:password], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 7, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)disconnect
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 8, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)doEvents
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 9, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)interrupt
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 10, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)probePresence:(NSString*)jabberId
{
  void *param[1+1] = {(void*)[self nsstringToCString:jabberId], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 11, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)queryRegister:(NSString*)XMPPServer
{
  void *param[1+1] = {(void*)[self nsstringToCString:XMPPServer], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 12, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)registerUser:(NSString*)XMPPServer
{
  void *param[1+1] = {(void*)[self nsstringToCString:XMPPServer], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 13, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)remove:(NSString*)jabberId :(NSString*)name :(NSString*)group
{
  void *param[3+1] = {(void*)[self nsstringToCString:jabberId], (void*)[self nsstringToCString:name], (void*)[self nsstringToCString:group], NULL};
  int cbparam[3+1] = {0, 0, 0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 14, 3, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 15, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)retrieveRoster
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 16, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)sendCommand:(NSString*)command
{
  void *param[1+1] = {(void*)[self nsstringToCString:command], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 17, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)sendFile:(NSString*)jabberId
{
  void *param[1+1] = {(void*)[self nsstringToCString:jabberId], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 18, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)sendMessage:(NSString*)jabberId
{
  void *param[1+1] = {(void*)[self nsstringToCString:jabberId], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 19, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)setUserInfo:(NSString*)field :(NSString*)value
{
  void *param[2+1] = {(void*)[self nsstringToCString:field], (void*)[self nsstringToCString:value], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 22, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)subscribeTo:(NSString*)jabberId
{
  void *param[1+1] = {(void*)[self nsstringToCString:jabberId], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 23, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)unregister
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 24, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)unsubscribeTo:(NSString*)jabberId
{
  void *param[1+1] = {(void*)[self nsstringToCString:jabberId], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XMPP_Do(m_pObj, 25, 1, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_XMPP_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_XMPP_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end