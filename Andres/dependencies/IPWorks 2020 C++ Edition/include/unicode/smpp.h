/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

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
#define CST_SECURITY_KEY                                   20
#define CST_AUTO                                           99

//TSSLStartMode
#define SSL_AUTOMATIC                                      0
#define SSL_IMPLICIT                                       1
#define SSL_EXPLICIT                                       2
#define SSL_NONE                                           3


extern "C" void* IPWORKS_CALL IPWorks_SMPP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SMPP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_SMPP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_SMPP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SMPP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SMPPConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SMPPConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} SMPPDisconnectedEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} SMPPErrorEventParams;

typedef struct {
  LPCWSTR SourceAddress;
  LPCWSTR ScheduleDeliveryTime;
  LPCWSTR ValidityPeriod;
  LPCWSTR Message;
  INT MessagePart;
  INT MessagePartCount;
  INT MessagePartReference;
  LPCWSTR DestinationAddress;
  INT ResponseErrorCode;
  INT reserved;
} SMPPMessageInEventParams;

typedef struct {
  LPCWSTR MessageId;
  INT MessageState;
  INT MessageError;
  LPCWSTR FinalDate;
  INT reserved;
} SMPPMessageStatusEventParams;

typedef struct {
  INT Direction;
  LPCSTR PDU;
  INT lenPDU;
  INT CommandLength;
  INT CommandId;
  LPCWSTR CommandDescription;
  LPCWSTR CommandStatus;
  INT SequenceNumber;
  INT reserved;
} SMPPPITrailEventParams;

typedef struct {
  INT reserved;
} SMPPReadyToSendEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} SMPPSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} SMPPSSLStatusEventParams;


