/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_LDAP_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_LDAP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_LDAP_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  const char *name;
  const char *operatingSystem;
  const char *lastLogon;
  int logonCount;
  const char *dn;
  int reserved;
} LDAPComputerListEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} LDAPConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} LDAPConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} LDAPDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} LDAPErrorEventParams;

typedef struct {
  int MessageId;
  const char *DN;
  int ResultCode;
  const char *ResultDescription;
  const char *ResponseName;
  const char *ResponseValue;
  int lenResponseValue;
  int reserved;
} LDAPExtendedResponseEventParams;

typedef struct {
  const char *name;
  const char *description;
  const char *dn;
  int reserved;
} LDAPGroupListEventParams;

typedef struct {
  int Direction;
  const char *Description;
  const char *Message;
  int reserved;
} LDAPPITrailEventParams;

typedef struct {
  int MessageId;
  const char *DN;
  int ResultCode;
  const char *ResultDescription;
  int reserved;
} LDAPResultEventParams;

typedef struct {
  int MessageId;
  const char *DN;
  int ResultCode;
  const char *ResultDescription;
  int reserved;
} LDAPSearchCompleteEventParams;

typedef struct {
  int MessageId;
  const char *DN;
  int ResultCode;
  const char *ResultDescription;
  int CancelSearch;
  int reserved;
} LDAPSearchPageEventParams;

typedef struct {
  int MessageId;
  const char *DN;
  int reserved;
} LDAPSearchResultEventParams;

typedef struct {
  int MessageId;
  const char *LdapUrl;
  int reserved;
} LDAPSearchResultReferenceEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} LDAPSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} LDAPSSLStatusEventParams;

typedef struct {
  const char *name;
  const char *description;
  const char *lastLogon;
  const char *memberOf;
  const char *dn;
  int reserved;
} LDAPUserListEventParams;


