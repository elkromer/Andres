/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_MX_H_
#define _IPWORKS_MX_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_MX_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_MX_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_MX_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_MX_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_MX_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_MX_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_MX_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_MX_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_MX_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} MXErrorEventParams;

typedef struct {
  INT RequestId;
  LPCWSTR Domain;
  LPCWSTR MailServer;
  INT Precedence;
  INT TimeToLive;
  INT StatusCode;
  LPCWSTR Description;
  BOOL Authoritative;
  INT reserved;
} MXResponseEventParams;


class MX {
  public: // Events
    virtual INT FireError(MXErrorEventParams *e) {return 0;}
    virtual INT FireResponse(MXResponseEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL MXEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          MXErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((MX*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          MXResponseEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (INT)param[3], (INT)param[4], (INT)param[5], (LPWSTR)param[6], (BOOL)param[7], 0};
          ret_code = ((MX*)lpObj)->FireResponse(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    MX(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_29) {
      m_pObj = IPWorks_MX_Create(MXEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~MX() {
      IPWorks_MX_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_MX_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_MX_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_MX_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_MX_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_MX_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetDNSPort() {
      LPVOID val = IPWorks_MX_Get(m_pObj, 1, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetDNSPort(INT iDNSPort) {
      LPVOID val = (LPVOID)(iDNSPort);
      return IPWorks_MX_Set(m_pObj, 1, 0, val, 0);
    }

    inline LPWSTR GetDNSServer() {
      LPVOID val = IPWorks_MX_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDNSServer(LPCWSTR lpszDNSServer) {
      return IPWorks_MX_Set(m_pObj, 2+10000, 0, (LPVOID)lpszDNSServer, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_MX_Get(m_pObj, 3, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_MX_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_MX_Set(m_pObj, 4+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetMailServer() {
      LPVOID val = IPWorks_MX_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetRequestId() {
      LPVOID val = IPWorks_MX_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRequestId(INT iRequestId) {
      LPVOID val = (LPVOID)(iRequestId);
      return IPWorks_MX_Set(m_pObj, 6, 0, val, 0);
    }

    inline LPWSTR GetStatus() {
      LPVOID val = IPWorks_MX_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_MX_Get(m_pObj, 8, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_MX_Set(m_pObj, 8, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_MX_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT Resolve(LPCWSTR lpszEmailAddress) {
      LPVOID param[1+1] = {(LPVOID)lpszEmailAddress, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_MX_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_MX_H_
