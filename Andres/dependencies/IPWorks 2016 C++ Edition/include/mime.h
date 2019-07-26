/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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


extern "C" void* IPWORKS_CALL IPWorks_MIME_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_MIME_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_MIME_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_MIME_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_MIME_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_MIME_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_MIME_GetLastErrorCode(void *lpObj);
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
  const char* Description;
  int reserved;
} MIMEErrorEventParams;

typedef struct {
  int PartIndex;
  const char* Field;
  const char* Value;
  int lenValue;
  int reserved;
} MIMEHeaderEventParams;

typedef struct {
  int PercentDone;
  int reserved;
} MIMEProgressEventParams;



class MIME {
  
  public: //events
  
    virtual int FireError(MIMEErrorEventParams *e) {return 0;}
    virtual int FireHeader(MIMEHeaderEventParams *e) {return 0;}
    virtual int FireProgress(MIMEProgressEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL MIMEEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((MIME*)lpObj)->MIMEEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            MIMEErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((MIME*)lpObj)->FireError(&e);
            break;
         }
         case 2: {
            MIMEHeaderEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[2]),  0};
            ret_code = ((MIME*)lpObj)->FireHeader(&e);
            break;
         }
         case 3: {
            MIMEProgressEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((MIME*)lpObj)->FireProgress(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int MIMEEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    MIME(char *lpOemKey = (char*)IPWORKS_OEMKEY_28) {
      m_pObj = IPWorks_MIME_Create(MIMEEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~MIME() {
      IPWorks_MIME_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_MIME_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_MIME_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_MIME_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_MIME_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_MIME_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline char* GetBoundary() {
      void* val = IPWorks_MIME_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetBoundary(const char *lpBoundary) {
      return IPWorks_MIME_Set(m_pObj, 1, 0, (void*)lpBoundary, 0);
    }

    inline char* GetContentType() {
      void* val = IPWorks_MIME_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetContentType(const char *lpContentType) {
      return IPWorks_MIME_Set(m_pObj, 2, 0, (void*)lpContentType, 0);
    }

    inline char* GetContentTypeAttr() {
      void* val = IPWorks_MIME_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetContentTypeAttr(const char *lpContentTypeAttr) {
      return IPWorks_MIME_Set(m_pObj, 3, 0, (void*)lpContentTypeAttr, 0);
    }

    inline int GetMessage(char *&lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_MIME_Get(m_pObj, 4, 0, &lenMessage);
      return lpMessage ? 0 : lenMessage;
    }

    inline int SetMessage(const char *lpMessage, int lenMessage) {
      return IPWorks_MIME_Set(m_pObj, 4, 0, (void*)lpMessage, lenMessage);
    }

    inline int GetMessageHeaderCount() {
      void* val = IPWorks_MIME_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetMessageHeaderCount(int iMessageHeaderCount) {
      void* val = (void*)IPW64CAST(iMessageHeaderCount);
      return IPWorks_MIME_Set(m_pObj, 5, 0, val, 0);
    }
    inline char* GetMessageHeaderField(int iMessageHeaderIndex) {
      void* val = IPWorks_MIME_Get(m_pObj, 6, iMessageHeaderIndex, 0);
      return (char*)val;
    }

    inline int SetMessageHeaderField(int iMessageHeaderIndex, const char *lpMessageHeaderField) {
      return IPWorks_MIME_Set(m_pObj, 6, iMessageHeaderIndex, (void*)lpMessageHeaderField, 0);
    }

    inline char* GetMessageHeaderValue(int iMessageHeaderIndex) {
      void* val = IPWorks_MIME_Get(m_pObj, 7, iMessageHeaderIndex, 0);
      return (char*)val;
    }

    inline int SetMessageHeaderValue(int iMessageHeaderIndex, const char *lpMessageHeaderValue) {
      return IPWorks_MIME_Set(m_pObj, 7, iMessageHeaderIndex, (void*)lpMessageHeaderValue, 0);
    }

    inline char* GetMessageHeadersString() {
      void* val = IPWorks_MIME_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetMessageHeadersString(const char *lpMessageHeadersString) {
      return IPWorks_MIME_Set(m_pObj, 8, 0, (void*)lpMessageHeadersString, 0);
    }

    inline int GetPartCount() {
      void* val = IPWorks_MIME_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetPartCount(int iPartCount) {
      void* val = (void*)IPW64CAST(iPartCount);
      return IPWorks_MIME_Set(m_pObj, 9, 0, val, 0);
    }
    inline char* GetPartContentDisposition(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 10, iPartIdx, 0);
      return (char*)val;
    }

    inline int SetPartContentDisposition(int iPartIdx, const char *lpPartContentDisposition) {
      return IPWorks_MIME_Set(m_pObj, 10, iPartIdx, (void*)lpPartContentDisposition, 0);
    }

    inline char* GetPartContentDispositionAttr(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 11, iPartIdx, 0);
      return (char*)val;
    }

    inline int SetPartContentDispositionAttr(int iPartIdx, const char *lpPartContentDispositionAttr) {
      return IPWorks_MIME_Set(m_pObj, 11, iPartIdx, (void*)lpPartContentDispositionAttr, 0);
    }

    inline char* GetPartContentId(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 12, iPartIdx, 0);
      return (char*)val;
    }

    inline int SetPartContentId(int iPartIdx, const char *lpPartContentId) {
      return IPWorks_MIME_Set(m_pObj, 12, iPartIdx, (void*)lpPartContentId, 0);
    }

    inline char* GetPartContentType(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 13, iPartIdx, 0);
      return (char*)val;
    }

    inline int SetPartContentType(int iPartIdx, const char *lpPartContentType) {
      return IPWorks_MIME_Set(m_pObj, 13, iPartIdx, (void*)lpPartContentType, 0);
    }

    inline char* GetPartContentTypeAttr(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 14, iPartIdx, 0);
      return (char*)val;
    }

    inline int SetPartContentTypeAttr(int iPartIdx, const char *lpPartContentTypeAttr) {
      return IPWorks_MIME_Set(m_pObj, 14, iPartIdx, (void*)lpPartContentTypeAttr, 0);
    }

    inline char* GetPartDecodedFile(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 15, iPartIdx, 0);
      return (char*)val;
    }

    inline int SetPartDecodedFile(int iPartIdx, const char *lpPartDecodedFile) {
      return IPWorks_MIME_Set(m_pObj, 15, iPartIdx, (void*)lpPartDecodedFile, 0);
    }

    inline int GetPartDecodedString(int iPartIdx, char *&lpPartDecodedString, int &lenPartDecodedString) {
      lpPartDecodedString = (char*)IPWorks_MIME_Get(m_pObj, 16, iPartIdx, &lenPartDecodedString);
      return lpPartDecodedString ? 0 : lenPartDecodedString;
    }

    inline int SetPartDecodedString(int iPartIdx, const char *lpPartDecodedString, int lenPartDecodedString) {
      return IPWorks_MIME_Set(m_pObj, 16, iPartIdx, (void*)lpPartDecodedString, lenPartDecodedString);
    }

    inline int GetPartEncoding(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 17, iPartIdx, 0);
      return (int)(long)val;
    }
    inline int SetPartEncoding(int iPartIdx, int iPartEncoding) {
      void* val = (void*)IPW64CAST(iPartEncoding);
      return IPWorks_MIME_Set(m_pObj, 17, iPartIdx, val, 0);
    }
    inline char* GetPartFilename(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 18, iPartIdx, 0);
      return (char*)val;
    }

    inline int SetPartFilename(int iPartIdx, const char *lpPartFilename) {
      return IPWorks_MIME_Set(m_pObj, 18, iPartIdx, (void*)lpPartFilename, 0);
    }

    inline char* GetPartHeaders(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 19, iPartIdx, 0);
      return (char*)val;
    }

    inline int SetPartHeaders(int iPartIdx, const char *lpPartHeaders) {
      return IPWorks_MIME_Set(m_pObj, 19, iPartIdx, (void*)lpPartHeaders, 0);
    }

    inline char* GetPartName(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 20, iPartIdx, 0);
      return (char*)val;
    }

    inline int SetPartName(int iPartIdx, const char *lpPartName) {
      return IPWorks_MIME_Set(m_pObj, 20, iPartIdx, (void*)lpPartName, 0);
    }

    inline int GetPartSize(int iPartIdx) {
      void* val = IPWorks_MIME_Get(m_pObj, 21, iPartIdx, 0);
      return (int)(long)val;
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_MIME_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DecodeFromFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int DecodeFromString() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int EncodeToFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int EncodeToString() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int ResetData() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} MIMEErrorEventParamsW;

typedef struct {
  int PartIndex;
  LPWSTR Field;
  LPWSTR Value;
  int lenValue;
  int reserved;
} MIMEHeaderEventParamsW;

typedef struct {
  int PercentDone;
  int reserved;
} MIMEProgressEventParamsW;



class MIMEW : public MIME {

  public: //properties
  
    inline LPWSTR GetBoundary() {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetBoundary(LPCWSTR lpBoundary) {
      return IPWorks_MIME_Set(m_pObj, 10000+1, 0, (void*)lpBoundary, 0);
    }

    inline LPWSTR GetContentType() {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetContentType(LPCWSTR lpContentType) {
      return IPWorks_MIME_Set(m_pObj, 10000+2, 0, (void*)lpContentType, 0);
    }

    inline LPWSTR GetContentTypeAttr() {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetContentTypeAttr(LPCWSTR lpContentTypeAttr) {
      return IPWorks_MIME_Set(m_pObj, 10000+3, 0, (void*)lpContentTypeAttr, 0);
    }

    inline LPWSTR GetMessage() {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetMessage(LPCWSTR lpMessage) {
      return IPWorks_MIME_Set(m_pObj, 10000+4, 0, (void*)lpMessage, 0);
    }
    inline int GetMessageB(char *&lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_MIME_Get(m_pObj, 4, 0, &lenMessage);
      return lpMessage ? 0 : lenMessage;
    }
    inline int SetMessageB(const char *lpMessage, int lenMessage) {
      return IPWorks_MIME_Set(m_pObj, 4, 0, (void*)lpMessage, lenMessage);
    }


    inline LPWSTR GetMessageHeaderField(int iMessageHeaderIndex) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+6, iMessageHeaderIndex, 0);
    }

    inline int SetMessageHeaderField(int iMessageHeaderIndex, LPCWSTR lpMessageHeaderField) {
      return IPWorks_MIME_Set(m_pObj, 10000+6, iMessageHeaderIndex, (void*)lpMessageHeaderField, 0);
    }

    inline LPWSTR GetMessageHeaderValue(int iMessageHeaderIndex) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+7, iMessageHeaderIndex, 0);
    }

    inline int SetMessageHeaderValue(int iMessageHeaderIndex, LPCWSTR lpMessageHeaderValue) {
      return IPWorks_MIME_Set(m_pObj, 10000+7, iMessageHeaderIndex, (void*)lpMessageHeaderValue, 0);
    }

    inline LPWSTR GetMessageHeadersString() {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetMessageHeadersString(LPCWSTR lpMessageHeadersString) {
      return IPWorks_MIME_Set(m_pObj, 10000+8, 0, (void*)lpMessageHeadersString, 0);
    }



    inline LPWSTR GetPartContentDisposition(int iPartIdx) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+10, iPartIdx, 0);
    }

    inline int SetPartContentDisposition(int iPartIdx, LPCWSTR lpPartContentDisposition) {
      return IPWorks_MIME_Set(m_pObj, 10000+10, iPartIdx, (void*)lpPartContentDisposition, 0);
    }

    inline LPWSTR GetPartContentDispositionAttr(int iPartIdx) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+11, iPartIdx, 0);
    }

    inline int SetPartContentDispositionAttr(int iPartIdx, LPCWSTR lpPartContentDispositionAttr) {
      return IPWorks_MIME_Set(m_pObj, 10000+11, iPartIdx, (void*)lpPartContentDispositionAttr, 0);
    }

    inline LPWSTR GetPartContentId(int iPartIdx) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+12, iPartIdx, 0);
    }

    inline int SetPartContentId(int iPartIdx, LPCWSTR lpPartContentId) {
      return IPWorks_MIME_Set(m_pObj, 10000+12, iPartIdx, (void*)lpPartContentId, 0);
    }

    inline LPWSTR GetPartContentType(int iPartIdx) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+13, iPartIdx, 0);
    }

    inline int SetPartContentType(int iPartIdx, LPCWSTR lpPartContentType) {
      return IPWorks_MIME_Set(m_pObj, 10000+13, iPartIdx, (void*)lpPartContentType, 0);
    }

    inline LPWSTR GetPartContentTypeAttr(int iPartIdx) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+14, iPartIdx, 0);
    }

    inline int SetPartContentTypeAttr(int iPartIdx, LPCWSTR lpPartContentTypeAttr) {
      return IPWorks_MIME_Set(m_pObj, 10000+14, iPartIdx, (void*)lpPartContentTypeAttr, 0);
    }

    inline LPWSTR GetPartDecodedFile(int iPartIdx) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+15, iPartIdx, 0);
    }

    inline int SetPartDecodedFile(int iPartIdx, LPCWSTR lpPartDecodedFile) {
      return IPWorks_MIME_Set(m_pObj, 10000+15, iPartIdx, (void*)lpPartDecodedFile, 0);
    }

    inline LPWSTR GetPartDecodedString(int iPartIdx) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+16, iPartIdx, 0);
    }

    inline int SetPartDecodedString(int iPartIdx, LPCWSTR lpPartDecodedString) {
      return IPWorks_MIME_Set(m_pObj, 10000+16, iPartIdx, (void*)lpPartDecodedString, 0);
    }
    inline int GetPartDecodedStringB(int iPartIdx, char *&lpPartDecodedString, int &lenPartDecodedString) {
      lpPartDecodedString = (char*)IPWorks_MIME_Get(m_pObj, 16, iPartIdx, &lenPartDecodedString);
      return lpPartDecodedString ? 0 : lenPartDecodedString;
    }
    inline int SetPartDecodedStringB(int iPartIdx, const char *lpPartDecodedString, int lenPartDecodedString) {
      return IPWorks_MIME_Set(m_pObj, 16, iPartIdx, (void*)lpPartDecodedString, lenPartDecodedString);
    }


    inline LPWSTR GetPartFilename(int iPartIdx) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+18, iPartIdx, 0);
    }

    inline int SetPartFilename(int iPartIdx, LPCWSTR lpPartFilename) {
      return IPWorks_MIME_Set(m_pObj, 10000+18, iPartIdx, (void*)lpPartFilename, 0);
    }

    inline LPWSTR GetPartHeaders(int iPartIdx) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+19, iPartIdx, 0);
    }

    inline int SetPartHeaders(int iPartIdx, LPCWSTR lpPartHeaders) {
      return IPWorks_MIME_Set(m_pObj, 10000+19, iPartIdx, (void*)lpPartHeaders, 0);
    }

    inline LPWSTR GetPartName(int iPartIdx) {
      return (LPWSTR)IPWorks_MIME_Get(m_pObj, 10000+20, iPartIdx, 0);
    }

    inline int SetPartName(int iPartIdx, LPCWSTR lpPartName) {
      return IPWorks_MIME_Set(m_pObj, 10000+20, iPartIdx, (void*)lpPartName, 0);
    }





  public: //events
  
    virtual int FireError(MIMEErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(MIMEHeaderEventParamsW *e) {return 0;}
    virtual int FireProgress(MIMEProgressEventParamsW *e) {return 0;}


  protected:
  
    virtual int MIMEEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            MIMEErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 2: {
            MIMEHeaderEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[2]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 3: {
            MIMEProgressEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireProgress(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireError(MIMEErrorEventParams *e) {return -10000;}
    virtual int FireHeader(MIMEHeaderEventParams *e) {return -10000;}
    virtual int FireProgress(MIMEProgressEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_MIME_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DecodeFromFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int DecodeFromString() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int EncodeToFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int EncodeToString() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int ResetData() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_MIME_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_MIME_H_




