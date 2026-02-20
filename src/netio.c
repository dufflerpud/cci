/************************************************************************
 *indx#	netio.c - Simple front end to standard UNIX network i/o
 *@HDR@	$Id$
 *@HDR@
 *@HDR@	Copyright (c) 2024-2026 Christopher Caldwell (Christopher.M.Caldwell0@gmail.com)
 *@HDR@
 *@HDR@	Permission is hereby granted, free of charge, to any person
 *@HDR@	obtaining a copy of this software and associated documentation
 *@HDR@	files (the "Software"), to deal in the Software without
 *@HDR@	restriction, including without limitation the rights to use,
 *@HDR@	copy, modify, merge, publish, distribute, sublicense, and/or
 *@HDR@	sell copies of the Software, and to permit persons to whom
 *@HDR@	the Software is furnished to do so, subject to the following
 *@HDR@	conditions:
 *@HDR@	
 *@HDR@	The above copyright notice and this permission notice shall be
 *@HDR@	included in all copies or substantial portions of the Software.
 *@HDR@	
 *@HDR@	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 *@HDR@	KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *@HDR@	WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 *@HDR@	AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *@HDR@	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *@HDR@	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *@HDR@	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 *@HDR@	OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *hist#	2026-02-19 - Christopher.M.Caldwell0@gmail.com - Created
 ************************************************************************
 *doc#	netio.c - Simple front end to standard UNIX network i/o
 ************************************************************************/
#define DEBUG
/* #include "idea.h" */

#ifndef SERVICEPORT
#define SERVICEPORT	80
#endif

#ifndef SERVICENAME
#define SERVICENAME	"http"
#endif

#ifndef DEFPROTOCOL
#define DEFPROTOCOL	"http"
#endif

#ifdef _AIX
#define unix		/* Dear god, you have GOT to be kidding */
#endif

#ifndef unix
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned long u_long;
#ifndef __APPLE__
typedef void * caddr_t;
#endif
#endif

#ifdef __APPLE__
#include <arpa/inet.h>
#endif

#ifndef qunix
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#ifdef stellar
#include <netinet/net.h>
#endif
#include <netinet/in.h>
#ifdef linux
#include <arpa/inet.h>
#endif
#include <sys/un.h>
#include <signal.h>
#include <sys/time.h>
#endif
#include <sys/ioctl.h>
#ifndef FIONREAD
#include <sys/filio.h>
#endif

extern struct servent *getservbyname();

#define BUFSIZE	2048

#include <unistd.h>

/************************************************************************/
/*	Convert IP address or hostname to hostent.			*/
/************************************************************************/
struct hostent *string_to_host( const char *hname )
    {
    static struct hostent res;
    static long taddr;

    if( (taddr = inet_addr( hname )) != (unsigned long) -1 )
	{
	static char *block[2];
	res.h_name = (char*)hname;
	res.h_aliases = NULL;
	res.h_addrtype = AF_INET;
	res.h_length = 4;
#ifndef NOT43
	res.h_addr_list = (char**)block;
	block[0] = (char*)&taddr;
	block[1] = NULL;
#else
	res.h_addr = temp;
#endif
	if( (unsigned char)(res.h_addr_list[0][0])!=255
	 || (unsigned char)(res.h_addr_list[0][1])!=255 )
	    return &res;
	}
	
    return gethostbyname(hname);
    }

/************************************************************************/
/*	Convert string to TCP port number				*/
/************************************************************************/
u_short string_to_port( const char *str )
    {
    struct servent *sp;
    u_short hport = 0;
    
    if( (hport = atoi(str)) <= 0 )
	{
        if( ( (sp = getservbyname( str, "tcp" )) != NULL )		||
	    ( (sp = getservbyname( SERVICENAME, "tcp" )) != NULL )	)
	    hport = ntohs(sp->s_port);
	else
	    hport = SERVICEPORT;
	}

    return hport;
    }

/************************************************************************/
/*	Create a printable of socket info in form nnn.nnn.nnn.nnn:nnn.	*/
/*	Used only for debugging.					*/
/************************************************************************/
char *make_hstring( struct sockaddr_in *sinp )
    {
    char buf[2048];
    sprintf( buf, "%s:%d\n", inet_ntoa(sinp->sin_addr), ntohs(sinp->sin_port) );
    return strdup(buf);
    }

