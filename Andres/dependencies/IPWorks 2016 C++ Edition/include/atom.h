/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_ATOM_H_
#define _IPWORKS_ATOM_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//AuthSchemes
#define AUTH_BASIC                                         0
#define AUTH_DIGEST                                        1
#define AUTH_PROPRIETARY                                   2
#define AUTH_NONE                                          3
#define AUTH_NTLM                                          4
#define AUTH_NEGOTIATE                                     5
#define AUTH_OAUTH                                         6

//AtomTextTypes
#define TT_TEXT                                            0
#define TT_HTML                                            1
#define TT_XHTML                                           2

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


extern "C" void* IPWORKS_CALL IPWorks_Atom_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_Atom_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Atom_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_Atom_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Atom_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_Atom_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Atom_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Atom_StaticDestroy();

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
} AtomConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} AtomConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} AtomDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} AtomEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} AtomErrorEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} AtomHeaderEventParams;

typedef struct {
  int LogLevel;
  const char* Message;
  const char* LogType;
  int reserved;
} AtomLogEventParams;

typedef struct {
  const char* Location;
  int Accept;
  int reserved;
} AtomRedirectEventParams;

typedef struct {
  const char* Name;
  const char* Value;
  const char* Expires;
  const char* Domain;
  const char* Path;
  int Secure;
  int reserved;
} AtomSetCookieEventParams;

typedef struct {
  const char* CertEncoded;
  const char* CertSubject;
  const char* CertIssuer;
  const char* Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} AtomSSLServerAuthenticationEventParams;

typedef struct {
  const char* Message;
  int reserved;
} AtomSSLStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} AtomStartTransferEventParams;

typedef struct {
  const char* HTTPVersion;
  int StatusCode;
  const char* Description;
  int reserved;
} AtomStatusEventParams;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  const char* Text;
  int lenText;
  int reserved;
} AtomTransferEventParams;



class Atom {
  
  public: //events
  
