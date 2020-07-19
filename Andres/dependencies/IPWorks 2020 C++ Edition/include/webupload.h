/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_WEBUPLOAD_H_
#define _IPWORKS_WEBUPLOAD_H_

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


extern "C" void* IPWORKS_CALL IPWorks_WebUpload_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_WebUpload_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_WebUpload_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_WebUpload_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_StaticDestroy();

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
} WebUploadConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} WebUploadConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} WebUploadDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} WebUploadEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} WebUploadErrorEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} WebUploadHeaderEventParams;

typedef struct {
  int LogLevel;
  const char *Message;
  const char *LogType;
  int reserved;
} WebUploadLogEventParams;

typedef struct {
  const char *Location;
  int Accept;
  int reserved;
} WebUploadRedirectEventParams;

typedef struct {
  const char *Name;
  const char *Value;
  const char *Expires;
  const char *Domain;
  const char *Path;
  int Secure;
  int reserved;
} WebUploadSetCookieEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} WebUploadSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} WebUploadSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} WebUploadStartTransferEventParams;

typedef struct {
  const char *HTTPVersion;
  int StatusCode;
  const char *Description;
  int reserved;
} WebUploadStatusEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int reserved;
} WebUploadTransferEventParams;

typedef struct {
  int PercentDone;
  int reserved;
} WebUploadUploadProgressEventParams;


