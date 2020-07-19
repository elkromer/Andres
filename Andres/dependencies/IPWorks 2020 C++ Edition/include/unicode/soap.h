/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_SOAP_H_
#define _IPWORKS_SOAP_H_

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

//TValueFormat
#define VF_TEXT                                            0
#define VF_XML                                             1
#define VF_FULL_XML                                        2


extern "C" void* IPWORKS_CALL IPWorks_SOAP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SOAP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_SOAP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_SOAP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SOAPConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SOAPConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SOAPDisconnectedEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} SOAPEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} SOAPErrorEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} SOAPHeaderEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} SOAPLogEventParams;

typedef struct {
  LPCWSTR Location;
  BOOL Accept;
  INT reserved;
} SOAPRedirectEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR Value;
  LPCWSTR Expires;
  LPCWSTR Domain;
  LPCWSTR Path;
  BOOL Secure;
  INT reserved;
} SOAPSetCookieEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} SOAPSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} SOAPSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} SOAPStartTransferEventParams;

typedef struct {
  LPCWSTR HTTPVersion;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SOAPStatusEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  INT reserved;
} SOAPTransferEventParams;


class SOAP {
  public: // Events
    virtual INT FireConnected(SOAPConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(SOAPConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(SOAPDisconnectedEventParams *e) {return 0;}
    virtual INT FireEndTransfer(SOAPEndTransferEventParams *e) {return 0;}
    virtual INT FireError(SOAPErrorEventParams *e) {return 0;}
    virtual INT FireHeader(SOAPHeaderEventParams *e) {return 0;}
    virtual INT FireLog(SOAPLogEventParams *e) {return 0;}
    virtual INT FireRedirect(SOAPRedirectEventParams *e) {return 0;}
    virtual INT FireSetCookie(SOAPSetCookieEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(SOAPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(SOAPSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(SOAPStartTransferEventParams *e) {return 0;}
    virtual INT FireStatus(SOAPStatusEventParams *e) {return 0;}
    virtual INT FireTransfer(SOAPTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL SOAPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          SOAPConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((SOAP*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          SOAPConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((SOAP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          SOAPDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((SOAP*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          SOAPEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((SOAP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          SOAPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((SOAP*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          SOAPHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((SOAP*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          SOAPLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((SOAP*)lpObj)->FireLog(&e);
          break;
        }
        case 8: {
          SOAPRedirectEventParams e = {(LPWSTR)param[0], (BOOL)param[1], 0};
          ret_code = ((SOAP*)lpObj)->FireRedirect(&e);
          param[1] = (LPVOID)e.Accept;
          break;
        }
        case 9: {
          SOAPSetCookieEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((SOAP*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 10: {
          SOAPSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((SOAP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 11: {
          SOAPSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((SOAP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 12: {
          SOAPStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((SOAP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 13: {
          SOAPStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((SOAP*)lpObj)->FireStatus(&e);
          break;
        }
        case 14: {
          SOAPTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], 0};
          ret_code = ((SOAP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    SOAP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_55) {
      m_pObj = IPWorks_SOAP_Create(SOAPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~SOAP() {
      IPWorks_SOAP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_SOAP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_SOAP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_SOAP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_SOAP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_SOAP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAccept() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAccept(LPCWSTR lpszAccept) {
      return IPWorks_SOAP_Set(m_pObj, 1+10000, 0, (LPVOID)lpszAccept, 0);
    }

    inline LPWSTR GetActionURI() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetActionURI(LPCWSTR lpszActionURI) {
      return IPWorks_SOAP_Set(m_pObj, 2+10000, 0, (LPVOID)lpszActionURI, 0);
    }

    inline LPWSTR GetAuthorization() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorization(LPCWSTR lpszAuthorization) {
      return IPWorks_SOAP_Set(m_pObj, 3+10000, 0, (LPVOID)lpszAuthorization, 0);
    }

    inline INT GetAuthScheme() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthScheme(INT iAuthScheme) {
      LPVOID val = (LPVOID)(iAuthScheme);
      return IPWorks_SOAP_Set(m_pObj, 4, 0, val, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 5, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_SOAP_Set(m_pObj, 5, 0, val, 0);
    }

    inline LPWSTR GetContentType() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetContentType(LPCWSTR lpszContentType) {
      return IPWorks_SOAP_Set(m_pObj, 6+10000, 0, (LPVOID)lpszContentType, 0);
    }

    inline INT GetCookieCount() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 7, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCookieCount(INT iCookieCount) {
      LPVOID val = (LPVOID)(iCookieCount);
      return IPWorks_SOAP_Set(m_pObj, 7, 0, val, 0);
    }

    inline LPWSTR GetCookieDomain(INT iCookieIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 8+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieExpiration(INT iCookieIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 9+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieName(INT iCookieIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 10+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieName(INT iCookieIndex, LPCWSTR lpszCookieName) {
      return IPWorks_SOAP_Set(m_pObj, 10+10000, iCookieIndex, (LPVOID)lpszCookieName, 0);
    }

    inline LPWSTR GetCookiePath(INT iCookieIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 11+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCookieSecure(INT iCookieIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 12, iCookieIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCookieValue(INT iCookieIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 13+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieValue(INT iCookieIndex, LPCWSTR lpszCookieValue) {
      return IPWorks_SOAP_Set(m_pObj, 13+10000, iCookieIndex, (LPVOID)lpszCookieValue, 0);
    }

    inline LPWSTR GetFaultActor() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetFaultCode() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetFaultString() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 17, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_SOAP_Set(m_pObj, 17, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 18, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_SOAP_Set(m_pObj, 18, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_SOAP_Set(m_pObj, 19+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_SOAP_Set(m_pObj, 20+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 21, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_SOAP_Set(m_pObj, 21, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_SOAP_Set(m_pObj, 22+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline INT GetFollowRedirects() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 23, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFollowRedirects(INT iFollowRedirects) {
      LPVOID val = (LPVOID)(iFollowRedirects);
      return IPWorks_SOAP_Set(m_pObj, 23, 0, val, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 24, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetIfModifiedSince() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetIfModifiedSince(LPCWSTR lpszIfModifiedSince) {
      return IPWorks_SOAP_Set(m_pObj, 25+10000, 0, (LPVOID)lpszIfModifiedSince, 0);
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_SOAP_Set(m_pObj, 26+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 27+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_SOAP_Set(m_pObj, 27+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetMethod() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 28+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMethod(LPCWSTR lpszMethod) {
      return IPWorks_SOAP_Set(m_pObj, 28+10000, 0, (LPVOID)lpszMethod, 0);
    }

    inline LPWSTR GetMethodURI() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMethodURI(LPCWSTR lpszMethodURI) {
      return IPWorks_SOAP_Set(m_pObj, 29+10000, 0, (LPVOID)lpszMethodURI, 0);
    }

    inline INT GetNamespaceCount() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 30, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetNamespaceCount(INT iNamespaceCount) {
      LPVOID val = (LPVOID)(iNamespaceCount);
      return IPWorks_SOAP_Set(m_pObj, 30, 0, val, 0);
    }

    inline LPWSTR GetNamespacePrefix(INT iNamespaceIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 31+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNamespacePrefix(INT iNamespaceIndex, LPCWSTR lpszNamespacePrefix) {
      return IPWorks_SOAP_Set(m_pObj, 31+10000, iNamespaceIndex, (LPVOID)lpszNamespacePrefix, 0);
    }

    inline LPWSTR GetNamespaceURI(INT iNamespaceIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 32+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNamespaceURI(INT iNamespaceIndex, LPCWSTR lpszNamespaceURI) {
      return IPWorks_SOAP_Set(m_pObj, 32+10000, iNamespaceIndex, (LPVOID)lpszNamespaceURI, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 33+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_SOAP_Set(m_pObj, 33+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline INT GetParamCount() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 34, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetParamCount(INT iParamCount) {
      LPVOID val = (LPVOID)(iParamCount);
      return IPWorks_SOAP_Set(m_pObj, 34, 0, val, 0);
    }

    inline LPWSTR GetParamAttrs(INT iParamIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 35+10000, iParamIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetParamAttrs(INT iParamIndex, LPCWSTR lpszParamAttrs) {
      return IPWorks_SOAP_Set(m_pObj, 35+10000, iParamIndex, (LPVOID)lpszParamAttrs, 0);
    }

    inline LPWSTR GetParamName(INT iParamIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 36+10000, iParamIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetParamName(INT iParamIndex, LPCWSTR lpszParamName) {
      return IPWorks_SOAP_Set(m_pObj, 36+10000, iParamIndex, (LPVOID)lpszParamName, 0);
    }

    inline LPWSTR GetParamValue(INT iParamIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 37+10000, iParamIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetParamValue(INT iParamIndex, LPCWSTR lpszParamValue) {
      return IPWorks_SOAP_Set(m_pObj, 37+10000, iParamIndex, (LPVOID)lpszParamValue, 0);
    }

    inline INT GetParsedHeaderCount() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 38, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetParsedHeaderField(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 39+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetParsedHeaderValue(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 40+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 41+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_SOAP_Set(m_pObj, 41+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline LPWSTR GetPragma() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 42+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPragma(LPCWSTR lpszPragma) {
      return IPWorks_SOAP_Set(m_pObj, 42+10000, 0, (LPVOID)lpszPragma, 0);
    }

    inline INT GetProxyAuthScheme() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 43, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyAuthScheme(INT iProxyAuthScheme) {
      LPVOID val = (LPVOID)(iProxyAuthScheme);
      return IPWorks_SOAP_Set(m_pObj, 43, 0, val, 0);
    }

    inline BOOL GetProxyAutoDetect() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 44, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetProxyAutoDetect(BOOL bProxyAutoDetect) {
      LPVOID val = (LPVOID)(bProxyAutoDetect);
      return IPWorks_SOAP_Set(m_pObj, 44, 0, val, 0);
    }

    inline LPWSTR GetProxyPassword() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 45+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyPassword(LPCWSTR lpszProxyPassword) {
      return IPWorks_SOAP_Set(m_pObj, 45+10000, 0, (LPVOID)lpszProxyPassword, 0);
    }

    inline INT GetProxyPort() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 46, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyPort(INT iProxyPort) {
      LPVOID val = (LPVOID)(iProxyPort);
      return IPWorks_SOAP_Set(m_pObj, 46, 0, val, 0);
    }

    inline LPWSTR GetProxyServer() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 47+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyServer(LPCWSTR lpszProxyServer) {
      return IPWorks_SOAP_Set(m_pObj, 47+10000, 0, (LPVOID)lpszProxyServer, 0);
    }

    inline INT GetProxySSL() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 48, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxySSL(INT iProxySSL) {
      LPVOID val = (LPVOID)(iProxySSL);
      return IPWorks_SOAP_Set(m_pObj, 48, 0, val, 0);
    }

    inline LPWSTR GetProxyUser() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 49+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyUser(LPCWSTR lpszProxyUser) {
      return IPWorks_SOAP_Set(m_pObj, 49+10000, 0, (LPVOID)lpszProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 50+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReferer(LPCWSTR lpszReferer) {
      return IPWorks_SOAP_Set(m_pObj, 50+10000, 0, (LPVOID)lpszReferer, 0);
    }

    inline LPWSTR GetReturnValue() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 51+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSOAPEncoding() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 52+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSOAPEncoding(LPCWSTR lpszSOAPEncoding) {
      return IPWorks_SOAP_Set(m_pObj, 52+10000, 0, (LPVOID)lpszSOAPEncoding, 0);
    }

    inline LPWSTR GetSOAPHeader() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 53+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSOAPHeader(LPCWSTR lpszSOAPHeader) {
      return IPWorks_SOAP_Set(m_pObj, 53+10000, 0, (LPVOID)lpszSOAPHeader, 0);
    }

    inline LPWSTR GetSOAPPacket() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 54+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSOAPPacket(LPCWSTR lpszSOAPPacket) {
      return IPWorks_SOAP_Set(m_pObj, 54+10000, 0, (LPVOID)lpszSOAPPacket, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_SOAP_Get(m_pObj, 55, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_SOAP_Set(m_pObj, 55, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_SOAP_Get(m_pObj, 56, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_SOAP_Set(m_pObj, 56, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_SOAP_Get(m_pObj, 57, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_SOAP_Set(m_pObj, 57, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 58+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_SOAP_Set(m_pObj, 58+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 59, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_SOAP_Set(m_pObj, 59, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 60+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_SOAP_Set(m_pObj, 60+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_SOAP_Get(m_pObj, 61, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline LPWSTR GetStatusLine() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 62+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 63, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_SOAP_Set(m_pObj, 63, 0, val, 0);
    }

    inline INT GetTransferredData(LPSTR &lpTransferredData, INT &lenTransferredData) {
      lpTransferredData = (LPSTR)IPWorks_SOAP_Get(m_pObj, 64, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline LONG64 GetTransferredDataLimit() {
      LONG64 retVal;
      IPWorks_SOAP_Get(m_pObj, 65, 0, NULL, &retVal);
      return retVal;
    }
    inline INT SetTransferredDataLimit(LONG64 lTransferredDataLimit) {
      LPVOID val = (LPVOID)(&lTransferredDataLimit);
      return IPWorks_SOAP_Set(m_pObj, 65, 0, val, 0);
    }

    inline LPWSTR GetTransferredHeaders() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 66+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetURL() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 67+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetURL(LPCWSTR lpszURL) {
      return IPWorks_SOAP_Set(m_pObj, 67+10000, 0, (LPVOID)lpszURL, 0);
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 68+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_SOAP_Set(m_pObj, 68+10000, 0, (LPVOID)lpszUser, 0);
    }

    inline INT GetValueFormat() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 69, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetValueFormat(INT iValueFormat) {
      LPVOID val = (LPVOID)(iValueFormat);
      return IPWorks_SOAP_Set(m_pObj, 69, 0, val, 0);
    }

    inline INT GetAttrCount() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 70, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetAttrName(INT iAttrIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 71+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAttrNamespace(INT iAttrIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 72+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAttrPrefix(INT iAttrIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 73+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAttrValue(INT iAttrIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 74+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetXChildCount() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 75, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetXChildName(INT iXChildIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 76+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXChildNamespace(INT iXChildIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 77+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXChildPrefix(INT iXChildIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 78+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXChildXText(INT iXChildIndex) {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 79+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXElement() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 80+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXNamespace() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 81+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXParent() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 82+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXPath() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 83+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXPath(LPCWSTR lpszXPath) {
      return IPWorks_SOAP_Set(m_pObj, 83+10000, 0, (LPVOID)lpszXPath, 0);
    }

    inline LPWSTR GetXPrefix() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 84+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXText() {
      LPVOID val = IPWorks_SOAP_Get(m_pObj, 85+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

  public: // Methods
    inline INT AddCookie(LPCWSTR lpszCookieName, LPCWSTR lpszCookieValue) {
      LPVOID param[2+1] = {(LPVOID)lpszCookieName, (LPVOID)lpszCookieValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 2+10000, 2, param, cbparam, NULL);
    }

    inline INT AddNamespace(LPCWSTR lpszPrefix, LPCWSTR lpszNamespaceURI) {
      LPVOID param[2+1] = {(LPVOID)lpszPrefix, (LPVOID)lpszNamespaceURI, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 3+10000, 2, param, cbparam, NULL);
    }

    inline INT AddParam(LPCWSTR lpszParamName, LPCWSTR lpszParamValue) {
      LPVOID param[2+1] = {(LPVOID)lpszParamName, (LPVOID)lpszParamValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 4+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR Attr(LPCWSTR lpszAttrName) {
      LPVOID param[1+1] = {(LPVOID)lpszAttrName, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT BuildPacket() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 7+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT EvalPacket() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT HasXPath(LPCWSTR lpszXPath) {
      LPVOID param[1+1] = {(LPVOID)lpszXPath, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 10+10000, 1, param, cbparam, NULL);
      return (BOOL)param[1];
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 11+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
    }

    inline INT SendPacket() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 13+10000, 0, param, cbparam, NULL);
    }

    inline INT SendRequest() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 14+10000, 0, param, cbparam, NULL);
    }

    inline INT TryXPath(LPCWSTR lpszxpath) {
      LPVOID param[1+1] = {(LPVOID)lpszxpath, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 15+10000, 1, param, cbparam, NULL);
      return (BOOL)param[1];
    }

    inline LPWSTR Value(LPCWSTR lpszParamName) {
      LPVOID param[1+1] = {(LPVOID)lpszParamName, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 16+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

};

#endif //_IPWORKS_SOAP_H_
