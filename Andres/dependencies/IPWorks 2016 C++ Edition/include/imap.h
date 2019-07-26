/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_IMAP_H_
#define _IPWORKS_IMAP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//AuthMechanisms
#define AM_USER_PASSWORD                                   0
#define AM_CRAMMD5                                         1
#define AM_NTLM                                            2
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

//TSSLStartMode
#define SSL_AUTOMATIC                                      0
#define SSL_IMPLICIT                                       1
#define SSL_EXPLICIT                                       2
#define SSL_NONE                                           3


extern "C" void* IPWORKS_CALL IPWorks_IMAP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_IMAP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_IMAP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_StaticDestroy();

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
} IMAPConnectionStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} IMAPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} IMAPErrorEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} IMAPHeaderEventParams;

typedef struct {
  const char* Message;
  int Cancel;
  int reserved;
} IMAPIdleInfoEventParams;

typedef struct {
  const char* Mailbox;
  const char* User;
  const char* Rights;
  int reserved;
} IMAPMailboxACLEventParams;

typedef struct {
  const char* Mailbox;
  const char* Separator;
  const char* Flags;
  int reserved;
} IMAPMailboxListEventParams;

typedef struct {
  const char* MessageId;
  const char* Subject;
  const char* MessageDate;
  const char* From;
  const char* Flags;
  ns_int64 Size;
  int reserved;
} IMAPMessageInfoEventParams;

typedef struct {
  const char* PartId;
  ns_int64 Size;
  const char* ContentType;
  const char* Filename;
  const char* ContentEncoding;
  const char* Parameters;
  const char* MultipartMode;
  const char* ContentId;
  const char* ContentDisposition;
  int reserved;
} IMAPMessagePartEventParams;

typedef struct {
  int Direction;
  const char* Message;
  int reserved;
} IMAPPITrailEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} IMAPSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} IMAPSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} IMAPStartTransferEventParams;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  const char* Text;
  int reserved;
} IMAPTransferEventParams;



class IMAP {
  
  public: //events
  
