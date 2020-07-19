/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_WEBDAV_H_
#define _IPWORKS_WEBDAV_H_

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

//TDepth
#define DP_UNSPECIFIED                                     0
#define DP_RESOURCE_ONLY                                   1
#define DP_IMMEDIATE_CHILDREN                              2
#define DP_INFINITY                                        3

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TFollowRedirects
#define FR_NEVER                                           0
#define FR_ALWAYS                                          1
#define FR_SAME_SCHEME                                     2

//DAVPropertyOperations
#define OP_NONE                                            0
#define OP_SET                                             1
#define OP_DELETE                                          2

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


extern "C" void* IPWORKS_CALL IPWorks_WebDAV_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_WebDAV_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_WebDAV_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_WebDAV_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebDAVConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebDAVConnectionStatusEventParams;

typedef struct {
  LPCWSTR ResourceURI;
  LPCWSTR DisplayName;
  LPCWSTR ContentLanguage;
  LPCWSTR ContentLength;
  LPCWSTR ContentType;
  LPCWSTR LastModified;
  INT reserved;
} WebDAVDirListEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebDAVDisconnectedEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} WebDAVEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} WebDAVErrorEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} WebDAVHeaderEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} WebDAVLogEventParams;

typedef struct {
  LPCWSTR Location;
  BOOL Accept;
  INT reserved;
} WebDAVRedirectEventParams;

typedef struct {
  LPCWSTR ResourceURI;
  LPCWSTR ResourceProperties;
  INT reserved;
} WebDAVResourcePropertiesEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR Value;
  LPCWSTR Expires;
  LPCWSTR Domain;
  LPCWSTR Path;
  BOOL Secure;
  INT reserved;
} WebDAVSetCookieEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} WebDAVSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} WebDAVSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} WebDAVStartTransferEventParams;

typedef struct {
  LPCWSTR HTTPVersion;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebDAVStatusEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  INT reserved;
} WebDAVTransferEventParams;


