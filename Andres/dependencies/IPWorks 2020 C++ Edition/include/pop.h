/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_POP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_POP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_POP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_POP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_POP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_POP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_POP_StaticDestroy();

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
} POPConnectionStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} POPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} POPErrorEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} POPHeaderEventParams;

typedef struct {
  int MessageNumber;
  const char *MessageUID;
  int MessageSize;
  int reserved;
} POPMessageListEventParams;

typedef struct {
  int Direction;
  const char *Message;
  int reserved;
} POPPITrailEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} POPSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} POPSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} POPStartTransferEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int EOL;
  int reserved;
} POPTransferEventParams;


class POP {
  public: // Events
    virtual int FireConnectionStatus(POPConnectionStatusEventParams *e) {return 0;}
    virtual int FireEndTransfer(POPEndTransferEventParams *e) {return 0;}
    virtual int FireError(POPErrorEventParams *e) {return 0;}
    virtual int FireHeader(POPHeaderEventParams *e) {return 0;}
    virtual int FireMessageList(POPMessageListEventParams *e) {return 0;}
    virtual int FirePITrail(POPPITrailEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(POPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(POPSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(POPStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(POPTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL POPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          POPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((POP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          POPEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((POP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 3: {
          POPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((POP*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          POPHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((POP*)lpObj)->FireHeader(&e);
          break;
        }
        case 5: {
          POPMessageListEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), 0};
          ret_code = ((POP*)lpObj)->FireMessageList(&e);
          break;
        }
        case 6: {
          POPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((POP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 7: {
          POPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((POP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 8: {
          POPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((POP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 9: {
          POPStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((POP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 10: {
          POPTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((POP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    POP(char *lpOemKey = (char*)IPWORKS_OEMKEY_24) {
      m_pObj = IPWorks_POP_Create(POPEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~POP() {
      IPWorks_POP_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_POP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_POP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_POP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_POP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_POP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetAuthMechanism() {
      void* val = IPWorks_POP_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthMechanism(int iAuthMechanism) {
      void* val = (void*)IPW64CAST(iAuthMechanism);
      return IPWorks_POP_Set(m_pObj, 1, 0, val, 0);
    }

    inline int SetCommand(const char* lpszCommand) {
      return IPWorks_POP_Set(m_pObj, 2, 0, (void*)lpszCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_POP_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_POP_Set(m_pObj, 3, 0, val, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_POP_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_POP_Set(m_pObj, 4, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_POP_Get(m_pObj, 5, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_POP_Set(m_pObj, 5, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_POP_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_POP_Set(m_pObj, 6, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_POP_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_POP_Set(m_pObj, 7, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_POP_Get(m_pObj, 8, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_POP_Set(m_pObj, 8, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_POP_Get(m_pObj, 9, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_POP_Set(m_pObj, 9, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_POP_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetIncludeHeaders() {
      void* val = IPWorks_POP_Get(m_pObj, 11, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetIncludeHeaders(int bIncludeHeaders) {
      void* val = (void*)IPW64CAST(bIncludeHeaders);
      return IPWorks_POP_Set(m_pObj, 11, 0, val, 0);
    }

    inline char* GetLastReply() {
      void* val = IPWorks_POP_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_POP_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_POP_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_POP_Set(m_pObj, 13, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_POP_Set(m_pObj, 13+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_POP_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_POP_Set(m_pObj, 14, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetMailPort() {
      void* val = IPWorks_POP_Get(m_pObj, 15, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMailPort(int iMailPort) {
      void* val = (void*)IPW64CAST(iMailPort);
      return IPWorks_POP_Set(m_pObj, 15, 0, val, 0);
    }

    inline char* GetMailServer() {
      void* val = IPWorks_POP_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMailServer(const char* lpszMailServer) {
      return IPWorks_POP_Set(m_pObj, 16, 0, (void*)lpszMailServer, 0);
    }

    inline int GetMaxLines() {
      void* val = IPWorks_POP_Get(m_pObj, 17, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMaxLines(int iMaxLines) {
      void* val = (void*)IPW64CAST(iMaxLines);
      return IPWorks_POP_Set(m_pObj, 17, 0, val, 0);
    }

    inline int GetMessage(char* &lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_POP_Get(m_pObj, 18, 0, &lenMessage, NULL);
      return lpMessage ? 0 : lenMessage;
    }

    inline char* GetMessageCc() {
      void* val = IPWorks_POP_Get(m_pObj, 19, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetMessageCount() {
      void* val = IPWorks_POP_Get(m_pObj, 20, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMessageDate() {
      void* val = IPWorks_POP_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageFrom() {
      void* val = IPWorks_POP_Get(m_pObj, 22, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetMessageHeaderCount() {
      void* val = IPWorks_POP_Get(m_pObj, 23, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMessageHeaderField(int iMessageHeaderIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 24, iMessageHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageHeaderValue(int iMessageHeaderIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 25, iMessageHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageHeadersString() {
      void* val = IPWorks_POP_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetMessageNumber() {
      void* val = IPWorks_POP_Get(m_pObj, 27, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMessageNumber(int iMessageNumber) {
      void* val = (void*)IPW64CAST(iMessageNumber);
      return IPWorks_POP_Set(m_pObj, 27, 0, val, 0);
    }

    inline int GetMessageRecipientCount() {
      void* val = IPWorks_POP_Get(m_pObj, 28, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMessageRecipientAddress(int iRecipientIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 29, iRecipientIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageRecipientName(int iRecipientIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 30, iRecipientIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageRecipientOptions(int iRecipientIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 31, iRecipientIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetMessageRecipientType(int iRecipientIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 32, iRecipientIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMessageReplyTo() {
      void* val = IPWorks_POP_Get(m_pObj, 33, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetMessageSize() {
      void* val = IPWorks_POP_Get(m_pObj, 34, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetMessageSubject() {
      void* val = IPWorks_POP_Get(m_pObj, 35, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageText() {
      void* val = IPWorks_POP_Get(m_pObj, 36, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageTo() {
      void* val = IPWorks_POP_Get(m_pObj, 37, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetMessageUID() {
      void* val = IPWorks_POP_Get(m_pObj, 38, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_POP_Get(m_pObj, 39, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_POP_Set(m_pObj, 39, 0, (void*)lpszPassword, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_POP_Get(m_pObj, 40, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_POP_Set(m_pObj, 40, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_POP_Get(m_pObj, 41, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_POP_Set(m_pObj, 41, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_POP_Get(m_pObj, 42, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_POP_Set(m_pObj, 42, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_POP_Get(m_pObj, 43, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_POP_Set(m_pObj, 43, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_POP_Get(m_pObj, 44, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_POP_Set(m_pObj, 44, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_POP_Get(m_pObj, 45, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_POP_Set(m_pObj, 45, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_POP_Get(m_pObj, 46, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_POP_Set(m_pObj, 46, 0, val, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_POP_Get(m_pObj, 47, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetSSLStartMode() {
      void* val = IPWorks_POP_Get(m_pObj, 48, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_POP_Set(m_pObj, 48, 0, val, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_POP_Get(m_pObj, 49, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_POP_Set(m_pObj, 49, 0, val, 0);
    }

    inline int64 GetTotalSize() {
      int64 retVal;
      IPWorks_POP_Get(m_pObj, 50, 0, NULL, &retVal);
      return retVal;
    }

    inline char* GetUser() {
      void* val = IPWorks_POP_Get(m_pObj, 51, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_POP_Set(m_pObj, 51, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_POP_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int Delete() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int ListMessageSizes() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline int ListMessageUIDs() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline char* LocalizeDate(const char* lpszDateTime) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDateTime), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_POP_Do(m_pObj, 10, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 11, 0, param, cbparam, NULL);
    }

    inline int Retrieve() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 12, 0, param, cbparam, NULL);
    }

    inline int RetrieveHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 13, 0, param, cbparam, NULL);
    }

    inline int SetMessageStream(IPWorksStream* sMessageStream) {
      void *param[1+1] = {(void*)IPW64CAST(sMessageStream), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_POP_Do(m_pObj, 14, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_POP_H_
