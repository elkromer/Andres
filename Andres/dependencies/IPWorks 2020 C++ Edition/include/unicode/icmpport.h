/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_ICMPPORT_H_
#define _IPWORKS_ICMPPORT_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_ICMPPort_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_ICMPPort_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_ICMPPort_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_ICMPPort_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_ICMPPort_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_ICMPPort_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_ICMPPort_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_ICMPPort_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_ICMPPort_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_ICMPPort_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_ICMPPort_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_ICMPPort_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_ICMPPort_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_ICMPPort_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT MessageType;
  INT MessageSubType;
  LPCSTR MessageData;
  INT lenMessageData;
  INT Checksum;
  LPCWSTR SourceAddress;
  INT reserved;
} ICMPPortDataInEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} ICMPPortErrorEventParams;

typedef struct {
  INT reserved;
} ICMPPortReadyToSendEventParams;


class ICMPPort {
  public: // Events
    virtual INT FireDataIn(ICMPPortDataInEventParams *e) {return 0;}
    virtual INT FireError(ICMPPortErrorEventParams *e) {return 0;}
    virtual INT FireReadyToSend(ICMPPortReadyToSendEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL ICMPPortEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          ICMPPortDataInEventParams e = {(INT)param[0], (INT)param[1], (LPSTR)param[2], (INT)cbparam[2], (INT)param[3], (LPWSTR)param[4], 0};
          ret_code = ((ICMPPort*)lpObj)->FireDataIn(&e);
          break;
        }
        case 2: {
          ICMPPortErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((ICMPPort*)lpObj)->FireError(&e);
          break;
        }
        case 3: {
          ICMPPortReadyToSendEventParams e = {0};
          ret_code = ((ICMPPort*)lpObj)->FireReadyToSend(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    ICMPPort(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_16) {
      m_pObj = IPWorks_ICMPPort_Create(ICMPPortEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~ICMPPort() {
      IPWorks_ICMPPort_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_ICMPPort_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_ICMPPort_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_ICMPPort_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_ICMPPort_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_ICMPPort_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetAcceptData() {
      LPVOID val = IPWorks_ICMPPort_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetAcceptData(BOOL bAcceptData) {
      LPVOID val = (LPVOID)(bAcceptData);
      return IPWorks_ICMPPort_Set(m_pObj, 1, 0, val, 0);
    }

    inline BOOL GetActive() {
      LPVOID val = IPWorks_ICMPPort_Get(m_pObj, 2, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetActive(BOOL bActive) {
      LPVOID val = (LPVOID)(bActive);
      return IPWorks_ICMPPort_Set(m_pObj, 2, 0, val, 0);
    }

    inline INT SetDataToSend(LPCSTR lpDataToSend, INT lenDataToSend) {
      return IPWorks_ICMPPort_Set(m_pObj, 3, 0, (LPVOID)lpDataToSend, lenDataToSend);
    }

    inline BOOL GetDontRoute() {
      LPVOID val = IPWorks_ICMPPort_Get(m_pObj, 4, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetDontRoute(BOOL bDontRoute) {
      LPVOID val = (LPVOID)(bDontRoute);
      return IPWorks_ICMPPort_Set(m_pObj, 4, 0, val, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_ICMPPort_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_ICMPPort_Set(m_pObj, 5+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetMessageSubType() {
      LPVOID val = IPWorks_ICMPPort_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMessageSubType(INT iMessageSubType) {
      LPVOID val = (LPVOID)(iMessageSubType);
      return IPWorks_ICMPPort_Set(m_pObj, 6, 0, val, 0);
    }

    inline INT GetMessageType() {
      LPVOID val = IPWorks_ICMPPort_Get(m_pObj, 7, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMessageType(INT iMessageType) {
      LPVOID val = (LPVOID)(iMessageType);
      return IPWorks_ICMPPort_Set(m_pObj, 7, 0, val, 0);
    }

    inline LPWSTR GetRemoteHost() {
      LPVOID val = IPWorks_ICMPPort_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteHost(LPCWSTR lpszRemoteHost) {
      return IPWorks_ICMPPort_Set(m_pObj, 8+10000, 0, (LPVOID)lpszRemoteHost, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_ICMPPort_Get(m_pObj, 9, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_ICMPPort_Set(m_pObj, 9, 0, val, 0);
    }

    inline INT GetTimeToLive() {
      LPVOID val = IPWorks_ICMPPort_Get(m_pObj, 10, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeToLive(INT iTimeToLive) {
      LPVOID val = (LPVOID)(iTimeToLive);
      return IPWorks_ICMPPort_Set(m_pObj, 10, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_ICMPPort_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_ICMPPort_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_ICMPPort_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Send(LPCSTR lpText, INT lenText) {
      LPVOID param[1+1] = {(LPVOID)lpText, 0};
      INT cbparam[1+1] = {lenText, 0};
      return IPWorks_ICMPPort_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_ICMPPORT_H_