class LDAP {
  public: // Events
    virtual int FireComputerList(LDAPComputerListEventParams *e) {return 0;}
    virtual int FireConnected(LDAPConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(LDAPConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(LDAPDisconnectedEventParams *e) {return 0;}
    virtual int FireError(LDAPErrorEventParams *e) {return 0;}
    virtual int FireExtendedResponse(LDAPExtendedResponseEventParams *e) {return 0;}
    virtual int FireGroupList(LDAPGroupListEventParams *e) {return 0;}
    virtual int FirePITrail(LDAPPITrailEventParams *e) {return 0;}
    virtual int FireResult(LDAPResultEventParams *e) {return 0;}
    virtual int FireSearchComplete(LDAPSearchCompleteEventParams *e) {return 0;}
    virtual int FireSearchPage(LDAPSearchPageEventParams *e) {return 0;}
    virtual int FireSearchResult(LDAPSearchResultEventParams *e) {return 0;}
    virtual int FireSearchResultReference(LDAPSearchResultReferenceEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(LDAPSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(LDAPSSLStatusEventParams *e) {return 0;}
    virtual int FireUserList(LDAPUserListEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL LDAPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          LDAPComputerListEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), 0};
          ret_code = ((LDAP*)lpObj)->FireComputerList(&e);
          break;
        }
        case 2: {
          LDAPConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((LDAP*)lpObj)->FireConnected(&e);
          break;
        }
        case 3: {
          LDAPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((LDAP*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 4: {
          LDAPDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((LDAP*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 5: {
          LDAPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((LDAP*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          LDAPExtendedResponseEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (int)IPW64CAST(cbparam[5]), 0};
          ret_code = ((LDAP*)lpObj)->FireExtendedResponse(&e);
          break;
        }
        case 7: {
          LDAPGroupListEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((LDAP*)lpObj)->FireGroupList(&e);
          break;
        }
        case 8: {
          LDAPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((LDAP*)lpObj)->FirePITrail(&e);
          break;
        }
        case 9: {
          LDAPResultEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), 0};
          ret_code = ((LDAP*)lpObj)->FireResult(&e);
          break;
        }
        case 10: {
          LDAPSearchCompleteEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), 0};
          ret_code = ((LDAP*)lpObj)->FireSearchComplete(&e);
          break;
        }
        case 11: {
          LDAPSearchPageEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((LDAP*)lpObj)->FireSearchPage(&e);
          param[4] = (void*)IPW64CAST(e.CancelSearch);
          break;
        }
        case 12: {
          LDAPSearchResultEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((LDAP*)lpObj)->FireSearchResult(&e);
          break;
        }
        case 13: {
          LDAPSearchResultReferenceEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((LDAP*)lpObj)->FireSearchResultReference(&e);
          break;
        }
        case 14: {
          LDAPSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((LDAP*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 15: {
          LDAPSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((LDAP*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 16: {
          LDAPUserListEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), 0};
          ret_code = ((LDAP*)lpObj)->FireUserList(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    LDAP(char *lpOemKey = (char*)IPWORKS_OEMKEY_33) {
      m_pObj = IPWorks_LDAP_Create(LDAPEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~LDAP() {
      IPWorks_LDAP_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_LDAP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_LDAP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_LDAP_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_LDAP_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_LDAP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetAcceptData() {
      void* val = IPWorks_LDAP_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAcceptData(int bAcceptData) {
      void* val = (void*)IPW64CAST(bAcceptData);
      return IPWorks_LDAP_Set(m_pObj, 1, 0, val, 0);
    }

    inline int GetAttrCount() {
      void* val = IPWorks_LDAP_Get(m_pObj, 2, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAttrCount(int iAttrCount) {
      void* val = (void*)IPW64CAST(iAttrCount);
      return IPWorks_LDAP_Set(m_pObj, 2, 0, val, 0);
    }

    inline char* GetAttrType(int iAttrIndex) {
      void* val = IPWorks_LDAP_Get(m_pObj, 3, iAttrIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetAttrType(int iAttrIndex, const char* lpszAttrType) {
      return IPWorks_LDAP_Set(m_pObj, 3, iAttrIndex, (void*)lpszAttrType, 0);
    }

    inline int GetAttrModOp(int iAttrIndex) {
      void* val = IPWorks_LDAP_Get(m_pObj, 4, iAttrIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAttrModOp(int iAttrIndex, int iAttrModOp) {
      void* val = (void*)IPW64CAST(iAttrModOp);
      return IPWorks_LDAP_Set(m_pObj, 4, iAttrIndex, val, 0);
    }

    inline int GetAttrValue(int iAttrIndex, char* &lpAttrValue, int &lenAttrValue) {
      lpAttrValue = (char*)IPWorks_LDAP_Get(m_pObj, 5, iAttrIndex, &lenAttrValue, NULL);
      return lpAttrValue ? 0 : lenAttrValue;
    }
    inline int SetAttrValue(int iAttrIndex, const char* lpAttrValue, int lenAttrValue) {
      return IPWorks_LDAP_Set(m_pObj, 5, iAttrIndex, (void*)lpAttrValue, lenAttrValue);
    }

    inline int GetAuthMechanism() {
      void* val = IPWorks_LDAP_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthMechanism(int iAuthMechanism) {
      void* val = (void*)IPW64CAST(iAuthMechanism);
      return IPWorks_LDAP_Set(m_pObj, 6, 0, val, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_LDAP_Get(m_pObj, 7, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_LDAP_Set(m_pObj, 7, 0, val, 0);
    }

    inline int GetDeleteOldRDN() {
      void* val = IPWorks_LDAP_Get(m_pObj, 8, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetDeleteOldRDN(int bDeleteOldRDN) {
      void* val = (void*)IPW64CAST(bDeleteOldRDN);
      return IPWorks_LDAP_Set(m_pObj, 8, 0, val, 0);
    }

    inline char* GetDN() {
      void* val = IPWorks_LDAP_Get(m_pObj, 9, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetDN(const char* lpszDN) {
      return IPWorks_LDAP_Set(m_pObj, 9, 0, (void*)lpszDN, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_LDAP_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_LDAP_Set(m_pObj, 10, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_LDAP_Get(m_pObj, 11, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_LDAP_Set(m_pObj, 11, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_LDAP_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_LDAP_Set(m_pObj, 12, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_LDAP_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_LDAP_Set(m_pObj, 13, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_LDAP_Get(m_pObj, 14, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_LDAP_Set(m_pObj, 14, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_LDAP_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_LDAP_Set(m_pObj, 15, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_LDAP_Get(m_pObj, 16, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline int GetLDAPVersion() {
      void* val = IPWorks_LDAP_Get(m_pObj, 17, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetLDAPVersion(int iLDAPVersion) {
      void* val = (void*)IPW64CAST(iLDAPVersion);
      return IPWorks_LDAP_Set(m_pObj, 17, 0, val, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_LDAP_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_LDAP_Set(m_pObj, 18, 0, (void*)lpszLocalHost, 0);
    }

    inline int GetMessageId() {
      void* val = IPWorks_LDAP_Get(m_pObj, 19, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMessageId(int iMessageId) {
      void* val = (void*)IPW64CAST(iMessageId);
      return IPWorks_LDAP_Set(m_pObj, 19, 0, val, 0);
    }

    inline int GetPageSize() {
      void* val = IPWorks_LDAP_Get(m_pObj, 20, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetPageSize(int iPageSize) {
      void* val = (void*)IPW64CAST(iPageSize);
      return IPWorks_LDAP_Set(m_pObj, 20, 0, val, 0);
    }

    inline char* GetPassword() {
      void* val = IPWorks_LDAP_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_LDAP_Set(m_pObj, 21, 0, (void*)lpszPassword, 0);
    }

    inline int GetReferenceCount() {
      void* val = IPWorks_LDAP_Get(m_pObj, 22, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetReferenceURL(int iReferenceIndex) {
      void* val = IPWorks_LDAP_Get(m_pObj, 23, iReferenceIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetResultCode() {
      void* val = IPWorks_LDAP_Get(m_pObj, 24, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetResultDescription() {
      void* val = IPWorks_LDAP_Get(m_pObj, 25, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetResultDN() {
      void* val = IPWorks_LDAP_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetSearchDerefAliases() {
      void* val = IPWorks_LDAP_Get(m_pObj, 27, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSearchDerefAliases(int iSearchDerefAliases) {
      void* val = (void*)IPW64CAST(iSearchDerefAliases);
      return IPWorks_LDAP_Set(m_pObj, 27, 0, val, 0);
    }

    inline int GetSearchReturnValues() {
      void* val = IPWorks_LDAP_Get(m_pObj, 28, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSearchReturnValues(int bSearchReturnValues) {
      void* val = (void*)IPW64CAST(bSearchReturnValues);
      return IPWorks_LDAP_Set(m_pObj, 28, 0, val, 0);
    }

    inline int GetSearchScope() {
      void* val = IPWorks_LDAP_Get(m_pObj, 29, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSearchScope(int iSearchScope) {
      void* val = (void*)IPW64CAST(iSearchScope);
      return IPWorks_LDAP_Set(m_pObj, 29, 0, val, 0);
    }

    inline int GetSearchSizeLimit() {
      void* val = IPWorks_LDAP_Get(m_pObj, 30, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSearchSizeLimit(int iSearchSizeLimit) {
      void* val = (void*)IPW64CAST(iSearchSizeLimit);
      return IPWorks_LDAP_Set(m_pObj, 30, 0, val, 0);
    }

    inline int GetSearchTimeLimit() {
      void* val = IPWorks_LDAP_Get(m_pObj, 31, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSearchTimeLimit(int iSearchTimeLimit) {
      void* val = (void*)IPW64CAST(iSearchTimeLimit);
      return IPWorks_LDAP_Set(m_pObj, 31, 0, val, 0);
    }

    inline char* GetServerName() {
      void* val = IPWorks_LDAP_Get(m_pObj, 32, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetServerName(const char* lpszServerName) {
      return IPWorks_LDAP_Set(m_pObj, 32, 0, (void*)lpszServerName, 0);
    }

    inline int GetServerPort() {
      void* val = IPWorks_LDAP_Get(m_pObj, 33, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetServerPort(int iServerPort) {
      void* val = (void*)IPW64CAST(iServerPort);
      return IPWorks_LDAP_Set(m_pObj, 33, 0, val, 0);
    }

    inline char* GetSortAttributes() {
      void* val = IPWorks_LDAP_Get(m_pObj, 34, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSortAttributes(const char* lpszSortAttributes) {
      return IPWorks_LDAP_Set(m_pObj, 34, 0, (void*)lpszSortAttributes, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_LDAP_Get(m_pObj, 35, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_LDAP_Set(m_pObj, 35, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_LDAP_Get(m_pObj, 36, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_LDAP_Set(m_pObj, 36, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_LDAP_Get(m_pObj, 37, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_LDAP_Set(m_pObj, 37, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_LDAP_Get(m_pObj, 38, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_LDAP_Set(m_pObj, 38, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_LDAP_Get(m_pObj, 39, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_LDAP_Set(m_pObj, 39, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_LDAP_Get(m_pObj, 40, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_LDAP_Set(m_pObj, 40, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLEnabled() {
      void* val = IPWorks_LDAP_Get(m_pObj, 41, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLEnabled(int bSSLEnabled) {
      void* val = (void*)IPW64CAST(bSSLEnabled);
      return IPWorks_LDAP_Set(m_pObj, 41, 0, val, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_LDAP_Get(m_pObj, 42, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline int GetSSLStartMode() {
      void* val = IPWorks_LDAP_Get(m_pObj, 43, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLStartMode(int iSSLStartMode) {
      void* val = (void*)IPW64CAST(iSSLStartMode);
      return IPWorks_LDAP_Set(m_pObj, 43, 0, val, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_LDAP_Get(m_pObj, 44, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_LDAP_Set(m_pObj, 44, 0, val, 0);
    }

  public: // Methods
    inline int Abandon(int iMessageId) {
      void *param[1+1] = {(void*)IPW64CAST(iMessageId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 2, 1, param, cbparam, NULL);
    }

    inline int Add() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline char* Attr(const char* lpszAttrType) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrType), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_LDAP_Do(m_pObj, 4, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Bind() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int ChangePassword(const char* lpszuser, const char* lpszoldPassword, const char* lpsznewPassword) {
      void *param[3+1] = {(void*)IPW64CAST(lpszuser), (void*)IPW64CAST(lpszoldPassword), (void*)IPW64CAST(lpsznewPassword), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_LDAP_Do(m_pObj, 6, 3, param, cbparam, NULL);
    }

    inline int Compare() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 7, 0, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_LDAP_Do(m_pObj, 8, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Delete() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

    inline int ExtendedRequest(const char* lpszRequestName, const char* lpRequestValue, int lenRequestValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszRequestName), (void*)IPW64CAST(lpRequestValue), 0};
      int cbparam[2+1] = {0, lenRequestValue, 0};
      return IPWorks_LDAP_Do(m_pObj, 11, 2, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 12, 0, param, cbparam, NULL);
    }

    inline int ListComputers() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 13, 0, param, cbparam, NULL);
    }

    inline int ListGroupMembers(const char* lpszgroup) {
      void *param[1+1] = {(void*)IPW64CAST(lpszgroup), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 14, 1, param, cbparam, NULL);
    }

    inline int ListGroups() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 15, 0, param, cbparam, NULL);
    }

    inline int ListUserGroups(const char* lpszuser) {
      void *param[1+1] = {(void*)IPW64CAST(lpszuser), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 16, 1, param, cbparam, NULL);
    }

    inline int Modify() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 17, 0, param, cbparam, NULL);
    }

    inline int ModifyRDN(const char* lpszNewRDN) {
      void *param[1+1] = {(void*)IPW64CAST(lpszNewRDN), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 18, 1, param, cbparam, NULL);
    }

    inline int MoveToDN(const char* lpszNewSuperior) {
      void *param[1+1] = {(void*)IPW64CAST(lpszNewSuperior), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 19, 1, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 20, 0, param, cbparam, NULL);
    }

    inline int Search(const char* lpszSearchFilter) {
      void *param[1+1] = {(void*)IPW64CAST(lpszSearchFilter), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 21, 1, param, cbparam, NULL);
    }

    inline int Unbind() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 22, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_LDAP_H_
