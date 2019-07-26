/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_NETCODE_H_
#define _IPWORKS_NETCODE_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//TFmt
#define FMT_UUENCODE                                       0
#define FMT_BASE_64                                        1
#define FMT_QP                                             2
#define FMT_URL                                            3
#define FMT_JIS                                            4
#define FMT_YENCODE                                        5
#define FMT_MD5HASH                                        6
#define FMT_SHA1HASH                                       7
#define FMT_HEX                                            8
#define FMT_HTML                                           9
#define FMT_HMAC                                           10
#define FMT_UTF8                                           11
#define FMT_UTF7                                           12
#define FMT_BASE_32                                        13
#define FMT_BASE_64URL                                     14
#define FMT_SHA256HASH                                     15


extern "C" void* IPWORKS_CALL IPWorks_NetCode_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NetCode_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_NetCode_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_StaticDestroy();

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
} NetCodeErrorEventParams;

typedef struct {
  int PercentDone;
  int reserved;
} NetCodeProgressEventParams;



class NetCode {
  
  public: //events
  
    virtual int FireError(NetCodeErrorEventParams *e) {return 0;}
    virtual int FireProgress(NetCodeProgressEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL NetCodeEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((NetCode*)lpObj)->NetCodeEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            NetCodeErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((NetCode*)lpObj)->FireError(&e);
            break;
         }
         case 2: {
            NetCodeProgressEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((NetCode*)lpObj)->FireProgress(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int NetCodeEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    NetCode(char *lpOemKey = (char*)IPWORKS_OEMKEY_14) {
      m_pObj = IPWorks_NetCode_Create(NetCodeEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~NetCode() {
      IPWorks_NetCode_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_NetCode_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_NetCode_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_NetCode_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_NetCode_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_NetCode_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetDecodedData(char *&lpDecodedData, int &lenDecodedData) {
      lpDecodedData = (char*)IPWorks_NetCode_Get(m_pObj, 1, 0, &lenDecodedData);
      return lpDecodedData ? 0 : lenDecodedData;
    }

    inline int SetDecodedData(const char *lpDecodedData, int lenDecodedData) {
      return IPWorks_NetCode_Set(m_pObj, 1, 0, (void*)lpDecodedData, lenDecodedData);
    }

    inline char* GetDecodedFile() {
      void* val = IPWorks_NetCode_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetDecodedFile(const char *lpDecodedFile) {
      return IPWorks_NetCode_Set(m_pObj, 2, 0, (void*)lpDecodedFile, 0);
    }

    inline int GetEncodedData(char *&lpEncodedData, int &lenEncodedData) {
      lpEncodedData = (char*)IPWorks_NetCode_Get(m_pObj, 3, 0, &lenEncodedData);
      return lpEncodedData ? 0 : lenEncodedData;
    }

    inline int SetEncodedData(const char *lpEncodedData, int lenEncodedData) {
      return IPWorks_NetCode_Set(m_pObj, 3, 0, (void*)lpEncodedData, lenEncodedData);
    }

    inline char* GetEncodedFile() {
      void* val = IPWorks_NetCode_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetEncodedFile(const char *lpEncodedFile) {
      return IPWorks_NetCode_Set(m_pObj, 4, 0, (void*)lpEncodedFile, 0);
    }

    inline int GetFileCnt() {
      void* val = IPWorks_NetCode_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }

    inline char* GetFileName() {
      void* val = IPWorks_NetCode_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetFileName(const char *lpFileName) {
      return IPWorks_NetCode_Set(m_pObj, 6, 0, (void*)lpFileName, 0);
    }

    inline int GetFormat() {
      void* val = IPWorks_NetCode_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetFormat(int iFormat) {
      void* val = (void*)IPW64CAST(iFormat);
      return IPWorks_NetCode_Set(m_pObj, 7, 0, val, 0);
    }
    inline char* GetMode() {
      void* val = IPWorks_NetCode_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetMode(const char *lpMode) {
      return IPWorks_NetCode_Set(m_pObj, 8, 0, (void*)lpMode, 0);
    }

    inline int GetOverwrite() {
      void* val = IPWorks_NetCode_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetOverwrite(int bOverwrite) {
      void* val = (void*)IPW64CAST(bOverwrite);
      return IPWorks_NetCode_Set(m_pObj, 9, 0, val, 0);
    }
    inline int GetProgressStep() {
      void* val = IPWorks_NetCode_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }
    inline int SetProgressStep(int iProgressStep) {
      void* val = (void*)IPW64CAST(iProgressStep);
      return IPWorks_NetCode_Set(m_pObj, 10, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NetCode_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Decode() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Encode() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int ResetData() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} NetCodeErrorEventParamsW;

typedef struct {
  int PercentDone;
  int reserved;
} NetCodeProgressEventParamsW;



class NetCodeW : public NetCode {

  public: //properties
  
    inline LPWSTR GetDecodedData() {
      return (LPWSTR)IPWorks_NetCode_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetDecodedData(LPCWSTR lpDecodedData) {
      return IPWorks_NetCode_Set(m_pObj, 10000+1, 0, (void*)lpDecodedData, 0);
    }
    inline int GetDecodedDataB(char *&lpDecodedData, int &lenDecodedData) {
      lpDecodedData = (char*)IPWorks_NetCode_Get(m_pObj, 1, 0, &lenDecodedData);
      return lpDecodedData ? 0 : lenDecodedData;
    }
    inline int SetDecodedDataB(const char *lpDecodedData, int lenDecodedData) {
      return IPWorks_NetCode_Set(m_pObj, 1, 0, (void*)lpDecodedData, lenDecodedData);
    }
    inline LPWSTR GetDecodedFile() {
      return (LPWSTR)IPWorks_NetCode_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetDecodedFile(LPCWSTR lpDecodedFile) {
      return IPWorks_NetCode_Set(m_pObj, 10000+2, 0, (void*)lpDecodedFile, 0);
    }

    inline LPWSTR GetEncodedData() {
      return (LPWSTR)IPWorks_NetCode_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetEncodedData(LPCWSTR lpEncodedData) {
      return IPWorks_NetCode_Set(m_pObj, 10000+3, 0, (void*)lpEncodedData, 0);
    }
    inline int GetEncodedDataB(char *&lpEncodedData, int &lenEncodedData) {
      lpEncodedData = (char*)IPWorks_NetCode_Get(m_pObj, 3, 0, &lenEncodedData);
      return lpEncodedData ? 0 : lenEncodedData;
    }
    inline int SetEncodedDataB(const char *lpEncodedData, int lenEncodedData) {
      return IPWorks_NetCode_Set(m_pObj, 3, 0, (void*)lpEncodedData, lenEncodedData);
    }
    inline LPWSTR GetEncodedFile() {
      return (LPWSTR)IPWorks_NetCode_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetEncodedFile(LPCWSTR lpEncodedFile) {
      return IPWorks_NetCode_Set(m_pObj, 10000+4, 0, (void*)lpEncodedFile, 0);
    }



    inline LPWSTR GetFileName() {
      return (LPWSTR)IPWorks_NetCode_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetFileName(LPCWSTR lpFileName) {
      return IPWorks_NetCode_Set(m_pObj, 10000+6, 0, (void*)lpFileName, 0);
    }



    inline LPWSTR GetMode() {
      return (LPWSTR)IPWorks_NetCode_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetMode(LPCWSTR lpMode) {
      return IPWorks_NetCode_Set(m_pObj, 10000+8, 0, (void*)lpMode, 0);
    }







  public: //events
  
    virtual int FireError(NetCodeErrorEventParamsW *e) {return 0;}
    virtual int FireProgress(NetCodeProgressEventParamsW *e) {return 0;}


  protected:
  
    virtual int NetCodeEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            NetCodeErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 2: {
            NetCodeProgressEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireProgress(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireError(NetCodeErrorEventParams *e) {return -10000;}
    virtual int FireProgress(NetCodeProgressEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NetCode_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Decode() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Encode() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int ResetData() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_NETCODE_H_




