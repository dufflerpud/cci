/************************************************************************
 *indx#	debug.c - Software for outputting debug messages
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
 *doc#	debug.c - Software for outputting debug messages
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "debug.h"
#include "gen.h"

enum { DEBUG_STANDARD_FLAGS };

int debug_flags = 0;
const char *all_debug_flags[MAX_DEBUG_FLAGS];
int debug_call_level = 0;

/************************************************************************/
/*	Register a debug flag.						*/
/************************************************************************/
void debug_register( int flag, const char *str )
    {
    static int debug_register_previously_called = 0;
    if( ! debug_register_previously_called )
        {
	INDEX_LOOP( i, MAX_DEBUG_FLAGS )	all_debug_flags[i]=NULL;
	debug_register_previously_called = 1;
	debug_register( CALLS, "calls" );
	debug_register( STATUS, "status" );
	}
    all_debug_flags[flag] = str;
    }

/************************************************************************/
/*	Produce appropriate string depending on if filename or line	*/
/*	provided.							*/
/************************************************************************/
const char *filename_line_string( const char *fname, int line )
    {
    if( fname )
        return ( line ? bprintf("%s:%d: ",fname,line) : bprintf("%s: ",fname) );
    else
        return ( line ? bprintf("Line %s: ",line) : "" );
    }

/************************************************************************/
/*	Print a debug message if appropriate.				*/
/************************************************************************/
void vdebug(
    int flags, const char *fname, int line, const char *fmt, va_list ap )
    {
    if( debug_flags & flags )
	{
	char buf0[1024];
	vssprintf( buf0, fmt, ap );
	fprintf(stderr,"%*s%s%s\n",
	    debug_call_level,"",filename_line_string(fname,line),buf0);
	fflush(stderr);
	}
    }

/************************************************************************/
/*	Print a debug message if appropriate.				*/
/************************************************************************/
void debug( int flags, const char *fname, int line, const char *fmt, ... )
    {
    va_list ap;
    va_start( ap, fmt );
    vdebug( flags, fname, line, fmt, ap );
    va_end( ap );
    }

/************************************************************************/
/*	Print message when called.					*/
/************************************************************************/
void deb_call( int flags, const char *fname, int line, const char *fmt, ... )
    {
    va_list ap;
    debug_call_level++;
    va_start( ap, fmt );
    vdebug( flags|DBG(CALLS), fname, line, fmt, ap );
    va_end( ap );
    }

/************************************************************************/
/*	Print message when called.					*/
/************************************************************************/
void deb_status( int flags, const char *fname, int line, const char *fmt, ... )
    {
    char buf[100];
    va_list ap;
    va_start( ap, fmt );
    strcpy( buf, "Got to " );
    strcpy( buf+strlen(buf), fmt );
    vdebug( flags|DBG(STATUS), fname, line, buf, ap );
    va_end( ap );
    }

/************************************************************************/
/*	Print message when returning.					*/
/************************************************************************/
void deb_return( int flags, const char *fname, int line, const char *fmt, ... )
    {
    va_list ap;
    va_start( ap, fmt );
    vdebug( flags|DBG(CALLS), fname, line, fmt, ap );
    va_end( ap );
    debug_call_level--;
    }

/************************************************************************/
/*	Return flag from string.					*/
/************************************************************************/
int debug_arg( const char **argvptr )
    {
    const char *would_be_flag = argvptr[0];
    int addsub = 0;
    if( !strncmp(would_be_flag,"-d",2) )
        { addsub=-1; }
    else if( !strncmp(would_be_flag,"+d",2) )
        { addsub=1; }
    else
        { return 0; }
    would_be_flag+=2;
    if( ! would_be_flag[0] || ! strcasecmp( would_be_flag, "all" ) )
	{
	debug_flags = ( addsub < 0 ? 0 : -1 );
	return 1;
	}
    else
	for( int i=0; all_debug_flags[i]; i++ )
	    if( ! strcasecmp(would_be_flag,all_debug_flags[i]) )
		{
	        if( addsub < 0 )
		    debug_flags &= ~(1<<i);
		else
		    debug_flags |= (1<<i);
		return 1;
		}
    return 0;
    }

/************************************************************************/
/*	Leave around a better error message				*/
/************************************************************************/
const char *error_message;
int set_error( const char *filename, int line, const char *fmt, ... )
    {
    char buf[100];
    va_list ap;
    strcpy( buf, filename_line_string( filename, line ) );
    va_start( ap, fmt );
    vssprintf( buf+strlen(buf), fmt, ap );
    va_end( ap );
    error_message = STRDUP(buf);
    return -1;
    }
