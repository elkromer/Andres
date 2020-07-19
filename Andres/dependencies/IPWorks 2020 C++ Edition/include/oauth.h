/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_OAuth_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_OAuth_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_OAuth_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} OAuthConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} OAuthConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} OAuthDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} OAuthEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} OAuthErrorEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} OAuthHeaderEventParams;

typedef struct {
  char *URL;
  char *Command;
  int reserved;
} OAuthLaunchBrowserEventParams;

typedef struct {
  int LogLevel;
  const char *Message;
  const char *LogType;
  int reserved;
} OAuthLogEventParams;

typedef struct {
  const char *Location;
  int Accept;
  int reserved;
} OAuthRedirectEventParams;

typedef struct {
  const char *URLPath;
  const char *QueryString;
  char *ResponseHeaders;
  char *ResponseBody;
  int reserved;
} OAuthReturnURLEventParams;

typedef struct {
  const char *Name;
  const char *Value;
  const char *Expires;
  const char *Domain;
  const char *Path;
  int Secure;
  int reserved;
} OAuthSetCookieEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} OAuthSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} OAuthSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} OAuthStartTransferEventParams;

typedef struct {
  const char *HTTPVersion;
  int StatusCode;
  const char *Description;
  int reserved;
} OAuthStatusEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int reserved;
} OAuthTransferEventParams;


