# Documentation for cci

Caldwell's C interface:

<hr>

<table src="Makefile src/*.c src/*.h"><tr><th align=left><a href='#dt_8738kcMbH'>Makefile</a></th><td>Build routines in Caldwell's C library</td></tr>
<tr><th align=left><a href='#dt_8738kcMbI'>deb_malloc.c</a></th><td>Software to debug garbage/memory problems</td></tr>
<tr><th align=left><a href='#dt_8738kcMbJ'>debug.c</a></th><td>Software for outputting debug messages</td></tr>
<tr><th align=left><a href='#dt_8738kcMbK'>gen.c</a></th><td>Random routines I commonly use (general purpose)</td></tr>
<tr><th align=left><a href='#dt_8738kcMbL'>hash.c</a></th><td>Software for maintaining a hash tables.</td></tr>
<tr><th align=left><a href='#dt_8738kcMbM'>list_test.c</a></th><td>Software for maintaining lists.</td></tr>
<tr><th align=left><a href='#dt_8738kcMbN'>netio.c</a></th><td>Simple front end to standard UNIX network i/o</td></tr>
<tr><th align=left><a href='#dt_8738kcMbO'>text.0.c</a></th><td>Software to maintain blocks of text</td></tr>
<tr><th align=left><a href='#dt_8738kcMbP'>text.c</a></th><td>Software for maintaining blocks of text</td></tr>
<tr><th align=left><a href='#dt_8738kcMbQ'>debug.h</a></th><td>Included by software using corresponding .c file</td></tr>
<tr><th align=left><a href='#dt_8738kcMbR'>gen.h</a></th><td>Included by software using corresponding .c file</td></tr>
<tr><th align=left><a href='#dt_8738kcMbS'>hash.h</a></th><td>Included by software using corresponding .c file</td></tr>
<tr><th align=left><a href='#dt_8738kcMbT'>list.h</a></th><td>Included by software using corresponding .c file</td></tr>
<tr><th align=left><a href='#dt_8738kcMbU'>netio.h</a></th><td>Included by software using corresponding .c file</td></tr>
<tr><th align=left><a href='#dt_8738kcMbV'>text.h</a></th><td>Included by software using corresponding .c file</td></tr></table>

<hr>

<div id=docs>

## <a id='dt_8738kcMbH'>Makefile</a>
Build routines in Caldwell's C library

## <a id='dt_8738kcMbI'>deb_malloc.c</a>
Software to debug garbage/memory problems

## <a id='dt_8738kcMbJ'>debug.c</a>
Software for outputting debug messages

## <a id='dt_8738kcMbK'>gen.c</a>
Random routines I commonly use (general purpose)

## <a id='dt_8738kcMbL'>hash.c</a>
Software for maintaining a hash tables.

## <a id='dt_8738kcMbM'>list_test.c</a>
Software for maintaining lists.

## <a id='dt_8738kcMbN'>netio.c</a>
Simple front end to standard UNIX network i/o

## <a id='dt_8738kcMbO'>text.0.c</a>
Software to maintain blocks of text

## <a id='dt_8738kcMbP'>text.c</a>
Software for maintaining blocks of text

## <a id='dt_8738kcMbQ'>debug.h</a>
Included by software using corresponding .c file

## <a id='dt_8738kcMbR'>gen.h</a>
Included by software using corresponding .c file

## <a id='dt_8738kcMbS'>hash.h</a>
Included by software using corresponding .c file

## <a id='dt_8738kcMbT'>list.h</a>
Included by software using corresponding .c file

## <a id='dt_8738kcMbU'>netio.h</a>
Included by software using corresponding .c file

## <a id='dt_8738kcMbV'>text.h</a>
Included by software using corresponding .c file</div>

<hr>

If you add a file with #doc#/#indx# lines, you should make sure it will be
found in the 'table src=' line above and then rerun doc_sep in this directory.

Similarly, if you remove files, re-run doc_sep.


