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
#ifndef __TEXT_H__
#define __TEXT_H__

typedef enum { ABRV_NONE_CLOSE=-1, ABRV_AMBIGUOUS=-2 } abbreviation_codes;

extern const char *numword( const char *word, int num );
extern int abbrev(const char *origstr, const char *vocab[] );
extern char *next_token( char **newbufpp );
extern int tokenize( char *bufp, char *strings[], int maxstrings );
extern void test_text( int argc, const char *argv[] );
extern void setup_text();

#endif