class OAuth {
  public: // Events
    virtual int FireConnected(OAuthConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(OAuthConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(OAuthDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(OAuthEndTransferEventParams *e) {return 0;}
    virtual int FireError(OAuthErrorEventParams *e) {return 0;}
    virtual int FireHeader(OAuthHeaderEventParams *e) {return 0;}
    virtual int FireLaunchBrowser(OAuthLaunchBrowserEventParams *e) {return 0;}
    virtual int FireLog(OAuthLogEventParams *e) {return 0;}
    virtual int FireRedirect(OAuthRedirectEventParams *e) {return 0;}
    virtual int FireReturnURL(OAuthReturnURLEventParams *e) {return 0;}
    virtual int FireSetCookie(OAuthSetCookieEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(OAuthSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(OAuthSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(OAuthStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(OAuthStatusEventParams *e) {return 0;}
    virtual int FireTransfer(OAuthTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL OAuthEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          OAuthConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((OAuth*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          OAuthConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((OAuth*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          OAuthDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((OAuth*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          OAuthEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((OAuth*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          OAuthErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((OAuth*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          OAuthHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((OAuth*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          OAuthLaunchBrowserEventParams e = {(char*)IPWorks_EvtStr(param[0], 0, NULL, 1), (char*)IPWorks_EvtStr(param[1], 0, NULL, 1), 0};
          ret_code = ((OAuth*)lpObj)->FireLaunchBrowser(&e);
          IPWorks_EvtStr(param[0], 1, (void*)e.URL, 1);
          IPWorks_EvtStr(param[1], 1, (void*)e.Command, 1);
          break;
        }
        case 8: {
          OAuthLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((OAuth*)lpObj)->FireLog(&e);
          break;
        }
        case 9: {
          OAuthRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), 0};
          ret_code = ((OAuth*)lpObj)->FireRedirect(&e);
          param[1] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 10: {
          OAuthReturnURLEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPWorks_EvtStr(param[2], 0, NULL, 1), (char*)IPWorks_EvtStr(param[3], 0, NULL, 1), 0};
          ret_code = ((OAuth*)lpObj)->FireReturnURL(&e);
          IPWorks_EvtStr(param[2], 1, (void*)e.ResponseHeaders, 1);
          IPWorks_EvtStr(param[3], 1, (void*)e.ResponseBody, 1);
          break;
        }
        case 11: {
          OAuthSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), 0};
          ret_code = ((OAuth*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 12: {
          OAuthSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((OAuth*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 13: {
          OAuthSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((OAuth*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 14: {
          OAuthStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((OAuth*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 15: {
          OAuthStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((OAuth*)lpObj)->FireStatus(&e);
          break;
        }
        case 16: {
          OAuthTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), 0};
          ret_code = ((OAuth*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    OAuth(char *lpOemKey = (char*)IPWORKS_OEMKEY_75) {
      m_pObj = IPWorks_OAuth_Create(OAuthEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~OAuth() {
      IPWorks_OAuth_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_OAuth_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_OAuth_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_OAuth_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_OAuth_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_OAuth_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetAccessToken() {
      void* val = IPWorks_OAuth_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAccessToken(const char* lpszAccessToken) {
      return IPWorks_OAuth_Set(m_pObj, 1, 0, (void*)lpszAccessToken, 0);
    }

    inline char* GetAuthorizationCode() {
      void* val = IPWorks_OAuth_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthorizationCode(const char* lpszAuthorizationCode) {
      return IPWorks_OAuth_Set(m_pObj, 2, 0, (void*)lpszAuthorizationCode, 0);
    }

    inline char* GetAuthorizationScope() {
      void* val = IPWorks_OAuth_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthorizationScope(const char* lpszAuthorizationScope) {
      return IPWorks_OAuth_Set(m_pObj, 3, 0, (void*)lpszAuthorizationScope, 0);
    }

    inline char* GetClientId() {
      void* val = IPWorks_OAuth_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetClientId(const char* lpszClientId) {
      return IPWorks_OAuth_Set(m_pObj, 4, 0, (void*)lpszClientId, 0);
    }

    inline int GetClientProfile() {
      void* val = IPWorks_OAuth_Get(m_pObj, 5, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetClientProfile(int iClientProfile) {
      void* val = (void*)IPW64CAST(iClientProfile);
      return IPWorks_OAuth_Set(m_pObj, 5, 0, val, 0);
    }

    inline char* GetClientSecret() {
      void* val = IPWorks_OAuth_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetClientSecret(const char* lpszClientSecret) {
      return IPWorks_OAuth_Set(m_pObj, 6, 0, (void*)lpszClientSecret, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_OAuth_Get(m_pObj, 7, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_OAuth_Set(m_pObj, 7, 0, val, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_OAuth_Get(m_pObj, 8, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_OAuth_Set(m_pObj, 8, 0, val, 0);
    }

    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 9, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 10, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 11, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieName(int iCookieIndex, const char* lpszCookieName) {
      return IPWorks_OAuth_Set(m_pObj, 11, iCookieIndex, (void*)lpszCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 12, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 13, iCookieIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 14, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieValue(int iCookieIndex, const char* lpszCookieValue) {
      return IPWorks_OAuth_Set(m_pObj, 14, iCookieIndex, (void*)lpszCookieValue, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_OAuth_Get(m_pObj, 15, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_OAuth_Set(m_pObj, 15, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_OAuth_Get(m_pObj, 16, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_OAuth_Set(m_pObj, 16, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_OAuth_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_OAuth_Set(m_pObj, 17, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_OAuth_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_OAuth_Set(m_pObj, 18, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_OAuth_Get(m_pObj, 19, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_OAuth_Set(m_pObj, 19, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_OAuth_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_OAuth_Set(m_pObj, 20, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_OAuth_Get(m_pObj, 21, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_OAuth_Set(m_pObj, 21, 0, val, 0);
    }

    inline int GetGrantType() {
      void* val = IPWorks_OAuth_Get(m_pObj, 22, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetGrantType(int iGrantType) {
      void* val = (void*)IPW64CAST(iGrantType);
      return IPWorks_OAuth_Set(m_pObj, 22, 0, val, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_OAuth_Get(m_pObj, 23, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_OAuth_Get(m_pObj, 24, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_OAuth_Set(m_pObj, 24, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_OAuth_Get(m_pObj, 25, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherHeaders(const char* lpszOtherHeaders) {
      return IPWorks_OAuth_Set(m_pObj, 25, 0, (void*)lpszOtherHeaders, 0);
    }

    inline int GetParamCount() {
      void* val = IPWorks_OAuth_Get(m_pObj, 26, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetParamCount(int iParamCount) {
      void* val = (void*)IPW64CAST(iParamCount);
      return IPWorks_OAuth_Set(m_pObj, 26, 0, val, 0);
    }

    inline char* GetParamName(int iParamIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 27, iParamIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetParamName(int iParamIndex, const char* lpszParamName) {
      return IPWorks_OAuth_Set(m_pObj, 27, iParamIndex, (void*)lpszParamName, 0);
    }

    inline char* GetParamValue(int iParamIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 28, iParamIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetParamValue(int iParamIndex, const char* lpszParamValue) {
      return IPWorks_OAuth_Set(m_pObj, 28, iParamIndex, (void*)lpszParamValue, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_OAuth_Get(m_pObj, 29, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_OAuth_Set(m_pObj, 29, 0, val, 0);
    }

    inline int GetProxyAutoDetect() {
      void* val = IPWorks_OAuth_Get(m_pObj, 30, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_OAuth_Set(m_pObj, 30, 0, val, 0);
    }

    inline char* GetProxyPassword() {
      void* val = IPWorks_OAuth_Get(m_pObj, 31, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyPassword(const char* lpszProxyPassword) {
      return IPWorks_OAuth_Set(m_pObj, 31, 0, (void*)lpszProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_OAuth_Get(m_pObj, 32, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyPort(int iProxyPort) {
      void* val = (void*)IPW64CAST(iProxyPort);
      return IPWorks_OAuth_Set(m_pObj, 32, 0, val, 0);
    }

    inline char* GetProxyServer() {
      void* val = IPWorks_OAuth_Get(m_pObj, 33, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyServer(const char* lpszProxyServer) {
      return IPWorks_OAuth_Set(m_pObj, 33, 0, (void*)lpszProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_OAuth_Get(m_pObj, 34, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_OAuth_Set(m_pObj, 34, 0, val, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_OAuth_Get(m_pObj, 35, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyUser(const char* lpszProxyUser) {
      return IPWorks_OAuth_Set(m_pObj, 35, 0, (void*)lpszProxyUser, 0);
    }

    inline char* GetRefreshToken() {
      void* val = IPWorks_OAuth_Get(m_pObj, 36, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRefreshToken(const char* lpszRefreshToken) {
      return IPWorks_OAuth_Set(m_pObj, 36, 0, (void*)lpszRefreshToken, 0);
    }

    inline char* GetReturnURL() {
      void* val = IPWorks_OAuth_Get(m_pObj, 37, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReturnURL(const char* lpszReturnURL) {
      return IPWorks_OAuth_Set(m_pObj, 37, 0, (void*)lpszReturnURL, 0);
    }

    inline char* GetServerAuthURL() {
      void* val = IPWorks_OAuth_Get(m_pObj, 38, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetServerAuthURL(const char* lpszServerAuthURL) {
      return IPWorks_OAuth_Set(m_pObj, 38, 0, (void*)lpszServerAuthURL, 0);
    }

    inline char* GetServerTokenURL() {
      void* val = IPWorks_OAuth_Get(m_pObj, 39, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetServerTokenURL(const char* lpszServerTokenURL) {
      return IPWorks_OAuth_Set(m_pObj, 39, 0, (void*)lpszServerTokenURL, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_OAuth_Get(m_pObj, 40, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_OAuth_Set(m_pObj, 40, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_OAuth_Get(m_pObj, 41, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_OAuth_Set(m_pObj, 41, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_OAuth_Get(m_pObj, 42, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_OAuth_Set(m_pObj, 42, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_OAuth_Get(m_pObj, 43, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_OAuth_Set(m_pObj, 43, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_OAuth_Get(m_pObj, 44, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_OAuth_Set(m_pObj, 44, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_OAuth_Get(m_pObj, 45, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_OAuth_Set(m_pObj, 45, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_OAuth_Get(m_pObj, 46, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetTimeout() {
      void* val = IPWorks_OAuth_Get(m_pObj, 47, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_OAuth_Set(m_pObj, 47, 0, val, 0);
    }

    inline int GetTransferredData(char* &lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_OAuth_Get(m_pObj, 48, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_OAuth_Get(m_pObj, 49, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetWebServerPort() {
      void* val = IPWorks_OAuth_Get(m_pObj, 50, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetWebServerPort(int iWebServerPort) {
      void* val = (void*)IPW64CAST(iWebServerPort);
      return IPWorks_OAuth_Set(m_pObj, 50, 0, val, 0);
    }

    inline int GetWebServerSSLCertStore(char* &lpWebServerSSLCertStore, int &lenWebServerSSLCertStore) {
      lpWebServerSSLCertStore = (char*)IPWorks_OAuth_Get(m_pObj, 51, 0, &lenWebServerSSLCertStore, NULL);
      return lpWebServerSSLCertStore ? 0 : lenWebServerSSLCertStore;
    }
    inline int SetWebServerSSLCertStore(const char* lpWebServerSSLCertStore, int lenWebServerSSLCertStore) {
      return IPWorks_OAuth_Set(m_pObj, 51, 0, (void*)lpWebServerSSLCertStore, lenWebServerSSLCertStore);
    }

    inline char* GetWebServerSSLCertStorePassword() {
      void* val = IPWorks_OAuth_Get(m_pObj, 52, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetWebServerSSLCertStorePassword(const char* lpszWebServerSSLCertStorePassword) {
      return IPWorks_OAuth_Set(m_pObj, 52, 0, (void*)lpszWebServerSSLCertStorePassword, 0);
    }

    inline int GetWebServerSSLCertStoreType() {
      void* val = IPWorks_OAuth_Get(m_pObj, 53, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetWebServerSSLCertStoreType(int iWebServerSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iWebServerSSLCertStoreType);
      return IPWorks_OAuth_Set(m_pObj, 53, 0, val, 0);
    }

    inline char* GetWebServerSSLCertSubject() {
      void* val = IPWorks_OAuth_Get(m_pObj, 54, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetWebServerSSLCertSubject(const char* lpszWebServerSSLCertSubject) {
      return IPWorks_OAuth_Set(m_pObj, 54, 0, (void*)lpszWebServerSSLCertSubject, 0);
    }

    inline int GetWebServerSSLEnabled() {
      void* val = IPWorks_OAuth_Get(m_pObj, 55, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetWebServerSSLEnabled(int bWebServerSSLEnabled) {
      void* val = (void*)IPW64CAST(bWebServerSSLEnabled);
      return IPWorks_OAuth_Set(m_pObj, 55, 0, val, 0);
    }

  public: // Methods
    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OAuth_Do(m_pObj, 2, 2, param, cbparam, NULL);
    }

    inline int AddParam(const char* lpszParamName, const char* lpszParamValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszParamName), (void*)IPW64CAST(lpszParamValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OAuth_Do(m_pObj, 3, 2, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OAuth_Do(m_pObj, 4, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline char* GetAuthorization() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_OAuth_Do(m_pObj, 6, 0, param, cbparam, NULL);
      return (char*)IPW64CAST(param[0]);
    }

    inline char* GetAuthorizationURL() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_OAuth_Do(m_pObj, 7, 0, param, cbparam, NULL);
      return (char*)IPW64CAST(param[0]);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int StartWebServer() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int StopWebServer() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 11, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_OAUTH_H_
