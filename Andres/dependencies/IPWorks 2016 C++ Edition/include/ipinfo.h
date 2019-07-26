/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_IPINFO_H_
#define _IPWORKS_IPINFO_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_IPInfo_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_IPInfo_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_IPInfo_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IPInfo_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  const char* RecordName;
  int RecordType;
  int TimeToLive;
  int DataLength;
  const char* Section;
  const char* RecordValue;
  const char* RecordInfo;
  int reserved;
} IPInfoDNSCacheEntryEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} IPInfoErrorEventParams;

typedef struct {
  int RequestId;
  int StatusCode;
  const char* Description;
  int reserved;
} IPInfoRequestCompleteEventParams;



class IPInfo {
  
  public: //events
  
    virtual int FireDNSCacheEntry(IPInfoDNSCacheEntryEventParams *e) {return 0;}
    virtual int FireError(IPInfoErrorEventParams *e) {return 0;}
    virtual int FireRequestComplete(IPInfoRequestCompleteEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL IPInfoEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((IPInfo*)lpObj)->IPInfoEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            IPInfoDNSCacheEntryEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (char*)IPW64CAST(param[6]),  0};
            ret_code = ((IPInfo*)lpObj)->FireDNSCacheEntry(&e);
            break;
         }
         case 2: {
            IPInfoErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((IPInfo*)lpObj)->FireError(&e);
            break;
         }
         case 3: {
            IPInfoRequestCompleteEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((IPInfo*)lpObj)->FireRequestComplete(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int IPInfoEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    IPInfo(char *lpOemKey = (char*)IPWORKS_OEMKEY_15) {
      m_pObj = IPWorks_IPInfo_Create(IPInfoEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~IPInfo() {
      IPWorks_IPInfo_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_IPInfo_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_IPInfo_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_IPInfo_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_IPInfo_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_IPInfo_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetAdapterBroadcastAddress() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }


    inline int GetAdapterCount() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }

    inline char* GetAdapterDescription() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }


    inline int GetAdapterDeviceIndex() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }

    inline int GetAdapterDHCPEnabled() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }

    inline char* GetAdapterDHCPServer() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterDNSServers() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterGateway() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }


    inline int GetAdapterIndex() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetAdapterIndex(int iAdapterIndex) {
      void* val = (void*)IPW64CAST(iAdapterIndex);
      return IPWorks_IPInfo_Set(m_pObj, 9, 0, val, 0);
    }
    inline char* GetAdapterIPAddress() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterIPv6Address() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterLeaseExpires() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterLeaseObtained() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterName() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterOtherIPAddresses() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterPhysicalAddress() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterPrimaryWINSServer() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterSecondaryWINSServer() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterSubnetMask() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }


    inline char* GetAdapterType() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }


    inline int GetAdapterUsesWINS() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }

    inline int GetAdapterZoneId() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 22, 0, 0);
      return (int)(long)val;
    }

    inline int GetARPProxy() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }

    inline char* GetDHCPScope() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }


    inline int GetDNSEnabled() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 25, 0, 0);
      return (int)(long)val;
    }

    inline char* GetDNSServer() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }


    inline char* GetDomainName() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 27, 0, 0);
      return (char*)val;
    }


    inline char* GetHostAddress() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }

    inline int SetHostAddress(const char *lpHostAddress) {
      return IPWorks_IPInfo_Set(m_pObj, 28, 0, (void*)lpHostAddress, 0);
    }

    inline char* GetHostAliases() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 29, 0, 0);
      return (char*)val;
    }


    inline char* GetHostName() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 30, 0, 0);
      return (char*)val;
    }

    inline int SetHostName(const char *lpHostName) {
      return IPWorks_IPInfo_Set(m_pObj, 30, 0, (void*)lpHostName, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 31, 0, 0);
      return (char*)val;
    }


    inline char* GetNodeType() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 32, 0, 0);
      return (char*)val;
    }


    inline char* GetOtherAddresses() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 33, 0, 0);
      return (char*)val;
    }


    inline char* GetOtherDNSServers() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 34, 0, 0);
      return (char*)val;
    }


    inline int GetPendingRequests() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 35, 0, 0);
      return (int)(long)val;
    }
    inline int SetPendingRequests(int iPendingRequests) {
      void* val = (void*)IPW64CAST(iPendingRequests);
      return IPWorks_IPInfo_Set(m_pObj, 35, 0, val, 0);
    }
    inline int GetRequestId() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 36, 0, 0);
      return (int)(long)val;
    }

    inline int GetRoutingEnabled() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 37, 0, 0);
      return (int)(long)val;
    }

    inline char* GetServiceAliases() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 38, 0, 0);
      return (char*)val;
    }


    inline char* GetServiceName() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 39, 0, 0);
      return (char*)val;
    }

    inline int SetServiceName(const char *lpServiceName) {
      return IPWorks_IPInfo_Set(m_pObj, 39, 0, (void*)lpServiceName, 0);
    }

    inline int GetServicePort() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 40, 0, 0);
      return (int)(long)val;
    }
    inline int SetServicePort(int lServicePort) {
      void* val = (void*)IPW64CAST(lServicePort);
      return IPWorks_IPInfo_Set(m_pObj, 40, 0, val, 0);
    }
    inline char* GetServiceProtocol() {
      void* val = IPWorks_IPInfo_Get(m_pObj, 41, 0, 0);
      return (char*)val;
    }

    inline int SetServiceProtocol(const char *lpServiceProtocol) {
      return IPWorks_IPInfo_Set(m_pObj, 41, 0, (void*)lpServiceProtocol, 0);
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DHCPRelease() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int DHCPRenew() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline char* DisplayDNSCache() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_IPInfo_Do(m_pObj, 5, 0, param, cbparam);
      
      return (char*)IPW64CAST(param[0]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int FlushDNSCache() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_IPInfo_Do(m_pObj, 7, 0, param, cbparam);
      
      return (int)IPW64CAST(param[0]);
    }
    inline char* GetMAC(const char* lpszIPAddress) {
      void *param[1+1] = {(void*)IPW64CAST(lpszIPAddress), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 8, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline char* ResolveAddress(const char* lpszHostAddress) {
      void *param[1+1] = {(void*)IPW64CAST(lpszHostAddress), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 10, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline char* ResolveName(const char* lpszHostName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszHostName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 11, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR RecordName;
  int RecordType;
  int TimeToLive;
  int DataLength;
  LPWSTR Section;
  LPWSTR RecordValue;
  LPWSTR RecordInfo;
  int reserved;
} IPInfoDNSCacheEntryEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} IPInfoErrorEventParamsW;

typedef struct {
  int RequestId;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} IPInfoRequestCompleteEventParamsW;



class IPInfoW : public IPInfo {

  public: //properties
  
    inline LPWSTR GetAdapterBroadcastAddress() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+1, 0, 0);
    }





    inline LPWSTR GetAdapterDescription() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+3, 0, 0);
    }







    inline LPWSTR GetAdapterDHCPServer() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+6, 0, 0);
    }



    inline LPWSTR GetAdapterDNSServers() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+7, 0, 0);
    }



    inline LPWSTR GetAdapterGateway() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+8, 0, 0);
    }





    inline LPWSTR GetAdapterIPAddress() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+10, 0, 0);
    }



    inline LPWSTR GetAdapterIPv6Address() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+11, 0, 0);
    }



    inline LPWSTR GetAdapterLeaseExpires() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+12, 0, 0);
    }



    inline LPWSTR GetAdapterLeaseObtained() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+13, 0, 0);
    }



    inline LPWSTR GetAdapterName() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+14, 0, 0);
    }



    inline LPWSTR GetAdapterOtherIPAddresses() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+15, 0, 0);
    }



    inline LPWSTR GetAdapterPhysicalAddress() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+16, 0, 0);
    }



    inline LPWSTR GetAdapterPrimaryWINSServer() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+17, 0, 0);
    }



    inline LPWSTR GetAdapterSecondaryWINSServer() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+18, 0, 0);
    }



    inline LPWSTR GetAdapterSubnetMask() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+19, 0, 0);
    }



    inline LPWSTR GetAdapterType() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+20, 0, 0);
    }









    inline LPWSTR GetDHCPScope() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+24, 0, 0);
    }





    inline LPWSTR GetDNSServer() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+26, 0, 0);
    }



    inline LPWSTR GetDomainName() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+27, 0, 0);
    }



    inline LPWSTR GetHostAddress() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+28, 0, 0);
    }

    inline int SetHostAddress(LPCWSTR lpHostAddress) {
      return IPWorks_IPInfo_Set(m_pObj, 10000+28, 0, (void*)lpHostAddress, 0);
    }

    inline LPWSTR GetHostAliases() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+29, 0, 0);
    }



    inline LPWSTR GetHostName() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+30, 0, 0);
    }

    inline int SetHostName(LPCWSTR lpHostName) {
      return IPWorks_IPInfo_Set(m_pObj, 10000+30, 0, (void*)lpHostName, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+31, 0, 0);
    }



    inline LPWSTR GetNodeType() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+32, 0, 0);
    }



    inline LPWSTR GetOtherAddresses() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+33, 0, 0);
    }



    inline LPWSTR GetOtherDNSServers() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+34, 0, 0);
    }









    inline LPWSTR GetServiceAliases() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+38, 0, 0);
    }



    inline LPWSTR GetServiceName() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+39, 0, 0);
    }

    inline int SetServiceName(LPCWSTR lpServiceName) {
      return IPWorks_IPInfo_Set(m_pObj, 10000+39, 0, (void*)lpServiceName, 0);
    }



    inline LPWSTR GetServiceProtocol() {
      return (LPWSTR)IPWorks_IPInfo_Get(m_pObj, 10000+41, 0, 0);
    }

    inline int SetServiceProtocol(LPCWSTR lpServiceProtocol) {
      return IPWorks_IPInfo_Set(m_pObj, 10000+41, 0, (void*)lpServiceProtocol, 0);
    }



  public: //events
  
    virtual int FireDNSCacheEntry(IPInfoDNSCacheEntryEventParamsW *e) {return 0;}
    virtual int FireError(IPInfoErrorEventParamsW *e) {return 0;}
    virtual int FireRequestComplete(IPInfoRequestCompleteEventParamsW *e) {return 0;}


  protected:
  
    virtual int IPInfoEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            IPInfoDNSCacheEntryEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]), (LPWSTR)IPW64CAST(param[6]),  0};
            ret_code = FireDNSCacheEntry(&e);
            break;
         }
         case 2: {
            IPInfoErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 3: {
            IPInfoRequestCompleteEventParamsW e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireRequestComplete(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireDNSCacheEntry(IPInfoDNSCacheEntryEventParams *e) {return -10000;}
    virtual int FireError(IPInfoErrorEventParams *e) {return -10000;}
    virtual int FireRequestComplete(IPInfoRequestCompleteEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DHCPRelease() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int DHCPRenew() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline LPWSTR DisplayDNSCache() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_IPInfo_Do(m_pObj, 10000+5, 0, param, cbparam);
      return (LPWSTR)IPW64CAST(param[0]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int FlushDNSCache() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_IPInfo_Do(m_pObj, 10000+7, 0, param, cbparam);
      return (int)IPW64CAST(param[0]);
    }
    inline LPWSTR GetMAC(LPWSTR lpszIPAddress) {
      void *param[1+1] = {(void*)lpszIPAddress, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 10000+8, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPInfo_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline LPWSTR ResolveAddress(LPWSTR lpszHostAddress) {
      void *param[1+1] = {(void*)lpszHostAddress, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 10000+10, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline LPWSTR ResolveName(LPWSTR lpszHostName) {
      void *param[1+1] = {(void*)lpszHostName, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPInfo_Do(m_pObj, 10000+11, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }

};

#endif //WIN32

#endif //_IPWORKS_IPINFO_H_




