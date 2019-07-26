/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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


extern "C" void* IPWORKS_CALL IPWorks_RCP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_RCP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_RCP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_RCP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_RCP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_RCP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RCP_GetLastErrorCode(void *lpObj);
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
  const char* Description;
  int reserved;
} RCPConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} RCPConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} RCPDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} RCPErrorEventParams;

typedef struct {
  int PercentDone;
  int reserved;
} RCPProgressEventParams;



class RCP {
  
  public: //events
  
    virtual int FireConnected(RCPConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(RCPConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(RCPDisconnectedEventParams *e) {return 0;}
    virtual int FireError(RCPErrorEventParams *e) {return 0;}
    virtual int FireProgress(RCPProgressEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL RCPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((RCP*)lpObj)->RCPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            RCPConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((RCP*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            RCPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((RCP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            RCPDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((RCP*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            RCPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((RCP*)lpObj)->FireError(&e);
            break;
         }
         case 5: {
            RCPProgressEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((RCP*)lpObj)->FireProgress(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int RCPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    RCP(char *lpOemKey = (char*)IPWORKS_OEMKEY_45) {
      m_pObj = IPWorks_RCP_Create(RCPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~RCP() {
      IPWorks_RCP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_RCP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_RCP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_RCP_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_RCP_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_RCP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetFileMode() {
      void* val = IPWorks_RCP_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetFileMode(const char *lpFileMode) {
      return IPWorks_RCP_Set(m_pObj, 1, 0, (void*)lpFileMode, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_RCP_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_RCP_Set(m_pObj, 2, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_RCP_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_RCP_Set(m_pObj, 3, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_RCP_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_RCP_Set(m_pObj, 4, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_RCP_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_RCP_Set(m_pObj, 5, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_RCP_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_RCP_Set(m_pObj, 6, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_RCP_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_RCP_Set(m_pObj, 7, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_RCP_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_RCP_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_RCP_Set(m_pObj, 9, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_RCP_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_RCP_Set(m_pObj, 10, 0, (void*)lpLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_RCP_Get(m_pObj, 11, 0, 0);
      return (int)(long)val;
    }
    inline int SetLocalPort(int lLocalPort) {
      void* val = (void*)IPW64CAST(lLocalPort);
      return IPWorks_RCP_Set(m_pObj, 11, 0, val, 0);
    }
    inline char* GetPassword() {
      void* val = IPWorks_RCP_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_RCP_Set(m_pObj, 12, 0, (void*)lpPassword, 0);
    }

    inline int GetProtocol() {
      void* val = IPWorks_RCP_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }
    inline int SetProtocol(int iProtocol) {
      void* val = (void*)IPW64CAST(iProtocol);
      return IPWorks_RCP_Set(m_pObj, 13, 0, val, 0);
    }
    inline char* GetRemoteFile() {
      void* val = IPWorks_RCP_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteFile(const char *lpRemoteFile) {
      return IPWorks_RCP_Set(m_pObj, 14, 0, (void*)lpRemoteFile, 0);
    }

    inline char* GetRemoteHost() {
      void* val = IPWorks_RCP_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteHost(const char *lpRemoteHost) {
      return IPWorks_RCP_Set(m_pObj, 15, 0, (void*)lpRemoteHost, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_RCP_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetRemotePort(int lRemotePort) {
      void* val = (void*)IPW64CAST(lRemotePort);
      return IPWorks_RCP_Set(m_pObj, 16, 0, val, 0);
    }
    inline int GetTimeout() {
      void* val = IPWorks_RCP_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_RCP_Set(m_pObj, 17, 0, val, 0);
    }
    inline char* GetUser() {
      void* val = IPWorks_RCP_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_RCP_Set(m_pObj, 18, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RCP_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int GetFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int PutFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RCPConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RCPConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RCPDisconnectedEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} RCPErrorEventParamsW;

typedef struct {
  int PercentDone;
  int reserved;
} RCPProgressEventParamsW;



class RCPW : public RCP {

  public: //properties
  
    inline LPWSTR GetFileMode() {
      return (LPWSTR)IPWorks_RCP_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetFileMode(LPCWSTR lpFileMode) {
      return IPWorks_RCP_Set(m_pObj, 10000+1, 0, (void*)lpFileMode, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_RCP_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_RCP_Set(m_pObj, 10000+4, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_RCP_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_RCP_Set(m_pObj, 10000+5, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_RCP_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_RCP_Set(m_pObj, 10000+7, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_RCP_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetLocalFile(LPCWSTR lpLocalFile) {
      return IPWorks_RCP_Set(m_pObj, 10000+9, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_RCP_Get(m_pObj, 10000+10, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_RCP_Set(m_pObj, 10000+10, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_RCP_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_RCP_Set(m_pObj, 10000+12, 0, (void*)lpPassword, 0);
    }



    inline LPWSTR GetRemoteFile() {
      return (LPWSTR)IPWorks_RCP_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetRemoteFile(LPCWSTR lpRemoteFile) {
      return IPWorks_RCP_Set(m_pObj, 10000+14, 0, (void*)lpRemoteFile, 0);
    }

    inline LPWSTR GetRemoteHost() {
      return (LPWSTR)IPWorks_RCP_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetRemoteHost(LPCWSTR lpRemoteHost) {
      return IPWorks_RCP_Set(m_pObj, 10000+15, 0, (void*)lpRemoteHost, 0);
    }





    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_RCP_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_RCP_Set(m_pObj, 10000+18, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnected(RCPConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(RCPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(RCPDisconnectedEventParamsW *e) {return 0;}
    virtual int FireError(RCPErrorEventParamsW *e) {return 0;}
    virtual int FireProgress(RCPProgressEventParamsW *e) {return 0;}


  protected:
  
    virtual int RCPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            RCPConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            RCPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            RCPDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            RCPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 5: {
            RCPProgressEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireProgress(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(RCPConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(RCPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(RCPDisconnectedEventParams *e) {return -10000;}
    virtual int FireError(RCPErrorEventParams *e) {return -10000;}
    virtual int FireProgress(RCPProgressEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RCP_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int GetFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int PutFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RCP_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_RCP_H_




