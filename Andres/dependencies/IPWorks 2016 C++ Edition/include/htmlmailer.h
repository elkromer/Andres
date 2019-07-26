/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_HTMLMAILER_H_
#define _IPWORKS_HTMLMAILER_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//AuthMechanisms
#define AM_USER_PASSWORD                                   0
#define AM_CRAMMD5                                         1
#define AM_NTLM                                            2
#define AM_SASLPLAIN                                       4
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

//TSSLStartMode
#define SSL_AUTOMATIC                                      0
#define SSL_IMPLICIT                                       1
#define SSL_EXPLICIT                                       2
#define SSL_NONE                                           3


extern "C" void* IPWORKS_CALL IPWorks_HTMLMailer_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_HTMLMailer_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_HTMLMailer_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_HTMLMailer_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} HTMLMailerConnectionStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} HTMLMailerEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} HTMLMailerErrorEventParams;

typedef struct {
  int Direction;
  const char* Message;
  int reserved;
} HTMLMailerPITrailEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} HTMLMailerSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} HTMLMailerSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} HTMLMailerStartTransferEventParams;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  int reserved;
} HTMLMailerTransferEventParams;



class HTMLMailer {
  
  public: //events
  
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
      if (event_id > 10000) return ((HTMLMailer*)lpObj)->HTMLMailerEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            HTMLMailerConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((HTMLMailer*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 2: {
            HTMLMailerEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((HTMLMailer*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 3: {
            HTMLMailerErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((HTMLMailer*)lpObj)->FireError(&e);
            break;
         }
         case 4: {
            HTMLMailerPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((HTMLMailer*)lpObj)->FirePITrail(&e);
            break;
         }
         case 5: {
            HTMLMailerSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((HTMLMailer*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 6: {
            HTMLMailerSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((HTMLMailer*)lpObj)->FireSSLStatus(&e);
            break;
         }
         case 7: {
            HTMLMailerStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((HTMLMailer*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 8: {
            HTMLMailerTransferEventParams e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = ((HTMLMailer*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int HTMLMailerEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    HTMLMailer(char *lpOemKey = (char*)IPWORKS_OEMKEY_42) {
      m_pObj = IPWorks_HTMLMailer_Create(HTMLMailerEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~HTMLMailer() {
      IPWorks_HTMLMailer_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_HTMLMailer_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_HTMLMailer_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_HTMLMailer_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_HTMLMailer_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_HTMLMailer_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetAttachmentCount() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAttachmentCount(int iAttachmentCount) {
      void* val = (void*)IPW64CAST(iAttachmentCount);
      return IPWorks_HTMLMailer_Set(m_pObj, 1, 0, val, 0);
    }
    inline char* GetAttachmentFile(int iAttachmentIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 2, iAttachmentIndex, 0);
      return (char*)val;
    }

    inline int SetAttachmentFile(int iAttachmentIndex, const char *lpAttachmentFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 2, iAttachmentIndex, (void*)lpAttachmentFile, 0);
    }

    inline char* GetAttachmentName(int iAttachmentIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 3, iAttachmentIndex, 0);
      return (char*)val;
    }

    inline int SetAttachmentName(int iAttachmentIndex, const char *lpAttachmentName) {
      return IPWorks_HTMLMailer_Set(m_pObj, 3, iAttachmentIndex, (void*)lpAttachmentName, 0);
    }

    inline int GetAuthMechanism() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthMechanism(int iAuthMechanism) {
      void* val = (void*)IPW64CAST(iAuthMechanism);
      return IPWorks_HTMLMailer_Set(m_pObj, 4, 0, val, 0);
    }
    inline char* GetBCc() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetBCc(const char *lpBCc) {
      return IPWorks_HTMLMailer_Set(m_pObj, 5, 0, (void*)lpBCc, 0);
    }

    inline char* GetCc() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetCc(const char *lpCc) {
      return IPWorks_HTMLMailer_Set(m_pObj, 6, 0, (void*)lpCc, 0);
    }


    inline int SetCommand(const char *lpCommand) {
      return IPWorks_HTMLMailer_Set(m_pObj, 7, 0, (void*)lpCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_HTMLMailer_Set(m_pObj, 8, 0, val, 0);
    }
    inline char* GetDeliveryNotificationTo() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetDeliveryNotificationTo(const char *lpDeliveryNotificationTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 9, 0, (void*)lpDeliveryNotificationTo, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_HTMLMailer_Set(m_pObj, 10, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 11, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_HTMLMailer_Set(m_pObj, 11, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_HTMLMailer_Set(m_pObj, 12, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 13, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 14, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_HTMLMailer_Set(m_pObj, 14, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_HTMLMailer_Set(m_pObj, 15, 0, (void*)lpFirewallUser, 0);
    }

    inline char* GetFrom() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetFrom(const char *lpFrom) {
      return IPWorks_HTMLMailer_Set(m_pObj, 16, 0, (void*)lpFrom, 0);
    }

    inline char* GetHTMLFile() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetHTMLFile(const char *lpHTMLFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 17, 0, (void*)lpHTMLFile, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }

    inline int GetImageCount() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 19, 0, 0);
      return (int)(long)val;
    }
    inline int SetImageCount(int iImageCount) {
      void* val = (void*)IPW64CAST(iImageCount);
      return IPWorks_HTMLMailer_Set(m_pObj, 19, 0, val, 0);
    }
    inline int GetImageData(int iImageIndex, char *&lpImageData, int &lenImageData) {
      lpImageData = (char*)IPWorks_HTMLMailer_Get(m_pObj, 20, iImageIndex, &lenImageData);
      return lpImageData ? 0 : lenImageData;
    }

    inline int SetImageData(int iImageIndex, const char *lpImageData, int lenImageData) {
      return IPWorks_HTMLMailer_Set(m_pObj, 20, iImageIndex, (void*)lpImageData, lenImageData);
    }

    inline char* GetImageFile(int iImageIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 21, iImageIndex, 0);
      return (char*)val;
    }

    inline int SetImageFile(int iImageIndex, const char *lpImageFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 21, iImageIndex, (void*)lpImageFile, 0);
    }

    inline char* GetImageId(int iImageIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 22, iImageIndex, 0);
      return (char*)val;
    }

    inline int SetImageId(int iImageIndex, const char *lpImageId) {
      return IPWorks_HTMLMailer_Set(m_pObj, 22, iImageIndex, (void*)lpImageId, 0);
    }

    inline char* GetImageType(int iImageIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 23, iImageIndex, 0);
      return (char*)val;
    }

    inline int SetImageType(int iImageIndex, const char *lpImageType) {
      return IPWorks_HTMLMailer_Set(m_pObj, 23, iImageIndex, (void*)lpImageType, 0);
    }

    inline int GetImportance() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 24, 0, 0);
      return (int)(long)val;
    }
    inline int SetImportance(int iImportance) {
      void* val = (void*)IPW64CAST(iImportance);
      return IPWorks_HTMLMailer_Set(m_pObj, 24, 0, val, 0);
    }
    inline char* GetLastReply() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }


    inline char* GetLocalHost() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_HTMLMailer_Set(m_pObj, 26, 0, (void*)lpLocalHost, 0);
    }

    inline int GetMailPort() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 27, 0, 0);
      return (int)(long)val;
    }
    inline int SetMailPort(int lMailPort) {
      void* val = (void*)IPW64CAST(lMailPort);
      return IPWorks_HTMLMailer_Set(m_pObj, 27, 0, val, 0);
    }
    inline char* GetMailServer() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }

    inline int SetMailServer(const char *lpMailServer) {
      return IPWorks_HTMLMailer_Set(m_pObj, 28, 0, (void*)lpMailServer, 0);
    }

    inline char* GetMessageDate() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 29, 0, 0);
      return (char*)val;
    }

    inline int SetMessageDate(const char *lpMessageDate) {
      return IPWorks_HTMLMailer_Set(m_pObj, 29, 0, (void*)lpMessageDate, 0);
    }

    inline char* GetMessageHTML() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 30, 0, 0);
      return (char*)val;
    }

    inline int SetMessageHTML(const char *lpMessageHTML) {
      return IPWorks_HTMLMailer_Set(m_pObj, 30, 0, (void*)lpMessageHTML, 0);
    }

    inline char* GetMessageId() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 31, 0, 0);
      return (char*)val;
    }

