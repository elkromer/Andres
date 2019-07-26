/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_UDPPORT_H_
#define _IPWORKS_UDPPORT_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_UDPPort_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_UDPPort_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_UDPPort_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_UDPPort_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_UDPPort_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_UDPPort_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_UDPPort_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_UDPPort_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_UDPPort_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_UDPPort_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  const char* Datagram;
  const char* SourceAddress;
  int SourcePort;
  int lenDatagram;
  int reserved;
} UDPPortDataInEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} UDPPortErrorEventParams;

typedef struct {
  int reserved;
} UDPPortReadyToSendEventParams;



class UDPPort {
  
  public: //events
  
    virtual int FireDataIn(UDPPortDataInEventParams *e) {return 0;}
    virtual int FireError(UDPPortErrorEventParams *e) {return 0;}
    virtual int FireReadyToSend(UDPPortReadyToSendEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL UDPPortEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((UDPPort*)lpObj)->UDPPortEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            UDPPortDataInEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((UDPPort*)lpObj)->FireDataIn(&e);
            break;
         }
         case 2: {
            UDPPortErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((UDPPort*)lpObj)->FireError(&e);
            break;
         }
         case 3: {
            UDPPortReadyToSendEventParams e = { 0};
            ret_code = ((UDPPort*)lpObj)->FireReadyToSend(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int UDPPortEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    UDPPort(char *lpOemKey = (char*)IPWORKS_OEMKEY_13) {
      m_pObj = IPWorks_UDPPort_Create(UDPPortEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~UDPPort() {
      IPWorks_UDPPort_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_UDPPort_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_UDPPort_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_UDPPort_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_UDPPort_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_UDPPort_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetAcceptData() {
      void* val = IPWorks_UDPPort_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAcceptData(int bAcceptData) {
      void* val = (void*)IPW64CAST(bAcceptData);
      return IPWorks_UDPPort_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetActive() {
      void* val = IPWorks_UDPPort_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }
    inline int SetActive(int bActive) {
      void* val = (void*)IPW64CAST(bActive);
      return IPWorks_UDPPort_Set(m_pObj, 2, 0, val, 0);
    }

    inline int SetDataToSend(const char *lpDataToSend, int lenDataToSend) {
      return IPWorks_UDPPort_Set(m_pObj, 3, 0, (void*)lpDataToSend, lenDataToSend);
    }

    inline int GetDontRoute() {
      void* val = IPWorks_UDPPort_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetDontRoute(int bDontRoute) {
      void* val = (void*)IPW64CAST(bDontRoute);
      return IPWorks_UDPPort_Set(m_pObj, 4, 0, val, 0);
    }
    inline char* GetLocalHost() {
      void* val = IPWorks_UDPPort_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_UDPPort_Set(m_pObj, 5, 0, (void*)lpLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_UDPPort_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetLocalPort(int lLocalPort) {
      void* val = (void*)IPW64CAST(lLocalPort);
      return IPWorks_UDPPort_Set(m_pObj, 6, 0, val, 0);
    }
    inline char* GetRemoteHost() {
      void* val = IPWorks_UDPPort_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteHost(const char *lpRemoteHost) {
      return IPWorks_UDPPort_Set(m_pObj, 7, 0, (void*)lpRemoteHost, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_UDPPort_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetRemotePort(int lRemotePort) {
      void* val = (void*)IPW64CAST(lRemotePort);
      return IPWorks_UDPPort_Set(m_pObj, 8, 0, val, 0);
    }
    inline int GetTimeToLive() {
      void* val = IPWorks_UDPPort_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeToLive(int iTimeToLive) {
      void* val = (void*)IPW64CAST(iTimeToLive);
      return IPWorks_UDPPort_Set(m_pObj, 9, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_UDPPort_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_UDPPort_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_UDPPort_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Send(const char* lpText, int lenText) {
      void *param[1+1] = {(void*)IPW64CAST(lpText), 0};
      int cbparam[1+1] = {lenText, 0};
      return IPWorks_UDPPort_Do(m_pObj, 5, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR Datagram;
  LPWSTR SourceAddress;
  int SourcePort;
  int lenDatagram;
  int reserved;
} UDPPortDataInEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} UDPPortErrorEventParamsW;

typedef struct {
  int reserved;
} UDPPortReadyToSendEventParamsW;



class UDPPortW : public UDPPort {

  public: //properties
  






    inline int SetDataToSend(LPCWSTR lpDataToSend) {
      return IPWorks_UDPPort_Set(m_pObj, 10000+3, 0, (void*)lpDataToSend, 0);
    }

    inline int SetDataToSendB(const char *lpDataToSend, int lenDataToSend) {
      return IPWorks_UDPPort_Set(m_pObj, 3, 0, (void*)lpDataToSend, lenDataToSend);
    }


    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_UDPPort_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_UDPPort_Set(m_pObj, 10000+5, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetRemoteHost() {
      return (LPWSTR)IPWorks_UDPPort_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetRemoteHost(LPCWSTR lpRemoteHost) {
      return IPWorks_UDPPort_Set(m_pObj, 10000+7, 0, (void*)lpRemoteHost, 0);
    }







  public: //events
  
    virtual int FireDataIn(UDPPortDataInEventParamsW *e) {return 0;}
    virtual int FireError(UDPPortErrorEventParamsW *e) {return 0;}
    virtual int FireReadyToSend(UDPPortReadyToSendEventParamsW *e) {return 0;}


  protected:
  
    virtual int UDPPortEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            UDPPortDataInEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireDataIn(&e);
            break;
         }
         case 2: {
            UDPPortErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 3: {
            UDPPortReadyToSendEventParamsW e = { 0};
            ret_code = FireReadyToSend(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireDataIn(UDPPortDataInEventParams *e) {return -10000;}
    virtual int FireError(UDPPortErrorEventParams *e) {return -10000;}
    virtual int FireReadyToSend(UDPPortReadyToSendEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_UDPPort_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_UDPPort_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_UDPPort_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Send(LPWSTR lpText, int lenText) {
      void *param[1+1] = {(void*)lpText, 0};
      int cbparam[1+1] = {lenText, 0};
      return IPWorks_UDPPort_Do(m_pObj, 10000+5, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_UDPPORT_H_




