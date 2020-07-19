/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

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
#define CST_SECURITY_KEY                                   20
#define CST_AUTO                                           99


extern "C" void* IPWORKS_CALL IPWorks_WebSocket_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_WebSocket_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_WebSocket_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_WebSocket_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_WebSocket_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebSocketConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebSocketConnectionStatusEventParams;

typedef struct {
  INT DataFormat;
  LPCSTR Text;
  INT lenText;
  BOOL EOM;
  INT reserved;
} WebSocketDataInEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebSocketDisconnectedEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} WebSocketErrorEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} WebSocketHeaderEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} WebSocketLogEventParams;

typedef struct {
  INT reserved;
} WebSocketReadyToSendEventParams;

typedef struct {
  LPCWSTR Location;
  BOOL Accept;
  INT reserved;
} WebSocketRedirectEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR Value;
  LPCWSTR Expires;
  LPCWSTR Domain;
  LPCWSTR Path;
  BOOL Secure;
  INT reserved;
} WebSocketSetCookieEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} WebSocketSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} WebSocketSSLStatusEventParams;


class WebSocket {
  public: // Events
    virtual INT FireConnected(WebSocketConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(WebSocketConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDataIn(WebSocketDataInEventParams *e) {return 0;}
    virtual INT FireDisconnected(WebSocketDisconnectedEventParams *e) {return 0;}
    virtual INT FireError(WebSocketErrorEventParams *e) {return 0;}
    virtual INT FireHeader(WebSocketHeaderEventParams *e) {return 0;}
    virtual INT FireLog(WebSocketLogEventParams *e) {return 0;}
    virtual INT FireReadyToSend(WebSocketReadyToSendEventParams *e) {return 0;}
    virtual INT FireRedirect(WebSocketRedirectEventParams *e) {return 0;}
    virtual INT FireSetCookie(WebSocketSetCookieEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(WebSocketSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(WebSocketSSLStatusEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL WebSocketEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          WebSocketConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebSocket*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          WebSocketConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((WebSocket*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          WebSocketDataInEventParams e = {(INT)param[0], (LPSTR)param[1], (INT)cbparam[1], (BOOL)param[2], 0};
          ret_code = ((WebSocket*)lpObj)->FireDataIn(&e);
          break;
        }
        case 4: {
          WebSocketDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebSocket*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 5: {
          WebSocketErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebSocket*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          WebSocketHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebSocket*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          WebSocketLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((WebSocket*)lpObj)->FireLog(&e);
          break;
        }
        case 8: {
          WebSocketReadyToSendEventParams e = {0};
          ret_code = ((WebSocket*)lpObj)->FireReadyToSend(&e);
          break;
        }
        case 9: {
          WebSocketRedirectEventParams e = {(LPWSTR)param[0], (BOOL)param[1], 0};
          ret_code = ((WebSocket*)lpObj)->FireRedirect(&e);
          param[1] = (LPVOID)e.Accept;
          break;
        }
        case 10: {
          WebSocketSetCookieEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((WebSocket*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 11: {
          WebSocketSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((WebSocket*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 12: {
          WebSocketSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((WebSocket*)lpObj)->FireSSLStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    WebSocket(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_20) {
      m_pObj = IPWorks_WebSocket_Create(WebSocketEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~WebSocket() {
      IPWorks_WebSocket_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_WebSocket_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_WebSocket_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_WebSocket_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_WebSocket_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_WebSocket_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetAcceptData() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetAcceptData(BOOL bAcceptData) {
      LPVOID val = (LPVOID)(bAcceptData);
      return IPWorks_WebSocket_Set(m_pObj, 1, 0, val, 0);
    }

    inline LPWSTR GetAuthorization() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorization(LPCWSTR lpszAuthorization) {
      return IPWorks_WebSocket_Set(m_pObj, 2+10000, 0, (LPVOID)lpszAuthorization, 0);
    }

    inline INT GetAuthScheme() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 3, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthScheme(INT iAuthScheme) {
      LPVOID val = (LPVOID)(iAuthScheme);
      return IPWorks_WebSocket_Set(m_pObj, 3, 0, val, 0);
    }

    inline INT GetBytesSent() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 5, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_WebSocket_Set(m_pObj, 5, 0, val, 0);
    }

    inline INT GetCookieCount() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCookieCount(INT iCookieCount) {
      LPVOID val = (LPVOID)(iCookieCount);
      return IPWorks_WebSocket_Set(m_pObj, 6, 0, val, 0);
    }

    inline LPWSTR GetCookieDomain(INT iCookieIndex) {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 7+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieExpiration(INT iCookieIndex) {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 8+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieName(INT iCookieIndex) {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 9+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieName(INT iCookieIndex, LPCWSTR lpszCookieName) {
      return IPWorks_WebSocket_Set(m_pObj, 9+10000, iCookieIndex, (LPVOID)lpszCookieName, 0);
    }

    inline LPWSTR GetCookiePath(INT iCookieIndex) {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 10+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCookieSecure(INT iCookieIndex) {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 11, iCookieIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCookieValue(INT iCookieIndex) {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 12+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieValue(INT iCookieIndex, LPCWSTR lpszCookieValue) {
      return IPWorks_WebSocket_Set(m_pObj, 12+10000, iCookieIndex, (LPVOID)lpszCookieValue, 0);
    }

    inline INT GetDataFormat() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 13, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetDataFormat(INT iDataFormat) {
      LPVOID val = (LPVOID)(iDataFormat);
      return IPWorks_WebSocket_Set(m_pObj, 13, 0, val, 0);
    }

    inline INT SetDataToSend(LPCSTR lpDataToSend, INT lenDataToSend) {
      return IPWorks_WebSocket_Set(m_pObj, 14, 0, (LPVOID)lpDataToSend, lenDataToSend);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 15, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_WebSocket_Set(m_pObj, 15, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 16, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_WebSocket_Set(m_pObj, 16, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_WebSocket_Set(m_pObj, 17+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_WebSocket_Set(m_pObj, 18+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 19, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_WebSocket_Set(m_pObj, 19, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_WebSocket_Set(m_pObj, 20+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline INT GetFollowRedirects() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 21, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFollowRedirects(INT iFollowRedirects) {
      LPVOID val = (LPVOID)(iFollowRedirects);
      return IPWorks_WebSocket_Set(m_pObj, 21, 0, val, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_WebSocket_Set(m_pObj, 22+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetLocalPort() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 23, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLocalPort(INT iLocalPort) {
      LPVOID val = (LPVOID)(iLocalPort);
      return IPWorks_WebSocket_Set(m_pObj, 23, 0, val, 0);
    }

    inline LPWSTR GetOrigin() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOrigin(LPCWSTR lpszOrigin) {
      return IPWorks_WebSocket_Set(m_pObj, 24+10000, 0, (LPVOID)lpszOrigin, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_WebSocket_Set(m_pObj, 25+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline INT GetParsedHeaderCount() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 26, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetParsedHeaderField(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 27+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetParsedHeaderValue(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 28+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_WebSocket_Set(m_pObj, 29+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetProxyAuthScheme() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 30, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyAuthScheme(INT iProxyAuthScheme) {
      LPVOID val = (LPVOID)(iProxyAuthScheme);
      return IPWorks_WebSocket_Set(m_pObj, 30, 0, val, 0);
    }

    inline BOOL GetProxyAutoDetect() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 31, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetProxyAutoDetect(BOOL bProxyAutoDetect) {
      LPVOID val = (LPVOID)(bProxyAutoDetect);
      return IPWorks_WebSocket_Set(m_pObj, 31, 0, val, 0);
    }

    inline LPWSTR GetProxyPassword() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 32+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyPassword(LPCWSTR lpszProxyPassword) {
      return IPWorks_WebSocket_Set(m_pObj, 32+10000, 0, (LPVOID)lpszProxyPassword, 0);
    }

    inline INT GetProxyPort() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 33, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyPort(INT iProxyPort) {
      LPVOID val = (LPVOID)(iProxyPort);
      return IPWorks_WebSocket_Set(m_pObj, 33, 0, val, 0);
    }

    inline LPWSTR GetProxyServer() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 34+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyServer(LPCWSTR lpszProxyServer) {
      return IPWorks_WebSocket_Set(m_pObj, 34+10000, 0, (LPVOID)lpszProxyServer, 0);
    }

    inline INT GetProxySSL() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 35, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxySSL(INT iProxySSL) {
      LPVOID val = (LPVOID)(iProxySSL);
      return IPWorks_WebSocket_Set(m_pObj, 35, 0, val, 0);
    }

    inline LPWSTR GetProxyUser() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 36+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyUser(LPCWSTR lpszProxyUser) {
      return IPWorks_WebSocket_Set(m_pObj, 36+10000, 0, (LPVOID)lpszProxyUser, 0);
    }

    inline BOOL GetReadyToSend() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 37, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_WebSocket_Get(m_pObj, 38, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_WebSocket_Set(m_pObj, 38, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_WebSocket_Get(m_pObj, 39, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_WebSocket_Set(m_pObj, 39, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_WebSocket_Get(m_pObj, 40, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_WebSocket_Set(m_pObj, 40, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 41+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_WebSocket_Set(m_pObj, 41+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 42, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_WebSocket_Set(m_pObj, 42, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 43+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_WebSocket_Set(m_pObj, 43+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_WebSocket_Get(m_pObj, 44, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline LPWSTR GetSubProtocols() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 45+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSubProtocols(LPCWSTR lpszSubProtocols) {
      return IPWorks_WebSocket_Set(m_pObj, 45+10000, 0, (LPVOID)lpszSubProtocols, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 46, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_WebSocket_Set(m_pObj, 46, 0, val, 0);
    }

    inline LPWSTR GetTransferredHeaders() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 47+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_WebSocket_Get(m_pObj, 48+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_WebSocket_Set(m_pObj, 48+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline INT AddCookie(LPCWSTR lpszCookieName, LPCWSTR lpszCookieValue) {
      LPVOID param[2+1] = {(LPVOID)lpszCookieName, (LPVOID)lpszCookieValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 2+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_WebSocket_Do(m_pObj, 3+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Connect(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 4+10000, 1, param, cbparam, NULL);
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT Ping() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT ResetHeaders() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebSocket_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT Send(LPCSTR lpData, INT lenData) {
      LPVOID param[1+1] = {(LPVOID)lpData, 0};
      INT cbparam[1+1] = {lenData, 0};
      return IPWorks_WebSocket_Do(m_pObj, 11+10000, 1, param, cbparam, NULL);
    }

    inline INT SendFile(LPCWSTR lpszFileName) {
      LPVOID param[1+1] = {(LPVOID)lpszFileName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 12+10000, 1, param, cbparam, NULL);
    }

    inline INT SendText(LPCWSTR lpszText) {
      LPVOID param[1+1] = {(LPVOID)lpszText, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebSocket_Do(m_pObj, 13+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_WEBSOCKET_H_
