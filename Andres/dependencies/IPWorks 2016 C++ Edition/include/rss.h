/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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


extern "C" void* IPWORKS_CALL IPWorks_RSS_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_RSS_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_RSS_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_RSS_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_RSS_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_RSS_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_RSS_GetLastErrorCode(void *lpObj);
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
  const char* Description;
  int reserved;
} RSSConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} RSSConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} RSSDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} RSSEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} RSSErrorEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} RSSHeaderEventParams;

typedef struct {
  int LogLevel;
  const char* Message;
  const char* LogType;
  int reserved;
} RSSLogEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} RSSOPMLHeaderEventParams;

typedef struct {
  int Level;
  const char* Text;
  const char* TypeName;
  const char* Title;
  const char* URL;
  const char* XMLURL;
  const char* HTMLURL;
  const char* Created;
  const char* Description;
  const char* OtherAttrs;
  int reserved;
} RSSOPMLOutlineEventParams;

typedef struct {
  const char* Location;
  int Accept;
  int reserved;
} RSSRedirectEventParams;

typedef struct {
  const char* Name;
  const char* Value;
  const char* Expires;
  const char* Domain;
  const char* Path;
  int Secure;
  int reserved;
} RSSSetCookieEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} RSSSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} RSSSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} RSSStartTransferEventParams;

typedef struct {
  const char* HTTPVersion;
  int StatusCode;
  const char* Description;
  int reserved;
} RSSStatusEventParams;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  const char* Text;
  int lenText;
  int reserved;
} RSSTransferEventParams;



class RSS {
  
