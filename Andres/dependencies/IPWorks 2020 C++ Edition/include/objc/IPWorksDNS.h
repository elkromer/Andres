
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//DNSPROTOCOL
#define PT_UDP                                             0
#define PT_TCP                                             1
#define PT_TLS                                             2
#define PT_HTTPS                                           3

//TQUERYTYPE
#define QT_ADDRESS                                         1
#define QT_NS                                              2
#define QT_MD                                              3
#define QT_MF                                              4
#define QT_CNAME                                           5
#define QT_SOA                                             6
#define QT_MAIL_BOX                                        7
#define QT_MAIL_GROUP                                      8
#define QT_MR                                              9
#define QT_NULL                                            10
#define QT_WKS                                             11
#define QT_POINTER                                         12
#define QT_HOST_INFO                                       13
#define QT_MAIL_INFO                                       14
#define QT_MX                                              15
#define QT_TEXT                                            16
#define QT_RP                                              17
#define QT_AFSDB                                           18
#define QT_X25                                             19
#define QT_ISDN                                            20
#define QT_RT                                              21
#define QT_AAAA                                            28
#define QT_SRV                                             33
#define QT_NAPTR                                           35
#define QT_CERT                                            37
#define QT_REV_LOOKUP                                      100

//DNSRECORDTYPES
#define RT_ADDRESS                                         1
#define RT_NS                                              2
#define RT_MD                                              3
#define RT_MF                                              4
#define RT_CNAME                                           5
#define RT_SOA                                             6
#define RT_MAIL_BOX                                        7
#define RT_MAIL_GROUP                                      8
#define RT_MR                                              9
#define RT_NULL                                            10
#define RT_WKS                                             11
#define RT_POINTER                                         12
#define RT_HOST_INFO                                       13
#define RT_MAIL_INFO                                       14
#define RT_MX                                              15
#define RT_TEXT                                            16
#define RT_RP                                              17
#define RT_AFSDB                                           18
#define RT_X25                                             19
#define RT_ISDN                                            20
#define RT_RT                                              21
#define RT_AAAA                                            28
#define RT_SRV                                             33
#define RT_NAPTR                                           35

//TRECORDSOURCE
#define RS_ANSWER_SECTION                                  0
#define RS_NAME_SERVER_SECTION                             1
#define RS_ADDITIONAL_RECORDS_SECTION                      2


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksDNSDelegate <NSObject>
@optional
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onResponse:(int)requestId :(NSString*)domain :(int)statusCode :(NSString*)description :(BOOL)authoritative NS_SWIFT_NAME(onResponse(_:_:_:_:_:));
- (void)onSSLServerAuthentication:(NSString*)remoteAddress :(int)remotePort :(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)remoteAddress :(int)remotePort :(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:_:_:));
@end

@interface IPWorksDNS : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksDNSDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasError;
  BOOL m_delegateHasResponse;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
}

+ (IPWorksDNS*)dns;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksDNSDelegate> delegate;
- (id <IPWorksDNSDelegate>)delegate;
- (void) setDelegate:(id <IPWorksDNSDelegate>)anObject;

  /* Events */

- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onResponse:(int)requestId :(NSString*)domain :(int)statusCode :(NSString*)description :(BOOL)authoritative NS_SWIFT_NAME(onResponse(_:_:_:_:_:));
- (void)onSSLServerAuthentication:(NSString*)remoteAddress :(int)remotePort :(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)remoteAddress :(int)remotePort :(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=DNSPort,setter=setDNSPort:) int DNSPort NS_SWIFT_NAME(DNSPort);
- (int)DNSPort NS_SWIFT_NAME(DNSPort());
- (void)setDNSPort:(int)newDNSPort NS_SWIFT_NAME(setDNSPort(_:));

