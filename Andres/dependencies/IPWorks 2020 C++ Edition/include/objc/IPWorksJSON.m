
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksJSON.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksJSON()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define JSON_EXTERN extern "C"
#else
#define JSON_EXTERN extern
#endif

JSON_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
JSON_EXTERN void* IPWorks_JSON_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
JSON_EXTERN int   IPWorks_JSON_Destroy(void* lpObj);
JSON_EXTERN int   IPWorks_JSON_CheckIndex(void* lpObj, int propid, int arridx);
JSON_EXTERN void* IPWorks_JSON_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
JSON_EXTERN int   IPWorks_JSON_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
JSON_EXTERN int   IPWorks_JSON_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
JSON_EXTERN char* IPWorks_JSON_GetLastError(void* lpObj);
JSON_EXTERN int   IPWorks_JSON_GetLastErrorCode(void* lpObj);
JSON_EXTERN int   IPWorks_JSON_SetLastErrorAndCode(void* lpObj, int code, char* message);
JSON_EXTERN char* IPWorks_JSON_GetEventError(void* lpObj);
JSON_EXTERN int   IPWorks_JSON_GetEventErrorCode(void* lpObj);
JSON_EXTERN int   IPWorks_JSON_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void JSON_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_JSON_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int JSON_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksJSON* ctl = (IPWorksJSON*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, JSON_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (JSON)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
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
    case 2 /*EID_ENDDOCUMENT*/: {
      @try {
        [ctl onEndDocument ];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EndDocument" :YES];
      }
      break;
    }
    case 3 /*EID_ENDELEMENT*/: {
      NSString* elementT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* element = elementT;
      @try {
        [ctl onEndElement :element];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"EndElement" :YES];
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
    case 5 /*EID_IGNORABLEWHITESPACE*/: {
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
    case 6 /*EID_JSON*/: {
      NSString* textT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* text = textT;
      @try {
        [ctl onJSON :text];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"JSON" :YES];
      }
      break;
    }
    case 7 /*EID_STARTDOCUMENT*/: {
      @try {
        [ctl onStartDocument ];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StartDocument" :YES];
      }
      break;
    }
    case 8 /*EID_STARTELEMENT*/: {
      NSString* elementT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* element = elementT;
      @try {
        [ctl onStartElement :element];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"StartElement" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksJSON

+ (IPWorksJSON*)json
{
#if __has_feature(objc_arc)
  return [[IPWorksJSON alloc] init];
#else
  return [[[IPWorksJSON alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_JSON_Create((void*)JSON_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_JSON_Create((void*)JSON_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_JSON_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_JSON_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_JSON_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_JSON_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_JSON_GetEventErrorCode(m_pObj);
}

- (id <IPWorksJSONDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksJSONDelegate>)anObject
{
  m_delegateHasCharacters = NO;
  m_delegateHasEndDocument = NO;
  m_delegateHasEndElement = NO;
  m_delegateHasError = NO;
  m_delegateHasIgnorableWhitespace = NO;
  m_delegateHasJSON = NO;
  m_delegateHasStartDocument = NO;
  m_delegateHasStartElement = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onCharacters:)]) m_delegateHasCharacters = YES;
    if ([m_delegate respondsToSelector:@selector(onEndDocument)]) m_delegateHasEndDocument = YES;
    if ([m_delegate respondsToSelector:@selector(onEndElement:)]) m_delegateHasEndElement = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onIgnorableWhitespace:)]) m_delegateHasIgnorableWhitespace = YES;
    if ([m_delegate respondsToSelector:@selector(onJSON:)]) m_delegateHasJSON = YES;
    if ([m_delegate respondsToSelector:@selector(onStartDocument)]) m_delegateHasStartDocument = YES;
    if ([m_delegate respondsToSelector:@selector(onStartElement:)]) m_delegateHasStartElement = YES;
  }
}

  /* Events */

- (void)onCharacters:(NSString*)text
{
  if (m_delegate != nil && m_delegateHasCharacters)
    [m_delegate onCharacters:text];
}
- (void)onEndDocument
{
  if (m_delegate != nil && m_delegateHasEndDocument)
    [m_delegate onEndDocument];
}
- (void)onEndElement:(NSString*)element
{
  if (m_delegate != nil && m_delegateHasEndElement)
    [m_delegate onEndElement:element];
}
- (void)onError:(int)errorCode :(NSString*)description
{
  if (m_delegate != nil && m_delegateHasError)
    [m_delegate onError:errorCode :description];
}
- (void)onIgnorableWhitespace:(NSString*)text
{
  if (m_delegate != nil && m_delegateHasIgnorableWhitespace)
    [m_delegate onIgnorableWhitespace:text];
}
- (void)onJSON:(NSString*)text
{
  if (m_delegate != nil && m_delegateHasJSON)
    [m_delegate onJSON:text];
}
- (void)onStartDocument
{
  if (m_delegate != nil && m_delegateHasStartDocument)
    [m_delegate onStartDocument];
}
- (void)onStartElement:(NSString*)element
{
  if (m_delegate != nil && m_delegateHasStartElement)
    [m_delegate onStartElement:element];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_JSON_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_JSON_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_JSON_Get(m_pObj, 0, 0, 0, nil);
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

- (BOOL)buildDOM
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setBuildDOM:(BOOL)newBuildDOM
{
  void *val = (void*)(long)(newBuildDOM ? 1 : 0);
  int ret_code = IPWorks_JSON_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)inputData
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setInputData:(NSString*)newInputData
{
  void *val = (void*)[self nsstringToCString:newInputData];
  int ret_code = IPWorks_JSON_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)inputFile
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setInputFile:(NSString*)newInputFile
{
  void *val = (void*)[self nsstringToCString:newInputFile];
  int ret_code = IPWorks_JSON_Set(m_pObj, 3, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)outputData
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOutputData:(NSString*)newOutputData
{
  void *val = (void*)[self nsstringToCString:newOutputData];
  int ret_code = IPWorks_JSON_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)outputFile
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 5, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOutputFile:(NSString*)newOutputFile
{
  void *val = (void*)[self nsstringToCString:newOutputFile];
  int ret_code = IPWorks_JSON_Set(m_pObj, 5, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)overwrite
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 6, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setOverwrite:(BOOL)newOverwrite
{
  void *val = (void*)(long)(newOverwrite ? 1 : 0);
  int ret_code = IPWorks_JSON_Set(m_pObj, 6, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)validate
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setValidate:(BOOL)newValidate
{
  void *val = (void*)(long)(newValidate ? 1 : 0);
  int ret_code = IPWorks_JSON_Set(m_pObj, 7, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)XChildCount
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setXChildCount:(int)newXChildCount
{
  void *val = (void*)(long)newXChildCount;
  int ret_code = IPWorks_JSON_Set(m_pObj, 8, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XChildName:(int)xChildIndex
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 9, xChildIndex, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XChildXText:(int)xChildIndex
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 10, xChildIndex, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XElement
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXElement:(NSString*)newXElement
{
  void *val = (void*)[self nsstringToCString:newXElement];
  int ret_code = IPWorks_JSON_Set(m_pObj, 11, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)XElementType
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 12, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (NSString*)XErrorPath
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 13, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXErrorPath:(NSString*)newXErrorPath
{
  void *val = (void*)[self nsstringToCString:newXErrorPath];
  int ret_code = IPWorks_JSON_Set(m_pObj, 13, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XParent
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 14, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XPath
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 15, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXPath:(NSString*)newXPath
{
  void *val = (void*)[self nsstringToCString:newXPath];
  int ret_code = IPWorks_JSON_Set(m_pObj, 15, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XSubTree
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XText
{
  int len = 0;
  void* val=IPWorks_JSON_Get(m_pObj, 17, 0, &len, nil);
  if (IPWorks_JSON_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXText:(NSString*)newXText
{
  void *val = (void*)[self nsstringToCString:newXText];
  int ret_code = IPWorks_JSON_Set(m_pObj, 17, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)endArray
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)endObject
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 4, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)flush
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 5, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)hasXPath:(NSString*)XPath
{
  void *param[1+1] = {(void*)[self nsstringToCString:XPath], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 9, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return param[1] ? YES : NO;
}

- (void)insertProperty:(NSString*)name :(NSString*)value :(int)valueType :(int)position
{
  void *param[4+1] = {(void*)[self nsstringToCString:name], (void*)[self nsstringToCString:value], (void*)(long)valueType, (void*)(long)position, NULL};
  int cbparam[4+1] = {0, 0, 0, 0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 10, 4, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)insertValue:(NSString*)value :(int)valueType :(int)position
{
  void *param[3+1] = {(void*)[self nsstringToCString:value], (void*)(long)valueType, (void*)(long)position, NULL};
  int cbparam[3+1] = {0, 0, 0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 11, 3, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)loadSchema:(NSString*)schema
{
  void *param[1+1] = {(void*)[self nsstringToCString:schema], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 12, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)parse
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 13, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putName:(NSString*)name
{
  void *param[1+1] = {(void*)[self nsstringToCString:name], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 14, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putProperty:(NSString*)name :(NSString*)value :(int)valueType
{
  void *param[3+1] = {(void*)[self nsstringToCString:name], (void*)[self nsstringToCString:value], (void*)(long)valueType, NULL};
  int cbparam[3+1] = {0, 0, 0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 15, 3, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putRaw:(NSString*)text
{
  void *param[1+1] = {(void*)[self nsstringToCString:text], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 16, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putValue:(NSString*)value :(int)valueType
{
  void *param[2+1] = {(void*)[self nsstringToCString:value], (void*)(long)valueType, NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 17, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)remove
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 18, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 19, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)save
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 20, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setName:(NSString*)name
{
  void *param[1+1] = {(void*)[self nsstringToCString:name], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 22, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)setValue:(NSString*)value :(int)valueType
{
  void *param[2+1] = {(void*)[self nsstringToCString:value], (void*)(long)valueType, NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 24, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)startArray
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 25, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)startObject
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 26, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)tryXPath:(NSString*)xpath
{
  void *param[1+1] = {(void*)[self nsstringToCString:xpath], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_JSON_Do(m_pObj, 27, 1, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_JSON_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_JSON_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end