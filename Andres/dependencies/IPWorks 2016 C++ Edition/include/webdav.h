/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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


extern "C" void* IPWORKS_CALL IPWorks_WebDAV_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_WebDAV_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_WebDAV_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebDAV_GetLastErrorCode(void *lpObj);
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
  const char* Description;
  int reserved;
} WebDAVConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} WebDAVConnectionStatusEventParams;

typedef struct {
  const char* ResourceURI;
  const char* DisplayName;
  const char* ContentLanguage;
  const char* ContentLength;
  const char* ContentType;
  const char* LastModified;
  int reserved;
} WebDAVDirListEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} WebDAVDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} WebDAVEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} WebDAVErrorEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} WebDAVHeaderEventParams;

typedef struct {
  int LogLevel;
  const char* Message;
  const char* LogType;
  int reserved;
} WebDAVLogEventParams;

typedef struct {
  const char* Location;
  int Accept;
  int reserved;
} WebDAVRedirectEventParams;

typedef struct {
  const char* ResourceURI;
  const char* ResourceProperties;
  int reserved;
} WebDAVResourcePropertiesEventParams;

typedef struct {
  const char* Name;
  const char* Value;
  const char* Expires;
  const char* Domain;
  const char* Path;
  int Secure;
  int reserved;
} WebDAVSetCookieEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} WebDAVSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} WebDAVSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} WebDAVStartTransferEventParams;

typedef struct {
  const char* HTTPVersion;
  int StatusCode;
  const char* Description;
  int reserved;
} WebDAVStatusEventParams;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  const char* Text;
  int lenText;
  int reserved;
} WebDAVTransferEventParams;



class WebDAV {
  
