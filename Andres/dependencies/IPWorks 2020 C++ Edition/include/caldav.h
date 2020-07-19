/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

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
#define CST_SECURITY_KEY                                   20
#define CST_AUTO                                           99


extern "C" void* IPWORKS_CALL IPWorks_CalDAV_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_CalDAV_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_CalDAV_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_CalDAV_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_SetEventErrorAndCode(void *lpObj, int code, char *message);
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
  const char *Description;
  int reserved;
} CalDAVConnectedEventParams;

typedef struct {
  const char *ConnectionEvent;
  int StatusCode;
  const char *Description;
  int reserved;
} CalDAVConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char *Description;
  int reserved;
} CalDAVDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} CalDAVEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} CalDAVErrorEventParams;

typedef struct {
  const char *ResourceURI;
  const char *ResponseStatus;
  const char *ETag;
  const char *CalendarData;
  int reserved;
} CalDAVEventDetailsEventParams;

typedef struct {
  const char *BusyType;
  const char *BusyRange;
  int reserved;
} CalDAVFreeBusyEventParams;

typedef struct {
  const char *Field;
  const char *Value;
  int reserved;
} CalDAVHeaderEventParams;

typedef struct {
  int LogLevel;
  const char *Message;
  const char *LogType;
  int reserved;
} CalDAVLogEventParams;

typedef struct {
  const char *Location;
  int Accept;
  int reserved;
} CalDAVRedirectEventParams;

typedef struct {
  const char *Name;
  const char *Value;
  const char *Expires;
  const char *Domain;
  const char *Path;
  int Secure;
  int reserved;
} CalDAVSetCookieEventParams;

typedef struct {
  const char *CertEncoded;
  int lenCertEncoded;
  const char *CertSubject;
  const char *CertIssuer;
  const char *Status;
  int Accept;
  int reserved;
} CalDAVSSLServerAuthenticationEventParams;

typedef struct {
  const char *Message;
  int reserved;
} CalDAVSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} CalDAVStartTransferEventParams;

typedef struct {
  const char *HTTPVersion;
  int StatusCode;
  const char *Description;
  int reserved;
} CalDAVStatusEventParams;

typedef struct {
  int Direction;
  int64 BytesTransferred;
  int PercentDone;
  const char *Text;
  int lenText;
  int reserved;
} CalDAVTransferEventParams;


