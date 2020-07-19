/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_OData_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_OData_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_OData_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_OData_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_OData_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_OData_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_OData_StaticDestroy();

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
} ODataConnectedEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} ODataDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} ODataEndTransferEventParams;

typedef struct {
  const char *Name;
  int reserved;
} ODataEntityEventParams;

typedef struct {
  const char *Id;
  const char *Title;
  const char *Summary;
  const char *ETag;
  int reserved;
} ODataEntryEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} ODataErrorEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} ODataHeaderEventParams;

typedef struct {
  int LogLevel;
  const char *Message;
  const char *LogType;
  int reserved;
} ODataLogEventParams;

typedef struct {
  const char *Name;
  const char *TypeName;
  int Nullable;
  int reserved;
} ODataPropertyEventParams;

typedef struct {
  const char *Name;
  const char *Value;
  const char *Expires;
  const char *Domain;
  const char *Path;
  int Secure;
  int reserved;
} ODataSetCookieEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} ODataSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} ODataSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} ODataStartTransferEventParams;

typedef struct {
  const char *HTTPVersion;
  int StatusCode;
  const char *Description;
  int reserved;
} ODataStatusEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int reserved;
} ODataTransferEventParams;


class OData {
  public: // Events
    virtual int FireConnected(ODataConnectedEventParams *e) {return 0;}
    virtual int FireDisconnected(ODataDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(ODataEndTransferEventParams *e) {return 0;}
    virtual int FireEntity(ODataEntityEventParams *e) {return 0;}
    virtual int FireEntry(ODataEntryEventParams *e) {return 0;}
    virtual int FireError(ODataErrorEventParams *e) {return 0;}
    virtual int FireHeader(ODataHeaderEventParams *e) {return 0;}
    virtual int FireLog(ODataLogEventParams *e) {return 0;}
    virtual int FireProperty(ODataPropertyEventParams *e) {return 0;}
    virtual int FireSetCookie(ODataSetCookieEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(ODataSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(ODataSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(ODataStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(ODataStatusEventParams *e) {return 0;}
    virtual int FireTransfer(ODataTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL ODataEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          ODataConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((OData*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          ODataDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((OData*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 3: {
          ODataEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((OData*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 4: {
          ODataEntityEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((OData*)lpObj)->FireEntity(&e);
          break;
        }
        case 5: {
          ODataEntryEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), 0};
          ret_code = ((OData*)lpObj)->FireEntry(&e);
          break;
        }
        case 6: {
          ODataErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((OData*)lpObj)->FireError(&e);
          break;
        }
        case 7: {
          ODataHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((OData*)lpObj)->FireHeader(&e);
          break;
        }
        case 8: {
          ODataLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((OData*)lpObj)->FireLog(&e);
          break;
        }
        case 9: {
          ODataPropertyEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), 0};
          ret_code = ((OData*)lpObj)->FireProperty(&e);
          break;
        }
        case 10: {
          ODataSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), 0};
          ret_code = ((OData*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 11: {
          ODataSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((OData*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 12: {
          ODataSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((OData*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 13: {
          ODataStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((OData*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 14: {
          ODataStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((OData*)lpObj)->FireStatus(&e);
          break;
        }
        case 15: {
          ODataTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), 0};
          ret_code = ((OData*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    OData(char *lpOemKey = (char*)IPWORKS_OEMKEY_81) {
      m_pObj = IPWorks_OData_Create(ODataEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~OData() {
      IPWorks_OData_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_OData_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_OData_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_OData_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_OData_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_OData_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetAuthorization() {
      void* val = IPWorks_OData_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthorization(const char* lpszAuthorization) {
      return IPWorks_OData_Set(m_pObj, 1, 0, (void*)lpszAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_OData_Get(m_pObj, 2, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_OData_Set(m_pObj, 2, 0, val, 0);
    }

    inline char* GetChannelAuthorEmail() {
      void* val = IPWorks_OData_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelAuthorEmail(const char* lpszChannelAuthorEmail) {
      return IPWorks_OData_Set(m_pObj, 3, 0, (void*)lpszChannelAuthorEmail, 0);
    }

    inline char* GetChannelAuthorName() {
      void* val = IPWorks_OData_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelAuthorName(const char* lpszChannelAuthorName) {
      return IPWorks_OData_Set(m_pObj, 4, 0, (void*)lpszChannelAuthorName, 0);
    }

    inline char* GetChannelAuthorUri() {
      void* val = IPWorks_OData_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelAuthorUri(const char* lpszChannelAuthorUri) {
      return IPWorks_OData_Set(m_pObj, 5, 0, (void*)lpszChannelAuthorUri, 0);
    }

    inline char* GetChannelCategoryLabel() {
      void* val = IPWorks_OData_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelCategoryLabel(const char* lpszChannelCategoryLabel) {
      return IPWorks_OData_Set(m_pObj, 6, 0, (void*)lpszChannelCategoryLabel, 0);
    }

    inline char* GetChannelCategoryScheme() {
      void* val = IPWorks_OData_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelCategoryScheme(const char* lpszChannelCategoryScheme) {
      return IPWorks_OData_Set(m_pObj, 7, 0, (void*)lpszChannelCategoryScheme, 0);
    }

    inline char* GetChannelCategoryTerm() {
      void* val = IPWorks_OData_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelCategoryTerm(const char* lpszChannelCategoryTerm) {
      return IPWorks_OData_Set(m_pObj, 8, 0, (void*)lpszChannelCategoryTerm, 0);
    }

    inline char* GetChannelContributorEmail() {
      void* val = IPWorks_OData_Get(m_pObj, 9, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelContributorEmail(const char* lpszChannelContributorEmail) {
      return IPWorks_OData_Set(m_pObj, 9, 0, (void*)lpszChannelContributorEmail, 0);
    }

    inline char* GetChannelContributorName() {
      void* val = IPWorks_OData_Get(m_pObj, 10, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelContributorName(const char* lpszChannelContributorName) {
      return IPWorks_OData_Set(m_pObj, 10, 0, (void*)lpszChannelContributorName, 0);
    }

    inline char* GetChannelContributorUri() {
      void* val = IPWorks_OData_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelContributorUri(const char* lpszChannelContributorUri) {
      return IPWorks_OData_Set(m_pObj, 11, 0, (void*)lpszChannelContributorUri, 0);
    }

    inline char* GetChannelGenerator() {
      void* val = IPWorks_OData_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelGenerator(const char* lpszChannelGenerator) {
      return IPWorks_OData_Set(m_pObj, 12, 0, (void*)lpszChannelGenerator, 0);
    }

    inline char* GetChannelIcon() {
      void* val = IPWorks_OData_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelIcon(const char* lpszChannelIcon) {
      return IPWorks_OData_Set(m_pObj, 13, 0, (void*)lpszChannelIcon, 0);
    }

    inline char* GetChannelId() {
      void* val = IPWorks_OData_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelId(const char* lpszChannelId) {
      return IPWorks_OData_Set(m_pObj, 14, 0, (void*)lpszChannelId, 0);
    }

    inline char* GetChannelLinkHref() {
      void* val = IPWorks_OData_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkHref(const char* lpszChannelLinkHref) {
      return IPWorks_OData_Set(m_pObj, 15, 0, (void*)lpszChannelLinkHref, 0);
    }

    inline char* GetChannelLinkHrefLang() {
      void* val = IPWorks_OData_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkHrefLang(const char* lpszChannelLinkHrefLang) {
      return IPWorks_OData_Set(m_pObj, 16, 0, (void*)lpszChannelLinkHrefLang, 0);
    }

    inline char* GetChannelLinkLength() {
      void* val = IPWorks_OData_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkLength(const char* lpszChannelLinkLength) {
      return IPWorks_OData_Set(m_pObj, 17, 0, (void*)lpszChannelLinkLength, 0);
    }

    inline char* GetChannelLinkRel() {
      void* val = IPWorks_OData_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkRel(const char* lpszChannelLinkRel) {
      return IPWorks_OData_Set(m_pObj, 18, 0, (void*)lpszChannelLinkRel, 0);
    }

    inline char* GetChannelLinkTitle() {
      void* val = IPWorks_OData_Get(m_pObj, 19, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkTitle(const char* lpszChannelLinkTitle) {
      return IPWorks_OData_Set(m_pObj, 19, 0, (void*)lpszChannelLinkTitle, 0);
    }

    inline char* GetChannelLinkType() {
      void* val = IPWorks_OData_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLinkType(const char* lpszChannelLinkType) {
      return IPWorks_OData_Set(m_pObj, 20, 0, (void*)lpszChannelLinkType, 0);
    }

    inline char* GetChannelLogo() {
      void* val = IPWorks_OData_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLogo(const char* lpszChannelLogo) {
      return IPWorks_OData_Set(m_pObj, 21, 0, (void*)lpszChannelLogo, 0);
    }

    inline char* GetChannelRights() {
      void* val = IPWorks_OData_Get(m_pObj, 22, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelRights(const char* lpszChannelRights) {
      return IPWorks_OData_Set(m_pObj, 22, 0, (void*)lpszChannelRights, 0);
    }

    inline int GetChannelRightsTextType() {
      void* val = IPWorks_OData_Get(m_pObj, 23, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetChannelRightsTextType(int iChannelRightsTextType) {
      void* val = (void*)IPW64CAST(iChannelRightsTextType);
      return IPWorks_OData_Set(m_pObj, 23, 0, val, 0);
    }

    inline char* GetChannelSubtitle() {
      void* val = IPWorks_OData_Get(m_pObj, 24, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelSubtitle(const char* lpszChannelSubtitle) {
      return IPWorks_OData_Set(m_pObj, 24, 0, (void*)lpszChannelSubtitle, 0);
    }

    inline int GetChannelSubtitleTextType() {
      void* val = IPWorks_OData_Get(m_pObj, 25, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetChannelSubtitleTextType(int iChannelSubtitleTextType) {
      void* val = (void*)IPW64CAST(iChannelSubtitleTextType);
      return IPWorks_OData_Set(m_pObj, 25, 0, val, 0);
    }

    inline char* GetChannelTitle() {
      void* val = IPWorks_OData_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelTitle(const char* lpszChannelTitle) {
      return IPWorks_OData_Set(m_pObj, 26, 0, (void*)lpszChannelTitle, 0);
    }

    inline int GetChannelTitleTextType() {
      void* val = IPWorks_OData_Get(m_pObj, 27, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetChannelTitleTextType(int iChannelTitleTextType) {
      void* val = (void*)IPW64CAST(iChannelTitleTextType);
      return IPWorks_OData_Set(m_pObj, 27, 0, val, 0);
    }

    inline char* GetChannelUpdated() {
      void* val = IPWorks_OData_Get(m_pObj, 28, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelUpdated(const char* lpszChannelUpdated) {
      return IPWorks_OData_Set(m_pObj, 28, 0, (void*)lpszChannelUpdated, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_OData_Get(m_pObj, 29, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_OData_Set(m_pObj, 29, 0, val, 0);
    }

    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 30, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 31, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 32, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieName(int iCookieIndex, const char* lpszCookieName) {
      return IPWorks_OData_Set(m_pObj, 32, iCookieIndex, (void*)lpszCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 33, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 34, iCookieIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 35, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieValue(int iCookieIndex, const char* lpszCookieValue) {
      return IPWorks_OData_Set(m_pObj, 35, iCookieIndex, (void*)lpszCookieValue, 0);
    }

    inline char* GetEntryAuthor() {
      void* val = IPWorks_OData_Get(m_pObj, 36, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryAuthor(const char* lpszEntryAuthor) {
      return IPWorks_OData_Set(m_pObj, 36, 0, (void*)lpszEntryAuthor, 0);
    }

    inline int GetEntryCount() {
      void* val = IPWorks_OData_Get(m_pObj, 37, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetEntryETag() {
      void* val = IPWorks_OData_Get(m_pObj, 38, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryETag(const char* lpszEntryETag) {
      return IPWorks_OData_Set(m_pObj, 38, 0, (void*)lpszEntryETag, 0);
    }

    inline char* GetEntryId() {
      void* val = IPWorks_OData_Get(m_pObj, 39, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryId(const char* lpszEntryId) {
      return IPWorks_OData_Set(m_pObj, 39, 0, (void*)lpszEntryId, 0);
    }

    inline int GetEntryIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 40, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetEntryIndex(int iEntryIndex) {
      void* val = (void*)IPW64CAST(iEntryIndex);
      return IPWorks_OData_Set(m_pObj, 40, 0, val, 0);
    }

    inline int GetEntryLinksCount() {
      void* val = IPWorks_OData_Get(m_pObj, 41, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetEntryLinksCount(int iEntryLinksCount) {
      void* val = (void*)IPW64CAST(iEntryLinksCount);
      return IPWorks_OData_Set(m_pObj, 41, 0, val, 0);
    }

    inline char* GetEntryLinksResourcePath(int iEntryLinksIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 42, iEntryLinksIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetEntryLinksTitle(int iEntryLinksIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 43, iEntryLinksIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetEntryPropertiesCount() {
      void* val = IPWorks_OData_Get(m_pObj, 44, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetEntryPropertiesCount(int iEntryPropertiesCount) {
      void* val = (void*)IPW64CAST(iEntryPropertiesCount);
      return IPWorks_OData_Set(m_pObj, 44, 0, val, 0);
    }

    inline char* GetEntryPropertiesAttributes(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 45, iEntryPropertiesIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryPropertiesAttributes(int iEntryPropertiesIndex, const char* lpszEntryPropertiesAttributes) {
      return IPWorks_OData_Set(m_pObj, 45, iEntryPropertiesIndex, (void*)lpszEntryPropertiesAttributes, 0);
    }

    inline int GetEntryPropertiesIsNull(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 46, iEntryPropertiesIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetEntryPropertiesIsNull(int iEntryPropertiesIndex, int bEntryPropertiesIsNull) {
      void* val = (void*)IPW64CAST(bEntryPropertiesIsNull);
      return IPWorks_OData_Set(m_pObj, 46, iEntryPropertiesIndex, val, 0);
    }

    inline char* GetEntryPropertiesName(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 47, iEntryPropertiesIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryPropertiesName(int iEntryPropertiesIndex, const char* lpszEntryPropertiesName) {
      return IPWorks_OData_Set(m_pObj, 47, iEntryPropertiesIndex, (void*)lpszEntryPropertiesName, 0);
    }

    inline char* GetEntryPropertiesType(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 48, iEntryPropertiesIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryPropertiesType(int iEntryPropertiesIndex, const char* lpszEntryPropertiesType) {
      return IPWorks_OData_Set(m_pObj, 48, iEntryPropertiesIndex, (void*)lpszEntryPropertiesType, 0);
    }

    inline char* GetEntryPropertiesValue(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 49, iEntryPropertiesIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryPropertiesValue(int iEntryPropertiesIndex, const char* lpszEntryPropertiesValue) {
      return IPWorks_OData_Set(m_pObj, 49, iEntryPropertiesIndex, (void*)lpszEntryPropertiesValue, 0);
    }

    inline char* GetEntryPropertiesXPath(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 50, iEntryPropertiesIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetEntrySummary() {
      void* val = IPWorks_OData_Get(m_pObj, 51, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntrySummary(const char* lpszEntrySummary) {
      return IPWorks_OData_Set(m_pObj, 51, 0, (void*)lpszEntrySummary, 0);
    }

    inline char* GetEntryTitle() {
      void* val = IPWorks_OData_Get(m_pObj, 52, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryTitle(const char* lpszEntryTitle) {
      return IPWorks_OData_Set(m_pObj, 52, 0, (void*)lpszEntryTitle, 0);
    }

    inline char* GetEntryType() {
      void* val = IPWorks_OData_Get(m_pObj, 53, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryType(const char* lpszEntryType) {
      return IPWorks_OData_Set(m_pObj, 53, 0, (void*)lpszEntryType, 0);
    }

    inline char* GetEntryUpdated() {
      void* val = IPWorks_OData_Get(m_pObj, 54, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetEntryXML() {
      void* val = IPWorks_OData_Get(m_pObj, 55, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEntryXML(const char* lpszEntryXML) {
      return IPWorks_OData_Set(m_pObj, 55, 0, (void*)lpszEntryXML, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_OData_Get(m_pObj, 56, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_OData_Set(m_pObj, 56, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_OData_Get(m_pObj, 57, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_OData_Set(m_pObj, 57, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_OData_Get(m_pObj, 58, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_OData_Set(m_pObj, 58, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_OData_Get(m_pObj, 59, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_OData_Set(m_pObj, 59, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_OData_Get(m_pObj, 60, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_OData_Set(m_pObj, 60, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_OData_Get(m_pObj, 61, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_OData_Set(m_pObj, 61, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_OData_Get(m_pObj, 62, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_OData_Get(m_pObj, 63, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_OData_Set(m_pObj, 63, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetODataVersion() {
      void* val = IPWorks_OData_Get(m_pObj, 64, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetODataVersion(int iODataVersion) {
      void* val = (void*)IPW64CAST(iODataVersion);
      return IPWorks_OData_Set(m_pObj, 64, 0, val, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_OData_Get(m_pObj, 65, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherHeaders(const char* lpszOtherHeaders) {
      return IPWorks_OData_Set(m_pObj, 65, 0, (void*)lpszOtherHeaders, 0);
    }

    inline char* GetOtherQueryOptions() {
      void* val = IPWorks_OData_Get(m_pObj, 66, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherQueryOptions(const char* lpszOtherQueryOptions) {
      return IPWorks_OData_Set(m_pObj, 66, 0, (void*)lpszOtherQueryOptions, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_OData_Get(m_pObj, 67, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 68, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 69, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_OData_Get(m_pObj, 70, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_OData_Set(m_pObj, 70, 0, (void*)lpszPassword, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_OData_Get(m_pObj, 71, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_OData_Set(m_pObj, 71, 0, val, 0);
    }

    inline int GetProxyAutoDetect() {
      void* val = IPWorks_OData_Get(m_pObj, 72, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_OData_Set(m_pObj, 72, 0, val, 0);
    }

    inline char* GetProxyPassword() {
      void* val = IPWorks_OData_Get(m_pObj, 73, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyPassword(const char* lpszProxyPassword) {
      return IPWorks_OData_Set(m_pObj, 73, 0, (void*)lpszProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_OData_Get(m_pObj, 74, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyPort(int iProxyPort) {
      void* val = (void*)IPW64CAST(iProxyPort);
      return IPWorks_OData_Set(m_pObj, 74, 0, val, 0);
    }

    inline char* GetProxyServer() {
      void* val = IPWorks_OData_Get(m_pObj, 75, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyServer(const char* lpszProxyServer) {
      return IPWorks_OData_Set(m_pObj, 75, 0, (void*)lpszProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_OData_Get(m_pObj, 76, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_OData_Set(m_pObj, 76, 0, val, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_OData_Get(m_pObj, 77, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyUser(const char* lpszProxyUser) {
      return IPWorks_OData_Set(m_pObj, 77, 0, (void*)lpszProxyUser, 0);
    }

    inline char* GetQueryFilter() {
      void* val = IPWorks_OData_Get(m_pObj, 78, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetQueryFilter(const char* lpszQueryFilter) {
      return IPWorks_OData_Set(m_pObj, 78, 0, (void*)lpszQueryFilter, 0);
    }

    inline char* GetQueryOrderBy() {
      void* val = IPWorks_OData_Get(m_pObj, 79, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetQueryOrderBy(const char* lpszQueryOrderBy) {
      return IPWorks_OData_Set(m_pObj, 79, 0, (void*)lpszQueryOrderBy, 0);
    }

    inline char* GetQuerySelect() {
      void* val = IPWorks_OData_Get(m_pObj, 80, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetQuerySelect(const char* lpszQuerySelect) {
      return IPWorks_OData_Set(m_pObj, 80, 0, (void*)lpszQuerySelect, 0);
    }

    inline char* GetQuerySkip() {
      void* val = IPWorks_OData_Get(m_pObj, 81, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetQuerySkip(const char* lpszQuerySkip) {
      return IPWorks_OData_Set(m_pObj, 81, 0, (void*)lpszQuerySkip, 0);
    }

    inline char* GetQuerySkipToken() {
      void* val = IPWorks_OData_Get(m_pObj, 82, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetQuerySkipToken(const char* lpszQuerySkipToken) {
      return IPWorks_OData_Set(m_pObj, 82, 0, (void*)lpszQuerySkipToken, 0);
    }

    inline char* GetQueryTop() {
      void* val = IPWorks_OData_Get(m_pObj, 83, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetQueryTop(const char* lpszQueryTop) {
      return IPWorks_OData_Set(m_pObj, 83, 0, (void*)lpszQueryTop, 0);
    }

    inline char* GetResourcePath() {
      void* val = IPWorks_OData_Get(m_pObj, 84, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetResourcePath(const char* lpszResourcePath) {
      return IPWorks_OData_Set(m_pObj, 84, 0, (void*)lpszResourcePath, 0);
    }

    inline int GetSchemaAssociationContainsTarget() {
      void* val = IPWorks_OData_Get(m_pObj, 85, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetSchemaAssociationDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 86, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationFromRole() {
      void* val = IPWorks_OData_Get(m_pObj, 87, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationFromRoleDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 88, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationFromRoleEntity() {
      void* val = IPWorks_OData_Get(m_pObj, 89, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaAssociationFromRoleMultiplicity() {
      void* val = IPWorks_OData_Get(m_pObj, 90, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetSchemaAssociationFromRoleSummary() {
      void* val = IPWorks_OData_Get(m_pObj, 91, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationName() {
      void* val = IPWorks_OData_Get(m_pObj, 92, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaAssociationNullable() {
      void* val = IPWorks_OData_Get(m_pObj, 93, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetSchemaAssociationOnDelete() {
      void* val = IPWorks_OData_Get(m_pObj, 94, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetSchemaAssociationPartner() {
      void* val = IPWorks_OData_Get(m_pObj, 95, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaAssociationRefConstraintCount() {
      void* val = IPWorks_OData_Get(m_pObj, 96, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetSchemaAssociationRefConstraintIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 97, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSchemaAssociationRefConstraintIndex(int iSchemaAssociationRefConstraintIndex) {
      void* val = (void*)IPW64CAST(iSchemaAssociationRefConstraintIndex);
      return IPWorks_OData_Set(m_pObj, 97, 0, val, 0);
    }

    inline char* GetSchemaAssociationRefConstraintProperty() {
      void* val = IPWorks_OData_Get(m_pObj, 98, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationRefConstraintReferencedProperty() {
      void* val = IPWorks_OData_Get(m_pObj, 99, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationRelationship() {
      void* val = IPWorks_OData_Get(m_pObj, 100, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationSummary() {
      void* val = IPWorks_OData_Get(m_pObj, 101, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationToRole() {
      void* val = IPWorks_OData_Get(m_pObj, 102, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationToRoleDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 103, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationToRoleEntity() {
      void* val = IPWorks_OData_Get(m_pObj, 104, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaAssociationToRoleMultiplicity() {
      void* val = IPWorks_OData_Get(m_pObj, 105, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetSchemaAssociationToRoleSummary() {
      void* val = IPWorks_OData_Get(m_pObj, 106, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaAssociationType() {
      void* val = IPWorks_OData_Get(m_pObj, 107, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaAssociationCount() {
      void* val = IPWorks_OData_Get(m_pObj, 108, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetSchemaAssociationIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 109, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSchemaAssociationIndex(int iSchemaAssociationIndex) {
      void* val = (void*)IPW64CAST(iSchemaAssociationIndex);
      return IPWorks_OData_Set(m_pObj, 109, 0, val, 0);
    }

    inline char* GetSchemaEntityDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 110, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaEntityName() {
      void* val = IPWorks_OData_Get(m_pObj, 111, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaEntitySummary() {
      void* val = IPWorks_OData_Get(m_pObj, 112, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaEntityCount() {
      void* val = IPWorks_OData_Get(m_pObj, 113, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetSchemaEntityIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 114, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSchemaEntityIndex(int iSchemaEntityIndex) {
      void* val = (void*)IPW64CAST(iSchemaEntityIndex);
      return IPWorks_OData_Set(m_pObj, 114, 0, val, 0);
    }

    inline int GetSchemaKeysCount() {
      void* val = IPWorks_OData_Get(m_pObj, 115, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetSchemaKeys(int iSchemaKeysIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 116, iSchemaKeysIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaPropertyAttributes() {
      void* val = IPWorks_OData_Get(m_pObj, 117, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaPropertyDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 118, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaPropertyIsComplexType() {
      void* val = IPWorks_OData_Get(m_pObj, 119, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetSchemaPropertyName() {
      void* val = IPWorks_OData_Get(m_pObj, 120, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaPropertyNullable() {
      void* val = IPWorks_OData_Get(m_pObj, 121, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetSchemaPropertySummary() {
      void* val = IPWorks_OData_Get(m_pObj, 122, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaPropertyType() {
      void* val = IPWorks_OData_Get(m_pObj, 123, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaPropertyCount() {
      void* val = IPWorks_OData_Get(m_pObj, 124, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetSchemaPropertyIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 125, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSchemaPropertyIndex(int iSchemaPropertyIndex) {
      void* val = (void*)IPW64CAST(iSchemaPropertyIndex);
      return IPWorks_OData_Set(m_pObj, 125, 0, val, 0);
    }

    inline char* GetSchemaTypeFieldAttributes() {
      void* val = IPWorks_OData_Get(m_pObj, 126, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaTypeFieldDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 127, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaTypeFieldIsComplexType() {
      void* val = IPWorks_OData_Get(m_pObj, 128, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetSchemaTypeFieldName() {
      void* val = IPWorks_OData_Get(m_pObj, 129, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaTypeFieldNullable() {
      void* val = IPWorks_OData_Get(m_pObj, 130, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetSchemaTypeFieldSummary() {
      void* val = IPWorks_OData_Get(m_pObj, 131, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSchemaTypeFieldType() {
      void* val = IPWorks_OData_Get(m_pObj, 132, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSchemaTypeFieldCount() {
      void* val = IPWorks_OData_Get(m_pObj, 133, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetSchemaTypeFieldIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 134, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSchemaTypeFieldIndex(int iSchemaTypeFieldIndex) {
      void* val = (void*)IPW64CAST(iSchemaTypeFieldIndex);
      return IPWorks_OData_Set(m_pObj, 134, 0, val, 0);
    }

    inline char* GetServiceRootURI() {
      void* val = IPWorks_OData_Get(m_pObj, 135, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetServiceRootURI(const char* lpszServiceRootURI) {
      return IPWorks_OData_Set(m_pObj, 135, 0, (void*)lpszServiceRootURI, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_OData_Get(m_pObj, 136, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_OData_Set(m_pObj, 136, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_OData_Get(m_pObj, 137, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_OData_Set(m_pObj, 137, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_OData_Get(m_pObj, 138, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_OData_Set(m_pObj, 138, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_OData_Get(m_pObj, 139, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_OData_Set(m_pObj, 139, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_OData_Get(m_pObj, 140, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_OData_Set(m_pObj, 140, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_OData_Get(m_pObj, 141, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_OData_Set(m_pObj, 141, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_OData_Get(m_pObj, 142, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetTimeout() {
      void* val = IPWorks_OData_Get(m_pObj, 143, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_OData_Set(m_pObj, 143, 0, val, 0);
    }

    inline int GetTransferredData(char* &lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_OData_Get(m_pObj, 144, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline char* GetUser() {
      void* val = IPWorks_OData_Get(m_pObj, 145, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_OData_Set(m_pObj, 145, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int CreateEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int CustomRequest(const char* lpszHTTPMethod, const char* lpszURL, const char* lpszPostData) {
      void *param[3+1] = {(void*)IPW64CAST(lpszHTTPMethod), (void*)IPW64CAST(lpszURL), (void*)IPW64CAST(lpszPostData), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 4, 3, param, cbparam, NULL);
    }

    inline int DeleteEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline char* GetEntryProperty(const char* lpszXPath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXPath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 6, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int GetSchema() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int HasXPath(const char* lpszXPath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXPath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 8, 1, param, cbparam, NULL);
      return (int)IPW64CAST(param[1]);
    }

    inline int QueryService() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int SetEntryProperty(const char* lpszXPath, const char* lpszValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszXPath), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 11, 2, param, cbparam, NULL);
    }

    inline int SetSchemaEntity(const char* lpszName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 12, 1, param, cbparam, NULL);
    }

    inline int SetSchemaProperty(const char* lpszName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 13, 1, param, cbparam, NULL);
    }

    inline int SetSchemaType(const char* lpszName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 14, 1, param, cbparam, NULL);
    }

    inline int UpdateEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 15, 0, param, cbparam, NULL);
    }

    inline int UpdateProperty(const char* lpszXPath, const char* lpszValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszXPath), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 16, 2, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_ODATA_H_