  public: //events
  
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
      if (event_id > 10000) return ((WebDAV*)lpObj)->WebDAVEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            WebDAVConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebDAV*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            WebDAVConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((WebDAV*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            WebDAVDirListEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]),  0};
            ret_code = ((WebDAV*)lpObj)->FireDirList(&e);
            break;
         }
         case 4: {
            WebDAVDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebDAV*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 5: {
            WebDAVEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((WebDAV*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 6: {
            WebDAVErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebDAV*)lpObj)->FireError(&e);
            break;
         }
         case 7: {
            WebDAVHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebDAV*)lpObj)->FireHeader(&e);
            break;
         }
         case 8: {
            WebDAVLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((WebDAV*)lpObj)->FireLog(&e);
            break;
         }
         case 9: {
            WebDAVRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = ((WebDAV*)lpObj)->FireRedirect(&e);
            param[1] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 10: {
            WebDAVResourcePropertiesEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebDAV*)lpObj)->FireResourceProperties(&e);
            break;
         }
         case 11: {
            WebDAVSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = ((WebDAV*)lpObj)->FireSetCookie(&e);
            break;
         }
         case 12: {
            WebDAVSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((WebDAV*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 13: {
            WebDAVSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((WebDAV*)lpObj)->FireSSLStatus(&e);
            break;
         }
         case 14: {
            WebDAVStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((WebDAV*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 15: {
            WebDAVStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((WebDAV*)lpObj)->FireStatus(&e);
            break;
         }
         case 16: {
            WebDAVTransferEventParams e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((WebDAV*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int WebDAVEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    WebDAV(char *lpOemKey = (char*)IPWORKS_OEMKEY_61) {
      m_pObj = IPWorks_WebDAV_Create(WebDAVEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~WebDAV() {
      IPWorks_WebDAV_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_WebDAV_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_WebDAV_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_WebDAV_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_WebDAV_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_WebDAV_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetAccept() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetAccept(const char *lpAccept) {
      return IPWorks_WebDAV_Set(m_pObj, 1, 0, (void*)lpAccept, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorization(const char *lpAuthorization) {
      return IPWorks_WebDAV_Set(m_pObj, 2, 0, (void*)lpAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_WebDAV_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetConnected() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_WebDAV_Set(m_pObj, 4, 0, val, 0);
    }
    inline int GetCookieCount() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_WebDAV_Set(m_pObj, 5, 0, val, 0);
    }
    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 6, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 7, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 8, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieName(int iCookieIndex, const char *lpCookieName) {
      return IPWorks_WebDAV_Set(m_pObj, 8, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 9, iCookieIndex, 0);
      return (char*)val;
    }


    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 10, iCookieIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 11, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieValue(int iCookieIndex, const char *lpCookieValue) {
      return IPWorks_WebDAV_Set(m_pObj, 11, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline int GetDepth() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 12, 0, 0);
      return (int)(long)val;
    }
    inline int SetDepth(int iDepth) {
      void* val = (void*)IPW64CAST(iDepth);
      return IPWorks_WebDAV_Set(m_pObj, 12, 0, val, 0);
    }
    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_WebDAV_Set(m_pObj, 13, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 14, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_WebDAV_Set(m_pObj, 14, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_WebDAV_Set(m_pObj, 15, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 16, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_WebDAV_Set(m_pObj, 17, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_WebDAV_Set(m_pObj, 18, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 19, 0, 0);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_WebDAV_Set(m_pObj, 19, 0, val, 0);
    }
    inline int GetIdle() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 20, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_WebDAV_Set(m_pObj, 21, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_WebDAV_Set(m_pObj, 22, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetLockOwner() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }

    inline int SetLockOwner(const char *lpLockOwner) {
      return IPWorks_WebDAV_Set(m_pObj, 23, 0, (void*)lpLockOwner, 0);
    }

    inline char* GetLockScope() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetLockScope(const char *lpLockScope) {
      return IPWorks_WebDAV_Set(m_pObj, 24, 0, (void*)lpLockScope, 0);
    }

    inline int GetLockTimeout() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 25, 0, 0);
      return (int)(long)val;
    }
    inline int SetLockTimeout(int iLockTimeout) {
      void* val = (void*)IPW64CAST(iLockTimeout);
      return IPWorks_WebDAV_Set(m_pObj, 25, 0, val, 0);
    }
    inline char* GetLockTokens() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }

    inline int SetLockTokens(const char *lpLockTokens) {
      return IPWorks_WebDAV_Set(m_pObj, 26, 0, (void*)lpLockTokens, 0);
    }

    inline char* GetLockType() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 27, 0, 0);
      return (char*)val;
    }

    inline int SetLockType(const char *lpLockType) {
      return IPWorks_WebDAV_Set(m_pObj, 27, 0, (void*)lpLockType, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 28, 0, 0);
      return (int)(long)val;
    }
    inline int SetNamespaceCount(int iNamespaceCount) {
      void* val = (void*)IPW64CAST(iNamespaceCount);
      return IPWorks_WebDAV_Set(m_pObj, 28, 0, val, 0);
    }
    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 29, iNamespaceIndex, 0);
      return (char*)val;
    }

    inline int SetNamespacePrefix(int iNamespaceIndex, const char *lpNamespacePrefix) {
      return IPWorks_WebDAV_Set(m_pObj, 29, iNamespaceIndex, (void*)lpNamespacePrefix, 0);
    }

    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 30, iNamespaceIndex, 0);
      return (char*)val;
    }

    inline int SetNamespaceURI(int iNamespaceIndex, const char *lpNamespaceURI) {
      return IPWorks_WebDAV_Set(m_pObj, 30, iNamespaceIndex, (void*)lpNamespaceURI, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 31, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_WebDAV_Set(m_pObj, 31, 0, (void*)lpOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 32, 0, 0);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 33, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 34, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 35, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 35, 0, (void*)lpPassword, 0);
    }

    inline int GetPropertyCount() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 36, 0, 0);
      return (int)(long)val;
    }
    inline int SetPropertyCount(int iPropertyCount) {
      void* val = (void*)IPW64CAST(iPropertyCount);
      return IPWorks_WebDAV_Set(m_pObj, 36, 0, val, 0);
    }
    inline char* GetPropertyAttr(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 37, iPropertyIndex, 0);
      return (char*)val;
    }

    inline int SetPropertyAttr(int iPropertyIndex, const char *lpPropertyAttr) {
      return IPWorks_WebDAV_Set(m_pObj, 37, iPropertyIndex, (void*)lpPropertyAttr, 0);
    }

    inline char* GetPropertyName(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 38, iPropertyIndex, 0);
      return (char*)val;
    }

    inline int SetPropertyName(int iPropertyIndex, const char *lpPropertyName) {
      return IPWorks_WebDAV_Set(m_pObj, 38, iPropertyIndex, (void*)lpPropertyName, 0);
    }

    inline char* GetPropertyNamespaceURI(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 39, iPropertyIndex, 0);
      return (char*)val;
    }

    inline int SetPropertyNamespaceURI(int iPropertyIndex, const char *lpPropertyNamespaceURI) {
      return IPWorks_WebDAV_Set(m_pObj, 39, iPropertyIndex, (void*)lpPropertyNamespaceURI, 0);
    }

    inline int GetPropertyOperation(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 40, iPropertyIndex, 0);
      return (int)(long)val;
    }
    inline int SetPropertyOperation(int iPropertyIndex, int iPropertyOperation) {
      void* val = (void*)IPW64CAST(iPropertyOperation);
      return IPWorks_WebDAV_Set(m_pObj, 40, iPropertyIndex, val, 0);
    }
    inline char* GetPropertyStatus(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 41, iPropertyIndex, 0);
      return (char*)val;
    }


    inline char* GetPropertyValue(int iPropertyIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 42, iPropertyIndex, 0);
      return (char*)val;
    }

    inline int SetPropertyValue(int iPropertyIndex, const char *lpPropertyValue) {
      return IPWorks_WebDAV_Set(m_pObj, 42, iPropertyIndex, (void*)lpPropertyValue, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 43, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_WebDAV_Set(m_pObj, 43, 0, val, 0);
    }
    inline int GetProxyAutoDetect() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 44, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_WebDAV_Set(m_pObj, 44, 0, val, 0);
    }
    inline char* GetProxyPassword() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 45, 0, 0);
      return (char*)val;
    }

    inline int SetProxyPassword(const char *lpProxyPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 45, 0, (void*)lpProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 46, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyPort(int lProxyPort) {
      void* val = (void*)IPW64CAST(lProxyPort);
      return IPWorks_WebDAV_Set(m_pObj, 46, 0, val, 0);
    }
    inline char* GetProxyServer() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 47, 0, 0);
      return (char*)val;
    }

    inline int SetProxyServer(const char *lpProxyServer) {
      return IPWorks_WebDAV_Set(m_pObj, 47, 0, (void*)lpProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 48, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_WebDAV_Set(m_pObj, 48, 0, val, 0);
    }
    inline char* GetProxyUser() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 49, 0, 0);
      return (char*)val;
    }

    inline int SetProxyUser(const char *lpProxyUser) {
      return IPWorks_WebDAV_Set(m_pObj, 49, 0, (void*)lpProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 50, 0, 0);
      return (char*)val;
    }

    inline int SetReferer(const char *lpReferer) {
      return IPWorks_WebDAV_Set(m_pObj, 50, 0, (void*)lpReferer, 0);
    }

    inline int GetResourceCount() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 51, 0, 0);
      return (int)(long)val;
    }

    inline char* GetResourceContentLanguage(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 52, iResourceIndex, 0);
      return (char*)val;
    }


    inline char* GetResourceContentLength(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 53, iResourceIndex, 0);
      return (char*)val;
    }


    inline char* GetResourceContentType(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 54, iResourceIndex, 0);
      return (char*)val;
    }


    inline char* GetResourceDisplayName(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 55, iResourceIndex, 0);
      return (char*)val;
    }


    inline char* GetResourceLastModified(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 56, iResourceIndex, 0);
      return (char*)val;
    }


    inline char* GetResourceURI(int iResourceIndex) {
      void* val = IPWorks_WebDAV_Get(m_pObj, 57, iResourceIndex, 0);
      return (char*)val;
    }


    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_WebDAV_Get(m_pObj, 58, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_WebDAV_Set(m_pObj, 58, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_WebDAV_Get(m_pObj, 59, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_WebDAV_Set(m_pObj, 59, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_WebDAV_Get(m_pObj, 60, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_WebDAV_Set(m_pObj, 60, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 61, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_WebDAV_Set(m_pObj, 61, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 62, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_WebDAV_Set(m_pObj, 62, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 63, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_WebDAV_Set(m_pObj, 63, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_WebDAV_Get(m_pObj, 64, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline char* GetStatusLine() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 65, 0, 0);
      return (char*)val;
    }


    inline int GetTimeout() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 66, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_WebDAV_Set(m_pObj, 66, 0, val, 0);
    }
    inline int GetTransferredData(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_WebDAV_Get(m_pObj, 67, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }


    inline ns_int64 GetTransferredDataLimit() {
      ns_int64 *pval = (ns_int64*)IPWorks_WebDAV_Get(m_pObj, 68, 0, 0);
      return *pval;
    }

    inline int SetTransferredDataLimit(ns_int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_WebDAV_Set(m_pObj, 68, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 69, 0, 0);
      return (char*)val;
    }


    inline char* GetUser() {
      void* val = IPWorks_WebDAV_Get(m_pObj, 70, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_WebDAV_Set(m_pObj, 70, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 2, 2, param, cbparam);
      
      
    }
    inline int AddNamespace(const char* lpszPrefix, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPrefix), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 3, 2, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebDAV_Do(m_pObj, 4, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int CopyResource(const char* lpszSourceResourceURI, const char* lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszSourceResourceURI), (void*)IPW64CAST(lpszDestinationResourceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 5, 2, param, cbparam);
      
      
    }
    inline int DeleteResource(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 6, 1, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int FindProperties(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 8, 1, param, cbparam);
      
      
    }
    inline int FindPropertyNames(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 9, 1, param, cbparam);
      
      
    }
    inline char* GetProperty(const char* lpszPropertyName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPropertyName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebDAV_Do(m_pObj, 10, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int GetResource(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 11, 1, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }
    inline int ListDirectory(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 13, 1, param, cbparam);
      
      
    }
    inline int LockResource(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 14, 1, param, cbparam);
      
      
    }
    inline int MakeDirectory(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 15, 1, param, cbparam);
      
      
    }
    inline int MoveResource(const char* lpszSourceResourceURI, const char* lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszSourceResourceURI), (void*)IPW64CAST(lpszDestinationResourceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 16, 2, param, cbparam);
      
      
    }
    inline int PatchProperties(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 17, 1, param, cbparam);
      
      
    }
    inline int PostToResource(const char* lpszResourceURI, const char* lpPostData, int lenPostData) {
      void *param[2+1] = {(void*)IPW64CAST(lpszResourceURI), (void*)IPW64CAST(lpPostData), 0};
      int cbparam[2+1] = {0, lenPostData, 0};
      return IPWorks_WebDAV_Do(m_pObj, 18, 2, param, cbparam);
      
      
    }
    inline int PutResource(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 19, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 20, 0, param, cbparam);
      
      
    }
    inline int SetProperty(const char* lpszPropertyName, const char* lpszPropertyValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPropertyName), (void*)IPW64CAST(lpszPropertyValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 22, 2, param, cbparam);
      
      
    }
    inline int UnLockResource(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 24, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebDAVConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebDAVConnectionStatusEventParamsW;

typedef struct {
  LPWSTR ResourceURI;
  LPWSTR DisplayName;
  LPWSTR ContentLanguage;
  LPWSTR ContentLength;
  LPWSTR ContentType;
  LPWSTR LastModified;
  int reserved;
} WebDAVDirListEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebDAVDisconnectedEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} WebDAVEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} WebDAVErrorEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} WebDAVHeaderEventParamsW;

typedef struct {
  int LogLevel;
  LPWSTR Message;
  LPWSTR LogType;
  int reserved;
} WebDAVLogEventParamsW;

typedef struct {
  LPWSTR Location;
  int Accept;
  int reserved;
} WebDAVRedirectEventParamsW;

typedef struct {
  LPWSTR ResourceURI;
  LPWSTR ResourceProperties;
  int reserved;
} WebDAVResourcePropertiesEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR Value;
  LPWSTR Expires;
  LPWSTR Domain;
  LPWSTR Path;
  int Secure;
  int reserved;
} WebDAVSetCookieEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} WebDAVSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} WebDAVSSLStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} WebDAVStartTransferEventParamsW;

