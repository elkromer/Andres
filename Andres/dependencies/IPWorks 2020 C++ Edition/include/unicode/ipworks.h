/******************************************************************************
  IPWorks 2020 C++ Edition (Windows Unicode)
  Copyright (c) 2019 /n software inc. - All rights reserved.
******************************************************************************/

#ifndef _IPWORKS_H_
#define _IPWORKS_H_

#define IPWORKS_CALL __stdcall

typedef int (IPWORKS_CALL *PIPWORKS_CALLBACK)
  (void *lpObj, int event_id, int cparam, void *param[], int cbparam[]);

extern "C" void* IPWORKS_CALL IPWorks_EvtStr(void *lpEvtStr, int id, void *val, int opt);
extern "C" int   IPWORKS_CALL IPWorks_Stream(void *lpStream, int op, void *param[], void *retVal);




#ifndef _IPWORKS_STREAM_
#define _IPWORKS_STREAM_

class IPWorksStream {
public:
  virtual ~IPWorksStream() { Close(); };
  virtual int Read(void* buffer, int count) = 0;
  virtual int Write(const void* buffer, int count) = 0;
  virtual void Close() { }
  virtual __int64 GetLength() = 0;
  // Possible seekOrigin values: 0 = Beginning, 1 = Current, 2 = End.
  virtual __int64 Seek(__int64 offset, int seekOrigin) = 0;

  virtual int Flush() { return 0; }
  virtual bool CanRead() { return true; }
  virtual bool CanWrite() { return true; }
  virtual bool CanSeek() { return true; }
};

#endif //_IPWORKS_STREAM_

#ifndef IPWORKS_ONLY_TYPES

#include "atom.h"
#include "caldav.h"
#include "certmgr.h"
#include "dns.h"
#include "filemailer.h"
#include "ftp.h"
#include "htmlmailer.h"
#include "http.h"
#include "icmpport.h"
#include "imap.h"
#include "ipdaemon.h"
#include "ipinfo.h"
#include "ipmonitor.h"
#include "ipport.h"
#include "json.h"
#include "ldap.h"
#include "mcast.h"
#include "mime.h"
#include "mx.h"
#include "netclock.h"
#include "netcode.h"
#include "netdial.h"
#include "nntp.h"
#include "oauth.h"
#include "odata.h"
#include "ping.h"
#include "pop.h"
#include "rcp.h"
#include "rest.h"
#include "rexec.h"
#include "rshell.h"
#include "rss.h"
#include "smpp.h"
#include "smtp.h"
#include "snpp.h"
#include "soap.h"
#include "syslog.h"
#include "telnet.h"
#include "tftp.h"
#include "traceroute.h"
#include "udpport.h"
#include "webdav.h"
#include "webform.h"
#include "websocket.h"
#include "webupload.h"
#include "whois.h"
#include "xml.h"
#include "xmpp.h"

#endif //IPWORKS_ONLY_TYPES

#endif //_IPWORKS_H_
