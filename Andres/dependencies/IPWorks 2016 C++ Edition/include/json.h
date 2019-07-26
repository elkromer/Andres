/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

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


extern "C" void* IPWORKS_CALL IPWorks_JSON_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_JSON_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_JSON_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_JSON_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_JSON_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_JSON_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_JSON_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_JSON_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  const char* Text;
  int reserved;
} JSONCharactersEventParams;

typedef struct {
  const char* Element;
  int reserved;
} JSONEndElementEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} JSONErrorEventParams;

typedef struct {
  const char* Text;
  int reserved;
} JSONIgnorableWhitespaceEventParams;

typedef struct {
  const char* Text;
  int reserved;
} JSONJSONEventParams;

typedef struct {
  const char* Element;
  int reserved;
} JSONStartElementEventParams;



class JSON {
  
  public: //events
  
    virtual int FireCharacters(JSONCharactersEventParams *e) {return 0;}
    virtual int FireEndElement(JSONEndElementEventParams *e) {return 0;}
    virtual int FireError(JSONErrorEventParams *e) {return 0;}
    virtual int FireIgnorableWhitespace(JSONIgnorableWhitespaceEventParams *e) {return 0;}
    virtual int FireJSON(JSONJSONEventParams *e) {return 0;}
    virtual int FireStartElement(JSONStartElementEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL JSONEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((JSON*)lpObj)->JSONEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            JSONCharactersEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((JSON*)lpObj)->FireCharacters(&e);
            break;
         }
         case 2: {
            JSONEndElementEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((JSON*)lpObj)->FireEndElement(&e);
            break;
         }
         case 3: {
            JSONErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((JSON*)lpObj)->FireError(&e);
            break;
         }
         case 4: {
            JSONIgnorableWhitespaceEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((JSON*)lpObj)->FireIgnorableWhitespace(&e);
            break;
         }
         case 5: {
            JSONJSONEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((JSON*)lpObj)->FireJSON(&e);
            break;
         }
         case 6: {
            JSONStartElementEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((JSON*)lpObj)->FireStartElement(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int JSONEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    JSON(char *lpOemKey = (char*)IPWORKS_OEMKEY_68) {
      m_pObj = IPWorks_JSON_Create(JSONEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~JSON() {
      IPWorks_JSON_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_JSON_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_JSON_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_JSON_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_JSON_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_JSON_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetBuildDOM() {
      void* val = IPWorks_JSON_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetBuildDOM(int bBuildDOM) {
      void* val = (void*)IPW64CAST(bBuildDOM);
      return IPWorks_JSON_Set(m_pObj, 1, 0, val, 0);
    }
    inline char* GetInputData() {
      void* val = IPWorks_JSON_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetInputData(const char *lpInputData) {
      return IPWorks_JSON_Set(m_pObj, 2, 0, (void*)lpInputData, 0);
    }

    inline char* GetInputFile() {
      void* val = IPWorks_JSON_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetInputFile(const char *lpInputFile) {
      return IPWorks_JSON_Set(m_pObj, 3, 0, (void*)lpInputFile, 0);
    }

    inline char* GetOutputData() {
      void* val = IPWorks_JSON_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetOutputData(const char *lpOutputData) {
      return IPWorks_JSON_Set(m_pObj, 4, 0, (void*)lpOutputData, 0);
    }

    inline char* GetOutputFile() {
      void* val = IPWorks_JSON_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetOutputFile(const char *lpOutputFile) {
      return IPWorks_JSON_Set(m_pObj, 5, 0, (void*)lpOutputFile, 0);
    }

    inline int GetOverwrite() {
      void* val = IPWorks_JSON_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetOverwrite(int bOverwrite) {
      void* val = (void*)IPW64CAST(bOverwrite);
      return IPWorks_JSON_Set(m_pObj, 6, 0, val, 0);
    }
    inline int GetValidate() {
      void* val = IPWorks_JSON_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetValidate(int bValidate) {
      void* val = (void*)IPW64CAST(bValidate);
      return IPWorks_JSON_Set(m_pObj, 7, 0, val, 0);
    }
    inline int GetXChildCount() {
      void* val = IPWorks_JSON_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetXChildCount(int iXChildCount) {
      void* val = (void*)IPW64CAST(iXChildCount);
      return IPWorks_JSON_Set(m_pObj, 8, 0, val, 0);
    }
    inline char* GetXChildName(int iXChildIndex) {
      void* val = IPWorks_JSON_Get(m_pObj, 9, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildXText(int iXChildIndex) {
      void* val = IPWorks_JSON_Get(m_pObj, 10, iXChildIndex, 0);
      return (char*)val;
    }


    inline int GetXCommentCount() {
      void* val = IPWorks_JSON_Get(m_pObj, 11, 0, 0);
      return (int)(long)val;
    }
    inline int SetXCommentCount(int iXCommentCount) {
      void* val = (void*)IPW64CAST(iXCommentCount);
      return IPWorks_JSON_Set(m_pObj, 11, 0, val, 0);
    }
    inline char* GetXCommentText(int iXCommentIndex) {
      void* val = IPWorks_JSON_Get(m_pObj, 12, iXCommentIndex, 0);
      return (char*)val;
    }

    inline int SetXCommentText(int iXCommentIndex, const char *lpXCommentText) {
      return IPWorks_JSON_Set(m_pObj, 12, iXCommentIndex, (void*)lpXCommentText, 0);
    }

    inline char* GetXElement() {
      void* val = IPWorks_JSON_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetXElement(const char *lpXElement) {
      return IPWorks_JSON_Set(m_pObj, 13, 0, (void*)lpXElement, 0);
    }

    inline int GetXElementType() {
      void* val = IPWorks_JSON_Get(m_pObj, 14, 0, 0);
      return (int)(long)val;
    }

    inline char* GetXErrorPath() {
      void* val = IPWorks_JSON_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetXErrorPath(const char *lpXErrorPath) {
      return IPWorks_JSON_Set(m_pObj, 15, 0, (void*)lpXErrorPath, 0);
    }

    inline char* GetXParent() {
      void* val = IPWorks_JSON_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }


    inline char* GetXPath() {
      void* val = IPWorks_JSON_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetXPath(const char *lpXPath) {
      return IPWorks_JSON_Set(m_pObj, 17, 0, (void*)lpXPath, 0);
    }

    inline char* GetXSubTree() {
      void* val = IPWorks_JSON_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }


    inline char* GetXText() {
      void* val = IPWorks_JSON_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetXText(const char *lpXText) {
      return IPWorks_JSON_Set(m_pObj, 19, 0, (void*)lpXText, 0);
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int EndArray() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int EndObject() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Flush() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int HasXPath(const char* lpszXPath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXPath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 9, 1, param, cbparam);
      
      return (int)IPW64CAST(param[1]);
    }
    inline int LoadSchema(const char* lpszSchema) {
      void *param[1+1] = {(void*)IPW64CAST(lpszSchema), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 10, 1, param, cbparam);
      
      
    }
    inline int Parse() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }
    inline int PutComment(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 12, 1, param, cbparam);
      
      
    }
    inline int PutName(const char* lpszName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 13, 1, param, cbparam);
      
      
    }
    inline int PutProperty(const char* lpszName, const char* lpszValue, int iValueType) {
      void *param[3+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszValue), (void*)IPW64CAST(iValueType), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 14, 3, param, cbparam);
      
      
    }
    inline int PutRaw(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 15, 1, param, cbparam);
      
      
    }
    inline int PutValue(const char* lpszValue, int iValueType) {
      void *param[2+1] = {(void*)IPW64CAST(lpszValue), (void*)IPW64CAST(iValueType), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 16, 2, param, cbparam);
      
      
    }
    inline int Remove() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 17, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 18, 0, param, cbparam);
      
      
    }
    inline int Save() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 19, 0, param, cbparam);
      
      
    }
    inline int StartArray() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 22, 0, param, cbparam);
      
      
    }
    inline int StartObject() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 23, 0, param, cbparam);
      
      
    }
    inline int TryXPath(const char* lpszxpath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszxpath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 24, 1, param, cbparam);
      
      return (int)IPW64CAST(param[1]);
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR Text;
  int reserved;
} JSONCharactersEventParamsW;

typedef struct {
  LPWSTR Element;
  int reserved;
} JSONEndElementEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} JSONErrorEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} JSONIgnorableWhitespaceEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} JSONJSONEventParamsW;

typedef struct {
  LPWSTR Element;
  int reserved;
} JSONStartElementEventParamsW;



class JSONW : public JSON {

  public: //properties
  


    inline LPWSTR GetInputData() {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetInputData(LPCWSTR lpInputData) {
      return IPWorks_JSON_Set(m_pObj, 10000+2, 0, (void*)lpInputData, 0);
    }

    inline LPWSTR GetInputFile() {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetInputFile(LPCWSTR lpInputFile) {
      return IPWorks_JSON_Set(m_pObj, 10000+3, 0, (void*)lpInputFile, 0);
    }

    inline LPWSTR GetOutputData() {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetOutputData(LPCWSTR lpOutputData) {
      return IPWorks_JSON_Set(m_pObj, 10000+4, 0, (void*)lpOutputData, 0);
    }

    inline LPWSTR GetOutputFile() {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetOutputFile(LPCWSTR lpOutputFile) {
      return IPWorks_JSON_Set(m_pObj, 10000+5, 0, (void*)lpOutputFile, 0);
    }







    inline LPWSTR GetXChildName(int iXChildIndex) {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+9, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildXText(int iXChildIndex) {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+10, iXChildIndex, 0);
    }





    inline LPWSTR GetXCommentText(int iXCommentIndex) {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+12, iXCommentIndex, 0);
    }

    inline int SetXCommentText(int iXCommentIndex, LPCWSTR lpXCommentText) {
      return IPWorks_JSON_Set(m_pObj, 10000+12, iXCommentIndex, (void*)lpXCommentText, 0);
    }

    inline LPWSTR GetXElement() {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetXElement(LPCWSTR lpXElement) {
      return IPWorks_JSON_Set(m_pObj, 10000+13, 0, (void*)lpXElement, 0);
    }



    inline LPWSTR GetXErrorPath() {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetXErrorPath(LPCWSTR lpXErrorPath) {
      return IPWorks_JSON_Set(m_pObj, 10000+15, 0, (void*)lpXErrorPath, 0);
    }

    inline LPWSTR GetXParent() {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+16, 0, 0);
    }



    inline LPWSTR GetXPath() {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetXPath(LPCWSTR lpXPath) {
      return IPWorks_JSON_Set(m_pObj, 10000+17, 0, (void*)lpXPath, 0);
    }

    inline LPWSTR GetXSubTree() {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+18, 0, 0);
    }



    inline LPWSTR GetXText() {
      return (LPWSTR)IPWorks_JSON_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetXText(LPCWSTR lpXText) {
      return IPWorks_JSON_Set(m_pObj, 10000+19, 0, (void*)lpXText, 0);
    }



  public: //events
  
    virtual int FireCharacters(JSONCharactersEventParamsW *e) {return 0;}
    virtual int FireEndElement(JSONEndElementEventParamsW *e) {return 0;}
    virtual int FireError(JSONErrorEventParamsW *e) {return 0;}
    virtual int FireIgnorableWhitespace(JSONIgnorableWhitespaceEventParamsW *e) {return 0;}
    virtual int FireJSON(JSONJSONEventParamsW *e) {return 0;}
    virtual int FireStartElement(JSONStartElementEventParamsW *e) {return 0;}


  protected:
  
    virtual int JSONEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            JSONCharactersEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireCharacters(&e);
            break;
         }
         case 2: {
            JSONEndElementEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireEndElement(&e);
            break;
         }
         case 3: {
            JSONErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 4: {
            JSONIgnorableWhitespaceEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireIgnorableWhitespace(&e);
            break;
         }
         case 5: {
            JSONJSONEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireJSON(&e);
            break;
         }
         case 6: {
            JSONStartElementEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireStartElement(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireCharacters(JSONCharactersEventParams *e) {return -10000;}
    virtual int FireEndElement(JSONEndElementEventParams *e) {return -10000;}
    virtual int FireError(JSONErrorEventParams *e) {return -10000;}
    virtual int FireIgnorableWhitespace(JSONIgnorableWhitespaceEventParams *e) {return -10000;}
    virtual int FireJSON(JSONJSONEventParams *e) {return -10000;}
    virtual int FireStartElement(JSONStartElementEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int EndArray() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int EndObject() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Flush() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int HasXPath(LPWSTR lpszXPath) {
      void *param[1+1] = {(void*)lpszXPath, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 10000+9, 1, param, cbparam);
      return (int)IPW64CAST(param[1]);
    }
    inline int LoadSchema(LPWSTR lpszSchema) {
      void *param[1+1] = {(void*)lpszSchema, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 10000+10, 1, param, cbparam);
      
    }
    inline int Parse() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }
    inline int PutComment(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 10000+12, 1, param, cbparam);
      
    }
    inline int PutName(LPWSTR lpszName) {
      void *param[1+1] = {(void*)lpszName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 10000+13, 1, param, cbparam);
      
    }
    inline int PutProperty(LPWSTR lpszName, LPWSTR lpszValue, int iValueType) {
      void *param[3+1] = {(void*)lpszName, (void*)lpszValue, (void*)iValueType, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 10000+14, 3, param, cbparam);
      
    }
    inline int PutRaw(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_JSON_Do(m_pObj, 10000+15, 1, param, cbparam);
      
    }
    inline int PutValue(LPWSTR lpszValue, int iValueType) {
      void *param[2+1] = {(void*)lpszValue, (void*)iValueType, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_JSON_Do(m_pObj, 10000+16, 2, param, cbparam);
      
    }
    inline int Remove() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 10000+17, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 10000+18, 0, param, cbparam);
      
    }
    inline int Save() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 10000+19, 0, param, cbparam);
      
    }
    inline int StartArray() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 10000+22, 0, param, cbparam);
      
    }
    inline int StartObject() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_JSON_Do(m_pObj, 10000+23, 0, param, cbparam);
      
    }
    inline int TryXPath(LPWSTR lpszxpath) {
      void *param[1+1] = {(void*)lpszxpath, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_JSON_Do(m_pObj, 10000+24, 1, param, cbparam);
      return (int)IPW64CAST(param[1]);
    }

};

#endif //WIN32

#endif //_IPWORKS_JSON_H_




