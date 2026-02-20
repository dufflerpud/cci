/************************************************************************
 *indx#	text.0.c - Software to maintain blocks of text
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
 *doc#	text.0.c - Software to maintain blocks of text
 ************************************************************************/
/* #include <idea.h> */
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "gen.h"
#include "text.h"
#include "debug.h"

/************************************************************************/
/*	Return integer index into string table vocab for string that	*/
/*	best matches string supplied in origstr.  Exact matches are	*/
/*	best, otherwise pick unambiguous abbreviation.  Otherwise	*/
/*	return negative values ABRV_NONE_CLOSE or ABRV_AMBIGUOUS.	*/
/************************************************************************/
int abbrev(const char *origstr, const char *vocab[] )
    {
    int ret;
    char lcstr[2048];
    int len;
    int near = ABRV_NONE_CLOSE;

    for( len=0; (lcstr[len] = origstr[len]); len++ )
        if( isupper(lcstr[len]) )
	    lcstr[len] = tolower( lcstr[len] );

    for( ret=0; vocab[ret]; ret++ )
        if( strncmp(lcstr,vocab[ret],len) == 0 )
	    {
	    if( lcstr[len] == vocab[ret][len] )
	        return ret;
	    else if( near == ABRV_NONE_CLOSE )
	        near = ret;
	    else
	        near = ABRV_AMBIGUOUS;
	    }

    if( near < 0 )
	{
	if( near == ABRV_NONE_CLOSE )
	    set_error(F,"'%s' is not understood.",lcstr);
	else
	    set_error(F,"'%s' is ambiguous.",lcstr);
	}
    return near;
    }

/************************************************************************/
/*	Return pointer to next token in buffer.				*/
/************************************************************************/
char *next_token( char **newbufpp )
    {
    static char *bufp = NULL;
    char *retval = NULL;

    bufp = *newbufpp;
    
    while( *bufp!=0 && *bufp <= ' ' )
        bufp++;

    if( *bufp != 0 && *bufp!='#' )
	{
	if( *bufp == '"' )
	    {
	    char c;
	    char *packp = ++bufp;
	    retval = packp;
	    while( (c = *packp++ = *bufp++) )
		if( c == '"' )
		    {
		    if( bufp[0] == '"' )
			bufp++;
		    else
			{
			break;
			}
		    }
	    *--packp = 0;
	    if( *bufp ) *bufp++ = 0;
	    }
	else
	    {
	    retval = bufp;
	    while( *bufp > ' ' && *bufp != '#' )
		{
		if( isupper(*bufp) )
		    *bufp = tolower( *bufp );
		bufp++;
		}
	    if( *bufp == '#' || *bufp == 0 )
		*bufp = 0;
	    else
		*bufp++ = 0;
	    }
	}
    *newbufpp = bufp;
    return retval;
    }

/************************************************************************/
/************************************************************************/
int tokenize( char *bufp, char *strings[], int maxstrings )
    {
    char *tokenptr = bufp;

    FORWARD_LOOP( numstrings, maxstrings )
        if( (strings[numstrings] = next_token( &tokenptr )) == NULL )
	    return numstrings;
    return maxstrings;
    }

/************************************************************************/
/*	Return num word or num words depending on whether num is 1.	*/
/************************************************************************/
const char *numword( const char *word, int num )
    {
    return bprintf("%d %s%s",num,word,(num==1?"":"s"));
    }

/************************************************************************/
/*	Only test abbreviation routine.					*/
/*	Someday, we could try actually executing the command.  However,	*/
/*	executing the "quit" command in a test environment won't be	*/
/*	that interesting.						*/
/************************************************************************/
void test_text( int argc, const char *argv[] )
    {
    int r;
    if( argc < 3 )
	fatal(F,"Usage:  %s command str1 str2 str3 ...\n",progname);
    else if( (r = abbrev(argv[1],argv+2)) >= 0 )
	printf("Result=%d (%s)\n",r,(argv+2)[r]);
    else
	printf("%s\n",error_message);
    }

/************************************************************************/
/*	Not much to setup.						*/
/************************************************************************/
void setup_text()
    {
    module_name_to_ptr("text")->module_test = test_text;
    }
