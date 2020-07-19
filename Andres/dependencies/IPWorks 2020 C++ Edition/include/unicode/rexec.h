/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_REXEC_H_
#define _IPWORKS_REXEC_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3


extern "C" void* IPWORKS_CALL IPWorks_Rexec_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_Rexec_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rexec_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Rexec_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_Rexec_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Rexec_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_Rexec_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rexec_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rexec_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_Rexec_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rexec_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rexec_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_Rexec_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Rexec_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RexecConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RexecConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RexecDisconnectedEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} RexecErrorEventParams;

typedef struct {
  LPCSTR Text;
  INT lenText;
  BOOL EOL;
  INT reserved;
} RexecStderrEventParams;

typedef struct {
  LPCSTR Text;
  INT lenText;
  BOOL EOL;
  INT reserved;
} RexecStdoutEventParams;


class Rexec {
  public: // Events
    virtual INT FireConnected(RexecConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(RexecConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(RexecDisconnectedEventParams *e) {return 0;}
    virtual INT FireError(RexecErrorEventParams *e) {return 0;}
    virtual INT FireStderr(RexecStderrEventParams *e) {return 0;}
    virtual INT FireStdout(RexecStdoutEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL RexecEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          RexecConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Rexec*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          RexecConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((Rexec*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          RexecDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Rexec*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          RexecErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Rexec*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          RexecStderrEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (BOOL)param[1], 0};
          ret_code = ((Rexec*)lpObj)->FireStderr(&e);
          break;
        }
        case 6: {
          RexecStdoutEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (BOOL)param[1], 0};
          ret_code = ((Rexec*)lpObj)->FireStdout(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    Rexec(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_22) {
      m_pObj = IPWorks_Rexec_Create(RexecEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~Rexec() {
      IPWorks_Rexec_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_Rexec_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_Rexec_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_Rexec_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_Rexec_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_Rexec_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetBytesSent() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 1, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetCommand() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCommand(LPCWSTR lpszCommand) {
      return IPWorks_Rexec_Set(m_pObj, 2+10000, 0, (LPVOID)lpszCommand, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 3, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_Rexec_Set(m_pObj, 3, 0, val, 0);
    }

    inline BOOL GetEoF() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 4, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline INT GetEOL(LPSTR &lpEOL, INT &lenEOL) {
      lpEOL = (LPSTR)IPWorks_Rexec_Get(m_pObj, 5, 0, &lenEOL, NULL);
      return lpEOL ? 0 : lenEOL;
    }
    inline INT SetEOL(LPCSTR lpEOL, INT lenEOL) {
      return IPWorks_Rexec_Set(m_pObj, 5, 0, (LPVOID)lpEOL, lenEOL);
    }

    inline INT GetErrEOL(LPSTR &lpErrEOL, INT &lenErrEOL) {
      lpErrEOL = (LPSTR)IPWorks_Rexec_Get(m_pObj, 6, 0, &lenErrEOL, NULL);
      return lpErrEOL ? 0 : lenErrEOL;
    }
    inline INT SetErrEOL(LPCSTR lpErrEOL, INT lenErrEOL) {
      return IPWorks_Rexec_Set(m_pObj, 6, 0, (LPVOID)lpErrEOL, lenErrEOL);
    }

    inline LPWSTR GetErrorMessage() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 8, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_Rexec_Set(m_pObj, 8, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 9, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_Rexec_Set(m_pObj, 9, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_Rexec_Set(m_pObj, 10+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_Rexec_Set(m_pObj, 11+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 12, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_Rexec_Set(m_pObj, 12, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_Rexec_Set(m_pObj, 13+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_Rexec_Set(m_pObj, 14+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetLocalPort() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 15, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLocalPort(INT iLocalPort) {
      LPVOID val = (LPVOID)(iLocalPort);
      return IPWorks_Rexec_Set(m_pObj, 15, 0, val, 0);
    }

    inline LPWSTR GetRemoteHost() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteHost(LPCWSTR lpszRemoteHost) {
      return IPWorks_Rexec_Set(m_pObj, 16+10000, 0, (LPVOID)lpszRemoteHost, 0);
    }

    inline LPWSTR GetRemotePassword() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemotePassword(LPCWSTR lpszRemotePassword) {
      return IPWorks_Rexec_Set(m_pObj, 17+10000, 0, (LPVOID)lpszRemotePassword, 0);
    }

    inline INT GetRemotePort() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 18, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRemotePort(INT iRemotePort) {
      LPVOID val = (LPVOID)(iRemotePort);
      return IPWorks_Rexec_Set(m_pObj, 18, 0, val, 0);
    }

    inline LPWSTR GetRemoteUser() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteUser(LPCWSTR lpszRemoteUser) {
      return IPWorks_Rexec_Set(m_pObj, 19+10000, 0, (LPVOID)lpszRemoteUser, 0);
    }

    inline INT GetStderr(LPSTR &lpStderr, INT &lenStderr) {
      lpStderr = (LPSTR)IPWorks_Rexec_Get(m_pObj, 20, 0, &lenStderr, NULL);
      return lpStderr ? 0 : lenStderr;
    }

    inline INT SetStdin(LPCSTR lpStdin, INT lenStdin) {
      return IPWorks_Rexec_Set(m_pObj, 21, 0, (LPVOID)lpStdin, lenStdin);
    }

    inline INT GetStdout(LPSTR &lpStdout, INT &lenStdout) {
      lpStdout = (LPSTR)IPWorks_Rexec_Get(m_pObj, 22, 0, &lenStdout, NULL);
      return lpStdout ? 0 : lenStdout;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_Rexec_Get(m_pObj, 23, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_Rexec_Set(m_pObj, 23, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_Rexec_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Rexec_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Rexec_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Execute(LPCWSTR lpszCommand) {
      LPVOID param[1+1] = {(LPVOID)lpszCommand, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Rexec_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Rexec_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Rexec_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT Send(LPCSTR lpText, INT lenText) {
      LPVOID param[1+1] = {(LPVOID)lpText, 0};
      INT cbparam[1+1] = {lenText, 0};
      return IPWorks_Rexec_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_REXEC_H_
