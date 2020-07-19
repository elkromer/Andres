/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_POP_H_
#define _IPWORKS_POP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//AuthMechanisms
#define AM_USER_PASSWORD                                   0
#define AM_CRAMMD5                                         1
#define AM_NTLM                                            2
#define AM_APOP                                            3
#define AM_SASLPLAIN                                       4
#define AM_SASLDIGEST_MD5                                  5
#define AM_KERBEROS                                        6
#define AM_XOAUTH2                                         7

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//EmailRecipientTypes
#define RT_TO                                              0
#define RT_CC                                              1
#define RT_BCC                                             2

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

//TSSLStartMode
#define SSL_AUTOMATIC                                      0
#define SSL_IMPLICIT                                       1
#define SSL_EXPLICIT                                       2
#define SSL_NONE                                           3


extern "C" void* IPWORKS_CALL IPWorks_POP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_POP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_POP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_POP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_POP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_POP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_POP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_POP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_POP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} POPConnectionStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} POPEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} POPErrorEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} POPHeaderEventParams;

typedef struct {
  INT MessageNumber;
  LPCWSTR MessageUID;
  INT MessageSize;
  INT reserved;
} POPMessageListEventParams;

typedef struct {
  INT Direction;
  LPCWSTR Message;
  INT reserved;
} POPPITrailEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} POPSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} POPSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} POPStartTransferEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  BOOL EOL;
  INT reserved;
} POPTransferEventParams;


