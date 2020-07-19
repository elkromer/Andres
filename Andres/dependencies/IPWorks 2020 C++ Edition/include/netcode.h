/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

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
#define FMT_PUNYCODE                                       16


extern "C" void* IPWORKS_CALL IPWorks_NetCode_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NetCode_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_NetCode_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_NetCode_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NetCode_SetEventErrorAndCode(void *lpObj, int code, char *message);
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
  const char *Description;
  int reserved;
} NetCodeErrorEventParams;

typedef struct {
  int PercentDone;
  int reserved;
} NetCodeProgressEventParams;


class NetCode {
  public: // Events
    virtual int FireError(NetCodeErrorEventParams *e) {return 0;}
    virtual int FireProgress(NetCodeProgressEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL NetCodeEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          NetCodeErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((NetCode*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          NetCodeProgressEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((NetCode*)lpObj)->FireProgress(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    NetCode(char *lpOemKey = (char*)IPWORKS_OEMKEY_14) {
      m_pObj = IPWorks_NetCode_Create(NetCodeEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~NetCode() {
      IPWorks_NetCode_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_NetCode_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_NetCode_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_NetCode_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_NetCode_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_NetCode_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetDecodedData(char* &lpDecodedData, int &lenDecodedData) {
      lpDecodedData = (char*)IPWorks_NetCode_Get(m_pObj, 1, 0, &lenDecodedData, NULL);
      return lpDecodedData ? 0 : lenDecodedData;
    }
    inline int SetDecodedData(const char* lpDecodedData, int lenDecodedData) {
      return IPWorks_NetCode_Set(m_pObj, 1, 0, (void*)lpDecodedData, lenDecodedData);
    }

    inline char* GetDecodedFile() {
      void* val = IPWorks_NetCode_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetDecodedFile(const char* lpszDecodedFile) {
      return IPWorks_NetCode_Set(m_pObj, 2, 0, (void*)lpszDecodedFile, 0);
    }

    inline int GetEncodedData(char* &lpEncodedData, int &lenEncodedData) {
      lpEncodedData = (char*)IPWorks_NetCode_Get(m_pObj, 3, 0, &lenEncodedData, NULL);
      return lpEncodedData ? 0 : lenEncodedData;
    }
    inline int SetEncodedData(const char* lpEncodedData, int lenEncodedData) {
      return IPWorks_NetCode_Set(m_pObj, 3, 0, (void*)lpEncodedData, lenEncodedData);
    }

    inline char* GetEncodedFile() {
      void* val = IPWorks_NetCode_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEncodedFile(const char* lpszEncodedFile) {
      return IPWorks_NetCode_Set(m_pObj, 4, 0, (void*)lpszEncodedFile, 0);
    }

    inline int GetFileCnt() {
      void* val = IPWorks_NetCode_Get(m_pObj, 5, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetFileName() {
      void* val = IPWorks_NetCode_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFileName(const char* lpszFileName) {
      return IPWorks_NetCode_Set(m_pObj, 6, 0, (void*)lpszFileName, 0);
    }

    inline int GetFormat() {
      void* val = IPWorks_NetCode_Get(m_pObj, 7, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFormat(int iFormat) {
      void* val = (void*)IPW64CAST(iFormat);
      return IPWorks_NetCode_Set(m_pObj, 7, 0, val, 0);
    }

    inline char* GetMode() {
      void* val = IPWorks_NetCode_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMode(const char* lpszMode) {
      return IPWorks_NetCode_Set(m_pObj, 8, 0, (void*)lpszMode, 0);
    }

    inline int GetOverwrite() {
      void* val = IPWorks_NetCode_Get(m_pObj, 9, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetOverwrite(int bOverwrite) {
      void* val = (void*)IPW64CAST(bOverwrite);
      return IPWorks_NetCode_Set(m_pObj, 9, 0, val, 0);
    }

    inline int GetProgressStep() {
      void* val = IPWorks_NetCode_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProgressStep(int iProgressStep) {
      void* val = (void*)IPW64CAST(iProgressStep);
      return IPWorks_NetCode_Set(m_pObj, 10, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NetCode_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Decode() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int Encode() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int ResetData() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NetCode_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_NETCODE_H_
