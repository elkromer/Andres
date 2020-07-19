
/******************************************************************
  IPWorks 2020 for macOS and iOS
  Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import "IPWorksXML.h"
#ifndef __has_feature
#define __has_feature(x) 0
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#define ENCODING_CONVERSION_ERROR @"Cannot convert string using specified encoding."
#define BUFFER_TOO_SMALL_CONVERSION_ERROR @"Cannot convert string, too large for destination buffer."

@interface IPWorksXML()
- (const char*)nsstringToCString:(NSString*)str;
- (int)nsstringToSPtr:(NSString*)str :(char*)dest :(int)destLen;
- (NSDate*)longLongToNSDate:(long long)secsSince1970;
- (long long)nsdateToLongLong:(NSDate*)date;
- (NSStringEncoding)innerGetCodePage;
- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire;
@end

#if __cplusplus
#define XML_EXTERN extern "C"
#else
#define XML_EXTERN extern
#endif

XML_EXTERN void* IPWorks_EvtStr(void* lpEvtStr, int esid, void* val, int opt);
XML_EXTERN void* IPWorks_XML_Create(void* lpSink, void* lpContext, char* lpOemKey, int opts);
XML_EXTERN int   IPWorks_XML_Destroy(void* lpObj);
XML_EXTERN int   IPWorks_XML_CheckIndex(void* lpObj, int propid, int arridx);
XML_EXTERN void* IPWorks_XML_Get(void* lpObj, int propid, int arridx, int* lpcbVal, long long* lpllVal);
XML_EXTERN int   IPWorks_XML_Set(void* lpObj, int propid, int arridx, void* val, int cbVal);
XML_EXTERN int   IPWorks_XML_Do(void* lpObj, int methid, int cparam, void* param[], int cbparam[], long long* lpllVal);
XML_EXTERN char* IPWorks_XML_GetLastError(void* lpObj);
XML_EXTERN int   IPWorks_XML_GetLastErrorCode(void* lpObj);
XML_EXTERN int   IPWorks_XML_SetLastErrorAndCode(void* lpObj, int code, char* message);
XML_EXTERN char* IPWorks_XML_GetEventError(void* lpObj);
XML_EXTERN int   IPWorks_XML_GetEventErrorCode(void* lpObj);
XML_EXTERN int   IPWorks_XML_SetEventErrorAndCode(void* lpObj, int code, char* message);

static void XML_cCallBack(CFSocketRef s, CFSocketCallBackType ct, CFDataRef addr, const void *data, void *info) {
  void* param[1] = {(void*)(long)CFSocketGetNative(s)};
  IPWorks_XML_Do(info, 2002/*MID_DOSOCKETEVENTS*/, 1, param, 0, nil);
}

#if !TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif

