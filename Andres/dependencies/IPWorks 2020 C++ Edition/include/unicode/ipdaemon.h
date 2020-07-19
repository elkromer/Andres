/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_IPDAEMON_H_
#define _IPWORKS_IPDAEMON_H_

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

//TSSLStartMode
#define SSL_AUTOMATIC                                      0
#define SSL_IMPLICIT                                       1
#define SSL_EXPLICIT                                       2
#define SSL_NONE                                           3


extern "C" void* IPWORKS_CALL IPWorks_IPDaemon_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_IPDaemon_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_IPDaemon_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_IPDaemon_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT ConnectionId;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} IPDaemonConnectedEventParams;

typedef struct {
  LPCWSTR Address;
  INT Port;
  BOOL Accept;
  INT reserved;
} IPDaemonConnectionRequestEventParams;

typedef struct {
  INT ConnectionId;
  LPCSTR Text;
  INT lenText;
  BOOL EOL;
  INT reserved;
} IPDaemonDataInEventParams;

typedef struct {
  INT ConnectionId;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} IPDaemonDisconnectedEventParams;

typedef struct {
  INT ConnectionId;
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} IPDaemonErrorEventParams;

typedef struct {
  INT ConnectionId;
  INT reserved;
} IPDaemonReadyToSendEventParams;

typedef struct {
  INT ConnectionId;
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} IPDaemonSSLClientAuthenticationEventParams;

typedef struct {
  INT ConnectionId;
  LPCWSTR SupportedCipherSuites;
  LPCWSTR SupportedSignatureAlgs;
  INT CertStoreType;
  LPWSTR CertStore;
  LPWSTR CertPassword;
  LPWSTR CertSubject;
  INT reserved;
} IPDaemonSSLConnectionRequestEventParams;

typedef struct {
  INT ConnectionId;
  LPCWSTR Message;
  INT reserved;
} IPDaemonSSLStatusEventParams;


