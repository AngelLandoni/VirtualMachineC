#ifndef __STRING_H__
#define __STRING_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

#define STRING_ENDLINE '\0'

/* --------------------------------------------------
   | STRING
   -------------------------------------------------- */

typedef struct String{
  // String inserted by user
  byte* buffer_mem_block_;
  // Length of inserted string
  unsigned int buffer_mem_block_length_;
}String;

// Create new string
String* new_string( char* );
/* New array of string */
String* new_array_string( unsigned int );
/* Allocate a string memory space */
String* string_alloc( unsigned int );
// Init string
void string_init( String*,char* );
// Set text
void string_set( String*,char* );
// Copy string ( destination, source )
void string_copy( String*,String* );
/* Compare strings */
bool string_cmp( String*,String* );
/* Compare string whit a text */
bool string_cmp_text( String*,char* );
/* String to int */
int string_to_int( String* );
/* String to unsigned int */
unsigned int string_to_uint( String* );
// Delete srting
void string_delete( String* );
// Delete ref string
void string_ref_delete( String* );
// Show debug information
void string_debug( String* );




#endif