class POP {
  public: // Events
    virtual INT FireConnectionStatus(POPConnectionStatusEventParams *e) {return 0;}
    virtual INT FireEndTransfer(POPEndTransferEventParams *e) {return 0;}
    virtual INT FireError(POPErrorEventParams *e) {return 0;}
    virtual INT FireHeader(POPHeaderEventParams *e) {return 0;}
    virtual INT FireMessageList(POPMessageListEventParams *e) {return 0;}
    virtual INT FirePITrail(POPPITrailEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(POPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(POPSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(POPStartTransferEventParams *e) {return 0;}
    virtual INT FireTransfer(POPTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL POPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          POPConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((POP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          POPEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((POP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 3: {
          POPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((POP*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          POPHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((POP*)lpObj)->FireHeader(&e);
          break;
        }
        case 5: {
          POPMessageListEventParams e = {(INT)param[0], (LPWSTR)param[1], (INT)param[2], 0};
          ret_code = ((POP*)lpObj)->FireMessageList(&e);
          break;
        }
        case 6: {
          POPPITrailEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((POP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 7: {
          POPSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((POP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 8: {
          POPSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((POP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 9: {
          POPStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((POP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 10: {
          POPTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], (BOOL)param[4], 0};
          ret_code = ((POP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    POP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_24) {
      m_pObj = IPWorks_POP_Create(POPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~POP() {
      IPWorks_POP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_POP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_POP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_POP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_POP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_POP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetAuthMechanism() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 1, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthMechanism(INT iAuthMechanism) {
      LPVOID val = (LPVOID)(iAuthMechanism);
      return IPWorks_POP_Set(m_pObj, 1, 0, val, 0);
    }

    inline INT SetCommand(LPCWSTR lpszCommand) {
      return IPWorks_POP_Set(m_pObj, 2+10000, 0, (LPVOID)lpszCommand, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 3, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_POP_Set(m_pObj, 3, 0, val, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 4, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_POP_Set(m_pObj, 4, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 5, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_POP_Set(m_pObj, 5, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_POP_Set(m_pObj, 6+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_POP_Set(m_pObj, 7+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 8, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_POP_Set(m_pObj, 8, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_POP_Set(m_pObj, 9+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 10, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline BOOL GetIncludeHeaders() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 11, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetIncludeHeaders(BOOL bIncludeHeaders) {
      LPVOID val = (LPVOID)(bIncludeHeaders);
      return IPWorks_POP_Set(m_pObj, 11, 0, val, 0);
    }

    inline LPWSTR GetLastReply() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_POP_Set(m_pObj, 13+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_POP_Set(m_pObj, 14+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetMailPort() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 15, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMailPort(INT iMailPort) {
      LPVOID val = (LPVOID)(iMailPort);
      return IPWorks_POP_Set(m_pObj, 15, 0, val, 0);
    }

    inline LPWSTR GetMailServer() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMailServer(LPCWSTR lpszMailServer) {
      return IPWorks_POP_Set(m_pObj, 16+10000, 0, (LPVOID)lpszMailServer, 0);
    }

    inline INT GetMaxLines() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 17, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMaxLines(INT iMaxLines) {
      LPVOID val = (LPVOID)(iMaxLines);
      return IPWorks_POP_Set(m_pObj, 17, 0, val, 0);
    }

    inline INT GetMessage(LPSTR &lpMessage, INT &lenMessage) {
      lpMessage = (LPSTR)IPWorks_POP_Get(m_pObj, 18, 0, &lenMessage, NULL);
      return lpMessage ? 0 : lenMessage;
    }

    inline LPWSTR GetMessageCc() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessageCount() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 20, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMessageDate() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageFrom() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessageHeaderCount() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 23, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMessageHeaderField(INT iMessageHeaderIndex) {
      LPVOID val = IPWorks_POP_Get(m_pObj, 24+10000, iMessageHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageHeaderValue(INT iMessageHeaderIndex) {
      LPVOID val = IPWorks_POP_Get(m_pObj, 25+10000, iMessageHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageHeadersString() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessageNumber() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 27, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMessageNumber(INT iMessageNumber) {
      LPVOID val = (LPVOID)(iMessageNumber);
      return IPWorks_POP_Set(m_pObj, 27, 0, val, 0);
    }

    inline INT GetMessageRecipientCount() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 28, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMessageRecipientAddress(INT iRecipientIndex) {
      LPVOID val = IPWorks_POP_Get(m_pObj, 29+10000, iRecipientIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageRecipientName(INT iRecipientIndex) {
      LPVOID val = IPWorks_POP_Get(m_pObj, 30+10000, iRecipientIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageRecipientOptions(INT iRecipientIndex) {
      LPVOID val = IPWorks_POP_Get(m_pObj, 31+10000, iRecipientIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessageRecipientType(INT iRecipientIndex) {
      LPVOID val = IPWorks_POP_Get(m_pObj, 32, iRecipientIndex, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMessageReplyTo() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 33+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessageSize() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 34, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMessageSubject() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 35+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageText() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 36+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageTo() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 37+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageUID() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 38+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 39+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_POP_Set(m_pObj, 39+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_POP_Get(m_pObj, 40, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_POP_Set(m_pObj, 40, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_POP_Get(m_pObj, 41, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_POP_Set(m_pObj, 41, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_POP_Get(m_pObj, 42, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_POP_Set(m_pObj, 42, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 43+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_POP_Set(m_pObj, 43+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 44, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_POP_Set(m_pObj, 44, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 45+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_POP_Set(m_pObj, 45+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 46, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_POP_Set(m_pObj, 46, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_POP_Get(m_pObj, 47, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 48, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_POP_Set(m_pObj, 48, 0, val, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 49, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_POP_Set(m_pObj, 49, 0, val, 0);
    }

    inline LONG64 GetTotalSize() {
      LONG64 retVal;
      IPWorks_POP_Get(m_pObj, 50, 0, NULL, &retVal);
      return retVal;
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_POP_Get(m_pObj, 51+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_POP_Set(m_pObj, 51+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_POP_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Connect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Delete() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT ListMessageSizes() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT ListMessageUIDs() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR LocalizeDate(LPCWSTR lpszDateTime) {
      LPVOID param[1+1] = {(LPVOID)lpszDateTime, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_POP_Do(m_pObj, 10+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 11+10000, 0, param, cbparam, NULL);
    }

    inline INT Retrieve() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
    }

    inline INT RetrieveHeaders() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 13+10000, 0, param, cbparam, NULL);
    }

    inline INT SetMessageStream(IPWorksStream* sMessageStream) {
      LPVOID param[1+1] = {(LPVOID)sMessageStream, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_POP_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_POP_H_
