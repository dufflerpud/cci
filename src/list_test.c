/************************************************************************
 *indx#	list_test.c - Software for maintaining lists.
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
 *doc#	list_test.c - Software for maintaining lists.
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
