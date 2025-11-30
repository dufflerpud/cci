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
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>

#include "hash.h"
#include "gen.h"

/************************************************************************/
/*	Create and initialize a hashtable.				*/
/************************************************************************/
hashtablep hash_new( int number_entries, size_t entry_size )
    {
    hashtablep hp =
        (hashtablep)malloc(
	    sizeof(hashtable) + (number_entries-1)*sizeof(void*) );
    hp->ht_entries = number_entries;
    hp->ht_size = entry_size;
    hp->ht_freelist = (void*)NULL;
    memset( hp->ht_ptrs, 0, number_entries*sizeof(void*) );
    return hp;
    }

/************************************************************************/
/*	Ye olde and inefficient hashing function.  Replace soon.	*/
/************************************************************************/
int hash_ind( hashtablep htp, const char *str )
    {
    int res = 13;
    while( *str )
        res = (res * 17 + *str++) & 0xffffff;
    return res % htp->ht_entries;
    }

/************************************************************************/
/*	Search hash table for the named object				*/
/************************************************************************/
hashtable_entryp hash_lookup( hashtablep htp, const char *str )
    {
    for( hashtable_entryp hep = htp->ht_ptrs[hash_ind(htp,str)];
	hep; hep=hep->he_next )
        if( strcmp( hep->he_name, str ) == 0 )
	    return hep;
    return (hashtable_entryp)NULL;
    }

/************************************************************************/
/*	Add entry to hash table.					*/
/************************************************************************/
hashtable_entryp hash_add( hashtablep htp, const char *str )
    {
    hashtable_entryp hep = (hashtable_entryp)obj_malloc( (void**)&(htp->ht_freelist), htp->ht_size );
    int ind = hash_ind(htp,str);
    hep->he_next = htp->ht_ptrs[ind];
    htp->ht_ptrs[ind] = hep;
    hep->he_name = strdup( str );
    return hep;
    }

/************************************************************************/
/*	Delete entry from hash table.					*/
/************************************************************************/
int hash_delete( hashtablep htp, hashtable_entryp hep0 )
    {
    int ind = hash_ind(htp,hep0->he_name);
    hashtable_entryp hep1 = htp->ht_ptrs[ind];
    if( hep1 == hep0 )
        htp->ht_ptrs[ind] = hep0->he_next;
    else
	while( (hep1 = hep1->he_next) )
	    if( hep1->he_next == hep0 )
	        {
		hep1->he_next = hep0->he_next;
		break;
		}
    if( hep1 )
	{
	free( (void*)(hep0->he_name) );
	obj_free( (void**)&(htp->ht_freelist), (void*)hep0 );
	return 1;
	}
    return 0;
    }

/************************************************************************/
/*	Init traversal routine.						*/
/************************************************************************/
void hash_init_traverser( hash_traverserp travp, hashtablep htp )
    {
    travp->htt_ind = 0;
    travp->htt_ptr = (hashtable_entryp)NULL;
    travp->htt_tbl = htp;
    }

/************************************************************************/
/*	Traverse every element in a hash table.				*/
/************************************************************************/
hashtable_entryp hash_next( hash_traverserp travp )
    {
    if( travp->htt_ptr )
        {
	if( (travp->htt_ptr = travp->htt_ptr->he_next) )
	    return travp->htt_ptr;
	travp->htt_ind++;
	}
    while( travp->htt_ind < travp->htt_tbl->ht_entries )
        if( (travp->htt_ptr = travp->htt_tbl->ht_ptrs[ travp->htt_ind ]) )
	    return travp->htt_ptr;
	else
	    travp->htt_ind++;
    return NULL;
    }
