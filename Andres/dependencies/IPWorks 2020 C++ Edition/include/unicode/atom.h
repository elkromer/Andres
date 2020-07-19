/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_ATOM_H_
#define _IPWORKS_ATOM_H_

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


extern "C" void* IPWORKS_CALL IPWorks_Atom_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_Atom_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Atom_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_Atom_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Atom_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_Atom_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_Atom_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_Atom_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Atom_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} AtomConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} AtomConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} AtomDisconnectedEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} AtomEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} AtomErrorEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} AtomHeaderEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} AtomLogEventParams;

typedef struct {
  LPCWSTR Location;
  BOOL Accept;
  INT reserved;
} AtomRedirectEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR Value;
  LPCWSTR Expires;
  LPCWSTR Domain;
  LPCWSTR Path;
  BOOL Secure;
  INT reserved;
} AtomSetCookieEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} AtomSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} AtomSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} AtomStartTransferEventParams;

typedef struct {
  LPCWSTR HTTPVersion;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} AtomStatusEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  INT reserved;
} AtomTransferEventParams;


class Atom {
  public: // Events
    virtual INT FireConnected(AtomConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(AtomConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(AtomDisconnectedEventParams *e) {return 0;}
    virtual INT FireEndTransfer(AtomEndTransferEventParams *e) {return 0;}
    virtual INT FireError(AtomErrorEventParams *e) {return 0;}
    virtual INT FireHeader(AtomHeaderEventParams *e) {return 0;}
    virtual INT FireLog(AtomLogEventParams *e) {return 0;}
    virtual INT FireRedirect(AtomRedirectEventParams *e) {return 0;}
    virtual INT FireSetCookie(AtomSetCookieEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(AtomSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(AtomSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(AtomStartTransferEventParams *e) {return 0;}
    virtual INT FireStatus(AtomStatusEventParams *e) {return 0;}
    virtual INT FireTransfer(AtomTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL AtomEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          AtomConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Atom*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          AtomConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((Atom*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          AtomDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Atom*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          AtomEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((Atom*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          AtomErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Atom*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          AtomHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((Atom*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          AtomLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((Atom*)lpObj)->FireLog(&e);
          break;
        }
        case 8: {
          AtomRedirectEventParams e = {(LPWSTR)param[0], (BOOL)param[1], 0};
          ret_code = ((Atom*)lpObj)->FireRedirect(&e);
          param[1] = (LPVOID)e.Accept;
          break;
        }
        case 9: {
          AtomSetCookieEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((Atom*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 10: {
          AtomSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((Atom*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 11: {
          AtomSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((Atom*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 12: {
          AtomStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((Atom*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 13: {
          AtomStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((Atom*)lpObj)->FireStatus(&e);
          break;
        }
        case 14: {
          AtomTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], 0};
          ret_code = ((Atom*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    Atom(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_69) {
      m_pObj = IPWorks_Atom_Create(AtomEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~Atom() {
      IPWorks_Atom_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_Atom_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_Atom_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_Atom_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_Atom_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_Atom_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAccept() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAccept(LPCWSTR lpszAccept) {
      return IPWorks_Atom_Set(m_pObj, 1+10000, 0, (LPVOID)lpszAccept, 0);
    }

    inline INT GetAtomData(LPSTR &lpAtomData, INT &lenAtomData) {
      lpAtomData = (LPSTR)IPWorks_Atom_Get(m_pObj, 2, 0, &lenAtomData, NULL);
      return lpAtomData ? 0 : lenAtomData;
    }
    inline INT SetAtomData(LPCSTR lpAtomData, INT lenAtomData) {
      return IPWorks_Atom_Set(m_pObj, 2, 0, (LPVOID)lpAtomData, lenAtomData);
    }

    inline LPWSTR GetAuthorization() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorization(LPCWSTR lpszAuthorization) {
      return IPWorks_Atom_Set(m_pObj, 3+10000, 0, (LPVOID)lpszAuthorization, 0);
    }

    inline INT GetAuthScheme() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthScheme(INT iAuthScheme) {
      LPVOID val = (LPVOID)(iAuthScheme);
      return IPWorks_Atom_Set(m_pObj, 4, 0, val, 0);
    }

    inline LPWSTR GetChannelAuthorEmail() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelAuthorEmail(LPCWSTR lpszChannelAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 5+10000, 0, (LPVOID)lpszChannelAuthorEmail, 0);
    }

    inline LPWSTR GetChannelAuthorName() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelAuthorName(LPCWSTR lpszChannelAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 6+10000, 0, (LPVOID)lpszChannelAuthorName, 0);
    }

    inline LPWSTR GetChannelAuthorUri() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelAuthorUri(LPCWSTR lpszChannelAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 7+10000, 0, (LPVOID)lpszChannelAuthorUri, 0);
    }

    inline LPWSTR GetChannelCategoryLabel() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelCategoryLabel(LPCWSTR lpszChannelCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 8+10000, 0, (LPVOID)lpszChannelCategoryLabel, 0);
    }

    inline LPWSTR GetChannelCategoryScheme() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelCategoryScheme(LPCWSTR lpszChannelCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 9+10000, 0, (LPVOID)lpszChannelCategoryScheme, 0);
    }

    inline LPWSTR GetChannelCategoryTerm() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelCategoryTerm(LPCWSTR lpszChannelCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 10+10000, 0, (LPVOID)lpszChannelCategoryTerm, 0);
    }

    inline LPWSTR GetChannelContributorEmail() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelContributorEmail(LPCWSTR lpszChannelContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 11+10000, 0, (LPVOID)lpszChannelContributorEmail, 0);
    }

    inline LPWSTR GetChannelContributorName() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelContributorName(LPCWSTR lpszChannelContributorName) {
      return IPWorks_Atom_Set(m_pObj, 12+10000, 0, (LPVOID)lpszChannelContributorName, 0);
    }

    inline LPWSTR GetChannelContributorUri() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelContributorUri(LPCWSTR lpszChannelContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 13+10000, 0, (LPVOID)lpszChannelContributorUri, 0);
    }

    inline LPWSTR GetChannelGenerator() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelGenerator(LPCWSTR lpszChannelGenerator) {
      return IPWorks_Atom_Set(m_pObj, 14+10000, 0, (LPVOID)lpszChannelGenerator, 0);
    }

    inline LPWSTR GetChannelIcon() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelIcon(LPCWSTR lpszChannelIcon) {
      return IPWorks_Atom_Set(m_pObj, 15+10000, 0, (LPVOID)lpszChannelIcon, 0);
    }

    inline LPWSTR GetChannelId() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelId(LPCWSTR lpszChannelId) {
      return IPWorks_Atom_Set(m_pObj, 16+10000, 0, (LPVOID)lpszChannelId, 0);
    }

    inline LPWSTR GetChannelLinkHref() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkHref(LPCWSTR lpszChannelLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 17+10000, 0, (LPVOID)lpszChannelLinkHref, 0);
    }

    inline LPWSTR GetChannelLinkHrefLang() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkHrefLang(LPCWSTR lpszChannelLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 18+10000, 0, (LPVOID)lpszChannelLinkHrefLang, 0);
    }

    inline LPWSTR GetChannelLinkLength() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkLength(LPCWSTR lpszChannelLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 19+10000, 0, (LPVOID)lpszChannelLinkLength, 0);
    }

    inline LPWSTR GetChannelLinkRel() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkRel(LPCWSTR lpszChannelLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 20+10000, 0, (LPVOID)lpszChannelLinkRel, 0);
    }

    inline LPWSTR GetChannelLinkTitle() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkTitle(LPCWSTR lpszChannelLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 21+10000, 0, (LPVOID)lpszChannelLinkTitle, 0);
    }

    inline LPWSTR GetChannelLinkType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLinkType(LPCWSTR lpszChannelLinkType) {
      return IPWorks_Atom_Set(m_pObj, 22+10000, 0, (LPVOID)lpszChannelLinkType, 0);
    }

    inline LPWSTR GetChannelLogo() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 23+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelLogo(LPCWSTR lpszChannelLogo) {
      return IPWorks_Atom_Set(m_pObj, 23+10000, 0, (LPVOID)lpszChannelLogo, 0);
    }

    inline LPWSTR GetChannelRights() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelRights(LPCWSTR lpszChannelRights) {
      return IPWorks_Atom_Set(m_pObj, 24+10000, 0, (LPVOID)lpszChannelRights, 0);
    }

    inline INT GetChannelRightsTextType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 25, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetChannelRightsTextType(INT iChannelRightsTextType) {
      LPVOID val = (LPVOID)(iChannelRightsTextType);
      return IPWorks_Atom_Set(m_pObj, 25, 0, val, 0);
    }

    inline LPWSTR GetChannelSubtitle() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelSubtitle(LPCWSTR lpszChannelSubtitle) {
      return IPWorks_Atom_Set(m_pObj, 26+10000, 0, (LPVOID)lpszChannelSubtitle, 0);
    }

    inline INT GetChannelSubtitleTextType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 27, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetChannelSubtitleTextType(INT iChannelSubtitleTextType) {
      LPVOID val = (LPVOID)(iChannelSubtitleTextType);
      return IPWorks_Atom_Set(m_pObj, 27, 0, val, 0);
    }

    inline LPWSTR GetChannelTitle() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 28+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelTitle(LPCWSTR lpszChannelTitle) {
      return IPWorks_Atom_Set(m_pObj, 28+10000, 0, (LPVOID)lpszChannelTitle, 0);
    }

    inline INT GetChannelTitleTextType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 29, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetChannelTitleTextType(INT iChannelTitleTextType) {
      LPVOID val = (LPVOID)(iChannelTitleTextType);
      return IPWorks_Atom_Set(m_pObj, 29, 0, val, 0);
    }

    inline LPWSTR GetChannelUpdated() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 30+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetChannelUpdated(LPCWSTR lpszChannelUpdated) {
      return IPWorks_Atom_Set(m_pObj, 30+10000, 0, (LPVOID)lpszChannelUpdated, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 31, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_Atom_Set(m_pObj, 31, 0, val, 0);
    }

    inline LPWSTR GetContentType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 32+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetContentType(LPCWSTR lpszContentType) {
      return IPWorks_Atom_Set(m_pObj, 32+10000, 0, (LPVOID)lpszContentType, 0);
    }

    inline INT GetCookieCount() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 33, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCookieCount(INT iCookieCount) {
      LPVOID val = (LPVOID)(iCookieCount);
      return IPWorks_Atom_Set(m_pObj, 33, 0, val, 0);
    }

    inline LPWSTR GetCookieDomain(INT iCookieIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 34+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieExpiration(INT iCookieIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 35+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieName(INT iCookieIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 36+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieName(INT iCookieIndex, LPCWSTR lpszCookieName) {
      return IPWorks_Atom_Set(m_pObj, 36+10000, iCookieIndex, (LPVOID)lpszCookieName, 0);
    }

    inline LPWSTR GetCookiePath(INT iCookieIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 37+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCookieSecure(INT iCookieIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 38, iCookieIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCookieValue(INT iCookieIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 39+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieValue(INT iCookieIndex, LPCWSTR lpszCookieValue) {
      return IPWorks_Atom_Set(m_pObj, 39+10000, iCookieIndex, (LPVOID)lpszCookieValue, 0);
    }

    inline INT GetEntryCount() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 40, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetEntryCount(INT iEntryCount) {
      LPVOID val = (LPVOID)(iEntryCount);
      return IPWorks_Atom_Set(m_pObj, 40, 0, val, 0);
    }

    inline LPWSTR GetEntryAuthorEmail(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 41+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryAuthorEmail(INT iEntryIndex, LPCWSTR lpszEntryAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 41+10000, iEntryIndex, (LPVOID)lpszEntryAuthorEmail, 0);
    }

    inline LPWSTR GetEntryAuthorName(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 42+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryAuthorName(INT iEntryIndex, LPCWSTR lpszEntryAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 42+10000, iEntryIndex, (LPVOID)lpszEntryAuthorName, 0);
    }

    inline LPWSTR GetEntryAuthorUri(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 43+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryAuthorUri(INT iEntryIndex, LPCWSTR lpszEntryAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 43+10000, iEntryIndex, (LPVOID)lpszEntryAuthorUri, 0);
    }

    inline LPWSTR GetEntryCategoryLabel(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 44+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryCategoryLabel(INT iEntryIndex, LPCWSTR lpszEntryCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 44+10000, iEntryIndex, (LPVOID)lpszEntryCategoryLabel, 0);
    }

    inline LPWSTR GetEntryCategoryScheme(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 45+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryCategoryScheme(INT iEntryIndex, LPCWSTR lpszEntryCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 45+10000, iEntryIndex, (LPVOID)lpszEntryCategoryScheme, 0);
    }

    inline LPWSTR GetEntryCategoryTerm(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 46+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryCategoryTerm(INT iEntryIndex, LPCWSTR lpszEntryCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 46+10000, iEntryIndex, (LPVOID)lpszEntryCategoryTerm, 0);
    }

    inline LPWSTR GetEntryContent(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 47+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryContent(INT iEntryIndex, LPCWSTR lpszEntryContent) {
      return IPWorks_Atom_Set(m_pObj, 47+10000, iEntryIndex, (LPVOID)lpszEntryContent, 0);
    }

    inline INT GetEntryContentTextType(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 48, iEntryIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetEntryContentTextType(INT iEntryIndex, INT iEntryContentTextType) {
      LPVOID val = (LPVOID)(iEntryContentTextType);
      return IPWorks_Atom_Set(m_pObj, 48, iEntryIndex, val, 0);
    }

    inline LPWSTR GetEntryContributorEmail(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 49+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryContributorEmail(INT iEntryIndex, LPCWSTR lpszEntryContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 49+10000, iEntryIndex, (LPVOID)lpszEntryContributorEmail, 0);
    }

    inline LPWSTR GetEntryContributorName(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 50+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryContributorName(INT iEntryIndex, LPCWSTR lpszEntryContributorName) {
      return IPWorks_Atom_Set(m_pObj, 50+10000, iEntryIndex, (LPVOID)lpszEntryContributorName, 0);
    }

    inline LPWSTR GetEntryContributorUri(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 51+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryContributorUri(INT iEntryIndex, LPCWSTR lpszEntryContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 51+10000, iEntryIndex, (LPVOID)lpszEntryContributorUri, 0);
    }

    inline LPWSTR GetEntryCopyright(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 52+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryCopyright(INT iEntryIndex, LPCWSTR lpszEntryCopyright) {
      return IPWorks_Atom_Set(m_pObj, 52+10000, iEntryIndex, (LPVOID)lpszEntryCopyright, 0);
    }

    inline LPWSTR GetEntryCreated(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 53+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryCreated(INT iEntryIndex, LPCWSTR lpszEntryCreated) {
      return IPWorks_Atom_Set(m_pObj, 53+10000, iEntryIndex, (LPVOID)lpszEntryCreated, 0);
    }

    inline LPWSTR GetEntryXML(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 54+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryXML(INT iEntryIndex, LPCWSTR lpszEntryXML) {
      return IPWorks_Atom_Set(m_pObj, 54+10000, iEntryIndex, (LPVOID)lpszEntryXML, 0);
    }

    inline LPWSTR GetEntryId(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 55+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryId(INT iEntryIndex, LPCWSTR lpszEntryId) {
      return IPWorks_Atom_Set(m_pObj, 55+10000, iEntryIndex, (LPVOID)lpszEntryId, 0);
    }

    inline LPWSTR GetEntryIssued(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 56+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryIssued(INT iEntryIndex, LPCWSTR lpszEntryIssued) {
      return IPWorks_Atom_Set(m_pObj, 56+10000, iEntryIndex, (LPVOID)lpszEntryIssued, 0);
    }

    inline LPWSTR GetEntryLinkHref(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 57+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryLinkHref(INT iEntryIndex, LPCWSTR lpszEntryLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 57+10000, iEntryIndex, (LPVOID)lpszEntryLinkHref, 0);
    }

    inline LPWSTR GetEntryLinkHrefLang(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 58+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryLinkHrefLang(INT iEntryIndex, LPCWSTR lpszEntryLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 58+10000, iEntryIndex, (LPVOID)lpszEntryLinkHrefLang, 0);
    }

    inline LPWSTR GetEntryLinkLength(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 59+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryLinkLength(INT iEntryIndex, LPCWSTR lpszEntryLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 59+10000, iEntryIndex, (LPVOID)lpszEntryLinkLength, 0);
    }

    inline LPWSTR GetEntryLinkRel(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 60+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryLinkRel(INT iEntryIndex, LPCWSTR lpszEntryLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 60+10000, iEntryIndex, (LPVOID)lpszEntryLinkRel, 0);
    }

    inline LPWSTR GetEntryLinkTitle(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 61+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryLinkTitle(INT iEntryIndex, LPCWSTR lpszEntryLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 61+10000, iEntryIndex, (LPVOID)lpszEntryLinkTitle, 0);
    }

    inline LPWSTR GetEntryLinkType(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 62+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryLinkType(INT iEntryIndex, LPCWSTR lpszEntryLinkType) {
      return IPWorks_Atom_Set(m_pObj, 62+10000, iEntryIndex, (LPVOID)lpszEntryLinkType, 0);
    }

    inline LPWSTR GetEntryModified(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 63+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryModified(INT iEntryIndex, LPCWSTR lpszEntryModified) {
      return IPWorks_Atom_Set(m_pObj, 63+10000, iEntryIndex, (LPVOID)lpszEntryModified, 0);
    }

    inline LPWSTR GetEntryPublished(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 64+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryPublished(INT iEntryIndex, LPCWSTR lpszEntryPublished) {
      return IPWorks_Atom_Set(m_pObj, 64+10000, iEntryIndex, (LPVOID)lpszEntryPublished, 0);
    }

    inline LPWSTR GetEntryRights(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 65+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryRights(INT iEntryIndex, LPCWSTR lpszEntryRights) {
      return IPWorks_Atom_Set(m_pObj, 65+10000, iEntryIndex, (LPVOID)lpszEntryRights, 0);
    }

    inline INT GetEntryRightsTextType(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 66, iEntryIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetEntryRightsTextType(INT iEntryIndex, INT iEntryRightsTextType) {
      LPVOID val = (LPVOID)(iEntryRightsTextType);
      return IPWorks_Atom_Set(m_pObj, 66, iEntryIndex, val, 0);
    }

    inline LPWSTR GetEntrySource(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 67+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntrySource(INT iEntryIndex, LPCWSTR lpszEntrySource) {
      return IPWorks_Atom_Set(m_pObj, 67+10000, iEntryIndex, (LPVOID)lpszEntrySource, 0);
    }

    inline LPWSTR GetEntrySummary(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 68+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntrySummary(INT iEntryIndex, LPCWSTR lpszEntrySummary) {
      return IPWorks_Atom_Set(m_pObj, 68+10000, iEntryIndex, (LPVOID)lpszEntrySummary, 0);
    }

    inline INT GetEntrySummaryTextType(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 69, iEntryIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetEntrySummaryTextType(INT iEntryIndex, INT iEntrySummaryTextType) {
      LPVOID val = (LPVOID)(iEntrySummaryTextType);
      return IPWorks_Atom_Set(m_pObj, 69, iEntryIndex, val, 0);
    }

    inline LPWSTR GetEntryTitle(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 70+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryTitle(INT iEntryIndex, LPCWSTR lpszEntryTitle) {
      return IPWorks_Atom_Set(m_pObj, 70+10000, iEntryIndex, (LPVOID)lpszEntryTitle, 0);
    }

    inline INT GetEntryTitleTextType(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 71, iEntryIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetEntryTitleTextType(INT iEntryIndex, INT iEntryTitleTextType) {
      LPVOID val = (LPVOID)(iEntryTitleTextType);
      return IPWorks_Atom_Set(m_pObj, 71, iEntryIndex, val, 0);
    }

    inline LPWSTR GetEntryUpdated(INT iEntryIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 72+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEntryUpdated(INT iEntryIndex, LPCWSTR lpszEntryUpdated) {
      return IPWorks_Atom_Set(m_pObj, 72+10000, iEntryIndex, (LPVOID)lpszEntryUpdated, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 73, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_Atom_Set(m_pObj, 73, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 74, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_Atom_Set(m_pObj, 74, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 75+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_Atom_Set(m_pObj, 75+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 76+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_Atom_Set(m_pObj, 76+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 77, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_Atom_Set(m_pObj, 77, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 78+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_Atom_Set(m_pObj, 78+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline INT GetFollowRedirects() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 79, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFollowRedirects(INT iFollowRedirects) {
      LPVOID val = (LPVOID)(iFollowRedirects);
      return IPWorks_Atom_Set(m_pObj, 79, 0, val, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 80, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetIfModifiedSince() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 81+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetIfModifiedSince(LPCWSTR lpszIfModifiedSince) {
      return IPWorks_Atom_Set(m_pObj, 81+10000, 0, (LPVOID)lpszIfModifiedSince, 0);
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 82+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_Atom_Set(m_pObj, 82+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 83+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_Atom_Set(m_pObj, 83+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetNamespaceCount() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 84, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetNamespaceCount(INT iNamespaceCount) {
      LPVOID val = (LPVOID)(iNamespaceCount);
      return IPWorks_Atom_Set(m_pObj, 84, 0, val, 0);
    }

    inline LPWSTR GetNamespacePrefix(INT iNamespaceIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 85+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNamespacePrefix(INT iNamespaceIndex, LPCWSTR lpszNamespacePrefix) {
      return IPWorks_Atom_Set(m_pObj, 85+10000, iNamespaceIndex, (LPVOID)lpszNamespacePrefix, 0);
    }

    inline LPWSTR GetNamespaceURI(INT iNamespaceIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 86+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNamespaceURI(INT iNamespaceIndex, LPCWSTR lpszNamespaceURI) {
      return IPWorks_Atom_Set(m_pObj, 86+10000, iNamespaceIndex, (LPVOID)lpszNamespaceURI, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 87+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_Atom_Set(m_pObj, 87+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline INT GetParsedHeaderCount() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 88, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetParsedHeaderField(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 89+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetParsedHeaderValue(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 90+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 91+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_Atom_Set(m_pObj, 91+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetProxyAuthScheme() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 92, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyAuthScheme(INT iProxyAuthScheme) {
      LPVOID val = (LPVOID)(iProxyAuthScheme);
      return IPWorks_Atom_Set(m_pObj, 92, 0, val, 0);
    }

    inline BOOL GetProxyAutoDetect() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 93, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetProxyAutoDetect(BOOL bProxyAutoDetect) {
      LPVOID val = (LPVOID)(bProxyAutoDetect);
      return IPWorks_Atom_Set(m_pObj, 93, 0, val, 0);
    }

    inline LPWSTR GetProxyPassword() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 94+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyPassword(LPCWSTR lpszProxyPassword) {
      return IPWorks_Atom_Set(m_pObj, 94+10000, 0, (LPVOID)lpszProxyPassword, 0);
    }

    inline INT GetProxyPort() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 95, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyPort(INT iProxyPort) {
      LPVOID val = (LPVOID)(iProxyPort);
      return IPWorks_Atom_Set(m_pObj, 95, 0, val, 0);
    }

    inline LPWSTR GetProxyServer() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 96+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyServer(LPCWSTR lpszProxyServer) {
      return IPWorks_Atom_Set(m_pObj, 96+10000, 0, (LPVOID)lpszProxyServer, 0);
    }

    inline INT GetProxySSL() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 97, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxySSL(INT iProxySSL) {
      LPVOID val = (LPVOID)(iProxySSL);
      return IPWorks_Atom_Set(m_pObj, 97, 0, val, 0);
    }

    inline LPWSTR GetProxyUser() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 98+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyUser(LPCWSTR lpszProxyUser) {
      return IPWorks_Atom_Set(m_pObj, 98+10000, 0, (LPVOID)lpszProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 99+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReferer(LPCWSTR lpszReferer) {
      return IPWorks_Atom_Set(m_pObj, 99+10000, 0, (LPVOID)lpszReferer, 0);
    }

    inline LPWSTR GetSlug() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 100+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSlug(LPCWSTR lpszSlug) {
      return IPWorks_Atom_Set(m_pObj, 100+10000, 0, (LPVOID)lpszSlug, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_Atom_Get(m_pObj, 101, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_Atom_Set(m_pObj, 101, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_Atom_Get(m_pObj, 102, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_Atom_Set(m_pObj, 102, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_Atom_Get(m_pObj, 103, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_Atom_Set(m_pObj, 103, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 104+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_Atom_Set(m_pObj, 104+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 105, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_Atom_Set(m_pObj, 105, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 106+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_Atom_Set(m_pObj, 106+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_Atom_Get(m_pObj, 107, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 108, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_Atom_Set(m_pObj, 108, 0, val, 0);
    }

    inline INT GetTransferredData(LPSTR &lpTransferredData, INT &lenTransferredData) {
      lpTransferredData = (LPSTR)IPWorks_Atom_Get(m_pObj, 109, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline LONG64 GetTransferredDataLimit() {
      LONG64 retVal;
      IPWorks_Atom_Get(m_pObj, 110, 0, NULL, &retVal);
      return retVal;
    }
    inline INT SetTransferredDataLimit(LONG64 lTransferredDataLimit) {
      LPVOID val = (LPVOID)(&lTransferredDataLimit);
      return IPWorks_Atom_Set(m_pObj, 110, 0, val, 0);
    }

    inline LPWSTR GetTransferredHeaders() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 111+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetUpdateEntryAuthorEmail() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 112+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryAuthorEmail(LPCWSTR lpszUpdateEntryAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 112+10000, 0, (LPVOID)lpszUpdateEntryAuthorEmail, 0);
    }

    inline LPWSTR GetUpdateEntryAuthorName() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 113+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryAuthorName(LPCWSTR lpszUpdateEntryAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 113+10000, 0, (LPVOID)lpszUpdateEntryAuthorName, 0);
    }

    inline LPWSTR GetUpdateEntryAuthorUri() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 114+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryAuthorUri(LPCWSTR lpszUpdateEntryAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 114+10000, 0, (LPVOID)lpszUpdateEntryAuthorUri, 0);
    }

    inline LPWSTR GetUpdateEntryCategoryLabel() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 115+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryCategoryLabel(LPCWSTR lpszUpdateEntryCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 115+10000, 0, (LPVOID)lpszUpdateEntryCategoryLabel, 0);
    }

    inline LPWSTR GetUpdateEntryCategoryScheme() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 116+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryCategoryScheme(LPCWSTR lpszUpdateEntryCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 116+10000, 0, (LPVOID)lpszUpdateEntryCategoryScheme, 0);
    }

    inline LPWSTR GetUpdateEntryCategoryTerm() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 117+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryCategoryTerm(LPCWSTR lpszUpdateEntryCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 117+10000, 0, (LPVOID)lpszUpdateEntryCategoryTerm, 0);
    }

    inline LPWSTR GetUpdateEntryContent() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 118+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryContent(LPCWSTR lpszUpdateEntryContent) {
      return IPWorks_Atom_Set(m_pObj, 118+10000, 0, (LPVOID)lpszUpdateEntryContent, 0);
    }

    inline INT GetUpdateEntryContentTextType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 119, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetUpdateEntryContentTextType(INT iUpdateEntryContentTextType) {
      LPVOID val = (LPVOID)(iUpdateEntryContentTextType);
      return IPWorks_Atom_Set(m_pObj, 119, 0, val, 0);
    }

    inline LPWSTR GetUpdateEntryContributorEmail() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 120+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryContributorEmail(LPCWSTR lpszUpdateEntryContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 120+10000, 0, (LPVOID)lpszUpdateEntryContributorEmail, 0);
    }

    inline LPWSTR GetUpdateEntryContributorName() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 121+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryContributorName(LPCWSTR lpszUpdateEntryContributorName) {
      return IPWorks_Atom_Set(m_pObj, 121+10000, 0, (LPVOID)lpszUpdateEntryContributorName, 0);
    }

    inline LPWSTR GetUpdateEntryContributorUri() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 122+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryContributorUri(LPCWSTR lpszUpdateEntryContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 122+10000, 0, (LPVOID)lpszUpdateEntryContributorUri, 0);
    }

    inline LPWSTR GetUpdateEntryCopyright() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 123+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryCopyright(LPCWSTR lpszUpdateEntryCopyright) {
      return IPWorks_Atom_Set(m_pObj, 123+10000, 0, (LPVOID)lpszUpdateEntryCopyright, 0);
    }

    inline LPWSTR GetUpdateEntryCreated() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 124+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryCreated(LPCWSTR lpszUpdateEntryCreated) {
      return IPWorks_Atom_Set(m_pObj, 124+10000, 0, (LPVOID)lpszUpdateEntryCreated, 0);
    }

    inline LPWSTR GetUpdateEntryXML() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 125+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryXML(LPCWSTR lpszUpdateEntryXML) {
      return IPWorks_Atom_Set(m_pObj, 125+10000, 0, (LPVOID)lpszUpdateEntryXML, 0);
    }

    inline LPWSTR GetUpdateEntryId() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 126+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryId(LPCWSTR lpszUpdateEntryId) {
      return IPWorks_Atom_Set(m_pObj, 126+10000, 0, (LPVOID)lpszUpdateEntryId, 0);
    }

    inline LPWSTR GetUpdateEntryIssued() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 127+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryIssued(LPCWSTR lpszUpdateEntryIssued) {
      return IPWorks_Atom_Set(m_pObj, 127+10000, 0, (LPVOID)lpszUpdateEntryIssued, 0);
    }

    inline LPWSTR GetUpdateEntryLinkHref() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 128+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryLinkHref(LPCWSTR lpszUpdateEntryLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 128+10000, 0, (LPVOID)lpszUpdateEntryLinkHref, 0);
    }

    inline LPWSTR GetUpdateEntryLinkHrefLang() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 129+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryLinkHrefLang(LPCWSTR lpszUpdateEntryLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 129+10000, 0, (LPVOID)lpszUpdateEntryLinkHrefLang, 0);
    }

    inline LPWSTR GetUpdateEntryLinkLength() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 130+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryLinkLength(LPCWSTR lpszUpdateEntryLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 130+10000, 0, (LPVOID)lpszUpdateEntryLinkLength, 0);
    }

    inline LPWSTR GetUpdateEntryLinkRel() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 131+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryLinkRel(LPCWSTR lpszUpdateEntryLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 131+10000, 0, (LPVOID)lpszUpdateEntryLinkRel, 0);
    }

    inline LPWSTR GetUpdateEntryLinkTitle() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 132+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryLinkTitle(LPCWSTR lpszUpdateEntryLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 132+10000, 0, (LPVOID)lpszUpdateEntryLinkTitle, 0);
    }

    inline LPWSTR GetUpdateEntryLinkType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 133+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryLinkType(LPCWSTR lpszUpdateEntryLinkType) {
      return IPWorks_Atom_Set(m_pObj, 133+10000, 0, (LPVOID)lpszUpdateEntryLinkType, 0);
    }

    inline LPWSTR GetUpdateEntryModified() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 134+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryModified(LPCWSTR lpszUpdateEntryModified) {
      return IPWorks_Atom_Set(m_pObj, 134+10000, 0, (LPVOID)lpszUpdateEntryModified, 0);
    }

    inline LPWSTR GetUpdateEntryPublished() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 135+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryPublished(LPCWSTR lpszUpdateEntryPublished) {
      return IPWorks_Atom_Set(m_pObj, 135+10000, 0, (LPVOID)lpszUpdateEntryPublished, 0);
    }

    inline LPWSTR GetUpdateEntryRights() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 136+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryRights(LPCWSTR lpszUpdateEntryRights) {
      return IPWorks_Atom_Set(m_pObj, 136+10000, 0, (LPVOID)lpszUpdateEntryRights, 0);
    }

    inline INT GetUpdateEntryRightsTextType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 137, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetUpdateEntryRightsTextType(INT iUpdateEntryRightsTextType) {
      LPVOID val = (LPVOID)(iUpdateEntryRightsTextType);
      return IPWorks_Atom_Set(m_pObj, 137, 0, val, 0);
    }

    inline LPWSTR GetUpdateEntrySource() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 138+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntrySource(LPCWSTR lpszUpdateEntrySource) {
      return IPWorks_Atom_Set(m_pObj, 138+10000, 0, (LPVOID)lpszUpdateEntrySource, 0);
    }

    inline LPWSTR GetUpdateEntrySummary() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 139+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntrySummary(LPCWSTR lpszUpdateEntrySummary) {
      return IPWorks_Atom_Set(m_pObj, 139+10000, 0, (LPVOID)lpszUpdateEntrySummary, 0);
    }

    inline INT GetUpdateEntrySummaryTextType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 140, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetUpdateEntrySummaryTextType(INT iUpdateEntrySummaryTextType) {
      LPVOID val = (LPVOID)(iUpdateEntrySummaryTextType);
      return IPWorks_Atom_Set(m_pObj, 140, 0, val, 0);
    }

    inline LPWSTR GetUpdateEntryTitle() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 141+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryTitle(LPCWSTR lpszUpdateEntryTitle) {
      return IPWorks_Atom_Set(m_pObj, 141+10000, 0, (LPVOID)lpszUpdateEntryTitle, 0);
    }

    inline INT GetUpdateEntryTitleTextType() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 142, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetUpdateEntryTitleTextType(INT iUpdateEntryTitleTextType) {
      LPVOID val = (LPVOID)(iUpdateEntryTitleTextType);
      return IPWorks_Atom_Set(m_pObj, 142, 0, val, 0);
    }

    inline LPWSTR GetUpdateEntryUpdated() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 143+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateEntryUpdated(LPCWSTR lpszUpdateEntryUpdated) {
      return IPWorks_Atom_Set(m_pObj, 143+10000, 0, (LPVOID)lpszUpdateEntryUpdated, 0);
    }

    inline LPWSTR GetUpdateFile() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 144+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUpdateFile(LPCWSTR lpszUpdateFile) {
      return IPWorks_Atom_Set(m_pObj, 144+10000, 0, (LPVOID)lpszUpdateFile, 0);
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_Atom_Get(m_pObj, 145+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_Atom_Set(m_pObj, 145+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline INT AddCookie(LPCWSTR lpszCookieName, LPCWSTR lpszCookieValue) {
      LPVOID param[2+1] = {(LPVOID)lpszCookieName, (LPVOID)lpszCookieValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 2+10000, 2, param, cbparam, NULL);
    }

    inline INT AddNamespace(LPCWSTR lpszPrefix, LPCWSTR lpszNamespaceURI) {
      LPVOID param[2+1] = {(LPVOID)lpszPrefix, (LPVOID)lpszNamespaceURI, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 3+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_Atom_Do(m_pObj, 4+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DeleteResource(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT GetFeed(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 7+10000, 1, param, cbparam, NULL);
    }

    inline LPWSTR GetProperty(LPCWSTR lpszPropertyName) {
      LPVOID param[1+1] = {(LPVOID)lpszPropertyName, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_Atom_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT GetResource(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 9+10000, 1, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT PostResource(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 11+10000, 1, param, cbparam, NULL);
    }

    inline INT Put(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 12+10000, 1, param, cbparam, NULL);
    }

    inline INT PutResource(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 13+10000, 1, param, cbparam, NULL);
    }

    inline INT ReadFile(LPCWSTR lpszFileName) {
      LPVOID param[1+1] = {(LPVOID)lpszFileName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 15+10000, 0, param, cbparam, NULL);
    }

    inline INT SetProperty(LPCWSTR lpszPropertyName, LPCWSTR lpszPropertyValue) {
      LPVOID param[2+1] = {(LPVOID)lpszPropertyName, (LPVOID)lpszPropertyValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 16+10000, 2, param, cbparam, NULL);
    }

    inline INT WriteFile(LPCWSTR lpszFilename) {
      LPVOID param[1+1] = {(LPVOID)lpszFilename, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 17+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_ATOM_H_
