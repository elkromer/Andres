
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//CERTSTORETYPES
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


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksCertMgrDelegate <NSObject>
@optional
- (void)onCertChain:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)certSerialNumber :(int)trustStatus :(int)trustInfo NS_SWIFT_NAME(onCertChain(_:_:_:_:_:_:));
- (void)onCertList:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)certSerialNumber :(BOOL)hasPrivateKey NS_SWIFT_NAME(onCertList(_:_:_:_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onKeyList:(NSString*)keyContainer :(int)keyType :(NSString*)algId :(int)keyLen NS_SWIFT_NAME(onKeyList(_:_:_:_:));
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType NS_SWIFT_NAME(onLog(_:_:_:));
- (void)onStoreList:(NSString*)certStore NS_SWIFT_NAME(onStoreList(_:));
@end

@interface IPWorksCertMgr : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksCertMgrDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasCertChain;
  BOOL m_delegateHasCertList;
  BOOL m_delegateHasError;
  BOOL m_delegateHasKeyList;
  BOOL m_delegateHasLog;
  BOOL m_delegateHasStoreList;
}

+ (IPWorksCertMgr*)certmgr;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksCertMgrDelegate> delegate;
- (id <IPWorksCertMgrDelegate>)delegate;
- (void) setDelegate:(id <IPWorksCertMgrDelegate>)anObject;

  /* Events */

- (void)onCertChain:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)certSerialNumber :(int)trustStatus :(int)trustInfo NS_SWIFT_NAME(onCertChain(_:_:_:_:_:_:));
- (void)onCertList:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)certSerialNumber :(BOOL)hasPrivateKey NS_SWIFT_NAME(onCertList(_:_:_:_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onKeyList:(NSString*)keyContainer :(int)keyType :(NSString*)algId :(int)keyLen NS_SWIFT_NAME(onKeyList(_:_:_:_:));
- (void)onLog:(int)logLevel :(NSString*)message :(NSString*)logType NS_SWIFT_NAME(onLog(_:_:_:));
- (void)onStoreList:(NSString*)certStore NS_SWIFT_NAME(onStoreList(_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readonly,assign,getter=certEffectiveDate) NSString* certEffectiveDate NS_SWIFT_NAME(certEffectiveDate);
- (NSString*)certEffectiveDate NS_SWIFT_NAME(certEffectiveDate());

@property (nonatomic,readwrite,assign,getter=certEncoded,setter=setCertEncoded:) NSString* certEncoded NS_SWIFT_NAME(certEncoded);
- (NSString*)certEncoded NS_SWIFT_NAME(certEncoded());
- (void)setCertEncoded:(NSString*)newCertEncoded NS_SWIFT_NAME(setCertEncoded(_:));

@property (nonatomic,readwrite,assign,getter=certEncodedB,setter=setCertEncodedB:) NSData* certEncodedB NS_SWIFT_NAME(certEncodedB);
- (NSData*)certEncodedB NS_SWIFT_NAME(certEncodedB());
- (void)setCertEncodedB :(NSData*)newCertEncoded NS_SWIFT_NAME(setCertEncodedB(_:));

@property (nonatomic,readonly,assign,getter=certExpirationDate) NSString* certExpirationDate NS_SWIFT_NAME(certExpirationDate);
- (NSString*)certExpirationDate NS_SWIFT_NAME(certExpirationDate());

@property (nonatomic,readwrite,assign,getter=certExtendedKeyUsage,setter=setCertExtendedKeyUsage:) NSString* certExtendedKeyUsage NS_SWIFT_NAME(certExtendedKeyUsage);
- (NSString*)certExtendedKeyUsage NS_SWIFT_NAME(certExtendedKeyUsage());
- (void)setCertExtendedKeyUsage:(NSString*)newCertExtendedKeyUsage NS_SWIFT_NAME(setCertExtendedKeyUsage(_:));

@property (nonatomic,readonly,assign,getter=certFingerprint) NSString* certFingerprint NS_SWIFT_NAME(certFingerprint);
- (NSString*)certFingerprint NS_SWIFT_NAME(certFingerprint());

@property (nonatomic,readonly,assign,getter=certIssuer) NSString* certIssuer NS_SWIFT_NAME(certIssuer);
- (NSString*)certIssuer NS_SWIFT_NAME(certIssuer());

@property (nonatomic,readwrite,assign,getter=certKeyPassword,setter=setCertKeyPassword:) NSString* certKeyPassword NS_SWIFT_NAME(certKeyPassword);
- (NSString*)certKeyPassword NS_SWIFT_NAME(certKeyPassword());
- (void)setCertKeyPassword:(NSString*)newCertKeyPassword NS_SWIFT_NAME(setCertKeyPassword(_:));

@property (nonatomic,readonly,assign,getter=certPrivateKey) NSString* certPrivateKey NS_SWIFT_NAME(certPrivateKey);
- (NSString*)certPrivateKey NS_SWIFT_NAME(certPrivateKey());

@property (nonatomic,readonly,assign,getter=certPrivateKeyAvailable) BOOL certPrivateKeyAvailable NS_SWIFT_NAME(certPrivateKeyAvailable);
- (BOOL)certPrivateKeyAvailable NS_SWIFT_NAME(certPrivateKeyAvailable());

@property (nonatomic,readonly,assign,getter=certPrivateKeyContainer) NSString* certPrivateKeyContainer NS_SWIFT_NAME(certPrivateKeyContainer);
- (NSString*)certPrivateKeyContainer NS_SWIFT_NAME(certPrivateKeyContainer());

@property (nonatomic,readonly,assign,getter=certPublicKey) NSString* certPublicKey NS_SWIFT_NAME(certPublicKey);
- (NSString*)certPublicKey NS_SWIFT_NAME(certPublicKey());

@property (nonatomic,readwrite,assign,getter=certPublicKeyAlgorithm,setter=setCertPublicKeyAlgorithm:) NSString* certPublicKeyAlgorithm NS_SWIFT_NAME(certPublicKeyAlgorithm);
- (NSString*)certPublicKeyAlgorithm NS_SWIFT_NAME(certPublicKeyAlgorithm());
- (void)setCertPublicKeyAlgorithm:(NSString*)newCertPublicKeyAlgorithm NS_SWIFT_NAME(setCertPublicKeyAlgorithm(_:));

@property (nonatomic,readonly,assign,getter=certPublicKeyLength) int certPublicKeyLength NS_SWIFT_NAME(certPublicKeyLength);
- (int)certPublicKeyLength NS_SWIFT_NAME(certPublicKeyLength());

@property (nonatomic,readonly,assign,getter=certSerialNumber) NSString* certSerialNumber NS_SWIFT_NAME(certSerialNumber);
- (NSString*)certSerialNumber NS_SWIFT_NAME(certSerialNumber());

@property (nonatomic,readonly,assign,getter=certSignatureAlgorithm) NSString* certSignatureAlgorithm NS_SWIFT_NAME(certSignatureAlgorithm);
- (NSString*)certSignatureAlgorithm NS_SWIFT_NAME(certSignatureAlgorithm());

@property (nonatomic,readwrite,assign,getter=certSubject,setter=setCertSubject:) NSString* certSubject NS_SWIFT_NAME(certSubject);
- (NSString*)certSubject NS_SWIFT_NAME(certSubject());
- (void)setCertSubject:(NSString*)newCertSubject NS_SWIFT_NAME(setCertSubject(_:));

@property (nonatomic,readonly,assign,getter=certSubjectAltNames) NSString* certSubjectAltNames NS_SWIFT_NAME(certSubjectAltNames);
- (NSString*)certSubjectAltNames NS_SWIFT_NAME(certSubjectAltNames());

@property (nonatomic,readonly,assign,getter=certThumbprintMD5) NSString* certThumbprintMD5 NS_SWIFT_NAME(certThumbprintMD5);
- (NSString*)certThumbprintMD5 NS_SWIFT_NAME(certThumbprintMD5());

@property (nonatomic,readonly,assign,getter=certThumbprintSHA1) NSString* certThumbprintSHA1 NS_SWIFT_NAME(certThumbprintSHA1);
- (NSString*)certThumbprintSHA1 NS_SWIFT_NAME(certThumbprintSHA1());

@property (nonatomic,readonly,assign,getter=certThumbprintSHA256) NSString* certThumbprintSHA256 NS_SWIFT_NAME(certThumbprintSHA256);
- (NSString*)certThumbprintSHA256 NS_SWIFT_NAME(certThumbprintSHA256());

@property (nonatomic,readwrite,assign,getter=certUsage,setter=setCertUsage:) NSString* certUsage NS_SWIFT_NAME(certUsage);
- (NSString*)certUsage NS_SWIFT_NAME(certUsage());
- (void)setCertUsage:(NSString*)newCertUsage NS_SWIFT_NAME(setCertUsage(_:));

@property (nonatomic,readwrite,assign,getter=certUsageFlags,setter=setCertUsageFlags:) int certUsageFlags NS_SWIFT_NAME(certUsageFlags);
- (int)certUsageFlags NS_SWIFT_NAME(certUsageFlags());
- (void)setCertUsageFlags:(int)newCertUsageFlags NS_SWIFT_NAME(setCertUsageFlags(_:));

@property (nonatomic,readonly,assign,getter=certVersion) NSString* certVersion NS_SWIFT_NAME(certVersion);
- (NSString*)certVersion NS_SWIFT_NAME(certVersion());

@property (nonatomic,readwrite,assign,getter=certExtensionCount,setter=setCertExtensionCount:) int certExtensionCount NS_SWIFT_NAME(certExtensionCount);
- (int)certExtensionCount NS_SWIFT_NAME(certExtensionCount());
- (void)setCertExtensionCount:(int)newCertExtensionCount NS_SWIFT_NAME(setCertExtensionCount(_:));

- (BOOL)certExtensionCritical:(int)certExtensionIndex NS_SWIFT_NAME(certExtensionCritical(_:));

- (NSString*)certExtensionOID:(int)certExtensionIndex NS_SWIFT_NAME(certExtensionOID(_:));

- (NSString*)certExtensionValue:(int)certExtensionIndex NS_SWIFT_NAME(certExtensionValue(_:));

- (NSData*)certExtensionValueB:(int)certExtensionIndex NS_SWIFT_NAME(certExtensionValueB(_:));

@property (nonatomic,readwrite,assign,getter=certStore,setter=setCertStore:) NSString* certStore NS_SWIFT_NAME(certStore);
- (NSString*)certStore NS_SWIFT_NAME(certStore());
- (void)setCertStore:(NSString*)newCertStore NS_SWIFT_NAME(setCertStore(_:));

@property (nonatomic,readwrite,assign,getter=certStoreB,setter=setCertStoreB:) NSData* certStoreB NS_SWIFT_NAME(certStoreB);
- (NSData*)certStoreB NS_SWIFT_NAME(certStoreB());
- (void)setCertStoreB :(NSData*)newCertStore NS_SWIFT_NAME(setCertStoreB(_:));

@property (nonatomic,readwrite,assign,getter=certStorePassword,setter=setCertStorePassword:) NSString* certStorePassword NS_SWIFT_NAME(certStorePassword);
- (NSString*)certStorePassword NS_SWIFT_NAME(certStorePassword());
- (void)setCertStorePassword:(NSString*)newCertStorePassword NS_SWIFT_NAME(setCertStorePassword(_:));

@property (nonatomic,readwrite,assign,getter=certStoreType,setter=setCertStoreType:) int certStoreType NS_SWIFT_NAME(certStoreType);
- (int)certStoreType NS_SWIFT_NAME(certStoreType());
- (void)setCertStoreType:(int)newCertStoreType NS_SWIFT_NAME(setCertStoreType(_:));

@property (nonatomic,readonly,assign,getter=exportedCert) NSString* exportedCert NS_SWIFT_NAME(exportedCert);
- (NSString*)exportedCert NS_SWIFT_NAME(exportedCert());

@property (nonatomic,readonly,assign,getter=exportedCertB) NSData* exportedCertB NS_SWIFT_NAME(exportedCertB);
- (NSData*)exportedCertB NS_SWIFT_NAME(exportedCertB());

@property (nonatomic,readwrite,assign,getter=exportFormat,setter=setExportFormat:) NSString* exportFormat NS_SWIFT_NAME(exportFormat);
- (NSString*)exportFormat NS_SWIFT_NAME(exportFormat());
- (void)setExportFormat:(NSString*)newExportFormat NS_SWIFT_NAME(setExportFormat(_:));

@property (nonatomic,readwrite,assign,getter=exportPrivateKey,setter=setExportPrivateKey:) BOOL exportPrivateKey NS_SWIFT_NAME(exportPrivateKey);
- (BOOL)exportPrivateKey NS_SWIFT_NAME(exportPrivateKey());
- (void)setExportPrivateKey:(BOOL)newExportPrivateKey NS_SWIFT_NAME(setExportPrivateKey(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)createCertificate:(NSString*)certSubject :(int)serialNumber NS_SWIFT_NAME(createCertificate(_:_:));
- (void)createKey:(NSString*)keyName NS_SWIFT_NAME(createKey(_:));
- (void)deleteCertificate NS_SWIFT_NAME(deleteCertificate());
- (void)deleteKey:(NSString*)keyName NS_SWIFT_NAME(deleteKey(_:));
- (void)exportCertificate:(NSString*)certFile :(NSString*)password NS_SWIFT_NAME(exportCertificate(_:_:));
- (NSString*)generateCSR:(NSString*)certSubject :(NSString*)keyName NS_SWIFT_NAME(generateCSR(_:_:));
- (void)importCertificate:(NSString*)certFile :(NSString*)password :(NSString*)subject NS_SWIFT_NAME(importCertificate(_:_:_:));
- (void)importSignedCSR:(NSData*)signedCSR :(NSString*)keyName NS_SWIFT_NAME(importSignedCSR(_:_:));
- (void)issueCertificate:(NSString*)certSubject :(int)serialNumber NS_SWIFT_NAME(issueCertificate(_:_:));
- (NSString*)listCertificateStores NS_SWIFT_NAME(listCertificateStores());
- (NSString*)listKeys NS_SWIFT_NAME(listKeys());
- (NSString*)listMachineStores NS_SWIFT_NAME(listMachineStores());
- (NSString*)listStoreCertificates NS_SWIFT_NAME(listStoreCertificates());
- (void)readCertificate:(NSString*)fileName NS_SWIFT_NAME(readCertificate(_:));
- (NSString*)readCSR:(NSString*)CSR NS_SWIFT_NAME(readCSR(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)saveCertificate:(NSString*)fileName NS_SWIFT_NAME(saveCertificate(_:));
- (NSString*)showCertificateChain NS_SWIFT_NAME(showCertificateChain());
- (NSString*)signCSR:(NSData*)CSR :(int)serialNumber NS_SWIFT_NAME(signCSR(_:_:));

@end


