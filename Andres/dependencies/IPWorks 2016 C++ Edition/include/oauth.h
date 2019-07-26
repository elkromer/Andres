/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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


extern "C" void* IPWORKS_CALL IPWorks_OAuth_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_OAuth_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_OAuth_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OAuth_GetLastErrorCode(void *lpObj);
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
  const char* Description;
  int reserved;
} OAuthConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} OAuthConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} OAuthDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} OAuthEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} OAuthErrorEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} OAuthHeaderEventParams;

typedef struct {
  const char* URL;
  const char* Command;
  int reserved;
} OAuthLaunchBrowserEventParams;

typedef struct {
  int LogLevel;
  const char* Message;
  const char* LogType;
  int reserved;
} OAuthLogEventParams;

typedef struct {
  const char* Location;
  int Accept;
  int reserved;
} OAuthRedirectEventParams;

typedef struct {
  const char* URLPath;
  const char* QueryString;
  const char* ResponseHeaders;
  const char* ResponseBody;
  int reserved;
} OAuthReturnURLEventParams;

typedef struct {
  const char* Name;
  const char* Value;
  const char* Expires;
  const char* Domain;
  const char* Path;
  int Secure;
  int reserved;
} OAuthSetCookieEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} OAuthSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} OAuthSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} OAuthStartTransferEventParams;

typedef struct {
  const char* HTTPVersion;
  int StatusCode;
  const char* Description;
  int reserved;
} OAuthStatusEventParams;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  const char* Text;
  int lenText;
  int reserved;
} OAuthTransferEventParams;



class OAuth {
  
