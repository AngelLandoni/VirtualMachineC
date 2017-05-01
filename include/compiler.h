#ifndef __COMPILER_H__
#define __COMPILER_H__

#include "parser.h"
#include "bytecode.h"
#include "tools/utilities.h"
#include "tools/file.h"

//#define COMPILER_DEBUGMODE

#define COMPILER_NOERROR 0

#define COMPILER_BYTECODE_HEADERSIZE 8 // In bytes

/* ############################################## */
/* # BYTECODE HEADER: */
/* #   [+] 4 bytes for code size */
/* #   [+] 4 bytes for entry point */
/* #   [+] Text section */
/* ##############################################*/

typedef struct Compiler{
  Parser* handler_parser_;
  BVector* bytecode_;
  BytecodeHeader* bytecode_header_;
  SVector* errors_;
}Compiler;

/* New compiler */
Compiler* new_compiler( void );
/* Compile */
byte compiler_compile( Compiler*,char* );
/* Save bytecode */
void compiler_save_bytecode( Compiler*,char* );
/* Delete */
void compiler_delete( Compiler* );

/* INTERNAL FUNCTIONS*/
/* Function correction  */
void __compiler_function_correction( SVector*,UIVector*,unsigned int,String*,unsigned int );
/* Show dump data */
void __compiler_dump_test( BVector*,SVector* );
/* Replace call dir whit the function dir */
void __complier_replace_calldir( Compiler*,UIVector* );

#endif
