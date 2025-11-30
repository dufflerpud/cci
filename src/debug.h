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
#ifndef __DEBUG_H__
#define __DEBUG_H__

#define F				__FILE__,__LINE__
#define DEBUG_STANDARD_FLAGS		CALLS,STATUS

static inline int DBG( int x )		{ return (1 << x); }

extern void debug_register( int flag, const char *name );
extern void debug(int flags,const char *fname,int line,const char *fmt,...);
extern void deb_call(int flags,const char *fname,int line,const char *fmt,...);
extern void deb_return(int flags,const char *fname,int line,const char *fmt,...);
extern void deb_status(int flags,const char *fname,int line,const char *fmt,...);
extern int debug_arg(const char **argvptr);
extern int debug_flags;

#define MAX_DEBUG_FLAGS			( sizeof(int) * 8 )
extern const char *all_debug_flags[ MAX_DEBUG_FLAGS ];

extern const char *error_message;
extern int set_error(const char *filename, int line, const char *fmt, ... );

#endif
