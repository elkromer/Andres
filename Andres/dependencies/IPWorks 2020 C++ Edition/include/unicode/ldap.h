/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_LDAP_H_
#define _IPWORKS_LDAP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//LDAPAttributeModOps
#define AMO_ADD                                            0
#define AMO_DELETE                                         1
#define AMO_REPLACE                                        2

//LDAPAuthMechanisms
#define LAM_SIMPLE                                         0
#define LAM_DIGEST_MD5                                     1
#define LAM_NEGOTIATE                                      2
#define LAM_KERBEROS                                       6

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TLDAPDerefAliases
#define SDA_NEVER                                          0
#define SDA_IN_SEARCHING                                   1
#define SDA_FINDING_BASE_OBJECT                            2
#define SDA_ALWAYS                                         3

//TLDAPSearchScope
#define SS_BASE_OBJECT                                     0
#define SS_SINGLE_LEVEL                                    1
#define SS_WHOLE_SUBTREE                                   2

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


extern "C" void* IPWORKS_CALL IPWorks_LDAP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_LDAP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_LDAP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_LDAP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR name;
  LPCWSTR operatingSystem;
  LPCWSTR lastLogon;
  INT logonCount;
  LPCWSTR dn;
  INT reserved;
} LDAPComputerListEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} LDAPConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} LDAPConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} LDAPDisconnectedEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} LDAPErrorEventParams;

typedef struct {
  INT MessageId;
  LPCWSTR DN;
  INT ResultCode;
  LPCWSTR ResultDescription;
  LPCWSTR ResponseName;
  LPCSTR ResponseValue;
  INT lenResponseValue;
  INT reserved;
} LDAPExtendedResponseEventParams;

typedef struct {
  LPCWSTR name;
  LPCWSTR description;
  LPCWSTR dn;
  INT reserved;
} LDAPGroupListEventParams;

typedef struct {
  INT Direction;
  LPCWSTR Description;
  LPCWSTR Message;
  INT reserved;
} LDAPPITrailEventParams;

typedef struct {
  INT MessageId;
  LPCWSTR DN;
  INT ResultCode;
  LPCWSTR ResultDescription;
  INT reserved;
} LDAPResultEventParams;

typedef struct {
  INT MessageId;
  LPCWSTR DN;
  INT ResultCode;
  LPCWSTR ResultDescription;
  INT reserved;
} LDAPSearchCompleteEventParams;

typedef struct {
  INT MessageId;
  LPCWSTR DN;
  INT ResultCode;
  LPCWSTR ResultDescription;
  BOOL CancelSearch;
  INT reserved;
} LDAPSearchPageEventParams;

typedef struct {
  INT MessageId;
  LPCWSTR DN;
  INT reserved;
} LDAPSearchResultEventParams;

typedef struct {
  INT MessageId;
  LPCWSTR LdapUrl;
  INT reserved;
} LDAPSearchResultReferenceEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} LDAPSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} LDAPSSLStatusEventParams;

typedef struct {
  LPCWSTR name;
  LPCWSTR description;
  LPCWSTR lastLogon;
  LPCWSTR memberOf;
  LPCWSTR dn;
  INT reserved;
} LDAPUserListEventParams;


