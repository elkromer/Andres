/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_MIME_H_
#define _IPWORKS_MIME_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//MIMEPartEncodings
#define PE_7BIT                                            0
#define PE_QUOTED_PRINTABLE                                1
#define PE_BASE_64                                         2
#define PE_8BIT                                            3
#define PE_BINARY                                          4
#define PE_UUENCODE                                        5


extern "C" void* IPWORKS_CALL IPWorks_MIME_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_MIME_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_MIME_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_MIME_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_MIME_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_MIME_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_MIME_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_MIME_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_MIME_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} MIMEErrorEventParams;

typedef struct {
  int PartIndex;
  const char *Field;
  const char *Value;
  int lenValue;
  int reserved;
} MIMEHeaderEventParams;

typedef struct {
  int PercentDone;
  int reserved;
} MIMEProgressEventParams;


class MIME {
  public: // Events
    virtual int FireError(MIMEErrorEventParams *e) {return 0;}
    virtual int FireHeader(MIMEHeaderEventParams *e) {return 0;}
    virtual int FireProgress(MIMEProgressEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL MIMEEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          MIMEErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((MIME*)lpObj)->FireError(&e);
          break;
        }
        case 2: {
          MIMEHeaderEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[2]), 0};
          ret_code = ((MIME*)lpObj)->FireHeader(&e);
          break;
        }
        case 3: {
          MIMEProgressEventParams e = {(int)IPW64CAST(param[0]), 0};
          ret_code = ((MIME*)lpObj)->FireProgress(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    MIME(char *lpOemKey = (char*)IPWORKS_OEMKEY_28) {
      m_pObj = IPWorks_MIME_Create(MIMEEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~MIME() {
      IPWorks_MIME_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_MIME_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_MIME_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_MIME_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_MIME_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_MIME_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline char* GetBoundary() {
      void* val = IPWorks_MIME_Get(m_pObj, 1, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetBoundary(const char* lpszBoundary) {
      return IPWorks_MIME_Set(m_pObj, 1, 0, (void*)lpszBoundary, 0);
    }

    inline char* GetContentType() {
      void* val = IPWorks_MIME_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetContentType(const char* lpszContentType) {
      return IPWorks_MIME_Set(m_pObj, 2, 0, (void*)lpszContentType, 0);
    }

    inline char* GetContentTypeAttr() {
      void* val = IPWorks_MIME_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetContentTypeAttr(const char* lpszContentTypeAttr) {
      return IPWorks_MIME_Set(m_pObj, 3, 0, (void*)lpszContentTypeAttr, 0);
    }

    inline int GetMessage(char* &lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_MIME_Get(m_pObj, 4, 0, &lenMessage, NULL);
      return lpMessage ? 0 : lenMessage;
    }
    inline int SetMessage(const char* lpMessage, int lenMessage) {
      return IPWorks_MIME_Set(m_pObj, 4, 0, (void*)lpMessage, lenMessage);
    }

    inline int GetMessageHeaderCount() {
      void* val = IPWorks_MIME_Get(m_pObj, 5, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetMessageHeaderCount(int iMessageHeaderCount) {
      void* val = (void*)IPW64CAST(iMessageHeaderCount);
      return IPWorks_MIME_Set(m_pObj, 5, 0, val, 0);
    }

    inline char* GetMessageHeaderField(int iMessageHeaderIndex) {
      void* val = IPWorks_MIME_Get(m_pObj, 6, iMessageHeaderIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageHeaderField(int iMessageHeaderIndex, const char* lpszMessageHeaderField) {
      return IPWorks_MIME_Set(m_pObj, 6, iMessageHeaderIndex, (void*)lpszMessageHeaderField, 0);
    }

    inline char* GetMessageHeaderValue(int iMessageHeaderIndex) {
      void* val = IPWorks_MIME_Get(m_pObj, 7, iMessageHeaderIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageHeaderValue(int iMessageHeaderIndex, const char* lpszMessageHeaderValue) {
      return IPWorks_MIME_Set(m_pObj, 7, iMessageHeaderIndex, (void*)lpszMessageHeaderValue, 0);
    }

    inline char* GetMessageHeadersString() {
      void* val = IPWorks_MIME_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetMessageHeadersString(const char* lpszMessageHeadersString) {
      return IPWorks_MIME_Set(m_pObj, 8, 0, (void*)lpszMessageHeadersString, 0);
    }

    inline int GetPartCount() {
      void* val = IPWorks_MIME_Get(m_pObj, 9, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetPartCount(int iPartCount) {
      void* val = (void*)IPW64CAST(iPartCount);
      return IPWorks_MIME_Set(m_pObj, 9, 0, val, 0);
    }

    inline char* GetPartContentDisposition(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 10, iPartIdx, NULL, NULL);
      return (char*)val;
    }
    inline int SetPartContentDisposition(int iPartIdx, const char* lpszPartContentDisposition) {
      return IPWorks_MIME_Set(m_pObj, 10, iPartIdx, (void*)lpszPartContentDisposition, 0);
    }

    inline char* GetPartContentDispositionAttr(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 11, iPartIdx, NULL, NULL);
      return (char*)val;
    }
    inline int SetPartContentDispositionAttr(int iPartIdx, const char* lpszPartContentDispositionAttr) {
      return IPWorks_MIME_Set(m_pObj, 11, iPartIdx, (void*)lpszPartContentDispositionAttr, 0);
    }

    inline char* GetPartContentId(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 12, iPartIdx, NULL, NULL);
      return (char*)val;
    }
    inline int SetPartContentId(int iPartIdx, const char* lpszPartContentId) {
      return IPWorks_MIME_Set(m_pObj, 12, iPartIdx, (void*)lpszPartContentId, 0);
    }

    inline char* GetPartContentType(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 13, iPartIdx, NULL, NULL);
      return (char*)val;
    }
    inline int SetPartContentType(int iPartIdx, const char* lpszPartContentType) {
      return IPWorks_MIME_Set(m_pObj, 13, iPartIdx, (void*)lpszPartContentType, 0);
    }

    inline char* GetPartContentTypeAttr(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 14, iPartIdx, NULL, NULL);
      return (char*)val;
    }
    inline int SetPartContentTypeAttr(int iPartIdx, const char* lpszPartContentTypeAttr) {
      return IPWorks_MIME_Set(m_pObj, 14, iPartIdx, (void*)lpszPartContentTypeAttr, 0);
    }

    inline char* GetPartDecodedFile(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 15, iPartIdx, NULL, NULL);
      return (char*)val;
    }
    inline int SetPartDecodedFile(int iPartIdx, const char* lpszPartDecodedFile) {
      return IPWorks_MIME_Set(m_pObj, 15, iPartIdx, (void*)lpszPartDecodedFile, 0);
    }

    inline int GetPartDecodedString(int iPartIdx, char* &lpPartDecodedString, int &lenPartDecodedString) {
      lpPartDecodedString = (char*)IPWorks_MIME_Get(m_pObj, 16, iPartIdx, &lenPartDecodedString, NULL);
      return lpPartDecodedString ? 0 : lenPartDecodedString;
    }
    inline int SetPartDecodedString(int iPartIdx, const char* lpPartDecodedString, int lenPartDecodedString) {
      return IPWorks_MIME_Set(m_pObj, 16, iPartIdx, (void*)lpPartDecodedString, lenPartDecodedString);
    }

    inline int GetPartEncoding(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 17, iPartIdx, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetPartEncoding(int iPartIdx, int iPartEncoding) {
      void* val = (void*)IPW64CAST(iPartEncoding);
      return IPWorks_MIME_Set(m_pObj, 17, iPartIdx, val, 0);
    }

    inline char* GetPartFilename(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 18, iPartIdx, NULL, NULL);
      return (char*)val;
    }
    inline int SetPartFilename(int iPartIdx, const char* lpszPartFilename) {
      return IPWorks_MIME_Set(m_pObj, 18, iPartIdx, (void*)lpszPartFilename, 0);
    }

    inline char* GetPartHeaders(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 19, iPartIdx, NULL, NULL);
      return (char*)val;
    }
    inline int SetPartHeaders(int iPartIdx, const char* lpszPartHeaders) {
      return IPWorks_MIME_Set(m_pObj, 19, iPartIdx, (void*)lpszPartHeaders, 0);
    }

    inline char* GetPartName(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 20, iPartIdx, NULL, NULL);
      return (char*)val;
    }
    inline int SetPartName(int iPartIdx, const char* lpszPartName) {
      return IPWorks_MIME_Set(m_pObj, 20, iPartIdx, (void*)lpszPartName, 0);
    }

    inline int GetPartSize(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 21, iPartIdx, NULL, NULL);
      return (int)(long)val;
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_MIME_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int DecodeFromFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int DecodeFromString() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int EncodeToFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 6, 0, param, cbparam, NULL);
    }

    inline int EncodeToString() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 8, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int ResetData() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 10, 0, param, cbparam, NULL);
    }

};

#endif //_IPWORKS_MIME_H_
