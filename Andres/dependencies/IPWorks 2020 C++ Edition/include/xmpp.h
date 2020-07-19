/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_XMPP_H_
#define _IPWORKS_XMPP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//XMPPBuddySubscriptions
#define ST_NONE                                            0
#define ST_TO                                              1
#define ST_FROM                                            2
#define ST_BOTH                                            3
#define ST_REMOVE                                          4

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TJabberMessageTypes
#define MT_NORMAL                                          0
#define MT_CHAT                                            1
#define MT_GROUP_CHAT                                      2
#define MT_HEADLINE                                        3
#define MT_ERROR                                           4

//TJabberPresenceCodes
#define PC_OFFLINE                                         0
#define PC_CHAT                                            1
#define PC_AWAY                                            2
#define PC_XA                                              3
#define PC_DND                                             4

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


extern "C" void* IPWORKS_CALL IPWorks_XMPP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_XMPP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_XMPP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_XMPP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  int BuddyIdx;
  int reserved;
} XMPPBuddyUpdateEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} XMPPConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} XMPPConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} XMPPDisconnectedEventParams;

typedef struct {
  int Direction;
  const char *FileId;
  const char *Filename;
  int Success;
  int reserved;
} XMPPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} XMPPErrorEventParams;

typedef struct {
  const char *Iq;
  const char *Id;
  const char *From;
  const char *IqType;
  int Ignore;
  int reserved;
} XMPPIQEventParams;

typedef struct {
  const char *MessageId;
  const char *From;
  const char *Domain;
  const char *Resource;
  int MessageType;
  const char *Subject;
  const char *MessageThread;
  const char *MessageText;
  const char *MessageHTML;
  const char *Other;
  int reserved;
} XMPPMessageInEventParams;

typedef struct {
  int Direction;
  const char *Pi;
  int reserved;
} XMPPPITrailEventParams;

typedef struct {
  const char *User;
  const char *Domain;
  const char *Resource;
  int Availability;
  const char *Status;
  int reserved;
} XMPPPresenceEventParams;

typedef struct {
  int reserved;
} XMPPReadyToSendEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} XMPPSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} XMPPSSLStatusEventParams;

typedef struct {
  int Direction;
  const char *FileId;
  const char *User;
  const char *Domain;
  const char *Resource;
  char *Filename;
  const char *Datetime;
  int64 Size;
  int Accept;
  int reserved;
} XMPPStartTransferEventParams;

typedef struct {
  const char *From;
  const char *Domain;
  int Accept;
  int reserved;
} XMPPSubscriptionRequestEventParams;

typedef struct {
  int reserved;
} XMPPSyncEventParams;

typedef struct {
  int Direction;
  const char *FileId;
  const char *Filename;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int Cancel;
  int reserved;
} XMPPTransferEventParams;


