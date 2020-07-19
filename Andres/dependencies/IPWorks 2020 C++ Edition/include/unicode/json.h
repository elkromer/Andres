/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
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
extern "C" void* IPWORKS_CALL IPWorks_JSON_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_JSON_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_JSON_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_JSON_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_JSON_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_JSON_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_JSON_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR Text;
  INT reserved;
} JSONCharactersEventParams;

typedef struct {
  INT reserved;
} JSONEndDocumentEventParams;

typedef struct {
  LPCWSTR Element;
  INT reserved;
} JSONEndElementEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} JSONErrorEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} JSONIgnorableWhitespaceEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} JSONJSONEventParams;

typedef struct {
  INT reserved;
} JSONStartDocumentEventParams;

typedef struct {
  LPCWSTR Element;
  INT reserved;
} JSONStartElementEventParams;


class JSON {
  public: // Events
    virtual INT FireCharacters(JSONCharactersEventParams *e) {return 0;}
    virtual INT FireEndDocument(JSONEndDocumentEventParams *e) {return 0;}
    virtual INT FireEndElement(JSONEndElementEventParams *e) {return 0;}
    virtual INT FireError(JSONErrorEventParams *e) {return 0;}
    virtual INT FireIgnorableWhitespace(JSONIgnorableWhitespaceEventParams *e) {return 0;}
    virtual INT FireJSON(JSONJSONEventParams *e) {return 0;}
    virtual INT FireStartDocument(JSONStartDocumentEventParams *e) {return 0;}
    virtual INT FireStartElement(JSONStartElementEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL JSONEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          JSONCharactersEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((JSON*)lpObj)->FireCharacters(&e);
          break;
        }
        case 2: {
          JSONEndDocumentEventParams e = {0};
          ret_code = ((JSON*)lpObj)->FireEndDocument(&e);
          break;
        }
        case 3: {
          JSONEndElementEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((JSON*)lpObj)->FireEndElement(&e);
          break;
        }
        case 4: {
          JSONErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((JSON*)lpObj)->FireError(&e);
          break;
        }
        case 5: {
          JSONIgnorableWhitespaceEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((JSON*)lpObj)->FireIgnorableWhitespace(&e);
          break;
        }
        case 6: {
          JSONJSONEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((JSON*)lpObj)->FireJSON(&e);
          break;
        }
        case 7: {
          JSONStartDocumentEventParams e = {0};
          ret_code = ((JSON*)lpObj)->FireStartDocument(&e);
          break;
        }
        case 8: {
          JSONStartElementEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((JSON*)lpObj)->FireStartElement(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    JSON(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_68) {
      m_pObj = IPWorks_JSON_Create(JSONEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~JSON() {
      IPWorks_JSON_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_JSON_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_JSON_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_JSON_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_JSON_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_JSON_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetBuildDOM() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetBuildDOM(BOOL bBuildDOM) {
      LPVOID val = (LPVOID)(bBuildDOM);
      return IPWorks_JSON_Set(m_pObj, 1, 0, val, 0);
    }

    inline LPWSTR GetInputData() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetInputData(LPCWSTR lpszInputData) {
      return IPWorks_JSON_Set(m_pObj, 2+10000, 0, (LPVOID)lpszInputData, 0);
    }

    inline LPWSTR GetInputFile() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetInputFile(LPCWSTR lpszInputFile) {
      return IPWorks_JSON_Set(m_pObj, 3+10000, 0, (LPVOID)lpszInputFile, 0);
    }

    inline LPWSTR GetOutputData() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 4+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOutputData(LPCWSTR lpszOutputData) {
      return IPWorks_JSON_Set(m_pObj, 4+10000, 0, (LPVOID)lpszOutputData, 0);
    }

    inline LPWSTR GetOutputFile() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 5+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOutputFile(LPCWSTR lpszOutputFile) {
      return IPWorks_JSON_Set(m_pObj, 5+10000, 0, (LPVOID)lpszOutputFile, 0);
    }

    inline BOOL GetOverwrite() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 6, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetOverwrite(BOOL bOverwrite) {
      LPVOID val = (LPVOID)(bOverwrite);
      return IPWorks_JSON_Set(m_pObj, 6, 0, val, 0);
    }

    inline BOOL GetValidate() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 7, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetValidate(BOOL bValidate) {
      LPVOID val = (LPVOID)(bValidate);
      return IPWorks_JSON_Set(m_pObj, 7, 0, val, 0);
    }

    inline INT GetXChildCount() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 8, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetXChildCount(INT iXChildCount) {
      LPVOID val = (LPVOID)(iXChildCount);
      return IPWorks_JSON_Set(m_pObj, 8, 0, val, 0);
    }

    inline LPWSTR GetXChildName(INT iXChildIndex) {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 9+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXChildXText(INT iXChildIndex) {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 10+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXElement() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 11+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXElement(LPCWSTR lpszXElement) {
      return IPWorks_JSON_Set(m_pObj, 11+10000, 0, (LPVOID)lpszXElement, 0);
    }

    inline INT GetXElementType() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 12, 0, NULL, NULL);
      return (INT)(LONG)val;
    }

    inline LPWSTR GetXErrorPath() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 13+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXErrorPath(LPCWSTR lpszXErrorPath) {
      return IPWorks_JSON_Set(m_pObj, 13+10000, 0, (LPVOID)lpszXErrorPath, 0);
    }

    inline LPWSTR GetXParent() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 14+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXPath() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 15+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXPath(LPCWSTR lpszXPath) {
      return IPWorks_JSON_Set(m_pObj, 15+10000, 0, (LPVOID)lpszXPath, 0);
    }

    inline LPWSTR GetXSubTree() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 16+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXText() {
      LPVOID val = IPWorks_JSON_Get(m_pObj, 17+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXText(LPCWSTR lpszXText) {
      return IPWorks_JSON_Set(m_pObj, 17+10000, 0, (LPVOID)lpszXText, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT EndArray() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT EndObject() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline INT Flush() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 5+10000, 0, param, cbparam, NULL);
    }

    inline INT HasXPath(LPCWSTR lpszXPath) {
      LPVOID param[1+1] = {(LPVOID)lpszXPath, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 9+10000, 1, param, cbparam, NULL);
      return (BOOL)param[1];
    }

    inline INT InsertProperty(LPCWSTR lpszName, LPCWSTR lpszValue, INT iValueType, INT iPosition) {
      LPVOID param[4+1] = {(LPVOID)lpszName, (LPVOID)lpszValue, (LPVOID)iValueType, (LPVOID)iPosition, 0};
      INT cbparam[4+1] = {0, 0, 0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 10+10000, 4, param, cbparam, NULL);
    }

    inline INT InsertValue(LPCWSTR lpszValue, INT iValueType, INT iPosition) {
      LPVOID param[3+1] = {(LPVOID)lpszValue, (LPVOID)iValueType, (LPVOID)iPosition, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 11+10000, 3, param, cbparam, NULL);
    }

    inline INT LoadSchema(LPCWSTR lpszSchema) {
      LPVOID param[1+1] = {(LPVOID)lpszSchema, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 12+10000, 1, param, cbparam, NULL);
    }

    inline INT Parse() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 13+10000, 0, param, cbparam, NULL);
    }

    inline INT PutName(LPCWSTR lpszName) {
      LPVOID param[1+1] = {(LPVOID)lpszName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
    }

    inline INT PutProperty(LPCWSTR lpszName, LPCWSTR lpszValue, INT iValueType) {
      LPVOID param[3+1] = {(LPVOID)lpszName, (LPVOID)lpszValue, (LPVOID)iValueType, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 15+10000, 3, param, cbparam, NULL);
    }

    inline INT PutRaw(LPCWSTR lpszText) {
      LPVOID param[1+1] = {(LPVOID)lpszText, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 16+10000, 1, param, cbparam, NULL);
    }

    inline INT PutValue(LPCWSTR lpszValue, INT iValueType) {
      LPVOID param[2+1] = {(LPVOID)lpszValue, (LPVOID)iValueType, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 17+10000, 2, param, cbparam, NULL);
    }

    inline INT Remove() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 18+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 19+10000, 0, param, cbparam, NULL);
    }

    inline INT Save() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 20+10000, 0, param, cbparam, NULL);
    }

    inline INT SetInputStream(IPWorksStream* sInputStream) {
      LPVOID param[1+1] = {(LPVOID)sInputStream, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 21+10000, 1, param, cbparam, NULL);
    }

    inline INT SetName(LPCWSTR lpszName) {
      LPVOID param[1+1] = {(LPVOID)lpszName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 22+10000, 1, param, cbparam, NULL);
    }

    inline INT SetOutputStream(IPWorksStream* sOutputStream) {
      LPVOID param[1+1] = {(LPVOID)sOutputStream, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 23+10000, 1, param, cbparam, NULL);
    }

    inline INT SetValue(LPCWSTR lpszValue, INT iValueType) {
      LPVOID param[2+1] = {(LPVOID)lpszValue, (LPVOID)iValueType, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 24+10000, 2, param, cbparam, NULL);
    }

    inline INT StartArray() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 25+10000, 0, param, cbparam, NULL);
    }

    inline INT StartObject() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 26+10000, 0, param, cbparam, NULL);
    }

    inline INT TryXPath(LPCWSTR lpszxpath) {
      LPVOID param[1+1] = {(LPVOID)lpszxpath, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 27+10000, 1, param, cbparam, NULL);
      return (BOOL)param[1];
    }

};

#endif //_IPWORKS_JSON_H_
