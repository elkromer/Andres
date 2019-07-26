/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_MX_H_
#define _IPWORKS_MX_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_MX_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_MX_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_MX_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_MX_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_MX_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_MX_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_MX_StaticDestroy();

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
} MXErrorEventParams;

typedef struct {
  int RequestId;
  const char* Domain;
  const char* MailServer;
  int Precedence;
  int TimeToLive;
  int StatusCode;
  const char* Description;
  int Authoritative;
  int reserved;
} MXResponseEventParams;



class MX {
  
  public: //events
  
    virtual int FireError(MXErrorEventParams *e) {return 0;}
    virtual int FireResponse(MXResponseEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL MXEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((MX*)lpObj)->MXEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            MXErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((MX*)lpObj)->FireError(&e);
            break;
         }
         case 2: {
            MXResponseEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), (int)IPW64CAST(param[7]),  0};
            ret_code = ((MX*)lpObj)->FireResponse(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int MXEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    MX(char *lpOemKey = (char*)IPWORKS_OEMKEY_29) {
      m_pObj = IPWorks_MX_Create(MXEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~MX() {
      IPWorks_MX_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_MX_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_MX_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_MX_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_MX_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_MX_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetDNSPort() {
      void* val = IPWorks_MX_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetDNSPort(int lDNSPort) {
      void* val = (void*)IPW64CAST(lDNSPort);
      return IPWorks_MX_Set(m_pObj, 1, 0, val, 0);
    }
    inline char* GetDNSServer() {
      void* val = IPWorks_MX_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetDNSServer(const char *lpDNSServer) {
      return IPWorks_MX_Set(m_pObj, 2, 0, (void*)lpDNSServer, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_MX_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_MX_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_MX_Set(m_pObj, 4, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetMailServer() {
      void* val = IPWorks_MX_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }


    inline int GetRequestId() {
      void* val = IPWorks_MX_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetRequestId(int iRequestId) {
      void* val = (void*)IPW64CAST(iRequestId);
      return IPWorks_MX_Set(m_pObj, 6, 0, val, 0);
    }
    inline char* GetStatus() {
      void* val = IPWorks_MX_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }


    inline int GetTimeout() {
      void* val = IPWorks_MX_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_MX_Set(m_pObj, 8, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_MX_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int Resolve(const char* lpszEmailAddress) {
      void *param[1+1] = {(void*)IPW64CAST(lpszEmailAddress), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_MX_Do(m_pObj, 6, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} MXErrorEventParamsW;

typedef struct {
  int RequestId;
  LPWSTR Domain;
  LPWSTR MailServer;
  int Precedence;
  int TimeToLive;
  int StatusCode;
  LPWSTR Description;
  int Authoritative;
  int reserved;
} MXResponseEventParamsW;



class MXW : public MX {

  public: //properties
  


    inline LPWSTR GetDNSServer() {
      return (LPWSTR)IPWorks_MX_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetDNSServer(LPCWSTR lpDNSServer) {
      return IPWorks_MX_Set(m_pObj, 10000+2, 0, (void*)lpDNSServer, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_MX_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_MX_Set(m_pObj, 10000+4, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetMailServer() {
      return (LPWSTR)IPWorks_MX_Get(m_pObj, 10000+5, 0, 0);
    }





    inline LPWSTR GetStatus() {
      return (LPWSTR)IPWorks_MX_Get(m_pObj, 10000+7, 0, 0);
    }







  public: //events
  
    virtual int FireError(MXErrorEventParamsW *e) {return 0;}
    virtual int FireResponse(MXResponseEventParamsW *e) {return 0;}


  protected:
  
    virtual int MXEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            MXErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 2: {
            MXResponseEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), (LPWSTR)IPW64CAST(param[6]), (int)IPW64CAST(param[7]),  0};
            ret_code = FireResponse(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireError(MXErrorEventParams *e) {return -10000;}
    virtual int FireResponse(MXResponseEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_MX_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int Resolve(LPWSTR lpszEmailAddress) {
      void *param[1+1] = {(void*)lpszEmailAddress, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_MX_Do(m_pObj, 10000+6, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_MX_H_




