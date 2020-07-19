/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_SYSLOG_H_
#define _IPWORKS_SYSLOG_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//CertStoreTypes
#define CST_USER                                           0
#define CST_MACHINE                                        1
#define CST_PFXFILE                                        2
#define CST_PFXBLOB                                        3
#define CST_JKSFILE                                        4
#define CST_JKSBLOB                                        5
#define CST_PEMKEY_FILE                                    6
#define CST_PEMKEY_BLOB                                    7
#define CST_PUBLIC_KEY_FILE                                8
#define CST_PUBLIC_KEY_BLOB                                9
#define CST_SSHPUBLIC_KEY_BLOB                             10
#define CST_P7BFILE                                        11
#define CST_P7BBLOB                                        12
#define CST_SSHPUBLIC_KEY_FILE                             13
#define CST_PPKFILE                                        14
#define CST_PPKBLOB                                        15
#define CST_XMLFILE                                        16
#define CST_XMLBLOB                                        17
#define CST_JWKFILE                                        18
#define CST_JWKBLOB                                        19
#define CST_SECURITY_KEY                                   20
#define CST_AUTO                                           99


extern "C" void* IPWORKS_CALL IPWorks_SysLog_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SysLog_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_SysLog_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_SysLog_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR RemoteAddress;
  INT RemotePort;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SysLogConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SysLogConnectionStatusEventParams;

typedef struct {
  LPCWSTR RemoteAddress;
  INT RemotePort;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SysLogDisconnectedEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} SysLogErrorEventParams;

typedef struct {
  INT FacilityCode;
  LPCWSTR Facility;
  INT SeverityCode;
  LPCWSTR Severity;
  LPCWSTR Timestamp;
  LPCWSTR Hostname;
  LPCWSTR Message;
  BOOL Conforms;
  LPCSTR Packet;
  INT lenPacket;
  LPCWSTR SourceAddress;
  INT SourcePort;
  INT reserved;
} SysLogPacketInEventParams;

typedef struct {
  LPCWSTR RemoteAddress;
  INT RemotePort;
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} SysLogSSLClientAuthenticationEventParams;

typedef struct {
  LPCWSTR RemoteAddress;
  INT RemotePort;
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} SysLogSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR RemoteAddress;
  INT RemotePort;
  LPCWSTR Message;
  INT reserved;
} SysLogSSLStatusEventParams;


class SysLog {
  public: // Events
    virtual INT FireConnected(SysLogConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(SysLogConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(SysLogDisconnectedEventParams *e) {return 0;}
    virtual INT FireError(SysLogErrorEventParams *e) {return 0;}
    virtual INT FirePacketIn(SysLogPacketInEventParams *e) {return 0;}
    virtual INT FireSSLClientAuthentication(SysLogSSLClientAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(SysLogSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(SysLogSSLStatusEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL SysLogEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          SysLogConnectedEventParams e = {(LPWSTR)param[0], (INT)param[1], (INT)param[2], (LPWSTR)param[3], 0};
          ret_code = ((SysLog*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          SysLogConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((SysLog*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          SysLogDisconnectedEventParams e = {(LPWSTR)param[0], (INT)param[1], (INT)param[2], (LPWSTR)param[3], 0};
          ret_code = ((SysLog*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          SysLogErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((SysLog*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          SysLogPacketInEventParams e = {(INT)param[0], (LPWSTR)param[1], (INT)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (LPWSTR)param[5], (LPWSTR)param[6], (BOOL)param[7], (LPSTR)param[8], (INT)cbparam[8], (LPWSTR)param[9], (INT)param[10], 0};
          ret_code = ((SysLog*)lpObj)->FirePacketIn(&e);
          break;
        }
        case 6: {
          SysLogSSLClientAuthenticationEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPSTR)param[2], (INT)cbparam[2], (LPWSTR)param[3], (LPWSTR)param[4], (LPWSTR)param[5], (BOOL)param[6], 0};
          ret_code = ((SysLog*)lpObj)->FireSSLClientAuthentication(&e);
          param[6] = (LPVOID)e.Accept;
          break;
        }
        case 7: {
          SysLogSSLServerAuthenticationEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPSTR)param[2], (INT)cbparam[2], (LPWSTR)param[3], (LPWSTR)param[4], (LPWSTR)param[5], (BOOL)param[6], 0};
          ret_code = ((SysLog*)lpObj)->FireSSLServerAuthentication(&e);
          param[6] = (LPVOID)e.Accept;
          break;
        }
        case 8: {
          SysLogSSLStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((SysLog*)lpObj)->FireSSLStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    SysLog(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_62) {
      m_pObj = IPWorks_SysLog_Create(SysLogEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~SysLog() {
      IPWorks_SysLog_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_SysLog_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_SysLog_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_SysLog_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_SysLog_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_SysLog_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetActive() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetActive(BOOL bActive) {
      LPVOID val = (LPVOID)(bActive);
      return IPWorks_SysLog_Set(m_pObj, 1, 0, val, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_SysLog_Set(m_pObj, 2+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetLocalPort() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 3, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLocalPort(INT iLocalPort) {
      LPVOID val = (LPVOID)(iLocalPort);
      return IPWorks_SysLog_Set(m_pObj, 3, 0, val, 0);
    }

    inline LPWSTR GetRemoteHost() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteHost(LPCWSTR lpszRemoteHost) {
      return IPWorks_SysLog_Set(m_pObj, 4+10000, 0, (LPVOID)lpszRemoteHost, 0);
    }

    inline INT GetRemotePort() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 5, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRemotePort(INT iRemotePort) {
      LPVOID val = (LPVOID)(iRemotePort);
      return IPWorks_SysLog_Set(m_pObj, 5, 0, val, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_SysLog_Get(m_pObj, 6, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_SysLog_Set(m_pObj, 6, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline BOOL GetSSLAuthenticateClients() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 7, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLAuthenticateClients(BOOL bSSLAuthenticateClients) {
      LPVOID val = (LPVOID)(bSSLAuthenticateClients);
      return IPWorks_SysLog_Set(m_pObj, 7, 0, val, 0);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_SysLog_Get(m_pObj, 8, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_SysLog_Set(m_pObj, 8, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_SysLog_Get(m_pObj, 9, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_SysLog_Set(m_pObj, 9, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_SysLog_Set(m_pObj, 10+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 11, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_SysLog_Set(m_pObj, 11, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_SysLog_Set(m_pObj, 12+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 13, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_SysLog_Set(m_pObj, 13, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_SysLog_Get(m_pObj, 14, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline BOOL GetUseTCP() {
      LPVOID val = IPWorks_SysLog_Get(m_pObj, 15, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetUseTCP(BOOL bUseTCP) {
      LPVOID val = (LPVOID)(bUseTCP);
      return IPWorks_SysLog_Set(m_pObj, 15, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_SysLog_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SysLog_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SysLog_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT SendPacket(INT iFacility, INT iSeverity, LPCWSTR lpszMessage) {
      LPVOID param[3+1] = {(LPVOID)iFacility, (LPVOID)iSeverity, (LPVOID)lpszMessage, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_SysLog_Do(m_pObj, 5+10000, 3, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_SYSLOG_H_
