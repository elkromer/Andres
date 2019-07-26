/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_XML_H_
#define _IPWORKS_XML_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_XML_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_XML_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_XML_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_XML_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_XML_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_XML_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XML_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_XML_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  const char* Text;
  int reserved;
} XMLCharactersEventParams;

typedef struct {
  const char* Text;
  int reserved;
} XMLCommentEventParams;

typedef struct {
  const char* Namespace;
  const char* Element;
  const char* QName;
  int IsEmpty;
  int reserved;
} XMLEndElementEventParams;

typedef struct {
  const char* Prefix;
  int reserved;
} XMLEndPrefixMappingEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} XMLErrorEventParams;

typedef struct {
  const char* Entity;
  const char* Value;
  int reserved;
} XMLEvalEntityEventParams;

typedef struct {
  const char* Text;
  int reserved;
} XMLIgnorableWhitespaceEventParams;

typedef struct {
  const char* Text;
  int reserved;
} XMLMetaEventParams;

typedef struct {
  const char* Text;
  int reserved;
} XMLPIEventParams;

typedef struct {
  const char* SectionId;
  const char* Text;
  int reserved;
} XMLSpecialSectionEventParams;

typedef struct {
  const char* Namespace;
  const char* Element;
  const char* QName;
  int IsEmpty;
  int reserved;
} XMLStartElementEventParams;

typedef struct {
  const char* Prefix;
  const char* URI;
  int reserved;
} XMLStartPrefixMappingEventParams;

typedef struct {
  const char* Text;
  int reserved;
} XMLXMLEventParams;



class XML {
  
