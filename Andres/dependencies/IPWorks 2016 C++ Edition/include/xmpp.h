/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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

//TSSLStartMode
#define SSL_AUTOMATIC                                      0
#define SSL_IMPLICIT                                       1
#define SSL_EXPLICIT                                       2
#define SSL_NONE                                           3


extern "C" void* IPWORKS_CALL IPWorks_XMPP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_XMPP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_XMPP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMPP_GetLastErrorCode(void *lpObj);
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
  const char* Description;
  int reserved;
} XMPPConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} XMPPConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} XMPPDisconnectedEventParams;

typedef struct {
  int Direction;
  const char* FileId;
  const char* Filename;
  int Success;
  int reserved;
} XMPPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} XMPPErrorEventParams;

typedef struct {
  const char* Iq;
  const char* Id;
  const char* From;
  const char* IqType;
  int Ignore;
  int reserved;
} XMPPIQEventParams;

typedef struct {
  const char* MessageId;
  const char* From;
  const char* Domain;
  const char* Resource;
  int MessageType;
  const char* Subject;
  const char* MessageThread;
  const char* MessageText;
  const char* MessageHTML;
  const char* Other;
  int reserved;
} XMPPMessageInEventParams;

typedef struct {
  int Direction;
  const char* Pi;
  int reserved;
} XMPPPITrailEventParams;

typedef struct {
  const char* User;
  const char* Domain;
  const char* Resource;
  int Availability;
  const char* Status;
  int reserved;
} XMPPPresenceEventParams;

typedef struct {
  int reserved;
} XMPPReadyToSendEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} XMPPSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} XMPPSSLStatusEventParams;

typedef struct {
  int Direction;
  const char* FileId;
  const char* User;
  const char* Domain;
  const char* Resource;
  const char* Filename;
  const char* Datetime;
  ns_int64 Size;
  int Accept;
  int reserved;
} XMPPStartTransferEventParams;

typedef struct {
  const char* From;
  const char* Domain;
  int Accept;
  int reserved;
} XMPPSubscriptionRequestEventParams;

typedef struct {
  int reserved;
} XMPPSyncEventParams;

typedef struct {
  int Direction;
  const char* FileId;
  const char* Filename;
  ns_int64 BytesTransferred;
  int PercentDone;
  const char* Text;
  int Cancel;
  int lenText;
  int reserved;
} XMPPTransferEventParams;



class XMPP {
  
