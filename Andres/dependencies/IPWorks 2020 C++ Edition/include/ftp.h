/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_FTP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_FTP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_FTP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_FTP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_FTP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_FTP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_FTP_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} FTPConnectionStatusEventParams;

typedef struct {
  const char *DirEntry;
  const char *FileName;
  int IsDir;
  int64 FileSize;
  const char *FileTime;
  int reserved;
} FTPDirListEventParams;

typedef struct {
  int Direction;
  int reserved;
} FTPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} FTPErrorEventParams;

typedef struct {
  int Direction;
  const char *Message;
  int reserved;
} FTPPITrailEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} FTPSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} FTPSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} FTPStartTransferEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int reserved;
} FTPTransferEventParams;


class FTP {
  public: // Events
    virtual int FireConnectionStatus(FTPConnectionStatusEventParams *e) {return 0;}
    virtual int FireDirList(FTPDirListEventParams *e) {return 0;}
    virtual int FireEndTransfer(FTPEndTransferEventParams *e) {return 0;}
    virtual int FireError(FTPErrorEventParams *e) {return 0;}
    virtual int FirePITrail(FTPPITrailEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(FTPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(FTPSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(FTPStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(FTPTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL FTPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          FTPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((FTP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          FTPDirListEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), *(int64*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), 0};
          ret_code = ((FTP*)lpObj)->FireDirList(&e);
          break;
        }
        case 3: {
          FTPEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((FTP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 4: {
          FTPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((FTP*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          FTPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((FTP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 6: {
          FTPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((FTP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 7: {
          FTPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((FTP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 8: {
          FTPStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((FTP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 9: {
          FTPTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), 0};
          ret_code = ((FTP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    FTP(char *lpOemKey = (char*)IPWORKS_OEMKEY_17) {
      m_pObj = IPWorks_FTP_Create(FTPEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~FTP() {
      IPWorks_FTP_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_FTP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_FTP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_FTP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_FTP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_FTP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetAccount() {
      void* val = IPWorks_FTP_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAccount(const char* lpszAccount) {
      return IPWorks_FTP_Set(m_pObj, 1, 0, (void*)lpszAccount, 0);
    }

    inline int SetCommand(const char* lpszCommand) {
      return IPWorks_FTP_Set(m_pObj, 2, 0, (void*)lpszCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_FTP_Get(m_pObj, 3, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_FTP_Set(m_pObj, 3, 0, val, 0);
    }

    inline int GetDirListCount() {
      void* val = IPWorks_FTP_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetDirListEntry(int iEntryIndex) {
      void* val = IPWorks_FTP_Get(m_pObj, 5, iEntryIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetDirListFileName(int iEntryIndex) {
      void* val = IPWorks_FTP_Get(m_pObj, 6, iEntryIndex, NULL, NULL);
      return (char*)val;
    }

    inline int64 GetDirListFileSize(int iEntryIndex) {
      int64 retVal;
      IPWorks_FTP_Get(m_pObj, 7, iEntryIndex, NULL, &retVal);
      return retVal;
    }

    inline char* GetDirListFileTime(int iEntryIndex) {
      void* val = IPWorks_FTP_Get(m_pObj, 8, iEntryIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetDirListIsDir(int iEntryIndex) {
      void* val = IPWorks_FTP_Get(m_pObj, 9, iEntryIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetFileExists() {
      void* val = IPWorks_FTP_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int64 GetFileSize() {
      int64 retVal;
      IPWorks_FTP_Get(m_pObj, 11, 0, NULL, &retVal);
      return retVal;
    }

    inline char* GetFileTime() {
      void* val = IPWorks_FTP_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_FTP_Get(m_pObj, 13, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_FTP_Set(m_pObj, 13, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_FTP_Get(m_pObj, 14, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_FTP_Set(m_pObj, 14, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_FTP_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_FTP_Set(m_pObj, 15, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_FTP_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_FTP_Set(m_pObj, 16, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_FTP_Get(m_pObj, 17, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_FTP_Set(m_pObj, 17, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_FTP_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_FTP_Set(m_pObj, 18, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_FTP_Get(m_pObj, 19, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLastReply() {
      void* val = IPWorks_FTP_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_FTP_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_FTP_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_FTP_Set(m_pObj, 21, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_FTP_Set(m_pObj, 21+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_FTP_Get(m_pObj, 22, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_FTP_Set(m_pObj, 22, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetOverwrite() {
      void* val = IPWorks_FTP_Get(m_pObj, 23, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetOverwrite(int bOverwrite) {
      void* val = (void*)IPW64CAST(bOverwrite);
      return IPWorks_FTP_Set(m_pObj, 23, 0, val, 0);
    }

    inline int GetPassive() {
      void* val = IPWorks_FTP_Get(m_pObj, 24, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetPassive(int bPassive) {
      void* val = (void*)IPW64CAST(bPassive);
      return IPWorks_FTP_Set(m_pObj, 24, 0, val, 0);
    }

    inline char* GetPassword() {
      void* val = IPWorks_FTP_Get(m_pObj, 25, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_FTP_Set(m_pObj, 25, 0, (void*)lpszPassword, 0);
    }

    inline char* GetRemoteFile() {
      void* val = IPWorks_FTP_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemoteFile(const char* lpszRemoteFile) {
      return IPWorks_FTP_Set(m_pObj, 26, 0, (void*)lpszRemoteFile, 0);
    }

    inline char* GetRemoteHost() {
      void* val = IPWorks_FTP_Get(m_pObj, 27, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemoteHost(const char* lpszRemoteHost) {
      return IPWorks_FTP_Set(m_pObj, 27, 0, (void*)lpszRemoteHost, 0);
    }

    inline char* GetRemotePath() {
      void* val = IPWorks_FTP_Get(m_pObj, 28, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRemotePath(const char* lpszRemotePath) {
      return IPWorks_FTP_Set(m_pObj, 28, 0, (void*)lpszRemotePath, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_FTP_Get(m_pObj, 29, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetRemotePort(int iRemotePort) {
      void* val = (void*)IPW64CAST(iRemotePort);
      return IPWorks_FTP_Set(m_pObj, 29, 0, val, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_FTP_Get(m_pObj, 30, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_FTP_Set(m_pObj, 30, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_FTP_Get(m_pObj, 31, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_FTP_Set(m_pObj, 31, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_FTP_Get(m_pObj, 32, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_FTP_Set(m_pObj, 32, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_FTP_Get(m_pObj, 33, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_FTP_Set(m_pObj, 33, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_FTP_Get(m_pObj, 34, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_FTP_Set(m_pObj, 34, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_FTP_Get(m_pObj, 35, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_FTP_Set(m_pObj, 35, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_FTP_Get(m_pObj, 36, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_FTP_Set(m_pObj, 36, 0, val, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_FTP_Get(m_pObj, 37, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetSSLStartMode() {
      void* val = IPWorks_FTP_Get(m_pObj, 38, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_FTP_Set(m_pObj, 38, 0, val, 0);
    }

    inline char* GetStartByte() {
      void* val = IPWorks_FTP_Get(m_pObj, 39, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetStartByte(const char* lpszStartByte) {
      return IPWorks_FTP_Set(m_pObj, 39, 0, (void*)lpszStartByte, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_FTP_Get(m_pObj, 40, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_FTP_Set(m_pObj, 40, 0, val, 0);
    }

    inline int GetTransferMode() {
      void* val = IPWorks_FTP_Get(m_pObj, 41, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTransferMode(int iTransferMode) {
      void* val = (void*)IPW64CAST(iTransferMode);
      return IPWorks_FTP_Set(m_pObj, 41, 0, val, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_FTP_Get(m_pObj, 42, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_FTP_Set(m_pObj, 42, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline int Abort() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 2, 0, param, cbparam, NULL);
    }

    inline int Append() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_FTP_Do(m_pObj, 4, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DeleteFile(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 5, 1, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int Download() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline int ListDirectory() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int ListDirectoryLong() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int Logoff() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 11, 0, param, cbparam, NULL);
    }

    inline int Logon() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 12, 0, param, cbparam, NULL);
    }

    inline int MakeDirectory(const char* lpszNewDir) {
      void *param[1+1] = {(void*)IPW64CAST(lpszNewDir), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 13, 1, param, cbparam, NULL);
    }

    inline int RemoveDirectory(const char* lpszDirName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDirName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 14, 1, param, cbparam, NULL);
    }

    inline int RenameFile(const char* lpszNewName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszNewName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 15, 1, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 16, 0, param, cbparam, NULL);
    }

    inline int SetDownloadStream(IPWorksStream* sDownloadStream) {
      void *param[1+1] = {(void*)IPW64CAST(sDownloadStream), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 17, 1, param, cbparam, NULL);
    }

    inline int SetUploadStream(IPWorksStream* sUploadStream) {
      void *param[1+1] = {(void*)IPW64CAST(sUploadStream), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 18, 1, param, cbparam, NULL);
    }

    inline int StoreUnique() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 19, 0, param, cbparam, NULL);
    }

    inline int Upload() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 20, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_FTP_H_
