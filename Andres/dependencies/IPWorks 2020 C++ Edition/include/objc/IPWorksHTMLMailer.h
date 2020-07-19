
/******************************************************************
   IPWorks 2020 for macOS and iOS
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#import <Foundation/Foundation.h>

//AUTHMECHANISMS
#define AM_USER_PASSWORD                                   0
#define AM_CRAMMD5                                         1
#define AM_NTLM                                            2
#define AM_APOP                                            3
#define AM_SASLPLAIN                                       4
#define AM_SASLDIGEST_MD5                                  5
#define AM_KERBEROS                                        6
#define AM_XOAUTH2                                         7

//FIREWALLTYPES
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TIMPORTANCE
#define MI_UNSPECIFIED                                     0
#define MI_HIGH                                            1
#define MI_NORMAL                                          2
#define MI_LOW                                             3

//EMAILRECIPIENTTYPES
#define RT_TO                                              0
#define RT_CC                                              1
#define RT_BCC                                             2

//TPRIORITY
#define EP_UNSPECIFIED                                     0
#define EP_NORMAL                                          1
#define EP_URGENT                                          2
#define EP_NON_URGENT                                      3

//TSENSITIVITY
#define ES_UNSPECIFIED                                     0
#define ES_PERSONAL                                        1
#define ES_PRIVATE                                         2
#define ES_COMPANY_CONFIDENTIAL                            3

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

//TSSLSTARTMODE
#define SSL_AUTOMATIC                                      0
#define SSL_IMPLICIT                                       1
#define SSL_EXPLICIT                                       2
#define SSL_NONE                                           3


#ifndef NS_SWIFT_NAME
#define NS_SWIFT_NAME(x)
#endif

@protocol IPWorksHTMLMailerDelegate <NSObject>
@optional
- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onPITrail:(int)direction :(NSString*)message NS_SWIFT_NAME(onPITrail(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone NS_SWIFT_NAME(onTransfer(_:_:_:));
@end

@interface IPWorksHTMLMailer : NSObject {
  @public void* m_pObj;
  @public CFMutableArrayRef m_rNotifiers;
  __unsafe_unretained id <IPWorksHTMLMailerDelegate> m_delegate;
  BOOL m_raiseNSException;
  BOOL m_delegateHasConnectionStatus;
  BOOL m_delegateHasEndTransfer;
  BOOL m_delegateHasError;
  BOOL m_delegateHasPITrail;
  BOOL m_delegateHasSSLServerAuthentication;
  BOOL m_delegateHasSSLStatus;
  BOOL m_delegateHasStartTransfer;
  BOOL m_delegateHasTransfer;
}

+ (IPWorksHTMLMailer*)htmlmailer;

- (id)init;
- (void)dealloc;

- (NSString*)lastError;
- (int)lastErrorCode;
- (int)eventErrorCode;

@property (nonatomic,readwrite,assign,getter=delegate,setter=setDelegate:) id <IPWorksHTMLMailerDelegate> delegate;
- (id <IPWorksHTMLMailerDelegate>)delegate;
- (void) setDelegate:(id <IPWorksHTMLMailerDelegate>)anObject;

  /* Events */

- (void)onConnectionStatus:(NSString*)connectionEvent :(int)statusCode :(NSString*)description NS_SWIFT_NAME(onConnectionStatus(_:_:_:));
- (void)onEndTransfer:(int)direction NS_SWIFT_NAME(onEndTransfer(_:));
- (void)onError:(int)errorCode :(NSString*)description NS_SWIFT_NAME(onError(_:_:));
- (void)onPITrail:(int)direction :(NSString*)message NS_SWIFT_NAME(onPITrail(_:_:));
- (void)onSSLServerAuthentication:(NSData*)certEncoded :(NSString*)certSubject :(NSString*)certIssuer :(NSString*)status :(int*)accept NS_SWIFT_NAME(onSSLServerAuthentication(_:_:_:_:_:));
- (void)onSSLStatus:(NSString*)message NS_SWIFT_NAME(onSSLStatus(_:));
- (void)onStartTransfer:(int)direction NS_SWIFT_NAME(onStartTransfer(_:));
- (void)onTransfer:(int)direction :(long long)bytesTransferred :(int)percentDone NS_SWIFT_NAME(onTransfer(_:_:_:));

  /* Properties */

