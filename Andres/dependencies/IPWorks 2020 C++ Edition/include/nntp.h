/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_NNTP_H_
#define _IPWORKS_NNTP_H_

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


extern "C" void* IPWORKS_CALL IPWorks_NNTP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NNTP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_NNTP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_NNTP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_StaticDestroy();

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
} NNTPConnectionStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} NNTPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} NNTPErrorEventParams;

typedef struct {
  const char *Group;
  int64 FirstArticle;
  int64 LastArticle;
  int CanPost;
  int reserved;
} NNTPGroupListEventParams;

typedef struct {
  int64 ArticleNumber;
  const char *Subject;
  const char *From;
  const char *ArticleDate;
  const char *MessageId;
  const char *References;
  int64 ArticleSize;
  int64 ArticleLines;
  const char *OtherHeaders;
  int reserved;
} NNTPGroupOverviewEventParams;

typedef struct {
  int64 ArticleNumber;
  const char *Header;
  int reserved;
} NNTPGroupSearchEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} NNTPHeaderEventParams;

typedef struct {
  int Direction;
  const char *Message;
  int reserved;
} NNTPPITrailEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} NNTPSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} NNTPSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} NNTPStartTransferEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int EOL;
  int reserved;
} NNTPTransferEventParams;


class NNTP {
  public: // Events
    virtual int FireConnectionStatus(NNTPConnectionStatusEventParams *e) {return 0;}
    virtual int FireEndTransfer(NNTPEndTransferEventParams *e) {return 0;}
    virtual int FireError(NNTPErrorEventParams *e) {return 0;}
    virtual int FireGroupList(NNTPGroupListEventParams *e) {return 0;}
    virtual int FireGroupOverview(NNTPGroupOverviewEventParams *e) {return 0;}
    virtual int FireGroupSearch(NNTPGroupSearchEventParams *e) {return 0;}
    virtual int FireHeader(NNTPHeaderEventParams *e) {return 0;}
    virtual int FirePITrail(NNTPPITrailEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(NNTPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(NNTPSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(NNTPStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(NNTPTransferEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL NNTPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          NNTPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((NNTP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          NNTPEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((NNTP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 3: {
          NNTPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((NNTP*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          NNTPGroupListEventParams e = {(char*)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), *(int64*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), 0};
          ret_code = ((NNTP*)lpObj)->FireGroupList(&e);
          break;
        }
        case 5: {
          NNTPGroupOverviewEventParams e = {*(int64*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), *(int64*)IPW64CAST(param[6]), *(int64*)IPW64CAST(param[7]), (char*)IPW64CAST(param[8]), 0};
          ret_code = ((NNTP*)lpObj)->FireGroupOverview(&e);
          break;
        }
        case 6: {
          NNTPGroupSearchEventParams e = {*(int64*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((NNTP*)lpObj)->FireGroupSearch(&e);
          break;
        }
        case 7: {
          NNTPHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((NNTP*)lpObj)->FireHeader(&e);
          break;
        }
        case 8: {
          NNTPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((NNTP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 9: {
          NNTPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((NNTP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 10: {
          NNTPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((NNTP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 11: {
          NNTPStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((NNTP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 12: {
          NNTPTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((NNTP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    NNTP(char *lpOemKey = (char*)IPWORKS_OEMKEY_25) {
      m_pObj = IPWorks_NNTP_Create(NNTPEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~NNTP() {
      IPWorks_NNTP_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_NNTP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_NNTP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_NNTP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_NNTP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_NNTP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int64 GetArticleCount() {
      int64 retVal;
      IPWorks_NNTP_Get(m_pObj, 1, 0, NULL, &retVal);
      return retVal;
    }

    inline char* GetArticleDate() {
      void* val = IPWorks_NNTP_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetArticleFrom() {
      void* val = IPWorks_NNTP_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetArticleFrom(const char* lpszArticleFrom) {
      return IPWorks_NNTP_Set(m_pObj, 3, 0, (void*)lpszArticleFrom, 0);
    }

    inline char* GetArticleHeaders() {
      void* val = IPWorks_NNTP_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetArticleId() {
      void* val = IPWorks_NNTP_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetGroupOverviewCount() {
      void* val = IPWorks_NNTP_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int64 GetGroupOverviewArticleLines(int iGroupOverviewIndex) {
      int64 retVal;
      IPWorks_NNTP_Get(m_pObj, 7, iGroupOverviewIndex, NULL, &retVal);
      return retVal;
    }

    inline int64 GetGroupOverviewArticleNumber(int iGroupOverviewIndex) {
      int64 retVal;
      IPWorks_NNTP_Get(m_pObj, 8, iGroupOverviewIndex, NULL, &retVal);
      return retVal;
    }

    inline int64 GetGroupOverviewArticleSize(int iGroupOverviewIndex) {
      int64 retVal;
      IPWorks_NNTP_Get(m_pObj, 9, iGroupOverviewIndex, NULL, &retVal);
      return retVal;
    }

    inline char* GetGroupOverviewDate(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 10, iGroupOverviewIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetGroupOverviewFrom(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 11, iGroupOverviewIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetGroupOverviewMessageId(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 12, iGroupOverviewIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetGroupOverviewOtherHeaders(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 13, iGroupOverviewIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetGroupOverviewReferences(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 14, iGroupOverviewIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetGroupOverviewSubject(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 15, iGroupOverviewIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetArticleReferences() {
      void* val = IPWorks_NNTP_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetArticleReferences(const char* lpszArticleReferences) {
      return IPWorks_NNTP_Set(m_pObj, 16, 0, (void*)lpszArticleReferences, 0);
    }

    inline char* GetArticleReplyTo() {
      void* val = IPWorks_NNTP_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetArticleReplyTo(const char* lpszArticleReplyTo) {
      return IPWorks_NNTP_Set(m_pObj, 17, 0, (void*)lpszArticleReplyTo, 0);
    }

    inline char* GetArticleSubject() {
      void* val = IPWorks_NNTP_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetArticleSubject(const char* lpszArticleSubject) {
      return IPWorks_NNTP_Set(m_pObj, 18, 0, (void*)lpszArticleSubject, 0);
    }

    inline char* GetArticleText() {
      void* val = IPWorks_NNTP_Get(m_pObj, 19, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetArticleText(const char* lpszArticleText) {
      return IPWorks_NNTP_Set(m_pObj, 19, 0, (void*)lpszArticleText, 0);
    }

    inline char* GetAttachedFile() {
      void* val = IPWorks_NNTP_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAttachedFile(const char* lpszAttachedFile) {
      return IPWorks_NNTP_Set(m_pObj, 20, 0, (void*)lpszAttachedFile, 0);
    }

    inline char* GetCheckDate() {
      void* val = IPWorks_NNTP_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCheckDate(const char* lpszCheckDate) {
      return IPWorks_NNTP_Set(m_pObj, 21, 0, (void*)lpszCheckDate, 0);
    }

    inline int SetCommand(const char* lpszCommand) {
      return IPWorks_NNTP_Set(m_pObj, 22, 0, (void*)lpszCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_NNTP_Get(m_pObj, 23, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_NNTP_Set(m_pObj, 23, 0, val, 0);
    }

    inline char* GetCurrentArticle() {
      void* val = IPWorks_NNTP_Get(m_pObj, 24, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCurrentArticle(const char* lpszCurrentArticle) {
      return IPWorks_NNTP_Set(m_pObj, 24, 0, (void*)lpszCurrentArticle, 0);
    }

    inline char* GetCurrentGroup() {
      void* val = IPWorks_NNTP_Get(m_pObj, 25, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCurrentGroup(const char* lpszCurrentGroup) {
      return IPWorks_NNTP_Set(m_pObj, 25, 0, (void*)lpszCurrentGroup, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_NNTP_Get(m_pObj, 26, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_NNTP_Set(m_pObj, 26, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_NNTP_Get(m_pObj, 27, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_NNTP_Set(m_pObj, 27, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_NNTP_Get(m_pObj, 28, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_NNTP_Set(m_pObj, 28, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_NNTP_Get(m_pObj, 29, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_NNTP_Set(m_pObj, 29, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_NNTP_Get(m_pObj, 30, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_NNTP_Set(m_pObj, 30, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_NNTP_Get(m_pObj, 31, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_NNTP_Set(m_pObj, 31, 0, (void*)lpszFirewallUser, 0);
    }

    inline int64 GetFirstArticle() {
      int64 retVal;
      IPWorks_NNTP_Get(m_pObj, 32, 0, NULL, &retVal);
      return retVal;
    }

    inline int GetGroupListCount() {
      void* val = IPWorks_NNTP_Get(m_pObj, 33, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetGroupListCanPost(int iGroupListIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 34, iGroupListIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline int64 GetGroupListFirstArticle(int iGroupListIndex) {
      int64 retVal;
      IPWorks_NNTP_Get(m_pObj, 35, iGroupListIndex, NULL, &retVal);
      return retVal;
    }

    inline char* GetGroupListGroup(int iGroupListIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 36, iGroupListIndex, NULL, NULL);
      return (char*)val;
    }

    inline int64 GetGroupListLastArticle(int iGroupListIndex) {
      int64 retVal;
      IPWorks_NNTP_Get(m_pObj, 37, iGroupListIndex, NULL, &retVal);
      return retVal;
    }

    inline int GetIdle() {
      void* val = IPWorks_NNTP_Get(m_pObj, 38, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int64 GetLastArticle() {
      int64 retVal;
      IPWorks_NNTP_Get(m_pObj, 39, 0, NULL, &retVal);
      return retVal;
    }

    inline char* GetLastReply() {
      void* val = IPWorks_NNTP_Get(m_pObj, 40, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_NNTP_Get(m_pObj, 41, 0, NULL, NULL);
      return (char*)val;
    }
#ifdef WIN32
    inline wchar_t* GetLocalFile_W() {
      void* val = IPWorks_NNTP_Get(m_pObj, 41+10000, 0, NULL, NULL);
      return (wchar_t*)val;
    }
#endif // WIN32
    inline int SetLocalFile(const char* lpszLocalFile) {
      return IPWorks_NNTP_Set(m_pObj, 41, 0, (void*)lpszLocalFile, 0);
    }
#ifdef WIN32
    inline int SetLocalFile(const wchar_t* lpszLocalFile) {
      return IPWorks_NNTP_Set(m_pObj, 41+10000, 0, (void*)lpszLocalFile, 0);
    }
#endif // WIN32

    inline char* GetLocalHost() {
      void* val = IPWorks_NNTP_Get(m_pObj, 42, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_NNTP_Set(m_pObj, 42, 0, (void*)lpszLocalHost, 0);
    }

    inline int64 GetMaxLines() {
      int64 retVal;
      IPWorks_NNTP_Get(m_pObj, 43, 0, NULL, &retVal);
      return retVal;
    }
    inline int SetMaxLines(int64 lMaxLines) {
      void* val = (void*)(&lMaxLines);
      return IPWorks_NNTP_Set(m_pObj, 43, 0, val, 0);
    }

    inline char* GetNewsgroups() {
      void* val = IPWorks_NNTP_Get(m_pObj, 44, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetNewsgroups(const char* lpszNewsgroups) {
      return IPWorks_NNTP_Set(m_pObj, 44, 0, (void*)lpszNewsgroups, 0);
    }

    inline int GetNewsPort() {
      void* val = IPWorks_NNTP_Get(m_pObj, 45, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetNewsPort(int iNewsPort) {
      void* val = (void*)IPW64CAST(iNewsPort);
      return IPWorks_NNTP_Set(m_pObj, 45, 0, val, 0);
    }

    inline char* GetNewsServer() {
      void* val = IPWorks_NNTP_Get(m_pObj, 46, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetNewsServer(const char* lpszNewsServer) {
      return IPWorks_NNTP_Set(m_pObj, 46, 0, (void*)lpszNewsServer, 0);
    }

    inline char* GetOrganization() {
      void* val = IPWorks_NNTP_Get(m_pObj, 47, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOrganization(const char* lpszOrganization) {
      return IPWorks_NNTP_Set(m_pObj, 47, 0, (void*)lpszOrganization, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_NNTP_Get(m_pObj, 48, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherHeaders(const char* lpszOtherHeaders) {
      return IPWorks_NNTP_Set(m_pObj, 48, 0, (void*)lpszOtherHeaders, 0);
    }

    inline char* GetOverviewRange() {
      void* val = IPWorks_NNTP_Get(m_pObj, 49, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOverviewRange(const char* lpszOverviewRange) {
      return IPWorks_NNTP_Set(m_pObj, 49, 0, (void*)lpszOverviewRange, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_NNTP_Get(m_pObj, 50, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 51, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 52, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_NNTP_Get(m_pObj, 53, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_NNTP_Set(m_pObj, 53, 0, (void*)lpszPassword, 0);
    }

    inline char* GetSearchHeader() {
      void* val = IPWorks_NNTP_Get(m_pObj, 54, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSearchHeader(const char* lpszSearchHeader) {
      return IPWorks_NNTP_Set(m_pObj, 54, 0, (void*)lpszSearchHeader, 0);
    }

    inline char* GetSearchPattern() {
      void* val = IPWorks_NNTP_Get(m_pObj, 55, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSearchPattern(const char* lpszSearchPattern) {
      return IPWorks_NNTP_Set(m_pObj, 55, 0, (void*)lpszSearchPattern, 0);
    }

    inline char* GetSearchRange() {
      void* val = IPWorks_NNTP_Get(m_pObj, 56, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSearchRange(const char* lpszSearchRange) {
      return IPWorks_NNTP_Set(m_pObj, 56, 0, (void*)lpszSearchRange, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_NNTP_Get(m_pObj, 57, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_NNTP_Set(m_pObj, 57, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_NNTP_Get(m_pObj, 58, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_NNTP_Set(m_pObj, 58, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_NNTP_Get(m_pObj, 59, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_NNTP_Set(m_pObj, 59, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_NNTP_Get(m_pObj, 60, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_NNTP_Set(m_pObj, 60, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_NNTP_Get(m_pObj, 61, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_NNTP_Set(m_pObj, 61, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_NNTP_Get(m_pObj, 62, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_NNTP_Set(m_pObj, 62, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_NNTP_Get(m_pObj, 63, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_NNTP_Set(m_pObj, 63, 0, val, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_NNTP_Get(m_pObj, 64, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetSSLStartMode() {
      void* val = IPWorks_NNTP_Get(m_pObj, 65, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_NNTP_Set(m_pObj, 65, 0, val, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_NNTP_Get(m_pObj, 66, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_NNTP_Set(m_pObj, 66, 0, val, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_NNTP_Get(m_pObj, 67, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_NNTP_Set(m_pObj, 67, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NNTP_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int FetchArticle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int FetchArticleBody() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline int FetchArticleHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline int GroupOverview() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int GroupSearch() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 11, 0, param, cbparam, NULL);
    }

    inline int ListGroups() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 12, 0, param, cbparam, NULL);
    }

    inline int ListNewGroups() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 13, 0, param, cbparam, NULL);
    }

    inline char* LocalizeDate(const char* lpszDateTime) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDateTime), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NNTP_Do(m_pObj, 14, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int PostArticle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 15, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 16, 0, param, cbparam, NULL);
    }

    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 17, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_NNTP_H_
