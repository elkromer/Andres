/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
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
extern "C" void* IPWORKS_CALL IPWorks_WebUpload_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_WebUpload_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_WebUpload_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_WebUpload_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebUploadConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebUploadConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebUploadDisconnectedEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} WebUploadEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} WebUploadErrorEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} WebUploadHeaderEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} WebUploadLogEventParams;

typedef struct {
  LPCWSTR Location;
  BOOL Accept;
  INT reserved;
} WebUploadRedirectEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR Value;
  LPCWSTR Expires;
  LPCWSTR Domain;
  LPCWSTR Path;
  BOOL Secure;
  INT reserved;
} WebUploadSetCookieEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} WebUploadSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} WebUploadSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} WebUploadStartTransferEventParams;

typedef struct {
  LPCWSTR HTTPVersion;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} WebUploadStatusEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  INT reserved;
} WebUploadTransferEventParams;

typedef struct {
  INT PercentDone;
  INT reserved;
} WebUploadUploadProgressEventParams;


class WebUpload {
  public: // Events
    virtual INT FireConnected(WebUploadConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(WebUploadConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(WebUploadDisconnectedEventParams *e) {return 0;}
    virtual INT FireEndTransfer(WebUploadEndTransferEventParams *e) {return 0;}
    virtual INT FireError(WebUploadErrorEventParams *e) {return 0;}
    virtual INT FireHeader(WebUploadHeaderEventParams *e) {return 0;}
    virtual INT FireLog(WebUploadLogEventParams *e) {return 0;}
    virtual INT FireRedirect(WebUploadRedirectEventParams *e) {return 0;}
    virtual INT FireSetCookie(WebUploadSetCookieEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(WebUploadSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(WebUploadSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(WebUploadStartTransferEventParams *e) {return 0;}
    virtual INT FireStatus(WebUploadStatusEventParams *e) {return 0;}
    virtual INT FireTransfer(WebUploadTransferEventParams *e) {return 0;}
    virtual INT FireUploadProgress(WebUploadUploadProgressEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL WebUploadEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          WebUploadConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebUpload*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          WebUploadConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((WebUpload*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          WebUploadDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebUpload*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          WebUploadEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((WebUpload*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          WebUploadErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebUpload*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          WebUploadHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((WebUpload*)lpObj)->FireHeader(&e);
          break;
        }
        case 7: {
          WebUploadLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((WebUpload*)lpObj)->FireLog(&e);
          break;
        }
        case 8: {
          WebUploadRedirectEventParams e = {(LPWSTR)param[0], (BOOL)param[1], 0};
          ret_code = ((WebUpload*)lpObj)->FireRedirect(&e);
          param[1] = (LPVOID)e.Accept;
          break;
        }
        case 9: {
          WebUploadSetCookieEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((WebUpload*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 10: {
          WebUploadSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((WebUpload*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 11: {
          WebUploadSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((WebUpload*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 12: {
          WebUploadStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((WebUpload*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 13: {
          WebUploadStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((WebUpload*)lpObj)->FireStatus(&e);
          break;
        }
        case 14: {
          WebUploadTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], 0};
          ret_code = ((WebUpload*)lpObj)->FireTransfer(&e);
          break;
        }
        case 15: {
          WebUploadUploadProgressEventParams e = {(INT)param[0], 0};
          ret_code = ((WebUpload*)lpObj)->FireUploadProgress(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    WebUpload(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_51) {
      m_pObj = IPWorks_WebUpload_Create(WebUploadEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~WebUpload() {
      IPWorks_WebUpload_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_WebUpload_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_WebUpload_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_WebUpload_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_WebUpload_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_WebUpload_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAccept() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAccept(LPCWSTR lpszAccept) {
      return IPWorks_WebUpload_Set(m_pObj, 1+10000, 0, (LPVOID)lpszAccept, 0);
    }

    inline LPWSTR GetAuthorization() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorization(LPCWSTR lpszAuthorization) {
      return IPWorks_WebUpload_Set(m_pObj, 2+10000, 0, (LPVOID)lpszAuthorization, 0);
    }

    inline INT GetAuthScheme() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 3, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthScheme(INT iAuthScheme) {
      LPVOID val = (LPVOID)(iAuthScheme);
      return IPWorks_WebUpload_Set(m_pObj, 3, 0, val, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 4, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_WebUpload_Set(m_pObj, 4, 0, val, 0);
    }

    inline LPWSTR GetContentType() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetContentType(LPCWSTR lpszContentType) {
      return IPWorks_WebUpload_Set(m_pObj, 5+10000, 0, (LPVOID)lpszContentType, 0);
    }

    inline INT GetCookieCount() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCookieCount(INT iCookieCount) {
      LPVOID val = (LPVOID)(iCookieCount);
      return IPWorks_WebUpload_Set(m_pObj, 6, 0, val, 0);
    }

    inline LPWSTR GetCookieDomain(INT iCookieIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 7+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieExpiration(INT iCookieIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 8+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieName(INT iCookieIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 9+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieName(INT iCookieIndex, LPCWSTR lpszCookieName) {
      return IPWorks_WebUpload_Set(m_pObj, 9+10000, iCookieIndex, (LPVOID)lpszCookieName, 0);
    }

    inline LPWSTR GetCookiePath(INT iCookieIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 10+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCookieSecure(INT iCookieIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 11, iCookieIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCookieValue(INT iCookieIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 12+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieValue(INT iCookieIndex, LPCWSTR lpszCookieValue) {
      return IPWorks_WebUpload_Set(m_pObj, 12+10000, iCookieIndex, (LPVOID)lpszCookieValue, 0);
    }

    inline INT GetFileCount() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 13, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFileCount(INT iFileCount) {
      LPVOID val = (LPVOID)(iFileCount);
      return IPWorks_WebUpload_Set(m_pObj, 13, 0, val, 0);
    }

    inline LPWSTR GetFileVarContentType(INT iFileIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 14+10000, iFileIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFileVarContentType(INT iFileIndex, LPCWSTR lpszFileVarContentType) {
      return IPWorks_WebUpload_Set(m_pObj, 14+10000, iFileIndex, (LPVOID)lpszFileVarContentType, 0);
    }

    inline LPWSTR GetFileVarFile(INT iFileIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 15+10000, iFileIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFileVarFile(INT iFileIndex, LPCWSTR lpszFileVarFile) {
      return IPWorks_WebUpload_Set(m_pObj, 15+10000, iFileIndex, (LPVOID)lpszFileVarFile, 0);
    }

    inline INT SetFileVarInputData(INT iFileIndex, LPCSTR lpFileVarInputData, INT lenFileVarInputData) {
      return IPWorks_WebUpload_Set(m_pObj, 16, iFileIndex, (LPVOID)lpFileVarInputData, lenFileVarInputData);
    }

    inline LPWSTR GetFileVarName(INT iFileIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 17+10000, iFileIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFileVarName(INT iFileIndex, LPCWSTR lpszFileVarName) {
      return IPWorks_WebUpload_Set(m_pObj, 17+10000, iFileIndex, (LPVOID)lpszFileVarName, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 18, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_WebUpload_Set(m_pObj, 18, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 19, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_WebUpload_Set(m_pObj, 19, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_WebUpload_Set(m_pObj, 20+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_WebUpload_Set(m_pObj, 21+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 22, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_WebUpload_Set(m_pObj, 22, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 23+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_WebUpload_Set(m_pObj, 23+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline INT GetFollowRedirects() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 24, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFollowRedirects(INT iFollowRedirects) {
      LPVOID val = (LPVOID)(iFollowRedirects);
      return IPWorks_WebUpload_Set(m_pObj, 24, 0, val, 0);
    }

    inline INT GetFormVarCount() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 25, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFormVarCount(INT iFormVarCount) {
      LPVOID val = (LPVOID)(iFormVarCount);
      return IPWorks_WebUpload_Set(m_pObj, 25, 0, val, 0);
    }

    inline LPWSTR GetFormVarContentType(INT iVarIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 26+10000, iVarIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFormVarContentType(INT iVarIndex, LPCWSTR lpszFormVarContentType) {
      return IPWorks_WebUpload_Set(m_pObj, 26+10000, iVarIndex, (LPVOID)lpszFormVarContentType, 0);
    }

    inline LPWSTR GetFormVarName(INT iVarIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 27+10000, iVarIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFormVarName(INT iVarIndex, LPCWSTR lpszFormVarName) {
      return IPWorks_WebUpload_Set(m_pObj, 27+10000, iVarIndex, (LPVOID)lpszFormVarName, 0);
    }

    inline LPWSTR GetFormVarValue(INT iVarIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 28+10000, iVarIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFormVarValue(INT iVarIndex, LPCWSTR lpszFormVarValue) {
      return IPWorks_WebUpload_Set(m_pObj, 28+10000, iVarIndex, (LPVOID)lpszFormVarValue, 0);
    }

    inline LPWSTR GetFrom() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFrom(LPCWSTR lpszFrom) {
      return IPWorks_WebUpload_Set(m_pObj, 29+10000, 0, (LPVOID)lpszFrom, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 30, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_WebUpload_Set(m_pObj, 31+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 32+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_WebUpload_Set(m_pObj, 32+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 33+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_WebUpload_Set(m_pObj, 33+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline INT GetParsedHeaderCount() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 34, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetParsedHeaderField(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 35+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetParsedHeaderValue(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 36+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 37+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_WebUpload_Set(m_pObj, 37+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetProxyAuthScheme() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 38, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyAuthScheme(INT iProxyAuthScheme) {
      LPVOID val = (LPVOID)(iProxyAuthScheme);
      return IPWorks_WebUpload_Set(m_pObj, 38, 0, val, 0);
    }

    inline BOOL GetProxyAutoDetect() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 39, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetProxyAutoDetect(BOOL bProxyAutoDetect) {
      LPVOID val = (LPVOID)(bProxyAutoDetect);
      return IPWorks_WebUpload_Set(m_pObj, 39, 0, val, 0);
    }

    inline LPWSTR GetProxyPassword() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 40+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyPassword(LPCWSTR lpszProxyPassword) {
      return IPWorks_WebUpload_Set(m_pObj, 40+10000, 0, (LPVOID)lpszProxyPassword, 0);
    }

    inline INT GetProxyPort() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 41, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyPort(INT iProxyPort) {
      LPVOID val = (LPVOID)(iProxyPort);
      return IPWorks_WebUpload_Set(m_pObj, 41, 0, val, 0);
    }

    inline LPWSTR GetProxyServer() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 42+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyServer(LPCWSTR lpszProxyServer) {
      return IPWorks_WebUpload_Set(m_pObj, 42+10000, 0, (LPVOID)lpszProxyServer, 0);
    }

    inline INT GetProxySSL() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 43, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxySSL(INT iProxySSL) {
      LPVOID val = (LPVOID)(iProxySSL);
      return IPWorks_WebUpload_Set(m_pObj, 43, 0, val, 0);
    }

    inline LPWSTR GetProxyUser() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 44+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyUser(LPCWSTR lpszProxyUser) {
      return IPWorks_WebUpload_Set(m_pObj, 44+10000, 0, (LPVOID)lpszProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 45+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReferer(LPCWSTR lpszReferer) {
      return IPWorks_WebUpload_Set(m_pObj, 45+10000, 0, (LPVOID)lpszReferer, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_WebUpload_Get(m_pObj, 46, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_WebUpload_Set(m_pObj, 46, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_WebUpload_Get(m_pObj, 47, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_WebUpload_Set(m_pObj, 47, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_WebUpload_Get(m_pObj, 48, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_WebUpload_Set(m_pObj, 48, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 49+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_WebUpload_Set(m_pObj, 49+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 50, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_WebUpload_Set(m_pObj, 50, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 51+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_WebUpload_Set(m_pObj, 51+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_WebUpload_Get(m_pObj, 52, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline LPWSTR GetStatusLine() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 53+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 54, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_WebUpload_Set(m_pObj, 54, 0, val, 0);
    }

    inline INT GetTransferredData(LPSTR &lpTransferredData, INT &lenTransferredData) {
      lpTransferredData = (LPSTR)IPWorks_WebUpload_Get(m_pObj, 55, 0, &lenTransferredData, NULL);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline LONG64 GetTransferredDataLimit() {
      LONG64 retVal;
      IPWorks_WebUpload_Get(m_pObj, 56, 0, NULL, &retVal);
      return retVal;
    }
    inline INT SetTransferredDataLimit(LONG64 lTransferredDataLimit) {
      LPVOID val = (LPVOID)(&lTransferredDataLimit);
      return IPWorks_WebUpload_Set(m_pObj, 56, 0, val, 0);
    }

    inline LPWSTR GetTransferredHeaders() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 57+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetURL() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 58+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetURL(LPCWSTR lpszURL) {
      return IPWorks_WebUpload_Set(m_pObj, 58+10000, 0, (LPVOID)lpszURL, 0);
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_WebUpload_Get(m_pObj, 59+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_WebUpload_Set(m_pObj, 59+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline INT AddCookie(LPCWSTR lpszCookieName, LPCWSTR lpszCookieValue) {
      LPVOID param[2+1] = {(LPVOID)lpszCookieName, (LPVOID)lpszCookieValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebUpload_Do(m_pObj, 2+10000, 2, param, cbparam, NULL);
    }

    inline INT AddFileVar(LPCWSTR lpszFileVar, LPCWSTR lpszFileName) {
      LPVOID param[2+1] = {(LPVOID)lpszFileVar, (LPVOID)lpszFileName, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebUpload_Do(m_pObj, 3+10000, 2, param, cbparam, NULL);
    }

    inline INT AddFormVar(LPCWSTR lpszVarName, LPCWSTR lpszVarValue) {
      LPVOID param[2+1] = {(LPVOID)lpszVarName, (LPVOID)lpszVarValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebUpload_Do(m_pObj, 4+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_WebUpload_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebUpload_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebUpload_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebUpload_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT Upload() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_WebUpload_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT UploadTo(LPCWSTR lpszURL) {
      LPVOID param[1+1] = {(LPVOID)lpszURL, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_WebUpload_Do(m_pObj, 10+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_WEBUPLOAD_H_
