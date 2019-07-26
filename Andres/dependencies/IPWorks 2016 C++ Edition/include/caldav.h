/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_CALDAV_H_
#define _IPWORKS_CALDAV_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//Actions
#define A_NO_ALARM                                         0
#define A_AUDIO                                            1
#define A_DISPLAY                                          2
#define A_EMAIL                                            3

//AuthSchemes
#define AUTH_BASIC                                         0
#define AUTH_DIGEST                                        1
#define AUTH_PROPRIETARY                                   2
#define AUTH_NONE                                          3
#define AUTH_NTLM                                          4
#define AUTH_NEGOTIATE                                     5
#define AUTH_OAUTH                                         6

//TDepth
#define DP_UNSPECIFIED                                     0
#define DP_RESOURCE_ONLY                                   1
#define DP_IMMEDIATE_CHILDREN                              2
#define DP_INFINITY                                        3

//EventTypes
#define V_EVENT                                            0
#define V_TODO                                             1
#define V_JOURNAL                                          2
#define V_FREE_BUSY                                        3

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TFollowRedirects
#define FR_NEVER                                           0
#define FR_ALWAYS                                          1
#define FR_SAME_SCHEME                                     2

//ProxySSLTypes
#define PS_AUTOMATIC                                       0
#define PS_ALWAYS                                          1
#define PS_NEVER                                           2
#define PS_TUNNEL                                          3

//VEventTypes
#define VT_EVENT                                           0
#define VT_TODO                                            1
#define VT_JOURNAL                                         2
#define VT_FREE_BUSY                                       3
#define VT_ALL                                             4

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


extern "C" void* IPWORKS_CALL IPWorks_CalDAV_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_CalDAV_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_CalDAV_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} CalDAVConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} CalDAVConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} CalDAVDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} CalDAVEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} CalDAVErrorEventParams;

typedef struct {
  const char* ResourceURI;
  const char* ResponseStatus;
  const char* ETag;
  const char* CalendarData;
  int reserved;
} CalDAVEventDetailsEventParams;

typedef struct {
  const char* BusyType;
  const char* BusyRange;
  int reserved;
} CalDAVFreeBusyEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} CalDAVHeaderEventParams;

typedef struct {
  int LogLevel;
  const char* Message;
  const char* LogType;
  int reserved;
} CalDAVLogEventParams;

typedef struct {
  const char* Location;
  int Accept;
  int reserved;
} CalDAVRedirectEventParams;

typedef struct {
  const char* Name;
  const char* Value;
  const char* Expires;
  const char* Domain;
  const char* Path;
  int Secure;
  int reserved;
} CalDAVSetCookieEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} CalDAVSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} CalDAVSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} CalDAVStartTransferEventParams;

typedef struct {
  const char* HTTPVersion;
  int StatusCode;
  const char* Description;
  int reserved;
} CalDAVStatusEventParams;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  const char* Text;
  int lenText;
  int reserved;
} CalDAVTransferEventParams;



class CalDAV {
  
  public: //events
  
