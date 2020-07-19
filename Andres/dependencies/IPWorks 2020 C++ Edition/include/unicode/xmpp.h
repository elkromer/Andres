/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
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
extern "C" void* IPWORKS_CALL IPWorks_XMPP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_XMPP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_XMPP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT BuddyIdx;
  INT reserved;
} XMPPBuddyUpdateEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} XMPPConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} XMPPConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} XMPPDisconnectedEventParams;

typedef struct {
  INT Direction;
  LPCWSTR FileId;
  LPCWSTR Filename;
  BOOL Success;
  INT reserved;
} XMPPEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} XMPPErrorEventParams;

typedef struct {
  LPCWSTR Iq;
  LPCWSTR Id;
  LPCWSTR From;
  LPCWSTR IqType;
  BOOL Ignore;
  INT reserved;
} XMPPIQEventParams;

typedef struct {
  LPCWSTR MessageId;
  LPCWSTR From;
  LPCWSTR Domain;
  LPCWSTR Resource;
  INT MessageType;
  LPCWSTR Subject;
  LPCWSTR MessageThread;
  LPCWSTR MessageText;
  LPCWSTR MessageHTML;
  LPCWSTR Other;
  INT reserved;
} XMPPMessageInEventParams;

typedef struct {
  INT Direction;
  LPCWSTR Pi;
  INT reserved;
} XMPPPITrailEventParams;

typedef struct {
  LPCWSTR User;
  LPCWSTR Domain;
  LPCWSTR Resource;
  INT Availability;
  LPCWSTR Status;
  INT reserved;
} XMPPPresenceEventParams;

typedef struct {
  INT reserved;
} XMPPReadyToSendEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} XMPPSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} XMPPSSLStatusEventParams;

typedef struct {
  INT Direction;
  LPCWSTR FileId;
  LPCWSTR User;
  LPCWSTR Domain;
  LPCWSTR Resource;
  LPWSTR Filename;
  LPCWSTR Datetime;
  LONG64 Size;
  BOOL Accept;
  INT reserved;
} XMPPStartTransferEventParams;

typedef struct {
  LPCWSTR From;
  LPCWSTR Domain;
  BOOL Accept;
  INT reserved;
} XMPPSubscriptionRequestEventParams;

typedef struct {
  INT reserved;
} XMPPSyncEventParams;

typedef struct {
  INT Direction;
  LPCWSTR FileId;
  LPCWSTR Filename;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  BOOL Cancel;
  INT reserved;
} XMPPTransferEventParams;