  public: //events
  
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
      if (event_id > 10000) return ((XML*)lpObj)->XMLEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            XMLCharactersEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XML*)lpObj)->FireCharacters(&e);
            break;
         }
         case 2: {
            XMLCommentEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XML*)lpObj)->FireComment(&e);
            break;
         }
         case 3: {
            XMLEndElementEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = ((XML*)lpObj)->FireEndElement(&e);
            break;
         }
         case 4: {
            XMLEndPrefixMappingEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XML*)lpObj)->FireEndPrefixMapping(&e);
            break;
         }
         case 5: {
            XMLErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XML*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            XMLEvalEntityEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XML*)lpObj)->FireEvalEntity(&e);
            param[1] = (void*)IPW64CAST(e.Value);
            break;
         }
         case 7: {
            XMLIgnorableWhitespaceEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XML*)lpObj)->FireIgnorableWhitespace(&e);
            break;
         }
         case 8: {
            XMLMetaEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XML*)lpObj)->FireMeta(&e);
            break;
         }
         case 9: {
            XMLPIEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XML*)lpObj)->FirePI(&e);
            break;
         }
         case 10: {
            XMLSpecialSectionEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XML*)lpObj)->FireSpecialSection(&e);
            break;
         }
         case 11: {
            XMLStartElementEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = ((XML*)lpObj)->FireStartElement(&e);
            break;
         }
         case 12: {
            XMLStartPrefixMappingEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XML*)lpObj)->FireStartPrefixMapping(&e);
            break;
         }
         case 13: {
            XMLXMLEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XML*)lpObj)->FireXML(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int XMLEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    XML(char *lpOemKey = (char*)IPWORKS_OEMKEY_82) {
      m_pObj = IPWorks_XML_Create(XMLEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~XML() {
      IPWorks_XML_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_XML_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_XML_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_XML_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_XML_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_XML_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetBuildDOM() {
      void* val = IPWorks_XML_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetBuildDOM(int bBuildDOM) {
      void* val = (void*)IPW64CAST(bBuildDOM);
      return IPWorks_XML_Set(m_pObj, 1, 0, val, 0);
    }
    inline char* GetInputData() {
      void* val = IPWorks_XML_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetInputData(const char *lpInputData) {
      return IPWorks_XML_Set(m_pObj, 2, 0, (void*)lpInputData, 0);
    }

    inline char* GetInputFile() {
      void* val = IPWorks_XML_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetInputFile(const char *lpInputFile) {
      return IPWorks_XML_Set(m_pObj, 3, 0, (void*)lpInputFile, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_XML_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetNamespaceCount(int iNamespaceCount) {
      void* val = (void*)IPW64CAST(iNamespaceCount);
      return IPWorks_XML_Set(m_pObj, 4, 0, val, 0);
    }
    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 5, iNamespaceIndex, 0);
      return (char*)val;
    }

    inline int SetNamespacePrefix(int iNamespaceIndex, const char *lpNamespacePrefix) {
      return IPWorks_XML_Set(m_pObj, 5, iNamespaceIndex, (void*)lpNamespacePrefix, 0);
    }

    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 6, iNamespaceIndex, 0);
      return (char*)val;
    }

    inline int SetNamespaceURI(int iNamespaceIndex, const char *lpNamespaceURI) {
      return IPWorks_XML_Set(m_pObj, 6, iNamespaceIndex, (void*)lpNamespaceURI, 0);
    }

    inline char* GetOutputData() {
      void* val = IPWorks_XML_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetOutputData(const char *lpOutputData) {
      return IPWorks_XML_Set(m_pObj, 7, 0, (void*)lpOutputData, 0);
    }

    inline char* GetOutputFile() {
      void* val = IPWorks_XML_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetOutputFile(const char *lpOutputFile) {
      return IPWorks_XML_Set(m_pObj, 8, 0, (void*)lpOutputFile, 0);
    }

    inline int GetOverwrite() {
      void* val = IPWorks_XML_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetOverwrite(int bOverwrite) {
      void* val = (void*)IPW64CAST(bOverwrite);
      return IPWorks_XML_Set(m_pObj, 9, 0, val, 0);
    }
    inline int GetValidate() {
      void* val = IPWorks_XML_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }
    inline int SetValidate(int bValidate) {
      void* val = (void*)IPW64CAST(bValidate);
      return IPWorks_XML_Set(m_pObj, 10, 0, val, 0);
    }
    inline int GetAttrCount() {
      void* val = IPWorks_XML_Get(m_pObj, 11, 0, 0);
      return (int)(long)val;
    }
    inline int SetAttrCount(int iAttrCount) {
      void* val = (void*)IPW64CAST(iAttrCount);
      return IPWorks_XML_Set(m_pObj, 11, 0, val, 0);
    }
    inline char* GetAttrName(int iAttrIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 12, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrNamespace(int iAttrIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 13, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrPrefix(int iAttrIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 14, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrValue(int iAttrIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 15, iAttrIndex, 0);
      return (char*)val;
    }


    inline int GetXChildCount() {
      void* val = IPWorks_XML_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetXChildCount(int iXChildCount) {
      void* val = (void*)IPW64CAST(iXChildCount);
      return IPWorks_XML_Set(m_pObj, 16, 0, val, 0);
    }
    inline char* GetXChildName(int iXChildIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 17, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildNamespace(int iXChildIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 18, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildPrefix(int iXChildIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 19, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildXText(int iXChildIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 20, iXChildIndex, 0);
      return (char*)val;
    }


    inline int GetXCommentCount() {
      void* val = IPWorks_XML_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }
    inline int SetXCommentCount(int iXCommentCount) {
      void* val = (void*)IPW64CAST(iXCommentCount);
      return IPWorks_XML_Set(m_pObj, 21, 0, val, 0);
    }
    inline char* GetXCommentText(int iXCommentIndex) {
      void* val = IPWorks_XML_Get(m_pObj, 22, iXCommentIndex, 0);
      return (char*)val;
    }

    inline int SetXCommentText(int iXCommentIndex, const char *lpXCommentText) {
      return IPWorks_XML_Set(m_pObj, 22, iXCommentIndex, (void*)lpXCommentText, 0);
    }

    inline char* GetXElement() {
      void* val = IPWorks_XML_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }

    inline int SetXElement(const char *lpXElement) {
      return IPWorks_XML_Set(m_pObj, 23, 0, (void*)lpXElement, 0);
    }

    inline char* GetXMLDeclarationEncoding() {
      void* val = IPWorks_XML_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetXMLDeclarationEncoding(const char *lpXMLDeclarationEncoding) {
      return IPWorks_XML_Set(m_pObj, 24, 0, (void*)lpXMLDeclarationEncoding, 0);
    }

    inline int GetXMLDeclarationStandalone() {
      void* val = IPWorks_XML_Get(m_pObj, 25, 0, 0);
      return (int)(long)val;
    }
    inline int SetXMLDeclarationStandalone(int bXMLDeclarationStandalone) {
      void* val = (void*)IPW64CAST(bXMLDeclarationStandalone);
      return IPWorks_XML_Set(m_pObj, 25, 0, val, 0);
    }
    inline char* GetXMLDeclarationVersion() {
      void* val = IPWorks_XML_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }

    inline int SetXMLDeclarationVersion(const char *lpXMLDeclarationVersion) {
      return IPWorks_XML_Set(m_pObj, 26, 0, (void*)lpXMLDeclarationVersion, 0);
    }

    inline char* GetXNamespace() {
      void* val = IPWorks_XML_Get(m_pObj, 27, 0, 0);
      return (char*)val;
    }

    inline int SetXNamespace(const char *lpXNamespace) {
      return IPWorks_XML_Set(m_pObj, 27, 0, (void*)lpXNamespace, 0);
    }

    inline char* GetXParent() {
      void* val = IPWorks_XML_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }


    inline char* GetXPath() {
      void* val = IPWorks_XML_Get(m_pObj, 29, 0, 0);
      return (char*)val;
    }

    inline int SetXPath(const char *lpXPath) {
      return IPWorks_XML_Set(m_pObj, 29, 0, (void*)lpXPath, 0);
    }

    inline char* GetXPrefix() {
      void* val = IPWorks_XML_Get(m_pObj, 30, 0, 0);
      return (char*)val;
    }

    inline int SetXPrefix(const char *lpXPrefix) {
      return IPWorks_XML_Set(m_pObj, 30, 0, (void*)lpXPrefix, 0);
    }

    inline char* GetXSubTree() {
      void* val = IPWorks_XML_Get(m_pObj, 31, 0, 0);
      return (char*)val;
    }


    inline char* GetXText() {
      void* val = IPWorks_XML_Get(m_pObj, 32, 0, 0);
      return (char*)val;
    }

    inline int SetXText(const char *lpXText) {
      return IPWorks_XML_Set(m_pObj, 32, 0, (void*)lpXText, 0);
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int EndElement() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Flush() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline char* GetAttr(const char* lpszAttrName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 5, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int HasXPath(const char* lpszXPath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXPath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 6, 1, param, cbparam);
      
      return (int)IPW64CAST(param[1]);
    }
    inline int LoadDOM(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 7, 1, param, cbparam);
      
      
    }
    inline int LoadSchema(const char* lpszSchema) {
      void *param[1+1] = {(void*)IPW64CAST(lpszSchema), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 8, 1, param, cbparam);
      
      
    }
    inline int Parse() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int PutAttr(const char* lpszName, const char* lpszNamespaceURI, const char* lpszValue) {
      void *param[3+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszNamespaceURI), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 10, 3, param, cbparam);
      
      
    }
    inline int PutCData(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 11, 1, param, cbparam);
      
      
    }
    inline int PutComment(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 12, 1, param, cbparam);
      
      
    }
    inline int PutElement(const char* lpszName, const char* lpszNamespaceURI, const char* lpszValue) {
      void *param[3+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszNamespaceURI), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 13, 3, param, cbparam);
      
      
    }
    inline int PutRaw(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 14, 1, param, cbparam);
      
      
    }
    inline int PutString(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 15, 1, param, cbparam);
      
      
    }
    inline int RemoveAttr(const char* lpszAttrName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 16, 1, param, cbparam);
      
      
    }
    inline int RemoveElement() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 17, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 18, 0, param, cbparam);
      
      
    }
    inline int Save() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 19, 0, param, cbparam);
      
      
    }
    inline int SaveDOM(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 20, 1, param, cbparam);
      
      
    }
    inline int StartElement(const char* lpszName, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 23, 2, param, cbparam);
      
      
    }
    inline int TryXPath(const char* lpszxpath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszxpath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 24, 1, param, cbparam);
      
      return (int)IPW64CAST(param[1]);
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR Text;
  int reserved;
} XMLCharactersEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} XMLCommentEventParamsW;

