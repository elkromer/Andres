/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_MCAST_H_
#define _IPWORKS_MCAST_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_MCast_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_MCast_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MCast_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_MCast_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_MCast_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_MCast_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_MCast_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MCast_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MCast_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_MCast_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MCast_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MCast_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_MCast_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_MCast_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCSTR Datagram;
  INT lenDatagram;
  LPCWSTR SourceAddress;
  INT SourcePort;
  INT reserved;
} MCastDataInEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} MCastErrorEventParams;

typedef struct {
  INT reserved;
} MCastReadyToSendEventParams;


class MCast {
  public: // Events
    virtual INT FireDataIn(MCastDataInEventParams *e) {return 0;}
    virtual INT FireError(MCastErrorEventParams *e) {return 0;}
    virtual INT FireReadyToSend(MCastReadyToSendEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL MCastEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          MCastDataInEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (INT)param[2], 0};
          ret_code = ((MCast*)lpObj)->FireDataIn(&e);
          break;
        }
        case 2: {
          MCastErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((MCast*)lpObj)->FireError(&e);
          break;
        }
        case 3: {
          MCastReadyToSendEventParams e = {0};
          ret_code = ((MCast*)lpObj)->FireReadyToSend(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    MCast(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_26) {
      m_pObj = IPWorks_MCast_Create(MCastEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~MCast() {
      IPWorks_MCast_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_MCast_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_MCast_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_MCast_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_MCast_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_MCast_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetAcceptData() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetAcceptData(BOOL bAcceptData) {
      LPVOID val = (LPVOID)(bAcceptData);
      return IPWorks_MCast_Set(m_pObj, 1, 0, val, 0);
    }

    inline BOOL GetActive() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 2, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetActive(BOOL bActive) {
      LPVOID val = (LPVOID)(bActive);
      return IPWorks_MCast_Set(m_pObj, 2, 0, val, 0);
    }

    inline INT SetDataToSend(LPCSTR lpDataToSend, INT lenDataToSend) {
      return IPWorks_MCast_Set(m_pObj, 3, 0, (LPVOID)lpDataToSend, lenDataToSend);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_MCast_Set(m_pObj, 4+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetLocalPort() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 5, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLocalPort(INT iLocalPort) {
      LPVOID val = (LPVOID)(iLocalPort);
      return IPWorks_MCast_Set(m_pObj, 5, 0, val, 0);
    }

    inline BOOL GetLoopback() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 6, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetLoopback(BOOL bLoopback) {
      LPVOID val = (LPVOID)(bLoopback);
      return IPWorks_MCast_Set(m_pObj, 6, 0, val, 0);
    }

    inline LPWSTR GetMulticastGroup() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMulticastGroup(LPCWSTR lpszMulticastGroup) {
      return IPWorks_MCast_Set(m_pObj, 7+10000, 0, (LPVOID)lpszMulticastGroup, 0);
    }

    inline LPWSTR GetReceiveInterface() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReceiveInterface(LPCWSTR lpszReceiveInterface) {
      return IPWorks_MCast_Set(m_pObj, 8+10000, 0, (LPVOID)lpszReceiveInterface, 0);
    }

    inline LPWSTR GetRemoteHost() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteHost(LPCWSTR lpszRemoteHost) {
      return IPWorks_MCast_Set(m_pObj, 9+10000, 0, (LPVOID)lpszRemoteHost, 0);
    }

    inline INT GetRemotePort() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 10, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRemotePort(INT iRemotePort) {
      LPVOID val = (LPVOID)(iRemotePort);
      return IPWorks_MCast_Set(m_pObj, 10, 0, val, 0);
    }

    inline LPWSTR GetSendInterface() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSendInterface(LPCWSTR lpszSendInterface) {
      return IPWorks_MCast_Set(m_pObj, 11+10000, 0, (LPVOID)lpszSendInterface, 0);
    }

    inline INT GetTimeToLive() {
      LPVOID val = IPWorks_MCast_Get(m_pObj, 12, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeToLive(INT iTimeToLive) {
      LPVOID val = (LPVOID)(iTimeToLive);
      return IPWorks_MCast_Set(m_pObj, 12, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_MCast_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MCast_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_MCast_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Send(LPCSTR lpText, INT lenText) {
      LPVOID param[1+1] = {(LPVOID)lpText, 0};
      INT cbparam[1+1] = {lenText, 0};
      return IPWorks_MCast_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_MCAST_H_
