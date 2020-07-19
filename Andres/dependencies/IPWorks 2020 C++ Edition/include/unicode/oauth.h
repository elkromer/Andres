/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_OAUTH_H_
#define _IPWORKS_OAUTH_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//TOAuthClientProfile
#define CF_APPLICATION                                     0
#define CF_WEB_SERVER                                      1
#define CF_DEVICE                                          2
#define CF_MOBILE                                          3
#define CF_BROWSER                                         4
#define CF_JWT                                             5

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TFollowRedirects
#define FR_NEVER                                           0
#define FR_ALWAYS                                          1
#define FR_SAME_SCHEME                                     2

//TGrantType
#define OGT_AUTHORIZATION_CODE                             0
#define OGT_IMPLICIT                                       1
#define OGT_PASSWORD                                       2
#define OGT_CLIENT_CREDENTIALS                             3

//AuthSchemes
#define AUTH_BASIC                                         0
#define AUTH_DIGEST                                        1
#define AUTH_PROPRIETARY                                   2
#define AUTH_NONE                                          3
#define AUTH_NTLM                                          4
#define AUTH_NEGOTIATE                                     5

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


extern "C" void* IPWORKS_CALL IPWorks_OAuth_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_OAuth_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_OAuth_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_OAuth_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} OAuthConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} OAuthConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} OAuthDisconnectedEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} OAuthEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} OAuthErrorEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} OAuthHeaderEventParams;

typedef struct {
  LPWSTR URL;
  LPWSTR Command;
  INT reserved;
} OAuthLaunchBrowserEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} OAuthLogEventParams;

typedef struct {
  LPCWSTR Location;
  BOOL Accept;
  INT reserved;
} OAuthRedirectEventParams;

typedef struct {
  LPCWSTR URLPath;
  LPCWSTR QueryString;
  LPWSTR ResponseHeaders;
  LPWSTR ResponseBody;
  INT reserved;
} OAuthReturnURLEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR Value;
  LPCWSTR Expires;
  LPCWSTR Domain;
  LPCWSTR Path;
  BOOL Secure;
  INT reserved;
} OAuthSetCookieEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} OAuthSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} OAuthSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} OAuthStartTransferEventParams;

typedef struct {
  LPCWSTR HTTPVersion;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} OAuthStatusEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  INT reserved;
} OAuthTransferEventParams;


