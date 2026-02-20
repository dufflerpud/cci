/************************************************************************
 *indx#	debug.h - Included by software using corresponding .c file
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
