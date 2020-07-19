/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_NETCLOCK_H_
#define _IPWORKS_NETCLOCK_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//TProtocol
#define TP_TIME                                            0
#define TP_SNTP                                            1


extern "C" void* IPWORKS_CALL IPWorks_NetClock_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NetClock_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_NetClock_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_NetClock_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} NetClockErrorEventParams;


class NetClock {
  public: // Events
    virtual INT FireError(NetClockErrorEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL NetClockEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          NetClockErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((NetClock*)lpObj)->FireError(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    NetClock(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_43) {
      m_pObj = IPWorks_NetClock_Create(NetClockEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~NetClock() {
      IPWorks_NetClock_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_NetClock_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_NetClock_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_NetClock_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_NetClock_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_NetClock_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetIdle() {
      LPVOID val = IPWorks_NetClock_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_NetClock_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_NetClock_Set(m_pObj, 2+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetLocalTime() {
      LPVOID val = IPWorks_NetClock_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetProtocol() {
      LPVOID val = IPWorks_NetClock_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProtocol(INT iProtocol) {
      LPVOID val = (LPVOID)(iProtocol);
      return IPWorks_NetClock_Set(m_pObj, 4, 0, val, 0);
    }

    inline LPWSTR GetServerTime() {
      LPVOID val = IPWorks_NetClock_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_NetClock_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_NetClock_Set(m_pObj, 6, 0, val, 0);
    }

    inline INT GetTimePort() {
      LPVOID val = IPWorks_NetClock_Get(m_pObj, 7, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimePort(INT iTimePort) {
      LPVOID val = (LPVOID)(iTimePort);
      return IPWorks_NetClock_Set(m_pObj, 7, 0, val, 0);
    }

    inline LPWSTR GetTimeServer() {
      LPVOID val = IPWorks_NetClock_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimeServer(LPCWSTR lpszTimeServer) {
      return IPWorks_NetClock_Set(m_pObj, 8+10000, 0, (LPVOID)lpszTimeServer, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_NetClock_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT GetAndSetTime() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT GetTime() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_NETCLOCK_H_