typedef struct {
  LPWSTR Namespace;
  LPWSTR Element;
  LPWSTR QName;
  int IsEmpty;
  int reserved;
} XMLEndElementEventParamsW;

typedef struct {
  LPWSTR Prefix;
  int reserved;
} XMLEndPrefixMappingEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} XMLErrorEventParamsW;

typedef struct {
  LPWSTR Entity;
  LPWSTR Value;
  int reserved;
} XMLEvalEntityEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} XMLIgnorableWhitespaceEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} XMLMetaEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} XMLPIEventParamsW;

typedef struct {
  LPWSTR SectionId;
  LPWSTR Text;
  int reserved;
} XMLSpecialSectionEventParamsW;

typedef struct {
  LPWSTR Namespace;
  LPWSTR Element;
  LPWSTR QName;
  int IsEmpty;
  int reserved;
} XMLStartElementEventParamsW;

typedef struct {
  LPWSTR Prefix;
  LPWSTR URI;
  int reserved;
} XMLStartPrefixMappingEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} XMLXMLEventParamsW;



class XMLW : public XML {

  public: //properties
  


    inline LPWSTR GetInputData() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetInputData(LPCWSTR lpInputData) {
      return IPWorks_XML_Set(m_pObj, 10000+2, 0, (void*)lpInputData, 0);
    }

