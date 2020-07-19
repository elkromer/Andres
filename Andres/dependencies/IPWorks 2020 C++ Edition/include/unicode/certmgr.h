/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_CERTMGR_H_
#define _IPWORKS_CERTMGR_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

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


extern "C" void* IPWORKS_CALL IPWorks_CertMgr_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_CertMgr_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_CertMgr_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_CertMgr_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR CertSerialNumber;
  INT TrustStatus;
  INT TrustInfo;
  INT reserved;
} CertMgrCertChainEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR CertSerialNumber;
  BOOL HasPrivateKey;
  INT reserved;
} CertMgrCertListEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} CertMgrErrorEventParams;

typedef struct {
  LPCWSTR KeyContainer;
  INT KeyType;
  LPCWSTR AlgId;
  INT KeyLen;
  INT reserved;
} CertMgrKeyListEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} CertMgrLogEventParams;

typedef struct {
  LPCWSTR CertStore;
  INT reserved;
} CertMgrStoreListEventParams;


class CertMgr {
  public: // Events
    virtual INT FireCertChain(CertMgrCertChainEventParams *e) {return 0;}
    virtual INT FireCertList(CertMgrCertListEventParams *e) {return 0;}
    virtual INT FireError(CertMgrErrorEventParams *e) {return 0;}
    virtual INT FireKeyList(CertMgrKeyListEventParams *e) {return 0;}
    virtual INT FireLog(CertMgrLogEventParams *e) {return 0;}
    virtual INT FireStoreList(CertMgrStoreListEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL CertMgrEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          CertMgrCertChainEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (INT)param[4], (INT)param[5], 0};
          ret_code = ((CertMgr*)lpObj)->FireCertChain(&e);
          break;
        }
        case 2: {
          CertMgrCertListEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((CertMgr*)lpObj)->FireCertList(&e);
          break;
        }
        case 3: {
          CertMgrErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((CertMgr*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          CertMgrKeyListEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], (INT)param[3], 0};
          ret_code = ((CertMgr*)lpObj)->FireKeyList(&e);
          break;
        }
        case 5: {
          CertMgrLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((CertMgr*)lpObj)->FireLog(&e);
          break;
        }
        case 6: {
          CertMgrStoreListEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((CertMgr*)lpObj)->FireStoreList(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    CertMgr(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_57) {
      m_pObj = IPWorks_CertMgr_Create(CertMgrEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~CertMgr() {
      IPWorks_CertMgr_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_CertMgr_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_CertMgr_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_CertMgr_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_CertMgr_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_CertMgr_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline LPWSTR GetCertEffectiveDate() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 1+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetCertEncoded(LPSTR &lpCertEncoded, INT &lenCertEncoded) {
      lpCertEncoded = (LPSTR)IPWorks_CertMgr_Get(m_pObj, 2, 0, &lenCertEncoded, NULL);
      return lpCertEncoded ? 0 : lenCertEncoded;
    }
    inline INT SetCertEncoded(LPCSTR lpCertEncoded, INT lenCertEncoded) {
      return IPWorks_CertMgr_Set(m_pObj, 2, 0, (LPVOID)lpCertEncoded, lenCertEncoded);
    }

    inline LPWSTR GetCertExpirationDate() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertExtendedKeyUsage() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCertExtendedKeyUsage(LPCWSTR lpszCertExtendedKeyUsage) {
      return IPWorks_CertMgr_Set(m_pObj, 4+10000, 0, (LPVOID)lpszCertExtendedKeyUsage, 0);
    }

    inline LPWSTR GetCertFingerprint() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertIssuer() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 6+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertKeyPassword() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCertKeyPassword(LPCWSTR lpszCertKeyPassword) {
      return IPWorks_CertMgr_Set(m_pObj, 7+10000, 0, (LPVOID)lpszCertKeyPassword, 0);
    }

    inline LPWSTR GetCertPrivateKey() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCertPrivateKeyAvailable() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 9, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCertPrivateKeyContainer() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 10+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertPublicKey() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertPublicKeyAlgorithm() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCertPublicKeyAlgorithm(LPCWSTR lpszCertPublicKeyAlgorithm) {
      return IPWorks_CertMgr_Set(m_pObj, 12+10000, 0, (LPVOID)lpszCertPublicKeyAlgorithm, 0);
    }

    inline INT GetCertPublicKeyLength() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 13, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetCertSerialNumber() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertSignatureAlgorithm() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertSubject() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCertSubject(LPCWSTR lpszCertSubject) {
      return IPWorks_CertMgr_Set(m_pObj, 16+10000, 0, (LPVOID)lpszCertSubject, 0);
    }

    inline LPWSTR GetCertSubjectAltNames() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertThumbprintMD5() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 18+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertThumbprintSHA1() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 19+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertThumbprintSHA256() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 20+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCertUsage() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 21+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCertUsage(LPCWSTR lpszCertUsage) {
      return IPWorks_CertMgr_Set(m_pObj, 21+10000, 0, (LPVOID)lpszCertUsage, 0);
    }

    inline INT GetCertUsageFlags() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 22, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCertUsageFlags(INT iCertUsageFlags) {
      LPVOID val = (LPVOID)(iCertUsageFlags);
      return IPWorks_CertMgr_Set(m_pObj, 22, 0, val, 0);
    }

    inline LPWSTR GetCertVersion() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 23+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetCertExtensionCount() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 24, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCertExtensionCount(INT iCertExtensionCount) {
      LPVOID val = (LPVOID)(iCertExtensionCount);
      return IPWorks_CertMgr_Set(m_pObj, 24, 0, val, 0);
    }

    inline BOOL GetCertExtensionCritical(INT iCertExtensionIndex) {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 25, iCertExtensionIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCertExtensionOID(INT iCertExtensionIndex) {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 26+10000, iCertExtensionIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetCertExtensionValue(INT iCertExtensionIndex, LPSTR &lpCertExtensionValue, INT &lenCertExtensionValue) {
      lpCertExtensionValue = (LPSTR)IPWorks_CertMgr_Get(m_pObj, 27, iCertExtensionIndex, &lenCertExtensionValue, NULL);
      return lpCertExtensionValue ? 0 : lenCertExtensionValue;
    }

    inline INT GetCertStore(LPSTR &lpCertStore, INT &lenCertStore) {
      lpCertStore = (LPSTR)IPWorks_CertMgr_Get(m_pObj, 28, 0, &lenCertStore, NULL);
      return lpCertStore ? 0 : lenCertStore;
    }
    inline INT SetCertStore(LPCSTR lpCertStore, INT lenCertStore) {
      return IPWorks_CertMgr_Set(m_pObj, 28, 0, (LPVOID)lpCertStore, lenCertStore);
    }

    inline LPWSTR GetCertStorePassword() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCertStorePassword(LPCWSTR lpszCertStorePassword) {
      return IPWorks_CertMgr_Set(m_pObj, 29+10000, 0, (LPVOID)lpszCertStorePassword, 0);
    }

    inline INT GetCertStoreType() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 30, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCertStoreType(INT iCertStoreType) {
      LPVOID val = (LPVOID)(iCertStoreType);
      return IPWorks_CertMgr_Set(m_pObj, 30, 0, val, 0);
    }

    inline INT GetExportedCert(LPSTR &lpExportedCert, INT &lenExportedCert) {
      lpExportedCert = (LPSTR)IPWorks_CertMgr_Get(m_pObj, 31, 0, &lenExportedCert, NULL);
      return lpExportedCert ? 0 : lenExportedCert;
    }

    inline LPWSTR GetExportFormat() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 32+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetExportFormat(LPCWSTR lpszExportFormat) {
      return IPWorks_CertMgr_Set(m_pObj, 32+10000, 0, (LPVOID)lpszExportFormat, 0);
    }

    inline BOOL GetExportPrivateKey() {
      LPVOID val = IPWorks_CertMgr_Get(m_pObj, 33, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetExportPrivateKey(BOOL bExportPrivateKey) {
      LPVOID val = (LPVOID)(bExportPrivateKey);
      return IPWorks_CertMgr_Set(m_pObj, 33, 0, val, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_CertMgr_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT CreateCertificate(LPCWSTR lpszCertSubject, INT iSerialNumber) {
      LPVOID param[2+1] = {(LPVOID)lpszCertSubject, (LPVOID)iSerialNumber, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 3+10000, 2, param, cbparam, NULL);
    }

    inline INT CreateKey(LPCWSTR lpszKeyName) {
      LPVOID param[1+1] = {(LPVOID)lpszKeyName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 4+10000, 1, param, cbparam, NULL);
    }

    inline INT DeleteCertificate() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_CertMgr_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT DeleteKey(LPCWSTR lpszKeyName) {
      LPVOID param[1+1] = {(LPVOID)lpszKeyName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
    }

    inline INT ExportCertificate(LPCWSTR lpszCertFile, LPCWSTR lpszPassword) {
      LPVOID param[2+1] = {(LPVOID)lpszCertFile, (LPVOID)lpszPassword, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 7+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR GenerateCSR(LPCWSTR lpszCertSubject, LPCWSTR lpszKeyName) {
      LPVOID param[2+1] = {(LPVOID)lpszCertSubject, (LPVOID)lpszKeyName, 0};
      INT cbparam[2+1] = {0, 0, 0};
      IPWorks_CertMgr_Do(m_pObj, 8+10000, 2, param, cbparam, NULL);
      return (LPWSTR)param[2];
    }

    inline INT ImportCertificate(LPCWSTR lpszCertFile, LPCWSTR lpszPassword, LPCWSTR lpszSubject) {
      LPVOID param[3+1] = {(LPVOID)lpszCertFile, (LPVOID)lpszPassword, (LPVOID)lpszSubject, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 9+10000, 3, param, cbparam, NULL);
    }

    inline INT ImportSignedCSR(LPCSTR lpSignedCSR, INT lenSignedCSR, LPCWSTR lpszKeyName) {
      LPVOID param[2+1] = {(LPVOID)lpSignedCSR, (LPVOID)lpszKeyName, 0};
      INT cbparam[2+1] = {lenSignedCSR, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10+10000, 2, param, cbparam, NULL);
    }

    inline INT IssueCertificate(LPCWSTR lpszCertSubject, INT iSerialNumber) {
      LPVOID param[2+1] = {(LPVOID)lpszCertSubject, (LPVOID)iSerialNumber, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 11+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR ListCertificateStores() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 12+10000, 0, param, cbparam, NULL);
      return (LPWSTR)param[0];
    }

    inline LPWSTR ListKeys() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 13+10000, 0, param, cbparam, NULL);
      return (LPWSTR)param[0];
    }

    inline LPWSTR ListMachineStores() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 14+10000, 0, param, cbparam, NULL);
      return (LPWSTR)param[0];
    }

    inline LPWSTR ListStoreCertificates() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 15+10000, 0, param, cbparam, NULL);
      return (LPWSTR)param[0];
    }

    inline INT ReadCertificate(LPCWSTR lpszFileName) {
      LPVOID param[1+1] = {(LPVOID)lpszFileName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 16+10000, 1, param, cbparam, NULL);
    }

    inline LPWSTR ReadCSR(LPCWSTR lpszCSR) {
      LPVOID param[1+1] = {(LPVOID)lpszCSR, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_CertMgr_Do(m_pObj, 17+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_CertMgr_Do(m_pObj, 18+10000, 0, param, cbparam, NULL);
    }

    inline INT SaveCertificate(LPCWSTR lpszFileName) {
      LPVOID param[1+1] = {(LPVOID)lpszFileName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 19+10000, 1, param, cbparam, NULL);
    }

    inline LPWSTR ShowCertificateChain() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 20+10000, 0, param, cbparam, NULL);
      return (LPWSTR)param[0];
    }

    inline LPWSTR SignCSR(LPCSTR lpCSR, INT lenCSR, INT iSerialNumber) {
      LPVOID param[2+1] = {(LPVOID)lpCSR, (LPVOID)iSerialNumber, 0};
      INT cbparam[2+1] = {lenCSR, 0, 0};
      IPWorks_CertMgr_Do(m_pObj, 21+10000, 2, param, cbparam, NULL);
      return (LPWSTR)param[2];
    }

};

#endif //_IPWORKS_CERTMGR_H_
