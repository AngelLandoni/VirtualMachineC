#include "../../include/tools/stack.h"

BStack* new_bstack( void ){
  BStack* nbs = malloc( sizeof( BStack ) );
  nbs->memory_ = malloc( sizeof( byte )*STACK_DEFAULT_START_SIZE );
  nbs->memory_size_ = STACK_DEFAULT_START_SIZE;
  nbs->sp_ = 0;
  return nbs;
}

void bstack_push( BStack* _ptr_stack,byte _data ){
  if( _ptr_stack->sp_ >= _ptr_stack->memory_size_ )
    __bstack_resize( _ptr_stack );
  _ptr_stack->memory_[_ptr_stack->sp_] = _data;
  _ptr_stack->sp_++;
}

void bstack_push_block( BStack* _ptr_stack,byte* _data,unsigned int _size ){
  if( _ptr_stack->sp_+_size >= _ptr_stack->memory_size_ )
    __bstack_resize( _ptr_stack );
  memcpy( &_ptr_stack->memory_[_ptr_stack->sp_],
	  _data,
	  _size );
  _ptr_stack->sp_ += _size;
}

byte bstack_write_at( BStack* _ptr_stack,unsigned int _position,byte _data ){
  if( _position > _ptr_stack->memory_size_ )
    return STACK_ERROR_OUTOFMEMORY;
  _ptr_stack->memory_[_position] = _data;
  return STACK_NOERROR;
}

byte bstack_write_block_at( BStack* _ptr_stack,
			    unsigned int _position,
			    byte*_data,
			    unsigned int _size ){
  if( _position+_size > _ptr_stack->memory_size_ )
    return STACK_ERROR_OUTOFMEMORY;
  memcpy( &_ptr_stack->memory_[_position],
	  _data,
	  _size );
  return STACK_NOERROR;
}

byte bstack_read_at( BStack* _ptr_stack,
		     unsigned int _position,
		     byte* _data ){
  if( _position > _ptr_stack->sp_ )
    return STACK_ERROR_OUTOFMEMORY;
  *_data = _ptr_stack->memory_[_position];
  return STACK_NOERROR;
}

byte bstack_set( BStack* _ptr_stack,
		 unsigned int _position,
		 byte _data,
		 unsigned int _size ){
 if( _position+_size > _ptr_stack->memory_size_ )
    return STACK_ERROR_OUTOFMEMORY;
 unsigned int i=_position;
 while( i<_position+_size ){
   _ptr_stack->memory_[i] = _data;
   i++;
 }
 return STACK_NOERROR;
}

byte bstack_pop( BStack* _ptr_stack,byte* _ptr_data ){
  if( _ptr_stack->sp_ <= 0 ){
    *_ptr_data = _ptr_stack->memory_[0]; 
    return STACK_WARNING_PTR_OUTOFMEMORY;
  }
  _ptr_stack->sp_--;
  *_ptr_data = _ptr_stack->memory_[_ptr_stack->sp_];
  return STACK_NOERROR;
}

byte bstack_pop_block( BStack* _ptr_stack,byte** _ptr_buffer,unsigned int _size ){
  if( _ptr_stack->sp_-_size > 0 ){
    char* tempbuffer = malloc( _size );
    _ptr_stack->sp_ -= _size;
    memcpy( tempbuffer,
	    &_ptr_stack->memory_[_ptr_stack->sp_],
	    _size );
    *_ptr_buffer = tempbuffer;
    return STACK_NOERROR;
  }
  return  STACK_ERROR_OUTOFMEMORY;
}

void bstack_delete( BStack* _ptr_stack ){
  free( _ptr_stack->memory_ );
  free( _ptr_stack );
}

void bstack_dump( BStack* _ptr_stack ){
  printf( "\n[STACK]: " );
  unsigned int i=0;
  while( i<_ptr_stack->sp_ ){
    printf( "{%d|%c}",
	    _ptr_stack->memory_[i],
	    _ptr_stack->memory_[i] );
    i++;
  }
}

void __bstack_resize( BStack* _ptr_stack ){
    byte* temp_memory = calloc( _ptr_stack->memory_size_*STACK_DEFAULT_SCALE,1 );
    memcpy( temp_memory,
	    _ptr_stack->memory_,
	    _ptr_stack->memory_size_ );
    free( _ptr_stack->memory_ );
    _ptr_stack->memory_ = temp_memory;
    _ptr_stack->memory_size_*=STACK_DEFAULT_SCALE;
}