@property (nonatomic,readwrite,assign,getter=RuntimeLicense,setter=setRuntimeLicense:) NSString* RuntimeLicense NS_SWIFT_NAME(RuntimeLicense);
- (NSString*)RuntimeLicense;
- (void)setRuntimeLicense:(NSString*)newRuntimeLicense;

@property (nonatomic,readonly,assign,getter=VERSION) NSString* VERSION NS_SWIFT_NAME(VERSION);
- (NSString*)VERSION;

@property (nonatomic,readwrite,assign,getter=raiseNSException,setter=setRaiseNSException:) BOOL raiseNSException NS_SWIFT_NAME(raiseNSException);
- (BOOL)raiseNSException NS_SWIFT_NAME(raiseNSException());
- (void)setRaiseNSException:(BOOL)newRaiseNSException NS_SWIFT_NAME(setRaiseNSException(_:));

@property (nonatomic,readwrite,assign,getter=attachmentCount,setter=setAttachmentCount:) int attachmentCount NS_SWIFT_NAME(attachmentCount);
- (int)attachmentCount NS_SWIFT_NAME(attachmentCount());
- (void)setAttachmentCount:(int)newAttachmentCount NS_SWIFT_NAME(setAttachmentCount(_:));

- (NSString*)attachmentFile:(int)attachmentIndex NS_SWIFT_NAME(attachmentFile(_:));
- (void)setAttachmentFile:(int)attachmentIndex:(NSString*)newAttachmentFile NS_SWIFT_NAME(setAttachmentFile(_:_:));

- (NSString*)attachmentName:(int)attachmentIndex NS_SWIFT_NAME(attachmentName(_:));
- (void)setAttachmentName:(int)attachmentIndex:(NSString*)newAttachmentName NS_SWIFT_NAME(setAttachmentName(_:_:));

@property (nonatomic,readwrite,assign,getter=authMechanism,setter=setAuthMechanism:) int authMechanism NS_SWIFT_NAME(authMechanism);
- (int)authMechanism NS_SWIFT_NAME(authMechanism());
- (void)setAuthMechanism:(int)newAuthMechanism NS_SWIFT_NAME(setAuthMechanism(_:));

@property (nonatomic,readwrite,assign,getter=BCc,setter=setBCc:) NSString* BCc NS_SWIFT_NAME(BCc);
- (NSString*)BCc NS_SWIFT_NAME(BCc());
- (void)setBCc:(NSString*)newBCc NS_SWIFT_NAME(setBCc(_:));

@property (nonatomic,readwrite,assign,getter=cc,setter=setCc:) NSString* cc NS_SWIFT_NAME(cc);
- (NSString*)cc NS_SWIFT_NAME(cc());
- (void)setCc:(NSString*)newCc NS_SWIFT_NAME(setCc(_:));

@property (nonatomic,readwrite,assign,getter=command,setter=setCommand:) NSString* command NS_SWIFT_NAME(command);
- (NSString*)command NS_SWIFT_NAME(command());
- (void)setCommand:(NSString*)newCommand NS_SWIFT_NAME(setCommand(_:));

@property (nonatomic,readwrite,assign,getter=connected,setter=setConnected:) BOOL connected NS_SWIFT_NAME(connected);
- (BOOL)connected NS_SWIFT_NAME(connected());
- (void)setConnected:(BOOL)newConnected NS_SWIFT_NAME(setConnected(_:));

