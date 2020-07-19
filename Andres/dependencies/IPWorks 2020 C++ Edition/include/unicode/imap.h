/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
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
extern "C" void* IPWORKS_CALL IPWorks_IMAP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_IMAP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_IMAP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IMAP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} IMAPConnectionStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} IMAPEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} IMAPErrorEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} IMAPHeaderEventParams;

typedef struct {
  LPCWSTR Message;
  BOOL Cancel;
  INT reserved;
} IMAPIdleInfoEventParams;

typedef struct {
  LPCWSTR Mailbox;
  LPCWSTR User;
  LPCWSTR Rights;
  INT reserved;
} IMAPMailboxACLEventParams;

typedef struct {
  LPCWSTR Mailbox;
  LPCWSTR Separator;
  LPCWSTR Flags;
  INT reserved;
} IMAPMailboxListEventParams;

typedef struct {
  LPCWSTR MessageId;
  LPCWSTR Subject;
  LPCWSTR MessageDate;
  LPCWSTR From;
  LPCWSTR Flags;
  LONG64 Size;
  INT reserved;
} IMAPMessageInfoEventParams;

typedef struct {
  LPCWSTR PartId;
  LONG64 Size;
  LPCWSTR ContentType;
  LPCWSTR Filename;
  LPCWSTR ContentEncoding;
  LPCWSTR Parameters;
  LPCWSTR MultipartMode;
  LPCWSTR ContentId;
  LPCWSTR ContentDisposition;
  INT reserved;
} IMAPMessagePartEventParams;

typedef struct {
  INT Direction;
  LPCWSTR Message;
  INT reserved;
} IMAPPITrailEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} IMAPSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} IMAPSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} IMAPStartTransferEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCWSTR Text;
  INT reserved;
} IMAPTransferEventParams;


