/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_SMPP_H_
#define _IPWORKS_SMPP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TSMPPMessagePriorities
#define SMPP_MESSAGE_PRIORITY_LOW                          0
#define SMPP_MESSAGE_PRIORITY_NORMAL                       1
#define SMPP_MESSAGE_PRIORITY_HIGH                         2
#define SMPP_MESSAGE_PRIORITY_URGENT                       3

//TSMPPProtocols
#define SMPP_SMPP                                          0
#define SMPP_CIMD2                                         1

//SMPPRecipientTypes
#define SMPP_RECIPIENT_TYPE_NORMAL                         0
#define SMPP_RECIPIENT_TYPE_LIST                           1

//TSMPPServiceTypes
#define SMPP_SERVICE_DEFAULT                               0
#define SMPP_SERVICE_CMT                                   1
#define SMPP_SERVICE_CPT                                   2
#define SMPP_SERVICE_VMN                                   3
#define SMPP_SERVICE_VMA                                   4
#define SMPP_SERVICE_WAP                                   5
#define SMPP_SERVICE_USSD                                  6
#define SMPP_SERVICE_CBS                                   7

//TSMPPVersions
#define SMPP_VERSION_50                                    0
#define SMPP_VERSION_34                                    1
#define SMPP_VERSION_33                                    2

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


extern "C" void* IPWORKS_CALL IPWorks_SMPP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SMPP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_SMPP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} SMPPConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} SMPPConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} SMPPDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} SMPPErrorEventParams;

typedef struct {
  const char* SourceAddress;
  const char* ScheduleDeliveryTime;
  const char* ValidityPeriod;
  const char* Message;
  int MessagePart;
  int MessagePartCount;
  int MessagePartReference;
  const char* DestinationAddress;
  int ResponseErrorCode;
  int reserved;
} SMPPMessageInEventParams;

typedef struct {
  const char* MessageId;
  int MessageState;
  int MessageError;
  const char* FinalDate;
  int reserved;
} SMPPMessageStatusEventParams;

typedef struct {
  int Direction;
  const char* PDU;
  int CommandLength;
  int CommandId;
  const char* CommandDescription;
  const char* CommandStatus;
  int SequenceNumber;
  int lenPDU;
  int reserved;
} SMPPPITrailEventParams;

typedef struct {
  int reserved;
} SMPPReadyToSendEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} SMPPSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} SMPPSSLStatusEventParams;



class SMPP {
  
  public: //events
  
