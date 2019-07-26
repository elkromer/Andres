/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_SYSLOG_H_
#define _IPWORKS_SYSLOG_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_SysLog_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SysLog_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_SysLog_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_StaticDestroy();

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
} SysLogErrorEventParams;

typedef struct {
  int FacilityCode;
  const char* Facility;
  int SeverityCode;
  const char* Severity;
  const char* Timestamp;
  const char* Hostname;
  const char* Message;
  int Conforms;
  const char* Packet;
  const char* SourceAddress;
  int SourcePort;
  int lenPacket;
  int reserved;
} SysLogPacketInEventParams;



class SysLog {
  
  public: //events
  
    virtual int FireError(SysLogErrorEventParams *e) {return 0;}
    virtual int FirePacketIn(SysLogPacketInEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL SysLogEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((SysLog*)lpObj)->SysLogEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            SysLogErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SysLog*)lpObj)->FireError(&e);
            break;
         }
         case 2: {
            SysLogPacketInEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), (int)IPW64CAST(param[7]), (char*)IPW64CAST(param[8]), (char*)IPW64CAST(param[9]), (int)IPW64CAST(param[10]), (int)IPW64CAST(cbparam[8]),  0};
            ret_code = ((SysLog*)lpObj)->FirePacketIn(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int SysLogEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    SysLog(char *lpOemKey = (char*)IPWORKS_OEMKEY_62) {
      m_pObj = IPWorks_SysLog_Create(SysLogEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~SysLog() {
      IPWorks_SysLog_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_SysLog_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_SysLog_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_SysLog_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_SysLog_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_SysLog_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetActive() {
      void* val = IPWorks_SysLog_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetActive(int bActive) {
      void* val = (void*)IPW64CAST(bActive);
      return IPWorks_SysLog_Set(m_pObj, 1, 0, val, 0);
    }
    inline char* GetLocalHost() {
      void* val = IPWorks_SysLog_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_SysLog_Set(m_pObj, 2, 0, (void*)lpLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_SysLog_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetLocalPort(int lLocalPort) {
      void* val = (void*)IPW64CAST(lLocalPort);
      return IPWorks_SysLog_Set(m_pObj, 3, 0, val, 0);
    }
    inline char* GetRemoteHost() {
      void* val = IPWorks_SysLog_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteHost(const char *lpRemoteHost) {
      return IPWorks_SysLog_Set(m_pObj, 4, 0, (void*)lpRemoteHost, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_SysLog_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetRemotePort(int lRemotePort) {
      void* val = (void*)IPW64CAST(lRemotePort);
      return IPWorks_SysLog_Set(m_pObj, 5, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SysLog_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SysLog_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SysLog_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int SendPacket(int iFacility, int iSeverity, const char* lpszMessage) {
      void *param[3+1] = {(void*)IPW64CAST(iFacility), (void*)IPW64CAST(iSeverity), (void*)IPW64CAST(lpszMessage), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_SysLog_Do(m_pObj, 5, 3, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} SysLogErrorEventParamsW;

typedef struct {
  int FacilityCode;
  LPWSTR Facility;
  int SeverityCode;
  LPWSTR Severity;
  LPWSTR Timestamp;
  LPWSTR Hostname;
  LPWSTR Message;
  int Conforms;
  LPWSTR Packet;
  LPWSTR SourceAddress;
  int SourcePort;
  int lenPacket;
  int reserved;
} SysLogPacketInEventParamsW;



class SysLogW : public SysLog {

  public: //properties
  


    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_SysLog_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_SysLog_Set(m_pObj, 10000+2, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetRemoteHost() {
      return (LPWSTR)IPWorks_SysLog_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetRemoteHost(LPCWSTR lpRemoteHost) {
      return IPWorks_SysLog_Set(m_pObj, 10000+4, 0, (void*)lpRemoteHost, 0);
    }





  public: //events
  
    virtual int FireError(SysLogErrorEventParamsW *e) {return 0;}
    virtual int FirePacketIn(SysLogPacketInEventParamsW *e) {return 0;}


  protected:
  
    virtual int SysLogEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            SysLogErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 2: {
            SysLogPacketInEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]), (LPWSTR)IPW64CAST(param[6]), (int)IPW64CAST(param[7]), (LPWSTR)IPW64CAST(param[8]), (LPWSTR)IPW64CAST(param[9]), (int)IPW64CAST(param[10]), (int)IPW64CAST(cbparam[8]),  0};
            ret_code = FirePacketIn(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireError(SysLogErrorEventParams *e) {return -10000;}
    virtual int FirePacketIn(SysLogPacketInEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SysLog_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SysLog_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SysLog_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int SendPacket(int iFacility, int iSeverity, LPWSTR lpszMessage) {
      void *param[3+1] = {(void*)iFacility, (void*)iSeverity, (void*)lpszMessage, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_SysLog_Do(m_pObj, 10000+5, 3, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_SYSLOG_H_




