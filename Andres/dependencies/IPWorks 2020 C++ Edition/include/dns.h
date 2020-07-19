/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_DNS_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_DNS_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_DNS_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_DNS_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_DNS_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_DNS_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_DNS_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} DNSErrorEventParams;

typedef struct {
  int RequestId;
  const char *Domain;
  int StatusCode;
  const char *Description;
  int Authoritative;
  int reserved;
} DNSResponseEventParams;

typedef struct {
  const char *RemoteAddress;
  int RemotePort;
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} DNSSSLServerAuthenticationEventParams;

typedef struct {
  const char *RemoteAddress;
  int RemotePort;
  const char *Message;
  int reserved;
} DNSSSLStatusEventParams;


class DNS {
  public: // Events
    virtual int FireError(DNSErrorEventParams *e) {return 0;}
    virtual int FireResponse(DNSResponseEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(DNSSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(DNSSSLStatusEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL DNSEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          DNSErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((DNS*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          DNSResponseEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((DNS*)lpObj)->FireResponse(&e);
          break;
        }
        case 3: {
          DNSSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), 0};
          ret_code = ((DNS*)lpObj)->FireSSLServerAuthentication(&e);
          param[6] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 4: {
          DNSSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((DNS*)lpObj)->FireSSLStatus(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    DNS(char *lpOemKey = (char*)IPWORKS_OEMKEY_58) {
      m_pObj = IPWorks_DNS_Create(DNSEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~DNS() {
      IPWorks_DNS_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_DNS_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_DNS_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_DNS_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_DNS_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_DNS_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetDNSPort() {
      void* val = IPWorks_DNS_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetDNSPort(int iDNSPort) {
      void* val = (void*)IPW64CAST(iDNSPort);
      return IPWorks_DNS_Set(m_pObj, 1, 0, val, 0);
    }

    inline char* GetDNSServer() {
      void* val = IPWorks_DNS_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetDNSServer(const char* lpszDNSServer) {
      return IPWorks_DNS_Set(m_pObj, 2, 0, (void*)lpszDNSServer, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_DNS_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_DNS_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_DNS_Set(m_pObj, 4, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetProtocol() {
      void* val = IPWorks_DNS_Get(m_pObj, 5, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProtocol(int iProtocol) {
      void* val = (void*)IPW64CAST(iProtocol);
      return IPWorks_DNS_Set(m_pObj, 5, 0, val, 0);
    }

    inline int GetQueryType() {
      void* val = IPWorks_DNS_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetQueryType(int iQueryType) {
      void* val = (void*)IPW64CAST(iQueryType);
      return IPWorks_DNS_Set(m_pObj, 6, 0, val, 0);
    }

    inline int GetRecordCount() {
      void* val = IPWorks_DNS_Get(m_pObj, 7, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetRecordDomain(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 8, iRecordIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetRecordFieldCount(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 9, iRecordIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetRecordFieldIndex(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 10, iRecordIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRecordFieldIndex(int iRecordIndex, int iRecordFieldIndex) {
      void* val = (void*)IPW64CAST(iRecordFieldIndex);
      return IPWorks_DNS_Set(m_pObj, 10, iRecordIndex, val, 0);
    }

    inline char* GetRecordFieldName(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 11, iRecordIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetRecordFieldValue(int iRecordIndex, char* &lpRecordFieldValue, int &lenRecordFieldValue) {
      lpRecordFieldValue = (char*)IPWorks_DNS_Get(m_pObj, 12, iRecordIndex, &lenRecordFieldValue, NULL);
      return lpRecordFieldValue ? 0 : lenRecordFieldValue;
    }

    inline int GetRecordData(int iRecordIndex, char* &lpRecordData, int &lenRecordData) {
      lpRecordData = (char*)IPWorks_DNS_Get(m_pObj, 13, iRecordIndex, &lenRecordData, NULL);
      return lpRecordData ? 0 : lenRecordData;
    }

    inline int GetRecordType(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 14, iRecordIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetRecordTypeName(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 15, iRecordIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetRecordTTL(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 16, iRecordIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetRecordSource() {
      void* val = IPWorks_DNS_Get(m_pObj, 17, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRecordSource(int iRecordSource) {
      void* val = (void*)IPW64CAST(iRecordSource);
      return IPWorks_DNS_Set(m_pObj, 17, 0, val, 0);
    }

    inline int GetRecursive() {
      void* val = IPWorks_DNS_Get(m_pObj, 18, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRecursive(int bRecursive) {
      void* val = (void*)IPW64CAST(bRecursive);
      return IPWorks_DNS_Set(m_pObj, 18, 0, val, 0);
    }

    inline int GetRequestId() {
      void* val = IPWorks_DNS_Get(m_pObj, 19, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRequestId(int iRequestId) {
      void* val = (void*)IPW64CAST(iRequestId);
      return IPWorks_DNS_Set(m_pObj, 19, 0, val, 0);
    }

    inline char* GetStatus() {
      void* val = IPWorks_DNS_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetStatusCode() {
      void* val = IPWorks_DNS_Get(m_pObj, 21, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetTimeout() {
      void* val = IPWorks_DNS_Get(m_pObj, 22, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_DNS_Set(m_pObj, 22, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_DNS_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline char* GetFieldValue(int iRecordIndex, const char* lpszFieldName) {
      void *param[2+1] = {(void*)IPW64CAST(iRecordIndex), (void*)IPW64CAST(lpszFieldName), 0};
      int cbparam[2+1] = {0, 0, 0};
      IPWorks_DNS_Do(m_pObj, 4, 2, param, cbparam, NULL);
      return (char*)IPW64CAST(param[2]);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int Query(const char* lpszDomain) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDomain), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_DNS_Do(m_pObj, 6, 1, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_DNS_H_
