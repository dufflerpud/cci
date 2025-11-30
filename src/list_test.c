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

#include "list.h"

typedef struct foostruct *fooptr;
struct foostruct
    {
    const char	*f_name;
    fooptr	f_next;
    };

fooptr make_foo( const char *n )
    {
    fooptr ret = malloc( sizeof(struct foostruct) );
    ret->f_name = n;
    return ret;
    }

int main(int argc, const char **argv)
    {
    LIST_DECL(fooptr,example);
    LIST_INIT(example);
    LIST_ADD(example,make_foo("Fred"),f_next);
    LIST_ADD(example,make_foo("Ted"),f_next);
    LIST_ADD(example,make_foo("Alice"),f_next);
    LIST_START(example);
    for( fooptr f; (f=LIST_NEXT(example,f_next)); )
	printf("(%s)\n",f->f_name);
    for( fooptr f; (f=LIST_SHIFT(example,f_next)); )
	printf("(%s)\n",f->f_name);
    exit(0);
    return 0;
    }
