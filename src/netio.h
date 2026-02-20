/************************************************************************
 *
 *indx#	netio.h - Included by software using corresponding .c file
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
 *doc#	Included by software using corresponding .c file
 ************************************************************************/
#ifndef __NETIO_H__
#define __NETIO_H__

/*
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned long u_long;
typedef void * caddr_t;
*/
#include <sys/types.h>
/*
extern char *strerror( int );
extern const char *sys_errlist[];
*/
extern struct servent *getservbyname();
extern struct hostent *string_to_host( const char *hname );
extern u_short string_to_port( const char *str );
/* extern char *make_hstring( struct sockaddr_in *sinp ); */
extern int setup_net_connect( const char *hstring, const char *pstring );
extern void write_string( int chan, const char *str );
extern void test_netio( int argc, const char *argv[] );
extern void setup_netio();

#endif
