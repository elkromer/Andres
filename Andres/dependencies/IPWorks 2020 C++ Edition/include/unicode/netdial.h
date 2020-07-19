/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_NETDIAL_H_
#define _IPWORKS_NETDIAL_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_NetDial_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NetDial_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_NetDial_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_NetDial_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_NetDial_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT Handle;
  LPCWSTR Entry;
  LPCWSTR DeviceName;
  LPCWSTR DeviceType;
  LPCWSTR StatusDescription;
  INT reserved;
} NetDialConnectedEntryEventParams;

typedef struct {
  LPCWSTR DeviceName;
  LPCWSTR DeviceType;
  INT reserved;
} NetDialDeviceEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} NetDialErrorEventParams;

typedef struct {
  LPCWSTR Entry;
  INT reserved;
} NetDialPhonebookEntryEventParams;

typedef struct {
  INT Operation;
  INT StatusCode;
  LPCWSTR OperationDescription;
  LPCWSTR StatusDescription;
  INT reserved;
} NetDialStatusEventParams;


class NetDial {
  public: // Events
    virtual INT FireConnectedEntry(NetDialConnectedEntryEventParams *e) {return 0;}
    virtual INT FireDevice(NetDialDeviceEventParams *e) {return 0;}
    virtual INT FireError(NetDialErrorEventParams *e) {return 0;}
    virtual INT FirePhonebookEntry(NetDialPhonebookEntryEventParams *e) {return 0;}
    virtual INT FireStatus(NetDialStatusEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL NetDialEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          NetDialConnectedEntryEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], 0};
          ret_code = ((NetDial*)lpObj)->FireConnectedEntry(&e);
          break;
        }
        case 2: {
          NetDialDeviceEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((NetDial*)lpObj)->FireDevice(&e);
          break;
        }
        case 3: {
          NetDialErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((NetDial*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          NetDialPhonebookEntryEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((NetDial*)lpObj)->FirePhonebookEntry(&e);
          break;
        }
        case 5: {
          NetDialStatusEventParams e = {(INT)param[0], (INT)param[1], (LPWSTR)param[2], (LPWSTR)param[3], 0};
          ret_code = ((NetDial*)lpObj)->FireStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    NetDial(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_27) {
      m_pObj = IPWorks_NetDial_Create(NetDialEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~NetDial() {
      IPWorks_NetDial_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_NetDial_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_NetDial_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_NetDial_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_NetDial_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_NetDial_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetCallbackNumber() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCallbackNumber(LPCWSTR lpszCallbackNumber) {
      return IPWorks_NetDial_Set(m_pObj, 1+10000, 0, (LPVOID)lpszCallbackNumber, 0);
    }

    inline LPWSTR GetDomain() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDomain(LPCWSTR lpszDomain) {
      return IPWorks_NetDial_Set(m_pObj, 2+10000, 0, (LPVOID)lpszDomain, 0);
    }

    inline LPWSTR GetEntryDeviceName() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryDeviceName(LPCWSTR lpszEntryDeviceName) {
      return IPWorks_NetDial_Set(m_pObj, 3+10000, 0, (LPVOID)lpszEntryDeviceName, 0);
    }

    inline LPWSTR GetEntryDeviceType() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryDeviceType(LPCWSTR lpszEntryDeviceType) {
      return IPWorks_NetDial_Set(m_pObj, 4+10000, 0, (LPVOID)lpszEntryDeviceType, 0);
    }

    inline LPWSTR GetEntryDNSServer() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryDNSServer(LPCWSTR lpszEntryDNSServer) {
      return IPWorks_NetDial_Set(m_pObj, 5+10000, 0, (LPVOID)lpszEntryDNSServer, 0);
    }

    inline LPWSTR GetEntryIPAddress() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryIPAddress(LPCWSTR lpszEntryIPAddress) {
      return IPWorks_NetDial_Set(m_pObj, 6+10000, 0, (LPVOID)lpszEntryIPAddress, 0);
    }

    inline LPWSTR GetEntryPhoneNumber() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryPhoneNumber(LPCWSTR lpszEntryPhoneNumber) {
      return IPWorks_NetDial_Set(m_pObj, 7+10000, 0, (LPVOID)lpszEntryPhoneNumber, 0);
    }

    inline LPWSTR GetEntryWINSServer() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryWINSServer(LPCWSTR lpszEntryWINSServer) {
      return IPWorks_NetDial_Set(m_pObj, 8+10000, 0, (LPVOID)lpszEntryWINSServer, 0);
    }

    inline INT GetHandle() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 9, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetHandle(INT iHandle) {
      LPVOID val = (LPVOID)(iHandle);
      return IPWorks_NetDial_Set(m_pObj, 9, 0, val, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 10, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_NetDial_Set(m_pObj, 11+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline LPWSTR GetPhonebook() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPhonebook(LPCWSTR lpszPhonebook) {
      return IPWorks_NetDial_Set(m_pObj, 12+10000, 0, (LPVOID)lpszPhonebook, 0);
    }

    inline LPWSTR GetPhonebookEntry() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPhonebookEntry(LPCWSTR lpszPhonebookEntry) {
      return IPWorks_NetDial_Set(m_pObj, 13+10000, 0, (LPVOID)lpszPhonebookEntry, 0);
    }

    inline LPWSTR GetPhoneNumber() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPhoneNumber(LPCWSTR lpszPhoneNumber) {
      return IPWorks_NetDial_Set(m_pObj, 14+10000, 0, (LPVOID)lpszPhoneNumber, 0);
    }

    inline BOOL GetRASAvailable() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 15, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 16, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_NetDial_Set(m_pObj, 16, 0, val, 0);
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_NetDial_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_NetDial_Set(m_pObj, 17+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_NetDial_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Connect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT CreateEntry() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT DeleteEntry() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT ListConnections() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT ListDevices() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT ListPhonebook() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 11+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
    }

    inline INT ShowDialDialog() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NetDial_Do(m_pObj, 13+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_NETDIAL_H_