class WebUpload {
  public: // Events
    virtual int FireConnected(WebUploadConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(WebUploadConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(WebUploadDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(WebUploadEndTransferEventParams *e) {return 0;}
    virtual int FireError(WebUploadErrorEventParams *e) {return 0;}
    virtual int FireHeader(WebUploadHeaderEventParams *e) {return 0;}
    virtual int FireLog(WebUploadLogEventParams *e) {return 0;}
    virtual int FireRedirect(WebUploadRedirectEventParams *e) {return 0;}
    virtual int FireSetCookie(WebUploadSetCookieEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(WebUploadSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(WebUploadSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(WebUploadStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(WebUploadStatusEventParams *e) {return 0;}
    virtual int FireTransfer(WebUploadTransferEventParams *e) {return 0;}
    virtual int FireUploadProgress(WebUploadUploadProgressEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL WebUploadEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          WebUploadConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((WebUpload*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          WebUploadConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((WebUpload*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          WebUploadDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((WebUpload*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          WebUploadEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((WebUpload*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          WebUploadErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((WebUpload*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          WebUploadHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((WebUpload*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          WebUploadLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((WebUpload*)lpObj)->FireLog(&e);
          break;
        }
        case 8: {
          WebUploadRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), 0};
          ret_code = ((WebUpload*)lpObj)->FireRedirect(&e);
          param[1] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 9: {
          WebUploadSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), 0};
          ret_code = ((WebUpload*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 10: {
          WebUploadSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((WebUpload*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 11: {
          WebUploadSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((WebUpload*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 12: {
          WebUploadStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((WebUpload*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 13: {
          WebUploadStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((WebUpload*)lpObj)->FireStatus(&e);
          break;
        }
        case 14: {
          WebUploadTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), 0};
          ret_code = ((WebUpload*)lpObj)->FireTransfer(&e);
          break;
        }
        case 15: {
          WebUploadUploadProgressEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((WebUpload*)lpObj)->FireUploadProgress(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    WebUpload(char *lpOemKey = (char*)IPWORKS_OEMKEY_51) {
      m_pObj = IPWorks_WebUpload_Create(WebUploadEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~WebUpload() {
      IPWorks_WebUpload_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_WebUpload_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_WebUpload_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_WebUpload_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_WebUpload_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_WebUpload_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetAccept() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAccept(const char* lpszAccept) {
      return IPWorks_WebUpload_Set(m_pObj, 1, 0, (void*)lpszAccept, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthorization(const char* lpszAuthorization) {
      return IPWorks_WebUpload_Set(m_pObj, 2, 0, (void*)lpszAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_WebUpload_Set(m_pObj, 3, 0, val, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_WebUpload_Set(m_pObj, 4, 0, val, 0);
    }

    inline char* GetContentType() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetContentType(const char* lpszContentType) {
      return IPWorks_WebUpload_Set(m_pObj, 5, 0, (void*)lpszContentType, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_WebUpload_Set(m_pObj, 6, 0, val, 0);
    }

    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 7, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 8, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 9, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieName(int iCookieIndex, const char* lpszCookieName) {
      return IPWorks_WebUpload_Set(m_pObj, 9, iCookieIndex, (void*)lpszCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 10, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 11, iCookieIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 12, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieValue(int iCookieIndex, const char* lpszCookieValue) {
      return IPWorks_WebUpload_Set(m_pObj, 12, iCookieIndex, (void*)lpszCookieValue, 0);
    }

    inline int GetFileCount() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 13, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFileCount(int iFileCount) {
      void* val = (void*)IPW64CAST(iFileCount);
      return IPWorks_WebUpload_Set(m_pObj, 13, 0, val, 0);
    }

    inline char* GetFileVarContentType(int iFileIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 14, iFileIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetFileVarContentType(int iFileIndex, const char* lpszFileVarContentType) {
      return IPWorks_WebUpload_Set(m_pObj, 14, iFileIndex, (void*)lpszFileVarContentType, 0);
    }

    inline char* GetFileVarFile(int iFileIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 15, iFileIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetFileVarFile(int iFileIndex, const char* lpszFileVarFile) {
      return IPWorks_WebUpload_Set(m_pObj, 15, iFileIndex, (void*)lpszFileVarFile, 0);
    }

    inline int SetFileVarInputData(int iFileIndex, const char* lpFileVarInputData, int lenFileVarInputData) {
      return IPWorks_WebUpload_Set(m_pObj, 16, iFileIndex, (void*)lpFileVarInputData, lenFileVarInputData);
    }

    inline char* GetFileVarName(int iFileIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 17, iFileIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetFileVarName(int iFileIndex, const char* lpszFileVarName) {
      return IPWorks_WebUpload_Set(m_pObj, 17, iFileIndex, (void*)lpszFileVarName, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 18, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_WebUpload_Set(m_pObj, 18, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 19, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_WebUpload_Set(m_pObj, 19, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_WebUpload_Set(m_pObj, 20, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_WebUpload_Set(m_pObj, 21, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 22, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_WebUpload_Set(m_pObj, 22, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 23, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_WebUpload_Set(m_pObj, 23, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 24, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_WebUpload_Set(m_pObj, 24, 0, val, 0);
    }

    inline int GetFormVarCount() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 25, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFormVarCount(int iFormVarCount) {
      void* val = (void*)IPW64CAST(iFormVarCount);
      return IPWorks_WebUpload_Set(m_pObj, 25, 0, val, 0);
    }

    inline char* GetFormVarContentType(int iVarIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 26, iVarIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetFormVarContentType(int iVarIndex, const char* lpszFormVarContentType) {
      return IPWorks_WebUpload_Set(m_pObj, 26, iVarIndex, (void*)lpszFormVarContentType, 0);
    }

    inline char* GetFormVarName(int iVarIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 27, iVarIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetFormVarName(int iVarIndex, const char* lpszFormVarName) {
      return IPWorks_WebUpload_Set(m_pObj, 27, iVarIndex, (void*)lpszFormVarName, 0);
    }

    inline char* GetFormVarValue(int iVarIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 28, iVarIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetFormVarValue(int iVarIndex, const char* lpszFormVarValue) {
      return IPWorks_WebUpload_Set(m_pObj, 28, iVarIndex, (void*)lpszFormVarValue, 0);
    }

    inline char* GetFrom() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 29, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFrom(const char* lpszFrom) {
      return IPWorks_WebUpload_Set(m_pObj, 29, 0, (void*)lpszFrom, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 30, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 31, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_WebUpload_Set(m_pObj, 31, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_WebUpload_Set(m_pObj, 31+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 32, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_WebUpload_Set(m_pObj, 32, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 33, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherHeaders(const char* lpszOtherHeaders) {
      return IPWorks_WebUpload_Set(m_pObj, 33, 0, (void*)lpszOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 34, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 35, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_WebUpload_Get(m_pObj, 36, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 37, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_WebUpload_Set(m_pObj, 37, 0, (void*)lpszPassword, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 38, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_WebUpload_Set(m_pObj, 38, 0, val, 0);
    }

    inline int GetProxyAutoDetect() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 39, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_WebUpload_Set(m_pObj, 39, 0, val, 0);
    }

    inline char* GetProxyPassword() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 40, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyPassword(const char* lpszProxyPassword) {
      return IPWorks_WebUpload_Set(m_pObj, 40, 0, (void*)lpszProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 41, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyPort(int iProxyPort) {
      void* val = (void*)IPW64CAST(iProxyPort);
      return IPWorks_WebUpload_Set(m_pObj, 41, 0, val, 0);
    }

    inline char* GetProxyServer() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 42, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyServer(const char* lpszProxyServer) {
      return IPWorks_WebUpload_Set(m_pObj, 42, 0, (void*)lpszProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 43, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_WebUpload_Set(m_pObj, 43, 0, val, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 44, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyUser(const char* lpszProxyUser) {
      return IPWorks_WebUpload_Set(m_pObj, 44, 0, (void*)lpszProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 45, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReferer(const char* lpszReferer) {
      return IPWorks_WebUpload_Set(m_pObj, 45, 0, (void*)lpszReferer, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_WebUpload_Get(m_pObj, 46, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_WebUpload_Set(m_pObj, 46, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_WebUpload_Get(m_pObj, 47, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_WebUpload_Set(m_pObj, 47, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_WebUpload_Get(m_pObj, 48, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_WebUpload_Set(m_pObj, 48, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 49, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_WebUpload_Set(m_pObj, 49, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 50, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_WebUpload_Set(m_pObj, 50, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 51, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_WebUpload_Set(m_pObj, 51, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_WebUpload_Get(m_pObj, 52, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline char* GetStatusLine() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 53, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetTimeout() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 54, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_WebUpload_Set(m_pObj, 54, 0, val, 0);
    }

    inline int GetTransferredData(char* &lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_WebUpload_Get(m_pObj, 55, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline int64 GetTransferredDataLimit() {
      int64 retVal;
      IPWorks_WebUpload_Get(m_pObj, 56, 0, NULL, &retVal);
      return retVal;
    }
    inline int SetTransferredDataLimit(int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_WebUpload_Set(m_pObj, 56, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 57, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetURL() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 58, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetURL(const char* lpszURL) {
      return IPWorks_WebUpload_Set(m_pObj, 58, 0, (void*)lpszURL, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_WebUpload_Get(m_pObj, 59, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_WebUpload_Set(m_pObj, 59, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebUpload_Do(m_pObj, 2, 2, param, cbparam, NULL);
    }

    inline int AddFileVar(const char* lpszFileVar, const char* lpszFileName) {
      void *param[2+1] = {(void*)IPW64CAST(lpszFileVar), (void*)IPW64CAST(lpszFileName), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebUpload_Do(m_pObj, 3, 2, param, cbparam, NULL);
    }

    inline int AddFormVar(const char* lpszVarName, const char* lpszVarValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszVarName), (void*)IPW64CAST(lpszVarValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebUpload_Do(m_pObj, 4, 2, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebUpload_Do(m_pObj, 5, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebUpload_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebUpload_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebUpload_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline int Upload() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebUpload_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int UploadTo(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebUpload_Do(m_pObj, 10, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_WEBUPLOAD_H_
