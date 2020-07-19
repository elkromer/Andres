/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
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
extern "C" void* IPWORKS_CALL IPWorks_NNTP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_NNTP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_NNTP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} NNTPConnectionStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} NNTPEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} NNTPErrorEventParams;

typedef struct {
  LPCWSTR Group;
  LONG64 FirstArticle;
  LONG64 LastArticle;
  BOOL CanPost;
  INT reserved;
} NNTPGroupListEventParams;

typedef struct {
  LONG64 ArticleNumber;
  LPCWSTR Subject;
  LPCWSTR From;
  LPCWSTR ArticleDate;
  LPCWSTR MessageId;
  LPCWSTR References;
  LONG64 ArticleSize;
  LONG64 ArticleLines;
  LPCWSTR OtherHeaders;
  INT reserved;
} NNTPGroupOverviewEventParams;

typedef struct {
  LONG64 ArticleNumber;
  LPCWSTR Header;
  INT reserved;
} NNTPGroupSearchEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} NNTPHeaderEventParams;

typedef struct {
  INT Direction;
  LPCWSTR Message;
  INT reserved;
} NNTPPITrailEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} NNTPSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} NNTPSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} NNTPStartTransferEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  BOOL EOL;
  INT reserved;
} NNTPTransferEventParams;


class NNTP {
  public: // Events
    virtual INT FireConnectionStatus(NNTPConnectionStatusEventParams *e) {return 0;}
    virtual INT FireEndTransfer(NNTPEndTransferEventParams *e) {return 0;}
    virtual INT FireError(NNTPErrorEventParams *e) {return 0;}
    virtual INT FireGroupList(NNTPGroupListEventParams *e) {return 0;}
    virtual INT FireGroupOverview(NNTPGroupOverviewEventParams *e) {return 0;}
    virtual INT FireGroupSearch(NNTPGroupSearchEventParams *e) {return 0;}
    virtual INT FireHeader(NNTPHeaderEventParams *e) {return 0;}
    virtual INT FirePITrail(NNTPPITrailEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(NNTPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(NNTPSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(NNTPStartTransferEventParams *e) {return 0;}
    virtual INT FireTransfer(NNTPTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL NNTPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          NNTPConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((NNTP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 2: {
          NNTPEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((NNTP*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 3: {
          NNTPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((NNTP*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          NNTPGroupListEventParams e = {(LPWSTR)param[0], *(LONG64*)param[1], *(LONG64*)param[2], (BOOL)param[3], 0};
          ret_code = ((NNTP*)lpObj)->FireGroupList(&e);
          break;
        }
        case 5: {
          NNTPGroupOverviewEventParams e = {*(LONG64*)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (LPWSTR)param[5], *(LONG64*)param[6], *(LONG64*)param[7], (LPWSTR)param[8], 0};
          ret_code = ((NNTP*)lpObj)->FireGroupOverview(&e);
          break;
        }
        case 6: {
          NNTPGroupSearchEventParams e = {*(LONG64*)param[0], (LPWSTR)param[1], 0};
          ret_code = ((NNTP*)lpObj)->FireGroupSearch(&e);
          break;
        }
        case 7: {
          NNTPHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((NNTP*)lpObj)->FireHeader(&e);
          break;
        }
        case 8: {
          NNTPPITrailEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((NNTP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 9: {
          NNTPSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((NNTP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 10: {
          NNTPSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((NNTP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 11: {
          NNTPStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((NNTP*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 12: {
          NNTPTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], (BOOL)param[4], 0};
          ret_code = ((NNTP*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    NNTP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_25) {
      m_pObj = IPWorks_NNTP_Create(NNTPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~NNTP() {
      IPWorks_NNTP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_NNTP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_NNTP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_NNTP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_NNTP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_NNTP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LONG64 GetArticleCount() {
      LONG64 retVal;
      IPWorks_NNTP_Get(m_pObj, 1, 0, NULL, &retVal);
      return retVal;
    }

    inline LPWSTR GetArticleDate() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetArticleFrom() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetArticleFrom(LPCWSTR lpszArticleFrom) {
      return IPWorks_NNTP_Set(m_pObj, 3+10000, 0, (LPVOID)lpszArticleFrom, 0);
    }

    inline LPWSTR GetArticleHeaders() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetArticleId() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetGroupOverviewCount() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LONG64 GetGroupOverviewArticleLines(INT iGroupOverviewIndex) {
      LONG64 retVal;
      IPWorks_NNTP_Get(m_pObj, 7, iGroupOverviewIndex, NULL, &retVal);
      return retVal;
    }

    inline LONG64 GetGroupOverviewArticleNumber(INT iGroupOverviewIndex) {
      LONG64 retVal;
      IPWorks_NNTP_Get(m_pObj, 8, iGroupOverviewIndex, NULL, &retVal);
      return retVal;
    }

    inline LONG64 GetGroupOverviewArticleSize(INT iGroupOverviewIndex) {
      LONG64 retVal;
      IPWorks_NNTP_Get(m_pObj, 9, iGroupOverviewIndex, NULL, &retVal);
      return retVal;
    }

    inline LPWSTR GetGroupOverviewDate(INT iGroupOverviewIndex) {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 10+10000, iGroupOverviewIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetGroupOverviewFrom(INT iGroupOverviewIndex) {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 11+10000, iGroupOverviewIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetGroupOverviewMessageId(INT iGroupOverviewIndex) {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 12+10000, iGroupOverviewIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetGroupOverviewOtherHeaders(INT iGroupOverviewIndex) {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 13+10000, iGroupOverviewIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetGroupOverviewReferences(INT iGroupOverviewIndex) {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 14+10000, iGroupOverviewIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetGroupOverviewSubject(INT iGroupOverviewIndex) {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 15+10000, iGroupOverviewIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetArticleReferences() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetArticleReferences(LPCWSTR lpszArticleReferences) {
      return IPWorks_NNTP_Set(m_pObj, 16+10000, 0, (LPVOID)lpszArticleReferences, 0);
    }

    inline LPWSTR GetArticleReplyTo() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetArticleReplyTo(LPCWSTR lpszArticleReplyTo) {
      return IPWorks_NNTP_Set(m_pObj, 17+10000, 0, (LPVOID)lpszArticleReplyTo, 0);
    }

    inline LPWSTR GetArticleSubject() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetArticleSubject(LPCWSTR lpszArticleSubject) {
      return IPWorks_NNTP_Set(m_pObj, 18+10000, 0, (LPVOID)lpszArticleSubject, 0);
    }

    inline LPWSTR GetArticleText() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetArticleText(LPCWSTR lpszArticleText) {
      return IPWorks_NNTP_Set(m_pObj, 19+10000, 0, (LPVOID)lpszArticleText, 0);
    }

    inline LPWSTR GetAttachedFile() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAttachedFile(LPCWSTR lpszAttachedFile) {
      return IPWorks_NNTP_Set(m_pObj, 20+10000, 0, (LPVOID)lpszAttachedFile, 0);
    }

    inline LPWSTR GetCheckDate() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCheckDate(LPCWSTR lpszCheckDate) {
      return IPWorks_NNTP_Set(m_pObj, 21+10000, 0, (LPVOID)lpszCheckDate, 0);
    }

    inline INT SetCommand(LPCWSTR lpszCommand) {
      return IPWorks_NNTP_Set(m_pObj, 22+10000, 0, (LPVOID)lpszCommand, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 23, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_NNTP_Set(m_pObj, 23, 0, val, 0);
    }

    inline LPWSTR GetCurrentArticle() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCurrentArticle(LPCWSTR lpszCurrentArticle) {
      return IPWorks_NNTP_Set(m_pObj, 24+10000, 0, (LPVOID)lpszCurrentArticle, 0);
    }

    inline LPWSTR GetCurrentGroup() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCurrentGroup(LPCWSTR lpszCurrentGroup) {
      return IPWorks_NNTP_Set(m_pObj, 25+10000, 0, (LPVOID)lpszCurrentGroup, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 26, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_NNTP_Set(m_pObj, 26, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 27, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_NNTP_Set(m_pObj, 27, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 28+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_NNTP_Set(m_pObj, 28+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_NNTP_Set(m_pObj, 29+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 30, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_NNTP_Set(m_pObj, 30, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_NNTP_Set(m_pObj, 31+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline LONG64 GetFirstArticle() {
      LONG64 retVal;
      IPWorks_NNTP_Get(m_pObj, 32, 0, NULL, &retVal);
      return retVal;
    }

    inline INT GetGroupListCount() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 33, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline BOOL GetGroupListCanPost(INT iGroupListIndex) {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 34, iGroupListIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LONG64 GetGroupListFirstArticle(INT iGroupListIndex) {
      LONG64 retVal;
      IPWorks_NNTP_Get(m_pObj, 35, iGroupListIndex, NULL, &retVal);
      return retVal;
    }

    inline LPWSTR GetGroupListGroup(INT iGroupListIndex) {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 36+10000, iGroupListIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LONG64 GetGroupListLastArticle(INT iGroupListIndex) {
      LONG64 retVal;
      IPWorks_NNTP_Get(m_pObj, 37, iGroupListIndex, NULL, &retVal);
      return retVal;
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 38, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LONG64 GetLastArticle() {
      LONG64 retVal;
      IPWorks_NNTP_Get(m_pObj, 39, 0, NULL, &retVal);
      return retVal;
    }

    inline LPWSTR GetLastReply() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 40+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetLocalFile() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 41+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalFile(LPCWSTR lpszLocalFile) {
      return IPWorks_NNTP_Set(m_pObj, 41+10000, 0, (LPVOID)lpszLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 42+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_NNTP_Set(m_pObj, 42+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LONG64 GetMaxLines() {
      LONG64 retVal;
      IPWorks_NNTP_Get(m_pObj, 43, 0, NULL, &retVal);
      return retVal;
    }
    inline INT SetMaxLines(LONG64 lMaxLines) {
      LPVOID val = (LPVOID)(&lMaxLines);
      return IPWorks_NNTP_Set(m_pObj, 43, 0, val, 0);
    }

    inline LPWSTR GetNewsgroups() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 44+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNewsgroups(LPCWSTR lpszNewsgroups) {
      return IPWorks_NNTP_Set(m_pObj, 44+10000, 0, (LPVOID)lpszNewsgroups, 0);
    }

    inline INT GetNewsPort() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 45, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetNewsPort(INT iNewsPort) {
      LPVOID val = (LPVOID)(iNewsPort);
      return IPWorks_NNTP_Set(m_pObj, 45, 0, val, 0);
    }

    inline LPWSTR GetNewsServer() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 46+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNewsServer(LPCWSTR lpszNewsServer) {
      return IPWorks_NNTP_Set(m_pObj, 46+10000, 0, (LPVOID)lpszNewsServer, 0);
    }

    inline LPWSTR GetOrganization() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 47+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOrganization(LPCWSTR lpszOrganization) {
      return IPWorks_NNTP_Set(m_pObj, 47+10000, 0, (LPVOID)lpszOrganization, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 48+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_NNTP_Set(m_pObj, 48+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline LPWSTR GetOverviewRange() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 49+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOverviewRange(LPCWSTR lpszOverviewRange) {
      return IPWorks_NNTP_Set(m_pObj, 49+10000, 0, (LPVOID)lpszOverviewRange, 0);
    }

    inline INT GetParsedHeaderCount() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 50, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetParsedHeaderField(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 51+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetParsedHeaderValue(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 52+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 53+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_NNTP_Set(m_pObj, 53+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline LPWSTR GetSearchHeader() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 54+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSearchHeader(LPCWSTR lpszSearchHeader) {
      return IPWorks_NNTP_Set(m_pObj, 54+10000, 0, (LPVOID)lpszSearchHeader, 0);
    }

    inline LPWSTR GetSearchPattern() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 55+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSearchPattern(LPCWSTR lpszSearchPattern) {
      return IPWorks_NNTP_Set(m_pObj, 55+10000, 0, (LPVOID)lpszSearchPattern, 0);
    }

    inline LPWSTR GetSearchRange() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 56+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSearchRange(LPCWSTR lpszSearchRange) {
      return IPWorks_NNTP_Set(m_pObj, 56+10000, 0, (LPVOID)lpszSearchRange, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_NNTP_Get(m_pObj, 57, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_NNTP_Set(m_pObj, 57, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_NNTP_Get(m_pObj, 58, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_NNTP_Set(m_pObj, 58, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_NNTP_Get(m_pObj, 59, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_NNTP_Set(m_pObj, 59, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 60+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_NNTP_Set(m_pObj, 60+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 61, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_NNTP_Set(m_pObj, 61, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 62+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_NNTP_Set(m_pObj, 62+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 63, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_NNTP_Set(m_pObj, 63, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_NNTP_Get(m_pObj, 64, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 65, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_NNTP_Set(m_pObj, 65, 0, val, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 66, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_NNTP_Set(m_pObj, 66, 0, val, 0);
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_NNTP_Get(m_pObj, 67+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_NNTP_Set(m_pObj, 67+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_NNTP_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Connect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Disconnect() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT FetchArticle() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 6+10000, 0, param, cbparam, NULL);
    }

    inline INT FetchArticleBody() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline INT FetchArticleHeaders() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline INT GroupOverview() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT GroupSearch() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 11+10000, 0, param, cbparam, NULL);
    }

    inline INT ListGroups() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
    }

    inline INT ListNewGroups() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 13+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR LocalizeDate(LPCWSTR lpszDateTime) {
      LPVOID param[1+1] = {(LPVOID)lpszDateTime, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_NNTP_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT PostArticle() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 15+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 16+10000, 0, param, cbparam, NULL);
    }

    inline INT ResetHeaders() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 17+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_NNTP_H_
