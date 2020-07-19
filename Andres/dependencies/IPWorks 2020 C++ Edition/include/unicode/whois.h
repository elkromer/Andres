/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_WHOIS_H_
#define _IPWORKS_WHOIS_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3


extern "C" void* IPWORKS_CALL IPWorks_Whois_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_Whois_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Whois_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Whois_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_Whois_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Whois_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_Whois_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Whois_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Whois_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_Whois_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Whois_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Whois_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_Whois_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Whois_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WhoisConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WhoisConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WhoisDisconnectedEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} WhoisErrorEventParams;


class Whois {
  public: // Events
    virtual INT FireConnected(WhoisConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(WhoisConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(WhoisDisconnectedEventParams *e) {return 0;}
    virtual INT FireError(WhoisErrorEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL WhoisEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          WhoisConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Whois*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          WhoisConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((Whois*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          WhoisDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Whois*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          WhoisErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Whois*)lpObj)->FireError(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    Whois(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_53) {
      m_pObj = IPWorks_Whois_Create(WhoisEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~Whois() {
      IPWorks_Whois_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_Whois_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_Whois_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_Whois_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_Whois_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_Whois_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetDefaultServer() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDefaultServer(LPCWSTR lpszDefaultServer) {
      return IPWorks_Whois_Set(m_pObj, 1+10000, 0, (LPVOID)lpszDefaultServer, 0);
    }

    inline LPWSTR GetDomainInfo() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 3, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_Whois_Set(m_pObj, 3, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_Whois_Set(m_pObj, 4, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_Whois_Set(m_pObj, 5+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_Whois_Set(m_pObj, 6+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 7, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_Whois_Set(m_pObj, 7, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_Whois_Set(m_pObj, 8+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 9, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_Whois_Set(m_pObj, 10+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetServer() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetServer(LPCWSTR lpszServer) {
      return IPWorks_Whois_Set(m_pObj, 11+10000, 0, (LPVOID)lpszServer, 0);
    }

    inline INT GetServerPort() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 12, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetServerPort(INT iServerPort) {
      LPVOID val = (LPVOID)(iServerPort);
      return IPWorks_Whois_Set(m_pObj, 12, 0, val, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_Whois_Get(m_pObj, 13, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_Whois_Set(m_pObj, 13, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_Whois_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Whois_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Whois_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Query(LPCWSTR lpszDomain) {
      LPVOID param[1+1] = {(LPVOID)lpszDomain, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Whois_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Whois_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_WHOIS_H_
