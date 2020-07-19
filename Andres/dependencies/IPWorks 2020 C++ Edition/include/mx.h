/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_MX_H_
#define _IPWORKS_MX_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_MX_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_MX_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_MX_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_MX_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_MX_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_MX_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_MX_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MX_SetEventErrorAndCode(void *lpObj, int code, char *message);
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
  const char *Description;
  int reserved;
} MXErrorEventParams;

typedef struct {
  int RequestId;
  const char *Domain;
  const char *MailServer;
  int Precedence;
  int TimeToLive;
  int StatusCode;
  const char *Description;
  int Authoritative;
  int reserved;
} MXResponseEventParams;


class MX {
  public: // Events
    virtual int FireError(MXErrorEventParams *e) {return 0;}
    virtual int FireResponse(MXResponseEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL MXEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          MXErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((MX*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          MXResponseEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), (int)IPW64CAST(param[7]), 0};
          ret_code = ((MX*)lpObj)->FireResponse(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    MX(char *lpOemKey = (char*)IPWORKS_OEMKEY_29) {
      m_pObj = IPWorks_MX_Create(MXEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~MX() {
      IPWorks_MX_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_MX_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_MX_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_MX_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_MX_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_MX_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetDNSPort() {
      void* val = IPWorks_MX_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetDNSPort(int iDNSPort) {
      void* val = (void*)IPW64CAST(iDNSPort);
      return IPWorks_MX_Set(m_pObj, 1, 0, val, 0);
    }

    inline char* GetDNSServer() {
      void* val = IPWorks_MX_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetDNSServer(const char* lpszDNSServer) {
      return IPWorks_MX_Set(m_pObj, 2, 0, (void*)lpszDNSServer, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_MX_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_MX_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_MX_Set(m_pObj, 4, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetMailServer() {
      void* val = IPWorks_MX_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetRequestId() {
      void* val = IPWorks_MX_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRequestId(int iRequestId) {
      void* val = (void*)IPW64CAST(iRequestId);
      return IPWorks_MX_Set(m_pObj, 6, 0, val, 0);
    }

    inline char* GetStatus() {
      void* val = IPWorks_MX_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetTimeout() {
      void* val = IPWorks_MX_Get(m_pObj, 8, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_MX_Set(m_pObj, 8, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_MX_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MX_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int Resolve(const char* lpszEmailAddress) {
      void *param[1+1] = {(void*)IPW64CAST(lpszEmailAddress), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_MX_Do(m_pObj, 6, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_MX_H_