@property (nonatomic,readwrite,assign,getter=deliveryNotificationTo,setter=setDeliveryNotificationTo:) NSString* deliveryNotificationTo NS_SWIFT_NAME(deliveryNotificationTo);
- (NSString*)deliveryNotificationTo NS_SWIFT_NAME(deliveryNotificationTo());
- (void)setDeliveryNotificationTo:(NSString*)newDeliveryNotificationTo NS_SWIFT_NAME(setDeliveryNotificationTo(_:));

@property (nonatomic,readwrite,assign,getter=firewallAutoDetect,setter=setFirewallAutoDetect:) BOOL firewallAutoDetect NS_SWIFT_NAME(firewallAutoDetect);
- (BOOL)firewallAutoDetect NS_SWIFT_NAME(firewallAutoDetect());
- (void)setFirewallAutoDetect:(BOOL)newFirewallAutoDetect NS_SWIFT_NAME(setFirewallAutoDetect(_:));

@property (nonatomic,readwrite,assign,getter=firewallType,setter=setFirewallType:) int firewallType NS_SWIFT_NAME(firewallType);
- (int)firewallType NS_SWIFT_NAME(firewallType());
- (void)setFirewallType:(int)newFirewallType NS_SWIFT_NAME(setFirewallType(_:));

@property (nonatomic,readwrite,assign,getter=firewallHost,setter=setFirewallHost:) NSString* firewallHost NS_SWIFT_NAME(firewallHost);
- (NSString*)firewallHost NS_SWIFT_NAME(firewallHost());
- (void)setFirewallHost:(NSString*)newFirewallHost NS_SWIFT_NAME(setFirewallHost(_:));

@property (nonatomic,readwrite,assign,getter=firewallPassword,setter=setFirewallPassword:) NSString* firewallPassword NS_SWIFT_NAME(firewallPassword);
- (NSString*)firewallPassword NS_SWIFT_NAME(firewallPassword());
- (void)setFirewallPassword:(NSString*)newFirewallPassword NS_SWIFT_NAME(setFirewallPassword(_:));

@property (nonatomic,readwrite,assign,getter=firewallPort,setter=setFirewallPort:) int firewallPort NS_SWIFT_NAME(firewallPort);
- (int)firewallPort NS_SWIFT_NAME(firewallPort());
- (void)setFirewallPort:(int)newFirewallPort NS_SWIFT_NAME(setFirewallPort(_:));

@property (nonatomic,readwrite,assign,getter=firewallUser,setter=setFirewallUser:) NSString* firewallUser NS_SWIFT_NAME(firewallUser);
- (NSString*)firewallUser NS_SWIFT_NAME(firewallUser());
- (void)setFirewallUser:(NSString*)newFirewallUser NS_SWIFT_NAME(setFirewallUser(_:));

@property (nonatomic,readwrite,assign,getter=from,setter=setFrom:) NSString* from NS_SWIFT_NAME(from);
- (NSString*)from NS_SWIFT_NAME(from());
- (void)setFrom:(NSString*)newFrom NS_SWIFT_NAME(setFrom(_:));

@property (nonatomic,readwrite,assign,getter=HTMLFile,setter=setHTMLFile:) NSString* HTMLFile NS_SWIFT_NAME(HTMLFile);
- (NSString*)HTMLFile NS_SWIFT_NAME(HTMLFile());
- (void)setHTMLFile:(NSString*)newHTMLFile NS_SWIFT_NAME(setHTMLFile(_:));

@property (nonatomic,readonly,assign,getter=idle) BOOL idle NS_SWIFT_NAME(idle);
- (BOOL)idle NS_SWIFT_NAME(idle());

@property (nonatomic,readwrite,assign,getter=imageCount,setter=setImageCount:) int imageCount NS_SWIFT_NAME(imageCount);
- (int)imageCount NS_SWIFT_NAME(imageCount());
- (void)setImageCount:(int)newImageCount NS_SWIFT_NAME(setImageCount(_:));

