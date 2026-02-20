/************************************************************************
 *
 *indx#	hash.h - Included by software using corresponding .c file
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
#ifndef __HASH_H__
#define __HASH_H__

#define DEFAULT_HASH_SIZE		999983		/* A big prime */

typedef struct hashtable_entry_struct
    {
    struct hashtable_entry_struct	*he_next;
    char				*he_name;
    } hashtable_entry;
typedef hashtable_entry *hashtable_entryp;

typedef struct hashtable_struct
    {
    int					ht_entries;
    size_t				ht_size;
    void				*ht_freelist;
    void				*ht_ptrs[0];
    } hashtable;
typedef hashtable *hashtablep;

typedef struct hash_traverser_struct
    {
    int					htt_ind;
    hashtable_entryp			htt_ptr;
    hashtablep				htt_tbl;
    } hash_traverser;
typedef hash_traverser *hash_traverserp;

extern hashtablep hash_new( int number_entries, size_t entry_size );
extern int hash_ind( hashtablep htp, const char *str );
extern hashtable_entryp hash_lookup( hashtablep htp, const char *str );
extern hashtable_entryp hash_add( hashtablep htp, const char *str );
extern int hash_delete( hashtablep htp, hashtable_entryp hep0 );
extern void hash_init_traverser( hash_traverserp travp, hashtablep htp );
extern hashtable_entryp hash_next( hash_traverserp travp );

#define ACROSS_HASHES( htbl, ptrtyp, p )	hash_traverser ANONYMOUS_VARIABLE(p); hash_init_traverser( &ANONYMOUS_VARIABLE(p), (hashtablep)htbl ); for( ptrtyp p; (p=(ptrtyp)hash_next( &ANONYMOUS_VARIABLE(p) ) ); )

#endif
