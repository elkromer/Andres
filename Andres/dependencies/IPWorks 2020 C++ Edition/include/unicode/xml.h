/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_XML_H_
#define _IPWORKS_XML_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_XML_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey, int opts);
extern "C" int   IPWORKS_CALL IPWorks_XML_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_XML_Get(void *lpObj, int propid, int arridx, int *lpcbVal, __int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_XML_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_XML_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], __int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_XML_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_XML_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_XML_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_XML_StaticDestroy();

#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)

typedef struct {
  LPCWSTR Text;
  INT reserved;
} XMLCharactersEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} XMLCommentEventParams;

typedef struct {
  LPCWSTR Namespace;
  LPCWSTR Element;
  LPCWSTR QName;
  BOOL IsEmpty;
  INT reserved;
} XMLEndElementEventParams;

typedef struct {
  LPCWSTR Prefix;
  INT reserved;
} XMLEndPrefixMappingEventParams;

typedef struct {
  INT ErrorCode;
  LPCWSTR Description;
  INT reserved;
} XMLErrorEventParams;

typedef struct {
  LPCWSTR Entity;
  LPWSTR Value;
  INT reserved;
} XMLEvalEntityEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} XMLIgnorableWhitespaceEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} XMLMetaEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} XMLPIEventParams;

typedef struct {
  LPCWSTR SectionId;
  LPCWSTR Text;
  INT reserved;
} XMLSpecialSectionEventParams;

typedef struct {
  LPCWSTR Namespace;
  LPCWSTR Element;
  LPCWSTR QName;
  BOOL IsEmpty;
  INT reserved;
} XMLStartElementEventParams;

typedef struct {
  LPCWSTR Prefix;
  LPCWSTR URI;
  INT reserved;
} XMLStartPrefixMappingEventParams;

typedef struct {
  LPCWSTR Text;
  INT reserved;
} XMLXMLEventParams;


class XML {
  public: // Events
    virtual INT FireCharacters(XMLCharactersEventParams *e) {return 0;}
    virtual INT FireComment(XMLCommentEventParams *e) {return 0;}
    virtual INT FireEndElement(XMLEndElementEventParams *e) {return 0;}
    virtual INT FireEndPrefixMapping(XMLEndPrefixMappingEventParams *e) {return 0;}
    virtual INT FireError(XMLErrorEventParams *e) {return 0;}
    virtual INT FireEvalEntity(XMLEvalEntityEventParams *e) {return 0;}
    virtual INT FireIgnorableWhitespace(XMLIgnorableWhitespaceEventParams *e) {return 0;}
    virtual INT FireMeta(XMLMetaEventParams *e) {return 0;}
    virtual INT FirePI(XMLPIEventParams *e) {return 0;}
    virtual INT FireSpecialSection(XMLSpecialSectionEventParams *e) {return 0;}
    virtual INT FireStartElement(XMLStartElementEventParams *e) {return 0;}
    virtual INT FireStartPrefixMapping(XMLStartPrefixMappingEventParams *e) {return 0;}
    virtual INT FireXML(XMLXMLEventParams *e) {return 0;}