  public: //events
  
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
      if (event_id > 10000) return ((XMPP*)lpObj)->XMPPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            XMPPBuddyUpdateEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((XMPP*)lpObj)->FireBuddyUpdate(&e);
            break;
         }
         case 2: {
            XMPPConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XMPP*)lpObj)->FireConnected(&e);
            break;
         }
         case 3: {
            XMPPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((XMPP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 4: {
            XMPPDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XMPP*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 5: {
            XMPPEndTransferEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = ((XMPP*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 6: {
            XMPPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XMPP*)lpObj)->FireError(&e);
            break;
         }
         case 7: {
            XMPPIQEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]),  0};
            ret_code = ((XMPP*)lpObj)->FireIQ(&e);
            param[4] = (void*)IPW64CAST(e.Ignore);
            break;
         }
         case 8: {
            XMPPMessageInEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), (char*)IPW64CAST(param[7]), (char*)IPW64CAST(param[8]), (char*)IPW64CAST(param[9]),  0};
            ret_code = ((XMPP*)lpObj)->FireMessageIn(&e);
            break;
         }
         case 9: {
            XMPPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XMPP*)lpObj)->FirePITrail(&e);
            break;
         }
         case 10: {
            XMPPPresenceEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]),  0};
            ret_code = ((XMPP*)lpObj)->FirePresence(&e);
            break;
         }
         case 11: {
            XMPPReadyToSendEventParams e = { 0};
            ret_code = ((XMPP*)lpObj)->FireReadyToSend(&e);
            break;
         }
         case 12: {
            XMPPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((XMPP*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 13: {
            XMPPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XMPP*)lpObj)->FireSSLStatus(&e);
            break;
         }
         case 14: {
            XMPPStartTransferEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]), *(ns_int64*)IPW64CAST(param[7]), (int)IPW64CAST(param[8]),  0};
            ret_code = ((XMPP*)lpObj)->FireStartTransfer(&e);
            param[5] = (void*)IPW64CAST(e.Filename);
            param[8] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 15: {
            XMPPSubscriptionRequestEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = ((XMPP*)lpObj)->FireSubscriptionRequest(&e);
            param[2] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 16: {
            XMPPSyncEventParams e = { 0};
            ret_code = ((XMPP*)lpObj)->FireSync(&e);
            break;
         }
         case 17: {
            XMPPTransferEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), *(ns_int64*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), (int)IPW64CAST(cbparam[5]),  0};
            ret_code = ((XMPP*)lpObj)->FireTransfer(&e);
            param[6] = (void*)IPW64CAST(e.Cancel);
            break;
         }

      }
      return ret_code;
    }

    virtual int XMPPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    XMPP(char *lpOemKey = (char*)IPWORKS_OEMKEY_70) {
      m_pObj = IPWorks_XMPP_Create(XMPPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~XMPP() {
      IPWorks_XMPP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_XMPP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_XMPP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_XMPP_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_XMPP_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_XMPP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetAuthDomain() {
      void* val = IPWorks_XMPP_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetAuthDomain(const char *lpAuthDomain) {
      return IPWorks_XMPP_Set(m_pObj, 1, 0, (void*)lpAuthDomain, 0);
    }

    inline char* GetAuthMethods() {
      void* val = IPWorks_XMPP_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetAuthMethods(const char *lpAuthMethods) {
      return IPWorks_XMPP_Set(m_pObj, 2, 0, (void*)lpAuthMethods, 0);
    }

    inline int GetBuddyCount() {
      void* val = IPWorks_XMPP_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }

    inline char* GetBuddyGroup(int iBuddyIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 4, iBuddyIndex, 0);
      return (char*)val;
    }

    inline int SetBuddyGroup(int iBuddyIndex, const char *lpBuddyGroup) {
      return IPWorks_XMPP_Set(m_pObj, 4, iBuddyIndex, (void*)lpBuddyGroup, 0);
    }

    inline char* GetBuddyId(int iBuddyIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 5, iBuddyIndex, 0);
      return (char*)val;
    }


    inline char* GetBuddyNickName(int iBuddyIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 6, iBuddyIndex, 0);
      return (char*)val;
    }

    inline int SetBuddyNickName(int iBuddyIndex, const char *lpBuddyNickName) {
      return IPWorks_XMPP_Set(m_pObj, 6, iBuddyIndex, (void*)lpBuddyNickName, 0);
    }

    inline char* GetBuddyRealName(int iBuddyIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 7, iBuddyIndex, 0);
      return (char*)val;
    }


    inline int GetBuddySubscription(int iBuddyIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 8, iBuddyIndex, 0);
      return (int)(long)val;
    }

    inline int GetConnected() {
      void* val = IPWorks_XMPP_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_XMPP_Set(m_pObj, 9, 0, val, 0);
    }
    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_XMPP_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_XMPP_Set(m_pObj, 10, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_XMPP_Get(m_pObj, 11, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_XMPP_Set(m_pObj, 11, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_XMPP_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_XMPP_Set(m_pObj, 12, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_XMPP_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_XMPP_Set(m_pObj, 13, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_XMPP_Get(m_pObj, 14, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_XMPP_Set(m_pObj, 14, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_XMPP_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_XMPP_Set(m_pObj, 15, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIMPort() {
      void* val = IPWorks_XMPP_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetIMPort(int iIMPort) {
      void* val = (void*)IPW64CAST(iIMPort);
      return IPWorks_XMPP_Set(m_pObj, 16, 0, val, 0);
    }
    inline char* GetIMServer() {
      void* val = IPWorks_XMPP_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetIMServer(const char *lpIMServer) {
      return IPWorks_XMPP_Set(m_pObj, 17, 0, (void*)lpIMServer, 0);
    }

    inline char* GetLocalDirectory() {
      void* val = IPWorks_XMPP_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetLocalDirectory(const char *lpLocalDirectory) {
      return IPWorks_XMPP_Set(m_pObj, 18, 0, (void*)lpLocalDirectory, 0);
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_XMPP_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_XMPP_Set(m_pObj, 19, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_XMPP_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_XMPP_Set(m_pObj, 20, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetMessageHTML() {
      void* val = IPWorks_XMPP_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetMessageHTML(const char *lpMessageHTML) {
      return IPWorks_XMPP_Set(m_pObj, 21, 0, (void*)lpMessageHTML, 0);
    }

    inline char* GetMessageOtherData() {
      void* val = IPWorks_XMPP_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetMessageOtherData(const char *lpMessageOtherData) {
      return IPWorks_XMPP_Set(m_pObj, 22, 0, (void*)lpMessageOtherData, 0);
    }

    inline char* GetMessageSubject() {
      void* val = IPWorks_XMPP_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }

    inline int SetMessageSubject(const char *lpMessageSubject) {
      return IPWorks_XMPP_Set(m_pObj, 23, 0, (void*)lpMessageSubject, 0);
    }

    inline char* GetMessageText() {
      void* val = IPWorks_XMPP_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetMessageText(const char *lpMessageText) {
      return IPWorks_XMPP_Set(m_pObj, 24, 0, (void*)lpMessageText, 0);
    }

    inline char* GetMessageThread() {
      void* val = IPWorks_XMPP_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }

    inline int SetMessageThread(const char *lpMessageThread) {
      return IPWorks_XMPP_Set(m_pObj, 25, 0, (void*)lpMessageThread, 0);
    }

    inline int GetMessageType() {
      void* val = IPWorks_XMPP_Get(m_pObj, 26, 0, 0);
      return (int)(long)val;
    }
    inline int SetMessageType(int iMessageType) {
      void* val = (void*)IPW64CAST(iMessageType);
      return IPWorks_XMPP_Set(m_pObj, 26, 0, val, 0);
    }
    inline char* GetPassword() {
      void* val = IPWorks_XMPP_Get(m_pObj, 27, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_XMPP_Set(m_pObj, 27, 0, (void*)lpPassword, 0);
    }

    inline int GetPresence() {
      void* val = IPWorks_XMPP_Get(m_pObj, 28, 0, 0);
      return (int)(long)val;
    }
    inline int SetPresence(int iPresence) {
      void* val = (void*)IPW64CAST(iPresence);
      return IPWorks_XMPP_Set(m_pObj, 28, 0, val, 0);
    }
    inline char* GetResource() {
      void* val = IPWorks_XMPP_Get(m_pObj, 29, 0, 0);
      return (char*)val;
    }

    inline int SetResource(const char *lpResource) {
      return IPWorks_XMPP_Set(m_pObj, 29, 0, (void*)lpResource, 0);
    }

    inline char* GetServerDomain() {
      void* val = IPWorks_XMPP_Get(m_pObj, 30, 0, 0);
      return (char*)val;
    }

    inline int SetServerDomain(const char *lpServerDomain) {
      return IPWorks_XMPP_Set(m_pObj, 30, 0, (void*)lpServerDomain, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_XMPP_Get(m_pObj, 31, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_XMPP_Set(m_pObj, 31, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_XMPP_Get(m_pObj, 32, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_XMPP_Set(m_pObj, 32, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_XMPP_Get(m_pObj, 33, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_XMPP_Set(m_pObj, 33, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_XMPP_Get(m_pObj, 34, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_XMPP_Set(m_pObj, 34, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_XMPP_Get(m_pObj, 35, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_XMPP_Set(m_pObj, 35, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_XMPP_Get(m_pObj, 36, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_XMPP_Set(m_pObj, 36, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_XMPP_Get(m_pObj, 37, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_XMPP_Set(m_pObj, 37, 0, val, 0);
    }
    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_XMPP_Get(m_pObj, 38, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline int GetSSLStartMode() {
      void* val = IPWorks_XMPP_Get(m_pObj, 39, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_XMPP_Set(m_pObj, 39, 0, val, 0);
    }
    inline char* GetStatus() {
      void* val = IPWorks_XMPP_Get(m_pObj, 40, 0, 0);
      return (char*)val;
    }

    inline int SetStatus(const char *lpStatus) {
      return IPWorks_XMPP_Set(m_pObj, 40, 0, (void*)lpStatus, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_XMPP_Get(m_pObj, 41, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_XMPP_Set(m_pObj, 41, 0, val, 0);
    }
    inline char* GetUser() {
      void* val = IPWorks_XMPP_Get(m_pObj, 42, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_XMPP_Set(m_pObj, 42, 0, (void*)lpUser, 0);
    }

    inline char* GetUserDomain() {
      void* val = IPWorks_XMPP_Get(m_pObj, 43, 0, 0);
      return (char*)val;
    }

    inline int SetUserDomain(const char *lpUserDomain) {
      return IPWorks_XMPP_Set(m_pObj, 43, 0, (void*)lpUserDomain, 0);
    }

    inline int GetUserInfoCount() {
      void* val = IPWorks_XMPP_Get(m_pObj, 44, 0, 0);
      return (int)(long)val;
    }
    inline int SetUserInfoCount(int iUserInfoCount) {
      void* val = (void*)IPW64CAST(iUserInfoCount);
      return IPWorks_XMPP_Set(m_pObj, 44, 0, val, 0);
    }
    inline char* GetUserInfoField(int iFieldIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 45, iFieldIndex, 0);
      return (char*)val;
    }

    inline int SetUserInfoField(int iFieldIndex, const char *lpUserInfoField) {
      return IPWorks_XMPP_Set(m_pObj, 45, iFieldIndex, (void*)lpUserInfoField, 0);
    }

    inline char* GetUserInfoValue(int iFieldIndex) {
      void* val = IPWorks_XMPP_Get(m_pObj, 46, iFieldIndex, 0);
      return (char*)val;
    }

    inline int SetUserInfoValue(int iFieldIndex, const char *lpUserInfoValue) {
      return IPWorks_XMPP_Set(m_pObj, 46, iFieldIndex, (void*)lpUserInfoValue, 0);
    }


  public: //methods

    inline int Add(const char* lpszJabberId, const char* lpszName, const char* lpszGroups) {
      void *param[3+1] = {(void*)IPW64CAST(lpszJabberId), (void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszGroups), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 2, 3, param, cbparam);
      
      
    }
    inline int Cancel(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 3, 1, param, cbparam);
      
      
    }
    inline int ChangePassword(const char* lpszPassword) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPassword), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 4, 1, param, cbparam);
      
      
    }
    inline int ChangePresence(int iPresenceCode, const char* lpszStatus) {
      void *param[2+1] = {(void*)IPW64CAST(iPresenceCode), (void*)IPW64CAST(lpszStatus), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 5, 2, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMPP_Do(m_pObj, 6, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect(const char* lpszUser, const char* lpszPassword) {
      void *param[2+1] = {(void*)IPW64CAST(lpszUser), (void*)IPW64CAST(lpszPassword), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 7, 2, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int ProbePresence(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 11, 1, param, cbparam);
      
      
    }
    inline int QueryRegister(const char* lpszXMPPServer) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXMPPServer), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 12, 1, param, cbparam);
      
      
    }
    inline int Register(const char* lpszXMPPServer) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXMPPServer), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 13, 1, param, cbparam);
      
      
    }
    inline int Remove(const char* lpszJabberId, const char* lpszName, const char* lpszGroup) {
      void *param[3+1] = {(void*)IPW64CAST(lpszJabberId), (void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszGroup), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 14, 3, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 15, 0, param, cbparam);
      
      
    }
    inline int RetrieveRoster() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 16, 0, param, cbparam);
      
      
    }
    inline int SendCommand(const char* lpszCommand) {
      void *param[1+1] = {(void*)IPW64CAST(lpszCommand), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 17, 1, param, cbparam);
      
      
    }
    inline int SendFile(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 18, 1, param, cbparam);
      
      
    }
    inline char* SendMessage(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMPP_Do(m_pObj, 19, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int SetUserInfoField(const char* lpszField, const char* lpszValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszField), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 22, 2, param, cbparam);
      
      
    }
    inline int SubscribeTo(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 23, 1, param, cbparam);
      
      
    }
    inline int Unregister() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 24, 0, param, cbparam);
      
      
    }
    inline int UnsubscribeTo(const char* lpszJabberId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszJabberId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 25, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int BuddyIdx;
  int reserved;
} XMPPBuddyUpdateEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} XMPPConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} XMPPConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} XMPPDisconnectedEventParamsW;

typedef struct {
  int Direction;
  LPWSTR FileId;
  LPWSTR Filename;
  int Success;
  int reserved;
} XMPPEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} XMPPErrorEventParamsW;

typedef struct {
  LPWSTR Iq;
  LPWSTR Id;
  LPWSTR From;
  LPWSTR IqType;
  int Ignore;
  int reserved;
} XMPPIQEventParamsW;

typedef struct {
  LPWSTR MessageId;
  LPWSTR From;
  LPWSTR Domain;
  LPWSTR Resource;
  int MessageType;
  LPWSTR Subject;
  LPWSTR MessageThread;
  LPWSTR MessageText;
  LPWSTR MessageHTML;
  LPWSTR Other;
  int reserved;
} XMPPMessageInEventParamsW;

typedef struct {
  int Direction;
  LPWSTR Pi;
  int reserved;
} XMPPPITrailEventParamsW;

typedef struct {
  LPWSTR User;
  LPWSTR Domain;
  LPWSTR Resource;
  int Availability;
  LPWSTR Status;
  int reserved;
} XMPPPresenceEventParamsW;

typedef struct {
  int reserved;
} XMPPReadyToSendEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} XMPPSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} XMPPSSLStatusEventParamsW;

typedef struct {
  int Direction;
  LPWSTR FileId;
  LPWSTR User;
  LPWSTR Domain;
  LPWSTR Resource;
  LPWSTR Filename;
  LPWSTR Datetime;
  ns_int64 Size;
  int Accept;
  int reserved;
} XMPPStartTransferEventParamsW;

typedef struct {
  LPWSTR From;
  LPWSTR Domain;
  int Accept;
  int reserved;
} XMPPSubscriptionRequestEventParamsW;

typedef struct {
  int reserved;
} XMPPSyncEventParamsW;

typedef struct {
  int Direction;
  LPWSTR FileId;
  LPWSTR Filename;
  ns_int64 BytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int Cancel;
  int lenText;
  int reserved;
} XMPPTransferEventParamsW;



class XMPPW : public XMPP {

  public: //properties
  
    inline LPWSTR GetAuthDomain() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetAuthDomain(LPCWSTR lpAuthDomain) {
      return IPWorks_XMPP_Set(m_pObj, 10000+1, 0, (void*)lpAuthDomain, 0);
    }

    inline LPWSTR GetAuthMethods() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetAuthMethods(LPCWSTR lpAuthMethods) {
      return IPWorks_XMPP_Set(m_pObj, 10000+2, 0, (void*)lpAuthMethods, 0);
    }



    inline LPWSTR GetBuddyGroup(int iBuddyIndex) {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+4, iBuddyIndex, 0);
    }

    inline int SetBuddyGroup(int iBuddyIndex, LPCWSTR lpBuddyGroup) {
      return IPWorks_XMPP_Set(m_pObj, 10000+4, iBuddyIndex, (void*)lpBuddyGroup, 0);
    }

    inline LPWSTR GetBuddyId(int iBuddyIndex) {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+5, iBuddyIndex, 0);
    }



    inline LPWSTR GetBuddyNickName(int iBuddyIndex) {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+6, iBuddyIndex, 0);
    }

    inline int SetBuddyNickName(int iBuddyIndex, LPCWSTR lpBuddyNickName) {
      return IPWorks_XMPP_Set(m_pObj, 10000+6, iBuddyIndex, (void*)lpBuddyNickName, 0);
    }

    inline LPWSTR GetBuddyRealName(int iBuddyIndex) {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+7, iBuddyIndex, 0);
    }











    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_XMPP_Set(m_pObj, 10000+12, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_XMPP_Set(m_pObj, 10000+13, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_XMPP_Set(m_pObj, 10000+15, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetIMServer() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetIMServer(LPCWSTR lpIMServer) {
      return IPWorks_XMPP_Set(m_pObj, 10000+17, 0, (void*)lpIMServer, 0);
    }

    inline LPWSTR GetLocalDirectory() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetLocalDirectory(LPCWSTR lpLocalDirectory) {
      return IPWorks_XMPP_Set(m_pObj, 10000+18, 0, (void*)lpLocalDirectory, 0);
    }

    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetLocalFile(LPCWSTR lpLocalFile) {
      return IPWorks_XMPP_Set(m_pObj, 10000+19, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_XMPP_Set(m_pObj, 10000+20, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetMessageHTML() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+21, 0, 0);
    }

    inline int SetMessageHTML(LPCWSTR lpMessageHTML) {
      return IPWorks_XMPP_Set(m_pObj, 10000+21, 0, (void*)lpMessageHTML, 0);
    }

    inline LPWSTR GetMessageOtherData() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetMessageOtherData(LPCWSTR lpMessageOtherData) {
      return IPWorks_XMPP_Set(m_pObj, 10000+22, 0, (void*)lpMessageOtherData, 0);
    }

    inline LPWSTR GetMessageSubject() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+23, 0, 0);
    }

    inline int SetMessageSubject(LPCWSTR lpMessageSubject) {
      return IPWorks_XMPP_Set(m_pObj, 10000+23, 0, (void*)lpMessageSubject, 0);
    }

    inline LPWSTR GetMessageText() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetMessageText(LPCWSTR lpMessageText) {
      return IPWorks_XMPP_Set(m_pObj, 10000+24, 0, (void*)lpMessageText, 0);
    }

    inline LPWSTR GetMessageThread() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+25, 0, 0);
    }

    inline int SetMessageThread(LPCWSTR lpMessageThread) {
      return IPWorks_XMPP_Set(m_pObj, 10000+25, 0, (void*)lpMessageThread, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+27, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_XMPP_Set(m_pObj, 10000+27, 0, (void*)lpPassword, 0);
    }



    inline LPWSTR GetResource() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+29, 0, 0);
    }

    inline int SetResource(LPCWSTR lpResource) {
      return IPWorks_XMPP_Set(m_pObj, 10000+29, 0, (void*)lpResource, 0);
    }

    inline LPWSTR GetServerDomain() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+30, 0, 0);
    }

    inline int SetServerDomain(LPCWSTR lpServerDomain) {
      return IPWorks_XMPP_Set(m_pObj, 10000+30, 0, (void*)lpServerDomain, 0);
    }

    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+31, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_XMPP_Set(m_pObj, 10000+31, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_XMPP_Get(m_pObj, 31, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_XMPP_Set(m_pObj, 31, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+32, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_XMPP_Set(m_pObj, 10000+32, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_XMPP_Get(m_pObj, 32, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_XMPP_Set(m_pObj, 32, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+33, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_XMPP_Set(m_pObj, 10000+33, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_XMPP_Get(m_pObj, 33, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_XMPP_Set(m_pObj, 33, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+34, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_XMPP_Set(m_pObj, 10000+34, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+36, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_XMPP_Set(m_pObj, 10000+36, 0, (void*)lpSSLCertSubject, 0);
    }



    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+38, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_XMPP_Get(m_pObj, 38, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }



    inline LPWSTR GetStatus() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+40, 0, 0);
    }

    inline int SetStatus(LPCWSTR lpStatus) {
      return IPWorks_XMPP_Set(m_pObj, 10000+40, 0, (void*)lpStatus, 0);
    }



    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+42, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_XMPP_Set(m_pObj, 10000+42, 0, (void*)lpUser, 0);
    }

    inline LPWSTR GetUserDomain() {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+43, 0, 0);
    }

    inline int SetUserDomain(LPCWSTR lpUserDomain) {
      return IPWorks_XMPP_Set(m_pObj, 10000+43, 0, (void*)lpUserDomain, 0);
    }



    inline LPWSTR GetUserInfoField(int iFieldIndex) {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+45, iFieldIndex, 0);
    }

    inline int SetUserInfoField(int iFieldIndex, LPCWSTR lpUserInfoField) {
      return IPWorks_XMPP_Set(m_pObj, 10000+45, iFieldIndex, (void*)lpUserInfoField, 0);
    }

    inline LPWSTR GetUserInfoValue(int iFieldIndex) {
      return (LPWSTR)IPWorks_XMPP_Get(m_pObj, 10000+46, iFieldIndex, 0);
    }

    inline int SetUserInfoValue(int iFieldIndex, LPCWSTR lpUserInfoValue) {
      return IPWorks_XMPP_Set(m_pObj, 10000+46, iFieldIndex, (void*)lpUserInfoValue, 0);
    }



  public: //events
  
    virtual int FireBuddyUpdate(XMPPBuddyUpdateEventParamsW *e) {return 0;}
    virtual int FireConnected(XMPPConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(XMPPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(XMPPDisconnectedEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(XMPPEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(XMPPErrorEventParamsW *e) {return 0;}
    virtual int FireIQ(XMPPIQEventParamsW *e) {return 0;}
    virtual int FireMessageIn(XMPPMessageInEventParamsW *e) {return 0;}
    virtual int FirePITrail(XMPPPITrailEventParamsW *e) {return 0;}
    virtual int FirePresence(XMPPPresenceEventParamsW *e) {return 0;}
    virtual int FireReadyToSend(XMPPReadyToSendEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(XMPPSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(XMPPSSLStatusEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(XMPPStartTransferEventParamsW *e) {return 0;}
    virtual int FireSubscriptionRequest(XMPPSubscriptionRequestEventParamsW *e) {return 0;}
    virtual int FireSync(XMPPSyncEventParamsW *e) {return 0;}
    virtual int FireTransfer(XMPPTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int XMPPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            XMPPBuddyUpdateEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireBuddyUpdate(&e);
            break;
         }
         case 2: {
            XMPPConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 3: {
            XMPPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 4: {
            XMPPDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 5: {
            XMPPEndTransferEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 6: {
            XMPPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 7: {
            XMPPIQEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]),  0};
            ret_code = FireIQ(&e);
            param[4] = (void*)(e.Ignore);
            break;
         }
         case 8: {
            XMPPMessageInEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]), (LPWSTR)IPW64CAST(param[6]), (LPWSTR)IPW64CAST(param[7]), (LPWSTR)IPW64CAST(param[8]), (LPWSTR)IPW64CAST(param[9]),  0};
            ret_code = FireMessageIn(&e);
            break;
         }
         case 9: {
            XMPPPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }
         case 10: {
            XMPPPresenceEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]),  0};
            ret_code = FirePresence(&e);
            break;
         }
         case 11: {
            XMPPReadyToSendEventParamsW e = { 0};
            ret_code = FireReadyToSend(&e);
            break;
         }
         case 12: {
            XMPPSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 13: {
            XMPPSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }
         case 14: {
            XMPPStartTransferEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]), (LPWSTR)IPW64CAST(param[6]), *(ns_int64*)IPW64CAST(param[7]), (int)IPW64CAST(param[8]),  0};
            ret_code = FireStartTransfer(&e);
            param[5] = (void*)(e.Filename);
            param[8] = (void*)(e.Accept);
            break;
         }
         case 15: {
            XMPPSubscriptionRequestEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = FireSubscriptionRequest(&e);
            param[2] = (void*)(e.Accept);
            break;
         }
         case 16: {
            XMPPSyncEventParamsW e = { 0};
            ret_code = FireSync(&e);
            break;
         }
         case 17: {
            XMPPTransferEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), *(ns_int64*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), (int)IPW64CAST(cbparam[5]),  0};
            ret_code = FireTransfer(&e);
            param[6] = (void*)(e.Cancel);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireBuddyUpdate(XMPPBuddyUpdateEventParams *e) {return -10000;}
    virtual int FireConnected(XMPPConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(XMPPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(XMPPDisconnectedEventParams *e) {return -10000;}
    virtual int FireEndTransfer(XMPPEndTransferEventParams *e) {return -10000;}
    virtual int FireError(XMPPErrorEventParams *e) {return -10000;}
    virtual int FireIQ(XMPPIQEventParams *e) {return -10000;}
    virtual int FireMessageIn(XMPPMessageInEventParams *e) {return -10000;}
    virtual int FirePITrail(XMPPPITrailEventParams *e) {return -10000;}
    virtual int FirePresence(XMPPPresenceEventParams *e) {return -10000;}
    virtual int FireReadyToSend(XMPPReadyToSendEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(XMPPSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(XMPPSSLStatusEventParams *e) {return -10000;}
    virtual int FireStartTransfer(XMPPStartTransferEventParams *e) {return -10000;}
    virtual int FireSubscriptionRequest(XMPPSubscriptionRequestEventParams *e) {return -10000;}
    virtual int FireSync(XMPPSyncEventParams *e) {return -10000;}
    virtual int FireTransfer(XMPPTransferEventParams *e) {return -10000;}

  public: //methods

    inline int Add(LPWSTR lpszJabberId, LPWSTR lpszName, LPWSTR lpszGroups) {
      void *param[3+1] = {(void*)lpszJabberId, (void*)lpszName, (void*)lpszGroups, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+2, 3, param, cbparam);
      
    }
    inline int Cancel(LPWSTR lpszJabberId) {
      void *param[1+1] = {(void*)lpszJabberId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+3, 1, param, cbparam);
      
    }
    inline int ChangePassword(LPWSTR lpszPassword) {
      void *param[1+1] = {(void*)lpszPassword, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+4, 1, param, cbparam);
      
    }
    inline int ChangePresence(int iPresenceCode, LPWSTR lpszStatus) {
      void *param[2+1] = {(void*)iPresenceCode, (void*)lpszStatus, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+5, 2, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMPP_Do(m_pObj, 10000+6, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect(LPWSTR lpszUser, LPWSTR lpszPassword) {
      void *param[2+1] = {(void*)lpszUser, (void*)lpszPassword, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+7, 2, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int ProbePresence(LPWSTR lpszJabberId) {
      void *param[1+1] = {(void*)lpszJabberId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+11, 1, param, cbparam);
      
    }
    inline int QueryRegister(LPWSTR lpszXMPPServer) {
      void *param[1+1] = {(void*)lpszXMPPServer, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+12, 1, param, cbparam);
      
    }
    inline int Register(LPWSTR lpszXMPPServer) {
      void *param[1+1] = {(void*)lpszXMPPServer, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+13, 1, param, cbparam);
      
    }
    inline int Remove(LPWSTR lpszJabberId, LPWSTR lpszName, LPWSTR lpszGroup) {
      void *param[3+1] = {(void*)lpszJabberId, (void*)lpszName, (void*)lpszGroup, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+14, 3, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 10000+15, 0, param, cbparam);
      
    }
    inline int RetrieveRoster() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 10000+16, 0, param, cbparam);
      
    }
    inline int SendCommand(LPWSTR lpszCommand) {
      void *param[1+1] = {(void*)lpszCommand, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+17, 1, param, cbparam);
      
    }
    inline int SendFile(LPWSTR lpszJabberId) {
      void *param[1+1] = {(void*)lpszJabberId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+18, 1, param, cbparam);
      
    }
    inline LPWSTR SendMessage(LPWSTR lpszJabberId) {
      void *param[1+1] = {(void*)lpszJabberId, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMPP_Do(m_pObj, 10000+19, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int SetUserInfoField(LPWSTR lpszField, LPWSTR lpszValue) {
      void *param[2+1] = {(void*)lpszField, (void*)lpszValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+22, 2, param, cbparam);
      
    }
    inline int SubscribeTo(LPWSTR lpszJabberId) {
      void *param[1+1] = {(void*)lpszJabberId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+23, 1, param, cbparam);
      
    }
    inline int Unregister() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMPP_Do(m_pObj, 10000+24, 0, param, cbparam);
      
    }
    inline int UnsubscribeTo(LPWSTR lpszJabberId) {
      void *param[1+1] = {(void*)lpszJabberId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMPP_Do(m_pObj, 10000+25, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_XMPP_H_




