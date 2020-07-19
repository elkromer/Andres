/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_CertMgr_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_CertMgr_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_CertMgr_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *CertSerialNumber;
  int TrustStatus;
  int TrustInfo;
  int reserved;
} CertMgrCertChainEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *CertSerialNumber;
  int HasPrivateKey;
  int reserved;
} CertMgrCertListEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} CertMgrErrorEventParams;

typedef struct {
  const char *KeyContainer;
  int KeyType;
  const char *AlgId;
  int KeyLen;
  int reserved;
} CertMgrKeyListEventParams;

typedef struct {
  int LogLevel;
  const char *Message;
  const char *LogType;
  int reserved;
} CertMgrLogEventParams;

typedef struct {
  const char *CertStore;
  int reserved;
} CertMgrStoreListEventParams;


class CertMgr {
  public: // Events
    virtual int FireCertChain(CertMgrCertChainEventParams *e) {return 0;}
    virtual int FireCertList(CertMgrCertListEventParams *e) {return 0;}
    virtual int FireError(CertMgrErrorEventParams *e) {return 0;}
    virtual int FireKeyList(CertMgrKeyListEventParams *e) {return 0;}
    virtual int FireLog(CertMgrLogEventParams *e) {return 0;}
    virtual int FireStoreList(CertMgrStoreListEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL CertMgrEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          CertMgrCertChainEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), 0};
          ret_code = ((CertMgr*)lpObj)->FireCertChain(&e);
          break;
        }
        case 2: {
          CertMgrCertListEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((CertMgr*)lpObj)->FireCertList(&e);
          break;
        }
        case 3: {
          CertMgrErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((CertMgr*)lpObj)->FireError(&e);
          break;
        }
        case 4: {
          CertMgrKeyListEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), 0};
          ret_code = ((CertMgr*)lpObj)->FireKeyList(&e);
          break;
        }
        case 5: {
          CertMgrLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((CertMgr*)lpObj)->FireLog(&e);
          break;
        }
        case 6: {
          CertMgrStoreListEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((CertMgr*)lpObj)->FireStoreList(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    CertMgr(char *lpOemKey = (char*)IPWORKS_OEMKEY_57) {
      m_pObj = IPWorks_CertMgr_Create(CertMgrEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~CertMgr() {
      IPWorks_CertMgr_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_CertMgr_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_CertMgr_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_CertMgr_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_CertMgr_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_CertMgr_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetCertEffectiveDate() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetCertEncoded(char* &lpCertEncoded, int &lenCertEncoded) {
      lpCertEncoded = (char*)IPWorks_CertMgr_Get(m_pObj, 2, 0, &lenCertEncoded, NULL);
      return lpCertEncoded ? 0 : lenCertEncoded;
    }
    inline int SetCertEncoded(const char* lpCertEncoded, int lenCertEncoded) {
      return IPWorks_CertMgr_Set(m_pObj, 2, 0, (void*)lpCertEncoded, lenCertEncoded);
    }

    inline char* GetCertExpirationDate() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertExtendedKeyUsage() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCertExtendedKeyUsage(const char* lpszCertExtendedKeyUsage) {
      return IPWorks_CertMgr_Set(m_pObj, 4, 0, (void*)lpszCertExtendedKeyUsage, 0);
    }

    inline char* GetCertFingerprint() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertIssuer() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 6, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertKeyPassword() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCertKeyPassword(const char* lpszCertKeyPassword) {
      return IPWorks_CertMgr_Set(m_pObj, 7, 0, (void*)lpszCertKeyPassword, 0);
    }

    inline char* GetCertPrivateKey() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetCertPrivateKeyAvailable() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 9, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCertPrivateKeyContainer() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 10, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertPublicKey() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertPublicKeyAlgorithm() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCertPublicKeyAlgorithm(const char* lpszCertPublicKeyAlgorithm) {
      return IPWorks_CertMgr_Set(m_pObj, 12, 0, (void*)lpszCertPublicKeyAlgorithm, 0);
    }

    inline int GetCertPublicKeyLength() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 13, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCertSerialNumber() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertSignatureAlgorithm() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertSubject() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCertSubject(const char* lpszCertSubject) {
      return IPWorks_CertMgr_Set(m_pObj, 16, 0, (void*)lpszCertSubject, 0);
    }

    inline char* GetCertSubjectAltNames() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertThumbprintMD5() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 18, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertThumbprintSHA1() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 19, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertThumbprintSHA256() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 20, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCertUsage() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 21, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCertUsage(const char* lpszCertUsage) {
      return IPWorks_CertMgr_Set(m_pObj, 21, 0, (void*)lpszCertUsage, 0);
    }

    inline int GetCertUsageFlags() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 22, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCertUsageFlags(int iCertUsageFlags) {
      void* val = (void*)IPW64CAST(iCertUsageFlags);
      return IPWorks_CertMgr_Set(m_pObj, 22, 0, val, 0);
    }

    inline char* GetCertVersion() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 23, 0, NULL, NULL);
      return (char*)val;
    }

    inline int GetCertExtensionCount() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 24, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCertExtensionCount(int iCertExtensionCount) {
      void* val = (void*)IPW64CAST(iCertExtensionCount);
      return IPWorks_CertMgr_Set(m_pObj, 24, 0, val, 0);
    }

    inline int GetCertExtensionCritical(int iCertExtensionIndex) {
      void* val = IPWorks_CertMgr_Get(m_pObj, 25, iCertExtensionIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCertExtensionOID(int iCertExtensionIndex) {
      void* val = IPWorks_CertMgr_Get(m_pObj, 26, iCertExtensionIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetCertExtensionValue(int iCertExtensionIndex, char* &lpCertExtensionValue, int &lenCertExtensionValue) {
      lpCertExtensionValue = (char*)IPWorks_CertMgr_Get(m_pObj, 27, iCertExtensionIndex, &lenCertExtensionValue, NULL);
      return lpCertExtensionValue ? 0 : lenCertExtensionValue;
    }

    inline int GetCertStore(char* &lpCertStore, int &lenCertStore) {
      lpCertStore = (char*)IPWorks_CertMgr_Get(m_pObj, 28, 0, &lenCertStore, NULL);
      return lpCertStore ? 0 : lenCertStore;
    }
    inline int SetCertStore(const char* lpCertStore, int lenCertStore) {
      return IPWorks_CertMgr_Set(m_pObj, 28, 0, (void*)lpCertStore, lenCertStore);
    }

    inline char* GetCertStorePassword() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 29, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCertStorePassword(const char* lpszCertStorePassword) {
      return IPWorks_CertMgr_Set(m_pObj, 29, 0, (void*)lpszCertStorePassword, 0);
    }

    inline int GetCertStoreType() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 30, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCertStoreType(int iCertStoreType) {
      void* val = (void*)IPW64CAST(iCertStoreType);
      return IPWorks_CertMgr_Set(m_pObj, 30, 0, val, 0);
    }

    inline int GetExportedCert(char* &lpExportedCert, int &lenExportedCert) {
      lpExportedCert = (char*)IPWorks_CertMgr_Get(m_pObj, 31, 0, &lenExportedCert, NULL);
      return lpExportedCert ? 0 : lenExportedCert;
    }

    inline char* GetExportFormat() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 32, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetExportFormat(const char* lpszExportFormat) {
      return IPWorks_CertMgr_Set(m_pObj, 32, 0, (void*)lpszExportFormat, 0);
    }

    inline int GetExportPrivateKey() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 33, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetExportPrivateKey(int bExportPrivateKey) {
      void* val = (void*)IPW64CAST(bExportPrivateKey);
      return IPWorks_CertMgr_Set(m_pObj, 33, 0, val, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_CertMgr_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int CreateCertificate(const char* lpszCertSubject, int iSerialNumber) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCertSubject), (void*)IPW64CAST(iSerialNumber), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 3, 2, param, cbparam, NULL);
    }

    inline int CreateKey(const char* lpszKeyName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszKeyName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 4, 1, param, cbparam, NULL);
    }

    inline int DeleteCertificate() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CertMgr_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int DeleteKey(const char* lpszKeyName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszKeyName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 6, 1, param, cbparam, NULL);
    }

    inline int ExportCertificate(const char* lpszCertFile, const char* lpszPassword) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCertFile), (void*)IPW64CAST(lpszPassword), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 7, 2, param, cbparam, NULL);
    }

    inline char* GenerateCSR(const char* lpszCertSubject, const char* lpszKeyName) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCertSubject), (void*)IPW64CAST(lpszKeyName), 0};
      int cbparam[2+1] = {0, 0, 0};
      IPWorks_CertMgr_Do(m_pObj, 8, 2, param, cbparam, NULL);
      return (char*)IPW64CAST(param[2]);
    }

    inline int ImportCertificate(const char* lpszCertFile, const char* lpszPassword, const char* lpszSubject) {
      void *param[3+1] = {(void*)IPW64CAST(lpszCertFile), (void*)IPW64CAST(lpszPassword), (void*)IPW64CAST(lpszSubject), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 9, 3, param, cbparam, NULL);
    }

    inline int ImportSignedCSR(const char* lpSignedCSR, int lenSignedCSR, const char* lpszKeyName) {
      void *param[2+1] = {(void*)IPW64CAST(lpSignedCSR), (void*)IPW64CAST(lpszKeyName), 0};
      int cbparam[2+1] = {lenSignedCSR, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10, 2, param, cbparam, NULL);
    }

    inline int IssueCertificate(const char* lpszCertSubject, int iSerialNumber) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCertSubject), (void*)IPW64CAST(iSerialNumber), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 11, 2, param, cbparam, NULL);
    }

    inline char* ListCertificateStores() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 12, 0, param, cbparam, NULL);
      return (char*)IPW64CAST(param[0]);
    }

    inline char* ListKeys() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 13, 0, param, cbparam, NULL);
      return (char*)IPW64CAST(param[0]);
    }

    inline char* ListMachineStores() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 14, 0, param, cbparam, NULL);
      return (char*)IPW64CAST(param[0]);
    }

    inline char* ListStoreCertificates() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 15, 0, param, cbparam, NULL);
      return (char*)IPW64CAST(param[0]);
    }

    inline int ReadCertificate(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 16, 1, param, cbparam, NULL);
    }

    inline char* ReadCSR(const char* lpszCSR) {
      void *param[1+1] = {(void*)IPW64CAST(lpszCSR), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_CertMgr_Do(m_pObj, 17, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CertMgr_Do(m_pObj, 18, 0, param, cbparam, NULL);
    }

    inline int SaveCertificate(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 19, 1, param, cbparam, NULL);
    }

    inline char* ShowCertificateChain() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 20, 0, param, cbparam, NULL);
      return (char*)IPW64CAST(param[0]);
    }

    inline char* SignCSR(const char* lpCSR, int lenCSR, int iSerialNumber) {
      void *param[2+1] = {(void*)IPW64CAST(lpCSR), (void*)IPW64CAST(iSerialNumber), 0};
      int cbparam[2+1] = {lenCSR, 0, 0};
      IPWorks_CertMgr_Do(m_pObj, 21, 2, param, cbparam, NULL);
      return (char*)IPW64CAST(param[2]);
    }

};

#endif //_IPWORKS_CERTMGR_H_
