/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_IPDaemon_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_IPDaemon_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_IPDaemon_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  int ConnectionId;
  int StatusCode;
  const char *Description;
  int reserved;
} IPDaemonConnectedEventParams;

typedef struct {
  const char *Address;
  int Port;
  int Accept;
  int reserved;
} IPDaemonConnectionRequestEventParams;

typedef struct {
  int ConnectionId;
  const char *Text;
  int lenText;
  int EOL;
  int reserved;
} IPDaemonDataInEventParams;

typedef struct {
  int ConnectionId;
  int StatusCode;
  const char *Description;
  int reserved;
} IPDaemonDisconnectedEventParams;

typedef struct {
  int ConnectionId;
  int ErrorCode;
  const char *Description;
  int reserved;
} IPDaemonErrorEventParams;

typedef struct {
  int ConnectionId;
  int reserved;
} IPDaemonReadyToSendEventParams;

typedef struct {
  int ConnectionId;
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} IPDaemonSSLClientAuthenticationEventParams;

typedef struct {
  int ConnectionId;
  const char *SupportedCipherSuites;
  const char *SupportedSignatureAlgs;
  int CertStoreType;
  char *CertStore;
  char *CertPassword;
  char *CertSubject;
  int reserved;
} IPDaemonSSLConnectionRequestEventParams;

typedef struct {
  int ConnectionId;
  const char *Message;
  int reserved;
} IPDaemonSSLStatusEventParams;