class XMPP {
  public: // Events
    virtual int FireBuddyUpdate(XMPPBuddyUpdateEventParams *e) {return 0;}
    virtual int FireConnected(XMPPConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(XMPPConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(XMPPDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(XMPPEndTransferEventParams *e) {return 0;}
    virtual int FireError(XMPPErrorEventParams *e) {return 0;}
    virtual int FireIQ(XMPPIQEventParams *e) {return 0;}
    virtual int FireMessageIn(XMPPMessageInEventParams *e) {return 0;}
    virtual int FirePITrail(XMPPPITrailEventParams *e) {return 0;}
    virtual int FirePresence(XMPPPresenceEventParams *e) {return 0;}
    virtual int FireReadyToSend(XMPPReadyToSendEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(XMPPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(XMPPSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(XMPPStartTransferEventParams *e) {return 0;}
    virtual int FireSubscriptionRequest(XMPPSubscriptionRequestEventParams *e) {return 0;}
    virtual int FireSync(XMPPSyncEventParams *e) {return 0;}
    virtual int FireTransfer(XMPPTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL XMPPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          XMPPBuddyUpdateEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((XMPP*)lpObj)->FireBuddyUpdate(&e);
          break;
        }
        case 2: {
          XMPPConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((XMPP*)lpObj)->FireConnected(&e);
          break;
        }
        case 3: {
          XMPPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((XMPP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 4: {
          XMPPDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((XMPP*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 5: {
          XMPPEndTransferEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), 0};
          ret_code = ((XMPP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 6: {
          XMPPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((XMPP*)lpObj)->FireError(&e);
          break;
        }
        case 7: {
          XMPPIQEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((XMPP*)lpObj)->FireIQ(&e);
          param[4] = (void*)IPW64CAST(e.Ignore);
          break;
        }
        case 8: {
          XMPPMessageInEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), (char*)IPW64CAST(param[7]), (char*)IPW64CAST(param[8]), (char*)IPW64CAST(param[9]), 0};
          ret_code = ((XMPP*)lpObj)->FireMessageIn(&e);
          break;
        }
        case 9: {
          XMPPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((XMPP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 10: {
          XMPPPresenceEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), 0};
          ret_code = ((XMPP*)lpObj)->FirePresence(&e);
          break;
        }
        case 11: {
          XMPPReadyToSendEventParams e = {0};
          ret_code = ((XMPP*)lpObj)->FireReadyToSend(&e);
          break;
        }
        case 12: {
          XMPPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((XMPP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 13: {
          XMPPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((XMPP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 14: {
          XMPPStartTransferEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPWorks_EvtStr(param[5], 0, NULL, 1), (char*)IPW64CAST(param[6]), *(int64*)IPW64CAST(param[7]), (int)IPW64CAST(param[8]), 0};
          ret_code = ((XMPP*)lpObj)->FireStartTransfer(&e);
          IPWorks_EvtStr(param[5], 1, (void*)e.Filename, 1);
          param[8] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 15: {
          XMPPSubscriptionRequestEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), 0};
          ret_code = ((XMPP*)lpObj)->FireSubscriptionRequest(&e);
          param[2] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 16: {
          XMPPSyncEventParams e = {0};
          ret_code = ((XMPP*)lpObj)->FireSync(&e);
          break;
        }
        case 17: {
          XMPPTransferEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), *(int64*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (int)IPW64CAST(cbparam[5]), (int)IPW64CAST(param[6]), 0};
          ret_code = ((XMPP*)lpObj)->FireTransfer(&e);
          param[6] = (void*)IPW64CAST(e.Cancel);
          break;
        }
      }
      return ret_code;
    }

  public:
    XMPP(char *lpOemKey = (char*)IPWORKS_OEMKEY_70) {
      m_pObj = IPWorks_XMPP_Create(XMPPEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~XMPP() {
      IPWorks_XMPP_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_XMPP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_XMPP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_XMPP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_XMPP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_XMPP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetAuthDomain() {
      void* val = IPWorks_XMPP_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthDomain(const char* lpszAuthDomain) {
      return IPWorks_XMPP_Set(m_pObj, 1, 0, (void*)lpszAuthDomain, 0);
    }

    inline char* GetAuthMethods() {
      void* val = IPWorks_XMPP_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthMethods(const char* lpszAuthMethods) {
      return IPWorks_XMPP_Set(m_pObj, 2, 0, (void*)lpszAuthMethods, 0);
    }

    inline int GetBuddyCount() {
      void* val = IPWorks_XMPP_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetBuddyGroup(int iBuddyIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 4, iBuddyIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetBuddyGroup(int iBuddyIndex, const char* lpszBuddyGroup) {
      return IPWorks_XMPP_Set(m_pObj, 4, iBuddyIndex, (void*)lpszBuddyGroup, 0);
    }

    inline char* GetBuddyId(int iBuddyIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 5, iBuddyIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetBuddyNickName(int iBuddyIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 6, iBuddyIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetBuddyNickName(int iBuddyIndex, const char* lpszBuddyNickName) {
      return IPWorks_XMPP_Set(m_pObj, 6, iBuddyIndex, (void*)lpszBuddyNickName, 0);
    }

    inline char* GetBuddyRealName(int iBuddyIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 7, iBuddyIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetBuddySubscription(int iBuddyIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 8, iBuddyIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetConnected() {
      void* val = IPWorks_XMPP_Get(m_pObj, 9, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_XMPP_Set(m_pObj, 9, 0, val, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_XMPP_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_XMPP_Set(m_pObj, 10, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_XMPP_Get(m_pObj, 11, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_XMPP_Set(m_pObj, 11, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_XMPP_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_XMPP_Set(m_pObj, 12, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_XMPP_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_XMPP_Set(m_pObj, 13, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_XMPP_Get(m_pObj, 14, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_XMPP_Set(m_pObj, 14, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_XMPP_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_XMPP_Set(m_pObj, 15, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetIMPort() {
      void* val = IPWorks_XMPP_Get(m_pObj, 16, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetIMPort(int iIMPort) {
      void* val = (void*)IPW64CAST(iIMPort);
      return IPWorks_XMPP_Set(m_pObj, 16, 0, val, 0);
    }

    inline char* GetIMServer() {
      void* val = IPWorks_XMPP_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetIMServer(const char* lpszIMServer) {
      return IPWorks_XMPP_Set(m_pObj, 17, 0, (void*)lpszIMServer, 0);
    }

    inline char* GetLocalDirectory() {
      void* val = IPWorks_XMPP_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalDirectory(const char* lpszLocalDirectory) {
      return IPWorks_XMPP_Set(m_pObj, 18, 0, (void*)lpszLocalDirectory, 0);
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_XMPP_Get(m_pObj, 19, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_XMPP_Set(m_pObj, 19, 0, (void*)lpszLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_XMPP_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_XMPP_Set(m_pObj, 20, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetMessageHTML() {
      void* val = IPWorks_XMPP_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageHTML(const char* lpszMessageHTML) {
      return IPWorks_XMPP_Set(m_pObj, 21, 0, (void*)lpszMessageHTML, 0);
    }

    inline char* GetMessageOtherData() {
      void* val = IPWorks_XMPP_Get(m_pObj, 22, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageOtherData(const char* lpszMessageOtherData) {
      return IPWorks_XMPP_Set(m_pObj, 22, 0, (void*)lpszMessageOtherData, 0);
    }

    inline char* GetMessageSubject() {
      void* val = IPWorks_XMPP_Get(m_pObj, 23, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageSubject(const char* lpszMessageSubject) {
      return IPWorks_XMPP_Set(m_pObj, 23, 0, (void*)lpszMessageSubject, 0);
    }

    inline char* GetMessageText() {
      void* val = IPWorks_XMPP_Get(m_pObj, 24, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageText(const char* lpszMessageText) {
      return IPWorks_XMPP_Set(m_pObj, 24, 0, (void*)lpszMessageText, 0);
    }

    inline char* GetMessageThread() {
      void* val = IPWorks_XMPP_Get(m_pObj, 25, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageThread(const char* lpszMessageThread) {
      return IPWorks_XMPP_Set(m_pObj, 25, 0, (void*)lpszMessageThread, 0);
    }

    inline int GetMessageType() {
      void* val = IPWorks_XMPP_Get(m_pObj, 26, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMessageType(int iMessageType) {
      void* val = (void*)IPW64CAST(iMessageType);
      return IPWorks_XMPP_Set(m_pObj, 26, 0, val, 0);
    }

    inline char* GetPassword() {
      void* val = IPWorks_XMPP_Get(m_pObj, 27, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_XMPP_Set(m_pObj, 27, 0, (void*)lpszPassword, 0);
    }

    inline int GetPresence() {
      void* val = IPWorks_XMPP_Get(m_pObj, 28, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetPresence(int iPresence) {
      void* val = (void*)IPW64CAST(iPresence);
      return IPWorks_XMPP_Set(m_pObj, 28, 0, val, 0);
    }

    inline char* GetResource() {
      void* val = IPWorks_XMPP_Get(m_pObj, 29, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetResource(const char* lpszResource) {
      return IPWorks_XMPP_Set(m_pObj, 29, 0, (void*)lpszResource, 0);
    }

    inline char* GetServerDomain() {
      void* val = IPWorks_XMPP_Get(m_pObj, 30, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetServerDomain(const char* lpszServerDomain) {
      return IPWorks_XMPP_Set(m_pObj, 30, 0, (void*)lpszServerDomain, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_XMPP_Get(m_pObj, 31, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_XMPP_Set(m_pObj, 31, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_XMPP_Get(m_pObj, 32, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_XMPP_Set(m_pObj, 32, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_XMPP_Get(m_pObj, 33, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_XMPP_Set(m_pObj, 33, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_XMPP_Get(m_pObj, 34, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_XMPP_Set(m_pObj, 34, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_XMPP_Get(m_pObj, 35, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_XMPP_Set(m_pObj, 35, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_XMPP_Get(m_pObj, 36, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_XMPP_Set(m_pObj, 36, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_XMPP_Get(m_pObj, 37, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_XMPP_Set(m_pObj, 37, 0, val, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_XMPP_Get(m_pObj, 38, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetSSLStartMode() {
      void* val = IPWorks_XMPP_Get(m_pObj, 39, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_XMPP_Set(m_pObj, 39, 0, val, 0);
    }

    inline char* GetStatus() {
      void* val = IPWorks_XMPP_Get(m_pObj, 40, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetStatus(const char* lpszStatus) {
      return IPWorks_XMPP_Set(m_pObj, 40, 0, (void*)lpszStatus, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_XMPP_Get(m_pObj, 41, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_XMPP_Set(m_pObj, 41, 0, val, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_XMPP_Get(m_pObj, 42, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_XMPP_Set(m_pObj, 42, 0, (void*)lpszUser, 0);
    }

    inline char* GetUserDomain() {
      void* val = IPWorks_XMPP_Get(m_pObj, 43, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUserDomain(const char* lpszUserDomain) {
      return IPWorks_XMPP_Set(m_pObj, 43, 0, (void*)lpszUserDomain, 0);
    }

    inline int GetUserInfoCount() {
      void* val = IPWorks_XMPP_Get(m_pObj, 44, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetUserInfoCount(int iUserInfoCount) {
      void* val = (void*)IPW64CAST(iUserInfoCount);
      return IPWorks_XMPP_Set(m_pObj, 44, 0, val, 0);
    }

    inline char* GetUserInfoField(int iFieldIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 45, iFieldIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetUserInfoField(int iFieldIndex, const char* lpszUserInfoField) {
      return IPWorks_XMPP_Set(m_pObj, 45, iFieldIndex, (void*)lpszUserInfoField, 0);
    }

    inline char* GetUserInfoValue(int iFieldIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 46, iFieldIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetUserInfoValue(int iFieldIndex, const char* lpszUserInfoValue) {
      return IPWorks_XMPP_Set(m_pObj, 46, iFieldIndex, (void*)lpszUserInfoValue, 0);
    }

  public: // Methods
    inline int Add(const char* lpszJabberId, const char* lpszName, const char* lpszGroups) {
      void *param[3+1] = {(void*)IPW64CAST(lpszJabberId), (void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszGroups), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 2, 3, param, cbparam, NULL);
    }

    inline int Cancel(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 3, 1, param, cbparam, NULL);
    }

    inline int ChangePassword(const char* lpszPassword) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPassword), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 4, 1, param, cbparam, NULL);
    }

    inline int ChangePresence(int iPresenceCode, const char* lpszStatus) {
      void *param[2+1] = {(void*)IPW64CAST(iPresenceCode), (void*)IPW64CAST(lpszStatus), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 5, 2, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMPP_Do(m_pObj, 6, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Connect(const char* lpszUser, const char* lpszPassword) {
      void *param[2+1] = {(void*)IPW64CAST(lpszUser), (void*)IPW64CAST(lpszPassword), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 7, 2, param, cbparam, NULL);
    }

    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int ProbePresence(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 11, 1, param, cbparam, NULL);
    }

    inline int QueryRegister(const char* lpszXMPPServer) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXMPPServer), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 12, 1, param, cbparam, NULL);
    }

    inline int Register(const char* lpszXMPPServer) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXMPPServer), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 13, 1, param, cbparam, NULL);
    }

    inline int Remove(const char* lpszJabberId, const char* lpszName, const char* lpszGroup) {
      void *param[3+1] = {(void*)IPW64CAST(lpszJabberId), (void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszGroup), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 14, 3, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 15, 0, param, cbparam, NULL);
    }

    inline int RetrieveRoster() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 16, 0, param, cbparam, NULL);
    }

    inline int SendCommand(const char* lpszCommand) {
      void *param[1+1] = {(void*)IPW64CAST(lpszCommand), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 17, 1, param, cbparam, NULL);
    }

    inline int SendFile(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 18, 1, param, cbparam, NULL);
    }

    inline char* SendMessage(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMPP_Do(m_pObj, 19, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int SetUserInfoField(const char* lpszField, const char* lpszValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszField), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 22, 2, param, cbparam, NULL);
    }

    inline int SubscribeTo(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 23, 1, param, cbparam, NULL);
    }

    inline int Unregister() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 24, 0, param, cbparam, NULL);
    }

    inline int UnsubscribeTo(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 25, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_XMPP_H_
