/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_HTMLMailer_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_HTMLMailer_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_HTMLMailer_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} HTMLMailerConnectionStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} HTMLMailerEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} HTMLMailerErrorEventParams;

typedef struct {
  int Direction;
  const char *Message;
  int reserved;
} HTMLMailerPITrailEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} HTMLMailerSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} HTMLMailerSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} HTMLMailerStartTransferEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  int reserved;
} HTMLMailerTransferEventParams;


class HTMLMailer {
  public: // Events
    virtual int FireConnectionStatus(HTMLMailerConnectionStatusEventParams *e) {return 0;}
    virtual int FireEndTransfer(HTMLMailerEndTransferEventParams *e) {return 0;}
    virtual int FireError(HTMLMailerErrorEventParams *e) {return 0;}
    virtual int FirePITrail(HTMLMailerPITrailEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(HTMLMailerSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(HTMLMailerSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(HTMLMailerStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(HTMLMailerTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL HTMLMailerEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          HTMLMailerConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((HTMLMailer*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          HTMLMailerEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((HTMLMailer*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 3: {
          HTMLMailerErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((HTMLMailer*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          HTMLMailerPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((HTMLMailer*)lpObj)->FirePITrail(&e);
          break;
        }
        case 5: {
          HTMLMailerSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((HTMLMailer*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 6: {
          HTMLMailerSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((HTMLMailer*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 7: {
          HTMLMailerStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((HTMLMailer*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 8: {
          HTMLMailerTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), 0};
          ret_code = ((HTMLMailer*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    HTMLMailer(char *lpOemKey = (char*)IPWORKS_OEMKEY_42) {
      m_pObj = IPWorks_HTMLMailer_Create(HTMLMailerEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~HTMLMailer() {
      IPWorks_HTMLMailer_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_HTMLMailer_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_HTMLMailer_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_HTMLMailer_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_HTMLMailer_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_HTMLMailer_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetAttachmentCount() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAttachmentCount(int iAttachmentCount) {
      void* val = (void*)IPW64CAST(iAttachmentCount);
      return IPWorks_HTMLMailer_Set(m_pObj, 1, 0, val, 0);
    }

    inline char* GetAttachmentFile(int iAttachmentIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 2, iAttachmentIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetAttachmentFile(int iAttachmentIndex, const char* lpszAttachmentFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 2, iAttachmentIndex, (void*)lpszAttachmentFile, 0);
    }

    inline char* GetAttachmentName(int iAttachmentIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 3, iAttachmentIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetAttachmentName(int iAttachmentIndex, const char* lpszAttachmentName) {
      return IPWorks_HTMLMailer_Set(m_pObj, 3, iAttachmentIndex, (void*)lpszAttachmentName, 0);
    }

    inline int GetAuthMechanism() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthMechanism(int iAuthMechanism) {
      void* val = (void*)IPW64CAST(iAuthMechanism);
      return IPWorks_HTMLMailer_Set(m_pObj, 4, 0, val, 0);
    }

    inline char* GetBCc() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetBCc(const char* lpszBCc) {
      return IPWorks_HTMLMailer_Set(m_pObj, 5, 0, (void*)lpszBCc, 0);
    }

    inline char* GetCc() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCc(const char* lpszCc) {
      return IPWorks_HTMLMailer_Set(m_pObj, 6, 0, (void*)lpszCc, 0);
    }

    inline int SetCommand(const char* lpszCommand) {
      return IPWorks_HTMLMailer_Set(m_pObj, 7, 0, (void*)lpszCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 8, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_HTMLMailer_Set(m_pObj, 8, 0, val, 0);
    }

    inline char* GetDeliveryNotificationTo() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 9, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetDeliveryNotificationTo(const char* lpszDeliveryNotificationTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 9, 0, (void*)lpszDeliveryNotificationTo, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_HTMLMailer_Set(m_pObj, 10, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 11, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_HTMLMailer_Set(m_pObj, 11, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_HTMLMailer_Set(m_pObj, 12, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 13, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 14, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_HTMLMailer_Set(m_pObj, 14, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_HTMLMailer_Set(m_pObj, 15, 0, (void*)lpszFirewallUser, 0);
    }

    inline char* GetFrom() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFrom(const char* lpszFrom) {
      return IPWorks_HTMLMailer_Set(m_pObj, 16, 0, (void*)lpszFrom, 0);
    }

    inline char* GetHTMLFile() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetHTMLFile(const char* lpszHTMLFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 17, 0, (void*)lpszHTMLFile, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 18, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetImageCount() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 19, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetImageCount(int iImageCount) {
      void* val = (void*)IPW64CAST(iImageCount);
      return IPWorks_HTMLMailer_Set(m_pObj, 19, 0, val, 0);
    }

    inline int GetImageData(int iImageIndex, char* &lpImageData, int &lenImageData) {
      lpImageData = (char*)IPWorks_HTMLMailer_Get(m_pObj, 20, iImageIndex, &lenImageData, NULL);
      return lpImageData ? 0 : lenImageData;
    }
    inline int SetImageData(int iImageIndex, const char* lpImageData, int lenImageData) {
      return IPWorks_HTMLMailer_Set(m_pObj, 20, iImageIndex, (void*)lpImageData, lenImageData);
    }

    inline char* GetImageFile(int iImageIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 21, iImageIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetImageFile(int iImageIndex, const char* lpszImageFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 21, iImageIndex, (void*)lpszImageFile, 0);
    }

    inline char* GetImageId(int iImageIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 22, iImageIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetImageId(int iImageIndex, const char* lpszImageId) {
      return IPWorks_HTMLMailer_Set(m_pObj, 22, iImageIndex, (void*)lpszImageId, 0);
    }

    inline char* GetImageType(int iImageIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 23, iImageIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetImageType(int iImageIndex, const char* lpszImageType) {
      return IPWorks_HTMLMailer_Set(m_pObj, 23, iImageIndex, (void*)lpszImageType, 0);
    }

    inline int GetImportance() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 24, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetImportance(int iImportance) {
      void* val = (void*)IPW64CAST(iImportance);
      return IPWorks_HTMLMailer_Set(m_pObj, 24, 0, val, 0);
    }

    inline char* GetLastReply() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 25, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_HTMLMailer_Set(m_pObj, 26, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetMailPort() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 27, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMailPort(int iMailPort) {
      void* val = (void*)IPW64CAST(iMailPort);
      return IPWorks_HTMLMailer_Set(m_pObj, 27, 0, val, 0);
    }

    inline char* GetMailServer() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 28, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMailServer(const char* lpszMailServer) {
      return IPWorks_HTMLMailer_Set(m_pObj, 28, 0, (void*)lpszMailServer, 0);
    }

    inline char* GetMessageDate() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 29, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageDate(const char* lpszMessageDate) {
      return IPWorks_HTMLMailer_Set(m_pObj, 29, 0, (void*)lpszMessageDate, 0);
    }

    inline char* GetMessageHTML() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 30, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageHTML(const char* lpszMessageHTML) {
      return IPWorks_HTMLMailer_Set(m_pObj, 30, 0, (void*)lpszMessageHTML, 0);
    }

    inline char* GetMessageId() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 31, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageId(const char* lpszMessageId) {
      return IPWorks_HTMLMailer_Set(m_pObj, 31, 0, (void*)lpszMessageId, 0);
    }

    inline int GetMessageRecipientCount() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 32, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMessageRecipientCount(int iMessageRecipientCount) {
      void* val = (void*)IPW64CAST(iMessageRecipientCount);
      return IPWorks_HTMLMailer_Set(m_pObj, 32, 0, val, 0);
    }

    inline char* GetMessageRecipientAddress(int iRecipientIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 33, iRecipientIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageRecipientAddress(int iRecipientIndex, const char* lpszMessageRecipientAddress) {
      return IPWorks_HTMLMailer_Set(m_pObj, 33, iRecipientIndex, (void*)lpszMessageRecipientAddress, 0);
    }

    inline char* GetMessageRecipientName(int iRecipientIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 34, iRecipientIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageRecipientName(int iRecipientIndex, const char* lpszMessageRecipientName) {
      return IPWorks_HTMLMailer_Set(m_pObj, 34, iRecipientIndex, (void*)lpszMessageRecipientName, 0);
    }

    inline char* GetMessageRecipientOptions(int iRecipientIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 35, iRecipientIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageRecipientOptions(int iRecipientIndex, const char* lpszMessageRecipientOptions) {
      return IPWorks_HTMLMailer_Set(m_pObj, 35, iRecipientIndex, (void*)lpszMessageRecipientOptions, 0);
    }

    inline int GetMessageRecipientType(int iRecipientIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 36, iRecipientIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMessageRecipientType(int iRecipientIndex, int iMessageRecipientType) {
      void* val = (void*)IPW64CAST(iMessageRecipientType);
      return IPWorks_HTMLMailer_Set(m_pObj, 36, iRecipientIndex, val, 0);
    }

    inline char* GetMessageText() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 37, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageText(const char* lpszMessageText) {
      return IPWorks_HTMLMailer_Set(m_pObj, 37, 0, (void*)lpszMessageText, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 38, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherHeaders(const char* lpszOtherHeaders) {
      return IPWorks_HTMLMailer_Set(m_pObj, 38, 0, (void*)lpszOtherHeaders, 0);
    }

    inline int GetParseHTML() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 39, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetParseHTML(int bParseHTML) {
      void* val = (void*)IPW64CAST(bParseHTML);
      return IPWorks_HTMLMailer_Set(m_pObj, 39, 0, val, 0);
    }

    inline char* GetPassword() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 40, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 40, 0, (void*)lpszPassword, 0);
    }

    inline int GetPriority() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 41, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetPriority(int iPriority) {
      void* val = (void*)IPW64CAST(iPriority);
      return IPWorks_HTMLMailer_Set(m_pObj, 41, 0, val, 0);
    }

    inline char* GetReadReceiptTo() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 42, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReadReceiptTo(const char* lpszReadReceiptTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 42, 0, (void*)lpszReadReceiptTo, 0);
    }

    inline char* GetReplyTo() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 43, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReplyTo(const char* lpszReplyTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 43, 0, (void*)lpszReplyTo, 0);
    }

    inline char* GetSendTo() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 44, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSendTo(const char* lpszSendTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 44, 0, (void*)lpszSendTo, 0);
    }

    inline int GetSensitivity() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 45, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSensitivity(int iSensitivity) {
      void* val = (void*)IPW64CAST(iSensitivity);
      return IPWorks_HTMLMailer_Set(m_pObj, 45, 0, val, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_HTMLMailer_Get(m_pObj, 46, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_HTMLMailer_Set(m_pObj, 46, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_HTMLMailer_Get(m_pObj, 47, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_HTMLMailer_Set(m_pObj, 47, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_HTMLMailer_Get(m_pObj, 48, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_HTMLMailer_Set(m_pObj, 48, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 49, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 49, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 50, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_HTMLMailer_Set(m_pObj, 50, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 51, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_HTMLMailer_Set(m_pObj, 51, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 52, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_HTMLMailer_Set(m_pObj, 52, 0, val, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_HTMLMailer_Get(m_pObj, 53, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetSSLStartMode() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 54, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_HTMLMailer_Set(m_pObj, 54, 0, val, 0);
    }

    inline char* GetSubject() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 55, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSubject(const char* lpszSubject) {
      return IPWorks_HTMLMailer_Set(m_pObj, 55, 0, (void*)lpszSubject, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 56, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_HTMLMailer_Set(m_pObj, 56, 0, val, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 57, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_HTMLMailer_Set(m_pObj, 57, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline int AddAttachment(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_HTMLMailer_Do(m_pObj, 2, 1, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_HTMLMailer_Do(m_pObj, 3, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int ProcessQueue(const char* lpszQueueDir) {
      void *param[1+1] = {(void*)IPW64CAST(lpszQueueDir), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_HTMLMailer_Do(m_pObj, 8, 1, param, cbparam, NULL);
    }

    inline char* Queue(const char* lpszQueueDir) {
      void *param[1+1] = {(void*)IPW64CAST(lpszQueueDir), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_HTMLMailer_Do(m_pObj, 9, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 11, 0, param, cbparam, NULL);
    }

    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 12, 0, param, cbparam, NULL);
    }

    inline int SetMessageHTMLStream(IPWorksStream* sMessageStream) {
      void *param[1+1] = {(void*)IPW64CAST(sMessageStream), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_HTMLMailer_Do(m_pObj, 13, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_HTMLMAILER_H_