class IPDaemon {
  public: // Events
    virtual int FireConnected(IPDaemonConnectedEventParams *e) {return 0;}
    virtual int FireConnectionRequest(IPDaemonConnectionRequestEventParams *e) {return 0;}
    virtual int FireDataIn(IPDaemonDataInEventParams *e) {return 0;}
    virtual int FireDisconnected(IPDaemonDisconnectedEventParams *e) {return 0;}
    virtual int FireError(IPDaemonErrorEventParams *e) {return 0;}
    virtual int FireReadyToSend(IPDaemonReadyToSendEventParams *e) {return 0;}
    virtual int FireSSLClientAuthentication(IPDaemonSSLClientAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLConnectionRequest(IPDaemonSSLConnectionRequestEventParams *e) {return 0;}
    virtual int FireSSLStatus(IPDaemonSSLStatusEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL IPDaemonEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          IPDaemonConnectedEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((IPDaemon*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          IPDaemonConnectionRequestEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), 0};
          ret_code = ((IPDaemon*)lpObj)->FireConnectionRequest(&e);
          param[2] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 3: {
          IPDaemonDataInEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(cbparam[1]), (int)IPW64CAST(param[2]), 0};
          ret_code = ((IPDaemon*)lpObj)->FireDataIn(&e);
          break;
        }
        case 4: {
          IPDaemonDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((IPDaemon*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 5: {
          IPDaemonErrorEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((IPDaemon*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          IPDaemonReadyToSendEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((IPDaemon*)lpObj)->FireReadyToSend(&e);
          break;
        }
        case 7: {
          IPDaemonSSLClientAuthenticationEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(cbparam[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), 0};
          ret_code = ((IPDaemon*)lpObj)->FireSSLClientAuthentication(&e);
          param[5] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 8: {
          IPDaemonSSLConnectionRequestEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (char*)IPWorks_EvtStr(param[4], 0, NULL, 1), (char*)IPWorks_EvtStr(param[5], 0, NULL, 1), (char*)IPWorks_EvtStr(param[6], 0, NULL, 1), 0};
          ret_code = ((IPDaemon*)lpObj)->FireSSLConnectionRequest(&e);
          param[3] = (void*)IPW64CAST(e.CertStoreType);
          IPWorks_EvtStr(param[4], 1, (void*)e.CertStore, 1);
          IPWorks_EvtStr(param[5], 1, (void*)e.CertPassword, 1);
          IPWorks_EvtStr(param[6], 1, (void*)e.CertSubject, 1);
          break;
        }
        case 9: {
          IPDaemonSSLStatusEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((IPDaemon*)lpObj)->FireSSLStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    IPDaemon(char *lpOemKey = (char*)IPWORKS_OEMKEY_12) {
      m_pObj = IPWorks_IPDaemon_Create(IPDaemonEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~IPDaemon() {
      IPWorks_IPDaemon_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_IPDaemon_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_IPDaemon_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_IPDaemon_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_IPDaemon_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_IPDaemon_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetConnectionBacklog() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnectionBacklog(int iConnectionBacklog) {
      void* val = (void*)IPW64CAST(iConnectionBacklog);
      return IPWorks_IPDaemon_Set(m_pObj, 1, 0, val, 0);
    }

    inline int GetConnectionCount() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 2, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetAcceptData(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 3, iConnectionId, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAcceptData(int iConnectionId, int bAcceptData) {
      void* val = (void*)IPW64CAST(bAcceptData);
      return IPWorks_IPDaemon_Set(m_pObj, 3, iConnectionId, val, 0);
    }

    inline int GetBytesSent(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 4, iConnectionId, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetConnected(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 5, iConnectionId, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int iConnectionId, int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_IPDaemon_Set(m_pObj, 5, iConnectionId, val, 0);
    }

    inline char* GetConnectionId(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 6, iConnectionId, NULL, NULL);
      return (char*)val;
    }

    inline int SetDataToSend(int iConnectionId, const char* lpDataToSend, int lenDataToSend) {
      return IPWorks_IPDaemon_Set(m_pObj, 7, iConnectionId, (void*)lpDataToSend, lenDataToSend);
    }

    inline int GetEOL(int iConnectionId, char* &lpEOL, int &lenEOL) {
      lpEOL = (char*)IPWorks_IPDaemon_Get(m_pObj, 8, iConnectionId, &lenEOL, NULL);
      return lpEOL ? 0 : lenEOL;
    }
    inline int SetEOL(int iConnectionId, const char* lpEOL, int lenEOL) {
      return IPWorks_IPDaemon_Set(m_pObj, 8, iConnectionId, (void*)lpEOL, lenEOL);
    }

    inline int GetIdleTimeout(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 9, iConnectionId, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetIdleTimeout(int iConnectionId, int iIdleTimeout) {
      void* val = (void*)IPW64CAST(iIdleTimeout);
      return IPWorks_IPDaemon_Set(m_pObj, 9, iConnectionId, val, 0);
    }

    inline char* GetLocalAddress(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 10, iConnectionId, NULL, NULL);
      return (char*)val;
    }

    inline int GetReadyToSend(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 11, iConnectionId, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetRecordLength(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 12, iConnectionId, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRecordLength(int iConnectionId, int iRecordLength) {
      void* val = (void*)IPW64CAST(iRecordLength);
      return IPWorks_IPDaemon_Set(m_pObj, 12, iConnectionId, val, 0);
    }

    inline char* GetRemoteHost(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 13, iConnectionId, NULL, NULL);
      return (char*)val;
    }

    inline int GetRemotePort(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 14, iConnectionId, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetSingleLineMode(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 15, iConnectionId, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSingleLineMode(int iConnectionId, int bSingleLineMode) {
      void* val = (void*)IPW64CAST(bSingleLineMode);
      return IPWorks_IPDaemon_Set(m_pObj, 15, iConnectionId, val, 0);
    }

    inline int GetTimeout(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 16, iConnectionId, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iConnectionId, int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_IPDaemon_Set(m_pObj, 16, iConnectionId, val, 0);
    }

    inline int GetUserData(int iConnectionId, char* &lpUserData, int &lenUserData) {
      lpUserData = (char*)IPWorks_IPDaemon_Get(m_pObj, 17, iConnectionId, &lenUserData, NULL);
      return lpUserData ? 0 : lenUserData;
    }
    inline int SetUserData(int iConnectionId, const char* lpUserData, int lenUserData) {
      return IPWorks_IPDaemon_Set(m_pObj, 17, iConnectionId, (void*)lpUserData, lenUserData);
    }

    inline int GetDefaultEOL(char* &lpDefaultEOL, int &lenDefaultEOL) {
      lpDefaultEOL = (char*)IPWorks_IPDaemon_Get(m_pObj, 18, 0, &lenDefaultEOL, NULL);
      return lpDefaultEOL ? 0 : lenDefaultEOL;
    }
    inline int SetDefaultEOL(const char* lpDefaultEOL, int lenDefaultEOL) {
      return IPWorks_IPDaemon_Set(m_pObj, 18, 0, (void*)lpDefaultEOL, lenDefaultEOL);
    }

    inline int GetDefaultIdleTimeout() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 19, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetDefaultIdleTimeout(int iDefaultIdleTimeout) {
      void* val = (void*)IPW64CAST(iDefaultIdleTimeout);
      return IPWorks_IPDaemon_Set(m_pObj, 19, 0, val, 0);
    }

    inline int GetDefaultMaxLineLength() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 20, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetDefaultMaxLineLength(int iDefaultMaxLineLength) {
      void* val = (void*)IPW64CAST(iDefaultMaxLineLength);
      return IPWorks_IPDaemon_Set(m_pObj, 20, 0, val, 0);
    }

    inline int GetDefaultSingleLineMode() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 21, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetDefaultSingleLineMode(int bDefaultSingleLineMode) {
      void* val = (void*)IPW64CAST(bDefaultSingleLineMode);
      return IPWorks_IPDaemon_Set(m_pObj, 21, 0, val, 0);
    }

    inline int GetDefaultTimeout() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 22, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetDefaultTimeout(int iDefaultTimeout) {
      void* val = (void*)IPW64CAST(iDefaultTimeout);
      return IPWorks_IPDaemon_Set(m_pObj, 22, 0, val, 0);
    }

    inline int GetKeepAlive() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 23, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetKeepAlive(int bKeepAlive) {
      void* val = (void*)IPW64CAST(bKeepAlive);
      return IPWorks_IPDaemon_Set(m_pObj, 23, 0, val, 0);
    }

    inline int GetLinger() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 24, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetLinger(int bLinger) {
      void* val = (void*)IPW64CAST(bLinger);
      return IPWorks_IPDaemon_Set(m_pObj, 24, 0, val, 0);
    }

    inline int GetListening() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 25, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetListening(int bListening) {
      void* val = (void*)IPW64CAST(bListening);
      return IPWorks_IPDaemon_Set(m_pObj, 25, 0, val, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_IPDaemon_Set(m_pObj, 26, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 27, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetLocalPort(int iLocalPort) {
      void* val = (void*)IPW64CAST(iLocalPort);
      return IPWorks_IPDaemon_Set(m_pObj, 27, 0, val, 0);
    }

    inline int GetSSLAuthenticateClients() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 28, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLAuthenticateClients(int bSSLAuthenticateClients) {
      void* val = (void*)IPW64CAST(bSSLAuthenticateClients);
      return IPWorks_IPDaemon_Set(m_pObj, 28, 0, val, 0);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_IPDaemon_Get(m_pObj, 29, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_IPDaemon_Set(m_pObj, 29, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_IPDaemon_Get(m_pObj, 30, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_IPDaemon_Set(m_pObj, 30, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 31, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_IPDaemon_Set(m_pObj, 31, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 32, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_IPDaemon_Set(m_pObj, 32, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 33, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_IPDaemon_Set(m_pObj, 33, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 34, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_IPDaemon_Set(m_pObj, 34, 0, val, 0);
    }

    inline int GetSSLStartMode() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 35, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_IPDaemon_Set(m_pObj, 35, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPDaemon_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Disconnect(int iConnectionId) {
      void *param[1+1] = {(void*)IPW64CAST(iConnectionId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 3, 1, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPDaemon_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Interrupt(int iConnectionId) {
      void *param[1+1] = {(void*)IPW64CAST(iConnectionId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 5, 1, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPDaemon_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int Send(int iConnectionId, const char* lpText, int lenText) {
      void *param[2+1] = {(void*)IPW64CAST(iConnectionId), (void*)IPW64CAST(lpText), 0};
      int cbparam[2+1] = {0, lenText, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 7, 2, param, cbparam, NULL);
    }

    inline int SendFile(int iConnectionId, const char* lpszFileName) {
      void *param[2+1] = {(void*)IPW64CAST(iConnectionId), (void*)IPW64CAST(lpszFileName), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 8, 2, param, cbparam, NULL);
    }

    inline int SendLine(int iConnectionId, const char* lpszText) {
      void *param[2+1] = {(void*)IPW64CAST(iConnectionId), (void*)IPW64CAST(lpszText), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 9, 2, param, cbparam, NULL);
    }

    inline int Shutdown() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPDaemon_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int StartSSL(int iConnectionId) {
      void *param[1+1] = {(void*)IPW64CAST(iConnectionId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 11, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_IPDAEMON_H_
