/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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


extern "C" void* IPWORKS_CALL IPWorks_CertMgr_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_CertMgr_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_CertMgr_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_CertMgr_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* CertSerialNumber;
  int TrustStatus;
  int TrustInfo;
  int lenCertEncoded;
  int reserved;
} CertMgrCertChainEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* CertSerialNumber;
  int HasPrivateKey;
  int lenCertEncoded;
  int reserved;
} CertMgrCertListEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} CertMgrErrorEventParams;

typedef struct {
  const char* KeyContainer;
  int KeyType;
  const char* AlgId;
  int KeyLen;
  int reserved;
} CertMgrKeyListEventParams;

typedef struct {
  const char* CertStore;
  int reserved;
} CertMgrStoreListEventParams;



class CertMgr {
  
  public: //events
  
    virtual int FireCertChain(CertMgrCertChainEventParams *e) {return 0;}
    virtual int FireCertList(CertMgrCertListEventParams *e) {return 0;}
    virtual int FireError(CertMgrErrorEventParams *e) {return 0;}
    virtual int FireKeyList(CertMgrKeyListEventParams *e) {return 0;}
    virtual int FireStoreList(CertMgrStoreListEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL CertMgrEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((CertMgr*)lpObj)->CertMgrEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            CertMgrCertChainEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((CertMgr*)lpObj)->FireCertChain(&e);
            break;
         }
         case 2: {
            CertMgrCertListEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((CertMgr*)lpObj)->FireCertList(&e);
            break;
         }
         case 3: {
            CertMgrErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((CertMgr*)lpObj)->FireError(&e);
            break;
         }
         case 4: {
            CertMgrKeyListEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = ((CertMgr*)lpObj)->FireKeyList(&e);
            break;
         }
         case 5: {
            CertMgrStoreListEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((CertMgr*)lpObj)->FireStoreList(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int CertMgrEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    CertMgr(char *lpOemKey = (char*)IPWORKS_OEMKEY_57) {
      m_pObj = IPWorks_CertMgr_Create(CertMgrEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~CertMgr() {
      IPWorks_CertMgr_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_CertMgr_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_CertMgr_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_CertMgr_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_CertMgr_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_CertMgr_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetCertEffectiveDate() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }


    inline int GetCertEncoded(char *&lpCertEncoded, int &lenCertEncoded) {
      lpCertEncoded = (char*)IPWorks_CertMgr_Get(m_pObj, 2, 0, &lenCertEncoded);
      return lpCertEncoded ? 0 : lenCertEncoded;
    }

    inline int SetCertEncoded(const char *lpCertEncoded, int lenCertEncoded) {
      return IPWorks_CertMgr_Set(m_pObj, 2, 0, (void*)lpCertEncoded, lenCertEncoded);
    }

    inline char* GetCertExpirationDate() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }


    inline char* GetCertExtendedKeyUsage() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetCertExtendedKeyUsage(const char *lpCertExtendedKeyUsage) {
      return IPWorks_CertMgr_Set(m_pObj, 4, 0, (void*)lpCertExtendedKeyUsage, 0);
    }

    inline char* GetCertFingerprint() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }


    inline char* GetCertIssuer() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }


    inline char* GetCertKeyPassword() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetCertKeyPassword(const char *lpCertKeyPassword) {
      return IPWorks_CertMgr_Set(m_pObj, 7, 0, (void*)lpCertKeyPassword, 0);
    }

    inline char* GetCertPrivateKey() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }


