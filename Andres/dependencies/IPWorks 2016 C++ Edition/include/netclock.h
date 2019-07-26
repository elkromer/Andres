/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_NETCLOCK_H_
#define _IPWORKS_NETCLOCK_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//TProtocol
#define TP_TIME                                            0
#define TP_SNTP                                            1


extern "C" void* IPWORKS_CALL IPWorks_NetClock_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NetClock_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_NetClock_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetClock_GetLastErrorCode(void *lpObj);
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
  const char* Description;
  int reserved;
} NetClockErrorEventParams;



class NetClock {
  
  public: //events
  
    virtual int FireError(NetClockErrorEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL NetClockEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((NetClock*)lpObj)->NetClockEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            NetClockErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((NetClock*)lpObj)->FireError(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int NetClockEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    NetClock(char *lpOemKey = (char*)IPWORKS_OEMKEY_43) {
      m_pObj = IPWorks_NetClock_Create(NetClockEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~NetClock() {
      IPWorks_NetClock_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_NetClock_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_NetClock_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_NetClock_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_NetClock_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_NetClock_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetIdle() {
      void* val = IPWorks_NetClock_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_NetClock_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_NetClock_Set(m_pObj, 2, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetLocalTime() {
      void* val = IPWorks_NetClock_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }


    inline int GetProtocol() {
      void* val = IPWorks_NetClock_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetProtocol(int iProtocol) {
      void* val = (void*)IPW64CAST(iProtocol);
      return IPWorks_NetClock_Set(m_pObj, 4, 0, val, 0);
    }
    inline char* GetServerTime() {
      void* val = IPWorks_NetClock_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }


    inline int GetTimeout() {
      void* val = IPWorks_NetClock_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_NetClock_Set(m_pObj, 6, 0, val, 0);
    }
    inline int GetTimePort() {
      void* val = IPWorks_NetClock_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimePort(int lTimePort) {
      void* val = (void*)IPW64CAST(lTimePort);
      return IPWorks_NetClock_Set(m_pObj, 7, 0, val, 0);
    }
    inline char* GetTimeServer() {
      void* val = IPWorks_NetClock_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetTimeServer(const char *lpTimeServer) {
      return IPWorks_NetClock_Set(m_pObj, 8, 0, (void*)lpTimeServer, 0);
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NetClock_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int GetAndSetTime() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int GetTime() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} NetClockErrorEventParamsW;



class NetClockW : public NetClock {

  public: //properties
  


    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_NetClock_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_NetClock_Set(m_pObj, 10000+2, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetLocalTime() {
      return (LPWSTR)IPWorks_NetClock_Get(m_pObj, 10000+3, 0, 0);
    }





    inline LPWSTR GetServerTime() {
      return (LPWSTR)IPWorks_NetClock_Get(m_pObj, 10000+5, 0, 0);
    }







    inline LPWSTR GetTimeServer() {
      return (LPWSTR)IPWorks_NetClock_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetTimeServer(LPCWSTR lpTimeServer) {
      return IPWorks_NetClock_Set(m_pObj, 10000+8, 0, (void*)lpTimeServer, 0);
    }



  public: //events
  
    virtual int FireError(NetClockErrorEventParamsW *e) {return 0;}


  protected:
  
    virtual int NetClockEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            NetClockErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireError(NetClockErrorEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NetClock_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int GetAndSetTime() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int GetTime() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetClock_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_NETCLOCK_H_




