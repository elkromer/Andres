/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_REST_H_
#define _IPWORKS_REST_H_

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


extern "C" void* IPWORKS_CALL IPWorks_REST_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_REST_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_REST_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_REST_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_REST_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_REST_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_REST_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_REST_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_REST_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_REST_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_REST_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_REST_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_REST_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_REST_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR Text;
  INT reserved;
} RESTCharactersEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} RESTCommentEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RESTConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RESTConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RESTDisconnectedEventParams;

typedef struct {
  LPCWSTR Namespace;
  LPCWSTR Element;
  LPCWSTR QName;
  BOOL IsEmpty;
  INT reserved;
} RESTEndElementEventParams;

typedef struct {
  LPCWSTR Prefix;
  INT reserved;
} RESTEndPrefixMappingEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} RESTEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} RESTErrorEventParams;

typedef struct {
  LPCWSTR Entity;
  LPWSTR Value;
  INT reserved;
} RESTEvalEntityEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} RESTHeaderEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} RESTIgnorableWhitespaceEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} RESTLogEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} RESTMetaEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} RESTPIEventParams;

typedef struct {
  LPCWSTR Location;
  BOOL Accept;
  INT reserved;
} RESTRedirectEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR Value;
  LPCWSTR Expires;
  LPCWSTR Domain;
  LPCWSTR Path;
  BOOL Secure;
  INT reserved;
} RESTSetCookieEventParams;

typedef struct {
  LPCWSTR SectionId;
  LPCWSTR Text;
  INT reserved;
} RESTSpecialSectionEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} RESTSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} RESTSSLStatusEventParams;

typedef struct {
  LPCWSTR Namespace;
  LPCWSTR Element;
  LPCWSTR QName;
  BOOL IsEmpty;
  INT reserved;
} RESTStartElementEventParams;

typedef struct {
  LPCWSTR Prefix;
  LPCWSTR URI;
  INT reserved;
} RESTStartPrefixMappingEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} RESTStartTransferEventParams;

typedef struct {
  LPCWSTR HTTPVersion;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RESTStatusEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  INT reserved;
} RESTTransferEventParams;