@property (nonatomic,readwrite,assign,getter=DNSServer,setter=setDNSServer:) NSString* DNSServer NS_SWIFT_NAME(DNSServer);
- (NSString*)DNSServer NS_SWIFT_NAME(DNSServer());
- (void)setDNSServer:(NSString*)newDNSServer NS_SWIFT_NAME(setDNSServer(_:));

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=protocol,setter=setProtocol:) int protocol NS_SWIFT_NAME(protocol);
- (int)protocol NS_SWIFT_NAME(protocol());
- (int)protocol_ NS_SWIFT_NAME(protocol_());
- (void)setProtocol:(int)newProtocol NS_SWIFT_NAME(setProtocol(_:));
- (void)setProtocol_:(int)newProtocol NS_SWIFT_NAME(setProtocol_(_:));

@property (nonatomic,readwrite,assign,getter=queryType,setter=setQueryType:) int queryType NS_SWIFT_NAME(queryType);
- (int)queryType NS_SWIFT_NAME(queryType());
- (void)setQueryType:(int)newQueryType NS_SWIFT_NAME(setQueryType(_:));

@property (nonatomic,readonly,assign,getter=recordCount) int recordCount NS_SWIFT_NAME(recordCount);
- (int)recordCount NS_SWIFT_NAME(recordCount());

- (NSString*)recordDomain:(int)recordIndex NS_SWIFT_NAME(recordDomain(_:));

- (int)recordFieldCount:(int)recordIndex NS_SWIFT_NAME(recordFieldCount(_:));

- (int)recordFieldIndex:(int)recordIndex NS_SWIFT_NAME(recordFieldIndex(_:));
- (void)setRecordFieldIndex:(int)recordIndex:(int)newRecordFieldIndex NS_SWIFT_NAME(setRecordFieldIndex(_:_:));

- (NSString*)recordFieldName:(int)recordIndex NS_SWIFT_NAME(recordFieldName(_:));

- (NSString*)recordFieldValue:(int)recordIndex NS_SWIFT_NAME(recordFieldValue(_:));

- (NSData*)recordFieldValueB:(int)recordIndex NS_SWIFT_NAME(recordFieldValueB(_:));

- (NSString*)recordData:(int)recordIndex NS_SWIFT_NAME(recordData(_:));

- (NSData*)recordDataB:(int)recordIndex NS_SWIFT_NAME(recordDataB(_:));

- (int)recordType:(int)recordIndex NS_SWIFT_NAME(recordType(_:));

- (NSString*)recordTypeName:(int)recordIndex NS_SWIFT_NAME(recordTypeName(_:));

- (int)recordTTL:(int)recordIndex NS_SWIFT_NAME(recordTTL(_:));

@property (nonatomic,readwrite,assign,getter=recordSource,setter=setRecordSource:) int recordSource NS_SWIFT_NAME(recordSource);
- (int)recordSource NS_SWIFT_NAME(recordSource());
- (void)setRecordSource:(int)newRecordSource NS_SWIFT_NAME(setRecordSource(_:));

@property (nonatomic,readwrite,assign,getter=recursive,setter=setRecursive:) BOOL recursive NS_SWIFT_NAME(recursive);
- (BOOL)recursive NS_SWIFT_NAME(recursive());
- (void)setRecursive:(BOOL)newRecursive NS_SWIFT_NAME(setRecursive(_:));

@property (nonatomic,readwrite,assign,getter=requestId,setter=setRequestId:) int requestId NS_SWIFT_NAME(requestId);
- (int)requestId NS_SWIFT_NAME(requestId());
- (void)setRequestId:(int)newRequestId NS_SWIFT_NAME(setRequestId(_:));

@property (nonatomic,readonly,assign,getter=status) NSString* status NS_SWIFT_NAME(status);
- (NSString*)status NS_SWIFT_NAME(status());

@property (nonatomic,readonly,assign,getter=statusCode) int statusCode NS_SWIFT_NAME(statusCode);
- (int)statusCode NS_SWIFT_NAME(statusCode());

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (NSString*)getFieldValue:(int)recordIndex :(NSString*)fieldName NS_SWIFT_NAME(getFieldValue(_:_:));
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)query:(NSString*)domain NS_SWIFT_NAME(query(_:));
- (void)reset NS_SWIFT_NAME(reset());

@end


