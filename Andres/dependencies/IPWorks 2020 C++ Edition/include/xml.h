/******************************************************************************
  IPWorks 2020 C++ Edition
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
extern "C" void* IPWORKS_CALL IPWorks_XML_Get(void *lpObj, int propid, int arridx, int *lpcbVal, int64 *lpllVal);
extern "C" int   IPWORKS_CALL IPWorks_XML_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_XML_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[], int64 *lpllVal);
extern "C" char* IPWORKS_CALL IPWorks_XML_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_SetLastErrorAndCode(void *lpObj, int code, char *message);
extern "C" char* IPWORKS_CALL IPWorks_XML_GetEventError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_GetEventErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_SetEventErrorAndCode(void *lpObj, int code, char *message);
extern "C" int   IPWORKS_CALL IPWorks_XML_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_XML_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif

typedef struct {
  const char *Text;
  int reserved;
} XMLCharactersEventParams;

typedef struct {
  const char *Text;
  int reserved;
} XMLCommentEventParams;

typedef struct {
  const char *Namespace;
  const char *Element;
  const char *QName;
  int IsEmpty;
  int reserved;
} XMLEndElementEventParams;

typedef struct {
  const char *Prefix;
  int reserved;
} XMLEndPrefixMappingEventParams;

typedef struct {
  int ErrorCode;
  const char *Description;
  int reserved;
} XMLErrorEventParams;

typedef struct {
  const char *Entity;
  char *Value;
  int reserved;
} XMLEvalEntityEventParams;

typedef struct {
  const char *Text;
  int reserved;
} XMLIgnorableWhitespaceEventParams;

typedef struct {
  const char *Text;
  int reserved;
} XMLMetaEventParams;

typedef struct {
  const char *Text;
  int reserved;
} XMLPIEventParams;

typedef struct {
  const char *SectionId;
  const char *Text;
  int reserved;
} XMLSpecialSectionEventParams;

typedef struct {
  const char *Namespace;
  const char *Element;
  const char *QName;
  int IsEmpty;
  int reserved;
} XMLStartElementEventParams;

typedef struct {
  const char *Prefix;
  const char *URI;
  int reserved;
} XMLStartPrefixMappingEventParams;

typedef struct {
  const char *Text;
  int reserved;
} XMLXMLEventParams;


class XML {
  public: // Events
    virtual int FireCharacters(XMLCharactersEventParams *e) {return 0;}
    virtual int FireComment(XMLCommentEventParams *e) {return 0;}
    virtual int FireEndElement(XMLEndElementEventParams *e) {return 0;}
    virtual int FireEndPrefixMapping(XMLEndPrefixMappingEventParams *e) {return 0;}
    virtual int FireError(XMLErrorEventParams *e) {return 0;}
    virtual int FireEvalEntity(XMLEvalEntityEventParams *e) {return 0;}
    virtual int FireIgnorableWhitespace(XMLIgnorableWhitespaceEventParams *e) {return 0;}
    virtual int FireMeta(XMLMetaEventParams *e) {return 0;}
    virtual int FirePI(XMLPIEventParams *e) {return 0;}
    virtual int FireSpecialSection(XMLSpecialSectionEventParams *e) {return 0;}
    virtual int FireStartElement(XMLStartElementEventParams *e) {return 0;}
    virtual int FireStartPrefixMapping(XMLStartPrefixMappingEventParams *e) {return 0;}
    virtual int FireXML(XMLXMLEventParams *e) {return 0;}

  protected:
    void *m_pObj;
    static int IPWORKS_CALL XMLEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      switch (event_id) {
        case 1: {
          XMLCharactersEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((XML*)lpObj)->FireCharacters(&e);
          break;
        }
        case 2: {
          XMLCommentEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((XML*)lpObj)->FireComment(&e);
          break;
        }
        case 3: {
          XMLEndElementEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), 0};
          ret_code = ((XML*)lpObj)->FireEndElement(&e);
          break;
        }
        case 4: {
          XMLEndPrefixMappingEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((XML*)lpObj)->FireEndPrefixMapping(&e);
          break;
        }
        case 5: {
          XMLErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((XML*)lpObj)->FireError(&e);
          break;
        }
        case 6: {
          XMLEvalEntityEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPWorks_EvtStr(param[1], 0, NULL, 1), 0};
          ret_code = ((XML*)lpObj)->FireEvalEntity(&e);
          IPWorks_EvtStr(param[1], 1, (void*)e.Value, 1);
          break;
        }
        case 7: {
          XMLIgnorableWhitespaceEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((XML*)lpObj)->FireIgnorableWhitespace(&e);
          break;
        }
        case 8: {
          XMLMetaEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((XML*)lpObj)->FireMeta(&e);
          break;
        }
        case 9: {
          XMLPIEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((XML*)lpObj)->FirePI(&e);
          break;
        }
        case 10: {
          XMLSpecialSectionEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((XML*)lpObj)->FireSpecialSection(&e);
          break;
        }
        case 11: {
          XMLStartElementEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]), 0};
          ret_code = ((XML*)lpObj)->FireStartElement(&e);
          break;
        }
        case 12: {
          XMLStartPrefixMappingEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), 0};
          ret_code = ((XML*)lpObj)->FireStartPrefixMapping(&e);
          break;
        }
        case 13: {
          XMLXMLEventParams e = {(char*)IPW64CAST(param[0]), 0};
          ret_code = ((XML*)lpObj)->FireXML(&e);
          break;
        }
      }
      return ret_code;
    }

  public:
    XML(char *lpOemKey = (char*)IPWORKS_OEMKEY_82) {
      m_pObj = IPWorks_XML_Create(XMLEventSink, (void*)this, (char*)lpOemKey, 0);
#ifdef WIN32
      Config("CodePage=65001"); // Use the UTF-8 code page for ANSI strings by default on Windows.
#endif
    }

    virtual ~XML() {
      IPWorks_XML_Destroy(m_pObj);
    }

    inline char *GetLastError() {
      return IPWorks_XML_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_XML_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_XML_Get(m_pObj, 0, 0, NULL, NULL);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_XML_Get(m_pObj, 2011, 0, NULL, NULL);
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_XML_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0);
    }
  public: // Properties
    inline int GetBuildDOM() {
      void* val = IPWorks_XML_Get(m_pObj, 1, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetBuildDOM(int bBuildDOM) {
      void* val = (void*)IPW64CAST(bBuildDOM);
      return IPWorks_XML_Set(m_pObj, 1, 0, val, 0);
    }

    inline char* GetInputData() {
      void* val = IPWorks_XML_Get(m_pObj, 2, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetInputData(const char* lpszInputData) {
      return IPWorks_XML_Set(m_pObj, 2, 0, (void*)lpszInputData, 0);
    }

    inline char* GetInputFile() {
      void* val = IPWorks_XML_Get(m_pObj, 3, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetInputFile(const char* lpszInputFile) {
      return IPWorks_XML_Set(m_pObj, 3, 0, (void*)lpszInputFile, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_XML_Get(m_pObj, 4, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetNamespaceCount(int iNamespaceCount) {
      void* val = (void*)IPW64CAST(iNamespaceCount);
      return IPWorks_XML_Set(m_pObj, 4, 0, val, 0);
    }

    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 5, iNamespaceIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetNamespacePrefix(int iNamespaceIndex, const char* lpszNamespacePrefix) {
      return IPWorks_XML_Set(m_pObj, 5, iNamespaceIndex, (void*)lpszNamespacePrefix, 0);
    }

    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 6, iNamespaceIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetNamespaceURI(int iNamespaceIndex, const char* lpszNamespaceURI) {
      return IPWorks_XML_Set(m_pObj, 6, iNamespaceIndex, (void*)lpszNamespaceURI, 0);
    }

    inline char* GetOutputData() {
      void* val = IPWorks_XML_Get(m_pObj, 7, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOutputData(const char* lpszOutputData) {
      return IPWorks_XML_Set(m_pObj, 7, 0, (void*)lpszOutputData, 0);
    }

    inline char* GetOutputFile() {
      void* val = IPWorks_XML_Get(m_pObj, 8, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetOutputFile(const char* lpszOutputFile) {
      return IPWorks_XML_Set(m_pObj, 8, 0, (void*)lpszOutputFile, 0);
    }

    inline int GetOverwrite() {
      void* val = IPWorks_XML_Get(m_pObj, 9, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetOverwrite(int bOverwrite) {
      void* val = (void*)IPW64CAST(bOverwrite);
      return IPWorks_XML_Set(m_pObj, 9, 0, val, 0);
    }

    inline int GetValidate() {
      void* val = IPWorks_XML_Get(m_pObj, 10, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetValidate(int bValidate) {
      void* val = (void*)IPW64CAST(bValidate);
      return IPWorks_XML_Set(m_pObj, 10, 0, val, 0);
    }

    inline int GetAttrCount() {
      void* val = IPWorks_XML_Get(m_pObj, 11, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetAttrCount(int iAttrCount) {
      void* val = (void*)IPW64CAST(iAttrCount);
      return IPWorks_XML_Set(m_pObj, 11, 0, val, 0);
    }

    inline char* GetAttrName(int iAttrIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 12, iAttrIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetAttrNamespace(int iAttrIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 13, iAttrIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetAttrPrefix(int iAttrIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 14, iAttrIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetAttrValue(int iAttrIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 15, iAttrIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetXChildCount() {
      void* val = IPWorks_XML_Get(m_pObj, 16, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetXChildCount(int iXChildCount) {
      void* val = (void*)IPW64CAST(iXChildCount);
      return IPWorks_XML_Set(m_pObj, 16, 0, val, 0);
    }

    inline char* GetXChildName(int iXChildIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 17, iXChildIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXChildNamespace(int iXChildIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 18, iXChildIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXChildPrefix(int iXChildIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 19, iXChildIndex, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXChildXText(int iXChildIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 20, iXChildIndex, NULL, NULL);
      return (char*)val;
    }

    inline int GetXCommentCount() {
      void* val = IPWorks_XML_Get(m_pObj, 21, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetXCommentCount(int iXCommentCount) {
      void* val = (void*)IPW64CAST(iXCommentCount);
      return IPWorks_XML_Set(m_pObj, 21, 0, val, 0);
    }

    inline char* GetXCommentText(int iXCommentIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 22, iXCommentIndex, NULL, NULL);
      return (char*)val;
    }
    inline int SetXCommentText(int iXCommentIndex, const char* lpszXCommentText) {
      return IPWorks_XML_Set(m_pObj, 22, iXCommentIndex, (void*)lpszXCommentText, 0);
    }

    inline char* GetXElement() {
      void* val = IPWorks_XML_Get(m_pObj, 23, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXElement(const char* lpszXElement) {
      return IPWorks_XML_Set(m_pObj, 23, 0, (void*)lpszXElement, 0);
    }

    inline char* GetXMLDeclarationEncoding() {
      void* val = IPWorks_XML_Get(m_pObj, 24, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXMLDeclarationEncoding(const char* lpszXMLDeclarationEncoding) {
      return IPWorks_XML_Set(m_pObj, 24, 0, (void*)lpszXMLDeclarationEncoding, 0);
    }

    inline int GetXMLDeclarationStandalone() {
      void* val = IPWorks_XML_Get(m_pObj, 25, 0, NULL, NULL);
      return (int)(long)val;
    }
    inline int SetXMLDeclarationStandalone(int bXMLDeclarationStandalone) {
      void* val = (void*)IPW64CAST(bXMLDeclarationStandalone);
      return IPWorks_XML_Set(m_pObj, 25, 0, val, 0);
    }

    inline char* GetXMLDeclarationVersion() {
      void* val = IPWorks_XML_Get(m_pObj, 26, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXMLDeclarationVersion(const char* lpszXMLDeclarationVersion) {
      return IPWorks_XML_Set(m_pObj, 26, 0, (void*)lpszXMLDeclarationVersion, 0);
    }

    inline char* GetXNamespace() {
      void* val = IPWorks_XML_Get(m_pObj, 27, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXNamespace(const char* lpszXNamespace) {
      return IPWorks_XML_Set(m_pObj, 27, 0, (void*)lpszXNamespace, 0);
    }

    inline char* GetXParent() {
      void* val = IPWorks_XML_Get(m_pObj, 28, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXPath() {
      void* val = IPWorks_XML_Get(m_pObj, 29, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXPath(const char* lpszXPath) {
      return IPWorks_XML_Set(m_pObj, 29, 0, (void*)lpszXPath, 0);
    }

    inline char* GetXPrefix() {
      void* val = IPWorks_XML_Get(m_pObj, 30, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXPrefix(const char* lpszXPrefix) {
      return IPWorks_XML_Set(m_pObj, 30, 0, (void*)lpszXPrefix, 0);
    }

    inline char* GetXSubTree() {
      void* val = IPWorks_XML_Get(m_pObj, 31, 0, NULL, NULL);
      return (char*)val;
    }

    inline char* GetXText() {
      void* val = IPWorks_XML_Get(m_pObj, 32, 0, NULL, NULL);
      return (char*)val;
    }
    inline int SetXText(const char* lpszXText) {
      return IPWorks_XML_Set(m_pObj, 32, 0, (void*)lpszXText, 0);
    }

  public: // Methods
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 2, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int EndElement() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 3, 0, param, cbparam, NULL);
    }

    inline int Flush() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 4, 0, param, cbparam, NULL);
    }

    inline char* GetAttr(const char* lpszAttrName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 5, 1, param, cbparam, NULL);
      return (char*)IPW64CAST(param[1]);
    }

    inline int HasXPath(const char* lpszXPath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXPath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 6, 1, param, cbparam, NULL);
      return (int)IPW64CAST(param[1]);
    }

    inline int LoadDOM(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 7, 1, param, cbparam, NULL);
    }

    inline int LoadSchema(const char* lpszSchema) {
      void *param[1+1] = {(void*)IPW64CAST(lpszSchema), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 8, 1, param, cbparam, NULL);
    }

    inline int Parse() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 9, 0, param, cbparam, NULL);
    }

    inline int PutAttr(const char* lpszName, const char* lpszNamespaceURI, const char* lpszValue) {
      void *param[3+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszNamespaceURI), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 10, 3, param, cbparam, NULL);
    }

    inline int PutCData(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 11, 1, param, cbparam, NULL);
    }

    inline int PutComment(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 12, 1, param, cbparam, NULL);
    }

    inline int PutElement(const char* lpszName, const char* lpszNamespaceURI, const char* lpszValue) {
      void *param[3+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszNamespaceURI), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 13, 3, param, cbparam, NULL);
    }

    inline int PutRaw(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 14, 1, param, cbparam, NULL);
    }

    inline int PutString(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 15, 1, param, cbparam, NULL);
    }

    inline int RemoveAttr(const char* lpszAttrName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 16, 1, param, cbparam, NULL);
    }

    inline int RemoveChildren() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 17, 0, param, cbparam, NULL);
    }

    inline int RemoveElement() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 18, 0, param, cbparam, NULL);
    }

    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 19, 0, param, cbparam, NULL);
    }

    inline int Save() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 20, 0, param, cbparam, NULL);
    }

    inline int SaveDOM(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 21, 1, param, cbparam, NULL);
    }

    inline int SetInputStream(IPWorksStream* sInputStream) {
      void *param[1+1] = {(void*)IPW64CAST(sInputStream), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 22, 1, param, cbparam, NULL);
    }

    inline int SetOutputStream(IPWorksStream* sOutputStream) {
      void *param[1+1] = {(void*)IPW64CAST(sOutputStream), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 23, 1, param, cbparam, NULL);
    }

    inline int StartElement(const char* lpszName, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 24, 2, param, cbparam, NULL);
    }

    inline int TryXPath(const char* lpszxpath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszxpath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 25, 1, param, cbparam, NULL);
      return (int)IPW64CAST(param[1]);
    }

};

#endif //_IPWORKS_XML_H_
