/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_TELNET_H_
#define _IPWORKS_TELNET_H_

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


extern "C" void* IPWORKS_CALL IPWorks_Telnet_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Telnet_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_Telnet_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_Telnet_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT CommandCode;
  INT reserved;
} TelnetCommandEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} TelnetConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} TelnetConnectionStatusEventParams;

typedef struct {
  LPCSTR Text;
  INT lenText;
  INT reserved;
} TelnetDataInEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} TelnetDisconnectedEventParams;

typedef struct {
  INT OptionCode;
  INT reserved;
} TelnetDoEventParams;

typedef struct {
  INT OptionCode;
  INT reserved;
} TelnetDontEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} TelnetErrorEventParams;

typedef struct {
  INT reserved;
} TelnetReadyToSendEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} TelnetSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} TelnetSSLStatusEventParams;

typedef struct {
  LPCSTR SubOption;
  INT lenSubOption;
  INT reserved;
} TelnetSubOptionEventParams;

typedef struct {
  INT OptionCode;
  INT reserved;
} TelnetWillEventParams;

typedef struct {
  INT OptionCode;
  INT reserved;
} TelnetWontEventParams;


class Telnet {
  public: // Events
    virtual INT FireCommand(TelnetCommandEventParams *e) {return 0;}
    virtual INT FireConnected(TelnetConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(TelnetConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDataIn(TelnetDataInEventParams *e) {return 0;}
    virtual INT FireDisconnected(TelnetDisconnectedEventParams *e) {return 0;}
    virtual INT FireDo(TelnetDoEventParams *e) {return 0;}
    virtual INT FireDont(TelnetDontEventParams *e) {return 0;}
    virtual INT FireError(TelnetErrorEventParams *e) {return 0;}
    virtual INT FireReadyToSend(TelnetReadyToSendEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(TelnetSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(TelnetSSLStatusEventParams *e) {return 0;}
    virtual INT FireSubOption(TelnetSubOptionEventParams *e) {return 0;}
    virtual INT FireWill(TelnetWillEventParams *e) {return 0;}
    virtual INT FireWont(TelnetWontEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL TelnetEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          TelnetCommandEventParams e = {(INT)param[0], 0};
          ret_code = ((Telnet*)lpObj)->FireCommand(&e);
          break;
        }
        case 2: {
          TelnetConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Telnet*)lpObj)->FireConnected(&e);
          break;
        }
        case 3: {
          TelnetConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((Telnet*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 4: {
          TelnetDataInEventParams e = {(LPSTR)param[0], (INT)cbparam[0], 0};
          ret_code = ((Telnet*)lpObj)->FireDataIn(&e);
          break;
        }
        case 5: {
          TelnetDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Telnet*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 6: {
          TelnetDoEventParams e = {(INT)param[0], 0};
          ret_code = ((Telnet*)lpObj)->FireDo(&e);
          break;
        }
        case 7: {
          TelnetDontEventParams e = {(INT)param[0], 0};
          ret_code = ((Telnet*)lpObj)->FireDont(&e);
          break;
        }
        case 8: {
          TelnetErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Telnet*)lpObj)->FireError(&e);
          break;
        }
        case 9: {
          TelnetReadyToSendEventParams e = {0};
          ret_code = ((Telnet*)lpObj)->FireReadyToSend(&e);
          break;
        }
        case 10: {
          TelnetSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((Telnet*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 11: {
          TelnetSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((Telnet*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 12: {
          TelnetSubOptionEventParams e = {(LPSTR)param[0], (INT)cbparam[0], 0};
          ret_code = ((Telnet*)lpObj)->FireSubOption(&e);
          break;
        }
        case 13: {
          TelnetWillEventParams e = {(INT)param[0], 0};
          ret_code = ((Telnet*)lpObj)->FireWill(&e);
          break;
        }
        case 14: {
          TelnetWontEventParams e = {(INT)param[0], 0};
          ret_code = ((Telnet*)lpObj)->FireWont(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    Telnet(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_19) {
      m_pObj = IPWorks_Telnet_Create(TelnetEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~Telnet() {
      IPWorks_Telnet_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_Telnet_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_Telnet_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_Telnet_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_Telnet_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_Telnet_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetAcceptData() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetAcceptData(BOOL bAcceptData) {
      LPVOID val = (LPVOID)(bAcceptData);
      return IPWorks_Telnet_Set(m_pObj, 1, 0, val, 0);
    }

    inline INT GetBytesSent() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 2, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT SetCommand(INT iCommand) {
      LPVOID val = (LPVOID)(iCommand);
      return IPWorks_Telnet_Set(m_pObj, 3, 0, val, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 4, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_Telnet_Set(m_pObj, 4, 0, val, 0);
    }

    inline INT SetDataToSend(LPCSTR lpDataToSend, INT lenDataToSend) {
      return IPWorks_Telnet_Set(m_pObj, 5, 0, (LPVOID)lpDataToSend, lenDataToSend);
    }

    inline INT SetDontOption(INT iDontOption) {
      LPVOID val = (LPVOID)(iDontOption);
      return IPWorks_Telnet_Set(m_pObj, 6, 0, val, 0);
    }

    inline INT SetDoOption(INT iDoOption) {
      LPVOID val = (LPVOID)(iDoOption);
      return IPWorks_Telnet_Set(m_pObj, 7, 0, val, 0);
    }

    inline INT SetDoSubOption(LPCSTR lpDoSubOption, INT lenDoSubOption) {
      return IPWorks_Telnet_Set(m_pObj, 8, 0, (LPVOID)lpDoSubOption, lenDoSubOption);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 9, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_Telnet_Set(m_pObj, 9, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 10, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_Telnet_Set(m_pObj, 10, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_Telnet_Set(m_pObj, 11+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_Telnet_Set(m_pObj, 12+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 13, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_Telnet_Set(m_pObj, 13, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_Telnet_Set(m_pObj, 14+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline BOOL GetKeepAlive() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 15, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetKeepAlive(BOOL bKeepAlive) {
      LPVOID val = (LPVOID)(bKeepAlive);
      return IPWorks_Telnet_Set(m_pObj, 15, 0, val, 0);
    }

    inline BOOL GetLinger() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 16, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetLinger(BOOL bLinger) {
      LPVOID val = (LPVOID)(bLinger);
      return IPWorks_Telnet_Set(m_pObj, 16, 0, val, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_Telnet_Set(m_pObj, 17+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetLocalPort() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 18, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLocalPort(INT iLocalPort) {
      LPVOID val = (LPVOID)(iLocalPort);
      return IPWorks_Telnet_Set(m_pObj, 18, 0, val, 0);
    }

    inline LPWSTR GetRemoteHost() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteHost(LPCWSTR lpszRemoteHost) {
      return IPWorks_Telnet_Set(m_pObj, 19+10000, 0, (LPVOID)lpszRemoteHost, 0);
    }

    inline INT GetRemotePort() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 20, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRemotePort(INT iRemotePort) {
      LPVOID val = (LPVOID)(iRemotePort);
      return IPWorks_Telnet_Set(m_pObj, 20, 0, val, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_Telnet_Get(m_pObj, 21, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_Telnet_Set(m_pObj, 21, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_Telnet_Get(m_pObj, 22, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_Telnet_Set(m_pObj, 22, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_Telnet_Get(m_pObj, 23, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_Telnet_Set(m_pObj, 23, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_Telnet_Set(m_pObj, 24+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 25, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_Telnet_Set(m_pObj, 25, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_Telnet_Set(m_pObj, 26+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 27, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_Telnet_Set(m_pObj, 27, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_Telnet_Get(m_pObj, 28, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 29, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_Telnet_Set(m_pObj, 29, 0, val, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 30, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_Telnet_Set(m_pObj, 30, 0, val, 0);
    }

    inline BOOL GetTransparent() {
      LPVOID val = IPWorks_Telnet_Get(m_pObj, 31, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetTransparent(BOOL bTransparent) {
      LPVOID val = (LPVOID)(bTransparent);
      return IPWorks_Telnet_Set(m_pObj, 31, 0, val, 0);
    }

    inline INT SetUrgentData(LPCSTR lpUrgentData, INT lenUrgentData) {
      return IPWorks_Telnet_Set(m_pObj, 32, 0, (LPVOID)lpUrgentData, lenUrgentData);
    }

    inline INT SetWillOption(INT iWillOption) {
      LPVOID val = (LPVOID)(iWillOption);
      return IPWorks_Telnet_Set(m_pObj, 33, 0, val, 0);
    }

    inline INT SetWontOption(INT iWontOption) {
      LPVOID val = (LPVOID)(iWontOption);
      return IPWorks_Telnet_Set(m_pObj, 34, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_Telnet_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Connect(LPCWSTR lpszHost) {
      LPVOID param[1+1] = {(LPVOID)lpszHost, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Telnet_Do(m_pObj, 3+10000, 1, param, cbparam, NULL);
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Telnet_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Telnet_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Telnet_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Send(LPCSTR lpText, INT lenText) {
      LPVOID param[1+1] = {(LPVOID)lpText, 0};
      INT cbparam[1+1] = {lenText, 0};
      return IPWorks_Telnet_Do(m_pObj, 7+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_TELNET_H_