  protected:
    LPVOID m_pObj;
    static int IPWORKS_CALL XMLEventSink(LPVOID lpObj, INT event_id, INT cparam, LPVOID param[], INT cbparam[]) {
      INT ret_code = 0;
      switch (event_id) {
        case 1: {
          XMLCharactersEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((XML*)lpObj)->FireCharacters(&e);
          break;
        }
        case 2: {
          XMLCommentEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((XML*)lpObj)->FireComment(&e);
          break;
        }
        case 3: {
          XMLEndElementEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (BOOL)param[3], 0};
          ret_code = ((XML*)lpObj)->FireEndElement(&e);
          break;
        }
        case 4: {
          XMLEndPrefixMappingEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((XML*)lpObj)->FireEndPrefixMapping(&e);
          break;
        }
        case 5: {
          XMLErrorEventParams e = {(INT)param[0], (LPWSTR)param[1], 0};
          ret_code = ((XML*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          XMLEvalEntityEventParams e = {(LPWSTR)param[0], (LPWSTR)IPWorks_EvtStr(param[1], 0, NULL, 2), 0};
          ret_code = ((XML*)lpObj)->FireEvalEntity(&e);
          IPWorks_EvtStr(param[1], 1, (void*)e.Value, 2);
          break;
        }
        case 7: {
          XMLIgnorableWhitespaceEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((XML*)lpObj)->FireIgnorableWhitespace(&e);
          break;
        }
        case 8: {
          XMLMetaEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((XML*)lpObj)->FireMeta(&e);
          break;
        }
        case 9: {
          XMLPIEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((XML*)lpObj)->FirePI(&e);
          break;
        }
        case 10: {
          XMLSpecialSectionEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((XML*)lpObj)->FireSpecialSection(&e);
          break;
        }
        case 11: {
          XMLStartElementEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], (LPWSTR)param[2], (BOOL)param[3], 0};
          ret_code = ((XML*)lpObj)->FireStartElement(&e);
          break;
        }
        case 12: {
          XMLStartPrefixMappingEventParams e = {(LPWSTR)param[0], (LPWSTR)param[1], 0};
          ret_code = ((XML*)lpObj)->FireStartPrefixMapping(&e);
          break;
        }
        case 13: {
          XMLXMLEventParams e = {(LPWSTR)param[0], 0};
          ret_code = ((XML*)lpObj)->FireXML(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    XML(LPSTR lpOemKey = (LPSTR)IPWORKS_OEMKEY_82) {
      m_pObj = IPWorks_XML_Create(XMLEventSink, (LPVOID)this, (LPSTR)lpOemKey, 1);
      Config(L"CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
    }

    virtual ~XML() {
      IPWorks_XML_Destroy(m_pObj);
    }

    inline LPSTR GetLastError() {
      return IPWorks_XML_GetLastError(m_pObj);
    }
    
    inline INT GetLastErrorCode() {
      return IPWorks_XML_GetLastErrorCode(m_pObj);
    }

    inline LPSTR VERSION() {
      return (LPSTR)IPWorks_XML_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline LPSTR GetRuntimeLicense() {
      return (LPSTR)IPWorks_XML_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(LPSTR lpRuntimeLicense) {
      return IPWorks_XML_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline BOOL GetBuildDOM() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 1, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetBuildDOM(BOOL bBuildDOM) {
      LPVOID val = (LPVOID)(bBuildDOM);
      return IPWorks_XML_Set(m_pObj, 1, 0, val, 0);
    }

    inline LPWSTR GetInputData() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 2+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetInputData(LPCWSTR lpszInputData) {
      return IPWorks_XML_Set(m_pObj, 2+10000, 0, (LPVOID)lpszInputData, 0);
    }

    inline LPWSTR GetInputFile() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 3+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetInputFile(LPCWSTR lpszInputFile) {
      return IPWorks_XML_Set(m_pObj, 3+10000, 0, (LPVOID)lpszInputFile, 0);
    }

    inline INT GetNamespaceCount() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 4, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetNamespaceCount(INT iNamespaceCount) {
      LPVOID val = (LPVOID)(iNamespaceCount);
      return IPWorks_XML_Set(m_pObj, 4, 0, val, 0);
    }

    inline LPWSTR GetNamespacePrefix(INT iNamespaceIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 5+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNamespacePrefix(INT iNamespaceIndex, LPCWSTR lpszNamespacePrefix) {
      return IPWorks_XML_Set(m_pObj, 5+10000, iNamespaceIndex, (LPVOID)lpszNamespacePrefix, 0);
    }

    inline LPWSTR GetNamespaceURI(INT iNamespaceIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 6+10000, iNamespaceIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetNamespaceURI(INT iNamespaceIndex, LPCWSTR lpszNamespaceURI) {
      return IPWorks_XML_Set(m_pObj, 6+10000, iNamespaceIndex, (LPVOID)lpszNamespaceURI, 0);
    }

    inline LPWSTR GetOutputData() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 7+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOutputData(LPCWSTR lpszOutputData) {
      return IPWorks_XML_Set(m_pObj, 7+10000, 0, (LPVOID)lpszOutputData, 0);
    }

    inline LPWSTR GetOutputFile() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 8+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetOutputFile(LPCWSTR lpszOutputFile) {
      return IPWorks_XML_Set(m_pObj, 8+10000, 0, (LPVOID)lpszOutputFile, 0);
    }

    inline BOOL GetOverwrite() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 9, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetOverwrite(BOOL bOverwrite) {
      LPVOID val = (LPVOID)(bOverwrite);
      return IPWorks_XML_Set(m_pObj, 9, 0, val, 0);
    }

    inline BOOL GetValidate() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 10, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetValidate(BOOL bValidate) {
      LPVOID val = (LPVOID)(bValidate);
      return IPWorks_XML_Set(m_pObj, 10, 0, val, 0);
    }

    inline INT GetAttrCount() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 11, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetAttrCount(INT iAttrCount) {
      LPVOID val = (LPVOID)(iAttrCount);
      return IPWorks_XML_Set(m_pObj, 11, 0, val, 0);
    }

    inline LPWSTR GetAttrName(INT iAttrIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 12+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAttrNamespace(INT iAttrIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 13+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAttrPrefix(INT iAttrIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 14+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetAttrValue(INT iAttrIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 15+10000, iAttrIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetXChildCount() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 16, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetXChildCount(INT iXChildCount) {
      LPVOID val = (LPVOID)(iXChildCount);
      return IPWorks_XML_Set(m_pObj, 16, 0, val, 0);
    }

    inline LPWSTR GetXChildName(INT iXChildIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 17+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXChildNamespace(INT iXChildIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 18+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXChildPrefix(INT iXChildIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 19+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXChildXText(INT iXChildIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 20+10000, iXChildIndex, NULL, NULL);
      return (LPWSTR)val;
    }

    inline INT GetXCommentCount() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 21, 0, NULL, NULL);
      return (INT)(LONG)val;
    }
    inline INT SetXCommentCount(INT iXCommentCount) {
      LPVOID val = (LPVOID)(iXCommentCount);
      return IPWorks_XML_Set(m_pObj, 21, 0, val, 0);
    }

    inline LPWSTR GetXCommentText(INT iXCommentIndex) {
      LPVOID val = IPWorks_XML_Get(m_pObj, 22+10000, iXCommentIndex, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXCommentText(INT iXCommentIndex, LPCWSTR lpszXCommentText) {
      return IPWorks_XML_Set(m_pObj, 22+10000, iXCommentIndex, (LPVOID)lpszXCommentText, 0);
    }

    inline LPWSTR GetXElement() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 23+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXElement(LPCWSTR lpszXElement) {
      return IPWorks_XML_Set(m_pObj, 23+10000, 0, (LPVOID)lpszXElement, 0);
    }

    inline LPWSTR GetXMLDeclarationEncoding() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 24+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXMLDeclarationEncoding(LPCWSTR lpszXMLDeclarationEncoding) {
      return IPWorks_XML_Set(m_pObj, 24+10000, 0, (LPVOID)lpszXMLDeclarationEncoding, 0);
    }

    inline BOOL GetXMLDeclarationStandalone() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 25, 0, NULL, NULL);
      return (BOOL)(LONG)val;
    }
    inline INT SetXMLDeclarationStandalone(BOOL bXMLDeclarationStandalone) {
      LPVOID val = (LPVOID)(bXMLDeclarationStandalone);
      return IPWorks_XML_Set(m_pObj, 25, 0, val, 0);
    }

    inline LPWSTR GetXMLDeclarationVersion() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 26+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXMLDeclarationVersion(LPCWSTR lpszXMLDeclarationVersion) {
      return IPWorks_XML_Set(m_pObj, 26+10000, 0, (LPVOID)lpszXMLDeclarationVersion, 0);
    }

    inline LPWSTR GetXNamespace() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 27+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXNamespace(LPCWSTR lpszXNamespace) {
      return IPWorks_XML_Set(m_pObj, 27+10000, 0, (LPVOID)lpszXNamespace, 0);
    }

    inline LPWSTR GetXParent() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 28+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXPath() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 29+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXPath(LPCWSTR lpszXPath) {
      return IPWorks_XML_Set(m_pObj, 29+10000, 0, (LPVOID)lpszXPath, 0);
    }

    inline LPWSTR GetXPrefix() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 30+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXPrefix(LPCWSTR lpszXPrefix) {
      return IPWorks_XML_Set(m_pObj, 30+10000, 0, (LPVOID)lpszXPrefix, 0);
    }

    inline LPWSTR GetXSubTree() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 31+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }

    inline LPWSTR GetXText() {
      LPVOID val = IPWorks_XML_Get(m_pObj, 32+10000, 0, NULL, NULL);
      return (LPWSTR)val;
    }
    inline INT SetXText(LPCWSTR lpszXText) {
      return IPWorks_XML_Set(m_pObj, 32+10000, 0, (LPVOID)lpszXText, 0);
    }

  public: // Methods
    inline LPWSTR Config(LPCWSTR lpszConfigurationString) {
      LPVOID param[1+1] = {(LPVOID)lpszConfigurationString, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 2+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT EndElement() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 3+10000, 0, param, cbparam, NULL);
    }

    inline INT Flush() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 4+10000, 0, param, cbparam, NULL);
    }

    inline LPWSTR GetAttr(LPCWSTR lpszAttrName) {
      LPVOID param[1+1] = {(LPVOID)lpszAttrName, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 5+10000, 1, param, cbparam, NULL);
      return (LPWSTR)param[1];
    }

    inline INT HasXPath(LPCWSTR lpszXPath) {
      LPVOID param[1+1] = {(LPVOID)lpszXPath, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 6+10000, 1, param, cbparam, NULL);
      return (BOOL)param[1];
    }

    inline INT LoadDOM(LPCWSTR lpszFileName) {
      LPVOID param[1+1] = {(LPVOID)lpszFileName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 7+10000, 1, param, cbparam, NULL);
    }

    inline INT LoadSchema(LPCWSTR lpszSchema) {
      LPVOID param[1+1] = {(LPVOID)lpszSchema, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 8+10000, 1, param, cbparam, NULL);
    }

    inline INT Parse() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 9+10000, 0, param, cbparam, NULL);
    }

    inline INT PutAttr(LPCWSTR lpszName, LPCWSTR lpszNamespaceURI, LPCWSTR lpszValue) {
      LPVOID param[3+1] = {(LPVOID)lpszName, (LPVOID)lpszNamespaceURI, (LPVOID)lpszValue, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 10+10000, 3, param, cbparam, NULL);
    }

    inline INT PutCData(LPCWSTR lpszText) {
      LPVOID param[1+1] = {(LPVOID)lpszText, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 11+10000, 1, param, cbparam, NULL);
    }

    inline INT PutComment(LPCWSTR lpszText) {
      LPVOID param[1+1] = {(LPVOID)lpszText, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 12+10000, 1, param, cbparam, NULL);
    }

    inline INT PutElement(LPCWSTR lpszName, LPCWSTR lpszNamespaceURI, LPCWSTR lpszValue) {
      LPVOID param[3+1] = {(LPVOID)lpszName, (LPVOID)lpszNamespaceURI, (LPVOID)lpszValue, 0};
      INT cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 13+10000, 3, param, cbparam, NULL);
    }

    inline INT PutRaw(LPCWSTR lpszText) {
      LPVOID param[1+1] = {(LPVOID)lpszText, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 14+10000, 1, param, cbparam, NULL);
    }

    inline INT PutString(LPCWSTR lpszText) {
      LPVOID param[1+1] = {(LPVOID)lpszText, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 15+10000, 1, param, cbparam, NULL);
    }

    inline INT RemoveAttr(LPCWSTR lpszAttrName) {
      LPVOID param[1+1] = {(LPVOID)lpszAttrName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 16+10000, 1, param, cbparam, NULL);
    }

    inline INT RemoveChildren() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 17+10000, 0, param, cbparam, NULL);
    }

    inline INT RemoveElement() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 18+10000, 0, param, cbparam, NULL);
    }

    inline INT Reset() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 19+10000, 0, param, cbparam, NULL);
    }

    inline INT Save() {
      LPVOID param[0+1] = {0};
      INT cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 20+10000, 0, param, cbparam, NULL);
    }

    inline INT SaveDOM(LPCWSTR lpszFileName) {
      LPVOID param[1+1] = {(LPVOID)lpszFileName, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 21+10000, 1, param, cbparam, NULL);
    }

    inline INT SetInputStream(IPWorksStream* sInputStream) {
      LPVOID param[1+1] = {(LPVOID)sInputStream, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 22+10000, 1, param, cbparam, NULL);
    }

    inline INT SetOutputStream(IPWorksStream* sOutputStream) {
      LPVOID param[1+1] = {(LPVOID)sOutputStream, 0};
      INT cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 23+10000, 1, param, cbparam, NULL);
    }

    inline INT StartElement(LPCWSTR lpszName, LPCWSTR lpszNamespaceURI) {
      LPVOID param[2+1] = {(LPVOID)lpszName, (LPVOID)lpszNamespaceURI, 0};
      INT cbparam[2+1] = {0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 24+10000, 2, param, cbparam, NULL);
    }

    inline INT TryXPath(LPCWSTR lpszxpath) {
      LPVOID param[1+1] = {(LPVOID)lpszxpath, 0};
      INT cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 25+10000, 1, param, cbparam, NULL);
      return (BOOL)param[1];
    }

};

#endif //_IPWORKS_XML_H_
