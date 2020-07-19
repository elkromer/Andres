/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
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
extern "C" void* IPWORKS_CALL IPWorks_CalDAV_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_CalDAV_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_CalDAV_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_CalDAV_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} CalDAVConnectedEventParams;

typedef struct {
  LPCWSTR ConnectionEvent;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} CalDAVConnectionStatusEventParams;

typedef struct {
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} CalDAVDisconnectedEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} CalDAVEndTransferEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} CalDAVErrorEventParams;

typedef struct {
  LPCWSTR ResourceURI;
  LPCWSTR ResponseStatus;
  LPCWSTR ETag;
  LPCWSTR CalendarData;
  INT reserved;
} CalDAVEventDetailsEventParams;

typedef struct {
  LPCWSTR BusyType;
  LPCWSTR BusyRange;
  INT reserved;
} CalDAVFreeBusyEventParams;

typedef struct {
  LPCWSTR Field;
  LPCWSTR Value;
  INT reserved;
} CalDAVHeaderEventParams;

typedef struct {
  INT LogLevel;
  LPCWSTR Message;
  LPCWSTR LogType;
  INT reserved;
} CalDAVLogEventParams;

typedef struct {
  LPCWSTR Location;
  BOOL Accept;
  INT reserved;
} CalDAVRedirectEventParams;

typedef struct {
  LPCWSTR Name;
  LPCWSTR Value;
  LPCWSTR Expires;
  LPCWSTR Domain;
  LPCWSTR Path;
  BOOL Secure;
  INT reserved;
} CalDAVSetCookieEventParams;

typedef struct {
  LPCSTR CertEncoded;
  INT lenCertEncoded;
  LPCWSTR CertSubject;
  LPCWSTR CertIssuer;
  LPCWSTR Status;
  BOOL Accept;
  INT reserved;
} CalDAVSSLServerAuthenticationEventParams;

typedef struct {
  LPCWSTR Message;
  INT reserved;
} CalDAVSSLStatusEventParams;

typedef struct {
  INT Direction;
  INT reserved;
} CalDAVStartTransferEventParams;

typedef struct {
  LPCWSTR HTTPVersion;
  INT StatusCode;
  LPCWSTR Description;
  INT reserved;
} CalDAVStatusEventParams;

typedef struct {
  INT Direction;
  LONG64 BytesTransferred;
  INT PercentDone;
  LPCSTR Text;
  INT lenText;
  INT reserved;
} CalDAVTransferEventParams;


