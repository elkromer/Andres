/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_HTMLMAILER_H_
#define _IPWORKS_HTMLMAILER_H_

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

//TImportance
#define MI_UNSPECIFIED                                     0
#define MI_HIGH                                            1
#define MI_NORMAL                                          2
#define MI_LOW                                             3

//EmailRecipientTypes
#define RT_TO                                              0
#define RT_CC                                              1
#define RT_BCC                                             2

//TPriority
#define EP_UNSPECIFIED                                     0
#define EP_NORMAL                                          1
#define EP_URGENT                                          2
#define EP_NON_URGENT                                      3

//TSensitivity
#define ES_UNSPECIFIED                                     0
#define ES_PERSONAL                                        1
#define ES_PRIVATE                                         2
#define ES_COMPANY_CONFIDENTIAL                            3

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


extern "C" void* IPWORKS_CALL IPWorks_HTMLMailer_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_HTMLMailer_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_HTMLMailer_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_HTMLMailer_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} HTMLMailerConnectionStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} HTMLMailerEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} HTMLMailerErrorEventParams;

typedef struct {
  INT Direction;
  LPCWSTR Message;
  INT reserved;
} HTMLMailerPITrailEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} HTMLMailerSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} HTMLMailerSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} HTMLMailerStartTransferEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  INT reserved;
} HTMLMailerTransferEventParams;