    virtual int FireConnectionStatus(IMAPConnectionStatusEventParams *e) {return 0;}
    virtual int FireEndTransfer(IMAPEndTransferEventParams *e) {return 0;}
    virtual int FireError(IMAPErrorEventParams *e) {return 0;}
    virtual int FireHeader(IMAPHeaderEventParams *e) {return 0;}
    virtual int FireIdleInfo(IMAPIdleInfoEventParams *e) {return 0;}
    virtual int FireMailboxACL(IMAPMailboxACLEventParams *e) {return 0;}
    virtual int FireMailboxList(IMAPMailboxListEventParams *e) {return 0;}
    virtual int FireMessageInfo(IMAPMessageInfoEventParams *e) {return 0;}
    virtual int FireMessagePart(IMAPMessagePartEventParams *e) {return 0;}
    virtual int FirePITrail(IMAPPITrailEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(IMAPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(IMAPSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(IMAPStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(IMAPTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL IMAPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((IMAP*)lpObj)->IMAPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            IMAPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((IMAP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 2: {
            IMAPEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((IMAP*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 3: {
            IMAPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((IMAP*)lpObj)->FireError(&e);
            break;
         }
         case 4: {
            IMAPHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((IMAP*)lpObj)->FireHeader(&e);
            break;
         }
         case 5: {
            IMAPIdleInfoEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = ((IMAP*)lpObj)->FireIdleInfo(&e);
            param[1] = (void*)IPW64CAST(e.Cancel);
            break;
         }
         case 6: {
            IMAPMailboxACLEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((IMAP*)lpObj)->FireMailboxACL(&e);
            break;
         }
         case 7: {
            IMAPMailboxListEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((IMAP*)lpObj)->FireMailboxList(&e);
            break;
         }
         case 8: {
            IMAPMessageInfoEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), *(ns_int64*)IPW64CAST(param[5]),  0};
            ret_code = ((IMAP*)lpObj)->FireMessageInfo(&e);
            break;
         }
         case 9: {
            IMAPMessagePartEventParams e = {(char*)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), (char*)IPW64CAST(param[7]), (char*)IPW64CAST(param[8]),  0};
            ret_code = ((IMAP*)lpObj)->FireMessagePart(&e);
            break;
         }
         case 10: {
            IMAPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((IMAP*)lpObj)->FirePITrail(&e);
            break;
         }
         case 11: {
            IMAPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((IMAP*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 12: {
            IMAPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((IMAP*)lpObj)->FireSSLStatus(&e);
            break;
         }
         case 13: {
            IMAPStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((IMAP*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 14: {
            IMAPTransferEventParams e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]),  0};
            ret_code = ((IMAP*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int IMAPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    IMAP(char *lpOemKey = (char*)IPWORKS_OEMKEY_31) {
      m_pObj = IPWorks_IMAP_Create(IMAPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~IMAP() {
      IPWorks_IMAP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_IMAP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_IMAP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_IMAP_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_IMAP_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_IMAP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetAuthMechanism() {
      void* val = IPWorks_IMAP_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthMechanism(int iAuthMechanism) {
      void* val = (void*)IPW64CAST(iAuthMechanism);
      return IPWorks_IMAP_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetAutoDecodeParts() {
      void* val = IPWorks_IMAP_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }
    inline int SetAutoDecodeParts(int bAutoDecodeParts) {
      void* val = (void*)IPW64CAST(bAutoDecodeParts);
      return IPWorks_IMAP_Set(m_pObj, 2, 0, val, 0);
    }

    inline int SetCommand(const char *lpCommand) {
      return IPWorks_IMAP_Set(m_pObj, 3, 0, (void*)lpCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_IMAP_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_IMAP_Set(m_pObj, 4, 0, val, 0);
    }
    inline ns_int64 GetEndByte() {
      ns_int64 *pval = (ns_int64*)IPWorks_IMAP_Get(m_pObj, 5, 0, 0);
      return *pval;
    }

    inline int SetEndByte(ns_int64 lEndByte) {
      void* val = (void*)(&lEndByte);
      return IPWorks_IMAP_Set(m_pObj, 5, 0, val, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_IMAP_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_IMAP_Set(m_pObj, 6, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_IMAP_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_IMAP_Set(m_pObj, 7, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_IMAP_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_IMAP_Set(m_pObj, 8, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_IMAP_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_IMAP_Set(m_pObj, 9, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_IMAP_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_IMAP_Set(m_pObj, 10, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_IMAP_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_IMAP_Set(m_pObj, 11, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_IMAP_Get(m_pObj, 12, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLastReply() {
      void* val = IPWorks_IMAP_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }


    inline char* GetLocalFile() {
      void* val = IPWorks_IMAP_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_IMAP_Set(m_pObj, 14, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_IMAP_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_IMAP_Set(m_pObj, 15, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetMailbox() {
      void* val = IPWorks_IMAP_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetMailbox(const char *lpMailbox) {
      return IPWorks_IMAP_Set(m_pObj, 16, 0, (void*)lpMailbox, 0);
    }

    inline char* GetMailboxFlags() {
      void* val = IPWorks_IMAP_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }


    inline int GetMailboxListCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }

    inline char* GetMailboxListFlags(int iMailboxListIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 19, iMailboxListIndex, 0);
      return (char*)val;
    }


    inline char* GetMailboxListName(int iMailboxListIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 20, iMailboxListIndex, 0);
      return (char*)val;
    }


    inline char* GetMailboxListSeparator(int iMailboxListIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 21, iMailboxListIndex, 0);
      return (char*)val;
    }


    inline int GetMailPort() {
      void* val = IPWorks_IMAP_Get(m_pObj, 22, 0, 0);
      return (int)(long)val;
    }
    inline int SetMailPort(int lMailPort) {
      void* val = (void*)IPW64CAST(lMailPort);
      return IPWorks_IMAP_Set(m_pObj, 22, 0, val, 0);
    }
    inline char* GetMailServer() {
      void* val = IPWorks_IMAP_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }

    inline int SetMailServer(const char *lpMailServer) {
      return IPWorks_IMAP_Set(m_pObj, 23, 0, (void*)lpMailServer, 0);
    }

    inline int GetMessage(char *&lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_IMAP_Get(m_pObj, 24, 0, &lenMessage);
      return lpMessage ? 0 : lenMessage;
    }

    inline int SetMessage(const char *lpMessage, int lenMessage) {
      return IPWorks_IMAP_Set(m_pObj, 24, 0, (void*)lpMessage, lenMessage);
    }

    inline char* GetMessageContentEncoding() {
      void* val = IPWorks_IMAP_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageContentType() {
      void* val = IPWorks_IMAP_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }


    inline int GetMessageCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 27, 0, 0);
      return (int)(long)val;
    }

    inline char* GetMessageDate() {
      void* val = IPWorks_IMAP_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageDeliveryTime() {
      void* val = IPWorks_IMAP_Get(m_pObj, 29, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageFlags() {
      void* val = IPWorks_IMAP_Get(m_pObj, 30, 0, 0);
      return (char*)val;
    }

    inline int SetMessageFlags(const char *lpMessageFlags) {
      return IPWorks_IMAP_Set(m_pObj, 30, 0, (void*)lpMessageFlags, 0);
    }

    inline char* GetMessageFrom() {
      void* val = IPWorks_IMAP_Get(m_pObj, 31, 0, 0);
      return (char*)val;
    }


    inline int GetMessageHeaderCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 32, 0, 0);
      return (int)(long)val;
    }
    inline int SetMessageHeaderCount(int iMessageHeaderCount) {
      void* val = (void*)IPW64CAST(iMessageHeaderCount);
      return IPWorks_IMAP_Set(m_pObj, 32, 0, val, 0);
    }
    inline char* GetMessageHeaderField(int iMessageHeaderIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 33, iMessageHeaderIndex, 0);
      return (char*)val;
    }

    inline int SetMessageHeaderField(int iMessageHeaderIndex, const char *lpMessageHeaderField) {
      return IPWorks_IMAP_Set(m_pObj, 33, iMessageHeaderIndex, (void*)lpMessageHeaderField, 0);
    }

    inline char* GetMessageHeaderValue(int iMessageHeaderIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 34, iMessageHeaderIndex, 0);
      return (char*)val;
    }

    inline int SetMessageHeaderValue(int iMessageHeaderIndex, const char *lpMessageHeaderValue) {
      return IPWorks_IMAP_Set(m_pObj, 34, iMessageHeaderIndex, (void*)lpMessageHeaderValue, 0);
    }

    inline char* GetMessageHeadersString() {
      void* val = IPWorks_IMAP_Get(m_pObj, 35, 0, 0);
      return (char*)val;
    }

    inline int SetMessageHeadersString(const char *lpMessageHeadersString) {
      return IPWorks_IMAP_Set(m_pObj, 35, 0, (void*)lpMessageHeadersString, 0);
    }

    inline char* GetMessageId() {
      void* val = IPWorks_IMAP_Get(m_pObj, 36, 0, 0);
      return (char*)val;
    }


    inline int GetMessageInfoCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 37, 0, 0);
      return (int)(long)val;
    }

    inline char* GetMessageInfoDate(int iMessageInfoIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 38, iMessageInfoIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageInfoFlags(int iMessageInfoIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 39, iMessageInfoIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageInfoFrom(int iMessageInfoIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 40, iMessageInfoIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageInfoMessageId(int iMessageInfoIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 41, iMessageInfoIndex, 0);
      return (char*)val;
    }


    inline ns_int64 GetMessageInfoSize(int iMessageInfoIndex) {
      ns_int64 *pval = (ns_int64*)IPWorks_IMAP_Get(m_pObj, 42, iMessageInfoIndex, 0);
      return *pval;
    }


    inline char* GetMessageInfoSubject(int iMessageInfoIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 43, iMessageInfoIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageInReplyTo() {
      void* val = IPWorks_IMAP_Get(m_pObj, 44, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageNetId() {
      void* val = IPWorks_IMAP_Get(m_pObj, 45, 0, 0);
      return (char*)val;
    }


    inline int GetMessagePartCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 46, 0, 0);
      return (int)(long)val;
    }

    inline char* GetMessagePartContentDisposition(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 47, iMessagePartIndex, 0);
      return (char*)val;
    }


    inline char* GetMessagePartContentEncoding(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 48, iMessagePartIndex, 0);
      return (char*)val;
    }


    inline char* GetMessagePartContentId(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 49, iMessagePartIndex, 0);
      return (char*)val;
    }


    inline char* GetMessagePartContentType(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 50, iMessagePartIndex, 0);
      return (char*)val;
    }


    inline char* GetMessagePartFilename(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 51, iMessagePartIndex, 0);
      return (char*)val;
    }


    inline char* GetMessagePartId(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 52, iMessagePartIndex, 0);
      return (char*)val;
    }


    inline char* GetMessagePartMultipartMode(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 53, iMessagePartIndex, 0);
      return (char*)val;
    }


    inline char* GetMessagePartParameters(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 54, iMessagePartIndex, 0);
      return (char*)val;
    }


    inline ns_int64 GetMessagePartSize(int iMessagePartIndex) {
      ns_int64 *pval = (ns_int64*)IPWorks_IMAP_Get(m_pObj, 55, iMessagePartIndex, 0);
      return *pval;
    }


    inline int GetMessageRecipientCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 56, 0, 0);
      return (int)(long)val;
    }

    inline char* GetMessageRecipientAddress(int iRecipientIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 57, iRecipientIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageRecipientName(int iRecipientIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 58, iRecipientIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageRecipientOptions(int iRecipientIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 59, iRecipientIndex, 0);
      return (char*)val;
    }


    inline int GetMessageRecipientType(int iRecipientIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 60, iRecipientIndex, 0);
      return (int)(long)val;
    }

    inline char* GetMessageReplyTo() {
      void* val = IPWorks_IMAP_Get(m_pObj, 61, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageSender() {
      void* val = IPWorks_IMAP_Get(m_pObj, 62, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageSet() {
      void* val = IPWorks_IMAP_Get(m_pObj, 63, 0, 0);
      return (char*)val;
    }

    inline int SetMessageSet(const char *lpMessageSet) {
      return IPWorks_IMAP_Set(m_pObj, 63, 0, (void*)lpMessageSet, 0);
    }

    inline ns_int64 GetMessageSize() {
      ns_int64 *pval = (ns_int64*)IPWorks_IMAP_Get(m_pObj, 64, 0, 0);
      return *pval;
    }


    inline char* GetMessageSubject() {
      void* val = IPWorks_IMAP_Get(m_pObj, 65, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageText() {
      void* val = IPWorks_IMAP_Get(m_pObj, 66, 0, 0);
      return (char*)val;
    }

    inline int SetMessageText(const char *lpMessageText) {
      return IPWorks_IMAP_Set(m_pObj, 66, 0, (void*)lpMessageText, 0);
    }

    inline int GetOverwrite() {
      void* val = IPWorks_IMAP_Get(m_pObj, 67, 0, 0);
      return (int)(long)val;
    }
    inline int SetOverwrite(int bOverwrite) {
      void* val = (void*)IPW64CAST(bOverwrite);
      return IPWorks_IMAP_Set(m_pObj, 67, 0, val, 0);
    }
    inline char* GetPassword() {
      void* val = IPWorks_IMAP_Get(m_pObj, 68, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_IMAP_Set(m_pObj, 68, 0, (void*)lpPassword, 0);
    }

    inline int GetPeekMode() {
      void* val = IPWorks_IMAP_Get(m_pObj, 69, 0, 0);
      return (int)(long)val;
    }
    inline int SetPeekMode(int bPeekMode) {
      void* val = (void*)IPW64CAST(bPeekMode);
      return IPWorks_IMAP_Set(m_pObj, 69, 0, val, 0);
    }
    inline int GetRecentMessageCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 70, 0, 0);
      return (int)(long)val;
    }

    inline char* GetSortCriteria() {
      void* val = IPWorks_IMAP_Get(m_pObj, 71, 0, 0);
      return (char*)val;
    }

    inline int SetSortCriteria(const char *lpSortCriteria) {
      return IPWorks_IMAP_Set(m_pObj, 71, 0, (void*)lpSortCriteria, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_IMAP_Get(m_pObj, 72, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_IMAP_Set(m_pObj, 72, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_IMAP_Get(m_pObj, 73, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_IMAP_Set(m_pObj, 73, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_IMAP_Get(m_pObj, 74, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_IMAP_Set(m_pObj, 74, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_IMAP_Get(m_pObj, 75, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_IMAP_Set(m_pObj, 75, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_IMAP_Get(m_pObj, 76, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_IMAP_Set(m_pObj, 76, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_IMAP_Get(m_pObj, 77, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_IMAP_Set(m_pObj, 77, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_IMAP_Get(m_pObj, 78, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_IMAP_Set(m_pObj, 78, 0, val, 0);
    }
    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_IMAP_Get(m_pObj, 79, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline int GetSSLStartMode() {
      void* val = IPWorks_IMAP_Get(m_pObj, 80, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_IMAP_Set(m_pObj, 80, 0, val, 0);
    }
    inline ns_int64 GetStartByte() {
      ns_int64 *pval = (ns_int64*)IPWorks_IMAP_Get(m_pObj, 81, 0, 0);
      return *pval;
    }

    inline int SetStartByte(ns_int64 lStartByte) {
      void* val = (void*)(&lStartByte);
      return IPWorks_IMAP_Set(m_pObj, 81, 0, val, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_IMAP_Get(m_pObj, 82, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_IMAP_Set(m_pObj, 82, 0, val, 0);
    }
    inline int GetUIDMode() {
      void* val = IPWorks_IMAP_Get(m_pObj, 83, 0, 0);
      return (int)(long)val;
    }
    inline int SetUIDMode(int bUIDMode) {
      void* val = (void*)IPW64CAST(bUIDMode);
      return IPWorks_IMAP_Set(m_pObj, 83, 0, val, 0);
    }
    inline char* GetUIDValidity() {
      void* val = IPWorks_IMAP_Get(m_pObj, 84, 0, 0);
      return (char*)val;
    }


    inline char* GetUser() {
      void* val = IPWorks_IMAP_Get(m_pObj, 85, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_IMAP_Set(m_pObj, 85, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline int AddMessageFlags(const char* lpszFlags) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFlags), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 2, 1, param, cbparam);
      
      
    }
    inline int AppendToMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int CheckMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int CloseMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IMAP_Do(m_pObj, 6, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int CopyToMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int CreateMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int DeleteFromMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int DeleteMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }
    inline int DeleteMailboxACL(const char* lpszUser) {
      void *param[1+1] = {(void*)IPW64CAST(lpszUser), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 12, 1, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 13, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 14, 0, param, cbparam);
      
      
    }
    inline int ExamineMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 15, 0, param, cbparam);
      
      
    }
    inline int ExpungeMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 16, 0, param, cbparam);
      
      
    }
    inline int FetchMessageHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 17, 0, param, cbparam);
      
      
    }
    inline int FetchMessageInfo() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 18, 0, param, cbparam);
      
      
    }
    inline int FetchMessagePart(const char* lpszPartId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPartId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 19, 1, param, cbparam);
      
      
    }
    inline int FetchMessagePartHeaders(const char* lpszPartId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPartId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 20, 1, param, cbparam);
      
      
    }
    inline int FetchMessageText() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 21, 0, param, cbparam);
      
      
    }
    inline int GetMailboxACL() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 22, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 23, 0, param, cbparam);
      
      
    }
    inline int ListMailboxes() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 24, 0, param, cbparam);
      
      
    }
    inline int ListSubscribedMailboxes() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 25, 0, param, cbparam);
      
      
    }
    inline char* LocalizeDate(const char* lpszDateTime) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDateTime), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IMAP_Do(m_pObj, 26, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int MoveToMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 27, 0, param, cbparam);
      
      
    }
    inline int Noop() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 28, 0, param, cbparam);
      
      
    }
    inline int RenameMailbox(const char* lpszNewName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszNewName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 29, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 30, 0, param, cbparam);
      
      
    }
    inline int ResetMessageFlags() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 31, 0, param, cbparam);
      
      
    }
    inline int SearchMailbox(const char* lpszSearchCriteria) {
      void *param[1+1] = {(void*)IPW64CAST(lpszSearchCriteria), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 32, 1, param, cbparam);
      
      
    }
    inline int SelectMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 33, 0, param, cbparam);
      
      
    }
    inline int SetMailboxACL(const char* lpszUser, const char* lpszRights) {
      void *param[2+1] = {(void*)IPW64CAST(lpszUser), (void*)IPW64CAST(lpszRights), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IMAP_Do(m_pObj, 34, 2, param, cbparam);
      
      
    }
    inline int StartIdle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 36, 0, param, cbparam);
      
      
    }
    inline int StopIdle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 37, 0, param, cbparam);
      
      
    }
    inline int SubscribeMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 38, 0, param, cbparam);
      
      
    }
    inline int UnsetMessageFlags() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 39, 0, param, cbparam);
      
      
    }
    inline int UnsubscribeMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 40, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} IMAPConnectionStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} IMAPEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} IMAPErrorEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} IMAPHeaderEventParamsW;

typedef struct {
  LPWSTR Message;
  int Cancel;
  int reserved;
} IMAPIdleInfoEventParamsW;

typedef struct {
  LPWSTR Mailbox;
  LPWSTR User;
  LPWSTR Rights;
  int reserved;
} IMAPMailboxACLEventParamsW;

typedef struct {
  LPWSTR Mailbox;
  LPWSTR Separator;
  LPWSTR Flags;
  int reserved;
} IMAPMailboxListEventParamsW;

typedef struct {
  LPWSTR MessageId;
  LPWSTR Subject;
  LPWSTR MessageDate;
  LPWSTR From;
  LPWSTR Flags;
  ns_int64 Size;
  int reserved;
} IMAPMessageInfoEventParamsW;

typedef struct {
  LPWSTR PartId;
  ns_int64 Size;
  LPWSTR ContentType;
  LPWSTR Filename;
  LPWSTR ContentEncoding;
  LPWSTR Parameters;
  LPWSTR MultipartMode;
  LPWSTR ContentId;
  LPWSTR ContentDisposition;
  int reserved;
} IMAPMessagePartEventParamsW;

typedef struct {
  int Direction;
  LPWSTR Message;
  int reserved;
} IMAPPITrailEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} IMAPSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} IMAPSSLStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} IMAPStartTransferEventParamsW;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int reserved;
} IMAPTransferEventParamsW;



