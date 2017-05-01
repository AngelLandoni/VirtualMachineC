#include "../../include/tools/file.h"


File* new_file( char* _path_file ){
  if( _path_file == NULL )
    return NULL;

  // File to load memory
  FILE *file;
  // File to return
  File *toreturn_file = malloc( sizeof( File ) );
  // file_len contain the length of file
  unsigned long file_len = 0;
  
  file = fopen( _path_file, "rb" );

  fseek( file, 0, SEEK_END );
  file_len = ftell( file );
  fseek( file, 0, SEEK_SET );

  toreturn_file->mem_block_ = malloc( file_len+1 );
  if ( !toreturn_file->mem_block_ ){
    fclose( file );
    return NULL;
  }

  fread( toreturn_file->mem_block_, file_len, 1, file );
  fclose( file );

  toreturn_file->mem_block_[file_len] = '\0';
  toreturn_file->mem_block_size_ = file_len;
  toreturn_file->path_file_ = _path_file;
  
  return toreturn_file;
}

void file_delete( File* _ptr_file ){
  if( _ptr_file->mem_block_ != NULL )
    free( _ptr_file->mem_block_ );
  free( _ptr_file );
}

byte* file_get_buffer( File* _ptr_file ){
  if( _ptr_file->mem_block_ == NULL )
    return NULL;
  byte* copy_file_mem = malloc( _ptr_file->mem_block_size_ );
  memcpy( copy_file_mem,_ptr_file->mem_block_,_ptr_file->mem_block_size_ );
  return copy_file_mem;
}

unsigned int file_get_size( File* _ptr_file ){
  return _ptr_file->mem_block_size_;
}

void file_save( char* _path_file,unsigned int _length,char* _data ){
  FILE *file = fopen( _path_file, "wb" );
  fwrite( _data,_length,1,file );
  fclose( file );
}
