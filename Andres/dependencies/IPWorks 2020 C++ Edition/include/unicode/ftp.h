/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_FTP_H_
#define _IPWORKS_FTP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

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

//TFTPTransferModes
#define TM_DEFAULT                                         0
#define TM_ASCII                                           1
#define TM_BINARY                                          2


extern "C" void* IPWORKS_CALL IPWorks_FTP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_FTP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_FTP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_FTP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_FTP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_FTP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_FTP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_FTP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_FTP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} FTPConnectionStatusEventParams;

typedef struct {
  LPCWSTR DirEntry;
  LPCWSTR FileName;
  BOOL IsDir;
  LONG64 FileSize;
  LPCWSTR FileTime;
  INT reserved;
} FTPDirListEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} FTPEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} FTPErrorEventParams;

typedef struct {
  INT Direction;
  LPCWSTR Message;
  INT reserved;
} FTPPITrailEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} FTPSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} FTPSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} FTPStartTransferEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  INT reserved;
} FTPTransferEventParams;


class FTP {
  public: // Events
    virtual INT FireConnectionStatus(FTPConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDirList(FTPDirListEventParams *e) {return 0;}
    virtual INT FireEndTransfer(FTPEndTransferEventParams *e) {return 0;}
    virtual INT FireError(FTPErrorEventParams *e) {return 0;}
    virtual INT FirePITrail(FTPPITrailEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(FTPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(FTPSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(FTPStartTransferEventParams *e) {return 0;}
    virtual INT FireTransfer(FTPTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL FTPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          FTPConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((FTP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          FTPDirListEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (BOOL)param[2], *(LONG64*)param[3], (LPWSTR)param[4], 0};
          ret_code = ((FTP*)lpObj)->FireDirList(&e);
          break;
        }
        case 3: {
          FTPEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((FTP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 4: {
          FTPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((FTP*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          FTPPITrailEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((FTP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 6: {
          FTPSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((FTP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 7: {
          FTPSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((FTP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 8: {
          FTPStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((FTP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 9: {
          FTPTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], 0};
          ret_code = ((FTP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    FTP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_17) {
      m_pObj = IPWorks_FTP_Create(FTPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~FTP() {
      IPWorks_FTP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_FTP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_FTP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_FTP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_FTP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_FTP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetAccount() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAccount(LPCWSTR lpszAccount) {
      return IPWorks_FTP_Set(m_pObj, 1+10000, 0, (LPVOID)lpszAccount, 0);
    }

    inline INT SetCommand(LPCWSTR lpszCommand) {
      return IPWorks_FTP_Set(m_pObj, 2+10000, 0, (LPVOID)lpszCommand, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 3, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_FTP_Set(m_pObj, 3, 0, val, 0);
    }

    inline INT GetDirListCount() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetDirListEntry(INT iEntryIndex) {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 5+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetDirListFileName(INT iEntryIndex) {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 6+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LONG64 GetDirListFileSize(INT iEntryIndex) {
      LONG64 retVal;
      IPWorks_FTP_Get(m_pObj, 7, iEntryIndex, NULL, &retVal);
      return retVal;
    }

    inline LPWSTR GetDirListFileTime(INT iEntryIndex) {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 8+10000, iEntryIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetDirListIsDir(INT iEntryIndex) {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 9, iEntryIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline BOOL GetFileExists() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 10, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LONG64 GetFileSize() {
      LONG64 retVal;
      IPWorks_FTP_Get(m_pObj, 11, 0, NULL, &retVal);
      return retVal;
    }

    inline LPWSTR GetFileTime() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 13, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_FTP_Set(m_pObj, 13, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 14, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_FTP_Set(m_pObj, 14, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_FTP_Set(m_pObj, 15+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_FTP_Set(m_pObj, 16+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 17, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_FTP_Set(m_pObj, 17, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_FTP_Set(m_pObj, 18+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 19, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLastReply() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_FTP_Set(m_pObj, 21+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 22+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_FTP_Set(m_pObj, 22+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline BOOL GetOverwrite() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 23, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetOverwrite(BOOL bOverwrite) {
      LPVOID val = (LPVOID)(bOverwrite);
      return IPWorks_FTP_Set(m_pObj, 23, 0, val, 0);
    }

    inline BOOL GetPassive() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 24, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetPassive(BOOL bPassive) {
      LPVOID val = (LPVOID)(bPassive);
      return IPWorks_FTP_Set(m_pObj, 24, 0, val, 0);
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_FTP_Set(m_pObj, 25+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline LPWSTR GetRemoteFile() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteFile(LPCWSTR lpszRemoteFile) {
      return IPWorks_FTP_Set(m_pObj, 26+10000, 0, (LPVOID)lpszRemoteFile, 0);
    }

    inline LPWSTR GetRemoteHost() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 27+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemoteHost(LPCWSTR lpszRemoteHost) {
      return IPWorks_FTP_Set(m_pObj, 27+10000, 0, (LPVOID)lpszRemoteHost, 0);
    }

    inline LPWSTR GetRemotePath() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 28+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRemotePath(LPCWSTR lpszRemotePath) {
      return IPWorks_FTP_Set(m_pObj, 28+10000, 0, (LPVOID)lpszRemotePath, 0);
    }

    inline INT GetRemotePort() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 29, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetRemotePort(INT iRemotePort) {
      LPVOID val = (LPVOID)(iRemotePort);
      return IPWorks_FTP_Set(m_pObj, 29, 0, val, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_FTP_Get(m_pObj, 30, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_FTP_Set(m_pObj, 30, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_FTP_Get(m_pObj, 31, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_FTP_Set(m_pObj, 31, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_FTP_Get(m_pObj, 32, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_FTP_Set(m_pObj, 32, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 33+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_FTP_Set(m_pObj, 33+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 34, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_FTP_Set(m_pObj, 34, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 35+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_FTP_Set(m_pObj, 35+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 36, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_FTP_Set(m_pObj, 36, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_FTP_Get(m_pObj, 37, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 38, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_FTP_Set(m_pObj, 38, 0, val, 0);
    }

    inline LPWSTR GetStartByte() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 39+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetStartByte(LPCWSTR lpszStartByte) {
      return IPWorks_FTP_Set(m_pObj, 39+10000, 0, (LPVOID)lpszStartByte, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 40, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_FTP_Set(m_pObj, 40, 0, val, 0);
    }

    inline INT GetTransferMode() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 41, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTransferMode(INT iTransferMode) {
      LPVOID val = (LPVOID)(iTransferMode);
      return IPWorks_FTP_Set(m_pObj, 41, 0, val, 0);
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_FTP_Get(m_pObj, 42+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_FTP_Set(m_pObj, 42+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline INT Abort() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 2+10000, 0, param, cbparam, NULL);
    }

    inline INT Append() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_FTP_Do(m_pObj, 4+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT DeleteFile(LPCWSTR lpszFileName) {
      LPVOID param[1+1] = {(LPVOID)lpszFileName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT Download() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT ListDirectory() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT ListDirectoryLong() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT Logoff() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 11+10000, 0, param, cbparam, NULL);
    }

    inline INT Logon() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
    }

    inline INT MakeDirectory(LPCWSTR lpszNewDir) {
      LPVOID param[1+1] = {(LPVOID)lpszNewDir, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 13+10000, 1, param, cbparam, NULL);
    }

    inline INT RemoveDirectory(LPCWSTR lpszDirName) {
      LPVOID param[1+1] = {(LPVOID)lpszDirName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
    }

    inline INT RenameFile(LPCWSTR lpszNewName) {
      LPVOID param[1+1] = {(LPVOID)lpszNewName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 15+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 16+10000, 0, param, cbparam, NULL);
    }

    inline INT SetDownloadStream(IPWorksStream* sDownloadStream) {
      LPVOID param[1+1] = {(LPVOID)sDownloadStream, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 17+10000, 1, param, cbparam, NULL);
    }

    inline INT SetUploadStream(IPWorksStream* sUploadStream) {
      LPVOID param[1+1] = {(LPVOID)sUploadStream, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 18+10000, 1, param, cbparam, NULL);
    }

    inline INT StoreUnique() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 19+10000, 0, param, cbparam, NULL);
    }

    inline INT Upload() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 20+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_FTP_H_
