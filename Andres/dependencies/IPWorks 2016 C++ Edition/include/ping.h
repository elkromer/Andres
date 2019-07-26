/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_PING_H_
#define _IPWORKS_PING_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_Ping_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_Ping_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Ping_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Ping_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_Ping_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Ping_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_Ping_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Ping_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Ping_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Ping_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} PingErrorEventParams;

typedef struct {
  int RequestId;
  const char* ResponseSource;
  const char* ResponseStatus;
  int ResponseTime;
  int reserved;
} PingResponseEventParams;



class Ping {
  
  public: //events
  
    virtual int FireError(PingErrorEventParams *e) {return 0;}
    virtual int FireResponse(PingResponseEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL PingEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((Ping*)lpObj)->PingEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            PingErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Ping*)lpObj)->FireError(&e);
            break;
         }
         case 2: {
            PingResponseEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = ((Ping*)lpObj)->FireResponse(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int PingEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    Ping(char *lpOemKey = (char*)IPWORKS_OEMKEY_44) {
      m_pObj = IPWorks_Ping_Create(PingEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~Ping() {
      IPWorks_Ping_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_Ping_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_Ping_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_Ping_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_Ping_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_Ping_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetActive() {
      void* val = IPWorks_Ping_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetActive(int bActive) {
      void* val = (void*)IPW64CAST(bActive);
      return IPWorks_Ping_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetIdle() {
      void* val = IPWorks_Ping_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_Ping_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_Ping_Set(m_pObj, 3, 0, (void*)lpLocalHost, 0);
    }

    inline int GetPacketSize() {
      void* val = IPWorks_Ping_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetPacketSize(int iPacketSize) {
      void* val = (void*)IPW64CAST(iPacketSize);
      return IPWorks_Ping_Set(m_pObj, 4, 0, val, 0);
    }
    inline char* GetRemoteHost() {
      void* val = IPWorks_Ping_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteHost(const char *lpRemoteHost) {
      return IPWorks_Ping_Set(m_pObj, 5, 0, (void*)lpRemoteHost, 0);
    }

    inline int GetRequestId() {
      void* val = IPWorks_Ping_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }

    inline char* GetResponseSource() {
      void* val = IPWorks_Ping_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }


    inline int GetResponseTime() {
      void* val = IPWorks_Ping_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }

    inline int GetTimeout() {
      void* val = IPWorks_Ping_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_Ping_Set(m_pObj, 9, 0, val, 0);
    }
    inline int GetTimeToLive() {
      void* val = IPWorks_Ping_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeToLive(int iTimeToLive) {
      void* val = (void*)IPW64CAST(iTimeToLive);
      return IPWorks_Ping_Set(m_pObj, 10, 0, val, 0);
    }
    inline int GetTypeOfService() {
      void* val = IPWorks_Ping_Get(m_pObj, 11, 0, 0);
      return (int)(long)val;
    }
    inline int SetTypeOfService(int iTypeOfService) {
      void* val = (void*)IPW64CAST(iTypeOfService);
      return IPWorks_Ping_Set(m_pObj, 11, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Ping_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Ping_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Ping_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int PingHost(const char* lpszHost) {
      void *param[1+1] = {(void*)IPW64CAST(lpszHost), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Ping_Do(m_pObj, 5, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Ping_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int WakeOnLAN(const char* lpszRemoteHost, const char* lpszMACAddress) {
      void *param[2+1] = {(void*)IPW64CAST(lpszRemoteHost), (void*)IPW64CAST(lpszMACAddress), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Ping_Do(m_pObj, 7, 2, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} PingErrorEventParamsW;

typedef struct {
  int RequestId;
  LPWSTR ResponseSource;
  LPWSTR ResponseStatus;
  int ResponseTime;
  int reserved;
} PingResponseEventParamsW;



class PingW : public Ping {

  public: //properties
  




    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_Ping_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_Ping_Set(m_pObj, 10000+3, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetRemoteHost() {
      return (LPWSTR)IPWorks_Ping_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetRemoteHost(LPCWSTR lpRemoteHost) {
      return IPWorks_Ping_Set(m_pObj, 10000+5, 0, (void*)lpRemoteHost, 0);
    }



    inline LPWSTR GetResponseSource() {
      return (LPWSTR)IPWorks_Ping_Get(m_pObj, 10000+7, 0, 0);
    }













  public: //events
  
    virtual int FireError(PingErrorEventParamsW *e) {return 0;}
    virtual int FireResponse(PingResponseEventParamsW *e) {return 0;}


  protected:
  
    virtual int PingEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            PingErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 2: {
            PingResponseEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = FireResponse(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireError(PingErrorEventParams *e) {return -10000;}
    virtual int FireResponse(PingResponseEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Ping_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Ping_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Ping_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int PingHost(LPWSTR lpszHost) {
      void *param[1+1] = {(void*)lpszHost, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Ping_Do(m_pObj, 10000+5, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Ping_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int WakeOnLAN(LPWSTR lpszRemoteHost, LPWSTR lpszMACAddress) {
      void *param[2+1] = {(void*)lpszRemoteHost, (void*)lpszMACAddress, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Ping_Do(m_pObj, 10000+7, 2, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_PING_H_