    inline int GetCertPrivateKeyAvailable() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }

    inline char* GetCertPrivateKeyContainer() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }


    inline char* GetCertPublicKey() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }


    inline char* GetCertPublicKeyAlgorithm() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetCertPublicKeyAlgorithm(const char *lpCertPublicKeyAlgorithm) {
      return IPWorks_CertMgr_Set(m_pObj, 12, 0, (void*)lpCertPublicKeyAlgorithm, 0);
    }

    inline int GetCertPublicKeyLength() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }

    inline char* GetCertSerialNumber() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }


    inline char* GetCertSignatureAlgorithm() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }


    inline char* GetCertSubject() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetCertSubject(const char *lpCertSubject) {
      return IPWorks_CertMgr_Set(m_pObj, 16, 0, (void*)lpCertSubject, 0);
    }

    inline char* GetCertSubjectAltNames() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }


    inline char* GetCertThumbprintMD5() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }


    inline char* GetCertThumbprintSHA1() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }


    inline char* GetCertThumbprintSHA256() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }


    inline char* GetCertUsage() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetCertUsage(const char *lpCertUsage) {
      return IPWorks_CertMgr_Set(m_pObj, 21, 0, (void*)lpCertUsage, 0);
    }

    inline int GetCertUsageFlags() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 22, 0, 0);
      return (int)(long)val;
    }
    inline int SetCertUsageFlags(int lCertUsageFlags) {
      void* val = (void*)IPW64CAST(lCertUsageFlags);
      return IPWorks_CertMgr_Set(m_pObj, 22, 0, val, 0);
    }
    inline char* GetCertVersion() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }


    inline int GetCertExtensionCount() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 24, 0, 0);
      return (int)(long)val;
    }
    inline int SetCertExtensionCount(int iCertExtensionCount) {
      void* val = (void*)IPW64CAST(iCertExtensionCount);
      return IPWorks_CertMgr_Set(m_pObj, 24, 0, val, 0);
    }
    inline int GetCertExtensionCritical(int iCertExtensionIndex) {
      void* val = IPWorks_CertMgr_Get(m_pObj, 25, iCertExtensionIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCertExtensionOID(int iCertExtensionIndex) {
      void* val = IPWorks_CertMgr_Get(m_pObj, 26, iCertExtensionIndex, 0);
      return (char*)val;
    }


    inline int GetCertExtensionValue(int iCertExtensionIndex, char *&lpCertExtensionValue, int &lenCertExtensionValue) {
      lpCertExtensionValue = (char*)IPWorks_CertMgr_Get(m_pObj, 27, iCertExtensionIndex, &lenCertExtensionValue);
      return lpCertExtensionValue ? 0 : lenCertExtensionValue;
    }


    inline int GetCertStore(char *&lpCertStore, int &lenCertStore) {
      lpCertStore = (char*)IPWorks_CertMgr_Get(m_pObj, 28, 0, &lenCertStore);
      return lpCertStore ? 0 : lenCertStore;
    }

    inline int SetCertStore(const char *lpCertStore, int lenCertStore) {
      return IPWorks_CertMgr_Set(m_pObj, 28, 0, (void*)lpCertStore, lenCertStore);
    }

    inline char* GetCertStorePassword() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 29, 0, 0);
      return (char*)val;
    }

    inline int SetCertStorePassword(const char *lpCertStorePassword) {
      return IPWorks_CertMgr_Set(m_pObj, 29, 0, (void*)lpCertStorePassword, 0);
    }

    inline int GetCertStoreType() {
      void* val = IPWorks_CertMgr_Get(m_pObj, 30, 0, 0);
      return (int)(long)val;
    }
    inline int SetCertStoreType(int iCertStoreType) {
      void* val = (void*)IPW64CAST(iCertStoreType);
      return IPWorks_CertMgr_Set(m_pObj, 30, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_CertMgr_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int CreateCertificate(const char* lpszCertSubject, int lSerialNumber) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCertSubject), (void*)IPW64CAST(lSerialNumber), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 3, 2, param, cbparam);
      
      
    }
    inline int CreateKey(const char* lpszKeyName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszKeyName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 4, 1, param, cbparam);
      
      
    }
    inline int DeleteCertificate() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CertMgr_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int DeleteKey(const char* lpszKeyName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszKeyName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 6, 1, param, cbparam);
      
      
    }
    inline int ExportCertificate(const char* lpszCertFile, const char* lpszPassword) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCertFile), (void*)IPW64CAST(lpszPassword), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 7, 2, param, cbparam);
      
      
    }
    inline char* GenerateCSR(const char* lpszCertSubject, const char* lpszKeyName) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCertSubject), (void*)IPW64CAST(lpszKeyName), 0};
      int cbparam[2+1] = {0, 0, 0};
      IPWorks_CertMgr_Do(m_pObj, 8, 2, param, cbparam);
      
      return (char*)IPW64CAST(param[2]);
    }
    inline int ImportCertificate(const char* lpszPFXFile, const char* lpszPassword, const char* lpszSubject) {
      void *param[3+1] = {(void*)IPW64CAST(lpszPFXFile), (void*)IPW64CAST(lpszPassword), (void*)IPW64CAST(lpszSubject), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 9, 3, param, cbparam);
      
      
    }
    inline int ImportSignedCSR(const char* lpSignedCSR, int lenSignedCSR, const char* lpszKeyName) {
      void *param[2+1] = {(void*)IPW64CAST(lpSignedCSR), (void*)IPW64CAST(lpszKeyName), 0};
      int cbparam[2+1] = {lenSignedCSR, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10, 2, param, cbparam);
      
      
    }
    inline int IssueCertificate(const char* lpszCertSubject, int lSerialNumber) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCertSubject), (void*)IPW64CAST(lSerialNumber), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 11, 2, param, cbparam);
      
      
    }
    inline char* ListCertificateStores() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 12, 0, param, cbparam);
      
      return (char*)IPW64CAST(param[0]);
    }
    inline char* ListKeys() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 13, 0, param, cbparam);
      
      return (char*)IPW64CAST(param[0]);
    }
    inline char* ListMachineStores() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 14, 0, param, cbparam);
      
      return (char*)IPW64CAST(param[0]);
    }
    inline char* ListStoreCertificates() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 15, 0, param, cbparam);
      
      return (char*)IPW64CAST(param[0]);
    }
    inline int ReadCertificate(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 16, 1, param, cbparam);
      
      
    }
    inline char* ReadCSR(const char* lpszCSR) {
      void *param[1+1] = {(void*)IPW64CAST(lpszCSR), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_CertMgr_Do(m_pObj, 17, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CertMgr_Do(m_pObj, 18, 0, param, cbparam);
      
      
    }
    inline int SaveCertificate(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 19, 1, param, cbparam);
      
      
    }
    inline char* ShowCertificateChain() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 20, 0, param, cbparam);
      
      return (char*)IPW64CAST(param[0]);
    }
    inline char* SignCSR(const char* lpCSR, int lenCSR, int lSerialNumber) {
      void *param[2+1] = {(void*)IPW64CAST(lpCSR), (void*)IPW64CAST(lSerialNumber), 0};
      int cbparam[2+1] = {lenCSR, 0, 0};
      IPWorks_CertMgr_Do(m_pObj, 21, 2, param, cbparam);
      
      return (char*)IPW64CAST(param[2]);
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR CertSerialNumber;
  int TrustStatus;
  int TrustInfo;
  int lenCertEncoded;
  int reserved;
} CertMgrCertChainEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR CertSerialNumber;
  int HasPrivateKey;
  int lenCertEncoded;
  int reserved;
} CertMgrCertListEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} CertMgrErrorEventParamsW;

