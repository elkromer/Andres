/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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

//TValueFormat
#define VF_TEXT                                            0
#define VF_XML                                             1
#define VF_FULL_XML                                        2


extern "C" void* IPWORKS_CALL IPWorks_SOAP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SOAP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_SOAP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SOAP_GetLastErrorCode(void *lpObj);
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
  const char* Description;
  int reserved;
} SOAPConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} SOAPConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} SOAPDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} SOAPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} SOAPErrorEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} SOAPHeaderEventParams;

typedef struct {
  int LogLevel;
  const char* Message;
  const char* LogType;
  int reserved;
} SOAPLogEventParams;

typedef struct {
  const char* Location;
  int Accept;
  int reserved;
} SOAPRedirectEventParams;

typedef struct {
  const char* Name;
  const char* Value;
  const char* Expires;
  const char* Domain;
  const char* Path;
  int Secure;
  int reserved;
} SOAPSetCookieEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} SOAPSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} SOAPSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} SOAPStartTransferEventParams;

typedef struct {
  const char* HTTPVersion;
  int StatusCode;
  const char* Description;
  int reserved;
} SOAPStatusEventParams;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  int reserved;
} SOAPTransferEventParams;



class SOAP {
  
  public: //events
  
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
      if (event_id > 10000) return ((SOAP*)lpObj)->SOAPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            SOAPConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SOAP*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            SOAPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((SOAP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            SOAPDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SOAP*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            SOAPEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((SOAP*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 5: {
            SOAPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SOAP*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            SOAPHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SOAP*)lpObj)->FireHeader(&e);
            break;
         }
         case 7: {
            SOAPLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((SOAP*)lpObj)->FireLog(&e);
            break;
         }
         case 8: {
            SOAPRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = ((SOAP*)lpObj)->FireRedirect(&e);
            param[1] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 9: {
            SOAPSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = ((SOAP*)lpObj)->FireSetCookie(&e);
            break;
         }
         case 10: {
            SOAPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((SOAP*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 11: {
            SOAPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((SOAP*)lpObj)->FireSSLStatus(&e);
            break;
         }
         case 12: {
            SOAPStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((SOAP*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 13: {
            SOAPStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((SOAP*)lpObj)->FireStatus(&e);
            break;
         }
         case 14: {
            SOAPTransferEventParams e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = ((SOAP*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int SOAPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    SOAP(char *lpOemKey = (char*)IPWORKS_OEMKEY_55) {
      m_pObj = IPWorks_SOAP_Create(SOAPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~SOAP() {
      IPWorks_SOAP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_SOAP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_SOAP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_SOAP_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_SOAP_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_SOAP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetAccept() {
      void* val = IPWorks_SOAP_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetAccept(const char *lpAccept) {
      return IPWorks_SOAP_Set(m_pObj, 1, 0, (void*)lpAccept, 0);
    }

    inline char* GetActionURI() {
      void* val = IPWorks_SOAP_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetActionURI(const char *lpActionURI) {
      return IPWorks_SOAP_Set(m_pObj, 2, 0, (void*)lpActionURI, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_SOAP_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorization(const char *lpAuthorization) {
      return IPWorks_SOAP_Set(m_pObj, 3, 0, (void*)lpAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_SOAP_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_SOAP_Set(m_pObj, 4, 0, val, 0);
    }
    inline int GetConnected() {
      void* val = IPWorks_SOAP_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_SOAP_Set(m_pObj, 5, 0, val, 0);
    }
    inline char* GetContentType() {
      void* val = IPWorks_SOAP_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetContentType(const char *lpContentType) {
      return IPWorks_SOAP_Set(m_pObj, 6, 0, (void*)lpContentType, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_SOAP_Set(m_pObj, 7, 0, val, 0);
    }
    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 8, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 9, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 10, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieName(int iCookieIndex, const char *lpCookieName) {
      return IPWorks_SOAP_Set(m_pObj, 10, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 11, iCookieIndex, 0);
      return (char*)val;
    }


    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 12, iCookieIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 13, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieValue(int iCookieIndex, const char *lpCookieValue) {
      return IPWorks_SOAP_Set(m_pObj, 13, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline char* GetFaultActor() {
      void* val = IPWorks_SOAP_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }


    inline char* GetFaultCode() {
      void* val = IPWorks_SOAP_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }


    inline char* GetFaultString() {
      void* val = IPWorks_SOAP_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }


    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_SOAP_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_SOAP_Set(m_pObj, 17, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_SOAP_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_SOAP_Set(m_pObj, 18, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_SOAP_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_SOAP_Set(m_pObj, 19, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_SOAP_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_SOAP_Set(m_pObj, 20, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_SOAP_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_SOAP_Set(m_pObj, 21, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_SOAP_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_SOAP_Set(m_pObj, 22, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_SOAP_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_SOAP_Set(m_pObj, 23, 0, val, 0);
    }
    inline int GetIdle() {
      void* val = IPWorks_SOAP_Get(m_pObj, 24, 0, 0);
      return (int)(long)val;
    }

    inline char* GetIfModifiedSince() {
      void* val = IPWorks_SOAP_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }

    inline int SetIfModifiedSince(const char *lpIfModifiedSince) {
      return IPWorks_SOAP_Set(m_pObj, 25, 0, (void*)lpIfModifiedSince, 0);
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_SOAP_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_SOAP_Set(m_pObj, 26, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_SOAP_Get(m_pObj, 27, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_SOAP_Set(m_pObj, 27, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetMethod() {
      void* val = IPWorks_SOAP_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }

    inline int SetMethod(const char *lpMethod) {
      return IPWorks_SOAP_Set(m_pObj, 28, 0, (void*)lpMethod, 0);
    }

    inline char* GetMethodURI() {
      void* val = IPWorks_SOAP_Get(m_pObj, 29, 0, 0);
      return (char*)val;
    }

    inline int SetMethodURI(const char *lpMethodURI) {
      return IPWorks_SOAP_Set(m_pObj, 29, 0, (void*)lpMethodURI, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 30, 0, 0);
      return (int)(long)val;
    }
    inline int SetNamespaceCount(int iNamespaceCount) {
      void* val = (void*)IPW64CAST(iNamespaceCount);
      return IPWorks_SOAP_Set(m_pObj, 30, 0, val, 0);
    }
    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 31, iNamespaceIndex, 0);
      return (char*)val;
    }

    inline int SetNamespacePrefix(int iNamespaceIndex, const char *lpNamespacePrefix) {
      return IPWorks_SOAP_Set(m_pObj, 31, iNamespaceIndex, (void*)lpNamespacePrefix, 0);
    }

    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 32, iNamespaceIndex, 0);
      return (char*)val;
    }

    inline int SetNamespaceURI(int iNamespaceIndex, const char *lpNamespaceURI) {
      return IPWorks_SOAP_Set(m_pObj, 32, iNamespaceIndex, (void*)lpNamespaceURI, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_SOAP_Get(m_pObj, 33, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_SOAP_Set(m_pObj, 33, 0, (void*)lpOtherHeaders, 0);
    }

    inline int GetParamCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 34, 0, 0);
      return (int)(long)val;
    }
    inline int SetParamCount(int iParamCount) {
      void* val = (void*)IPW64CAST(iParamCount);
      return IPWorks_SOAP_Set(m_pObj, 34, 0, val, 0);
    }
    inline char* GetParamAttrs(int iParamIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 35, iParamIndex, 0);
      return (char*)val;
    }

    inline int SetParamAttrs(int iParamIndex, const char *lpParamAttrs) {
      return IPWorks_SOAP_Set(m_pObj, 35, iParamIndex, (void*)lpParamAttrs, 0);
    }

    inline char* GetParamName(int iParamIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 36, iParamIndex, 0);
      return (char*)val;
    }

    inline int SetParamName(int iParamIndex, const char *lpParamName) {
      return IPWorks_SOAP_Set(m_pObj, 36, iParamIndex, (void*)lpParamName, 0);
    }

    inline char* GetParamValue(int iParamIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 37, iParamIndex, 0);
      return (char*)val;
    }

    inline int SetParamValue(int iParamIndex, const char *lpParamValue) {
      return IPWorks_SOAP_Set(m_pObj, 37, iParamIndex, (void*)lpParamValue, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 38, 0, 0);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 39, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 40, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_SOAP_Get(m_pObj, 41, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_SOAP_Set(m_pObj, 41, 0, (void*)lpPassword, 0);
    }

    inline char* GetPragma() {
      void* val = IPWorks_SOAP_Get(m_pObj, 42, 0, 0);
      return (char*)val;
    }

    inline int SetPragma(const char *lpPragma) {
      return IPWorks_SOAP_Set(m_pObj, 42, 0, (void*)lpPragma, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_SOAP_Get(m_pObj, 43, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_SOAP_Set(m_pObj, 43, 0, val, 0);
    }
    inline int GetProxyAutoDetect() {
      void* val = IPWorks_SOAP_Get(m_pObj, 44, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_SOAP_Set(m_pObj, 44, 0, val, 0);
    }
    inline char* GetProxyPassword() {
      void* val = IPWorks_SOAP_Get(m_pObj, 45, 0, 0);
      return (char*)val;
    }

    inline int SetProxyPassword(const char *lpProxyPassword) {
      return IPWorks_SOAP_Set(m_pObj, 45, 0, (void*)lpProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_SOAP_Get(m_pObj, 46, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyPort(int lProxyPort) {
      void* val = (void*)IPW64CAST(lProxyPort);
      return IPWorks_SOAP_Set(m_pObj, 46, 0, val, 0);
    }
    inline char* GetProxyServer() {
      void* val = IPWorks_SOAP_Get(m_pObj, 47, 0, 0);
      return (char*)val;
    }

    inline int SetProxyServer(const char *lpProxyServer) {
      return IPWorks_SOAP_Set(m_pObj, 47, 0, (void*)lpProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_SOAP_Get(m_pObj, 48, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_SOAP_Set(m_pObj, 48, 0, val, 0);
    }
    inline char* GetProxyUser() {
      void* val = IPWorks_SOAP_Get(m_pObj, 49, 0, 0);
      return (char*)val;
    }

    inline int SetProxyUser(const char *lpProxyUser) {
      return IPWorks_SOAP_Set(m_pObj, 49, 0, (void*)lpProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_SOAP_Get(m_pObj, 50, 0, 0);
      return (char*)val;
    }

    inline int SetReferer(const char *lpReferer) {
      return IPWorks_SOAP_Set(m_pObj, 50, 0, (void*)lpReferer, 0);
    }

    inline char* GetReturnValue() {
      void* val = IPWorks_SOAP_Get(m_pObj, 51, 0, 0);
      return (char*)val;
    }


    inline char* GetSOAPEncoding() {
      void* val = IPWorks_SOAP_Get(m_pObj, 52, 0, 0);
      return (char*)val;
    }

    inline int SetSOAPEncoding(const char *lpSOAPEncoding) {
      return IPWorks_SOAP_Set(m_pObj, 52, 0, (void*)lpSOAPEncoding, 0);
    }

    inline char* GetSOAPHeader() {
      void* val = IPWorks_SOAP_Get(m_pObj, 53, 0, 0);
      return (char*)val;
    }

    inline int SetSOAPHeader(const char *lpSOAPHeader) {
      return IPWorks_SOAP_Set(m_pObj, 53, 0, (void*)lpSOAPHeader, 0);
    }

    inline char* GetSOAPPacket() {
      void* val = IPWorks_SOAP_Get(m_pObj, 54, 0, 0);
      return (char*)val;
    }

    inline int SetSOAPPacket(const char *lpSOAPPacket) {
      return IPWorks_SOAP_Set(m_pObj, 54, 0, (void*)lpSOAPPacket, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_SOAP_Get(m_pObj, 55, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_SOAP_Set(m_pObj, 55, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_SOAP_Get(m_pObj, 56, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_SOAP_Set(m_pObj, 56, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_SOAP_Get(m_pObj, 57, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_SOAP_Set(m_pObj, 57, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_SOAP_Get(m_pObj, 58, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_SOAP_Set(m_pObj, 58, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_SOAP_Get(m_pObj, 59, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_SOAP_Set(m_pObj, 59, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_SOAP_Get(m_pObj, 60, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_SOAP_Set(m_pObj, 60, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_SOAP_Get(m_pObj, 61, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline char* GetStatusLine() {
      void* val = IPWorks_SOAP_Get(m_pObj, 62, 0, 0);
      return (char*)val;
    }


    inline int GetTimeout() {
      void* val = IPWorks_SOAP_Get(m_pObj, 63, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_SOAP_Set(m_pObj, 63, 0, val, 0);
    }
    inline int GetTransferredData(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_SOAP_Get(m_pObj, 64, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }


    inline ns_int64 GetTransferredDataLimit() {
      ns_int64 *pval = (ns_int64*)IPWorks_SOAP_Get(m_pObj, 65, 0, 0);
      return *pval;
    }

    inline int SetTransferredDataLimit(ns_int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_SOAP_Set(m_pObj, 65, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_SOAP_Get(m_pObj, 66, 0, 0);
      return (char*)val;
    }


    inline char* GetURL() {
      void* val = IPWorks_SOAP_Get(m_pObj, 67, 0, 0);
      return (char*)val;
    }

    inline int SetURL(const char *lpURL) {
      return IPWorks_SOAP_Set(m_pObj, 67, 0, (void*)lpURL, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_SOAP_Get(m_pObj, 68, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_SOAP_Set(m_pObj, 68, 0, (void*)lpUser, 0);
    }

    inline int GetValueFormat() {
      void* val = IPWorks_SOAP_Get(m_pObj, 69, 0, 0);
      return (int)(long)val;
    }
    inline int SetValueFormat(int iValueFormat) {
      void* val = (void*)IPW64CAST(iValueFormat);
      return IPWorks_SOAP_Set(m_pObj, 69, 0, val, 0);
    }
    inline int GetAttrCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 70, 0, 0);
      return (int)(long)val;
    }

    inline char* GetAttrName(int iAttrIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 71, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrNamespace(int iAttrIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 72, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrPrefix(int iAttrIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 73, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrValue(int iAttrIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 74, iAttrIndex, 0);
      return (char*)val;
    }


    inline int GetXChildCount() {
      void* val = IPWorks_SOAP_Get(m_pObj, 75, 0, 0);
      return (int)(long)val;
    }

    inline char* GetXChildName(int iXChildIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 76, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildNamespace(int iXChildIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 77, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildPrefix(int iXChildIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 78, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildXText(int iXChildIndex) {
      void* val = IPWorks_SOAP_Get(m_pObj, 79, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXElement() {
      void* val = IPWorks_SOAP_Get(m_pObj, 80, 0, 0);
      return (char*)val;
    }


    inline char* GetXNamespace() {
      void* val = IPWorks_SOAP_Get(m_pObj, 81, 0, 0);
      return (char*)val;
    }


    inline char* GetXParent() {
      void* val = IPWorks_SOAP_Get(m_pObj, 82, 0, 0);
      return (char*)val;
    }


    inline char* GetXPath() {
      void* val = IPWorks_SOAP_Get(m_pObj, 83, 0, 0);
      return (char*)val;
    }

    inline int SetXPath(const char *lpXPath) {
      return IPWorks_SOAP_Set(m_pObj, 83, 0, (void*)lpXPath, 0);
    }

    inline char* GetXPrefix() {
      void* val = IPWorks_SOAP_Get(m_pObj, 84, 0, 0);
      return (char*)val;
    }


    inline char* GetXText() {
      void* val = IPWorks_SOAP_Get(m_pObj, 85, 0, 0);
      return (char*)val;
    }



  public: //methods

    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 2, 2, param, cbparam);
      
      
    }
    inline int AddNamespace(const char* lpszPrefix, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPrefix), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 3, 2, param, cbparam);
      
      
    }
    inline int AddParam(const char* lpszParamName, const char* lpszParamValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszParamName), (void*)IPW64CAST(lpszParamValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 4, 2, param, cbparam);
      
      
    }
    inline char* Attr(const char* lpszAttrName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 5, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int BuildPacket() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 7, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int EvalPacket() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int HasXPath(const char* lpszXPath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXPath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 10, 1, param, cbparam);
      
      return (int)IPW64CAST(param[1]);
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }
    inline int SendPacket() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 13, 0, param, cbparam);
      
      
    }
    inline int SendRequest() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 14, 0, param, cbparam);
      
      
    }
    inline int TryXPath(const char* lpszxpath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszxpath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 15, 1, param, cbparam);
      
      return (int)IPW64CAST(param[1]);
    }
    inline char* Value(const char* lpszParamName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszParamName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 16, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} SOAPConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} SOAPConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} SOAPDisconnectedEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} SOAPEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} SOAPErrorEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} SOAPHeaderEventParamsW;

typedef struct {
  int LogLevel;
  LPWSTR Message;
  LPWSTR LogType;
  int reserved;
} SOAPLogEventParamsW;

typedef struct {
  LPWSTR Location;
  int Accept;
  int reserved;
} SOAPRedirectEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR Value;
  LPWSTR Expires;
  LPWSTR Domain;
  LPWSTR Path;
  int Secure;
  int reserved;
} SOAPSetCookieEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} SOAPSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} SOAPSSLStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} SOAPStartTransferEventParamsW;

typedef struct {
  LPWSTR HTTPVersion;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} SOAPStatusEventParamsW;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  int reserved;
} SOAPTransferEventParamsW;



class SOAPW : public SOAP {

  public: //properties
  
    inline LPWSTR GetAccept() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetAccept(LPCWSTR lpAccept) {
      return IPWorks_SOAP_Set(m_pObj, 10000+1, 0, (void*)lpAccept, 0);
    }

    inline LPWSTR GetActionURI() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetActionURI(LPCWSTR lpActionURI) {
      return IPWorks_SOAP_Set(m_pObj, 10000+2, 0, (void*)lpActionURI, 0);
    }

    inline LPWSTR GetAuthorization() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetAuthorization(LPCWSTR lpAuthorization) {
      return IPWorks_SOAP_Set(m_pObj, 10000+3, 0, (void*)lpAuthorization, 0);
    }





    inline LPWSTR GetContentType() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetContentType(LPCWSTR lpContentType) {
      return IPWorks_SOAP_Set(m_pObj, 10000+6, 0, (void*)lpContentType, 0);
    }



    inline LPWSTR GetCookieDomain(int iCookieIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+8, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieExpiration(int iCookieIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+9, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieName(int iCookieIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+10, iCookieIndex, 0);
    }

    inline int SetCookieName(int iCookieIndex, LPCWSTR lpCookieName) {
      return IPWorks_SOAP_Set(m_pObj, 10000+10, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline LPWSTR GetCookiePath(int iCookieIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+11, iCookieIndex, 0);
    }





    inline LPWSTR GetCookieValue(int iCookieIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+13, iCookieIndex, 0);
    }

    inline int SetCookieValue(int iCookieIndex, LPCWSTR lpCookieValue) {
      return IPWorks_SOAP_Set(m_pObj, 10000+13, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline LPWSTR GetFaultActor() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+14, 0, 0);
    }



    inline LPWSTR GetFaultCode() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+15, 0, 0);
    }



    inline LPWSTR GetFaultString() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+16, 0, 0);
    }







    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_SOAP_Set(m_pObj, 10000+19, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_SOAP_Set(m_pObj, 10000+20, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_SOAP_Set(m_pObj, 10000+22, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetIfModifiedSince() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+25, 0, 0);
    }

    inline int SetIfModifiedSince(LPCWSTR lpIfModifiedSince) {
      return IPWorks_SOAP_Set(m_pObj, 10000+25, 0, (void*)lpIfModifiedSince, 0);
    }

    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+10000+26, 0, 0);
    }

    inline int SetLocalFile(LPCWSTR lpLocalFile) {
      return IPWorks_SOAP_Set(m_pObj, 10000+10000+26, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+27, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_SOAP_Set(m_pObj, 10000+27, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetMethod() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+28, 0, 0);
    }

    inline int SetMethod(LPCWSTR lpMethod) {
      return IPWorks_SOAP_Set(m_pObj, 10000+28, 0, (void*)lpMethod, 0);
    }

    inline LPWSTR GetMethodURI() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+29, 0, 0);
    }

    inline int SetMethodURI(LPCWSTR lpMethodURI) {
      return IPWorks_SOAP_Set(m_pObj, 10000+29, 0, (void*)lpMethodURI, 0);
    }



    inline LPWSTR GetNamespacePrefix(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+31, iNamespaceIndex, 0);
    }

    inline int SetNamespacePrefix(int iNamespaceIndex, LPCWSTR lpNamespacePrefix) {
      return IPWorks_SOAP_Set(m_pObj, 10000+31, iNamespaceIndex, (void*)lpNamespacePrefix, 0);
    }

    inline LPWSTR GetNamespaceURI(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+32, iNamespaceIndex, 0);
    }

    inline int SetNamespaceURI(int iNamespaceIndex, LPCWSTR lpNamespaceURI) {
      return IPWorks_SOAP_Set(m_pObj, 10000+32, iNamespaceIndex, (void*)lpNamespaceURI, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+33, 0, 0);
    }

    inline int SetOtherHeaders(LPCWSTR lpOtherHeaders) {
      return IPWorks_SOAP_Set(m_pObj, 10000+33, 0, (void*)lpOtherHeaders, 0);
    }



    inline LPWSTR GetParamAttrs(int iParamIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+35, iParamIndex, 0);
    }

    inline int SetParamAttrs(int iParamIndex, LPCWSTR lpParamAttrs) {
      return IPWorks_SOAP_Set(m_pObj, 10000+35, iParamIndex, (void*)lpParamAttrs, 0);
    }

    inline LPWSTR GetParamName(int iParamIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+36, iParamIndex, 0);
    }

    inline int SetParamName(int iParamIndex, LPCWSTR lpParamName) {
      return IPWorks_SOAP_Set(m_pObj, 10000+36, iParamIndex, (void*)lpParamName, 0);
    }

    inline LPWSTR GetParamValue(int iParamIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+37, iParamIndex, 0);
    }

    inline int SetParamValue(int iParamIndex, LPCWSTR lpParamValue) {
      return IPWorks_SOAP_Set(m_pObj, 10000+37, iParamIndex, (void*)lpParamValue, 0);
    }



    inline LPWSTR GetParsedHeaderField(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+39, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetParsedHeaderValue(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+40, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+41, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_SOAP_Set(m_pObj, 10000+41, 0, (void*)lpPassword, 0);
    }

    inline LPWSTR GetPragma() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+42, 0, 0);
    }

    inline int SetPragma(LPCWSTR lpPragma) {
      return IPWorks_SOAP_Set(m_pObj, 10000+42, 0, (void*)lpPragma, 0);
    }





    inline LPWSTR GetProxyPassword() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+45, 0, 0);
    }

    inline int SetProxyPassword(LPCWSTR lpProxyPassword) {
      return IPWorks_SOAP_Set(m_pObj, 10000+45, 0, (void*)lpProxyPassword, 0);
    }



    inline LPWSTR GetProxyServer() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+47, 0, 0);
    }

    inline int SetProxyServer(LPCWSTR lpProxyServer) {
      return IPWorks_SOAP_Set(m_pObj, 10000+47, 0, (void*)lpProxyServer, 0);
    }



    inline LPWSTR GetProxyUser() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+49, 0, 0);
    }

    inline int SetProxyUser(LPCWSTR lpProxyUser) {
      return IPWorks_SOAP_Set(m_pObj, 10000+49, 0, (void*)lpProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+50, 0, 0);
    }

    inline int SetReferer(LPCWSTR lpReferer) {
      return IPWorks_SOAP_Set(m_pObj, 10000+50, 0, (void*)lpReferer, 0);
    }

    inline LPWSTR GetReturnValue() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+51, 0, 0);
    }



    inline LPWSTR GetSOAPEncoding() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+52, 0, 0);
    }

    inline int SetSOAPEncoding(LPCWSTR lpSOAPEncoding) {
      return IPWorks_SOAP_Set(m_pObj, 10000+52, 0, (void*)lpSOAPEncoding, 0);
    }

    inline LPWSTR GetSOAPHeader() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+53, 0, 0);
    }

    inline int SetSOAPHeader(LPCWSTR lpSOAPHeader) {
      return IPWorks_SOAP_Set(m_pObj, 10000+53, 0, (void*)lpSOAPHeader, 0);
    }

    inline LPWSTR GetSOAPPacket() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+54, 0, 0);
    }

    inline int SetSOAPPacket(LPCWSTR lpSOAPPacket) {
      return IPWorks_SOAP_Set(m_pObj, 10000+54, 0, (void*)lpSOAPPacket, 0);
    }

    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+55, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_SOAP_Set(m_pObj, 10000+55, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_SOAP_Get(m_pObj, 55, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_SOAP_Set(m_pObj, 55, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+56, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_SOAP_Set(m_pObj, 10000+56, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_SOAP_Get(m_pObj, 56, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_SOAP_Set(m_pObj, 56, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+57, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_SOAP_Set(m_pObj, 10000+57, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_SOAP_Get(m_pObj, 57, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_SOAP_Set(m_pObj, 57, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+58, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_SOAP_Set(m_pObj, 10000+58, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+60, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_SOAP_Set(m_pObj, 10000+60, 0, (void*)lpSSLCertSubject, 0);
    }

    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+61, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_SOAP_Get(m_pObj, 61, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline LPWSTR GetStatusLine() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+62, 0, 0);
    }





    inline LPWSTR GetTransferredData() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+64, 0, 0);
    }


    inline int GetTransferredDataB(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_SOAP_Get(m_pObj, 64, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }



    inline LPWSTR GetTransferredHeaders() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+66, 0, 0);
    }



    inline LPWSTR GetURL() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+67, 0, 0);
    }

    inline int SetURL(LPCWSTR lpURL) {
      return IPWorks_SOAP_Set(m_pObj, 10000+67, 0, (void*)lpURL, 0);
    }

    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+68, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_SOAP_Set(m_pObj, 10000+68, 0, (void*)lpUser, 0);
    }





    inline LPWSTR GetAttrName(int iAttrIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+71, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrNamespace(int iAttrIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+72, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrPrefix(int iAttrIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+73, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrValue(int iAttrIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+74, iAttrIndex, 0);
    }





    inline LPWSTR GetXChildName(int iXChildIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+76, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildNamespace(int iXChildIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+77, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildPrefix(int iXChildIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+78, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildXText(int iXChildIndex) {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+79, iXChildIndex, 0);
    }



    inline LPWSTR GetXElement() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+80, 0, 0);
    }



    inline LPWSTR GetXNamespace() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+81, 0, 0);
    }



    inline LPWSTR GetXParent() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+82, 0, 0);
    }



    inline LPWSTR GetXPath() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+83, 0, 0);
    }

    inline int SetXPath(LPCWSTR lpXPath) {
      return IPWorks_SOAP_Set(m_pObj, 10000+83, 0, (void*)lpXPath, 0);
    }

    inline LPWSTR GetXPrefix() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+84, 0, 0);
    }



    inline LPWSTR GetXText() {
      return (LPWSTR)IPWorks_SOAP_Get(m_pObj, 10000+85, 0, 0);
    }





  public: //events
  
    virtual int FireConnected(SOAPConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(SOAPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(SOAPDisconnectedEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(SOAPEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(SOAPErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(SOAPHeaderEventParamsW *e) {return 0;}
    virtual int FireLog(SOAPLogEventParamsW *e) {return 0;}
    virtual int FireRedirect(SOAPRedirectEventParamsW *e) {return 0;}
    virtual int FireSetCookie(SOAPSetCookieEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(SOAPSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(SOAPSSLStatusEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(SOAPStartTransferEventParamsW *e) {return 0;}
    virtual int FireStatus(SOAPStatusEventParamsW *e) {return 0;}
    virtual int FireTransfer(SOAPTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int SOAPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            SOAPConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            SOAPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            SOAPDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            SOAPEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 5: {
            SOAPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            SOAPHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 7: {
            SOAPLogEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireLog(&e);
            break;
         }
         case 8: {
            SOAPRedirectEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = FireRedirect(&e);
            param[1] = (void*)(e.Accept);
            break;
         }
         case 9: {
            SOAPSetCookieEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = FireSetCookie(&e);
            break;
         }
         case 10: {
            SOAPSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 11: {
            SOAPSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }
         case 12: {
            SOAPStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 13: {
            SOAPStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireStatus(&e);
            break;
         }
         case 14: {
            SOAPTransferEventParamsW e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(SOAPConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(SOAPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(SOAPDisconnectedEventParams *e) {return -10000;}
    virtual int FireEndTransfer(SOAPEndTransferEventParams *e) {return -10000;}
    virtual int FireError(SOAPErrorEventParams *e) {return -10000;}
    virtual int FireHeader(SOAPHeaderEventParams *e) {return -10000;}
    virtual int FireLog(SOAPLogEventParams *e) {return -10000;}
    virtual int FireRedirect(SOAPRedirectEventParams *e) {return -10000;}
    virtual int FireSetCookie(SOAPSetCookieEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(SOAPSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(SOAPSSLStatusEventParams *e) {return -10000;}
    virtual int FireStartTransfer(SOAPStartTransferEventParams *e) {return -10000;}
    virtual int FireStatus(SOAPStatusEventParams *e) {return -10000;}
    virtual int FireTransfer(SOAPTransferEventParams *e) {return -10000;}

  public: //methods

    inline int AddCookie(LPWSTR lpszCookieName, LPWSTR lpszCookieValue) {
      void *param[2+1] = {(void*)lpszCookieName, (void*)lpszCookieValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 10000+2, 2, param, cbparam);
      
    }
    inline int AddNamespace(LPWSTR lpszPrefix, LPWSTR lpszNamespaceURI) {
      void *param[2+1] = {(void*)lpszPrefix, (void*)lpszNamespaceURI, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 10000+3, 2, param, cbparam);
      
    }
    inline int AddParam(LPWSTR lpszParamName, LPWSTR lpszParamValue) {
      void *param[2+1] = {(void*)lpszParamName, (void*)lpszParamValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SOAP_Do(m_pObj, 10000+4, 2, param, cbparam);
      
    }
    inline LPWSTR Attr(LPWSTR lpszAttrName) {
      void *param[1+1] = {(void*)lpszAttrName, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 10000+5, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int BuildPacket() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 10000+7, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int EvalPacket() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int HasXPath(LPWSTR lpszXPath) {
      void *param[1+1] = {(void*)lpszXPath, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 10000+10, 1, param, cbparam);
      return (int)IPW64CAST(param[1]);
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }
    inline int SendPacket() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 10000+13, 0, param, cbparam);
      
    }
    inline int SendRequest() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SOAP_Do(m_pObj, 10000+14, 0, param, cbparam);
      
    }
    inline int TryXPath(LPWSTR lpszxpath) {
      void *param[1+1] = {(void*)lpszxpath, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 10000+15, 1, param, cbparam);
      return (int)IPW64CAST(param[1]);
    }
    inline LPWSTR Value(LPWSTR lpszParamName) {
      void *param[1+1] = {(void*)lpszParamName, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SOAP_Do(m_pObj, 10000+16, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }

};

#endif //WIN32

#endif //_IPWORKS_SOAP_H_




