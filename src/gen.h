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
#ifndef __GEN_H__
#define __GEN_H__

#undef DEBUGGING_MALLOC

#ifndef DEBUGGING_MALLOC
#define MALLOC		malloc
#define REALLOC		realloc
#define REALLOCARRAY	reallocarray
#define CALLOC		calloc
#define STRDUP		strdup
#define xSTRNDUP		strndup
#define xSTRDUPA		strdupa
#define xSTRNDUPA	strndupa
#define FREE		free
#else
#define MALLOC		deb_malloc
#define REALLOC		deb_realloc
#define REALLOCARRAY	deb_reallocarray
#define CALLOC		deb_calloc
#define STRDUP		deb_strdup
#define xSTRNDUP		deb_strndup
#define xSTRDUPA		deb_strdupa
#define xSTRNDUPA	deb_strndupa
#define FREE		deb_free

extern void *deb_malloc(size_t size);
extern void deb_free(void *ptr);
extern void *deb_calloc(size_t nmemb, size_t size);
extern void *deb_realloc(void *ptr, size_t size );
extern void *deb_reallocarray(void *ptr, size_t nmemb, size_t size );
extern char *deb_strdup( const char *s );
extern char *deb_strndup(const char *s, size_t n);
extern char *deb_strdupa(const char *s);
extern char *deb_strndupa(const char *s, size_t n);
extern void sanity( int );
#endif

#include <errno.h>

typedef enum { FALSE, TRUE } booleans;
typedef enum { NOCOPY, COPY } copyflag;

#define CONCATENATE_DIRECT(s1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_DIRECT(s1, s2)
#define ANONYMOUS_VARIABLE(str) CONCATENATE(str,CONCATENATE(_ANON, __LINE__))

#define F			__FILE__,__LINE__

#define FORWARD_LOOP(ind,sz)	for(int ind=0,ANONYMOUS_VARIABLE(bnd)=(sz); ind<ANONYMOUS_VARIABLE(bnd); ind++ )
#define QFORWARD_LOOP(ind,sz)	for(int ind=0,ind##_LOOP_BOUNDARY=(sz); ind<ind##_LOOP_BOUNDARY; ind++ )
#define BACKWARD_LOOP(ind,sz)	for(int ind=(sz); ind-->0; )
#define INDEX_LOOP(ind,sz)	FORWARD_LOOP(ind,sz)

#define RANDOM_BETWEEN(mn,mx)	((mx-mn)*random()/RAND_MAX + mn)

extern const char *get_progname( const char *orig );
extern char cprintf_buf[];
extern char *cprintf( char *bufp, const char *fmt, ... );
extern char *cheap_buf();
extern const char *bprintf( const char *fmt, ... );
extern const char *mprintf( const char *fmt, ... );
extern void fatal( const char *fname, int line, const char *fmt, ... );
extern const char *vssprintf( char *buf0, const char * fmt, va_list ap );
extern char *new_file_name( const char *basename );

#define ARRAY_DEFAULT_ELEM_SIZE	sizeof(char)
#define ARRAY_DEFAULT_BUF_INCR	1024

extern const char *array_copy_flags[];
extern void array_check( const char *fname, int line, void *p );
extern void *array_setup( size_t size, int chunksize, int count );
extern void *array_resize( void **orig_ptr, int count, copyflag c );
extern int array_count( void *orig_ptr );
extern void *array_new( void **orig_ptr );
extern void array_shrink( void **orig_ptr );
extern void array_remove( void **orig_ptr );
extern void *obj_malloc( void **freelist_arg, size_t size );
extern void obj_free( void **freelist_arg, void *obj );

extern char *strerror( int );
extern const char *const sys_errlist[];
/* extern void growbuf( void **vmemp, int size, int copyflag, int addsize ); */
extern void *nrealloc( void *orig, int size );
extern const char *pretty_buf( const char *buf, int size );
extern int reprand( unsigned int seed, int range );

#define GENERATE_STRING(PREF,VAL)	#VAL,
#define GENERATE_ENUM(PREF,VAL)		PREF##VAL,
#define string_enum_list( strings, enums, list )	\
    const char *strings[] = { list(GENERATE_STRING) NULL }; \
    typedef enum { list(GENERATE_ENUM) } enums

/* Example use							*/
/*								*/
/*	#define COMMANDS(V)	V(COM_,quit) V(COM_,help)	*/
/*	string_enum_list( strings, enums, COMMANDS );		*/

#ifdef linux
#include <unistd.h>
#include <errno.h>
extern char *strerror( int );
#define STRERROR(x)	strerror(x)
#else
#ifndef __APPLE__
extern const char *const sys_errlist[];
#endif
#define STRERROR(x)	sys_errlist[x]
#endif

#ifdef TEST
extern void test_gen(int argc,const char *argv[]);
extern void setup_gen();
#endif

#endif
