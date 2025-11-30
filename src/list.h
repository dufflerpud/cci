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

