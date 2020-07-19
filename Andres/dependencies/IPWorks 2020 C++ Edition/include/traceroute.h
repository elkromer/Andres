/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_TRACEROUTE_H_
#define _IPWORKS_TRACEROUTE_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_TraceRoute_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_TraceRoute_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_TraceRoute_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_TraceRoute_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TraceRoute_SetEventErrorAndCode(void *lpObj, int code, char *message);
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
  const char *Description;
  int reserved;
} TraceRouteErrorEventParams;

typedef struct {
  int HopNumber;
  const char *HostAddress;
  int Duration;
  int reserved;
} TraceRouteHopEventParams;

typedef struct {
  int HopNumber;
  int StatusCode;
  const char *HopHostName;
  int reserved;
} TraceRouteHopResolvedEventParams;


class TraceRoute {
  public: // Events
    virtual int FireError(TraceRouteErrorEventParams *e) {return 0;}
    virtual int FireHop(TraceRouteHopEventParams *e) {return 0;}
    virtual int FireHopResolved(TraceRouteHopResolvedEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL TraceRouteEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          TraceRouteErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((TraceRoute*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          TraceRouteHopEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), 0};
          ret_code = ((TraceRoute*)lpObj)->FireHop(&e);
          break;
        }
        case 3: {
          TraceRouteHopResolvedEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((TraceRoute*)lpObj)->FireHopResolved(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    TraceRoute(char *lpOemKey = (char*)IPWORKS_OEMKEY_48) {
      m_pObj = IPWorks_TraceRoute_Create(TraceRouteEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~TraceRoute() {
      IPWorks_TraceRoute_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_TraceRoute_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_TraceRoute_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_TraceRoute_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_TraceRoute_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_TraceRoute_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetHopLimit() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetHopLimit(int iHopLimit) {
      void* val = (void*)IPW64CAST(iHopLimit);
      return IPWorks_TraceRoute_Set(m_pObj, 1, 0, val, 0);
    }

    inline int GetHopCount() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 2, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetHopErrorCode(int iHopIndex) {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 3, iHopIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetHopErrorDescription(int iHopIndex) {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 4, iHopIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetHopHostAddress(int iHopIndex) {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 5, iHopIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetHopHostName(int iHopIndex) {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 6, iHopIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetHopTime(int iHopIndex) {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 7, iHopIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetHopTimeout() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 8, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetHopTimeout(int iHopTimeout) {
      void* val = (void*)IPW64CAST(iHopTimeout);
      return IPWorks_TraceRoute_Set(m_pObj, 8, 0, val, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 9, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 10, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_TraceRoute_Set(m_pObj, 10, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetRemoteHost() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemoteHost(const char* lpszRemoteHost) {
      return IPWorks_TraceRoute_Set(m_pObj, 11, 0, (void*)lpszRemoteHost, 0);
    }

    inline int GetResolveNames() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 12, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetResolveNames(int bResolveNames) {
      void* val = (void*)IPW64CAST(bResolveNames);
      return IPWorks_TraceRoute_Set(m_pObj, 12, 0, val, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_TraceRoute_Get(m_pObj, 13, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_TraceRoute_Set(m_pObj, 13, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_TraceRoute_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TraceRoute_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int TraceTo(const char* lpszHost) {
      void *param[1+1] = {(void*)IPW64CAST(lpszHost), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_TraceRoute_Do(m_pObj, 6, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_TRACEROUTE_H_
