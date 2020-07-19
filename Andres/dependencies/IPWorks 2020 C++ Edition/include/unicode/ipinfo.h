/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_IPINFO_H_
#define _IPWORKS_IPINFO_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_IPInfo_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_IPInfo_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_IPInfo_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_IPInfo_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR RecordName;
  INT RecordType;
  INT TimeToLive;
  INT DataLength;
  LPCWSTR Section;
  LPCWSTR RecordValue;
  LPCWSTR RecordInfo;
  INT reserved;
} IPInfoDNSCacheEntryEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} IPInfoErrorEventParams;

typedef struct {
  INT RequestId;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} IPInfoRequestCompleteEventParams;


class IPInfo {
  public: // Events
    virtual INT FireDNSCacheEntry(IPInfoDNSCacheEntryEventParams *e) {return 0;}
    virtual INT FireError(IPInfoErrorEventParams *e) {return 0;}
    virtual INT FireRequestComplete(IPInfoRequestCompleteEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL IPInfoEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          IPInfoDNSCacheEntryEventParams e = {(LPWSTR)param[0], (INT)param[1], (INT)param[2], (INT)param[3], (LPWSTR)param[4], (LPWSTR)param[5], (LPWSTR)param[6], 0};
          ret_code = ((IPInfo*)lpObj)->FireDNSCacheEntry(&e);
          break;
        }
        case 2: {
          IPInfoErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((IPInfo*)lpObj)->FireError(&e);
          break;
        }
        case 3: {
          IPInfoRequestCompleteEventParams e = {(INT)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((IPInfo*)lpObj)->FireRequestComplete(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    IPInfo(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_15) {
      m_pObj = IPWorks_IPInfo_Create(IPInfoEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~IPInfo() {
      IPWorks_IPInfo_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_IPInfo_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_IPInfo_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_IPInfo_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_IPInfo_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_IPInfo_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAdapterBroadcastAddress() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetAdapterCount() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 2, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetAdapterDescription() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetAdapterDeviceIndex() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline BOOL GetAdapterDHCPEnabled() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 5, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetAdapterDHCPServer() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterDNSServers() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterGateway() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetAdapterIndex() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 9, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAdapterIndex(INT iAdapterIndex) {
      LPVOID val = (LPVOID)(iAdapterIndex);
      return IPWorks_IPInfo_Set(m_pObj, 9, 0, val, 0);
    }

    inline LPWSTR GetAdapterIPAddress() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterIPv6Address() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterIPv6LinkLocalAddress() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterLeaseExpires() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterLeaseObtained() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterName() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterOtherIPAddresses() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterPhysicalAddress() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterPrimaryWINSServer() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterSecondaryWINSServer() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterStatus() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterSubnetMask() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAdapterType() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetAdapterUsesWINS() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 23, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline INT GetAdapterZoneId() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 24, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline BOOL GetARPProxy() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 25, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetDHCPScope() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetDNSEnabled() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 27, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetDNSServer() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 28+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetDomainName() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetHostAddress() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 30+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetHostAddress(LPCWSTR lpszHostAddress) {
      return IPWorks_IPInfo_Set(m_pObj, 30+10000, 0, (LPVOID)lpszHostAddress, 0);
    }

    inline LPWSTR GetHostAliases() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetHostName() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 32+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetHostName(LPCWSTR lpszHostName) {
      return IPWorks_IPInfo_Set(m_pObj, 32+10000, 0, (LPVOID)lpszHostName, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 33+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetNodeType() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 34+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetOtherAddresses() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 35+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetOtherDNSServers() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 36+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetPendingRequests() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 37, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetPendingRequests(INT iPendingRequests) {
      LPVOID val = (LPVOID)(iPendingRequests);
      return IPWorks_IPInfo_Set(m_pObj, 37, 0, val, 0);
    }

    inline INT GetRequestId() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 38, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline BOOL GetRoutingEnabled() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 39, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetServiceAliases() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 40+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetServiceName() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 41+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetServiceName(LPCWSTR lpszServiceName) {
      return IPWorks_IPInfo_Set(m_pObj, 41+10000, 0, (LPVOID)lpszServiceName, 0);
    }

    inline INT GetServicePort() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 42, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetServicePort(INT iServicePort) {
      LPVOID val = (LPVOID)(iServicePort);
      return IPWorks_IPInfo_Set(m_pObj, 42, 0, val, 0);
    }

    inline LPWSTR GetServiceProtocol() {
      LPVOID val = IPWorks_IPInfo_Get(m_pObj, 43+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetServiceProtocol(LPCWSTR lpszServiceProtocol) {
      return IPWorks_IPInfo_Set(m_pObj, 43+10000, 0, (LPVOID)lpszServiceProtocol, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DHCPRelease() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT DHCPRenew() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR DisplayDNSCache() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      IPWorks_IPInfo_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
      return (LPWSTR)param[0];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT FlushDNSCache() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      IPWorks_IPInfo_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
      return (BOOL)param[0];
    }

    inline LPWSTR GetMAC(LPCWSTR lpszIPAddress) {
      LPVOID param[1+1] = {(LPVOID)lpszIPAddress, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR ResolveAddress(LPCWSTR lpszHostAddress) {
      LPVOID param[1+1] = {(LPVOID)lpszHostAddress, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 10+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline LPWSTR ResolveName(LPCWSTR lpszHostName) {
      LPVOID param[1+1] = {(LPVOID)lpszHostName, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 11+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

};

#endif //_IPWORKS_IPINFO_H_
