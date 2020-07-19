/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_RSS_H_
#define _IPWORKS_RSS_H_

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

//TRSSVersion
#define RSS_VERSION_UNDEFINED                              0
#define RSS_VERSION_091                                    1
#define RSS_VERSION_092                                    2
#define RSS_VERSION_200                                    3

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


extern "C" void* IPWORKS_CALL IPWorks_RSS_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_RSS_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_RSS_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_RSS_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_RSS_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_RSS_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_RSS_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_RSS_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_RSS_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RSSConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RSSConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RSSDisconnectedEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} RSSEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} RSSErrorEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} RSSHeaderEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} RSSLogEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} RSSOPMLHeaderEventParams;

typedef struct {
  INT Level;
  LPCWSTR Text;
  LPCWSTR TypeName;
  LPCWSTR Title;
  LPCWSTR URL;
  LPCWSTR XMLURL;
  LPCWSTR HTMLURL;
  LPCWSTR Created;
  LPCWSTR Description;
  LPCWSTR OtherAttrs;
  INT reserved;
} RSSOPMLOutlineEventParams;

typedef struct {
  LPCWSTR Location;
  BOOL Accept;
  INT reserved;
} RSSRedirectEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR Value;
  LPCWSTR Expires;
  LPCWSTR Domain;
  LPCWSTR Path;
  BOOL Secure;
  INT reserved;
} RSSSetCookieEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} RSSSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} RSSSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} RSSStartTransferEventParams;

typedef struct {
  LPCWSTR HTTPVersion;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} RSSStatusEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  INT reserved;
} RSSTransferEventParams;