typedef struct {
  LPWSTR HTTPVersion;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebDAVStatusEventParamsW;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int lenText;
  int reserved;
} WebDAVTransferEventParamsW;



class WebDAVW : public WebDAV {

  public: //properties
  
    inline LPWSTR GetAccept() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetAccept(LPCWSTR lpAccept) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+1, 0, (void*)lpAccept, 0);
    }

    inline LPWSTR GetAuthorization() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetAuthorization(LPCWSTR lpAuthorization) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+2, 0, (void*)lpAuthorization, 0);
    }







    inline LPWSTR GetCookieDomain(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+6, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieExpiration(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+7, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieName(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+8, iCookieIndex, 0);
    }

    inline int SetCookieName(int iCookieIndex, LPCWSTR lpCookieName) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+8, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline LPWSTR GetCookiePath(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+9, iCookieIndex, 0);
    }





    inline LPWSTR GetCookieValue(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+11, iCookieIndex, 0);
    }

    inline int SetCookieValue(int iCookieIndex, LPCWSTR lpCookieValue) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+11, iCookieIndex, (void*)lpCookieValue, 0);
    }







    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+15, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+16, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+18, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+10000+21, 0, 0);
    }

    inline int SetLocalFile(LPCWSTR lpLocalFile) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+10000+21, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+22, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetLockOwner() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+23, 0, 0);
    }

    inline int SetLockOwner(LPCWSTR lpLockOwner) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+23, 0, (void*)lpLockOwner, 0);
    }

    inline LPWSTR GetLockScope() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetLockScope(LPCWSTR lpLockScope) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+24, 0, (void*)lpLockScope, 0);
    }



    inline LPWSTR GetLockTokens() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+26, 0, 0);
    }

    inline int SetLockTokens(LPCWSTR lpLockTokens) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+26, 0, (void*)lpLockTokens, 0);
    }

    inline LPWSTR GetLockType() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+27, 0, 0);
    }

    inline int SetLockType(LPCWSTR lpLockType) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+27, 0, (void*)lpLockType, 0);
    }



    inline LPWSTR GetNamespacePrefix(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+29, iNamespaceIndex, 0);
    }

    inline int SetNamespacePrefix(int iNamespaceIndex, LPCWSTR lpNamespacePrefix) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+29, iNamespaceIndex, (void*)lpNamespacePrefix, 0);
    }

    inline LPWSTR GetNamespaceURI(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+30, iNamespaceIndex, 0);
    }

    inline int SetNamespaceURI(int iNamespaceIndex, LPCWSTR lpNamespaceURI) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+30, iNamespaceIndex, (void*)lpNamespaceURI, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+31, 0, 0);
    }

    inline int SetOtherHeaders(LPCWSTR lpOtherHeaders) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+31, 0, (void*)lpOtherHeaders, 0);
    }



    inline LPWSTR GetParsedHeaderField(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+33, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetParsedHeaderValue(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+34, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+35, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+35, 0, (void*)lpPassword, 0);
    }



    inline LPWSTR GetPropertyAttr(int iPropertyIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+37, iPropertyIndex, 0);
    }

    inline int SetPropertyAttr(int iPropertyIndex, LPCWSTR lpPropertyAttr) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+37, iPropertyIndex, (void*)lpPropertyAttr, 0);
    }

    inline LPWSTR GetPropertyName(int iPropertyIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+38, iPropertyIndex, 0);
    }

    inline int SetPropertyName(int iPropertyIndex, LPCWSTR lpPropertyName) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+38, iPropertyIndex, (void*)lpPropertyName, 0);
    }

    inline LPWSTR GetPropertyNamespaceURI(int iPropertyIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+39, iPropertyIndex, 0);
    }

    inline int SetPropertyNamespaceURI(int iPropertyIndex, LPCWSTR lpPropertyNamespaceURI) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+39, iPropertyIndex, (void*)lpPropertyNamespaceURI, 0);
    }



    inline LPWSTR GetPropertyStatus(int iPropertyIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+41, iPropertyIndex, 0);
    }



    inline LPWSTR GetPropertyValue(int iPropertyIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+42, iPropertyIndex, 0);
    }

    inline int SetPropertyValue(int iPropertyIndex, LPCWSTR lpPropertyValue) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+42, iPropertyIndex, (void*)lpPropertyValue, 0);
    }





    inline LPWSTR GetProxyPassword() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+45, 0, 0);
    }

    inline int SetProxyPassword(LPCWSTR lpProxyPassword) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+45, 0, (void*)lpProxyPassword, 0);
    }



    inline LPWSTR GetProxyServer() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+47, 0, 0);
    }

    inline int SetProxyServer(LPCWSTR lpProxyServer) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+47, 0, (void*)lpProxyServer, 0);
    }



    inline LPWSTR GetProxyUser() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+49, 0, 0);
    }

    inline int SetProxyUser(LPCWSTR lpProxyUser) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+49, 0, (void*)lpProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+50, 0, 0);
    }

    inline int SetReferer(LPCWSTR lpReferer) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+50, 0, (void*)lpReferer, 0);
    }



    inline LPWSTR GetResourceContentLanguage(int iResourceIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+52, iResourceIndex, 0);
    }



    inline LPWSTR GetResourceContentLength(int iResourceIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+53, iResourceIndex, 0);
    }



    inline LPWSTR GetResourceContentType(int iResourceIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+54, iResourceIndex, 0);
    }



    inline LPWSTR GetResourceDisplayName(int iResourceIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+55, iResourceIndex, 0);
    }



    inline LPWSTR GetResourceLastModified(int iResourceIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+56, iResourceIndex, 0);
    }



    inline LPWSTR GetResourceURI(int iResourceIndex) {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+57, iResourceIndex, 0);
    }



    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+58, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+58, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_WebDAV_Get(m_pObj, 58, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_WebDAV_Set(m_pObj, 58, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+59, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+59, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_WebDAV_Get(m_pObj, 59, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_WebDAV_Set(m_pObj, 59, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+60, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+60, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_WebDAV_Get(m_pObj, 60, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_WebDAV_Set(m_pObj, 60, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+61, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+61, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+63, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+63, 0, (void*)lpSSLCertSubject, 0);
    }

    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+64, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_WebDAV_Get(m_pObj, 64, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline LPWSTR GetStatusLine() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+65, 0, 0);
    }





    inline LPWSTR GetTransferredData() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+67, 0, 0);
    }


    inline int GetTransferredDataB(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_WebDAV_Get(m_pObj, 67, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }



    inline LPWSTR GetTransferredHeaders() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+69, 0, 0);
    }



    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_WebDAV_Get(m_pObj, 10000+70, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_WebDAV_Set(m_pObj, 10000+70, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnected(WebDAVConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(WebDAVConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDirList(WebDAVDirListEventParamsW *e) {return 0;}
    virtual int FireDisconnected(WebDAVDisconnectedEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(WebDAVEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(WebDAVErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(WebDAVHeaderEventParamsW *e) {return 0;}
    virtual int FireLog(WebDAVLogEventParamsW *e) {return 0;}
    virtual int FireRedirect(WebDAVRedirectEventParamsW *e) {return 0;}
    virtual int FireResourceProperties(WebDAVResourcePropertiesEventParamsW *e) {return 0;}
    virtual int FireSetCookie(WebDAVSetCookieEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(WebDAVSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(WebDAVSSLStatusEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(WebDAVStartTransferEventParamsW *e) {return 0;}
    virtual int FireStatus(WebDAVStatusEventParamsW *e) {return 0;}
    virtual int FireTransfer(WebDAVTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int WebDAVEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            WebDAVConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            WebDAVConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            WebDAVDirListEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]),  0};
            ret_code = FireDirList(&e);
            break;
         }
         case 4: {
            WebDAVDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 5: {
            WebDAVEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 6: {
            WebDAVErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 7: {
            WebDAVHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 8: {
            WebDAVLogEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireLog(&e);
            break;
         }
         case 9: {
            WebDAVRedirectEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = FireRedirect(&e);
            param[1] = (void*)(e.Accept);
            break;
         }
         case 10: {
            WebDAVResourcePropertiesEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireResourceProperties(&e);
            break;
         }
         case 11: {
            WebDAVSetCookieEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = FireSetCookie(&e);
            break;
         }
         case 12: {
            WebDAVSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 13: {
            WebDAVSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }
         case 14: {
            WebDAVStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 15: {
            WebDAVStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireStatus(&e);
            break;
         }
         case 16: {
            WebDAVTransferEventParamsW e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(WebDAVConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(WebDAVConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDirList(WebDAVDirListEventParams *e) {return -10000;}
    virtual int FireDisconnected(WebDAVDisconnectedEventParams *e) {return -10000;}
    virtual int FireEndTransfer(WebDAVEndTransferEventParams *e) {return -10000;}
    virtual int FireError(WebDAVErrorEventParams *e) {return -10000;}
    virtual int FireHeader(WebDAVHeaderEventParams *e) {return -10000;}
    virtual int FireLog(WebDAVLogEventParams *e) {return -10000;}
    virtual int FireRedirect(WebDAVRedirectEventParams *e) {return -10000;}
    virtual int FireResourceProperties(WebDAVResourcePropertiesEventParams *e) {return -10000;}
    virtual int FireSetCookie(WebDAVSetCookieEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(WebDAVSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(WebDAVSSLStatusEventParams *e) {return -10000;}
    virtual int FireStartTransfer(WebDAVStartTransferEventParams *e) {return -10000;}
    virtual int FireStatus(WebDAVStatusEventParams *e) {return -10000;}
    virtual int FireTransfer(WebDAVTransferEventParams *e) {return -10000;}

  public: //methods

    inline int AddCookie(LPWSTR lpszCookieName, LPWSTR lpszCookieValue) {
      void *param[2+1] = {(void*)lpszCookieName, (void*)lpszCookieValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+2, 2, param, cbparam);
      
    }
    inline int AddNamespace(LPWSTR lpszPrefix, LPWSTR lpszNamespaceURI) {
      void *param[2+1] = {(void*)lpszPrefix, (void*)lpszNamespaceURI, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+3, 2, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebDAV_Do(m_pObj, 10000+4, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int CopyResource(LPWSTR lpszSourceResourceURI, LPWSTR lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)lpszSourceResourceURI, (void*)lpszDestinationResourceURI, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+5, 2, param, cbparam);
      
    }
    inline int DeleteResource(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+6, 1, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int FindProperties(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+8, 1, param, cbparam);
      
    }
    inline int FindPropertyNames(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+9, 1, param, cbparam);
      
    }
    inline LPWSTR GetProperty(LPWSTR lpszPropertyName) {
      void *param[1+1] = {(void*)lpszPropertyName, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebDAV_Do(m_pObj, 10000+10, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int GetResource(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+11, 1, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }
    inline int ListDirectory(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+13, 1, param, cbparam);
      
    }
    inline int LockResource(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+14, 1, param, cbparam);
      
    }
    inline int MakeDirectory(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+15, 1, param, cbparam);
      
    }
    inline int MoveResource(LPWSTR lpszSourceResourceURI, LPWSTR lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)lpszSourceResourceURI, (void*)lpszDestinationResourceURI, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+16, 2, param, cbparam);
      
    }
    inline int PatchProperties(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+17, 1, param, cbparam);
      
    }
    inline int PostToResource(LPWSTR lpszResourceURI, LPWSTR lpPostData, int lenPostData) {
      void *param[2+1] = {(void*)lpszResourceURI, (void*)lpPostData, 0};
      int cbparam[2+1] = {0, lenPostData, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+18, 2, param, cbparam);
      
    }
    inline int PutResource(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+19, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+20, 0, param, cbparam);
      
    }
    inline int SetProperty(LPWSTR lpszPropertyName, LPWSTR lpszPropertyValue) {
      void *param[2+1] = {(void*)lpszPropertyName, (void*)lpszPropertyValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+22, 2, param, cbparam);
      
    }
    inline int UnLockResource(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebDAV_Do(m_pObj, 10000+24, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_WEBDAV_H_




