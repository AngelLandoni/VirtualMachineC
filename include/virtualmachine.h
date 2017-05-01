#ifndef __VIRTUALMACHINE_H__
#define __VIRTUALMACHINE_H__

#include "bytecode.h"
#include "tools/file.h"
#include "tools/utilities.h"
#include "tools/vector.h"
#include "tools/stack.h"

#define VM_DEBUGMODE

#define VM_NOERROR 0
#define VM_ERROR_OVERFLOW 1
#define VM_ERROR_ENTRYPOINT_OUTOFMEMORY 2
#define VM_ERROR_NOTIDENTIFIED_OPCODE 3

typedef struct VM{
  unsigned int entrypoint_,
    bytecode_size_;
  byte* filedata_;
  byte* bytecode_;
  BStack* stack_;
  /* Flags register */
  byte ZF;
}VM;

/* New virtual machine */
VM* new_vm( void );
/* Load bytecode */
byte vm_load_bytecode( VM*,char* );
/* init virtual machine */
byte vm_init( VM* );
/* Execute bytecode */
byte vm_run( VM* );
/* Delete cpu */
void vm_delete( VM* );

/* INTERNAL VM CPU OPCODE PUSH ( VM,IP ) */
void __vm_cpu_opcode_push( VM*,unsigned int* );
/* INTERNAL VM CPU OPCODE BPUSH ( VM,IP ) */
void __vm_cpu_opcode_bpush( VM*,unsigned int* );
/* INTERNAL VM CPU OPCODE BMOV ( VM,IP,REF ADDRESS )*/
void __vm_cpu_opcode_bmov( VM*,unsigned int* );
/* INTERNAL VM CPU OPCODE JMP */
void __vm_cpu_opcode_jmp( VM*,unsigned int* );

/* DEBUG FUNCTIONS */
void ___vm_cpu_opcode( VM*,unsigned int* );

#endif
