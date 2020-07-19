/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_DNS_H_
#define _IPWORKS_DNS_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//DNSProtocol
#define PT_UDP                                             0
#define PT_TCP                                             1
#define PT_TLS                                             2
#define PT_HTTPS                                           3

//TQueryType
#define QT_ADDRESS                                         1
#define QT_NS                                              2
#define QT_MD                                              3
#define QT_MF                                              4
#define QT_CNAME                                           5
#define QT_SOA                                             6
#define QT_MAIL_BOX                                        7
#define QT_MAIL_GROUP                                      8
#define QT_MR                                              9
#define QT_NULL                                            10
#define QT_WKS                                             11
#define QT_POINTER                                         12
#define QT_HOST_INFO                                       13
#define QT_MAIL_INFO                                       14
#define QT_MX                                              15
#define QT_TEXT                                            16
#define QT_RP                                              17
#define QT_AFSDB                                           18
#define QT_X25                                             19
#define QT_ISDN                                            20
#define QT_RT                                              21
#define QT_AAAA                                            28
#define QT_SRV                                             33
#define QT_NAPTR                                           35
#define QT_CERT                                            37
#define QT_REV_LOOKUP                                      100

//DNSRecordTypes
#define RT_ADDRESS                                         1
#define RT_NS                                              2
#define RT_MD                                              3
#define RT_MF                                              4
#define RT_CNAME                                           5
#define RT_SOA                                             6
#define RT_MAIL_BOX                                        7
#define RT_MAIL_GROUP                                      8
#define RT_MR                                              9
#define RT_NULL                                            10
#define RT_WKS                                             11
#define RT_POINTER                                         12
#define RT_HOST_INFO                                       13
#define RT_MAIL_INFO                                       14
#define RT_MX                                              15
#define RT_TEXT                                            16
#define RT_RP                                              17
#define RT_AFSDB                                           18
#define RT_X25                                             19
#define RT_ISDN                                            20
#define RT_RT                                              21
#define RT_AAAA                                            28
#define RT_SRV                                             33
#define RT_NAPTR                                           35

//TRecordSource
#define RS_ANSWER_SECTION                                  0
#define RS_NAME_SERVER_SECTION                             1
#define RS_ADDITIONAL_RECORDS_SECTION                      2


extern "C" void* IPWORKS_CALL IPWorks_DNS_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_DNS_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_DNS_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_DNS_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_DNS_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_DNS_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_DNS_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_DNS_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_DNS_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} DNSErrorEventParams;

typedef struct {
  INT RequestId;
  LPCWSTR Domain;
  INT StatusCode;
  LPCWSTR Description;
  BOOL Authoritative;
  INT reserved;
} DNSResponseEventParams;

typedef struct {
  LPCWSTR RemoteAddress;
  INT RemotePort;
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} DNSSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR RemoteAddress;
  INT RemotePort;
  LPCWSTR Message;
  INT reserved;
} DNSSSLStatusEventParams;


