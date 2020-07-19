/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_TFTP_H_
#define _IPWORKS_TFTP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_TFTP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_TFTP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_TFTP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_TFTP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  int Direction;
  int reserved;
} TFTPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} TFTPErrorEventParams;

typedef struct {
  int Direction;
  int reserved;
} TFTPStartTransferEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int reserved;
} TFTPTransferEventParams;


class TFTP {
  public: // Events
    virtual int FireEndTransfer(TFTPEndTransferEventParams *e) {return 0;}
    virtual int FireError(TFTPErrorEventParams *e) {return 0;}
    virtual int FireStartTransfer(TFTPStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(TFTPTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL TFTPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          TFTPEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((TFTP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 2: {
          TFTPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((TFTP*)lpObj)->FireError(&e);
          break;
        }
        case 3: {
          TFTPStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((TFTP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 4: {
          TFTPTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), 0};
          ret_code = ((TFTP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    TFTP(char *lpOemKey = (char*)IPWORKS_OEMKEY_46) {
      m_pObj = IPWorks_TFTP_Create(TFTPEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~TFTP() {
      IPWorks_TFTP_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_TFTP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_TFTP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_TFTP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_TFTP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_TFTP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetIdle() {
      void* val = IPWorks_TFTP_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_TFTP_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_TFTP_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_TFTP_Set(m_pObj, 2, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_TFTP_Set(m_pObj, 2+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_TFTP_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_TFTP_Set(m_pObj, 3, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetMaxRetransmits() {
      void* val = IPWorks_TFTP_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMaxRetransmits(int iMaxRetransmits) {
      void* val = (void*)IPW64CAST(iMaxRetransmits);
      return IPWorks_TFTP_Set(m_pObj, 4, 0, val, 0);
    }

    inline char* GetRemoteFile() {
      void* val = IPWorks_TFTP_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemoteFile(const char* lpszRemoteFile) {
      return IPWorks_TFTP_Set(m_pObj, 5, 0, (void*)lpszRemoteFile, 0);
    }

    inline int GetRetransmitTimeout() {
      void* val = IPWorks_TFTP_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRetransmitTimeout(int iRetransmitTimeout) {
      void* val = (void*)IPW64CAST(iRetransmitTimeout);
      return IPWorks_TFTP_Set(m_pObj, 6, 0, val, 0);
    }

    inline int GetTFTPPort() {
      void* val = IPWorks_TFTP_Get(m_pObj, 7, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTFTPPort(int iTFTPPort) {
      void* val = (void*)IPW64CAST(iTFTPPort);
      return IPWorks_TFTP_Set(m_pObj, 7, 0, val, 0);
    }

    inline char* GetTFTPServer() {
      void* val = IPWorks_TFTP_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTFTPServer(const char* lpszTFTPServer) {
      return IPWorks_TFTP_Set(m_pObj, 8, 0, (void*)lpszTFTPServer, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_TFTP_Get(m_pObj, 9, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_TFTP_Set(m_pObj, 9, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_TFTP_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int GetFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int PutFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_TFTP_H_
