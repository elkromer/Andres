/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_SNPP_H_
#define _IPWORKS_SNPP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

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

//TSSLStartMode
#define SSL_AUTOMATIC                                      0
#define SSL_IMPLICIT                                       1
#define SSL_EXPLICIT                                       2
#define SSL_NONE                                           3


extern "C" void* IPWORKS_CALL IPWorks_SNPP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SNPP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_SNPP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_SNPP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SNPPConnectionStatusEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} SNPPErrorEventParams;

typedef struct {
  INT Direction;
  LPCWSTR Message;
  INT reserved;
} SNPPPITrailEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} SNPPSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} SNPPSSLStatusEventParams;


class SNPP {
  public: // Events
    virtual INT FireConnectionStatus(SNPPConnectionStatusEventParams *e) {return 0;}
    virtual INT FireError(SNPPErrorEventParams *e) {return 0;}
    virtual INT FirePITrail(SNPPPITrailEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(SNPPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(SNPPSSLStatusEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL SNPPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          SNPPConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((SNPP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          SNPPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((SNPP*)lpObj)->FireError(&e);
          break;
        }
        case 3: {
          SNPPPITrailEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((SNPP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 4: {
          SNPPSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((SNPP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 5: {
          SNPPSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((SNPP*)lpObj)->FireSSLStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    SNPP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_32) {
      m_pObj = IPWorks_SNPP_Create(SNPPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~SNPP() {
      IPWorks_SNPP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_SNPP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_SNPP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_SNPP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_SNPP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_SNPP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetCallerId() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCallerId(LPCWSTR lpszCallerId) {
      return IPWorks_SNPP_Set(m_pObj, 1+10000, 0, (LPVOID)lpszCallerId, 0);
    }

    inline INT SetCommand(LPCWSTR lpszCommand) {
      return IPWorks_SNPP_Set(m_pObj, 2+10000, 0, (LPVOID)lpszCommand, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 3, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_SNPP_Set(m_pObj, 3, 0, val, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 4, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_SNPP_Set(m_pObj, 4, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 5, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_SNPP_Set(m_pObj, 5, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_SNPP_Set(m_pObj, 6+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_SNPP_Set(m_pObj, 7+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 8, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_SNPP_Set(m_pObj, 8, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_SNPP_Set(m_pObj, 9+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 10, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLastReply() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_SNPP_Set(m_pObj, 12+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetMessage() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessage(LPCWSTR lpszMessage) {
      return IPWorks_SNPP_Set(m_pObj, 13+10000, 0, (LPVOID)lpszMessage, 0);
    }

    inline LPWSTR GetPagerId() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPagerId(LPCWSTR lpszPagerId) {
      return IPWorks_SNPP_Set(m_pObj, 14+10000, 0, (LPVOID)lpszPagerId, 0);
    }

    inline LPWSTR GetServerName() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetServerName(LPCWSTR lpszServerName) {
      return IPWorks_SNPP_Set(m_pObj, 15+10000, 0, (LPVOID)lpszServerName, 0);
    }

    inline INT GetServerPort() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 16, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetServerPort(INT iServerPort) {
      LPVOID val = (LPVOID)(iServerPort);
      return IPWorks_SNPP_Set(m_pObj, 16, 0, val, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_SNPP_Get(m_pObj, 17, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_SNPP_Set(m_pObj, 17, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_SNPP_Get(m_pObj, 18, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_SNPP_Set(m_pObj, 18, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_SNPP_Get(m_pObj, 19, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_SNPP_Set(m_pObj, 19, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_SNPP_Set(m_pObj, 20+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 21, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_SNPP_Set(m_pObj, 21, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_SNPP_Set(m_pObj, 22+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 23, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_SNPP_Set(m_pObj, 23, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_SNPP_Get(m_pObj, 24, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 25, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_SNPP_Set(m_pObj, 25, 0, val, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_SNPP_Get(m_pObj, 26, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_SNPP_Set(m_pObj, 26, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_SNPP_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Connect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT Send() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_SNPP_H_