class HTMLMailer {
  public: // Events
    virtual INT FireConnectionStatus(HTMLMailerConnectionStatusEventParams *e) {return 0;}
    virtual INT FireEndTransfer(HTMLMailerEndTransferEventParams *e) {return 0;}
    virtual INT FireError(HTMLMailerErrorEventParams *e) {return 0;}
    virtual INT FirePITrail(HTMLMailerPITrailEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(HTMLMailerSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(HTMLMailerSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(HTMLMailerStartTransferEventParams *e) {return 0;}
    virtual INT FireTransfer(HTMLMailerTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL HTMLMailerEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          HTMLMailerConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((HTMLMailer*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          HTMLMailerEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((HTMLMailer*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 3: {
          HTMLMailerErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((HTMLMailer*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          HTMLMailerPITrailEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((HTMLMailer*)lpObj)->FirePITrail(&e);
          break;
        }
        case 5: {
          HTMLMailerSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((HTMLMailer*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 6: {
          HTMLMailerSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((HTMLMailer*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 7: {
          HTMLMailerStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((HTMLMailer*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 8: {
          HTMLMailerTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], 0};
          ret_code = ((HTMLMailer*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    HTMLMailer(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_42) {
      m_pObj = IPWorks_HTMLMailer_Create(HTMLMailerEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~HTMLMailer() {
      IPWorks_HTMLMailer_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_HTMLMailer_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_HTMLMailer_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_HTMLMailer_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_HTMLMailer_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_HTMLMailer_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetAttachmentCount() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 1, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAttachmentCount(INT iAttachmentCount) {
      LPVOID val = (LPVOID)(iAttachmentCount);
      return IPWorks_HTMLMailer_Set(m_pObj, 1, 0, val, 0);
    }

    inline LPWSTR GetAttachmentFile(INT iAttachmentIndex) {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 2+10000, iAttachmentIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAttachmentFile(INT iAttachmentIndex, LPCWSTR lpszAttachmentFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 2+10000, iAttachmentIndex, (LPVOID)lpszAttachmentFile, 0);
    }

    inline LPWSTR GetAttachmentName(INT iAttachmentIndex) {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 3+10000, iAttachmentIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAttachmentName(INT iAttachmentIndex, LPCWSTR lpszAttachmentName) {
      return IPWorks_HTMLMailer_Set(m_pObj, 3+10000, iAttachmentIndex, (LPVOID)lpszAttachmentName, 0);
    }

    inline INT GetAuthMechanism() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthMechanism(INT iAuthMechanism) {
      LPVOID val = (LPVOID)(iAuthMechanism);
      return IPWorks_HTMLMailer_Set(m_pObj, 4, 0, val, 0);
    }

    inline LPWSTR GetBCc() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetBCc(LPCWSTR lpszBCc) {
      return IPWorks_HTMLMailer_Set(m_pObj, 5+10000, 0, (LPVOID)lpszBCc, 0);
    }

    inline LPWSTR GetCc() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCc(LPCWSTR lpszCc) {
      return IPWorks_HTMLMailer_Set(m_pObj, 6+10000, 0, (LPVOID)lpszCc, 0);
    }

    inline INT SetCommand(LPCWSTR lpszCommand) {
      return IPWorks_HTMLMailer_Set(m_pObj, 7+10000, 0, (LPVOID)lpszCommand, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 8, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_HTMLMailer_Set(m_pObj, 8, 0, val, 0);
    }

    inline LPWSTR GetDeliveryNotificationTo() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDeliveryNotificationTo(LPCWSTR lpszDeliveryNotificationTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 9+10000, 0, (LPVOID)lpszDeliveryNotificationTo, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 10, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_HTMLMailer_Set(m_pObj, 10, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 11, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_HTMLMailer_Set(m_pObj, 11, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_HTMLMailer_Set(m_pObj, 12+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 13+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 14, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_HTMLMailer_Set(m_pObj, 14, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_HTMLMailer_Set(m_pObj, 15+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline LPWSTR GetFrom() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFrom(LPCWSTR lpszFrom) {
      return IPWorks_HTMLMailer_Set(m_pObj, 16+10000, 0, (LPVOID)lpszFrom, 0);
    }

    inline LPWSTR GetHTMLFile() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetHTMLFile(LPCWSTR lpszHTMLFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 17+10000, 0, (LPVOID)lpszHTMLFile, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 18, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline INT GetImageCount() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 19, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetImageCount(INT iImageCount) {
      LPVOID val = (LPVOID)(iImageCount);
      return IPWorks_HTMLMailer_Set(m_pObj, 19, 0, val, 0);
    }

    inline INT GetImageData(INT iImageIndex, LPSTR &lpImageData, INT &lenImageData) {
      lpImageData = (LPSTR)IPWorks_HTMLMailer_Get(m_pObj, 20, iImageIndex, &lenImageData, NULL);
      return lpImageData ? 0 : lenImageData;
    }
    inline INT SetImageData(INT iImageIndex, LPCSTR lpImageData, INT lenImageData) {
      return IPWorks_HTMLMailer_Set(m_pObj, 20, iImageIndex, (LPVOID)lpImageData, lenImageData);
    }

    inline LPWSTR GetImageFile(INT iImageIndex) {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 21+10000, iImageIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetImageFile(INT iImageIndex, LPCWSTR lpszImageFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 21+10000, iImageIndex, (LPVOID)lpszImageFile, 0);
    }

    inline LPWSTR GetImageId(INT iImageIndex) {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 22+10000, iImageIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetImageId(INT iImageIndex, LPCWSTR lpszImageId) {
      return IPWorks_HTMLMailer_Set(m_pObj, 22+10000, iImageIndex, (LPVOID)lpszImageId, 0);
    }

    inline LPWSTR GetImageType(INT iImageIndex) {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 23+10000, iImageIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetImageType(INT iImageIndex, LPCWSTR lpszImageType) {
      return IPWorks_HTMLMailer_Set(m_pObj, 23+10000, iImageIndex, (LPVOID)lpszImageType, 0);
    }

    inline INT GetImportance() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 24, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetImportance(INT iImportance) {
      LPVOID val = (LPVOID)(iImportance);
      return IPWorks_HTMLMailer_Set(m_pObj, 24, 0, val, 0);
    }

    inline LPWSTR GetLastReply() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_HTMLMailer_Set(m_pObj, 26+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetMailPort() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 27, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMailPort(INT iMailPort) {
      LPVOID val = (LPVOID)(iMailPort);
      return IPWorks_HTMLMailer_Set(m_pObj, 27, 0, val, 0);
    }

    inline LPWSTR GetMailServer() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 28+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMailServer(LPCWSTR lpszMailServer) {
      return IPWorks_HTMLMailer_Set(m_pObj, 28+10000, 0, (LPVOID)lpszMailServer, 0);
    }

    inline LPWSTR GetMessageDate() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageDate(LPCWSTR lpszMessageDate) {
      return IPWorks_HTMLMailer_Set(m_pObj, 29+10000, 0, (LPVOID)lpszMessageDate, 0);
    }

    inline LPWSTR GetMessageHTML() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 30+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageHTML(LPCWSTR lpszMessageHTML) {
      return IPWorks_HTMLMailer_Set(m_pObj, 30+10000, 0, (LPVOID)lpszMessageHTML, 0);
    }

    inline LPWSTR GetMessageId() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageId(LPCWSTR lpszMessageId) {
      return IPWorks_HTMLMailer_Set(m_pObj, 31+10000, 0, (LPVOID)lpszMessageId, 0);
    }

    inline INT GetMessageRecipientCount() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 32, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMessageRecipientCount(INT iMessageRecipientCount) {
      LPVOID val = (LPVOID)(iMessageRecipientCount);
      return IPWorks_HTMLMailer_Set(m_pObj, 32, 0, val, 0);
    }

    inline LPWSTR GetMessageRecipientAddress(INT iRecipientIndex) {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 33+10000, iRecipientIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageRecipientAddress(INT iRecipientIndex, LPCWSTR lpszMessageRecipientAddress) {
      return IPWorks_HTMLMailer_Set(m_pObj, 33+10000, iRecipientIndex, (LPVOID)lpszMessageRecipientAddress, 0);
    }

    inline LPWSTR GetMessageRecipientName(INT iRecipientIndex) {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 34+10000, iRecipientIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageRecipientName(INT iRecipientIndex, LPCWSTR lpszMessageRecipientName) {
      return IPWorks_HTMLMailer_Set(m_pObj, 34+10000, iRecipientIndex, (LPVOID)lpszMessageRecipientName, 0);
    }

    inline LPWSTR GetMessageRecipientOptions(INT iRecipientIndex) {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 35+10000, iRecipientIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageRecipientOptions(INT iRecipientIndex, LPCWSTR lpszMessageRecipientOptions) {
      return IPWorks_HTMLMailer_Set(m_pObj, 35+10000, iRecipientIndex, (LPVOID)lpszMessageRecipientOptions, 0);
    }

    inline INT GetMessageRecipientType(INT iRecipientIndex) {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 36, iRecipientIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMessageRecipientType(INT iRecipientIndex, INT iMessageRecipientType) {
      LPVOID val = (LPVOID)(iMessageRecipientType);
      return IPWorks_HTMLMailer_Set(m_pObj, 36, iRecipientIndex, val, 0);
    }

    inline LPWSTR GetMessageText() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 37+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageText(LPCWSTR lpszMessageText) {
      return IPWorks_HTMLMailer_Set(m_pObj, 37+10000, 0, (LPVOID)lpszMessageText, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 38+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_HTMLMailer_Set(m_pObj, 38+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline BOOL GetParseHTML() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 39, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetParseHTML(BOOL bParseHTML) {
      LPVOID val = (LPVOID)(bParseHTML);
      return IPWorks_HTMLMailer_Set(m_pObj, 39, 0, val, 0);
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 40+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 40+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetPriority() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 41, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetPriority(INT iPriority) {
      LPVOID val = (LPVOID)(iPriority);
      return IPWorks_HTMLMailer_Set(m_pObj, 41, 0, val, 0);
    }

    inline LPWSTR GetReadReceiptTo() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 42+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReadReceiptTo(LPCWSTR lpszReadReceiptTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 42+10000, 0, (LPVOID)lpszReadReceiptTo, 0);
    }

    inline LPWSTR GetReplyTo() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 43+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReplyTo(LPCWSTR lpszReplyTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 43+10000, 0, (LPVOID)lpszReplyTo, 0);
    }

    inline LPWSTR GetSendTo() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 44+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSendTo(LPCWSTR lpszSendTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 44+10000, 0, (LPVOID)lpszSendTo, 0);
    }

    inline INT GetSensitivity() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 45, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSensitivity(INT iSensitivity) {
      LPVOID val = (LPVOID)(iSensitivity);
      return IPWorks_HTMLMailer_Set(m_pObj, 45, 0, val, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_HTMLMailer_Get(m_pObj, 46, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_HTMLMailer_Set(m_pObj, 46, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_HTMLMailer_Get(m_pObj, 47, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_HTMLMailer_Set(m_pObj, 47, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_HTMLMailer_Get(m_pObj, 48, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_HTMLMailer_Set(m_pObj, 48, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 49+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 49+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 50, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_HTMLMailer_Set(m_pObj, 50, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 51+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_HTMLMailer_Set(m_pObj, 51+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 52, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_HTMLMailer_Set(m_pObj, 52, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_HTMLMailer_Get(m_pObj, 53, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 54, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_HTMLMailer_Set(m_pObj, 54, 0, val, 0);
    }

    inline LPWSTR GetSubject() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 55+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSubject(LPCWSTR lpszSubject) {
      return IPWorks_HTMLMailer_Set(m_pObj, 55+10000, 0, (LPVOID)lpszSubject, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 56, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_HTMLMailer_Set(m_pObj, 56, 0, val, 0);
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_HTMLMailer_Get(m_pObj, 57+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_HTMLMailer_Set(m_pObj, 57+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline INT AddAttachment(LPCWSTR lpszFileName) {
      LPVOID param[1+1] = {(LPVOID)lpszFileName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_HTMLMailer_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_HTMLMailer_Do(m_pObj, 3+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Connect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT ProcessQueue(LPCWSTR lpszQueueDir) {
      LPVOID param[1+1] = {(LPVOID)lpszQueueDir, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_HTMLMailer_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
    }

    inline LPWSTR Queue(LPCWSTR lpszQueueDir) {
      LPVOID param[1+1] = {(LPVOID)lpszQueueDir, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_HTMLMailer_Do(m_pObj, 9+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT ResetHeaders() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 11+10000, 0, param, cbparam, NULL);
    }

    inline INT Send() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
    }

    inline INT SetMessageHTMLStream(IPWorksStream* sMessageStream) {
      LPVOID param[1+1] = {(LPVOID)sMessageStream, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_HTMLMailer_Do(m_pObj, 13+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_HTMLMAILER_H_