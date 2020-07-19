/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_Atom_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_Atom_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Atom_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_Atom_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_Atom_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_Atom_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Atom_StaticDestroy();

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
} AtomConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} AtomConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} AtomDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} AtomEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} AtomErrorEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} AtomHeaderEventParams;

typedef struct {
  int LogLevel;
  const char *Message;
  const char *LogType;
  int reserved;
} AtomLogEventParams;

typedef struct {
  const char *Location;
  int Accept;
  int reserved;
} AtomRedirectEventParams;

typedef struct {
  const char *Name;
  const char *Value;
  const char *Expires;
  const char *Domain;
  const char *Path;
  int Secure;
  int reserved;
} AtomSetCookieEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} AtomSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} AtomSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} AtomStartTransferEventParams;

typedef struct {
  const char *HTTPVersion;
  int StatusCode;
  const char *Description;
  int reserved;
} AtomStatusEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int reserved;
} AtomTransferEventParams;


class Atom {
  public: // Events
    virtual int FireConnected(AtomConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(AtomConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(AtomDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(AtomEndTransferEventParams *e) {return 0;}
    virtual int FireError(AtomErrorEventParams *e) {return 0;}
    virtual int FireHeader(AtomHeaderEventParams *e) {return 0;}
    virtual int FireLog(AtomLogEventParams *e) {return 0;}
    virtual int FireRedirect(AtomRedirectEventParams *e) {return 0;}
    virtual int FireSetCookie(AtomSetCookieEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(AtomSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(AtomSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(AtomStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(AtomStatusEventParams *e) {return 0;}
    virtual int FireTransfer(AtomTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL AtomEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          AtomConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((Atom*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          AtomConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((Atom*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          AtomDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((Atom*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          AtomEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((Atom*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          AtomErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((Atom*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          AtomHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((Atom*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          AtomLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((Atom*)lpObj)->FireLog(&e);
          break;
        }
        case 8: {
          AtomRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), 0};
          ret_code = ((Atom*)lpObj)->FireRedirect(&e);
          param[1] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 9: {
          AtomSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), 0};
          ret_code = ((Atom*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 10: {
          AtomSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((Atom*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 11: {
          AtomSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((Atom*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 12: {
          AtomStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((Atom*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 13: {
          AtomStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((Atom*)lpObj)->FireStatus(&e);
          break;
        }
        case 14: {
          AtomTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), 0};
          ret_code = ((Atom*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    Atom(char *lpOemKey = (char*)IPWORKS_OEMKEY_69) {
      m_pObj = IPWorks_Atom_Create(AtomEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~Atom() {
      IPWorks_Atom_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_Atom_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_Atom_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_Atom_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_Atom_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_Atom_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetAccept() {
      void* val = IPWorks_Atom_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAccept(const char* lpszAccept) {
      return IPWorks_Atom_Set(m_pObj, 1, 0, (void*)lpszAccept, 0);
    }

    inline int GetAtomData(char* &lpAtomData, int &lenAtomData) {
      lpAtomData = (char*)IPWorks_Atom_Get(m_pObj, 2, 0, &lenAtomData, NULL);
      return lpAtomData ? 0 : lenAtomData;
    }
    inline int SetAtomData(const char* lpAtomData, int lenAtomData) {
      return IPWorks_Atom_Set(m_pObj, 2, 0, (void*)lpAtomData, lenAtomData);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_Atom_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthorization(const char* lpszAuthorization) {
      return IPWorks_Atom_Set(m_pObj, 3, 0, (void*)lpszAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_Atom_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_Atom_Set(m_pObj, 4, 0, val, 0);
    }

    inline char* GetChannelAuthorEmail() {
      void* val = IPWorks_Atom_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelAuthorEmail(const char* lpszChannelAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 5, 0, (void*)lpszChannelAuthorEmail, 0);
    }

    inline char* GetChannelAuthorName() {
      void* val = IPWorks_Atom_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelAuthorName(const char* lpszChannelAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 6, 0, (void*)lpszChannelAuthorName, 0);
    }

    inline char* GetChannelAuthorUri() {
      void* val = IPWorks_Atom_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelAuthorUri(const char* lpszChannelAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 7, 0, (void*)lpszChannelAuthorUri, 0);
    }

    inline char* GetChannelCategoryLabel() {
      void* val = IPWorks_Atom_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelCategoryLabel(const char* lpszChannelCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 8, 0, (void*)lpszChannelCategoryLabel, 0);
    }

    inline char* GetChannelCategoryScheme() {
      void* val = IPWorks_Atom_Get(m_pObj, 9, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelCategoryScheme(const char* lpszChannelCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 9, 0, (void*)lpszChannelCategoryScheme, 0);
    }

    inline char* GetChannelCategoryTerm() {
      void* val = IPWorks_Atom_Get(m_pObj, 10, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelCategoryTerm(const char* lpszChannelCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 10, 0, (void*)lpszChannelCategoryTerm, 0);
    }

    inline char* GetChannelContributorEmail() {
      void* val = IPWorks_Atom_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelContributorEmail(const char* lpszChannelContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 11, 0, (void*)lpszChannelContributorEmail, 0);
    }

    inline char* GetChannelContributorName() {
      void* val = IPWorks_Atom_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelContributorName(const char* lpszChannelContributorName) {
      return IPWorks_Atom_Set(m_pObj, 12, 0, (void*)lpszChannelContributorName, 0);
    }

    inline char* GetChannelContributorUri() {
      void* val = IPWorks_Atom_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelContributorUri(const char* lpszChannelContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 13, 0, (void*)lpszChannelContributorUri, 0);
    }

    inline char* GetChannelGenerator() {
      void* val = IPWorks_Atom_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelGenerator(const char* lpszChannelGenerator) {
      return IPWorks_Atom_Set(m_pObj, 14, 0, (void*)lpszChannelGenerator, 0);
    }

    inline char* GetChannelIcon() {
      void* val = IPWorks_Atom_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelIcon(const char* lpszChannelIcon) {
      return IPWorks_Atom_Set(m_pObj, 15, 0, (void*)lpszChannelIcon, 0);
    }

    inline char* GetChannelId() {
      void* val = IPWorks_Atom_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelId(const char* lpszChannelId) {
      return IPWorks_Atom_Set(m_pObj, 16, 0, (void*)lpszChannelId, 0);
    }

    inline char* GetChannelLinkHref() {
      void* val = IPWorks_Atom_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkHref(const char* lpszChannelLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 17, 0, (void*)lpszChannelLinkHref, 0);
    }

    inline char* GetChannelLinkHrefLang() {
      void* val = IPWorks_Atom_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkHrefLang(const char* lpszChannelLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 18, 0, (void*)lpszChannelLinkHrefLang, 0);
    }

    inline char* GetChannelLinkLength() {
      void* val = IPWorks_Atom_Get(m_pObj, 19, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkLength(const char* lpszChannelLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 19, 0, (void*)lpszChannelLinkLength, 0);
    }

    inline char* GetChannelLinkRel() {
      void* val = IPWorks_Atom_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkRel(const char* lpszChannelLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 20, 0, (void*)lpszChannelLinkRel, 0);
    }

    inline char* GetChannelLinkTitle() {
      void* val = IPWorks_Atom_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkTitle(const char* lpszChannelLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 21, 0, (void*)lpszChannelLinkTitle, 0);
    }

    inline char* GetChannelLinkType() {
      void* val = IPWorks_Atom_Get(m_pObj, 22, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkType(const char* lpszChannelLinkType) {
      return IPWorks_Atom_Set(m_pObj, 22, 0, (void*)lpszChannelLinkType, 0);
    }

    inline char* GetChannelLogo() {
      void* val = IPWorks_Atom_Get(m_pObj, 23, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLogo(const char* lpszChannelLogo) {
      return IPWorks_Atom_Set(m_pObj, 23, 0, (void*)lpszChannelLogo, 0);
    }

    inline char* GetChannelRights() {
      void* val = IPWorks_Atom_Get(m_pObj, 24, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelRights(const char* lpszChannelRights) {
      return IPWorks_Atom_Set(m_pObj, 24, 0, (void*)lpszChannelRights, 0);
    }

    inline int GetChannelRightsTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 25, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetChannelRightsTextType(int iChannelRightsTextType) {
      void* val = (void*)IPW64CAST(iChannelRightsTextType);
      return IPWorks_Atom_Set(m_pObj, 25, 0, val, 0);
    }

    inline char* GetChannelSubtitle() {
      void* val = IPWorks_Atom_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelSubtitle(const char* lpszChannelSubtitle) {
      return IPWorks_Atom_Set(m_pObj, 26, 0, (void*)lpszChannelSubtitle, 0);
    }

    inline int GetChannelSubtitleTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 27, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetChannelSubtitleTextType(int iChannelSubtitleTextType) {
      void* val = (void*)IPW64CAST(iChannelSubtitleTextType);
      return IPWorks_Atom_Set(m_pObj, 27, 0, val, 0);
    }

    inline char* GetChannelTitle() {
      void* val = IPWorks_Atom_Get(m_pObj, 28, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelTitle(const char* lpszChannelTitle) {
      return IPWorks_Atom_Set(m_pObj, 28, 0, (void*)lpszChannelTitle, 0);
    }

    inline int GetChannelTitleTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 29, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetChannelTitleTextType(int iChannelTitleTextType) {
      void* val = (void*)IPW64CAST(iChannelTitleTextType);
      return IPWorks_Atom_Set(m_pObj, 29, 0, val, 0);
    }

    inline char* GetChannelUpdated() {
      void* val = IPWorks_Atom_Get(m_pObj, 30, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelUpdated(const char* lpszChannelUpdated) {
      return IPWorks_Atom_Set(m_pObj, 30, 0, (void*)lpszChannelUpdated, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_Atom_Get(m_pObj, 31, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_Atom_Set(m_pObj, 31, 0, val, 0);
    }

    inline char* GetContentType() {
      void* val = IPWorks_Atom_Get(m_pObj, 32, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetContentType(const char* lpszContentType) {
      return IPWorks_Atom_Set(m_pObj, 32, 0, (void*)lpszContentType, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_Atom_Get(m_pObj, 33, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_Atom_Set(m_pObj, 33, 0, val, 0);
    }

    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 34, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 35, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 36, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieName(int iCookieIndex, const char* lpszCookieName) {
      return IPWorks_Atom_Set(m_pObj, 36, iCookieIndex, (void*)lpszCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 37, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 38, iCookieIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 39, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieValue(int iCookieIndex, const char* lpszCookieValue) {
      return IPWorks_Atom_Set(m_pObj, 39, iCookieIndex, (void*)lpszCookieValue, 0);
    }

    inline int GetEntryCount() {
      void* val = IPWorks_Atom_Get(m_pObj, 40, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetEntryCount(int iEntryCount) {
      void* val = (void*)IPW64CAST(iEntryCount);
      return IPWorks_Atom_Set(m_pObj, 40, 0, val, 0);
    }

    inline char* GetEntryAuthorEmail(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 41, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryAuthorEmail(int iEntryIndex, const char* lpszEntryAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 41, iEntryIndex, (void*)lpszEntryAuthorEmail, 0);
    }

    inline char* GetEntryAuthorName(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 42, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryAuthorName(int iEntryIndex, const char* lpszEntryAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 42, iEntryIndex, (void*)lpszEntryAuthorName, 0);
    }

    inline char* GetEntryAuthorUri(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 43, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryAuthorUri(int iEntryIndex, const char* lpszEntryAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 43, iEntryIndex, (void*)lpszEntryAuthorUri, 0);
    }

    inline char* GetEntryCategoryLabel(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 44, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryCategoryLabel(int iEntryIndex, const char* lpszEntryCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 44, iEntryIndex, (void*)lpszEntryCategoryLabel, 0);
    }

    inline char* GetEntryCategoryScheme(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 45, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryCategoryScheme(int iEntryIndex, const char* lpszEntryCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 45, iEntryIndex, (void*)lpszEntryCategoryScheme, 0);
    }

    inline char* GetEntryCategoryTerm(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 46, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryCategoryTerm(int iEntryIndex, const char* lpszEntryCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 46, iEntryIndex, (void*)lpszEntryCategoryTerm, 0);
    }

    inline char* GetEntryContent(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 47, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryContent(int iEntryIndex, const char* lpszEntryContent) {
      return IPWorks_Atom_Set(m_pObj, 47, iEntryIndex, (void*)lpszEntryContent, 0);
    }

    inline int GetEntryContentTextType(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 48, iEntryIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetEntryContentTextType(int iEntryIndex, int iEntryContentTextType) {
      void* val = (void*)IPW64CAST(iEntryContentTextType);
      return IPWorks_Atom_Set(m_pObj, 48, iEntryIndex, val, 0);
    }

    inline char* GetEntryContributorEmail(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 49, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryContributorEmail(int iEntryIndex, const char* lpszEntryContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 49, iEntryIndex, (void*)lpszEntryContributorEmail, 0);
    }

    inline char* GetEntryContributorName(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 50, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryContributorName(int iEntryIndex, const char* lpszEntryContributorName) {
      return IPWorks_Atom_Set(m_pObj, 50, iEntryIndex, (void*)lpszEntryContributorName, 0);
    }

    inline char* GetEntryContributorUri(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 51, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryContributorUri(int iEntryIndex, const char* lpszEntryContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 51, iEntryIndex, (void*)lpszEntryContributorUri, 0);
    }

    inline char* GetEntryCopyright(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 52, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryCopyright(int iEntryIndex, const char* lpszEntryCopyright) {
      return IPWorks_Atom_Set(m_pObj, 52, iEntryIndex, (void*)lpszEntryCopyright, 0);
    }

    inline char* GetEntryCreated(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 53, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryCreated(int iEntryIndex, const char* lpszEntryCreated) {
      return IPWorks_Atom_Set(m_pObj, 53, iEntryIndex, (void*)lpszEntryCreated, 0);
    }

    inline char* GetEntryXML(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 54, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryXML(int iEntryIndex, const char* lpszEntryXML) {
      return IPWorks_Atom_Set(m_pObj, 54, iEntryIndex, (void*)lpszEntryXML, 0);
    }

    inline char* GetEntryId(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 55, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryId(int iEntryIndex, const char* lpszEntryId) {
      return IPWorks_Atom_Set(m_pObj, 55, iEntryIndex, (void*)lpszEntryId, 0);
    }

    inline char* GetEntryIssued(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 56, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryIssued(int iEntryIndex, const char* lpszEntryIssued) {
      return IPWorks_Atom_Set(m_pObj, 56, iEntryIndex, (void*)lpszEntryIssued, 0);
    }

    inline char* GetEntryLinkHref(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 57, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryLinkHref(int iEntryIndex, const char* lpszEntryLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 57, iEntryIndex, (void*)lpszEntryLinkHref, 0);
    }

    inline char* GetEntryLinkHrefLang(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 58, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryLinkHrefLang(int iEntryIndex, const char* lpszEntryLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 58, iEntryIndex, (void*)lpszEntryLinkHrefLang, 0);
    }

    inline char* GetEntryLinkLength(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 59, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryLinkLength(int iEntryIndex, const char* lpszEntryLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 59, iEntryIndex, (void*)lpszEntryLinkLength, 0);
    }

    inline char* GetEntryLinkRel(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 60, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryLinkRel(int iEntryIndex, const char* lpszEntryLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 60, iEntryIndex, (void*)lpszEntryLinkRel, 0);
    }

    inline char* GetEntryLinkTitle(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 61, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryLinkTitle(int iEntryIndex, const char* lpszEntryLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 61, iEntryIndex, (void*)lpszEntryLinkTitle, 0);
    }

    inline char* GetEntryLinkType(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 62, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryLinkType(int iEntryIndex, const char* lpszEntryLinkType) {
      return IPWorks_Atom_Set(m_pObj, 62, iEntryIndex, (void*)lpszEntryLinkType, 0);
    }

    inline char* GetEntryModified(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 63, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryModified(int iEntryIndex, const char* lpszEntryModified) {
      return IPWorks_Atom_Set(m_pObj, 63, iEntryIndex, (void*)lpszEntryModified, 0);
    }

    inline char* GetEntryPublished(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 64, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryPublished(int iEntryIndex, const char* lpszEntryPublished) {
      return IPWorks_Atom_Set(m_pObj, 64, iEntryIndex, (void*)lpszEntryPublished, 0);
    }

    inline char* GetEntryRights(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 65, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryRights(int iEntryIndex, const char* lpszEntryRights) {
      return IPWorks_Atom_Set(m_pObj, 65, iEntryIndex, (void*)lpszEntryRights, 0);
    }

    inline int GetEntryRightsTextType(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 66, iEntryIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetEntryRightsTextType(int iEntryIndex, int iEntryRightsTextType) {
      void* val = (void*)IPW64CAST(iEntryRightsTextType);
      return IPWorks_Atom_Set(m_pObj, 66, iEntryIndex, val, 0);
    }

    inline char* GetEntrySource(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 67, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntrySource(int iEntryIndex, const char* lpszEntrySource) {
      return IPWorks_Atom_Set(m_pObj, 67, iEntryIndex, (void*)lpszEntrySource, 0);
    }

    inline char* GetEntrySummary(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 68, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntrySummary(int iEntryIndex, const char* lpszEntrySummary) {
      return IPWorks_Atom_Set(m_pObj, 68, iEntryIndex, (void*)lpszEntrySummary, 0);
    }

    inline int GetEntrySummaryTextType(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 69, iEntryIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetEntrySummaryTextType(int iEntryIndex, int iEntrySummaryTextType) {
      void* val = (void*)IPW64CAST(iEntrySummaryTextType);
      return IPWorks_Atom_Set(m_pObj, 69, iEntryIndex, val, 0);
    }

    inline char* GetEntryTitle(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 70, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryTitle(int iEntryIndex, const char* lpszEntryTitle) {
      return IPWorks_Atom_Set(m_pObj, 70, iEntryIndex, (void*)lpszEntryTitle, 0);
    }

    inline int GetEntryTitleTextType(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 71, iEntryIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetEntryTitleTextType(int iEntryIndex, int iEntryTitleTextType) {
      void* val = (void*)IPW64CAST(iEntryTitleTextType);
      return IPWorks_Atom_Set(m_pObj, 71, iEntryIndex, val, 0);
    }

    inline char* GetEntryUpdated(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 72, iEntryIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryUpdated(int iEntryIndex, const char* lpszEntryUpdated) {
      return IPWorks_Atom_Set(m_pObj, 72, iEntryIndex, (void*)lpszEntryUpdated, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_Atom_Get(m_pObj, 73, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_Atom_Set(m_pObj, 73, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_Atom_Get(m_pObj, 74, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_Atom_Set(m_pObj, 74, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_Atom_Get(m_pObj, 75, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_Atom_Set(m_pObj, 75, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_Atom_Get(m_pObj, 76, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_Atom_Set(m_pObj, 76, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_Atom_Get(m_pObj, 77, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_Atom_Set(m_pObj, 77, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_Atom_Get(m_pObj, 78, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_Atom_Set(m_pObj, 78, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_Atom_Get(m_pObj, 79, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_Atom_Set(m_pObj, 79, 0, val, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_Atom_Get(m_pObj, 80, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetIfModifiedSince() {
      void* val = IPWorks_Atom_Get(m_pObj, 81, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetIfModifiedSince(const char* lpszIfModifiedSince) {
      return IPWorks_Atom_Set(m_pObj, 81, 0, (void*)lpszIfModifiedSince, 0);
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_Atom_Get(m_pObj, 82, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_Atom_Get(m_pObj, 82+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_Atom_Set(m_pObj, 82, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_Atom_Set(m_pObj, 82+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_Atom_Get(m_pObj, 83, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_Atom_Set(m_pObj, 83, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_Atom_Get(m_pObj, 84, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetNamespaceCount(int iNamespaceCount) {
      void* val = (void*)IPW64CAST(iNamespaceCount);
      return IPWorks_Atom_Set(m_pObj, 84, 0, val, 0);
    }

    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 85, iNamespaceIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetNamespacePrefix(int iNamespaceIndex, const char* lpszNamespacePrefix) {
      return IPWorks_Atom_Set(m_pObj, 85, iNamespaceIndex, (void*)lpszNamespacePrefix, 0);
    }

    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 86, iNamespaceIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetNamespaceURI(int iNamespaceIndex, const char* lpszNamespaceURI) {
      return IPWorks_Atom_Set(m_pObj, 86, iNamespaceIndex, (void*)lpszNamespaceURI, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_Atom_Get(m_pObj, 87, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherHeaders(const char* lpszOtherHeaders) {
      return IPWorks_Atom_Set(m_pObj, 87, 0, (void*)lpszOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_Atom_Get(m_pObj, 88, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 89, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 90, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_Atom_Get(m_pObj, 91, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_Atom_Set(m_pObj, 91, 0, (void*)lpszPassword, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_Atom_Get(m_pObj, 92, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_Atom_Set(m_pObj, 92, 0, val, 0);
    }

    inline int GetProxyAutoDetect() {
      void* val = IPWorks_Atom_Get(m_pObj, 93, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_Atom_Set(m_pObj, 93, 0, val, 0);
    }

    inline char* GetProxyPassword() {
      void* val = IPWorks_Atom_Get(m_pObj, 94, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyPassword(const char* lpszProxyPassword) {
      return IPWorks_Atom_Set(m_pObj, 94, 0, (void*)lpszProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_Atom_Get(m_pObj, 95, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyPort(int iProxyPort) {
      void* val = (void*)IPW64CAST(iProxyPort);
      return IPWorks_Atom_Set(m_pObj, 95, 0, val, 0);
    }

    inline char* GetProxyServer() {
      void* val = IPWorks_Atom_Get(m_pObj, 96, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyServer(const char* lpszProxyServer) {
      return IPWorks_Atom_Set(m_pObj, 96, 0, (void*)lpszProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_Atom_Get(m_pObj, 97, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_Atom_Set(m_pObj, 97, 0, val, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_Atom_Get(m_pObj, 98, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyUser(const char* lpszProxyUser) {
      return IPWorks_Atom_Set(m_pObj, 98, 0, (void*)lpszProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_Atom_Get(m_pObj, 99, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReferer(const char* lpszReferer) {
      return IPWorks_Atom_Set(m_pObj, 99, 0, (void*)lpszReferer, 0);
    }

    inline char* GetSlug() {
      void* val = IPWorks_Atom_Get(m_pObj, 100, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSlug(const char* lpszSlug) {
      return IPWorks_Atom_Set(m_pObj, 100, 0, (void*)lpszSlug, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_Atom_Get(m_pObj, 101, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_Atom_Set(m_pObj, 101, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_Atom_Get(m_pObj, 102, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_Atom_Set(m_pObj, 102, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_Atom_Get(m_pObj, 103, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_Atom_Set(m_pObj, 103, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_Atom_Get(m_pObj, 104, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_Atom_Set(m_pObj, 104, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_Atom_Get(m_pObj, 105, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_Atom_Set(m_pObj, 105, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_Atom_Get(m_pObj, 106, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_Atom_Set(m_pObj, 106, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_Atom_Get(m_pObj, 107, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetTimeout() {
      void* val = IPWorks_Atom_Get(m_pObj, 108, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_Atom_Set(m_pObj, 108, 0, val, 0);
    }

    inline int GetTransferredData(char* &lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_Atom_Get(m_pObj, 109, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline int64 GetTransferredDataLimit() {
      int64 retVal;
      IPWorks_Atom_Get(m_pObj, 110, 0, NULL, &retVal);
      return retVal;
    }
    inline int SetTransferredDataLimit(int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_Atom_Set(m_pObj, 110, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_Atom_Get(m_pObj, 111, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetUpdateEntryAuthorEmail() {
      void* val = IPWorks_Atom_Get(m_pObj, 112, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryAuthorEmail(const char* lpszUpdateEntryAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 112, 0, (void*)lpszUpdateEntryAuthorEmail, 0);
    }

    inline char* GetUpdateEntryAuthorName() {
      void* val = IPWorks_Atom_Get(m_pObj, 113, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryAuthorName(const char* lpszUpdateEntryAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 113, 0, (void*)lpszUpdateEntryAuthorName, 0);
    }

    inline char* GetUpdateEntryAuthorUri() {
      void* val = IPWorks_Atom_Get(m_pObj, 114, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryAuthorUri(const char* lpszUpdateEntryAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 114, 0, (void*)lpszUpdateEntryAuthorUri, 0);
    }

    inline char* GetUpdateEntryCategoryLabel() {
      void* val = IPWorks_Atom_Get(m_pObj, 115, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryCategoryLabel(const char* lpszUpdateEntryCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 115, 0, (void*)lpszUpdateEntryCategoryLabel, 0);
    }

    inline char* GetUpdateEntryCategoryScheme() {
      void* val = IPWorks_Atom_Get(m_pObj, 116, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryCategoryScheme(const char* lpszUpdateEntryCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 116, 0, (void*)lpszUpdateEntryCategoryScheme, 0);
    }

    inline char* GetUpdateEntryCategoryTerm() {
      void* val = IPWorks_Atom_Get(m_pObj, 117, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryCategoryTerm(const char* lpszUpdateEntryCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 117, 0, (void*)lpszUpdateEntryCategoryTerm, 0);
    }

    inline char* GetUpdateEntryContent() {
      void* val = IPWorks_Atom_Get(m_pObj, 118, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryContent(const char* lpszUpdateEntryContent) {
      return IPWorks_Atom_Set(m_pObj, 118, 0, (void*)lpszUpdateEntryContent, 0);
    }

    inline int GetUpdateEntryContentTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 119, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetUpdateEntryContentTextType(int iUpdateEntryContentTextType) {
      void* val = (void*)IPW64CAST(iUpdateEntryContentTextType);
      return IPWorks_Atom_Set(m_pObj, 119, 0, val, 0);
    }

    inline char* GetUpdateEntryContributorEmail() {
      void* val = IPWorks_Atom_Get(m_pObj, 120, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryContributorEmail(const char* lpszUpdateEntryContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 120, 0, (void*)lpszUpdateEntryContributorEmail, 0);
    }

    inline char* GetUpdateEntryContributorName() {
      void* val = IPWorks_Atom_Get(m_pObj, 121, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryContributorName(const char* lpszUpdateEntryContributorName) {
      return IPWorks_Atom_Set(m_pObj, 121, 0, (void*)lpszUpdateEntryContributorName, 0);
    }

    inline char* GetUpdateEntryContributorUri() {
      void* val = IPWorks_Atom_Get(m_pObj, 122, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryContributorUri(const char* lpszUpdateEntryContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 122, 0, (void*)lpszUpdateEntryContributorUri, 0);
    }

    inline char* GetUpdateEntryCopyright() {
      void* val = IPWorks_Atom_Get(m_pObj, 123, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryCopyright(const char* lpszUpdateEntryCopyright) {
      return IPWorks_Atom_Set(m_pObj, 123, 0, (void*)lpszUpdateEntryCopyright, 0);
    }

    inline char* GetUpdateEntryCreated() {
      void* val = IPWorks_Atom_Get(m_pObj, 124, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryCreated(const char* lpszUpdateEntryCreated) {
      return IPWorks_Atom_Set(m_pObj, 124, 0, (void*)lpszUpdateEntryCreated, 0);
    }

    inline char* GetUpdateEntryXML() {
      void* val = IPWorks_Atom_Get(m_pObj, 125, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryXML(const char* lpszUpdateEntryXML) {
      return IPWorks_Atom_Set(m_pObj, 125, 0, (void*)lpszUpdateEntryXML, 0);
    }

    inline char* GetUpdateEntryId() {
      void* val = IPWorks_Atom_Get(m_pObj, 126, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryId(const char* lpszUpdateEntryId) {
      return IPWorks_Atom_Set(m_pObj, 126, 0, (void*)lpszUpdateEntryId, 0);
    }

    inline char* GetUpdateEntryIssued() {
      void* val = IPWorks_Atom_Get(m_pObj, 127, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryIssued(const char* lpszUpdateEntryIssued) {
      return IPWorks_Atom_Set(m_pObj, 127, 0, (void*)lpszUpdateEntryIssued, 0);
    }

    inline char* GetUpdateEntryLinkHref() {
      void* val = IPWorks_Atom_Get(m_pObj, 128, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryLinkHref(const char* lpszUpdateEntryLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 128, 0, (void*)lpszUpdateEntryLinkHref, 0);
    }

    inline char* GetUpdateEntryLinkHrefLang() {
      void* val = IPWorks_Atom_Get(m_pObj, 129, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryLinkHrefLang(const char* lpszUpdateEntryLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 129, 0, (void*)lpszUpdateEntryLinkHrefLang, 0);
    }

    inline char* GetUpdateEntryLinkLength() {
      void* val = IPWorks_Atom_Get(m_pObj, 130, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryLinkLength(const char* lpszUpdateEntryLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 130, 0, (void*)lpszUpdateEntryLinkLength, 0);
    }

    inline char* GetUpdateEntryLinkRel() {
      void* val = IPWorks_Atom_Get(m_pObj, 131, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryLinkRel(const char* lpszUpdateEntryLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 131, 0, (void*)lpszUpdateEntryLinkRel, 0);
    }

    inline char* GetUpdateEntryLinkTitle() {
      void* val = IPWorks_Atom_Get(m_pObj, 132, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryLinkTitle(const char* lpszUpdateEntryLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 132, 0, (void*)lpszUpdateEntryLinkTitle, 0);
    }

    inline char* GetUpdateEntryLinkType() {
      void* val = IPWorks_Atom_Get(m_pObj, 133, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryLinkType(const char* lpszUpdateEntryLinkType) {
      return IPWorks_Atom_Set(m_pObj, 133, 0, (void*)lpszUpdateEntryLinkType, 0);
    }

    inline char* GetUpdateEntryModified() {
      void* val = IPWorks_Atom_Get(m_pObj, 134, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryModified(const char* lpszUpdateEntryModified) {
      return IPWorks_Atom_Set(m_pObj, 134, 0, (void*)lpszUpdateEntryModified, 0);
    }

    inline char* GetUpdateEntryPublished() {
      void* val = IPWorks_Atom_Get(m_pObj, 135, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryPublished(const char* lpszUpdateEntryPublished) {
      return IPWorks_Atom_Set(m_pObj, 135, 0, (void*)lpszUpdateEntryPublished, 0);
    }

    inline char* GetUpdateEntryRights() {
      void* val = IPWorks_Atom_Get(m_pObj, 136, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryRights(const char* lpszUpdateEntryRights) {
      return IPWorks_Atom_Set(m_pObj, 136, 0, (void*)lpszUpdateEntryRights, 0);
    }

    inline int GetUpdateEntryRightsTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 137, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetUpdateEntryRightsTextType(int iUpdateEntryRightsTextType) {
      void* val = (void*)IPW64CAST(iUpdateEntryRightsTextType);
      return IPWorks_Atom_Set(m_pObj, 137, 0, val, 0);
    }

    inline char* GetUpdateEntrySource() {
      void* val = IPWorks_Atom_Get(m_pObj, 138, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntrySource(const char* lpszUpdateEntrySource) {
      return IPWorks_Atom_Set(m_pObj, 138, 0, (void*)lpszUpdateEntrySource, 0);
    }

    inline char* GetUpdateEntrySummary() {
      void* val = IPWorks_Atom_Get(m_pObj, 139, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntrySummary(const char* lpszUpdateEntrySummary) {
      return IPWorks_Atom_Set(m_pObj, 139, 0, (void*)lpszUpdateEntrySummary, 0);
    }

    inline int GetUpdateEntrySummaryTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 140, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetUpdateEntrySummaryTextType(int iUpdateEntrySummaryTextType) {
      void* val = (void*)IPW64CAST(iUpdateEntrySummaryTextType);
      return IPWorks_Atom_Set(m_pObj, 140, 0, val, 0);
    }

    inline char* GetUpdateEntryTitle() {
      void* val = IPWorks_Atom_Get(m_pObj, 141, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryTitle(const char* lpszUpdateEntryTitle) {
      return IPWorks_Atom_Set(m_pObj, 141, 0, (void*)lpszUpdateEntryTitle, 0);
    }

    inline int GetUpdateEntryTitleTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 142, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetUpdateEntryTitleTextType(int iUpdateEntryTitleTextType) {
      void* val = (void*)IPW64CAST(iUpdateEntryTitleTextType);
      return IPWorks_Atom_Set(m_pObj, 142, 0, val, 0);
    }

    inline char* GetUpdateEntryUpdated() {
      void* val = IPWorks_Atom_Get(m_pObj, 143, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateEntryUpdated(const char* lpszUpdateEntryUpdated) {
      return IPWorks_Atom_Set(m_pObj, 143, 0, (void*)lpszUpdateEntryUpdated, 0);
    }

    inline char* GetUpdateFile() {
      void* val = IPWorks_Atom_Get(m_pObj, 144, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUpdateFile(const char* lpszUpdateFile) {
      return IPWorks_Atom_Set(m_pObj, 144, 0, (void*)lpszUpdateFile, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_Atom_Get(m_pObj, 145, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_Atom_Set(m_pObj, 145, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 2, 2, param, cbparam, NULL);
    }

    inline int AddNamespace(const char* lpszPrefix, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPrefix), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 3, 2, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Atom_Do(m_pObj, 4, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DeleteResource(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 5, 1, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int GetFeed(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 7, 1, param, cbparam, NULL);
    }

    inline char* GetProperty(const char* lpszPropertyName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPropertyName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Atom_Do(m_pObj, 8, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int GetResource(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 9, 1, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int PostResource(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 11, 1, param, cbparam, NULL);
    }

    inline int Put(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 12, 1, param, cbparam, NULL);
    }

    inline int PutResource(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 13, 1, param, cbparam, NULL);
    }

    inline int ReadFile(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 14, 1, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 15, 0, param, cbparam, NULL);
    }

    inline int SetProperty(const char* lpszPropertyName, const char* lpszPropertyValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPropertyName), (void*)IPW64CAST(lpszPropertyValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 16, 2, param, cbparam, NULL);
    }

    inline int WriteFile(const char* lpszFilename) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFilename), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 17, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_ATOM_H_