  public: //events
  
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
      if (event_id > 10000) return ((RSS*)lpObj)->RSSEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            RSSConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((RSS*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            RSSConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((RSS*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            RSSDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((RSS*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            RSSEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((RSS*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 5: {
            RSSErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((RSS*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            RSSHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((RSS*)lpObj)->FireHeader(&e);
            break;
         }
         case 7: {
            RSSLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((RSS*)lpObj)->FireLog(&e);
            break;
         }
         case 8: {
            RSSOPMLHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((RSS*)lpObj)->FireOPMLHeader(&e);
            break;
         }
         case 9: {
            RSSOPMLOutlineEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), (char*)IPW64CAST(param[7]), (char*)IPW64CAST(param[8]), (char*)IPW64CAST(param[9]),  0};
            ret_code = ((RSS*)lpObj)->FireOPMLOutline(&e);
            break;
         }
         case 10: {
            RSSRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = ((RSS*)lpObj)->FireRedirect(&e);
            param[1] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 11: {
            RSSSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = ((RSS*)lpObj)->FireSetCookie(&e);
            break;
         }
         case 12: {
            RSSSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((RSS*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 13: {
            RSSSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((RSS*)lpObj)->FireSSLStatus(&e);
            break;
         }
         case 14: {
            RSSStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((RSS*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 15: {
            RSSStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((RSS*)lpObj)->FireStatus(&e);
            break;
         }
         case 16: {
            RSSTransferEventParams e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((RSS*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int RSSEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    RSS(char *lpOemKey = (char*)IPWORKS_OEMKEY_59) {
      m_pObj = IPWorks_RSS_Create(RSSEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~RSS() {
      IPWorks_RSS_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_RSS_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_RSS_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_RSS_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_RSS_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_RSS_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetAccept() {
      void* val = IPWorks_RSS_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetAccept(const char *lpAccept) {
      return IPWorks_RSS_Set(m_pObj, 1, 0, (void*)lpAccept, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_RSS_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorization(const char *lpAuthorization) {
      return IPWorks_RSS_Set(m_pObj, 2, 0, (void*)lpAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_RSS_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_RSS_Set(m_pObj, 3, 0, val, 0);
    }
    inline char* GetChannelCategory() {
      void* val = IPWorks_RSS_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetChannelCategory(const char *lpChannelCategory) {
      return IPWorks_RSS_Set(m_pObj, 4, 0, (void*)lpChannelCategory, 0);
    }

    inline char* GetChannelCategoryDomain() {
      void* val = IPWorks_RSS_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetChannelCategoryDomain(const char *lpChannelCategoryDomain) {
      return IPWorks_RSS_Set(m_pObj, 5, 0, (void*)lpChannelCategoryDomain, 0);
    }

    inline char* GetChannelCopyright() {
      void* val = IPWorks_RSS_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetChannelCopyright(const char *lpChannelCopyright) {
      return IPWorks_RSS_Set(m_pObj, 6, 0, (void*)lpChannelCopyright, 0);
    }

    inline char* GetChannelDescription() {
      void* val = IPWorks_RSS_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetChannelDescription(const char *lpChannelDescription) {
      return IPWorks_RSS_Set(m_pObj, 7, 0, (void*)lpChannelDescription, 0);
    }

    inline char* GetChannelDocs() {
      void* val = IPWorks_RSS_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetChannelDocs(const char *lpChannelDocs) {
      return IPWorks_RSS_Set(m_pObj, 8, 0, (void*)lpChannelDocs, 0);
    }

    inline char* GetChannelGenerator() {
      void* val = IPWorks_RSS_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetChannelGenerator(const char *lpChannelGenerator) {
      return IPWorks_RSS_Set(m_pObj, 9, 0, (void*)lpChannelGenerator, 0);
    }

    inline char* GetChannelImageDescription() {
      void* val = IPWorks_RSS_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }

    inline int SetChannelImageDescription(const char *lpChannelImageDescription) {
      return IPWorks_RSS_Set(m_pObj, 10, 0, (void*)lpChannelImageDescription, 0);
    }

    inline char* GetChannelImageHeight() {
      void* val = IPWorks_RSS_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetChannelImageHeight(const char *lpChannelImageHeight) {
      return IPWorks_RSS_Set(m_pObj, 11, 0, (void*)lpChannelImageHeight, 0);
    }

    inline char* GetChannelImageLink() {
      void* val = IPWorks_RSS_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetChannelImageLink(const char *lpChannelImageLink) {
      return IPWorks_RSS_Set(m_pObj, 12, 0, (void*)lpChannelImageLink, 0);
    }

    inline char* GetChannelImageTitle() {
      void* val = IPWorks_RSS_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetChannelImageTitle(const char *lpChannelImageTitle) {
      return IPWorks_RSS_Set(m_pObj, 13, 0, (void*)lpChannelImageTitle, 0);
    }

    inline char* GetChannelImageUrl() {
      void* val = IPWorks_RSS_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetChannelImageUrl(const char *lpChannelImageUrl) {
      return IPWorks_RSS_Set(m_pObj, 14, 0, (void*)lpChannelImageUrl, 0);
    }

    inline char* GetChannelImageWidth() {
      void* val = IPWorks_RSS_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetChannelImageWidth(const char *lpChannelImageWidth) {
      return IPWorks_RSS_Set(m_pObj, 15, 0, (void*)lpChannelImageWidth, 0);
    }

    inline char* GetChannelLanguage() {
      void* val = IPWorks_RSS_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLanguage(const char *lpChannelLanguage) {
      return IPWorks_RSS_Set(m_pObj, 16, 0, (void*)lpChannelLanguage, 0);
    }

    inline char* GetChannelLastBuildDate() {
      void* val = IPWorks_RSS_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLastBuildDate(const char *lpChannelLastBuildDate) {
      return IPWorks_RSS_Set(m_pObj, 17, 0, (void*)lpChannelLastBuildDate, 0);
    }

    inline char* GetChannelLink() {
      void* val = IPWorks_RSS_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLink(const char *lpChannelLink) {
      return IPWorks_RSS_Set(m_pObj, 18, 0, (void*)lpChannelLink, 0);
    }

    inline char* GetChannelManagingEditor() {
      void* val = IPWorks_RSS_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetChannelManagingEditor(const char *lpChannelManagingEditor) {
      return IPWorks_RSS_Set(m_pObj, 19, 0, (void*)lpChannelManagingEditor, 0);
    }

    inline char* GetChannelPubDate() {
      void* val = IPWorks_RSS_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetChannelPubDate(const char *lpChannelPubDate) {
      return IPWorks_RSS_Set(m_pObj, 20, 0, (void*)lpChannelPubDate, 0);
    }

    inline char* GetChannelSkipDays() {
      void* val = IPWorks_RSS_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetChannelSkipDays(const char *lpChannelSkipDays) {
      return IPWorks_RSS_Set(m_pObj, 21, 0, (void*)lpChannelSkipDays, 0);
    }

    inline char* GetChannelSkipHours() {
      void* val = IPWorks_RSS_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetChannelSkipHours(const char *lpChannelSkipHours) {
      return IPWorks_RSS_Set(m_pObj, 22, 0, (void*)lpChannelSkipHours, 0);
    }

    inline char* GetChannelTitle() {
      void* val = IPWorks_RSS_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }

    inline int SetChannelTitle(const char *lpChannelTitle) {
      return IPWorks_RSS_Set(m_pObj, 23, 0, (void*)lpChannelTitle, 0);
    }

    inline char* GetChannelTtl() {
      void* val = IPWorks_RSS_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetChannelTtl(const char *lpChannelTtl) {
      return IPWorks_RSS_Set(m_pObj, 24, 0, (void*)lpChannelTtl, 0);
    }

    inline char* GetChannelWebMaster() {
      void* val = IPWorks_RSS_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }

    inline int SetChannelWebMaster(const char *lpChannelWebMaster) {
      return IPWorks_RSS_Set(m_pObj, 25, 0, (void*)lpChannelWebMaster, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_RSS_Get(m_pObj, 26, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_RSS_Set(m_pObj, 26, 0, val, 0);
    }
    inline int GetCookieCount() {
      void* val = IPWorks_RSS_Get(m_pObj, 27, 0, 0);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_RSS_Set(m_pObj, 27, 0, val, 0);
    }
    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 28, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 29, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 30, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieName(int iCookieIndex, const char *lpCookieName) {
      return IPWorks_RSS_Set(m_pObj, 30, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 31, iCookieIndex, 0);
      return (char*)val;
    }


    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 32, iCookieIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 33, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieValue(int iCookieIndex, const char *lpCookieValue) {
      return IPWorks_RSS_Set(m_pObj, 33, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_RSS_Get(m_pObj, 34, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_RSS_Set(m_pObj, 34, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_RSS_Get(m_pObj, 35, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_RSS_Set(m_pObj, 35, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_RSS_Get(m_pObj, 36, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_RSS_Set(m_pObj, 36, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_RSS_Get(m_pObj, 37, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_RSS_Set(m_pObj, 37, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_RSS_Get(m_pObj, 38, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_RSS_Set(m_pObj, 38, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_RSS_Get(m_pObj, 39, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_RSS_Set(m_pObj, 39, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_RSS_Get(m_pObj, 40, 0, 0);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_RSS_Set(m_pObj, 40, 0, val, 0);
    }
    inline int GetIdle() {
      void* val = IPWorks_RSS_Get(m_pObj, 41, 0, 0);
      return (int)(long)val;
    }

    inline char* GetIfModifiedSince() {
      void* val = IPWorks_RSS_Get(m_pObj, 42, 0, 0);
      return (char*)val;
    }

    inline int SetIfModifiedSince(const char *lpIfModifiedSince) {
      return IPWorks_RSS_Set(m_pObj, 42, 0, (void*)lpIfModifiedSince, 0);
    }

    inline int GetItemCount() {
      void* val = IPWorks_RSS_Get(m_pObj, 43, 0, 0);
      return (int)(long)val;
    }
    inline int SetItemCount(int iItemCount) {
      void* val = (void*)IPW64CAST(iItemCount);
      return IPWorks_RSS_Set(m_pObj, 43, 0, val, 0);
    }
    inline char* GetItemAuthor(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 44, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemAuthor(int iItemIndex, const char *lpItemAuthor) {
      return IPWorks_RSS_Set(m_pObj, 44, iItemIndex, (void*)lpItemAuthor, 0);
    }

    inline char* GetItemCategory(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 45, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemCategory(int iItemIndex, const char *lpItemCategory) {
      return IPWorks_RSS_Set(m_pObj, 45, iItemIndex, (void*)lpItemCategory, 0);
    }

    inline char* GetItemCategoryDomain(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 46, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemCategoryDomain(int iItemIndex, const char *lpItemCategoryDomain) {
      return IPWorks_RSS_Set(m_pObj, 46, iItemIndex, (void*)lpItemCategoryDomain, 0);
    }

    inline char* GetItemComments(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 47, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemComments(int iItemIndex, const char *lpItemComments) {
      return IPWorks_RSS_Set(m_pObj, 47, iItemIndex, (void*)lpItemComments, 0);
    }

    inline char* GetItemDescription(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 48, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemDescription(int iItemIndex, const char *lpItemDescription) {
      return IPWorks_RSS_Set(m_pObj, 48, iItemIndex, (void*)lpItemDescription, 0);
    }

    inline char* GetItemEnclosureLength(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 49, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemEnclosureLength(int iItemIndex, const char *lpItemEnclosureLength) {
      return IPWorks_RSS_Set(m_pObj, 49, iItemIndex, (void*)lpItemEnclosureLength, 0);
    }

    inline char* GetItemEnclosureType(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 50, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemEnclosureType(int iItemIndex, const char *lpItemEnclosureType) {
      return IPWorks_RSS_Set(m_pObj, 50, iItemIndex, (void*)lpItemEnclosureType, 0);
    }

    inline char* GetItemEnclosureUrl(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 51, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemEnclosureUrl(int iItemIndex, const char *lpItemEnclosureUrl) {
      return IPWorks_RSS_Set(m_pObj, 51, iItemIndex, (void*)lpItemEnclosureUrl, 0);
    }

    inline char* GetItemGuid(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 52, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemGuid(int iItemIndex, const char *lpItemGuid) {
      return IPWorks_RSS_Set(m_pObj, 52, iItemIndex, (void*)lpItemGuid, 0);
    }

    inline int GetItemGuidIsPermaLink(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 53, iItemIndex, 0);
      return (int)(long)val;
    }
    inline int SetItemGuidIsPermaLink(int iItemIndex, int bItemGuidIsPermaLink) {
      void* val = (void*)IPW64CAST(bItemGuidIsPermaLink);
      return IPWorks_RSS_Set(m_pObj, 53, iItemIndex, val, 0);
    }
    inline char* GetItemXML(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 54, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemXML(int iItemIndex, const char *lpItemXML) {
      return IPWorks_RSS_Set(m_pObj, 54, iItemIndex, (void*)lpItemXML, 0);
    }

    inline char* GetItemLink(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 55, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemLink(int iItemIndex, const char *lpItemLink) {
      return IPWorks_RSS_Set(m_pObj, 55, iItemIndex, (void*)lpItemLink, 0);
    }

    inline char* GetItemPubDate(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 56, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemPubDate(int iItemIndex, const char *lpItemPubDate) {
      return IPWorks_RSS_Set(m_pObj, 56, iItemIndex, (void*)lpItemPubDate, 0);
    }

    inline char* GetItemSource(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 57, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemSource(int iItemIndex, const char *lpItemSource) {
      return IPWorks_RSS_Set(m_pObj, 57, iItemIndex, (void*)lpItemSource, 0);
    }

    inline char* GetItemSourceURL(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 58, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemSourceURL(int iItemIndex, const char *lpItemSourceURL) {
      return IPWorks_RSS_Set(m_pObj, 58, iItemIndex, (void*)lpItemSourceURL, 0);
    }

    inline char* GetItemTitle(int iItemIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 59, iItemIndex, 0);
      return (char*)val;
    }

    inline int SetItemTitle(int iItemIndex, const char *lpItemTitle) {
      return IPWorks_RSS_Set(m_pObj, 59, iItemIndex, (void*)lpItemTitle, 0);
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_RSS_Get(m_pObj, 60, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_RSS_Set(m_pObj, 60, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_RSS_Get(m_pObj, 61, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_RSS_Set(m_pObj, 61, 0, (void*)lpLocalHost, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_RSS_Get(m_pObj, 62, 0, 0);
      return (int)(long)val;
    }
    inline int SetNamespaceCount(int iNamespaceCount) {
      void* val = (void*)IPW64CAST(iNamespaceCount);
      return IPWorks_RSS_Set(m_pObj, 62, 0, val, 0);
    }
    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 63, iNamespaceIndex, 0);
      return (char*)val;
    }

    inline int SetNamespacePrefix(int iNamespaceIndex, const char *lpNamespacePrefix) {
      return IPWorks_RSS_Set(m_pObj, 63, iNamespaceIndex, (void*)lpNamespacePrefix, 0);
    }

    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 64, iNamespaceIndex, 0);
      return (char*)val;
    }

    inline int SetNamespaceURI(int iNamespaceIndex, const char *lpNamespaceURI) {
      return IPWorks_RSS_Set(m_pObj, 64, iNamespaceIndex, (void*)lpNamespaceURI, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_RSS_Get(m_pObj, 65, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_RSS_Set(m_pObj, 65, 0, (void*)lpOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_RSS_Get(m_pObj, 66, 0, 0);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 67, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_RSS_Get(m_pObj, 68, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_RSS_Get(m_pObj, 69, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_RSS_Set(m_pObj, 69, 0, (void*)lpPassword, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_RSS_Get(m_pObj, 70, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_RSS_Set(m_pObj, 70, 0, val, 0);
    }
    inline int GetProxyAutoDetect() {
      void* val = IPWorks_RSS_Get(m_pObj, 71, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_RSS_Set(m_pObj, 71, 0, val, 0);
    }
    inline char* GetProxyPassword() {
      void* val = IPWorks_RSS_Get(m_pObj, 72, 0, 0);
      return (char*)val;
    }

    inline int SetProxyPassword(const char *lpProxyPassword) {
      return IPWorks_RSS_Set(m_pObj, 72, 0, (void*)lpProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_RSS_Get(m_pObj, 73, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyPort(int lProxyPort) {
      void* val = (void*)IPW64CAST(lProxyPort);
      return IPWorks_RSS_Set(m_pObj, 73, 0, val, 0);
    }
    inline char* GetProxyServer() {
      void* val = IPWorks_RSS_Get(m_pObj, 74, 0, 0);
      return (char*)val;
    }

    inline int SetProxyServer(const char *lpProxyServer) {
      return IPWorks_RSS_Set(m_pObj, 74, 0, (void*)lpProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_RSS_Get(m_pObj, 75, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_RSS_Set(m_pObj, 75, 0, val, 0);
    }
    inline char* GetProxyUser() {
      void* val = IPWorks_RSS_Get(m_pObj, 76, 0, 0);
      return (char*)val;
    }

    inline int SetProxyUser(const char *lpProxyUser) {
      return IPWorks_RSS_Set(m_pObj, 76, 0, (void*)lpProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_RSS_Get(m_pObj, 77, 0, 0);
      return (char*)val;
    }

    inline int SetReferer(const char *lpReferer) {
      return IPWorks_RSS_Set(m_pObj, 77, 0, (void*)lpReferer, 0);
    }

    inline char* GetRSSData() {
      void* val = IPWorks_RSS_Get(m_pObj, 78, 0, 0);
      return (char*)val;
    }

    inline int SetRSSData(const char *lpRSSData) {
      return IPWorks_RSS_Set(m_pObj, 78, 0, (void*)lpRSSData, 0);
    }

    inline int GetRSSVersion() {
      void* val = IPWorks_RSS_Get(m_pObj, 79, 0, 0);
      return (int)(long)val;
    }
    inline int SetRSSVersion(int iRSSVersion) {
      void* val = (void*)IPW64CAST(iRSSVersion);
      return IPWorks_RSS_Set(m_pObj, 79, 0, val, 0);
    }
    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_RSS_Get(m_pObj, 80, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_RSS_Set(m_pObj, 80, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_RSS_Get(m_pObj, 81, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_RSS_Set(m_pObj, 81, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_RSS_Get(m_pObj, 82, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_RSS_Set(m_pObj, 82, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_RSS_Get(m_pObj, 83, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_RSS_Set(m_pObj, 83, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_RSS_Get(m_pObj, 84, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_RSS_Set(m_pObj, 84, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_RSS_Get(m_pObj, 85, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_RSS_Set(m_pObj, 85, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_RSS_Get(m_pObj, 86, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline int GetTimeout() {
      void* val = IPWorks_RSS_Get(m_pObj, 87, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_RSS_Set(m_pObj, 87, 0, val, 0);
    }
    inline int GetTransferredData(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_RSS_Get(m_pObj, 88, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }


    inline ns_int64 GetTransferredDataLimit() {
      ns_int64 *pval = (ns_int64*)IPWorks_RSS_Get(m_pObj, 89, 0, 0);
      return *pval;
    }

    inline int SetTransferredDataLimit(ns_int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_RSS_Set(m_pObj, 89, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_RSS_Get(m_pObj, 90, 0, 0);
      return (char*)val;
    }


    inline char* GetUser() {
      void* val = IPWorks_RSS_Get(m_pObj, 91, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_RSS_Set(m_pObj, 91, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 2, 2, param, cbparam);
      
      
    }
    inline int AddItem(const char* lpszTitle, const char* lpszDescription, const char* lpszLink) {
      void *param[3+1] = {(void*)IPW64CAST(lpszTitle), (void*)IPW64CAST(lpszDescription), (void*)IPW64CAST(lpszLink), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 3, 3, param, cbparam);
      
      
    }
    inline int AddNamespace(const char* lpszPrefix, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPrefix), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 4, 2, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 5, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int GetFeed(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 7, 1, param, cbparam);
      
      
    }
    inline char* GetProperty(const char* lpszPropertyName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPropertyName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 8, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int GetURL(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 9, 1, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline char* OPMLAttr(const char* lpszAttrName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 11, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Put(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 12, 1, param, cbparam);
      
      
    }
    inline int ReadFile(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 13, 1, param, cbparam);
      
      
    }
    inline int ReadOPML(const char* lpszOPMLFile) {
      void *param[1+1] = {(void*)IPW64CAST(lpszOPMLFile), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 14, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 15, 0, param, cbparam);
      
      
    }
    inline int SetProperty(const char* lpszPropertyName, const char* lpszPropertyValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPropertyName), (void*)IPW64CAST(lpszPropertyValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 16, 2, param, cbparam);
      
      
    }
    inline int WriteFile(const char* lpszFilename) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFilename), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 17, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RSSConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RSSConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RSSDisconnectedEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} RSSEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} RSSErrorEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} RSSHeaderEventParamsW;

typedef struct {
  int LogLevel;
  LPWSTR Message;
  LPWSTR LogType;
  int reserved;
} RSSLogEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} RSSOPMLHeaderEventParamsW;

typedef struct {
  int Level;
  LPWSTR Text;
  LPWSTR TypeName;
  LPWSTR Title;
  LPWSTR URL;
  LPWSTR XMLURL;
  LPWSTR HTMLURL;
  LPWSTR Created;
  LPWSTR Description;
  LPWSTR OtherAttrs;
  int reserved;
} RSSOPMLOutlineEventParamsW;

typedef struct {
  LPWSTR Location;
  int Accept;
  int reserved;
} RSSRedirectEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR Value;
  LPWSTR Expires;
  LPWSTR Domain;
  LPWSTR Path;
  int Secure;
  int reserved;
} RSSSetCookieEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} RSSSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} RSSSSLStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} RSSStartTransferEventParamsW;

typedef struct {
  LPWSTR HTTPVersion;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RSSStatusEventParamsW;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int lenText;
  int reserved;
} RSSTransferEventParamsW;



class RSSW : public RSS {

  public: //properties
  
    inline LPWSTR GetAccept() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetAccept(LPCWSTR lpAccept) {
      return IPWorks_RSS_Set(m_pObj, 10000+1, 0, (void*)lpAccept, 0);
    }

    inline LPWSTR GetAuthorization() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetAuthorization(LPCWSTR lpAuthorization) {
      return IPWorks_RSS_Set(m_pObj, 10000+2, 0, (void*)lpAuthorization, 0);
    }



    inline LPWSTR GetChannelCategory() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetChannelCategory(LPCWSTR lpChannelCategory) {
      return IPWorks_RSS_Set(m_pObj, 10000+4, 0, (void*)lpChannelCategory, 0);
    }

    inline LPWSTR GetChannelCategoryDomain() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetChannelCategoryDomain(LPCWSTR lpChannelCategoryDomain) {
      return IPWorks_RSS_Set(m_pObj, 10000+5, 0, (void*)lpChannelCategoryDomain, 0);
    }

    inline LPWSTR GetChannelCopyright() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetChannelCopyright(LPCWSTR lpChannelCopyright) {
      return IPWorks_RSS_Set(m_pObj, 10000+6, 0, (void*)lpChannelCopyright, 0);
    }

    inline LPWSTR GetChannelDescription() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetChannelDescription(LPCWSTR lpChannelDescription) {
      return IPWorks_RSS_Set(m_pObj, 10000+7, 0, (void*)lpChannelDescription, 0);
    }

    inline LPWSTR GetChannelDocs() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetChannelDocs(LPCWSTR lpChannelDocs) {
      return IPWorks_RSS_Set(m_pObj, 10000+8, 0, (void*)lpChannelDocs, 0);
    }

    inline LPWSTR GetChannelGenerator() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetChannelGenerator(LPCWSTR lpChannelGenerator) {
      return IPWorks_RSS_Set(m_pObj, 10000+9, 0, (void*)lpChannelGenerator, 0);
    }

    inline LPWSTR GetChannelImageDescription() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+10, 0, 0);
    }

    inline int SetChannelImageDescription(LPCWSTR lpChannelImageDescription) {
      return IPWorks_RSS_Set(m_pObj, 10000+10, 0, (void*)lpChannelImageDescription, 0);
    }

    inline LPWSTR GetChannelImageHeight() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetChannelImageHeight(LPCWSTR lpChannelImageHeight) {
      return IPWorks_RSS_Set(m_pObj, 10000+11, 0, (void*)lpChannelImageHeight, 0);
    }

    inline LPWSTR GetChannelImageLink() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetChannelImageLink(LPCWSTR lpChannelImageLink) {
      return IPWorks_RSS_Set(m_pObj, 10000+12, 0, (void*)lpChannelImageLink, 0);
    }

    inline LPWSTR GetChannelImageTitle() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetChannelImageTitle(LPCWSTR lpChannelImageTitle) {
      return IPWorks_RSS_Set(m_pObj, 10000+13, 0, (void*)lpChannelImageTitle, 0);
    }

    inline LPWSTR GetChannelImageUrl() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetChannelImageUrl(LPCWSTR lpChannelImageUrl) {
      return IPWorks_RSS_Set(m_pObj, 10000+14, 0, (void*)lpChannelImageUrl, 0);
    }

    inline LPWSTR GetChannelImageWidth() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetChannelImageWidth(LPCWSTR lpChannelImageWidth) {
      return IPWorks_RSS_Set(m_pObj, 10000+15, 0, (void*)lpChannelImageWidth, 0);
    }

    inline LPWSTR GetChannelLanguage() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetChannelLanguage(LPCWSTR lpChannelLanguage) {
      return IPWorks_RSS_Set(m_pObj, 10000+16, 0, (void*)lpChannelLanguage, 0);
    }

    inline LPWSTR GetChannelLastBuildDate() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetChannelLastBuildDate(LPCWSTR lpChannelLastBuildDate) {
      return IPWorks_RSS_Set(m_pObj, 10000+17, 0, (void*)lpChannelLastBuildDate, 0);
    }

    inline LPWSTR GetChannelLink() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetChannelLink(LPCWSTR lpChannelLink) {
      return IPWorks_RSS_Set(m_pObj, 10000+18, 0, (void*)lpChannelLink, 0);
    }

    inline LPWSTR GetChannelManagingEditor() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetChannelManagingEditor(LPCWSTR lpChannelManagingEditor) {
      return IPWorks_RSS_Set(m_pObj, 10000+19, 0, (void*)lpChannelManagingEditor, 0);
    }

    inline LPWSTR GetChannelPubDate() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetChannelPubDate(LPCWSTR lpChannelPubDate) {
      return IPWorks_RSS_Set(m_pObj, 10000+20, 0, (void*)lpChannelPubDate, 0);
    }

    inline LPWSTR GetChannelSkipDays() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+21, 0, 0);
    }

    inline int SetChannelSkipDays(LPCWSTR lpChannelSkipDays) {
      return IPWorks_RSS_Set(m_pObj, 10000+21, 0, (void*)lpChannelSkipDays, 0);
    }

    inline LPWSTR GetChannelSkipHours() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetChannelSkipHours(LPCWSTR lpChannelSkipHours) {
      return IPWorks_RSS_Set(m_pObj, 10000+22, 0, (void*)lpChannelSkipHours, 0);
    }

    inline LPWSTR GetChannelTitle() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+23, 0, 0);
    }

    inline int SetChannelTitle(LPCWSTR lpChannelTitle) {
      return IPWorks_RSS_Set(m_pObj, 10000+23, 0, (void*)lpChannelTitle, 0);
    }

    inline LPWSTR GetChannelTtl() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetChannelTtl(LPCWSTR lpChannelTtl) {
      return IPWorks_RSS_Set(m_pObj, 10000+24, 0, (void*)lpChannelTtl, 0);
    }

    inline LPWSTR GetChannelWebMaster() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+25, 0, 0);
    }

    inline int SetChannelWebMaster(LPCWSTR lpChannelWebMaster) {
      return IPWorks_RSS_Set(m_pObj, 10000+25, 0, (void*)lpChannelWebMaster, 0);
    }





    inline LPWSTR GetCookieDomain(int iCookieIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+28, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieExpiration(int iCookieIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+29, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieName(int iCookieIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+30, iCookieIndex, 0);
    }

    inline int SetCookieName(int iCookieIndex, LPCWSTR lpCookieName) {
      return IPWorks_RSS_Set(m_pObj, 10000+30, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline LPWSTR GetCookiePath(int iCookieIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+31, iCookieIndex, 0);
    }





    inline LPWSTR GetCookieValue(int iCookieIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+33, iCookieIndex, 0);
    }

    inline int SetCookieValue(int iCookieIndex, LPCWSTR lpCookieValue) {
      return IPWorks_RSS_Set(m_pObj, 10000+33, iCookieIndex, (void*)lpCookieValue, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+36, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_RSS_Set(m_pObj, 10000+36, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+37, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_RSS_Set(m_pObj, 10000+37, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+39, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_RSS_Set(m_pObj, 10000+39, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetIfModifiedSince() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+42, 0, 0);
    }

    inline int SetIfModifiedSince(LPCWSTR lpIfModifiedSince) {
      return IPWorks_RSS_Set(m_pObj, 10000+42, 0, (void*)lpIfModifiedSince, 0);
    }



    inline LPWSTR GetItemAuthor(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+44, iItemIndex, 0);
    }

    inline int SetItemAuthor(int iItemIndex, LPCWSTR lpItemAuthor) {
      return IPWorks_RSS_Set(m_pObj, 10000+44, iItemIndex, (void*)lpItemAuthor, 0);
    }

    inline LPWSTR GetItemCategory(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+45, iItemIndex, 0);
    }

    inline int SetItemCategory(int iItemIndex, LPCWSTR lpItemCategory) {
      return IPWorks_RSS_Set(m_pObj, 10000+45, iItemIndex, (void*)lpItemCategory, 0);
    }

    inline LPWSTR GetItemCategoryDomain(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+46, iItemIndex, 0);
    }

    inline int SetItemCategoryDomain(int iItemIndex, LPCWSTR lpItemCategoryDomain) {
      return IPWorks_RSS_Set(m_pObj, 10000+46, iItemIndex, (void*)lpItemCategoryDomain, 0);
    }

    inline LPWSTR GetItemComments(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+47, iItemIndex, 0);
    }

    inline int SetItemComments(int iItemIndex, LPCWSTR lpItemComments) {
      return IPWorks_RSS_Set(m_pObj, 10000+47, iItemIndex, (void*)lpItemComments, 0);
    }

    inline LPWSTR GetItemDescription(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+48, iItemIndex, 0);
    }

    inline int SetItemDescription(int iItemIndex, LPCWSTR lpItemDescription) {
      return IPWorks_RSS_Set(m_pObj, 10000+48, iItemIndex, (void*)lpItemDescription, 0);
    }

    inline LPWSTR GetItemEnclosureLength(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+49, iItemIndex, 0);
    }

    inline int SetItemEnclosureLength(int iItemIndex, LPCWSTR lpItemEnclosureLength) {
      return IPWorks_RSS_Set(m_pObj, 10000+49, iItemIndex, (void*)lpItemEnclosureLength, 0);
    }

    inline LPWSTR GetItemEnclosureType(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+50, iItemIndex, 0);
    }

    inline int SetItemEnclosureType(int iItemIndex, LPCWSTR lpItemEnclosureType) {
      return IPWorks_RSS_Set(m_pObj, 10000+50, iItemIndex, (void*)lpItemEnclosureType, 0);
    }

    inline LPWSTR GetItemEnclosureUrl(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+51, iItemIndex, 0);
    }

    inline int SetItemEnclosureUrl(int iItemIndex, LPCWSTR lpItemEnclosureUrl) {
      return IPWorks_RSS_Set(m_pObj, 10000+51, iItemIndex, (void*)lpItemEnclosureUrl, 0);
    }

    inline LPWSTR GetItemGuid(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+52, iItemIndex, 0);
    }

    inline int SetItemGuid(int iItemIndex, LPCWSTR lpItemGuid) {
      return IPWorks_RSS_Set(m_pObj, 10000+52, iItemIndex, (void*)lpItemGuid, 0);
    }



    inline LPWSTR GetItemXML(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+54, iItemIndex, 0);
    }

    inline int SetItemXML(int iItemIndex, LPCWSTR lpItemXML) {
      return IPWorks_RSS_Set(m_pObj, 10000+54, iItemIndex, (void*)lpItemXML, 0);
    }

    inline LPWSTR GetItemLink(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+55, iItemIndex, 0);
    }

    inline int SetItemLink(int iItemIndex, LPCWSTR lpItemLink) {
      return IPWorks_RSS_Set(m_pObj, 10000+55, iItemIndex, (void*)lpItemLink, 0);
    }

    inline LPWSTR GetItemPubDate(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+56, iItemIndex, 0);
    }

    inline int SetItemPubDate(int iItemIndex, LPCWSTR lpItemPubDate) {
      return IPWorks_RSS_Set(m_pObj, 10000+56, iItemIndex, (void*)lpItemPubDate, 0);
    }

    inline LPWSTR GetItemSource(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+57, iItemIndex, 0);
    }

    inline int SetItemSource(int iItemIndex, LPCWSTR lpItemSource) {
      return IPWorks_RSS_Set(m_pObj, 10000+57, iItemIndex, (void*)lpItemSource, 0);
    }

    inline LPWSTR GetItemSourceURL(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+58, iItemIndex, 0);
    }

    inline int SetItemSourceURL(int iItemIndex, LPCWSTR lpItemSourceURL) {
      return IPWorks_RSS_Set(m_pObj, 10000+58, iItemIndex, (void*)lpItemSourceURL, 0);
    }

    inline LPWSTR GetItemTitle(int iItemIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+59, iItemIndex, 0);
    }

    inline int SetItemTitle(int iItemIndex, LPCWSTR lpItemTitle) {
      return IPWorks_RSS_Set(m_pObj, 10000+59, iItemIndex, (void*)lpItemTitle, 0);
    }

    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+10000+60, 0, 0);
    }

    inline int SetLocalFile(LPCWSTR lpLocalFile) {
      return IPWorks_RSS_Set(m_pObj, 10000+10000+60, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+61, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_RSS_Set(m_pObj, 10000+61, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetNamespacePrefix(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+63, iNamespaceIndex, 0);
    }

    inline int SetNamespacePrefix(int iNamespaceIndex, LPCWSTR lpNamespacePrefix) {
      return IPWorks_RSS_Set(m_pObj, 10000+63, iNamespaceIndex, (void*)lpNamespacePrefix, 0);
    }

    inline LPWSTR GetNamespaceURI(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+64, iNamespaceIndex, 0);
    }

    inline int SetNamespaceURI(int iNamespaceIndex, LPCWSTR lpNamespaceURI) {
      return IPWorks_RSS_Set(m_pObj, 10000+64, iNamespaceIndex, (void*)lpNamespaceURI, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+65, 0, 0);
    }

    inline int SetOtherHeaders(LPCWSTR lpOtherHeaders) {
      return IPWorks_RSS_Set(m_pObj, 10000+65, 0, (void*)lpOtherHeaders, 0);
    }



    inline LPWSTR GetParsedHeaderField(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+67, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetParsedHeaderValue(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+68, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+69, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_RSS_Set(m_pObj, 10000+69, 0, (void*)lpPassword, 0);
    }





    inline LPWSTR GetProxyPassword() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+72, 0, 0);
    }

    inline int SetProxyPassword(LPCWSTR lpProxyPassword) {
      return IPWorks_RSS_Set(m_pObj, 10000+72, 0, (void*)lpProxyPassword, 0);
    }



    inline LPWSTR GetProxyServer() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+74, 0, 0);
    }

    inline int SetProxyServer(LPCWSTR lpProxyServer) {
      return IPWorks_RSS_Set(m_pObj, 10000+74, 0, (void*)lpProxyServer, 0);
    }



    inline LPWSTR GetProxyUser() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+76, 0, 0);
    }

    inline int SetProxyUser(LPCWSTR lpProxyUser) {
      return IPWorks_RSS_Set(m_pObj, 10000+76, 0, (void*)lpProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+77, 0, 0);
    }

    inline int SetReferer(LPCWSTR lpReferer) {
      return IPWorks_RSS_Set(m_pObj, 10000+77, 0, (void*)lpReferer, 0);
    }

    inline LPWSTR GetRSSData() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+78, 0, 0);
    }

    inline int SetRSSData(LPCWSTR lpRSSData) {
      return IPWorks_RSS_Set(m_pObj, 10000+78, 0, (void*)lpRSSData, 0);
    }



    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+80, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_RSS_Set(m_pObj, 10000+80, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_RSS_Get(m_pObj, 80, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_RSS_Set(m_pObj, 80, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+81, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_RSS_Set(m_pObj, 10000+81, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_RSS_Get(m_pObj, 81, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_RSS_Set(m_pObj, 81, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+82, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_RSS_Set(m_pObj, 10000+82, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_RSS_Get(m_pObj, 82, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_RSS_Set(m_pObj, 82, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+83, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_RSS_Set(m_pObj, 10000+83, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+85, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_RSS_Set(m_pObj, 10000+85, 0, (void*)lpSSLCertSubject, 0);
    }

    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+86, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_RSS_Get(m_pObj, 86, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }



    inline LPWSTR GetTransferredData() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+88, 0, 0);
    }


    inline int GetTransferredDataB(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_RSS_Get(m_pObj, 88, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }



    inline LPWSTR GetTransferredHeaders() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+90, 0, 0);
    }



    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_RSS_Get(m_pObj, 10000+91, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_RSS_Set(m_pObj, 10000+91, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnected(RSSConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(RSSConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(RSSDisconnectedEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(RSSEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(RSSErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(RSSHeaderEventParamsW *e) {return 0;}
    virtual int FireLog(RSSLogEventParamsW *e) {return 0;}
    virtual int FireOPMLHeader(RSSOPMLHeaderEventParamsW *e) {return 0;}
    virtual int FireOPMLOutline(RSSOPMLOutlineEventParamsW *e) {return 0;}
    virtual int FireRedirect(RSSRedirectEventParamsW *e) {return 0;}
    virtual int FireSetCookie(RSSSetCookieEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(RSSSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(RSSSSLStatusEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(RSSStartTransferEventParamsW *e) {return 0;}
    virtual int FireStatus(RSSStatusEventParamsW *e) {return 0;}
    virtual int FireTransfer(RSSTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int RSSEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            RSSConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            RSSConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            RSSDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            RSSEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 5: {
            RSSErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            RSSHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 7: {
            RSSLogEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireLog(&e);
            break;
         }
         case 8: {
            RSSOPMLHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireOPMLHeader(&e);
            break;
         }
         case 9: {
            RSSOPMLOutlineEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]), (LPWSTR)IPW64CAST(param[6]), (LPWSTR)IPW64CAST(param[7]), (LPWSTR)IPW64CAST(param[8]), (LPWSTR)IPW64CAST(param[9]),  0};
            ret_code = FireOPMLOutline(&e);
            break;
         }
         case 10: {
            RSSRedirectEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = FireRedirect(&e);
            param[1] = (void*)(e.Accept);
            break;
         }
         case 11: {
            RSSSetCookieEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = FireSetCookie(&e);
            break;
         }
         case 12: {
            RSSSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 13: {
            RSSSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }
         case 14: {
            RSSStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 15: {
            RSSStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireStatus(&e);
            break;
         }
         case 16: {
            RSSTransferEventParamsW e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(RSSConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(RSSConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(RSSDisconnectedEventParams *e) {return -10000;}
    virtual int FireEndTransfer(RSSEndTransferEventParams *e) {return -10000;}
    virtual int FireError(RSSErrorEventParams *e) {return -10000;}
    virtual int FireHeader(RSSHeaderEventParams *e) {return -10000;}
    virtual int FireLog(RSSLogEventParams *e) {return -10000;}
    virtual int FireOPMLHeader(RSSOPMLHeaderEventParams *e) {return -10000;}
    virtual int FireOPMLOutline(RSSOPMLOutlineEventParams *e) {return -10000;}
    virtual int FireRedirect(RSSRedirectEventParams *e) {return -10000;}
    virtual int FireSetCookie(RSSSetCookieEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(RSSSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(RSSSSLStatusEventParams *e) {return -10000;}
    virtual int FireStartTransfer(RSSStartTransferEventParams *e) {return -10000;}
    virtual int FireStatus(RSSStatusEventParams *e) {return -10000;}
    virtual int FireTransfer(RSSTransferEventParams *e) {return -10000;}

  public: //methods

    inline int AddCookie(LPWSTR lpszCookieName, LPWSTR lpszCookieValue) {
      void *param[2+1] = {(void*)lpszCookieName, (void*)lpszCookieValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 10000+2, 2, param, cbparam);
      
    }
    inline int AddItem(LPWSTR lpszTitle, LPWSTR lpszDescription, LPWSTR lpszLink) {
      void *param[3+1] = {(void*)lpszTitle, (void*)lpszDescription, (void*)lpszLink, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 10000+3, 3, param, cbparam);
      
    }
    inline int AddNamespace(LPWSTR lpszPrefix, LPWSTR lpszNamespaceURI) {
      void *param[2+1] = {(void*)lpszPrefix, (void*)lpszNamespaceURI, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 10000+4, 2, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 10000+5, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int GetFeed(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 10000+7, 1, param, cbparam);
      
    }
    inline LPWSTR GetProperty(LPWSTR lpszPropertyName) {
      void *param[1+1] = {(void*)lpszPropertyName, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 10000+8, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int GetURL(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 10000+9, 1, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline LPWSTR OPMLAttr(LPWSTR lpszAttrName) {
      void *param[1+1] = {(void*)lpszAttrName, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_RSS_Do(m_pObj, 10000+11, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Put(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 10000+12, 1, param, cbparam);
      
    }
    inline int ReadFile(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 10000+13, 1, param, cbparam);
      
    }
    inline int ReadOPML(LPWSTR lpszOPMLFile) {
      void *param[1+1] = {(void*)lpszOPMLFile, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 10000+14, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_RSS_Do(m_pObj, 10000+15, 0, param, cbparam);
      
    }
    inline int SetProperty(LPWSTR lpszPropertyName, LPWSTR lpszPropertyValue) {
      void *param[2+1] = {(void*)lpszPropertyName, (void*)lpszPropertyValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_RSS_Do(m_pObj, 10000+16, 2, param, cbparam);
      
    }
    inline int WriteFile(LPWSTR lpszFilename) {
      void *param[1+1] = {(void*)lpszFilename, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_RSS_Do(m_pObj, 10000+17, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_RSS_H_