- (NSString*)imageData:(int)imageIndex NS_SWIFT_NAME(imageData(_:));
- (void)setImageData:(int)imageIndex:(NSString*)newImageData NS_SWIFT_NAME(setImageData(_:_:));

- (NSData*)imageDataB:(int)imageIndex NS_SWIFT_NAME(imageDataB(_:));
- (void)setImageDataB:(int)imageIndex :(NSData*)newImageData NS_SWIFT_NAME(setImageDataB(_:_:));

- (NSString*)imageFile:(int)imageIndex NS_SWIFT_NAME(imageFile(_:));
- (void)setImageFile:(int)imageIndex:(NSString*)newImageFile NS_SWIFT_NAME(setImageFile(_:_:));

- (NSString*)imageId:(int)imageIndex NS_SWIFT_NAME(imageId(_:));
- (void)setImageId:(int)imageIndex:(NSString*)newImageId NS_SWIFT_NAME(setImageId(_:_:));

- (NSString*)imageType:(int)imageIndex NS_SWIFT_NAME(imageType(_:));
- (void)setImageType:(int)imageIndex:(NSString*)newImageType NS_SWIFT_NAME(setImageType(_:_:));

@property (nonatomic,readwrite,assign,getter=importance,setter=setImportance:) int importance NS_SWIFT_NAME(importance);
- (int)importance NS_SWIFT_NAME(importance());
- (void)setImportance:(int)newImportance NS_SWIFT_NAME(setImportance(_:));

@property (nonatomic,readonly,assign,getter=lastReply) NSString* lastReply NS_SWIFT_NAME(lastReply);
- (NSString*)lastReply NS_SWIFT_NAME(lastReply());

@property (nonatomic,readwrite,assign,getter=localHost,setter=setLocalHost:) NSString* localHost NS_SWIFT_NAME(localHost);
- (NSString*)localHost NS_SWIFT_NAME(localHost());
- (void)setLocalHost:(NSString*)newLocalHost NS_SWIFT_NAME(setLocalHost(_:));

@property (nonatomic,readwrite,assign,getter=mailPort,setter=setMailPort:) int mailPort NS_SWIFT_NAME(mailPort);
- (int)mailPort NS_SWIFT_NAME(mailPort());
- (void)setMailPort:(int)newMailPort NS_SWIFT_NAME(setMailPort(_:));

@property (nonatomic,readwrite,assign,getter=mailServer,setter=setMailServer:) NSString* mailServer NS_SWIFT_NAME(mailServer);
- (NSString*)mailServer NS_SWIFT_NAME(mailServer());
- (void)setMailServer:(NSString*)newMailServer NS_SWIFT_NAME(setMailServer(_:));

@property (nonatomic,readwrite,assign,getter=messageDate,setter=setMessageDate:) NSString* messageDate NS_SWIFT_NAME(messageDate);
- (NSString*)messageDate NS_SWIFT_NAME(messageDate());
- (void)setMessageDate:(NSString*)newMessageDate NS_SWIFT_NAME(setMessageDate(_:));

@property (nonatomic,readwrite,assign,getter=messageHTML,setter=setMessageHTML:) NSString* messageHTML NS_SWIFT_NAME(messageHTML);
- (NSString*)messageHTML NS_SWIFT_NAME(messageHTML());
- (void)setMessageHTML:(NSString*)newMessageHTML NS_SWIFT_NAME(setMessageHTML(_:));

@property (nonatomic,readwrite,assign,getter=messageId,setter=setMessageId:) NSString* messageId NS_SWIFT_NAME(messageId);
- (NSString*)messageId NS_SWIFT_NAME(messageId());
- (void)setMessageId:(NSString*)newMessageId NS_SWIFT_NAME(setMessageId(_:));