class SMPP {
  public: // Events
    virtual INT FireConnected(SMPPConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(SMPPConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(SMPPDisconnectedEventParams *e) {return 0;}
    virtual INT FireError(SMPPErrorEventParams *e) {return 0;}
    virtual INT FireMessageIn(SMPPMessageInEventParams *e) {return 0;}
    virtual INT FireMessageStatus(SMPPMessageStatusEventParams *e) {return 0;}
    virtual INT FirePITrail(SMPPPITrailEventParams *e) {return 0;}
    virtual INT FireReadyToSend(SMPPReadyToSendEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(SMPPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(SMPPSSLStatusEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL SMPPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          SMPPConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((SMPP*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          SMPPConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((SMPP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          SMPPDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((SMPP*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          SMPPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((SMPP*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          SMPPMessageInEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (INT)param[4], (INT)param[5], (INT)param[6], (LPWSTR)param[7], (INT)param[8], 0};
          ret_code = ((SMPP*)lpObj)->FireMessageIn(&e);
          param[8] = (LPVOID)e.ResponseErrorCode;
          break;
        }
        case 6: {
          SMPPMessageStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (INT)param[2], (LPWSTR)param[3], 0};
          ret_code = ((SMPP*)lpObj)->FireMessageStatus(&e);
          break;
        }
        case 7: {
          SMPPPITrailEventParams e = {(INT)param[0], (LPSTR)param[1], (INT)cbparam[1], (INT)param[2], (INT)param[3], (LPWSTR)param[4], (LPWSTR)param[5], (INT)param[6], 0};
          ret_code = ((SMPP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 8: {
          SMPPReadyToSendEventParams e = {0};
          ret_code = ((SMPP*)lpObj)->FireReadyToSend(&e);
          break;
        }
        case 9: {
          SMPPSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((SMPP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 10: {
          SMPPSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((SMPP*)lpObj)->FireSSLStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    SMPP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_71) {
      m_pObj = IPWorks_SMPP_Create(SMPPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~SMPP() {
      IPWorks_SMPP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_SMPP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_SMPP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_SMPP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_SMPP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_SMPP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetConnected() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 2, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_SMPP_Set(m_pObj, 2, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 3, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_SMPP_Set(m_pObj, 3, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_SMPP_Set(m_pObj, 4+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_SMPP_Set(m_pObj, 5+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_SMPP_Set(m_pObj, 6, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_SMPP_Set(m_pObj, 7+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 8, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_SMPP_Set(m_pObj, 9+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetMessageExpiration() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetMessageExpiration(LPCWSTR lpszMessageExpiration) {
      return IPWorks_SMPP_Set(m_pObj, 10+10000, 0, (LPVOID)lpszMessageExpiration, 0);
    }

    inline LPWSTR GetMessageId() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetMessagePriority() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 12, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMessagePriority(INT iMessagePriority) {
      LPVOID val = (LPVOID)(iMessagePriority);
      return IPWorks_SMPP_Set(m_pObj, 12, 0, val, 0);
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_SMPP_Set(m_pObj, 13+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetProtocol() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 14, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProtocol(INT iProtocol) {
      LPVOID val = (LPVOID)(iProtocol);
      return IPWorks_SMPP_Set(m_pObj, 14, 0, val, 0);
    }

    inline INT GetRecipientCount() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 15, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRecipientCount(INT iRecipientCount) {
      LPVOID val = (LPVOID)(iRecipientCount);
      return IPWorks_SMPP_Set(m_pObj, 15, 0, val, 0);
    }

    inline LPWSTR GetRecipientAddress(INT iRecipientIndex) {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 16+10000, iRecipientIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRecipientAddress(INT iRecipientIndex, LPCWSTR lpszRecipientAddress) {
      return IPWorks_SMPP_Set(m_pObj, 16+10000, iRecipientIndex, (LPVOID)lpszRecipientAddress, 0);
    }

    inline INT GetRecipientType(INT iRecipientIndex) {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 17, iRecipientIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRecipientType(INT iRecipientIndex, INT iRecipientType) {
      LPVOID val = (LPVOID)(iRecipientType);
      return IPWorks_SMPP_Set(m_pObj, 17, iRecipientIndex, val, 0);
    }

    inline LPWSTR GetScheduledDelivery() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetScheduledDelivery(LPCWSTR lpszScheduledDelivery) {
      return IPWorks_SMPP_Set(m_pObj, 18+10000, 0, (LPVOID)lpszScheduledDelivery, 0);
    }

    inline LPWSTR GetSenderAddress() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSenderAddress(LPCWSTR lpszSenderAddress) {
      return IPWorks_SMPP_Set(m_pObj, 19+10000, 0, (LPVOID)lpszSenderAddress, 0);
    }

    inline INT GetServiceType() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 20, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetServiceType(INT iServiceType) {
      LPVOID val = (LPVOID)(iServiceType);
      return IPWorks_SMPP_Set(m_pObj, 20, 0, val, 0);
    }

    inline INT GetSMPPPort() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 21, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSMPPPort(INT iSMPPPort) {
      LPVOID val = (LPVOID)(iSMPPPort);
      return IPWorks_SMPP_Set(m_pObj, 21, 0, val, 0);
    }

    inline LPWSTR GetSMPPServer() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSMPPServer(LPCWSTR lpszSMPPServer) {
      return IPWorks_SMPP_Set(m_pObj, 22+10000, 0, (LPVOID)lpszSMPPServer, 0);
    }

    inline INT GetSMPPVersion() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 23, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSMPPVersion(INT iSMPPVersion) {
      LPVOID val = (LPVOID)(iSMPPVersion);
      return IPWorks_SMPP_Set(m_pObj, 23, 0, val, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_SMPP_Get(m_pObj, 24, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_SMPP_Set(m_pObj, 24, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_SMPP_Get(m_pObj, 25, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_SMPP_Set(m_pObj, 25, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_SMPP_Get(m_pObj, 26, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_SMPP_Set(m_pObj, 26, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 27+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_SMPP_Set(m_pObj, 27+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 28, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_SMPP_Set(m_pObj, 28, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_SMPP_Set(m_pObj, 29+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 30, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_SMPP_Set(m_pObj, 30, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_SMPP_Get(m_pObj, 31, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 32, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_SMPP_Set(m_pObj, 32, 0, val, 0);
    }

    inline LPWSTR GetSystemType() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 33+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSystemType(LPCWSTR lpszSystemType) {
      return IPWorks_SMPP_Set(m_pObj, 33+10000, 0, (LPVOID)lpszSystemType, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 34, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_SMPP_Set(m_pObj, 34, 0, val, 0);
    }

    inline LPWSTR GetUserId() {
      LPVOID val = IPWorks_SMPP_Get(m_pObj, 35+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUserId(LPCWSTR lpszUserId) {
      return IPWorks_SMPP_Set(m_pObj, 35+10000, 0, (LPVOID)lpszUserId, 0);
    }

  public: // Methods
    inline INT AddRecipient(INT iRecipientType, LPCWSTR lpszRecipientAddress) {
      LPVOID param[2+1] = {(LPVOID)iRecipientType, (LPVOID)lpszRecipientAddress, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_SMPP_Do(m_pObj, 2+10000, 2, param, cbparam, NULL);
    }

    inline INT CancelMessage(LPCWSTR lpszMessageId) {
      LPVOID param[1+1] = {(LPVOID)lpszMessageId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_SMPP_Do(m_pObj, 3+10000, 1, param, cbparam, NULL);
    }

    inline INT CheckLink() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT CheckMessageStatus(LPCWSTR lpszMessageId) {
      LPVOID param[1+1] = {(LPVOID)lpszMessageId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_SMPP_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_SMPP_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Connect(LPCWSTR lpszUserId, LPCWSTR lpszPassword) {
      LPVOID param[2+1] = {(LPVOID)lpszUserId, (LPVOID)lpszPassword, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_SMPP_Do(m_pObj, 7+10000, 2, param, cbparam, NULL);
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT ReplaceMessage(LPCWSTR lpszMessageId, LPCWSTR lpszNewMessage) {
      LPVOID param[2+1] = {(LPVOID)lpszMessageId, (LPVOID)lpszNewMessage, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_SMPP_Do(m_pObj, 11+10000, 2, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_SMPP_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
    }

    inline LPSTR SendCommand(INT iCommandId, LPCSTR lpPayload, INT lenPayload, LPINT lpSize = NULL) {
      LPVOID param[2+1] = {(LPVOID)iCommandId, (LPVOID)lpPayload, 0};
      INT cbparam[2+1] = {0, lenPayload, 0};
      IPWorks_SMPP_Do(m_pObj, 13+10000, 2, param, cbparam, NULL);
      if (lpSize) *lpSize = cbparam[2];
      return (LPSTR)param[2];
    }

    inline LPWSTR SendData(LPCSTR lpData, INT lenData) {
      LPVOID param[1+1] = {(LPVOID)lpData, 0};
      INT cbparam[1+1] = {lenData, 0};
      IPWorks_SMPP_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline LPWSTR SendMessage(LPCWSTR lpszMessage) {
      LPVOID param[1+1] = {(LPVOID)lpszMessage, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_SMPP_Do(m_pObj, 15+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

};

#endif //_IPWORKS_SMPP_H_
