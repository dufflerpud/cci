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
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "debug.h"
#include "gen.h"

#include <unistd.h>

#ifndef notdef
#define PARANOID(fn,ln,pt)	array_valid(fn,ln,pt)
#define XPARANOID(fn,ln,pt)
#define PARANOID1		12345678
#define PARANOID2		(-PARANOID1)
#else
#define PARANOID(fn,ln,pt)
#endif

/************************************************************************/
/*	Like basename but just returns pointer into original string.	*/
/************************************************************************/
const char *get_progname( const char *orig )
    {
    const char *res = strrchr( orig, '/' );
    return ( res ? res+1 : orig );
    }

/************************************************************************/
/*	Like sprintf only concatinates result into buffer.		*/
/************************************************************************/
char cprintf_buf[1000];
char *cprintf( char *old_cp, const char *fmt, ... )
    {
    char *cp = ( old_cp ? old_cp : cprintf_buf );
    cp[0] = 0;
    va_list ap;
    va_start( ap, fmt );
    (void)vssprintf( cp, fmt, ap );
    va_end( ap );
    return ( old_cp ? (old_cp + strlen(old_cp)) : cprintf_buf );
    }

/************************************************************************/
/*	Allocate one chunk of memory and use it for scribbling.		*/
/************************************************************************/
#define CBSIZE		1000
#define CBPOVERRUN	100
char *cheap_buf()
    {
    static char *cbp = NULL;
    static int ind = 0;
    if( cbp == NULL )
	{
	cbp = (char*)MALLOC( CBSIZE+CBPOVERRUN );
	}
    else if( (ind += ( strlen(cbp+ind) + 1 )) > CBSIZE )
        {
	ind = 0;
	}
    cbp[ind] = 0;
    return cbp + ind;
    }

/************************************************************************/
/*	Like sprintf only returns value into malloc'd buffer.		*/
/************************************************************************/
const char *bprintf( const char *fmt, ... )
    {
    char *cp = cheap_buf();
    va_list ap;
    va_start( ap, fmt );
    (void)vssprintf( cp, fmt, ap );
    va_end( ap );
    return cp;
    }

/************************************************************************/
/*	Like sprintf only returns value into malloc'd buffer.		*/
/************************************************************************/
const char *mprintf( const char *fmt, ... )
    {
    char buf[1000];
    va_list ap;
    va_start( ap, fmt );
    (void)vssprintf( buf, fmt, ap );
    va_end( ap );
    return STRDUP( buf );
    }

typedef struct memblk_struct
    {
#ifdef PARANOID1
    int		mb_para1;	/* Something to check not overwritten */
#endif
    size_t	mb_elem_size;	/* Number of bytes in each element */
    int		mb_count;	/* Number of elements used */
    int		mb_allocated;	/* Number of elements already allocated */
    int		mb_chunk;	/* When used > allocated, inc by how much */
#ifdef PARANOID2
    int		mb_para2;	/* Something to check not overwritten */
#endif
    } memblk, *memblk_ptr;

#ifdef PARANOID
/************************************************************************/
/*	Check to make sure a header is valid.				*/
/************************************************************************/
void array_valid( const char *fname, int line, memblk_ptr mp )
    {
    mp--;
#ifdef PARANOID1
    if( mp->mb_para1 != PARANOID1 )
        fatal( fname, line, "Beginning of array header for %p trashed.", mp );
#endif
#ifdef PARANOID2
    if( mp->mb_para2 != PARANOID2 )
        fatal( fname, line, "End of array header for %p trashed.", mp );
#endif
    }
#endif

/************************************************************************/
/*	Shows information from array header.				*/
/************************************************************************/
void array_check( const char *fname, int line, void *p0 )
    {
    if( ! p0 )
        deb_status(0,fname,line,"array_check(null)");
    else
        {
	memblk_ptr mp = (memblk_ptr)p0 - 1;
	deb_status(0,fname,line,
	    "array_check(%p) elem_size=%d count=%d allocated=%d chunk=%d", p0,
	    mp->mb_elem_size,
	    mp->mb_count,
	    mp->mb_allocated,
	    mp->mb_chunk);
	}
    }