    virtual int FireConnected(CalDAVConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(CalDAVConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(CalDAVDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(CalDAVEndTransferEventParams *e) {return 0;}
    virtual int FireError(CalDAVErrorEventParams *e) {return 0;}
    virtual int FireEventDetails(CalDAVEventDetailsEventParams *e) {return 0;}
    virtual int FireFreeBusy(CalDAVFreeBusyEventParams *e) {return 0;}
    virtual int FireHeader(CalDAVHeaderEventParams *e) {return 0;}
    virtual int FireLog(CalDAVLogEventParams *e) {return 0;}
    virtual int FireRedirect(CalDAVRedirectEventParams *e) {return 0;}
    virtual int FireSetCookie(CalDAVSetCookieEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(CalDAVSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(CalDAVSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(CalDAVStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(CalDAVStatusEventParams *e) {return 0;}
    virtual int FireTransfer(CalDAVTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL CalDAVEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((CalDAV*)lpObj)->CalDAVEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            CalDAVConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((CalDAV*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            CalDAVConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((CalDAV*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            CalDAVDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((CalDAV*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            CalDAVEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((CalDAV*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 5: {
            CalDAVErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((CalDAV*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            CalDAVEventDetailsEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]),  0};
            ret_code = ((CalDAV*)lpObj)->FireEventDetails(&e);
            break;
         }
         case 7: {
            CalDAVFreeBusyEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((CalDAV*)lpObj)->FireFreeBusy(&e);
            break;
         }
         case 8: {
            CalDAVHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((CalDAV*)lpObj)->FireHeader(&e);
            break;
         }
         case 9: {
            CalDAVLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((CalDAV*)lpObj)->FireLog(&e);
            break;
         }
         case 10: {
            CalDAVRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = ((CalDAV*)lpObj)->FireRedirect(&e);
            param[1] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 11: {
            CalDAVSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = ((CalDAV*)lpObj)->FireSetCookie(&e);
            break;
         }
         case 12: {
            CalDAVSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((CalDAV*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 13: {
            CalDAVSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((CalDAV*)lpObj)->FireSSLStatus(&e);
            break;
         }
         case 14: {
            CalDAVStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((CalDAV*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 15: {
            CalDAVStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((CalDAV*)lpObj)->FireStatus(&e);
            break;
         }
         case 16: {
            CalDAVTransferEventParams e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((CalDAV*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int CalDAVEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    CalDAV(char *lpOemKey = (char*)IPWORKS_OEMKEY_98) {
      m_pObj = IPWorks_CalDAV_Create(CalDAVEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~CalDAV() {
      IPWorks_CalDAV_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_CalDAV_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_CalDAV_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_CalDAV_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_CalDAV_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_CalDAV_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetAlarmCount() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAlarmCount(int iAlarmCount) {
      void* val = (void*)IPW64CAST(iAlarmCount);
      return IPWorks_CalDAV_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetAlarmAction(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 2, iAlarmIndex, 0);
      return (int)(long)val;
    }
    inline int SetAlarmAction(int iAlarmIndex, int iAlarmAction) {
      void* val = (void*)IPW64CAST(iAlarmAction);
      return IPWorks_CalDAV_Set(m_pObj, 2, iAlarmIndex, val, 0);
    }
    inline char* GetAlarmAttachment(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 3, iAlarmIndex, 0);
      return (char*)val;
    }

    inline int SetAlarmAttachment(int iAlarmIndex, const char *lpAlarmAttachment) {
      return IPWorks_CalDAV_Set(m_pObj, 3, iAlarmIndex, (void*)lpAlarmAttachment, 0);
    }

    inline char* GetAlarmAttachmentType(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 4, iAlarmIndex, 0);
      return (char*)val;
    }

    inline int SetAlarmAttachmentType(int iAlarmIndex, const char *lpAlarmAttachmentType) {
      return IPWorks_CalDAV_Set(m_pObj, 4, iAlarmIndex, (void*)lpAlarmAttachmentType, 0);
    }

    inline char* GetAlarmDuration(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 5, iAlarmIndex, 0);
      return (char*)val;
    }

    inline int SetAlarmDuration(int iAlarmIndex, const char *lpAlarmDuration) {
      return IPWorks_CalDAV_Set(m_pObj, 5, iAlarmIndex, (void*)lpAlarmDuration, 0);
    }

    inline char* GetAlarmMessage(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 6, iAlarmIndex, 0);
      return (char*)val;
    }

    inline int SetAlarmMessage(int iAlarmIndex, const char *lpAlarmMessage) {
      return IPWorks_CalDAV_Set(m_pObj, 6, iAlarmIndex, (void*)lpAlarmMessage, 0);
    }

    inline char* GetAlarmRecipient(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 7, iAlarmIndex, 0);
      return (char*)val;
    }

    inline int SetAlarmRecipient(int iAlarmIndex, const char *lpAlarmRecipient) {
      return IPWorks_CalDAV_Set(m_pObj, 7, iAlarmIndex, (void*)lpAlarmRecipient, 0);
    }

    inline int GetAlarmRepeat(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 8, iAlarmIndex, 0);
      return (int)(long)val;
    }
    inline int SetAlarmRepeat(int iAlarmIndex, int iAlarmRepeat) {
      void* val = (void*)IPW64CAST(iAlarmRepeat);
      return IPWorks_CalDAV_Set(m_pObj, 8, iAlarmIndex, val, 0);
    }
    inline char* GetAlarmSubject(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 9, iAlarmIndex, 0);
      return (char*)val;
    }

    inline int SetAlarmSubject(int iAlarmIndex, const char *lpAlarmSubject) {
      return IPWorks_CalDAV_Set(m_pObj, 9, iAlarmIndex, (void*)lpAlarmSubject, 0);
    }

    inline char* GetAlarmTrigger(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 10, iAlarmIndex, 0);
      return (char*)val;
    }

    inline int SetAlarmTrigger(int iAlarmIndex, const char *lpAlarmTrigger) {
      return IPWorks_CalDAV_Set(m_pObj, 10, iAlarmIndex, (void*)lpAlarmTrigger, 0);
    }

    inline char* GetAttendees() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetAttendees(const char *lpAttendees) {
      return IPWorks_CalDAV_Set(m_pObj, 11, 0, (void*)lpAttendees, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorization(const char *lpAuthorization) {
      return IPWorks_CalDAV_Set(m_pObj, 12, 0, (void*)lpAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_CalDAV_Set(m_pObj, 13, 0, val, 0);
    }
    inline char* GetCategories() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetCategories(const char *lpCategories) {
      return IPWorks_CalDAV_Set(m_pObj, 14, 0, (void*)lpCategories, 0);
    }

    inline char* GetClassification() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetClassification(const char *lpClassification) {
      return IPWorks_CalDAV_Set(m_pObj, 15, 0, (void*)lpClassification, 0);
    }

    inline char* GetCompleted() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetCompleted(const char *lpCompleted) {
      return IPWorks_CalDAV_Set(m_pObj, 16, 0, (void*)lpCompleted, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_CalDAV_Set(m_pObj, 17, 0, val, 0);
    }
    inline int GetCookieCount() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_CalDAV_Set(m_pObj, 18, 0, val, 0);
    }
    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 19, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 20, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 21, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieName(int iCookieIndex, const char *lpCookieName) {
      return IPWorks_CalDAV_Set(m_pObj, 21, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 22, iCookieIndex, 0);
      return (char*)val;
    }


    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 23, iCookieIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 24, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieValue(int iCookieIndex, const char *lpCookieValue) {
      return IPWorks_CalDAV_Set(m_pObj, 24, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline char* GetCreated() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }

    inline int SetCreated(const char *lpCreated) {
      return IPWorks_CalDAV_Set(m_pObj, 25, 0, (void*)lpCreated, 0);
    }

    inline int GetCustomPropertyCount() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 26, 0, 0);
      return (int)(long)val;
    }
    inline int SetCustomPropertyCount(int iCustomPropertyCount) {
      void* val = (void*)IPW64CAST(iCustomPropertyCount);
      return IPWorks_CalDAV_Set(m_pObj, 26, 0, val, 0);
    }
    inline char* GetCustomPropertyAttribute(int iCustomPropertyIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 27, iCustomPropertyIndex, 0);
      return (char*)val;
    }

    inline int SetCustomPropertyAttribute(int iCustomPropertyIndex, const char *lpCustomPropertyAttribute) {
      return IPWorks_CalDAV_Set(m_pObj, 27, iCustomPropertyIndex, (void*)lpCustomPropertyAttribute, 0);
    }

    inline char* GetCustomPropertyName(int iCustomPropertyIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 28, iCustomPropertyIndex, 0);
      return (char*)val;
    }

    inline int SetCustomPropertyName(int iCustomPropertyIndex, const char *lpCustomPropertyName) {
      return IPWorks_CalDAV_Set(m_pObj, 28, iCustomPropertyIndex, (void*)lpCustomPropertyName, 0);
    }

    inline char* GetCustomPropertyValue(int iCustomPropertyIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 29, iCustomPropertyIndex, 0);
      return (char*)val;
    }

    inline int SetCustomPropertyValue(int iCustomPropertyIndex, const char *lpCustomPropertyValue) {
      return IPWorks_CalDAV_Set(m_pObj, 29, iCustomPropertyIndex, (void*)lpCustomPropertyValue, 0);
    }

    inline int GetDepth() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 30, 0, 0);
      return (int)(long)val;
    }
    inline int SetDepth(int iDepth) {
      void* val = (void*)IPW64CAST(iDepth);
      return IPWorks_CalDAV_Set(m_pObj, 30, 0, val, 0);
    }
    inline char* GetDescription() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 31, 0, 0);
      return (char*)val;
    }

    inline int SetDescription(const char *lpDescription) {
      return IPWorks_CalDAV_Set(m_pObj, 31, 0, (void*)lpDescription, 0);
    }

    inline char* GetDisplayName() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 32, 0, 0);
      return (char*)val;
    }

    inline int SetDisplayName(const char *lpDisplayName) {
      return IPWorks_CalDAV_Set(m_pObj, 32, 0, (void*)lpDisplayName, 0);
    }

    inline char* GetDueDate() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 33, 0, 0);
      return (char*)val;
    }

    inline int SetDueDate(const char *lpDueDate) {
      return IPWorks_CalDAV_Set(m_pObj, 33, 0, (void*)lpDueDate, 0);
    }

    inline char* GetDuration() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 34, 0, 0);
      return (char*)val;
    }

    inline int SetDuration(const char *lpDuration) {
      return IPWorks_CalDAV_Set(m_pObj, 34, 0, (void*)lpDuration, 0);
    }

    inline char* GetEndDate() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 35, 0, 0);
      return (char*)val;
    }

    inline int SetEndDate(const char *lpEndDate) {
      return IPWorks_CalDAV_Set(m_pObj, 35, 0, (void*)lpEndDate, 0);
    }

    inline char* GetETag() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 36, 0, 0);
      return (char*)val;
    }

    inline int SetETag(const char *lpETag) {
      return IPWorks_CalDAV_Set(m_pObj, 36, 0, (void*)lpETag, 0);
    }

    inline int GetEventType() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 37, 0, 0);
      return (int)(long)val;
    }
    inline int SetEventType(int iEventType) {
      void* val = (void*)IPW64CAST(iEventType);
      return IPWorks_CalDAV_Set(m_pObj, 37, 0, val, 0);
    }
    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 38, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_CalDAV_Set(m_pObj, 38, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 39, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_CalDAV_Set(m_pObj, 39, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 40, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_CalDAV_Set(m_pObj, 40, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 41, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 41, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 42, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_CalDAV_Set(m_pObj, 42, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 43, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_CalDAV_Set(m_pObj, 43, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 44, 0, 0);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_CalDAV_Set(m_pObj, 44, 0, val, 0);
    }
    inline int GetFreeBusyCount() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 45, 0, 0);
      return (int)(long)val;
    }

    inline char* GetFreeBusyRange(int iFreeBusyIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 46, iFreeBusyIndex, 0);
      return (char*)val;
    }


    inline char* GetFreeBusyType(int iFreeBusyIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 47, iFreeBusyIndex, 0);
      return (char*)val;
    }


    inline int GetIdle() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 48, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLastModified() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 49, 0, 0);
      return (char*)val;
    }

