/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_WEBSOCKET_H_
#define _IPWORKS_WEBSOCKET_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//AuthSchemes
#define AUTH_BASIC                                         0
#define AUTH_DIGEST                                        1
#define AUTH_PROPRIETARY                                   2
#define AUTH_NONE                                          3
#define AUTH_NTLM                                          4
#define AUTH_NEGOTIATE                                     5
#define AUTH_OAUTH                                         6

//DataFormats
#define DF_AUTOMATIC                                       0
#define DF_TEXT                                            1
#define DF_BINARY                                          2
#define DF_PING                                            9
#define DF_PONG                                            10

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TFollowRedirects
#define FR_NEVER                                           0
#define FR_ALWAYS                                          1
#define FR_SAME_SCHEME                                     2

//ProxySSLTypes
#define PS_AUTOMATIC                                       0
#define PS_ALWAYS                                          1
#define PS_NEVER                                           2
#define PS_TUNNEL                                          3

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


extern "C" void* IPWORKS_CALL IPWorks_WebSocket_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_WebSocket_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_WebSocket_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} WebSocketConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} WebSocketConnectionStatusEventParams;

typedef struct {
  int DataFormat;
  const char* Text;
  int EOM;
  int lenText;
  int reserved;
} WebSocketDataInEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} WebSocketDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} WebSocketErrorEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} WebSocketHeaderEventParams;

typedef struct {
  int reserved;
} WebSocketReadyToSendEventParams;

typedef struct {
  const char* Location;
  int Accept;
  int reserved;
} WebSocketRedirectEventParams;

typedef struct {
  const char* Name;
  const char* Value;
  const char* Expires;
  const char* Domain;
  const char* Path;
  int Secure;
  int reserved;
} WebSocketSetCookieEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} WebSocketSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} WebSocketSSLStatusEventParams;



class WebSocket {
  
  public: //events
  