class IPDaemon {
  public: // Events
    virtual INT FireConnected(IPDaemonConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionRequest(IPDaemonConnectionRequestEventParams *e) {return 0;}
    virtual INT FireDataIn(IPDaemonDataInEventParams *e) {return 0;}
    virtual INT FireDisconnected(IPDaemonDisconnectedEventParams *e) {return 0;}
    virtual INT FireError(IPDaemonErrorEventParams *e) {return 0;}
    virtual INT FireReadyToSend(IPDaemonReadyToSendEventParams *e) {return 0;}
    virtual INT FireSSLClientAuthentication(IPDaemonSSLClientAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLConnectionRequest(IPDaemonSSLConnectionRequestEventParams *e) {return 0;}
    virtual INT FireSSLStatus(IPDaemonSSLStatusEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL IPDaemonEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          IPDaemonConnectedEventParams e = {(INT)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((IPDaemon*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          IPDaemonConnectionRequestEventParams e = {(LPWSTR)param[0], (INT)param[1], (BOOL)param[2], 0};
          ret_code = ((IPDaemon*)lpObj)->FireConnectionRequest(&e);
          param[2] = (LPVOID)e.Accept;
          break;
        }
        case 3: {
          IPDaemonDataInEventParams e = {(INT)param[0], (LPSTR)param[1], (INT)cbparam[1], (BOOL)param[2], 0};
          ret_code = ((IPDaemon*)lpObj)->FireDataIn(&e);
          break;
        }
        case 4: {
          IPDaemonDisconnectedEventParams e = {(INT)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((IPDaemon*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 5: {
          IPDaemonErrorEventParams e = {(INT)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((IPDaemon*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          IPDaemonReadyToSendEventParams e = {(INT)param[0], 0};
          ret_code = ((IPDaemon*)lpObj)->FireReadyToSend(&e);
          break;
        }
        case 7: {
          IPDaemonSSLClientAuthenticationEventParams e = {(INT)param[0], (LPSTR)param[1], (INT)cbparam[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((IPDaemon*)lpObj)->FireSSLClientAuthentication(&e);
          param[5] = (LPVOID)e.Accept;
          break;
        }
        case 8: {
          IPDaemonSSLConnectionRequestEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (INT)param[3], (LPWSTR)IPWorks_EvtStr(param[4], 0, NULL, 2), (LPWSTR)IPWorks_EvtStr(param[5], 0, NULL, 2), (LPWSTR)IPWorks_EvtStr(param[6], 0, NULL, 2), 0};
          ret_code = ((IPDaemon*)lpObj)->FireSSLConnectionRequest(&e);
          param[3] = (LPVOID)e.CertStoreType;
          IPWorks_EvtStr(param[4], 1, (void*)e.CertStore, 2);
          IPWorks_EvtStr(param[5], 1, (void*)e.CertPassword, 2);
          IPWorks_EvtStr(param[6], 1, (void*)e.CertSubject, 2);
          break;
        }
        case 9: {
          IPDaemonSSLStatusEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((IPDaemon*)lpObj)->FireSSLStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    IPDaemon(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_12) {
      m_pObj = IPWorks_IPDaemon_Create(IPDaemonEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~IPDaemon() {
      IPWorks_IPDaemon_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_IPDaemon_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_IPDaemon_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_IPDaemon_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_IPDaemon_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_IPDaemon_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetConnectionBacklog() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 1, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetConnectionBacklog(INT iConnectionBacklog) {
      LPVOID val = (LPVOID)(iConnectionBacklog);
      return IPWorks_IPDaemon_Set(m_pObj, 1, 0, val, 0);
    }

    inline INT GetConnectionCount() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 2, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline BOOL GetAcceptData(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 3, iConnectionId, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetAcceptData(INT iConnectionId, BOOL bAcceptData) {
      LPVOID val = (LPVOID)(bAcceptData);
      return IPWorks_IPDaemon_Set(m_pObj, 3, iConnectionId, val, 0);
    }

    inline INT GetBytesSent(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 4, iConnectionId, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline BOOL GetConnected(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 5, iConnectionId, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(INT iConnectionId, BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_IPDaemon_Set(m_pObj, 5, iConnectionId, val, 0);
    }

    inline LPWSTR GetConnectionId(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 6+10000, iConnectionId, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT SetDataToSend(INT iConnectionId, LPCSTR lpDataToSend, INT lenDataToSend) {
      return IPWorks_IPDaemon_Set(m_pObj, 7, iConnectionId, (LPVOID)lpDataToSend, lenDataToSend);
    }

    inline INT GetEOL(INT iConnectionId, LPSTR &lpEOL, INT &lenEOL) {
      lpEOL = (LPSTR)IPWorks_IPDaemon_Get(m_pObj, 8, iConnectionId, &lenEOL, NULL);
      return lpEOL ? 0 : lenEOL;
    }
    inline INT SetEOL(INT iConnectionId, LPCSTR lpEOL, INT lenEOL) {
      return IPWorks_IPDaemon_Set(m_pObj, 8, iConnectionId, (LPVOID)lpEOL, lenEOL);
    }

    inline INT GetIdleTimeout(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 9, iConnectionId, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetIdleTimeout(INT iConnectionId, INT iIdleTimeout) {
      LPVOID val = (LPVOID)(iIdleTimeout);
      return IPWorks_IPDaemon_Set(m_pObj, 9, iConnectionId, val, 0);
    }

    inline LPWSTR GetLocalAddress(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 10+10000, iConnectionId, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetReadyToSend(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 11, iConnectionId, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline INT GetRecordLength(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 12, iConnectionId, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRecordLength(INT iConnectionId, INT iRecordLength) {
      LPVOID val = (LPVOID)(iRecordLength);
      return IPWorks_IPDaemon_Set(m_pObj, 12, iConnectionId, val, 0);
    }

    inline LPWSTR GetRemoteHost(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 13+10000, iConnectionId, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetRemotePort(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 14, iConnectionId, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline BOOL GetSingleLineMode(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 15, iConnectionId, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSingleLineMode(INT iConnectionId, BOOL bSingleLineMode) {
      LPVOID val = (LPVOID)(bSingleLineMode);
      return IPWorks_IPDaemon_Set(m_pObj, 15, iConnectionId, val, 0);
    }

    inline INT GetTimeout(INT iConnectionId) {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 16, iConnectionId, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iConnectionId, INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_IPDaemon_Set(m_pObj, 16, iConnectionId, val, 0);
    }

    inline INT GetUserData(INT iConnectionId, LPSTR &lpUserData, INT &lenUserData) {
      lpUserData = (LPSTR)IPWorks_IPDaemon_Get(m_pObj, 17, iConnectionId, &lenUserData, NULL);
      return lpUserData ? 0 : lenUserData;
    }
    inline INT SetUserData(INT iConnectionId, LPCSTR lpUserData, INT lenUserData) {
      return IPWorks_IPDaemon_Set(m_pObj, 17, iConnectionId, (LPVOID)lpUserData, lenUserData);
    }

    inline INT GetDefaultEOL(LPSTR &lpDefaultEOL, INT &lenDefaultEOL) {
      lpDefaultEOL = (LPSTR)IPWorks_IPDaemon_Get(m_pObj, 18, 0, &lenDefaultEOL, NULL);
      return lpDefaultEOL ? 0 : lenDefaultEOL;
    }
    inline INT SetDefaultEOL(LPCSTR lpDefaultEOL, INT lenDefaultEOL) {
      return IPWorks_IPDaemon_Set(m_pObj, 18, 0, (LPVOID)lpDefaultEOL, lenDefaultEOL);
    }

    inline INT GetDefaultIdleTimeout() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 19, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetDefaultIdleTimeout(INT iDefaultIdleTimeout) {
      LPVOID val = (LPVOID)(iDefaultIdleTimeout);
      return IPWorks_IPDaemon_Set(m_pObj, 19, 0, val, 0);
    }

    inline INT GetDefaultMaxLineLength() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 20, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetDefaultMaxLineLength(INT iDefaultMaxLineLength) {
      LPVOID val = (LPVOID)(iDefaultMaxLineLength);
      return IPWorks_IPDaemon_Set(m_pObj, 20, 0, val, 0);
    }

    inline BOOL GetDefaultSingleLineMode() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 21, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetDefaultSingleLineMode(BOOL bDefaultSingleLineMode) {
      LPVOID val = (LPVOID)(bDefaultSingleLineMode);
      return IPWorks_IPDaemon_Set(m_pObj, 21, 0, val, 0);
    }

    inline INT GetDefaultTimeout() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 22, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetDefaultTimeout(INT iDefaultTimeout) {
      LPVOID val = (LPVOID)(iDefaultTimeout);
      return IPWorks_IPDaemon_Set(m_pObj, 22, 0, val, 0);
    }

    inline BOOL GetKeepAlive() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 23, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetKeepAlive(BOOL bKeepAlive) {
      LPVOID val = (LPVOID)(bKeepAlive);
      return IPWorks_IPDaemon_Set(m_pObj, 23, 0, val, 0);
    }

    inline BOOL GetLinger() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 24, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetLinger(BOOL bLinger) {
      LPVOID val = (LPVOID)(bLinger);
      return IPWorks_IPDaemon_Set(m_pObj, 24, 0, val, 0);
    }

    inline BOOL GetListening() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 25, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetListening(BOOL bListening) {
      LPVOID val = (LPVOID)(bListening);
      return IPWorks_IPDaemon_Set(m_pObj, 25, 0, val, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_IPDaemon_Set(m_pObj, 26+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetLocalPort() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 27, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLocalPort(INT iLocalPort) {
      LPVOID val = (LPVOID)(iLocalPort);
      return IPWorks_IPDaemon_Set(m_pObj, 27, 0, val, 0);
    }

    inline BOOL GetSSLAuthenticateClients() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 28, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLAuthenticateClients(BOOL bSSLAuthenticateClients) {
      LPVOID val = (LPVOID)(bSSLAuthenticateClients);
      return IPWorks_IPDaemon_Set(m_pObj, 28, 0, val, 0);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_IPDaemon_Get(m_pObj, 29, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_IPDaemon_Set(m_pObj, 29, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_IPDaemon_Get(m_pObj, 30, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_IPDaemon_Set(m_pObj, 30, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_IPDaemon_Set(m_pObj, 31+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 32, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_IPDaemon_Set(m_pObj, 32, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 33+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_IPDaemon_Set(m_pObj, 33+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 34, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_IPDaemon_Set(m_pObj, 34, 0, val, 0);
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_IPDaemon_Get(m_pObj, 35, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_IPDaemon_Set(m_pObj, 35, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_IPDaemon_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Disconnect(INT iConnectionId) {
      LPVOID param[1+1] = {(LPVOID)iConnectionId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 3+10000, 1, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IPDaemon_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt(INT iConnectionId) {
      LPVOID param[1+1] = {(LPVOID)iConnectionId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IPDaemon_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Send(INT iConnectionId, LPCSTR lpText, INT lenText) {
      LPVOID param[2+1] = {(LPVOID)iConnectionId, (LPVOID)lpText, 0};
      INT cbparam[2+1] = {0, lenText, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 7+10000, 2, param, cbparam, NULL);
    }

    inline INT SendFile(INT iConnectionId, LPCWSTR lpszFileName) {
      LPVOID param[2+1] = {(LPVOID)iConnectionId, (LPVOID)lpszFileName, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 8+10000, 2, param, cbparam, NULL);
    }

    inline INT SendLine(INT iConnectionId, LPCWSTR lpszText) {
      LPVOID param[2+1] = {(LPVOID)iConnectionId, (LPVOID)lpszText, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 9+10000, 2, param, cbparam, NULL);
    }

    inline INT Shutdown() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IPDaemon_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT StartSSL(INT iConnectionId) {
      LPVOID param[1+1] = {(LPVOID)iConnectionId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 11+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_IPDAEMON_H_
