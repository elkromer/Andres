/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_NETDIAL_H_
#define _IPWORKS_NETDIAL_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_NetDial_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NetDial_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_NetDial_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int Handle;
  const char* Entry;
  const char* DeviceName;
  const char* DeviceType;
  const char* StatusDescription;
  int reserved;
} NetDialConnectedEntryEventParams;

typedef struct {
  const char* DeviceName;
  const char* DeviceType;
  int reserved;
} NetDialDeviceEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} NetDialErrorEventParams;

typedef struct {
  const char* Entry;
  int reserved;
} NetDialPhonebookEntryEventParams;

typedef struct {
  int Operation;
  int StatusCode;
  const char* OperationDescription;
  const char* StatusDescription;
  int reserved;
} NetDialStatusEventParams;



class NetDial {
  
  public: //events
  
    virtual int FireConnectedEntry(NetDialConnectedEntryEventParams *e) {return 0;}
    virtual int FireDevice(NetDialDeviceEventParams *e) {return 0;}
    virtual int FireError(NetDialErrorEventParams *e) {return 0;}
    virtual int FirePhonebookEntry(NetDialPhonebookEntryEventParams *e) {return 0;}
    virtual int FireStatus(NetDialStatusEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL NetDialEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((NetDial*)lpObj)->NetDialEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            NetDialConnectedEntryEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]),  0};
            ret_code = ((NetDial*)lpObj)->FireConnectedEntry(&e);
            break;
         }
         case 2: {
            NetDialDeviceEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((NetDial*)lpObj)->FireDevice(&e);
            break;
         }
         case 3: {
            NetDialErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((NetDial*)lpObj)->FireError(&e);
            break;
         }
         case 4: {
            NetDialPhonebookEntryEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((NetDial*)lpObj)->FirePhonebookEntry(&e);
            break;
         }
         case 5: {
            NetDialStatusEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]),  0};
            ret_code = ((NetDial*)lpObj)->FireStatus(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int NetDialEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    NetDial(char *lpOemKey = (char*)IPWORKS_OEMKEY_27) {
      m_pObj = IPWorks_NetDial_Create(NetDialEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~NetDial() {
      IPWorks_NetDial_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_NetDial_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_NetDial_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_NetDial_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_NetDial_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_NetDial_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetCallbackNumber() {
      void* val = IPWorks_NetDial_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetCallbackNumber(const char *lpCallbackNumber) {
      return IPWorks_NetDial_Set(m_pObj, 1, 0, (void*)lpCallbackNumber, 0);
    }

    inline char* GetDomain() {
      void* val = IPWorks_NetDial_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetDomain(const char *lpDomain) {
      return IPWorks_NetDial_Set(m_pObj, 2, 0, (void*)lpDomain, 0);
    }

    inline char* GetEntryDeviceName() {
      void* val = IPWorks_NetDial_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetEntryDeviceName(const char *lpEntryDeviceName) {
      return IPWorks_NetDial_Set(m_pObj, 3, 0, (void*)lpEntryDeviceName, 0);
    }

    inline char* GetEntryDeviceType() {
      void* val = IPWorks_NetDial_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetEntryDeviceType(const char *lpEntryDeviceType) {
      return IPWorks_NetDial_Set(m_pObj, 4, 0, (void*)lpEntryDeviceType, 0);
    }

    inline char* GetEntryDNSServer() {
      void* val = IPWorks_NetDial_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetEntryDNSServer(const char *lpEntryDNSServer) {
      return IPWorks_NetDial_Set(m_pObj, 5, 0, (void*)lpEntryDNSServer, 0);
    }

    inline char* GetEntryIPAddress() {
      void* val = IPWorks_NetDial_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetEntryIPAddress(const char *lpEntryIPAddress) {
      return IPWorks_NetDial_Set(m_pObj, 6, 0, (void*)lpEntryIPAddress, 0);
    }

    inline char* GetEntryPhoneNumber() {
      void* val = IPWorks_NetDial_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetEntryPhoneNumber(const char *lpEntryPhoneNumber) {
      return IPWorks_NetDial_Set(m_pObj, 7, 0, (void*)lpEntryPhoneNumber, 0);
    }

    inline char* GetEntryWINSServer() {
      void* val = IPWorks_NetDial_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetEntryWINSServer(const char *lpEntryWINSServer) {
      return IPWorks_NetDial_Set(m_pObj, 8, 0, (void*)lpEntryWINSServer, 0);
    }

    inline int GetHandle() {
      void* val = IPWorks_NetDial_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetHandle(int lHandle) {
      void* val = (void*)IPW64CAST(lHandle);
      return IPWorks_NetDial_Set(m_pObj, 9, 0, val, 0);
    }
    inline int GetIdle() {
      void* val = IPWorks_NetDial_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_NetDial_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_NetDial_Set(m_pObj, 11, 0, (void*)lpPassword, 0);
    }

    inline char* GetPhonebook() {
      void* val = IPWorks_NetDial_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetPhonebook(const char *lpPhonebook) {
      return IPWorks_NetDial_Set(m_pObj, 12, 0, (void*)lpPhonebook, 0);
    }

    inline char* GetPhonebookEntry() {
      void* val = IPWorks_NetDial_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetPhonebookEntry(const char *lpPhonebookEntry) {
      return IPWorks_NetDial_Set(m_pObj, 13, 0, (void*)lpPhonebookEntry, 0);
    }

    inline char* GetPhoneNumber() {
      void* val = IPWorks_NetDial_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetPhoneNumber(const char *lpPhoneNumber) {
      return IPWorks_NetDial_Set(m_pObj, 14, 0, (void*)lpPhoneNumber, 0);
    }

    inline int GetRASAvailable() {
      void* val = IPWorks_NetDial_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }

    inline int GetTimeout() {
      void* val = IPWorks_NetDial_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_NetDial_Set(m_pObj, 16, 0, val, 0);
    }
    inline char* GetUser() {
      void* val = IPWorks_NetDial_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_NetDial_Set(m_pObj, 17, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NetDial_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int CreateEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int DeleteEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int ListConnections() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int ListDevices() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int ListPhonebook() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }
    inline int ShowDialDialog() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 13, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int Handle;
  LPWSTR Entry;
  LPWSTR DeviceName;
  LPWSTR DeviceType;
  LPWSTR StatusDescription;
  int reserved;
} NetDialConnectedEntryEventParamsW;

typedef struct {
  LPWSTR DeviceName;
  LPWSTR DeviceType;
  int reserved;
} NetDialDeviceEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} NetDialErrorEventParamsW;

typedef struct {
  LPWSTR Entry;
  int reserved;
} NetDialPhonebookEntryEventParamsW;

typedef struct {
  int Operation;
  int StatusCode;
  LPWSTR OperationDescription;
  LPWSTR StatusDescription;
  int reserved;
} NetDialStatusEventParamsW;



class NetDialW : public NetDial {

  public: //properties
  
    inline LPWSTR GetCallbackNumber() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetCallbackNumber(LPCWSTR lpCallbackNumber) {
      return IPWorks_NetDial_Set(m_pObj, 10000+1, 0, (void*)lpCallbackNumber, 0);
    }

    inline LPWSTR GetDomain() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetDomain(LPCWSTR lpDomain) {
      return IPWorks_NetDial_Set(m_pObj, 10000+2, 0, (void*)lpDomain, 0);
    }

    inline LPWSTR GetEntryDeviceName() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetEntryDeviceName(LPCWSTR lpEntryDeviceName) {
      return IPWorks_NetDial_Set(m_pObj, 10000+3, 0, (void*)lpEntryDeviceName, 0);
    }

    inline LPWSTR GetEntryDeviceType() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetEntryDeviceType(LPCWSTR lpEntryDeviceType) {
      return IPWorks_NetDial_Set(m_pObj, 10000+4, 0, (void*)lpEntryDeviceType, 0);
    }

    inline LPWSTR GetEntryDNSServer() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetEntryDNSServer(LPCWSTR lpEntryDNSServer) {
      return IPWorks_NetDial_Set(m_pObj, 10000+5, 0, (void*)lpEntryDNSServer, 0);
    }

    inline LPWSTR GetEntryIPAddress() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetEntryIPAddress(LPCWSTR lpEntryIPAddress) {
      return IPWorks_NetDial_Set(m_pObj, 10000+6, 0, (void*)lpEntryIPAddress, 0);
    }

    inline LPWSTR GetEntryPhoneNumber() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetEntryPhoneNumber(LPCWSTR lpEntryPhoneNumber) {
      return IPWorks_NetDial_Set(m_pObj, 10000+7, 0, (void*)lpEntryPhoneNumber, 0);
    }

    inline LPWSTR GetEntryWINSServer() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetEntryWINSServer(LPCWSTR lpEntryWINSServer) {
      return IPWorks_NetDial_Set(m_pObj, 10000+8, 0, (void*)lpEntryWINSServer, 0);
    }





    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_NetDial_Set(m_pObj, 10000+11, 0, (void*)lpPassword, 0);
    }

    inline LPWSTR GetPhonebook() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetPhonebook(LPCWSTR lpPhonebook) {
      return IPWorks_NetDial_Set(m_pObj, 10000+12, 0, (void*)lpPhonebook, 0);
    }

    inline LPWSTR GetPhonebookEntry() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetPhonebookEntry(LPCWSTR lpPhonebookEntry) {
      return IPWorks_NetDial_Set(m_pObj, 10000+13, 0, (void*)lpPhonebookEntry, 0);
    }

    inline LPWSTR GetPhoneNumber() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetPhoneNumber(LPCWSTR lpPhoneNumber) {
      return IPWorks_NetDial_Set(m_pObj, 10000+14, 0, (void*)lpPhoneNumber, 0);
    }





    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_NetDial_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_NetDial_Set(m_pObj, 10000+17, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnectedEntry(NetDialConnectedEntryEventParamsW *e) {return 0;}
    virtual int FireDevice(NetDialDeviceEventParamsW *e) {return 0;}
    virtual int FireError(NetDialErrorEventParamsW *e) {return 0;}
    virtual int FirePhonebookEntry(NetDialPhonebookEntryEventParamsW *e) {return 0;}
    virtual int FireStatus(NetDialStatusEventParamsW *e) {return 0;}


  protected:
  
    virtual int NetDialEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            NetDialConnectedEntryEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]),  0};
            ret_code = FireConnectedEntry(&e);
            break;
         }
         case 2: {
            NetDialDeviceEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDevice(&e);
            break;
         }
         case 3: {
            NetDialErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 4: {
            NetDialPhonebookEntryEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FirePhonebookEntry(&e);
            break;
         }
         case 5: {
            NetDialStatusEventParamsW e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]),  0};
            ret_code = FireStatus(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnectedEntry(NetDialConnectedEntryEventParams *e) {return -10000;}
    virtual int FireDevice(NetDialDeviceEventParams *e) {return -10000;}
    virtual int FireError(NetDialErrorEventParams *e) {return -10000;}
    virtual int FirePhonebookEntry(NetDialPhonebookEntryEventParams *e) {return -10000;}
    virtual int FireStatus(NetDialStatusEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NetDial_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int CreateEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int DeleteEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int ListConnections() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int ListDevices() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int ListPhonebook() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }
    inline int ShowDialDialog() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10000+13, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_NETDIAL_H_