class CalDAV {
  public: // Events
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
      switch (event_id) {
        case 1: {
          CalDAVConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((CalDAV*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          CalDAVConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((CalDAV*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          CalDAVDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((CalDAV*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          CalDAVEndTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((CalDAV*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          CalDAVErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((CalDAV*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          CalDAVEventDetailsEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), 0};
          ret_code = ((CalDAV*)lpObj)->FireEventDetails(&e);
          break;
        }
        case 7: {
          CalDAVFreeBusyEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((CalDAV*)lpObj)->FireFreeBusy(&e);
          break;
        }
        case 8: {
          CalDAVHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((CalDAV*)lpObj)->FireHeader(&e);
          break;
        }
        case 9: {
          CalDAVLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((CalDAV*)lpObj)->FireLog(&e);
          break;
        }
        case 10: {
          CalDAVRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), 0};
          ret_code = ((CalDAV*)lpObj)->FireRedirect(&e);
          param[1] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 11: {
          CalDAVSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]), 0};
          ret_code = ((CalDAV*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 12: {
          CalDAVSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), 0};
          ret_code = ((CalDAV*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (void*)IPW64CAST(e.Accept);
          break;
        }
        case 13: {
          CalDAVSSLStatusEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((CalDAV*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 14: {
          CalDAVStartTransferEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((CalDAV*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 15: {
          CalDAVStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), 0};
          ret_code = ((CalDAV*)lpObj)->FireStatus(&e);
          break;
        }
        case 16: {
          CalDAVTransferEventParams e = {(int)IPW64CAST(param[0]), *(int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]), 0};
          ret_code = ((CalDAV*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    CalDAV(char *lpOemKey = (char*)IPWORKS_OEMKEY_98) {
      m_pObj = IPWorks_CalDAV_Create(CalDAVEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~CalDAV() {
      IPWorks_CalDAV_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_CalDAV_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_CalDAV_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_CalDAV_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_CalDAV_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_CalDAV_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetAlarmCount() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAlarmCount(int iAlarmCount) {
      void* val = (void*)IPW64CAST(iAlarmCount);
      return IPWorks_CalDAV_Set(m_pObj, 1, 0, val, 0);
    }

    inline int GetAlarmAction(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 2, iAlarmIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAlarmAction(int iAlarmIndex, int iAlarmAction) {
      void* val = (void*)IPW64CAST(iAlarmAction);
      return IPWorks_CalDAV_Set(m_pObj, 2, iAlarmIndex, val, 0);
    }

    inline char* GetAlarmAttachment(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 3, iAlarmIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetAlarmAttachment(int iAlarmIndex, const char* lpszAlarmAttachment) {
      return IPWorks_CalDAV_Set(m_pObj, 3, iAlarmIndex, (void*)lpszAlarmAttachment, 0);
    }

    inline char* GetAlarmAttachmentType(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 4, iAlarmIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetAlarmAttachmentType(int iAlarmIndex, const char* lpszAlarmAttachmentType) {
      return IPWorks_CalDAV_Set(m_pObj, 4, iAlarmIndex, (void*)lpszAlarmAttachmentType, 0);
    }

    inline char* GetAlarmDuration(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 5, iAlarmIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetAlarmDuration(int iAlarmIndex, const char* lpszAlarmDuration) {
      return IPWorks_CalDAV_Set(m_pObj, 5, iAlarmIndex, (void*)lpszAlarmDuration, 0);
    }

    inline char* GetAlarmMessage(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 6, iAlarmIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetAlarmMessage(int iAlarmIndex, const char* lpszAlarmMessage) {
      return IPWorks_CalDAV_Set(m_pObj, 6, iAlarmIndex, (void*)lpszAlarmMessage, 0);
    }

    inline char* GetAlarmRecipient(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 7, iAlarmIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetAlarmRecipient(int iAlarmIndex, const char* lpszAlarmRecipient) {
      return IPWorks_CalDAV_Set(m_pObj, 7, iAlarmIndex, (void*)lpszAlarmRecipient, 0);
    }

    inline int GetAlarmRepeat(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 8, iAlarmIndex, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAlarmRepeat(int iAlarmIndex, int iAlarmRepeat) {
      void* val = (void*)IPW64CAST(iAlarmRepeat);
      return IPWorks_CalDAV_Set(m_pObj, 8, iAlarmIndex, val, 0);
    }

    inline char* GetAlarmSubject(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 9, iAlarmIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetAlarmSubject(int iAlarmIndex, const char* lpszAlarmSubject) {
      return IPWorks_CalDAV_Set(m_pObj, 9, iAlarmIndex, (void*)lpszAlarmSubject, 0);
    }

    inline char* GetAlarmTrigger(int iAlarmIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 10, iAlarmIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetAlarmTrigger(int iAlarmIndex, const char* lpszAlarmTrigger) {
      return IPWorks_CalDAV_Set(m_pObj, 10, iAlarmIndex, (void*)lpszAlarmTrigger, 0);
    }

    inline char* GetAttendees() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAttendees(const char* lpszAttendees) {
      return IPWorks_CalDAV_Set(m_pObj, 11, 0, (void*)lpszAttendees, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 12, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetAuthorization(const char* lpszAuthorization) {
      return IPWorks_CalDAV_Set(m_pObj, 12, 0, (void*)lpszAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 13, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_CalDAV_Set(m_pObj, 13, 0, val, 0);
    }

    inline char* GetCategories() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCategories(const char* lpszCategories) {
      return IPWorks_CalDAV_Set(m_pObj, 14, 0, (void*)lpszCategories, 0);
    }

    inline char* GetClassification() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetClassification(const char* lpszClassification) {
      return IPWorks_CalDAV_Set(m_pObj, 15, 0, (void*)lpszClassification, 0);
    }

    inline char* GetCompleted() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCompleted(const char* lpszCompleted) {
      return IPWorks_CalDAV_Set(m_pObj, 16, 0, (void*)lpszCompleted, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 17, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_CalDAV_Set(m_pObj, 17, 0, val, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 18, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_CalDAV_Set(m_pObj, 18, 0, val, 0);
    }

    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 19, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 20, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 21, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieName(int iCookieIndex, const char* lpszCookieName) {
      return IPWorks_CalDAV_Set(m_pObj, 21, iCookieIndex, (void*)lpszCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 22, iCookieIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 23, iCookieIndex, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 24, iCookieIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCookieValue(int iCookieIndex, const char* lpszCookieValue) {
      return IPWorks_CalDAV_Set(m_pObj, 24, iCookieIndex, (void*)lpszCookieValue, 0);
    }

    inline char* GetCreated() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 25, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetCreated(const char* lpszCreated) {
      return IPWorks_CalDAV_Set(m_pObj, 25, 0, (void*)lpszCreated, 0);
    }

    inline int GetCustomPropertyCount() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 26, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetCustomPropertyCount(int iCustomPropertyCount) {
      void* val = (void*)IPW64CAST(iCustomPropertyCount);
      return IPWorks_CalDAV_Set(m_pObj, 26, 0, val, 0);
    }

    inline char* GetCustomPropertyAttribute(int iCustomPropertyIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 27, iCustomPropertyIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCustomPropertyAttribute(int iCustomPropertyIndex, const char* lpszCustomPropertyAttribute) {
      return IPWorks_CalDAV_Set(m_pObj, 27, iCustomPropertyIndex, (void*)lpszCustomPropertyAttribute, 0);
    }

    inline char* GetCustomPropertyName(int iCustomPropertyIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 28, iCustomPropertyIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCustomPropertyName(int iCustomPropertyIndex, const char* lpszCustomPropertyName) {
      return IPWorks_CalDAV_Set(m_pObj, 28, iCustomPropertyIndex, (void*)lpszCustomPropertyName, 0);
    }

    inline char* GetCustomPropertyValue(int iCustomPropertyIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 29, iCustomPropertyIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetCustomPropertyValue(int iCustomPropertyIndex, const char* lpszCustomPropertyValue) {
      return IPWorks_CalDAV_Set(m_pObj, 29, iCustomPropertyIndex, (void*)lpszCustomPropertyValue, 0);
    }

    inline int GetDepth() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 30, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetDepth(int iDepth) {
      void* val = (void*)IPW64CAST(iDepth);
      return IPWorks_CalDAV_Set(m_pObj, 30, 0, val, 0);
    }

    inline char* GetDescription() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 31, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetDescription(const char* lpszDescription) {
      return IPWorks_CalDAV_Set(m_pObj, 31, 0, (void*)lpszDescription, 0);
    }

    inline char* GetDisplayName() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 32, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetDisplayName(const char* lpszDisplayName) {
      return IPWorks_CalDAV_Set(m_pObj, 32, 0, (void*)lpszDisplayName, 0);
    }

    inline char* GetDueDate() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 33, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetDueDate(const char* lpszDueDate) {
      return IPWorks_CalDAV_Set(m_pObj, 33, 0, (void*)lpszDueDate, 0);
    }

    inline char* GetDuration() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 34, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetDuration(const char* lpszDuration) {
      return IPWorks_CalDAV_Set(m_pObj, 34, 0, (void*)lpszDuration, 0);
    }

    inline char* GetEndDate() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 35, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetEndDate(const char* lpszEndDate) {
      return IPWorks_CalDAV_Set(m_pObj, 35, 0, (void*)lpszEndDate, 0);
    }

    inline char* GetETag() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 36, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetETag(const char* lpszETag) {
      return IPWorks_CalDAV_Set(m_pObj, 36, 0, (void*)lpszETag, 0);
    }

    inline int GetEventType() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 37, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetEventType(int iEventType) {
      void* val = (void*)IPW64CAST(iEventType);
      return IPWorks_CalDAV_Set(m_pObj, 37, 0, val, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 38, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_CalDAV_Set(m_pObj, 38, 0, val, 0);
    }

    inline int GetFirewallType() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 39, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_CalDAV_Set(m_pObj, 39, 0, val, 0);
    }

    inline char* GetFirewallHost() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 40, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallHost(const char* lpszFirewallHost) {
      return IPWorks_CalDAV_Set(m_pObj, 40, 0, (void*)lpszFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 41, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallPassword(const char* lpszFirewallPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 41, 0, (void*)lpszFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 42, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int iFirewallPort) {
      void* val = (void*)IPW64CAST(iFirewallPort);
      return IPWorks_CalDAV_Set(m_pObj, 42, 0, val, 0);
    }

    inline char* GetFirewallUser() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 43, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetFirewallUser(const char* lpszFirewallUser) {
      return IPWorks_CalDAV_Set(m_pObj, 43, 0, (void*)lpszFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 44, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_CalDAV_Set(m_pObj, 44, 0, val, 0);
    }

    inline int GetFreeBusyCount() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 45, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetFreeBusyRange(int iFreeBusyIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 46, iFreeBusyIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetFreeBusyType(int iFreeBusyIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 47, iFreeBusyIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetIdle() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 48, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetLastModified() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 49, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLastModified(const char* lpszLastModified) {
      return IPWorks_CalDAV_Set(m_pObj, 49, 0, (void*)lpszLastModified, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 50, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocalHost(const char* lpszLocalHost) {
      return IPWorks_CalDAV_Set(m_pObj, 50, 0, (void*)lpszLocalHost, 0);
    }

    inline char* GetLocation() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 51, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLocation(const char* lpszLocation) {
      return IPWorks_CalDAV_Set(m_pObj, 51, 0, (void*)lpszLocation, 0);
    }

    inline char* GetLockType() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 52, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLockType(const char* lpszLockType) {
      return IPWorks_CalDAV_Set(m_pObj, 52, 0, (void*)lpszLockType, 0);
    }

    inline char* GetLockOwner() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 53, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLockOwner(const char* lpszLockOwner) {
      return IPWorks_CalDAV_Set(m_pObj, 53, 0, (void*)lpszLockOwner, 0);
    }

    inline char* GetLockScope() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 54, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLockScope(const char* lpszLockScope) {
      return IPWorks_CalDAV_Set(m_pObj, 54, 0, (void*)lpszLockScope, 0);
    }

    inline int GetLockTimeout() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 55, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetLockTimeout(int iLockTimeout) {
      void* val = (void*)IPW64CAST(iLockTimeout);
      return IPWorks_CalDAV_Set(m_pObj, 55, 0, val, 0);
    }

    inline char* GetLockTokens() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 56, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetLockTokens(const char* lpszLockTokens) {
      return IPWorks_CalDAV_Set(m_pObj, 56, 0, (void*)lpszLockTokens, 0);
    }

    inline char* GetOrganizer() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 57, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOrganizer(const char* lpszOrganizer) {
      return IPWorks_CalDAV_Set(m_pObj, 57, 0, (void*)lpszOrganizer, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 58, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOtherHeaders(const char* lpszOtherHeaders) {
      return IPWorks_CalDAV_Set(m_pObj, 58, 0, (void*)lpszOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 59, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 60, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_CalDAV_Get(m_pObj, 61, iParsedHeaderIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetPassword() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 62, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetPassword(const char* lpszPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 62, 0, (void*)lpszPassword, 0);
    }

    inline int GetPriority() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 63, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetPriority(int iPriority) {
      void* val = (void*)IPW64CAST(iPriority);
      return IPWorks_CalDAV_Set(m_pObj, 63, 0, val, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 64, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_CalDAV_Set(m_pObj, 64, 0, val, 0);
    }

    inline int GetProxyAutoDetect() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 65, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_CalDAV_Set(m_pObj, 65, 0, val, 0);
    }

    inline char* GetProxyPassword() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 66, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyPassword(const char* lpszProxyPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 66, 0, (void*)lpszProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 67, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxyPort(int iProxyPort) {
      void* val = (void*)IPW64CAST(iProxyPort);
      return IPWorks_CalDAV_Set(m_pObj, 67, 0, val, 0);
    }

    inline char* GetProxyServer() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 68, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyServer(const char* lpszProxyServer) {
      return IPWorks_CalDAV_Set(m_pObj, 68, 0, (void*)lpszProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 69, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_CalDAV_Set(m_pObj, 69, 0, val, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 70, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetProxyUser(const char* lpszProxyUser) {
      return IPWorks_CalDAV_Set(m_pObj, 70, 0, (void*)lpszProxyUser, 0);
    }

    inline char* GetRecurrenceDates() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 71, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRecurrenceDates(const char* lpszRecurrenceDates) {
      return IPWorks_CalDAV_Set(m_pObj, 71, 0, (void*)lpszRecurrenceDates, 0);
    }

    inline char* GetRecurrenceExceptionDates() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 72, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRecurrenceExceptionDates(const char* lpszRecurrenceExceptionDates) {
      return IPWorks_CalDAV_Set(m_pObj, 72, 0, (void*)lpszRecurrenceExceptionDates, 0);
    }

    inline char* GetRecurrenceExceptionRule() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 73, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRecurrenceExceptionRule(const char* lpszRecurrenceExceptionRule) {
      return IPWorks_CalDAV_Set(m_pObj, 73, 0, (void*)lpszRecurrenceExceptionRule, 0);
    }

    inline char* GetRecurrenceId() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 74, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRecurrenceId(const char* lpszRecurrenceId) {
      return IPWorks_CalDAV_Set(m_pObj, 74, 0, (void*)lpszRecurrenceId, 0);
    }

    inline char* GetRecurrenceRule() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 75, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetRecurrenceRule(const char* lpszRecurrenceRule) {
      return IPWorks_CalDAV_Set(m_pObj, 75, 0, (void*)lpszRecurrenceRule, 0);
    }

    inline char* GetReportFilterAlarmEnd() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 76, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReportFilterAlarmEnd(const char* lpszReportFilterAlarmEnd) {
      return IPWorks_CalDAV_Set(m_pObj, 76, 0, (void*)lpszReportFilterAlarmEnd, 0);
    }

    inline char* GetReportFilterAlarmStart() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 77, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReportFilterAlarmStart(const char* lpszReportFilterAlarmStart) {
      return IPWorks_CalDAV_Set(m_pObj, 77, 0, (void*)lpszReportFilterAlarmStart, 0);
    }

    inline char* GetReportFilterCustomFilter() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 78, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReportFilterCustomFilter(const char* lpszReportFilterCustomFilter) {
      return IPWorks_CalDAV_Set(m_pObj, 78, 0, (void*)lpszReportFilterCustomFilter, 0);
    }

    inline char* GetReportFilterEndDate() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 79, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReportFilterEndDate(const char* lpszReportFilterEndDate) {
      return IPWorks_CalDAV_Set(m_pObj, 79, 0, (void*)lpszReportFilterEndDate, 0);
    }

    inline int GetReportFilterEventType() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 80, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetReportFilterEventType(int iReportFilterEventType) {
      void* val = (void*)IPW64CAST(iReportFilterEventType);
      return IPWorks_CalDAV_Set(m_pObj, 80, 0, val, 0);
    }

    inline char* GetReportFilterProperty() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 81, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReportFilterProperty(const char* lpszReportFilterProperty) {
      return IPWorks_CalDAV_Set(m_pObj, 81, 0, (void*)lpszReportFilterProperty, 0);
    }

    inline char* GetReportFilterRecurEnd() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 82, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReportFilterRecurEnd(const char* lpszReportFilterRecurEnd) {
      return IPWorks_CalDAV_Set(m_pObj, 82, 0, (void*)lpszReportFilterRecurEnd, 0);
    }

    inline char* GetReportFilterRecurStart() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 83, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReportFilterRecurStart(const char* lpszReportFilterRecurStart) {
      return IPWorks_CalDAV_Set(m_pObj, 83, 0, (void*)lpszReportFilterRecurStart, 0);
    }

    inline int GetReportFilterReturnCalendarData() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 84, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetReportFilterReturnCalendarData(int bReportFilterReturnCalendarData) {
      void* val = (void*)IPW64CAST(bReportFilterReturnCalendarData);
      return IPWorks_CalDAV_Set(m_pObj, 84, 0, val, 0);
    }

    inline char* GetReportFilterStartDate() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 85, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReportFilterStartDate(const char* lpszReportFilterStartDate) {
      return IPWorks_CalDAV_Set(m_pObj, 85, 0, (void*)lpszReportFilterStartDate, 0);
    }

    inline char* GetReportFilterUID() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 86, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetReportFilterUID(const char* lpszReportFilterUID) {
      return IPWorks_CalDAV_Set(m_pObj, 86, 0, (void*)lpszReportFilterUID, 0);
    }

    inline int GetSequence() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 87, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSequence(int iSequence) {
      void* val = (void*)IPW64CAST(iSequence);
      return IPWorks_CalDAV_Set(m_pObj, 87, 0, val, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char* &lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_CalDAV_Get(m_pObj, 88, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncoded(const char* lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_CalDAV_Set(m_pObj, 88, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char* &lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_CalDAV_Get(m_pObj, 89, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncoded(const char* lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_CalDAV_Set(m_pObj, 89, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char* &lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_CalDAV_Get(m_pObj, 90, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStore(const char* lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_CalDAV_Set(m_pObj, 90, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 91, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertStorePassword(const char* lpszSSLCertStorePassword) {
      return IPWorks_CalDAV_Set(m_pObj, 91, 0, (void*)lpszSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 92, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_CalDAV_Set(m_pObj, 92, 0, val, 0);
    }

    inline char* GetSSLCertSubject() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 93, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSSLCertSubject(const char* lpszSSLCertSubject) {
      return IPWorks_CalDAV_Set(m_pObj, 93, 0, (void*)lpszSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char* &lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_CalDAV_Get(m_pObj, 94, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline char* GetStartDate() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 95, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetStartDate(const char* lpszStartDate) {
      return IPWorks_CalDAV_Set(m_pObj, 95, 0, (void*)lpszStartDate, 0);
    }

    inline char* GetStatus() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 96, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetStatus(const char* lpszStatus) {
      return IPWorks_CalDAV_Set(m_pObj, 96, 0, (void*)lpszStatus, 0);
    }

    inline char* GetStatusLine() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 97, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetSummary() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 98, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetSummary(const char* lpszSummary) {
      return IPWorks_CalDAV_Set(m_pObj, 98, 0, (void*)lpszSummary, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 99, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_CalDAV_Set(m_pObj, 99, 0, val, 0);
    }

    inline char* GetTimestamp() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 100, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimestamp(const char* lpszTimestamp) {
      return IPWorks_CalDAV_Set(m_pObj, 100, 0, (void*)lpszTimestamp, 0);
    }

    inline char* GetTimezoneDSTName() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 101, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneDSTName(const char* lpszTimezoneDSTName) {
      return IPWorks_CalDAV_Set(m_pObj, 101, 0, (void*)lpszTimezoneDSTName, 0);
    }

    inline char* GetTimezoneDSTOffsetFrom() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 102, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneDSTOffsetFrom(const char* lpszTimezoneDSTOffsetFrom) {
      return IPWorks_CalDAV_Set(m_pObj, 102, 0, (void*)lpszTimezoneDSTOffsetFrom, 0);
    }

    inline char* GetTimezoneDSTOffsetTo() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 103, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneDSTOffsetTo(const char* lpszTimezoneDSTOffsetTo) {
      return IPWorks_CalDAV_Set(m_pObj, 103, 0, (void*)lpszTimezoneDSTOffsetTo, 0);
    }

    inline char* GetTimezoneDSTRule() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 104, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneDSTRule(const char* lpszTimezoneDSTRule) {
      return IPWorks_CalDAV_Set(m_pObj, 104, 0, (void*)lpszTimezoneDSTRule, 0);
    }

    inline char* GetTimezoneDSTStart() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 105, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneDSTStart(const char* lpszTimezoneDSTStart) {
      return IPWorks_CalDAV_Set(m_pObj, 105, 0, (void*)lpszTimezoneDSTStart, 0);
    }

    inline char* GetTimezoneLastModified() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 106, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneLastModified(const char* lpszTimezoneLastModified) {
      return IPWorks_CalDAV_Set(m_pObj, 106, 0, (void*)lpszTimezoneLastModified, 0);
    }

    inline char* GetTimezoneStdName() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 107, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneStdName(const char* lpszTimezoneStdName) {
      return IPWorks_CalDAV_Set(m_pObj, 107, 0, (void*)lpszTimezoneStdName, 0);
    }

    inline char* GetTimezoneStdOffsetFrom() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 108, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneStdOffsetFrom(const char* lpszTimezoneStdOffsetFrom) {
      return IPWorks_CalDAV_Set(m_pObj, 108, 0, (void*)lpszTimezoneStdOffsetFrom, 0);
    }

    inline char* GetTimezoneStdOffsetTo() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 109, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneStdOffsetTo(const char* lpszTimezoneStdOffsetTo) {
      return IPWorks_CalDAV_Set(m_pObj, 109, 0, (void*)lpszTimezoneStdOffsetTo, 0);
    }

    inline char* GetTimezoneStdRule() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 110, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneStdRule(const char* lpszTimezoneStdRule) {
      return IPWorks_CalDAV_Set(m_pObj, 110, 0, (void*)lpszTimezoneStdRule, 0);
    }

    inline char* GetTimezoneStdStart() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 111, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneStdStart(const char* lpszTimezoneStdStart) {
      return IPWorks_CalDAV_Set(m_pObj, 111, 0, (void*)lpszTimezoneStdStart, 0);
    }

    inline char* GetTimezoneId() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 112, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneId(const char* lpszTimezoneId) {
      return IPWorks_CalDAV_Set(m_pObj, 112, 0, (void*)lpszTimezoneId, 0);
    }

    inline char* GetTimezoneURL() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 113, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTimezoneURL(const char* lpszTimezoneURL) {
      return IPWorks_CalDAV_Set(m_pObj, 113, 0, (void*)lpszTimezoneURL, 0);
    }

    inline char* GetTransparency() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 114, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetTransparency(const char* lpszTransparency) {
      return IPWorks_CalDAV_Set(m_pObj, 114, 0, (void*)lpszTransparency, 0);
    }

    inline char* GetUID() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 115, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUID(const char* lpszUID) {
      return IPWorks_CalDAV_Set(m_pObj, 115, 0, (void*)lpszUID, 0);
    }

    inline char* GetURL() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 116, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetUser() {
      void* val = IPWorks_CalDAV_Get(m_pObj, 117, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetUser(const char* lpszUser) {
      return IPWorks_CalDAV_Set(m_pObj, 117, 0, (void*)lpszUser, 0);
    }

  public: // Methods
    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 2, 2, param, cbparam, NULL);
    }

    inline int AddCustomProperty(const char* lpszVarName, const char* lpszVarValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszVarName), (void*)IPW64CAST(lpszVarValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 3, 2, param, cbparam, NULL);
    }

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_CalDAV_Do(m_pObj, 4, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int CopyCalendarEvent(const char* lpszSourceResourceURI, const char* lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszSourceResourceURI), (void*)IPW64CAST(lpszDestinationResourceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 5, 2, param, cbparam, NULL);
    }

    inline int CreateCalendar(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 6, 1, param, cbparam, NULL);
    }

    inline int DeleteCalendarEvent(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 7, 1, param, cbparam, NULL);
    }

    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline char* ExportICS() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_CalDAV_Do(m_pObj, 9, 0, param, cbparam, NULL);
      return (char*)IPW64CAST(param[0]);
    }

    inline int GetCalendarEvent(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10, 1, param, cbparam, NULL);
    }

    inline int GetCalendarOptions(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 11, 1, param, cbparam, NULL);
    }

    inline int GetCalendarReport(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 12, 1, param, cbparam, NULL);
    }

    inline int GetFreeBusyReport(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 13, 1, param, cbparam, NULL);
    }

    inline int ImportICS(const char* lpszCalendarData) {
      void *param[1+1] = {(void*)IPW64CAST(lpszCalendarData), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 14, 1, param, cbparam, NULL);
    }

    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 15, 0, param, cbparam, NULL);
    }

    inline int LockCalendar(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 16, 1, param, cbparam, NULL);
    }

    inline int MoveCalendarEvent(const char* lpszSourceResourceURI, const char* lpszDestinationResourceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszSourceResourceURI), (void*)IPW64CAST(lpszDestinationResourceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 17, 2, param, cbparam, NULL);
    }

    inline int PutCalendarEvent(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 18, 1, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 19, 0, param, cbparam, NULL);
    }

    inline int UnLockCalendar(const char* lpszResourceURI) {
      void *param[1+1] = {(void*)IPW64CAST(lpszResourceURI), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 20, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_CALDAV_H_
