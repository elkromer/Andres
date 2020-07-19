/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#if !defined(WIN32) || defined(UNIX)
// The NetDial component is only available on Windows.
#define _IPWORKS_NETDIAL_H_
#endif // !WIN32 || UNIX

#ifndef _IPWORKS_NETDIAL_H_
#define _IPWORKS_NETDIAL_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_NetDial_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NetDial_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_NetDial_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_NetDial_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_SetEventErrorAndCode(void *lpObj, int code, char *message);
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
  const char *Entry;
  const char *DeviceName;
  const char *DeviceType;
  const char *StatusDescription;
  int reserved;
} NetDialConnectedEntryEventParams;

typedef struct {
  const char *DeviceName;
  const char *DeviceType;
  int reserved;
} NetDialDeviceEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} NetDialErrorEventParams;

typedef struct {
  const char *Entry;
  int reserved;
} NetDialPhonebookEntryEventParams;

typedef struct {
  int Operation;
  int StatusCode;
  const char *OperationDescription;
  const char *StatusDescription;
  int reserved;
} NetDialStatusEventParams;


class NetDial {
  public: // Events
    virtual int FireConnectedEntry(NetDialConnectedEntryEventParams *e) {return 0;}
    virtual int FireDevice(NetDialDeviceEventParams *e) {return 0;}
    virtual int FireError(NetDialErrorEventParams *e) {return 0;}
    virtual int FirePhonebookEntry(NetDialPhonebookEntryEventParams *e) {return 0;}
    virtual int FireStatus(NetDialStatusEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL NetDialEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          NetDialConnectedEntryEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), 0};
          ret_code = ((NetDial*)lpObj)->FireConnectedEntry(&e);
          break;
        }
        case 2: {
          NetDialDeviceEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((NetDial*)lpObj)->FireDevice(&e);
          break;
        }
        case 3: {
          NetDialErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((NetDial*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          NetDialPhonebookEntryEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((NetDial*)lpObj)->FirePhonebookEntry(&e);
          break;
        }
        case 5: {
          NetDialStatusEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), 0};
          ret_code = ((NetDial*)lpObj)->FireStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    NetDial(char *lpOemKey = (char*)IPWORKS_OEMKEY_27) {
      m_pObj = IPWorks_NetDial_Create(NetDialEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~NetDial() {
      IPWorks_NetDial_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_NetDial_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_NetDial_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_NetDial_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_NetDial_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_NetDial_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetCallbackNumber() {
      void* val = IPWorks_NetDial_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCallbackNumber(const char* lpszCallbackNumber) {
      return IPWorks_NetDial_Set(m_pObj, 1, 0, (void*)lpszCallbackNumber, 0);
    }

    inline char* GetDomain() {
      void* val = IPWorks_NetDial_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetDomain(const char* lpszDomain) {
      return IPWorks_NetDial_Set(m_pObj, 2, 0, (void*)lpszDomain, 0);
    }

    inline char* GetEntryDeviceName() {
      void* val = IPWorks_NetDial_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryDeviceName(const char* lpszEntryDeviceName) {
      return IPWorks_NetDial_Set(m_pObj, 3, 0, (void*)lpszEntryDeviceName, 0);
    }

    inline char* GetEntryDeviceType() {
      void* val = IPWorks_NetDial_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryDeviceType(const char* lpszEntryDeviceType) {
      return IPWorks_NetDial_Set(m_pObj, 4, 0, (void*)lpszEntryDeviceType, 0);
    }

    inline char* GetEntryDNSServer() {
      void* val = IPWorks_NetDial_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryDNSServer(const char* lpszEntryDNSServer) {
      return IPWorks_NetDial_Set(m_pObj, 5, 0, (void*)lpszEntryDNSServer, 0);
    }

    inline char* GetEntryIPAddress() {
      void* val = IPWorks_NetDial_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryIPAddress(const char* lpszEntryIPAddress) {
      return IPWorks_NetDial_Set(m_pObj, 6, 0, (void*)lpszEntryIPAddress, 0);
    }

    inline char* GetEntryPhoneNumber() {
      void* val = IPWorks_NetDial_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryPhoneNumber(const char* lpszEntryPhoneNumber) {
      return IPWorks_NetDial_Set(m_pObj, 7, 0, (void*)lpszEntryPhoneNumber, 0);
    }

    inline char* GetEntryWINSServer() {
      void* val = IPWorks_NetDial_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryWINSServer(const char* lpszEntryWINSServer) {
      return IPWorks_NetDial_Set(m_pObj, 8, 0, (void*)lpszEntryWINSServer, 0);
    }

    inline int GetHandle() {
      void* val = IPWorks_NetDial_Get(m_pObj, 9, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetHandle(int iHandle) {
      void* val = (void*)IPW64CAST(iHandle);
      return IPWorks_NetDial_Set(m_pObj, 9, 0, val, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_NetDial_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_NetDial_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_NetDial_Set(m_pObj, 11, 0, (void*)lpszPassword, 0);
    }

    inline char* GetPhonebook() {
      void* val = IPWorks_NetDial_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPhonebook(const char* lpszPhonebook) {
      return IPWorks_NetDial_Set(m_pObj, 12, 0, (void*)lpszPhonebook, 0);
    }

    inline char* GetPhonebookEntry() {
      void* val = IPWorks_NetDial_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPhonebookEntry(const char* lpszPhonebookEntry) {
      return IPWorks_NetDial_Set(m_pObj, 13, 0, (void*)lpszPhonebookEntry, 0);
    }

    inline char* GetPhoneNumber() {
      void* val = IPWorks_NetDial_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPhoneNumber(const char* lpszPhoneNumber) {
      return IPWorks_NetDial_Set(m_pObj, 14, 0, (void*)lpszPhoneNumber, 0);
    }

    inline int GetRASAvailable() {
      void* val = IPWorks_NetDial_Get(m_pObj, 15, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetTimeout() {
      void* val = IPWorks_NetDial_Get(m_pObj, 16, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_NetDial_Set(m_pObj, 16, 0, val, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_NetDial_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_NetDial_Set(m_pObj, 17, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NetDial_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int CreateEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int DeleteEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline int ListConnections() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int ListDevices() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int ListPhonebook() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 11, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 12, 0, param, cbparam, NULL);
    }

    inline int ShowDialDialog() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 13, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_NETDIAL_H_
