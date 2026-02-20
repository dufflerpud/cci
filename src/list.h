/************************************************************************
 *
 *indx#	list.h - Included by software using corresponding .c file
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
#define LIST_DECL(ptrtyp,v0)	struct {ptrtyp l_begin,l_active,l_end; } v0 = { 0, 0, 0 }
#define LIST_INIT(v1)		v1.l_begin = v1.l_active = v1.l_end = 0
#define LIST_START(v2)		( v2.l_active=v2.l_begin )
#define LIST_CLICK(v3,l_next0)	((v3.l_begin = v3.l_begin->l_next0) || (v3.l_end=0))
#define LIST_SHIFT(v4,l_next1)	((LIST_START(v4) && LIST_CLICK(v4,l_next1)), v4.l_active )

#define LIST_ADD(v5,e,l_next2)	( v5.l_active=(e), \
				    v5.l_active->l_next2=0, \
				    ( v5.l_end \
					? (v5.l_end->l_next2=v5.l_active, v5.l_end=v5.l_active )\
					: (v5.l_begin = v5.l_end = v5.l_active )\
				    ) \
				)

