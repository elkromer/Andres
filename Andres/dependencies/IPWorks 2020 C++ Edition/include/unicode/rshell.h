/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_RSHELL_H_
#define _IPWORKS_RSHELL_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3


extern "C" void* IPWORKS_CALL IPWorks_Rshell_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Rshell_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_Rshell_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_Rshell_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RshellConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RshellConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RshellDisconnectedEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} RshellErrorEventParams;

typedef struct {
  LPCSTR Text;
  INT lenText;
  BOOL EOL;
  INT reserved;
} RshellStderrEventParams;

typedef struct {
  LPCSTR Text;
  INT lenText;
  BOOL EOL;
  INT reserved;
} RshellStdoutEventParams;


class Rshell {
  public: // Events
    virtual INT FireConnected(RshellConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(RshellConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(RshellDisconnectedEventParams *e) {return 0;}
    virtual INT FireError(RshellErrorEventParams *e) {return 0;}
    virtual INT FireStderr(RshellStderrEventParams *e) {return 0;}
    virtual INT FireStdout(RshellStdoutEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL RshellEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          RshellConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Rshell*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          RshellConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((Rshell*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          RshellDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Rshell*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          RshellErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Rshell*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          RshellStderrEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (BOOL)param[1], 0};
          ret_code = ((Rshell*)lpObj)->FireStderr(&e);
          break;
        }
        case 6: {
          RshellStdoutEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (BOOL)param[1], 0};
          ret_code = ((Rshell*)lpObj)->FireStdout(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    Rshell(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_21) {
      m_pObj = IPWorks_Rshell_Create(RshellEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~Rshell() {
      IPWorks_Rshell_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_Rshell_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_Rshell_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_Rshell_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_Rshell_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_Rshell_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetBytesSent() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 1, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetCommand() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCommand(LPCWSTR lpszCommand) {
      return IPWorks_Rshell_Set(m_pObj, 2+10000, 0, (LPVOID)lpszCommand, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 3, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_Rshell_Set(m_pObj, 3, 0, val, 0);
    }

    inline BOOL GetEoF() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 4, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline INT GetEOL(LPSTR &lpEOL, INT &lenEOL) {
      lpEOL = (LPSTR)IPWorks_Rshell_Get(m_pObj, 5, 0, &lenEOL, NULL);
      return lpEOL ? 0 : lenEOL;
    }
    inline INT SetEOL(LPCSTR lpEOL, INT lenEOL) {
      return IPWorks_Rshell_Set(m_pObj, 5, 0, (LPVOID)lpEOL, lenEOL);
    }

    inline INT GetErrEOL(LPSTR &lpErrEOL, INT &lenErrEOL) {
      lpErrEOL = (LPSTR)IPWorks_Rshell_Get(m_pObj, 6, 0, &lenErrEOL, NULL);
      return lpErrEOL ? 0 : lenErrEOL;
    }
    inline INT SetErrEOL(LPCSTR lpErrEOL, INT lenErrEOL) {
      return IPWorks_Rshell_Set(m_pObj, 6, 0, (LPVOID)lpErrEOL, lenErrEOL);
    }

    inline LPWSTR GetErrorMessage() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 8, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_Rshell_Set(m_pObj, 8, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 9, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_Rshell_Set(m_pObj, 9, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_Rshell_Set(m_pObj, 10+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_Rshell_Set(m_pObj, 11+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 12, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_Rshell_Set(m_pObj, 12, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_Rshell_Set(m_pObj, 13+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_Rshell_Set(m_pObj, 14+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetLocalPort() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 15, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLocalPort(INT iLocalPort) {
      LPVOID val = (LPVOID)(iLocalPort);
      return IPWorks_Rshell_Set(m_pObj, 15, 0, val, 0);
    }

    inline LPWSTR GetLocalUser() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalUser(LPCWSTR lpszLocalUser) {
      return IPWorks_Rshell_Set(m_pObj, 16+10000, 0, (LPVOID)lpszLocalUser, 0);
    }

    inline LPWSTR GetRemoteHost() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteHost(LPCWSTR lpszRemoteHost) {
      return IPWorks_Rshell_Set(m_pObj, 17+10000, 0, (LPVOID)lpszRemoteHost, 0);
    }

    inline INT GetRemotePort() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 18, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRemotePort(INT iRemotePort) {
      LPVOID val = (LPVOID)(iRemotePort);
      return IPWorks_Rshell_Set(m_pObj, 18, 0, val, 0);
    }

    inline LPWSTR GetRemoteUser() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteUser(LPCWSTR lpszRemoteUser) {
      return IPWorks_Rshell_Set(m_pObj, 19+10000, 0, (LPVOID)lpszRemoteUser, 0);
    }

    inline INT GetStderr(LPSTR &lpStderr, INT &lenStderr) {
      lpStderr = (LPSTR)IPWorks_Rshell_Get(m_pObj, 20, 0, &lenStderr, NULL);
      return lpStderr ? 0 : lenStderr;
    }

    inline INT SetStdin(LPCSTR lpStdin, INT lenStdin) {
      return IPWorks_Rshell_Set(m_pObj, 21, 0, (LPVOID)lpStdin, lenStdin);
    }

    inline INT GetStdout(LPSTR &lpStdout, INT &lenStdout) {
      lpStdout = (LPSTR)IPWorks_Rshell_Get(m_pObj, 22, 0, &lenStdout, NULL);
      return lpStdout ? 0 : lenStdout;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_Rshell_Get(m_pObj, 23, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_Rshell_Set(m_pObj, 23, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_Rshell_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Execute(LPCWSTR lpszCommand) {
      LPVOID param[1+1] = {(LPVOID)lpszCommand, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Rshell_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT Send(LPCSTR lpText, INT lenText) {
      LPVOID param[1+1] = {(LPVOID)lpText, 0};
      INT cbparam[1+1] = {lenText, 0};
      return IPWorks_Rshell_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_RSHELL_H_