    virtual int FireConnected(AtomConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(AtomConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(AtomDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(AtomEndTransferEventParams *e) {return 0;}
    virtual int FireError(AtomErrorEventParams *e) {return 0;}
    virtual int FireHeader(AtomHeaderEventParams *e) {return 0;}
    virtual int FireLog(AtomLogEventParams *e) {return 0;}
    virtual int FireRedirect(AtomRedirectEventParams *e) {return 0;}
    virtual int FireSetCookie(AtomSetCookieEventParams *e) {return 0;}
    virtual int FireSSLServerAuthentication(AtomSSLServerAuthenticationEventParams *e) {return 0;}
    virtual int FireSSLStatus(AtomSSLStatusEventParams *e) {return 0;}
    virtual int FireStartTransfer(AtomStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(AtomStatusEventParams *e) {return 0;}
    virtual int FireTransfer(AtomTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL AtomEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((Atom*)lpObj)->AtomEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            AtomConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Atom*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            AtomConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((Atom*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            AtomDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Atom*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            AtomEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((Atom*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 5: {
            AtomErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Atom*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            AtomHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Atom*)lpObj)->FireHeader(&e);
            break;
         }
         case 7: {
            AtomLogEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((Atom*)lpObj)->FireLog(&e);
            break;
         }
         case 8: {
            AtomRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = ((Atom*)lpObj)->FireRedirect(&e);
            param[1] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 9: {
            AtomSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = ((Atom*)lpObj)->FireSetCookie(&e);
            break;
         }
         case 10: {
            AtomSSLServerAuthenticationEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((Atom*)lpObj)->FireSSLServerAuthentication(&e);
            param[4] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 11: {
            AtomSSLStatusEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((Atom*)lpObj)->FireSSLStatus(&e);
            break;
         }
         case 12: {
            AtomStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((Atom*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 13: {
            AtomStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((Atom*)lpObj)->FireStatus(&e);
            break;
         }
         case 14: {
            AtomTransferEventParams e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((Atom*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int AtomEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    Atom(char *lpOemKey = (char*)IPWORKS_OEMKEY_69) {
      m_pObj = IPWorks_Atom_Create(AtomEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~Atom() {
      IPWorks_Atom_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_Atom_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_Atom_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_Atom_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_Atom_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_Atom_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetAccept() {
      void* val = IPWorks_Atom_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetAccept(const char *lpAccept) {
      return IPWorks_Atom_Set(m_pObj, 1, 0, (void*)lpAccept, 0);
    }

    inline int GetAtomData(char *&lpAtomData, int &lenAtomData) {
      lpAtomData = (char*)IPWorks_Atom_Get(m_pObj, 2, 0, &lenAtomData);
      return lpAtomData ? 0 : lenAtomData;
    }

    inline int SetAtomData(const char *lpAtomData, int lenAtomData) {
      return IPWorks_Atom_Set(m_pObj, 2, 0, (void*)lpAtomData, lenAtomData);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_Atom_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorization(const char *lpAuthorization) {
      return IPWorks_Atom_Set(m_pObj, 3, 0, (void*)lpAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_Atom_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_Atom_Set(m_pObj, 4, 0, val, 0);
    }
    inline char* GetChannelAuthorEmail() {
      void* val = IPWorks_Atom_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetChannelAuthorEmail(const char *lpChannelAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 5, 0, (void*)lpChannelAuthorEmail, 0);
    }

    inline char* GetChannelAuthorName() {
      void* val = IPWorks_Atom_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetChannelAuthorName(const char *lpChannelAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 6, 0, (void*)lpChannelAuthorName, 0);
    }

    inline char* GetChannelAuthorUri() {
      void* val = IPWorks_Atom_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetChannelAuthorUri(const char *lpChannelAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 7, 0, (void*)lpChannelAuthorUri, 0);
    }

    inline char* GetChannelCategoryLabel() {
      void* val = IPWorks_Atom_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetChannelCategoryLabel(const char *lpChannelCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 8, 0, (void*)lpChannelCategoryLabel, 0);
    }

    inline char* GetChannelCategoryScheme() {
      void* val = IPWorks_Atom_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetChannelCategoryScheme(const char *lpChannelCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 9, 0, (void*)lpChannelCategoryScheme, 0);
    }

    inline char* GetChannelCategoryTerm() {
      void* val = IPWorks_Atom_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }

    inline int SetChannelCategoryTerm(const char *lpChannelCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 10, 0, (void*)lpChannelCategoryTerm, 0);
    }

    inline char* GetChannelContributorEmail() {
      void* val = IPWorks_Atom_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetChannelContributorEmail(const char *lpChannelContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 11, 0, (void*)lpChannelContributorEmail, 0);
    }

    inline char* GetChannelContributorName() {
      void* val = IPWorks_Atom_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetChannelContributorName(const char *lpChannelContributorName) {
      return IPWorks_Atom_Set(m_pObj, 12, 0, (void*)lpChannelContributorName, 0);
    }

    inline char* GetChannelContributorUri() {
      void* val = IPWorks_Atom_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetChannelContributorUri(const char *lpChannelContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 13, 0, (void*)lpChannelContributorUri, 0);
    }

    inline char* GetChannelGenerator() {
      void* val = IPWorks_Atom_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetChannelGenerator(const char *lpChannelGenerator) {
      return IPWorks_Atom_Set(m_pObj, 14, 0, (void*)lpChannelGenerator, 0);
    }

    inline char* GetChannelIcon() {
      void* val = IPWorks_Atom_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetChannelIcon(const char *lpChannelIcon) {
      return IPWorks_Atom_Set(m_pObj, 15, 0, (void*)lpChannelIcon, 0);
    }

    inline char* GetChannelId() {
      void* val = IPWorks_Atom_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetChannelId(const char *lpChannelId) {
      return IPWorks_Atom_Set(m_pObj, 16, 0, (void*)lpChannelId, 0);
    }

    inline char* GetChannelLinkHref() {
      void* val = IPWorks_Atom_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkHref(const char *lpChannelLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 17, 0, (void*)lpChannelLinkHref, 0);
    }

    inline char* GetChannelLinkHrefLang() {
      void* val = IPWorks_Atom_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkHrefLang(const char *lpChannelLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 18, 0, (void*)lpChannelLinkHrefLang, 0);
    }

    inline char* GetChannelLinkLength() {
      void* val = IPWorks_Atom_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkLength(const char *lpChannelLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 19, 0, (void*)lpChannelLinkLength, 0);
    }

    inline char* GetChannelLinkRel() {
      void* val = IPWorks_Atom_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkRel(const char *lpChannelLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 20, 0, (void*)lpChannelLinkRel, 0);
    }

    inline char* GetChannelLinkTitle() {
      void* val = IPWorks_Atom_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkTitle(const char *lpChannelLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 21, 0, (void*)lpChannelLinkTitle, 0);
    }

    inline char* GetChannelLinkType() {
      void* val = IPWorks_Atom_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkType(const char *lpChannelLinkType) {
      return IPWorks_Atom_Set(m_pObj, 22, 0, (void*)lpChannelLinkType, 0);
    }

    inline char* GetChannelLogo() {
      void* val = IPWorks_Atom_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLogo(const char *lpChannelLogo) {
      return IPWorks_Atom_Set(m_pObj, 23, 0, (void*)lpChannelLogo, 0);
    }

    inline char* GetChannelRights() {
      void* val = IPWorks_Atom_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetChannelRights(const char *lpChannelRights) {
      return IPWorks_Atom_Set(m_pObj, 24, 0, (void*)lpChannelRights, 0);
    }

    inline int GetChannelRightsTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 25, 0, 0);
      return (int)(long)val;
    }
    inline int SetChannelRightsTextType(int iChannelRightsTextType) {
      void* val = (void*)IPW64CAST(iChannelRightsTextType);
      return IPWorks_Atom_Set(m_pObj, 25, 0, val, 0);
    }
    inline char* GetChannelSubtitle() {
      void* val = IPWorks_Atom_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }

    inline int SetChannelSubtitle(const char *lpChannelSubtitle) {
      return IPWorks_Atom_Set(m_pObj, 26, 0, (void*)lpChannelSubtitle, 0);
    }

    inline int GetChannelSubtitleTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 27, 0, 0);
      return (int)(long)val;
    }
    inline int SetChannelSubtitleTextType(int iChannelSubtitleTextType) {
      void* val = (void*)IPW64CAST(iChannelSubtitleTextType);
      return IPWorks_Atom_Set(m_pObj, 27, 0, val, 0);
    }
    inline char* GetChannelTitle() {
      void* val = IPWorks_Atom_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }

    inline int SetChannelTitle(const char *lpChannelTitle) {
      return IPWorks_Atom_Set(m_pObj, 28, 0, (void*)lpChannelTitle, 0);
    }

    inline int GetChannelTitleTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 29, 0, 0);
      return (int)(long)val;
    }
    inline int SetChannelTitleTextType(int iChannelTitleTextType) {
      void* val = (void*)IPW64CAST(iChannelTitleTextType);
      return IPWorks_Atom_Set(m_pObj, 29, 0, val, 0);
    }
    inline char* GetChannelUpdated() {
      void* val = IPWorks_Atom_Get(m_pObj, 30, 0, 0);
      return (char*)val;
    }

    inline int SetChannelUpdated(const char *lpChannelUpdated) {
      return IPWorks_Atom_Set(m_pObj, 30, 0, (void*)lpChannelUpdated, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_Atom_Get(m_pObj, 31, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_Atom_Set(m_pObj, 31, 0, val, 0);
    }
    inline char* GetContentType() {
      void* val = IPWorks_Atom_Get(m_pObj, 32, 0, 0);
      return (char*)val;
    }

    inline int SetContentType(const char *lpContentType) {
      return IPWorks_Atom_Set(m_pObj, 32, 0, (void*)lpContentType, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_Atom_Get(m_pObj, 33, 0, 0);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_Atom_Set(m_pObj, 33, 0, val, 0);
    }
    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 34, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 35, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 36, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieName(int iCookieIndex, const char *lpCookieName) {
      return IPWorks_Atom_Set(m_pObj, 36, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 37, iCookieIndex, 0);
      return (char*)val;
    }


    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 38, iCookieIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 39, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieValue(int iCookieIndex, const char *lpCookieValue) {
      return IPWorks_Atom_Set(m_pObj, 39, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline int GetEntryCount() {
      void* val = IPWorks_Atom_Get(m_pObj, 40, 0, 0);
      return (int)(long)val;
    }
    inline int SetEntryCount(int iEntryCount) {
      void* val = (void*)IPW64CAST(iEntryCount);
      return IPWorks_Atom_Set(m_pObj, 40, 0, val, 0);
    }
    inline char* GetEntryAuthorEmail(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 41, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryAuthorEmail(int iEntryIndex, const char *lpEntryAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 41, iEntryIndex, (void*)lpEntryAuthorEmail, 0);
    }

    inline char* GetEntryAuthorName(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 42, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryAuthorName(int iEntryIndex, const char *lpEntryAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 42, iEntryIndex, (void*)lpEntryAuthorName, 0);
    }

    inline char* GetEntryAuthorUri(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 43, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryAuthorUri(int iEntryIndex, const char *lpEntryAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 43, iEntryIndex, (void*)lpEntryAuthorUri, 0);
    }

    inline char* GetEntryCategoryLabel(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 44, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryCategoryLabel(int iEntryIndex, const char *lpEntryCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 44, iEntryIndex, (void*)lpEntryCategoryLabel, 0);
    }

    inline char* GetEntryCategoryScheme(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 45, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryCategoryScheme(int iEntryIndex, const char *lpEntryCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 45, iEntryIndex, (void*)lpEntryCategoryScheme, 0);
    }

    inline char* GetEntryCategoryTerm(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 46, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryCategoryTerm(int iEntryIndex, const char *lpEntryCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 46, iEntryIndex, (void*)lpEntryCategoryTerm, 0);
    }

    inline char* GetEntryContent(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 47, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryContent(int iEntryIndex, const char *lpEntryContent) {
      return IPWorks_Atom_Set(m_pObj, 47, iEntryIndex, (void*)lpEntryContent, 0);
    }

    inline int GetEntryContentTextType(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 48, iEntryIndex, 0);
      return (int)(long)val;
    }
    inline int SetEntryContentTextType(int iEntryIndex, int iEntryContentTextType) {
      void* val = (void*)IPW64CAST(iEntryContentTextType);
      return IPWorks_Atom_Set(m_pObj, 48, iEntryIndex, val, 0);
    }
    inline char* GetEntryContributorEmail(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 49, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryContributorEmail(int iEntryIndex, const char *lpEntryContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 49, iEntryIndex, (void*)lpEntryContributorEmail, 0);
    }

    inline char* GetEntryContributorName(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 50, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryContributorName(int iEntryIndex, const char *lpEntryContributorName) {
      return IPWorks_Atom_Set(m_pObj, 50, iEntryIndex, (void*)lpEntryContributorName, 0);
    }

    inline char* GetEntryContributorUri(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 51, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryContributorUri(int iEntryIndex, const char *lpEntryContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 51, iEntryIndex, (void*)lpEntryContributorUri, 0);
    }

    inline char* GetEntryCopyright(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 52, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryCopyright(int iEntryIndex, const char *lpEntryCopyright) {
      return IPWorks_Atom_Set(m_pObj, 52, iEntryIndex, (void*)lpEntryCopyright, 0);
    }

    inline char* GetEntryCreated(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 53, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryCreated(int iEntryIndex, const char *lpEntryCreated) {
      return IPWorks_Atom_Set(m_pObj, 53, iEntryIndex, (void*)lpEntryCreated, 0);
    }

    inline char* GetEntryXML(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 54, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryXML(int iEntryIndex, const char *lpEntryXML) {
      return IPWorks_Atom_Set(m_pObj, 54, iEntryIndex, (void*)lpEntryXML, 0);
    }

    inline char* GetEntryId(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 55, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryId(int iEntryIndex, const char *lpEntryId) {
      return IPWorks_Atom_Set(m_pObj, 55, iEntryIndex, (void*)lpEntryId, 0);
    }

    inline char* GetEntryIssued(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 56, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryIssued(int iEntryIndex, const char *lpEntryIssued) {
      return IPWorks_Atom_Set(m_pObj, 56, iEntryIndex, (void*)lpEntryIssued, 0);
    }

    inline char* GetEntryLinkHref(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 57, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryLinkHref(int iEntryIndex, const char *lpEntryLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 57, iEntryIndex, (void*)lpEntryLinkHref, 0);
    }

    inline char* GetEntryLinkHrefLang(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 58, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryLinkHrefLang(int iEntryIndex, const char *lpEntryLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 58, iEntryIndex, (void*)lpEntryLinkHrefLang, 0);
    }

    inline char* GetEntryLinkLength(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 59, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryLinkLength(int iEntryIndex, const char *lpEntryLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 59, iEntryIndex, (void*)lpEntryLinkLength, 0);
    }

    inline char* GetEntryLinkRel(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 60, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryLinkRel(int iEntryIndex, const char *lpEntryLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 60, iEntryIndex, (void*)lpEntryLinkRel, 0);
    }

    inline char* GetEntryLinkTitle(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 61, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryLinkTitle(int iEntryIndex, const char *lpEntryLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 61, iEntryIndex, (void*)lpEntryLinkTitle, 0);
    }

    inline char* GetEntryLinkType(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 62, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryLinkType(int iEntryIndex, const char *lpEntryLinkType) {
      return IPWorks_Atom_Set(m_pObj, 62, iEntryIndex, (void*)lpEntryLinkType, 0);
    }

    inline char* GetEntryModified(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 63, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryModified(int iEntryIndex, const char *lpEntryModified) {
      return IPWorks_Atom_Set(m_pObj, 63, iEntryIndex, (void*)lpEntryModified, 0);
    }

    inline char* GetEntryPublished(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 64, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryPublished(int iEntryIndex, const char *lpEntryPublished) {
      return IPWorks_Atom_Set(m_pObj, 64, iEntryIndex, (void*)lpEntryPublished, 0);
    }

    inline char* GetEntryRights(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 65, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryRights(int iEntryIndex, const char *lpEntryRights) {
      return IPWorks_Atom_Set(m_pObj, 65, iEntryIndex, (void*)lpEntryRights, 0);
    }

    inline int GetEntryRightsTextType(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 66, iEntryIndex, 0);
      return (int)(long)val;
    }
    inline int SetEntryRightsTextType(int iEntryIndex, int iEntryRightsTextType) {
      void* val = (void*)IPW64CAST(iEntryRightsTextType);
      return IPWorks_Atom_Set(m_pObj, 66, iEntryIndex, val, 0);
    }
    inline char* GetEntrySource(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 67, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntrySource(int iEntryIndex, const char *lpEntrySource) {
      return IPWorks_Atom_Set(m_pObj, 67, iEntryIndex, (void*)lpEntrySource, 0);
    }

    inline char* GetEntrySummary(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 68, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntrySummary(int iEntryIndex, const char *lpEntrySummary) {
      return IPWorks_Atom_Set(m_pObj, 68, iEntryIndex, (void*)lpEntrySummary, 0);
    }

    inline int GetEntrySummaryTextType(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 69, iEntryIndex, 0);
      return (int)(long)val;
    }
    inline int SetEntrySummaryTextType(int iEntryIndex, int iEntrySummaryTextType) {
      void* val = (void*)IPW64CAST(iEntrySummaryTextType);
      return IPWorks_Atom_Set(m_pObj, 69, iEntryIndex, val, 0);
    }
    inline char* GetEntryTitle(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 70, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryTitle(int iEntryIndex, const char *lpEntryTitle) {
      return IPWorks_Atom_Set(m_pObj, 70, iEntryIndex, (void*)lpEntryTitle, 0);
    }

    inline int GetEntryTitleTextType(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 71, iEntryIndex, 0);
      return (int)(long)val;
    }
    inline int SetEntryTitleTextType(int iEntryIndex, int iEntryTitleTextType) {
      void* val = (void*)IPW64CAST(iEntryTitleTextType);
      return IPWorks_Atom_Set(m_pObj, 71, iEntryIndex, val, 0);
    }
    inline char* GetEntryUpdated(int iEntryIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 72, iEntryIndex, 0);
      return (char*)val;
    }

    inline int SetEntryUpdated(int iEntryIndex, const char *lpEntryUpdated) {
      return IPWorks_Atom_Set(m_pObj, 72, iEntryIndex, (void*)lpEntryUpdated, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_Atom_Get(m_pObj, 73, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_Atom_Set(m_pObj, 73, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_Atom_Get(m_pObj, 74, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_Atom_Set(m_pObj, 74, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_Atom_Get(m_pObj, 75, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_Atom_Set(m_pObj, 75, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_Atom_Get(m_pObj, 76, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_Atom_Set(m_pObj, 76, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_Atom_Get(m_pObj, 77, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_Atom_Set(m_pObj, 77, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_Atom_Get(m_pObj, 78, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_Atom_Set(m_pObj, 78, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_Atom_Get(m_pObj, 79, 0, 0);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_Atom_Set(m_pObj, 79, 0, val, 0);
    }
    inline int GetIdle() {
      void* val = IPWorks_Atom_Get(m_pObj, 80, 0, 0);
      return (int)(long)val;
    }

    inline char* GetIfModifiedSince() {
      void* val = IPWorks_Atom_Get(m_pObj, 81, 0, 0);
      return (char*)val;
    }

    inline int SetIfModifiedSince(const char *lpIfModifiedSince) {
      return IPWorks_Atom_Set(m_pObj, 81, 0, (void*)lpIfModifiedSince, 0);
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_Atom_Get(m_pObj, 82, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_Atom_Set(m_pObj, 82, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_Atom_Get(m_pObj, 83, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_Atom_Set(m_pObj, 83, 0, (void*)lpLocalHost, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_Atom_Get(m_pObj, 84, 0, 0);
      return (int)(long)val;
    }
    inline int SetNamespaceCount(int iNamespaceCount) {
      void* val = (void*)IPW64CAST(iNamespaceCount);
      return IPWorks_Atom_Set(m_pObj, 84, 0, val, 0);
    }
    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 85, iNamespaceIndex, 0);
      return (char*)val;
    }

    inline int SetNamespacePrefix(int iNamespaceIndex, const char *lpNamespacePrefix) {
      return IPWorks_Atom_Set(m_pObj, 85, iNamespaceIndex, (void*)lpNamespacePrefix, 0);
    }

    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 86, iNamespaceIndex, 0);
      return (char*)val;
    }

    inline int SetNamespaceURI(int iNamespaceIndex, const char *lpNamespaceURI) {
      return IPWorks_Atom_Set(m_pObj, 86, iNamespaceIndex, (void*)lpNamespaceURI, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_Atom_Get(m_pObj, 87, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_Atom_Set(m_pObj, 87, 0, (void*)lpOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_Atom_Get(m_pObj, 88, 0, 0);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 89, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_Atom_Get(m_pObj, 90, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_Atom_Get(m_pObj, 91, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_Atom_Set(m_pObj, 91, 0, (void*)lpPassword, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_Atom_Get(m_pObj, 92, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_Atom_Set(m_pObj, 92, 0, val, 0);
    }
    inline int GetProxyAutoDetect() {
      void* val = IPWorks_Atom_Get(m_pObj, 93, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_Atom_Set(m_pObj, 93, 0, val, 0);
    }
    inline char* GetProxyPassword() {
      void* val = IPWorks_Atom_Get(m_pObj, 94, 0, 0);
      return (char*)val;
    }

    inline int SetProxyPassword(const char *lpProxyPassword) {
      return IPWorks_Atom_Set(m_pObj, 94, 0, (void*)lpProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_Atom_Get(m_pObj, 95, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyPort(int lProxyPort) {
      void* val = (void*)IPW64CAST(lProxyPort);
      return IPWorks_Atom_Set(m_pObj, 95, 0, val, 0);
    }
    inline char* GetProxyServer() {
      void* val = IPWorks_Atom_Get(m_pObj, 96, 0, 0);
      return (char*)val;
    }

    inline int SetProxyServer(const char *lpProxyServer) {
      return IPWorks_Atom_Set(m_pObj, 96, 0, (void*)lpProxyServer, 0);
    }

    inline int GetProxySSL() {
      void* val = IPWorks_Atom_Get(m_pObj, 97, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxySSL(int iProxySSL) {
      void* val = (void*)IPW64CAST(iProxySSL);
      return IPWorks_Atom_Set(m_pObj, 97, 0, val, 0);
    }
    inline char* GetProxyUser() {
      void* val = IPWorks_Atom_Get(m_pObj, 98, 0, 0);
      return (char*)val;
    }

    inline int SetProxyUser(const char *lpProxyUser) {
      return IPWorks_Atom_Set(m_pObj, 98, 0, (void*)lpProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_Atom_Get(m_pObj, 99, 0, 0);
      return (char*)val;
    }

    inline int SetReferer(const char *lpReferer) {
      return IPWorks_Atom_Set(m_pObj, 99, 0, (void*)lpReferer, 0);
    }

    inline char* GetSlug() {
      void* val = IPWorks_Atom_Get(m_pObj, 100, 0, 0);
      return (char*)val;
    }

    inline int SetSlug(const char *lpSlug) {
      return IPWorks_Atom_Set(m_pObj, 100, 0, (void*)lpSlug, 0);
    }

    inline int GetSSLAcceptServerCertEncoded(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_Atom_Get(m_pObj, 101, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }

    inline int SetSSLAcceptServerCertEncoded(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_Atom_Set(m_pObj, 101, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }

    inline int GetSSLCertEncoded(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_Atom_Get(m_pObj, 102, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }

    inline int SetSSLCertEncoded(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_Atom_Set(m_pObj, 102, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }

    inline int GetSSLCertStore(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_Atom_Get(m_pObj, 103, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }

    inline int SetSSLCertStore(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_Atom_Set(m_pObj, 103, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }

    inline char* GetSSLCertStorePassword() {
      void* val = IPWorks_Atom_Get(m_pObj, 104, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertStorePassword(const char *lpSSLCertStorePassword) {
      return IPWorks_Atom_Set(m_pObj, 104, 0, (void*)lpSSLCertStorePassword, 0);
    }

    inline int GetSSLCertStoreType() {
      void* val = IPWorks_Atom_Get(m_pObj, 105, 0, 0);
      return (int)(long)val;
    }
    inline int SetSSLCertStoreType(int iSSLCertStoreType) {
      void* val = (void*)IPW64CAST(iSSLCertStoreType);
      return IPWorks_Atom_Set(m_pObj, 105, 0, val, 0);
    }
    inline char* GetSSLCertSubject() {
      void* val = IPWorks_Atom_Get(m_pObj, 106, 0, 0);
      return (char*)val;
    }

    inline int SetSSLCertSubject(const char *lpSSLCertSubject) {
      return IPWorks_Atom_Set(m_pObj, 106, 0, (void*)lpSSLCertSubject, 0);
    }

    inline int GetSSLServerCertEncoded(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_Atom_Get(m_pObj, 107, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }


    inline int GetTimeout() {
      void* val = IPWorks_Atom_Get(m_pObj, 108, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_Atom_Set(m_pObj, 108, 0, val, 0);
    }
    inline int GetTransferredData(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_Atom_Get(m_pObj, 109, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }


    inline ns_int64 GetTransferredDataLimit() {
      ns_int64 *pval = (ns_int64*)IPWorks_Atom_Get(m_pObj, 110, 0, 0);
      return *pval;
    }

    inline int SetTransferredDataLimit(ns_int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_Atom_Set(m_pObj, 110, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_Atom_Get(m_pObj, 111, 0, 0);
      return (char*)val;
    }


    inline char* GetUpdateEntryAuthorEmail() {
      void* val = IPWorks_Atom_Get(m_pObj, 112, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryAuthorEmail(const char *lpUpdateEntryAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 112, 0, (void*)lpUpdateEntryAuthorEmail, 0);
    }

    inline char* GetUpdateEntryAuthorName() {
      void* val = IPWorks_Atom_Get(m_pObj, 113, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryAuthorName(const char *lpUpdateEntryAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 113, 0, (void*)lpUpdateEntryAuthorName, 0);
    }

    inline char* GetUpdateEntryAuthorUri() {
      void* val = IPWorks_Atom_Get(m_pObj, 114, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryAuthorUri(const char *lpUpdateEntryAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 114, 0, (void*)lpUpdateEntryAuthorUri, 0);
    }

    inline char* GetUpdateEntryCategoryLabel() {
      void* val = IPWorks_Atom_Get(m_pObj, 115, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryCategoryLabel(const char *lpUpdateEntryCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 115, 0, (void*)lpUpdateEntryCategoryLabel, 0);
    }

    inline char* GetUpdateEntryCategoryScheme() {
      void* val = IPWorks_Atom_Get(m_pObj, 116, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryCategoryScheme(const char *lpUpdateEntryCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 116, 0, (void*)lpUpdateEntryCategoryScheme, 0);
    }

    inline char* GetUpdateEntryCategoryTerm() {
      void* val = IPWorks_Atom_Get(m_pObj, 117, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryCategoryTerm(const char *lpUpdateEntryCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 117, 0, (void*)lpUpdateEntryCategoryTerm, 0);
    }

    inline char* GetUpdateEntryContent() {
      void* val = IPWorks_Atom_Get(m_pObj, 118, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryContent(const char *lpUpdateEntryContent) {
      return IPWorks_Atom_Set(m_pObj, 118, 0, (void*)lpUpdateEntryContent, 0);
    }

    inline int GetUpdateEntryContentTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 119, 0, 0);
      return (int)(long)val;
    }
    inline int SetUpdateEntryContentTextType(int iUpdateEntryContentTextType) {
      void* val = (void*)IPW64CAST(iUpdateEntryContentTextType);
      return IPWorks_Atom_Set(m_pObj, 119, 0, val, 0);
    }
    inline char* GetUpdateEntryContributorEmail() {
      void* val = IPWorks_Atom_Get(m_pObj, 120, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryContributorEmail(const char *lpUpdateEntryContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 120, 0, (void*)lpUpdateEntryContributorEmail, 0);
    }

    inline char* GetUpdateEntryContributorName() {
      void* val = IPWorks_Atom_Get(m_pObj, 121, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryContributorName(const char *lpUpdateEntryContributorName) {
      return IPWorks_Atom_Set(m_pObj, 121, 0, (void*)lpUpdateEntryContributorName, 0);
    }

    inline char* GetUpdateEntryContributorUri() {
      void* val = IPWorks_Atom_Get(m_pObj, 122, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryContributorUri(const char *lpUpdateEntryContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 122, 0, (void*)lpUpdateEntryContributorUri, 0);
    }

    inline char* GetUpdateEntryCopyright() {
      void* val = IPWorks_Atom_Get(m_pObj, 123, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryCopyright(const char *lpUpdateEntryCopyright) {
      return IPWorks_Atom_Set(m_pObj, 123, 0, (void*)lpUpdateEntryCopyright, 0);
    }

    inline char* GetUpdateEntryCreated() {
      void* val = IPWorks_Atom_Get(m_pObj, 124, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryCreated(const char *lpUpdateEntryCreated) {
      return IPWorks_Atom_Set(m_pObj, 124, 0, (void*)lpUpdateEntryCreated, 0);
    }

    inline char* GetUpdateEntryXML() {
      void* val = IPWorks_Atom_Get(m_pObj, 125, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryXML(const char *lpUpdateEntryXML) {
      return IPWorks_Atom_Set(m_pObj, 125, 0, (void*)lpUpdateEntryXML, 0);
    }

    inline char* GetUpdateEntryId() {
      void* val = IPWorks_Atom_Get(m_pObj, 126, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryId(const char *lpUpdateEntryId) {
      return IPWorks_Atom_Set(m_pObj, 126, 0, (void*)lpUpdateEntryId, 0);
    }

    inline char* GetUpdateEntryIssued() {
      void* val = IPWorks_Atom_Get(m_pObj, 127, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryIssued(const char *lpUpdateEntryIssued) {
      return IPWorks_Atom_Set(m_pObj, 127, 0, (void*)lpUpdateEntryIssued, 0);
    }

    inline char* GetUpdateEntryLinkHref() {
      void* val = IPWorks_Atom_Get(m_pObj, 128, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryLinkHref(const char *lpUpdateEntryLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 128, 0, (void*)lpUpdateEntryLinkHref, 0);
    }

    inline char* GetUpdateEntryLinkHrefLang() {
      void* val = IPWorks_Atom_Get(m_pObj, 129, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryLinkHrefLang(const char *lpUpdateEntryLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 129, 0, (void*)lpUpdateEntryLinkHrefLang, 0);
    }

    inline char* GetUpdateEntryLinkLength() {
      void* val = IPWorks_Atom_Get(m_pObj, 130, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryLinkLength(const char *lpUpdateEntryLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 130, 0, (void*)lpUpdateEntryLinkLength, 0);
    }

    inline char* GetUpdateEntryLinkRel() {
      void* val = IPWorks_Atom_Get(m_pObj, 131, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryLinkRel(const char *lpUpdateEntryLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 131, 0, (void*)lpUpdateEntryLinkRel, 0);
    }

    inline char* GetUpdateEntryLinkTitle() {
      void* val = IPWorks_Atom_Get(m_pObj, 132, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryLinkTitle(const char *lpUpdateEntryLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 132, 0, (void*)lpUpdateEntryLinkTitle, 0);
    }

    inline char* GetUpdateEntryLinkType() {
      void* val = IPWorks_Atom_Get(m_pObj, 133, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryLinkType(const char *lpUpdateEntryLinkType) {
      return IPWorks_Atom_Set(m_pObj, 133, 0, (void*)lpUpdateEntryLinkType, 0);
    }

    inline char* GetUpdateEntryModified() {
      void* val = IPWorks_Atom_Get(m_pObj, 134, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryModified(const char *lpUpdateEntryModified) {
      return IPWorks_Atom_Set(m_pObj, 134, 0, (void*)lpUpdateEntryModified, 0);
    }

    inline char* GetUpdateEntryPublished() {
      void* val = IPWorks_Atom_Get(m_pObj, 135, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryPublished(const char *lpUpdateEntryPublished) {
      return IPWorks_Atom_Set(m_pObj, 135, 0, (void*)lpUpdateEntryPublished, 0);
    }

    inline char* GetUpdateEntryRights() {
      void* val = IPWorks_Atom_Get(m_pObj, 136, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryRights(const char *lpUpdateEntryRights) {
      return IPWorks_Atom_Set(m_pObj, 136, 0, (void*)lpUpdateEntryRights, 0);
    }

    inline int GetUpdateEntryRightsTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 137, 0, 0);
      return (int)(long)val;
    }
    inline int SetUpdateEntryRightsTextType(int iUpdateEntryRightsTextType) {
      void* val = (void*)IPW64CAST(iUpdateEntryRightsTextType);
      return IPWorks_Atom_Set(m_pObj, 137, 0, val, 0);
    }
    inline char* GetUpdateEntrySource() {
      void* val = IPWorks_Atom_Get(m_pObj, 138, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntrySource(const char *lpUpdateEntrySource) {
      return IPWorks_Atom_Set(m_pObj, 138, 0, (void*)lpUpdateEntrySource, 0);
    }

    inline char* GetUpdateEntrySummary() {
      void* val = IPWorks_Atom_Get(m_pObj, 139, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntrySummary(const char *lpUpdateEntrySummary) {
      return IPWorks_Atom_Set(m_pObj, 139, 0, (void*)lpUpdateEntrySummary, 0);
    }

    inline int GetUpdateEntrySummaryTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 140, 0, 0);
      return (int)(long)val;
    }
    inline int SetUpdateEntrySummaryTextType(int iUpdateEntrySummaryTextType) {
      void* val = (void*)IPW64CAST(iUpdateEntrySummaryTextType);
      return IPWorks_Atom_Set(m_pObj, 140, 0, val, 0);
    }
    inline char* GetUpdateEntryTitle() {
      void* val = IPWorks_Atom_Get(m_pObj, 141, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryTitle(const char *lpUpdateEntryTitle) {
      return IPWorks_Atom_Set(m_pObj, 141, 0, (void*)lpUpdateEntryTitle, 0);
    }

    inline int GetUpdateEntryTitleTextType() {
      void* val = IPWorks_Atom_Get(m_pObj, 142, 0, 0);
      return (int)(long)val;
    }
    inline int SetUpdateEntryTitleTextType(int iUpdateEntryTitleTextType) {
      void* val = (void*)IPW64CAST(iUpdateEntryTitleTextType);
      return IPWorks_Atom_Set(m_pObj, 142, 0, val, 0);
    }
    inline char* GetUpdateEntryUpdated() {
      void* val = IPWorks_Atom_Get(m_pObj, 143, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateEntryUpdated(const char *lpUpdateEntryUpdated) {
      return IPWorks_Atom_Set(m_pObj, 143, 0, (void*)lpUpdateEntryUpdated, 0);
    }

    inline char* GetUpdateFile() {
      void* val = IPWorks_Atom_Get(m_pObj, 144, 0, 0);
      return (char*)val;
    }

    inline int SetUpdateFile(const char *lpUpdateFile) {
      return IPWorks_Atom_Set(m_pObj, 144, 0, (void*)lpUpdateFile, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_Atom_Get(m_pObj, 145, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_Atom_Set(m_pObj, 145, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 2, 2, param, cbparam);
      
      
    }
    inline int AddNamespace(const char* lpszPrefix, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPrefix), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 3, 2, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Atom_Do(m_pObj, 4, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DeleteResource(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 5, 1, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int GetFeed(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 7, 1, param, cbparam);
      
      
    }
    inline char* GetProperty(const char* lpszPropertyName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszPropertyName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Atom_Do(m_pObj, 8, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int GetResource(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 9, 1, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int PostResource(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 11, 1, param, cbparam);
      
      
    }
    inline int Put(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 12, 1, param, cbparam);
      
      
    }
    inline int PutResource(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 13, 1, param, cbparam);
      
      
    }
    inline int ReadFile(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 14, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 15, 0, param, cbparam);
      
      
    }
    inline int SetProperty(const char* lpszPropertyName, const char* lpszPropertyValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszPropertyName), (void*)IPW64CAST(lpszPropertyValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 16, 2, param, cbparam);
      
      
    }
    inline int WriteFile(const char* lpszFilename) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFilename), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 17, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} AtomConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} AtomConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} AtomDisconnectedEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} AtomEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} AtomErrorEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} AtomHeaderEventParamsW;

typedef struct {
  int LogLevel;
  LPWSTR Message;
  LPWSTR LogType;
  int reserved;
} AtomLogEventParamsW;

typedef struct {
  LPWSTR Location;
  int Accept;
  int reserved;
} AtomRedirectEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR Value;
  LPWSTR Expires;
  LPWSTR Domain;
  LPWSTR Path;
  int Secure;
  int reserved;
} AtomSetCookieEventParamsW;

typedef struct {
  LPWSTR CertEncoded;
  LPWSTR CertSubject;
  LPWSTR CertIssuer;
  LPWSTR Status;
  int Accept;
  int lenCertEncoded;
  int reserved;
} AtomSSLServerAuthenticationEventParamsW;

typedef struct {
  LPWSTR Message;
  int reserved;
} AtomSSLStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} AtomStartTransferEventParamsW;

typedef struct {
  LPWSTR HTTPVersion;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} AtomStatusEventParamsW;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int lenText;
  int reserved;
} AtomTransferEventParamsW;



class AtomW : public Atom {

  public: //properties
  
    inline LPWSTR GetAccept() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetAccept(LPCWSTR lpAccept) {
      return IPWorks_Atom_Set(m_pObj, 10000+1, 0, (void*)lpAccept, 0);
    }

    inline LPWSTR GetAtomData() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetAtomData(LPCWSTR lpAtomData) {
      return IPWorks_Atom_Set(m_pObj, 10000+2, 0, (void*)lpAtomData, 0);
    }
    inline int GetAtomDataB(char *&lpAtomData, int &lenAtomData) {
      lpAtomData = (char*)IPWorks_Atom_Get(m_pObj, 2, 0, &lenAtomData);
      return lpAtomData ? 0 : lenAtomData;
    }
    inline int SetAtomDataB(const char *lpAtomData, int lenAtomData) {
      return IPWorks_Atom_Set(m_pObj, 2, 0, (void*)lpAtomData, lenAtomData);
    }
    inline LPWSTR GetAuthorization() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetAuthorization(LPCWSTR lpAuthorization) {
      return IPWorks_Atom_Set(m_pObj, 10000+3, 0, (void*)lpAuthorization, 0);
    }



    inline LPWSTR GetChannelAuthorEmail() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetChannelAuthorEmail(LPCWSTR lpChannelAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 10000+5, 0, (void*)lpChannelAuthorEmail, 0);
    }

    inline LPWSTR GetChannelAuthorName() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetChannelAuthorName(LPCWSTR lpChannelAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 10000+6, 0, (void*)lpChannelAuthorName, 0);
    }

    inline LPWSTR GetChannelAuthorUri() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetChannelAuthorUri(LPCWSTR lpChannelAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 10000+7, 0, (void*)lpChannelAuthorUri, 0);
    }

    inline LPWSTR GetChannelCategoryLabel() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetChannelCategoryLabel(LPCWSTR lpChannelCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 10000+8, 0, (void*)lpChannelCategoryLabel, 0);
    }

    inline LPWSTR GetChannelCategoryScheme() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetChannelCategoryScheme(LPCWSTR lpChannelCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 10000+9, 0, (void*)lpChannelCategoryScheme, 0);
    }

    inline LPWSTR GetChannelCategoryTerm() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+10, 0, 0);
    }

    inline int SetChannelCategoryTerm(LPCWSTR lpChannelCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 10000+10, 0, (void*)lpChannelCategoryTerm, 0);
    }

    inline LPWSTR GetChannelContributorEmail() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetChannelContributorEmail(LPCWSTR lpChannelContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 10000+11, 0, (void*)lpChannelContributorEmail, 0);
    }

    inline LPWSTR GetChannelContributorName() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetChannelContributorName(LPCWSTR lpChannelContributorName) {
      return IPWorks_Atom_Set(m_pObj, 10000+12, 0, (void*)lpChannelContributorName, 0);
    }

    inline LPWSTR GetChannelContributorUri() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetChannelContributorUri(LPCWSTR lpChannelContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 10000+13, 0, (void*)lpChannelContributorUri, 0);
    }

    inline LPWSTR GetChannelGenerator() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetChannelGenerator(LPCWSTR lpChannelGenerator) {
      return IPWorks_Atom_Set(m_pObj, 10000+14, 0, (void*)lpChannelGenerator, 0);
    }

    inline LPWSTR GetChannelIcon() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetChannelIcon(LPCWSTR lpChannelIcon) {
      return IPWorks_Atom_Set(m_pObj, 10000+15, 0, (void*)lpChannelIcon, 0);
    }

    inline LPWSTR GetChannelId() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetChannelId(LPCWSTR lpChannelId) {
      return IPWorks_Atom_Set(m_pObj, 10000+16, 0, (void*)lpChannelId, 0);
    }

    inline LPWSTR GetChannelLinkHref() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetChannelLinkHref(LPCWSTR lpChannelLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 10000+17, 0, (void*)lpChannelLinkHref, 0);
    }

    inline LPWSTR GetChannelLinkHrefLang() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetChannelLinkHrefLang(LPCWSTR lpChannelLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 10000+18, 0, (void*)lpChannelLinkHrefLang, 0);
    }

    inline LPWSTR GetChannelLinkLength() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetChannelLinkLength(LPCWSTR lpChannelLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 10000+19, 0, (void*)lpChannelLinkLength, 0);
    }

    inline LPWSTR GetChannelLinkRel() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetChannelLinkRel(LPCWSTR lpChannelLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 10000+20, 0, (void*)lpChannelLinkRel, 0);
    }

    inline LPWSTR GetChannelLinkTitle() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+21, 0, 0);
    }

    inline int SetChannelLinkTitle(LPCWSTR lpChannelLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 10000+21, 0, (void*)lpChannelLinkTitle, 0);
    }

    inline LPWSTR GetChannelLinkType() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetChannelLinkType(LPCWSTR lpChannelLinkType) {
      return IPWorks_Atom_Set(m_pObj, 10000+22, 0, (void*)lpChannelLinkType, 0);
    }

    inline LPWSTR GetChannelLogo() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+23, 0, 0);
    }

    inline int SetChannelLogo(LPCWSTR lpChannelLogo) {
      return IPWorks_Atom_Set(m_pObj, 10000+23, 0, (void*)lpChannelLogo, 0);
    }

    inline LPWSTR GetChannelRights() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetChannelRights(LPCWSTR lpChannelRights) {
      return IPWorks_Atom_Set(m_pObj, 10000+24, 0, (void*)lpChannelRights, 0);
    }



    inline LPWSTR GetChannelSubtitle() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+26, 0, 0);
    }

    inline int SetChannelSubtitle(LPCWSTR lpChannelSubtitle) {
      return IPWorks_Atom_Set(m_pObj, 10000+26, 0, (void*)lpChannelSubtitle, 0);
    }



    inline LPWSTR GetChannelTitle() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+28, 0, 0);
    }

    inline int SetChannelTitle(LPCWSTR lpChannelTitle) {
      return IPWorks_Atom_Set(m_pObj, 10000+28, 0, (void*)lpChannelTitle, 0);
    }



    inline LPWSTR GetChannelUpdated() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+30, 0, 0);
    }

    inline int SetChannelUpdated(LPCWSTR lpChannelUpdated) {
      return IPWorks_Atom_Set(m_pObj, 10000+30, 0, (void*)lpChannelUpdated, 0);
    }



    inline LPWSTR GetContentType() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+32, 0, 0);
    }

    inline int SetContentType(LPCWSTR lpContentType) {
      return IPWorks_Atom_Set(m_pObj, 10000+32, 0, (void*)lpContentType, 0);
    }



    inline LPWSTR GetCookieDomain(int iCookieIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+34, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieExpiration(int iCookieIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+35, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieName(int iCookieIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+36, iCookieIndex, 0);
    }

    inline int SetCookieName(int iCookieIndex, LPCWSTR lpCookieName) {
      return IPWorks_Atom_Set(m_pObj, 10000+36, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline LPWSTR GetCookiePath(int iCookieIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+37, iCookieIndex, 0);
    }





    inline LPWSTR GetCookieValue(int iCookieIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+39, iCookieIndex, 0);
    }

    inline int SetCookieValue(int iCookieIndex, LPCWSTR lpCookieValue) {
      return IPWorks_Atom_Set(m_pObj, 10000+39, iCookieIndex, (void*)lpCookieValue, 0);
    }



    inline LPWSTR GetEntryAuthorEmail(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+41, iEntryIndex, 0);
    }

    inline int SetEntryAuthorEmail(int iEntryIndex, LPCWSTR lpEntryAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 10000+41, iEntryIndex, (void*)lpEntryAuthorEmail, 0);
    }

    inline LPWSTR GetEntryAuthorName(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+42, iEntryIndex, 0);
    }

    inline int SetEntryAuthorName(int iEntryIndex, LPCWSTR lpEntryAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 10000+42, iEntryIndex, (void*)lpEntryAuthorName, 0);
    }

    inline LPWSTR GetEntryAuthorUri(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+43, iEntryIndex, 0);
    }

    inline int SetEntryAuthorUri(int iEntryIndex, LPCWSTR lpEntryAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 10000+43, iEntryIndex, (void*)lpEntryAuthorUri, 0);
    }

    inline LPWSTR GetEntryCategoryLabel(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+44, iEntryIndex, 0);
    }

    inline int SetEntryCategoryLabel(int iEntryIndex, LPCWSTR lpEntryCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 10000+44, iEntryIndex, (void*)lpEntryCategoryLabel, 0);
    }

    inline LPWSTR GetEntryCategoryScheme(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+45, iEntryIndex, 0);
    }

    inline int SetEntryCategoryScheme(int iEntryIndex, LPCWSTR lpEntryCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 10000+45, iEntryIndex, (void*)lpEntryCategoryScheme, 0);
    }

    inline LPWSTR GetEntryCategoryTerm(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+46, iEntryIndex, 0);
    }

    inline int SetEntryCategoryTerm(int iEntryIndex, LPCWSTR lpEntryCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 10000+46, iEntryIndex, (void*)lpEntryCategoryTerm, 0);
    }

    inline LPWSTR GetEntryContent(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+47, iEntryIndex, 0);
    }

    inline int SetEntryContent(int iEntryIndex, LPCWSTR lpEntryContent) {
      return IPWorks_Atom_Set(m_pObj, 10000+47, iEntryIndex, (void*)lpEntryContent, 0);
    }



    inline LPWSTR GetEntryContributorEmail(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+49, iEntryIndex, 0);
    }

    inline int SetEntryContributorEmail(int iEntryIndex, LPCWSTR lpEntryContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 10000+49, iEntryIndex, (void*)lpEntryContributorEmail, 0);
    }

    inline LPWSTR GetEntryContributorName(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+50, iEntryIndex, 0);
    }

    inline int SetEntryContributorName(int iEntryIndex, LPCWSTR lpEntryContributorName) {
      return IPWorks_Atom_Set(m_pObj, 10000+50, iEntryIndex, (void*)lpEntryContributorName, 0);
    }

    inline LPWSTR GetEntryContributorUri(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+51, iEntryIndex, 0);
    }

    inline int SetEntryContributorUri(int iEntryIndex, LPCWSTR lpEntryContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 10000+51, iEntryIndex, (void*)lpEntryContributorUri, 0);
    }

    inline LPWSTR GetEntryCopyright(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+52, iEntryIndex, 0);
    }

    inline int SetEntryCopyright(int iEntryIndex, LPCWSTR lpEntryCopyright) {
      return IPWorks_Atom_Set(m_pObj, 10000+52, iEntryIndex, (void*)lpEntryCopyright, 0);
    }

    inline LPWSTR GetEntryCreated(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+53, iEntryIndex, 0);
    }

    inline int SetEntryCreated(int iEntryIndex, LPCWSTR lpEntryCreated) {
      return IPWorks_Atom_Set(m_pObj, 10000+53, iEntryIndex, (void*)lpEntryCreated, 0);
    }

    inline LPWSTR GetEntryXML(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+54, iEntryIndex, 0);
    }

    inline int SetEntryXML(int iEntryIndex, LPCWSTR lpEntryXML) {
      return IPWorks_Atom_Set(m_pObj, 10000+54, iEntryIndex, (void*)lpEntryXML, 0);
    }

    inline LPWSTR GetEntryId(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+55, iEntryIndex, 0);
    }

    inline int SetEntryId(int iEntryIndex, LPCWSTR lpEntryId) {
      return IPWorks_Atom_Set(m_pObj, 10000+55, iEntryIndex, (void*)lpEntryId, 0);
    }

    inline LPWSTR GetEntryIssued(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+56, iEntryIndex, 0);
    }

    inline int SetEntryIssued(int iEntryIndex, LPCWSTR lpEntryIssued) {
      return IPWorks_Atom_Set(m_pObj, 10000+56, iEntryIndex, (void*)lpEntryIssued, 0);
    }

    inline LPWSTR GetEntryLinkHref(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+57, iEntryIndex, 0);
    }

    inline int SetEntryLinkHref(int iEntryIndex, LPCWSTR lpEntryLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 10000+57, iEntryIndex, (void*)lpEntryLinkHref, 0);
    }

    inline LPWSTR GetEntryLinkHrefLang(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+58, iEntryIndex, 0);
    }

    inline int SetEntryLinkHrefLang(int iEntryIndex, LPCWSTR lpEntryLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 10000+58, iEntryIndex, (void*)lpEntryLinkHrefLang, 0);
    }

    inline LPWSTR GetEntryLinkLength(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+59, iEntryIndex, 0);
    }

    inline int SetEntryLinkLength(int iEntryIndex, LPCWSTR lpEntryLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 10000+59, iEntryIndex, (void*)lpEntryLinkLength, 0);
    }

    inline LPWSTR GetEntryLinkRel(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+60, iEntryIndex, 0);
    }

    inline int SetEntryLinkRel(int iEntryIndex, LPCWSTR lpEntryLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 10000+60, iEntryIndex, (void*)lpEntryLinkRel, 0);
    }

    inline LPWSTR GetEntryLinkTitle(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+61, iEntryIndex, 0);
    }

    inline int SetEntryLinkTitle(int iEntryIndex, LPCWSTR lpEntryLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 10000+61, iEntryIndex, (void*)lpEntryLinkTitle, 0);
    }

    inline LPWSTR GetEntryLinkType(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+62, iEntryIndex, 0);
    }

    inline int SetEntryLinkType(int iEntryIndex, LPCWSTR lpEntryLinkType) {
      return IPWorks_Atom_Set(m_pObj, 10000+62, iEntryIndex, (void*)lpEntryLinkType, 0);
    }

    inline LPWSTR GetEntryModified(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+63, iEntryIndex, 0);
    }

    inline int SetEntryModified(int iEntryIndex, LPCWSTR lpEntryModified) {
      return IPWorks_Atom_Set(m_pObj, 10000+63, iEntryIndex, (void*)lpEntryModified, 0);
    }

    inline LPWSTR GetEntryPublished(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+64, iEntryIndex, 0);
    }

    inline int SetEntryPublished(int iEntryIndex, LPCWSTR lpEntryPublished) {
      return IPWorks_Atom_Set(m_pObj, 10000+64, iEntryIndex, (void*)lpEntryPublished, 0);
    }

    inline LPWSTR GetEntryRights(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+65, iEntryIndex, 0);
    }

    inline int SetEntryRights(int iEntryIndex, LPCWSTR lpEntryRights) {
      return IPWorks_Atom_Set(m_pObj, 10000+65, iEntryIndex, (void*)lpEntryRights, 0);
    }



    inline LPWSTR GetEntrySource(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+67, iEntryIndex, 0);
    }

    inline int SetEntrySource(int iEntryIndex, LPCWSTR lpEntrySource) {
      return IPWorks_Atom_Set(m_pObj, 10000+67, iEntryIndex, (void*)lpEntrySource, 0);
    }

    inline LPWSTR GetEntrySummary(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+68, iEntryIndex, 0);
    }

    inline int SetEntrySummary(int iEntryIndex, LPCWSTR lpEntrySummary) {
      return IPWorks_Atom_Set(m_pObj, 10000+68, iEntryIndex, (void*)lpEntrySummary, 0);
    }



    inline LPWSTR GetEntryTitle(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+70, iEntryIndex, 0);
    }

    inline int SetEntryTitle(int iEntryIndex, LPCWSTR lpEntryTitle) {
      return IPWorks_Atom_Set(m_pObj, 10000+70, iEntryIndex, (void*)lpEntryTitle, 0);
    }



    inline LPWSTR GetEntryUpdated(int iEntryIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+72, iEntryIndex, 0);
    }

    inline int SetEntryUpdated(int iEntryIndex, LPCWSTR lpEntryUpdated) {
      return IPWorks_Atom_Set(m_pObj, 10000+72, iEntryIndex, (void*)lpEntryUpdated, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+75, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_Atom_Set(m_pObj, 10000+75, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+76, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_Atom_Set(m_pObj, 10000+76, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+78, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_Atom_Set(m_pObj, 10000+78, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetIfModifiedSince() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+81, 0, 0);
    }

    inline int SetIfModifiedSince(LPCWSTR lpIfModifiedSince) {
      return IPWorks_Atom_Set(m_pObj, 10000+81, 0, (void*)lpIfModifiedSince, 0);
    }

    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+10000+82, 0, 0);
    }

    inline int SetLocalFile(LPCWSTR lpLocalFile) {
      return IPWorks_Atom_Set(m_pObj, 10000+10000+82, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+83, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_Atom_Set(m_pObj, 10000+83, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetNamespacePrefix(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+85, iNamespaceIndex, 0);
    }

    inline int SetNamespacePrefix(int iNamespaceIndex, LPCWSTR lpNamespacePrefix) {
      return IPWorks_Atom_Set(m_pObj, 10000+85, iNamespaceIndex, (void*)lpNamespacePrefix, 0);
    }

    inline LPWSTR GetNamespaceURI(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+86, iNamespaceIndex, 0);
    }

    inline int SetNamespaceURI(int iNamespaceIndex, LPCWSTR lpNamespaceURI) {
      return IPWorks_Atom_Set(m_pObj, 10000+86, iNamespaceIndex, (void*)lpNamespaceURI, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+87, 0, 0);
    }

    inline int SetOtherHeaders(LPCWSTR lpOtherHeaders) {
      return IPWorks_Atom_Set(m_pObj, 10000+87, 0, (void*)lpOtherHeaders, 0);
    }



    inline LPWSTR GetParsedHeaderField(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+89, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetParsedHeaderValue(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+90, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+91, 0, 0);
    }

    inline int SetPassword(LPCWSTR lpPassword) {
      return IPWorks_Atom_Set(m_pObj, 10000+91, 0, (void*)lpPassword, 0);
    }





    inline LPWSTR GetProxyPassword() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+94, 0, 0);
    }

    inline int SetProxyPassword(LPCWSTR lpProxyPassword) {
      return IPWorks_Atom_Set(m_pObj, 10000+94, 0, (void*)lpProxyPassword, 0);
    }



    inline LPWSTR GetProxyServer() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+96, 0, 0);
    }

    inline int SetProxyServer(LPCWSTR lpProxyServer) {
      return IPWorks_Atom_Set(m_pObj, 10000+96, 0, (void*)lpProxyServer, 0);
    }



    inline LPWSTR GetProxyUser() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+98, 0, 0);
    }

    inline int SetProxyUser(LPCWSTR lpProxyUser) {
      return IPWorks_Atom_Set(m_pObj, 10000+98, 0, (void*)lpProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+99, 0, 0);
    }

    inline int SetReferer(LPCWSTR lpReferer) {
      return IPWorks_Atom_Set(m_pObj, 10000+99, 0, (void*)lpReferer, 0);
    }

    inline LPWSTR GetSlug() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+100, 0, 0);
    }

    inline int SetSlug(LPCWSTR lpSlug) {
      return IPWorks_Atom_Set(m_pObj, 10000+100, 0, (void*)lpSlug, 0);
    }

    inline LPWSTR GetSSLAcceptServerCertEncoded() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+101, 0, 0);
    }

    inline int SetSSLAcceptServerCertEncoded(LPCWSTR lpSSLAcceptServerCertEncoded) {
      return IPWorks_Atom_Set(m_pObj, 10000+101, 0, (void*)lpSSLAcceptServerCertEncoded, 0);
    }
    inline int GetSSLAcceptServerCertEncodedB(char *&lpSSLAcceptServerCertEncoded, int &lenSSLAcceptServerCertEncoded) {
      lpSSLAcceptServerCertEncoded = (char*)IPWorks_Atom_Get(m_pObj, 101, 0, &lenSSLAcceptServerCertEncoded);
      return lpSSLAcceptServerCertEncoded ? 0 : lenSSLAcceptServerCertEncoded;
    }
    inline int SetSSLAcceptServerCertEncodedB(const char *lpSSLAcceptServerCertEncoded, int lenSSLAcceptServerCertEncoded) {
      return IPWorks_Atom_Set(m_pObj, 101, 0, (void*)lpSSLAcceptServerCertEncoded, lenSSLAcceptServerCertEncoded);
    }
    inline LPWSTR GetSSLCertEncoded() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+102, 0, 0);
    }

    inline int SetSSLCertEncoded(LPCWSTR lpSSLCertEncoded) {
      return IPWorks_Atom_Set(m_pObj, 10000+102, 0, (void*)lpSSLCertEncoded, 0);
    }
    inline int GetSSLCertEncodedB(char *&lpSSLCertEncoded, int &lenSSLCertEncoded) {
      lpSSLCertEncoded = (char*)IPWorks_Atom_Get(m_pObj, 102, 0, &lenSSLCertEncoded);
      return lpSSLCertEncoded ? 0 : lenSSLCertEncoded;
    }
    inline int SetSSLCertEncodedB(const char *lpSSLCertEncoded, int lenSSLCertEncoded) {
      return IPWorks_Atom_Set(m_pObj, 102, 0, (void*)lpSSLCertEncoded, lenSSLCertEncoded);
    }
    inline LPWSTR GetSSLCertStore() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+103, 0, 0);
    }

    inline int SetSSLCertStore(LPCWSTR lpSSLCertStore) {
      return IPWorks_Atom_Set(m_pObj, 10000+103, 0, (void*)lpSSLCertStore, 0);
    }
    inline int GetSSLCertStoreB(char *&lpSSLCertStore, int &lenSSLCertStore) {
      lpSSLCertStore = (char*)IPWorks_Atom_Get(m_pObj, 103, 0, &lenSSLCertStore);
      return lpSSLCertStore ? 0 : lenSSLCertStore;
    }
    inline int SetSSLCertStoreB(const char *lpSSLCertStore, int lenSSLCertStore) {
      return IPWorks_Atom_Set(m_pObj, 103, 0, (void*)lpSSLCertStore, lenSSLCertStore);
    }
    inline LPWSTR GetSSLCertStorePassword() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+104, 0, 0);
    }

    inline int SetSSLCertStorePassword(LPCWSTR lpSSLCertStorePassword) {
      return IPWorks_Atom_Set(m_pObj, 10000+104, 0, (void*)lpSSLCertStorePassword, 0);
    }



    inline LPWSTR GetSSLCertSubject() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+106, 0, 0);
    }

    inline int SetSSLCertSubject(LPCWSTR lpSSLCertSubject) {
      return IPWorks_Atom_Set(m_pObj, 10000+106, 0, (void*)lpSSLCertSubject, 0);
    }

    inline LPWSTR GetSSLServerCertEncoded() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+107, 0, 0);
    }


    inline int GetSSLServerCertEncodedB(char *&lpSSLServerCertEncoded, int &lenSSLServerCertEncoded) {
      lpSSLServerCertEncoded = (char*)IPWorks_Atom_Get(m_pObj, 107, 0, &lenSSLServerCertEncoded);
      return lpSSLServerCertEncoded ? 0 : lenSSLServerCertEncoded;
    }



    inline LPWSTR GetTransferredData() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+109, 0, 0);
    }


    inline int GetTransferredDataB(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_Atom_Get(m_pObj, 109, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }



    inline LPWSTR GetTransferredHeaders() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+111, 0, 0);
    }



    inline LPWSTR GetUpdateEntryAuthorEmail() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+112, 0, 0);
    }

    inline int SetUpdateEntryAuthorEmail(LPCWSTR lpUpdateEntryAuthorEmail) {
      return IPWorks_Atom_Set(m_pObj, 10000+112, 0, (void*)lpUpdateEntryAuthorEmail, 0);
    }

    inline LPWSTR GetUpdateEntryAuthorName() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+113, 0, 0);
    }

    inline int SetUpdateEntryAuthorName(LPCWSTR lpUpdateEntryAuthorName) {
      return IPWorks_Atom_Set(m_pObj, 10000+113, 0, (void*)lpUpdateEntryAuthorName, 0);
    }

    inline LPWSTR GetUpdateEntryAuthorUri() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+114, 0, 0);
    }

    inline int SetUpdateEntryAuthorUri(LPCWSTR lpUpdateEntryAuthorUri) {
      return IPWorks_Atom_Set(m_pObj, 10000+114, 0, (void*)lpUpdateEntryAuthorUri, 0);
    }

    inline LPWSTR GetUpdateEntryCategoryLabel() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+115, 0, 0);
    }

    inline int SetUpdateEntryCategoryLabel(LPCWSTR lpUpdateEntryCategoryLabel) {
      return IPWorks_Atom_Set(m_pObj, 10000+115, 0, (void*)lpUpdateEntryCategoryLabel, 0);
    }

    inline LPWSTR GetUpdateEntryCategoryScheme() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+116, 0, 0);
    }

    inline int SetUpdateEntryCategoryScheme(LPCWSTR lpUpdateEntryCategoryScheme) {
      return IPWorks_Atom_Set(m_pObj, 10000+116, 0, (void*)lpUpdateEntryCategoryScheme, 0);
    }

    inline LPWSTR GetUpdateEntryCategoryTerm() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+117, 0, 0);
    }

    inline int SetUpdateEntryCategoryTerm(LPCWSTR lpUpdateEntryCategoryTerm) {
      return IPWorks_Atom_Set(m_pObj, 10000+117, 0, (void*)lpUpdateEntryCategoryTerm, 0);
    }

    inline LPWSTR GetUpdateEntryContent() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+118, 0, 0);
    }

    inline int SetUpdateEntryContent(LPCWSTR lpUpdateEntryContent) {
      return IPWorks_Atom_Set(m_pObj, 10000+118, 0, (void*)lpUpdateEntryContent, 0);
    }



    inline LPWSTR GetUpdateEntryContributorEmail() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+120, 0, 0);
    }

    inline int SetUpdateEntryContributorEmail(LPCWSTR lpUpdateEntryContributorEmail) {
      return IPWorks_Atom_Set(m_pObj, 10000+120, 0, (void*)lpUpdateEntryContributorEmail, 0);
    }

    inline LPWSTR GetUpdateEntryContributorName() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+121, 0, 0);
    }

    inline int SetUpdateEntryContributorName(LPCWSTR lpUpdateEntryContributorName) {
      return IPWorks_Atom_Set(m_pObj, 10000+121, 0, (void*)lpUpdateEntryContributorName, 0);
    }

    inline LPWSTR GetUpdateEntryContributorUri() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+122, 0, 0);
    }

    inline int SetUpdateEntryContributorUri(LPCWSTR lpUpdateEntryContributorUri) {
      return IPWorks_Atom_Set(m_pObj, 10000+122, 0, (void*)lpUpdateEntryContributorUri, 0);
    }

    inline LPWSTR GetUpdateEntryCopyright() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+123, 0, 0);
    }

    inline int SetUpdateEntryCopyright(LPCWSTR lpUpdateEntryCopyright) {
      return IPWorks_Atom_Set(m_pObj, 10000+123, 0, (void*)lpUpdateEntryCopyright, 0);
    }

    inline LPWSTR GetUpdateEntryCreated() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+124, 0, 0);
    }

    inline int SetUpdateEntryCreated(LPCWSTR lpUpdateEntryCreated) {
      return IPWorks_Atom_Set(m_pObj, 10000+124, 0, (void*)lpUpdateEntryCreated, 0);
    }

    inline LPWSTR GetUpdateEntryXML() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+125, 0, 0);
    }

    inline int SetUpdateEntryXML(LPCWSTR lpUpdateEntryXML) {
      return IPWorks_Atom_Set(m_pObj, 10000+125, 0, (void*)lpUpdateEntryXML, 0);
    }

    inline LPWSTR GetUpdateEntryId() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+126, 0, 0);
    }

    inline int SetUpdateEntryId(LPCWSTR lpUpdateEntryId) {
      return IPWorks_Atom_Set(m_pObj, 10000+126, 0, (void*)lpUpdateEntryId, 0);
    }

    inline LPWSTR GetUpdateEntryIssued() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+127, 0, 0);
    }

    inline int SetUpdateEntryIssued(LPCWSTR lpUpdateEntryIssued) {
      return IPWorks_Atom_Set(m_pObj, 10000+127, 0, (void*)lpUpdateEntryIssued, 0);
    }

    inline LPWSTR GetUpdateEntryLinkHref() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+128, 0, 0);
    }

    inline int SetUpdateEntryLinkHref(LPCWSTR lpUpdateEntryLinkHref) {
      return IPWorks_Atom_Set(m_pObj, 10000+128, 0, (void*)lpUpdateEntryLinkHref, 0);
    }

    inline LPWSTR GetUpdateEntryLinkHrefLang() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+129, 0, 0);
    }

    inline int SetUpdateEntryLinkHrefLang(LPCWSTR lpUpdateEntryLinkHrefLang) {
      return IPWorks_Atom_Set(m_pObj, 10000+129, 0, (void*)lpUpdateEntryLinkHrefLang, 0);
    }

    inline LPWSTR GetUpdateEntryLinkLength() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+130, 0, 0);
    }

    inline int SetUpdateEntryLinkLength(LPCWSTR lpUpdateEntryLinkLength) {
      return IPWorks_Atom_Set(m_pObj, 10000+130, 0, (void*)lpUpdateEntryLinkLength, 0);
    }

    inline LPWSTR GetUpdateEntryLinkRel() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+131, 0, 0);
    }

    inline int SetUpdateEntryLinkRel(LPCWSTR lpUpdateEntryLinkRel) {
      return IPWorks_Atom_Set(m_pObj, 10000+131, 0, (void*)lpUpdateEntryLinkRel, 0);
    }

    inline LPWSTR GetUpdateEntryLinkTitle() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+132, 0, 0);
    }

    inline int SetUpdateEntryLinkTitle(LPCWSTR lpUpdateEntryLinkTitle) {
      return IPWorks_Atom_Set(m_pObj, 10000+132, 0, (void*)lpUpdateEntryLinkTitle, 0);
    }

    inline LPWSTR GetUpdateEntryLinkType() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+133, 0, 0);
    }

    inline int SetUpdateEntryLinkType(LPCWSTR lpUpdateEntryLinkType) {
      return IPWorks_Atom_Set(m_pObj, 10000+133, 0, (void*)lpUpdateEntryLinkType, 0);
    }

    inline LPWSTR GetUpdateEntryModified() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+134, 0, 0);
    }

    inline int SetUpdateEntryModified(LPCWSTR lpUpdateEntryModified) {
      return IPWorks_Atom_Set(m_pObj, 10000+134, 0, (void*)lpUpdateEntryModified, 0);
    }

    inline LPWSTR GetUpdateEntryPublished() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+135, 0, 0);
    }

    inline int SetUpdateEntryPublished(LPCWSTR lpUpdateEntryPublished) {
      return IPWorks_Atom_Set(m_pObj, 10000+135, 0, (void*)lpUpdateEntryPublished, 0);
    }

    inline LPWSTR GetUpdateEntryRights() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+136, 0, 0);
    }

    inline int SetUpdateEntryRights(LPCWSTR lpUpdateEntryRights) {
      return IPWorks_Atom_Set(m_pObj, 10000+136, 0, (void*)lpUpdateEntryRights, 0);
    }



    inline LPWSTR GetUpdateEntrySource() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+138, 0, 0);
    }

    inline int SetUpdateEntrySource(LPCWSTR lpUpdateEntrySource) {
      return IPWorks_Atom_Set(m_pObj, 10000+138, 0, (void*)lpUpdateEntrySource, 0);
    }

    inline LPWSTR GetUpdateEntrySummary() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+139, 0, 0);
    }

    inline int SetUpdateEntrySummary(LPCWSTR lpUpdateEntrySummary) {
      return IPWorks_Atom_Set(m_pObj, 10000+139, 0, (void*)lpUpdateEntrySummary, 0);
    }



    inline LPWSTR GetUpdateEntryTitle() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+141, 0, 0);
    }

    inline int SetUpdateEntryTitle(LPCWSTR lpUpdateEntryTitle) {
      return IPWorks_Atom_Set(m_pObj, 10000+141, 0, (void*)lpUpdateEntryTitle, 0);
    }



    inline LPWSTR GetUpdateEntryUpdated() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+143, 0, 0);
    }

    inline int SetUpdateEntryUpdated(LPCWSTR lpUpdateEntryUpdated) {
      return IPWorks_Atom_Set(m_pObj, 10000+143, 0, (void*)lpUpdateEntryUpdated, 0);
    }

    inline LPWSTR GetUpdateFile() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+144, 0, 0);
    }

    inline int SetUpdateFile(LPCWSTR lpUpdateFile) {
      return IPWorks_Atom_Set(m_pObj, 10000+144, 0, (void*)lpUpdateFile, 0);
    }

    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_Atom_Get(m_pObj, 10000+145, 0, 0);
    }

    inline int SetUser(LPCWSTR lpUser) {
      return IPWorks_Atom_Set(m_pObj, 10000+145, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnected(AtomConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(AtomConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(AtomDisconnectedEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(AtomEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(AtomErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(AtomHeaderEventParamsW *e) {return 0;}
    virtual int FireLog(AtomLogEventParamsW *e) {return 0;}
    virtual int FireRedirect(AtomRedirectEventParamsW *e) {return 0;}
    virtual int FireSetCookie(AtomSetCookieEventParamsW *e) {return 0;}
    virtual int FireSSLServerAuthentication(AtomSSLServerAuthenticationEventParamsW *e) {return 0;}
    virtual int FireSSLStatus(AtomSSLStatusEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(AtomStartTransferEventParamsW *e) {return 0;}
    virtual int FireStatus(AtomStatusEventParamsW *e) {return 0;}
    virtual int FireTransfer(AtomTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int AtomEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            AtomConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            AtomConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            AtomDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            AtomEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 5: {
            AtomErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            AtomHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 7: {
            AtomLogEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireLog(&e);
            break;
         }
         case 8: {
            AtomRedirectEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = FireRedirect(&e);
            param[1] = (void*)(e.Accept);
            break;
         }
         case 9: {
            AtomSetCookieEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = FireSetCookie(&e);
            break;
         }
         case 10: {
            AtomSSLServerAuthenticationEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSSLServerAuthentication(&e);
            param[4] = (void*)(e.Accept);
            break;
         }
         case 11: {
            AtomSSLStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireSSLStatus(&e);
            break;
         }
         case 12: {
            AtomStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 13: {
            AtomStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireStatus(&e);
            break;
         }
         case 14: {
            AtomTransferEventParamsW e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(AtomConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(AtomConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(AtomDisconnectedEventParams *e) {return -10000;}
    virtual int FireEndTransfer(AtomEndTransferEventParams *e) {return -10000;}
    virtual int FireError(AtomErrorEventParams *e) {return -10000;}
    virtual int FireHeader(AtomHeaderEventParams *e) {return -10000;}
    virtual int FireLog(AtomLogEventParams *e) {return -10000;}
    virtual int FireRedirect(AtomRedirectEventParams *e) {return -10000;}
    virtual int FireSetCookie(AtomSetCookieEventParams *e) {return -10000;}
    virtual int FireSSLServerAuthentication(AtomSSLServerAuthenticationEventParams *e) {return -10000;}
    virtual int FireSSLStatus(AtomSSLStatusEventParams *e) {return -10000;}
    virtual int FireStartTransfer(AtomStartTransferEventParams *e) {return -10000;}
    virtual int FireStatus(AtomStatusEventParams *e) {return -10000;}
    virtual int FireTransfer(AtomTransferEventParams *e) {return -10000;}

  public: //methods

    inline int AddCookie(LPWSTR lpszCookieName, LPWSTR lpszCookieValue) {
      void *param[2+1] = {(void*)lpszCookieName, (void*)lpszCookieValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+2, 2, param, cbparam);
      
    }
    inline int AddNamespace(LPWSTR lpszPrefix, LPWSTR lpszNamespaceURI) {
      void *param[2+1] = {(void*)lpszPrefix, (void*)lpszNamespaceURI, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+3, 2, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Atom_Do(m_pObj, 10000+4, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DeleteResource(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+5, 1, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int GetFeed(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+7, 1, param, cbparam);
      
    }
    inline LPWSTR GetProperty(LPWSTR lpszPropertyName) {
      void *param[1+1] = {(void*)lpszPropertyName, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Atom_Do(m_pObj, 10000+8, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int GetResource(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+9, 1, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int PostResource(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+11, 1, param, cbparam);
      
    }
    inline int Put(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+12, 1, param, cbparam);
      
    }
    inline int PutResource(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+13, 1, param, cbparam);
      
    }
    inline int ReadFile(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+14, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Atom_Do(m_pObj, 10000+15, 0, param, cbparam);
      
    }
    inline int SetProperty(LPWSTR lpszPropertyName, LPWSTR lpszPropertyValue) {
      void *param[2+1] = {(void*)lpszPropertyName, (void*)lpszPropertyValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+16, 2, param, cbparam);
      
    }
    inline int WriteFile(LPWSTR lpszFilename) {
      void *param[1+1] = {(void*)lpszFilename, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Atom_Do(m_pObj, 10000+17, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_ATOM_H_




