/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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

//TSSLStartMode
#define SSL_AUTOMATIC                                      0
#define SSL_IMPLICIT                                       1
#define SSL_EXPLICIT                                       2
#define SSL_NONE                                           3


extern "C" void* IPWORKS_CALL IPWorks_SNPP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SNPP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_SNPP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} SNPPConnectionStatusEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} SNPPErrorEventParams;

typedef struct {
  int Direction;
  const char* Message;
  int reserved;
} SNPPPITrailEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} SNPPSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} SNPPSSLStatusEventParams;



class SNPP {
  
  public: //events
  
    virtual int FireConnectionStatus(SNPPConnectionStatusEventParams *e) {return 0;}
    virtual int FireError(SNPPErrorEventParams *e) {return 0;}
    virtual int FirePITrail(SNPPPITrailEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(SNPPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(SNPPSSLStatusEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL SNPPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((SNPP*)lpObj)->SNPPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            SNPPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((SNPP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 2: {
            SNPPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SNPP*)lpObj)->FireError(&e);
            break;
         }
         case 3: {
            SNPPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SNPP*)lpObj)->FirePITrail(&e);
            break;
         }
         case 4: {
            SNPPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((SNPP*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 5: {
            SNPPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((SNPP*)lpObj)->FireSSLStatus(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int SNPPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    SNPP(char *lpOemKey = (char*)IPWORKS_OEMKEY_32) {
      m_pObj = IPWorks_SNPP_Create(SNPPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~SNPP() {
      IPWorks_SNPP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_SNPP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_SNPP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_SNPP_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_SNPP_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_SNPP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetCallerId() {
      void* val = IPWorks_SNPP_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetCallerId(const char *lpCallerId) {
      return IPWorks_SNPP_Set(m_pObj, 1, 0, (void*)lpCallerId, 0);
    }


    inline int SetCommand(const char *lpCommand) {
      return IPWorks_SNPP_Set(m_pObj, 2, 0, (void*)lpCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_SNPP_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_SNPP_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_SNPP_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_SNPP_Set(m_pObj, 4, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_SNPP_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_SNPP_Set(m_pObj, 5, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_SNPP_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_SNPP_Set(m_pObj, 6, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_SNPP_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_SNPP_Set(m_pObj, 7, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_SNPP_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_SNPP_Set(m_pObj, 8, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_SNPP_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_SNPP_Set(m_pObj, 9, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_SNPP_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLastReply() {
      void* val = IPWorks_SNPP_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }


    inline char* GetLocalHost() {
      void* val = IPWorks_SNPP_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_SNPP_Set(m_pObj, 12, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetMessage() {
      void* val = IPWorks_SNPP_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetMessage(const char *lpMessage) {
      return IPWorks_SNPP_Set(m_pObj, 13, 0, (void*)lpMessage, 0);
    }

    inline char* GetPagerId() {
      void* val = IPWorks_SNPP_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetPagerId(const char *lpPagerId) {
      return IPWorks_SNPP_Set(m_pObj, 14, 0, (void*)lpPagerId, 0);
    }

    inline char* GetServerName() {
      void* val = IPWorks_SNPP_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetServerName(const char *lpServerName) {
      return IPWorks_SNPP_Set(m_pObj, 15, 0, (void*)lpServerName, 0);
    }

    inline int GetServerPort() {
      void* val = IPWorks_SNPP_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetServerPort(int lServerPort) {
      void* val = (void*)IPW64CAST(lServerPort);
      return IPWorks_SNPP_Set(m_pObj, 16, 0, val, 0);
    }
    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_SNPP_Get(m_pObj, 17, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_SNPP_Set(m_pObj, 17, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_SNPP_Get(m_pObj, 18, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_SNPP_Set(m_pObj, 18, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_SNPP_Get(m_pObj, 19, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_SNPP_Set(m_pObj, 19, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_SNPP_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_SNPP_Set(m_pObj, 20, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_SNPP_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_SNPP_Set(m_pObj, 21, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_SNPP_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_SNPP_Set(m_pObj, 22, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_SNPP_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_SNPP_Set(m_pObj, 23, 0, val, 0);
    }
    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_SNPP_Get(m_pObj, 24, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline int GetSSLStartMode() {
      void* val = IPWorks_SNPP_Get(m_pObj, 25, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_SNPP_Set(m_pObj, 25, 0, val, 0);
    }
    inline int GetTimeout() {
      void* val = IPWorks_SNPP_Get(m_pObj, 26, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_SNPP_Set(m_pObj, 26, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SNPP_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} SNPPConnectionStatusEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} SNPPErrorEventParamsW;

typedef struct {
  int Direction;
  LPWSTR Message;
  int reserved;
} SNPPPITrailEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} SNPPSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} SNPPSSLStatusEventParamsW;



class SNPPW : public SNPP {

  public: //properties
  
    inline LPWSTR GetCallerId() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetCallerId(LPCWSTR lpCallerId) {
      return IPWorks_SNPP_Set(m_pObj, 10000+1, 0, (void*)lpCallerId, 0);
    }



    inline int SetCommand(LPCWSTR lpCommand) {
      return IPWorks_SNPP_Set(m_pObj, 10000+2, 0, (void*)lpCommand, 0);
    }







    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_SNPP_Set(m_pObj, 10000+6, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_SNPP_Set(m_pObj, 10000+7, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_SNPP_Set(m_pObj, 10000+9, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetLastReply() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+11, 0, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_SNPP_Set(m_pObj, 10000+12, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetMessage() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetMessage(LPCWSTR lpMessage) {
      return IPWorks_SNPP_Set(m_pObj, 10000+13, 0, (void*)lpMessage, 0);
    }

    inline LPWSTR GetPagerId() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetPagerId(LPCWSTR lpPagerId) {
      return IPWorks_SNPP_Set(m_pObj, 10000+14, 0, (void*)lpPagerId, 0);
    }

    inline LPWSTR GetServerName() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetServerName(LPCWSTR lpServerName) {
      return IPWorks_SNPP_Set(m_pObj, 10000+15, 0, (void*)lpServerName, 0);
    }



    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_SNPP_Set(m_pObj, 10000+17, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_SNPP_Get(m_pObj, 17, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_SNPP_Set(m_pObj, 17, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_SNPP_Set(m_pObj, 10000+18, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_SNPP_Get(m_pObj, 18, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_SNPP_Set(m_pObj, 18, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_SNPP_Set(m_pObj, 10000+19, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_SNPP_Get(m_pObj, 19, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_SNPP_Set(m_pObj, 19, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_SNPP_Set(m_pObj, 10000+20, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_SNPP_Set(m_pObj, 10000+22, 0, (void*)lpSSLCertSubject, 0);
    }



    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+24, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_SNPP_Get(m_pObj, 24, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }







  public: //events
  
    virtual int FireConnectionStatus(SNPPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireError(SNPPErrorEventParamsW *e) {return 0;}
    virtual int FirePITrail(SNPPPITrailEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(SNPPSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(SNPPSSLStatusEventParamsW *e) {return 0;}


  protected:
  
    virtual int SNPPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            SNPPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 2: {
            SNPPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 3: {
            SNPPPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }
         case 4: {
            SNPPSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 5: {
            SNPPSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnectionStatus(SNPPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireError(SNPPErrorEventParams *e) {return -10000;}
    virtual int FirePITrail(SNPPPITrailEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(SNPPSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(SNPPSSLStatusEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SNPP_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_SNPP_H_




