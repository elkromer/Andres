/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_IMAP_H_
#define _IPWORKS_IMAP_H_

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


extern "C" void* IPWORKS_CALL IPWorks_IMAP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_IMAP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_IMAP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_IMAP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_StaticDestroy();

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
} IMAPConnectionStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} IMAPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} IMAPErrorEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} IMAPHeaderEventParams;

typedef struct {
  const char *Message;
  int Cancel;
  int reserved;
} IMAPIdleInfoEventParams;

typedef struct {
  const char *Mailbox;
  const char *User;
  const char *Rights;
  int reserved;
} IMAPMailboxACLEventParams;

typedef struct {
  const char *Mailbox;
  const char *Separator;
  const char *Flags;
  int reserved;
} IMAPMailboxListEventParams;

typedef struct {
  const char *MessageId;
  const char *Subject;
  const char *MessageDate;
  const char *From;
  const char *Flags;
  int64 Size;
  int reserved;
} IMAPMessageInfoEventParams;

typedef struct {
  const char *PartId;
  int64 Size;
  const char *ContentType;
  const char *Filename;
  const char *ContentEncoding;
  const char *Parameters;
  const char *MultipartMode;
  const char *ContentId;
  const char *ContentDisposition;
  int reserved;
} IMAPMessagePartEventParams;

typedef struct {
  int Direction;
  const char *Message;
  int reserved;
} IMAPPITrailEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} IMAPSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} IMAPSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} IMAPStartTransferEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int reserved;
} IMAPTransferEventParams;


