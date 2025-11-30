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