    inline LPWSTR GetInputFile() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetInputFile(LPCWSTR lpInputFile) {
      return IPWorks_XML_Set(m_pObj, 10000+3, 0, (void*)lpInputFile, 0);
    }



    inline LPWSTR GetNamespacePrefix(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+5, iNamespaceIndex, 0);
    }

    inline int SetNamespacePrefix(int iNamespaceIndex, LPCWSTR lpNamespacePrefix) {
      return IPWorks_XML_Set(m_pObj, 10000+5, iNamespaceIndex, (void*)lpNamespacePrefix, 0);
    }

    inline LPWSTR GetNamespaceURI(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+6, iNamespaceIndex, 0);
    }

    inline int SetNamespaceURI(int iNamespaceIndex, LPCWSTR lpNamespaceURI) {
      return IPWorks_XML_Set(m_pObj, 10000+6, iNamespaceIndex, (void*)lpNamespaceURI, 0);
    }

    inline LPWSTR GetOutputData() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetOutputData(LPCWSTR lpOutputData) {
      return IPWorks_XML_Set(m_pObj, 10000+7, 0, (void*)lpOutputData, 0);
    }

    inline LPWSTR GetOutputFile() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetOutputFile(LPCWSTR lpOutputFile) {
      return IPWorks_XML_Set(m_pObj, 10000+8, 0, (void*)lpOutputFile, 0);
    }







    inline LPWSTR GetAttrName(int iAttrIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+12, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrNamespace(int iAttrIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+13, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrPrefix(int iAttrIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+14, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrValue(int iAttrIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+15, iAttrIndex, 0);
    }





    inline LPWSTR GetXChildName(int iXChildIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+17, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildNamespace(int iXChildIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+18, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildPrefix(int iXChildIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+19, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildXText(int iXChildIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+20, iXChildIndex, 0);
    }





    inline LPWSTR GetXCommentText(int iXCommentIndex) {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+22, iXCommentIndex, 0);
    }

    inline int SetXCommentText(int iXCommentIndex, LPCWSTR lpXCommentText) {
      return IPWorks_XML_Set(m_pObj, 10000+22, iXCommentIndex, (void*)lpXCommentText, 0);
    }

    inline LPWSTR GetXElement() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+23, 0, 0);
    }

    inline int SetXElement(LPCWSTR lpXElement) {
      return IPWorks_XML_Set(m_pObj, 10000+23, 0, (void*)lpXElement, 0);
    }

    inline LPWSTR GetXMLDeclarationEncoding() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetXMLDeclarationEncoding(LPCWSTR lpXMLDeclarationEncoding) {
      return IPWorks_XML_Set(m_pObj, 10000+24, 0, (void*)lpXMLDeclarationEncoding, 0);
    }



    inline LPWSTR GetXMLDeclarationVersion() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+26, 0, 0);
    }

    inline int SetXMLDeclarationVersion(LPCWSTR lpXMLDeclarationVersion) {
      return IPWorks_XML_Set(m_pObj, 10000+26, 0, (void*)lpXMLDeclarationVersion, 0);
    }

    inline LPWSTR GetXNamespace() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+27, 0, 0);
    }

    inline int SetXNamespace(LPCWSTR lpXNamespace) {
      return IPWorks_XML_Set(m_pObj, 10000+27, 0, (void*)lpXNamespace, 0);
    }

    inline LPWSTR GetXParent() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+28, 0, 0);
    }



    inline LPWSTR GetXPath() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+29, 0, 0);
    }

    inline int SetXPath(LPCWSTR lpXPath) {
      return IPWorks_XML_Set(m_pObj, 10000+29, 0, (void*)lpXPath, 0);
    }

    inline LPWSTR GetXPrefix() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+30, 0, 0);
    }

    inline int SetXPrefix(LPCWSTR lpXPrefix) {
      return IPWorks_XML_Set(m_pObj, 10000+30, 0, (void*)lpXPrefix, 0);
    }

    inline LPWSTR GetXSubTree() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+31, 0, 0);
    }



    inline LPWSTR GetXText() {
      return (LPWSTR)IPWorks_XML_Get(m_pObj, 10000+32, 0, 0);
    }

    inline int SetXText(LPCWSTR lpXText) {
      return IPWorks_XML_Set(m_pObj, 10000+32, 0, (void*)lpXText, 0);
    }



  public: //events
  
    virtual int FireCharacters(XMLCharactersEventParamsW *e) {return 0;}
    virtual int FireComment(XMLCommentEventParamsW *e) {return 0;}
    virtual int FireEndElement(XMLEndElementEventParamsW *e) {return 0;}
    virtual int FireEndPrefixMapping(XMLEndPrefixMappingEventParamsW *e) {return 0;}
    virtual int FireError(XMLErrorEventParamsW *e) {return 0;}
    virtual int FireEvalEntity(XMLEvalEntityEventParamsW *e) {return 0;}
    virtual int FireIgnorableWhitespace(XMLIgnorableWhitespaceEventParamsW *e) {return 0;}
    virtual int FireMeta(XMLMetaEventParamsW *e) {return 0;}
    virtual int FirePI(XMLPIEventParamsW *e) {return 0;}
    virtual int FireSpecialSection(XMLSpecialSectionEventParamsW *e) {return 0;}
    virtual int FireStartElement(XMLStartElementEventParamsW *e) {return 0;}
    virtual int FireStartPrefixMapping(XMLStartPrefixMappingEventParamsW *e) {return 0;}
    virtual int FireXML(XMLXMLEventParamsW *e) {return 0;}


  protected:
  
    virtual int XMLEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            XMLCharactersEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireCharacters(&e);
            break;
         }
         case 2: {
            XMLCommentEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireComment(&e);
            break;
         }
         case 3: {
            XMLEndElementEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = FireEndElement(&e);
            break;
         }
         case 4: {
            XMLEndPrefixMappingEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireEndPrefixMapping(&e);
            break;
         }
         case 5: {
            XMLErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            XMLEvalEntityEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireEvalEntity(&e);
            param[1] = (void*)(e.Value);
            break;
         }
         case 7: {
            XMLIgnorableWhitespaceEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireIgnorableWhitespace(&e);
            break;
         }
         case 8: {
            XMLMetaEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireMeta(&e);
            break;
         }
         case 9: {
            XMLPIEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FirePI(&e);
            break;
         }
         case 10: {
            XMLSpecialSectionEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireSpecialSection(&e);
            break;
         }
         case 11: {
            XMLStartElementEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = FireStartElement(&e);
            break;
         }
         case 12: {
            XMLStartPrefixMappingEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireStartPrefixMapping(&e);
            break;
         }
         case 13: {
            XMLXMLEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireXML(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireCharacters(XMLCharactersEventParams *e) {return -10000;}
    virtual int FireComment(XMLCommentEventParams *e) {return -10000;}
    virtual int FireEndElement(XMLEndElementEventParams *e) {return -10000;}
    virtual int FireEndPrefixMapping(XMLEndPrefixMappingEventParams *e) {return -10000;}
    virtual int FireError(XMLErrorEventParams *e) {return -10000;}
    virtual int FireEvalEntity(XMLEvalEntityEventParams *e) {return -10000;}
    virtual int FireIgnorableWhitespace(XMLIgnorableWhitespaceEventParams *e) {return -10000;}
    virtual int FireMeta(XMLMetaEventParams *e) {return -10000;}
    virtual int FirePI(XMLPIEventParams *e) {return -10000;}
    virtual int FireSpecialSection(XMLSpecialSectionEventParams *e) {return -10000;}
    virtual int FireStartElement(XMLStartElementEventParams *e) {return -10000;}
    virtual int FireStartPrefixMapping(XMLStartPrefixMappingEventParams *e) {return -10000;}
    virtual int FireXML(XMLXMLEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int EndElement() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Flush() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline LPWSTR GetAttr(LPWSTR lpszAttrName) {
      void *param[1+1] = {(void*)lpszAttrName, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 10000+5, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int HasXPath(LPWSTR lpszXPath) {
      void *param[1+1] = {(void*)lpszXPath, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 10000+6, 1, param, cbparam);
      return (int)IPW64CAST(param[1]);
    }
    inline int LoadDOM(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+7, 1, param, cbparam);
      
    }
    inline int LoadSchema(LPWSTR lpszSchema) {
      void *param[1+1] = {(void*)lpszSchema, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+8, 1, param, cbparam);
      
    }
    inline int Parse() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int PutAttr(LPWSTR lpszName, LPWSTR lpszNamespaceURI, LPWSTR lpszValue) {
      void *param[3+1] = {(void*)lpszName, (void*)lpszNamespaceURI, (void*)lpszValue, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+10, 3, param, cbparam);
      
    }
    inline int PutCData(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+11, 1, param, cbparam);
      
    }
    inline int PutComment(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+12, 1, param, cbparam);
      
    }
    inline int PutElement(LPWSTR lpszName, LPWSTR lpszNamespaceURI, LPWSTR lpszValue) {
      void *param[3+1] = {(void*)lpszName, (void*)lpszNamespaceURI, (void*)lpszValue, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+13, 3, param, cbparam);
      
    }
    inline int PutRaw(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+14, 1, param, cbparam);
      
    }
    inline int PutString(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+15, 1, param, cbparam);
      
    }
    inline int RemoveAttr(LPWSTR lpszAttrName) {
      void *param[1+1] = {(void*)lpszAttrName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+16, 1, param, cbparam);
      
    }
    inline int RemoveElement() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 10000+17, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 10000+18, 0, param, cbparam);
      
    }
    inline int Save() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XML_Do(m_pObj, 10000+19, 0, param, cbparam);
      
    }
    inline int SaveDOM(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+20, 1, param, cbparam);
      
    }
    inline int StartElement(LPWSTR lpszName, LPWSTR lpszNamespaceURI) {
      void *param[2+1] = {(void*)lpszName, (void*)lpszNamespaceURI, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XML_Do(m_pObj, 10000+23, 2, param, cbparam);
      
    }
    inline int TryXPath(LPWSTR lpszxpath) {
      void *param[1+1] = {(void*)lpszxpath, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XML_Do(m_pObj, 10000+24, 1, param, cbparam);
      return (int)IPW64CAST(param[1]);
    }

};

#endif //WIN32

#endif //_IPWORKS_XML_H_




