/******************************************************************
   IP*Works! 2016 C++ Edition
   Copyright (c) 2019 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_RSHELL_H_
#define _IPWORKS_RSHELL_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3


extern "C" void* IPWORKS_CALL IPWorks_Rshell_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Rshell_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_Rshell_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Rshell_StaticDestroy();

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
} RshellConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} RshellConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} RshellDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} RshellErrorEventParams;

typedef struct {
  const char* Text;
  int EOL;
  int lenText;
  int reserved;
} RshellStderrEventParams;

typedef struct {
  const char* Text;
  int EOL;
  int lenText;
  int reserved;
} RshellStdoutEventParams;



class Rshell {
  
  public: //events
  
    virtual int FireConnected(RshellConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(RshellConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(RshellDisconnectedEventParams *e) {return 0;}
    virtual int FireError(RshellErrorEventParams *e) {return 0;}
    virtual int FireStderr(RshellStderrEventParams *e) {return 0;}
    virtual int FireStdout(RshellStdoutEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL RshellEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((Rshell*)lpObj)->RshellEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            RshellConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Rshell*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            RshellConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((Rshell*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            RshellDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Rshell*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            RshellErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Rshell*)lpObj)->FireError(&e);
            break;
         }
         case 5: {
            RshellStderrEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((Rshell*)lpObj)->FireStderr(&e);
            break;
         }
         case 6: {
            RshellStdoutEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((Rshell*)lpObj)->FireStdout(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int RshellEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    Rshell(char *lpOemKey = (char*)IPWORKS_OEMKEY_21) {
      m_pObj = IPWorks_Rshell_Create(RshellEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~Rshell() {
      IPWorks_Rshell_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_Rshell_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_Rshell_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_Rshell_Get(m_pObj, 0, 0, 0);
    }
    inline char* GetRuntimeLicense() {
      return (char*)IPWorks_Rshell_Get(m_pObj, 2011, 0, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

    inline int SetRuntimeLicense(char* lpRuntimeLicense) {
      return IPWorks_Rshell_Set(m_pObj, 2011, 0, lpRuntimeLicense, 0); // "PID_RUNTIME_LICENSE 2011" is defined in *.cpp file
    }

  public: //properties

    inline int GetBytesSent() {
      void* val = IPWorks_Rshell_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }

    inline char* GetCommand() {
      void* val = IPWorks_Rshell_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetCommand(const char *lpCommand) {
      return IPWorks_Rshell_Set(m_pObj, 2, 0, (void*)lpCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_Rshell_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_Rshell_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetEoF() {
      void* val = IPWorks_Rshell_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }

    inline int GetEOL(char *&lpEOL, int &lenEOL) {
      lpEOL = (char*)IPWorks_Rshell_Get(m_pObj, 5, 0, &lenEOL);
      return lpEOL ? 0 : lenEOL;
    }

    inline int SetEOL(const char *lpEOL, int lenEOL) {
      return IPWorks_Rshell_Set(m_pObj, 5, 0, (void*)lpEOL, lenEOL);
    }

    inline int GetErrEOL(char *&lpErrEOL, int &lenErrEOL) {
      lpErrEOL = (char*)IPWorks_Rshell_Get(m_pObj, 6, 0, &lenErrEOL);
      return lpErrEOL ? 0 : lenErrEOL;
    }

    inline int SetErrEOL(const char *lpErrEOL, int lenErrEOL) {
      return IPWorks_Rshell_Set(m_pObj, 6, 0, (void*)lpErrEOL, lenErrEOL);
    }

    inline char* GetErrorMessage() {
      void* val = IPWorks_Rshell_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }


    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_Rshell_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_Rshell_Set(m_pObj, 8, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_Rshell_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_Rshell_Set(m_pObj, 9, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_Rshell_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_Rshell_Set(m_pObj, 10, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_Rshell_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_Rshell_Set(m_pObj, 11, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_Rshell_Get(m_pObj, 12, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_Rshell_Set(m_pObj, 12, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_Rshell_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_Rshell_Set(m_pObj, 13, 0, (void*)lpFirewallUser, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_Rshell_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_Rshell_Set(m_pObj, 14, 0, (void*)lpLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_Rshell_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }
    inline int SetLocalPort(int lLocalPort) {
      void* val = (void*)IPW64CAST(lLocalPort);
      return IPWorks_Rshell_Set(m_pObj, 15, 0, val, 0);
    }
    inline char* GetLocalUser() {
      void* val = IPWorks_Rshell_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetLocalUser(const char *lpLocalUser) {
      return IPWorks_Rshell_Set(m_pObj, 16, 0, (void*)lpLocalUser, 0);
    }

    inline char* GetRemoteHost() {
      void* val = IPWorks_Rshell_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteHost(const char *lpRemoteHost) {
      return IPWorks_Rshell_Set(m_pObj, 17, 0, (void*)lpRemoteHost, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_Rshell_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }
    inline int SetRemotePort(int lRemotePort) {
      void* val = (void*)IPW64CAST(lRemotePort);
      return IPWorks_Rshell_Set(m_pObj, 18, 0, val, 0);
    }
    inline char* GetRemoteUser() {
      void* val = IPWorks_Rshell_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteUser(const char *lpRemoteUser) {
      return IPWorks_Rshell_Set(m_pObj, 19, 0, (void*)lpRemoteUser, 0);
    }

    inline int GetStderr(char *&lpStderr, int &lenStderr) {
      lpStderr = (char*)IPWorks_Rshell_Get(m_pObj, 20, 0, &lenStderr);
      return lpStderr ? 0 : lenStderr;
    }



    inline int SetStdin(const char *lpStdin, int lenStdin) {
      return IPWorks_Rshell_Set(m_pObj, 21, 0, (void*)lpStdin, lenStdin);
    }

    inline int GetStdout(char *&lpStdout, int &lenStdout) {
      lpStdout = (char*)IPWorks_Rshell_Get(m_pObj, 22, 0, &lenStdout);
      return lpStdout ? 0 : lenStdout;
    }


    inline int GetTimeout() {
      void* val = IPWorks_Rshell_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_Rshell_Set(m_pObj, 23, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Rshell_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Execute(const char* lpszCommand) {
      void *param[1+1] = {(void*)IPW64CAST(lpszCommand), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Rshell_Do(m_pObj, 5, 1, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int Send(const char* lpText, int lenText) {
      void *param[1+1] = {(void*)IPW64CAST(lpText), 0};
      int cbparam[1+1] = {lenText, 0};
      return IPWorks_Rshell_Do(m_pObj, 8, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RshellConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RshellConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RshellDisconnectedEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} RshellErrorEventParamsW;

typedef struct {
  LPWSTR Text;
  int EOL;
  int lenText;
  int reserved;
} RshellStderrEventParamsW;

typedef struct {
  LPWSTR Text;
  int EOL;
  int lenText;
  int reserved;
} RshellStdoutEventParamsW;



class RshellW : public Rshell {

  public: //properties
  


    inline LPWSTR GetCommand() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetCommand(LPCWSTR lpCommand) {
      return IPWorks_Rshell_Set(m_pObj, 10000+2, 0, (void*)lpCommand, 0);
    }





    inline LPWSTR GetEOL() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetEOL(LPCWSTR lpEOL) {
      return IPWorks_Rshell_Set(m_pObj, 10000+5, 0, (void*)lpEOL, 0);
    }
    inline int GetEOLB(char *&lpEOL, int &lenEOL) {
      lpEOL = (char*)IPWorks_Rshell_Get(m_pObj, 5, 0, &lenEOL);
      return lpEOL ? 0 : lenEOL;
    }
    inline int SetEOLB(const char *lpEOL, int lenEOL) {
      return IPWorks_Rshell_Set(m_pObj, 5, 0, (void*)lpEOL, lenEOL);
    }
    inline LPWSTR GetErrEOL() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetErrEOL(LPCWSTR lpErrEOL) {
      return IPWorks_Rshell_Set(m_pObj, 10000+6, 0, (void*)lpErrEOL, 0);
    }
    inline int GetErrEOLB(char *&lpErrEOL, int &lenErrEOL) {
      lpErrEOL = (char*)IPWorks_Rshell_Get(m_pObj, 6, 0, &lenErrEOL);
      return lpErrEOL ? 0 : lenErrEOL;
    }
    inline int SetErrEOLB(const char *lpErrEOL, int lenErrEOL) {
      return IPWorks_Rshell_Set(m_pObj, 6, 0, (void*)lpErrEOL, lenErrEOL);
    }
    inline LPWSTR GetErrorMessage() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+7, 0, 0);
    }







    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+10, 0, 0);
    }

    inline int SetFirewallHost(LPCWSTR lpFirewallHost) {
      return IPWorks_Rshell_Set(m_pObj, 10000+10, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetFirewallPassword(LPCWSTR lpFirewallPassword) {
      return IPWorks_Rshell_Set(m_pObj, 10000+11, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetFirewallUser(LPCWSTR lpFirewallUser) {
      return IPWorks_Rshell_Set(m_pObj, 10000+13, 0, (void*)lpFirewallUser, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetLocalHost(LPCWSTR lpLocalHost) {
      return IPWorks_Rshell_Set(m_pObj, 10000+14, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetLocalUser() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetLocalUser(LPCWSTR lpLocalUser) {
      return IPWorks_Rshell_Set(m_pObj, 10000+16, 0, (void*)lpLocalUser, 0);
    }

    inline LPWSTR GetRemoteHost() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetRemoteHost(LPCWSTR lpRemoteHost) {
      return IPWorks_Rshell_Set(m_pObj, 10000+17, 0, (void*)lpRemoteHost, 0);
    }



    inline LPWSTR GetRemoteUser() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetRemoteUser(LPCWSTR lpRemoteUser) {
      return IPWorks_Rshell_Set(m_pObj, 10000+19, 0, (void*)lpRemoteUser, 0);
    }

    inline LPWSTR GetStderr() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+20, 0, 0);
    }


    inline int GetStderrB(char *&lpStderr, int &lenStderr) {
      lpStderr = (char*)IPWorks_Rshell_Get(m_pObj, 20, 0, &lenStderr);
      return lpStderr ? 0 : lenStderr;
    }



    inline int SetStdin(LPCWSTR lpStdin) {
      return IPWorks_Rshell_Set(m_pObj, 10000+21, 0, (void*)lpStdin, 0);
    }

    inline int SetStdinB(const char *lpStdin, int lenStdin) {
      return IPWorks_Rshell_Set(m_pObj, 21, 0, (void*)lpStdin, lenStdin);
    }
    inline LPWSTR GetStdout() {
      return (LPWSTR)IPWorks_Rshell_Get(m_pObj, 10000+22, 0, 0);
    }


    inline int GetStdoutB(char *&lpStdout, int &lenStdout) {
      lpStdout = (char*)IPWorks_Rshell_Get(m_pObj, 22, 0, &lenStdout);
      return lpStdout ? 0 : lenStdout;
    }





  public: //events
  
    virtual int FireConnected(RshellConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(RshellConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(RshellDisconnectedEventParamsW *e) {return 0;}
    virtual int FireError(RshellErrorEventParamsW *e) {return 0;}
    virtual int FireStderr(RshellStderrEventParamsW *e) {return 0;}
    virtual int FireStdout(RshellStdoutEventParamsW *e) {return 0;}


  protected:
  
    virtual int RshellEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            RshellConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            RshellConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            RshellDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            RshellErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 5: {
            RshellStderrEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireStderr(&e);
            break;
         }
         case 6: {
            RshellStdoutEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireStdout(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(RshellConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(RshellConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(RshellDisconnectedEventParams *e) {return -10000;}
    virtual int FireError(RshellErrorEventParams *e) {return -10000;}
    virtual int FireStderr(RshellStderrEventParams *e) {return -10000;}
    virtual int FireStdout(RshellStdoutEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Rshell_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Execute(LPWSTR lpszCommand) {
      void *param[1+1] = {(void*)lpszCommand, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Rshell_Do(m_pObj, 10000+5, 1, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Rshell_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int Send(LPWSTR lpText, int lenText) {
      void *param[1+1] = {(void*)lpText, 0};
      int cbparam[1+1] = {lenText, 0};
      return IPWorks_Rshell_Do(m_pObj, 10000+8, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_RSHELL_H_




