/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_RCP_H_
#define _IPWORKS_RCP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TRCPProtocol
#define PROT_REXEC                                         0
#define PROT_RSHELL                                        1


extern "C" void* IPWORKS_CALL IPWorks_RCP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_RCP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_RCP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_RCP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_RCP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_RCP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_RCP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_RCP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_RCP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RCPConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RCPConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RCPDisconnectedEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} RCPErrorEventParams;

typedef struct {
  INT PercentDone;
  INT reserved;
} RCPProgressEventParams;


class RCP {
  public: // Events
    virtual INT FireConnected(RCPConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(RCPConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(RCPDisconnectedEventParams *e) {return 0;}
    virtual INT FireError(RCPErrorEventParams *e) {return 0;}
    virtual INT FireProgress(RCPProgressEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL RCPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          RCPConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((RCP*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          RCPConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((RCP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          RCPDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((RCP*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          RCPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((RCP*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          RCPProgressEventParams e = {(INT)param[0], 0};
          ret_code = ((RCP*)lpObj)->FireProgress(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    RCP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_45) {
      m_pObj = IPWorks_RCP_Create(RCPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~RCP() {
      IPWorks_RCP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_RCP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_RCP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_RCP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_RCP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_RCP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetFileMode() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFileMode(LPCWSTR lpszFileMode) {
      return IPWorks_RCP_Set(m_pObj, 1+10000, 0, (LPVOID)lpszFileMode, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 2, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_RCP_Set(m_pObj, 2, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 3, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_RCP_Set(m_pObj, 3, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_RCP_Set(m_pObj, 4+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_RCP_Set(m_pObj, 5+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_RCP_Set(m_pObj, 6, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_RCP_Set(m_pObj, 7+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 8, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_RCP_Set(m_pObj, 9+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_RCP_Set(m_pObj, 10+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetLocalPort() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 11, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLocalPort(INT iLocalPort) {
      LPVOID val = (LPVOID)(iLocalPort);
      return IPWorks_RCP_Set(m_pObj, 11, 0, val, 0);
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_RCP_Set(m_pObj, 12+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetProtocol() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 13, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProtocol(INT iProtocol) {
      LPVOID val = (LPVOID)(iProtocol);
      return IPWorks_RCP_Set(m_pObj, 13, 0, val, 0);
    }

    inline LPWSTR GetRemoteFile() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteFile(LPCWSTR lpszRemoteFile) {
      return IPWorks_RCP_Set(m_pObj, 14+10000, 0, (LPVOID)lpszRemoteFile, 0);
    }

    inline LPWSTR GetRemoteHost() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteHost(LPCWSTR lpszRemoteHost) {
      return IPWorks_RCP_Set(m_pObj, 15+10000, 0, (LPVOID)lpszRemoteHost, 0);
    }

    inline INT GetRemotePort() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 16, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRemotePort(INT iRemotePort) {
      LPVOID val = (LPVOID)(iRemotePort);
      return IPWorks_RCP_Set(m_pObj, 16, 0, val, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 17, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_RCP_Set(m_pObj, 17, 0, val, 0);
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_RCP_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_RCP_Set(m_pObj, 18+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_RCP_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT GetFile() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT PutFile() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_RCP_H_
