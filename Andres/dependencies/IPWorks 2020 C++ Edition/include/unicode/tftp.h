/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
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
extern "C" void* IPWORKS_CALL IPWorks_TFTP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_TFTP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_TFTP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT Direction;
  INT reserved;
} TFTPEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} TFTPErrorEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} TFTPStartTransferEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  INT reserved;
} TFTPTransferEventParams;


class TFTP {
  public: // Events
    virtual INT FireEndTransfer(TFTPEndTransferEventParams *e) {return 0;}
    virtual INT FireError(TFTPErrorEventParams *e) {return 0;}
    virtual INT FireStartTransfer(TFTPStartTransferEventParams *e) {return 0;}
    virtual INT FireTransfer(TFTPTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL TFTPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          TFTPEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((TFTP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 2: {
          TFTPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((TFTP*)lpObj)->FireError(&e);
          break;
        }
        case 3: {
          TFTPStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((TFTP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 4: {
          TFTPTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], 0};
          ret_code = ((TFTP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    TFTP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_46) {
      m_pObj = IPWorks_TFTP_Create(TFTPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~TFTP() {
      IPWorks_TFTP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_TFTP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_TFTP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_TFTP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_TFTP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_TFTP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetIdle() {
      LPVOID val = IPWorks_TFTP_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_TFTP_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_TFTP_Set(m_pObj, 2+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_TFTP_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_TFTP_Set(m_pObj, 3+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetMaxRetransmits() {
      LPVOID val = IPWorks_TFTP_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMaxRetransmits(INT iMaxRetransmits) {
      LPVOID val = (LPVOID)(iMaxRetransmits);
      return IPWorks_TFTP_Set(m_pObj, 4, 0, val, 0);
    }

    inline LPWSTR GetRemoteFile() {
      LPVOID val = IPWorks_TFTP_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteFile(LPCWSTR lpszRemoteFile) {
      return IPWorks_TFTP_Set(m_pObj, 5+10000, 0, (LPVOID)lpszRemoteFile, 0);
    }

    inline INT GetRetransmitTimeout() {
      LPVOID val = IPWorks_TFTP_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRetransmitTimeout(INT iRetransmitTimeout) {
      LPVOID val = (LPVOID)(iRetransmitTimeout);
      return IPWorks_TFTP_Set(m_pObj, 6, 0, val, 0);
    }

    inline INT GetTFTPPort() {
      LPVOID val = IPWorks_TFTP_Get(m_pObj, 7, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTFTPPort(INT iTFTPPort) {
      LPVOID val = (LPVOID)(iTFTPPort);
      return IPWorks_TFTP_Set(m_pObj, 7, 0, val, 0);
    }

    inline LPWSTR GetTFTPServer() {
      LPVOID val = IPWorks_TFTP_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTFTPServer(LPCWSTR lpszTFTPServer) {
      return IPWorks_TFTP_Set(m_pObj, 8+10000, 0, (LPVOID)lpszTFTPServer, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_TFTP_Get(m_pObj, 9, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_TFTP_Set(m_pObj, 9, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_TFTP_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT GetFile() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT PutFile() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_TFTP_H_