class CalDAV {
  public: // Events
    virtual INT FireConnected(CalDAVConnectedEventParams *e) {return 0;}
    virtual INT FireConnectionStatus(CalDAVConnectionStatusEventParams *e) {return 0;}
    virtual INT FireDisconnected(CalDAVDisconnectedEventParams *e) {return 0;}
    virtual INT FireEndTransfer(CalDAVEndTransferEventParams *e) {return 0;}
    virtual INT FireError(CalDAVErrorEventParams *e) {return 0;}
    virtual INT FireEventDetails(CalDAVEventDetailsEventParams *e) {return 0;}
    virtual INT FireFreeBusy(CalDAVFreeBusyEventParams *e) {return 0;}
    virtual INT FireHeader(CalDAVHeaderEventParams *e) {return 0;}
    virtual INT FireLog(CalDAVLogEventParams *e) {return 0;}
    virtual INT FireRedirect(CalDAVRedirectEventParams *e) {return 0;}
    virtual INT FireSetCookie(CalDAVSetCookieEventParams *e) {return 0;}
    virtual INT FireSSLServerAuthentication(CalDAVSSLServerAuthenticationEventParams *e) {return 0;}
    virtual INT FireSSLStatus(CalDAVSSLStatusEventParams *e) {return 0;}
    virtual INT FireStartTransfer(CalDAVStartTransferEventParams *e) {return 0;}
    virtual INT FireStatus(CalDAVStatusEventParams *e) {return 0;}
    virtual INT FireTransfer(CalDAVTransferEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL CalDAVEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          CalDAVConnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((CalDAV*)lpObj)->FireConnected(&e);
          break;
        }
        case 2: {
          CalDAVConnectionStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((CalDAV*)lpObj)->FireConnectionStatus(&e);
          break;
        }
        case 3: {
          CalDAVDisconnectedEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((CalDAV*)lpObj)->FireDisconnected(&e);
          break;
        }
        case 4: {
          CalDAVEndTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((CalDAV*)lpObj)->FireEndTransfer(&e);
          break;
        }
        case 5: {
          CalDAVErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((CalDAV*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          CalDAVEventDetailsEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], 0};
          ret_code = ((CalDAV*)lpObj)->FireEventDetails(&e);
          break;
        }
        case 7: {
          CalDAVFreeBusyEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((CalDAV*)lpObj)->FireFreeBusy(&e);
          break;
        }
        case 8: {
          CalDAVHeaderEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((CalDAV*)lpObj)->FireHeader(&e);
          break;
        }
        case 9: {
          CalDAVLogEventParams e = {(INT)param[0], (LPWSTR)param[1], (LPWSTR)param[2], 0};
          ret_code = ((CalDAV*)lpObj)->FireLog(&e);
          break;
        }
        case 10: {
          CalDAVRedirectEventParams e = {(LPWSTR)param[0], (BOOL)param[1], 0};
          ret_code = ((CalDAV*)lpObj)->FireRedirect(&e);
          param[1] = (LPVOID)e.Accept;
          break;
        }
        case 11: {
          CalDAVSetCookieEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (LPWSTR)param[4], (BOOL)param[5], 0};
          ret_code = ((CalDAV*)lpObj)->FireSetCookie(&e);
          break;
        }
        case 12: {
          CalDAVSSLServerAuthenticationEventParams e = {(LPSTR)param[0], (INT)cbparam[0], (LPWSTR)param[1], (LPWSTR)param[2], (LPWSTR)param[3], (BOOL)param[4], 0};
          ret_code = ((CalDAV*)lpObj)->FireSSLServerAuthentication(&e);
          param[4] = (LPVOID)e.Accept;
          break;
        }
        case 13: {
          CalDAVSSLStatusEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((CalDAV*)lpObj)->FireSSLStatus(&e);
          break;
        }
        case 14: {
          CalDAVStartTransferEventParams e = {(INT)param[0], 0};
          ret_code = ((CalDAV*)lpObj)->FireStartTransfer(&e);
          break;
        }
        case 15: {
          CalDAVStatusEventParams e = {(LPWSTR)param[0], (INT)param[1], (LPWSTR)param[2], 0};
          ret_code = ((CalDAV*)lpObj)->FireStatus(&e);
          break;
        }
        case 16: {
          CalDAVTransferEventParams e = {(INT)param[0], *(LONG64*)param[1], (INT)param[2], (LPSTR)param[3], (INT)cbparam[3], 0};
          ret_code = ((CalDAV*)lpObj)->FireTransfer(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    CalDAV(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_98) {
      m_pObj = IPWorks_CalDAV_Create(CalDAVEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~CalDAV() {
      IPWorks_CalDAV_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_CalDAV_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_CalDAV_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_CalDAV_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_CalDAV_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_CalDAV_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline INT GetAlarmCount() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 1, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAlarmCount(INT iAlarmCount) {
      LPVOID val = (LPVOID)(iAlarmCount);
      return IPWorks_CalDAV_Set(m_pObj, 1, 0, val, 0);
    }

    inline INT GetAlarmAction(INT iAlarmIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 2, iAlarmIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAlarmAction(INT iAlarmIndex, INT iAlarmAction) {
      LPVOID val = (LPVOID)(iAlarmAction);
      return IPWorks_CalDAV_Set(m_pObj, 2, iAlarmIndex, val, 0);
    }

    inline LPWSTR GetAlarmAttachment(INT iAlarmIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 3+10000, iAlarmIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAlarmAttachment(INT iAlarmIndex, LPCWSTR lpszAlarmAttachment) {
      return IPWorks_CalDAV_Set(m_pObj, 3+10000, iAlarmIndex, (LPVOID)lpszAlarmAttachment, 0);
    }

    inline LPWSTR GetAlarmAttachmentType(INT iAlarmIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 4+10000, iAlarmIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAlarmAttachmentType(INT iAlarmIndex, LPCWSTR lpszAlarmAttachmentType) {
      return IPWorks_CalDAV_Set(m_pObj, 4+10000, iAlarmIndex, (LPVOID)lpszAlarmAttachmentType, 0);
    }

    inline LPWSTR GetAlarmDuration(INT iAlarmIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 5+10000, iAlarmIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAlarmDuration(INT iAlarmIndex, LPCWSTR lpszAlarmDuration) {
      return IPWorks_CalDAV_Set(m_pObj, 5+10000, iAlarmIndex, (LPVOID)lpszAlarmDuration, 0);
    }

    inline LPWSTR GetAlarmMessage(INT iAlarmIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 6+10000, iAlarmIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAlarmMessage(INT iAlarmIndex, LPCWSTR lpszAlarmMessage) {
      return IPWorks_CalDAV_Set(m_pObj, 6+10000, iAlarmIndex, (LPVOID)lpszAlarmMessage, 0);
    }

    inline LPWSTR GetAlarmRecipient(INT iAlarmIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 7+10000, iAlarmIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAlarmRecipient(INT iAlarmIndex, LPCWSTR lpszAlarmRecipient) {
      return IPWorks_CalDAV_Set(m_pObj, 7+10000, iAlarmIndex, (LPVOID)lpszAlarmRecipient, 0);
    }

    inline INT GetAlarmRepeat(INT iAlarmIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 8, iAlarmIndex, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAlarmRepeat(INT iAlarmIndex, INT iAlarmRepeat) {
      LPVOID val = (LPVOID)(iAlarmRepeat);
      return IPWorks_CalDAV_Set(m_pObj, 8, iAlarmIndex, val, 0);
    }

    inline LPWSTR GetAlarmSubject(INT iAlarmIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 9+10000, iAlarmIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAlarmSubject(INT iAlarmIndex, LPCWSTR lpszAlarmSubject) {
      return IPWorks_CalDAV_Set(m_pObj, 9+10000, iAlarmIndex, (LPVOID)lpszAlarmSubject, 0);
    }

    inline LPWSTR GetAlarmTrigger(INT iAlarmIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 10+10000, iAlarmIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAlarmTrigger(INT iAlarmIndex, LPCWSTR lpszAlarmTrigger) {
      return IPWorks_CalDAV_Set(m_pObj, 10+10000, iAlarmIndex, (LPVOID)lpszAlarmTrigger, 0);
    }

    inline LPWSTR GetAttendees() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAttendees(LPCWSTR lpszAttendees) {
      return IPWorks_CalDAV_Set(m_pObj, 11+10000, 0, (LPVOID)lpszAttendees, 0);
    }

    inline LPWSTR GetAuthorization() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 12+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetAuthorization(LPCWSTR lpszAuthorization) {
      return IPWorks_CalDAV_Set(m_pObj, 12+10000, 0, (LPVOID)lpszAuthorization, 0);
    }

    inline INT GetAuthScheme() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 13, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAuthScheme(INT iAuthScheme) {
      LPVOID val = (LPVOID)(iAuthScheme);
      return IPWorks_CalDAV_Set(m_pObj, 13, 0, val, 0);
    }

    inline LPWSTR GetCategories() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCategories(LPCWSTR lpszCategories) {
      return IPWorks_CalDAV_Set(m_pObj, 14+10000, 0, (LPVOID)lpszCategories, 0);
    }

    inline LPWSTR GetClassification() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetClassification(LPCWSTR lpszClassification) {
      return IPWorks_CalDAV_Set(m_pObj, 15+10000, 0, (LPVOID)lpszClassification, 0);
    }

    inline LPWSTR GetCompleted() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCompleted(LPCWSTR lpszCompleted) {
      return IPWorks_CalDAV_Set(m_pObj, 16+10000, 0, (LPVOID)lpszCompleted, 0);
    }

    inline BOOL GetConnected() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 17, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetConnected(BOOL bConnected) {
      LPVOID val = (LPVOID)(bConnected);
      return IPWorks_CalDAV_Set(m_pObj, 17, 0, val, 0);
    }

    inline INT GetCookieCount() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 18, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCookieCount(INT iCookieCount) {
      LPVOID val = (LPVOID)(iCookieCount);
      return IPWorks_CalDAV_Set(m_pObj, 18, 0, val, 0);
    }

    inline LPWSTR GetCookieDomain(INT iCookieIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 19+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieExpiration(INT iCookieIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 20+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetCookieName(INT iCookieIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 21+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieName(INT iCookieIndex, LPCWSTR lpszCookieName) {
      return IPWorks_CalDAV_Set(m_pObj, 21+10000, iCookieIndex, (LPVOID)lpszCookieName, 0);
    }

    inline LPWSTR GetCookiePath(INT iCookieIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 22+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetCookieSecure(INT iCookieIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 23, iCookieIndex, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetCookieValue(INT iCookieIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 24+10000, iCookieIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCookieValue(INT iCookieIndex, LPCWSTR lpszCookieValue) {
      return IPWorks_CalDAV_Set(m_pObj, 24+10000, iCookieIndex, (LPVOID)lpszCookieValue, 0);
    }

    inline LPWSTR GetCreated() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 25+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCreated(LPCWSTR lpszCreated) {
      return IPWorks_CalDAV_Set(m_pObj, 25+10000, 0, (LPVOID)lpszCreated, 0);
    }

    inline INT GetCustomPropertyCount() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 26, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetCustomPropertyCount(INT iCustomPropertyCount) {
      LPVOID val = (LPVOID)(iCustomPropertyCount);
      return IPWorks_CalDAV_Set(m_pObj, 26, 0, val, 0);
    }

    inline LPWSTR GetCustomPropertyAttribute(INT iCustomPropertyIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 27+10000, iCustomPropertyIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCustomPropertyAttribute(INT iCustomPropertyIndex, LPCWSTR lpszCustomPropertyAttribute) {
      return IPWorks_CalDAV_Set(m_pObj, 27+10000, iCustomPropertyIndex, (LPVOID)lpszCustomPropertyAttribute, 0);
    }

    inline LPWSTR GetCustomPropertyName(INT iCustomPropertyIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 28+10000, iCustomPropertyIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCustomPropertyName(INT iCustomPropertyIndex, LPCWSTR lpszCustomPropertyName) {
      return IPWorks_CalDAV_Set(m_pObj, 28+10000, iCustomPropertyIndex, (LPVOID)lpszCustomPropertyName, 0);
    }

    inline LPWSTR GetCustomPropertyValue(INT iCustomPropertyIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 29+10000, iCustomPropertyIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetCustomPropertyValue(INT iCustomPropertyIndex, LPCWSTR lpszCustomPropertyValue) {
      return IPWorks_CalDAV_Set(m_pObj, 29+10000, iCustomPropertyIndex, (LPVOID)lpszCustomPropertyValue, 0);
    }

    inline INT GetDepth() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 30, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetDepth(INT iDepth) {
      LPVOID val = (LPVOID)(iDepth);
      return IPWorks_CalDAV_Set(m_pObj, 30, 0, val, 0);
    }

    inline LPWSTR GetDescription() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDescription(LPCWSTR lpszDescription) {
      return IPWorks_CalDAV_Set(m_pObj, 31+10000, 0, (LPVOID)lpszDescription, 0);
    }

    inline LPWSTR GetDisplayName() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 32+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDisplayName(LPCWSTR lpszDisplayName) {
      return IPWorks_CalDAV_Set(m_pObj, 32+10000, 0, (LPVOID)lpszDisplayName, 0);
    }

    inline LPWSTR GetDueDate() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 33+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDueDate(LPCWSTR lpszDueDate) {
      return IPWorks_CalDAV_Set(m_pObj, 33+10000, 0, (LPVOID)lpszDueDate, 0);
    }

    inline LPWSTR GetDuration() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 34+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetDuration(LPCWSTR lpszDuration) {
      return IPWorks_CalDAV_Set(m_pObj, 34+10000, 0, (LPVOID)lpszDuration, 0);
    }

    inline LPWSTR GetEndDate() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 35+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetEndDate(LPCWSTR lpszEndDate) {
      return IPWorks_CalDAV_Set(m_pObj, 35+10000, 0, (LPVOID)lpszEndDate, 0);
    }

    inline LPWSTR GetETag() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 36+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetETag(LPCWSTR lpszETag) {
      return IPWorks_CalDAV_Set(m_pObj, 36+10000, 0, (LPVOID)lpszETag, 0);
    }

    inline INT GetEventType() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 37, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetEventType(INT iEventType) {
      LPVOID val = (LPVOID)(iEventType);
      return IPWorks_CalDAV_Set(m_pObj, 37, 0, val, 0);
    }

    inline BOOL GetFirewallAutoDetect() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 38, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetFirewallAutoDetect(BOOL bFirewallAutoDetect) {
      LPVOID val = (LPVOID)(bFirewallAutoDetect);
      return IPWorks_CalDAV_Set(m_pObj, 38, 0, val, 0);
    }

    inline INT GetFirewallType() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 39, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallType(INT iFirewallType) {
      LPVOID val = (LPVOID)(iFirewallType);
      return IPWorks_CalDAV_Set(m_pObj, 39, 0, val, 0);
    }

    inline LPWSTR GetFirewallHost() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 40+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallHost(LPCWSTR lpszFirewallHost) {
      return IPWorks_CalDAV_Set(m_pObj, 40+10000, 0, (LPVOID)lpszFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 41+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallPassword(LPCWSTR lpszFirewallPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 41+10000, 0, (LPVOID)lpszFirewallPassword, 0);
    }

    inline INT GetFirewallPort() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 42, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFirewallPort(INT iFirewallPort) {
      LPVOID val = (LPVOID)(iFirewallPort);
      return IPWorks_CalDAV_Set(m_pObj, 42, 0, val, 0);
    }

    inline LPWSTR GetFirewallUser() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 43+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetFirewallUser(LPCWSTR lpszFirewallUser) {
      return IPWorks_CalDAV_Set(m_pObj, 43+10000, 0, (LPVOID)lpszFirewallUser, 0);
    }

    inline INT GetFollowRedirects() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 44, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetFollowRedirects(INT iFollowRedirects) {
      LPVOID val = (LPVOID)(iFollowRedirects);
      return IPWorks_CalDAV_Set(m_pObj, 44, 0, val, 0);
    }

    inline INT GetFreeBusyCount() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 45, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetFreeBusyRange(INT iFreeBusyIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 46+10000, iFreeBusyIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetFreeBusyType(INT iFreeBusyIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 47+10000, iFreeBusyIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline BOOL GetIdle() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 48, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }

    inline LPWSTR GetLastModified() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 49+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLastModified(LPCWSTR lpszLastModified) {
      return IPWorks_CalDAV_Set(m_pObj, 49+10000, 0, (LPVOID)lpszLastModified, 0);
    }

    inline LPWSTR GetLocalHost() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 50+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocalHost(LPCWSTR lpszLocalHost) {
      return IPWorks_CalDAV_Set(m_pObj, 50+10000, 0, (LPVOID)lpszLocalHost, 0);
    }

    inline LPWSTR GetLocation() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 51+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLocation(LPCWSTR lpszLocation) {
      return IPWorks_CalDAV_Set(m_pObj, 51+10000, 0, (LPVOID)lpszLocation, 0);
    }

    inline LPWSTR GetLockType() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 52+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLockType(LPCWSTR lpszLockType) {
      return IPWorks_CalDAV_Set(m_pObj, 52+10000, 0, (LPVOID)lpszLockType, 0);
    }

    inline LPWSTR GetLockOwner() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 53+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLockOwner(LPCWSTR lpszLockOwner) {
      return IPWorks_CalDAV_Set(m_pObj, 53+10000, 0, (LPVOID)lpszLockOwner, 0);
    }

    inline LPWSTR GetLockScope() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 54+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLockScope(LPCWSTR lpszLockScope) {
      return IPWorks_CalDAV_Set(m_pObj, 54+10000, 0, (LPVOID)lpszLockScope, 0);
    }

    inline INT GetLockTimeout() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 55, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetLockTimeout(INT iLockTimeout) {
      LPVOID val = (LPVOID)(iLockTimeout);
      return IPWorks_CalDAV_Set(m_pObj, 55, 0, val, 0);
    }

    inline LPWSTR GetLockTokens() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 56+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetLockTokens(LPCWSTR lpszLockTokens) {
      return IPWorks_CalDAV_Set(m_pObj, 56+10000, 0, (LPVOID)lpszLockTokens, 0);
    }

    inline LPWSTR GetOrganizer() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 57+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOrganizer(LPCWSTR lpszOrganizer) {
      return IPWorks_CalDAV_Set(m_pObj, 57+10000, 0, (LPVOID)lpszOrganizer, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 58+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOtherHeaders(LPCWSTR lpszOtherHeaders) {
      return IPWorks_CalDAV_Set(m_pObj, 58+10000, 0, (LPVOID)lpszOtherHeaders, 0);
    }

    inline INT GetParsedHeaderCount() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 59, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetParsedHeaderField(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 60+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetParsedHeaderValue(INT iParsedHeaderIndex) {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 61+10000, iParsedHeaderIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetPassword() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 62+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetPassword(LPCWSTR lpszPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 62+10000, 0, (LPVOID)lpszPassword, 0);
    }

    inline INT GetPriority() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 63, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetPriority(INT iPriority) {
      LPVOID val = (LPVOID)(iPriority);
      return IPWorks_CalDAV_Set(m_pObj, 63, 0, val, 0);
    }

    inline INT GetProxyAuthScheme() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 64, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyAuthScheme(INT iProxyAuthScheme) {
      LPVOID val = (LPVOID)(iProxyAuthScheme);
      return IPWorks_CalDAV_Set(m_pObj, 64, 0, val, 0);
    }

    inline BOOL GetProxyAutoDetect() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 65, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetProxyAutoDetect(BOOL bProxyAutoDetect) {
      LPVOID val = (LPVOID)(bProxyAutoDetect);
      return IPWorks_CalDAV_Set(m_pObj, 65, 0, val, 0);
    }

    inline LPWSTR GetProxyPassword() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 66+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyPassword(LPCWSTR lpszProxyPassword) {
      return IPWorks_CalDAV_Set(m_pObj, 66+10000, 0, (LPVOID)lpszProxyPassword, 0);
    }

    inline INT GetProxyPort() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 67, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxyPort(INT iProxyPort) {
      LPVOID val = (LPVOID)(iProxyPort);
      return IPWorks_CalDAV_Set(m_pObj, 67, 0, val, 0);
    }

    inline LPWSTR GetProxyServer() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 68+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyServer(LPCWSTR lpszProxyServer) {
      return IPWorks_CalDAV_Set(m_pObj, 68+10000, 0, (LPVOID)lpszProxyServer, 0);
    }

    inline INT GetProxySSL() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 69, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetProxySSL(INT iProxySSL) {
      LPVOID val = (LPVOID)(iProxySSL);
      return IPWorks_CalDAV_Set(m_pObj, 69, 0, val, 0);
    }

    inline LPWSTR GetProxyUser() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 70+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetProxyUser(LPCWSTR lpszProxyUser) {
      return IPWorks_CalDAV_Set(m_pObj, 70+10000, 0, (LPVOID)lpszProxyUser, 0);
    }

    inline LPWSTR GetRecurrenceDates() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 71+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRecurrenceDates(LPCWSTR lpszRecurrenceDates) {
      return IPWorks_CalDAV_Set(m_pObj, 71+10000, 0, (LPVOID)lpszRecurrenceDates, 0);
    }

    inline LPWSTR GetRecurrenceExceptionDates() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 72+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRecurrenceExceptionDates(LPCWSTR lpszRecurrenceExceptionDates) {
      return IPWorks_CalDAV_Set(m_pObj, 72+10000, 0, (LPVOID)lpszRecurrenceExceptionDates, 0);
    }

    inline LPWSTR GetRecurrenceExceptionRule() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 73+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRecurrenceExceptionRule(LPCWSTR lpszRecurrenceExceptionRule) {
      return IPWorks_CalDAV_Set(m_pObj, 73+10000, 0, (LPVOID)lpszRecurrenceExceptionRule, 0);
    }

    inline LPWSTR GetRecurrenceId() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 74+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRecurrenceId(LPCWSTR lpszRecurrenceId) {
      return IPWorks_CalDAV_Set(m_pObj, 74+10000, 0, (LPVOID)lpszRecurrenceId, 0);
    }

    inline LPWSTR GetRecurrenceRule() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 75+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetRecurrenceRule(LPCWSTR lpszRecurrenceRule) {
      return IPWorks_CalDAV_Set(m_pObj, 75+10000, 0, (LPVOID)lpszRecurrenceRule, 0);
    }

    inline LPWSTR GetReportFilterAlarmEnd() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 76+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReportFilterAlarmEnd(LPCWSTR lpszReportFilterAlarmEnd) {
      return IPWorks_CalDAV_Set(m_pObj, 76+10000, 0, (LPVOID)lpszReportFilterAlarmEnd, 0);
    }

    inline LPWSTR GetReportFilterAlarmStart() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 77+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReportFilterAlarmStart(LPCWSTR lpszReportFilterAlarmStart) {
      return IPWorks_CalDAV_Set(m_pObj, 77+10000, 0, (LPVOID)lpszReportFilterAlarmStart, 0);
    }

    inline LPWSTR GetReportFilterCustomFilter() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 78+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReportFilterCustomFilter(LPCWSTR lpszReportFilterCustomFilter) {
      return IPWorks_CalDAV_Set(m_pObj, 78+10000, 0, (LPVOID)lpszReportFilterCustomFilter, 0);
    }

    inline LPWSTR GetReportFilterEndDate() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 79+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReportFilterEndDate(LPCWSTR lpszReportFilterEndDate) {
      return IPWorks_CalDAV_Set(m_pObj, 79+10000, 0, (LPVOID)lpszReportFilterEndDate, 0);
    }

    inline INT GetReportFilterEventType() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 80, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetReportFilterEventType(INT iReportFilterEventType) {
      LPVOID val = (LPVOID)(iReportFilterEventType);
      return IPWorks_CalDAV_Set(m_pObj, 80, 0, val, 0);
    }

    inline LPWSTR GetReportFilterProperty() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 81+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReportFilterProperty(LPCWSTR lpszReportFilterProperty) {
      return IPWorks_CalDAV_Set(m_pObj, 81+10000, 0, (LPVOID)lpszReportFilterProperty, 0);
    }

    inline LPWSTR GetReportFilterRecurEnd() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 82+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReportFilterRecurEnd(LPCWSTR lpszReportFilterRecurEnd) {
      return IPWorks_CalDAV_Set(m_pObj, 82+10000, 0, (LPVOID)lpszReportFilterRecurEnd, 0);
    }

    inline LPWSTR GetReportFilterRecurStart() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 83+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReportFilterRecurStart(LPCWSTR lpszReportFilterRecurStart) {
      return IPWorks_CalDAV_Set(m_pObj, 83+10000, 0, (LPVOID)lpszReportFilterRecurStart, 0);
    }

    inline BOOL GetReportFilterReturnCalendarData() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 84, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetReportFilterReturnCalendarData(BOOL bReportFilterReturnCalendarData) {
      LPVOID val = (LPVOID)(bReportFilterReturnCalendarData);
      return IPWorks_CalDAV_Set(m_pObj, 84, 0, val, 0);
    }

    inline LPWSTR GetReportFilterStartDate() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 85+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReportFilterStartDate(LPCWSTR lpszReportFilterStartDate) {
      return IPWorks_CalDAV_Set(m_pObj, 85+10000, 0, (LPVOID)lpszReportFilterStartDate, 0);
    }

    inline LPWSTR GetReportFilterUID() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 86+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetReportFilterUID(LPCWSTR lpszReportFilterUID) {
      return IPWorks_CalDAV_Set(m_pObj, 86+10000, 0, (LPVOID)lpszReportFilterUID, 0);
    }

    inline INT GetSequence() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 87, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSequence(INT iSequence) {
      LPVOID val = (LPVOID)(iSequence);
      return IPWorks_CalDAV_Set(m_pObj, 87, 0, val, 0);
    }

    inline INT GetSSLAcceptServerCertEncoded(LPSTR &lpSSLAcceptServerCertEncoded, INT &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (LPSTR)IPWorks_CalDAV_Get(m_pObj, 88, 0, &lenSSLAcceptServerCertEncoded, NULL);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline INT SetSSLAcceptServerCertEncoded(LPCSTR lpSSLAcceptServerCertEncoded, INT lenSSLAcceptServerCertEncoded) {
      return IPWorks_CalDAV_Set(m_pObj, 88, 0, (LPVOID)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline INT GetSSLCertEncoded(LPSTR &lpSSLCertEncoded, INT &lenSSLCertEncoded) {
      lpSSLCertEncoded = (LPSTR)IPWorks_CalDAV_Get(m_pObj, 89, 0, &lenSSLCertEncoded, NULL);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline INT SetSSLCertEncoded(LPCSTR lpSSLCertEncoded, INT lenSSLCertEncoded) {
      return IPWorks_CalDAV_Set(m_pObj, 89, 0, (LPVOID)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline INT GetSSLCertStore(LPSTR &lpSSLCertStore, INT &lenSSLCertStore) {
      lpSSLCertStore = (LPSTR)IPWorks_CalDAV_Get(m_pObj, 90, 0, &lenSSLCertStore, NULL);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline INT SetSSLCertStore(LPCSTR lpSSLCertStore, INT lenSSLCertStore) {
      return IPWorks_CalDAV_Set(m_pObj, 90, 0, (LPVOID)lpSSLCertStore, lenSSLCertStore);
    }

    inline LPWSTR GetSSLCertStorePassword() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 91+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertStorePassword(LPCWSTR lpszSSLCertStorePassword) {
      return IPWorks_CalDAV_Set(m_pObj, 91+10000, 0, (LPVOID)lpszSSLCertStorePassword, 0);
    }

    inline INT GetSSLCertStoreType() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 92, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetSSLCertStoreType(INT iSSLCertStoreType) {
      LPVOID val = (LPVOID)(iSSLCertStoreType);
      return IPWorks_CalDAV_Set(m_pObj, 92, 0, val, 0);
    }

    inline LPWSTR GetSSLCertSubject() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 93+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSSLCertSubject(LPCWSTR lpszSSLCertSubject) {
      return IPWorks_CalDAV_Set(m_pObj, 93+10000, 0, (LPVOID)lpszSSLCertSubject, 0);
    }

    inline INT GetSSLServerCertEncoded(LPSTR &lpSSLServerCertEncoded, INT &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (LPSTR)IPWorks_CalDAV_Get(m_pObj, 94, 0, &lenSSLServerCertEncoded, NULL);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }

    inline LPWSTR GetStartDate() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 95+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetStartDate(LPCWSTR lpszStartDate) {
      return IPWorks_CalDAV_Set(m_pObj, 95+10000, 0, (LPVOID)lpszStartDate, 0);
    }

    inline LPWSTR GetStatus() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 96+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetStatus(LPCWSTR lpszStatus) {
      return IPWorks_CalDAV_Set(m_pObj, 96+10000, 0, (LPVOID)lpszStatus, 0);
    }

    inline LPWSTR GetStatusLine() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 97+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetSummary() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 98+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetSummary(LPCWSTR lpszSummary) {
      return IPWorks_CalDAV_Set(m_pObj, 98+10000, 0, (LPVOID)lpszSummary, 0);
    }

    inline INT GetTimeout() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 99, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetTimeout(INT iTimeout) {
      LPVOID val = (LPVOID)(iTimeout);
      return IPWorks_CalDAV_Set(m_pObj, 99, 0, val, 0);
    }

    inline LPWSTR GetTimestamp() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 100+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimestamp(LPCWSTR lpszTimestamp) {
      return IPWorks_CalDAV_Set(m_pObj, 100+10000, 0, (LPVOID)lpszTimestamp, 0);
    }

    inline LPWSTR GetTimezoneDSTName() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 101+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneDSTName(LPCWSTR lpszTimezoneDSTName) {
      return IPWorks_CalDAV_Set(m_pObj, 101+10000, 0, (LPVOID)lpszTimezoneDSTName, 0);
    }

    inline LPWSTR GetTimezoneDSTOffsetFrom() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 102+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneDSTOffsetFrom(LPCWSTR lpszTimezoneDSTOffsetFrom) {
      return IPWorks_CalDAV_Set(m_pObj, 102+10000, 0, (LPVOID)lpszTimezoneDSTOffsetFrom, 0);
    }

    inline LPWSTR GetTimezoneDSTOffsetTo() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 103+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneDSTOffsetTo(LPCWSTR lpszTimezoneDSTOffsetTo) {
      return IPWorks_CalDAV_Set(m_pObj, 103+10000, 0, (LPVOID)lpszTimezoneDSTOffsetTo, 0);
    }

    inline LPWSTR GetTimezoneDSTRule() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 104+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneDSTRule(LPCWSTR lpszTimezoneDSTRule) {
      return IPWorks_CalDAV_Set(m_pObj, 104+10000, 0, (LPVOID)lpszTimezoneDSTRule, 0);
    }

    inline LPWSTR GetTimezoneDSTStart() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 105+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneDSTStart(LPCWSTR lpszTimezoneDSTStart) {
      return IPWorks_CalDAV_Set(m_pObj, 105+10000, 0, (LPVOID)lpszTimezoneDSTStart, 0);
    }

    inline LPWSTR GetTimezoneLastModified() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 106+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneLastModified(LPCWSTR lpszTimezoneLastModified) {
      return IPWorks_CalDAV_Set(m_pObj, 106+10000, 0, (LPVOID)lpszTimezoneLastModified, 0);
    }

    inline LPWSTR GetTimezoneStdName() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 107+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneStdName(LPCWSTR lpszTimezoneStdName) {
      return IPWorks_CalDAV_Set(m_pObj, 107+10000, 0, (LPVOID)lpszTimezoneStdName, 0);
    }

    inline LPWSTR GetTimezoneStdOffsetFrom() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 108+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneStdOffsetFrom(LPCWSTR lpszTimezoneStdOffsetFrom) {
      return IPWorks_CalDAV_Set(m_pObj, 108+10000, 0, (LPVOID)lpszTimezoneStdOffsetFrom, 0);
    }

    inline LPWSTR GetTimezoneStdOffsetTo() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 109+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneStdOffsetTo(LPCWSTR lpszTimezoneStdOffsetTo) {
      return IPWorks_CalDAV_Set(m_pObj, 109+10000, 0, (LPVOID)lpszTimezoneStdOffsetTo, 0);
    }

    inline LPWSTR GetTimezoneStdRule() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 110+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneStdRule(LPCWSTR lpszTimezoneStdRule) {
      return IPWorks_CalDAV_Set(m_pObj, 110+10000, 0, (LPVOID)lpszTimezoneStdRule, 0);
    }

    inline LPWSTR GetTimezoneStdStart() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 111+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneStdStart(LPCWSTR lpszTimezoneStdStart) {
      return IPWorks_CalDAV_Set(m_pObj, 111+10000, 0, (LPVOID)lpszTimezoneStdStart, 0);
    }

    inline LPWSTR GetTimezoneId() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 112+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneId(LPCWSTR lpszTimezoneId) {
      return IPWorks_CalDAV_Set(m_pObj, 112+10000, 0, (LPVOID)lpszTimezoneId, 0);
    }

    inline LPWSTR GetTimezoneURL() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 113+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTimezoneURL(LPCWSTR lpszTimezoneURL) {
      return IPWorks_CalDAV_Set(m_pObj, 113+10000, 0, (LPVOID)lpszTimezoneURL, 0);
    }

    inline LPWSTR GetTransparency() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 114+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetTransparency(LPCWSTR lpszTransparency) {
      return IPWorks_CalDAV_Set(m_pObj, 114+10000, 0, (LPVOID)lpszTransparency, 0);
    }

    inline LPWSTR GetUID() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 115+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUID(LPCWSTR lpszUID) {
      return IPWorks_CalDAV_Set(m_pObj, 115+10000, 0, (LPVOID)lpszUID, 0);
    }

    inline LPWSTR GetURL() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 116+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetUser() {
      LPVOID val = IPWorks_CalDAV_Get(m_pObj, 117+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetUser(LPCWSTR lpszUser) {
      return IPWorks_CalDAV_Set(m_pObj, 117+10000, 0, (LPVOID)lpszUser, 0);
    }

  public: // Methods
    inline INT AddCookie(LPCWSTR lpszCookieName, LPCWSTR lpszCookieValue) {
      LPVOID param[2+1] = {(LPVOID)lpszCookieName, (LPVOID)lpszCookieValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 2+10000, 2, param, cbparam, NULL);
    }

    inline INT AddCustomProperty(LPCWSTR lpszVarName, LPCWSTR lpszVarValue) {
      LPVOID param[2+1] = {(LPVOID)lpszVarName, (LPVOID)lpszVarValue, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 3+10000, 2, param, cbparam, NULL);
    }

    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_CalDAV_Do(m_pObj, 4+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT CopyCalendarEvent(LPCWSTR lpszSourceResourceURI, LPCWSTR lpszDestinationResourceURI) {
      LPVOID param[2+1] = {(LPVOID)lpszSourceResourceURI, (LPVOID)lpszDestinationResourceURI, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 5+10000, 2, param, cbparam, NULL);
    }

    inline INT CreateCalendar(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
    }

    inline INT DeleteCalendarEvent(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 7+10000, 1, param, cbparam, NULL);
    }

    inline INT DoEvents() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 8+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR ExportICS() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      IPWorks_CalDAV_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
      return (LPWSTR)param[0];
    }

    inline INT GetCalendarEvent(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 10+10000, 1, param, cbparam, NULL);
    }

    inline INT GetCalendarOptions(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 11+10000, 1, param, cbparam, NULL);
    }

    inline INT GetCalendarReport(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 12+10000, 1, param, cbparam, NULL);
    }

    inline INT GetFreeBusyReport(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 13+10000, 1, param, cbparam, NULL);
    }

    inline INT ImportICS(LPCWSTR lpszCalendarData) {
      LPVOID param[1+1] = {(LPVOID)lpszCalendarData, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
    }

    inline INT Interrupt() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 15+10000, 0, param, cbparam, NULL);
    }

    inline INT LockCalendar(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 16+10000, 1, param, cbparam, NULL);
    }

    inline INT MoveCalendarEvent(LPCWSTR lpszSourceResourceURI, LPCWSTR lpszDestinationResourceURI) {
      LPVOID param[2+1] = {(LPVOID)lpszSourceResourceURI, (LPVOID)lpszDestinationResourceURI, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 17+10000, 2, param, cbparam, NULL);
    }

    inline INT PutCalendarEvent(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 18+10000, 1, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_CalDAV_Do(m_pObj, 19+10000, 0, param, cbparam, NULL);
    }

    inline INT UnLockCalendar(LPCWSTR lpszResourceURI) {
      LPVOID param[1+1] = {(LPVOID)lpszResourceURI, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_CalDAV_Do(m_pObj, 20+10000, 1, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_CALDAV_H_
