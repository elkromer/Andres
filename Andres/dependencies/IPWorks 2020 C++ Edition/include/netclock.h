/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_NETCLOCK_H_
#define _IPWORKS_NETCLOCK_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//TProtocol
#define TP_TIME                                            0
#define TP_SNTP                                            1


extern "C" void* IPWORKS_CALL IPWorks_NetClock_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NetClock_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_NetClock_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_NetClock_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_StaticDestroy();

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
} NetClockErrorEventParams;


class NetClock {
  public: // Events
    virtual int FireError(NetClockErrorEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL NetClockEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          NetClockErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((NetClock*)lpObj)->FireError(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    NetClock(char *lpOemKey = (char*)IPWORKS_OEMKEY_43) {
      m_pObj = IPWorks_NetClock_Create(NetClockEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~NetClock() {
      IPWorks_NetClock_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_NetClock_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_NetClock_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_NetClock_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_NetClock_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_NetClock_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetIdle() {
      void* val = IPWorks_NetClock_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_NetClock_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_NetClock_Set(m_pObj, 2, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetLocalTime() {
      void* val = IPWorks_NetClock_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetProtocol() {
      void* val = IPWorks_NetClock_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProtocol(int iProtocol) {
      void* val = (void*)IPW64CAST(iProtocol);
      return IPWorks_NetClock_Set(m_pObj, 4, 0, val, 0);
    }

    inline char* GetServerTime() {
      void* val = IPWorks_NetClock_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetTimeout() {
      void* val = IPWorks_NetClock_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_NetClock_Set(m_pObj, 6, 0, val, 0);
    }

    inline int GetTimePort() {
      void* val = IPWorks_NetClock_Get(m_pObj, 7, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimePort(int iTimePort) {
      void* val = (void*)IPW64CAST(iTimePort);
      return IPWorks_NetClock_Set(m_pObj, 7, 0, val, 0);
    }

    inline char* GetTimeServer() {
      void* val = IPWorks_NetClock_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimeServer(const char* lpszTimeServer) {
      return IPWorks_NetClock_Set(m_pObj, 8, 0, (void*)lpszTimeServer, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NetClock_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int GetAndSetTime() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int GetTime() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_NETCLOCK_H_