    inline int SetLastModified(const char *lpLastModified) {
      return IPWorks_CalDAV_Set(m_pObj, 49, 0, (void*)lpLastModified, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 50, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_CalDAV_Set(m_pObj, 50, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetLocation() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 51, 0, 0);
      return (char*)val;
    }

    inline int SetLocation(const char *lpLocation) {
      return IPWorks_CalDAV_Set(m_pObj, 51, 0, (void*)lpLocation, 0);
    }

    inline char* GetLockType() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 52, 0, 0);
      return (char*)val;
    }

    inline int SetLockType(const char *lpLockType) {
      return IPWorks_CalDAV_Set(m_pObj, 52, 0, (void*)lpLockType, 0);
    }

    inline char* GetLockOwner() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 53, 0, 0);
      return (char*)val;
    }

    inline int SetLockOwner(const char *lpLockOwner) {
      return IPWorks_CalDAV_Set(m_pObj, 53, 0, (void*)lpLockOwner, 0);
    }

    inline char* GetLockScope() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 54, 0, 0);
      return (char*)val;
    }

    inline int SetLockScope(const char *lpLockScope) {
      return IPWorks_CalDAV_Set(m_pObj, 54, 0, (void*)lpLockScope, 0);
    }

    inline int GetLockTimeout() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 55, 0, 0);
      return (int)(long)val;
    }
    inline int SetLockTimeout(int iLockTimeout) {
      void* val = (void*)IPW64CAST(iLockTimeout);
      return IPWorks_CalDAV_Set(m_pObj, 55, 0, val, 0);
    }
    inline char* GetLockTokens() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 56, 0, 0);
      return (char*)val;
    }

    inline int SetLockTokens(const char *lpLockTokens) {
      return IPWorks_CalDAV_Set(m_pObj, 56, 0, (void*)lpLockTokens, 0);
    }

    inline char* GetOrganizer() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 57, 0, 0);
      return (char*)val;
    }

    inline int SetOrganizer(const char *lpOrganizer) {
      return IPWorks_CalDAV_Set(m_pObj, 57, 0, (void*)lpOrganizer, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 58, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_CalDAV_Set(m_pObj, 58, 0, (void*)lpOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 59, 0, 0);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 60, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 61, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 62, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 62, 0, (void*)lpPassword, 0);
    }

    inline int GetPriority() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 63, 0, 0);
      return (int)(long)val;
    }
    inline int SetPriority(int iPriority) {
      void* val = (void*)IPW64CAST(iPriority);
      return IPWorks_CalDAV_Set(m_pObj, 63, 0, val, 0);
    }
    inline int GetProxyAuthScheme() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 64, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_CalDAV_Set(m_pObj, 64, 0, val, 0);
    }
    inline int GetProxyAutoDetect() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 65, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_CalDAV_Set(m_pObj, 65, 0, val, 0);
    }
    inline char* GetProxyPassword() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 66, 0, 0);
      return (char*)val;
    }

    inline int SetProxyPassword(const char *lpProxyPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 66, 0, (void*)lpProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 67, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyPort(int lProxyPort) {
      void* val = (void*)IPW64CAST(lProxyPort);
      return IPWorks_CalDAV_Set(m_pObj, 67, 0, val, 0);
    }
    inline char* GetProxyServer() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 68, 0, 0);
      return (char*)val;
    }

    inline int SetProxyServer(const char *lpProxyServer) {
      return IPWorks_CalDAV_Set(m_pObj, 68, 0, (void*)lpProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 69, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_CalDAV_Set(m_pObj, 69, 0, val, 0);
    }
    inline char* GetProxyUser() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 70, 0, 0);
      return (char*)val;
    }

    inline int SetProxyUser(const char *lpProxyUser) {
      return IPWorks_CalDAV_Set(m_pObj, 70, 0, (void*)lpProxyUser, 0);
    }

    inline char* GetRecurrenceDates() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 71, 0, 0);
      return (char*)val;
    }

    inline int SetRecurrenceDates(const char *lpRecurrenceDates) {
      return IPWorks_CalDAV_Set(m_pObj, 71, 0, (void*)lpRecurrenceDates, 0);
    }

    inline char* GetRecurrenceExceptionDates() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 72, 0, 0);
      return (char*)val;
    }

    inline int SetRecurrenceExceptionDates(const char *lpRecurrenceExceptionDates) {
      return IPWorks_CalDAV_Set(m_pObj, 72, 0, (void*)lpRecurrenceExceptionDates, 0);
    }

    inline char* GetRecurrenceExceptionRule() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 73, 0, 0);
      return (char*)val;
    }

    inline int SetRecurrenceExceptionRule(const char *lpRecurrenceExceptionRule) {
      return IPWorks_CalDAV_Set(m_pObj, 73, 0, (void*)lpRecurrenceExceptionRule, 0);
    }

    inline char* GetRecurrenceId() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 74, 0, 0);
      return (char*)val;
    }

    inline int SetRecurrenceId(const char *lpRecurrenceId) {
      return IPWorks_CalDAV_Set(m_pObj, 74, 0, (void*)lpRecurrenceId, 0);
    }

    inline char* GetRecurrenceRule() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 75, 0, 0);
      return (char*)val;
    }

    inline int SetRecurrenceRule(const char *lpRecurrenceRule) {
      return IPWorks_CalDAV_Set(m_pObj, 75, 0, (void*)lpRecurrenceRule, 0);
    }

    inline char* GetReportFilterAlarmEnd() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 76, 0, 0);
      return (char*)val;
    }

    inline int SetReportFilterAlarmEnd(const char *lpReportFilterAlarmEnd) {
      return IPWorks_CalDAV_Set(m_pObj, 76, 0, (void*)lpReportFilterAlarmEnd, 0);
    }

    inline char* GetReportFilterAlarmStart() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 77, 0, 0);
      return (char*)val;
    }

    inline int SetReportFilterAlarmStart(const char *lpReportFilterAlarmStart) {
      return IPWorks_CalDAV_Set(m_pObj, 77, 0, (void*)lpReportFilterAlarmStart, 0);
    }

    inline char* GetReportFilterCustomFilter() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 78, 0, 0);
      return (char*)val;
    }

    inline int SetReportFilterCustomFilter(const char *lpReportFilterCustomFilter) {
      return IPWorks_CalDAV_Set(m_pObj, 78, 0, (void*)lpReportFilterCustomFilter, 0);
    }

    inline char* GetReportFilterEndDate() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 79, 0, 0);
      return (char*)val;
    }

    inline int SetReportFilterEndDate(const char *lpReportFilterEndDate) {
      return IPWorks_CalDAV_Set(m_pObj, 79, 0, (void*)lpReportFilterEndDate, 0);
    }

    inline int GetReportFilterEventType() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 80, 0, 0);
      return (int)(long)val;
    }
    inline int SetReportFilterEventType(int iReportFilterEventType) {
      void* val = (void*)IPW64CAST(iReportFilterEventType);
      return IPWorks_CalDAV_Set(m_pObj, 80, 0, val, 0);
    }
    inline char* GetReportFilterProperty() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 81, 0, 0);
      return (char*)val;
    }

    inline int SetReportFilterProperty(const char *lpReportFilterProperty) {
      return IPWorks_CalDAV_Set(m_pObj, 81, 0, (void*)lpReportFilterProperty, 0);
    }

    inline char* GetReportFilterRecurEnd() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 82, 0, 0);
      return (char*)val;
    }

    inline int SetReportFilterRecurEnd(const char *lpReportFilterRecurEnd) {
      return IPWorks_CalDAV_Set(m_pObj, 82, 0, (void*)lpReportFilterRecurEnd, 0);
    }

    inline char* GetReportFilterRecurStart() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 83, 0, 0);
      return (char*)val;
    }

    inline int SetReportFilterRecurStart(const char *lpReportFilterRecurStart) {
      return IPWorks_CalDAV_Set(m_pObj, 83, 0, (void*)lpReportFilterRecurStart, 0);
    }

    inline int GetReportFilterReturnCalendarData() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 84, 0, 0);
      return (int)(long)val;
    }
    inline int SetReportFilterReturnCalendarData(int bReportFilterReturnCalendarData) {
      void* val = (void*)IPW64CAST(bReportFilterReturnCalendarData);
      return IPWorks_CalDAV_Set(m_pObj, 84, 0, val, 0);
    }
    inline char* GetReportFilterStartDate() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 85, 0, 0);
      return (char*)val;
    }

    inline int SetReportFilterStartDate(const char *lpReportFilterStartDate) {
      return IPWorks_CalDAV_Set(m_pObj, 85, 0, (void*)lpReportFilterStartDate, 0);
    }

    inline char* GetReportFilterUID() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 86, 0, 0);
      return (char*)val;
    }

    inline int SetReportFilterUID(const char *lpReportFilterUID) {
      return IPWorks_CalDAV_Set(m_pObj, 86, 0, (void*)lpReportFilterUID, 0);
    }

    inline int GetSequence() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 87, 0, 0);
      return (int)(long)val;
    }
    inline int SetSequence(int iSequence) {
      void* val = (void*)IPW64CAST(iSequence);
      return IPWorks_CalDAV_Set(m_pObj, 87, 0, val, 0);
    }
    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_CalDAV_Get(m_pObj, 88, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_CalDAV_Set(m_pObj, 88, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_CalDAV_Get(m_pObj, 89, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_CalDAV_Set(m_pObj, 89, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_CalDAV_Get(m_pObj, 90, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_CalDAV_Set(m_pObj, 90, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 91, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_CalDAV_Set(m_pObj, 91, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 92, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_CalDAV_Set(m_pObj, 92, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 93, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_CalDAV_Set(m_pObj, 93, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_CalDAV_Get(m_pObj, 94, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline char* GetStartDate() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 95, 0, 0);
      return (char*)val;
    }

    inline int SetStartDate(const char *lpStartDate) {
      return IPWorks_CalDAV_Set(m_pObj, 95, 0, (void*)lpStartDate, 0);
    }

    inline char* GetStatus() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 96, 0, 0);
      return (char*)val;
    }

    inline int SetStatus(const char *lpStatus) {
      return IPWorks_CalDAV_Set(m_pObj, 96, 0, (void*)lpStatus, 0);
    }

    inline char* GetStatusLine() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 97, 0, 0);
      return (char*)val;
    }


    inline char* GetSummary() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 98, 0, 0);
      return (char*)val;
    }

    inline int SetSummary(const char *lpSummary) {
      return IPWorks_CalDAV_Set(m_pObj, 98, 0, (void*)lpSummary, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 99, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_CalDAV_Set(m_pObj, 99, 0, val, 0);
    }
    inline char* GetTimestamp() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 100, 0, 0);
      return (char*)val;
    }

    inline int SetTimestamp(const char *lpTimestamp) {
      return IPWorks_CalDAV_Set(m_pObj, 100, 0, (void*)lpTimestamp, 0);
    }

    inline char* GetTimezoneDSTName() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 101, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneDSTName(const char *lpTimezoneDSTName) {
      return IPWorks_CalDAV_Set(m_pObj, 101, 0, (void*)lpTimezoneDSTName, 0);
    }

    inline char* GetTimezoneDSTOffsetFrom() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 102, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneDSTOffsetFrom(const char *lpTimezoneDSTOffsetFrom) {
      return IPWorks_CalDAV_Set(m_pObj, 102, 0, (void*)lpTimezoneDSTOffsetFrom, 0);
    }

    inline char* GetTimezoneDSTOffsetTo() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 103, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneDSTOffsetTo(const char *lpTimezoneDSTOffsetTo) {
      return IPWorks_CalDAV_Set(m_pObj, 103, 0, (void*)lpTimezoneDSTOffsetTo, 0);
    }

    inline char* GetTimezoneDSTRule() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 104, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneDSTRule(const char *lpTimezoneDSTRule) {
      return IPWorks_CalDAV_Set(m_pObj, 104, 0, (void*)lpTimezoneDSTRule, 0);
    }

    inline char* GetTimezoneDSTStart() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 105, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneDSTStart(const char *lpTimezoneDSTStart) {
      return IPWorks_CalDAV_Set(m_pObj, 105, 0, (void*)lpTimezoneDSTStart, 0);
    }

    inline char* GetTimezoneLastModified() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 106, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneLastModified(const char *lpTimezoneLastModified) {
      return IPWorks_CalDAV_Set(m_pObj, 106, 0, (void*)lpTimezoneLastModified, 0);
    }

    inline char* GetTimezoneStdName() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 107, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneStdName(const char *lpTimezoneStdName) {
      return IPWorks_CalDAV_Set(m_pObj, 107, 0, (void*)lpTimezoneStdName, 0);
    }

    inline char* GetTimezoneStdOffsetFrom() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 108, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneStdOffsetFrom(const char *lpTimezoneStdOffsetFrom) {
      return IPWorks_CalDAV_Set(m_pObj, 108, 0, (void*)lpTimezoneStdOffsetFrom, 0);
    }

    inline char* GetTimezoneStdOffsetTo() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 109, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneStdOffsetTo(const char *lpTimezoneStdOffsetTo) {
      return IPWorks_CalDAV_Set(m_pObj, 109, 0, (void*)lpTimezoneStdOffsetTo, 0);
    }

    inline char* GetTimezoneStdRule() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 110, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneStdRule(const char *lpTimezoneStdRule) {
      return IPWorks_CalDAV_Set(m_pObj, 110, 0, (void*)lpTimezoneStdRule, 0);
    }

    inline char* GetTimezoneStdStart() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 111, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneStdStart(const char *lpTimezoneStdStart) {
      return IPWorks_CalDAV_Set(m_pObj, 111, 0, (void*)lpTimezoneStdStart, 0);
    }

    inline char* GetTimezoneId() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 112, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneId(const char *lpTimezoneId) {
      return IPWorks_CalDAV_Set(m_pObj, 112, 0, (void*)lpTimezoneId, 0);
    }

    inline char* GetTimezoneURL() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 113, 0, 0);
      return (char*)val;
    }

    inline int SetTimezoneURL(const char *lpTimezoneURL) {
      return IPWorks_CalDAV_Set(m_pObj, 113, 0, (void*)lpTimezoneURL, 0);
    }

    inline char* GetTransparency() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 114, 0, 0);
      return (char*)val;
    }

    inline int SetTransparency(const char *lpTransparency) {
      return IPWorks_CalDAV_Set(m_pObj, 114, 0, (void*)lpTransparency, 0);
    }

    inline char* GetUID() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 115, 0, 0);
      return (char*)val;
    }

    inline int SetUID(const char *lpUID) {
      return IPWorks_CalDAV_Set(m_pObj, 115, 0, (void*)lpUID, 0);
    }

    inline char* GetURL() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 116, 0, 0);
      return (char*)val;
    }


    inline char* GetUser() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 117, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_CalDAV_Set(m_pObj, 117, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 2, 2, param, cbparam);
      
      
    }
    inline int AddCustomProperty(const char* lpszVarName, const char* lpszVarValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszVarName), (void*)IPW64CAST(lpszVarValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 3, 2, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_CalDAV_Do(m_pObj, 4, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int CopyCalendarEvent(const char* lpszSourceResourceURI, const char* lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszSourceResourceURI), (void*)IPW64CAST(lpszDestinationResourceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 5, 2, param, cbparam);
      
      
    }
    inline int CreateCalendar(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 6, 1, param, cbparam);
      
      
    }
    inline int DeleteCalendarEvent(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 7, 1, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline char* ExportICS() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CalDAV_Do(m_pObj, 9, 0, param, cbparam);
      
      return (char*)IPW64CAST(param[0]);
    }
    inline int GetCalendarEvent(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10, 1, param, cbparam);
      
      
    }
    inline int GetCalendarOptions(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 11, 1, param, cbparam);
      
      
    }
    inline int GetCalendarReport(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 12, 1, param, cbparam);
      
      
    }
    inline int GetFreeBusyReport(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 13, 1, param, cbparam);
      
      
    }
    inline int ImportICS(const char* lpszCalendarData) {
      void *param[1+1] = {(void*)IPW64CAST(lpszCalendarData), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 14, 1, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 15, 0, param, cbparam);
      
      
    }
    inline int LockCalendar(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 16, 1, param, cbparam);
      
      
    }
    inline int MoveCalendarEvent(const char* lpszSourceResourceURI, const char* lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszSourceResourceURI), (void*)IPW64CAST(lpszDestinationResourceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 17, 2, param, cbparam);
      
      
    }
    inline int PutCalendarEvent(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 18, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 19, 0, param, cbparam);
      
      
    }
    inline int UnLockCalendar(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 20, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} CalDAVConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} CalDAVConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} CalDAVDisconnectedEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} CalDAVEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} CalDAVErrorEventParamsW;

