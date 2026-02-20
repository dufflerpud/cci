/************************************************************************
 *indx#	deb_malloc.c - Software to debug garbage/memory problems
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
 *doc#	deb_malloc.c - Software to debug garbage/memory problems
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gen.h>

void sanity( int lineno )
    {
#ifdef arf
    char *n = malloc( 1 );
    fprintf(stderr,"Sanity at %d\n",lineno);	fflush(stderr);
#endif
    }

#ifdef MALLOC
void *deb_malloc(size_t size)
    {
    fprintf(stderr,"deb_malloc(%d)",size);	fflush(stderr);
    void *ret = malloc( size );
    fprintf(stderr," returned %d.\n",ret);	fflush(stderr);
    return ret;
    }
#endif

#ifdef FREE
void deb_free(void *ptr)
    {
    fprintf(stderr,"deb_free(%d)",ptr);		fflush(stderr);
    free( ptr );
    fprintf(stderr," returns.\n");		fflush(stderr);
    }
#endif

#ifdef CALLOC
void *deb_calloc(size_t nmemb, size_t size)
    {
    fprintf(stderr,"deb_calloc(%d,%d)",nmemb,size);	fflush(stderr);
    void *ret = calloc( nmemb, size );
    fprintf(stderr," returned %d.\n",ret);	fflush(stderr);
    return ret;
    }
#endif

#ifdef REALLOC
void *deb_realloc(void *ptr, size_t size )
    {
    fprintf(stderr,"deb_realloc(%d,%d)",ptr,size);	fflush(stderr);
    void *ret = realloc( ptr, size );
    fprintf(stderr," returned %d.\n",ret);	fflush(stderr);
    return ret;
    }
#endif

#ifdef REALLOCARRAY
void *deb_reallocarray(void *ptr, size_t nmemb, size_t size )
    {
    fprintf(stderr,"deb_realloc(%d,%d,%d)",ptr,nmemb,size);	fflush(stderr);
    void *ret = reallocarray( ptr, nmemb, size );
    fprintf(stderr," returned %d.\n",ret);	fflush(stderr);
    return ret;
    }
#endif

#ifdef STRDUP
char *deb_strdup( const char *s )
    {
    fprintf(stderr,"deb_strdup(%s)",s);		fflush(stderr);
    char *ret = strdup(s);
    fprintf(stderr," returned %d.\n",ret);	fflush(stderr);
    return ret;
    }
#endif

#ifdef STRNDUP
char *deb_strndup(const char *s, size_t n)
    {
    char *ret = strndup(s,n);
    return ret;
    }
#endif

#ifdef STRDUPA
char *deb_strdupa(const char *s)
    {
    char *ret = strdupa(s);
    return ret;
    }
#endif

#ifdef STRNDUPA
char *deb_strndupa(const char *s, size_t n)
    {
    char *ret = strndupa(s,n);
    return ret;
    }
#endif
