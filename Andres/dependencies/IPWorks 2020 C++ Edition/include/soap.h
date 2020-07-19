/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_SOAP_H_
#define _IPWORKS_SOAP_H_

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

//TValueFormat
#define VF_TEXT                                            0
#define VF_XML                                             1
#define VF_FULL_XML                                        2


extern "C" void* IPWORKS_CALL IPWorks_SOAP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SOAP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_SOAP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_SOAP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_StaticDestroy();

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
} SOAPConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} SOAPConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} SOAPDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} SOAPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} SOAPErrorEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} SOAPHeaderEventParams;

typedef struct {
  int LogLevel;
  const char *Message;
  const char *LogType;
  int reserved;
} SOAPLogEventParams;

typedef struct {
  const char *Location;
  int Accept;
  int reserved;
} SOAPRedirectEventParams;

typedef struct {
  const char *Name;
  const char *Value;
  const char *Expires;
  const char *Domain;
  const char *Path;
  int Secure;
  int reserved;
} SOAPSetCookieEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} SOAPSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} SOAPSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} SOAPStartTransferEventParams;

typedef struct {
  const char *HTTPVersion;
  int StatusCode;
  const char *Description;
  int reserved;
} SOAPStatusEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  int reserved;
} SOAPTransferEventParams;


