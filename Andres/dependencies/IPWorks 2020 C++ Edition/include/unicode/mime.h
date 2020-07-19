/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_MIME_H_
#define _IPWORKS_MIME_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//MIMEPartEncodings
#define PE_7BIT                                            0
#define PE_QUOTED_PRINTABLE                                1
#define PE_BASE_64                                         2
#define PE_8BIT                                            3
#define PE_BINARY                                          4
#define PE_UUENCODE                                        5


extern "C" void* IPWORKS_CALL IPWorks_MIME_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_MIME_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_MIME_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_MIME_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_MIME_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_MIME_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_MIME_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_MIME_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_MIME_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} MIMEErrorEventParams;

typedef struct {
  INT PartIndex;
  LPCWSTR Field;
  LPCSTR Value;
  INT lenValue;
  INT reserved;
} MIMEHeaderEventParams;

typedef struct {
  INT PercentDone;
  INT reserved;
} MIMEProgressEventParams;


class MIME {
  public: // Events
    virtual INT FireError(MIMEErrorEventParams *e) {return 0;}
    virtual INT FireHeader(MIMEHeaderEventParams *e) {return 0;}
    virtual INT FireProgress(MIMEProgressEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL MIMEEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          MIMEErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((MIME*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          MIMEHeaderEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPSTR)param[2], (INT)cbparam[2], 0};
          ret_code = ((MIME*)lpObj)->FireHeader(&e);
          break;
        }
        case 3: {
          MIMEProgressEventParams e = {(INT)param[0], 0};
          ret_code = ((MIME*)lpObj)->FireProgress(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    MIME(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_28) {
      m_pObj = IPWorks_MIME_Create(MIMEEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~MIME() {
      IPWorks_MIME_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_MIME_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_MIME_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_MIME_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_MIME_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_MIME_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetBoundary() {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetBoundary(LPCWSTR lpszBoundary) {
      return IPWorks_MIME_Set(m_pObj, 1+10000, 0, (LPVOID)lpszBoundary, 0);
    }

    inline LPWSTR GetContentType() {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetContentType(LPCWSTR lpszContentType) {
      return IPWorks_MIME_Set(m_pObj, 2+10000, 0, (LPVOID)lpszContentType, 0);
    }

    inline LPWSTR GetContentTypeAttr() {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetContentTypeAttr(LPCWSTR lpszContentTypeAttr) {
      return IPWorks_MIME_Set(m_pObj, 3+10000, 0, (LPVOID)lpszContentTypeAttr, 0);
    }

    inline INT GetMessage(LPSTR &lpMessage, INT &lenMessage) {
      lpMessage = (LPSTR)IPWorks_MIME_Get(m_pObj, 4, 0, &lenMessage, NULL);
      return lpMessage ? 0 : lenMessage;
    }
    inline INT SetMessage(LPCSTR lpMessage, INT lenMessage) {
      return IPWorks_MIME_Set(m_pObj, 4, 0, (LPVOID)lpMessage, lenMessage);
    }

    inline INT GetMessageHeaderCount() {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 5, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMessageHeaderCount(INT iMessageHeaderCount) {
      LPVOID val = (LPVOID)(iMessageHeaderCount);
      return IPWorks_MIME_Set(m_pObj, 5, 0, val, 0);
    }

    inline LPWSTR GetMessageHeaderField(INT iMessageHeaderIndex) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 6+10000, iMessageHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageHeaderField(INT iMessageHeaderIndex, LPCWSTR lpszMessageHeaderField) {
      return IPWorks_MIME_Set(m_pObj, 6+10000, iMessageHeaderIndex, (LPVOID)lpszMessageHeaderField, 0);
    }

    inline LPWSTR GetMessageHeaderValue(INT iMessageHeaderIndex) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 7+10000, iMessageHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageHeaderValue(INT iMessageHeaderIndex, LPCWSTR lpszMessageHeaderValue) {
      return IPWorks_MIME_Set(m_pObj, 7+10000, iMessageHeaderIndex, (LPVOID)lpszMessageHeaderValue, 0);
    }

    inline LPWSTR GetMessageHeadersString() {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageHeadersString(LPCWSTR lpszMessageHeadersString) {
      return IPWorks_MIME_Set(m_pObj, 8+10000, 0, (LPVOID)lpszMessageHeadersString, 0);
    }

    inline INT GetPartCount() {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 9, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetPartCount(INT iPartCount) {
      LPVOID val = (LPVOID)(iPartCount);
      return IPWorks_MIME_Set(m_pObj, 9, 0, val, 0);
    }

    inline LPWSTR GetPartContentDisposition(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 10+10000, iPartIdx, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPartContentDisposition(INT iPartIdx, LPCWSTR lpszPartContentDisposition) {
      return IPWorks_MIME_Set(m_pObj, 10+10000, iPartIdx, (LPVOID)lpszPartContentDisposition, 0);
    }

    inline LPWSTR GetPartContentDispositionAttr(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 11+10000, iPartIdx, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPartContentDispositionAttr(INT iPartIdx, LPCWSTR lpszPartContentDispositionAttr) {
      return IPWorks_MIME_Set(m_pObj, 11+10000, iPartIdx, (LPVOID)lpszPartContentDispositionAttr, 0);
    }

    inline LPWSTR GetPartContentId(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 12+10000, iPartIdx, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPartContentId(INT iPartIdx, LPCWSTR lpszPartContentId) {
      return IPWorks_MIME_Set(m_pObj, 12+10000, iPartIdx, (LPVOID)lpszPartContentId, 0);
    }

    inline LPWSTR GetPartContentType(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 13+10000, iPartIdx, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPartContentType(INT iPartIdx, LPCWSTR lpszPartContentType) {
      return IPWorks_MIME_Set(m_pObj, 13+10000, iPartIdx, (LPVOID)lpszPartContentType, 0);
    }

    inline LPWSTR GetPartContentTypeAttr(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 14+10000, iPartIdx, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPartContentTypeAttr(INT iPartIdx, LPCWSTR lpszPartContentTypeAttr) {
      return IPWorks_MIME_Set(m_pObj, 14+10000, iPartIdx, (LPVOID)lpszPartContentTypeAttr, 0);
    }

    inline LPWSTR GetPartDecodedFile(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 15+10000, iPartIdx, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPartDecodedFile(INT iPartIdx, LPCWSTR lpszPartDecodedFile) {
      return IPWorks_MIME_Set(m_pObj, 15+10000, iPartIdx, (LPVOID)lpszPartDecodedFile, 0);
    }

    inline INT GetPartDecodedString(INT iPartIdx, LPSTR &lpPartDecodedString, INT &lenPartDecodedString) {
      lpPartDecodedString = (LPSTR)IPWorks_MIME_Get(m_pObj, 16, iPartIdx, &lenPartDecodedString, NULL);
      return lpPartDecodedString ? 0 : lenPartDecodedString;
    }
    inline INT SetPartDecodedString(INT iPartIdx, LPCSTR lpPartDecodedString, INT lenPartDecodedString) {
      return IPWorks_MIME_Set(m_pObj, 16, iPartIdx, (LPVOID)lpPartDecodedString, lenPartDecodedString);
    }

    inline INT GetPartEncoding(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 17, iPartIdx, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetPartEncoding(INT iPartIdx, INT iPartEncoding) {
      LPVOID val = (LPVOID)(iPartEncoding);
      return IPWorks_MIME_Set(m_pObj, 17, iPartIdx, val, 0);
    }

    inline LPWSTR GetPartFilename(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 18+10000, iPartIdx, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPartFilename(INT iPartIdx, LPCWSTR lpszPartFilename) {
      return IPWorks_MIME_Set(m_pObj, 18+10000, iPartIdx, (LPVOID)lpszPartFilename, 0);
    }

    inline LPWSTR GetPartHeaders(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 19+10000, iPartIdx, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPartHeaders(INT iPartIdx, LPCWSTR lpszPartHeaders) {
      return IPWorks_MIME_Set(m_pObj, 19+10000, iPartIdx, (LPVOID)lpszPartHeaders, 0);
    }

    inline LPWSTR GetPartName(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 20+10000, iPartIdx, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPartName(INT iPartIdx, LPCWSTR lpszPartName) {
      return IPWorks_MIME_Set(m_pObj, 20+10000, iPartIdx, (LPVOID)lpszPartName, 0);
    }

    inline INT GetPartSize(INT iPartIdx) {
      LPVOID val = IPWorks_MIME_Get(m_pObj, 21, iPartIdx, NULL, NULL);
      return (INT)(LONG)val;
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_MIME_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DecodeFromFile() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT DecodeFromString() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT EncodeToFile() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT EncodeToString() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT ResetData() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_MIME_H_
