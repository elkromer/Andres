/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_TFTP_H_
#define _IPWORKS_TFTP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_TFTP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_TFTP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_TFTP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_TFTP_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4302) //Only on by default in VS2015
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int Direction;
  int reserved;
} TFTPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} TFTPErrorEventParams;

typedef struct {
  int Direction;
  int reserved;
} TFTPStartTransferEventParams;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  const char* Text;
  int lenText;
  int reserved;
} TFTPTransferEventParams;



class TFTP {
  
  public: //events
  
    virtual int FireEndTransfer(TFTPEndTransferEventParams *e) {return 0;}
    virtual int FireError(TFTPErrorEventParams *e) {return 0;}
    virtual int FireStartTransfer(TFTPStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(TFTPTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL TFTPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((TFTP*)lpObj)->TFTPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            TFTPEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((TFTP*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 2: {
            TFTPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((TFTP*)lpObj)->FireError(&e);
            break;
         }
         case 3: {
            TFTPStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((TFTP*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 4: {
            TFTPTransferEventParams e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((TFTP*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int TFTPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    TFTP(char *lpOemKey = (char*)IPWORKS_OEMKEY_46) {
      m_pObj = IPWorks_TFTP_Create(TFTPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~TFTP() {
      IPWorks_TFTP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_TFTP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_TFTP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_TFTP_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_TFTP_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_TFTP_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetIdle() {
      void* val = IPWorks_TFTP_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_TFTP_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_TFTP_Set(m_pObj, 2, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_TFTP_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_TFTP_Set(m_pObj, 3, 0, (void*)lpLocalHost, 0);
    }

    inline int GetMaxRetransmits() {
      void* val = IPWorks_TFTP_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetMaxRetransmits(int iMaxRetransmits) {
      void* val = (void*)IPW64CAST(iMaxRetransmits);
      return IPWorks_TFTP_Set(m_pObj, 4, 0, val, 0);
    }
    inline char* GetRemoteFile() {
      void* val = IPWorks_TFTP_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteFile(const char *lpRemoteFile) {
      return IPWorks_TFTP_Set(m_pObj, 5, 0, (void*)lpRemoteFile, 0);
    }

    inline int GetRetransmitTimeout() {
      void* val = IPWorks_TFTP_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetRetransmitTimeout(int iRetransmitTimeout) {
      void* val = (void*)IPW64CAST(iRetransmitTimeout);
      return IPWorks_TFTP_Set(m_pObj, 6, 0, val, 0);
    }
    inline int GetTFTPPort() {
      void* val = IPWorks_TFTP_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetTFTPPort(int lTFTPPort) {
      void* val = (void*)IPW64CAST(lTFTPPort);
      return IPWorks_TFTP_Set(m_pObj, 7, 0, val, 0);
    }
    inline char* GetTFTPServer() {
      void* val = IPWorks_TFTP_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetTFTPServer(const char *lpTFTPServer) {
      return IPWorks_TFTP_Set(m_pObj, 8, 0, (void*)lpTFTPServer, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_TFTP_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_TFTP_Set(m_pObj, 9, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_TFTP_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int GetFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int PutFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int Direction;
  int reserved;
} TFTPEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} TFTPErrorEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} TFTPStartTransferEventParamsW;

typedef struct {
  int Direction;
  ns_int64 BytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int lenText;
  int reserved;
} TFTPTransferEventParamsW;



class TFTPW : public TFTP {

  public: //properties
  


    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_TFTP_Get(m_pObj, 10000+10000+2, 0, 0);
    }

    inline int SetLocalFile(LPCWSTR lpLocalFile) {
      return IPWorks_TFTP_Set(m_pObj, 10000+10000+2, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_TFTP_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_TFTP_Set(m_pObj, 10000+3, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetRemoteFile() {
      return (LPWSTR)IPWorks_TFTP_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetRemoteFile(LPCWSTR lpRemoteFile) {
      return IPWorks_TFTP_Set(m_pObj, 10000+5, 0, (void*)lpRemoteFile, 0);
    }





    inline LPWSTR GetTFTPServer() {
      return (LPWSTR)IPWorks_TFTP_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetTFTPServer(LPCWSTR lpTFTPServer) {
      return IPWorks_TFTP_Set(m_pObj, 10000+8, 0, (void*)lpTFTPServer, 0);
    }





  public: //events
  
    virtual int FireEndTransfer(TFTPEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(TFTPErrorEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(TFTPStartTransferEventParamsW *e) {return 0;}
    virtual int FireTransfer(TFTPTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int TFTPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            TFTPEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 2: {
            TFTPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 3: {
            TFTPStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 4: {
            TFTPTransferEventParamsW e = {(int)IPW64CAST(param[0]), *(ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireEndTransfer(TFTPEndTransferEventParams *e) {return -10000;}
    virtual int FireError(TFTPErrorEventParams *e) {return -10000;}
    virtual int FireStartTransfer(TFTPStartTransferEventParams *e) {return -10000;}
    virtual int FireTransfer(TFTPTransferEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_TFTP_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int GetFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int PutFile() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_TFTP_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_TFTP_H_




