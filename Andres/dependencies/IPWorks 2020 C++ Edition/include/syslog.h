/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_SysLog_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_SysLog_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_SysLog_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SysLog_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  const char *RemoteAddress;
  int RemotePort;
  int StatusCode;
  const char *Description;
  int reserved;
} SysLogConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} SysLogConnectionStatusEventParams;

typedef struct {
  const char *RemoteAddress;
  int RemotePort;
  int StatusCode;
  const char *Description;
  int reserved;
} SysLogDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} SysLogErrorEventParams;

typedef struct {
  int FacilityCode;
  const char *Facility;
  int SeverityCode;
  const char *Severity;
  const char *Timestamp;
  const char *Hostname;
  const char *Message;
  int Conforms;
  const char *Packet;
  int lenPacket;
  const char *SourceAddress;
  int SourcePort;
  int reserved;
} SysLogPacketInEventParams;

typedef struct {
  const char *RemoteAddress;
  int RemotePort;
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} SysLogSSLClientAuthenticationEventParams;

typedef struct {
  const char *RemoteAddress;
  int RemotePort;
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} SysLogSSLServerAuthenticationEventParams;

typedef struct {
  const char *RemoteAddress;
  int RemotePort;
  const char *Message;
  int reserved;
} SysLogSSLStatusEventParams;


class SysLog {
  public: // Events
    virtual int FireConnected(SysLogConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(SysLogConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(SysLogDisconnectedEventParams *e) {return 0;}
    virtual int FireError(SysLogErrorEventParams *e) {return 0;}
    virtual int FirePacketIn(SysLogPacketInEventParams *e) {return 0;}
    virtual int FireSSLClientAuthentication(SysLogSSLClientAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(SysLogSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(SysLogSSLStatusEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL SysLogEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          SysLogConnectedEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), 0};
          ret_code = ((SysLog*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          SysLogConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((SysLog*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          SysLogDisconnectedEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), 0};
          ret_code = ((SysLog*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          SysLogErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((SysLog*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          SysLogPacketInEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), (int)IPW64CAST(param[7]), (char*)IPW64CAST(param[8]), (int)IPW64CAST(cbparam[8]), (char*)IPW64CAST(param[9]), (int)IPW64CAST(param[10]), 0};
          ret_code = ((SysLog*)lpObj)->FirePacketIn(&e);
          break;
        }
        case 6: {
          SysLogSSLClientAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), 0};
          ret_code = ((SysLog*)lpObj)->FireSSLClientAuthentication(&e);
          param[6] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 7: {
          SysLogSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), 0};
          ret_code = ((SysLog*)lpObj)->FireSSLServerAuthentication(&e);
          param[6] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 8: {
          SysLogSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((SysLog*)lpObj)->FireSSLStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    SysLog(char *lpOemKey = (char*)IPWORKS_OEMKEY_62) {
      m_pObj = IPWorks_SysLog_Create(SysLogEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~SysLog() {
      IPWorks_SysLog_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_SysLog_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_SysLog_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_SysLog_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_SysLog_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_SysLog_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetActive() {
      void* val = IPWorks_SysLog_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetActive(int bActive) {
      void* val = (void*)IPW64CAST(bActive);
      return IPWorks_SysLog_Set(m_pObj, 1, 0, val, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_SysLog_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_SysLog_Set(m_pObj, 2, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_SysLog_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetLocalPort(int iLocalPort) {
      void* val = (void*)IPW64CAST(iLocalPort);
      return IPWorks_SysLog_Set(m_pObj, 3, 0, val, 0);
    }

    inline char* GetRemoteHost() {
      void* val = IPWorks_SysLog_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemoteHost(const char* lpszRemoteHost) {
      return IPWorks_SysLog_Set(m_pObj, 4, 0, (void*)lpszRemoteHost, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_SysLog_Get(m_pObj, 5, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRemotePort(int iRemotePort) {
      void* val = (void*)IPW64CAST(iRemotePort);
      return IPWorks_SysLog_Set(m_pObj, 5, 0, val, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_SysLog_Get(m_pObj, 6, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_SysLog_Set(m_pObj, 6, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLAuthenticateClients() {
      void* val = IPWorks_SysLog_Get(m_pObj, 7, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLAuthenticateClients(int bSSLAuthenticateClients) {
      void* val = (void*)IPW64CAST(bSSLAuthenticateClients);
      return IPWorks_SysLog_Set(m_pObj, 7, 0, val, 0);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_SysLog_Get(m_pObj, 8, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_SysLog_Set(m_pObj, 8, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_SysLog_Get(m_pObj, 9, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_SysLog_Set(m_pObj, 9, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_SysLog_Get(m_pObj, 10, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_SysLog_Set(m_pObj, 10, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_SysLog_Get(m_pObj, 11, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_SysLog_Set(m_pObj, 11, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_SysLog_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_SysLog_Set(m_pObj, 12, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_SysLog_Get(m_pObj, 13, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_SysLog_Set(m_pObj, 13, 0, val, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_SysLog_Get(m_pObj, 14, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetUseTCP() {
      void* val = IPWorks_SysLog_Get(m_pObj, 15, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetUseTCP(int bUseTCP) {
      void* val = (void*)IPW64CAST(bUseTCP);
      return IPWorks_SysLog_Set(m_pObj, 15, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SysLog_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SysLog_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SysLog_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int SendPacket(int iFacility, int iSeverity, const char* lpszMessage) {
      void *param[3+1] = {(void*)IPW64CAST(iFacility), (void*)IPW64CAST(iSeverity), (void*)IPW64CAST(lpszMessage), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_SysLog_Do(m_pObj, 5, 3, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_SYSLOG_H_
