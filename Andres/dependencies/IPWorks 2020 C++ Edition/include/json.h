/******************************************************************************
  IPWorks 2020 C++ Edition
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_JSON_H_
#define _IPWORKS_JSON_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//TXElementType
#define ET_OBJECT                                          0
#define ET_ARRAY                                           1
#define ET_STRING                                          2
#define ET_NUMBER                                          3
#define ET_BOOL                                            4
#define ET_NULL                                            5


extern "C" void* IPWORKS_CALL IPWorks_JSON_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_JSON_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_JSON_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_JSON_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_JSON_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_JSON_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_JSON_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_JSON_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_JSON_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  const char *Text;
  int reserved;
} JSONCharactersEventParams;

typedef struct {
  int reserved;
} JSONEndDocumentEventParams;

typedef struct {
  const char *Element;
  int reserved;
} JSONEndElementEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} JSONErrorEventParams;

typedef struct {
  const char *Text;
  int reserved;
} JSONIgnorableWhitespaceEventParams;

typedef struct {
  const char *Text;
  int reserved;
} JSONJSONEventParams;

typedef struct {
  int reserved;
} JSONStartDocumentEventParams;

typedef struct {
  const char *Element;
  int reserved;
} JSONStartElementEventParams;


class JSON {
  public: // Events
    virtual int FireCharacters(JSONCharactersEventParams *e) {return 0;}
    virtual int FireEndDocument(JSONEndDocumentEventParams *e) {return 0;}
    virtual int FireEndElement(JSONEndElementEventParams *e) {return 0;}
    virtual int FireError(JSONErrorEventParams *e) {return 0;}
    virtual int FireIgnorableWhitespace(JSONIgnorableWhitespaceEventParams *e) {return 0;}
    virtual int FireJSON(JSONJSONEventParams *e) {return 0;}
    virtual int FireStartDocument(JSONStartDocumentEventParams *e) {return 0;}
    virtual int FireStartElement(JSONStartElementEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL JSONEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          JSONCharactersEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((JSON*)lpObj)->FireCharacters(&e);
          break;
        }
        case 2: {
          JSONEndDocumentEventParams e = {0};
          ret_code = ((JSON*)lpObj)->FireEndDocument(&e);
          break;
        }
        case 3: {
          JSONEndElementEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((JSON*)lpObj)->FireEndElement(&e);
          break;
        }
        case 4: {
          JSONErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((JSON*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          JSONIgnorableWhitespaceEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((JSON*)lpObj)->FireIgnorableWhitespace(&e);
          break;
        }
        case 6: {
          JSONJSONEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((JSON*)lpObj)->FireJSON(&e);
          break;
        }
        case 7: {
          JSONStartDocumentEventParams e = {0};
          ret_code = ((JSON*)lpObj)->FireStartDocument(&e);
          break;
        }
        case 8: {
          JSONStartElementEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((JSON*)lpObj)->FireStartElement(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    JSON(char *lpOemKey = (char*)IPWORKS_OEMKEY_68) {
      m_pObj = IPWorks_JSON_Create(JSONEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~JSON() {
      IPWorks_JSON_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_JSON_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_JSON_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_JSON_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_JSON_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_JSON_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetBuildDOM() {
      void* val = IPWorks_JSON_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetBuildDOM(int bBuildDOM) {
      void* val = (void*)IPW64CAST(bBuildDOM);
      return IPWorks_JSON_Set(m_pObj, 1, 0, val, 0);
    }

    inline char* GetInputData() {
      void* val = IPWorks_JSON_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetInputData(const char* lpszInputData) {
      return IPWorks_JSON_Set(m_pObj, 2, 0, (void*)lpszInputData, 0);
    }

    inline char* GetInputFile() {
      void* val = IPWorks_JSON_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetInputFile(const char* lpszInputFile) {
      return IPWorks_JSON_Set(m_pObj, 3, 0, (void*)lpszInputFile, 0);
    }

    inline char* GetOutputData() {
      void* val = IPWorks_JSON_Get(m_pObj, 4, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOutputData(const char* lpszOutputData) {
      return IPWorks_JSON_Set(m_pObj, 4, 0, (void*)lpszOutputData, 0);
    }

    inline char* GetOutputFile() {
      void* val = IPWorks_JSON_Get(m_pObj, 5, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOutputFile(const char* lpszOutputFile) {
      return IPWorks_JSON_Set(m_pObj, 5, 0, (void*)lpszOutputFile, 0);
    }

    inline int GetOverwrite() {
      void* val = IPWorks_JSON_Get(m_pObj, 6, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetOverwrite(int bOverwrite) {
      void* val = (void*)IPW64CAST(bOverwrite);
      return IPWorks_JSON_Set(m_pObj, 6, 0, val, 0);
    }

    inline int GetValidate() {
      void* val = IPWorks_JSON_Get(m_pObj, 7, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetValidate(int bValidate) {
      void* val = (void*)IPW64CAST(bValidate);
      return IPWorks_JSON_Set(m_pObj, 7, 0, val, 0);
    }

    inline int GetXChildCount() {
      void* val = IPWorks_JSON_Get(m_pObj, 8, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetXChildCount(int iXChildCount) {
      void* val = (void*)IPW64CAST(iXChildCount);
      return IPWorks_JSON_Set(m_pObj, 8, 0, val, 0);
    }

    inline char* GetXChildName(int iXChildIndex) {
      void* val = IPWorks_JSON_Get(m_pObj, 9, iXChildIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXChildXText(int iXChildIndex) {
      void* val = IPWorks_JSON_Get(m_pObj, 10, iXChildIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXElement() {
      void* val = IPWorks_JSON_Get(m_pObj, 11, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXElement(const char* lpszXElement) {
      return IPWorks_JSON_Set(m_pObj, 11, 0, (void*)lpszXElement, 0);
    }

    inline int GetXElementType() {
      void* val = IPWorks_JSON_Get(m_pObj, 12, 0, NULL, NULL);
      return (int)(long)val;
    }

    inline char* GetXErrorPath() {
      void* val = IPWorks_JSON_Get(m_pObj, 13, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXErrorPath(const char* lpszXErrorPath) {
      return IPWorks_JSON_Set(m_pObj, 13, 0, (void*)lpszXErrorPath, 0);
    }

    inline char* GetXParent() {
      void* val = IPWorks_JSON_Get(m_pObj, 14, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXPath() {
      void* val = IPWorks_JSON_Get(m_pObj, 15, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXPath(const char* lpszXPath) {
      return IPWorks_JSON_Set(m_pObj, 15, 0, (void*)lpszXPath, 0);
    }

    inline char* GetXSubTree() {
      void* val = IPWorks_JSON_Get(m_pObj, 16, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXText() {
      void* val = IPWorks_JSON_Get(m_pObj, 17, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXText(const char* lpszXText) {
      return IPWorks_JSON_Set(m_pObj, 17, 0, (void*)lpszXText, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int EndArray() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int EndObject() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline int Flush() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 5, 0, param, cbparam, NULL);
    }

    inline int HasXPath(const char* lpszXPath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXPath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 9, 1, param, cbparam, NULL);
      return (int)IPW64CAST(param[1]);
    }

    inline int InsertProperty(const char* lpszName, const char* lpszValue, int iValueType, int iPosition) {
      void *param[4+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszValue), (void*)IPW64CAST(iValueType), (void*)IPW64CAST(iPosition), 0};
      int cbparam[4+1] = {0, 0, 0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 10, 4, param, cbparam, NULL);
    }

    inline int InsertValue(const char* lpszValue, int iValueType, int iPosition) {
      void *param[3+1] = {(void*)IPW64CAST(lpszValue), (void*)IPW64CAST(iValueType), (void*)IPW64CAST(iPosition), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 11, 3, param, cbparam, NULL);
    }

    inline int LoadSchema(const char* lpszSchema) {
      void *param[1+1] = {(void*)IPW64CAST(lpszSchema), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 12, 1, param, cbparam, NULL);
    }

    inline int Parse() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 13, 0, param, cbparam, NULL);
    }

    inline int PutName(const char* lpszName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 14, 1, param, cbparam, NULL);
    }

    inline int PutProperty(const char* lpszName, const char* lpszValue, int iValueType) {
      void *param[3+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszValue), (void*)IPW64CAST(iValueType), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 15, 3, param, cbparam, NULL);
    }

    inline int PutRaw(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 16, 1, param, cbparam, NULL);
    }

    inline int PutValue(const char* lpszValue, int iValueType) {
      void *param[2+1] = {(void*)IPW64CAST(lpszValue), (void*)IPW64CAST(iValueType), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 17, 2, param, cbparam, NULL);
    }

    inline int Remove() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 18, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 19, 0, param, cbparam, NULL);
    }

    inline int Save() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 20, 0, param, cbparam, NULL);
    }

    inline int SetInputStream(IPWorksStream* sInputStream) {
      void *param[1+1] = {(void*)IPW64CAST(sInputStream), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 21, 1, param, cbparam, NULL);
    }

    inline int SetName(const char* lpszName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 22, 1, param, cbparam, NULL);
    }

    inline int SetOutputStream(IPWorksStream* sOutputStream) {
      void *param[1+1] = {(void*)IPW64CAST(sOutputStream), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 23, 1, param, cbparam, NULL);
    }

    inline int SetValue(const char* lpszValue, int iValueType) {
      void *param[2+1] = {(void*)IPW64CAST(lpszValue), (void*)IPW64CAST(iValueType), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 24, 2, param, cbparam, NULL);
    }

    inline int StartArray() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 25, 0, param, cbparam, NULL);
    }

    inline int StartObject() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 26, 0, param, cbparam, NULL);
    }

    inline int TryXPath(const char* lpszxpath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszxpath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 27, 1, param, cbparam, NULL);
      return (int)IPW64CAST(param[1]);
    }

};

#endif //_IPWORKS_JSON_H_