class REST {
  public: // Events
    virtual INT FireCharacters(RESTCharactersEventParams *e) {return 0;}
    virtual INT FireComment(RESTCommentEventParams *e) {return 0;}
    virtual INT FireConnected(RESTConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(RESTConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(RESTDisconnectedEventParams *e) {return 0;}
    virtual INT FireEndElement(RESTEndElementEventParams *e) {return 0;}
    virtual INT FireEndPrefixMapping(RESTEndPrefixMappingEventParams *e) {return 0;}
    virtual INT FireEndTransfer(RESTEndTransferEventParams *e) {return 0;}
    virtual INT FireError(RESTErrorEventParams *e) {return 0;}
    virtual INT FireEvalEntity(RESTEvalEntityEventParams *e) {return 0;}
    virtual INT FireHeader(RESTHeaderEventParams *e) {return 0;}
    virtual INT FireIgnorableWhitespace(RESTIgnorableWhitespaceEventParams *e) {return 0;}
    virtual INT FireLog(RESTLogEventParams *e) {return 0;}
    virtual INT FireMeta(RESTMetaEventParams *e) {return 0;}
    virtual INT FirePI(RESTPIEventParams *e) {return 0;}
    virtual INT FireRedirect(RESTRedirectEventParams *e) {return 0;}
    virtual INT FireSetCookie(RESTSetCookieEventParams *e) {return 0;}
    virtual INT FireSpecialSection(RESTSpecialSectionEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(RESTSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(RESTSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartElement(RESTStartElementEventParams *e) {return 0;}
    virtual INT FireStartPrefixMapping(RESTStartPrefixMappingEventParams *e) {return 0;}
    virtual INT FireStartTransfer(RESTStartTransferEventParams *e) {return 0;}
    virtual INT FireStatus(RESTStatusEventParams *e) {return 0;}
    virtual INT FireTransfer(RESTTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL RESTEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          RESTCharactersEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((REST*)lpObj)->FireCharacters(&e);
          break;
        }
        case 2: {
          RESTCommentEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((REST*)lpObj)->FireComment(&e);
          break;
        }
        case 3: {
          RESTConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((REST*)lpObj)->FireConnected(&e);
          break;
        }
        case 4: {
          RESTConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((REST*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 5: {
          RESTDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((REST*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 6: {
          RESTEndElementEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (BOOL)param[3], 0};
          ret_code = ((REST*)lpObj)->FireEndElement(&e);
          break;
        }
        case 7: {
          RESTEndPrefixMappingEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((REST*)lpObj)->FireEndPrefixMapping(&e);
          break;
        }
        case 8: {
          RESTEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((REST*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 9: {
          RESTErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((REST*)lpObj)->FireError(&e);
          break;
        }
        case 10: {
          RESTEvalEntityEventParams e = {(LPWSTR)param[0], (LPWSTR)IPWorks_EvtStr(param[1], 0, NULL, 2), 0};
          ret_code = ((REST*)lpObj)->FireEvalEntity(&e);
          IPWorks_EvtStr(param[1], 1, (void*)e.Value, 2);
          break;
        }
        case 11: {
          RESTHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((REST*)lpObj)->FireHeader(&e);
          break;
        }
        case 12: {
          RESTIgnorableWhitespaceEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((REST*)lpObj)->FireIgnorableWhitespace(&e);
          break;
        }
        case 13: {
          RESTLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((REST*)lpObj)->FireLog(&e);
          break;
        }
        case 14: {
          RESTMetaEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((REST*)lpObj)->FireMeta(&e);
          break;
        }
        case 15: {
          RESTPIEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((REST*)lpObj)->FirePI(&e);
          break;
        }
        case 16: {
          RESTRedirectEventParams e = {(LPWSTR)param[0], (BOOL)param[1], 0};
          ret_code = ((REST*)lpObj)->FireRedirect(&e);
          param[1] = (LPVOID)e.Accept;
          break;
        }
        case 17: {
          RESTSetCookieEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((REST*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 18: {
          RESTSpecialSectionEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((REST*)lpObj)->FireSpecialSection(&e);
          break;
        }
        case 19: {
          RESTSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((REST*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 20: {
          RESTSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((REST*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 21: {
          RESTStartElementEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (BOOL)param[3], 0};
          ret_code = ((REST*)lpObj)->FireStartElement(&e);
          break;
        }
        case 22: {
          RESTStartPrefixMappingEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((REST*)lpObj)->FireStartPrefixMapping(&e);
          break;
        }
        case 23: {
          RESTStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((REST*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 24: {
          RESTStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((REST*)lpObj)->FireStatus(&e);
          break;
        }
        case 25: {
          RESTTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], 0};
          ret_code = ((REST*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    REST(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_34) {
      m_pObj = IPWorks_REST_Create(RESTEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~REST() {
      IPWorks_REST_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_REST_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_REST_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_REST_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_REST_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_REST_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAccept() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAccept(LPCWSTR lpszAccept) {
      return IPWorks_REST_Set(m_pObj, 1+10000, 0, (LPVOID)lpszAccept, 0);
    }

    inline LPWSTR GetAuthorization() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorization(LPCWSTR lpszAuthorization) {
      return IPWorks_REST_Set(m_pObj, 2+10000, 0, (LPVOID)lpszAuthorization, 0);
    }

    inline INT GetAuthScheme() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 3, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthScheme(INT iAuthScheme) {
      LPVOID val = (LPVOID)(iAuthScheme);
      return IPWorks_REST_Set(m_pObj, 3, 0, val, 0);
    }

    inline BOOL GetBuildDOM() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 4, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetBuildDOM(BOOL bBuildDOM) {
      LPVOID val = (LPVOID)(bBuildDOM);
      return IPWorks_REST_Set(m_pObj, 4, 0, val, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 5, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_REST_Set(m_pObj, 5, 0, val, 0);
    }

    inline LPWSTR GetContentType() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetContentType(LPCWSTR lpszContentType) {
      return IPWorks_REST_Set(m_pObj, 6+10000, 0, (LPVOID)lpszContentType, 0);
    }

    inline INT GetCookieCount() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 7, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCookieCount(INT iCookieCount) {
      LPVOID val = (LPVOID)(iCookieCount);
      return IPWorks_REST_Set(m_pObj, 7, 0, val, 0);
    }

    inline LPWSTR GetCookieDomain(INT iCookieIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 8+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieExpiration(INT iCookieIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 9+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieName(INT iCookieIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 10+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieName(INT iCookieIndex, LPCWSTR lpszCookieName) {
      return IPWorks_REST_Set(m_pObj, 10+10000, iCookieIndex, (LPVOID)lpszCookieName, 0);
    }

    inline LPWSTR GetCookiePath(INT iCookieIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 11+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCookieSecure(INT iCookieIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 12, iCookieIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCookieValue(INT iCookieIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 13+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieValue(INT iCookieIndex, LPCWSTR lpszCookieValue) {
      return IPWorks_REST_Set(m_pObj, 13+10000, iCookieIndex, (LPVOID)lpszCookieValue, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 14, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_REST_Set(m_pObj, 14, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 15, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_REST_Set(m_pObj, 15, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_REST_Set(m_pObj, 16+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_REST_Set(m_pObj, 17+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 18, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_REST_Set(m_pObj, 18, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_REST_Set(m_pObj, 19+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline INT GetFollowRedirects() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 20, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFollowRedirects(INT iFollowRedirects) {
      LPVOID val = (LPVOID)(iFollowRedirects);
      return IPWorks_REST_Set(m_pObj, 20, 0, val, 0);
    }

    inline LPWSTR GetFrom() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFrom(LPCWSTR lpszFrom) {
      return IPWorks_REST_Set(m_pObj, 21+10000, 0, (LPVOID)lpszFrom, 0);
    }

    inline LPWSTR GetHTTPMethod() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetHTTPMethod(LPCWSTR lpszHTTPMethod) {
      return IPWorks_REST_Set(m_pObj, 22+10000, 0, (LPVOID)lpszHTTPMethod, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 23, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetIfModifiedSince() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetIfModifiedSince(LPCWSTR lpszIfModifiedSince) {
      return IPWorks_REST_Set(m_pObj, 24+10000, 0, (LPVOID)lpszIfModifiedSince, 0);
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_REST_Set(m_pObj, 25+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_REST_Set(m_pObj, 26+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetNamespaceCount() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 27, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetNamespacePrefix(INT iNamespaceIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 28+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetNamespaceURI(INT iNamespaceIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 29+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 30+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_REST_Set(m_pObj, 30+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline INT GetParsedHeaderCount() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 31, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetParsedHeaderField(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 32+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetParsedHeaderValue(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 33+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 34+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_REST_Set(m_pObj, 34+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetPostData(LPSTR &lpPostData, INT &lenPostData) {
      lpPostData = (LPSTR)IPWorks_REST_Get(m_pObj, 35, 0, &lenPostData, NULL);
      return lpPostData ? 0 : lenPostData;
    }
    inline INT SetPostData(LPCSTR lpPostData, INT lenPostData) {
      return IPWorks_REST_Set(m_pObj, 35, 0, (LPVOID)lpPostData, lenPostData);
    }

    inline INT GetProxyAuthScheme() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 36, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyAuthScheme(INT iProxyAuthScheme) {
      LPVOID val = (LPVOID)(iProxyAuthScheme);
      return IPWorks_REST_Set(m_pObj, 36, 0, val, 0);
    }

    inline BOOL GetProxyAutoDetect() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 37, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetProxyAutoDetect(BOOL bProxyAutoDetect) {
      LPVOID val = (LPVOID)(bProxyAutoDetect);
      return IPWorks_REST_Set(m_pObj, 37, 0, val, 0);
    }

    inline LPWSTR GetProxyPassword() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 38+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyPassword(LPCWSTR lpszProxyPassword) {
      return IPWorks_REST_Set(m_pObj, 38+10000, 0, (LPVOID)lpszProxyPassword, 0);
    }

    inline INT GetProxyPort() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 39, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyPort(INT iProxyPort) {
      LPVOID val = (LPVOID)(iProxyPort);
      return IPWorks_REST_Set(m_pObj, 39, 0, val, 0);
    }

    inline LPWSTR GetProxyServer() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 40+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyServer(LPCWSTR lpszProxyServer) {
      return IPWorks_REST_Set(m_pObj, 40+10000, 0, (LPVOID)lpszProxyServer, 0);
    }

    inline INT GetProxySSL() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 41, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxySSL(INT iProxySSL) {
      LPVOID val = (LPVOID)(iProxySSL);
      return IPWorks_REST_Set(m_pObj, 41, 0, val, 0);
    }

    inline LPWSTR GetProxyUser() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 42+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyUser(LPCWSTR lpszProxyUser) {
      return IPWorks_REST_Set(m_pObj, 42+10000, 0, (LPVOID)lpszProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 43+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReferer(LPCWSTR lpszReferer) {
      return IPWorks_REST_Set(m_pObj, 43+10000, 0, (LPVOID)lpszReferer, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_REST_Get(m_pObj, 44, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_REST_Set(m_pObj, 44, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_REST_Get(m_pObj, 45, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_REST_Set(m_pObj, 45, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_REST_Get(m_pObj, 46, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_REST_Set(m_pObj, 46, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 47+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_REST_Set(m_pObj, 47+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 48, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_REST_Set(m_pObj, 48, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 49+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_REST_Set(m_pObj, 49+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_REST_Get(m_pObj, 50, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline LPWSTR GetStatusLine() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 51+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 52, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_REST_Set(m_pObj, 52, 0, val, 0);
    }

    inline INT GetTransferredData(LPSTR &lpTransferredData, INT &lenTransferredData) {
      lpTransferredData = (LPSTR)IPWorks_REST_Get(m_pObj, 53, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline LONG64 GetTransferredDataLimit() {
      LONG64 retVal;
      IPWorks_REST_Get(m_pObj, 54, 0, NULL, &retVal);
      return retVal;
    }
    inline INT SetTransferredDataLimit(LONG64 lTransferredDataLimit) {
      LPVOID val = (LPVOID)(&lTransferredDataLimit);
      return IPWorks_REST_Set(m_pObj, 54, 0, val, 0);
    }

    inline LPWSTR GetTransferredHeaders() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 55+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetURL() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 56+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetURL(LPCWSTR lpszURL) {
      return IPWorks_REST_Set(m_pObj, 56+10000, 0, (LPVOID)lpszURL, 0);
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 57+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_REST_Set(m_pObj, 57+10000, 0, (LPVOID)lpszUser, 0);
    }

    inline BOOL GetValidate() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 58, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetValidate(BOOL bValidate) {
      LPVOID val = (LPVOID)(bValidate);
      return IPWorks_REST_Set(m_pObj, 58, 0, val, 0);
    }

    inline INT GetAttrCount() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 59, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetAttrName(INT iAttrIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 60+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAttrNamespace(INT iAttrIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 61+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAttrPrefix(INT iAttrIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 62+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAttrValue(INT iAttrIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 63+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetXChildCount() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 64, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetXChildName(INT iXChildIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 65+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXChildNamespace(INT iXChildIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 66+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXChildPrefix(INT iXChildIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 67+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXChildXText(INT iXChildIndex) {
      LPVOID val = IPWorks_REST_Get(m_pObj, 68+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXElement() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 69+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXErrorPath() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 70+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXErrorPath(LPCWSTR lpszXErrorPath) {
      return IPWorks_REST_Set(m_pObj, 70+10000, 0, (LPVOID)lpszXErrorPath, 0);
    }

    inline LPWSTR GetXNamespace() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 71+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXParent() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 72+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXPath() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 73+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXPath(LPCWSTR lpszXPath) {
      return IPWorks_REST_Set(m_pObj, 73+10000, 0, (LPVOID)lpszXPath, 0);
    }

    inline LPWSTR GetXPrefix() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 74+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXSubTree() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 75+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXText() {
      LPVOID val = IPWorks_REST_Get(m_pObj, 76+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

  public: // Methods
    inline INT AddCookie(LPCWSTR lpszCookieName, LPCWSTR lpszCookieValue) {
      LPVOID param[2+1] = {(LPVOID)lpszCookieName, (LPVOID)lpszCookieValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_REST_Do(m_pObj, 2+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR Attr(LPCWSTR lpszAttrName) {
      LPVOID param[1+1] = {(LPVOID)lpszAttrName, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_REST_Do(m_pObj, 3+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_REST_Do(m_pObj, 4+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Delete(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_REST_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Get(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 7+10000, 1, param, cbparam, NULL);
    }

    inline INT HasXPath(LPCWSTR lpszXPath) {
      LPVOID param[1+1] = {(LPVOID)lpszXPath, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_REST_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
      return (BOOL)param[1];
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_REST_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT Post(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 10+10000, 1, param, cbparam, NULL);
    }

    inline INT Put(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 11+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_REST_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
    }

    inline INT TryXPath(LPCWSTR lpszxpath) {
      LPVOID param[1+1] = {(LPVOID)lpszxpath, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_REST_Do(m_pObj, 13+10000, 1, param, cbparam, NULL);
      return (BOOL)param[1];
    }

};

#endif //_IPWORKS_REST_H_