class DNS {
  public: // Events
    virtual INT FireError(DNSErrorEventParams *e) {return 0;}
    virtual INT FireResponse(DNSResponseEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(DNSSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(DNSSSLStatusEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL DNSEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          DNSErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((DNS*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          DNSResponseEventParams e = {(INT)param[0], (LPWSTR)param[1], (INT)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((DNS*)lpObj)->FireResponse(&e);
          break;
        }
        case 3: {
          DNSSSLServerAuthenticationEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPSTR)param[2], (INT)cbparam[2], (LPWSTR)param[3], (LPWSTR)param[4], (LPWSTR)param[5], (BOOL)param[6], 0};
          ret_code = ((DNS*)lpObj)->FireSSLServerAuthentication(&e);
          param[6] = (LPVOID)e.Accept;
          break;
        }
        case 4: {
          DNSSSLStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((DNS*)lpObj)->FireSSLStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    DNS(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_58) {
      m_pObj = IPWorks_DNS_Create(DNSEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~DNS() {
      IPWorks_DNS_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_DNS_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_DNS_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_DNS_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_DNS_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_DNS_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetDNSPort() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 1, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetDNSPort(INT iDNSPort) {
      LPVOID val = (LPVOID)(iDNSPort);
      return IPWorks_DNS_Set(m_pObj, 1, 0, val, 0);
    }

    inline LPWSTR GetDNSServer() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDNSServer(LPCWSTR lpszDNSServer) {
      return IPWorks_DNS_Set(m_pObj, 2+10000, 0, (LPVOID)lpszDNSServer, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 3, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_DNS_Set(m_pObj, 4+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetProtocol() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 5, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProtocol(INT iProtocol) {
      LPVOID val = (LPVOID)(iProtocol);
      return IPWorks_DNS_Set(m_pObj, 5, 0, val, 0);
    }

    inline INT GetQueryType() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetQueryType(INT iQueryType) {
      LPVOID val = (LPVOID)(iQueryType);
      return IPWorks_DNS_Set(m_pObj, 6, 0, val, 0);
    }

    inline INT GetRecordCount() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 7, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetRecordDomain(INT iRecordIndex) {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 8+10000, iRecordIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetRecordFieldCount(INT iRecordIndex) {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 9, iRecordIndex, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetRecordFieldIndex(INT iRecordIndex) {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 10, iRecordIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRecordFieldIndex(INT iRecordIndex, INT iRecordFieldIndex) {
      LPVOID val = (LPVOID)(iRecordFieldIndex);
      return IPWorks_DNS_Set(m_pObj, 10, iRecordIndex, val, 0);
    }

    inline LPWSTR GetRecordFieldName(INT iRecordIndex) {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 11+10000, iRecordIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetRecordFieldValue(INT iRecordIndex, LPSTR &lpRecordFieldValue, INT &lenRecordFieldValue) {
      lpRecordFieldValue = (LPSTR)IPWorks_DNS_Get(m_pObj, 12, iRecordIndex, &lenRecordFieldValue, NULL);
      return lpRecordFieldValue ? 0 : lenRecordFieldValue;
    }

    inline INT GetRecordData(INT iRecordIndex, LPSTR &lpRecordData, INT &lenRecordData) {
      lpRecordData = (LPSTR)IPWorks_DNS_Get(m_pObj, 13, iRecordIndex, &lenRecordData, NULL);
      return lpRecordData ? 0 : lenRecordData;
    }

    inline INT GetRecordType(INT iRecordIndex) {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 14, iRecordIndex, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetRecordTypeName(INT iRecordIndex) {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 15+10000, iRecordIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetRecordTTL(INT iRecordIndex) {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 16, iRecordIndex, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetRecordSource() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 17, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRecordSource(INT iRecordSource) {
      LPVOID val = (LPVOID)(iRecordSource);
      return IPWorks_DNS_Set(m_pObj, 17, 0, val, 0);
    }

    inline BOOL GetRecursive() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 18, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetRecursive(BOOL bRecursive) {
      LPVOID val = (LPVOID)(bRecursive);
      return IPWorks_DNS_Set(m_pObj, 18, 0, val, 0);
    }

    inline INT GetRequestId() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 19, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRequestId(INT iRequestId) {
      LPVOID val = (LPVOID)(iRequestId);
      return IPWorks_DNS_Set(m_pObj, 19, 0, val, 0);
    }

    inline LPWSTR GetStatus() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetStatusCode() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 21, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_DNS_Get(m_pObj, 22, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_DNS_Set(m_pObj, 22, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_DNS_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR GetFieldValue(INT iRecordIndex, LPCWSTR lpszFieldName) {
      LPVOID param[2+1] = {(LPVOID)iRecordIndex, (LPVOID)lpszFieldName, 0};
      INT cbparam[2+1] = {0, 0, 0};
      IPWorks_DNS_Do(m_pObj, 4+10000, 2, param, cbparam, NULL);
      return (LPWSTR)param[2];
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT Query(LPCWSTR lpszDomain) {
      LPVOID param[1+1] = {(LPVOID)lpszDomain, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_DNS_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_DNS_H_
