/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_WebDAV_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_WebDAV_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_WebDAV_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_StaticDestroy();

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
} WebDAVConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} WebDAVConnectionStatusEventParams;

typedef struct {
  const char *ResourceURI;
  const char *DisplayName;
  const char *ContentLanguage;
  const char *ContentLength;
  const char *ContentType;
  const char *LastModified;
  int reserved;
} WebDAVDirListEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} WebDAVDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} WebDAVEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} WebDAVErrorEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} WebDAVHeaderEventParams;

typedef struct {
  int LogLevel;
  const char *Message;
  const char *LogType;
  int reserved;
} WebDAVLogEventParams;

typedef struct {
  const char *Location;
  int Accept;
  int reserved;
} WebDAVRedirectEventParams;

typedef struct {
  const char *ResourceURI;
  const char *ResourceProperties;
  int reserved;
} WebDAVResourcePropertiesEventParams;

typedef struct {
  const char *Name;
  const char *Value;
  const char *Expires;
  const char *Domain;
  const char *Path;
  int Secure;
  int reserved;
} WebDAVSetCookieEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} WebDAVSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} WebDAVSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} WebDAVStartTransferEventParams;

typedef struct {
  const char *HTTPVersion;
  int StatusCode;
  const char *Description;
  int reserved;
} WebDAVStatusEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int reserved;
} WebDAVTransferEventParams;