class SOAP {
  public: // Events
    virtual int FireConnected(SOAPConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(SOAPConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(SOAPDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(SOAPEndTransferEventParams *e) {return 0;}
    virtual int FireError(SOAPErrorEventParams *e) {return 0;}
    virtual int FireHeader(SOAPHeaderEventParams *e) {return 0;}
    virtual int FireLog(SOAPLogEventParams *e) {return 0;}
    virtual int FireRedirect(SOAPRedirectEventParams *e) {return 0;}
    virtual int FireSetCookie(SOAPSetCookieEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(SOAPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(SOAPSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(SOAPStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(SOAPStatusEventParams *e) {return 0;}
    virtual int FireTransfer(SOAPTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL SOAPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          SOAPConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((SOAP*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          SOAPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((SOAP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          SOAPDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((SOAP*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          SOAPEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((SOAP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          SOAPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((SOAP*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          SOAPHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((SOAP*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          SOAPLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((SOAP*)lpObj)->FireLog(&e);
          break;
        }
        case 8: {
          SOAPRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), 0};
          ret_code = ((SOAP*)lpObj)->FireRedirect(&e);
          param[1] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 9: {
          SOAPSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), 0};
          ret_code = ((SOAP*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 10: {
          SOAPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((SOAP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 11: {
          SOAPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((SOAP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 12: {
          SOAPStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((SOAP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 13: {
          SOAPStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((SOAP*)lpObj)->FireStatus(&e);
          break;
        }
        case 14: {
          SOAPTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), 0};
          ret_code = ((SOAP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    SOAP(char *lpOemKey = (char*)IPWORKS_OEMKEY_55) {
      m_pObj = IPWorks_SOAP_Create(SOAPEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~SOAP() {
      IPWorks_SOAP_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_SOAP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_SOAP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_SOAP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_SOAP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_SOAP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetAccept() {
      void* val = IPWorks_SOAP_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAccept(const char* lpszAccept) {
      return IPWorks_SOAP_Set(m_pObj, 1, 0, (void*)lpszAccept, 0);
    }

    inline char* GetActionURI() {
      void* val = IPWorks_SOAP_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetActionURI(const char* lpszActionURI) {
      return IPWorks_SOAP_Set(m_pObj, 2, 0, (void*)lpszActionURI, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_SOAP_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthorization(const char* lpszAuthorization) {
      return IPWorks_SOAP_Set(m_pObj, 3, 0, (void*)lpszAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_SOAP_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_SOAP_Set(m_pObj, 4, 0, val, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_SOAP_Get(m_pObj, 5, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_SOAP_Set(m_pObj, 5, 0, val, 0);
    }

    inline char* GetContentType() {
      void* val = IPWorks_SOAP_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetContentType(const char* lpszContentType) {
      return IPWorks_SOAP_Set(m_pObj, 6, 0, (void*)lpszContentType, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 7, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_SOAP_Set(m_pObj, 7, 0, val, 0);
    }

    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 8, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 9, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 10, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieName(int iCookieIndex, const char* lpszCookieName) {
      return IPWorks_SOAP_Set(m_pObj, 10, iCookieIndex, (void*)lpszCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 11, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 12, iCookieIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 13, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieValue(int iCookieIndex, const char* lpszCookieValue) {
      return IPWorks_SOAP_Set(m_pObj, 13, iCookieIndex, (void*)lpszCookieValue, 0);
    }

    inline char* GetFaultActor() {
      void* val = IPWorks_SOAP_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetFaultCode() {
      void* val = IPWorks_SOAP_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetFaultString() {
      void* val = IPWorks_SOAP_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_SOAP_Get(m_pObj, 17, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_SOAP_Set(m_pObj, 17, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_SOAP_Get(m_pObj, 18, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_SOAP_Set(m_pObj, 18, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_SOAP_Get(m_pObj, 19, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_SOAP_Set(m_pObj, 19, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_SOAP_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_SOAP_Set(m_pObj, 20, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_SOAP_Get(m_pObj, 21, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_SOAP_Set(m_pObj, 21, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_SOAP_Get(m_pObj, 22, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_SOAP_Set(m_pObj, 22, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_SOAP_Get(m_pObj, 23, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_SOAP_Set(m_pObj, 23, 0, val, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_SOAP_Get(m_pObj, 24, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetIfModifiedSince() {
      void* val = IPWorks_SOAP_Get(m_pObj, 25, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetIfModifiedSince(const char* lpszIfModifiedSince) {
      return IPWorks_SOAP_Set(m_pObj, 25, 0, (void*)lpszIfModifiedSince, 0);
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_SOAP_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_SOAP_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_SOAP_Set(m_pObj, 26, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_SOAP_Set(m_pObj, 26+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_SOAP_Get(m_pObj, 27, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_SOAP_Set(m_pObj, 27, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetMethod() {
      void* val = IPWorks_SOAP_Get(m_pObj, 28, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMethod(const char* lpszMethod) {
      return IPWorks_SOAP_Set(m_pObj, 28, 0, (void*)lpszMethod, 0);
    }

    inline char* GetMethodURI() {
      void* val = IPWorks_SOAP_Get(m_pObj, 29, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMethodURI(const char* lpszMethodURI) {
      return IPWorks_SOAP_Set(m_pObj, 29, 0, (void*)lpszMethodURI, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 30, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetNamespaceCount(int iNamespaceCount) {
      void* val = (void*)IPW64CAST(iNamespaceCount);
      return IPWorks_SOAP_Set(m_pObj, 30, 0, val, 0);
    }

    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 31, iNamespaceIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetNamespacePrefix(int iNamespaceIndex, const char* lpszNamespacePrefix) {
      return IPWorks_SOAP_Set(m_pObj, 31, iNamespaceIndex, (void*)lpszNamespacePrefix, 0);
    }

    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 32, iNamespaceIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetNamespaceURI(int iNamespaceIndex, const char* lpszNamespaceURI) {
      return IPWorks_SOAP_Set(m_pObj, 32, iNamespaceIndex, (void*)lpszNamespaceURI, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_SOAP_Get(m_pObj, 33, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherHeaders(const char* lpszOtherHeaders) {
      return IPWorks_SOAP_Set(m_pObj, 33, 0, (void*)lpszOtherHeaders, 0);
    }

    inline int GetParamCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 34, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetParamCount(int iParamCount) {
      void* val = (void*)IPW64CAST(iParamCount);
      return IPWorks_SOAP_Set(m_pObj, 34, 0, val, 0);
    }

    inline char* GetParamAttrs(int iParamIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 35, iParamIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetParamAttrs(int iParamIndex, const char* lpszParamAttrs) {
      return IPWorks_SOAP_Set(m_pObj, 35, iParamIndex, (void*)lpszParamAttrs, 0);
    }

    inline char* GetParamName(int iParamIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 36, iParamIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetParamName(int iParamIndex, const char* lpszParamName) {
      return IPWorks_SOAP_Set(m_pObj, 36, iParamIndex, (void*)lpszParamName, 0);
    }

    inline char* GetParamValue(int iParamIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 37, iParamIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetParamValue(int iParamIndex, const char* lpszParamValue) {
      return IPWorks_SOAP_Set(m_pObj, 37, iParamIndex, (void*)lpszParamValue, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 38, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 39, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 40, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_SOAP_Get(m_pObj, 41, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_SOAP_Set(m_pObj, 41, 0, (void*)lpszPassword, 0);
    }

    inline char* GetPragma() {
      void* val = IPWorks_SOAP_Get(m_pObj, 42, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPragma(const char* lpszPragma) {
      return IPWorks_SOAP_Set(m_pObj, 42, 0, (void*)lpszPragma, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_SOAP_Get(m_pObj, 43, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_SOAP_Set(m_pObj, 43, 0, val, 0);
    }

    inline int GetProxyAutoDetect() {
      void* val = IPWorks_SOAP_Get(m_pObj, 44, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_SOAP_Set(m_pObj, 44, 0, val, 0);
    }

    inline char* GetProxyPassword() {
      void* val = IPWorks_SOAP_Get(m_pObj, 45, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyPassword(const char* lpszProxyPassword) {
      return IPWorks_SOAP_Set(m_pObj, 45, 0, (void*)lpszProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_SOAP_Get(m_pObj, 46, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyPort(int iProxyPort) {
      void* val = (void*)IPW64CAST(iProxyPort);
      return IPWorks_SOAP_Set(m_pObj, 46, 0, val, 0);
    }

    inline char* GetProxyServer() {
      void* val = IPWorks_SOAP_Get(m_pObj, 47, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyServer(const char* lpszProxyServer) {
      return IPWorks_SOAP_Set(m_pObj, 47, 0, (void*)lpszProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_SOAP_Get(m_pObj, 48, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_SOAP_Set(m_pObj, 48, 0, val, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_SOAP_Get(m_pObj, 49, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyUser(const char* lpszProxyUser) {
      return IPWorks_SOAP_Set(m_pObj, 49, 0, (void*)lpszProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_SOAP_Get(m_pObj, 50, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReferer(const char* lpszReferer) {
      return IPWorks_SOAP_Set(m_pObj, 50, 0, (void*)lpszReferer, 0);
    }

    inline char* GetReturnValue() {
      void* val = IPWorks_SOAP_Get(m_pObj, 51, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSOAPEncoding() {
      void* val = IPWorks_SOAP_Get(m_pObj, 52, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSOAPEncoding(const char* lpszSOAPEncoding) {
      return IPWorks_SOAP_Set(m_pObj, 52, 0, (void*)lpszSOAPEncoding, 0);
    }

    inline char* GetSOAPHeader() {
      void* val = IPWorks_SOAP_Get(m_pObj, 53, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSOAPHeader(const char* lpszSOAPHeader) {
      return IPWorks_SOAP_Set(m_pObj, 53, 0, (void*)lpszSOAPHeader, 0);
    }

    inline char* GetSOAPPacket() {
      void* val = IPWorks_SOAP_Get(m_pObj, 54, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSOAPPacket(const char* lpszSOAPPacket) {
      return IPWorks_SOAP_Set(m_pObj, 54, 0, (void*)lpszSOAPPacket, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_SOAP_Get(m_pObj, 55, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_SOAP_Set(m_pObj, 55, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_SOAP_Get(m_pObj, 56, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_SOAP_Set(m_pObj, 56, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_SOAP_Get(m_pObj, 57, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_SOAP_Set(m_pObj, 57, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_SOAP_Get(m_pObj, 58, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_SOAP_Set(m_pObj, 58, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_SOAP_Get(m_pObj, 59, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_SOAP_Set(m_pObj, 59, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_SOAP_Get(m_pObj, 60, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_SOAP_Set(m_pObj, 60, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_SOAP_Get(m_pObj, 61, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline char* GetStatusLine() {
      void* val = IPWorks_SOAP_Get(m_pObj, 62, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetTimeout() {
      void* val = IPWorks_SOAP_Get(m_pObj, 63, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_SOAP_Set(m_pObj, 63, 0, val, 0);
    }

    inline int GetTransferredData(char* &lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_SOAP_Get(m_pObj, 64, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline int64 GetTransferredDataLimit() {
      int64 retVal;
      IPWorks_SOAP_Get(m_pObj, 65, 0, NULL, &retVal);
      return retVal;
    }
    inline int SetTransferredDataLimit(int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_SOAP_Set(m_pObj, 65, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_SOAP_Get(m_pObj, 66, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetURL() {
      void* val = IPWorks_SOAP_Get(m_pObj, 67, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetURL(const char* lpszURL) {
      return IPWorks_SOAP_Set(m_pObj, 67, 0, (void*)lpszURL, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_SOAP_Get(m_pObj, 68, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_SOAP_Set(m_pObj, 68, 0, (void*)lpszUser, 0);
    }

    inline int GetValueFormat() {
      void* val = IPWorks_SOAP_Get(m_pObj, 69, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetValueFormat(int iValueFormat) {
      void* val = (void*)IPW64CAST(iValueFormat);
      return IPWorks_SOAP_Set(m_pObj, 69, 0, val, 0);
    }

    inline int GetAttrCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 70, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetAttrName(int iAttrIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 71, iAttrIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetAttrNamespace(int iAttrIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 72, iAttrIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetAttrPrefix(int iAttrIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 73, iAttrIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetAttrValue(int iAttrIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 74, iAttrIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetXChildCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 75, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetXChildName(int iXChildIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 76, iXChildIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXChildNamespace(int iXChildIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 77, iXChildIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXChildPrefix(int iXChildIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 78, iXChildIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXChildXText(int iXChildIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 79, iXChildIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXElement() {
      void* val = IPWorks_SOAP_Get(m_pObj, 80, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXNamespace() {
      void* val = IPWorks_SOAP_Get(m_pObj, 81, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXParent() {
      void* val = IPWorks_SOAP_Get(m_pObj, 82, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXPath() {
      void* val = IPWorks_SOAP_Get(m_pObj, 83, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXPath(const char* lpszXPath) {
      return IPWorks_SOAP_Set(m_pObj, 83, 0, (void*)lpszXPath, 0);
    }

    inline char* GetXPrefix() {
      void* val = IPWorks_SOAP_Get(m_pObj, 84, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXText() {
      void* val = IPWorks_SOAP_Get(m_pObj, 85, 0, NULL, NULL);
      return (char*)val;
    }

  public: // Methods
    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 2, 2, param, cbparam, NULL);
    }

    inline int AddNamespace(const char* lpszPrefix, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPrefix), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 3, 2, param, cbparam, NULL);
    }

    inline int AddParam(const char* lpszParamName, const char* lpszParamValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszParamName), (void*)IPW64CAST(lpszParamValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 4, 2, param, cbparam, NULL);
    }

    inline char* Attr(const char* lpszAttrName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 5, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int BuildPacket() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 7, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline int EvalPacket() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int HasXPath(const char* lpszXPath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXPath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 10, 1, param, cbparam, NULL);
      return (int)IPW64CAST(param[1]);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 11, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 12, 0, param, cbparam, NULL);
    }

    inline int SendPacket() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 13, 0, param, cbparam, NULL);
    }

    inline int SendRequest() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 14, 0, param, cbparam, NULL);
    }

    inline int TryXPath(const char* lpszxpath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszxpath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 15, 1, param, cbparam, NULL);
      return (int)IPW64CAST(param[1]);
    }

    inline char* Value(const char* lpszParamName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszParamName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 16, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

};

#endif //_IPWORKS_SOAP_H_
