/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_SNPP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_SNPP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_SNPP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} SNPPConnectionStatusEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} SNPPErrorEventParams;

typedef struct {
  int Direction;
  const char *Message;
  int reserved;
} SNPPPITrailEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} SNPPSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} SNPPSSLStatusEventParams;


class SNPP {
  public: // Events
    virtual int FireConnectionStatus(SNPPConnectionStatusEventParams *e) {return 0;}
    virtual int FireError(SNPPErrorEventParams *e) {return 0;}
    virtual int FirePITrail(SNPPPITrailEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(SNPPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(SNPPSSLStatusEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL SNPPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          SNPPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((SNPP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          SNPPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((SNPP*)lpObj)->FireError(&e);
          break;
        }
        case 3: {
          SNPPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((SNPP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 4: {
          SNPPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((SNPP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 5: {
          SNPPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((SNPP*)lpObj)->FireSSLStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    SNPP(char *lpOemKey = (char*)IPWORKS_OEMKEY_32) {
      m_pObj = IPWorks_SNPP_Create(SNPPEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~SNPP() {
      IPWorks_SNPP_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_SNPP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_SNPP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_SNPP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_SNPP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_SNPP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetCallerId() {
      void* val = IPWorks_SNPP_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCallerId(const char* lpszCallerId) {
      return IPWorks_SNPP_Set(m_pObj, 1, 0, (void*)lpszCallerId, 0);
    }

    inline int SetCommand(const char* lpszCommand) {
      return IPWorks_SNPP_Set(m_pObj, 2, 0, (void*)lpszCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_SNPP_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_SNPP_Set(m_pObj, 3, 0, val, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_SNPP_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_SNPP_Set(m_pObj, 4, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_SNPP_Get(m_pObj, 5, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_SNPP_Set(m_pObj, 5, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_SNPP_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_SNPP_Set(m_pObj, 6, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_SNPP_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_SNPP_Set(m_pObj, 7, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_SNPP_Get(m_pObj, 8, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_SNPP_Set(m_pObj, 8, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_SNPP_Get(m_pObj, 9, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_SNPP_Set(m_pObj, 9, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_SNPP_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLastReply() {
      void* val = IPWorks_SNPP_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_SNPP_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_SNPP_Set(m_pObj, 12, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetMessage() {
      void* val = IPWorks_SNPP_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessage(const char* lpszMessage) {
      return IPWorks_SNPP_Set(m_pObj, 13, 0, (void*)lpszMessage, 0);
    }

    inline char* GetPagerId() {
      void* val = IPWorks_SNPP_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPagerId(const char* lpszPagerId) {
      return IPWorks_SNPP_Set(m_pObj, 14, 0, (void*)lpszPagerId, 0);
    }

    inline char* GetServerName() {
      void* val = IPWorks_SNPP_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetServerName(const char* lpszServerName) {
      return IPWorks_SNPP_Set(m_pObj, 15, 0, (void*)lpszServerName, 0);
    }

    inline int GetServerPort() {
      void* val = IPWorks_SNPP_Get(m_pObj, 16, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetServerPort(int iServerPort) {
      void* val = (void*)IPW64CAST(iServerPort);
      return IPWorks_SNPP_Set(m_pObj, 16, 0, val, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_SNPP_Get(m_pObj, 17, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_SNPP_Set(m_pObj, 17, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_SNPP_Get(m_pObj, 18, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_SNPP_Set(m_pObj, 18, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_SNPP_Get(m_pObj, 19, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_SNPP_Set(m_pObj, 19, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_SNPP_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_SNPP_Set(m_pObj, 20, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_SNPP_Get(m_pObj, 21, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_SNPP_Set(m_pObj, 21, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_SNPP_Get(m_pObj, 22, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_SNPP_Set(m_pObj, 22, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_SNPP_Get(m_pObj, 23, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_SNPP_Set(m_pObj, 23, 0, val, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_SNPP_Get(m_pObj, 24, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetSSLStartMode() {
      void* val = IPWorks_SNPP_Get(m_pObj, 25, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_SNPP_Set(m_pObj, 25, 0, val, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_SNPP_Get(m_pObj, 26, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_SNPP_Set(m_pObj, 26, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SNPP_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_SNPP_H_