    virtual int FireConnected(WebSocketConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(WebSocketConnectionStatusEventParams *e) {return 0;}
    virtual int FireDataIn(WebSocketDataInEventParams *e) {return 0;}
    virtual int FireDisconnected(WebSocketDisconnectedEventParams *e) {return 0;}
    virtual int FireError(WebSocketErrorEventParams *e) {return 0;}
    virtual int FireHeader(WebSocketHeaderEventParams *e) {return 0;}
    virtual int FireReadyToSend(WebSocketReadyToSendEventParams *e) {return 0;}
    virtual int FireRedirect(WebSocketRedirectEventParams *e) {return 0;}
    virtual int FireSetCookie(WebSocketSetCookieEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(WebSocketSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(WebSocketSSLStatusEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL WebSocketEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((WebSocket*)lpObj)->WebSocketEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            WebSocketConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebSocket*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            WebSocketConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((WebSocket*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            WebSocketDataInEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[1]),  0};
            ret_code = ((WebSocket*)lpObj)->FireDataIn(&e);
            break;
         }
         case 4: {
            WebSocketDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebSocket*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 5: {
            WebSocketErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebSocket*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            WebSocketHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebSocket*)lpObj)->FireHeader(&e);
            break;
         }
         case 7: {
            WebSocketReadyToSendEventParams e = { 0};
            ret_code = ((WebSocket*)lpObj)->FireReadyToSend(&e);
            break;
         }
         case 8: {
            WebSocketRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = ((WebSocket*)lpObj)->FireRedirect(&e);
            param[1] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 9: {
            WebSocketSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = ((WebSocket*)lpObj)->FireSetCookie(&e);
            break;
         }
         case 10: {
            WebSocketSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((WebSocket*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 11: {
            WebSocketSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((WebSocket*)lpObj)->FireSSLStatus(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int WebSocketEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    WebSocket(char *lpOemKey = (char*)IPWORKS_OEMKEY_20) {
      m_pObj = IPWorks_WebSocket_Create(WebSocketEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~WebSocket() {
      IPWorks_WebSocket_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_WebSocket_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_WebSocket_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_WebSocket_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_WebSocket_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_WebSocket_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetAcceptData() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAcceptData(int bAcceptData) {
      void* val = (void*)IPW64CAST(bAcceptData);
      return IPWorks_WebSocket_Set(m_pObj, 1, 0, val, 0);
    }
    inline char* GetAuthorization() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorization(const char *lpAuthorization) {
      return IPWorks_WebSocket_Set(m_pObj, 2, 0, (void*)lpAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_WebSocket_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetBytesSent() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }

    inline int GetConnected() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_WebSocket_Set(m_pObj, 5, 0, val, 0);
    }
    inline int GetCookieCount() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_WebSocket_Set(m_pObj, 6, 0, val, 0);
    }
    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_WebSocket_Get(m_pObj, 7, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_WebSocket_Get(m_pObj, 8, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_WebSocket_Get(m_pObj, 9, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieName(int iCookieIndex, const char *lpCookieName) {
      return IPWorks_WebSocket_Set(m_pObj, 9, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_WebSocket_Get(m_pObj, 10, iCookieIndex, 0);
      return (char*)val;
    }


    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_WebSocket_Get(m_pObj, 11, iCookieIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_WebSocket_Get(m_pObj, 12, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieValue(int iCookieIndex, const char *lpCookieValue) {
      return IPWorks_WebSocket_Set(m_pObj, 12, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline int GetDataFormat() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }
    inline int SetDataFormat(int iDataFormat) {
      void* val = (void*)IPW64CAST(iDataFormat);
      return IPWorks_WebSocket_Set(m_pObj, 13, 0, val, 0);
    }

    inline int SetDataToSend(const char *lpDataToSend, int lenDataToSend) {
      return IPWorks_WebSocket_Set(m_pObj, 14, 0, (void*)lpDataToSend, lenDataToSend);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_WebSocket_Set(m_pObj, 15, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_WebSocket_Set(m_pObj, 16, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_WebSocket_Set(m_pObj, 17, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_WebSocket_Set(m_pObj, 18, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 19, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_WebSocket_Set(m_pObj, 19, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_WebSocket_Set(m_pObj, 20, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_WebSocket_Set(m_pObj, 21, 0, val, 0);
    }
    inline char* GetLocalHost() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_WebSocket_Set(m_pObj, 22, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetOrigin() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }

    inline int SetOrigin(const char *lpOrigin) {
      return IPWorks_WebSocket_Set(m_pObj, 23, 0, (void*)lpOrigin, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_WebSocket_Set(m_pObj, 24, 0, (void*)lpOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 25, 0, 0);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_WebSocket_Get(m_pObj, 26, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_WebSocket_Get(m_pObj, 27, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_WebSocket_Set(m_pObj, 28, 0, (void*)lpPassword, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 29, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_WebSocket_Set(m_pObj, 29, 0, val, 0);
    }
    inline int GetProxyAutoDetect() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 30, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_WebSocket_Set(m_pObj, 30, 0, val, 0);
    }
    inline char* GetProxyPassword() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 31, 0, 0);
      return (char*)val;
    }

    inline int SetProxyPassword(const char *lpProxyPassword) {
      return IPWorks_WebSocket_Set(m_pObj, 31, 0, (void*)lpProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 32, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyPort(int lProxyPort) {
      void* val = (void*)IPW64CAST(lProxyPort);
      return IPWorks_WebSocket_Set(m_pObj, 32, 0, val, 0);
    }
    inline char* GetProxyServer() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 33, 0, 0);
      return (char*)val;
    }

    inline int SetProxyServer(const char *lpProxyServer) {
      return IPWorks_WebSocket_Set(m_pObj, 33, 0, (void*)lpProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 34, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_WebSocket_Set(m_pObj, 34, 0, val, 0);
    }
    inline char* GetProxyUser() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 35, 0, 0);
      return (char*)val;
    }

    inline int SetProxyUser(const char *lpProxyUser) {
      return IPWorks_WebSocket_Set(m_pObj, 35, 0, (void*)lpProxyUser, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_WebSocket_Get(m_pObj, 36, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_WebSocket_Set(m_pObj, 36, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_WebSocket_Get(m_pObj, 37, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_WebSocket_Set(m_pObj, 37, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_WebSocket_Get(m_pObj, 38, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_WebSocket_Set(m_pObj, 38, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 39, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_WebSocket_Set(m_pObj, 39, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 40, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_WebSocket_Set(m_pObj, 40, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 41, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_WebSocket_Set(m_pObj, 41, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_WebSocket_Get(m_pObj, 42, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline char* GetSubProtocols() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 43, 0, 0);
      return (char*)val;
    }

    inline int SetSubProtocols(const char *lpSubProtocols) {
      return IPWorks_WebSocket_Set(m_pObj, 43, 0, (void*)lpSubProtocols, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 44, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_WebSocket_Set(m_pObj, 44, 0, val, 0);
    }
    inline char* GetTransferredHeaders() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 45, 0, 0);
      return (char*)val;
    }


    inline char* GetUser() {
      void* val = IPWorks_WebSocket_Get(m_pObj, 46, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_WebSocket_Set(m_pObj, 46, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 2, 2, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebSocket_Do(m_pObj, 3, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 4, 1, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int Send(const char* lpData, int lenData) {
      void *param[1+1] = {(void*)IPW64CAST(lpData), 0};
      int cbparam[1+1] = {lenData, 0};
      return IPWorks_WebSocket_Do(m_pObj, 10, 1, param, cbparam);
      
      
    }
    inline int SendFile(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 11, 1, param, cbparam);
      
      
    }
    inline int SendText(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 12, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebSocketConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebSocketConnectionStatusEventParamsW;

typedef struct {
  int DataFormat;
  LPWSTR Text;
  int EOM;
  int lenText;
  int reserved;
} WebSocketDataInEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebSocketDisconnectedEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} WebSocketErrorEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} WebSocketHeaderEventParamsW;

typedef struct {
  int reserved;
} WebSocketReadyToSendEventParamsW;

typedef struct {
  LPWSTR Location;
  int Accept;
  int reserved;
} WebSocketRedirectEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR Value;
  LPWSTR Expires;
  LPWSTR Domain;
  LPWSTR Path;
  int Secure;
  int reserved;
} WebSocketSetCookieEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} WebSocketSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} WebSocketSSLStatusEventParamsW;



class WebSocketW : public WebSocket {

  public: //properties
  


    inline LPWSTR GetAuthorization() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetAuthorization(LPCWSTR lpAuthorization) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+2, 0, (void*)lpAuthorization, 0);
    }









    inline LPWSTR GetCookieDomain(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+7, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieExpiration(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+8, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieName(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+9, iCookieIndex, 0);
    }

    inline int SetCookieName(int iCookieIndex, LPCWSTR lpCookieName) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+9, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline LPWSTR GetCookiePath(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+10, iCookieIndex, 0);
    }





    inline LPWSTR GetCookieValue(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+12, iCookieIndex, 0);
    }

    inline int SetCookieValue(int iCookieIndex, LPCWSTR lpCookieValue) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+12, iCookieIndex, (void*)lpCookieValue, 0);
    }





    inline int SetDataToSend(LPCWSTR lpDataToSend) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+14, 0, (void*)lpDataToSend, 0);
    }

    inline int SetDataToSendB(const char *lpDataToSend, int lenDataToSend) {
      return IPWorks_WebSocket_Set(m_pObj, 14, 0, (void*)lpDataToSend, lenDataToSend);
    }




    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+17, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+18, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+20, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+22, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetOrigin() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+23, 0, 0);
    }

    inline int SetOrigin(LPCWSTR lpOrigin) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+23, 0, (void*)lpOrigin, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetOtherHeaders(LPCWSTR lpOtherHeaders) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+24, 0, (void*)lpOtherHeaders, 0);
    }



    inline LPWSTR GetParsedHeaderField(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+26, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetParsedHeaderValue(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+27, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+28, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+28, 0, (void*)lpPassword, 0);
    }





    inline LPWSTR GetProxyPassword() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+31, 0, 0);
    }

    inline int SetProxyPassword(LPCWSTR lpProxyPassword) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+31, 0, (void*)lpProxyPassword, 0);
    }



    inline LPWSTR GetProxyServer() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+33, 0, 0);
    }

    inline int SetProxyServer(LPCWSTR lpProxyServer) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+33, 0, (void*)lpProxyServer, 0);
    }



    inline LPWSTR GetProxyUser() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+35, 0, 0);
    }

    inline int SetProxyUser(LPCWSTR lpProxyUser) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+35, 0, (void*)lpProxyUser, 0);
    }

    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+36, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+36, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_WebSocket_Get(m_pObj, 36, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_WebSocket_Set(m_pObj, 36, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+37, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+37, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_WebSocket_Get(m_pObj, 37, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_WebSocket_Set(m_pObj, 37, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+38, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+38, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_WebSocket_Get(m_pObj, 38, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_WebSocket_Set(m_pObj, 38, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+39, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+39, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+41, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+41, 0, (void*)lpSSLCertSubject, 0);
    }

    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+42, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_WebSocket_Get(m_pObj, 42, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline LPWSTR GetSubProtocols() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+43, 0, 0);
    }

    inline int SetSubProtocols(LPCWSTR lpSubProtocols) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+43, 0, (void*)lpSubProtocols, 0);
    }



    inline LPWSTR GetTransferredHeaders() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+45, 0, 0);
    }



    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_WebSocket_Get(m_pObj, 10000+46, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_WebSocket_Set(m_pObj, 10000+46, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnected(WebSocketConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(WebSocketConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDataIn(WebSocketDataInEventParamsW *e) {return 0;}
    virtual int FireDisconnected(WebSocketDisconnectedEventParamsW *e) {return 0;}
    virtual int FireError(WebSocketErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(WebSocketHeaderEventParamsW *e) {return 0;}
    virtual int FireReadyToSend(WebSocketReadyToSendEventParamsW *e) {return 0;}
    virtual int FireRedirect(WebSocketRedirectEventParamsW *e) {return 0;}
    virtual int FireSetCookie(WebSocketSetCookieEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(WebSocketSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(WebSocketSSLStatusEventParamsW *e) {return 0;}


  protected:
  
    virtual int WebSocketEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            WebSocketConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            WebSocketConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            WebSocketDataInEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[1]),  0};
            ret_code = FireDataIn(&e);
            break;
         }
         case 4: {
            WebSocketDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 5: {
            WebSocketErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            WebSocketHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 7: {
            WebSocketReadyToSendEventParamsW e = { 0};
            ret_code = FireReadyToSend(&e);
            break;
         }
         case 8: {
            WebSocketRedirectEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = FireRedirect(&e);
            param[1] = (void*)(e.Accept);
            break;
         }
         case 9: {
            WebSocketSetCookieEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = FireSetCookie(&e);
            break;
         }
         case 10: {
            WebSocketSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 11: {
            WebSocketSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(WebSocketConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(WebSocketConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDataIn(WebSocketDataInEventParams *e) {return -10000;}
    virtual int FireDisconnected(WebSocketDisconnectedEventParams *e) {return -10000;}
    virtual int FireError(WebSocketErrorEventParams *e) {return -10000;}
    virtual int FireHeader(WebSocketHeaderEventParams *e) {return -10000;}
    virtual int FireReadyToSend(WebSocketReadyToSendEventParams *e) {return -10000;}
    virtual int FireRedirect(WebSocketRedirectEventParams *e) {return -10000;}
    virtual int FireSetCookie(WebSocketSetCookieEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(WebSocketSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(WebSocketSSLStatusEventParams *e) {return -10000;}

  public: //methods

    inline int AddCookie(LPWSTR lpszCookieName, LPWSTR lpszCookieValue) {
      void *param[2+1] = {(void*)lpszCookieName, (void*)lpszCookieValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 10000+2, 2, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebSocket_Do(m_pObj, 10000+3, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 10000+4, 1, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int Send(LPWSTR lpData, int lenData) {
      void *param[1+1] = {(void*)lpData, 0};
      int cbparam[1+1] = {lenData, 0};
      return IPWorks_WebSocket_Do(m_pObj, 10000+10, 1, param, cbparam);
      
    }
    inline int SendFile(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 10000+11, 1, param, cbparam);
      
    }
    inline int SendText(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 10000+12, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_WEBSOCKET_H_




