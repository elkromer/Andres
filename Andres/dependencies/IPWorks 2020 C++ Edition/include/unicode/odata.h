/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_ODATA_H_
#define _IPWORKS_ODATA_H_

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

//AtomTextTypes
#define TT_TEXT                                            0
#define TT_HTML                                            1
#define TT_XHTML                                           2

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TODataVersion
#define OD_V2                                              0
#define OD_V3                                              1
#define OD_V4                                              2
#define OD_AUTO                                            3

//ProxySSLTypes
#define PS_AUTOMATIC                                       0
#define PS_ALWAYS                                          1
#define PS_NEVER                                           2
#define PS_TUNNEL                                          3

//AssociationMultiplicities
#define NM_ZERO_ONE                                        0
#define NM_ONE                                             1
#define NM_MANY                                            2

//AssociationDeleteActions
#define DA_NONE                                            0
#define DA_CASCADE                                         1
#define DA_SET_NULL                                        2
#define DA_SET_DEFAULT                                     3

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


extern "C" void* IPWORKS_CALL IPWorks_OData_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_OData_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_OData_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_OData_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_OData_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_OData_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_OData_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_OData_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_OData_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} ODataConnectedEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} ODataDisconnectedEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} ODataEndTransferEventParams;

typedef struct {
  LPCWSTR Name;
  INT reserved;
} ODataEntityEventParams;

typedef struct {
  LPCWSTR Id;
  LPCWSTR Title;
  LPCWSTR Summary;
  LPCWSTR ETag;
  INT reserved;
} ODataEntryEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} ODataErrorEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} ODataHeaderEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} ODataLogEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR TypeName;
  BOOL Nullable;
  INT reserved;
} ODataPropertyEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR Value;
  LPCWSTR Expires;
  LPCWSTR Domain;
  LPCWSTR Path;
  BOOL Secure;
  INT reserved;
} ODataSetCookieEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} ODataSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} ODataSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} ODataStartTransferEventParams;

typedef struct {
  LPCWSTR HTTPVersion;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} ODataStatusEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  INT reserved;
} ODataTransferEventParams;