class IMAPW : public IMAP {

  public: //properties
  






    inline int SetCommand(LPCWSTR lpCommand) {
      return IPWorks_IMAP_Set(m_pObj, 10000+3, 0, (void*)lpCommand, 0);
    }









    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_IMAP_Set(m_pObj, 10000+8, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_IMAP_Set(m_pObj, 10000+9, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_IMAP_Set(m_pObj, 10000+11, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetLastReply() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+13, 0, 0);
    }



    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+10000+14, 0, 0);
    }

    inline int SetLocalFile(LPCWSTR lpLocalFile) {
      return IPWorks_IMAP_Set(m_pObj, 10000+10000+14, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_IMAP_Set(m_pObj, 10000+15, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetMailbox() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetMailbox(LPCWSTR lpMailbox) {
      return IPWorks_IMAP_Set(m_pObj, 10000+16, 0, (void*)lpMailbox, 0);
    }

    inline LPWSTR GetMailboxFlags() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+17, 0, 0);
    }





    inline LPWSTR GetMailboxListFlags(int iMailboxListIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+19, iMailboxListIndex, 0);
    }



    inline LPWSTR GetMailboxListName(int iMailboxListIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+20, iMailboxListIndex, 0);
    }



    inline LPWSTR GetMailboxListSeparator(int iMailboxListIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+21, iMailboxListIndex, 0);
    }





    inline LPWSTR GetMailServer() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+23, 0, 0);
    }

    inline int SetMailServer(LPCWSTR lpMailServer) {
      return IPWorks_IMAP_Set(m_pObj, 10000+23, 0, (void*)lpMailServer, 0);
    }

    inline LPWSTR GetMessage() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetMessage(LPCWSTR lpMessage) {
      return IPWorks_IMAP_Set(m_pObj, 10000+24, 0, (void*)lpMessage, 0);
    }
    inline int GetMessageB(char *&lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_IMAP_Get(m_pObj, 24, 0, &lenMessage);
      return lpMessage ? 0 : lenMessage;
    }
    inline int SetMessageB(const char *lpMessage, int lenMessage) {
      return IPWorks_IMAP_Set(m_pObj, 24, 0, (void*)lpMessage, lenMessage);
    }
    inline LPWSTR GetMessageContentEncoding() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+25, 0, 0);
    }



    inline LPWSTR GetMessageContentType() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+26, 0, 0);
    }





    inline LPWSTR GetMessageDate() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+28, 0, 0);
    }



    inline LPWSTR GetMessageDeliveryTime() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+29, 0, 0);
    }



    inline LPWSTR GetMessageFlags() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+30, 0, 0);
    }

    inline int SetMessageFlags(LPCWSTR lpMessageFlags) {
      return IPWorks_IMAP_Set(m_pObj, 10000+30, 0, (void*)lpMessageFlags, 0);
    }

    inline LPWSTR GetMessageFrom() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+31, 0, 0);
    }





    inline LPWSTR GetMessageHeaderField(int iMessageHeaderIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+33, iMessageHeaderIndex, 0);
    }

    inline int SetMessageHeaderField(int iMessageHeaderIndex, LPCWSTR lpMessageHeaderField) {
      return IPWorks_IMAP_Set(m_pObj, 10000+33, iMessageHeaderIndex, (void*)lpMessageHeaderField, 0);
    }

    inline LPWSTR GetMessageHeaderValue(int iMessageHeaderIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+34, iMessageHeaderIndex, 0);
    }

    inline int SetMessageHeaderValue(int iMessageHeaderIndex, LPCWSTR lpMessageHeaderValue) {
      return IPWorks_IMAP_Set(m_pObj, 10000+34, iMessageHeaderIndex, (void*)lpMessageHeaderValue, 0);
    }

    inline LPWSTR GetMessageHeadersString() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+35, 0, 0);
    }

    inline int SetMessageHeadersString(LPCWSTR lpMessageHeadersString) {
      return IPWorks_IMAP_Set(m_pObj, 10000+35, 0, (void*)lpMessageHeadersString, 0);
    }

    inline LPWSTR GetMessageId() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+36, 0, 0);
    }





    inline LPWSTR GetMessageInfoDate(int iMessageInfoIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+38, iMessageInfoIndex, 0);
    }



    inline LPWSTR GetMessageInfoFlags(int iMessageInfoIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+39, iMessageInfoIndex, 0);
    }



    inline LPWSTR GetMessageInfoFrom(int iMessageInfoIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+40, iMessageInfoIndex, 0);
    }



    inline LPWSTR GetMessageInfoMessageId(int iMessageInfoIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+41, iMessageInfoIndex, 0);
    }





    inline LPWSTR GetMessageInfoSubject(int iMessageInfoIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+43, iMessageInfoIndex, 0);
    }



    inline LPWSTR GetMessageInReplyTo() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+44, 0, 0);
    }



    inline LPWSTR GetMessageNetId() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+45, 0, 0);
    }





    inline LPWSTR GetMessagePartContentDisposition(int iMessagePartIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+47, iMessagePartIndex, 0);
    }



    inline LPWSTR GetMessagePartContentEncoding(int iMessagePartIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+48, iMessagePartIndex, 0);
    }



    inline LPWSTR GetMessagePartContentId(int iMessagePartIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+49, iMessagePartIndex, 0);
    }



    inline LPWSTR GetMessagePartContentType(int iMessagePartIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+50, iMessagePartIndex, 0);
    }



    inline LPWSTR GetMessagePartFilename(int iMessagePartIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+51, iMessagePartIndex, 0);
    }



    inline LPWSTR GetMessagePartId(int iMessagePartIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+52, iMessagePartIndex, 0);
    }



    inline LPWSTR GetMessagePartMultipartMode(int iMessagePartIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+53, iMessagePartIndex, 0);
    }



    inline LPWSTR GetMessagePartParameters(int iMessagePartIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+54, iMessagePartIndex, 0);
    }







    inline LPWSTR GetMessageRecipientAddress(int iRecipientIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+57, iRecipientIndex, 0);
    }



    inline LPWSTR GetMessageRecipientName(int iRecipientIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+58, iRecipientIndex, 0);
    }



    inline LPWSTR GetMessageRecipientOptions(int iRecipientIndex) {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+59, iRecipientIndex, 0);
    }





    inline LPWSTR GetMessageReplyTo() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+61, 0, 0);
    }



    inline LPWSTR GetMessageSender() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+62, 0, 0);
    }



    inline LPWSTR GetMessageSet() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+63, 0, 0);
    }

    inline int SetMessageSet(LPCWSTR lpMessageSet) {
      return IPWorks_IMAP_Set(m_pObj, 10000+63, 0, (void*)lpMessageSet, 0);
    }



    inline LPWSTR GetMessageSubject() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+65, 0, 0);
    }



    inline LPWSTR GetMessageText() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+66, 0, 0);
    }

    inline int SetMessageText(LPCWSTR lpMessageText) {
      return IPWorks_IMAP_Set(m_pObj, 10000+66, 0, (void*)lpMessageText, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+68, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_IMAP_Set(m_pObj, 10000+68, 0, (void*)lpPassword, 0);
    }





    inline LPWSTR GetSortCriteria() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+71, 0, 0);
    }

    inline int SetSortCriteria(LPCWSTR lpSortCriteria) {
      return IPWorks_IMAP_Set(m_pObj, 10000+71, 0, (void*)lpSortCriteria, 0);
    }

    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+72, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_IMAP_Set(m_pObj, 10000+72, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_IMAP_Get(m_pObj, 72, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_IMAP_Set(m_pObj, 72, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+73, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_IMAP_Set(m_pObj, 10000+73, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_IMAP_Get(m_pObj, 73, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_IMAP_Set(m_pObj, 73, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+74, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_IMAP_Set(m_pObj, 10000+74, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_IMAP_Get(m_pObj, 74, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_IMAP_Set(m_pObj, 74, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+75, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_IMAP_Set(m_pObj, 10000+75, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+77, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_IMAP_Set(m_pObj, 10000+77, 0, (void*)lpSSLCertSubject, 0);
    }



    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+79, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_IMAP_Get(m_pObj, 79, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }









    inline LPWSTR GetUIDValidity() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+84, 0, 0);
    }



    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_IMAP_Get(m_pObj, 10000+85, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_IMAP_Set(m_pObj, 10000+85, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnectionStatus(IMAPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(IMAPEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(IMAPErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(IMAPHeaderEventParamsW *e) {return 0;}
    virtual int FireIdleInfo(IMAPIdleInfoEventParamsW *e) {return 0;}
    virtual int FireMailboxACL(IMAPMailboxACLEventParamsW *e) {return 0;}
    virtual int FireMailboxList(IMAPMailboxListEventParamsW *e) {return 0;}
    virtual int FireMessageInfo(IMAPMessageInfoEventParamsW *e) {return 0;}
    virtual int FireMessagePart(IMAPMessagePartEventParamsW *e) {return 0;}
    virtual int FirePITrail(IMAPPITrailEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(IMAPSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(IMAPSSLStatusEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(IMAPStartTransferEventParamsW *e) {return 0;}
    virtual int FireTransfer(IMAPTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int IMAPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            IMAPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 2: {
            IMAPEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 3: {
            IMAPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 4: {
            IMAPHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 5: {
            IMAPIdleInfoEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = FireIdleInfo(&e);
            param[1] = (void*)(e.Cancel);
            break;
         }
         case 6: {
            IMAPMailboxACLEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireMailboxACL(&e);
            break;
         }
         case 7: {
            IMAPMailboxListEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireMailboxList(&e);
            break;
         }
         case 8: {
            IMAPMessageInfoEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), *(ns_int64*)IPW64CAST(param[5]),  0};
            ret_code = FireMessageInfo(&e);
            break;
         }
         case 9: {
            IMAPMessagePartEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]), (LPWSTR)IPW64CAST(param[6]), (LPWSTR)IPW64CAST(param[7]), (LPWSTR)IPW64CAST(param[8]),  0};
            ret_code = FireMessagePart(&e);
            break;
         }
         case 10: {
            IMAPPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }
         case 11: {
            IMAPSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 12: {
            IMAPSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }
         case 13: {
            IMAPStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 14: {
            IMAPTransferEventParamsW e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnectionStatus(IMAPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireEndTransfer(IMAPEndTransferEventParams *e) {return -10000;}
    virtual int FireError(IMAPErrorEventParams *e) {return -10000;}
    virtual int FireHeader(IMAPHeaderEventParams *e) {return -10000;}
    virtual int FireIdleInfo(IMAPIdleInfoEventParams *e) {return -10000;}
    virtual int FireMailboxACL(IMAPMailboxACLEventParams *e) {return -10000;}
    virtual int FireMailboxList(IMAPMailboxListEventParams *e) {return -10000;}
    virtual int FireMessageInfo(IMAPMessageInfoEventParams *e) {return -10000;}
    virtual int FireMessagePart(IMAPMessagePartEventParams *e) {return -10000;}
    virtual int FirePITrail(IMAPPITrailEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(IMAPSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(IMAPSSLStatusEventParams *e) {return -10000;}
    virtual int FireStartTransfer(IMAPStartTransferEventParams *e) {return -10000;}
    virtual int FireTransfer(IMAPTransferEventParams *e) {return -10000;}

  public: //methods

    inline int AddMessageFlags(LPWSTR lpszFlags) {
      void *param[1+1] = {(void*)lpszFlags, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 10000+2, 1, param, cbparam);
      
    }
    inline int AppendToMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int CheckMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int CloseMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IMAP_Do(m_pObj, 10000+6, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int CopyToMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int CreateMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int DeleteFromMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int DeleteMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }
    inline int DeleteMailboxACL(LPWSTR lpszUser) {
      void *param[1+1] = {(void*)lpszUser, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 10000+12, 1, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+13, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+14, 0, param, cbparam);
      
    }
    inline int ExamineMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+15, 0, param, cbparam);
      
    }
    inline int ExpungeMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+16, 0, param, cbparam);
      
    }
    inline int FetchMessageHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+17, 0, param, cbparam);
      
    }
    inline int FetchMessageInfo() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+18, 0, param, cbparam);
      
    }
    inline int FetchMessagePart(LPWSTR lpszPartId) {
      void *param[1+1] = {(void*)lpszPartId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 10000+19, 1, param, cbparam);
      
    }
    inline int FetchMessagePartHeaders(LPWSTR lpszPartId) {
      void *param[1+1] = {(void*)lpszPartId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 10000+20, 1, param, cbparam);
      
    }
    inline int FetchMessageText() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+21, 0, param, cbparam);
      
    }
    inline int GetMailboxACL() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+22, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+23, 0, param, cbparam);
      
    }
    inline int ListMailboxes() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+24, 0, param, cbparam);
      
    }
    inline int ListSubscribedMailboxes() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+25, 0, param, cbparam);
      
    }
    inline LPWSTR LocalizeDate(LPWSTR lpszDateTime) {
      void *param[1+1] = {(void*)lpszDateTime, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IMAP_Do(m_pObj, 10000+26, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int MoveToMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+27, 0, param, cbparam);
      
    }
    inline int Noop() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+28, 0, param, cbparam);
      
    }
    inline int RenameMailbox(LPWSTR lpszNewName) {
      void *param[1+1] = {(void*)lpszNewName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 10000+29, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+30, 0, param, cbparam);
      
    }
    inline int ResetMessageFlags() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+31, 0, param, cbparam);
      
    }
    inline int SearchMailbox(LPWSTR lpszSearchCriteria) {
      void *param[1+1] = {(void*)lpszSearchCriteria, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 10000+32, 1, param, cbparam);
      
    }
    inline int SelectMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+33, 0, param, cbparam);
      
    }
    inline int SetMailboxACL(LPWSTR lpszUser, LPWSTR lpszRights) {
      void *param[2+1] = {(void*)lpszUser, (void*)lpszRights, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IMAP_Do(m_pObj, 10000+34, 2, param, cbparam);
      
    }
    inline int StartIdle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+36, 0, param, cbparam);
      
    }
    inline int StopIdle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+37, 0, param, cbparam);
      
    }
    inline int SubscribeMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+38, 0, param, cbparam);
      
    }
    inline int UnsetMessageFlags() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+39, 0, param, cbparam);
      
    }
    inline int UnsubscribeMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10000+40, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_IMAP_H_




