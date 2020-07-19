/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_NETCODE_H_
#define _IPWORKS_NETCODE_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//TFmt
#define FMT_UUENCODE                                       0
#define FMT_BASE_64                                        1
#define FMT_QP                                             2
#define FMT_URL                                            3
#define FMT_JIS                                            4
#define FMT_YENCODE                                        5
#define FMT_MD5HASH                                        6
#define FMT_SHA1HASH                                       7
#define FMT_HEX                                            8
#define FMT_HTML                                           9
#define FMT_HMAC                                           10
#define FMT_UTF8                                           11
#define FMT_UTF7                                           12
#define FMT_BASE_32                                        13
#define FMT_BASE_64URL                                     14
#define FMT_SHA256HASH                                     15
#define FMT_PUNYCODE                                       16


extern "C" void* IPWORKS_CALL IPWorks_NetCode_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NetCode_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_NetCode_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_NetCode_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} NetCodeErrorEventParams;

typedef struct {
  INT PercentDone;
  INT reserved;
} NetCodeProgressEventParams;


class NetCode {
  public: // Events
    virtual INT FireError(NetCodeErrorEventParams *e) {return 0;}
    virtual INT FireProgress(NetCodeProgressEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL NetCodeEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          NetCodeErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((NetCode*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          NetCodeProgressEventParams e = {(INT)param[0], 0};
          ret_code = ((NetCode*)lpObj)->FireProgress(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    NetCode(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_14) {
      m_pObj = IPWorks_NetCode_Create(NetCodeEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~NetCode() {
      IPWorks_NetCode_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_NetCode_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_NetCode_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_NetCode_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_NetCode_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_NetCode_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetDecodedData(LPSTR &lpDecodedData, INT &lenDecodedData) {
      lpDecodedData = (LPSTR)IPWorks_NetCode_Get(m_pObj, 1, 0, &lenDecodedData, NULL);
      return lpDecodedData ? 0 : lenDecodedData;
    }
    inline INT SetDecodedData(LPCSTR lpDecodedData, INT lenDecodedData) {
      return IPWorks_NetCode_Set(m_pObj, 1, 0, (LPVOID)lpDecodedData, lenDecodedData);
    }

    inline LPWSTR GetDecodedFile() {
      LPVOID val = IPWorks_NetCode_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDecodedFile(LPCWSTR lpszDecodedFile) {
      return IPWorks_NetCode_Set(m_pObj, 2+10000, 0, (LPVOID)lpszDecodedFile, 0);
    }

    inline INT GetEncodedData(LPSTR &lpEncodedData, INT &lenEncodedData) {
      lpEncodedData = (LPSTR)IPWorks_NetCode_Get(m_pObj, 3, 0, &lenEncodedData, NULL);
      return lpEncodedData ? 0 : lenEncodedData;
    }
    inline INT SetEncodedData(LPCSTR lpEncodedData, INT lenEncodedData) {
      return IPWorks_NetCode_Set(m_pObj, 3, 0, (LPVOID)lpEncodedData, lenEncodedData);
    }

    inline LPWSTR GetEncodedFile() {
      LPVOID val = IPWorks_NetCode_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEncodedFile(LPCWSTR lpszEncodedFile) {
      return IPWorks_NetCode_Set(m_pObj, 4+10000, 0, (LPVOID)lpszEncodedFile, 0);
    }

    inline INT GetFileCnt() {
      LPVOID val = IPWorks_NetCode_Get(m_pObj, 5, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetFileName() {
      LPVOID val = IPWorks_NetCode_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFileName(LPCWSTR lpszFileName) {
      return IPWorks_NetCode_Set(m_pObj, 6+10000, 0, (LPVOID)lpszFileName, 0);
    }

    inline INT GetFormat() {
      LPVOID val = IPWorks_NetCode_Get(m_pObj, 7, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFormat(INT iFormat) {
      LPVOID val = (LPVOID)(iFormat);
      return IPWorks_NetCode_Set(m_pObj, 7, 0, val, 0);
    }

    inline LPWSTR GetMode() {
      LPVOID val = IPWorks_NetCode_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMode(LPCWSTR lpszMode) {
      return IPWorks_NetCode_Set(m_pObj, 8+10000, 0, (LPVOID)lpszMode, 0);
    }

    inline BOOL GetOverwrite() {
      LPVOID val = IPWorks_NetCode_Get(m_pObj, 9, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetOverwrite(BOOL bOverwrite) {
      LPVOID val = (LPVOID)(bOverwrite);
      return IPWorks_NetCode_Set(m_pObj, 9, 0, val, 0);
    }

    inline INT GetProgressStep() {
      LPVOID val = IPWorks_NetCode_Get(m_pObj, 10, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProgressStep(INT iProgressStep) {
      LPVOID val = (LPVOID)(iProgressStep);
      return IPWorks_NetCode_Set(m_pObj, 10, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_NetCode_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Decode() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Encode() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT ResetData() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_NETCODE_H_