static int XML_cSink(id lpObj, int event_id, int cparam, void* param[], int cbparam[]) {
  IPWorksXML* ctl = (IPWorksXML*)lpObj;

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
        void* notifier = (void*)CFSocketCreateWithNative(NULL, (CFSocketNativeHandle)((unsigned long)param[0]), evtflags, XML_cCallBack, &ctx);

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
      UIAlertView *myAlert = [[UIAlertView alloc] initWithTitle:@"IPWorks 2020 (XML)" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
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
    case 3 /*EID_ENDELEMENT*/: {
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
    case 4 /*EID_ENDPREFIXMAPPING*/: {
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
    case 6 /*EID_EVALENTITY*/: {
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
    case 7 /*EID_IGNORABLEWHITESPACE*/: {
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
    case 8 /*EID_META*/: {
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
    case 9 /*EID_PI*/: {
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
    case 10 /*EID_SPECIALSECTION*/: {
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
    case 11 /*EID_STARTELEMENT*/: {
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
    case 12 /*EID_STARTPREFIXMAPPING*/: {
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
    case 13 /*EID_XML*/: {
      NSString* textT = [NSString stringWithCString:(const char*)param[0] encoding:[ctl innerGetCodePage]];
      NSString* text = textT;
      @try {
        [ctl onXML :text];
      }
      @catch (NSException* e) {
        [ctl reportEventException:e :@"XML" :YES];
      }
      break;
    }

  }
  return [ctl eventErrorCode]; // So we emulate true C++ event error reporting regardless of whether the error happened in Obj-C or Swift.
}

@implementation IPWorksXML

+ (IPWorksXML*)xml
{
#if __has_feature(objc_arc)
  return [[IPWorksXML alloc] init];
#else
  return [[[IPWorksXML alloc] init] autorelease];
#endif
}

- (id)init
{
  self = [super init];
  if (!self) return nil;

  m_rNotifiers = CFArrayCreateMutable(NULL, 0, &kCFTypeArrayCallBacks);
#if __has_feature(objc_arc)
  m_pObj = IPWorks_XML_Create((void*)XML_cSink, (__bridge void*)self, (char *)"\1\1\1MAC\1\1\1", 0);
#else
  m_pObj = IPWorks_XML_Create((void*)XML_cSink, self, (char *)"\1\1\1MAC\1\1\1", 0);
#endif
  if (m_pObj) IPWorks_XML_Do(m_pObj, 2001/*MID_ENABLEASYNCEVENTS*/, 0, 0, 0, nil);

  m_raiseNSException = YES;

  return self;
}

- (void)dealloc
{
  if (m_pObj) {
    IPWorks_XML_Destroy(m_pObj);
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
  return [NSString stringWithCString:(const char*)IPWorks_XML_GetLastError(m_pObj) encoding:[self innerGetCodePage]];
}

- (int)lastErrorCode
{
  return IPWorks_XML_GetLastErrorCode(m_pObj);
}

- (int)eventErrorCode
{
  return IPWorks_XML_GetEventErrorCode(m_pObj);
}

- (id <IPWorksXMLDelegate>)delegate
{
  return m_delegate;
}

- (void) setDelegate:(id <IPWorksXMLDelegate>)anObject
{
  m_delegateHasCharacters = NO;
  m_delegateHasComment = NO;
  m_delegateHasEndElement = NO;
  m_delegateHasEndPrefixMapping = NO;
  m_delegateHasError = NO;
  m_delegateHasEvalEntity = NO;
  m_delegateHasIgnorableWhitespace = NO;
  m_delegateHasMeta = NO;
  m_delegateHasPI = NO;
  m_delegateHasSpecialSection = NO;
  m_delegateHasStartElement = NO;
  m_delegateHasStartPrefixMapping = NO;
  m_delegateHasXML = NO;

  m_delegate = anObject;
  if (m_delegate != nil) {
    if ([m_delegate respondsToSelector:@selector(onCharacters:)]) m_delegateHasCharacters = YES;
    if ([m_delegate respondsToSelector:@selector(onComment:)]) m_delegateHasComment = YES;
    if ([m_delegate respondsToSelector:@selector(onEndElement::::)]) m_delegateHasEndElement = YES;
    if ([m_delegate respondsToSelector:@selector(onEndPrefixMapping:)]) m_delegateHasEndPrefixMapping = YES;
    if ([m_delegate respondsToSelector:@selector(onError::)]) m_delegateHasError = YES;
    if ([m_delegate respondsToSelector:@selector(onEvalEntity::)]) m_delegateHasEvalEntity = YES;
    if ([m_delegate respondsToSelector:@selector(onIgnorableWhitespace:)]) m_delegateHasIgnorableWhitespace = YES;
    if ([m_delegate respondsToSelector:@selector(onMeta:)]) m_delegateHasMeta = YES;
    if ([m_delegate respondsToSelector:@selector(onPI:)]) m_delegateHasPI = YES;
    if ([m_delegate respondsToSelector:@selector(onSpecialSection::)]) m_delegateHasSpecialSection = YES;
    if ([m_delegate respondsToSelector:@selector(onStartElement::::)]) m_delegateHasStartElement = YES;
    if ([m_delegate respondsToSelector:@selector(onStartPrefixMapping::)]) m_delegateHasStartPrefixMapping = YES;
    if ([m_delegate respondsToSelector:@selector(onXML:)]) m_delegateHasXML = YES;
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
- (void)onIgnorableWhitespace:(NSString*)text
{
  if (m_delegate != nil && m_delegateHasIgnorableWhitespace)
    [m_delegate onIgnorableWhitespace:text];
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
- (void)onSpecialSection:(NSString*)sectionId :(NSString*)text
{
  if (m_delegate != nil && m_delegateHasSpecialSection)
    [m_delegate onSpecialSection:sectionId :text];
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
- (void)onXML:(NSString*)text
{
  if (m_delegate != nil && m_delegateHasXML)
    [m_delegate onXML:text];
}

  /* Properties */

- (NSString*)RuntimeLicense
{
  int len = 0;
  void* val = IPWorks_XML_Get(m_pObj, 2011, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj)) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setRuntimeLicense:(NSString*)newRuntimeLicense
{
  int len = 0;
  void *val = (void*)[self nsstringToCString:newRuntimeLicense];
  int ret_code = IPWorks_XML_Set(m_pObj, 2011, 0, val, len);
  if (ret_code) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)VERSION
{
  void* val = IPWorks_XML_Get(m_pObj, 0, 0, 0, nil);
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
  void* val=IPWorks_XML_Get(m_pObj, 1, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setBuildDOM:(BOOL)newBuildDOM
{
  void *val = (void*)(long)(newBuildDOM ? 1 : 0);
  int ret_code = IPWorks_XML_Set(m_pObj, 1, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)inputData
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 2, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setInputData:(NSString*)newInputData
{
  void *val = (void*)[self nsstringToCString:newInputData];
  int ret_code = IPWorks_XML_Set(m_pObj, 2, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)inputFile
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 3, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setInputFile:(NSString*)newInputFile
{
  void *val = (void*)[self nsstringToCString:newInputFile];
  int ret_code = IPWorks_XML_Set(m_pObj, 3, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)namespaceCount
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 4, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setNamespaceCount:(int)newNamespaceCount
{
  void *val = (void*)(long)newNamespaceCount;
  int ret_code = IPWorks_XML_Set(m_pObj, 4, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)namespacePrefix:(int)namespaceIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 5, namespaceIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setNamespacePrefix:(int)namespaceIndex:(NSString*)newNamespacePrefix
{
  void *val = (void*)[self nsstringToCString:newNamespacePrefix];
  int ret_code = IPWorks_XML_Set(m_pObj, 5, namespaceIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)namespaceURI:(int)namespaceIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 6, namespaceIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setNamespaceURI:(int)namespaceIndex:(NSString*)newNamespaceURI
{
  void *val = (void*)[self nsstringToCString:newNamespaceURI];
  int ret_code = IPWorks_XML_Set(m_pObj, 6, namespaceIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)outputData
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 7, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOutputData:(NSString*)newOutputData
{
  void *val = (void*)[self nsstringToCString:newOutputData];
  int ret_code = IPWorks_XML_Set(m_pObj, 7, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)outputFile
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 8, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setOutputFile:(NSString*)newOutputFile
{
  void *val = (void*)[self nsstringToCString:newOutputFile];
  int ret_code = IPWorks_XML_Set(m_pObj, 8, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)overwrite
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 9, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setOverwrite:(BOOL)newOverwrite
{
  void *val = (void*)(long)(newOverwrite ? 1 : 0);
  int ret_code = IPWorks_XML_Set(m_pObj, 9, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)validate
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 10, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setValidate:(BOOL)newValidate
{
  void *val = (void*)(long)(newValidate ? 1 : 0);
  int ret_code = IPWorks_XML_Set(m_pObj, 10, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (int)attrCount
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 11, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setAttrCount:(int)newAttrCount
{
  void *val = (void*)(long)newAttrCount;
  int ret_code = IPWorks_XML_Set(m_pObj, 11, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)attrName:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 12, attrIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)attrNamespace:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 13, attrIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)attrPrefix:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 14, attrIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)attrValue:(int)attrIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 15, attrIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)XChildCount
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 16, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setXChildCount:(int)newXChildCount
{
  void *val = (void*)(long)newXChildCount;
  int ret_code = IPWorks_XML_Set(m_pObj, 16, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XChildName:(int)xChildIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 17, xChildIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XChildNamespace:(int)xChildIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 18, xChildIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XChildPrefix:(int)xChildIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 19, xChildIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XChildXText:(int)xChildIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 20, xChildIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (int)XCommentCount
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 21, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return (int)(long)val;
}

- (void)setXCommentCount:(int)newXCommentCount
{
  void *val = (void*)(long)newXCommentCount;
  int ret_code = IPWorks_XML_Set(m_pObj, 21, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XCommentText:(int)xCommentIndex
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 22, xCommentIndex, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXCommentText:(int)xCommentIndex:(NSString*)newXCommentText
{
  void *val = (void*)[self nsstringToCString:newXCommentText];
  int ret_code = IPWorks_XML_Set(m_pObj, 22, xCommentIndex, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XElement
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 23, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXElement:(NSString*)newXElement
{
  void *val = (void*)[self nsstringToCString:newXElement];
  int ret_code = IPWorks_XML_Set(m_pObj, 23, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XMLDeclarationEncoding
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 24, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXMLDeclarationEncoding:(NSString*)newXMLDeclarationEncoding
{
  void *val = (void*)[self nsstringToCString:newXMLDeclarationEncoding];
  int ret_code = IPWorks_XML_Set(m_pObj, 24, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)XMLDeclarationStandalone
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 25, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return val ? YES : NO;
}

- (void)setXMLDeclarationStandalone:(BOOL)newXMLDeclarationStandalone
{
  void *val = (void*)(long)(newXMLDeclarationStandalone ? 1 : 0);
  int ret_code = IPWorks_XML_Set(m_pObj, 25, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XMLDeclarationVersion
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 26, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXMLDeclarationVersion:(NSString*)newXMLDeclarationVersion
{
  void *val = (void*)[self nsstringToCString:newXMLDeclarationVersion];
  int ret_code = IPWorks_XML_Set(m_pObj, 26, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XNamespace
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 27, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXNamespace:(NSString*)newXNamespace
{
  void *val = (void*)[self nsstringToCString:newXNamespace];
  int ret_code = IPWorks_XML_Set(m_pObj, 27, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XParent
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 28, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XPath
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 29, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXPath:(NSString*)newXPath
{
  void *val = (void*)[self nsstringToCString:newXPath];
  int ret_code = IPWorks_XML_Set(m_pObj, 29, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XPrefix
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 30, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXPrefix:(NSString*)newXPrefix
{
  void *val = (void*)[self nsstringToCString:newXPrefix];
  int ret_code = IPWorks_XML_Set(m_pObj, 30, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)XSubTree
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 31, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (NSString*)XText
{
  int len = 0;
  void* val=IPWorks_XML_Get(m_pObj, 32, 0, &len, nil);
  if (IPWorks_XML_GetLastErrorCode(m_pObj) && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)val encoding:[self innerGetCodePage]];
}

- (void)setXText:(NSString*)newXText
{
  void *val = (void*)[self nsstringToCString:newXText];
  int ret_code = IPWorks_XML_Set(m_pObj, 32, 0, val, 0);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

  /* Methods */

- (NSString*)config:(NSString*)configurationString
{
  void *param[1+1] = {(void*)[self nsstringToCString:configurationString], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 2, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (void)endElement
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XML_Do(m_pObj, 3, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)flush
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XML_Do(m_pObj, 4, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (NSString*)getAttr:(NSString*)attrName
{
  void *param[1+1] = {(void*)[self nsstringToCString:attrName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 5, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return [NSString stringWithCString:(const char*)param[1] encoding:[self innerGetCodePage]];
}

- (BOOL)hasXPath:(NSString*)XPath
{
  void *param[1+1] = {(void*)[self nsstringToCString:XPath], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 6, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
  return param[1] ? YES : NO;
}

- (void)loadDOM:(NSString*)fileName
{
  void *param[1+1] = {(void*)[self nsstringToCString:fileName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 7, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)loadSchema:(NSString*)schema
{
  void *param[1+1] = {(void*)[self nsstringToCString:schema], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 8, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)parse
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XML_Do(m_pObj, 9, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putAttr:(NSString*)name :(NSString*)namespaceURI :(NSString*)value
{
  void *param[3+1] = {(void*)[self nsstringToCString:name], (void*)[self nsstringToCString:namespaceURI], (void*)[self nsstringToCString:value], NULL};
  int cbparam[3+1] = {0, 0, 0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 10, 3, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putCData:(NSString*)text
{
  void *param[1+1] = {(void*)[self nsstringToCString:text], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 11, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putComment:(NSString*)text
{
  void *param[1+1] = {(void*)[self nsstringToCString:text], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 12, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putElement:(NSString*)name :(NSString*)namespaceURI :(NSString*)value
{
  void *param[3+1] = {(void*)[self nsstringToCString:name], (void*)[self nsstringToCString:namespaceURI], (void*)[self nsstringToCString:value], NULL};
  int cbparam[3+1] = {0, 0, 0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 13, 3, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putRaw:(NSString*)text
{
  void *param[1+1] = {(void*)[self nsstringToCString:text], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 14, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)putString:(NSString*)text
{
  void *param[1+1] = {(void*)[self nsstringToCString:text], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 15, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)removeAttr:(NSString*)attrName
{
  void *param[1+1] = {(void*)[self nsstringToCString:attrName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 16, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)removeChildren
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XML_Do(m_pObj, 17, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)removeElement
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XML_Do(m_pObj, 18, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)reset
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XML_Do(m_pObj, 19, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)save
{
  void *param[0+1] = {NULL};
  int cbparam[0+1] = {0};

  int ret_code = IPWorks_XML_Do(m_pObj, 20, 0, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)saveDOM:(NSString*)fileName
{
  void *param[1+1] = {(void*)[self nsstringToCString:fileName], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 21, 1, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (void)startElement:(NSString*)name :(NSString*)namespaceURI
{
  void *param[2+1] = {(void*)[self nsstringToCString:name], (void*)[self nsstringToCString:namespaceURI], NULL};
  int cbparam[2+1] = {0, 0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 24, 2, param, cbparam, nil);
  if (ret_code && m_raiseNSException) [NSException raise:[self lastError] format:@"%@", [self lastError]];
}

- (BOOL)tryXPath:(NSString*)xpath
{
  void *param[1+1] = {(void*)[self nsstringToCString:xpath], NULL};
  int cbparam[1+1] = {0, 0};

  int ret_code = IPWorks_XML_Do(m_pObj, 25, 1, param, cbparam, nil);
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
  int codePage = (int)(long)IPWorks_XML_Get(m_pObj, 2010, 0, &len, nil);
  if (codePage == 0) return NSUTF8StringEncoding;
  return (NSStringEncoding)codePage;
}

- (void)reportEventException:(NSException*)ex :(NSString*)event :(BOOL)reFire {
  NSString* msg = [NSString stringWithFormat:@"An unhandled error occurred in the %@ event handler: %@", event, [ex reason]];
  IPWorks_XML_SetEventErrorAndCode(m_pObj, -1, [self nsstringToCString:msg]);
  if (reFire) [self onError:-1 :msg];
}
@end