    virtual int FireConnected(SMPPConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(SMPPConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(SMPPDisconnectedEventParams *e) {return 0;}
    virtual int FireError(SMPPErrorEventParams *e) {return 0;}
    virtual int FireMessageIn(SMPPMessageInEventParams *e) {return 0;}
    virtual int FireMessageStatus(SMPPMessageStatusEventParams *e) {return 0;}
    virtual int FirePITrail(SMPPPITrailEventParams *e) {return 0;}
    virtual int FireReadyToSend(SMPPReadyToSendEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(SMPPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(SMPPSSLStatusEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL SMPPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((SMPP*)lpObj)->SMPPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            SMPPConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SMPP*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            SMPPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((SMPP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            SMPPDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SMPP*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            SMPPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SMPP*)lpObj)->FireError(&e);
            break;
         }
         case 5: {
            SMPPMessageInEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), (char*)IPW64CAST(param[7]), (int)IPW64CAST(param[8]),  0};
            ret_code = ((SMPP*)lpObj)->FireMessageIn(&e);
            param[8] = (void*)IPW64CAST(e.ResponseErrorCode);
            break;
         }
         case 6: {
            SMPPMessageStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]),  0};
            ret_code = ((SMPP*)lpObj)->FireMessageStatus(&e);
            break;
         }
         case 7: {
            SMPPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), (int)IPW64CAST(cbparam[1]),  0};
            ret_code = ((SMPP*)lpObj)->FirePITrail(&e);
            break;
         }
         case 8: {
            SMPPReadyToSendEventParams e = { 0};
            ret_code = ((SMPP*)lpObj)->FireReadyToSend(&e);
            break;
         }
         case 9: {
            SMPPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((SMPP*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 10: {
            SMPPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((SMPP*)lpObj)->FireSSLStatus(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int SMPPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    SMPP(char *lpOemKey = (char*)IPWORKS_OEMKEY_71) {
      m_pObj = IPWorks_SMPP_Create(SMPPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~SMPP() {
      IPWorks_SMPP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_SMPP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_SMPP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_SMPP_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_SMPP_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_SMPP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetConnected() {
      void* val = IPWorks_SMPP_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_SMPP_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_SMPP_Set(m_pObj, 2, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_SMPP_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_SMPP_Set(m_pObj, 3, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_SMPP_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_SMPP_Set(m_pObj, 4, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_SMPP_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_SMPP_Set(m_pObj, 5, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_SMPP_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_SMPP_Set(m_pObj, 6, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_SMPP_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_SMPP_Set(m_pObj, 7, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_SMPP_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_SMPP_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_SMPP_Set(m_pObj, 9, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetMessageExpiration() {
      void* val = IPWorks_SMPP_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }

    inline int SetMessageExpiration(const char *lpMessageExpiration) {
      return IPWorks_SMPP_Set(m_pObj, 10, 0, (void*)lpMessageExpiration, 0);
    }

    inline char* GetMessageId() {
      void* val = IPWorks_SMPP_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }


    inline int GetMessagePriority() {
      void* val = IPWorks_SMPP_Get(m_pObj, 12, 0, 0);
      return (int)(long)val;
    }
    inline int SetMessagePriority(int iMessagePriority) {
      void* val = (void*)IPW64CAST(iMessagePriority);
      return IPWorks_SMPP_Set(m_pObj, 12, 0, val, 0);
    }
    inline char* GetPassword() {
      void* val = IPWorks_SMPP_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_SMPP_Set(m_pObj, 13, 0, (void*)lpPassword, 0);
    }

    inline int GetProtocol() {
      void* val = IPWorks_SMPP_Get(m_pObj, 14, 0, 0);
      return (int)(long)val;
    }
    inline int SetProtocol(int iProtocol) {
      void* val = (void*)IPW64CAST(iProtocol);
      return IPWorks_SMPP_Set(m_pObj, 14, 0, val, 0);
    }
    inline int GetRecipientCount() {
      void* val = IPWorks_SMPP_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }
    inline int SetRecipientCount(int iRecipientCount) {
      void* val = (void*)IPW64CAST(iRecipientCount);
      return IPWorks_SMPP_Set(m_pObj, 15, 0, val, 0);
    }
    inline char* GetRecipientAddress(int iRecipientIndex) {
      void* val = IPWorks_SMPP_Get(m_pObj, 16, iRecipientIndex, 0);
      return (char*)val;
    }

    inline int SetRecipientAddress(int iRecipientIndex, const char *lpRecipientAddress) {
      return IPWorks_SMPP_Set(m_pObj, 16, iRecipientIndex, (void*)lpRecipientAddress, 0);
    }

    inline int GetRecipientType(int iRecipientIndex) {
      void* val = IPWorks_SMPP_Get(m_pObj, 17, iRecipientIndex, 0);
      return (int)(long)val;
    }
    inline int SetRecipientType(int iRecipientIndex, int iRecipientType) {
      void* val = (void*)IPW64CAST(iRecipientType);
      return IPWorks_SMPP_Set(m_pObj, 17, iRecipientIndex, val, 0);
    }
    inline char* GetScheduledDelivery() {
      void* val = IPWorks_SMPP_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetScheduledDelivery(const char *lpScheduledDelivery) {
      return IPWorks_SMPP_Set(m_pObj, 18, 0, (void*)lpScheduledDelivery, 0);
    }

    inline char* GetSenderAddress() {
      void* val = IPWorks_SMPP_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetSenderAddress(const char *lpSenderAddress) {
      return IPWorks_SMPP_Set(m_pObj, 19, 0, (void*)lpSenderAddress, 0);
    }

    inline int GetServiceType() {
      void* val = IPWorks_SMPP_Get(m_pObj, 20, 0, 0);
      return (int)(long)val;
    }
    inline int SetServiceType(int iServiceType) {
      void* val = (void*)IPW64CAST(iServiceType);
      return IPWorks_SMPP_Set(m_pObj, 20, 0, val, 0);
    }
    inline int GetSMPPPort() {
      void* val = IPWorks_SMPP_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }
    inline int SetSMPPPort(int iSMPPPort) {
      void* val = (void*)IPW64CAST(iSMPPPort);
      return IPWorks_SMPP_Set(m_pObj, 21, 0, val, 0);
    }
    inline char* GetSMPPServer() {
      void* val = IPWorks_SMPP_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetSMPPServer(const char *lpSMPPServer) {
      return IPWorks_SMPP_Set(m_pObj, 22, 0, (void*)lpSMPPServer, 0);
    }

    inline int GetSMPPVersion() {
      void* val = IPWorks_SMPP_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }
    inline int SetSMPPVersion(int iSMPPVersion) {
      void* val = (void*)IPW64CAST(iSMPPVersion);
      return IPWorks_SMPP_Set(m_pObj, 23, 0, val, 0);
    }
    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_SMPP_Get(m_pObj, 24, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_SMPP_Set(m_pObj, 24, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_SMPP_Get(m_pObj, 25, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_SMPP_Set(m_pObj, 25, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_SMPP_Get(m_pObj, 26, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_SMPP_Set(m_pObj, 26, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_SMPP_Get(m_pObj, 27, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_SMPP_Set(m_pObj, 27, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_SMPP_Get(m_pObj, 28, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_SMPP_Set(m_pObj, 28, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_SMPP_Get(m_pObj, 29, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_SMPP_Set(m_pObj, 29, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_SMPP_Get(m_pObj, 30, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_SMPP_Set(m_pObj, 30, 0, val, 0);
    }
    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_SMPP_Get(m_pObj, 31, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline int GetSSLStartMode() {
      void* val = IPWorks_SMPP_Get(m_pObj, 32, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_SMPP_Set(m_pObj, 32, 0, val, 0);
    }
    inline char* GetSystemType() {
      void* val = IPWorks_SMPP_Get(m_pObj, 33, 0, 0);
      return (char*)val;
    }

    inline int SetSystemType(const char *lpSystemType) {
      return IPWorks_SMPP_Set(m_pObj, 33, 0, (void*)lpSystemType, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_SMPP_Get(m_pObj, 34, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_SMPP_Set(m_pObj, 34, 0, val, 0);
    }
    inline char* GetUserId() {
      void* val = IPWorks_SMPP_Get(m_pObj, 35, 0, 0);
      return (char*)val;
    }

    inline int SetUserId(const char *lpUserId) {
      return IPWorks_SMPP_Set(m_pObj, 35, 0, (void*)lpUserId, 0);
    }


  public: //methods

    inline int AddRecipient(int iRecipientType, const char* lpszRecipientAddress) {
      void *param[2+1] = {(void*)IPW64CAST(iRecipientType), (void*)IPW64CAST(lpszRecipientAddress), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SMPP_Do(m_pObj, 2, 2, param, cbparam);
      
      
    }
    inline int CancelMessage(const char* lpszMessageId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszMessageId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_SMPP_Do(m_pObj, 3, 1, param, cbparam);
      
      
    }
    inline int CheckLink() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int CheckMessageStatus(const char* lpszMessageId) {
      void *param[1+1] = {(void*)IPW64CAST(lpszMessageId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_SMPP_Do(m_pObj, 5, 1, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SMPP_Do(m_pObj, 6, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect(const char* lpszUserId, const char* lpszPassword) {
      void *param[2+1] = {(void*)IPW64CAST(lpszUserId), (void*)IPW64CAST(lpszPassword), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SMPP_Do(m_pObj, 7, 2, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int ReplaceMessage(const char* lpszMessageId, const char* lpszNewMessage) {
      void *param[2+1] = {(void*)IPW64CAST(lpszMessageId), (void*)IPW64CAST(lpszNewMessage), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SMPP_Do(m_pObj, 11, 2, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }
    inline char* SendCommand(int iCommandId, const char* lpPayload, int lenPayload, int *lpSize = 0) {
      void *param[2+1] = {(void*)IPW64CAST(iCommandId), (void*)IPW64CAST(lpPayload), 0};
      int cbparam[2+1] = {0, lenPayload, 0};
      IPWorks_SMPP_Do(m_pObj, 13, 2, param, cbparam);
      if (lpSize) *lpSize = cbparam[2];
      return (char*)IPW64CAST(param[2]);
    }
    inline char* SendData(const char* lpData, int lenData) {
      void *param[1+1] = {(void*)IPW64CAST(lpData), 0};
      int cbparam[1+1] = {lenData, 0};
      IPWorks_SMPP_Do(m_pObj, 14, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline char* SendMessage(const char* lpszMessage) {
      void *param[1+1] = {(void*)IPW64CAST(lpszMessage), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SMPP_Do(m_pObj, 15, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} SMPPConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} SMPPConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} SMPPDisconnectedEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} SMPPErrorEventParamsW;

typedef struct {
  LPWSTR SourceAddress;
  LPWSTR ScheduleDeliveryTime;
  LPWSTR ValidityPeriod;
  LPWSTR Message;
  int MessagePart;
  int MessagePartCount;
  int MessagePartReference;
  LPWSTR DestinationAddress;
  int ResponseErrorCode;
  int reserved;
} SMPPMessageInEventParamsW;

typedef struct {
  LPWSTR MessageId;
  int MessageState;
  int MessageError;
  LPWSTR FinalDate;
  int reserved;
} SMPPMessageStatusEventParamsW;

typedef struct {
  int Direction;
  LPWSTR PDU;
  int CommandLength;
  int CommandId;
  LPWSTR CommandDescription;
  LPWSTR CommandStatus;
  int SequenceNumber;
  int lenPDU;
  int reserved;
} SMPPPITrailEventParamsW;

typedef struct {
  int reserved;
} SMPPReadyToSendEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} SMPPSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} SMPPSSLStatusEventParamsW;



class SMPPW : public SMPP {

  public: //properties
  






    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_SMPP_Set(m_pObj, 10000+4, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_SMPP_Set(m_pObj, 10000+5, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_SMPP_Set(m_pObj, 10000+7, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_SMPP_Set(m_pObj, 10000+9, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetMessageExpiration() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+10, 0, 0);
    }

    inline int SetMessageExpiration(LPCWSTR lpMessageExpiration) {
      return IPWorks_SMPP_Set(m_pObj, 10000+10, 0, (void*)lpMessageExpiration, 0);
    }

    inline LPWSTR GetMessageId() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+11, 0, 0);
    }





    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_SMPP_Set(m_pObj, 10000+13, 0, (void*)lpPassword, 0);
    }





    inline LPWSTR GetRecipientAddress(int iRecipientIndex) {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+16, iRecipientIndex, 0);
    }

    inline int SetRecipientAddress(int iRecipientIndex, LPCWSTR lpRecipientAddress) {
      return IPWorks_SMPP_Set(m_pObj, 10000+16, iRecipientIndex, (void*)lpRecipientAddress, 0);
    }



    inline LPWSTR GetScheduledDelivery() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetScheduledDelivery(LPCWSTR lpScheduledDelivery) {
      return IPWorks_SMPP_Set(m_pObj, 10000+18, 0, (void*)lpScheduledDelivery, 0);
    }

    inline LPWSTR GetSenderAddress() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetSenderAddress(LPCWSTR lpSenderAddress) {
      return IPWorks_SMPP_Set(m_pObj, 10000+19, 0, (void*)lpSenderAddress, 0);
    }





    inline LPWSTR GetSMPPServer() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetSMPPServer(LPCWSTR lpSMPPServer) {
      return IPWorks_SMPP_Set(m_pObj, 10000+22, 0, (void*)lpSMPPServer, 0);
    }



    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_SMPP_Set(m_pObj, 10000+24, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_SMPP_Get(m_pObj, 24, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_SMPP_Set(m_pObj, 24, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+25, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_SMPP_Set(m_pObj, 10000+25, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_SMPP_Get(m_pObj, 25, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_SMPP_Set(m_pObj, 25, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+26, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_SMPP_Set(m_pObj, 10000+26, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_SMPP_Get(m_pObj, 26, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_SMPP_Set(m_pObj, 26, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+27, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_SMPP_Set(m_pObj, 10000+27, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+29, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_SMPP_Set(m_pObj, 10000+29, 0, (void*)lpSSLCertSubject, 0);
    }



    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+31, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_SMPP_Get(m_pObj, 31, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }



    inline LPWSTR GetSystemType() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+33, 0, 0);
    }

    inline int SetSystemType(LPCWSTR lpSystemType) {
      return IPWorks_SMPP_Set(m_pObj, 10000+33, 0, (void*)lpSystemType, 0);
    }



    inline LPWSTR GetUserId() {
      return (LPWSTR)IPWorks_SMPP_Get(m_pObj, 10000+35, 0, 0);
    }

    inline int SetUserId(LPCWSTR lpUserId) {
      return IPWorks_SMPP_Set(m_pObj, 10000+35, 0, (void*)lpUserId, 0);
    }



  public: //events
  
    virtual int FireConnected(SMPPConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(SMPPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(SMPPDisconnectedEventParamsW *e) {return 0;}
    virtual int FireError(SMPPErrorEventParamsW *e) {return 0;}
    virtual int FireMessageIn(SMPPMessageInEventParamsW *e) {return 0;}
    virtual int FireMessageStatus(SMPPMessageStatusEventParamsW *e) {return 0;}
    virtual int FirePITrail(SMPPPITrailEventParamsW *e) {return 0;}
    virtual int FireReadyToSend(SMPPReadyToSendEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(SMPPSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(SMPPSSLStatusEventParamsW *e) {return 0;}


  protected:
  
    virtual int SMPPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            SMPPConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            SMPPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            SMPPDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            SMPPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 5: {
            SMPPMessageInEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), (LPWSTR)IPW64CAST(param[7]), (int)IPW64CAST(param[8]),  0};
            ret_code = FireMessageIn(&e);
            param[8] = (void*)(e.ResponseErrorCode);
            break;
         }
         case 6: {
            SMPPMessageStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]),  0};
            ret_code = FireMessageStatus(&e);
            break;
         }
         case 7: {
            SMPPPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), (int)IPW64CAST(cbparam[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }
         case 8: {
            SMPPReadyToSendEventParamsW e = { 0};
            ret_code = FireReadyToSend(&e);
            break;
         }
         case 9: {
            SMPPSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 10: {
            SMPPSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(SMPPConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(SMPPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(SMPPDisconnectedEventParams *e) {return -10000;}
    virtual int FireError(SMPPErrorEventParams *e) {return -10000;}
    virtual int FireMessageIn(SMPPMessageInEventParams *e) {return -10000;}
    virtual int FireMessageStatus(SMPPMessageStatusEventParams *e) {return -10000;}
    virtual int FirePITrail(SMPPPITrailEventParams *e) {return -10000;}
    virtual int FireReadyToSend(SMPPReadyToSendEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(SMPPSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(SMPPSSLStatusEventParams *e) {return -10000;}

  public: //methods

    inline int AddRecipient(int iRecipientType, LPWSTR lpszRecipientAddress) {
      void *param[2+1] = {(void*)iRecipientType, (void*)lpszRecipientAddress, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SMPP_Do(m_pObj, 10000+2, 2, param, cbparam);
      
    }
    inline int CancelMessage(LPWSTR lpszMessageId) {
      void *param[1+1] = {(void*)lpszMessageId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_SMPP_Do(m_pObj, 10000+3, 1, param, cbparam);
      
    }
    inline int CheckLink() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int CheckMessageStatus(LPWSTR lpszMessageId) {
      void *param[1+1] = {(void*)lpszMessageId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_SMPP_Do(m_pObj, 10000+5, 1, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SMPP_Do(m_pObj, 10000+6, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect(LPWSTR lpszUserId, LPWSTR lpszPassword) {
      void *param[2+1] = {(void*)lpszUserId, (void*)lpszPassword, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SMPP_Do(m_pObj, 10000+7, 2, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int ReplaceMessage(LPWSTR lpszMessageId, LPWSTR lpszNewMessage) {
      void *param[2+1] = {(void*)lpszMessageId, (void*)lpszNewMessage, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_SMPP_Do(m_pObj, 10000+11, 2, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }
    inline LPWSTR SendCommand(int iCommandId, LPWSTR lpPayload, int lenPayload) {
      void *param[2+1] = {(void*)iCommandId, (void*)lpPayload, 0};
      int cbparam[2+1] = {0, lenPayload, 0};
      IPWorks_SMPP_Do(m_pObj, 10000+13, 2, param, cbparam);
      return (LPWSTR)IPW64CAST(param[2]);
    }
    inline LPWSTR SendData(LPWSTR lpData, int lenData) {
      void *param[1+1] = {(void*)lpData, 0};
      int cbparam[1+1] = {lenData, 0};
      IPWorks_SMPP_Do(m_pObj, 10000+14, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline LPWSTR SendMessage(LPWSTR lpszMessage) {
      void *param[1+1] = {(void*)lpszMessage, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SMPP_Do(m_pObj, 10000+15, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }

};

#endif //WIN32

#endif //_IPWORKS_SMPP_H_




