/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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


extern "C" void* IPWORKS_CALL IPWorks_Whois_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_Whois_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Whois_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Whois_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_Whois_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Whois_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_Whois_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Whois_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Whois_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Whois_StaticDestroy();

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
} WhoisConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} WhoisConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} WhoisDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} WhoisErrorEventParams;



class Whois {
  
  public: //events
  
    virtual int FireConnected(WhoisConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(WhoisConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(WhoisDisconnectedEventParams *e) {return 0;}
    virtual int FireError(WhoisErrorEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL WhoisEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((Whois*)lpObj)->WhoisEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            WhoisConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Whois*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            WhoisConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((Whois*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            WhoisDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Whois*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            WhoisErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Whois*)lpObj)->FireError(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int WhoisEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    Whois(char *lpOemKey = (char*)IPWORKS_OEMKEY_53) {
      m_pObj = IPWorks_Whois_Create(WhoisEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~Whois() {
      IPWorks_Whois_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_Whois_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_Whois_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_Whois_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_Whois_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_Whois_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetDefaultServer() {
      void* val = IPWorks_Whois_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetDefaultServer(const char *lpDefaultServer) {
      return IPWorks_Whois_Set(m_pObj, 1, 0, (void*)lpDefaultServer, 0);
    }

    inline char* GetDomainInfo() {
      void* val = IPWorks_Whois_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }


    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_Whois_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_Whois_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_Whois_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_Whois_Set(m_pObj, 4, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_Whois_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_Whois_Set(m_pObj, 5, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_Whois_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_Whois_Set(m_pObj, 6, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_Whois_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_Whois_Set(m_pObj, 7, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_Whois_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_Whois_Set(m_pObj, 8, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_Whois_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_Whois_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_Whois_Set(m_pObj, 10, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetServer() {
      void* val = IPWorks_Whois_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetServer(const char *lpServer) {
      return IPWorks_Whois_Set(m_pObj, 11, 0, (void*)lpServer, 0);
    }

    inline int GetServerPort() {
      void* val = IPWorks_Whois_Get(m_pObj, 12, 0, 0);
      return (int)(long)val;
    }
    inline int SetServerPort(int lServerPort) {
      void* val = (void*)IPW64CAST(lServerPort);
      return IPWorks_Whois_Set(m_pObj, 12, 0, val, 0);
    }
    inline int GetTimeout() {
      void* val = IPWorks_Whois_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_Whois_Set(m_pObj, 13, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Whois_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Whois_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Whois_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Query(const char* lpszDomain) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDomain), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Whois_Do(m_pObj, 5, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Whois_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WhoisConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WhoisConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WhoisDisconnectedEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} WhoisErrorEventParamsW;



class WhoisW : public Whois {

  public: //properties
  
    inline LPWSTR GetDefaultServer() {
      return (LPWSTR)IPWorks_Whois_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetDefaultServer(LPCWSTR lpDefaultServer) {
      return IPWorks_Whois_Set(m_pObj, 10000+1, 0, (void*)lpDefaultServer, 0);
    }

    inline LPWSTR GetDomainInfo() {
      return (LPWSTR)IPWorks_Whois_Get(m_pObj, 10000+2, 0, 0);
    }







    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_Whois_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_Whois_Set(m_pObj, 10000+5, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_Whois_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_Whois_Set(m_pObj, 10000+6, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_Whois_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_Whois_Set(m_pObj, 10000+8, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_Whois_Get(m_pObj, 10000+10, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_Whois_Set(m_pObj, 10000+10, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetServer() {
      return (LPWSTR)IPWorks_Whois_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetServer(LPCWSTR lpServer) {
      return IPWorks_Whois_Set(m_pObj, 10000+11, 0, (void*)lpServer, 0);
    }







  public: //events
  
    virtual int FireConnected(WhoisConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(WhoisConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(WhoisDisconnectedEventParamsW *e) {return 0;}
    virtual int FireError(WhoisErrorEventParamsW *e) {return 0;}


  protected:
  
    virtual int WhoisEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            WhoisConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            WhoisConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            WhoisDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            WhoisErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(WhoisConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(WhoisConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(WhoisDisconnectedEventParams *e) {return -10000;}
    virtual int FireError(WhoisErrorEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Whois_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Whois_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Whois_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Query(LPWSTR lpszDomain) {
      void *param[1+1] = {(void*)lpszDomain, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Whois_Do(m_pObj, 10000+5, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Whois_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_WHOIS_H_