@property (nonatomic,readwrite,assign,getter=messageRecipientCount,setter=setMessageRecipientCount:) int messageRecipientCount NS_SWIFT_NAME(messageRecipientCount);
- (int)messageRecipientCount NS_SWIFT_NAME(messageRecipientCount());
- (void)setMessageRecipientCount:(int)newMessageRecipientCount NS_SWIFT_NAME(setMessageRecipientCount(_:));

- (NSString*)messageRecipientAddress:(int)recipientIndex NS_SWIFT_NAME(messageRecipientAddress(_:));
- (void)setMessageRecipientAddress:(int)recipientIndex:(NSString*)newMessageRecipientAddress NS_SWIFT_NAME(setMessageRecipientAddress(_:_:));

- (NSString*)messageRecipientName:(int)recipientIndex NS_SWIFT_NAME(messageRecipientName(_:));
- (void)setMessageRecipientName:(int)recipientIndex:(NSString*)newMessageRecipientName NS_SWIFT_NAME(setMessageRecipientName(_:_:));

- (NSString*)messageRecipientOptions:(int)recipientIndex NS_SWIFT_NAME(messageRecipientOptions(_:));
- (void)setMessageRecipientOptions:(int)recipientIndex:(NSString*)newMessageRecipientOptions NS_SWIFT_NAME(setMessageRecipientOptions(_:_:));

- (int)messageRecipientType:(int)recipientIndex NS_SWIFT_NAME(messageRecipientType(_:));
- (void)setMessageRecipientType:(int)recipientIndex:(int)newMessageRecipientType NS_SWIFT_NAME(setMessageRecipientType(_:_:));

@property (nonatomic,readwrite,assign,getter=messageText,setter=setMessageText:) NSString* messageText NS_SWIFT_NAME(messageText);
- (NSString*)messageText NS_SWIFT_NAME(messageText());
- (void)setMessageText:(NSString*)newMessageText NS_SWIFT_NAME(setMessageText(_:));

@property (nonatomic,readwrite,assign,getter=otherHeaders,setter=setOtherHeaders:) NSString* otherHeaders NS_SWIFT_NAME(otherHeaders);
- (NSString*)otherHeaders NS_SWIFT_NAME(otherHeaders());
- (void)setOtherHeaders:(NSString*)newOtherHeaders NS_SWIFT_NAME(setOtherHeaders(_:));

@property (nonatomic,readwrite,assign,getter=parseHTML,setter=setParseHTML:) BOOL parseHTML NS_SWIFT_NAME(parseHTML);
- (BOOL)parseHTML NS_SWIFT_NAME(parseHTML());
- (void)setParseHTML:(BOOL)newParseHTML NS_SWIFT_NAME(setParseHTML(_:));

@property (nonatomic,readwrite,assign,getter=password,setter=setPassword:) NSString* password NS_SWIFT_NAME(password);
- (NSString*)password NS_SWIFT_NAME(password());
- (void)setPassword:(NSString*)newPassword NS_SWIFT_NAME(setPassword(_:));

@property (nonatomic,readwrite,assign,getter=priority,setter=setPriority:) int priority NS_SWIFT_NAME(priority);
- (int)priority NS_SWIFT_NAME(priority());
- (void)setPriority:(int)newPriority NS_SWIFT_NAME(setPriority(_:));

@property (nonatomic,readwrite,assign,getter=readReceiptTo,setter=setReadReceiptTo:) NSString* readReceiptTo NS_SWIFT_NAME(readReceiptTo);
- (NSString*)readReceiptTo NS_SWIFT_NAME(readReceiptTo());
- (void)setReadReceiptTo:(NSString*)newReadReceiptTo NS_SWIFT_NAME(setReadReceiptTo(_:));

@property (nonatomic,readwrite,assign,getter=replyTo,setter=setReplyTo:) NSString* replyTo NS_SWIFT_NAME(replyTo);
- (NSString*)replyTo NS_SWIFT_NAME(replyTo());
- (void)setReplyTo:(NSString*)newReplyTo NS_SWIFT_NAME(setReplyTo(_:));