class LDAP {
  public: // Events
    virtual INT FireComputerList(LDAPComputerListEventParams *e) {return 0;}
    virtual INT FireConnected(LDAPConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(LDAPConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(LDAPDisconnectedEventParams *e) {return 0;}
    virtual INT FireError(LDAPErrorEventParams *e) {return 0;}
    virtual INT FireExtendedResponse(LDAPExtendedResponseEventParams *e) {return 0;}
    virtual INT FireGroupList(LDAPGroupListEventParams *e) {return 0;}
    virtual INT FirePITrail(LDAPPITrailEventParams *e) {return 0;}
    virtual INT FireResult(LDAPResultEventParams *e) {return 0;}
    virtual INT FireSearchComplete(LDAPSearchCompleteEventParams *e) {return 0;}
    virtual INT FireSearchPage(LDAPSearchPageEventParams *e) {return 0;}
    virtual INT FireSearchResult(LDAPSearchResultEventParams *e) {return 0;}
    virtual INT FireSearchResultReference(LDAPSearchResultReferenceEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(LDAPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(LDAPSSLStatusEventParams *e) {return 0;}
    virtual INT FireUserList(LDAPUserListEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL LDAPEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          LDAPComputerListEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (INT)param[3], (LPWSTR)param[4], 0};
          ret_code = ((LDAP*)lpObj)->FireComputerList(&e);
          break;
        }
        case 2: {
          LDAPConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((LDAP*)lpObj)->FireConnected(&e);
          break;
        }
        case 3: {
          LDAPConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((LDAP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 4: {
          LDAPDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((LDAP*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 5: {
          LDAPErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((LDAP*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          LDAPExtendedResponseEventParams e = {(INT)param[0], (LPWSTR)param[1], (INT)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (LPSTR)param[5], (INT)cbparam[5], 0};
          ret_code = ((LDAP*)lpObj)->FireExtendedResponse(&e);
          break;
        }
        case 7: {
          LDAPGroupListEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((LDAP*)lpObj)->FireGroupList(&e);
          break;
        }
        case 8: {
          LDAPPITrailEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((LDAP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 9: {
          LDAPResultEventParams e = {(INT)param[0], (LPWSTR)param[1], (INT)param[2], (LPWSTR)param[3], 0};
          ret_code = ((LDAP*)lpObj)->FireResult(&e);
          break;
        }
        case 10: {
          LDAPSearchCompleteEventParams e = {(INT)param[0], (LPWSTR)param[1], (INT)param[2], (LPWSTR)param[3], 0};
          ret_code = ((LDAP*)lpObj)->FireSearchComplete(&e);
          break;
        }
        case 11: {
          LDAPSearchPageEventParams e = {(INT)param[0], (LPWSTR)param[1], (INT)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((LDAP*)lpObj)->FireSearchPage(&e);
          param[4] = (LPVOID)e.CancelSearch;
          break;
        }
        case 12: {
          LDAPSearchResultEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((LDAP*)lpObj)->FireSearchResult(&e);
          break;
        }
        case 13: {
          LDAPSearchResultReferenceEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((LDAP*)lpObj)->FireSearchResultReference(&e);
          break;
        }
        case 14: {
          LDAPSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((LDAP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 15: {
          LDAPSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((LDAP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 16: {
          LDAPUserListEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], 0};
          ret_code = ((LDAP*)lpObj)->FireUserList(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    LDAP(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_33) {
      m_pObj = IPWorks_LDAP_Create(LDAPEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~LDAP() {
      IPWorks_LDAP_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_LDAP_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_LDAP_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_LDAP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_LDAP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_LDAP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetAcceptData() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetAcceptData(BOOL bAcceptData) {
      LPVOID val = (LPVOID)(bAcceptData);
      return IPWorks_LDAP_Set(m_pObj, 1, 0, val, 0);
    }

    inline INT GetAttrCount() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 2, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAttrCount(INT iAttrCount) {
      LPVOID val = (LPVOID)(iAttrCount);
      return IPWorks_LDAP_Set(m_pObj, 2, 0, val, 0);
    }

    inline LPWSTR GetAttrType(INT iAttrIndex) {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 3+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAttrType(INT iAttrIndex, LPCWSTR lpszAttrType) {
      return IPWorks_LDAP_Set(m_pObj, 3+10000, iAttrIndex, (LPVOID)lpszAttrType, 0);
    }

    inline INT GetAttrModOp(INT iAttrIndex) {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 4, iAttrIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAttrModOp(INT iAttrIndex, INT iAttrModOp) {
      LPVOID val = (LPVOID)(iAttrModOp);
      return IPWorks_LDAP_Set(m_pObj, 4, iAttrIndex, val, 0);
    }

    inline INT GetAttrValue(INT iAttrIndex, LPSTR &lpAttrValue, INT &lenAttrValue) {
      lpAttrValue = (LPSTR)IPWorks_LDAP_Get(m_pObj, 5, iAttrIndex, &lenAttrValue, NULL);
      return lpAttrValue ? 0 : lenAttrValue;
    }
    inline INT SetAttrValue(INT iAttrIndex, LPCSTR lpAttrValue, INT lenAttrValue) {
      return IPWorks_LDAP_Set(m_pObj, 5, iAttrIndex, (LPVOID)lpAttrValue, lenAttrValue);
    }

    inline INT GetAuthMechanism() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 6, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthMechanism(INT iAuthMechanism) {
      LPVOID val = (LPVOID)(iAuthMechanism);
      return IPWorks_LDAP_Set(m_pObj, 6, 0, val, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 7, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_LDAP_Set(m_pObj, 7, 0, val, 0);
    }

    inline BOOL GetDeleteOldRDN() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 8, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetDeleteOldRDN(BOOL bDeleteOldRDN) {
      LPVOID val = (LPVOID)(bDeleteOldRDN);
      return IPWorks_LDAP_Set(m_pObj, 8, 0, val, 0);
    }

    inline LPWSTR GetDN() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 9+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDN(LPCWSTR lpszDN) {
      return IPWorks_LDAP_Set(m_pObj, 9+10000, 0, (LPVOID)lpszDN, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 10, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_LDAP_Set(m_pObj, 10, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 11, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_LDAP_Set(m_pObj, 11, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_LDAP_Set(m_pObj, 12+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_LDAP_Set(m_pObj, 13+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 14, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_LDAP_Set(m_pObj, 14, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_LDAP_Set(m_pObj, 15+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 16, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline INT GetLDAPVersion() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 17, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLDAPVersion(INT iLDAPVersion) {
      LPVOID val = (LPVOID)(iLDAPVersion);
      return IPWorks_LDAP_Set(m_pObj, 17, 0, val, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_LDAP_Set(m_pObj, 18+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline INT GetMessageId() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 19, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetMessageId(INT iMessageId) {
      LPVOID val = (LPVOID)(iMessageId);
      return IPWorks_LDAP_Set(m_pObj, 19, 0, val, 0);
    }

    inline INT GetPageSize() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 20, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetPageSize(INT iPageSize) {
      LPVOID val = (LPVOID)(iPageSize);
      return IPWorks_LDAP_Set(m_pObj, 20, 0, val, 0);
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_LDAP_Set(m_pObj, 21+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetReferenceCount() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 22, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetReferenceURL(INT iReferenceIndex) {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 23+10000, iReferenceIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetResultCode() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 24, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetResultDescription() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetResultDN() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetSearchDerefAliases() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 27, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSearchDerefAliases(INT iSearchDerefAliases) {
      LPVOID val = (LPVOID)(iSearchDerefAliases);
      return IPWorks_LDAP_Set(m_pObj, 27, 0, val, 0);
    }

    inline BOOL GetSearchReturnValues() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 28, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSearchReturnValues(BOOL bSearchReturnValues) {
      LPVOID val = (LPVOID)(bSearchReturnValues);
      return IPWorks_LDAP_Set(m_pObj, 28, 0, val, 0);
    }

    inline INT GetSearchScope() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 29, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSearchScope(INT iSearchScope) {
      LPVOID val = (LPVOID)(iSearchScope);
      return IPWorks_LDAP_Set(m_pObj, 29, 0, val, 0);
    }

    inline INT GetSearchSizeLimit() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 30, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSearchSizeLimit(INT iSearchSizeLimit) {
      LPVOID val = (LPVOID)(iSearchSizeLimit);
      return IPWorks_LDAP_Set(m_pObj, 30, 0, val, 0);
    }

    inline INT GetSearchTimeLimit() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 31, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSearchTimeLimit(INT iSearchTimeLimit) {
      LPVOID val = (LPVOID)(iSearchTimeLimit);
      return IPWorks_LDAP_Set(m_pObj, 31, 0, val, 0);
    }

    inline LPWSTR GetServerName() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 32+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetServerName(LPCWSTR lpszServerName) {
      return IPWorks_LDAP_Set(m_pObj, 32+10000, 0, (LPVOID)lpszServerName, 0);
    }

    inline INT GetServerPort() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 33, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetServerPort(INT iServerPort) {
      LPVOID val = (LPVOID)(iServerPort);
      return IPWorks_LDAP_Set(m_pObj, 33, 0, val, 0);
    }

    inline LPWSTR GetSortAttributes() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 34+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSortAttributes(LPCWSTR lpszSortAttributes) {
      return IPWorks_LDAP_Set(m_pObj, 34+10000, 0, (LPVOID)lpszSortAttributes, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_LDAP_Get(m_pObj, 35, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_LDAP_Set(m_pObj, 35, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_LDAP_Get(m_pObj, 36, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_LDAP_Set(m_pObj, 36, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_LDAP_Get(m_pObj, 37, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_LDAP_Set(m_pObj, 37, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 38+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_LDAP_Set(m_pObj, 38+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 39, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_LDAP_Set(m_pObj, 39, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 40+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_LDAP_Set(m_pObj, 40+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline BOOL GetSSLEnabled() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 41, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetSSLEnabled(BOOL bSSLEnabled) {
      LPVOID val = (LPVOID)(bSSLEnabled);
      return IPWorks_LDAP_Set(m_pObj, 41, 0, val, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_LDAP_Get(m_pObj, 42, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline INT GetSSLStartMode() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 43, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLStartMode(INT iSSLStartMode) {
      LPVOID val = (LPVOID)(iSSLStartMode);
      return IPWorks_LDAP_Set(m_pObj, 43, 0, val, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_LDAP_Get(m_pObj, 44, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_LDAP_Set(m_pObj, 44, 0, val, 0);
    }

  public: // Methods
    inline INT Abandon(INT iMessageId) {
      LPVOID param[1+1] = {(LPVOID)iMessageId, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
    }

    inline INT Add() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR Attr(LPCWSTR lpszAttrType) {
      LPVOID param[1+1] = {(LPVOID)lpszAttrType, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_LDAP_Do(m_pObj, 4+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Bind() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT ChangePassword(LPCWSTR lpszuser, LPCWSTR lpszoldPassword, LPCWSTR lpsznewPassword) {
      LPVOID param[3+1] = {(LPVOID)lpszuser, (LPVOID)lpszoldPassword, (LPVOID)lpsznewPassword, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_LDAP_Do(m_pObj, 6+10000, 3, param, cbparam, NULL);
    }

    inline INT Compare() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 7+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_LDAP_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Delete() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 10+10000, 0, param, cbparam, NULL);
    }

    inline INT ExtendedRequest(LPCWSTR lpszRequestName, LPCSTR lpRequestValue, INT lenRequestValue) {
      LPVOID param[2+1] = {(LPVOID)lpszRequestName, (LPVOID)lpRequestValue, 0};
      INT cbparam[2+1] = {0, lenRequestValue, 0};
      return IPWorks_LDAP_Do(m_pObj, 11+10000, 2, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
    }

    inline INT ListComputers() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 13+10000, 0, param, cbparam, NULL);
    }

    inline INT ListGroupMembers(LPCWSTR lpszgroup) {
      LPVOID param[1+1] = {(LPVOID)lpszgroup, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
    }

    inline INT ListGroups() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 15+10000, 0, param, cbparam, NULL);
    }

    inline INT ListUserGroups(LPCWSTR lpszuser) {
      LPVOID param[1+1] = {(LPVOID)lpszuser, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 16+10000, 1, param, cbparam, NULL);
    }

    inline INT Modify() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 17+10000, 0, param, cbparam, NULL);
    }

    inline INT ModifyRDN(LPCWSTR lpszNewRDN) {
      LPVOID param[1+1] = {(LPVOID)lpszNewRDN, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 18+10000, 1, param, cbparam, NULL);
    }

    inline INT MoveToDN(LPCWSTR lpszNewSuperior) {
      LPVOID param[1+1] = {(LPVOID)lpszNewSuperior, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 19+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 20+10000, 0, param, cbparam, NULL);
    }

    inline INT Search(LPCWSTR lpszSearchFilter) {
      LPVOID param[1+1] = {(LPVOID)lpszSearchFilter, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 21+10000, 1, param, cbparam, NULL);
    }

    inline INT Unbind() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 22+10000, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_LDAP_H_