  public: //events
  
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
      if (event_id > 10000) return ((OAuth*)lpObj)->OAuthEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            OAuthConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((OAuth*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            OAuthConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((OAuth*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            OAuthDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((OAuth*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            OAuthEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((OAuth*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 5: {
            OAuthErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((OAuth*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            OAuthHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((OAuth*)lpObj)->FireHeader(&e);
            break;
         }
         case 7: {
            OAuthLaunchBrowserEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((OAuth*)lpObj)->FireLaunchBrowser(&e);
            param[0] = (void*)IPW64CAST(e.URL);
            param[1] = (void*)IPW64CAST(e.Command);
            break;
         }
         case 8: {
            OAuthLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((OAuth*)lpObj)->FireLog(&e);
            break;
         }
         case 9: {
            OAuthRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = ((OAuth*)lpObj)->FireRedirect(&e);
            param[1] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 10: {
            OAuthReturnURLEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]),  0};
            ret_code = ((OAuth*)lpObj)->FireReturnURL(&e);
            param[2] = (void*)IPW64CAST(e.ResponseHeaders);
            param[3] = (void*)IPW64CAST(e.ResponseBody);
            break;
         }
         case 11: {
            OAuthSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = ((OAuth*)lpObj)->FireSetCookie(&e);
            break;
         }
         case 12: {
            OAuthSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((OAuth*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 13: {
            OAuthSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((OAuth*)lpObj)->FireSSLStatus(&e);
            break;
         }
         case 14: {
            OAuthStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((OAuth*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 15: {
            OAuthStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((OAuth*)lpObj)->FireStatus(&e);
            break;
         }
         case 16: {
            OAuthTransferEventParams e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((OAuth*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int OAuthEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    OAuth(char *lpOemKey = (char*)IPWORKS_OEMKEY_75) {
      m_pObj = IPWorks_OAuth_Create(OAuthEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~OAuth() {
      IPWorks_OAuth_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_OAuth_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_OAuth_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_OAuth_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_OAuth_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_OAuth_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetAccessToken() {
      void* val = IPWorks_OAuth_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetAccessToken(const char *lpAccessToken) {
      return IPWorks_OAuth_Set(m_pObj, 1, 0, (void*)lpAccessToken, 0);
    }

    inline char* GetAuthorizationCode() {
      void* val = IPWorks_OAuth_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorizationCode(const char *lpAuthorizationCode) {
      return IPWorks_OAuth_Set(m_pObj, 2, 0, (void*)lpAuthorizationCode, 0);
    }

    inline char* GetAuthorizationScope() {
      void* val = IPWorks_OAuth_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorizationScope(const char *lpAuthorizationScope) {
      return IPWorks_OAuth_Set(m_pObj, 3, 0, (void*)lpAuthorizationScope, 0);
    }

    inline char* GetClientId() {
      void* val = IPWorks_OAuth_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetClientId(const char *lpClientId) {
      return IPWorks_OAuth_Set(m_pObj, 4, 0, (void*)lpClientId, 0);
    }

    inline int GetClientProfile() {
      void* val = IPWorks_OAuth_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetClientProfile(int iClientProfile) {
      void* val = (void*)IPW64CAST(iClientProfile);
      return IPWorks_OAuth_Set(m_pObj, 5, 0, val, 0);
    }
    inline char* GetClientSecret() {
      void* val = IPWorks_OAuth_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetClientSecret(const char *lpClientSecret) {
      return IPWorks_OAuth_Set(m_pObj, 6, 0, (void*)lpClientSecret, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_OAuth_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_OAuth_Set(m_pObj, 7, 0, val, 0);
    }
    inline int GetCookieCount() {
      void* val = IPWorks_OAuth_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_OAuth_Set(m_pObj, 8, 0, val, 0);
    }
    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 9, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 10, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 11, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieName(int iCookieIndex, const char *lpCookieName) {
      return IPWorks_OAuth_Set(m_pObj, 11, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 12, iCookieIndex, 0);
      return (char*)val;
    }


    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 13, iCookieIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 14, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieValue(int iCookieIndex, const char *lpCookieValue) {
      return IPWorks_OAuth_Set(m_pObj, 14, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_OAuth_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_OAuth_Set(m_pObj, 15, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_OAuth_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_OAuth_Set(m_pObj, 16, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_OAuth_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_OAuth_Set(m_pObj, 17, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_OAuth_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_OAuth_Set(m_pObj, 18, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_OAuth_Get(m_pObj, 19, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_OAuth_Set(m_pObj, 19, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_OAuth_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_OAuth_Set(m_pObj, 20, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_OAuth_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_OAuth_Set(m_pObj, 21, 0, val, 0);
    }
    inline int GetIdle() {
      void* val = IPWorks_OAuth_Get(m_pObj, 22, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_OAuth_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_OAuth_Set(m_pObj, 23, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_OAuth_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_OAuth_Set(m_pObj, 24, 0, (void*)lpOtherHeaders, 0);
    }

    inline int GetParamCount() {
      void* val = IPWorks_OAuth_Get(m_pObj, 25, 0, 0);
      return (int)(long)val;
    }
    inline int SetParamCount(int iParamCount) {
      void* val = (void*)IPW64CAST(iParamCount);
      return IPWorks_OAuth_Set(m_pObj, 25, 0, val, 0);
    }
    inline char* GetParamName(int iParamIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 26, iParamIndex, 0);
      return (char*)val;
    }

    inline int SetParamName(int iParamIndex, const char *lpParamName) {
      return IPWorks_OAuth_Set(m_pObj, 26, iParamIndex, (void*)lpParamName, 0);
    }

    inline char* GetParamValue(int iParamIndex) {
      void* val = IPWorks_OAuth_Get(m_pObj, 27, iParamIndex, 0);
      return (char*)val;
    }

    inline int SetParamValue(int iParamIndex, const char *lpParamValue) {
      return IPWorks_OAuth_Set(m_pObj, 27, iParamIndex, (void*)lpParamValue, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_OAuth_Get(m_pObj, 28, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_OAuth_Set(m_pObj, 28, 0, val, 0);
    }
    inline int GetProxyAutoDetect() {
      void* val = IPWorks_OAuth_Get(m_pObj, 29, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_OAuth_Set(m_pObj, 29, 0, val, 0);
    }
    inline char* GetProxyPassword() {
      void* val = IPWorks_OAuth_Get(m_pObj, 30, 0, 0);
      return (char*)val;
    }

    inline int SetProxyPassword(const char *lpProxyPassword) {
      return IPWorks_OAuth_Set(m_pObj, 30, 0, (void*)lpProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_OAuth_Get(m_pObj, 31, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyPort(int lProxyPort) {
      void* val = (void*)IPW64CAST(lProxyPort);
      return IPWorks_OAuth_Set(m_pObj, 31, 0, val, 0);
    }
    inline char* GetProxyServer() {
      void* val = IPWorks_OAuth_Get(m_pObj, 32, 0, 0);
      return (char*)val;
    }

    inline int SetProxyServer(const char *lpProxyServer) {
      return IPWorks_OAuth_Set(m_pObj, 32, 0, (void*)lpProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_OAuth_Get(m_pObj, 33, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_OAuth_Set(m_pObj, 33, 0, val, 0);
    }
    inline char* GetProxyUser() {
      void* val = IPWorks_OAuth_Get(m_pObj, 34, 0, 0);
      return (char*)val;
    }

    inline int SetProxyUser(const char *lpProxyUser) {
      return IPWorks_OAuth_Set(m_pObj, 34, 0, (void*)lpProxyUser, 0);
    }

    inline char* GetRefreshToken() {
      void* val = IPWorks_OAuth_Get(m_pObj, 35, 0, 0);
      return (char*)val;
    }

    inline int SetRefreshToken(const char *lpRefreshToken) {
      return IPWorks_OAuth_Set(m_pObj, 35, 0, (void*)lpRefreshToken, 0);
    }

    inline char* GetReturnURL() {
      void* val = IPWorks_OAuth_Get(m_pObj, 36, 0, 0);
      return (char*)val;
    }

    inline int SetReturnURL(const char *lpReturnURL) {
      return IPWorks_OAuth_Set(m_pObj, 36, 0, (void*)lpReturnURL, 0);
    }

    inline char* GetServerAuthURL() {
      void* val = IPWorks_OAuth_Get(m_pObj, 37, 0, 0);
      return (char*)val;
    }

    inline int SetServerAuthURL(const char *lpServerAuthURL) {
      return IPWorks_OAuth_Set(m_pObj, 37, 0, (void*)lpServerAuthURL, 0);
    }

    inline char* GetServerTokenURL() {
      void* val = IPWorks_OAuth_Get(m_pObj, 38, 0, 0);
      return (char*)val;
    }

    inline int SetServerTokenURL(const char *lpServerTokenURL) {
      return IPWorks_OAuth_Set(m_pObj, 38, 0, (void*)lpServerTokenURL, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_OAuth_Get(m_pObj, 39, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_OAuth_Set(m_pObj, 39, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_OAuth_Get(m_pObj, 40, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_OAuth_Set(m_pObj, 40, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_OAuth_Get(m_pObj, 41, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_OAuth_Set(m_pObj, 41, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_OAuth_Get(m_pObj, 42, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_OAuth_Set(m_pObj, 42, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_OAuth_Get(m_pObj, 43, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_OAuth_Set(m_pObj, 43, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_OAuth_Get(m_pObj, 44, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_OAuth_Set(m_pObj, 44, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_OAuth_Get(m_pObj, 45, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline int GetTimeout() {
      void* val = IPWorks_OAuth_Get(m_pObj, 46, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_OAuth_Set(m_pObj, 46, 0, val, 0);
    }
    inline int GetTransferredData(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_OAuth_Get(m_pObj, 47, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }


    inline char* GetTransferredHeaders() {
      void* val = IPWorks_OAuth_Get(m_pObj, 48, 0, 0);
      return (char*)val;
    }



  public: //methods

    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OAuth_Do(m_pObj, 2, 2, param, cbparam);
      
      
    }
    inline int AddParam(const char* lpszParamName, const char* lpszParamValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszParamName), (void*)IPW64CAST(lpszParamValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OAuth_Do(m_pObj, 3, 2, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OAuth_Do(m_pObj, 4, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline char* GetAuthorization() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_OAuth_Do(m_pObj, 6, 0, param, cbparam);
      
      return (char*)IPW64CAST(param[0]);
    }
    inline char* GetAuthorizationURL() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_OAuth_Do(m_pObj, 7, 0, param, cbparam);
      
      return (char*)IPW64CAST(param[0]);
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int StartWebServer() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int StopWebServer() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} OAuthConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} OAuthConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} OAuthDisconnectedEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} OAuthEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} OAuthErrorEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} OAuthHeaderEventParamsW;

typedef struct {
  LPWSTR URL;
  LPWSTR Command;
  int reserved;
} OAuthLaunchBrowserEventParamsW;

typedef struct {
  int LogLevel;
  LPWSTR Message;
  LPWSTR LogType;
  int reserved;
} OAuthLogEventParamsW;

typedef struct {
  LPWSTR Location;
  int Accept;
  int reserved;
} OAuthRedirectEventParamsW;

typedef struct {
  LPWSTR URLPath;
  LPWSTR QueryString;
  LPWSTR ResponseHeaders;
  LPWSTR ResponseBody;
  int reserved;
} OAuthReturnURLEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR Value;
  LPWSTR Expires;
  LPWSTR Domain;
  LPWSTR Path;
  int Secure;
  int reserved;
} OAuthSetCookieEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} OAuthSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} OAuthSSLStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} OAuthStartTransferEventParamsW;

typedef struct {
  LPWSTR HTTPVersion;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} OAuthStatusEventParamsW;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int lenText;
  int reserved;
} OAuthTransferEventParamsW;



class OAuthW : public OAuth {

  public: //properties
  
    inline LPWSTR GetAccessToken() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetAccessToken(LPCWSTR lpAccessToken) {
      return IPWorks_OAuth_Set(m_pObj, 10000+1, 0, (void*)lpAccessToken, 0);
    }

    inline LPWSTR GetAuthorizationCode() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetAuthorizationCode(LPCWSTR lpAuthorizationCode) {
      return IPWorks_OAuth_Set(m_pObj, 10000+2, 0, (void*)lpAuthorizationCode, 0);
    }

    inline LPWSTR GetAuthorizationScope() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetAuthorizationScope(LPCWSTR lpAuthorizationScope) {
      return IPWorks_OAuth_Set(m_pObj, 10000+3, 0, (void*)lpAuthorizationScope, 0);
    }

    inline LPWSTR GetClientId() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetClientId(LPCWSTR lpClientId) {
      return IPWorks_OAuth_Set(m_pObj, 10000+4, 0, (void*)lpClientId, 0);
    }



    inline LPWSTR GetClientSecret() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetClientSecret(LPCWSTR lpClientSecret) {
      return IPWorks_OAuth_Set(m_pObj, 10000+6, 0, (void*)lpClientSecret, 0);
    }





    inline LPWSTR GetCookieDomain(int iCookieIndex) {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+9, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieExpiration(int iCookieIndex) {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+10, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieName(int iCookieIndex) {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+11, iCookieIndex, 0);
    }

    inline int SetCookieName(int iCookieIndex, LPCWSTR lpCookieName) {
      return IPWorks_OAuth_Set(m_pObj, 10000+11, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline LPWSTR GetCookiePath(int iCookieIndex) {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+12, iCookieIndex, 0);
    }





    inline LPWSTR GetCookieValue(int iCookieIndex) {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+14, iCookieIndex, 0);
    }

    inline int SetCookieValue(int iCookieIndex, LPCWSTR lpCookieValue) {
      return IPWorks_OAuth_Set(m_pObj, 10000+14, iCookieIndex, (void*)lpCookieValue, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_OAuth_Set(m_pObj, 10000+17, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_OAuth_Set(m_pObj, 10000+18, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_OAuth_Set(m_pObj, 10000+20, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+23, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_OAuth_Set(m_pObj, 10000+23, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetOtherHeaders(LPCWSTR lpOtherHeaders) {
      return IPWorks_OAuth_Set(m_pObj, 10000+24, 0, (void*)lpOtherHeaders, 0);
    }



    inline LPWSTR GetParamName(int iParamIndex) {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+26, iParamIndex, 0);
    }

    inline int SetParamName(int iParamIndex, LPCWSTR lpParamName) {
      return IPWorks_OAuth_Set(m_pObj, 10000+26, iParamIndex, (void*)lpParamName, 0);
    }

    inline LPWSTR GetParamValue(int iParamIndex) {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+27, iParamIndex, 0);
    }

    inline int SetParamValue(int iParamIndex, LPCWSTR lpParamValue) {
      return IPWorks_OAuth_Set(m_pObj, 10000+27, iParamIndex, (void*)lpParamValue, 0);
    }





    inline LPWSTR GetProxyPassword() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+30, 0, 0);
    }

    inline int SetProxyPassword(LPCWSTR lpProxyPassword) {
      return IPWorks_OAuth_Set(m_pObj, 10000+30, 0, (void*)lpProxyPassword, 0);
    }



    inline LPWSTR GetProxyServer() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+32, 0, 0);
    }

    inline int SetProxyServer(LPCWSTR lpProxyServer) {
      return IPWorks_OAuth_Set(m_pObj, 10000+32, 0, (void*)lpProxyServer, 0);
    }



    inline LPWSTR GetProxyUser() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+34, 0, 0);
    }

    inline int SetProxyUser(LPCWSTR lpProxyUser) {
      return IPWorks_OAuth_Set(m_pObj, 10000+34, 0, (void*)lpProxyUser, 0);
    }

    inline LPWSTR GetRefreshToken() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+35, 0, 0);
    }

    inline int SetRefreshToken(LPCWSTR lpRefreshToken) {
      return IPWorks_OAuth_Set(m_pObj, 10000+35, 0, (void*)lpRefreshToken, 0);
    }

    inline LPWSTR GetReturnURL() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+36, 0, 0);
    }

    inline int SetReturnURL(LPCWSTR lpReturnURL) {
      return IPWorks_OAuth_Set(m_pObj, 10000+36, 0, (void*)lpReturnURL, 0);
    }

    inline LPWSTR GetServerAuthURL() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+37, 0, 0);
    }

    inline int SetServerAuthURL(LPCWSTR lpServerAuthURL) {
      return IPWorks_OAuth_Set(m_pObj, 10000+37, 0, (void*)lpServerAuthURL, 0);
    }

    inline LPWSTR GetServerTokenURL() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+38, 0, 0);
    }

    inline int SetServerTokenURL(LPCWSTR lpServerTokenURL) {
      return IPWorks_OAuth_Set(m_pObj, 10000+38, 0, (void*)lpServerTokenURL, 0);
    }

    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+39, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_OAuth_Set(m_pObj, 10000+39, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_OAuth_Get(m_pObj, 39, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_OAuth_Set(m_pObj, 39, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+40, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_OAuth_Set(m_pObj, 10000+40, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_OAuth_Get(m_pObj, 40, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_OAuth_Set(m_pObj, 40, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+41, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_OAuth_Set(m_pObj, 10000+41, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_OAuth_Get(m_pObj, 41, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_OAuth_Set(m_pObj, 41, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+42, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_OAuth_Set(m_pObj, 10000+42, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+44, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_OAuth_Set(m_pObj, 10000+44, 0, (void*)lpSSLCertSubject, 0);
    }

    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+45, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_OAuth_Get(m_pObj, 45, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }



    inline LPWSTR GetTransferredData() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+47, 0, 0);
    }


    inline int GetTransferredDataB(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_OAuth_Get(m_pObj, 47, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline LPWSTR GetTransferredHeaders() {
      return (LPWSTR)IPWorks_OAuth_Get(m_pObj, 10000+48, 0, 0);
    }





  public: //events
  
    virtual int FireConnected(OAuthConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(OAuthConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(OAuthDisconnectedEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(OAuthEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(OAuthErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(OAuthHeaderEventParamsW *e) {return 0;}
    virtual int FireLaunchBrowser(OAuthLaunchBrowserEventParamsW *e) {return 0;}
    virtual int FireLog(OAuthLogEventParamsW *e) {return 0;}
    virtual int FireRedirect(OAuthRedirectEventParamsW *e) {return 0;}
    virtual int FireReturnURL(OAuthReturnURLEventParamsW *e) {return 0;}
    virtual int FireSetCookie(OAuthSetCookieEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(OAuthSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(OAuthSSLStatusEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(OAuthStartTransferEventParamsW *e) {return 0;}
    virtual int FireStatus(OAuthStatusEventParamsW *e) {return 0;}
    virtual int FireTransfer(OAuthTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int OAuthEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            OAuthConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            OAuthConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            OAuthDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            OAuthEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 5: {
            OAuthErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            OAuthHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 7: {
            OAuthLaunchBrowserEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireLaunchBrowser(&e);
            param[0] = (void*)(e.URL);
            param[1] = (void*)(e.Command);
            break;
         }
         case 8: {
            OAuthLogEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireLog(&e);
            break;
         }
         case 9: {
            OAuthRedirectEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = FireRedirect(&e);
            param[1] = (void*)(e.Accept);
            break;
         }
         case 10: {
            OAuthReturnURLEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]),  0};
            ret_code = FireReturnURL(&e);
            param[2] = (void*)(e.ResponseHeaders);
            param[3] = (void*)(e.ResponseBody);
            break;
         }
         case 11: {
            OAuthSetCookieEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = FireSetCookie(&e);
            break;
         }
         case 12: {
            OAuthSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 13: {
            OAuthSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }
         case 14: {
            OAuthStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 15: {
            OAuthStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireStatus(&e);
            break;
         }
         case 16: {
            OAuthTransferEventParamsW e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(OAuthConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(OAuthConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(OAuthDisconnectedEventParams *e) {return -10000;}
    virtual int FireEndTransfer(OAuthEndTransferEventParams *e) {return -10000;}
    virtual int FireError(OAuthErrorEventParams *e) {return -10000;}
    virtual int FireHeader(OAuthHeaderEventParams *e) {return -10000;}
    virtual int FireLaunchBrowser(OAuthLaunchBrowserEventParams *e) {return -10000;}
    virtual int FireLog(OAuthLogEventParams *e) {return -10000;}
    virtual int FireRedirect(OAuthRedirectEventParams *e) {return -10000;}
    virtual int FireReturnURL(OAuthReturnURLEventParams *e) {return -10000;}
    virtual int FireSetCookie(OAuthSetCookieEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(OAuthSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(OAuthSSLStatusEventParams *e) {return -10000;}
    virtual int FireStartTransfer(OAuthStartTransferEventParams *e) {return -10000;}
    virtual int FireStatus(OAuthStatusEventParams *e) {return -10000;}
    virtual int FireTransfer(OAuthTransferEventParams *e) {return -10000;}

  public: //methods

    inline int AddCookie(LPWSTR lpszCookieName, LPWSTR lpszCookieValue) {
      void *param[2+1] = {(void*)lpszCookieName, (void*)lpszCookieValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OAuth_Do(m_pObj, 10000+2, 2, param, cbparam);
      
    }
    inline int AddParam(LPWSTR lpszParamName, LPWSTR lpszParamValue) {
      void *param[2+1] = {(void*)lpszParamName, (void*)lpszParamValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OAuth_Do(m_pObj, 10000+3, 2, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OAuth_Do(m_pObj, 10000+4, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline LPWSTR GetAuthorization() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_OAuth_Do(m_pObj, 10000+6, 0, param, cbparam);
      return (LPWSTR)IPW64CAST(param[0]);
    }
    inline LPWSTR GetAuthorizationURL() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_OAuth_Do(m_pObj, 10000+7, 0, param, cbparam);
      return (LPWSTR)IPW64CAST(param[0]);
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int StartWebServer() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int StopWebServer() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OAuth_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_OAUTH_H_