class OAuth {
  public: // Events
    virtual INT FireConnected(OAuthConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(OAuthConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(OAuthDisconnectedEventParams *e) {return 0;}
    virtual INT FireEndTransfer(OAuthEndTransferEventParams *e) {return 0;}
    virtual INT FireError(OAuthErrorEventParams *e) {return 0;}
    virtual INT FireHeader(OAuthHeaderEventParams *e) {return 0;}
    virtual INT FireLaunchBrowser(OAuthLaunchBrowserEventParams *e) {return 0;}
    virtual INT FireLog(OAuthLogEventParams *e) {return 0;}
    virtual INT FireRedirect(OAuthRedirectEventParams *e) {return 0;}
    virtual INT FireReturnURL(OAuthReturnURLEventParams *e) {return 0;}
    virtual INT FireSetCookie(OAuthSetCookieEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(OAuthSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(OAuthSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(OAuthStartTransferEventParams *e) {return 0;}
    virtual INT FireStatus(OAuthStatusEventParams *e) {return 0;}
    virtual INT FireTransfer(OAuthTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL OAuthEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          OAuthConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((OAuth*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          OAuthConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((OAuth*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          OAuthDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((OAuth*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          OAuthEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((OAuth*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          OAuthErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((OAuth*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          OAuthHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((OAuth*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          OAuthLaunchBrowserEventParams e = {(LPWSTR)IPWorks_EvtStr(param[0], 0, NULL, 2), (LPWSTR)IPWorks_EvtStr(param[1], 0, NULL, 2), 0};
          ret_code = ((OAuth*)lpObj)->FireLaunchBrowser(&e);
          IPWorks_EvtStr(param[0], 1, (void*)e.URL, 2);
          IPWorks_EvtStr(param[1], 1, (void*)e.Command, 2);
          break;
        }
        case 8: {
          OAuthLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((OAuth*)lpObj)->FireLog(&e);
          break;
        }
        case 9: {
          OAuthRedirectEventParams e = {(LPWSTR)param[0], (BOOL)param[1], 0};
          ret_code = ((OAuth*)lpObj)->FireRedirect(&e);
          param[1] = (LPVOID)e.Accept;
          break;
        }
        case 10: {
          OAuthReturnURLEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)IPWorks_EvtStr(param[2], 0, NULL, 2), (LPWSTR)IPWorks_EvtStr(param[3], 0, NULL, 2), 0};
          ret_code = ((OAuth*)lpObj)->FireReturnURL(&e);
          IPWorks_EvtStr(param[2], 1, (void*)e.ResponseHeaders, 2);
          IPWorks_EvtStr(param[3], 1, (void*)e.ResponseBody, 2);
          break;
        }
        case 11: {
          OAuthSetCookieEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((OAuth*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 12: {
          OAuthSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((OAuth*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 13: {
          OAuthSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((OAuth*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 14: {
          OAuthStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((OAuth*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 15: {
          OAuthStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((OAuth*)lpObj)->FireStatus(&e);
          break;
        }
        case 16: {
          OAuthTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], 0};
          ret_code = ((OAuth*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    OAuth(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_75) {
      m_pObj = IPWorks_OAuth_Create(OAuthEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~OAuth() {
      IPWorks_OAuth_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_OAuth_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_OAuth_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_OAuth_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_OAuth_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_OAuth_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAccessToken() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAccessToken(LPCWSTR lpszAccessToken) {
      return IPWorks_OAuth_Set(m_pObj, 1+10000, 0, (LPVOID)lpszAccessToken, 0);
    }

    inline LPWSTR GetAuthorizationCode() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorizationCode(LPCWSTR lpszAuthorizationCode) {
      return IPWorks_OAuth_Set(m_pObj, 2+10000, 0, (LPVOID)lpszAuthorizationCode, 0);
    }

    inline LPWSTR GetAuthorizationScope() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorizationScope(LPCWSTR lpszAuthorizationScope) {
      return IPWorks_OAuth_Set(m_pObj, 3+10000, 0, (LPVOID)lpszAuthorizationScope, 0);
    }

    inline LPWSTR GetClientId() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetClientId(LPCWSTR lpszClientId) {
      return IPWorks_OAuth_Set(m_pObj, 4+10000, 0, (LPVOID)lpszClientId, 0);
    }

    inline INT GetClientProfile() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 5, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetClientProfile(INT iClientProfile) {
      LPVOID val = (LPVOID)(iClientProfile);
      return IPWorks_OAuth_Set(m_pObj, 5, 0, val, 0);
    }

    inline LPWSTR GetClientSecret() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetClientSecret(LPCWSTR lpszClientSecret) {
      return IPWorks_OAuth_Set(m_pObj, 6+10000, 0, (LPVOID)lpszClientSecret, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 7, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_OAuth_Set(m_pObj, 7, 0, val, 0);
    }

    inline INT GetCookieCount() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 8, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCookieCount(INT iCookieCount) {
      LPVOID val = (LPVOID)(iCookieCount);
      return IPWorks_OAuth_Set(m_pObj, 8, 0, val, 0);
    }

    inline LPWSTR GetCookieDomain(INT iCookieIndex) {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 9+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieExpiration(INT iCookieIndex) {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 10+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieName(INT iCookieIndex) {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 11+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieName(INT iCookieIndex, LPCWSTR lpszCookieName) {
      return IPWorks_OAuth_Set(m_pObj, 11+10000, iCookieIndex, (LPVOID)lpszCookieName, 0);
    }

    inline LPWSTR GetCookiePath(INT iCookieIndex) {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 12+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCookieSecure(INT iCookieIndex) {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 13, iCookieIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCookieValue(INT iCookieIndex) {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 14+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieValue(INT iCookieIndex, LPCWSTR lpszCookieValue) {
      return IPWorks_OAuth_Set(m_pObj, 14+10000, iCookieIndex, (LPVOID)lpszCookieValue, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 15, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_OAuth_Set(m_pObj, 15, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 16, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_OAuth_Set(m_pObj, 16, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_OAuth_Set(m_pObj, 17+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_OAuth_Set(m_pObj, 18+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 19, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_OAuth_Set(m_pObj, 19, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_OAuth_Set(m_pObj, 20+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline INT GetFollowRedirects() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 21, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFollowRedirects(INT iFollowRedirects) {
      LPVOID val = (LPVOID)(iFollowRedirects);
      return IPWorks_OAuth_Set(m_pObj, 21, 0, val, 0);
    }

    inline INT GetGrantType() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 22, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetGrantType(INT iGrantType) {
      LPVOID val = (LPVOID)(iGrantType);
      return IPWorks_OAuth_Set(m_pObj, 22, 0, val, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 23, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_OAuth_Set(m_pObj, 24+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_OAuth_Set(m_pObj, 25+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline INT GetParamCount() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 26, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetParamCount(INT iParamCount) {
      LPVOID val = (LPVOID)(iParamCount);
      return IPWorks_OAuth_Set(m_pObj, 26, 0, val, 0);
    }

    inline LPWSTR GetParamName(INT iParamIndex) {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 27+10000, iParamIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetParamName(INT iParamIndex, LPCWSTR lpszParamName) {
      return IPWorks_OAuth_Set(m_pObj, 27+10000, iParamIndex, (LPVOID)lpszParamName, 0);
    }

    inline LPWSTR GetParamValue(INT iParamIndex) {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 28+10000, iParamIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetParamValue(INT iParamIndex, LPCWSTR lpszParamValue) {
      return IPWorks_OAuth_Set(m_pObj, 28+10000, iParamIndex, (LPVOID)lpszParamValue, 0);
    }

    inline INT GetProxyAuthScheme() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 29, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyAuthScheme(INT iProxyAuthScheme) {
      LPVOID val = (LPVOID)(iProxyAuthScheme);
      return IPWorks_OAuth_Set(m_pObj, 29, 0, val, 0);
    }

    inline BOOL GetProxyAutoDetect() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 30, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetProxyAutoDetect(BOOL bProxyAutoDetect) {
      LPVOID val = (LPVOID)(bProxyAutoDetect);
      return IPWorks_OAuth_Set(m_pObj, 30, 0, val, 0);
    }

    inline LPWSTR GetProxyPassword() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyPassword(LPCWSTR lpszProxyPassword) {
      return IPWorks_OAuth_Set(m_pObj, 31+10000, 0, (LPVOID)lpszProxyPassword, 0);
    }

    inline INT GetProxyPort() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 32, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyPort(INT iProxyPort) {
      LPVOID val = (LPVOID)(iProxyPort);
      return IPWorks_OAuth_Set(m_pObj, 32, 0, val, 0);
    }

    inline LPWSTR GetProxyServer() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 33+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyServer(LPCWSTR lpszProxyServer) {
      return IPWorks_OAuth_Set(m_pObj, 33+10000, 0, (LPVOID)lpszProxyServer, 0);
    }

    inline INT GetProxySSL() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 34, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxySSL(INT iProxySSL) {
      LPVOID val = (LPVOID)(iProxySSL);
      return IPWorks_OAuth_Set(m_pObj, 34, 0, val, 0);
    }

    inline LPWSTR GetProxyUser() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 35+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyUser(LPCWSTR lpszProxyUser) {
      return IPWorks_OAuth_Set(m_pObj, 35+10000, 0, (LPVOID)lpszProxyUser, 0);
    }

    inline LPWSTR GetRefreshToken() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 36+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRefreshToken(LPCWSTR lpszRefreshToken) {
      return IPWorks_OAuth_Set(m_pObj, 36+10000, 0, (LPVOID)lpszRefreshToken, 0);
    }

    inline LPWSTR GetReturnURL() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 37+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReturnURL(LPCWSTR lpszReturnURL) {
      return IPWorks_OAuth_Set(m_pObj, 37+10000, 0, (LPVOID)lpszReturnURL, 0);
    }

    inline LPWSTR GetServerAuthURL() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 38+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetServerAuthURL(LPCWSTR lpszServerAuthURL) {
      return IPWorks_OAuth_Set(m_pObj, 38+10000, 0, (LPVOID)lpszServerAuthURL, 0);
    }

    inline LPWSTR GetServerTokenURL() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 39+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetServerTokenURL(LPCWSTR lpszServerTokenURL) {
      return IPWorks_OAuth_Set(m_pObj, 39+10000, 0, (LPVOID)lpszServerTokenURL, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_OAuth_Get(m_pObj, 40, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_OAuth_Set(m_pObj, 40, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_OAuth_Get(m_pObj, 41, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_OAuth_Set(m_pObj, 41, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_OAuth_Get(m_pObj, 42, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_OAuth_Set(m_pObj, 42, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 43+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_OAuth_Set(m_pObj, 43+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 44, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_OAuth_Set(m_pObj, 44, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 45+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_OAuth_Set(m_pObj, 45+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_OAuth_Get(m_pObj, 46, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 47, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_OAuth_Set(m_pObj, 47, 0, val, 0);
    }

    inline INT GetTransferredData(LPSTR &lpTransferredData, INT &lenTransferredData) {
      lpTransferredData = (LPSTR)IPWorks_OAuth_Get(m_pObj, 48, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline LPWSTR GetTransferredHeaders() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 49+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetWebServerPort() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 50, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetWebServerPort(INT iWebServerPort) {
      LPVOID val = (LPVOID)(iWebServerPort);
      return IPWorks_OAuth_Set(m_pObj, 50, 0, val, 0);
    }

    inline INT GetWebServerSSLCertStore(LPSTR &lpWebServerSSLCertStore, INT &lenWebServerSSLCertStore) {
      lpWebServerSSLCertStore = (LPSTR)IPWorks_OAuth_Get(m_pObj, 51, 0, &lenWebServerSSLCertStore, NULL);
      return lpWebServerSSLCertStore ? 0 : lenWebServerSSLCertStore;
    }
    inline INT SetWebServerSSLCertStore(LPCSTR lpWebServerSSLCertStore, INT lenWebServerSSLCertStore) {
      return IPWorks_OAuth_Set(m_pObj, 51, 0, (LPVOID)lpWebServerSSLCertStore, lenWebServerSSLCertStore);
    }

    inline LPWSTR GetWebServerSSLCertStorePassword() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 52+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetWebServerSSLCertStorePassword(LPCWSTR lpszWebServerSSLCertStorePassword) {
      return IPWorks_OAuth_Set(m_pObj, 52+10000, 0, (LPVOID)lpszWebServerSSLCertStorePassword, 0);
    }

    inline INT GetWebServerSSLCertStoreType() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 53, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetWebServerSSLCertStoreType(INT iWebServerSSLCertStoreType) {
      LPVOID val = (LPVOID)(iWebServerSSLCertStoreType);
      return IPWorks_OAuth_Set(m_pObj, 53, 0, val, 0);
    }

    inline LPWSTR GetWebServerSSLCertSubject() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 54+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetWebServerSSLCertSubject(LPCWSTR lpszWebServerSSLCertSubject) {
      return IPWorks_OAuth_Set(m_pObj, 54+10000, 0, (LPVOID)lpszWebServerSSLCertSubject, 0);
    }

    inline BOOL GetWebServerSSLEnabled() {
      LPVOID val = IPWorks_OAuth_Get(m_pObj, 55, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetWebServerSSLEnabled(BOOL bWebServerSSLEnabled) {
      LPVOID val = (LPVOID)(bWebServerSSLEnabled);
      return IPWorks_OAuth_Set(m_pObj, 55, 0, val, 0);
    }

  public: // Methods
    inline INT AddCookie(LPCWSTR lpszCookieName, LPCWSTR lpszCookieValue) {
      LPVOID param[2+1] = {(LPVOID)lpszCookieName, (LPVOID)lpszCookieValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_OAuth_Do(m_pObj, 2+10000, 2, param, cbparam, NULL);
    }

    inline INT AddParam(LPCWSTR lpszParamName, LPCWSTR lpszParamValue) {
      LPVOID param[2+1] = {(LPVOID)lpszParamName, (LPVOID)lpszParamValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_OAuth_Do(m_pObj, 3+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_OAuth_Do(m_pObj, 4+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR GetAuthorization() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      IPWorks_OAuth_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
      return (LPWSTR)param[0];
    }

    inline LPWSTR GetAuthorizationURL() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      IPWorks_OAuth_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
      return (LPWSTR)param[0];
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT StartWebServer() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT StopWebServer() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 11+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_OAUTH_H_
