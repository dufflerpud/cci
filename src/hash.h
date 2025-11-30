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