typedef struct {
  LPWSTR ResourceURI;
  LPWSTR ResponseStatus;
  LPWSTR ETag;
  LPWSTR CalendarData;
  int reserved;
} CalDAVEventDetailsEventParamsW;

typedef struct {
  LPWSTR BusyType;
  LPWSTR BusyRange;
  int reserved;
} CalDAVFreeBusyEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} CalDAVHeaderEventParamsW;

typedef struct {
  int LogLevel;
  LPWSTR Message;
  LPWSTR LogType;
  int reserved;
} CalDAVLogEventParamsW;

typedef struct {
  LPWSTR Location;
  int Accept;
  int reserved;
} CalDAVRedirectEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR Value;
  LPWSTR Expires;
  LPWSTR Domain;
  LPWSTR Path;
  int Secure;
  int reserved;
} CalDAVSetCookieEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} CalDAVSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} CalDAVSSLStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} CalDAVStartTransferEventParamsW;

typedef struct {
  LPWSTR HTTPVersion;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} CalDAVStatusEventParamsW;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int lenText;
  int reserved;
} CalDAVTransferEventParamsW;



class CalDAVW : public CalDAV {

  public: //properties
  




    inline LPWSTR GetAlarmAttachment(int iAlarmIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+3, iAlarmIndex, 0);
    }

    inline int SetAlarmAttachment(int iAlarmIndex, LPCWSTR lpAlarmAttachment) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+3, iAlarmIndex, (void*)lpAlarmAttachment, 0);
    }

    inline LPWSTR GetAlarmAttachmentType(int iAlarmIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+4, iAlarmIndex, 0);
    }

    inline int SetAlarmAttachmentType(int iAlarmIndex, LPCWSTR lpAlarmAttachmentType) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+4, iAlarmIndex, (void*)lpAlarmAttachmentType, 0);
    }

    inline LPWSTR GetAlarmDuration(int iAlarmIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+5, iAlarmIndex, 0);
    }

    inline int SetAlarmDuration(int iAlarmIndex, LPCWSTR lpAlarmDuration) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+5, iAlarmIndex, (void*)lpAlarmDuration, 0);
    }

    inline LPWSTR GetAlarmMessage(int iAlarmIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+6, iAlarmIndex, 0);
    }

    inline int SetAlarmMessage(int iAlarmIndex, LPCWSTR lpAlarmMessage) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+6, iAlarmIndex, (void*)lpAlarmMessage, 0);
    }

    inline LPWSTR GetAlarmRecipient(int iAlarmIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+7, iAlarmIndex, 0);
    }

    inline int SetAlarmRecipient(int iAlarmIndex, LPCWSTR lpAlarmRecipient) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+7, iAlarmIndex, (void*)lpAlarmRecipient, 0);
    }



    inline LPWSTR GetAlarmSubject(int iAlarmIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+9, iAlarmIndex, 0);
    }

    inline int SetAlarmSubject(int iAlarmIndex, LPCWSTR lpAlarmSubject) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+9, iAlarmIndex, (void*)lpAlarmSubject, 0);
    }

    inline LPWSTR GetAlarmTrigger(int iAlarmIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+10, iAlarmIndex, 0);
    }

    inline int SetAlarmTrigger(int iAlarmIndex, LPCWSTR lpAlarmTrigger) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+10, iAlarmIndex, (void*)lpAlarmTrigger, 0);
    }

    inline LPWSTR GetAttendees() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetAttendees(LPCWSTR lpAttendees) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+11, 0, (void*)lpAttendees, 0);
    }

    inline LPWSTR GetAuthorization() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetAuthorization(LPCWSTR lpAuthorization) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+12, 0, (void*)lpAuthorization, 0);
    }



    inline LPWSTR GetCategories() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetCategories(LPCWSTR lpCategories) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+14, 0, (void*)lpCategories, 0);
    }

    inline LPWSTR GetClassification() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetClassification(LPCWSTR lpClassification) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+15, 0, (void*)lpClassification, 0);
    }

    inline LPWSTR GetCompleted() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetCompleted(LPCWSTR lpCompleted) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+16, 0, (void*)lpCompleted, 0);
    }





    inline LPWSTR GetCookieDomain(int iCookieIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+19, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieExpiration(int iCookieIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+20, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieName(int iCookieIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+21, iCookieIndex, 0);
    }

    inline int SetCookieName(int iCookieIndex, LPCWSTR lpCookieName) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+21, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline LPWSTR GetCookiePath(int iCookieIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+22, iCookieIndex, 0);
    }





    inline LPWSTR GetCookieValue(int iCookieIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+24, iCookieIndex, 0);
    }

    inline int SetCookieValue(int iCookieIndex, LPCWSTR lpCookieValue) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+24, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline LPWSTR GetCreated() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+25, 0, 0);
    }

    inline int SetCreated(LPCWSTR lpCreated) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+25, 0, (void*)lpCreated, 0);
    }



    inline LPWSTR GetCustomPropertyAttribute(int iCustomPropertyIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+27, iCustomPropertyIndex, 0);
    }

    inline int SetCustomPropertyAttribute(int iCustomPropertyIndex, LPCWSTR lpCustomPropertyAttribute) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+27, iCustomPropertyIndex, (void*)lpCustomPropertyAttribute, 0);
    }

    inline LPWSTR GetCustomPropertyName(int iCustomPropertyIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+28, iCustomPropertyIndex, 0);
    }

    inline int SetCustomPropertyName(int iCustomPropertyIndex, LPCWSTR lpCustomPropertyName) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+28, iCustomPropertyIndex, (void*)lpCustomPropertyName, 0);
    }

    inline LPWSTR GetCustomPropertyValue(int iCustomPropertyIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+29, iCustomPropertyIndex, 0);
    }

    inline int SetCustomPropertyValue(int iCustomPropertyIndex, LPCWSTR lpCustomPropertyValue) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+29, iCustomPropertyIndex, (void*)lpCustomPropertyValue, 0);
    }



    inline LPWSTR GetDescription() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+31, 0, 0);
    }

    inline int SetDescription(LPCWSTR lpDescription) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+31, 0, (void*)lpDescription, 0);
    }

    inline LPWSTR GetDisplayName() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+32, 0, 0);
    }

    inline int SetDisplayName(LPCWSTR lpDisplayName) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+32, 0, (void*)lpDisplayName, 0);
    }

    inline LPWSTR GetDueDate() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+33, 0, 0);
    }

    inline int SetDueDate(LPCWSTR lpDueDate) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+33, 0, (void*)lpDueDate, 0);
    }

    inline LPWSTR GetDuration() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+34, 0, 0);
    }

    inline int SetDuration(LPCWSTR lpDuration) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+34, 0, (void*)lpDuration, 0);
    }

    inline LPWSTR GetEndDate() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+35, 0, 0);
    }

    inline int SetEndDate(LPCWSTR lpEndDate) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+35, 0, (void*)lpEndDate, 0);
    }

    inline LPWSTR GetETag() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+36, 0, 0);
    }

    inline int SetETag(LPCWSTR lpETag) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+36, 0, (void*)lpETag, 0);
    }







    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+40, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+40, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+41, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+41, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+43, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+43, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetFreeBusyRange(int iFreeBusyIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+46, iFreeBusyIndex, 0);
    }



    inline LPWSTR GetFreeBusyType(int iFreeBusyIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+47, iFreeBusyIndex, 0);
    }





    inline LPWSTR GetLastModified() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+49, 0, 0);
    }

    inline int SetLastModified(LPCWSTR lpLastModified) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+49, 0, (void*)lpLastModified, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+50, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+50, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetLocation() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+51, 0, 0);
    }

    inline int SetLocation(LPCWSTR lpLocation) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+51, 0, (void*)lpLocation, 0);
    }

    inline LPWSTR GetLockType() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+52, 0, 0);
    }

    inline int SetLockType(LPCWSTR lpLockType) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+52, 0, (void*)lpLockType, 0);
    }

    inline LPWSTR GetLockOwner() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+53, 0, 0);
    }

    inline int SetLockOwner(LPCWSTR lpLockOwner) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+53, 0, (void*)lpLockOwner, 0);
    }

    inline LPWSTR GetLockScope() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+54, 0, 0);
    }

    inline int SetLockScope(LPCWSTR lpLockScope) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+54, 0, (void*)lpLockScope, 0);
    }



    inline LPWSTR GetLockTokens() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+56, 0, 0);
    }

    inline int SetLockTokens(LPCWSTR lpLockTokens) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+56, 0, (void*)lpLockTokens, 0);
    }

    inline LPWSTR GetOrganizer() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+57, 0, 0);
    }

    inline int SetOrganizer(LPCWSTR lpOrganizer) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+57, 0, (void*)lpOrganizer, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+58, 0, 0);
    }

    inline int SetOtherHeaders(LPCWSTR lpOtherHeaders) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+58, 0, (void*)lpOtherHeaders, 0);
    }



    inline LPWSTR GetParsedHeaderField(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+60, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetParsedHeaderValue(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+61, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+62, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+62, 0, (void*)lpPassword, 0);
    }







    inline LPWSTR GetProxyPassword() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+66, 0, 0);
    }

    inline int SetProxyPassword(LPCWSTR lpProxyPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+66, 0, (void*)lpProxyPassword, 0);
    }



    inline LPWSTR GetProxyServer() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+68, 0, 0);
    }

    inline int SetProxyServer(LPCWSTR lpProxyServer) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+68, 0, (void*)lpProxyServer, 0);
    }



    inline LPWSTR GetProxyUser() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+70, 0, 0);
    }

    inline int SetProxyUser(LPCWSTR lpProxyUser) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+70, 0, (void*)lpProxyUser, 0);
    }

    inline LPWSTR GetRecurrenceDates() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+71, 0, 0);
    }

    inline int SetRecurrenceDates(LPCWSTR lpRecurrenceDates) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+71, 0, (void*)lpRecurrenceDates, 0);
    }

    inline LPWSTR GetRecurrenceExceptionDates() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+72, 0, 0);
    }

    inline int SetRecurrenceExceptionDates(LPCWSTR lpRecurrenceExceptionDates) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+72, 0, (void*)lpRecurrenceExceptionDates, 0);
    }

    inline LPWSTR GetRecurrenceExceptionRule() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+73, 0, 0);
    }

    inline int SetRecurrenceExceptionRule(LPCWSTR lpRecurrenceExceptionRule) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+73, 0, (void*)lpRecurrenceExceptionRule, 0);
    }

    inline LPWSTR GetRecurrenceId() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+74, 0, 0);
    }

    inline int SetRecurrenceId(LPCWSTR lpRecurrenceId) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+74, 0, (void*)lpRecurrenceId, 0);
    }

    inline LPWSTR GetRecurrenceRule() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+75, 0, 0);
    }

    inline int SetRecurrenceRule(LPCWSTR lpRecurrenceRule) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+75, 0, (void*)lpRecurrenceRule, 0);
    }

    inline LPWSTR GetReportFilterAlarmEnd() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+76, 0, 0);
    }

    inline int SetReportFilterAlarmEnd(LPCWSTR lpReportFilterAlarmEnd) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+76, 0, (void*)lpReportFilterAlarmEnd, 0);
    }

    inline LPWSTR GetReportFilterAlarmStart() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+77, 0, 0);
    }

    inline int SetReportFilterAlarmStart(LPCWSTR lpReportFilterAlarmStart) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+77, 0, (void*)lpReportFilterAlarmStart, 0);
    }

    inline LPWSTR GetReportFilterCustomFilter() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+78, 0, 0);
    }

    inline int SetReportFilterCustomFilter(LPCWSTR lpReportFilterCustomFilter) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+78, 0, (void*)lpReportFilterCustomFilter, 0);
    }

    inline LPWSTR GetReportFilterEndDate() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+79, 0, 0);
    }

    inline int SetReportFilterEndDate(LPCWSTR lpReportFilterEndDate) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+79, 0, (void*)lpReportFilterEndDate, 0);
    }



    inline LPWSTR GetReportFilterProperty() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+81, 0, 0);
    }

    inline int SetReportFilterProperty(LPCWSTR lpReportFilterProperty) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+81, 0, (void*)lpReportFilterProperty, 0);
    }

    inline LPWSTR GetReportFilterRecurEnd() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+82, 0, 0);
    }

    inline int SetReportFilterRecurEnd(LPCWSTR lpReportFilterRecurEnd) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+82, 0, (void*)lpReportFilterRecurEnd, 0);
    }

    inline LPWSTR GetReportFilterRecurStart() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+83, 0, 0);
    }

    inline int SetReportFilterRecurStart(LPCWSTR lpReportFilterRecurStart) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+83, 0, (void*)lpReportFilterRecurStart, 0);
    }



    inline LPWSTR GetReportFilterStartDate() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+85, 0, 0);
    }

    inline int SetReportFilterStartDate(LPCWSTR lpReportFilterStartDate) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+85, 0, (void*)lpReportFilterStartDate, 0);
    }

    inline LPWSTR GetReportFilterUID() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+86, 0, 0);
    }

    inline int SetReportFilterUID(LPCWSTR lpReportFilterUID) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+86, 0, (void*)lpReportFilterUID, 0);
    }



    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+88, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+88, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_CalDAV_Get(m_pObj, 88, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_CalDAV_Set(m_pObj, 88, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+89, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+89, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_CalDAV_Get(m_pObj, 89, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_CalDAV_Set(m_pObj, 89, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+90, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+90, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_CalDAV_Get(m_pObj, 90, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_CalDAV_Set(m_pObj, 90, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+91, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+91, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+93, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+93, 0, (void*)lpSSLCertSubject, 0);
    }

    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+94, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_CalDAV_Get(m_pObj, 94, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline LPWSTR GetStartDate() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+95, 0, 0);
    }

    inline int SetStartDate(LPCWSTR lpStartDate) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+95, 0, (void*)lpStartDate, 0);
    }

    inline LPWSTR GetStatus() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+96, 0, 0);
    }

    inline int SetStatus(LPCWSTR lpStatus) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+96, 0, (void*)lpStatus, 0);
    }

    inline LPWSTR GetStatusLine() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+97, 0, 0);
    }



    inline LPWSTR GetSummary() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+98, 0, 0);
    }

    inline int SetSummary(LPCWSTR lpSummary) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+98, 0, (void*)lpSummary, 0);
    }



    inline LPWSTR GetTimestamp() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+100, 0, 0);
    }

    inline int SetTimestamp(LPCWSTR lpTimestamp) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+100, 0, (void*)lpTimestamp, 0);
    }

    inline LPWSTR GetTimezoneDSTName() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+101, 0, 0);
    }

    inline int SetTimezoneDSTName(LPCWSTR lpTimezoneDSTName) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+101, 0, (void*)lpTimezoneDSTName, 0);
    }

    inline LPWSTR GetTimezoneDSTOffsetFrom() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+102, 0, 0);
    }

    inline int SetTimezoneDSTOffsetFrom(LPCWSTR lpTimezoneDSTOffsetFrom) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+102, 0, (void*)lpTimezoneDSTOffsetFrom, 0);
    }

    inline LPWSTR GetTimezoneDSTOffsetTo() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+103, 0, 0);
    }

    inline int SetTimezoneDSTOffsetTo(LPCWSTR lpTimezoneDSTOffsetTo) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+103, 0, (void*)lpTimezoneDSTOffsetTo, 0);
    }

    inline LPWSTR GetTimezoneDSTRule() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+104, 0, 0);
    }

    inline int SetTimezoneDSTRule(LPCWSTR lpTimezoneDSTRule) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+104, 0, (void*)lpTimezoneDSTRule, 0);
    }

    inline LPWSTR GetTimezoneDSTStart() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+105, 0, 0);
    }

    inline int SetTimezoneDSTStart(LPCWSTR lpTimezoneDSTStart) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+105, 0, (void*)lpTimezoneDSTStart, 0);
    }

    inline LPWSTR GetTimezoneLastModified() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+106, 0, 0);
    }

    inline int SetTimezoneLastModified(LPCWSTR lpTimezoneLastModified) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+106, 0, (void*)lpTimezoneLastModified, 0);
    }

    inline LPWSTR GetTimezoneStdName() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+107, 0, 0);
    }

    inline int SetTimezoneStdName(LPCWSTR lpTimezoneStdName) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+107, 0, (void*)lpTimezoneStdName, 0);
    }

    inline LPWSTR GetTimezoneStdOffsetFrom() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+108, 0, 0);
    }

    inline int SetTimezoneStdOffsetFrom(LPCWSTR lpTimezoneStdOffsetFrom) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+108, 0, (void*)lpTimezoneStdOffsetFrom, 0);
    }

    inline LPWSTR GetTimezoneStdOffsetTo() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+109, 0, 0);
    }

    inline int SetTimezoneStdOffsetTo(LPCWSTR lpTimezoneStdOffsetTo) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+109, 0, (void*)lpTimezoneStdOffsetTo, 0);
    }

    inline LPWSTR GetTimezoneStdRule() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+110, 0, 0);
    }

    inline int SetTimezoneStdRule(LPCWSTR lpTimezoneStdRule) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+110, 0, (void*)lpTimezoneStdRule, 0);
    }

    inline LPWSTR GetTimezoneStdStart() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+111, 0, 0);
    }

    inline int SetTimezoneStdStart(LPCWSTR lpTimezoneStdStart) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+111, 0, (void*)lpTimezoneStdStart, 0);
    }

    inline LPWSTR GetTimezoneId() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+112, 0, 0);
    }

    inline int SetTimezoneId(LPCWSTR lpTimezoneId) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+112, 0, (void*)lpTimezoneId, 0);
    }

    inline LPWSTR GetTimezoneURL() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+113, 0, 0);
    }

    inline int SetTimezoneURL(LPCWSTR lpTimezoneURL) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+113, 0, (void*)lpTimezoneURL, 0);
    }

    inline LPWSTR GetTransparency() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+114, 0, 0);
    }

    inline int SetTransparency(LPCWSTR lpTransparency) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+114, 0, (void*)lpTransparency, 0);
    }

    inline LPWSTR GetUID() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+115, 0, 0);
    }

    inline int SetUID(LPCWSTR lpUID) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+115, 0, (void*)lpUID, 0);
    }

    inline LPWSTR GetURL() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+116, 0, 0);
    }



    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_CalDAV_Get(m_pObj, 10000+117, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_CalDAV_Set(m_pObj, 10000+117, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnected(CalDAVConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(CalDAVConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(CalDAVDisconnectedEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(CalDAVEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(CalDAVErrorEventParamsW *e) {return 0;}
    virtual int FireEventDetails(CalDAVEventDetailsEventParamsW *e) {return 0;}
    virtual int FireFreeBusy(CalDAVFreeBusyEventParamsW *e) {return 0;}
    virtual int FireHeader(CalDAVHeaderEventParamsW *e) {return 0;}
    virtual int FireLog(CalDAVLogEventParamsW *e) {return 0;}
    virtual int FireRedirect(CalDAVRedirectEventParamsW *e) {return 0;}
    virtual int FireSetCookie(CalDAVSetCookieEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(CalDAVSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(CalDAVSSLStatusEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(CalDAVStartTransferEventParamsW *e) {return 0;}
    virtual int FireStatus(CalDAVStatusEventParamsW *e) {return 0;}
    virtual int FireTransfer(CalDAVTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int CalDAVEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            CalDAVConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            CalDAVConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            CalDAVDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            CalDAVEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 5: {
            CalDAVErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            CalDAVEventDetailsEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]),  0};
            ret_code = FireEventDetails(&e);
            break;
         }
         case 7: {
            CalDAVFreeBusyEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireFreeBusy(&e);
            break;
         }
         case 8: {
            CalDAVHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 9: {
            CalDAVLogEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireLog(&e);
            break;
         }
         case 10: {
            CalDAVRedirectEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = FireRedirect(&e);
            param[1] = (void*)(e.Accept);
            break;
         }
         case 11: {
            CalDAVSetCookieEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = FireSetCookie(&e);
            break;
         }
         case 12: {
            CalDAVSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 13: {
            CalDAVSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }
         case 14: {
            CalDAVStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 15: {
            CalDAVStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireStatus(&e);
            break;
         }
         case 16: {
            CalDAVTransferEventParamsW e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(CalDAVConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(CalDAVConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(CalDAVDisconnectedEventParams *e) {return -10000;}
    virtual int FireEndTransfer(CalDAVEndTransferEventParams *e) {return -10000;}
    virtual int FireError(CalDAVErrorEventParams *e) {return -10000;}
    virtual int FireEventDetails(CalDAVEventDetailsEventParams *e) {return -10000;}
    virtual int FireFreeBusy(CalDAVFreeBusyEventParams *e) {return -10000;}
    virtual int FireHeader(CalDAVHeaderEventParams *e) {return -10000;}
    virtual int FireLog(CalDAVLogEventParams *e) {return -10000;}
    virtual int FireRedirect(CalDAVRedirectEventParams *e) {return -10000;}
    virtual int FireSetCookie(CalDAVSetCookieEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(CalDAVSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(CalDAVSSLStatusEventParams *e) {return -10000;}
    virtual int FireStartTransfer(CalDAVStartTransferEventParams *e) {return -10000;}
    virtual int FireStatus(CalDAVStatusEventParams *e) {return -10000;}
    virtual int FireTransfer(CalDAVTransferEventParams *e) {return -10000;}

  public: //methods

    inline int AddCookie(LPWSTR lpszCookieName, LPWSTR lpszCookieValue) {
      void *param[2+1] = {(void*)lpszCookieName, (void*)lpszCookieValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+2, 2, param, cbparam);
      
    }
    inline int AddCustomProperty(LPWSTR lpszVarName, LPWSTR lpszVarValue) {
      void *param[2+1] = {(void*)lpszVarName, (void*)lpszVarValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+3, 2, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_CalDAV_Do(m_pObj, 10000+4, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int CopyCalendarEvent(LPWSTR lpszSourceResourceURI, LPWSTR lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)lpszSourceResourceURI, (void*)lpszDestinationResourceURI, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+5, 2, param, cbparam);
      
    }
    inline int CreateCalendar(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+6, 1, param, cbparam);
      
    }
    inline int DeleteCalendarEvent(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+7, 1, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline LPWSTR ExportICS() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CalDAV_Do(m_pObj, 10000+9, 0, param, cbparam);
      return (LPWSTR)IPW64CAST(param[0]);
    }
    inline int GetCalendarEvent(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+10, 1, param, cbparam);
      
    }
    inline int GetCalendarOptions(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+11, 1, param, cbparam);
      
    }
    inline int GetCalendarReport(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+12, 1, param, cbparam);
      
    }
    inline int GetFreeBusyReport(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+13, 1, param, cbparam);
      
    }
    inline int ImportICS(LPWSTR lpszCalendarData) {
      void *param[1+1] = {(void*)lpszCalendarData, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+14, 1, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+15, 0, param, cbparam);
      
    }
    inline int LockCalendar(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+16, 1, param, cbparam);
      
    }
    inline int MoveCalendarEvent(LPWSTR lpszSourceResourceURI, LPWSTR lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)lpszSourceResourceURI, (void*)lpszDestinationResourceURI, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+17, 2, param, cbparam);
      
    }
    inline int PutCalendarEvent(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+18, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+19, 0, param, cbparam);
      
    }
    inline int UnLockCalendar(LPWSTR lpszResourceURI) {
      void *param[1+1] = {(void*)lpszResourceURI, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10000+20, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_CALDAV_H_




