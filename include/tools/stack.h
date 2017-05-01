#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

#define STACK_DEFAULT_START_SIZE 512 // 512 bytes!
#define STACK_DEFAULT_SCALE 2

#define STACK_NOERROR 0
#define STACK_ERROR_OUTOFMEMORY 1

#define STACK_WARNING_PTR_OUTOFMEMORY -1

typedef struct BStack{
  unsigned int memory_size_,
    sp_;
  byte* memory_;
}BStack;

/* Create new BStack */
BStack* new_bstack( void );
/* Push stack */
void bstack_push( BStack*,byte );
/* Push block stack */
void bstack_push_block( BStack*,byte*,unsigned int );
/* Write at  ( STACK,address,data  )*/
byte bstack_write_at( BStack*,unsigned int,byte );
/* Write block at */
byte bstack_write_block_at( BStack*,unsigned int,byte*,unsigned int );
/* Read at */
byte bstack_read_at( BStack*,unsigned int,byte* );
/* Set */
byte bstack_set( BStack*,unsigned int,byte,unsigned int );
/* Pop stack */
byte bstack_pop( BStack*,byte* );
/* Pop block stack */
byte bstack_pop_block( BStack*,byte**,unsigned int );
/* Delete stack */
void bstack_delete( BStack* );

/* Dump data */
void bstack_dump( BStack* );

/* INTERNAL USE */
void __bstack_resize( BStack* );

#endif
