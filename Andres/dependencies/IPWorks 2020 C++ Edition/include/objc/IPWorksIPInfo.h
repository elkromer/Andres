
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksIPInfoDelegate <NSObject>
@optional
- (void)onDNSCacheEntry:(NSString*)recordName :(int)recordType :(int)timeToLive :(int)dataLength :(NSString*)section :(NSString*)recordValue :(NSString*)recordInfo NS_SWIFT_NAME(onDNSCacheEntry(_:_:_:_:_:_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onRequestComplete:(int)requestId :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onRequestComplete(_:_:_:));
@end

@interface IPWorksIPInfo : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksIPInfoDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasDNSCacheEntry;
  BOOL m_delegateHasError;
  BOOL m_delegateHasRequestComplete;
}

+ (IPWorksIPInfo*)ipinfo;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksIPInfoDelegate> delegate;
- (id <IPWorksIPInfoDelegate>)delegate;
- (void) setDelegate:(id <IPWorksIPInfoDelegate>)anObject;

  /* Events */

- (void)onDNSCacheEntry:(NSString*)recordName :(int)recordType :(int)timeToLive :(int)dataLength :(NSString*)section :(NSString*)recordValue :(NSString*)recordInfo NS_SWIFT_NAME(onDNSCacheEntry(_:_:_:_:_:_:_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onRequestComplete:(int)requestId :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onRequestComplete(_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readonly,assign,getter=adapterBroadcastAddress) NSString* adapterBroadcastAddress NS_SWIFT_NAME(adapterBroadcastAddress);
- (NSString*)adapterBroadcastAddress NS_SWIFT_NAME(adapterBroadcastAddress());

@property (nonatomic,readonly,assign,getter=adapterCount) int adapterCount NS_SWIFT_NAME(adapterCount);
- (int)adapterCount NS_SWIFT_NAME(adapterCount());

@property (nonatomic,readonly,assign,getter=adapterDescription) NSString* adapterDescription NS_SWIFT_NAME(adapterDescription);
- (NSString*)adapterDescription NS_SWIFT_NAME(adapterDescription());

@property (nonatomic,readonly,assign,getter=adapterDeviceIndex) int adapterDeviceIndex NS_SWIFT_NAME(adapterDeviceIndex);
- (int)adapterDeviceIndex NS_SWIFT_NAME(adapterDeviceIndex());

@property (nonatomic,readonly,assign,getter=adapterDHCPEnabled) BOOL adapterDHCPEnabled NS_SWIFT_NAME(adapterDHCPEnabled);
- (BOOL)adapterDHCPEnabled NS_SWIFT_NAME(adapterDHCPEnabled());

@property (nonatomic,readonly,assign,getter=adapterDHCPServer) NSString* adapterDHCPServer NS_SWIFT_NAME(adapterDHCPServer);
- (NSString*)adapterDHCPServer NS_SWIFT_NAME(adapterDHCPServer());

@property (nonatomic,readonly,assign,getter=adapterDNSServers) NSString* adapterDNSServers NS_SWIFT_NAME(adapterDNSServers);
- (NSString*)adapterDNSServers NS_SWIFT_NAME(adapterDNSServers());

@property (nonatomic,readonly,assign,getter=adapterGateway) NSString* adapterGateway NS_SWIFT_NAME(adapterGateway);
- (NSString*)adapterGateway NS_SWIFT_NAME(adapterGateway());

@property (nonatomic,readwrite,assign,getter=adapterIndex,setter=setAdapterIndex:) int adapterIndex NS_SWIFT_NAME(adapterIndex);
- (int)adapterIndex NS_SWIFT_NAME(adapterIndex());
- (void)setAdapterIndex:(int)newAdapterIndex NS_SWIFT_NAME(setAdapterIndex(_:));

@property (nonatomic,readonly,assign,getter=adapterIPAddress) NSString* adapterIPAddress NS_SWIFT_NAME(adapterIPAddress);
- (NSString*)adapterIPAddress NS_SWIFT_NAME(adapterIPAddress());

@property (nonatomic,readonly,assign,getter=adapterIPv6Address) NSString* adapterIPv6Address NS_SWIFT_NAME(adapterIPv6Address);
- (NSString*)adapterIPv6Address NS_SWIFT_NAME(adapterIPv6Address());

@property (nonatomic,readonly,assign,getter=adapterIPv6LinkLocalAddress) NSString* adapterIPv6LinkLocalAddress NS_SWIFT_NAME(adapterIPv6LinkLocalAddress);
- (NSString*)adapterIPv6LinkLocalAddress NS_SWIFT_NAME(adapterIPv6LinkLocalAddress());

@property (nonatomic,readonly,assign,getter=adapterLeaseExpires) NSString* adapterLeaseExpires NS_SWIFT_NAME(adapterLeaseExpires);
- (NSString*)adapterLeaseExpires NS_SWIFT_NAME(adapterLeaseExpires());

@property (nonatomic,readonly,assign,getter=adapterLeaseObtained) NSString* adapterLeaseObtained NS_SWIFT_NAME(adapterLeaseObtained);
- (NSString*)adapterLeaseObtained NS_SWIFT_NAME(adapterLeaseObtained());

@property (nonatomic,readonly,assign,getter=adapterName) NSString* adapterName NS_SWIFT_NAME(adapterName);
- (NSString*)adapterName NS_SWIFT_NAME(adapterName());

@property (nonatomic,readonly,assign,getter=adapterOtherIPAddresses) NSString* adapterOtherIPAddresses NS_SWIFT_NAME(adapterOtherIPAddresses);
- (NSString*)adapterOtherIPAddresses NS_SWIFT_NAME(adapterOtherIPAddresses());

@property (nonatomic,readonly,assign,getter=adapterPhysicalAddress) NSString* adapterPhysicalAddress NS_SWIFT_NAME(adapterPhysicalAddress);
- (NSString*)adapterPhysicalAddress NS_SWIFT_NAME(adapterPhysicalAddress());

@property (nonatomic,readonly,assign,getter=adapterPrimaryWINSServer) NSString* adapterPrimaryWINSServer NS_SWIFT_NAME(adapterPrimaryWINSServer);
- (NSString*)adapterPrimaryWINSServer NS_SWIFT_NAME(adapterPrimaryWINSServer());

@property (nonatomic,readonly,assign,getter=adapterSecondaryWINSServer) NSString* adapterSecondaryWINSServer NS_SWIFT_NAME(adapterSecondaryWINSServer);
- (NSString*)adapterSecondaryWINSServer NS_SWIFT_NAME(adapterSecondaryWINSServer());

@property (nonatomic,readonly,assign,getter=adapterStatus) NSString* adapterStatus NS_SWIFT_NAME(adapterStatus);
- (NSString*)adapterStatus NS_SWIFT_NAME(adapterStatus());

@property (nonatomic,readonly,assign,getter=adapterSubnetMask) NSString* adapterSubnetMask NS_SWIFT_NAME(adapterSubnetMask);
- (NSString*)adapterSubnetMask NS_SWIFT_NAME(adapterSubnetMask());

@property (nonatomic,readonly,assign,getter=adapterType) NSString* adapterType NS_SWIFT_NAME(adapterType);
- (NSString*)adapterType NS_SWIFT_NAME(adapterType());

@property (nonatomic,readonly,assign,getter=adapterUsesWINS) BOOL adapterUsesWINS NS_SWIFT_NAME(adapterUsesWINS);
- (BOOL)adapterUsesWINS NS_SWIFT_NAME(adapterUsesWINS());

@property (nonatomic,readonly,assign,getter=adapterZoneId) int adapterZoneId NS_SWIFT_NAME(adapterZoneId);
- (int)adapterZoneId NS_SWIFT_NAME(adapterZoneId());

@property (nonatomic,readonly,assign,getter=ARPProxy) BOOL ARPProxy NS_SWIFT_NAME(ARPProxy);
- (BOOL)ARPProxy NS_SWIFT_NAME(ARPProxy());

@property (nonatomic,readonly,assign,getter=DHCPScope) NSString* DHCPScope NS_SWIFT_NAME(DHCPScope);
- (NSString*)DHCPScope NS_SWIFT_NAME(DHCPScope());

@property (nonatomic,readonly,assign,getter=DNSEnabled) BOOL DNSEnabled NS_SWIFT_NAME(DNSEnabled);
- (BOOL)DNSEnabled NS_SWIFT_NAME(DNSEnabled());

@property (nonatomic,readonly,assign,getter=DNSServer) NSString* DNSServer NS_SWIFT_NAME(DNSServer);
- (NSString*)DNSServer NS_SWIFT_NAME(DNSServer());

@property (nonatomic,readonly,assign,getter=domainName) NSString* domainName NS_SWIFT_NAME(domainName);
- (NSString*)domainName NS_SWIFT_NAME(domainName());

@property (nonatomic,readwrite,assign,getter=hostAddress,setter=setHostAddress:) NSString* hostAddress NS_SWIFT_NAME(hostAddress);
- (NSString*)hostAddress NS_SWIFT_NAME(hostAddress());
- (void)setHostAddress:(NSString*)newHostAddress NS_SWIFT_NAME(setHostAddress(_:));

@property (nonatomic,readonly,assign,getter=hostAliases) NSString* hostAliases NS_SWIFT_NAME(hostAliases);
- (NSString*)hostAliases NS_SWIFT_NAME(hostAliases());

@property (nonatomic,readwrite,assign,getter=hostName,setter=setHostName:) NSString* hostName NS_SWIFT_NAME(hostName);
- (NSString*)hostName NS_SWIFT_NAME(hostName());
- (void)setHostName:(NSString*)newHostName NS_SWIFT_NAME(setHostName(_:));

@property (nonatomic,readonly,assign,getter=localHost) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());

@property (nonatomic,readonly,assign,getter=nodeType) NSString* nodeType NS_SWIFT_NAME(nodeType);
- (NSString*)nodeType NS_SWIFT_NAME(nodeType());

@property (nonatomic,readonly,assign,getter=otherAddresses) NSString* otherAddresses NS_SWIFT_NAME(otherAddresses);
- (NSString*)otherAddresses NS_SWIFT_NAME(otherAddresses());

@property (nonatomic,readonly,assign,getter=otherDNSServers) NSString* otherDNSServers NS_SWIFT_NAME(otherDNSServers);
- (NSString*)otherDNSServers NS_SWIFT_NAME(otherDNSServers());

@property (nonatomic,readwrite,assign,getter=pendingRequests,setter=setPendingRequests:) int pendingRequests NS_SWIFT_NAME(pendingRequests);
- (int)pendingRequests NS_SWIFT_NAME(pendingRequests());
- (void)setPendingRequests:(int)newPendingRequests NS_SWIFT_NAME(setPendingRequests(_:));

@property (nonatomic,readonly,assign,getter=requestId) int requestId NS_SWIFT_NAME(requestId);
- (int)requestId NS_SWIFT_NAME(requestId());

@property (nonatomic,readonly,assign,getter=routingEnabled) BOOL routingEnabled NS_SWIFT_NAME(routingEnabled);
- (BOOL)routingEnabled NS_SWIFT_NAME(routingEnabled());

@property (nonatomic,readonly,assign,getter=serviceAliases) NSString* serviceAliases NS_SWIFT_NAME(serviceAliases);
- (NSString*)serviceAliases NS_SWIFT_NAME(serviceAliases());

@property (nonatomic,readwrite,assign,getter=serviceName,setter=setServiceName:) NSString* serviceName NS_SWIFT_NAME(serviceName);
- (NSString*)serviceName NS_SWIFT_NAME(serviceName());
- (void)setServiceName:(NSString*)newServiceName NS_SWIFT_NAME(setServiceName(_:));

@property (nonatomic,readwrite,assign,getter=servicePort,setter=setServicePort:) int servicePort NS_SWIFT_NAME(servicePort);
- (int)servicePort NS_SWIFT_NAME(servicePort());
- (void)setServicePort:(int)newServicePort NS_SWIFT_NAME(setServicePort(_:));

@property (nonatomic,readwrite,assign,getter=serviceProtocol,setter=setServiceProtocol:) NSString* serviceProtocol NS_SWIFT_NAME(serviceProtocol);
- (NSString*)serviceProtocol NS_SWIFT_NAME(serviceProtocol());
- (void)setServiceProtocol:(NSString*)newServiceProtocol NS_SWIFT_NAME(setServiceProtocol(_:));

  /* Methods */

- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)DHCPRelease NS_SWIFT_NAME(DHCPRelease());
- (void)DHCPRenew NS_SWIFT_NAME(DHCPRenew());
- (NSString*)displayDNSCache NS_SWIFT_NAME(displayDNSCache());
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (BOOL)flushDNSCache NS_SWIFT_NAME(flushDNSCache());
- (NSString*)getMAC:(NSString*)IPAddress NS_SWIFT_NAME(getMAC(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (NSString*)resolveAddress:(NSString*)hostAddress NS_SWIFT_NAME(resolveAddress(_:));
- (NSString*)resolveName:(NSString*)hostName NS_SWIFT_NAME(resolveName(_:));

@end


