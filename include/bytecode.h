#ifndef __BYTECODE_H__
#define __BYTECODE_H__

#include <stdlib.h>
#include "tools/utilities.h"

#define BPUSH 0
#define PUSH 1
#define BPOP 2
#define BMOV 3
#define IMOV 4
#define CMP 5
#define HALT 15
#define CALL 16
#define JMP 17
#define RET 18
#define VM_STACK_DUMP 19

#define BYTESIZE_INTR_BPUSH 2
#define BYTESIZE_INTR_PUSH 5
#define BYTESIZE_INTR_BMOV 6 // 6 bytes BMOV -> 1 byte , REGA(DIR)-> 4 byte, DATA-> 1 byte
#define BYTESIZE_INTR_IMOV 9
#define BYTESIZE_INTR_CMP 9
#define BYTESIZE_INTR_HALT 1
#define BYTESIZE_INTR_CALL 5
#define BYTESIZE_INTR_JMP 5
#define BYTESIZE_INTR_RET 1
#define BYTESIZE_INTR_VM_STACK_DUMP 1

#define STRING_BPUSH "bpush"
#define STRING_PUSH "push"
#define STRING_BPOP "bpop"
#define STRING_BMOV "bmov"
#define STRING_IMOV "imov"
#define STRING_CMP "cmp"
#define STRING_HALT "halt"
#define STRING_CALL "call"
#define STRING_JMP "jmp"
#define STRING_RET "ret"
#define STRING_VM_STACK_DUMP "vm_stack_dump"

#define STRING_MAIN "__main"

#define REGA 0 // MEM DIR
#define REGB 4 // MEM DIR
#define REGC 8 // MEM DIR
#define REGD 12 // MEM DIR
#define STRING_REGA "rega"
#define STRING_REGB "regb"
#define STRING_REGC "regc"
#define STRING_REGD "regd"

#define STRING_MAIN "__main"

typedef struct BytecodeHeader{
  unsigned int entry_point_,
    code_size_;
}BytecodeHeader;

/* New bytecode header*/
BytecodeHeader* new_bytecodeheader( void );
/* Set header */
void bytecodeheader_set_entrypoint( BytecodeHeader*,unsigned int );
/* Set code size */
void bytecodeheader_set_codesize( BytecodeHeader*,unsigned int );
/* Delete */
void bytecodeheader_delete( BytecodeHeader* );

char* bytecode_to_string( byte );
byte bytecode_to_int( char* );

#endif