class RSS {
  public: // Events
    virtual INT FireConnected(RSSConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(RSSConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(RSSDisconnectedEventParams *e) {return 0;}
    virtual INT FireEndTransfer(RSSEndTransferEventParams *e) {return 0;}
    virtual INT FireError(RSSErrorEventParams *e) {return 0;}
    virtual INT FireHeader(RSSHeaderEventParams *e) {return 0;}
    virtual INT FireLog(RSSLogEventParams *e) {return 0;}
    virtual INT FireOPMLHeader(RSSOPMLHeaderEventParams *e) {return 0;}
    virtual INT FireOPMLOutline(RSSOPMLOutlineEventParams *e) {return 0;}
    virtual INT FireRedirect(RSSRedirectEventParams *e) {return 0;}
    virtual INT FireSetCookie(RSSSetCookieEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(RSSSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(RSSSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(RSSStartTransferEventParams *e) {return 0;}
    virtual INT FireStatus(RSSStatusEventParams *e) {return 0;}
    virtual INT FireTransfer(RSSTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL RSSEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          RSSConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((RSS*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          RSSConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((RSS*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          RSSDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((RSS*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          RSSEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((RSS*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          RSSErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((RSS*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          RSSHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((RSS*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          RSSLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((RSS*)lpObj)->FireLog(&e);
          break;
        }
        case 8: {
          RSSOPMLHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((RSS*)lpObj)->FireOPMLHeader(&e);
          break;
        }
        case 9: {
          RSSOPMLOutlineEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (LPWSTR)param[5], (LPWSTR)param[6], (LPWSTR)param[7], (LPWSTR)param[8], (LPWSTR)param[9], 0};
          ret_code = ((RSS*)lpObj)->FireOPMLOutline(&e);
          break;
        }
        case 10: {
          RSSRedirectEventParams e = {(LPWSTR)param[0], (BOOL)param[1], 0};
          ret_code = ((RSS*)lpObj)->FireRedirect(&e);
          param[1] = (LPVOID)e.Accept;
          break;
        }
        case 11: {
          RSSSetCookieEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((RSS*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 12: {
          RSSSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((RSS*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 13: {
          RSSSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((RSS*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 14: {
          RSSStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((RSS*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 15: {
          RSSStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((RSS*)lpObj)->FireStatus(&e);
          break;
        }
        case 16: {
          RSSTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], 0};
          ret_code = ((RSS*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    RSS(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_59) {
      m_pObj = IPWorks_RSS_Create(RSSEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~RSS() {
      IPWorks_RSS_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_RSS_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_RSS_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_RSS_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_RSS_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_RSS_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAccept() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAccept(LPCWSTR lpszAccept) {
      return IPWorks_RSS_Set(m_pObj, 1+10000, 0, (LPVOID)lpszAccept, 0);
    }

    inline LPWSTR GetAuthorization() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorization(LPCWSTR lpszAuthorization) {
      return IPWorks_RSS_Set(m_pObj, 2+10000, 0, (LPVOID)lpszAuthorization, 0);
    }

    inline INT GetAuthScheme() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 3, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthScheme(INT iAuthScheme) {
      LPVOID val = (LPVOID)(iAuthScheme);
      return IPWorks_RSS_Set(m_pObj, 3, 0, val, 0);
    }

    inline LPWSTR GetChannelCategory() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelCategory(LPCWSTR lpszChannelCategory) {
      return IPWorks_RSS_Set(m_pObj, 4+10000, 0, (LPVOID)lpszChannelCategory, 0);
    }

    inline LPWSTR GetChannelCategoryDomain() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelCategoryDomain(LPCWSTR lpszChannelCategoryDomain) {
      return IPWorks_RSS_Set(m_pObj, 5+10000, 0, (LPVOID)lpszChannelCategoryDomain, 0);
    }

    inline LPWSTR GetChannelCopyright() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelCopyright(LPCWSTR lpszChannelCopyright) {
      return IPWorks_RSS_Set(m_pObj, 6+10000, 0, (LPVOID)lpszChannelCopyright, 0);
    }

    inline LPWSTR GetChannelDescription() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelDescription(LPCWSTR lpszChannelDescription) {
      return IPWorks_RSS_Set(m_pObj, 7+10000, 0, (LPVOID)lpszChannelDescription, 0);
    }

    inline LPWSTR GetChannelDocs() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelDocs(LPCWSTR lpszChannelDocs) {
      return IPWorks_RSS_Set(m_pObj, 8+10000, 0, (LPVOID)lpszChannelDocs, 0);
    }

    inline LPWSTR GetChannelGenerator() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelGenerator(LPCWSTR lpszChannelGenerator) {
      return IPWorks_RSS_Set(m_pObj, 9+10000, 0, (LPVOID)lpszChannelGenerator, 0);
    }

    inline LPWSTR GetChannelImageDescription() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelImageDescription(LPCWSTR lpszChannelImageDescription) {
      return IPWorks_RSS_Set(m_pObj, 10+10000, 0, (LPVOID)lpszChannelImageDescription, 0);
    }

    inline LPWSTR GetChannelImageHeight() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelImageHeight(LPCWSTR lpszChannelImageHeight) {
      return IPWorks_RSS_Set(m_pObj, 11+10000, 0, (LPVOID)lpszChannelImageHeight, 0);
    }

    inline LPWSTR GetChannelImageLink() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelImageLink(LPCWSTR lpszChannelImageLink) {
      return IPWorks_RSS_Set(m_pObj, 12+10000, 0, (LPVOID)lpszChannelImageLink, 0);
    }

    inline LPWSTR GetChannelImageTitle() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelImageTitle(LPCWSTR lpszChannelImageTitle) {
      return IPWorks_RSS_Set(m_pObj, 13+10000, 0, (LPVOID)lpszChannelImageTitle, 0);
    }

    inline LPWSTR GetChannelImageUrl() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelImageUrl(LPCWSTR lpszChannelImageUrl) {
      return IPWorks_RSS_Set(m_pObj, 14+10000, 0, (LPVOID)lpszChannelImageUrl, 0);
    }

    inline LPWSTR GetChannelImageWidth() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelImageWidth(LPCWSTR lpszChannelImageWidth) {
      return IPWorks_RSS_Set(m_pObj, 15+10000, 0, (LPVOID)lpszChannelImageWidth, 0);
    }

    inline LPWSTR GetChannelLanguage() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLanguage(LPCWSTR lpszChannelLanguage) {
      return IPWorks_RSS_Set(m_pObj, 16+10000, 0, (LPVOID)lpszChannelLanguage, 0);
    }

    inline LPWSTR GetChannelLastBuildDate() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLastBuildDate(LPCWSTR lpszChannelLastBuildDate) {
      return IPWorks_RSS_Set(m_pObj, 17+10000, 0, (LPVOID)lpszChannelLastBuildDate, 0);
    }

    inline LPWSTR GetChannelLink() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLink(LPCWSTR lpszChannelLink) {
      return IPWorks_RSS_Set(m_pObj, 18+10000, 0, (LPVOID)lpszChannelLink, 0);
    }

    inline LPWSTR GetChannelManagingEditor() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelManagingEditor(LPCWSTR lpszChannelManagingEditor) {
      return IPWorks_RSS_Set(m_pObj, 19+10000, 0, (LPVOID)lpszChannelManagingEditor, 0);
    }

    inline LPWSTR GetChannelPubDate() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelPubDate(LPCWSTR lpszChannelPubDate) {
      return IPWorks_RSS_Set(m_pObj, 20+10000, 0, (LPVOID)lpszChannelPubDate, 0);
    }

    inline LPWSTR GetChannelSkipDays() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelSkipDays(LPCWSTR lpszChannelSkipDays) {
      return IPWorks_RSS_Set(m_pObj, 21+10000, 0, (LPVOID)lpszChannelSkipDays, 0);
    }

    inline LPWSTR GetChannelSkipHours() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelSkipHours(LPCWSTR lpszChannelSkipHours) {
      return IPWorks_RSS_Set(m_pObj, 22+10000, 0, (LPVOID)lpszChannelSkipHours, 0);
    }

    inline LPWSTR GetChannelTitle() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 23+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelTitle(LPCWSTR lpszChannelTitle) {
      return IPWorks_RSS_Set(m_pObj, 23+10000, 0, (LPVOID)lpszChannelTitle, 0);
    }

    inline LPWSTR GetChannelTtl() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelTtl(LPCWSTR lpszChannelTtl) {
      return IPWorks_RSS_Set(m_pObj, 24+10000, 0, (LPVOID)lpszChannelTtl, 0);
    }

    inline LPWSTR GetChannelWebMaster() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelWebMaster(LPCWSTR lpszChannelWebMaster) {
      return IPWorks_RSS_Set(m_pObj, 25+10000, 0, (LPVOID)lpszChannelWebMaster, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 26, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_RSS_Set(m_pObj, 26, 0, val, 0);
    }

    inline INT GetCookieCount() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 27, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCookieCount(INT iCookieCount) {
      LPVOID val = (LPVOID)(iCookieCount);
      return IPWorks_RSS_Set(m_pObj, 27, 0, val, 0);
    }

    inline LPWSTR GetCookieDomain(INT iCookieIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 28+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieExpiration(INT iCookieIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 29+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieName(INT iCookieIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 30+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieName(INT iCookieIndex, LPCWSTR lpszCookieName) {
      return IPWorks_RSS_Set(m_pObj, 30+10000, iCookieIndex, (LPVOID)lpszCookieName, 0);
    }

    inline LPWSTR GetCookiePath(INT iCookieIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 31+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCookieSecure(INT iCookieIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 32, iCookieIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCookieValue(INT iCookieIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 33+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieValue(INT iCookieIndex, LPCWSTR lpszCookieValue) {
      return IPWorks_RSS_Set(m_pObj, 33+10000, iCookieIndex, (LPVOID)lpszCookieValue, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 34, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_RSS_Set(m_pObj, 34, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 35, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_RSS_Set(m_pObj, 35, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 36+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_RSS_Set(m_pObj, 36+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 37+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_RSS_Set(m_pObj, 37+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 38, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_RSS_Set(m_pObj, 38, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 39+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_RSS_Set(m_pObj, 39+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline INT GetFollowRedirects() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 40, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFollowRedirects(INT iFollowRedirects) {
      LPVOID val = (LPVOID)(iFollowRedirects);
      return IPWorks_RSS_Set(m_pObj, 40, 0, val, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 41, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetIfModifiedSince() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 42+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetIfModifiedSince(LPCWSTR lpszIfModifiedSince) {
      return IPWorks_RSS_Set(m_pObj, 42+10000, 0, (LPVOID)lpszIfModifiedSince, 0);
    }

    inline INT GetItemCount() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 43, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetItemCount(INT iItemCount) {
      LPVOID val = (LPVOID)(iItemCount);
      return IPWorks_RSS_Set(m_pObj, 43, 0, val, 0);
    }

    inline LPWSTR GetItemAuthor(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 44+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemAuthor(INT iItemIndex, LPCWSTR lpszItemAuthor) {
      return IPWorks_RSS_Set(m_pObj, 44+10000, iItemIndex, (LPVOID)lpszItemAuthor, 0);
    }

    inline LPWSTR GetItemCategory(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 45+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemCategory(INT iItemIndex, LPCWSTR lpszItemCategory) {
      return IPWorks_RSS_Set(m_pObj, 45+10000, iItemIndex, (LPVOID)lpszItemCategory, 0);
    }

    inline LPWSTR GetItemCategoryDomain(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 46+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemCategoryDomain(INT iItemIndex, LPCWSTR lpszItemCategoryDomain) {
      return IPWorks_RSS_Set(m_pObj, 46+10000, iItemIndex, (LPVOID)lpszItemCategoryDomain, 0);
    }

    inline LPWSTR GetItemComments(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 47+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemComments(INT iItemIndex, LPCWSTR lpszItemComments) {
      return IPWorks_RSS_Set(m_pObj, 47+10000, iItemIndex, (LPVOID)lpszItemComments, 0);
    }

    inline LPWSTR GetItemDescription(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 48+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemDescription(INT iItemIndex, LPCWSTR lpszItemDescription) {
      return IPWorks_RSS_Set(m_pObj, 48+10000, iItemIndex, (LPVOID)lpszItemDescription, 0);
    }

    inline LPWSTR GetItemEnclosureLength(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 49+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemEnclosureLength(INT iItemIndex, LPCWSTR lpszItemEnclosureLength) {
      return IPWorks_RSS_Set(m_pObj, 49+10000, iItemIndex, (LPVOID)lpszItemEnclosureLength, 0);
    }

    inline LPWSTR GetItemEnclosureType(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 50+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemEnclosureType(INT iItemIndex, LPCWSTR lpszItemEnclosureType) {
      return IPWorks_RSS_Set(m_pObj, 50+10000, iItemIndex, (LPVOID)lpszItemEnclosureType, 0);
    }

    inline LPWSTR GetItemEnclosureUrl(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 51+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemEnclosureUrl(INT iItemIndex, LPCWSTR lpszItemEnclosureUrl) {
      return IPWorks_RSS_Set(m_pObj, 51+10000, iItemIndex, (LPVOID)lpszItemEnclosureUrl, 0);
    }

    inline LPWSTR GetItemGuid(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 52+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemGuid(INT iItemIndex, LPCWSTR lpszItemGuid) {
      return IPWorks_RSS_Set(m_pObj, 52+10000, iItemIndex, (LPVOID)lpszItemGuid, 0);
    }

    inline BOOL GetItemGuidIsPermaLink(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 53, iItemIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetItemGuidIsPermaLink(INT iItemIndex, BOOL bItemGuidIsPermaLink) {
      LPVOID val = (LPVOID)(bItemGuidIsPermaLink);
      return IPWorks_RSS_Set(m_pObj, 53, iItemIndex, val, 0);
    }

    inline LPWSTR GetItemXML(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 54+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemXML(INT iItemIndex, LPCWSTR lpszItemXML) {
      return IPWorks_RSS_Set(m_pObj, 54+10000, iItemIndex, (LPVOID)lpszItemXML, 0);
    }

    inline LPWSTR GetItemLink(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 55+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemLink(INT iItemIndex, LPCWSTR lpszItemLink) {
      return IPWorks_RSS_Set(m_pObj, 55+10000, iItemIndex, (LPVOID)lpszItemLink, 0);
    }

    inline LPWSTR GetItemPubDate(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 56+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemPubDate(INT iItemIndex, LPCWSTR lpszItemPubDate) {
      return IPWorks_RSS_Set(m_pObj, 56+10000, iItemIndex, (LPVOID)lpszItemPubDate, 0);
    }

    inline LPWSTR GetItemSource(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 57+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemSource(INT iItemIndex, LPCWSTR lpszItemSource) {
      return IPWorks_RSS_Set(m_pObj, 57+10000, iItemIndex, (LPVOID)lpszItemSource, 0);
    }

    inline LPWSTR GetItemSourceURL(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 58+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemSourceURL(INT iItemIndex, LPCWSTR lpszItemSourceURL) {
      return IPWorks_RSS_Set(m_pObj, 58+10000, iItemIndex, (LPVOID)lpszItemSourceURL, 0);
    }

    inline LPWSTR GetItemTitle(INT iItemIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 59+10000, iItemIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetItemTitle(INT iItemIndex, LPCWSTR lpszItemTitle) {
      return IPWorks_RSS_Set(m_pObj, 59+10000, iItemIndex, (LPVOID)lpszItemTitle, 0);
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 60+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_RSS_Set(m_pObj, 60+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 61+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_RSS_Set(m_pObj, 61+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetNamespaceCount() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 62, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetNamespaceCount(INT iNamespaceCount) {
      LPVOID val = (LPVOID)(iNamespaceCount);
      return IPWorks_RSS_Set(m_pObj, 62, 0, val, 0);
    }

    inline LPWSTR GetNamespacePrefix(INT iNamespaceIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 63+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNamespacePrefix(INT iNamespaceIndex, LPCWSTR lpszNamespacePrefix) {
      return IPWorks_RSS_Set(m_pObj, 63+10000, iNamespaceIndex, (LPVOID)lpszNamespacePrefix, 0);
    }

    inline LPWSTR GetNamespaceURI(INT iNamespaceIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 64+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNamespaceURI(INT iNamespaceIndex, LPCWSTR lpszNamespaceURI) {
      return IPWorks_RSS_Set(m_pObj, 64+10000, iNamespaceIndex, (LPVOID)lpszNamespaceURI, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 65+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_RSS_Set(m_pObj, 65+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline INT GetParsedHeaderCount() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 66, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetParsedHeaderField(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 67+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetParsedHeaderValue(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 68+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 69+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_RSS_Set(m_pObj, 69+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetProxyAuthScheme() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 70, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyAuthScheme(INT iProxyAuthScheme) {
      LPVOID val = (LPVOID)(iProxyAuthScheme);
      return IPWorks_RSS_Set(m_pObj, 70, 0, val, 0);
    }

    inline BOOL GetProxyAutoDetect() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 71, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetProxyAutoDetect(BOOL bProxyAutoDetect) {
      LPVOID val = (LPVOID)(bProxyAutoDetect);
      return IPWorks_RSS_Set(m_pObj, 71, 0, val, 0);
    }

    inline LPWSTR GetProxyPassword() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 72+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyPassword(LPCWSTR lpszProxyPassword) {
      return IPWorks_RSS_Set(m_pObj, 72+10000, 0, (LPVOID)lpszProxyPassword, 0);
    }

    inline INT GetProxyPort() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 73, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyPort(INT iProxyPort) {
      LPVOID val = (LPVOID)(iProxyPort);
      return IPWorks_RSS_Set(m_pObj, 73, 0, val, 0);
    }

    inline LPWSTR GetProxyServer() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 74+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyServer(LPCWSTR lpszProxyServer) {
      return IPWorks_RSS_Set(m_pObj, 74+10000, 0, (LPVOID)lpszProxyServer, 0);
    }

    inline INT GetProxySSL() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 75, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxySSL(INT iProxySSL) {
      LPVOID val = (LPVOID)(iProxySSL);
      return IPWorks_RSS_Set(m_pObj, 75, 0, val, 0);
    }

    inline LPWSTR GetProxyUser() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 76+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyUser(LPCWSTR lpszProxyUser) {
      return IPWorks_RSS_Set(m_pObj, 76+10000, 0, (LPVOID)lpszProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 77+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReferer(LPCWSTR lpszReferer) {
      return IPWorks_RSS_Set(m_pObj, 77+10000, 0, (LPVOID)lpszReferer, 0);
    }

    inline LPWSTR GetRSSData() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 78+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRSSData(LPCWSTR lpszRSSData) {
      return IPWorks_RSS_Set(m_pObj, 78+10000, 0, (LPVOID)lpszRSSData, 0);
    }

    inline INT GetRSSVersion() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 79, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRSSVersion(INT iRSSVersion) {
      LPVOID val = (LPVOID)(iRSSVersion);
      return IPWorks_RSS_Set(m_pObj, 79, 0, val, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_RSS_Get(m_pObj, 80, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_RSS_Set(m_pObj, 80, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_RSS_Get(m_pObj, 81, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_RSS_Set(m_pObj, 81, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_RSS_Get(m_pObj, 82, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_RSS_Set(m_pObj, 82, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 83+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_RSS_Set(m_pObj, 83+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 84, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_RSS_Set(m_pObj, 84, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 85+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_RSS_Set(m_pObj, 85+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_RSS_Get(m_pObj, 86, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 87, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_RSS_Set(m_pObj, 87, 0, val, 0);
    }

    inline INT GetTransferredData(LPSTR &lpTransferredData, INT &lenTransferredData) {
      lpTransferredData = (LPSTR)IPWorks_RSS_Get(m_pObj, 88, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline LONG64 GetTransferredDataLimit() {
      LONG64 retVal;
      IPWorks_RSS_Get(m_pObj, 89, 0, NULL, &retVal);
      return retVal;
    }
    inline INT SetTransferredDataLimit(LONG64 lTransferredDataLimit) {
      LPVOID val = (LPVOID)(&lTransferredDataLimit);
      return IPWorks_RSS_Set(m_pObj, 89, 0, val, 0);
    }

    inline LPWSTR GetTransferredHeaders() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 90+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_RSS_Get(m_pObj, 91+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_RSS_Set(m_pObj, 91+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline INT AddCookie(LPCWSTR lpszCookieName, LPCWSTR lpszCookieValue) {
      LPVOID param[2+1] = {(LPVOID)lpszCookieName, (LPVOID)lpszCookieValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 2+10000, 2, param, cbparam, NULL);
    }

    inline INT AddItem(LPCWSTR lpszTitle, LPCWSTR lpszDescription, LPCWSTR lpszLink) {
      LPVOID param[3+1] = {(LPVOID)lpszTitle, (LPVOID)lpszDescription, (LPVOID)lpszLink, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 3+10000, 3, param, cbparam, NULL);
    }

    inline INT AddNamespace(LPCWSTR lpszPrefix, LPCWSTR lpszNamespaceURI) {
      LPVOID param[2+1] = {(LPVOID)lpszPrefix, (LPVOID)lpszNamespaceURI, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 4+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT GetFeed(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 7+10000, 1, param, cbparam, NULL);
    }

    inline LPWSTR GetProperty(LPCWSTR lpszPropertyName) {
      LPVOID param[1+1] = {(LPVOID)lpszPropertyName, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT GetURL(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 9+10000, 1, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR OPMLAttr(LPCWSTR lpszAttrName) {
      LPVOID param[1+1] = {(LPVOID)lpszAttrName, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 11+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Put(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 12+10000, 1, param, cbparam, NULL);
    }

    inline INT ReadFile(LPCWSTR lpszFileName) {
      LPVOID param[1+1] = {(LPVOID)lpszFileName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 13+10000, 1, param, cbparam, NULL);
    }

    inline INT ReadOPML(LPCWSTR lpszOPMLFile) {
      LPVOID param[1+1] = {(LPVOID)lpszOPMLFile, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 15+10000, 0, param, cbparam, NULL);
    }

    inline INT SetProperty(LPCWSTR lpszPropertyName, LPCWSTR lpszPropertyValue) {
      LPVOID param[2+1] = {(LPVOID)lpszPropertyName, (LPVOID)lpszPropertyValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 16+10000, 2, param, cbparam, NULL);
    }

    inline INT WriteFile(LPCWSTR lpszFilename) {
      LPVOID param[1+1] = {(LPVOID)lpszFilename, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 17+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_RSS_H_