/************************************************************************/
/*	Create an array with header.					*/
/************************************************************************/
void *array_setup( size_t elem_size, int chunk, int count )
    {
    deb_call(0,F,"array_setup(%d,%d,%d)",elem_size,chunk,count);
    memblk_ptr mp = MALLOC( sizeof(memblk) + elem_size*count );
#ifdef PARANOID1
    mp->mb_para1 = PARANOID1;
#endif
    mp->mb_elem_size = elem_size;
    mp->mb_allocated = mp->mb_count = count;
    mp->mb_chunk = chunk;
#ifdef PARANOID2
    mp->mb_para2 = PARANOID2;
#endif
    PARANOID(__FILE__,__LINE__,mp+1);
    deb_return(0,F,"array_setup(%d,%d,%d) returns %p",elem_size,chunk,count,mp+1);
    return (void*)(mp + 1);
    }

/************************************************************************/
/*	Return number of items in array.				*/
/************************************************************************/
extern int array_count( void *orig_ptr )
    {
    PARANOID(__FILE__,__LINE__,orig_ptr);
    return ( orig_ptr==NULL ? 0 : (((memblk_ptr)orig_ptr)-1) -> mb_count );
    }

/************************************************************************/
/*	Slightly smarter realloc.					*/
/************************************************************************/
const char *array_copy_flags[] = { "NOCOPY", "COPY" };
void *array_resize( void **orig_ptr, int count, copyflag cf )
    {
    PARANOID(__FILE__,__LINE__,*orig_ptr);
    deb_call(0,F,"array_resize(%p,%d,%s) called",
        *orig_ptr, count, array_copy_flags[cf] );

    if( *orig_ptr == NULL )
        *orig_ptr =
	    array_setup(ARRAY_DEFAULT_ELEM_SIZE,ARRAY_DEFAULT_BUF_INCR,count);
    else
	{
	memblk_ptr mp = ((memblk_ptr)*orig_ptr) - 1;
	mp->mb_count = count;

	if( count > mp->mb_allocated ) 
	    {
	    mp->mb_allocated += mp->mb_chunk;
	    size_t to_malloc =
		mp->mb_allocated * mp->mb_elem_size
		+ sizeof(memblk);

	    if( cf == COPY )
		mp = REALLOC( mp, to_malloc );
	    else
		{
		memblk remember_blk;
		memcpy( &remember_blk, mp, sizeof(remember_blk) );
		FREE( mp );
		mp = MALLOC( to_malloc );
		memcpy( mp, &remember_blk, sizeof(remember_blk) );
		}
	    *orig_ptr = mp + 1;
	    }
	}
    deb_return(0,F,"array_resize returns %p.",*orig_ptr);
    return *orig_ptr;
    }

/************************************************************************/
/*	Increase the size of the array and return a pointer to the	*/
/*	newest element.							*/
/************************************************************************/
void *array_new( void **orig_ptr )
    {
    PARANOID(__FILE__,__LINE__,*orig_ptr);
    int ind = array_count( *orig_ptr );
    deb_call(0,F,"array_new(%p)",orig_ptr);
    (void)array_resize( orig_ptr, ind+1, COPY );
    void *ret = *orig_ptr + ind * (((memblk_ptr)*orig_ptr-1)->mb_elem_size);
    deb_return(0,F,"array_new(%p) ind=%d returns %p",orig_ptr,ind,ret);
    return ret;
    }

/************************************************************************/
/*	Decrease size of array by one.					*/
/************************************************************************/
void array_shrink( void **orig_ptr )
    {
    PARANOID(__FILE__,__LINE__,*orig_ptr);
    deb_call(0,F,"array_shrink(%p)",orig_ptr);
    if( *orig_ptr )
	(void)array_resize( orig_ptr, array_count(*orig_ptr) - 1, COPY );
    deb_call(0,F,"array_shrink(%p) returns",orig_ptr);
    }

/************************************************************************/
/*	Free up space used for array.					*/
/************************************************************************/
void array_remove( void **orig_ptr )
    {
    PARANOID(__FILE__,__LINE__,*orig_ptr);
    memblk_ptr to_free = ((memblk_ptr)*orig_ptr) - 1;
    FREE( to_free );
    *orig_ptr = NULL;
    }

/************************************************************************/
/*	Unpack a sprintf string with substitutions for %m and %p	*/
/************************************************************************/
const char *vssprintf( char *buf0, const char * fmt, va_list ap )
    {
    char buf1[1024];
    char *buf1p = buf1;
    while( (*buf1p = *fmt++) )
        {
	if( *buf1p != '%' )
	    { buf1p++; }
	else
	    {
	    switch( *fmt++ )
	        {
		case 'm':	strcpy( buf1p, STRERROR(errno) );	break;
		case 'p':	strcpy( buf1p, "{%08x}" );		break;
		case '%':	strcpy( buf1p, "%%" );			break;
		default:	*++buf1p=fmt[-1]; *++buf1p=0;		break;
		}
	    buf1p += strlen( buf1p );
	    }
	}
    *buf1p = 0;
    vsprintf( buf0, buf1, ap );
    return buf0;
    }

