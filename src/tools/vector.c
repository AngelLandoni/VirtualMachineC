#include "../../include/tools/vector.h"

void ivector_show_info( IVector* _ptr_vector ){
  printf( "[?] Integer Vector Info\n\t \
           [->] Memory size: %d\n\t \
           [->] Iterator: %d\n\t \
           [->] Is blocked: %s\n",
           _ptr_vector->mem_size_,
          _ptr_vector->iterator_,
          bool_to_string( &_ptr_vector->is_locked_ ) );
}

void ivector_dump( IVector* _ptr_vector ){
  unsigned int i=0;
  printf( "[" );
  while( i<_ptr_vector->iterator_ ){
    if( i==0 ){
      printf( "%d",_ptr_vector->mem_block_[i] );
      i++;
      continue;
    }
    printf( ",%d",_ptr_vector->mem_block_[i] );
    i++;
  }
  printf( "]\n" );
}

IVector* new_ivector( void ){
  IVector* obj = malloc( sizeof( IVector ) );
  obj->mem_block_ = malloc( sizeof( int )*VECTOR_START_SIZE );
  obj->mem_size_ = VECTOR_START_SIZE;
  obj->iterator_ = 0;
  obj->is_locked_ = false;
  return obj;
}

void ivector_delete( IVector* _ptr_vector ){
  if( _ptr_vector->mem_block_ != NULL )
    free( _ptr_vector->mem_block_ );
  free( _ptr_vector );
}

byte ivector_push( IVector* _ptr_vector,int _item ){
  if( _ptr_vector->is_locked_ == true ) return VECTOR_ERROR_LOCKED;

  if( _ptr_vector->iterator_-1 >= _ptr_vector->mem_size_ &&
  _ptr_vector->iterator_ != 0 ){
    _ptr_vector->mem_size_*=VECTOR_SCALE_CONSTANT;
    _ptr_vector->mem_block_ = realloc( _ptr_vector->mem_block_,
                                       sizeof( int ) * _ptr_vector->mem_size_ );
  }
  _ptr_vector->mem_block_[_ptr_vector->iterator_] = _item;
  _ptr_vector->iterator_+=1;
  return VECTOR_NOERROR;
}

unsigned int ivector_erase( IVector* _ptr_vector,unsigned int _position ){
  if( _ptr_vector->is_locked_ == true ) return VECTOR_ERROR_LOCKED;
  
  if( _position >= _ptr_vector->iterator_ )
    return VECTOR_ERROR_OUTOFMEMORY;

  unsigned int size_diference = sizeof( int )*_ptr_vector->iterator_-_position;
  int * mem_trash = malloc( size_diference );
  memcpy( mem_trash,&_ptr_vector->mem_block_[_position+1],size_diference );
  memcpy( &_ptr_vector->mem_block_[_position],mem_trash,size_diference );
  free( mem_trash );

  _ptr_vector->iterator_-=1;
  return VECTOR_NOERROR;
}

int ivector_at( IVector* _ptr_vector,unsigned int _position ){
  if( _position >= _ptr_vector->iterator_ )
    return _ptr_vector->mem_block_[_ptr_vector->iterator_-1];
  return _ptr_vector->mem_block_[_position];
}

byte ivector_find( IVector* _ptr_vector,int* _ref_response,int _number ){
  unsigned int i=0;
  while( i<_ptr_vector->iterator_ ){
    if( _ptr_vector->mem_block_[i] == _number ){
      *_ref_response = i;
      return VECTOR_ERROR_FOUND;
    }
    i++;
  }
  return VECTOR_NOERROR;
}

void ivector_lock( IVector* _ptr_vector ){
  _ptr_vector->is_locked_ = true;
}

void ivector_unlock( IVector* _ptr_vector ){
  _ptr_vector->is_locked_ = false;
}

/* ------------------------------------------------------------------
   | Unsigned integer vector
   ------------------------------------------------------------------ */

