/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_MCAST_H_
#define _IPWORKS_MCAST_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_MCast_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_MCast_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MCast_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_MCast_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_MCast_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_MCast_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_MCast_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MCast_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MCast_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_MCast_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MCast_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MCast_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_MCast_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_MCast_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  const char *Datagram;
  int lenDatagram;
  const char *SourceAddress;
  int SourcePort;
  int reserved;
} MCastDataInEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} MCastErrorEventParams;

typedef struct {
  int reserved;
} MCastReadyToSendEventParams;


class MCast {
  public: // Events
    virtual int FireDataIn(MCastDataInEventParams *e) {return 0;}
    virtual int FireError(MCastErrorEventParams *e) {return 0;}
    virtual int FireReadyToSend(MCastReadyToSendEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL MCastEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          MCastDataInEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), 0};
          ret_code = ((MCast*)lpObj)->FireDataIn(&e);
          break;
        }
        case 2: {
          MCastErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((MCast*)lpObj)->FireError(&e);
          break;
        }
        case 3: {
          MCastReadyToSendEventParams e = {0};
          ret_code = ((MCast*)lpObj)->FireReadyToSend(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    MCast(char *lpOemKey = (char*)IPWORKS_OEMKEY_26) {
      m_pObj = IPWorks_MCast_Create(MCastEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~MCast() {
      IPWorks_MCast_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_MCast_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_MCast_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_MCast_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_MCast_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_MCast_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetAcceptData() {
      void* val = IPWorks_MCast_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAcceptData(int bAcceptData) {
      void* val = (void*)IPW64CAST(bAcceptData);
      return IPWorks_MCast_Set(m_pObj, 1, 0, val, 0);
    }

    inline int GetActive() {
      void* val = IPWorks_MCast_Get(m_pObj, 2, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetActive(int bActive) {
      void* val = (void*)IPW64CAST(bActive);
      return IPWorks_MCast_Set(m_pObj, 2, 0, val, 0);
    }

    inline int SetDataToSend(const char* lpDataToSend, int lenDataToSend) {
      return IPWorks_MCast_Set(m_pObj, 3, 0, (void*)lpDataToSend, lenDataToSend);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_MCast_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_MCast_Set(m_pObj, 4, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_MCast_Get(m_pObj, 5, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetLocalPort(int iLocalPort) {
      void* val = (void*)IPW64CAST(iLocalPort);
      return IPWorks_MCast_Set(m_pObj, 5, 0, val, 0);
    }

    inline int GetLoopback() {
      void* val = IPWorks_MCast_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetLoopback(int bLoopback) {
      void* val = (void*)IPW64CAST(bLoopback);
      return IPWorks_MCast_Set(m_pObj, 6, 0, val, 0);
    }

    inline char* GetMulticastGroup() {
      void* val = IPWorks_MCast_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMulticastGroup(const char* lpszMulticastGroup) {
      return IPWorks_MCast_Set(m_pObj, 7, 0, (void*)lpszMulticastGroup, 0);
    }

    inline char* GetReceiveInterface() {
      void* val = IPWorks_MCast_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReceiveInterface(const char* lpszReceiveInterface) {
      return IPWorks_MCast_Set(m_pObj, 8, 0, (void*)lpszReceiveInterface, 0);
    }

    inline char* GetRemoteHost() {
      void* val = IPWorks_MCast_Get(m_pObj, 9, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemoteHost(const char* lpszRemoteHost) {
      return IPWorks_MCast_Set(m_pObj, 9, 0, (void*)lpszRemoteHost, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_MCast_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRemotePort(int iRemotePort) {
      void* val = (void*)IPW64CAST(iRemotePort);
      return IPWorks_MCast_Set(m_pObj, 10, 0, val, 0);
    }

    inline char* GetSendInterface() {
      void* val = IPWorks_MCast_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSendInterface(const char* lpszSendInterface) {
      return IPWorks_MCast_Set(m_pObj, 11, 0, (void*)lpszSendInterface, 0);
    }

    inline int GetTimeToLive() {
      void* val = IPWorks_MCast_Get(m_pObj, 12, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeToLive(int iTimeToLive) {
      void* val = (void*)IPW64CAST(iTimeToLive);
      return IPWorks_MCast_Set(m_pObj, 12, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_MCast_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MCast_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MCast_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Send(const char* lpText, int lenText) {
      void *param[1+1] = {(void*)IPW64CAST(lpText), 0};
      int cbparam[1+1] = {lenText, 0};
      return IPWorks_MCast_Do(m_pObj, 5, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_MCAST_H_
