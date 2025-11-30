/************************************************************************
 *@HDR@	$Id$
 *@HDR@		Copyright 2024 by
 *@HDR@		Christopher Caldwell/Brightsands
 *@HDR@		P.O. Box 401, Bailey Island, ME 04003
 *@HDR@		All Rights Reserved
 *@HDR@
 *@HDR@	This software comprises unpublished confidential information
 *@HDR@	of Brightsands and may not be used, copied or made available
 *@HDR@	to anyone, except in accordance with the license under which
 *@HDR@	it is furnished.
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