/************************************************************************/
/*	Setup connection to daemon with internet address in hstring	*/
/*	and port in pstring.						*/
/************************************************************************/
int setup_net_connect( const char *hstring, const char *pstring )
    {
    struct sockaddr_in sin;
    int net;
    int debug = 1;
    int connected = 0;
    u_short hport = 0;
    struct hostent *host = 0;

    if( (host = string_to_host(hstring)) == NULL )
	return set_error(F,"\"%s\" has unknown host\n", hstring );
    if( (hport = string_to_port(pstring)) <= 0 )
	return set_error(F,"\"%s\" has unknown port\n", pstring );
    sin.sin_family = host->h_addrtype;
    memcpy((caddr_t)&sin.sin_addr,
#ifndef	NOT43
	host->h_addr_list[0],
#else	/* NOT43 */
	host->h_addr,
#endif	/* NOT43 */
	host->h_length);
    sin.sin_port = htons( hport );

    do  {
	net = socket(AF_INET, SOCK_STREAM, 0);
	if (net < 0)
	    return set_error(F,"Socket call failed:  %m\n");
#ifdef notdef
	if( debug &&
#ifndef	NOT43
	    setsockopt(net, SOL_SOCKET, SO_DEBUG, (char *)&debug, sizeof(debug))
#else	/* NOT43 */
	    setsockopt(net, SOL_SOCKET, SO_DEBUG, 0, 0)
#endif	/* NOT43 */
	    < 0 )
	    return set_error(F,"setsockopt (SO_DEBUG) failed:  %m\n");
#endif

	if (connect(net, (struct sockaddr *)&sin, sizeof (sin)) < 0)
	    {
#ifndef	NOT43
	    if (host && host->h_addr_list[1])
		{
#ifdef DEBUG
		fprintf(stderr, "connect to address %s:  %s\n",
		    inet_ntoa(sin.sin_addr),STRERROR(errno));
#endif
		host->h_addr_list++;
		memcpy((caddr_t)&sin.sin_addr,
		    host->h_addr_list[0], host->h_length);
#ifdef DEBUG
		fprintf(stderr, "Trying %s...\n", inet_ntoa(sin.sin_addr));
#endif
		(void) close(net);
		continue;
		}
#endif	/* NOT43 */
	    return set_error(F,"connect %s(%d/tcp) failed:  %m\n",
		hstring,ntohs(sin.sin_port));
	    }
	connected++;
	} while (connected == 0);
    return net;
    }

/************************************************************************/
/*	API Routine for sending a null terminated string to server.	*/
/************************************************************************/
void write_string( int chan, const char *str )
    {
    write( chan, str, strlen(str) );
    }

/************************************************************************/
/*	Test routine which sets up connection to server specified on	*/
/*	the command line.  Command line can be of two forms:		*/
/*		host port						*/
/*		URL							*/
/************************************************************************/
void test_netio( int argc, const char *argv[] )
    {
    char buf[BUFSIZE];
    int n, net;

    if( argc < 2 || argc > 3 )
        {
	fprintf(stderr,"Usage:  %s host port\n",argv[0]);
	exit(0);
	}

    debug(DBG(CHAT),F,"Setting up connection.");

    /* Open then i/o channel to the server */
    if( argc == 3 )
	net = setup_net_connect( argv[1], argv[2] );
    else
	net = open_url( argv[1], NULL );

    /* If this fails, print an error message. */
    if( net <= 0 )
        {
	fprintf(stderr,"%s",error_message);
	exit(1);
	}

    debug(DBG(CHAT),F,"Read loop.");

    /* Loop reading data from server, print it to standard output */
    while( (n = read(net,buf,BUFSIZE)) > 0 )
        write( 1, buf, n );

    /* Close the channel and exit */
    debug(DBG(CHAT),F,"End of file");
    close(net);
    exit(0);
    }

/************************************************************************/
/*	Not much to setup.						*/
/************************************************************************/
void setup_netio()
    {
    module_name_to_ptr("netio")->module_test = test_netio;
    }