class XMPP {
  public: // Events
    virtual INT FireBuddyUpdate(XMPPBuddyUpdateEventParams *e) {return 0;}
    virtual INT FireConnected(XMPPConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(XMPPConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(XMPPDisconnectedEventParams *e) {return 0;}
    virtual INT FireEndTransfer(XMPPEndTransferEventParams *e) {return 0;}
    virtual INT FireError(XMPPErrorEventParams *e) {return 0;}
    virtual INT FireIQ(XMPPIQEventParams *e) {return 0;}
    virtual INT FireMessageIn(XMPPMessageInEventParams *e) {return 0;}
    virtual INT FirePITrail(XMPPPITrailEventParams *e) {return 0;}
    virtual INT FirePresence(XMPPPresenceEventParams *e) {return 0;}
    virtual INT FireReadyToSend(XMPPReadyToSendEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(XMPPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(XMPPSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(XMPPStartTransferEventParams *e) {return 0;}
    virtual INT FireSubscriptionRequest(XMPPSubscriptionRequestEventParams *e) {return 0;}
    virtual INT FireSync(XMPPSyncEventParams *e) {return 0;}
    virtual INT FireTransfer(XMPPTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL XMPPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          XMPPBuddyUpdateEventParams e = {(INT)param[0], 0};
          ret_code = ((XMPP*)lpObj)->FireBuddyUpdate(&e);
          break;
        }
        case 2: {
          XMPPConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((XMPP*)lpObj)->FireConnected(&e);
          break;
        }
        case 3: {
          XMPPConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((XMPP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 4: {
          XMPPDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((XMPP*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 5: {
          XMPPEndTransferEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (BOOL)param[3], 0};
          ret_code = ((XMPP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 6: {
          XMPPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((XMPP*)lpObj)->FireError(&e);
          break;
        }
        case 7: {
          XMPPIQEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((XMPP*)lpObj)->FireIQ(&e);
          param[4] = (LPVOID)e.Ignore;
          break;
        }
        case 8: {
          XMPPMessageInEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (INT)param[4], (LPWSTR)param[5], (LPWSTR)param[6], (LPWSTR)param[7], (LPWSTR)param[8], (LPWSTR)param[9], 0};
          ret_code = ((XMPP*)lpObj)->FireMessageIn(&e);
          break;
        }
        case 9: {
          XMPPPITrailEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((XMPP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 10: {
          XMPPPresenceEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (INT)param[3], (LPWSTR)param[4], 0};
          ret_code = ((XMPP*)lpObj)->FirePresence(&e);
          break;
        }
        case 11: {
          XMPPReadyToSendEventParams e = {0};
          ret_code = ((XMPP*)lpObj)->FireReadyToSend(&e);
          break;
        }
        case 12: {
          XMPPSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((XMPP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 13: {
          XMPPSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((XMPP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 14: {
          XMPPStartTransferEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (LPWSTR)IPWorks_EvtStr(param[5], 0, NULL, 2), (LPWSTR)param[6], *(LONG64*)param[7], (BOOL)param[8], 0};
          ret_code = ((XMPP*)lpObj)->FireStartTransfer(&e);
          IPWorks_EvtStr(param[5], 1, (void*)e.Filename, 2);
          param[8] = (LPVOID)e.Accept;
          break;
        }
        case 15: {
          XMPPSubscriptionRequestEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (BOOL)param[2], 0};
          ret_code = ((XMPP*)lpObj)->FireSubscriptionRequest(&e);
          param[2] = (LPVOID)e.Accept;
          break;
        }
        case 16: {
          XMPPSyncEventParams e = {0};
          ret_code = ((XMPP*)lpObj)->FireSync(&e);
          break;
        }
        case 17: {
          XMPPTransferEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], *(LONG64*)param[3], (INT)param[4], (LPSTR)param[5], (INT)cbparam[5], (BOOL)param[6], 0};
          ret_code = ((XMPP*)lpObj)->FireTransfer(&e);
          param[6] = (LPVOID)e.Cancel;
          break;
        }
      }
      return ret_code;
    }

  public:
    XMPP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_70) {
      m_pObj = IPWorks_XMPP_Create(XMPPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~XMPP() {
      IPWorks_XMPP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_XMPP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_XMPP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_XMPP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_XMPP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_XMPP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAuthDomain() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthDomain(LPCWSTR lpszAuthDomain) {
      return IPWorks_XMPP_Set(m_pObj, 1+10000, 0, (LPVOID)lpszAuthDomain, 0);
    }

    inline LPWSTR GetAuthMethods() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthMethods(LPCWSTR lpszAuthMethods) {
      return IPWorks_XMPP_Set(m_pObj, 2+10000, 0, (LPVOID)lpszAuthMethods, 0);
    }

    inline INT GetBuddyCount() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 3, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetBuddyGroup(INT iBuddyIndex) {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 4+10000, iBuddyIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetBuddyGroup(INT iBuddyIndex, LPCWSTR lpszBuddyGroup) {
      return IPWorks_XMPP_Set(m_pObj, 4+10000, iBuddyIndex, (LPVOID)lpszBuddyGroup, 0);
    }

    inline LPWSTR GetBuddyId(INT iBuddyIndex) {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 5+10000, iBuddyIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetBuddyNickName(INT iBuddyIndex) {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 6+10000, iBuddyIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetBuddyNickName(INT iBuddyIndex, LPCWSTR lpszBuddyNickName) {
      return IPWorks_XMPP_Set(m_pObj, 6+10000, iBuddyIndex, (LPVOID)lpszBuddyNickName, 0);
    }

    inline LPWSTR GetBuddyRealName(INT iBuddyIndex) {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 7+10000, iBuddyIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetBuddySubscription(INT iBuddyIndex) {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 8, iBuddyIndex, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 9, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_XMPP_Set(m_pObj, 9, 0, val, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 10, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_XMPP_Set(m_pObj, 10, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 11, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_XMPP_Set(m_pObj, 11, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_XMPP_Set(m_pObj, 12+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_XMPP_Set(m_pObj, 13+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 14, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_XMPP_Set(m_pObj, 14, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_XMPP_Set(m_pObj, 15+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline INT GetIMPort() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 16, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetIMPort(INT iIMPort) {
      LPVOID val = (LPVOID)(iIMPort);
      return IPWorks_XMPP_Set(m_pObj, 16, 0, val, 0);
    }

    inline LPWSTR GetIMServer() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetIMServer(LPCWSTR lpszIMServer) {
      return IPWorks_XMPP_Set(m_pObj, 17+10000, 0, (LPVOID)lpszIMServer, 0);
    }

    inline LPWSTR GetLocalDirectory() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalDirectory(LPCWSTR lpszLocalDirectory) {
      return IPWorks_XMPP_Set(m_pObj, 18+10000, 0, (LPVOID)lpszLocalDirectory, 0);
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_XMPP_Set(m_pObj, 19+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_XMPP_Set(m_pObj, 20+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetMessageHTML() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageHTML(LPCWSTR lpszMessageHTML) {
      return IPWorks_XMPP_Set(m_pObj, 21+10000, 0, (LPVOID)lpszMessageHTML, 0);
    }

    inline LPWSTR GetMessageOtherData() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageOtherData(LPCWSTR lpszMessageOtherData) {
      return IPWorks_XMPP_Set(m_pObj, 22+10000, 0, (LPVOID)lpszMessageOtherData, 0);
    }

    inline LPWSTR GetMessageSubject() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 23+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageSubject(LPCWSTR lpszMessageSubject) {
      return IPWorks_XMPP_Set(m_pObj, 23+10000, 0, (LPVOID)lpszMessageSubject, 0);
    }

    inline LPWSTR GetMessageText() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageText(LPCWSTR lpszMessageText) {
      return IPWorks_XMPP_Set(m_pObj, 24+10000, 0, (LPVOID)lpszMessageText, 0);
    }

    inline LPWSTR GetMessageThread() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageThread(LPCWSTR lpszMessageThread) {
      return IPWorks_XMPP_Set(m_pObj, 25+10000, 0, (LPVOID)lpszMessageThread, 0);
    }

    inline INT GetMessageType() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 26, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMessageType(INT iMessageType) {
      LPVOID val = (LPVOID)(iMessageType);
      return IPWorks_XMPP_Set(m_pObj, 26, 0, val, 0);
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 27+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_XMPP_Set(m_pObj, 27+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetPresence() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 28, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetPresence(INT iPresence) {
      LPVOID val = (LPVOID)(iPresence);
      return IPWorks_XMPP_Set(m_pObj, 28, 0, val, 0);
    }

    inline LPWSTR GetResource() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetResource(LPCWSTR lpszResource) {
      return IPWorks_XMPP_Set(m_pObj, 29+10000, 0, (LPVOID)lpszResource, 0);
    }

    inline LPWSTR GetServerDomain() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 30+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetServerDomain(LPCWSTR lpszServerDomain) {
      return IPWorks_XMPP_Set(m_pObj, 30+10000, 0, (LPVOID)lpszServerDomain, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_XMPP_Get(m_pObj, 31, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_XMPP_Set(m_pObj, 31, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_XMPP_Get(m_pObj, 32, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_XMPP_Set(m_pObj, 32, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_XMPP_Get(m_pObj, 33, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_XMPP_Set(m_pObj, 33, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 34+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_XMPP_Set(m_pObj, 34+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 35, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_XMPP_Set(m_pObj, 35, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 36+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_XMPP_Set(m_pObj, 36+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 37, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_XMPP_Set(m_pObj, 37, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_XMPP_Get(m_pObj, 38, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 39, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_XMPP_Set(m_pObj, 39, 0, val, 0);
    }

    inline LPWSTR GetStatus() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 40+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetStatus(LPCWSTR lpszStatus) {
      return IPWorks_XMPP_Set(m_pObj, 40+10000, 0, (LPVOID)lpszStatus, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 41, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_XMPP_Set(m_pObj, 41, 0, val, 0);
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 42+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_XMPP_Set(m_pObj, 42+10000, 0, (LPVOID)lpszUser, 0);
    }

    inline LPWSTR GetUserDomain() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 43+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUserDomain(LPCWSTR lpszUserDomain) {
      return IPWorks_XMPP_Set(m_pObj, 43+10000, 0, (LPVOID)lpszUserDomain, 0);
    }

    inline INT GetUserInfoCount() {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 44, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetUserInfoCount(INT iUserInfoCount) {
      LPVOID val = (LPVOID)(iUserInfoCount);
      return IPWorks_XMPP_Set(m_pObj, 44, 0, val, 0);
    }

    inline LPWSTR GetUserInfoField(INT iFieldIndex) {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 45+10000, iFieldIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUserInfoField(INT iFieldIndex, LPCWSTR lpszUserInfoField) {
      return IPWorks_XMPP_Set(m_pObj, 45+10000, iFieldIndex, (LPVOID)lpszUserInfoField, 0);
    }

    inline LPWSTR GetUserInfoValue(INT iFieldIndex) {
      LPVOID val = IPWorks_XMPP_Get(m_pObj, 46+10000, iFieldIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUserInfoValue(INT iFieldIndex, LPCWSTR lpszUserInfoValue) {
      return IPWorks_XMPP_Set(m_pObj, 46+10000, iFieldIndex, (LPVOID)lpszUserInfoValue, 0);
    }

  public: // Methods
    inline INT Add(LPCWSTR lpszJabberId, LPCWSTR lpszName, LPCWSTR lpszGroups) {
      LPVOID param[3+1] = {(LPVOID)lpszJabberId, (LPVOID)lpszName, (LPVOID)lpszGroups, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 2+10000, 3, param, cbparam, NULL);
    }

    inline INT Cancel(LPCWSTR lpszJabberId) {
      LPVOID param[1+1] = {(LPVOID)lpszJabberId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 3+10000, 1, param, cbparam, NULL);
    }

    inline INT ChangePassword(LPCWSTR lpszPassword) {
      LPVOID param[1+1] = {(LPVOID)lpszPassword, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 4+10000, 1, param, cbparam, NULL);
    }

    inline INT ChangePresence(INT iPresenceCode, LPCWSTR lpszStatus) {
      LPVOID param[2+1] = {(LPVOID)iPresenceCode, (LPVOID)lpszStatus, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 5+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_XMPP_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Connect(LPCWSTR lpszUser, LPCWSTR lpszPassword) {
      LPVOID param[2+1] = {(LPVOID)lpszUser, (LPVOID)lpszPassword, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 7+10000, 2, param, cbparam, NULL);
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT ProbePresence(LPCWSTR lpszJabberId) {
      LPVOID param[1+1] = {(LPVOID)lpszJabberId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 11+10000, 1, param, cbparam, NULL);
    }

    inline INT QueryRegister(LPCWSTR lpszXMPPServer) {
      LPVOID param[1+1] = {(LPVOID)lpszXMPPServer, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 12+10000, 1, param, cbparam, NULL);
    }

    inline INT Register(LPCWSTR lpszXMPPServer) {
      LPVOID param[1+1] = {(LPVOID)lpszXMPPServer, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 13+10000, 1, param, cbparam, NULL);
    }

    inline INT Remove(LPCWSTR lpszJabberId, LPCWSTR lpszName, LPCWSTR lpszGroup) {
      LPVOID param[3+1] = {(LPVOID)lpszJabberId, (LPVOID)lpszName, (LPVOID)lpszGroup, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 14+10000, 3, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 15+10000, 0, param, cbparam, NULL);
    }

    inline INT RetrieveRoster() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 16+10000, 0, param, cbparam, NULL);
    }

    inline INT SendCommand(LPCWSTR lpszCommand) {
      LPVOID param[1+1] = {(LPVOID)lpszCommand, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 17+10000, 1, param, cbparam, NULL);
    }

    inline INT SendFile(LPCWSTR lpszJabberId) {
      LPVOID param[1+1] = {(LPVOID)lpszJabberId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 18+10000, 1, param, cbparam, NULL);
    }

    inline LPWSTR SendMessage(LPCWSTR lpszJabberId) {
      LPVOID param[1+1] = {(LPVOID)lpszJabberId, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_XMPP_Do(m_pObj, 19+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT SetUserInfoField(LPCWSTR lpszField, LPCWSTR lpszValue) {
      LPVOID param[2+1] = {(LPVOID)lpszField, (LPVOID)lpszValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 22+10000, 2, param, cbparam, NULL);
    }

    inline INT SubscribeTo(LPCWSTR lpszJabberId) {
      LPVOID param[1+1] = {(LPVOID)lpszJabberId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 23+10000, 1, param, cbparam, NULL);
    }

    inline INT Unregister() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 24+10000, 0, param, cbparam, NULL);
    }

    inline INT UnsubscribeTo(LPCWSTR lpszJabberId) {
      LPVOID param[1+1] = {(LPVOID)lpszJabberId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 25+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_XMPP_H_
