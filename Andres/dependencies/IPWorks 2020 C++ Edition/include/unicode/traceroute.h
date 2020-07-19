/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_TRACEROUTE_H_
#define _IPWORKS_TRACEROUTE_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_TraceRoute_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_TraceRoute_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_TraceRoute_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_TraceRoute_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} TraceRouteErrorEventParams;

typedef struct {
  INT HopNumber;
  LPCWSTR HostAddress;
  INT Duration;
  INT reserved;
} TraceRouteHopEventParams;

typedef struct {
  INT HopNumber;
  INT StatusCode;
  LPCWSTR HopHostName;
  INT reserved;
} TraceRouteHopResolvedEventParams;


class TraceRoute {
  public: // Events
    virtual INT FireError(TraceRouteErrorEventParams *e) {return 0;}
    virtual INT FireHop(TraceRouteHopEventParams *e) {return 0;}
    virtual INT FireHopResolved(TraceRouteHopResolvedEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL TraceRouteEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          TraceRouteErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((TraceRoute*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          TraceRouteHopEventParams e = {(INT)param[0], (LPWSTR)param[1], (INT)param[2], 0};
          ret_code = ((TraceRoute*)lpObj)->FireHop(&e);
          break;
        }
        case 3: {
          TraceRouteHopResolvedEventParams e = {(INT)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((TraceRoute*)lpObj)->FireHopResolved(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    TraceRoute(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_48) {
      m_pObj = IPWorks_TraceRoute_Create(TraceRouteEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~TraceRoute() {
      IPWorks_TraceRoute_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_TraceRoute_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_TraceRoute_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_TraceRoute_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_TraceRoute_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_TraceRoute_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetHopLimit() {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 1, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetHopLimit(INT iHopLimit) {
      LPVOID val = (LPVOID)(iHopLimit);
      return IPWorks_TraceRoute_Set(m_pObj, 1, 0, val, 0);
    }

    inline INT GetHopCount() {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 2, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetHopErrorCode(INT iHopIndex) {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 3, iHopIndex, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetHopErrorDescription(INT iHopIndex) {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 4+10000, iHopIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetHopHostAddress(INT iHopIndex) {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 5+10000, iHopIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetHopHostName(INT iHopIndex) {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 6+10000, iHopIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetHopTime(INT iHopIndex) {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 7, iHopIndex, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetHopTimeout() {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 8, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetHopTimeout(INT iHopTimeout) {
      LPVOID val = (LPVOID)(iHopTimeout);
      return IPWorks_TraceRoute_Set(m_pObj, 8, 0, val, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 9, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_TraceRoute_Set(m_pObj, 10+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetRemoteHost() {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteHost(LPCWSTR lpszRemoteHost) {
      return IPWorks_TraceRoute_Set(m_pObj, 11+10000, 0, (LPVOID)lpszRemoteHost, 0);
    }

    inline BOOL GetResolveNames() {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 12, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetResolveNames(BOOL bResolveNames) {
      LPVOID val = (LPVOID)(bResolveNames);
      return IPWorks_TraceRoute_Set(m_pObj, 12, 0, val, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_TraceRoute_Get(m_pObj, 13, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_TraceRoute_Set(m_pObj, 13, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_TraceRoute_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT TraceTo(LPCWSTR lpszHost) {
      LPVOID param[1+1] = {(LPVOID)lpszHost, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_TraceRoute_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_TRACEROUTE_H_
