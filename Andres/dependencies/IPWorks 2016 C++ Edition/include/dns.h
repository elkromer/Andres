/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_DNS_H_
#define _IPWORKS_DNS_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

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


extern "C" void* IPWORKS_CALL IPWorks_DNS_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_DNS_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_DNS_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_DNS_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_DNS_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_DNS_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_DNS_GetLastErrorCode(void *lpObj);
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
  const char* Description;
  int reserved;
} DNSErrorEventParams;

typedef struct {
  int RequestId;
  const char* Domain;
  int StatusCode;
  const char* Description;
  int Authoritative;
  int reserved;
} DNSResponseEventParams;



class DNS {
  
  public: //events
  
    virtual int FireError(DNSErrorEventParams *e) {return 0;}
    virtual int FireResponse(DNSResponseEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL DNSEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((DNS*)lpObj)->DNSEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            DNSErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((DNS*)lpObj)->FireError(&e);
            break;
         }
         case 2: {
            DNSResponseEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]),  0};
            ret_code = ((DNS*)lpObj)->FireResponse(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int DNSEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    DNS(char *lpOemKey = (char*)IPWORKS_OEMKEY_58) {
      m_pObj = IPWorks_DNS_Create(DNSEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~DNS() {
      IPWorks_DNS_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_DNS_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_DNS_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_DNS_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_DNS_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_DNS_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetDNSPort() {
      void* val = IPWorks_DNS_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetDNSPort(int lDNSPort) {
      void* val = (void*)IPW64CAST(lDNSPort);
      return IPWorks_DNS_Set(m_pObj, 1, 0, val, 0);
    }
    inline char* GetDNSServer() {
      void* val = IPWorks_DNS_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetDNSServer(const char *lpDNSServer) {
      return IPWorks_DNS_Set(m_pObj, 2, 0, (void*)lpDNSServer, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_DNS_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_DNS_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_DNS_Set(m_pObj, 4, 0, (void*)lpLocalHost, 0);
    }

    inline int GetQueryType() {
      void* val = IPWorks_DNS_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetQueryType(int iQueryType) {
      void* val = (void*)IPW64CAST(iQueryType);
      return IPWorks_DNS_Set(m_pObj, 5, 0, val, 0);
    }
    inline int GetRecordCount() {
      void* val = IPWorks_DNS_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }

    inline char* GetRecordDomain(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 7, iRecordIndex, 0);
      return (char*)val;
    }


    inline int GetRecordFieldCount(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 8, iRecordIndex, 0);
      return (int)(long)val;
    }

    inline int GetRecordFieldIndex(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 9, iRecordIndex, 0);
      return (int)(long)val;
    }
    inline int SetRecordFieldIndex(int iRecordIndex, int iRecordFieldIndex) {
      void* val = (void*)IPW64CAST(iRecordFieldIndex);
      return IPWorks_DNS_Set(m_pObj, 9, iRecordIndex, val, 0);
    }
    inline char* GetRecordFieldName(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 10, iRecordIndex, 0);
      return (char*)val;
    }


    inline int GetRecordFieldValue(int iRecordIndex, char *&lpRecordFieldValue, int &lenRecordFieldValue) {
      lpRecordFieldValue = (char*)IPWorks_DNS_Get(m_pObj, 11, iRecordIndex, &lenRecordFieldValue);
      return lpRecordFieldValue ? 0 : lenRecordFieldValue;
    }


    inline int GetRecordData(int iRecordIndex, char *&lpRecordData, int &lenRecordData) {
      lpRecordData = (char*)IPWorks_DNS_Get(m_pObj, 12, iRecordIndex, &lenRecordData);
      return lpRecordData ? 0 : lenRecordData;
    }


    inline int GetRecordType(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 13, iRecordIndex, 0);
      return (int)(long)val;
    }

    inline char* GetRecordTypeName(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 14, iRecordIndex, 0);
      return (char*)val;
    }


    inline int GetRecordTTL(int iRecordIndex) {
      void* val = IPWorks_DNS_Get(m_pObj, 15, iRecordIndex, 0);
      return (int)(long)val;
    }

    inline int GetRecordSource() {
      void* val = IPWorks_DNS_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetRecordSource(int iRecordSource) {
      void* val = (void*)IPW64CAST(iRecordSource);
      return IPWorks_DNS_Set(m_pObj, 16, 0, val, 0);
    }
    inline int GetRecursive() {
      void* val = IPWorks_DNS_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetRecursive(int bRecursive) {
      void* val = (void*)IPW64CAST(bRecursive);
      return IPWorks_DNS_Set(m_pObj, 17, 0, val, 0);
    }
    inline int GetRequestId() {
      void* val = IPWorks_DNS_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }
    inline int SetRequestId(int iRequestId) {
      void* val = (void*)IPW64CAST(iRequestId);
      return IPWorks_DNS_Set(m_pObj, 18, 0, val, 0);
    }
    inline char* GetStatus() {
      void* val = IPWorks_DNS_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }


    inline int GetStatusCode() {
      void* val = IPWorks_DNS_Get(m_pObj, 20, 0, 0);
      return (int)(long)val;
    }

    inline int GetTimeout() {
      void* val = IPWorks_DNS_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_DNS_Set(m_pObj, 21, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_DNS_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline char* GetFieldValue(int iRecordIndex, const char* lpszFieldName) {
      void *param[2+1] = {(void*)IPW64CAST(iRecordIndex), (void*)IPW64CAST(lpszFieldName), 0};
      int cbparam[2+1] = {0, 0, 0};
      IPWorks_DNS_Do(m_pObj, 4, 2, param, cbparam);
      
      return (char*)IPW64CAST(param[2]);
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int Query(const char* lpszDomain) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDomain), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_DNS_Do(m_pObj, 6, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} DNSErrorEventParamsW;

typedef struct {
  int RequestId;
  LPWSTR Domain;
  int StatusCode;
  LPWSTR Description;
  int Authoritative;
  int reserved;
} DNSResponseEventParamsW;



class DNSW : public DNS {

  public: //properties
  


    inline LPWSTR GetDNSServer() {
      return (LPWSTR)IPWorks_DNS_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetDNSServer(LPCWSTR lpDNSServer) {
      return IPWorks_DNS_Set(m_pObj, 10000+2, 0, (void*)lpDNSServer, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_DNS_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_DNS_Set(m_pObj, 10000+4, 0, (void*)lpLocalHost, 0);
    }





    inline LPWSTR GetRecordDomain(int iRecordIndex) {
      return (LPWSTR)IPWorks_DNS_Get(m_pObj, 10000+7, iRecordIndex, 0);
    }







    inline LPWSTR GetRecordFieldName(int iRecordIndex) {
      return (LPWSTR)IPWorks_DNS_Get(m_pObj, 10000+10, iRecordIndex, 0);
    }



    inline LPWSTR GetRecordFieldValue(int iRecordIndex) {
      return (LPWSTR)IPWorks_DNS_Get(m_pObj, 10000+11, iRecordIndex, 0);
    }


    inline int GetRecordFieldValueB(int iRecordIndex, char *&lpRecordFieldValue, int &lenRecordFieldValue) {
      lpRecordFieldValue = (char*)IPWorks_DNS_Get(m_pObj, 11, iRecordIndex, &lenRecordFieldValue);
      return lpRecordFieldValue ? 0 : lenRecordFieldValue;
    }

    inline LPWSTR GetRecordData(int iRecordIndex) {
      return (LPWSTR)IPWorks_DNS_Get(m_pObj, 10000+12, iRecordIndex, 0);
    }


    inline int GetRecordDataB(int iRecordIndex, char *&lpRecordData, int &lenRecordData) {
      lpRecordData = (char*)IPWorks_DNS_Get(m_pObj, 12, iRecordIndex, &lenRecordData);
      return lpRecordData ? 0 : lenRecordData;
    }



    inline LPWSTR GetRecordTypeName(int iRecordIndex) {
      return (LPWSTR)IPWorks_DNS_Get(m_pObj, 10000+14, iRecordIndex, 0);
    }











    inline LPWSTR GetStatus() {
      return (LPWSTR)IPWorks_DNS_Get(m_pObj, 10000+19, 0, 0);
    }









  public: //events
  
    virtual int FireError(DNSErrorEventParamsW *e) {return 0;}
    virtual int FireResponse(DNSResponseEventParamsW *e) {return 0;}


  protected:
  
    virtual int DNSEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            DNSErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 2: {
            DNSResponseEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]),  0};
            ret_code = FireResponse(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireError(DNSErrorEventParams *e) {return -10000;}
    virtual int FireResponse(DNSResponseEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_DNS_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline LPWSTR GetFieldValue(int iRecordIndex, LPWSTR lpszFieldName) {
      void *param[2+1] = {(void*)iRecordIndex, (void*)lpszFieldName, 0};
      int cbparam[2+1] = {0, 0, 0};
      IPWorks_DNS_Do(m_pObj, 10000+4, 2, param, cbparam);
      return (LPWSTR)IPW64CAST(param[2]);
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int Query(LPWSTR lpszDomain) {
      void *param[1+1] = {(void*)lpszDomain, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_DNS_Do(m_pObj, 10000+6, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_DNS_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_DNS_H_




