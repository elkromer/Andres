/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_RCP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_RCP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_RCP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_RCP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_RCP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_RCP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_RCP_StaticDestroy();

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
} RCPConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} RCPConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} RCPDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} RCPErrorEventParams;

typedef struct {
  int PercentDone;
  int reserved;
} RCPProgressEventParams;


class RCP {
  public: // Events
    virtual int FireConnected(RCPConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(RCPConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(RCPDisconnectedEventParams *e) {return 0;}
    virtual int FireError(RCPErrorEventParams *e) {return 0;}
    virtual int FireProgress(RCPProgressEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL RCPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          RCPConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((RCP*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          RCPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((RCP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          RCPDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((RCP*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          RCPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((RCP*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          RCPProgressEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((RCP*)lpObj)->FireProgress(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    RCP(char *lpOemKey = (char*)IPWORKS_OEMKEY_45) {
      m_pObj = IPWorks_RCP_Create(RCPEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~RCP() {
      IPWorks_RCP_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_RCP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_RCP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_RCP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_RCP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_RCP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetFileMode() {
      void* val = IPWorks_RCP_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFileMode(const char* lpszFileMode) {
      return IPWorks_RCP_Set(m_pObj, 1, 0, (void*)lpszFileMode, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_RCP_Get(m_pObj, 2, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_RCP_Set(m_pObj, 2, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_RCP_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_RCP_Set(m_pObj, 3, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_RCP_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_RCP_Set(m_pObj, 4, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_RCP_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_RCP_Set(m_pObj, 5, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_RCP_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_RCP_Set(m_pObj, 6, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_RCP_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_RCP_Set(m_pObj, 7, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_RCP_Get(m_pObj, 8, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_RCP_Get(m_pObj, 9, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_RCP_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_RCP_Set(m_pObj, 9, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_RCP_Set(m_pObj, 9+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_RCP_Get(m_pObj, 10, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_RCP_Set(m_pObj, 10, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_RCP_Get(m_pObj, 11, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetLocalPort(int iLocalPort) {
      void* val = (void*)IPW64CAST(iLocalPort);
      return IPWorks_RCP_Set(m_pObj, 11, 0, val, 0);
    }

    inline char* GetPassword() {
      void* val = IPWorks_RCP_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_RCP_Set(m_pObj, 12, 0, (void*)lpszPassword, 0);
    }

    inline int GetProtocol() {
      void* val = IPWorks_RCP_Get(m_pObj, 13, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProtocol(int iProtocol) {
      void* val = (void*)IPW64CAST(iProtocol);
      return IPWorks_RCP_Set(m_pObj, 13, 0, val, 0);
    }

    inline char* GetRemoteFile() {
      void* val = IPWorks_RCP_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemoteFile(const char* lpszRemoteFile) {
      return IPWorks_RCP_Set(m_pObj, 14, 0, (void*)lpszRemoteFile, 0);
    }

    inline char* GetRemoteHost() {
      void* val = IPWorks_RCP_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemoteHost(const char* lpszRemoteHost) {
      return IPWorks_RCP_Set(m_pObj, 15, 0, (void*)lpszRemoteHost, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_RCP_Get(m_pObj, 16, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRemotePort(int iRemotePort) {
      void* val = (void*)IPW64CAST(iRemotePort);
      return IPWorks_RCP_Set(m_pObj, 16, 0, val, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_RCP_Get(m_pObj, 17, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_RCP_Set(m_pObj, 17, 0, val, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_RCP_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_RCP_Set(m_pObj, 18, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RCP_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int GetFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int PutFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_RCP_H_
