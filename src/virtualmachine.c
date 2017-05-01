#include "../include/virtualmachine.h"

VM* new_vm( void ){
  VM* nvm = malloc( sizeof( VM ) );
  nvm->entrypoint_ = 0;
  nvm->bytecode_size_ = 0;
  nvm->filedata_ = NULL;
  nvm->stack_ = new_bstack(  );
  nvm->ZF = 0;
  return nvm;
}

byte vm_load_bytecode( VM* _ptr_vm,char* _path_file ){
  File* file = new_file( _path_file );
  _ptr_vm->filedata_ = file_get_buffer( file );
  file_delete( file );
  return VM_NOERROR;
}

byte vm_init( VM* _ptr_vm ){
  memcpy( &_ptr_vm->bytecode_size_,
	  &_ptr_vm->filedata_[0],
	  4 ) ;
  memcpy( &_ptr_vm->entrypoint_,
	  &_ptr_vm->filedata_[4],
	  4 ) ;

  _ptr_vm->bytecode_ = malloc( _ptr_vm->bytecode_size_ );

  memcpy( &_ptr_vm->bytecode_[0],
	  &_ptr_vm->filedata_[8],
	  _ptr_vm->bytecode_size_ );

  /* Reserver space */
  /* RegA 4 bytes , RegB 4 bytes, RegC 4 byte , RegD 4 bytes*/
  bstack_push_block( _ptr_vm->stack_,"0000000000000000",16 );

  // ERRORS!
  if( _ptr_vm->entrypoint_ > _ptr_vm->bytecode_size_ )
    return VM_ERROR_ENTRYPOINT_OUTOFMEMORY;


  return VM_NOERROR;
}

byte vm_run( VM* _ptr_vm ){
  unsigned int ip = _ptr_vm->entrypoint_; /* instruction pointe */
  bool cpu_state = true; /* State CPU TRUE = ON , FALSE = OFF */
  byte byte_address[4];

  // CPU EMULATOR
  while( ip<_ptr_vm->bytecode_size_ && cpu_state == true ){
    #ifdef VM_DEBUGMODE
    ___vm_cpu_opcode( _ptr_vm,&ip );
#endif
    switch( _ptr_vm->bytecode_[ip] ){
    case PUSH:
      __vm_cpu_opcode_push( _ptr_vm,&ip );
      continue;
    case BPUSH:
      __vm_cpu_opcode_bpush( _ptr_vm,&ip );
      break;
    case BMOV:
      __vm_cpu_opcode_bmov( _ptr_vm,&ip );
      break;

    case CALL:
      printf( "CALL\n" );
      break;

   case RET:
      printf( "RETURN!\n" );
      break;

    case JMP:
      __vm_cpu_opcode_jmp( _ptr_vm,&ip );
      continue;

    case HALT:
      cpu_state = false;
      break;

    case VM_STACK_DUMP:
      bstack_dump( _ptr_vm->stack_ );
      break;
    }
    ip++;
  }


  return VM_NOERROR;
}

void vm_delete( VM* _ptr_vm ){
  bstack_delete( _ptr_vm->stack_ );
  free( _ptr_vm );
}

void __vm_cpu_opcode_push( VM* _ptr_vm,unsigned int* _ip ){
  *_ip = *_ip+1;
  byte i = 0;
  int dir = 0;
  memcpy( &dir,&_ptr_vm->bytecode_[*_ip],4 );

  byte temp;
  for( i=0;i<4;i++ ){
    /* Read block at ????????? solution! performance. */
    bstack_read_at( _ptr_vm->stack_,dir+i,&temp );
    bstack_push( _ptr_vm->stack_,temp );
  }
  *_ip = *_ip+4;
}

void __vm_cpu_opcode_bpush( VM* _ptr_vm,unsigned int* _ip ){
  *_ip = *_ip+1;
  bstack_push( _ptr_vm->stack_,_ptr_vm->bytecode_[*_ip] );
}

void __vm_cpu_opcode_bmov( VM* _ptr_vm,unsigned int* _ip ){
  unsigned int int_address=0;
  *_ip = *_ip+1;
  memcpy( &int_address,
	  &_ptr_vm->bytecode_[*_ip],
	  4 );
  *_ip = *_ip+4;
  bstack_set( _ptr_vm->stack_,int_address,0,4 );
  bstack_write_at( _ptr_vm->stack_,
		   int_address,
		   _ptr_vm->bytecode_[*_ip] );
}

void __vm_cpu_opcode_jmp( VM* _ptr_vm,unsigned int* _ip ){
  *_ip = *_ip+1;
  memcpy( _ip,
	  &_ptr_vm->bytecode_[*_ip],
	  4 );
}

void ___vm_cpu_opcode( VM* _ptr_vm,unsigned int* _ip ){
    printf( "[OPCODE]: %s(%d)\n",bytecode_to_string( _ptr_vm->bytecode_[*_ip] ),_ptr_vm->bytecode_[*_ip] );
}