class IMAP {
  public: // Events
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
      switch (event_id) {
        case 1: {
          IMAPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((IMAP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          IMAPEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((IMAP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 3: {
          IMAPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((IMAP*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          IMAPHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((IMAP*)lpObj)->FireHeader(&e);
          break;
        }
        case 5: {
          IMAPIdleInfoEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), 0};
          ret_code = ((IMAP*)lpObj)->FireIdleInfo(&e);
          param[1] = (void*)IPW64CAST(e.Cancel);
          break;
        }
        case 6: {
          IMAPMailboxACLEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((IMAP*)lpObj)->FireMailboxACL(&e);
          break;
        }
        case 7: {
          IMAPMailboxListEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((IMAP*)lpObj)->FireMailboxList(&e);
          break;
        }
        case 8: {
          IMAPMessageInfoEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), *(int64*)IPW64CAST(param[5]), 0};
          ret_code = ((IMAP*)lpObj)->FireMessageInfo(&e);
          break;
        }
        case 9: {
          IMAPMessagePartEventParams e = {(char*)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), (char*)IPW64CAST(param[7]), (char*)IPW64CAST(param[8]), 0};
          ret_code = ((IMAP*)lpObj)->FireMessagePart(&e);
          break;
        }
        case 10: {
          IMAPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((IMAP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 11: {
          IMAPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((IMAP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 12: {
          IMAPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((IMAP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 13: {
          IMAPStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((IMAP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 14: {
          IMAPTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), 0};
          ret_code = ((IMAP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    IMAP(char *lpOemKey = (char*)IPWORKS_OEMKEY_31) {
      m_pObj = IPWorks_IMAP_Create(IMAPEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~IMAP() {
      IPWorks_IMAP_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_IMAP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_IMAP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_IMAP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_IMAP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_IMAP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetAuthMechanism() {
      void* val = IPWorks_IMAP_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthMechanism(int iAuthMechanism) {
      void* val = (void*)IPW64CAST(iAuthMechanism);
      return IPWorks_IMAP_Set(m_pObj, 1, 0, val, 0);
    }

    inline int GetAutoDecodeParts() {
      void* val = IPWorks_IMAP_Get(m_pObj, 2, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAutoDecodeParts(int bAutoDecodeParts) {
      void* val = (void*)IPW64CAST(bAutoDecodeParts);
      return IPWorks_IMAP_Set(m_pObj, 2, 0, val, 0);
    }

    inline int SetCommand(const char* lpszCommand) {
      return IPWorks_IMAP_Set(m_pObj, 3, 0, (void*)lpszCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_IMAP_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_IMAP_Set(m_pObj, 4, 0, val, 0);
    }

    inline int64 GetEndByte() {
      int64 retVal;
      IPWorks_IMAP_Get(m_pObj, 5, 0, NULL, &retVal);
      return retVal;
    }
    inline int SetEndByte(int64 lEndByte) {
      void* val = (void*)(&lEndByte);
      return IPWorks_IMAP_Set(m_pObj, 5, 0, val, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_IMAP_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_IMAP_Set(m_pObj, 6, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_IMAP_Get(m_pObj, 7, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_IMAP_Set(m_pObj, 7, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_IMAP_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_IMAP_Set(m_pObj, 8, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_IMAP_Get(m_pObj, 9, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_IMAP_Set(m_pObj, 9, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_IMAP_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_IMAP_Set(m_pObj, 10, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_IMAP_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_IMAP_Set(m_pObj, 11, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_IMAP_Get(m_pObj, 12, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLastReply() {
      void* val = IPWorks_IMAP_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_IMAP_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_IMAP_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_IMAP_Set(m_pObj, 14, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_IMAP_Set(m_pObj, 14+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_IMAP_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_IMAP_Set(m_pObj, 15, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetMailbox() {
      void* val = IPWorks_IMAP_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMailbox(const char* lpszMailbox) {
      return IPWorks_IMAP_Set(m_pObj, 16, 0, (void*)lpszMailbox, 0);
    }

    inline char* GetMailboxFlags() {
      void* val = IPWorks_IMAP_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetMailboxListCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 18, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMailboxListFlags(int iMailboxListIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 19, iMailboxListIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMailboxListName(int iMailboxListIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 20, iMailboxListIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMailboxListSeparator(int iMailboxListIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 21, iMailboxListIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetMailPort() {
      void* val = IPWorks_IMAP_Get(m_pObj, 22, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMailPort(int iMailPort) {
      void* val = (void*)IPW64CAST(iMailPort);
      return IPWorks_IMAP_Set(m_pObj, 22, 0, val, 0);
    }

    inline char* GetMailServer() {
      void* val = IPWorks_IMAP_Get(m_pObj, 23, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMailServer(const char* lpszMailServer) {
      return IPWorks_IMAP_Set(m_pObj, 23, 0, (void*)lpszMailServer, 0);
    }

    inline int GetMessage(char* &lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_IMAP_Get(m_pObj, 24, 0, &lenMessage, NULL);
      return lpMessage ? 0 : lenMessage;
    }
    inline int SetMessage(const char* lpMessage, int lenMessage) {
      return IPWorks_IMAP_Set(m_pObj, 24, 0, (void*)lpMessage, lenMessage);
    }

    inline char* GetMessageContentEncoding() {
      void* val = IPWorks_IMAP_Get(m_pObj, 25, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageContentType() {
      void* val = IPWorks_IMAP_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetMessageCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 27, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMessageDate() {
      void* val = IPWorks_IMAP_Get(m_pObj, 28, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageDeliveryTime() {
      void* val = IPWorks_IMAP_Get(m_pObj, 29, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageFlags() {
      void* val = IPWorks_IMAP_Get(m_pObj, 30, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageFlags(const char* lpszMessageFlags) {
      return IPWorks_IMAP_Set(m_pObj, 30, 0, (void*)lpszMessageFlags, 0);
    }

    inline char* GetMessageFrom() {
      void* val = IPWorks_IMAP_Get(m_pObj, 31, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetMessageHeaderCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 32, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMessageHeaderCount(int iMessageHeaderCount) {
      void* val = (void*)IPW64CAST(iMessageHeaderCount);
      return IPWorks_IMAP_Set(m_pObj, 32, 0, val, 0);
    }

    inline char* GetMessageHeaderField(int iMessageHeaderIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 33, iMessageHeaderIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageHeaderField(int iMessageHeaderIndex, const char* lpszMessageHeaderField) {
      return IPWorks_IMAP_Set(m_pObj, 33, iMessageHeaderIndex, (void*)lpszMessageHeaderField, 0);
    }

    inline char* GetMessageHeaderValue(int iMessageHeaderIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 34, iMessageHeaderIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageHeaderValue(int iMessageHeaderIndex, const char* lpszMessageHeaderValue) {
      return IPWorks_IMAP_Set(m_pObj, 34, iMessageHeaderIndex, (void*)lpszMessageHeaderValue, 0);
    }

    inline char* GetMessageHeadersString() {
      void* val = IPWorks_IMAP_Get(m_pObj, 35, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageHeadersString(const char* lpszMessageHeadersString) {
      return IPWorks_IMAP_Set(m_pObj, 35, 0, (void*)lpszMessageHeadersString, 0);
    }

    inline char* GetMessageId() {
      void* val = IPWorks_IMAP_Get(m_pObj, 36, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetMessageInfoCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 37, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMessageInfoDate(int iMessageInfoIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 38, iMessageInfoIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageInfoFlags(int iMessageInfoIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 39, iMessageInfoIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageInfoFrom(int iMessageInfoIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 40, iMessageInfoIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageInfoMessageId(int iMessageInfoIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 41, iMessageInfoIndex, NULL, NULL);
      return (char*)val;
    }

    inline int64 GetMessageInfoSize(int iMessageInfoIndex) {
      int64 retVal;
      IPWorks_IMAP_Get(m_pObj, 42, iMessageInfoIndex, NULL, &retVal);
      return retVal;
    }

    inline char* GetMessageInfoSubject(int iMessageInfoIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 43, iMessageInfoIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageInReplyTo() {
      void* val = IPWorks_IMAP_Get(m_pObj, 44, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageNetId() {
      void* val = IPWorks_IMAP_Get(m_pObj, 45, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetMessagePartCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 46, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMessagePartContentDisposition(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 47, iMessagePartIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessagePartContentEncoding(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 48, iMessagePartIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessagePartContentId(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 49, iMessagePartIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessagePartContentType(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 50, iMessagePartIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessagePartFilename(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 51, iMessagePartIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessagePartId(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 52, iMessagePartIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessagePartMultipartMode(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 53, iMessagePartIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessagePartParameters(int iMessagePartIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 54, iMessagePartIndex, NULL, NULL);
      return (char*)val;
    }

    inline int64 GetMessagePartSize(int iMessagePartIndex) {
      int64 retVal;
      IPWorks_IMAP_Get(m_pObj, 55, iMessagePartIndex, NULL, &retVal);
      return retVal;
    }

    inline int GetMessageRecipientCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 56, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMessageRecipientAddress(int iRecipientIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 57, iRecipientIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageRecipientName(int iRecipientIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 58, iRecipientIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageRecipientOptions(int iRecipientIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 59, iRecipientIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetMessageRecipientType(int iRecipientIndex) {
      void* val = IPWorks_IMAP_Get(m_pObj, 60, iRecipientIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMessageReplyTo() {
      void* val = IPWorks_IMAP_Get(m_pObj, 61, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageSender() {
      void* val = IPWorks_IMAP_Get(m_pObj, 62, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageSet() {
      void* val = IPWorks_IMAP_Get(m_pObj, 63, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageSet(const char* lpszMessageSet) {
      return IPWorks_IMAP_Set(m_pObj, 63, 0, (void*)lpszMessageSet, 0);
    }

    inline int64 GetMessageSize() {
      int64 retVal;
      IPWorks_IMAP_Get(m_pObj, 64, 0, NULL, &retVal);
      return retVal;
    }

    inline char* GetMessageSubject() {
      void* val = IPWorks_IMAP_Get(m_pObj, 65, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageText() {
      void* val = IPWorks_IMAP_Get(m_pObj, 66, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageText(const char* lpszMessageText) {
      return IPWorks_IMAP_Set(m_pObj, 66, 0, (void*)lpszMessageText, 0);
    }

    inline int GetOverwrite() {
      void* val = IPWorks_IMAP_Get(m_pObj, 67, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetOverwrite(int bOverwrite) {
      void* val = (void*)IPW64CAST(bOverwrite);
      return IPWorks_IMAP_Set(m_pObj, 67, 0, val, 0);
    }

    inline char* GetPassword() {
      void* val = IPWorks_IMAP_Get(m_pObj, 68, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_IMAP_Set(m_pObj, 68, 0, (void*)lpszPassword, 0);
    }

    inline int GetPeekMode() {
      void* val = IPWorks_IMAP_Get(m_pObj, 69, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetPeekMode(int bPeekMode) {
      void* val = (void*)IPW64CAST(bPeekMode);
      return IPWorks_IMAP_Set(m_pObj, 69, 0, val, 0);
    }

    inline int GetRecentMessageCount() {
      void* val = IPWorks_IMAP_Get(m_pObj, 70, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetSortCriteria() {
      void* val = IPWorks_IMAP_Get(m_pObj, 71, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSortCriteria(const char* lpszSortCriteria) {
      return IPWorks_IMAP_Set(m_pObj, 71, 0, (void*)lpszSortCriteria, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_IMAP_Get(m_pObj, 72, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_IMAP_Set(m_pObj, 72, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_IMAP_Get(m_pObj, 73, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_IMAP_Set(m_pObj, 73, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_IMAP_Get(m_pObj, 74, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_IMAP_Set(m_pObj, 74, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_IMAP_Get(m_pObj, 75, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_IMAP_Set(m_pObj, 75, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_IMAP_Get(m_pObj, 76, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_IMAP_Set(m_pObj, 76, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_IMAP_Get(m_pObj, 77, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_IMAP_Set(m_pObj, 77, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_IMAP_Get(m_pObj, 78, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_IMAP_Set(m_pObj, 78, 0, val, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_IMAP_Get(m_pObj, 79, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetSSLStartMode() {
      void* val = IPWorks_IMAP_Get(m_pObj, 80, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_IMAP_Set(m_pObj, 80, 0, val, 0);
    }

    inline int64 GetStartByte() {
      int64 retVal;
      IPWorks_IMAP_Get(m_pObj, 81, 0, NULL, &retVal);
      return retVal;
    }
    inline int SetStartByte(int64 lStartByte) {
      void* val = (void*)(&lStartByte);
      return IPWorks_IMAP_Set(m_pObj, 81, 0, val, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_IMAP_Get(m_pObj, 82, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_IMAP_Set(m_pObj, 82, 0, val, 0);
    }

    inline int GetUIDMode() {
      void* val = IPWorks_IMAP_Get(m_pObj, 83, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetUIDMode(int bUIDMode) {
      void* val = (void*)IPW64CAST(bUIDMode);
      return IPWorks_IMAP_Set(m_pObj, 83, 0, val, 0);
    }

    inline char* GetUIDValidity() {
      void* val = IPWorks_IMAP_Get(m_pObj, 84, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetUser() {
      void* val = IPWorks_IMAP_Get(m_pObj, 85, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_IMAP_Set(m_pObj, 85, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline int AddMessageFlags(const char* lpszFlags) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFlags), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 2, 1, param, cbparam, NULL);
    }

    inline int AppendToMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int CheckMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int CloseMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IMAP_Do(m_pObj, 6, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int CopyToMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline int CreateMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int DeleteFromMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int DeleteMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 11, 0, param, cbparam, NULL);
    }

    inline int DeleteMailboxACL(const char* lpszUser) {
      void *param[1+1] = {(void*)IPW64CAST(lpszUser), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 12, 1, param, cbparam, NULL);
    }

    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 13, 0, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 14, 0, param, cbparam, NULL);
    }

    inline int ExamineMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 15, 0, param, cbparam, NULL);
    }

    inline int ExpungeMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 16, 0, param, cbparam, NULL);
    }

    inline int FetchMessageHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 17, 0, param, cbparam, NULL);
    }

    inline int FetchMessageInfo() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 18, 0, param, cbparam, NULL);
    }

    inline int FetchMessagePart(const char* lpszPartId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPartId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 19, 1, param, cbparam, NULL);
    }

    inline int FetchMessagePartHeaders(const char* lpszPartId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPartId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 20, 1, param, cbparam, NULL);
    }

    inline int FetchMessageText() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 21, 0, param, cbparam, NULL);
    }

    inline int GetMailboxACL() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 22, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 23, 0, param, cbparam, NULL);
    }

    inline int ListMailboxes() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 24, 0, param, cbparam, NULL);
    }

    inline int ListSubscribedMailboxes() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 25, 0, param, cbparam, NULL);
    }

    inline char* LocalizeDate(const char* lpszDateTime) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDateTime), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IMAP_Do(m_pObj, 26, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int MoveToMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 27, 0, param, cbparam, NULL);
    }

    inline int Noop() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 28, 0, param, cbparam, NULL);
    }

    inline int RenameMailbox(const char* lpszNewName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszNewName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 29, 1, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 30, 0, param, cbparam, NULL);
    }

    inline int ResetMessageFlags() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 31, 0, param, cbparam, NULL);
    }

    inline int SearchMailbox(const char* lpszSearchCriteria) {
      void *param[1+1] = {(void*)IPW64CAST(lpszSearchCriteria), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 32, 1, param, cbparam, NULL);
    }

    inline int SelectMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 33, 0, param, cbparam, NULL);
    }

    inline int SetMailboxACL(const char* lpszUser, const char* lpszRights) {
      void *param[2+1] = {(void*)IPW64CAST(lpszUser), (void*)IPW64CAST(lpszRights), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IMAP_Do(m_pObj, 34, 2, param, cbparam, NULL);
    }

    inline int SetMessageStream(IPWorksStream* sMessageStream) {
      void *param[1+1] = {(void*)IPW64CAST(sMessageStream), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 35, 1, param, cbparam, NULL);
    }

    inline int StartIdle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 36, 0, param, cbparam, NULL);
    }

    inline int StopIdle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 37, 0, param, cbparam, NULL);
    }

    inline int SubscribeMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 38, 0, param, cbparam, NULL);
    }

    inline int UnsetMessageFlags() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 39, 0, param, cbparam, NULL);
    }

    inline int UnsubscribeMailbox() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 40, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_IMAP_H_