void uivector_dump( UIVector* _ptr_vector ){
  unsigned int i=0;
  printf( "[" );
  while( i<_ptr_vector->iterator_ ){
    if( i==0 ){
      printf( "%d",_ptr_vector->mem_block_[i] );
      i++;
      continue;
    }
    printf( ",%d",_ptr_vector->mem_block_[i] );
    i++;
  }
  printf( "]\n" );
  
}

UIVector* new_uivector( void ){
  UIVector* nuiv = malloc( sizeof( UIVector ) );
  nuiv->mem_block_ = calloc( VECTOR_START_SIZE,sizeof( unsigned int ) );
  nuiv->mem_size_ = VECTOR_START_SIZE;
  nuiv->iterator_ = 0;
  nuiv->is_locked_ = false;
  return nuiv;
}

void uivector_delete( UIVector* _ptr_vector ){
  if( _ptr_vector->mem_block_ != NULL )
    free( _ptr_vector->mem_block_ );
  free( _ptr_vector );
}

byte uivector_push( UIVector* _ptr_vector,unsigned int _item ){
  if( _ptr_vector->is_locked_ == true ) return VECTOR_ERROR_LOCKED;

  if( _ptr_vector->iterator_-1 >= _ptr_vector->mem_size_ &&
  _ptr_vector->iterator_ != 0 ){
    _ptr_vector->mem_size_*=VECTOR_SCALE_CONSTANT;
    _ptr_vector->mem_block_ = realloc( _ptr_vector->mem_block_,
                                       sizeof( unsigned int ) * _ptr_vector->mem_size_ );
  }
  _ptr_vector->mem_block_[_ptr_vector->iterator_] = _item;
  _ptr_vector->iterator_+=1;
  return VECTOR_NOERROR;
}

unsigned int uivector_erase( UIVector* _ptr_vector,unsigned int _position ){
  if( _ptr_vector->is_locked_ == true ) return VECTOR_ERROR_LOCKED;
  
  if( _position >= _ptr_vector->iterator_ )
    return VECTOR_ERROR_OUTOFMEMORY;

  unsigned int size_diference = sizeof( unsigned int )*_ptr_vector->iterator_-_position;
  int * mem_trash = malloc( size_diference );
  memcpy( mem_trash,&_ptr_vector->mem_block_[_position+1],size_diference );
  memcpy( &_ptr_vector->mem_block_[_position],mem_trash,size_diference );
  free( mem_trash );

  _ptr_vector->iterator_-=1;
  return VECTOR_NOERROR;
}

unsigned int uivector_at( UIVector* _ptr_vector,unsigned int _position ){
  if( _position >= _ptr_vector->iterator_ )
    return _ptr_vector->mem_block_[_ptr_vector->iterator_-1];
  return _ptr_vector->mem_block_[_position];
}

byte uivector_add_at( UIVector* _ptr_vector,unsigned int _position,unsigned int _data ){
  if( _position >= _ptr_vector->iterator_ )
    return VECTOR_ERROR_OUTOFMEMORY;
  _ptr_vector->mem_block_[_position] += _data;
  return VECTOR_NOERROR;
}

byte uivector_find( UIVector* _ptr_vector,unsigned int* _ref_response,unsigned int _number ){
  unsigned int i=0;
  while( i<_ptr_vector->iterator_ ){
    if( _ptr_vector->mem_block_[i] == _number ){
      *_ref_response = i;
      return VECTOR_ERROR_FOUND;
    }
    i++;
  }
  return VECTOR_NOERROR;
}

void uivector_lock( UIVector* _ptr_vector ){
  _ptr_vector->is_locked_ = true;
}

void uivector_unlock( UIVector* _ptr_vector ){
  _ptr_vector->is_locked_ = false;
}

/* ------------------------------------------------------------------
   | Byte vector                                                    |
   ------------------------------------------------------------------ */

void bvector_show_info( BVector* _ptr_vector ){
  printf( "[?] Byte Vector Info\n\t \
           [->] Memory size: %d\n\t \
           [->] Iterator: %d\n\t \
           [->] Is blocked: %s\n",
           _ptr_vector->mem_size_,
          _ptr_vector->iterator_,
          bool_to_string( &_ptr_vector->is_locked_ ) );
  
}

