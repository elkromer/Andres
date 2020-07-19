/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_RSS_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_RSS_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_RSS_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_RSS_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_RSS_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_RSS_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_RSS_StaticDestroy();

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
} RSSConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} RSSConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} RSSDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} RSSEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} RSSErrorEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} RSSHeaderEventParams;

typedef struct {
  int LogLevel;
  const char *Message;
  const char *LogType;
  int reserved;
} RSSLogEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} RSSOPMLHeaderEventParams;

typedef struct {
  int Level;
  const char *Text;
  const char *TypeName;
  const char *Title;
  const char *URL;
  const char *XMLURL;
  const char *HTMLURL;
  const char *Created;
  const char *Description;
  const char *OtherAttrs;
  int reserved;
} RSSOPMLOutlineEventParams;

typedef struct {
  const char *Location;
  int Accept;
  int reserved;
} RSSRedirectEventParams;

typedef struct {
  const char *Name;
  const char *Value;
  const char *Expires;
  const char *Domain;
  const char *Path;
  int Secure;
  int reserved;
} RSSSetCookieEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} RSSSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} RSSSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} RSSStartTransferEventParams;

typedef struct {
  const char *HTTPVersion;
  int StatusCode;
  const char *Description;
  int reserved;
} RSSStatusEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int reserved;
} RSSTransferEventParams;


