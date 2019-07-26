/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_TRACEROUTE_H_
#define _IPWORKS_TRACEROUTE_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_TraceRoute_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_TraceRoute_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_TraceRoute_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_StaticDestroy();

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
} TraceRouteErrorEventParams;

typedef struct {
  int HopNumber;
  const char* HostAddress;
  int Duration;
  int reserved;
} TraceRouteHopEventParams;

typedef struct {
  int HopNumber;
  int StatusCode;
  const char* HopHostName;
  int reserved;
} TraceRouteHopResolvedEventParams;



class TraceRoute {
  
  public: //events
  
    virtual int FireError(TraceRouteErrorEventParams *e) {return 0;}
    virtual int FireHop(TraceRouteHopEventParams *e) {return 0;}
    virtual int FireHopResolved(TraceRouteHopResolvedEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL TraceRouteEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((TraceRoute*)lpObj)->TraceRouteEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            TraceRouteErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((TraceRoute*)lpObj)->FireError(&e);
            break;
         }
         case 2: {
            TraceRouteHopEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = ((TraceRoute*)lpObj)->FireHop(&e);
            break;
         }
         case 3: {
            TraceRouteHopResolvedEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((TraceRoute*)lpObj)->FireHopResolved(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int TraceRouteEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    TraceRoute(char *lpOemKey = (char*)IPWORKS_OEMKEY_48) {
      m_pObj = IPWorks_TraceRoute_Create(TraceRouteEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~TraceRoute() {
      IPWorks_TraceRoute_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_TraceRoute_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_TraceRoute_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_TraceRoute_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_TraceRoute_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_TraceRoute_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetHopLimit() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetHopLimit(int iHopLimit) {
      void* val = (void*)IPW64CAST(iHopLimit);
      return IPWorks_TraceRoute_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetHopCount() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }

    inline int GetHopErrorCode(int iHopIndex) {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 3, iHopIndex, 0);
      return (int)(long)val;
    }

    inline char* GetHopErrorDescription(int iHopIndex) {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 4, iHopIndex, 0);
      return (char*)val;
    }


    inline char* GetHopHostAddress(int iHopIndex) {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 5, iHopIndex, 0);
      return (char*)val;
    }


    inline char* GetHopHostName(int iHopIndex) {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 6, iHopIndex, 0);
      return (char*)val;
    }


    inline int GetHopTime(int iHopIndex) {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 7, iHopIndex, 0);
      return (int)(long)val;
    }

    inline int GetHopTimeout() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetHopTimeout(int iHopTimeout) {
      void* val = (void*)IPW64CAST(iHopTimeout);
      return IPWorks_TraceRoute_Set(m_pObj, 8, 0, val, 0);
    }
    inline int GetIdle() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_TraceRoute_Set(m_pObj, 10, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetRemoteHost() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteHost(const char *lpRemoteHost) {
      return IPWorks_TraceRoute_Set(m_pObj, 11, 0, (void*)lpRemoteHost, 0);
    }

    inline int GetResolveNames() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 12, 0, 0);
      return (int)(long)val;
    }
    inline int SetResolveNames(int bResolveNames) {
      void* val = (void*)IPW64CAST(bResolveNames);
      return IPWorks_TraceRoute_Set(m_pObj, 12, 0, val, 0);
    }
    inline int GetTimeout() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_TraceRoute_Set(m_pObj, 13, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_TraceRoute_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int TraceTo(const char* lpszHost) {
      void *param[1+1] = {(void*)IPW64CAST(lpszHost), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_TraceRoute_Do(m_pObj, 6, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} TraceRouteErrorEventParamsW;

typedef struct {
  int HopNumber;
  LPWSTR HostAddress;
  int Duration;
  int reserved;
} TraceRouteHopEventParamsW;

typedef struct {
  int HopNumber;
  int StatusCode;
  LPWSTR HopHostName;
  int reserved;
} TraceRouteHopResolvedEventParamsW;



class TraceRouteW : public TraceRoute {

  public: //properties
  






    inline LPWSTR GetHopErrorDescription(int iHopIndex) {
      return (LPWSTR)IPWorks_TraceRoute_Get(m_pObj, 10000+4, iHopIndex, 0);
    }



    inline LPWSTR GetHopHostAddress(int iHopIndex) {
      return (LPWSTR)IPWorks_TraceRoute_Get(m_pObj, 10000+5, iHopIndex, 0);
    }



    inline LPWSTR GetHopHostName(int iHopIndex) {
      return (LPWSTR)IPWorks_TraceRoute_Get(m_pObj, 10000+6, iHopIndex, 0);
    }









    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_TraceRoute_Get(m_pObj, 10000+10, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_TraceRoute_Set(m_pObj, 10000+10, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetRemoteHost() {
      return (LPWSTR)IPWorks_TraceRoute_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetRemoteHost(LPCWSTR lpRemoteHost) {
      return IPWorks_TraceRoute_Set(m_pObj, 10000+11, 0, (void*)lpRemoteHost, 0);
    }







  public: //events
  
    virtual int FireError(TraceRouteErrorEventParamsW *e) {return 0;}
    virtual int FireHop(TraceRouteHopEventParamsW *e) {return 0;}
    virtual int FireHopResolved(TraceRouteHopResolvedEventParamsW *e) {return 0;}


  protected:
  
    virtual int TraceRouteEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            TraceRouteErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 2: {
            TraceRouteHopEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = FireHop(&e);
            break;
         }
         case 3: {
            TraceRouteHopResolvedEventParamsW e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireHopResolved(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireError(TraceRouteErrorEventParams *e) {return -10000;}
    virtual int FireHop(TraceRouteHopEventParams *e) {return -10000;}
    virtual int FireHopResolved(TraceRouteHopResolvedEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_TraceRoute_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int TraceTo(LPWSTR lpszHost) {
      void *param[1+1] = {(void*)lpszHost, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_TraceRoute_Do(m_pObj, 10000+6, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_TRACEROUTE_H_