/************************************************************************/
/*	Print an error message and die.					*/
/************************************************************************/
void fatal( const char *fname, int line, const char * fmt, ... )
    {
    va_list ap;
    va_start(ap,fmt);
    char buf0[1024];
    buf0[0] = 0;
    if( fname )	{ sprintf(buf0,"%s:",fname); }
    if( line )	{ sprintf(buf0+strlen(buf0),"%d:",line); }
    vssprintf( buf0+strlen(buf0), fmt, ap );
    fprintf( stderr, "%s\n", buf0 );
    va_end(ap);
    exit(1);
    }

/************************************************************************/
/*	Find a unique filename based on the specified format.		*/
/************************************************************************/
char *new_file_name( const char *basename )
    {
    static char buf[1024];
    FORWARD_LOOP( ind, 999999 )
        {
	sprintf( buf, "%s.%06d", basename, ind );
	if( access(buf,F_OK) < 0 ) return buf;
	}
    return NULL;
    }

typedef struct malloc_struct
    {
    struct malloc_struct *malloc_next;
    } malloc_obj, *malloc_ptr;

/************************************************************************/
/*	Only call malloc when we have no unallocated objects.		*/
/************************************************************************/
void *obj_malloc( void **freelist, size_t size )
    {
    malloc_ptr ret = *freelist;
    if( ret )
	*(malloc_ptr*)freelist = ret->malloc_next;
    else
	ret = MALLOC( size<sizeof(malloc_obj) ? sizeof(malloc_obj) : size );
    return ret;
    }

/************************************************************************/
/*	Don't deallocate an object, just put it back in the free list.	*/
/************************************************************************/
void obj_free( void **freelist, void *obj )
    {
    ((malloc_ptr)obj)->malloc_next = (malloc_ptr)*freelist;
    *freelist = obj;
    }

/************************************************************************/
/*	Return a string but show non-printable bytes in (%d) format.	*/
/************************************************************************/
const char *pretty_buf( const char *bufp, int size )
    {
    static char *pbp = NULL;
    char *cp;
    if( pbp ) FREE( pbp );
    cp = pbp = (char*)MALLOC( size*4 + 3 );
    *cp++ = '[';
    while( size-- > 0 )
	{
	int c = *bufp++;
	sprintf( cp, ((c<' '||c>'~')?"(%%%03d)":"%c"), c );
	cp += strlen(cp);
	}
    *cp++ = ']';
    *cp++ = 0;
    return pbp;
    }

/************************************************************************/
/************************************************************************/
int reprand( unsigned int seed, int range )
    {
    srand( seed );
    return rand() % range;
    }

#ifdef notdef
/************************************************************************/
/*	OK, this is gross enough for a comment.				*/
/*	Called with a pointer to a pointer (initially pointer to NULL)	*/
/*	and a size.  Return a pointer to one int into a block of memory	*/
/*	and store the size of the block in that int (if you will, at	*/
/*	offset "-1".  This simply cuts down on the amount of code	*/
/*	required to maintain growing buffers by putting all of the	*/
/*	badness here.  Worth it?  You decide.				*/
/************************************************************************/
void growbuf( void **vmemp, int size, int copyflag, int addsize )
    {
    int **memp = (int**)vmemp;
    if( (*memp) == NULL )
        {
	size += addsize;
	*memp = (int*)MALLOC( sizeof(int) + size );
	*(*memp)++ = size;
	}
    else if( (*memp)[-1] < size )
        {
	size += addsize;
	if( copyflag )
	    {
	    *memp = (int*)REALLOC( *memp-1, sizeof(int) + size );
	    }
	else
	    {
	    FREE( *memp );
	    *memp = (int*)MALLOC( sizeof(int) + size );
	    }
	*(*memp)++ = size;
	}
    }
#endif

/************************************************************************/
/*	Just like REALLOC() only allows original pointer to be null.	*/
/************************************************************************/
void *nrealloc( void *orig, int size )
    {
    return ( orig ? REALLOC((void*)orig,size) : MALLOC(size) );
    }
