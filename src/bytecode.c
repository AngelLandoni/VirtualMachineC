#include "../include/bytecode.h"

BytecodeHeader* new_bytecodeheader( void ){
  BytecodeHeader* bch = malloc( sizeof(BytecodeHeader) );
  bch->entry_point_ = 0;
  bch->code_size_ = 0;
  return bch;
}

void bytecodeheader_set_entrypoint( BytecodeHeader* _ptr_bch,unsigned int _data ){
  _ptr_bch->entry_point_ = _data;
}

void bytecodeheader_set_codesize( BytecodeHeader* _ptr_bch,unsigned int _data ){
  _ptr_bch->code_size_ = _data;
}

void bytecodeheader_delete( BytecodeHeader* _ptr_bytecodeheader ){
  free( _ptr_bytecodeheader );
}

char* bytecode_to_string( byte _id ){
  if( _id == BPUSH ) return STRING_BPUSH;
  else if( _id == BPOP ) return STRING_BPOP;
  else if( _id == BMOV ) return STRING_BMOV;
  else if( _id == IMOV ) return STRING_IMOV;
  else if( _id == HALT ) return STRING_HALT;
  else if( _id == JMP ) return STRING_JMP;
  return "";
}

byte bytecode_to_int( char* _text ){
  if( _text == STRING_BPUSH ) return BPUSH;
  else if( _text == STRING_BPOP ) return BPOP;
  else if( _text == STRING_BMOV ) return BMOV;
  else if( _text == STRING_IMOV ) return IMOV;
  else if( _text == STRING_HALT ) return HALT;
  return -1;  
}