@property (nonatomic,readwrite,assign,getter=sendTo,setter=setSendTo:) NSString* sendTo NS_SWIFT_NAME(sendTo);
- (NSString*)sendTo NS_SWIFT_NAME(sendTo());
- (void)setSendTo:(NSString*)newSendTo NS_SWIFT_NAME(setSendTo(_:));

@property (nonatomic,readwrite,assign,getter=sensitivity,setter=setSensitivity:) int sensitivity NS_SWIFT_NAME(sensitivity);
- (int)sensitivity NS_SWIFT_NAME(sensitivity());
- (void)setSensitivity:(int)newSensitivity NS_SWIFT_NAME(setSensitivity(_:));

@property (nonatomic,readwrite,assign,getter=SSLAcceptServerCertEncoded,setter=setSSLAcceptServerCertEncoded:) NSString* SSLAcceptServerCertEncoded NS_SWIFT_NAME(SSLAcceptServerCertEncoded);
- (NSString*)SSLAcceptServerCertEncoded NS_SWIFT_NAME(SSLAcceptServerCertEncoded());
- (void)setSSLAcceptServerCertEncoded:(NSString*)newSSLAcceptServerCertEncoded NS_SWIFT_NAME(setSSLAcceptServerCertEncoded(_:));

@property (nonatomic,readwrite,assign,getter=SSLAcceptServerCertEncodedB,setter=setSSLAcceptServerCertEncodedB:) NSData* SSLAcceptServerCertEncodedB NS_SWIFT_NAME(SSLAcceptServerCertEncodedB);
- (NSData*)SSLAcceptServerCertEncodedB NS_SWIFT_NAME(SSLAcceptServerCertEncodedB());
- (void)setSSLAcceptServerCertEncodedB :(NSData*)newSSLAcceptServerCertEncoded NS_SWIFT_NAME(setSSLAcceptServerCertEncodedB(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertEncoded,setter=setSSLCertEncoded:) NSString* SSLCertEncoded NS_SWIFT_NAME(SSLCertEncoded);
- (NSString*)SSLCertEncoded NS_SWIFT_NAME(SSLCertEncoded());
- (void)setSSLCertEncoded:(NSString*)newSSLCertEncoded NS_SWIFT_NAME(setSSLCertEncoded(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertEncodedB,setter=setSSLCertEncodedB:) NSData* SSLCertEncodedB NS_SWIFT_NAME(SSLCertEncodedB);
- (NSData*)SSLCertEncodedB NS_SWIFT_NAME(SSLCertEncodedB());
- (void)setSSLCertEncodedB :(NSData*)newSSLCertEncoded NS_SWIFT_NAME(setSSLCertEncodedB(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertStore,setter=setSSLCertStore:) NSString* SSLCertStore NS_SWIFT_NAME(SSLCertStore);
- (NSString*)SSLCertStore NS_SWIFT_NAME(SSLCertStore());
- (void)setSSLCertStore:(NSString*)newSSLCertStore NS_SWIFT_NAME(setSSLCertStore(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertStoreB,setter=setSSLCertStoreB:) NSData* SSLCertStoreB NS_SWIFT_NAME(SSLCertStoreB);
- (NSData*)SSLCertStoreB NS_SWIFT_NAME(SSLCertStoreB());
- (void)setSSLCertStoreB :(NSData*)newSSLCertStore NS_SWIFT_NAME(setSSLCertStoreB(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertStorePassword,setter=setSSLCertStorePassword:) NSString* SSLCertStorePassword NS_SWIFT_NAME(SSLCertStorePassword);
- (NSString*)SSLCertStorePassword NS_SWIFT_NAME(SSLCertStorePassword());
- (void)setSSLCertStorePassword:(NSString*)newSSLCertStorePassword NS_SWIFT_NAME(setSSLCertStorePassword(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertStoreType,setter=setSSLCertStoreType:) int SSLCertStoreType NS_SWIFT_NAME(SSLCertStoreType);
- (int)SSLCertStoreType NS_SWIFT_NAME(SSLCertStoreType());
- (void)setSSLCertStoreType:(int)newSSLCertStoreType NS_SWIFT_NAME(setSSLCertStoreType(_:));

@property (nonatomic,readwrite,assign,getter=SSLCertSubject,setter=setSSLCertSubject:) NSString* SSLCertSubject NS_SWIFT_NAME(SSLCertSubject);
- (NSString*)SSLCertSubject NS_SWIFT_NAME(SSLCertSubject());
- (void)setSSLCertSubject:(NSString*)newSSLCertSubject NS_SWIFT_NAME(setSSLCertSubject(_:));

@property (nonatomic,readwrite,assign,getter=SSLEnabled,setter=setSSLEnabled:) BOOL SSLEnabled NS_SWIFT_NAME(SSLEnabled);
- (BOOL)SSLEnabled NS_SWIFT_NAME(SSLEnabled());
- (void)setSSLEnabled:(BOOL)newSSLEnabled NS_SWIFT_NAME(setSSLEnabled(_:));

@property (nonatomic,readonly,assign,getter=SSLServerCertEncoded) NSString* SSLServerCertEncoded NS_SWIFT_NAME(SSLServerCertEncoded);
- (NSString*)SSLServerCertEncoded NS_SWIFT_NAME(SSLServerCertEncoded());

@property (nonatomic,readonly,assign,getter=SSLServerCertEncodedB) NSData* SSLServerCertEncodedB NS_SWIFT_NAME(SSLServerCertEncodedB);
- (NSData*)SSLServerCertEncodedB NS_SWIFT_NAME(SSLServerCertEncodedB());

@property (nonatomic,readwrite,assign,getter=SSLStartMode,setter=setSSLStartMode:) int SSLStartMode NS_SWIFT_NAME(SSLStartMode);
- (int)SSLStartMode NS_SWIFT_NAME(SSLStartMode());
- (void)setSSLStartMode:(int)newSSLStartMode NS_SWIFT_NAME(setSSLStartMode(_:));

@property (nonatomic,readwrite,assign,getter=subject,setter=setSubject:) NSString* subject NS_SWIFT_NAME(subject);
- (NSString*)subject NS_SWIFT_NAME(subject());
- (void)setSubject:(NSString*)newSubject NS_SWIFT_NAME(setSubject(_:));

@property (nonatomic,readwrite,assign,getter=timeout,setter=setTimeout:) int timeout NS_SWIFT_NAME(timeout);
- (int)timeout NS_SWIFT_NAME(timeout());
- (void)setTimeout:(int)newTimeout NS_SWIFT_NAME(setTimeout(_:));

@property (nonatomic,readwrite,assign,getter=user,setter=setUser:) NSString* user NS_SWIFT_NAME(user);
- (NSString*)user NS_SWIFT_NAME(user());
- (void)setUser:(NSString*)newUser NS_SWIFT_NAME(setUser(_:));

  /* Methods */

- (void)addAttachment:(NSString*)fileName NS_SWIFT_NAME(addAttachment(_:));
- (NSString*)config:(NSString*)configurationString NS_SWIFT_NAME(config(_:));
- (void)connect NS_SWIFT_NAME(connect());
- (void)disconnect NS_SWIFT_NAME(disconnect());
- (void)doEvents NS_SWIFT_NAME(doEvents());
- (void)interrupt NS_SWIFT_NAME(interrupt());
- (void)processQueue:(NSString*)queueDir NS_SWIFT_NAME(processQueue(_:));
- (NSString*)queue:(NSString*)queueDir NS_SWIFT_NAME(queue(_:));
- (void)reset NS_SWIFT_NAME(reset());
- (void)resetHeaders NS_SWIFT_NAME(resetHeaders());
- (void)send NS_SWIFT_NAME(send());

@end


