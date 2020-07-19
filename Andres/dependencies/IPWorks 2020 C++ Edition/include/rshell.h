/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_Rshell_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_Rshell_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_Rshell_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} RshellConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} RshellConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} RshellDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} RshellErrorEventParams;

typedef struct {
  const char *Text;
  int lenText;
  int EOL;
  int reserved;
} RshellStderrEventParams;

typedef struct {
  const char *Text;
  int lenText;
  int EOL;
  int reserved;
} RshellStdoutEventParams;


class Rshell {
  public: // Events
    virtual int FireConnected(RshellConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(RshellConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(RshellDisconnectedEventParams *e) {return 0;}
    virtual int FireError(RshellErrorEventParams *e) {return 0;}
    virtual int FireStderr(RshellStderrEventParams *e) {return 0;}
    virtual int FireStdout(RshellStdoutEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL RshellEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          RshellConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((Rshell*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          RshellConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((Rshell*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          RshellDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((Rshell*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          RshellErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((Rshell*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          RshellStderrEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (int)IPW64CAST(param[1]), 0};
          ret_code = ((Rshell*)lpObj)->FireStderr(&e);
          break;
        }
        case 6: {
          RshellStdoutEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (int)IPW64CAST(param[1]), 0};
          ret_code = ((Rshell*)lpObj)->FireStdout(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    Rshell(char *lpOemKey = (char*)IPWORKS_OEMKEY_21) {
      m_pObj = IPWorks_Rshell_Create(RshellEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~Rshell() {
      IPWorks_Rshell_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_Rshell_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_Rshell_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_Rshell_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_Rshell_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_Rshell_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetBytesSent() {
      void* val = IPWorks_Rshell_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCommand() {
      void* val = IPWorks_Rshell_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCommand(const char* lpszCommand) {
      return IPWorks_Rshell_Set(m_pObj, 2, 0, (void*)lpszCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_Rshell_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_Rshell_Set(m_pObj, 3, 0, val, 0);
    }

    inline int GetEoF() {
      void* val = IPWorks_Rshell_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetEOL(char* &lpEOL, int &lenEOL) {
      lpEOL = (char*)IPWorks_Rshell_Get(m_pObj, 5, 0, &lenEOL, NULL);
      return lpEOL ? 0 : lenEOL;
    }
    inline int SetEOL(const char* lpEOL, int lenEOL) {
      return IPWorks_Rshell_Set(m_pObj, 5, 0, (void*)lpEOL, lenEOL);
    }

    inline int GetErrEOL(char* &lpErrEOL, int &lenErrEOL) {
      lpErrEOL = (char*)IPWorks_Rshell_Get(m_pObj, 6, 0, &lenErrEOL, NULL);
      return lpErrEOL ? 0 : lenErrEOL;
    }
    inline int SetErrEOL(const char* lpErrEOL, int lenErrEOL) {
      return IPWorks_Rshell_Set(m_pObj, 6, 0, (void*)lpErrEOL, lenErrEOL);
    }

    inline char* GetErrorMessage() {
      void* val = IPWorks_Rshell_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_Rshell_Get(m_pObj, 8, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_Rshell_Set(m_pObj, 8, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_Rshell_Get(m_pObj, 9, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_Rshell_Set(m_pObj, 9, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_Rshell_Get(m_pObj, 10, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_Rshell_Set(m_pObj, 10, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_Rshell_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_Rshell_Set(m_pObj, 11, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_Rshell_Get(m_pObj, 12, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_Rshell_Set(m_pObj, 12, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_Rshell_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_Rshell_Set(m_pObj, 13, 0, (void*)lpszFirewallUser, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_Rshell_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_Rshell_Set(m_pObj, 14, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_Rshell_Get(m_pObj, 15, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetLocalPort(int iLocalPort) {
      void* val = (void*)IPW64CAST(iLocalPort);
      return IPWorks_Rshell_Set(m_pObj, 15, 0, val, 0);
    }

    inline char* GetLocalUser() {
      void* val = IPWorks_Rshell_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalUser(const char* lpszLocalUser) {
      return IPWorks_Rshell_Set(m_pObj, 16, 0, (void*)lpszLocalUser, 0);
    }

    inline char* GetRemoteHost() {
      void* val = IPWorks_Rshell_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemoteHost(const char* lpszRemoteHost) {
      return IPWorks_Rshell_Set(m_pObj, 17, 0, (void*)lpszRemoteHost, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_Rshell_Get(m_pObj, 18, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRemotePort(int iRemotePort) {
      void* val = (void*)IPW64CAST(iRemotePort);
      return IPWorks_Rshell_Set(m_pObj, 18, 0, val, 0);
    }

    inline char* GetRemoteUser() {
      void* val = IPWorks_Rshell_Get(m_pObj, 19, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemoteUser(const char* lpszRemoteUser) {
      return IPWorks_Rshell_Set(m_pObj, 19, 0, (void*)lpszRemoteUser, 0);
    }

    inline int GetStderr(char* &lpStderr, int &lenStderr) {
      lpStderr = (char*)IPWorks_Rshell_Get(m_pObj, 20, 0, &lenStderr, NULL);
      return lpStderr ? 0 : lenStderr;
    }

    inline int SetStdin(const char* lpStdin, int lenStdin) {
      return IPWorks_Rshell_Set(m_pObj, 21, 0, (void*)lpStdin, lenStdin);
    }

    inline int GetStdout(char* &lpStdout, int &lenStdout) {
      lpStdout = (char*)IPWorks_Rshell_Get(m_pObj, 22, 0, &lenStdout, NULL);
      return lpStdout ? 0 : lenStdout;
    }

    inline int GetTimeout() {
      void* val = IPWorks_Rshell_Get(m_pObj, 23, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_Rshell_Set(m_pObj, 23, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Rshell_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Execute(const char* lpszCommand) {
      void *param[1+1] = {(void*)IPW64CAST(lpszCommand), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Rshell_Do(m_pObj, 5, 1, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int Send(const char* lpText, int lenText) {
      void *param[1+1] = {(void*)IPW64CAST(lpText), 0};
      int cbparam[1+1] = {lenText, 0};
      return IPWorks_Rshell_Do(m_pObj, 8, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_RSHELL_H_