class RSS {
  public: // Events
    virtual int FireConnected(RSSConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(RSSConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(RSSDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(RSSEndTransferEventParams *e) {return 0;}
    virtual int FireError(RSSErrorEventParams *e) {return 0;}
    virtual int FireHeader(RSSHeaderEventParams *e) {return 0;}
    virtual int FireLog(RSSLogEventParams *e) {return 0;}
    virtual int FireOPMLHeader(RSSOPMLHeaderEventParams *e) {return 0;}
    virtual int FireOPMLOutline(RSSOPMLOutlineEventParams *e) {return 0;}
    virtual int FireRedirect(RSSRedirectEventParams *e) {return 0;}
    virtual int FireSetCookie(RSSSetCookieEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(RSSSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(RSSSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(RSSStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(RSSStatusEventParams *e) {return 0;}
    virtual int FireTransfer(RSSTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL RSSEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          RSSConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((RSS*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          RSSConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((RSS*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          RSSDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((RSS*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          RSSEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((RSS*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          RSSErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((RSS*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          RSSHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((RSS*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          RSSLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((RSS*)lpObj)->FireLog(&e);
          break;
        }
        case 8: {
          RSSOPMLHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((RSS*)lpObj)->FireOPMLHeader(&e);
          break;
        }
        case 9: {
          RSSOPMLOutlineEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), (char*)IPW64CAST(param[7]), (char*)IPW64CAST(param[8]), (char*)IPW64CAST(param[9]), 0};
          ret_code = ((RSS*)lpObj)->FireOPMLOutline(&e);
          break;
        }
        case 10: {
          RSSRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), 0};
          ret_code = ((RSS*)lpObj)->FireRedirect(&e);
          param[1] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 11: {
          RSSSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), 0};
          ret_code = ((RSS*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 12: {
          RSSSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((RSS*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 13: {
          RSSSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((RSS*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 14: {
          RSSStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((RSS*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 15: {
          RSSStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((RSS*)lpObj)->FireStatus(&e);
          break;
        }
        case 16: {
          RSSTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), 0};
          ret_code = ((RSS*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    RSS(char *lpOemKey = (char*)IPWORKS_OEMKEY_59) {
      m_pObj = IPWorks_RSS_Create(RSSEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~RSS() {
      IPWorks_RSS_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_RSS_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_RSS_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_RSS_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_RSS_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_RSS_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetAccept() {
      void* val = IPWorks_RSS_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAccept(const char* lpszAccept) {
      return IPWorks_RSS_Set(m_pObj, 1, 0, (void*)lpszAccept, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_RSS_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthorization(const char* lpszAuthorization) {
      return IPWorks_RSS_Set(m_pObj, 2, 0, (void*)lpszAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_RSS_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_RSS_Set(m_pObj, 3, 0, val, 0);
    }

    inline char* GetChannelCategory() {
      void* val = IPWorks_RSS_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelCategory(const char* lpszChannelCategory) {
      return IPWorks_RSS_Set(m_pObj, 4, 0, (void*)lpszChannelCategory, 0);
    }

    inline char* GetChannelCategoryDomain() {
      void* val = IPWorks_RSS_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelCategoryDomain(const char* lpszChannelCategoryDomain) {
      return IPWorks_RSS_Set(m_pObj, 5, 0, (void*)lpszChannelCategoryDomain, 0);
    }

    inline char* GetChannelCopyright() {
      void* val = IPWorks_RSS_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelCopyright(const char* lpszChannelCopyright) {
      return IPWorks_RSS_Set(m_pObj, 6, 0, (void*)lpszChannelCopyright, 0);
    }

    inline char* GetChannelDescription() {
      void* val = IPWorks_RSS_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelDescription(const char* lpszChannelDescription) {
      return IPWorks_RSS_Set(m_pObj, 7, 0, (void*)lpszChannelDescription, 0);
    }

    inline char* GetChannelDocs() {
      void* val = IPWorks_RSS_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelDocs(const char* lpszChannelDocs) {
      return IPWorks_RSS_Set(m_pObj, 8, 0, (void*)lpszChannelDocs, 0);
    }

    inline char* GetChannelGenerator() {
      void* val = IPWorks_RSS_Get(m_pObj, 9, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelGenerator(const char* lpszChannelGenerator) {
      return IPWorks_RSS_Set(m_pObj, 9, 0, (void*)lpszChannelGenerator, 0);
    }

    inline char* GetChannelImageDescription() {
      void* val = IPWorks_RSS_Get(m_pObj, 10, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelImageDescription(const char* lpszChannelImageDescription) {
      return IPWorks_RSS_Set(m_pObj, 10, 0, (void*)lpszChannelImageDescription, 0);
    }

    inline char* GetChannelImageHeight() {
      void* val = IPWorks_RSS_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelImageHeight(const char* lpszChannelImageHeight) {
      return IPWorks_RSS_Set(m_pObj, 11, 0, (void*)lpszChannelImageHeight, 0);
    }

    inline char* GetChannelImageLink() {
      void* val = IPWorks_RSS_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelImageLink(const char* lpszChannelImageLink) {
      return IPWorks_RSS_Set(m_pObj, 12, 0, (void*)lpszChannelImageLink, 0);
    }

    inline char* GetChannelImageTitle() {
      void* val = IPWorks_RSS_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelImageTitle(const char* lpszChannelImageTitle) {
      return IPWorks_RSS_Set(m_pObj, 13, 0, (void*)lpszChannelImageTitle, 0);
    }

    inline char* GetChannelImageUrl() {
      void* val = IPWorks_RSS_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelImageUrl(const char* lpszChannelImageUrl) {
      return IPWorks_RSS_Set(m_pObj, 14, 0, (void*)lpszChannelImageUrl, 0);
    }

    inline char* GetChannelImageWidth() {
      void* val = IPWorks_RSS_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelImageWidth(const char* lpszChannelImageWidth) {
      return IPWorks_RSS_Set(m_pObj, 15, 0, (void*)lpszChannelImageWidth, 0);
    }

    inline char* GetChannelLanguage() {
      void* val = IPWorks_RSS_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLanguage(const char* lpszChannelLanguage) {
      return IPWorks_RSS_Set(m_pObj, 16, 0, (void*)lpszChannelLanguage, 0);
    }

    inline char* GetChannelLastBuildDate() {
      void* val = IPWorks_RSS_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLastBuildDate(const char* lpszChannelLastBuildDate) {
      return IPWorks_RSS_Set(m_pObj, 17, 0, (void*)lpszChannelLastBuildDate, 0);
    }

    inline char* GetChannelLink() {
      void* val = IPWorks_RSS_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelLink(const char* lpszChannelLink) {
      return IPWorks_RSS_Set(m_pObj, 18, 0, (void*)lpszChannelLink, 0);
    }

    inline char* GetChannelManagingEditor() {
      void* val = IPWorks_RSS_Get(m_pObj, 19, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelManagingEditor(const char* lpszChannelManagingEditor) {
      return IPWorks_RSS_Set(m_pObj, 19, 0, (void*)lpszChannelManagingEditor, 0);
    }

    inline char* GetChannelPubDate() {
      void* val = IPWorks_RSS_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelPubDate(const char* lpszChannelPubDate) {
      return IPWorks_RSS_Set(m_pObj, 20, 0, (void*)lpszChannelPubDate, 0);
    }

    inline char* GetChannelSkipDays() {
      void* val = IPWorks_RSS_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelSkipDays(const char* lpszChannelSkipDays) {
      return IPWorks_RSS_Set(m_pObj, 21, 0, (void*)lpszChannelSkipDays, 0);
    }

    inline char* GetChannelSkipHours() {
      void* val = IPWorks_RSS_Get(m_pObj, 22, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelSkipHours(const char* lpszChannelSkipHours) {
      return IPWorks_RSS_Set(m_pObj, 22, 0, (void*)lpszChannelSkipHours, 0);
    }

    inline char* GetChannelTitle() {
      void* val = IPWorks_RSS_Get(m_pObj, 23, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelTitle(const char* lpszChannelTitle) {
      return IPWorks_RSS_Set(m_pObj, 23, 0, (void*)lpszChannelTitle, 0);
    }

    inline char* GetChannelTtl() {
      void* val = IPWorks_RSS_Get(m_pObj, 24, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelTtl(const char* lpszChannelTtl) {
      return IPWorks_RSS_Set(m_pObj, 24, 0, (void*)lpszChannelTtl, 0);
    }

    inline char* GetChannelWebMaster() {
      void* val = IPWorks_RSS_Get(m_pObj, 25, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetChannelWebMaster(const char* lpszChannelWebMaster) {
      return IPWorks_RSS_Set(m_pObj, 25, 0, (void*)lpszChannelWebMaster, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_RSS_Get(m_pObj, 26, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_RSS_Set(m_pObj, 26, 0, val, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_RSS_Get(m_pObj, 27, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_RSS_Set(m_pObj, 27, 0, val, 0);
    }

    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 28, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 29, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 30, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieName(int iCookieIndex, const char* lpszCookieName) {
      return IPWorks_RSS_Set(m_pObj, 30, iCookieIndex, (void*)lpszCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 31, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 32, iCookieIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 33, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieValue(int iCookieIndex, const char* lpszCookieValue) {
      return IPWorks_RSS_Set(m_pObj, 33, iCookieIndex, (void*)lpszCookieValue, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_RSS_Get(m_pObj, 34, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_RSS_Set(m_pObj, 34, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_RSS_Get(m_pObj, 35, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_RSS_Set(m_pObj, 35, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_RSS_Get(m_pObj, 36, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_RSS_Set(m_pObj, 36, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_RSS_Get(m_pObj, 37, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_RSS_Set(m_pObj, 37, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_RSS_Get(m_pObj, 38, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_RSS_Set(m_pObj, 38, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_RSS_Get(m_pObj, 39, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_RSS_Set(m_pObj, 39, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_RSS_Get(m_pObj, 40, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_RSS_Set(m_pObj, 40, 0, val, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_RSS_Get(m_pObj, 41, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetIfModifiedSince() {
      void* val = IPWorks_RSS_Get(m_pObj, 42, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetIfModifiedSince(const char* lpszIfModifiedSince) {
      return IPWorks_RSS_Set(m_pObj, 42, 0, (void*)lpszIfModifiedSince, 0);
    }

    inline int GetItemCount() {
      void* val = IPWorks_RSS_Get(m_pObj, 43, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetItemCount(int iItemCount) {
      void* val = (void*)IPW64CAST(iItemCount);
      return IPWorks_RSS_Set(m_pObj, 43, 0, val, 0);
    }

    inline char* GetItemAuthor(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 44, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemAuthor(int iItemIndex, const char* lpszItemAuthor) {
      return IPWorks_RSS_Set(m_pObj, 44, iItemIndex, (void*)lpszItemAuthor, 0);
    }

    inline char* GetItemCategory(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 45, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemCategory(int iItemIndex, const char* lpszItemCategory) {
      return IPWorks_RSS_Set(m_pObj, 45, iItemIndex, (void*)lpszItemCategory, 0);
    }

    inline char* GetItemCategoryDomain(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 46, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemCategoryDomain(int iItemIndex, const char* lpszItemCategoryDomain) {
      return IPWorks_RSS_Set(m_pObj, 46, iItemIndex, (void*)lpszItemCategoryDomain, 0);
    }

    inline char* GetItemComments(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 47, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemComments(int iItemIndex, const char* lpszItemComments) {
      return IPWorks_RSS_Set(m_pObj, 47, iItemIndex, (void*)lpszItemComments, 0);
    }

    inline char* GetItemDescription(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 48, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemDescription(int iItemIndex, const char* lpszItemDescription) {
      return IPWorks_RSS_Set(m_pObj, 48, iItemIndex, (void*)lpszItemDescription, 0);
    }

    inline char* GetItemEnclosureLength(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 49, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemEnclosureLength(int iItemIndex, const char* lpszItemEnclosureLength) {
      return IPWorks_RSS_Set(m_pObj, 49, iItemIndex, (void*)lpszItemEnclosureLength, 0);
    }

    inline char* GetItemEnclosureType(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 50, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemEnclosureType(int iItemIndex, const char* lpszItemEnclosureType) {
      return IPWorks_RSS_Set(m_pObj, 50, iItemIndex, (void*)lpszItemEnclosureType, 0);
    }

    inline char* GetItemEnclosureUrl(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 51, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemEnclosureUrl(int iItemIndex, const char* lpszItemEnclosureUrl) {
      return IPWorks_RSS_Set(m_pObj, 51, iItemIndex, (void*)lpszItemEnclosureUrl, 0);
    }

    inline char* GetItemGuid(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 52, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemGuid(int iItemIndex, const char* lpszItemGuid) {
      return IPWorks_RSS_Set(m_pObj, 52, iItemIndex, (void*)lpszItemGuid, 0);
    }

    inline int GetItemGuidIsPermaLink(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 53, iItemIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetItemGuidIsPermaLink(int iItemIndex, int bItemGuidIsPermaLink) {
      void* val = (void*)IPW64CAST(bItemGuidIsPermaLink);
      return IPWorks_RSS_Set(m_pObj, 53, iItemIndex, val, 0);
    }

    inline char* GetItemXML(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 54, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemXML(int iItemIndex, const char* lpszItemXML) {
      return IPWorks_RSS_Set(m_pObj, 54, iItemIndex, (void*)lpszItemXML, 0);
    }

    inline char* GetItemLink(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 55, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemLink(int iItemIndex, const char* lpszItemLink) {
      return IPWorks_RSS_Set(m_pObj, 55, iItemIndex, (void*)lpszItemLink, 0);
    }

    inline char* GetItemPubDate(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 56, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemPubDate(int iItemIndex, const char* lpszItemPubDate) {
      return IPWorks_RSS_Set(m_pObj, 56, iItemIndex, (void*)lpszItemPubDate, 0);
    }

    inline char* GetItemSource(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 57, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemSource(int iItemIndex, const char* lpszItemSource) {
      return IPWorks_RSS_Set(m_pObj, 57, iItemIndex, (void*)lpszItemSource, 0);
    }

    inline char* GetItemSourceURL(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 58, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemSourceURL(int iItemIndex, const char* lpszItemSourceURL) {
      return IPWorks_RSS_Set(m_pObj, 58, iItemIndex, (void*)lpszItemSourceURL, 0);
    }

    inline char* GetItemTitle(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 59, iItemIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetItemTitle(int iItemIndex, const char* lpszItemTitle) {
      return IPWorks_RSS_Set(m_pObj, 59, iItemIndex, (void*)lpszItemTitle, 0);
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_RSS_Get(m_pObj, 60, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_RSS_Get(m_pObj, 60+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_RSS_Set(m_pObj, 60, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_RSS_Set(m_pObj, 60+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_RSS_Get(m_pObj, 61, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_RSS_Set(m_pObj, 61, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_RSS_Get(m_pObj, 62, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetNamespaceCount(int iNamespaceCount) {
      void* val = (void*)IPW64CAST(iNamespaceCount);
      return IPWorks_RSS_Set(m_pObj, 62, 0, val, 0);
    }

    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 63, iNamespaceIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetNamespacePrefix(int iNamespaceIndex, const char* lpszNamespacePrefix) {
      return IPWorks_RSS_Set(m_pObj, 63, iNamespaceIndex, (void*)lpszNamespacePrefix, 0);
    }

    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 64, iNamespaceIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetNamespaceURI(int iNamespaceIndex, const char* lpszNamespaceURI) {
      return IPWorks_RSS_Set(m_pObj, 64, iNamespaceIndex, (void*)lpszNamespaceURI, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_RSS_Get(m_pObj, 65, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherHeaders(const char* lpszOtherHeaders) {
      return IPWorks_RSS_Set(m_pObj, 65, 0, (void*)lpszOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_RSS_Get(m_pObj, 66, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 67, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 68, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_RSS_Get(m_pObj, 69, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_RSS_Set(m_pObj, 69, 0, (void*)lpszPassword, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_RSS_Get(m_pObj, 70, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_RSS_Set(m_pObj, 70, 0, val, 0);
    }

    inline int GetProxyAutoDetect() {
      void* val = IPWorks_RSS_Get(m_pObj, 71, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_RSS_Set(m_pObj, 71, 0, val, 0);
    }

    inline char* GetProxyPassword() {
      void* val = IPWorks_RSS_Get(m_pObj, 72, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyPassword(const char* lpszProxyPassword) {
      return IPWorks_RSS_Set(m_pObj, 72, 0, (void*)lpszProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_RSS_Get(m_pObj, 73, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyPort(int iProxyPort) {
      void* val = (void*)IPW64CAST(iProxyPort);
      return IPWorks_RSS_Set(m_pObj, 73, 0, val, 0);
    }

    inline char* GetProxyServer() {
      void* val = IPWorks_RSS_Get(m_pObj, 74, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyServer(const char* lpszProxyServer) {
      return IPWorks_RSS_Set(m_pObj, 74, 0, (void*)lpszProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_RSS_Get(m_pObj, 75, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_RSS_Set(m_pObj, 75, 0, val, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_RSS_Get(m_pObj, 76, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyUser(const char* lpszProxyUser) {
      return IPWorks_RSS_Set(m_pObj, 76, 0, (void*)lpszProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_RSS_Get(m_pObj, 77, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReferer(const char* lpszReferer) {
      return IPWorks_RSS_Set(m_pObj, 77, 0, (void*)lpszReferer, 0);
    }

    inline char* GetRSSData() {
      void* val = IPWorks_RSS_Get(m_pObj, 78, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRSSData(const char* lpszRSSData) {
      return IPWorks_RSS_Set(m_pObj, 78, 0, (void*)lpszRSSData, 0);
    }

    inline int GetRSSVersion() {
      void* val = IPWorks_RSS_Get(m_pObj, 79, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRSSVersion(int iRSSVersion) {
      void* val = (void*)IPW64CAST(iRSSVersion);
      return IPWorks_RSS_Set(m_pObj, 79, 0, val, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_RSS_Get(m_pObj, 80, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_RSS_Set(m_pObj, 80, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_RSS_Get(m_pObj, 81, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_RSS_Set(m_pObj, 81, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_RSS_Get(m_pObj, 82, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_RSS_Set(m_pObj, 82, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_RSS_Get(m_pObj, 83, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_RSS_Set(m_pObj, 83, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_RSS_Get(m_pObj, 84, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_RSS_Set(m_pObj, 84, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_RSS_Get(m_pObj, 85, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_RSS_Set(m_pObj, 85, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_RSS_Get(m_pObj, 86, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetTimeout() {
      void* val = IPWorks_RSS_Get(m_pObj, 87, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_RSS_Set(m_pObj, 87, 0, val, 0);
    }

    inline int GetTransferredData(char* &lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_RSS_Get(m_pObj, 88, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline int64 GetTransferredDataLimit() {
      int64 retVal;
      IPWorks_RSS_Get(m_pObj, 89, 0, NULL, &retVal);
      return retVal;
    }
    inline int SetTransferredDataLimit(int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_RSS_Set(m_pObj, 89, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_RSS_Get(m_pObj, 90, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetUser() {
      void* val = IPWorks_RSS_Get(m_pObj, 91, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_RSS_Set(m_pObj, 91, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 2, 2, param, cbparam, NULL);
    }

    inline int AddItem(const char* lpszTitle, const char* lpszDescription, const char* lpszLink) {
      void *param[3+1] = {(void*)IPW64CAST(lpszTitle), (void*)IPW64CAST(lpszDescription), (void*)IPW64CAST(lpszLink), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 3, 3, param, cbparam, NULL);
    }

    inline int AddNamespace(const char* lpszPrefix, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPrefix), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 4, 2, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 5, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int GetFeed(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 7, 1, param, cbparam, NULL);
    }

    inline char* GetProperty(const char* lpszPropertyName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPropertyName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 8, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int GetURL(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 9, 1, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline char* OPMLAttr(const char* lpszAttrName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 11, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Put(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 12, 1, param, cbparam, NULL);
    }

    inline int ReadFile(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 13, 1, param, cbparam, NULL);
    }

    inline int ReadOPML(const char* lpszOPMLFile) {
      void *param[1+1] = {(void*)IPW64CAST(lpszOPMLFile), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 14, 1, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 15, 0, param, cbparam, NULL);
    }

    inline int SetProperty(const char* lpszPropertyName, const char* lpszPropertyValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPropertyName), (void*)IPW64CAST(lpszPropertyValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 16, 2, param, cbparam, NULL);
    }

    inline int WriteFile(const char* lpszFilename) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFilename), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 17, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_RSS_H_
