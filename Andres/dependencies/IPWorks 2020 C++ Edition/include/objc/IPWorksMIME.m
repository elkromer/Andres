
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksMIME.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksMIME()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define MIME_EXTERN extern "C"
#else
#define MIME_EXTERN extern
#endif

MIME_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
MIME_EXTERN void* IPWorks_MIME_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
MIME_EXTERN int   IPWorks_MIME_Destroy(void* lpObj);
MIME_EXTERN int   IPWorks_MIME_CheckIndex(void* lpObj, int propid, int arridx);
MIME_EXTERN void* IPWorks_MIME_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
MIME_EXTERN int   IPWorks_MIME_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
MIME_EXTERN int   IPWorks_MIME_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
MIME_EXTERN char* IPWorks_MIME_GetLastError(void* lpObj);
MIME_EXTERN int   IPWorks_MIME_GetLastErrorCode(void* lpObj);
MIME_EXTERN int   IPWorks_MIME_SetLastErrorAndCode(void* lpObj, int code, char* message);
MIME_EXTERN char* IPWorks_MIME_GetEventError(void* lpObj);
MIME_EXTERN int   IPWorks_MIME_GetEventErrorCode(void* lpObj);
MIME_EXTERN int   IPWorks_MIME_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void MIME_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_MIME_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int MIME_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksMIME* ctl = (IPWorksMIME*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, MIME_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (MIME)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
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
    case 2 /*EID_HEADER*/: {
      int partIndex = (int)(long)param[0];
      NSString* fieldT = [NSString stringWithCString:(const char*)param[1] encoding:[ctl innerGetCodePage]];
      NSString* field = fieldT;
      NSData* value = [NSData dataWithBytesNoCopy:param[2] length:cbparam[2] freeWhenDone:NO];
      @try {
        [ctl onHeader :partIndex :field :value];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Header" :YES];
      }
      break;
    }
    case 3 /*EID_PROGRESS*/: {
      int percentDone = (int)(long)param[0];
      @try {
        [ctl onProgress :percentDone];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"Progress" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksMIME

+ (IPWorksMIME*)mime
{
#if __has_feature(objc_arc)
  return [[IPWorksMIME alloc] init];
#else
  return [[[IPWorksMIME alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_MIME_Create((void*)MIME_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_MIME_Create((void*)MIME_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_MIME_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_MIME_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_MIME_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_MIME_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_MIME_GetEventErrorCode(m_pObj);
}

- (id <IPWorksMIMEDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksMIMEDelegate>)anObject
{
  m_delegateHasError = NO;
  m_delegateHasHeader = NO;
  m_delegateHasProgress = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onHeader:::)]) m_delegateHasHeader = YES;
    if ([m_delegate respondsToSelector:@selector(onProgress:)]) m_delegateHasProgress = YES;
  }
}

  /* Events */

- (void)onError:(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:errorCode :description];
}
- (void)onHeader:(int)partIndex :(NSString*)field :(NSData*)value
{
  if (m_delegate != nil && m_delegateHasHeader)
    [m_delegate onHeader:partIndex :field :value];
}
- (void)onProgress:(int)percentDone
{
  if (m_delegate != nil && m_delegateHasProgress)
    [m_delegate onProgress:percentDone];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_MIME_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_MIME_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_MIME_Get(m_pObj, 0, 0, 0, nil);
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

- (NSString*)boundary
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setBoundary:(NSString*)newBoundary
{
  void *val = (void*)[self nsstringToCString:newBoundary];
  int ret_code = IPWorks_MIME_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)contentType
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setContentType:(NSString*)newContentType
{
  void *val = (void*)[self nsstringToCString:newContentType];
  int ret_code = IPWorks_MIME_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)contentTypeAttr
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setContentTypeAttr:(NSString*)newContentTypeAttr
{
  void *val = (void*)[self nsstringToCString:newContentTypeAttr];
  int ret_code = IPWorks_MIME_Set(m_pObj, 3, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)message
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setMessage:(NSString*)newMessage
{
  int len = (int)[newMessage lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newMessage];
  int ret_code = IPWorks_MIME_Set(m_pObj, 4, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)messageB
{
  int len = 0;
  void* val = IPWorks_MIME_Get(m_pObj, 4, 0, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setMessageB :(NSData*)newMessage
{
  int len = (int)[newMessage length];
  void *val = (void*)[newMessage bytes];
  int ret_code = IPWorks_MIME_Set(m_pObj, 4, 0, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)messageHeaderCount
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setMessageHeaderCount:(int)newMessageHeaderCount
{
  void *val = (void*)(long)newMessageHeaderCount;
  int ret_code = IPWorks_MIME_Set(m_pObj, 5, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageHeaderField:(int)messageHeaderIndex
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 6, messageHeaderIndex, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageHeaderField:(int)messageHeaderIndex:(NSString*)newMessageHeaderField
{
  void *val = (void*)[self nsstringToCString:newMessageHeaderField];
  int ret_code = IPWorks_MIME_Set(m_pObj, 6, messageHeaderIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageHeaderValue:(int)messageHeaderIndex
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 7, messageHeaderIndex, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageHeaderValue:(int)messageHeaderIndex:(NSString*)newMessageHeaderValue
{
  void *val = (void*)[self nsstringToCString:newMessageHeaderValue];
  int ret_code = IPWorks_MIME_Set(m_pObj, 7, messageHeaderIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)messageHeadersString
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setMessageHeadersString:(NSString*)newMessageHeadersString
{
  void *val = (void*)[self nsstringToCString:newMessageHeadersString];
  int ret_code = IPWorks_MIME_Set(m_pObj, 8, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)partCount
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setPartCount:(int)newPartCount
{
  void *val = (void*)(long)newPartCount;
  int ret_code = IPWorks_MIME_Set(m_pObj, 9, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)partContentDisposition:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 10, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPartContentDisposition:(int)partIdx:(NSString*)newPartContentDisposition
{
  void *val = (void*)[self nsstringToCString:newPartContentDisposition];
  int ret_code = IPWorks_MIME_Set(m_pObj, 10, partIdx, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)partContentDispositionAttr:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 11, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPartContentDispositionAttr:(int)partIdx:(NSString*)newPartContentDispositionAttr
{
  void *val = (void*)[self nsstringToCString:newPartContentDispositionAttr];
  int ret_code = IPWorks_MIME_Set(m_pObj, 11, partIdx, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)partContentId:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 12, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPartContentId:(int)partIdx:(NSString*)newPartContentId
{
  void *val = (void*)[self nsstringToCString:newPartContentId];
  int ret_code = IPWorks_MIME_Set(m_pObj, 12, partIdx, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)partContentType:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 13, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPartContentType:(int)partIdx:(NSString*)newPartContentType
{
  void *val = (void*)[self nsstringToCString:newPartContentType];
  int ret_code = IPWorks_MIME_Set(m_pObj, 13, partIdx, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)partContentTypeAttr:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 14, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPartContentTypeAttr:(int)partIdx:(NSString*)newPartContentTypeAttr
{
  void *val = (void*)[self nsstringToCString:newPartContentTypeAttr];
  int ret_code = IPWorks_MIME_Set(m_pObj, 14, partIdx, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)partDecodedFile:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 15, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPartDecodedFile:(int)partIdx:(NSString*)newPartDecodedFile
{
  void *val = (void*)[self nsstringToCString:newPartDecodedFile];
  int ret_code = IPWorks_MIME_Set(m_pObj, 15, partIdx, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)partDecodedString:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 16, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [[NSString alloc] initWithBytes:val length:len encoding:[self innerGetCodePage]];
}

- (void)setPartDecodedString:(int)partIdx:(NSString*)newPartDecodedString
{
  int len = (int)[newPartDecodedString lengthOfBytesUsingEncoding:[self innerGetCodePage]];
  void *val = (void*)[self nsstringToCString:newPartDecodedString];
  int ret_code = IPWorks_MIME_Set(m_pObj, 16, partIdx, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSData*)partDecodedStringB:(int)partIdx
{
  int len = 0;
  void* val = IPWorks_MIME_Get(m_pObj, 16, partIdx, &len, nil);
  return [NSData dataWithBytesNoCopy:val length:len freeWhenDone:NO];
}

- (void)setPartDecodedStringB:(int)partIdx :(NSData*)newPartDecodedString
{
  int len = (int)[newPartDecodedString length];
  void *val = (void*)[newPartDecodedString bytes];
  int ret_code = IPWorks_MIME_Set(m_pObj, 16, partIdx, val, len);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)partEncoding:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 17, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setPartEncoding:(int)partIdx:(int)newPartEncoding
{
  void *val = (void*)(long)newPartEncoding;
  int ret_code = IPWorks_MIME_Set(m_pObj, 17, partIdx, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)partFilename:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 18, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPartFilename:(int)partIdx:(NSString*)newPartFilename
{
  void *val = (void*)[self nsstringToCString:newPartFilename];
  int ret_code = IPWorks_MIME_Set(m_pObj, 18, partIdx, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)partHeaders:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 19, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPartHeaders:(int)partIdx:(NSString*)newPartHeaders
{
  void *val = (void*)[self nsstringToCString:newPartHeaders];
  int ret_code = IPWorks_MIME_Set(m_pObj, 19, partIdx, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)partName:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 20, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setPartName:(int)partIdx:(NSString*)newPartName
{
  void *val = (void*)[self nsstringToCString:newPartName];
  int ret_code = IPWorks_MIME_Set(m_pObj, 20, partIdx, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)partSize:(int)partIdx
{
  int len = 0;
  void* val=IPWorks_MIME_Get(m_pObj, 21, partIdx, &len, nil);
  if (IPWorks_MIME_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

  /* Methods */

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_MIME_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)decodeFromFile
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_MIME_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)decodeFromString
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_MIME_Do(m_pObj, 5, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)encodeToFile
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_MIME_Do(m_pObj, 6, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)encodeToString
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_MIME_Do(m_pObj, 8, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_MIME_Do(m_pObj, 9, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)resetData
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_MIME_Do(m_pObj, 10, 0, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_MIME_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_MIME_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end