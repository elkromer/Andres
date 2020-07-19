/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_IPMONITOR_H_
#define _IPWORKS_IPMONITOR_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_IPMonitor_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_IPMonitor_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_IPMonitor_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_IPMonitor_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} IPMonitorErrorEventParams;

typedef struct {
  LPCWSTR IpAddress;
  INT reserved;
} IPMonitorIPAddressEventParams;

typedef struct {
  LPCWSTR SourceAddress;
  INT SourcePort;
  LPCWSTR DestinationAddress;
  INT DestinationPort;
  INT IPVersion;
  INT TOS;
  INT Id;
  INT Flags;
  INT Offset;
  INT TTL;
  INT Checksum;
  INT IPProtocol;
  LPCSTR Payload;
  INT lenPayload;
  LONG64 Timestamp;
  INT reserved;
} IPMonitorIPPacketEventParams;


class IPMonitor {
  public: // Events
    virtual INT FireError(IPMonitorErrorEventParams *e) {return 0;}
    virtual INT FireIPAddress(IPMonitorIPAddressEventParams *e) {return 0;}
    virtual INT FireIPPacket(IPMonitorIPPacketEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL IPMonitorEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          IPMonitorErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((IPMonitor*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          IPMonitorIPAddressEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((IPMonitor*)lpObj)->FireIPAddress(&e);
          break;
        }
        case 3: {
          IPMonitorIPPacketEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], (INT)param[3], (INT)param[4], (INT)param[5], (INT)param[6], (INT)param[7], (INT)param[8], (INT)param[9], (INT)param[10], (INT)param[11], (LPSTR)param[12], (INT)cbparam[12], *(LONG64*)param[13], 0};
          ret_code = ((IPMonitor*)lpObj)->FireIPPacket(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    IPMonitor(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_60) {
      m_pObj = IPWorks_IPMonitor_Create(IPMonitorEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~IPMonitor() {
      IPWorks_IPMonitor_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_IPMonitor_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_IPMonitor_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_IPMonitor_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_IPMonitor_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_IPMonitor_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetAcceptData() {
      LPVOID val = IPWorks_IPMonitor_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetAcceptData(BOOL bAcceptData) {
      LPVOID val = (LPVOID)(bAcceptData);
      return IPWorks_IPMonitor_Set(m_pObj, 1, 0, val, 0);
    }

    inline BOOL GetActive() {
      LPVOID val = IPWorks_IPMonitor_Get(m_pObj, 2, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetActive(BOOL bActive) {
      LPVOID val = (LPVOID)(bActive);
      return IPWorks_IPMonitor_Set(m_pObj, 2, 0, val, 0);
    }

    inline INT GetIPPacket(LPSTR &lpIPPacket, INT &lenIPPacket) {
      lpIPPacket = (LPSTR)IPWorks_IPMonitor_Get(m_pObj, 3, 0, &lenIPPacket, NULL);
      return lpIPPacket ? 0 : lenIPPacket;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_IPMonitor_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_IPMonitor_Set(m_pObj, 4+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_IPMonitor_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IPMonitor_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT ListIPAddresses() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IPMonitor_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT ParsePcapFile(LPCWSTR lpszfileName) {
      LPVOID param[1+1] = {(LPVOID)lpszfileName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IPMonitor_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IPMonitor_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_IPMONITOR_H_
