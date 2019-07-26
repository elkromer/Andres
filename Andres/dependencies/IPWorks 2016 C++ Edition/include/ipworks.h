// IP*Works! 2016 C++ Edition - C++ Interface
//
// Copyright (c) 2019 /n software inc. - All rights reserved.
//

#ifndef _IPWORKS_H_
#define _IPWORKS_H_
  
#ifdef WIN32
#define IPWORKS_CALL __stdcall
#else //UNIX
#define IPWORKS_CALL
#endif

#if defined(_MSC_VER) || defined(__BORLANDC__)
  typedef __int64 ns_int64;
  typedef unsigned __int64 ns_uint64;
#else
  typedef long long int ns_int64;
  typedef unsigned long long int ns_uint64;
#endif


#ifdef UNIX
#if defined(__LP64__) || defined(__x86_64__) || defined(__ia64__) || defined(__amd64__) || defined(__ppc64__)
#ifndef UNIX64
#define UNIX64
#endif
#endif
#endif

#ifndef UNIX64
#define IPW64CAST
#else
#define IPW64CAST (ns_int64)
#endif

typedef int (IPWORKS_CALL *PIPWORKS_CALLBACK)
  (void *lpObj, int event_id, int cparam, void *param[], int cbparam[]);

#ifndef IPWORKS_ONLY_TYPES
#ifdef WIN32

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


#else //UNIX

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
#include "ipport.h"
#include "json.h"
#include "ldap.h"
#include "mcast.h"
#include "mime.h"
#include "mx.h"
#include "netclock.h"
#include "netcode.h"
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


#endif
#endif //IPWORKS_ONLY_TYPES

#endif //_IPWORKS_H_


