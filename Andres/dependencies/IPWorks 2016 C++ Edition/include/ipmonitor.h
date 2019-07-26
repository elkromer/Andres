/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_IPMONITOR_H_
#define _IPWORKS_IPMONITOR_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_IPMonitor_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_IPMonitor_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_IPMonitor_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IPMonitor_StaticDestroy();

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
} IPMonitorErrorEventParams;

typedef struct {
  const char* IpAddress;
  int reserved;
} IPMonitorIPAddressEventParams;

typedef struct {
  const char* SourceAddress;
  int SourcePort;
  const char* DestinationAddress;
  int DestinationPort;
  int IPVersion;
  int TOS;
  int Id;
  int Flags;
  int Offset;
  int TTL;
  int Checksum;
  int IPProtocol;
  const char* Payload;
  int lenPayload;
  int reserved;
} IPMonitorIPPacketEventParams;



class IPMonitor {
  
  public: //events
  
    virtual int FireError(IPMonitorErrorEventParams *e) {return 0;}
    virtual int FireIPAddress(IPMonitorIPAddressEventParams *e) {return 0;}
    virtual int FireIPPacket(IPMonitorIPPacketEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL IPMonitorEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((IPMonitor*)lpObj)->IPMonitorEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            IPMonitorErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((IPMonitor*)lpObj)->FireError(&e);
            break;
         }
         case 2: {
            IPMonitorIPAddressEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((IPMonitor*)lpObj)->FireIPAddress(&e);
            break;
         }
         case 3: {
            IPMonitorIPPacketEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), (int)IPW64CAST(param[7]), (int)IPW64CAST(param[8]), (int)IPW64CAST(param[9]), (int)IPW64CAST(param[10]), (int)IPW64CAST(param[11]), (char*)IPW64CAST(param[12]), (int)IPW64CAST(cbparam[12]),  0};
            ret_code = ((IPMonitor*)lpObj)->FireIPPacket(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int IPMonitorEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    IPMonitor(char *lpOemKey = (char*)IPWORKS_OEMKEY_60) {
      m_pObj = IPWorks_IPMonitor_Create(IPMonitorEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~IPMonitor() {
      IPWorks_IPMonitor_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_IPMonitor_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_IPMonitor_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_IPMonitor_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_IPMonitor_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_IPMonitor_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetAcceptData() {
      void* val = IPWorks_IPMonitor_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAcceptData(int bAcceptData) {
      void* val = (void*)IPW64CAST(bAcceptData);
      return IPWorks_IPMonitor_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetActive() {
      void* val = IPWorks_IPMonitor_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }
    inline int SetActive(int bActive) {
      void* val = (void*)IPW64CAST(bActive);
      return IPWorks_IPMonitor_Set(m_pObj, 2, 0, val, 0);
    }
    inline int GetIPPacket(char *&lpIPPacket, int &lenIPPacket) {
      lpIPPacket = (char*)IPWorks_IPMonitor_Get(m_pObj, 3, 0, &lenIPPacket);
      return lpIPPacket ? 0 : lenIPPacket;
    }


    inline char* GetLocalHost() {
      void* val = IPWorks_IPMonitor_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_IPMonitor_Set(m_pObj, 4, 0, (void*)lpLocalHost, 0);
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPMonitor_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPMonitor_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int ListIPAddresses() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPMonitor_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int ParsePcapFile(const char* lpszfileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszfileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPMonitor_Do(m_pObj, 5, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPMonitor_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} IPMonitorErrorEventParamsW;

typedef struct {
  LPWSTR IpAddress;
  int reserved;
} IPMonitorIPAddressEventParamsW;

typedef struct {
  LPWSTR SourceAddress;
  int SourcePort;
  LPWSTR DestinationAddress;
  int DestinationPort;
  int IPVersion;
  int TOS;
  int Id;
  int Flags;
  int Offset;
  int TTL;
  int Checksum;
  int IPProtocol;
  LPWSTR Payload;
  int lenPayload;
  int reserved;
} IPMonitorIPPacketEventParamsW;



class IPMonitorW : public IPMonitor {

  public: //properties
  




    inline LPWSTR GetIPPacket() {
      return (LPWSTR)IPWorks_IPMonitor_Get(m_pObj, 10000+3, 0, 0);
    }


    inline int GetIPPacketB(char *&lpIPPacket, int &lenIPPacket) {
      lpIPPacket = (char*)IPWorks_IPMonitor_Get(m_pObj, 3, 0, &lenIPPacket);
      return lpIPPacket ? 0 : lenIPPacket;
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_IPMonitor_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_IPMonitor_Set(m_pObj, 10000+4, 0, (void*)lpLocalHost, 0);
    }



  public: //events
  
    virtual int FireError(IPMonitorErrorEventParamsW *e) {return 0;}
    virtual int FireIPAddress(IPMonitorIPAddressEventParamsW *e) {return 0;}
    virtual int FireIPPacket(IPMonitorIPPacketEventParamsW *e) {return 0;}


  protected:
  
    virtual int IPMonitorEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            IPMonitorErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 2: {
            IPMonitorIPAddressEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireIPAddress(&e);
            break;
         }
         case 3: {
            IPMonitorIPPacketEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), (int)IPW64CAST(param[7]), (int)IPW64CAST(param[8]), (int)IPW64CAST(param[9]), (int)IPW64CAST(param[10]), (int)IPW64CAST(param[11]), (LPWSTR)IPW64CAST(param[12]), (int)IPW64CAST(cbparam[12]),  0};
            ret_code = FireIPPacket(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireError(IPMonitorErrorEventParams *e) {return -10000;}
    virtual int FireIPAddress(IPMonitorIPAddressEventParams *e) {return -10000;}
    virtual int FireIPPacket(IPMonitorIPPacketEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPMonitor_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPMonitor_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int ListIPAddresses() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPMonitor_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int ParsePcapFile(LPWSTR lpszfileName) {
      void *param[1+1] = {(void*)lpszfileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPMonitor_Do(m_pObj, 10000+5, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPMonitor_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_IPMONITOR_H_