class IMAP {
  public: // Events
    virtual INT FireConnectionStatus(IMAPConnectionStatusEventParams *e) {return 0;}
    virtual INT FireEndTransfer(IMAPEndTransferEventParams *e) {return 0;}
    virtual INT FireError(IMAPErrorEventParams *e) {return 0;}
    virtual INT FireHeader(IMAPHeaderEventParams *e) {return 0;}
    virtual INT FireIdleInfo(IMAPIdleInfoEventParams *e) {return 0;}
    virtual INT FireMailboxACL(IMAPMailboxACLEventParams *e) {return 0;}
    virtual INT FireMailboxList(IMAPMailboxListEventParams *e) {return 0;}
    virtual INT FireMessageInfo(IMAPMessageInfoEventParams *e) {return 0;}
    virtual INT FireMessagePart(IMAPMessagePartEventParams *e) {return 0;}
    virtual INT FirePITrail(IMAPPITrailEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(IMAPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(IMAPSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(IMAPStartTransferEventParams *e) {return 0;}
    virtual INT FireTransfer(IMAPTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL IMAPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          IMAPConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((IMAP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          IMAPEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((IMAP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 3: {
          IMAPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((IMAP*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          IMAPHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((IMAP*)lpObj)->FireHeader(&e);
          break;
        }
        case 5: {
          IMAPIdleInfoEventParams e = {(LPWSTR)param[0], (BOOL)param[1], 0};
          ret_code = ((IMAP*)lpObj)->FireIdleInfo(&e);
          param[1] = (LPVOID)e.Cancel;
          break;
        }
        case 6: {
          IMAPMailboxACLEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((IMAP*)lpObj)->FireMailboxACL(&e);
          break;
        }
        case 7: {
          IMAPMailboxListEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((IMAP*)lpObj)->FireMailboxList(&e);
          break;
        }
        case 8: {
          IMAPMessageInfoEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], *(LONG64*)param[5], 0};
          ret_code = ((IMAP*)lpObj)->FireMessageInfo(&e);
          break;
        }
        case 9: {
          IMAPMessagePartEventParams e = {(LPWSTR)param[0], *(LONG64*)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (LPWSTR)param[5], (LPWSTR)param[6], (LPWSTR)param[7], (LPWSTR)param[8], 0};
          ret_code = ((IMAP*)lpObj)->FireMessagePart(&e);
          break;
        }
        case 10: {
          IMAPPITrailEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((IMAP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 11: {
          IMAPSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((IMAP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 12: {
          IMAPSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((IMAP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 13: {
          IMAPStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((IMAP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 14: {
          IMAPTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPWSTR)param[3], 0};
          ret_code = ((IMAP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    IMAP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_31) {
      m_pObj = IPWorks_IMAP_Create(IMAPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~IMAP() {
      IPWorks_IMAP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_IMAP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_IMAP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_IMAP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_IMAP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_IMAP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetAuthMechanism() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 1, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthMechanism(INT iAuthMechanism) {
      LPVOID val = (LPVOID)(iAuthMechanism);
      return IPWorks_IMAP_Set(m_pObj, 1, 0, val, 0);
    }

    inline BOOL GetAutoDecodeParts() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 2, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetAutoDecodeParts(BOOL bAutoDecodeParts) {
      LPVOID val = (LPVOID)(bAutoDecodeParts);
      return IPWorks_IMAP_Set(m_pObj, 2, 0, val, 0);
    }

    inline INT SetCommand(LPCWSTR lpszCommand) {
      return IPWorks_IMAP_Set(m_pObj, 3+10000, 0, (LPVOID)lpszCommand, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 4, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_IMAP_Set(m_pObj, 4, 0, val, 0);
    }

    inline LONG64 GetEndByte() {
      LONG64 retVal;
      IPWorks_IMAP_Get(m_pObj, 5, 0, NULL, &retVal);
      return retVal;
    }
    inline INT SetEndByte(LONG64 lEndByte) {
      LPVOID val = (LPVOID)(&lEndByte);
      return IPWorks_IMAP_Set(m_pObj, 5, 0, val, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 6, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_IMAP_Set(m_pObj, 6, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 7, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_IMAP_Set(m_pObj, 7, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_IMAP_Set(m_pObj, 8+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_IMAP_Set(m_pObj, 9+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 10, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_IMAP_Set(m_pObj, 10, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_IMAP_Set(m_pObj, 11+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 12, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLastReply() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_IMAP_Set(m_pObj, 14+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_IMAP_Set(m_pObj, 15+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetMailbox() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMailbox(LPCWSTR lpszMailbox) {
      return IPWorks_IMAP_Set(m_pObj, 16+10000, 0, (LPVOID)lpszMailbox, 0);
    }

    inline LPWSTR GetMailboxFlags() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMailboxListCount() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 18, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMailboxListFlags(INT iMailboxListIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 19+10000, iMailboxListIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMailboxListName(INT iMailboxListIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 20+10000, iMailboxListIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMailboxListSeparator(INT iMailboxListIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 21+10000, iMailboxListIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMailPort() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 22, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMailPort(INT iMailPort) {
      LPVOID val = (LPVOID)(iMailPort);
      return IPWorks_IMAP_Set(m_pObj, 22, 0, val, 0);
    }

    inline LPWSTR GetMailServer() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 23+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMailServer(LPCWSTR lpszMailServer) {
      return IPWorks_IMAP_Set(m_pObj, 23+10000, 0, (LPVOID)lpszMailServer, 0);
    }

    inline INT GetMessage(LPSTR &lpMessage, INT &lenMessage) {
      lpMessage = (LPSTR)IPWorks_IMAP_Get(m_pObj, 24, 0, &lenMessage, NULL);
      return lpMessage ? 0 : lenMessage;
    }
    inline INT SetMessage(LPCSTR lpMessage, INT lenMessage) {
      return IPWorks_IMAP_Set(m_pObj, 24, 0, (LPVOID)lpMessage, lenMessage);
    }

    inline LPWSTR GetMessageContentEncoding() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageContentType() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessageCount() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 27, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMessageDate() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 28+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageDeliveryTime() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageFlags() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 30+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageFlags(LPCWSTR lpszMessageFlags) {
      return IPWorks_IMAP_Set(m_pObj, 30+10000, 0, (LPVOID)lpszMessageFlags, 0);
    }

    inline LPWSTR GetMessageFrom() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessageHeaderCount() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 32, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMessageHeaderCount(INT iMessageHeaderCount) {
      LPVOID val = (LPVOID)(iMessageHeaderCount);
      return IPWorks_IMAP_Set(m_pObj, 32, 0, val, 0);
    }

    inline LPWSTR GetMessageHeaderField(INT iMessageHeaderIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 33+10000, iMessageHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageHeaderField(INT iMessageHeaderIndex, LPCWSTR lpszMessageHeaderField) {
      return IPWorks_IMAP_Set(m_pObj, 33+10000, iMessageHeaderIndex, (LPVOID)lpszMessageHeaderField, 0);
    }

    inline LPWSTR GetMessageHeaderValue(INT iMessageHeaderIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 34+10000, iMessageHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageHeaderValue(INT iMessageHeaderIndex, LPCWSTR lpszMessageHeaderValue) {
      return IPWorks_IMAP_Set(m_pObj, 34+10000, iMessageHeaderIndex, (LPVOID)lpszMessageHeaderValue, 0);
    }

    inline LPWSTR GetMessageHeadersString() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 35+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageHeadersString(LPCWSTR lpszMessageHeadersString) {
      return IPWorks_IMAP_Set(m_pObj, 35+10000, 0, (LPVOID)lpszMessageHeadersString, 0);
    }

    inline LPWSTR GetMessageId() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 36+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessageInfoCount() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 37, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMessageInfoDate(INT iMessageInfoIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 38+10000, iMessageInfoIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageInfoFlags(INT iMessageInfoIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 39+10000, iMessageInfoIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageInfoFrom(INT iMessageInfoIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 40+10000, iMessageInfoIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageInfoMessageId(INT iMessageInfoIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 41+10000, iMessageInfoIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LONG64 GetMessageInfoSize(INT iMessageInfoIndex) {
      LONG64 retVal;
      IPWorks_IMAP_Get(m_pObj, 42, iMessageInfoIndex, NULL, &retVal);
      return retVal;
    }

    inline LPWSTR GetMessageInfoSubject(INT iMessageInfoIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 43+10000, iMessageInfoIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageInReplyTo() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 44+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageNetId() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 45+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessagePartCount() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 46, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMessagePartContentDisposition(INT iMessagePartIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 47+10000, iMessagePartIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessagePartContentEncoding(INT iMessagePartIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 48+10000, iMessagePartIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessagePartContentId(INT iMessagePartIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 49+10000, iMessagePartIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessagePartContentType(INT iMessagePartIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 50+10000, iMessagePartIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessagePartFilename(INT iMessagePartIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 51+10000, iMessagePartIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessagePartId(INT iMessagePartIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 52+10000, iMessagePartIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessagePartMultipartMode(INT iMessagePartIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 53+10000, iMessagePartIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessagePartParameters(INT iMessagePartIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 54+10000, iMessagePartIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LONG64 GetMessagePartSize(INT iMessagePartIndex) {
      LONG64 retVal;
      IPWorks_IMAP_Get(m_pObj, 55, iMessagePartIndex, NULL, &retVal);
      return retVal;
    }

    inline INT GetMessageRecipientCount() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 56, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMessageRecipientAddress(INT iRecipientIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 57+10000, iRecipientIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageRecipientName(INT iRecipientIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 58+10000, iRecipientIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageRecipientOptions(INT iRecipientIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 59+10000, iRecipientIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessageRecipientType(INT iRecipientIndex) {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 60, iRecipientIndex, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetMessageReplyTo() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 61+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageSender() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 62+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageSet() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 63+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageSet(LPCWSTR lpszMessageSet) {
      return IPWorks_IMAP_Set(m_pObj, 63+10000, 0, (LPVOID)lpszMessageSet, 0);
    }

    inline LONG64 GetMessageSize() {
      LONG64 retVal;
      IPWorks_IMAP_Get(m_pObj, 64, 0, NULL, &retVal);
      return retVal;
    }

    inline LPWSTR GetMessageSubject() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 65+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetMessageText() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 66+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageText(LPCWSTR lpszMessageText) {
      return IPWorks_IMAP_Set(m_pObj, 66+10000, 0, (LPVOID)lpszMessageText, 0);
    }

    inline BOOL GetOverwrite() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 67, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetOverwrite(BOOL bOverwrite) {
      LPVOID val = (LPVOID)(bOverwrite);
      return IPWorks_IMAP_Set(m_pObj, 67, 0, val, 0);
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 68+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_IMAP_Set(m_pObj, 68+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline BOOL GetPeekMode() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 69, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetPeekMode(BOOL bPeekMode) {
      LPVOID val = (LPVOID)(bPeekMode);
      return IPWorks_IMAP_Set(m_pObj, 69, 0, val, 0);
    }

    inline INT GetRecentMessageCount() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 70, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetSortCriteria() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 71+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSortCriteria(LPCWSTR lpszSortCriteria) {
      return IPWorks_IMAP_Set(m_pObj, 71+10000, 0, (LPVOID)lpszSortCriteria, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_IMAP_Get(m_pObj, 72, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_IMAP_Set(m_pObj, 72, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_IMAP_Get(m_pObj, 73, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_IMAP_Set(m_pObj, 73, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_IMAP_Get(m_pObj, 74, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_IMAP_Set(m_pObj, 74, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 75+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_IMAP_Set(m_pObj, 75+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 76, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_IMAP_Set(m_pObj, 76, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 77+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_IMAP_Set(m_pObj, 77+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 78, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_IMAP_Set(m_pObj, 78, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_IMAP_Get(m_pObj, 79, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 80, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_IMAP_Set(m_pObj, 80, 0, val, 0);
    }

    inline LONG64 GetStartByte() {
      LONG64 retVal;
      IPWorks_IMAP_Get(m_pObj, 81, 0, NULL, &retVal);
      return retVal;
    }
    inline INT SetStartByte(LONG64 lStartByte) {
      LPVOID val = (LPVOID)(&lStartByte);
      return IPWorks_IMAP_Set(m_pObj, 81, 0, val, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 82, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_IMAP_Set(m_pObj, 82, 0, val, 0);
    }

    inline BOOL GetUIDMode() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 83, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetUIDMode(BOOL bUIDMode) {
      LPVOID val = (LPVOID)(bUIDMode);
      return IPWorks_IMAP_Set(m_pObj, 83, 0, val, 0);
    }

    inline LPWSTR GetUIDValidity() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 84+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_IMAP_Get(m_pObj, 85+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_IMAP_Set(m_pObj, 85+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline INT AddMessageFlags(LPCWSTR lpszFlags) {
      LPVOID param[1+1] = {(LPVOID)lpszFlags, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
    }

    inline INT AppendToMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT CheckMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT CloseMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_IMAP_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Connect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT CopyToMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT CreateMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT DeleteFromMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT DeleteMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 11+10000, 0, param, cbparam, NULL);
    }

    inline INT DeleteMailboxACL(LPCWSTR lpszUser) {
      LPVOID param[1+1] = {(LPVOID)lpszUser, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 12+10000, 1, param, cbparam, NULL);
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 13+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 14+10000, 0, param, cbparam, NULL);
    }

    inline INT ExamineMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 15+10000, 0, param, cbparam, NULL);
    }

    inline INT ExpungeMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 16+10000, 0, param, cbparam, NULL);
    }

    inline INT FetchMessageHeaders() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 17+10000, 0, param, cbparam, NULL);
    }

    inline INT FetchMessageInfo() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 18+10000, 0, param, cbparam, NULL);
    }

    inline INT FetchMessagePart(LPCWSTR lpszPartId) {
      LPVOID param[1+1] = {(LPVOID)lpszPartId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 19+10000, 1, param, cbparam, NULL);
    }

    inline INT FetchMessagePartHeaders(LPCWSTR lpszPartId) {
      LPVOID param[1+1] = {(LPVOID)lpszPartId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 20+10000, 1, param, cbparam, NULL);
    }

    inline INT FetchMessageText() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 21+10000, 0, param, cbparam, NULL);
    }

    inline INT GetMailboxACL() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 22+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 23+10000, 0, param, cbparam, NULL);
    }

    inline INT ListMailboxes() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 24+10000, 0, param, cbparam, NULL);
    }

    inline INT ListSubscribedMailboxes() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 25+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR LocalizeDate(LPCWSTR lpszDateTime) {
      LPVOID param[1+1] = {(LPVOID)lpszDateTime, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_IMAP_Do(m_pObj, 26+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT MoveToMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 27+10000, 0, param, cbparam, NULL);
    }

    inline INT Noop() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 28+10000, 0, param, cbparam, NULL);
    }

    inline INT RenameMailbox(LPCWSTR lpszNewName) {
      LPVOID param[1+1] = {(LPVOID)lpszNewName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 29+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 30+10000, 0, param, cbparam, NULL);
    }

    inline INT ResetMessageFlags() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 31+10000, 0, param, cbparam, NULL);
    }

    inline INT SearchMailbox(LPCWSTR lpszSearchCriteria) {
      LPVOID param[1+1] = {(LPVOID)lpszSearchCriteria, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 32+10000, 1, param, cbparam, NULL);
    }

    inline INT SelectMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 33+10000, 0, param, cbparam, NULL);
    }

    inline INT SetMailboxACL(LPCWSTR lpszUser, LPCWSTR lpszRights) {
      LPVOID param[2+1] = {(LPVOID)lpszUser, (LPVOID)lpszRights, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_IMAP_Do(m_pObj, 34+10000, 2, param, cbparam, NULL);
    }

    inline INT SetMessageStream(IPWorksStream* sMessageStream) {
      LPVOID param[1+1] = {(LPVOID)sMessageStream, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_IMAP_Do(m_pObj, 35+10000, 1, param, cbparam, NULL);
    }

    inline INT StartIdle() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 36+10000, 0, param, cbparam, NULL);
    }

    inline INT StopIdle() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 37+10000, 0, param, cbparam, NULL);
    }

    inline INT SubscribeMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 38+10000, 0, param, cbparam, NULL);
    }

    inline INT UnsetMessageFlags() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 39+10000, 0, param, cbparam, NULL);
    }

    inline INT UnsubscribeMailbox() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_IMAP_Do(m_pObj, 40+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_IMAP_H_