    inline int SetMessageId(const char *lpMessageId) {
      return IPWorks_HTMLMailer_Set(m_pObj, 31, 0, (void*)lpMessageId, 0);
    }

    inline int GetMessageRecipientCount() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 32, 0, 0);
      return (int)(long)val;
    }
    inline int SetMessageRecipientCount(int iMessageRecipientCount) {
      void* val = (void*)IPW64CAST(iMessageRecipientCount);
      return IPWorks_HTMLMailer_Set(m_pObj, 32, 0, val, 0);
    }
    inline char* GetMessageRecipientAddress(int iRecipientIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 33, iRecipientIndex, 0);
      return (char*)val;
    }

    inline int SetMessageRecipientAddress(int iRecipientIndex, const char *lpMessageRecipientAddress) {
      return IPWorks_HTMLMailer_Set(m_pObj, 33, iRecipientIndex, (void*)lpMessageRecipientAddress, 0);
    }

    inline char* GetMessageRecipientName(int iRecipientIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 34, iRecipientIndex, 0);
      return (char*)val;
    }

    inline int SetMessageRecipientName(int iRecipientIndex, const char *lpMessageRecipientName) {
      return IPWorks_HTMLMailer_Set(m_pObj, 34, iRecipientIndex, (void*)lpMessageRecipientName, 0);
    }

    inline char* GetMessageRecipientOptions(int iRecipientIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 35, iRecipientIndex, 0);
      return (char*)val;
    }

    inline int SetMessageRecipientOptions(int iRecipientIndex, const char *lpMessageRecipientOptions) {
      return IPWorks_HTMLMailer_Set(m_pObj, 35, iRecipientIndex, (void*)lpMessageRecipientOptions, 0);
    }

    inline int GetMessageRecipientType(int iRecipientIndex) {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 36, iRecipientIndex, 0);
      return (int)(long)val;
    }
    inline int SetMessageRecipientType(int iRecipientIndex, int iMessageRecipientType) {
      void* val = (void*)IPW64CAST(iMessageRecipientType);
      return IPWorks_HTMLMailer_Set(m_pObj, 36, iRecipientIndex, val, 0);
    }
    inline char* GetMessageText() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 37, 0, 0);
      return (char*)val;
    }

    inline int SetMessageText(const char *lpMessageText) {
      return IPWorks_HTMLMailer_Set(m_pObj, 37, 0, (void*)lpMessageText, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 38, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_HTMLMailer_Set(m_pObj, 38, 0, (void*)lpOtherHeaders, 0);
    }

    inline int GetParseHTML() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 39, 0, 0);
      return (int)(long)val;
    }
    inline int SetParseHTML(int bParseHTML) {
      void* val = (void*)IPW64CAST(bParseHTML);
      return IPWorks_HTMLMailer_Set(m_pObj, 39, 0, val, 0);
    }
    inline char* GetPassword() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 40, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 40, 0, (void*)lpPassword, 0);
    }

    inline int GetPriority() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 41, 0, 0);
      return (int)(long)val;
    }
    inline int SetPriority(int iPriority) {
      void* val = (void*)IPW64CAST(iPriority);
      return IPWorks_HTMLMailer_Set(m_pObj, 41, 0, val, 0);
    }
    inline char* GetReadReceiptTo() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 42, 0, 0);
      return (char*)val;
    }

    inline int SetReadReceiptTo(const char *lpReadReceiptTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 42, 0, (void*)lpReadReceiptTo, 0);
    }

    inline char* GetReplyTo() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 43, 0, 0);
      return (char*)val;
    }

    inline int SetReplyTo(const char *lpReplyTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 43, 0, (void*)lpReplyTo, 0);
    }

    inline char* GetSendTo() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 44, 0, 0);
      return (char*)val;
    }

    inline int SetSendTo(const char *lpSendTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 44, 0, (void*)lpSendTo, 0);
    }

    inline int GetSensitivity() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 45, 0, 0);
      return (int)(long)val;
    }
    inline int SetSensitivity(int iSensitivity) {
      void* val = (void*)IPW64CAST(iSensitivity);
      return IPWorks_HTMLMailer_Set(m_pObj, 45, 0, val, 0);
    }
    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_HTMLMailer_Get(m_pObj, 46, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_HTMLMailer_Set(m_pObj, 46, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_HTMLMailer_Get(m_pObj, 47, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_HTMLMailer_Set(m_pObj, 47, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_HTMLMailer_Get(m_pObj, 48, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_HTMLMailer_Set(m_pObj, 48, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 49, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 49, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 50, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_HTMLMailer_Set(m_pObj, 50, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 51, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_HTMLMailer_Set(m_pObj, 51, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 52, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_HTMLMailer_Set(m_pObj, 52, 0, val, 0);
    }
    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_HTMLMailer_Get(m_pObj, 53, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline int GetSSLStartMode() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 54, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_HTMLMailer_Set(m_pObj, 54, 0, val, 0);
    }
    inline char* GetSubject() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 55, 0, 0);
      return (char*)val;
    }

    inline int SetSubject(const char *lpSubject) {
      return IPWorks_HTMLMailer_Set(m_pObj, 55, 0, (void*)lpSubject, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 56, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_HTMLMailer_Set(m_pObj, 56, 0, val, 0);
    }
    inline char* GetUser() {
      void* val = IPWorks_HTMLMailer_Get(m_pObj, 57, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_HTMLMailer_Set(m_pObj, 57, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline int AddAttachment(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_HTMLMailer_Do(m_pObj, 2, 1, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_HTMLMailer_Do(m_pObj, 3, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int ProcessQueue(const char* lpszQueueDir) {
      void *param[1+1] = {(void*)IPW64CAST(lpszQueueDir), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_HTMLMailer_Do(m_pObj, 8, 1, param, cbparam);
      
      
    }
    inline char* Queue(const char* lpszQueueDir) {
      void *param[1+1] = {(void*)IPW64CAST(lpszQueueDir), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_HTMLMailer_Do(m_pObj, 9, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }
    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} HTMLMailerConnectionStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} HTMLMailerEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} HTMLMailerErrorEventParamsW;

typedef struct {
  int Direction;
  LPWSTR Message;
  int reserved;
} HTMLMailerPITrailEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} HTMLMailerSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} HTMLMailerSSLStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} HTMLMailerStartTransferEventParamsW;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  int reserved;
} HTMLMailerTransferEventParamsW;



class HTMLMailerW : public HTMLMailer {

  public: //properties
  


    inline LPWSTR GetAttachmentFile(int iAttachmentIndex) {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+2, iAttachmentIndex, 0);
    }

    inline int SetAttachmentFile(int iAttachmentIndex, LPCWSTR lpAttachmentFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+2, iAttachmentIndex, (void*)lpAttachmentFile, 0);
    }

    inline LPWSTR GetAttachmentName(int iAttachmentIndex) {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+3, iAttachmentIndex, 0);
    }

    inline int SetAttachmentName(int iAttachmentIndex, LPCWSTR lpAttachmentName) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+3, iAttachmentIndex, (void*)lpAttachmentName, 0);
    }



    inline LPWSTR GetBCc() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetBCc(LPCWSTR lpBCc) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+5, 0, (void*)lpBCc, 0);
    }

    inline LPWSTR GetCc() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetCc(LPCWSTR lpCc) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+6, 0, (void*)lpCc, 0);
    }



    inline int SetCommand(LPCWSTR lpCommand) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+7, 0, (void*)lpCommand, 0);
    }



    inline LPWSTR GetDeliveryNotificationTo() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetDeliveryNotificationTo(LPCWSTR lpDeliveryNotificationTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+9, 0, (void*)lpDeliveryNotificationTo, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+12, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+13, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+15, 0, (void*)lpFirewallUser, 0);
    }

    inline LPWSTR GetFrom() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetFrom(LPCWSTR lpFrom) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+16, 0, (void*)lpFrom, 0);
    }

    inline LPWSTR GetHTMLFile() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetHTMLFile(LPCWSTR lpHTMLFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+17, 0, (void*)lpHTMLFile, 0);
    }





    inline LPWSTR GetImageData(int iImageIndex) {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+20, iImageIndex, 0);
    }

    inline int SetImageData(int iImageIndex, LPCWSTR lpImageData) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+20, iImageIndex, (void*)lpImageData, 0);
    }
    inline int GetImageDataB(int iImageIndex, char *&lpImageData, int &lenImageData) {
      lpImageData = (char*)IPWorks_HTMLMailer_Get(m_pObj, 20, iImageIndex, &lenImageData);
      return lpImageData ? 0 : lenImageData;
    }
    inline int SetImageDataB(int iImageIndex, const char *lpImageData, int lenImageData) {
      return IPWorks_HTMLMailer_Set(m_pObj, 20, iImageIndex, (void*)lpImageData, lenImageData);
    }
    inline LPWSTR GetImageFile(int iImageIndex) {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+21, iImageIndex, 0);
    }

    inline int SetImageFile(int iImageIndex, LPCWSTR lpImageFile) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+21, iImageIndex, (void*)lpImageFile, 0);
    }

    inline LPWSTR GetImageId(int iImageIndex) {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+22, iImageIndex, 0);
    }

    inline int SetImageId(int iImageIndex, LPCWSTR lpImageId) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+22, iImageIndex, (void*)lpImageId, 0);
    }

    inline LPWSTR GetImageType(int iImageIndex) {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+23, iImageIndex, 0);
    }

    inline int SetImageType(int iImageIndex, LPCWSTR lpImageType) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+23, iImageIndex, (void*)lpImageType, 0);
    }



    inline LPWSTR GetLastReply() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+25, 0, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+26, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+26, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetMailServer() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+28, 0, 0);
    }

    inline int SetMailServer(LPCWSTR lpMailServer) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+28, 0, (void*)lpMailServer, 0);
    }

    inline LPWSTR GetMessageDate() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+29, 0, 0);
    }

    inline int SetMessageDate(LPCWSTR lpMessageDate) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+29, 0, (void*)lpMessageDate, 0);
    }

    inline LPWSTR GetMessageHTML() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+30, 0, 0);
    }

    inline int SetMessageHTML(LPCWSTR lpMessageHTML) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+30, 0, (void*)lpMessageHTML, 0);
    }

    inline LPWSTR GetMessageId() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+31, 0, 0);
    }

    inline int SetMessageId(LPCWSTR lpMessageId) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+31, 0, (void*)lpMessageId, 0);
    }



    inline LPWSTR GetMessageRecipientAddress(int iRecipientIndex) {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+33, iRecipientIndex, 0);
    }

    inline int SetMessageRecipientAddress(int iRecipientIndex, LPCWSTR lpMessageRecipientAddress) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+33, iRecipientIndex, (void*)lpMessageRecipientAddress, 0);
    }

    inline LPWSTR GetMessageRecipientName(int iRecipientIndex) {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+34, iRecipientIndex, 0);
    }

    inline int SetMessageRecipientName(int iRecipientIndex, LPCWSTR lpMessageRecipientName) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+34, iRecipientIndex, (void*)lpMessageRecipientName, 0);
    }

    inline LPWSTR GetMessageRecipientOptions(int iRecipientIndex) {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+35, iRecipientIndex, 0);
    }

    inline int SetMessageRecipientOptions(int iRecipientIndex, LPCWSTR lpMessageRecipientOptions) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+35, iRecipientIndex, (void*)lpMessageRecipientOptions, 0);
    }



    inline LPWSTR GetMessageText() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+37, 0, 0);
    }

    inline int SetMessageText(LPCWSTR lpMessageText) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+37, 0, (void*)lpMessageText, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+38, 0, 0);
    }

    inline int SetOtherHeaders(LPCWSTR lpOtherHeaders) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+38, 0, (void*)lpOtherHeaders, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+40, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+40, 0, (void*)lpPassword, 0);
    }



    inline LPWSTR GetReadReceiptTo() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+42, 0, 0);
    }

    inline int SetReadReceiptTo(LPCWSTR lpReadReceiptTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+42, 0, (void*)lpReadReceiptTo, 0);
    }

    inline LPWSTR GetReplyTo() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+43, 0, 0);
    }

    inline int SetReplyTo(LPCWSTR lpReplyTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+43, 0, (void*)lpReplyTo, 0);
    }

    inline LPWSTR GetSendTo() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+44, 0, 0);
    }

    inline int SetSendTo(LPCWSTR lpSendTo) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+44, 0, (void*)lpSendTo, 0);
    }



    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+46, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+46, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_HTMLMailer_Get(m_pObj, 46, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_HTMLMailer_Set(m_pObj, 46, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+47, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+47, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_HTMLMailer_Get(m_pObj, 47, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_HTMLMailer_Set(m_pObj, 47, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+48, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+48, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_HTMLMailer_Get(m_pObj, 48, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_HTMLMailer_Set(m_pObj, 48, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+49, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+49, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+51, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+51, 0, (void*)lpSSLCertSubject, 0);
    }



    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+53, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_HTMLMailer_Get(m_pObj, 53, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }



    inline LPWSTR GetSubject() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+55, 0, 0);
    }

    inline int SetSubject(LPCWSTR lpSubject) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+55, 0, (void*)lpSubject, 0);
    }



    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_HTMLMailer_Get(m_pObj, 10000+57, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_HTMLMailer_Set(m_pObj, 10000+57, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnectionStatus(HTMLMailerConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(HTMLMailerEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(HTMLMailerErrorEventParamsW *e) {return 0;}
    virtual int FirePITrail(HTMLMailerPITrailEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(HTMLMailerSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(HTMLMailerSSLStatusEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(HTMLMailerStartTransferEventParamsW *e) {return 0;}
    virtual int FireTransfer(HTMLMailerTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int HTMLMailerEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            HTMLMailerConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 2: {
            HTMLMailerEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 3: {
            HTMLMailerErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 4: {
            HTMLMailerPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }
         case 5: {
            HTMLMailerSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 6: {
            HTMLMailerSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }
         case 7: {
            HTMLMailerStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 8: {
            HTMLMailerTransferEventParamsW e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnectionStatus(HTMLMailerConnectionStatusEventParams *e) {return -10000;}
    virtual int FireEndTransfer(HTMLMailerEndTransferEventParams *e) {return -10000;}
    virtual int FireError(HTMLMailerErrorEventParams *e) {return -10000;}
    virtual int FirePITrail(HTMLMailerPITrailEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(HTMLMailerSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(HTMLMailerSSLStatusEventParams *e) {return -10000;}
    virtual int FireStartTransfer(HTMLMailerStartTransferEventParams *e) {return -10000;}
    virtual int FireTransfer(HTMLMailerTransferEventParams *e) {return -10000;}

  public: //methods

    inline int AddAttachment(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10000+2, 1, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_HTMLMailer_Do(m_pObj, 10000+3, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int ProcessQueue(LPWSTR lpszQueueDir) {
      void *param[1+1] = {(void*)lpszQueueDir, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10000+8, 1, param, cbparam);
      
    }
    inline LPWSTR Queue(LPWSTR lpszQueueDir) {
      void *param[1+1] = {(void*)lpszQueueDir, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_HTMLMailer_Do(m_pObj, 10000+9, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }
    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_HTMLMailer_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_HTMLMAILER_H_