class WebDAV {
  public: // Events
    virtual int FireConnected(WebDAVConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(WebDAVConnectionStatusEventParams *e) {return 0;}
    virtual int FireDirList(WebDAVDirListEventParams *e) {return 0;}
    virtual int FireDisconnected(WebDAVDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(WebDAVEndTransferEventParams *e) {return 0;}
    virtual int FireError(WebDAVErrorEventParams *e) {return 0;}
    virtual int FireHeader(WebDAVHeaderEventParams *e) {return 0;}
    virtual int FireLog(WebDAVLogEventParams *e) {return 0;}
    virtual int FireRedirect(WebDAVRedirectEventParams *e) {return 0;}
    virtual int FireResourceProperties(WebDAVResourcePropertiesEventParams *e) {return 0;}
    virtual int FireSetCookie(WebDAVSetCookieEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(WebDAVSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(WebDAVSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(WebDAVStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(WebDAVStatusEventParams *e) {return 0;}
    virtual int FireTransfer(WebDAVTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL WebDAVEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          WebDAVConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((WebDAV*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          WebDAVConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((WebDAV*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          WebDAVDirListEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), 0};
          ret_code = ((WebDAV*)lpObj)->FireDirList(&e);
          break;
        }
        case 4: {
          WebDAVDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((WebDAV*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 5: {
          WebDAVEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((WebDAV*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 6: {
          WebDAVErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((WebDAV*)lpObj)->FireError(&e);
          break;
        }
        case 7: {
          WebDAVHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((WebDAV*)lpObj)->FireHeader(&e);
          break;
        }
        case 8: {
          WebDAVLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((WebDAV*)lpObj)->FireLog(&e);
          break;
        }
        case 9: {
          WebDAVRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), 0};
          ret_code = ((WebDAV*)lpObj)->FireRedirect(&e);
          param[1] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 10: {
          WebDAVResourcePropertiesEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((WebDAV*)lpObj)->FireResourceProperties(&e);
          break;
        }
        case 11: {
          WebDAVSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), 0};
          ret_code = ((WebDAV*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 12: {
          WebDAVSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((WebDAV*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 13: {
          WebDAVSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((WebDAV*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 14: {
          WebDAVStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((WebDAV*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 15: {
          WebDAVStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((WebDAV*)lpObj)->FireStatus(&e);
          break;
        }
        case 16: {
          WebDAVTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), 0};
          ret_code = ((WebDAV*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    WebDAV(char *lpOemKey = (char*)IPWORKS_OEMKEY_61) {
      m_pObj = IPWorks_WebDAV_Create(WebDAVEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~WebDAV() {
      IPWorks_WebDAV_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_WebDAV_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_WebDAV_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_WebDAV_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_WebDAV_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_WebDAV_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetAccept() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAccept(const char* lpszAccept) {
      return IPWorks_WebDAV_Set(m_pObj, 1, 0, (void*)lpszAccept, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthorization(const char* lpszAuthorization) {
      return IPWorks_WebDAV_Set(m_pObj, 2, 0, (void*)lpszAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_WebDAV_Set(m_pObj, 3, 0, val, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_WebDAV_Set(m_pObj, 4, 0, val, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 5, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_WebDAV_Set(m_pObj, 5, 0, val, 0);
    }

    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 6, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 7, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 8, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieName(int iCookieIndex, const char* lpszCookieName) {
      return IPWorks_WebDAV_Set(m_pObj, 8, iCookieIndex, (void*)lpszCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 9, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 10, iCookieIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 11, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieValue(int iCookieIndex, const char* lpszCookieValue) {
      return IPWorks_WebDAV_Set(m_pObj, 11, iCookieIndex, (void*)lpszCookieValue, 0);
    }

    inline int GetDepth() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 12, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetDepth(int iDepth) {
      void* val = (void*)IPW64CAST(iDepth);
      return IPWorks_WebDAV_Set(m_pObj, 12, 0, val, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 13, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_WebDAV_Set(m_pObj, 13, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 14, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_WebDAV_Set(m_pObj, 14, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_WebDAV_Set(m_pObj, 15, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 16, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 17, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_WebDAV_Set(m_pObj, 17, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_WebDAV_Set(m_pObj, 18, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 19, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_WebDAV_Set(m_pObj, 19, 0, val, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 20, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_WebDAV_Set(m_pObj, 21, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_WebDAV_Set(m_pObj, 21+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 22, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_WebDAV_Set(m_pObj, 22, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetLockOwner() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 23, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLockOwner(const char* lpszLockOwner) {
      return IPWorks_WebDAV_Set(m_pObj, 23, 0, (void*)lpszLockOwner, 0);
    }

    inline char* GetLockScope() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 24, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLockScope(const char* lpszLockScope) {
      return IPWorks_WebDAV_Set(m_pObj, 24, 0, (void*)lpszLockScope, 0);
    }

    inline int GetLockTimeout() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 25, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetLockTimeout(int iLockTimeout) {
      void* val = (void*)IPW64CAST(iLockTimeout);
      return IPWorks_WebDAV_Set(m_pObj, 25, 0, val, 0);
    }

    inline char* GetLockTokens() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLockTokens(const char* lpszLockTokens) {
      return IPWorks_WebDAV_Set(m_pObj, 26, 0, (void*)lpszLockTokens, 0);
    }

    inline char* GetLockType() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 27, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLockType(const char* lpszLockType) {
      return IPWorks_WebDAV_Set(m_pObj, 27, 0, (void*)lpszLockType, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 28, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetNamespaceCount(int iNamespaceCount) {
      void* val = (void*)IPW64CAST(iNamespaceCount);
      return IPWorks_WebDAV_Set(m_pObj, 28, 0, val, 0);
    }

    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 29, iNamespaceIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetNamespacePrefix(int iNamespaceIndex, const char* lpszNamespacePrefix) {
      return IPWorks_WebDAV_Set(m_pObj, 29, iNamespaceIndex, (void*)lpszNamespacePrefix, 0);
    }

    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 30, iNamespaceIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetNamespaceURI(int iNamespaceIndex, const char* lpszNamespaceURI) {
      return IPWorks_WebDAV_Set(m_pObj, 30, iNamespaceIndex, (void*)lpszNamespaceURI, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 31, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherHeaders(const char* lpszOtherHeaders) {
      return IPWorks_WebDAV_Set(m_pObj, 31, 0, (void*)lpszOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 32, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 33, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 34, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 35, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 35, 0, (void*)lpszPassword, 0);
    }

    inline int GetPropertyCount() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 36, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetPropertyCount(int iPropertyCount) {
      void* val = (void*)IPW64CAST(iPropertyCount);
      return IPWorks_WebDAV_Set(m_pObj, 36, 0, val, 0);
    }

    inline char* GetPropertyAttr(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 37, iPropertyIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetPropertyAttr(int iPropertyIndex, const char* lpszPropertyAttr) {
      return IPWorks_WebDAV_Set(m_pObj, 37, iPropertyIndex, (void*)lpszPropertyAttr, 0);
    }

    inline char* GetPropertyName(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 38, iPropertyIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetPropertyName(int iPropertyIndex, const char* lpszPropertyName) {
      return IPWorks_WebDAV_Set(m_pObj, 38, iPropertyIndex, (void*)lpszPropertyName, 0);
    }

    inline char* GetPropertyNamespaceURI(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 39, iPropertyIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetPropertyNamespaceURI(int iPropertyIndex, const char* lpszPropertyNamespaceURI) {
      return IPWorks_WebDAV_Set(m_pObj, 39, iPropertyIndex, (void*)lpszPropertyNamespaceURI, 0);
    }

    inline int GetPropertyOperation(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 40, iPropertyIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetPropertyOperation(int iPropertyIndex, int iPropertyOperation) {
      void* val = (void*)IPW64CAST(iPropertyOperation);
      return IPWorks_WebDAV_Set(m_pObj, 40, iPropertyIndex, val, 0);
    }

    inline char* GetPropertyStatus(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 41, iPropertyIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetPropertyValue(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 42, iPropertyIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetPropertyValue(int iPropertyIndex, const char* lpszPropertyValue) {
      return IPWorks_WebDAV_Set(m_pObj, 42, iPropertyIndex, (void*)lpszPropertyValue, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 43, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_WebDAV_Set(m_pObj, 43, 0, val, 0);
    }

    inline int GetProxyAutoDetect() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 44, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_WebDAV_Set(m_pObj, 44, 0, val, 0);
    }

    inline char* GetProxyPassword() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 45, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyPassword(const char* lpszProxyPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 45, 0, (void*)lpszProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 46, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyPort(int iProxyPort) {
      void* val = (void*)IPW64CAST(iProxyPort);
      return IPWorks_WebDAV_Set(m_pObj, 46, 0, val, 0);
    }

    inline char* GetProxyServer() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 47, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyServer(const char* lpszProxyServer) {
      return IPWorks_WebDAV_Set(m_pObj, 47, 0, (void*)lpszProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 48, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_WebDAV_Set(m_pObj, 48, 0, val, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 49, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyUser(const char* lpszProxyUser) {
      return IPWorks_WebDAV_Set(m_pObj, 49, 0, (void*)lpszProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 50, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReferer(const char* lpszReferer) {
      return IPWorks_WebDAV_Set(m_pObj, 50, 0, (void*)lpszReferer, 0);
    }

    inline int GetResourceCount() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 51, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetResourceContentLanguage(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 52, iResourceIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetResourceContentLength(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 53, iResourceIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetResourceContentType(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 54, iResourceIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetResourceDisplayName(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 55, iResourceIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetResourceLastModified(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 56, iResourceIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetResourceURI(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 57, iResourceIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_WebDAV_Get(m_pObj, 58, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_WebDAV_Set(m_pObj, 58, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_WebDAV_Get(m_pObj, 59, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_WebDAV_Set(m_pObj, 59, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_WebDAV_Get(m_pObj, 60, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_WebDAV_Set(m_pObj, 60, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 61, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_WebDAV_Set(m_pObj, 61, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 62, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_WebDAV_Set(m_pObj, 62, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 63, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_WebDAV_Set(m_pObj, 63, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_WebDAV_Get(m_pObj, 64, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline char* GetStatusLine() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 65, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetTimeout() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 66, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_WebDAV_Set(m_pObj, 66, 0, val, 0);
    }

    inline int GetTransferredData(char* &lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_WebDAV_Get(m_pObj, 67, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline int64 GetTransferredDataLimit() {
      int64 retVal;
      IPWorks_WebDAV_Get(m_pObj, 68, 0, NULL, &retVal);
      return retVal;
    }
    inline int SetTransferredDataLimit(int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_WebDAV_Set(m_pObj, 68, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 69, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetUser() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 70, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_WebDAV_Set(m_pObj, 70, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 2, 2, param, cbparam, NULL);
    }

    inline int AddNamespace(const char* lpszPrefix, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPrefix), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 3, 2, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebDAV_Do(m_pObj, 4, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int CopyResource(const char* lpszSourceResourceURI, const char* lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszSourceResourceURI), (void*)IPW64CAST(lpszDestinationResourceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 5, 2, param, cbparam, NULL);
    }

    inline int DeleteResource(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 6, 1, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int FindProperties(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 8, 1, param, cbparam, NULL);
    }

    inline int FindPropertyNames(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 9, 1, param, cbparam, NULL);
    }

    inline char* GetProperty(const char* lpszPropertyName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPropertyName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebDAV_Do(m_pObj, 10, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int GetResource(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 11, 1, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 12, 0, param, cbparam, NULL);
    }

    inline int ListDirectory(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 13, 1, param, cbparam, NULL);
    }

    inline int LockResource(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 14, 1, param, cbparam, NULL);
    }

    inline int MakeDirectory(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 15, 1, param, cbparam, NULL);
    }

    inline int MoveResource(const char* lpszSourceResourceURI, const char* lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszSourceResourceURI), (void*)IPW64CAST(lpszDestinationResourceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 16, 2, param, cbparam, NULL);
    }

    inline int PatchProperties(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 17, 1, param, cbparam, NULL);
    }

    inline int PostToResource(const char* lpszResourceURI, const char* lpPostData, int lenPostData) {
      void *param[2+1] = {(void*)IPW64CAST(lpszResourceURI), (void*)IPW64CAST(lpPostData), 0};
      int cbparam[2+1] = {0, lenPostData, 0};
      return IPWorks_WebDAV_Do(m_pObj, 18, 2, param, cbparam, NULL);
    }

    inline int PutResource(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 19, 1, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 20, 0, param, cbparam, NULL);
    }

    inline int SetProperty(const char* lpszPropertyName, const char* lpszPropertyValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPropertyName), (void*)IPW64CAST(lpszPropertyValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 22, 2, param, cbparam, NULL);
    }

    inline int UnLockResource(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 24, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_WEBDAV_H_