class OData {
  public: // Events
    virtual INT FireConnected(ODataConnectedEventParams *e) {return 0;}
    virtual INT FireDisconnected(ODataDisconnectedEventParams *e) {return 0;}
    virtual INT FireEndTransfer(ODataEndTransferEventParams *e) {return 0;}
    virtual INT FireEntity(ODataEntityEventParams *e) {return 0;}
    virtual INT FireEntry(ODataEntryEventParams *e) {return 0;}
    virtual INT FireError(ODataErrorEventParams *e) {return 0;}
    virtual INT FireHeader(ODataHeaderEventParams *e) {return 0;}
    virtual INT FireLog(ODataLogEventParams *e) {return 0;}
    virtual INT FireProperty(ODataPropertyEventParams *e) {return 0;}
    virtual INT FireSetCookie(ODataSetCookieEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(ODataSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(ODataSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(ODataStartTransferEventParams *e) {return 0;}
    virtual INT FireStatus(ODataStatusEventParams *e) {return 0;}
    virtual INT FireTransfer(ODataTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL ODataEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          ODataConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((OData*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          ODataDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((OData*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 3: {
          ODataEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((OData*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 4: {
          ODataEntityEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((OData*)lpObj)->FireEntity(&e);
          break;
        }
        case 5: {
          ODataEntryEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], 0};
          ret_code = ((OData*)lpObj)->FireEntry(&e);
          break;
        }
        case 6: {
          ODataErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((OData*)lpObj)->FireError(&e);
          break;
        }
        case 7: {
          ODataHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((OData*)lpObj)->FireHeader(&e);
          break;
        }
        case 8: {
          ODataLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((OData*)lpObj)->FireLog(&e);
          break;
        }
        case 9: {
          ODataPropertyEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (BOOL)param[2], 0};
          ret_code = ((OData*)lpObj)->FireProperty(&e);
          break;
        }
        case 10: {
          ODataSetCookieEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((OData*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 11: {
          ODataSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((OData*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 12: {
          ODataSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((OData*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 13: {
          ODataStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((OData*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 14: {
          ODataStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((OData*)lpObj)->FireStatus(&e);
          break;
        }
        case 15: {
          ODataTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], 0};
          ret_code = ((OData*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    OData(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_81) {
      m_pObj = IPWorks_OData_Create(ODataEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~OData() {
      IPWorks_OData_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_OData_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_OData_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_OData_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_OData_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_OData_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAuthorization() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorization(LPCWSTR lpszAuthorization) {
      return IPWorks_OData_Set(m_pObj, 1+10000, 0, (LPVOID)lpszAuthorization, 0);
    }

    inline INT GetAuthScheme() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 2, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthScheme(INT iAuthScheme) {
      LPVOID val = (LPVOID)(iAuthScheme);
      return IPWorks_OData_Set(m_pObj, 2, 0, val, 0);
    }

    inline LPWSTR GetChannelAuthorEmail() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelAuthorEmail(LPCWSTR lpszChannelAuthorEmail) {
      return IPWorks_OData_Set(m_pObj, 3+10000, 0, (LPVOID)lpszChannelAuthorEmail, 0);
    }

    inline LPWSTR GetChannelAuthorName() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelAuthorName(LPCWSTR lpszChannelAuthorName) {
      return IPWorks_OData_Set(m_pObj, 4+10000, 0, (LPVOID)lpszChannelAuthorName, 0);
    }

    inline LPWSTR GetChannelAuthorUri() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelAuthorUri(LPCWSTR lpszChannelAuthorUri) {
      return IPWorks_OData_Set(m_pObj, 5+10000, 0, (LPVOID)lpszChannelAuthorUri, 0);
    }

    inline LPWSTR GetChannelCategoryLabel() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelCategoryLabel(LPCWSTR lpszChannelCategoryLabel) {
      return IPWorks_OData_Set(m_pObj, 6+10000, 0, (LPVOID)lpszChannelCategoryLabel, 0);
    }

    inline LPWSTR GetChannelCategoryScheme() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelCategoryScheme(LPCWSTR lpszChannelCategoryScheme) {
      return IPWorks_OData_Set(m_pObj, 7+10000, 0, (LPVOID)lpszChannelCategoryScheme, 0);
    }

    inline LPWSTR GetChannelCategoryTerm() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelCategoryTerm(LPCWSTR lpszChannelCategoryTerm) {
      return IPWorks_OData_Set(m_pObj, 8+10000, 0, (LPVOID)lpszChannelCategoryTerm, 0);
    }

    inline LPWSTR GetChannelContributorEmail() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelContributorEmail(LPCWSTR lpszChannelContributorEmail) {
      return IPWorks_OData_Set(m_pObj, 9+10000, 0, (LPVOID)lpszChannelContributorEmail, 0);
    }

    inline LPWSTR GetChannelContributorName() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelContributorName(LPCWSTR lpszChannelContributorName) {
      return IPWorks_OData_Set(m_pObj, 10+10000, 0, (LPVOID)lpszChannelContributorName, 0);
    }

    inline LPWSTR GetChannelContributorUri() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelContributorUri(LPCWSTR lpszChannelContributorUri) {
      return IPWorks_OData_Set(m_pObj, 11+10000, 0, (LPVOID)lpszChannelContributorUri, 0);
    }

    inline LPWSTR GetChannelGenerator() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelGenerator(LPCWSTR lpszChannelGenerator) {
      return IPWorks_OData_Set(m_pObj, 12+10000, 0, (LPVOID)lpszChannelGenerator, 0);
    }

    inline LPWSTR GetChannelIcon() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelIcon(LPCWSTR lpszChannelIcon) {
      return IPWorks_OData_Set(m_pObj, 13+10000, 0, (LPVOID)lpszChannelIcon, 0);
    }

    inline LPWSTR GetChannelId() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelId(LPCWSTR lpszChannelId) {
      return IPWorks_OData_Set(m_pObj, 14+10000, 0, (LPVOID)lpszChannelId, 0);
    }

    inline LPWSTR GetChannelLinkHref() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkHref(LPCWSTR lpszChannelLinkHref) {
      return IPWorks_OData_Set(m_pObj, 15+10000, 0, (LPVOID)lpszChannelLinkHref, 0);
    }

    inline LPWSTR GetChannelLinkHrefLang() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkHrefLang(LPCWSTR lpszChannelLinkHrefLang) {
      return IPWorks_OData_Set(m_pObj, 16+10000, 0, (LPVOID)lpszChannelLinkHrefLang, 0);
    }

    inline LPWSTR GetChannelLinkLength() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkLength(LPCWSTR lpszChannelLinkLength) {
      return IPWorks_OData_Set(m_pObj, 17+10000, 0, (LPVOID)lpszChannelLinkLength, 0);
    }

    inline LPWSTR GetChannelLinkRel() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkRel(LPCWSTR lpszChannelLinkRel) {
      return IPWorks_OData_Set(m_pObj, 18+10000, 0, (LPVOID)lpszChannelLinkRel, 0);
    }

    inline LPWSTR GetChannelLinkTitle() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkTitle(LPCWSTR lpszChannelLinkTitle) {
      return IPWorks_OData_Set(m_pObj, 19+10000, 0, (LPVOID)lpszChannelLinkTitle, 0);
    }

    inline LPWSTR GetChannelLinkType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkType(LPCWSTR lpszChannelLinkType) {
      return IPWorks_OData_Set(m_pObj, 20+10000, 0, (LPVOID)lpszChannelLinkType, 0);
    }

    inline LPWSTR GetChannelLogo() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLogo(LPCWSTR lpszChannelLogo) {
      return IPWorks_OData_Set(m_pObj, 21+10000, 0, (LPVOID)lpszChannelLogo, 0);
    }

    inline LPWSTR GetChannelRights() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelRights(LPCWSTR lpszChannelRights) {
      return IPWorks_OData_Set(m_pObj, 22+10000, 0, (LPVOID)lpszChannelRights, 0);
    }

    inline INT GetChannelRightsTextType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 23, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetChannelRightsTextType(INT iChannelRightsTextType) {
      LPVOID val = (LPVOID)(iChannelRightsTextType);
      return IPWorks_OData_Set(m_pObj, 23, 0, val, 0);
    }

    inline LPWSTR GetChannelSubtitle() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelSubtitle(LPCWSTR lpszChannelSubtitle) {
      return IPWorks_OData_Set(m_pObj, 24+10000, 0, (LPVOID)lpszChannelSubtitle, 0);
    }

    inline INT GetChannelSubtitleTextType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 25, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetChannelSubtitleTextType(INT iChannelSubtitleTextType) {
      LPVOID val = (LPVOID)(iChannelSubtitleTextType);
      return IPWorks_OData_Set(m_pObj, 25, 0, val, 0);
    }

    inline LPWSTR GetChannelTitle() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelTitle(LPCWSTR lpszChannelTitle) {
      return IPWorks_OData_Set(m_pObj, 26+10000, 0, (LPVOID)lpszChannelTitle, 0);
    }

    inline INT GetChannelTitleTextType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 27, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetChannelTitleTextType(INT iChannelTitleTextType) {
      LPVOID val = (LPVOID)(iChannelTitleTextType);
      return IPWorks_OData_Set(m_pObj, 27, 0, val, 0);
    }

    inline LPWSTR GetChannelUpdated() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 28+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelUpdated(LPCWSTR lpszChannelUpdated) {
      return IPWorks_OData_Set(m_pObj, 28+10000, 0, (LPVOID)lpszChannelUpdated, 0);
    }

    inline INT GetCookieCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 29, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCookieCount(INT iCookieCount) {
      LPVOID val = (LPVOID)(iCookieCount);
      return IPWorks_OData_Set(m_pObj, 29, 0, val, 0);
    }

    inline LPWSTR GetCookieDomain(INT iCookieIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 30+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieExpiration(INT iCookieIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 31+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieName(INT iCookieIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 32+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieName(INT iCookieIndex, LPCWSTR lpszCookieName) {
      return IPWorks_OData_Set(m_pObj, 32+10000, iCookieIndex, (LPVOID)lpszCookieName, 0);
    }

    inline LPWSTR GetCookiePath(INT iCookieIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 33+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCookieSecure(INT iCookieIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 34, iCookieIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCookieValue(INT iCookieIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 35+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieValue(INT iCookieIndex, LPCWSTR lpszCookieValue) {
      return IPWorks_OData_Set(m_pObj, 35+10000, iCookieIndex, (LPVOID)lpszCookieValue, 0);
    }

    inline LPWSTR GetEntryAuthor() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 36+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryAuthor(LPCWSTR lpszEntryAuthor) {
      return IPWorks_OData_Set(m_pObj, 36+10000, 0, (LPVOID)lpszEntryAuthor, 0);
    }

    inline INT GetEntryCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 37, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetEntryETag() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 38+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryETag(LPCWSTR lpszEntryETag) {
      return IPWorks_OData_Set(m_pObj, 38+10000, 0, (LPVOID)lpszEntryETag, 0);
    }

    inline LPWSTR GetEntryId() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 39+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryId(LPCWSTR lpszEntryId) {
      return IPWorks_OData_Set(m_pObj, 39+10000, 0, (LPVOID)lpszEntryId, 0);
    }

    inline INT GetEntryIndex() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 40, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetEntryIndex(INT iEntryIndex) {
      LPVOID val = (LPVOID)(iEntryIndex);
      return IPWorks_OData_Set(m_pObj, 40, 0, val, 0);
    }

    inline INT GetEntryLinksCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 41, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetEntryLinksCount(INT iEntryLinksCount) {
      LPVOID val = (LPVOID)(iEntryLinksCount);
      return IPWorks_OData_Set(m_pObj, 41, 0, val, 0);
    }

    inline LPWSTR GetEntryLinksResourcePath(INT iEntryLinksIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 42+10000, iEntryLinksIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetEntryLinksTitle(INT iEntryLinksIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 43+10000, iEntryLinksIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetEntryPropertiesCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 44, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetEntryPropertiesCount(INT iEntryPropertiesCount) {
      LPVOID val = (LPVOID)(iEntryPropertiesCount);
      return IPWorks_OData_Set(m_pObj, 44, 0, val, 0);
    }

    inline LPWSTR GetEntryPropertiesAttributes(INT iEntryPropertiesIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 45+10000, iEntryPropertiesIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryPropertiesAttributes(INT iEntryPropertiesIndex, LPCWSTR lpszEntryPropertiesAttributes) {
      return IPWorks_OData_Set(m_pObj, 45+10000, iEntryPropertiesIndex, (LPVOID)lpszEntryPropertiesAttributes, 0);
    }

    inline BOOL GetEntryPropertiesIsNull(INT iEntryPropertiesIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 46, iEntryPropertiesIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetEntryPropertiesIsNull(INT iEntryPropertiesIndex, BOOL bEntryPropertiesIsNull) {
      LPVOID val = (LPVOID)(bEntryPropertiesIsNull);
      return IPWorks_OData_Set(m_pObj, 46, iEntryPropertiesIndex, val, 0);
    }

    inline LPWSTR GetEntryPropertiesName(INT iEntryPropertiesIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 47+10000, iEntryPropertiesIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryPropertiesName(INT iEntryPropertiesIndex, LPCWSTR lpszEntryPropertiesName) {
      return IPWorks_OData_Set(m_pObj, 47+10000, iEntryPropertiesIndex, (LPVOID)lpszEntryPropertiesName, 0);
    }

    inline LPWSTR GetEntryPropertiesType(INT iEntryPropertiesIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 48+10000, iEntryPropertiesIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryPropertiesType(INT iEntryPropertiesIndex, LPCWSTR lpszEntryPropertiesType) {
      return IPWorks_OData_Set(m_pObj, 48+10000, iEntryPropertiesIndex, (LPVOID)lpszEntryPropertiesType, 0);
    }

    inline LPWSTR GetEntryPropertiesValue(INT iEntryPropertiesIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 49+10000, iEntryPropertiesIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryPropertiesValue(INT iEntryPropertiesIndex, LPCWSTR lpszEntryPropertiesValue) {
      return IPWorks_OData_Set(m_pObj, 49+10000, iEntryPropertiesIndex, (LPVOID)lpszEntryPropertiesValue, 0);
    }

    inline LPWSTR GetEntryPropertiesXPath(INT iEntryPropertiesIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 50+10000, iEntryPropertiesIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetEntrySummary() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 51+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntrySummary(LPCWSTR lpszEntrySummary) {
      return IPWorks_OData_Set(m_pObj, 51+10000, 0, (LPVOID)lpszEntrySummary, 0);
    }

    inline LPWSTR GetEntryTitle() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 52+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryTitle(LPCWSTR lpszEntryTitle) {
      return IPWorks_OData_Set(m_pObj, 52+10000, 0, (LPVOID)lpszEntryTitle, 0);
    }

    inline LPWSTR GetEntryType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 53+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryType(LPCWSTR lpszEntryType) {
      return IPWorks_OData_Set(m_pObj, 53+10000, 0, (LPVOID)lpszEntryType, 0);
    }

    inline LPWSTR GetEntryUpdated() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 54+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetEntryXML() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 55+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryXML(LPCWSTR lpszEntryXML) {
      return IPWorks_OData_Set(m_pObj, 55+10000, 0, (LPVOID)lpszEntryXML, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 56, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_OData_Set(m_pObj, 56, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 57, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_OData_Set(m_pObj, 57, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 58+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_OData_Set(m_pObj, 58+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 59+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_OData_Set(m_pObj, 59+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 60, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_OData_Set(m_pObj, 60, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 61+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_OData_Set(m_pObj, 61+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 62, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 63+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_OData_Set(m_pObj, 63+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetODataVersion() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 64, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetODataVersion(INT iODataVersion) {
      LPVOID val = (LPVOID)(iODataVersion);
      return IPWorks_OData_Set(m_pObj, 64, 0, val, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 65+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_OData_Set(m_pObj, 65+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline LPWSTR GetOtherQueryOptions() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 66+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherQueryOptions(LPCWSTR lpszOtherQueryOptions) {
      return IPWorks_OData_Set(m_pObj, 66+10000, 0, (LPVOID)lpszOtherQueryOptions, 0);
    }

    inline INT GetParsedHeaderCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 67, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetParsedHeaderField(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 68+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetParsedHeaderValue(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 69+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 70+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_OData_Set(m_pObj, 70+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetProxyAuthScheme() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 71, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyAuthScheme(INT iProxyAuthScheme) {
      LPVOID val = (LPVOID)(iProxyAuthScheme);
      return IPWorks_OData_Set(m_pObj, 71, 0, val, 0);
    }

    inline BOOL GetProxyAutoDetect() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 72, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetProxyAutoDetect(BOOL bProxyAutoDetect) {
      LPVOID val = (LPVOID)(bProxyAutoDetect);
      return IPWorks_OData_Set(m_pObj, 72, 0, val, 0);
    }

    inline LPWSTR GetProxyPassword() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 73+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyPassword(LPCWSTR lpszProxyPassword) {
      return IPWorks_OData_Set(m_pObj, 73+10000, 0, (LPVOID)lpszProxyPassword, 0);
    }

    inline INT GetProxyPort() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 74, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyPort(INT iProxyPort) {
      LPVOID val = (LPVOID)(iProxyPort);
      return IPWorks_OData_Set(m_pObj, 74, 0, val, 0);
    }

    inline LPWSTR GetProxyServer() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 75+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyServer(LPCWSTR lpszProxyServer) {
      return IPWorks_OData_Set(m_pObj, 75+10000, 0, (LPVOID)lpszProxyServer, 0);
    }

    inline INT GetProxySSL() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 76, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxySSL(INT iProxySSL) {
      LPVOID val = (LPVOID)(iProxySSL);
      return IPWorks_OData_Set(m_pObj, 76, 0, val, 0);
    }

    inline LPWSTR GetProxyUser() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 77+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyUser(LPCWSTR lpszProxyUser) {
      return IPWorks_OData_Set(m_pObj, 77+10000, 0, (LPVOID)lpszProxyUser, 0);
    }

    inline LPWSTR GetQueryFilter() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 78+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetQueryFilter(LPCWSTR lpszQueryFilter) {
      return IPWorks_OData_Set(m_pObj, 78+10000, 0, (LPVOID)lpszQueryFilter, 0);
    }

    inline LPWSTR GetQueryOrderBy() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 79+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetQueryOrderBy(LPCWSTR lpszQueryOrderBy) {
      return IPWorks_OData_Set(m_pObj, 79+10000, 0, (LPVOID)lpszQueryOrderBy, 0);
    }

    inline LPWSTR GetQuerySelect() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 80+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetQuerySelect(LPCWSTR lpszQuerySelect) {
      return IPWorks_OData_Set(m_pObj, 80+10000, 0, (LPVOID)lpszQuerySelect, 0);
    }

    inline LPWSTR GetQuerySkip() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 81+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetQuerySkip(LPCWSTR lpszQuerySkip) {
      return IPWorks_OData_Set(m_pObj, 81+10000, 0, (LPVOID)lpszQuerySkip, 0);
    }

    inline LPWSTR GetQuerySkipToken() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 82+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetQuerySkipToken(LPCWSTR lpszQuerySkipToken) {
      return IPWorks_OData_Set(m_pObj, 82+10000, 0, (LPVOID)lpszQuerySkipToken, 0);
    }

    inline LPWSTR GetQueryTop() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 83+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetQueryTop(LPCWSTR lpszQueryTop) {
      return IPWorks_OData_Set(m_pObj, 83+10000, 0, (LPVOID)lpszQueryTop, 0);
    }

    inline LPWSTR GetResourcePath() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 84+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetResourcePath(LPCWSTR lpszResourcePath) {
      return IPWorks_OData_Set(m_pObj, 84+10000, 0, (LPVOID)lpszResourcePath, 0);
    }

    inline BOOL GetSchemaAssociationContainsTarget() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 85, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetSchemaAssociationDescription() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 86+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationFromRole() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 87+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationFromRoleDescription() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 88+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationFromRoleEntity() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 89+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetSchemaAssociationFromRoleMultiplicity() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 90, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetSchemaAssociationFromRoleSummary() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 91+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationName() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 92+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetSchemaAssociationNullable() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 93, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline INT GetSchemaAssociationOnDelete() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 94, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetSchemaAssociationPartner() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 95+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetSchemaAssociationRefConstraintCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 96, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetSchemaAssociationRefConstraintIndex() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 97, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSchemaAssociationRefConstraintIndex(INT iSchemaAssociationRefConstraintIndex) {
      LPVOID val = (LPVOID)(iSchemaAssociationRefConstraintIndex);
      return IPWorks_OData_Set(m_pObj, 97, 0, val, 0);
    }

    inline LPWSTR GetSchemaAssociationRefConstraintProperty() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 98+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationRefConstraintReferencedProperty() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 99+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationRelationship() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 100+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationSummary() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 101+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationToRole() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 102+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationToRoleDescription() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 103+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationToRoleEntity() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 104+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetSchemaAssociationToRoleMultiplicity() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 105, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetSchemaAssociationToRoleSummary() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 106+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaAssociationType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 107+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetSchemaAssociationCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 108, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetSchemaAssociationIndex() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 109, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSchemaAssociationIndex(INT iSchemaAssociationIndex) {
      LPVOID val = (LPVOID)(iSchemaAssociationIndex);
      return IPWorks_OData_Set(m_pObj, 109, 0, val, 0);
    }

    inline LPWSTR GetSchemaEntityDescription() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 110+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaEntityName() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 111+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaEntitySummary() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 112+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetSchemaEntityCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 113, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetSchemaEntityIndex() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 114, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSchemaEntityIndex(INT iSchemaEntityIndex) {
      LPVOID val = (LPVOID)(iSchemaEntityIndex);
      return IPWorks_OData_Set(m_pObj, 114, 0, val, 0);
    }

    inline INT GetSchemaKeysCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 115, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetSchemaKeys(INT iSchemaKeysIndex) {
      LPVOID val = IPWorks_OData_Get(m_pObj, 116+10000, iSchemaKeysIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaPropertyAttributes() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 117+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaPropertyDescription() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 118+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetSchemaPropertyIsComplexType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 119, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetSchemaPropertyName() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 120+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetSchemaPropertyNullable() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 121, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetSchemaPropertySummary() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 122+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaPropertyType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 123+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetSchemaPropertyCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 124, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetSchemaPropertyIndex() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 125, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSchemaPropertyIndex(INT iSchemaPropertyIndex) {
      LPVOID val = (LPVOID)(iSchemaPropertyIndex);
      return IPWorks_OData_Set(m_pObj, 125, 0, val, 0);
    }

    inline LPWSTR GetSchemaTypeFieldAttributes() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 126+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaTypeFieldDescription() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 127+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetSchemaTypeFieldIsComplexType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 128, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetSchemaTypeFieldName() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 129+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetSchemaTypeFieldNullable() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 130, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetSchemaTypeFieldSummary() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 131+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSchemaTypeFieldType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 132+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetSchemaTypeFieldCount() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 133, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetSchemaTypeFieldIndex() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 134, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSchemaTypeFieldIndex(INT iSchemaTypeFieldIndex) {
      LPVOID val = (LPVOID)(iSchemaTypeFieldIndex);
      return IPWorks_OData_Set(m_pObj, 134, 0, val, 0);
    }

    inline LPWSTR GetServiceRootURI() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 135+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetServiceRootURI(LPCWSTR lpszServiceRootURI) {
      return IPWorks_OData_Set(m_pObj, 135+10000, 0, (LPVOID)lpszServiceRootURI, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_OData_Get(m_pObj, 136, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_OData_Set(m_pObj, 136, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_OData_Get(m_pObj, 137, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_OData_Set(m_pObj, 137, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_OData_Get(m_pObj, 138, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_OData_Set(m_pObj, 138, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 139+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_OData_Set(m_pObj, 139+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 140, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_OData_Set(m_pObj, 140, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 141+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_OData_Set(m_pObj, 141+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_OData_Get(m_pObj, 142, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 143, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_OData_Set(m_pObj, 143, 0, val, 0);
    }

    inline INT GetTransferredData(LPSTR &lpTransferredData, INT &lenTransferredData) {
      lpTransferredData = (LPSTR)IPWorks_OData_Get(m_pObj, 144, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_OData_Get(m_pObj, 145+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_OData_Set(m_pObj, 145+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT CreateEntry() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT CustomRequest(LPCWSTR lpszHTTPMethod, LPCWSTR lpszURL, LPCWSTR lpszPostData) {
      LPVOID param[3+1] = {(LPVOID)lpszHTTPMethod, (LPVOID)lpszURL, (LPVOID)lpszPostData, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 4+10000, 3, param, cbparam, NULL);
    }

    inline INT DeleteEntry() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR GetEntryProperty(LPCWSTR lpszXPath) {
      LPVOID param[1+1] = {(LPVOID)lpszXPath, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT GetSchema() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT HasXPath(LPCWSTR lpszXPath) {
      LPVOID param[1+1] = {(LPVOID)lpszXPath, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
      return (BOOL)param[1];
    }

    inline INT QueryService() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT SetEntryProperty(LPCWSTR lpszXPath, LPCWSTR lpszValue) {
      LPVOID param[2+1] = {(LPVOID)lpszXPath, (LPVOID)lpszValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 11+10000, 2, param, cbparam, NULL);
    }

    inline INT SetSchemaEntity(LPCWSTR lpszName) {
      LPVOID param[1+1] = {(LPVOID)lpszName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 12+10000, 1, param, cbparam, NULL);
    }

    inline INT SetSchemaProperty(LPCWSTR lpszName) {
      LPVOID param[1+1] = {(LPVOID)lpszName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 13+10000, 1, param, cbparam, NULL);
    }

    inline INT SetSchemaType(LPCWSTR lpszName) {
      LPVOID param[1+1] = {(LPVOID)lpszName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
    }

    inline INT UpdateEntry() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 15+10000, 0, param, cbparam, NULL);
    }

    inline INT UpdateProperty(LPCWSTR lpszXPath, LPCWSTR lpszValue) {
      LPVOID param[2+1] = {(LPVOID)lpszXPath, (LPVOID)lpszValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 16+10000, 2, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_ODATA_H_