typedef struct {
  LPWSTR KeyContainer;
  int KeyType;
  LPWSTR AlgId;
  int KeyLen;
  int reserved;
} CertMgrKeyListEventParamsW;

typedef struct {
  LPWSTR CertStore;
  int reserved;
} CertMgrStoreListEventParamsW;



class CertMgrW : public CertMgr {

  public: //properties
  
    inline LPWSTR GetCertEffectiveDate() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+1, 0, 0);
    }



    inline LPWSTR GetCertEncoded() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetCertEncoded(LPCWSTR lpCertEncoded) {
      return IPWorks_CertMgr_Set(m_pObj, 10000+2, 0, (void*)lpCertEncoded, 0);
    }
    inline int GetCertEncodedB(char *&lpCertEncoded, int &lenCertEncoded) {
      lpCertEncoded = (char*)IPWorks_CertMgr_Get(m_pObj, 2, 0, &lenCertEncoded);
      return lpCertEncoded ? 0 : lenCertEncoded;
    }
    inline int SetCertEncodedB(const char *lpCertEncoded, int lenCertEncoded) {
      return IPWorks_CertMgr_Set(m_pObj, 2, 0, (void*)lpCertEncoded, lenCertEncoded);
    }
    inline LPWSTR GetCertExpirationDate() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+3, 0, 0);
    }



    inline LPWSTR GetCertExtendedKeyUsage() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetCertExtendedKeyUsage(LPCWSTR lpCertExtendedKeyUsage) {
      return IPWorks_CertMgr_Set(m_pObj, 10000+4, 0, (void*)lpCertExtendedKeyUsage, 0);
    }

    inline LPWSTR GetCertFingerprint() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+5, 0, 0);
    }



    inline LPWSTR GetCertIssuer() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+6, 0, 0);
    }



    inline LPWSTR GetCertKeyPassword() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetCertKeyPassword(LPCWSTR lpCertKeyPassword) {
      return IPWorks_CertMgr_Set(m_pObj, 10000+7, 0, (void*)lpCertKeyPassword, 0);
    }

    inline LPWSTR GetCertPrivateKey() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+8, 0, 0);
    }





    inline LPWSTR GetCertPrivateKeyContainer() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+10, 0, 0);
    }



    inline LPWSTR GetCertPublicKey() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+11, 0, 0);
    }



    inline LPWSTR GetCertPublicKeyAlgorithm() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetCertPublicKeyAlgorithm(LPCWSTR lpCertPublicKeyAlgorithm) {
      return IPWorks_CertMgr_Set(m_pObj, 10000+12, 0, (void*)lpCertPublicKeyAlgorithm, 0);
    }



    inline LPWSTR GetCertSerialNumber() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+14, 0, 0);
    }



    inline LPWSTR GetCertSignatureAlgorithm() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+15, 0, 0);
    }



    inline LPWSTR GetCertSubject() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetCertSubject(LPCWSTR lpCertSubject) {
      return IPWorks_CertMgr_Set(m_pObj, 10000+16, 0, (void*)lpCertSubject, 0);
    }

    inline LPWSTR GetCertSubjectAltNames() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+17, 0, 0);
    }



    inline LPWSTR GetCertThumbprintMD5() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+18, 0, 0);
    }



    inline LPWSTR GetCertThumbprintSHA1() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+19, 0, 0);
    }



    inline LPWSTR GetCertThumbprintSHA256() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+20, 0, 0);
    }



    inline LPWSTR GetCertUsage() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+21, 0, 0);
    }

    inline int SetCertUsage(LPCWSTR lpCertUsage) {
      return IPWorks_CertMgr_Set(m_pObj, 10000+21, 0, (void*)lpCertUsage, 0);
    }



    inline LPWSTR GetCertVersion() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+23, 0, 0);
    }







    inline LPWSTR GetCertExtensionOID(int iCertExtensionIndex) {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+26, iCertExtensionIndex, 0);
    }



    inline LPWSTR GetCertExtensionValue(int iCertExtensionIndex) {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+27, iCertExtensionIndex, 0);
    }


    inline int GetCertExtensionValueB(int iCertExtensionIndex, char *&lpCertExtensionValue, int &lenCertExtensionValue) {
      lpCertExtensionValue = (char*)IPWorks_CertMgr_Get(m_pObj, 27, iCertExtensionIndex, &lenCertExtensionValue);
      return lpCertExtensionValue ? 0 : lenCertExtensionValue;
    }

    inline LPWSTR GetCertStore() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+28, 0, 0);
    }

    inline int SetCertStore(LPCWSTR lpCertStore) {
      return IPWorks_CertMgr_Set(m_pObj, 10000+28, 0, (void*)lpCertStore, 0);
    }
    inline int GetCertStoreB(char *&lpCertStore, int &lenCertStore) {
      lpCertStore = (char*)IPWorks_CertMgr_Get(m_pObj, 28, 0, &lenCertStore);
      return lpCertStore ? 0 : lenCertStore;
    }
    inline int SetCertStoreB(const char *lpCertStore, int lenCertStore) {
      return IPWorks_CertMgr_Set(m_pObj, 28, 0, (void*)lpCertStore, lenCertStore);
    }
    inline LPWSTR GetCertStorePassword() {
      return (LPWSTR)IPWorks_CertMgr_Get(m_pObj, 10000+29, 0, 0);
    }

    inline int SetCertStorePassword(LPCWSTR lpCertStorePassword) {
      return IPWorks_CertMgr_Set(m_pObj, 10000+29, 0, (void*)lpCertStorePassword, 0);
    }





  public: //events
  
    virtual int FireCertChain(CertMgrCertChainEventParamsW *e) {return 0;}
    virtual int FireCertList(CertMgrCertListEventParamsW *e) {return 0;}
    virtual int FireError(CertMgrErrorEventParamsW *e) {return 0;}
    virtual int FireKeyList(CertMgrKeyListEventParamsW *e) {return 0;}
    virtual int FireStoreList(CertMgrStoreListEventParamsW *e) {return 0;}


  protected:
  
    virtual int CertMgrEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            CertMgrCertChainEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireCertChain(&e);
            break;
         }
         case 2: {
            CertMgrCertListEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireCertList(&e);
            break;
         }
         case 3: {
            CertMgrErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 4: {
            CertMgrKeyListEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = FireKeyList(&e);
            break;
         }
         case 5: {
            CertMgrStoreListEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireStoreList(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireCertChain(CertMgrCertChainEventParams *e) {return -10000;}
    virtual int FireCertList(CertMgrCertListEventParams *e) {return -10000;}
    virtual int FireError(CertMgrErrorEventParams *e) {return -10000;}
    virtual int FireKeyList(CertMgrKeyListEventParams *e) {return -10000;}
    virtual int FireStoreList(CertMgrStoreListEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_CertMgr_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int CreateCertificate(LPWSTR lpszCertSubject, int lSerialNumber) {
      void *param[2+1] = {(void*)lpszCertSubject, (void*)lSerialNumber, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+3, 2, param, cbparam);
      
    }
    inline int CreateKey(LPWSTR lpszKeyName) {
      void *param[1+1] = {(void*)lpszKeyName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+4, 1, param, cbparam);
      
    }
    inline int DeleteCertificate() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int DeleteKey(LPWSTR lpszKeyName) {
      void *param[1+1] = {(void*)lpszKeyName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+6, 1, param, cbparam);
      
    }
    inline int ExportCertificate(LPWSTR lpszCertFile, LPWSTR lpszPassword) {
      void *param[2+1] = {(void*)lpszCertFile, (void*)lpszPassword, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+7, 2, param, cbparam);
      
    }
    inline LPWSTR GenerateCSR(LPWSTR lpszCertSubject, LPWSTR lpszKeyName) {
      void *param[2+1] = {(void*)lpszCertSubject, (void*)lpszKeyName, 0};
      int cbparam[2+1] = {0, 0, 0};
      IPWorks_CertMgr_Do(m_pObj, 10000+8, 2, param, cbparam);
      return (LPWSTR)IPW64CAST(param[2]);
    }
    inline int ImportCertificate(LPWSTR lpszPFXFile, LPWSTR lpszPassword, LPWSTR lpszSubject) {
      void *param[3+1] = {(void*)lpszPFXFile, (void*)lpszPassword, (void*)lpszSubject, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+9, 3, param, cbparam);
      
    }
    inline int ImportSignedCSR(LPWSTR lpSignedCSR, int lenSignedCSR, LPWSTR lpszKeyName) {
      void *param[2+1] = {(void*)lpSignedCSR, (void*)lpszKeyName, 0};
      int cbparam[2+1] = {lenSignedCSR, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+10, 2, param, cbparam);
      
    }
    inline int IssueCertificate(LPWSTR lpszCertSubject, int lSerialNumber) {
      void *param[2+1] = {(void*)lpszCertSubject, (void*)lSerialNumber, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+11, 2, param, cbparam);
      
    }
    inline LPWSTR ListCertificateStores() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 10000+12, 0, param, cbparam);
      return (LPWSTR)IPW64CAST(param[0]);
    }
    inline LPWSTR ListKeys() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 10000+13, 0, param, cbparam);
      return (LPWSTR)IPW64CAST(param[0]);
    }
    inline LPWSTR ListMachineStores() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 10000+14, 0, param, cbparam);
      return (LPWSTR)IPW64CAST(param[0]);
    }
    inline LPWSTR ListStoreCertificates() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 10000+15, 0, param, cbparam);
      return (LPWSTR)IPW64CAST(param[0]);
    }
    inline int ReadCertificate(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+16, 1, param, cbparam);
      
    }
    inline LPWSTR ReadCSR(LPWSTR lpszCSR) {
      void *param[1+1] = {(void*)lpszCSR, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_CertMgr_Do(m_pObj, 10000+17, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+18, 0, param, cbparam);
      
    }
    inline int SaveCertificate(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CertMgr_Do(m_pObj, 10000+19, 1, param, cbparam);
      
    }
    inline LPWSTR ShowCertificateChain() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CertMgr_Do(m_pObj, 10000+20, 0, param, cbparam);
      return (LPWSTR)IPW64CAST(param[0]);
    }
    inline LPWSTR SignCSR(LPWSTR lpCSR, int lenCSR, int lSerialNumber) {
      void *param[2+1] = {(void*)lpCSR, (void*)lSerialNumber, 0};
      int cbparam[2+1] = {lenCSR, 0, 0};
      IPWorks_CertMgr_Do(m_pObj, 10000+21, 2, param, cbparam);
      return (LPWSTR)IPW64CAST(param[2]);
    }

};

#endif //WIN32

#endif //_IPWORKS_CERTMGR_H_