void bvector_dump( BVector* _ptr_vector ){
  unsigned int i=0;
  printf( "[" );
  fflush(stdout);
  while( i<_ptr_vector->iterator_ ){
    if( i == 0 ){
      printf( "(%d|%c)",_ptr_vector->mem_block_[i],_ptr_vector->mem_block_[i] );
      fflush(stdout);
      i++;
      continue;
    }
    printf( ",(%d|%c)",_ptr_vector->mem_block_[i],_ptr_vector->mem_block_[i] );
    fflush(stdout);
    i++;
  }
  printf( "]" );
  fflush(stdout);
}

BVector* new_bvector( void ){
  BVector* obj = malloc( sizeof( BVector ) );
  obj->mem_block_ = malloc( sizeof( byte )*VECTOR_START_SIZE );
  obj->mem_size_ = VECTOR_START_SIZE;
  obj->iterator_ = 0;
  obj->is_locked_ = false;
  return obj;
}

void bvector_delete( BVector* _ptr_vector ){
  free( _ptr_vector->mem_block_ );
  free( _ptr_vector );
}

byte bvector_push( BVector* _ptr_vector,byte _item ){
  if( _ptr_vector->is_locked_ == true ) return VECTOR_ERROR_LOCKED;
  
   if( _ptr_vector->iterator_-1 >= _ptr_vector->mem_size_ &&
  _ptr_vector->iterator_ != 0 ){
    _ptr_vector->mem_size_*=VECTOR_SCALE_CONSTANT;
    _ptr_vector->mem_block_ = realloc( _ptr_vector->mem_block_,
                                       _ptr_vector->mem_size_ );
  }
  _ptr_vector->mem_block_[_ptr_vector->iterator_] = _item;
  _ptr_vector->iterator_+=1;

  return VECTOR_NOERROR;
}

byte bvector_write( BVector* _ptr_vector,unsigned int _position,char* _buffer ){
  if( _position >= _ptr_vector->iterator_ ) return VECTOR_ERROR_OUTOFMEMORY;
  strcpy( &_ptr_vector->mem_block_[_position],_buffer );
  return VECTOR_NOERROR;
}

byte bvector_erase( BVector* _ptr_vector,unsigned int _position ){
  if( _ptr_vector->is_locked_ == true ) return VECTOR_ERROR_LOCKED;
  
  if( _position >= _ptr_vector->iterator_ )
    return VECTOR_ERROR_OUTOFMEMORY;

  unsigned int size_diference = _ptr_vector->iterator_-_position;
  byte* mem_trash = malloc( size_diference );
  memcpy( mem_trash,&_ptr_vector->mem_block_[_position+1],size_diference );
  memcpy( &_ptr_vector->mem_block_[_position],mem_trash,size_diference );
  free( mem_trash );
  _ptr_vector->iterator_-=1;
  return VECTOR_NOERROR;
}

byte bvector_at( BVector* _ptr_vector,unsigned int _position ){
  if( _position >= _ptr_vector->iterator_ )
    return _ptr_vector->mem_block_[_ptr_vector->iterator_-1];
  return _ptr_vector->mem_block_[_position];
}

bool bvector_cmp_at( BVector* _ptr_vector,unsigned int _position,byte _data ){
  if( _ptr_vector->mem_block_[_position] == _data ) return true;
  return false;
}

unsigned int bvector_get_size( BVector* _ptr_vector ){
  return _ptr_vector->iterator_;
}

byte bvector_find( BVector* _ptr_vector,unsigned int* _ref_response,byte _data ){
  unsigned int i=0;
  while( i<_ptr_vector->iterator_ ){
    if( _ptr_vector->mem_block_[i] == _data ){
      *_ref_response = i;
      return VECTOR_ERROR_FOUND;
    }
    i++;
  }
  return VECTOR_NOERROR;
}

void bvector_lock( BVector* _ptr_vector ){
  _ptr_vector->is_locked_ = true;
}

void bvector_unlock( BVector* _ptr_vector ){
  _ptr_vector->is_locked_ = false;
}

