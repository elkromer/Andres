/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_PING_H_
#define _IPWORKS_PING_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_Ping_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_Ping_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Ping_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Ping_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_Ping_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Ping_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_Ping_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Ping_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Ping_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_Ping_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Ping_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Ping_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_Ping_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Ping_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} PingErrorEventParams;

typedef struct {
  INT RequestId;
  LPCWSTR ResponseSource;
  LPCWSTR ResponseStatus;
  INT ResponseTime;
  INT reserved;
} PingResponseEventParams;


class Ping {
  public: // Events
    virtual INT FireError(PingErrorEventParams *e) {return 0;}
    virtual INT FireResponse(PingResponseEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL PingEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          PingErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Ping*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          PingResponseEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (INT)param[3], 0};
          ret_code = ((Ping*)lpObj)->FireResponse(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    Ping(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_44) {
      m_pObj = IPWorks_Ping_Create(PingEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~Ping() {
      IPWorks_Ping_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_Ping_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_Ping_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_Ping_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_Ping_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_Ping_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetActive() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetActive(BOOL bActive) {
      LPVOID val = (LPVOID)(bActive);
      return IPWorks_Ping_Set(m_pObj, 1, 0, val, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 2, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_Ping_Set(m_pObj, 3+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetPacketSize() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetPacketSize(INT iPacketSize) {
      LPVOID val = (LPVOID)(iPacketSize);
      return IPWorks_Ping_Set(m_pObj, 4, 0, val, 0);
    }

    inline LPWSTR GetRemoteHost() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteHost(LPCWSTR lpszRemoteHost) {
      return IPWorks_Ping_Set(m_pObj, 5+10000, 0, (LPVOID)lpszRemoteHost, 0);
    }

    inline INT GetRequestId() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetResponseSource() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetResponseTime() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 8, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 9, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_Ping_Set(m_pObj, 9, 0, val, 0);
    }

    inline INT GetTimeToLive() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 10, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeToLive(INT iTimeToLive) {
      LPVOID val = (LPVOID)(iTimeToLive);
      return IPWorks_Ping_Set(m_pObj, 10, 0, val, 0);
    }

    inline INT GetTypeOfService() {
      LPVOID val = IPWorks_Ping_Get(m_pObj, 11, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTypeOfService(INT iTypeOfService) {
      LPVOID val = (LPVOID)(iTypeOfService);
      return IPWorks_Ping_Set(m_pObj, 11, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_Ping_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Ping_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Ping_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT PingHost(LPCWSTR lpszHost) {
      LPVOID param[1+1] = {(LPVOID)lpszHost, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Ping_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Ping_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT WakeOnLAN(LPCWSTR lpszRemoteHost, LPCWSTR lpszMACAddress) {
      LPVOID param[2+1] = {(LPVOID)lpszRemoteHost, (LPVOID)lpszMACAddress, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_Ping_Do(m_pObj, 7+10000, 2, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_PING_H_