class WebDAV {
  public: // Events
    virtual INT FireConnected(WebDAVConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(WebDAVConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDirList(WebDAVDirListEventParams *e) {return 0;}
    virtual INT FireDisconnected(WebDAVDisconnectedEventParams *e) {return 0;}
    virtual INT FireEndTransfer(WebDAVEndTransferEventParams *e) {return 0;}
    virtual INT FireError(WebDAVErrorEventParams *e) {return 0;}
    virtual INT FireHeader(WebDAVHeaderEventParams *e) {return 0;}
    virtual INT FireLog(WebDAVLogEventParams *e) {return 0;}
    virtual INT FireRedirect(WebDAVRedirectEventParams *e) {return 0;}
    virtual INT FireResourceProperties(WebDAVResourcePropertiesEventParams *e) {return 0;}
    virtual INT FireSetCookie(WebDAVSetCookieEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(WebDAVSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(WebDAVSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(WebDAVStartTransferEventParams *e) {return 0;}
    virtual INT FireStatus(WebDAVStatusEventParams *e) {return 0;}
    virtual INT FireTransfer(WebDAVTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL WebDAVEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          WebDAVConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebDAV*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          WebDAVConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((WebDAV*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          WebDAVDirListEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (LPWSTR)param[5], 0};
          ret_code = ((WebDAV*)lpObj)->FireDirList(&e);
          break;
        }
        case 4: {
          WebDAVDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebDAV*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 5: {
          WebDAVEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((WebDAV*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 6: {
          WebDAVErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebDAV*)lpObj)->FireError(&e);
          break;
        }
        case 7: {
          WebDAVHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebDAV*)lpObj)->FireHeader(&e);
          break;
        }
        case 8: {
          WebDAVLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((WebDAV*)lpObj)->FireLog(&e);
          break;
        }
        case 9: {
          WebDAVRedirectEventParams e = {(LPWSTR)param[0], (BOOL)param[1], 0};
          ret_code = ((WebDAV*)lpObj)->FireRedirect(&e);
          param[1] = (LPVOID)e.Accept;
          break;
        }
        case 10: {
          WebDAVResourcePropertiesEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebDAV*)lpObj)->FireResourceProperties(&e);
          break;
        }
        case 11: {
          WebDAVSetCookieEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((WebDAV*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 12: {
          WebDAVSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((WebDAV*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 13: {
          WebDAVSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((WebDAV*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 14: {
          WebDAVStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((WebDAV*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 15: {
          WebDAVStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((WebDAV*)lpObj)->FireStatus(&e);
          break;
        }
        case 16: {
          WebDAVTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], 0};
          ret_code = ((WebDAV*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    WebDAV(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_61) {
      m_pObj = IPWorks_WebDAV_Create(WebDAVEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~WebDAV() {
      IPWorks_WebDAV_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_WebDAV_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_WebDAV_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_WebDAV_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_WebDAV_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_WebDAV_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAccept() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAccept(LPCWSTR lpszAccept) {
      return IPWorks_WebDAV_Set(m_pObj, 1+10000, 0, (LPVOID)lpszAccept, 0);
    }

    inline LPWSTR GetAuthorization() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorization(LPCWSTR lpszAuthorization) {
      return IPWorks_WebDAV_Set(m_pObj, 2+10000, 0, (LPVOID)lpszAuthorization, 0);
    }

    inline INT GetAuthScheme() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 3, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthScheme(INT iAuthScheme) {
      LPVOID val = (LPVOID)(iAuthScheme);
      return IPWorks_WebDAV_Set(m_pObj, 3, 0, val, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 4, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_WebDAV_Set(m_pObj, 4, 0, val, 0);
    }

    inline INT GetCookieCount() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 5, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCookieCount(INT iCookieCount) {
      LPVOID val = (LPVOID)(iCookieCount);
      return IPWorks_WebDAV_Set(m_pObj, 5, 0, val, 0);
    }

    inline LPWSTR GetCookieDomain(INT iCookieIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 6+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieExpiration(INT iCookieIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 7+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieName(INT iCookieIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 8+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieName(INT iCookieIndex, LPCWSTR lpszCookieName) {
      return IPWorks_WebDAV_Set(m_pObj, 8+10000, iCookieIndex, (LPVOID)lpszCookieName, 0);
    }

    inline LPWSTR GetCookiePath(INT iCookieIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 9+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCookieSecure(INT iCookieIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 10, iCookieIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCookieValue(INT iCookieIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 11+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieValue(INT iCookieIndex, LPCWSTR lpszCookieValue) {
      return IPWorks_WebDAV_Set(m_pObj, 11+10000, iCookieIndex, (LPVOID)lpszCookieValue, 0);
    }

    inline INT GetDepth() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 12, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetDepth(INT iDepth) {
      LPVOID val = (LPVOID)(iDepth);
      return IPWorks_WebDAV_Set(m_pObj, 12, 0, val, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 13, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_WebDAV_Set(m_pObj, 13, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 14, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_WebDAV_Set(m_pObj, 14, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_WebDAV_Set(m_pObj, 15+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 16+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 17, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_WebDAV_Set(m_pObj, 17, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_WebDAV_Set(m_pObj, 18+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline INT GetFollowRedirects() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 19, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFollowRedirects(INT iFollowRedirects) {
      LPVOID val = (LPVOID)(iFollowRedirects);
      return IPWorks_WebDAV_Set(m_pObj, 19, 0, val, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 20, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_WebDAV_Set(m_pObj, 21+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_WebDAV_Set(m_pObj, 22+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetLockOwner() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 23+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLockOwner(LPCWSTR lpszLockOwner) {
      return IPWorks_WebDAV_Set(m_pObj, 23+10000, 0, (LPVOID)lpszLockOwner, 0);
    }

    inline LPWSTR GetLockScope() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLockScope(LPCWSTR lpszLockScope) {
      return IPWorks_WebDAV_Set(m_pObj, 24+10000, 0, (LPVOID)lpszLockScope, 0);
    }

    inline INT GetLockTimeout() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 25, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLockTimeout(INT iLockTimeout) {
      LPVOID val = (LPVOID)(iLockTimeout);
      return IPWorks_WebDAV_Set(m_pObj, 25, 0, val, 0);
    }

    inline LPWSTR GetLockTokens() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLockTokens(LPCWSTR lpszLockTokens) {
      return IPWorks_WebDAV_Set(m_pObj, 26+10000, 0, (LPVOID)lpszLockTokens, 0);
    }

    inline LPWSTR GetLockType() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 27+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLockType(LPCWSTR lpszLockType) {
      return IPWorks_WebDAV_Set(m_pObj, 27+10000, 0, (LPVOID)lpszLockType, 0);
    }

    inline INT GetNamespaceCount() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 28, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetNamespaceCount(INT iNamespaceCount) {
      LPVOID val = (LPVOID)(iNamespaceCount);
      return IPWorks_WebDAV_Set(m_pObj, 28, 0, val, 0);
    }

    inline LPWSTR GetNamespacePrefix(INT iNamespaceIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 29+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNamespacePrefix(INT iNamespaceIndex, LPCWSTR lpszNamespacePrefix) {
      return IPWorks_WebDAV_Set(m_pObj, 29+10000, iNamespaceIndex, (LPVOID)lpszNamespacePrefix, 0);
    }

    inline LPWSTR GetNamespaceURI(INT iNamespaceIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 30+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNamespaceURI(INT iNamespaceIndex, LPCWSTR lpszNamespaceURI) {
      return IPWorks_WebDAV_Set(m_pObj, 30+10000, iNamespaceIndex, (LPVOID)lpszNamespaceURI, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_WebDAV_Set(m_pObj, 31+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline INT GetParsedHeaderCount() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 32, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetParsedHeaderField(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 33+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetParsedHeaderValue(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 34+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 35+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 35+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetPropertyCount() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 36, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetPropertyCount(INT iPropertyCount) {
      LPVOID val = (LPVOID)(iPropertyCount);
      return IPWorks_WebDAV_Set(m_pObj, 36, 0, val, 0);
    }

    inline LPWSTR GetPropertyAttr(INT iPropertyIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 37+10000, iPropertyIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPropertyAttr(INT iPropertyIndex, LPCWSTR lpszPropertyAttr) {
      return IPWorks_WebDAV_Set(m_pObj, 37+10000, iPropertyIndex, (LPVOID)lpszPropertyAttr, 0);
    }

    inline LPWSTR GetPropertyName(INT iPropertyIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 38+10000, iPropertyIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPropertyName(INT iPropertyIndex, LPCWSTR lpszPropertyName) {
      return IPWorks_WebDAV_Set(m_pObj, 38+10000, iPropertyIndex, (LPVOID)lpszPropertyName, 0);
    }

    inline LPWSTR GetPropertyNamespaceURI(INT iPropertyIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 39+10000, iPropertyIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPropertyNamespaceURI(INT iPropertyIndex, LPCWSTR lpszPropertyNamespaceURI) {
      return IPWorks_WebDAV_Set(m_pObj, 39+10000, iPropertyIndex, (LPVOID)lpszPropertyNamespaceURI, 0);
    }

    inline INT GetPropertyOperation(INT iPropertyIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 40, iPropertyIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetPropertyOperation(INT iPropertyIndex, INT iPropertyOperation) {
      LPVOID val = (LPVOID)(iPropertyOperation);
      return IPWorks_WebDAV_Set(m_pObj, 40, iPropertyIndex, val, 0);
    }

    inline LPWSTR GetPropertyStatus(INT iPropertyIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 41+10000, iPropertyIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPropertyValue(INT iPropertyIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 42+10000, iPropertyIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPropertyValue(INT iPropertyIndex, LPCWSTR lpszPropertyValue) {
      return IPWorks_WebDAV_Set(m_pObj, 42+10000, iPropertyIndex, (LPVOID)lpszPropertyValue, 0);
    }

    inline INT GetProxyAuthScheme() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 43, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyAuthScheme(INT iProxyAuthScheme) {
      LPVOID val = (LPVOID)(iProxyAuthScheme);
      return IPWorks_WebDAV_Set(m_pObj, 43, 0, val, 0);
    }

    inline BOOL GetProxyAutoDetect() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 44, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetProxyAutoDetect(BOOL bProxyAutoDetect) {
      LPVOID val = (LPVOID)(bProxyAutoDetect);
      return IPWorks_WebDAV_Set(m_pObj, 44, 0, val, 0);
    }

    inline LPWSTR GetProxyPassword() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 45+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyPassword(LPCWSTR lpszProxyPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 45+10000, 0, (LPVOID)lpszProxyPassword, 0);
    }

    inline INT GetProxyPort() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 46, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyPort(INT iProxyPort) {
      LPVOID val = (LPVOID)(iProxyPort);
      return IPWorks_WebDAV_Set(m_pObj, 46, 0, val, 0);
    }

    inline LPWSTR GetProxyServer() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 47+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyServer(LPCWSTR lpszProxyServer) {
      return IPWorks_WebDAV_Set(m_pObj, 47+10000, 0, (LPVOID)lpszProxyServer, 0);
    }

    inline INT GetProxySSL() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 48, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxySSL(INT iProxySSL) {
      LPVOID val = (LPVOID)(iProxySSL);
      return IPWorks_WebDAV_Set(m_pObj, 48, 0, val, 0);
    }

    inline LPWSTR GetProxyUser() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 49+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyUser(LPCWSTR lpszProxyUser) {
      return IPWorks_WebDAV_Set(m_pObj, 49+10000, 0, (LPVOID)lpszProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 50+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReferer(LPCWSTR lpszReferer) {
      return IPWorks_WebDAV_Set(m_pObj, 50+10000, 0, (LPVOID)lpszReferer, 0);
    }

    inline INT GetResourceCount() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 51, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetResourceContentLanguage(INT iResourceIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 52+10000, iResourceIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetResourceContentLength(INT iResourceIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 53+10000, iResourceIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetResourceContentType(INT iResourceIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 54+10000, iResourceIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetResourceDisplayName(INT iResourceIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 55+10000, iResourceIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetResourceLastModified(INT iResourceIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 56+10000, iResourceIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetResourceURI(INT iResourceIndex) {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 57+10000, iResourceIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_WebDAV_Get(m_pObj, 58, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_WebDAV_Set(m_pObj, 58, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_WebDAV_Get(m_pObj, 59, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_WebDAV_Set(m_pObj, 59, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_WebDAV_Get(m_pObj, 60, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_WebDAV_Set(m_pObj, 60, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 61+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_WebDAV_Set(m_pObj, 61+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 62, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_WebDAV_Set(m_pObj, 62, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 63+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_WebDAV_Set(m_pObj, 63+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_WebDAV_Get(m_pObj, 64, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline LPWSTR GetStatusLine() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 65+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 66, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_WebDAV_Set(m_pObj, 66, 0, val, 0);
    }

    inline INT GetTransferredData(LPSTR &lpTransferredData, INT &lenTransferredData) {
      lpTransferredData = (LPSTR)IPWorks_WebDAV_Get(m_pObj, 67, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline LONG64 GetTransferredDataLimit() {
      LONG64 retVal;
      IPWorks_WebDAV_Get(m_pObj, 68, 0, NULL, &retVal);
      return retVal;
    }
    inline INT SetTransferredDataLimit(LONG64 lTransferredDataLimit) {
      LPVOID val = (LPVOID)(&lTransferredDataLimit);
      return IPWorks_WebDAV_Set(m_pObj, 68, 0, val, 0);
    }

    inline LPWSTR GetTransferredHeaders() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 69+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_WebDAV_Get(m_pObj, 70+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_WebDAV_Set(m_pObj, 70+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline INT AddCookie(LPCWSTR lpszCookieName, LPCWSTR lpszCookieValue) {
      LPVOID param[2+1] = {(LPVOID)lpszCookieName, (LPVOID)lpszCookieValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 2+10000, 2, param, cbparam, NULL);
    }

    inline INT AddNamespace(LPCWSTR lpszPrefix, LPCWSTR lpszNamespaceURI) {
      LPVOID param[2+1] = {(LPVOID)lpszPrefix, (LPVOID)lpszNamespaceURI, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 3+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_WebDAV_Do(m_pObj, 4+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT CopyResource(LPCWSTR lpszSourceResourceURI, LPCWSTR lpszDestinationResourceURI) {
      LPVOID param[2+1] = {(LPVOID)lpszSourceResourceURI, (LPVOID)lpszDestinationResourceURI, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 5+10000, 2, param, cbparam, NULL);
    }

    inline INT DeleteResource(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT FindProperties(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
    }

    inline INT FindPropertyNames(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 9+10000, 1, param, cbparam, NULL);
    }

    inline LPWSTR GetProperty(LPCWSTR lpszPropertyName) {
      LPVOID param[1+1] = {(LPVOID)lpszPropertyName, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_WebDAV_Do(m_pObj, 10+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT GetResource(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 11+10000, 1, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
    }

    inline INT ListDirectory(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 13+10000, 1, param, cbparam, NULL);
    }

    inline INT LockResource(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
    }

    inline INT MakeDirectory(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 15+10000, 1, param, cbparam, NULL);
    }

    inline INT MoveResource(LPCWSTR lpszSourceResourceURI, LPCWSTR lpszDestinationResourceURI) {
      LPVOID param[2+1] = {(LPVOID)lpszSourceResourceURI, (LPVOID)lpszDestinationResourceURI, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 16+10000, 2, param, cbparam, NULL);
    }

    inline INT PatchProperties(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 17+10000, 1, param, cbparam, NULL);
    }

    inline INT PostToResource(LPCWSTR lpszResourceURI, LPCSTR lpPostData, INT lenPostData) {
      LPVOID param[2+1] = {(LPVOID)lpszResourceURI, (LPVOID)lpPostData, 0};
      INT cbparam[2+1] = {0, lenPostData, 0};
      return IPWorks_WebDAV_Do(m_pObj, 18+10000, 2, param, cbparam, NULL);
    }

    inline INT PutResource(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 19+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 20+10000, 0, param, cbparam, NULL);
    }

    inline INT SetProperty(LPCWSTR lpszPropertyName, LPCWSTR lpszPropertyValue) {
      LPVOID param[2+1] = {(LPVOID)lpszPropertyName, (LPVOID)lpszPropertyValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 22+10000, 2, param, cbparam, NULL);
    }

    inline INT UnLockResource(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 24+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_WEBDAV_H_