/* ------------------------------------------------------------------
   | String vector                                                  |
   ------------------------------------------------------------------ */

void svector_debug( SVector* _ptr_vector ){
  
}

void svector_dump( SVector* _ptr_vector ){
  printf( "[SVECTOR]: [ " );
  int i = 0;
  for( i=0;i<_ptr_vector->iterator_;i++ ){
    if( i == 0 ) printf( "{%s}",_ptr_vector->mem_block_[i].buffer_mem_block_ );
    else printf( ",{%s}",_ptr_vector->mem_block_[i].buffer_mem_block_ );
  }
  printf(" ]\n");
}

SVector* new_svector( void ){
  SVector* temp_vector = malloc( sizeof( SVector ) );
  temp_vector->mem_block_ = calloc( VECTOR_START_SIZE,sizeof( String ) );
  temp_vector->mem_size_ = VECTOR_START_SIZE;
  temp_vector->iterator_ = 0;
  temp_vector->is_locked_ = false;
  return temp_vector;
}

void svector_push( SVector* _ptr_vector,String* _ptr_buffer ){
  if( _ptr_vector->is_locked_ == true ) return;
  if( _ptr_vector->iterator_+1 >= _ptr_vector->mem_size_ ){
    String* new_mem = calloc( _ptr_vector->mem_size_*VECTOR_SCALE_CONSTANT,sizeof( String ) );
    memcpy( new_mem,_ptr_vector->mem_block_,_ptr_vector->mem_size_*sizeof( String ) );
    free( _ptr_vector->mem_block_ );
    _ptr_vector->mem_block_ = new_mem;
    _ptr_vector->mem_size_+=VECTOR_SCALE_CONSTANT;
  }
  string_copy( &_ptr_vector->mem_block_[_ptr_vector->iterator_],_ptr_buffer );
  _ptr_vector->iterator_ += 1;
}

void svector_push_text( SVector* _ptr_vector,char* _buffer ){
  if( _ptr_vector->is_locked_ == true ) return;
  if( _ptr_vector->iterator_+1 >= _ptr_vector->mem_size_ ){
    String* new_mem = calloc( _ptr_vector->mem_size_*VECTOR_SCALE_CONSTANT,sizeof( String ) );
    memcpy( new_mem,_ptr_vector->mem_block_,_ptr_vector->mem_size_*sizeof( String ) );
    free( _ptr_vector->mem_block_ );
    _ptr_vector->mem_block_ = new_mem;
    _ptr_vector->mem_size_+=VECTOR_SCALE_CONSTANT;
  }
  string_set( &_ptr_vector->mem_block_[_ptr_vector->iterator_],_buffer );
  _ptr_vector->iterator_ += 1;
}

byte svector_erase( SVector* _ptr_vector,unsigned int _position ){
  if( _ptr_vector->is_locked_ == true ) return VECTOR_ERROR_LOCKED;
  
  if( _position >= _ptr_vector->iterator_ )
    return VECTOR_ERROR_OUTOFMEMORY;

  String* memblock = string_alloc( _ptr_vector->mem_size_-_position );
  memcpy( memblock,
	  &_ptr_vector->mem_block_[_position+1],
	  _ptr_vector->mem_size_-_position );
  memcpy( &_ptr_vector->mem_block_[_position],
	  memblock,
	  _ptr_vector->mem_size_-_position );
  free( memblock );
  _ptr_vector->iterator_ -= 1;
  
  return VECTOR_NOERROR;
}

String* svector_at( SVector* _ptr_vector,unsigned int _position ){
  if( _ptr_vector->is_locked_ == true ) return NULL;
  return &_ptr_vector->mem_block_[_position];
}

unsigned int svector_get_size( SVector* _ptr_vector ){
  return _ptr_vector->iterator_;
}

void svector_delete( SVector* _ptr_svector ){
  free( _ptr_svector->mem_block_ );
  free( _ptr_svector );
}

void svector_ref_delete( SVector* _ptr_svector ){
  free( _ptr_svector->mem_block_ );
}
