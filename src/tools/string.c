#include "../../include/tools/string.h"

String* new_string( char* _buffer ){
  String* temp_string = malloc( sizeof( String ) );
  // Save length
  temp_string->buffer_mem_block_length_ = strlen( _buffer );
  // Assign memory for the buffer
  temp_string->buffer_mem_block_ = malloc( temp_string->buffer_mem_block_length_ );
  // Copy the string to string memory
  memcpy( temp_string->buffer_mem_block_,_buffer,temp_string->buffer_mem_block_length_ );
  // Set end to the string
  temp_string->buffer_mem_block_[temp_string->buffer_mem_block_length_] = STRING_ENDLINE;
  return temp_string;
}

String* new_array_string( unsigned int _size ){
  unsigned int i = 0;
  String* array_string = calloc( _size,sizeof( String ) );
  while( i<_size ){
    array_string[i].buffer_mem_block_ = NULL;
    array_string[i].buffer_mem_block_length_ = _size;
    i++;
  }
  return array_string;
}

String* string_alloc( unsigned int _size ){
  return calloc( _size,sizeof( String ) );
}

void string_init( String* _ptr_string,char* _buffer ){
  _ptr_string->buffer_mem_block_length_ = strlen( _buffer );
  _ptr_string->buffer_mem_block_ = malloc( _ptr_string->buffer_mem_block_length_ );
  // Copy the string to string memory
  memcpy( _ptr_string->buffer_mem_block_,_buffer,_ptr_string->buffer_mem_block_length_ );
  _ptr_string->buffer_mem_block_[_ptr_string->buffer_mem_block_length_] = '\0';
}

void string_set( String* _ptr_string,char* _buffer ){
  if( _ptr_string->buffer_mem_block_ == NULL )
    _ptr_string->buffer_mem_block_ = malloc( strlen( _buffer ) );
  else
    _ptr_string->buffer_mem_block_ = realloc( _ptr_string->buffer_mem_block_,strlen( _buffer ) );
  memcpy( _ptr_string->buffer_mem_block_,_buffer,strlen( _buffer ) );
}

void string_copy( String* _ptr_f_string,String* _ptr_s_string ){
  _ptr_f_string->buffer_mem_block_length_ = _ptr_s_string->buffer_mem_block_length_;
  _ptr_f_string->buffer_mem_block_ = realloc( _ptr_f_string->buffer_mem_block_,
					      _ptr_f_string->buffer_mem_block_length_);
  memcpy( _ptr_f_string->buffer_mem_block_,
	  _ptr_s_string->buffer_mem_block_,
	  _ptr_f_string->buffer_mem_block_length_ );
  _ptr_f_string->buffer_mem_block_[_ptr_f_string->buffer_mem_block_length_] = '\0'; 
}

bool string_cmp( String* _ptr_stringA,String* _ptr_stringB ){
  if( !strcmp( _ptr_stringA->buffer_mem_block_,
	       _ptr_stringB->buffer_mem_block_ ) )
    return true;
  return false;
}

bool string_cmp_text( String* _ptr_string,char* _text ){
  if( !strcmp( _ptr_string->buffer_mem_block_,
	       _text ) )
    return true;
  return false;
}

int string_to_int( String* _ptr_string ){
  return atoi( _ptr_string->buffer_mem_block_ );
}

unsigned int string_to_uint( String* _ptr_string ){
  return strtoul( _ptr_string->buffer_mem_block_,NULL,10 );
}

void string_delete( String* _ptr_string ){
  free( _ptr_string->buffer_mem_block_ );
  free( _ptr_string );
}

void string_ref_delete( String* _ptr_string ){
  free( _ptr_string->buffer_mem_block_ );
}

void string_debug( String* _ptr_string ){
  printf( "[DEBUG STRING] -> \n\tString: %s\n\tLength: %d\n",
	  _ptr_string->buffer_mem_block_,
	  _ptr_string->buffer_mem_block_length_ );
}
