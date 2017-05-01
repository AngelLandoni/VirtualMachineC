#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "string.h"

#define VECTOR_NOERROR 0
#define VECTOR_ERROR_OUTOFMEMORY 1
#define VECTOR_ERROR_NOTFIND 2
#define VECTOR_ERROR_FOUND 3
#define VECTOR_ERROR_LOCKED 4

#define VECTOR_START_SIZE 512
#define VECTOR_SCALE_CONSTANT 2

/*------------------------------------------------------
 * VM Vector Structure, define
 *------------------------------------------------------*/

/* Integer vector*/
typedef struct IVector{
  int* mem_block_;
  unsigned int mem_size_,
               iterator_;
  bool is_locked_;
} IVector;

/* Get integer vector info in a buffer
   [?] Used to show in console or informative use. */
void ivector_show_info( IVector* );
/* Dump data */
void ivector_dump( IVector* );
/* New integer vector */
IVector* new_ivector( void );
/* Delete integer vector */
void ivector_delete( IVector* );
/* Add item to integer vector */
byte ivector_push( IVector*,int );
/* Erase item */
unsigned int ivector_erase( IVector*,unsigned int );
/* Get element */
int ivector_at( IVector*,unsigned int );
/* Search number ?? Return the position of this */
byte ivector_find( IVector*,int*,int );
/* Lock and unlock vector */
void ivector_lock( IVector* );
void ivector_unlock( IVector* );


/* Unsigned integer vector */
typedef struct UIVector{
  unsigned int* mem_block_;
  unsigned int mem_size_,
               iterator_;
  bool is_locked_;  
} UIVector;

/* Dump data */
void uivector_dump( UIVector* );
/* New unsigned integer */
UIVector* new_uivector( void );
/* Delete integer vector */
void uivector_delete( UIVector* );
/* Add item to integer vector */
byte uivector_push( UIVector*,unsigned int );
/* Erase item */
unsigned int uivector_erase( UIVector*,unsigned int );
/* Get element */
unsigned int uivector_at( UIVector*,unsigned int );
/* Add at */
byte uivector_add_at( UIVector*,unsigned int,unsigned int );
/* Search number ?? Return the position of this */
byte uivector_find( UIVector*,unsigned int*,unsigned int );
/* Lock and unlock vector */
void uivector_lock( UIVector* );
void uivector_unlock( UIVector* );

/*Byte vector*/
typedef struct BVector{
  byte* mem_block_;
  unsigned int mem_size_,
	       iterator_;
  bool is_locked_;
} BVector;

/* Get byte vector info in a buffer
    [?] Used to show in console or informative use.*/
void bvector_show_info( BVector* );
/* Dump data */
void bvector_dump( BVector* );
/* New byte vector */
BVector* new_bvector( void );
/* Delete byte vetor */
void bvector_delete( BVector* );
/* Add item to byte vector */
byte bvector_push( BVector*,byte );
/* Write in memory */
byte bvector_write( BVector*,unsigned int,char* );
/* Erase item */
byte bvector_erase( BVector*,unsigned int );
/* Get element */
byte bvector_at( BVector*,unsigned int );
/* Compare */
bool bvector_cmp_at( BVector*,unsigned int,byte );
/* Get size */
unsigned int bvector_get_size( BVector* );
/* Search number ?? Return the position of this */
byte bvector_find( BVector*,unsigned int*,byte );
/* Lock and unlock vector */
void bvector_lock( BVector* );
void bvector_unlock( BVector* );

/*String vector*/
typedef struct SVector{
  String* mem_block_;
  unsigned int mem_size_,
               iterator_;
  bool is_locked_;
}SVector;

/* Get string vector info in a buffer */
void svector_debug( SVector* );
/* Dump data */
void svector_dump( SVector* );
/* New string vector */
SVector* new_svector( void );
/* Push item */
void svector_push( SVector*,String* );
/* Push text item */
void svector_push_text( SVector*,char* );
/* Erase item */
byte svector_erase( SVector*,unsigned int );
/* Get element  */
String* svector_at( SVector*,unsigned int );
/* Get size */
unsigned int svector_get_size( SVector* );
/* Delete string vector */
void svector_delete( SVector* );
/* Delete ref  */
void svector_ref_delete( SVector* );


#endif
