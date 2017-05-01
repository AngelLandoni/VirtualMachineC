#include "../include/compiler.h"

Compiler* new_compiler( void ){
  Compiler* newc = malloc( sizeof( Compiler ) );
  newc->handler_parser_ = new_parser(  );
  newc->bytecode_ = new_bvector(  );
  newc->bytecode_header_ = new_bytecodeheader(  );
  newc->errors_ = new_svector(  );
  return newc;
}

byte compiler_compile( Compiler* _ptr_compiler,char* _buffer ){
  parser_parse_file( _ptr_compiler->handler_parser_,_buffer );
  SVector* _ptr_parse_code = _ptr_compiler->handler_parser_->parse_code_;
  SVector* _ptr_functions_names_table = _ptr_compiler->handler_parser_->functions_names_table_;
  UIVector* _functions_names_table_ip = new_uivector(  );
  unsigned int i = 0,j = 0,
    bytes_counter = 0, /* For function table correction integer to bytes data */
    function_table_size = svector_get_size( _ptr_functions_names_table ),
    parse_code_size = svector_get_size( _ptr_parse_code );
  String* _ref_code;

  //To bytecode
  while( i<parse_code_size ){
    _ref_code = svector_at( _ptr_parse_code,i );

    if( string_cmp_text( _ref_code,STRING_MAIN ) ){
      bytecodeheader_set_entrypoint( _ptr_compiler->bytecode_header_,
				     bytes_counter );
      i++;
      continue;
    }

    /* BEGIN BPUSH */
    if( string_cmp_text( _ref_code,STRING_BPUSH ) ){
      bvector_push( _ptr_compiler->bytecode_,BPUSH );
      i++;
      _ref_code = svector_at( _ptr_parse_code,i );
      int selector = atoi( _ref_code->buffer_mem_block_ );
      bvector_push( _ptr_compiler->bytecode_,(char)selector );
      bytes_counter+=BYTESIZE_INTR_BPUSH;
      i++;
      continue;
    }
    /* END BPUSH */


    /* BEGIN PUSH */
    if( string_cmp_text( _ref_code,STRING_PUSH ) ){
      bvector_push( _ptr_compiler->bytecode_,PUSH );
      i++;
      _ref_code = svector_at( _ptr_parse_code,i );
      char memdir[4];
      int selector = -1;
      if( string_cmp_text( _ref_code,STRING_REGA ) ) selector = REGA;
      else if( string_cmp_text( _ref_code,STRING_REGB ) ) selector = REGB;
      else if( string_cmp_text( _ref_code,STRING_REGC ) ) selector = REGC;
      else if( string_cmp_text( _ref_code,STRING_REGD ) ) selector = REGD;
      // else is not a register,is a mem dir jaja

      memcpy( &memdir,&selector,4 );
      for( j=0;j<4;j++ )
	bvector_push( _ptr_compiler->bytecode_,memdir[j] );

      bytes_counter += BYTESIZE_INTR_PUSH;
      i++;
      continue;
    }
    /* END PUSH */

    // BEGIN BMOV
    if( string_cmp_text( _ref_code,STRING_BMOV ) ){
      bvector_push( _ptr_compiler->bytecode_,BMOV );
      // the two next instructions
      i++;
      _ref_code = svector_at( _ptr_parse_code,i );
      char memreg[4];
      int selector = -1;
      if( string_cmp_text( _ref_code,STRING_REGA ) ) selector = REGA;
      else if( string_cmp_text( _ref_code,STRING_REGB ) ) selector = REGB;
      else if( string_cmp_text( _ref_code,STRING_REGC ) ) selector = REGC;
      else if( string_cmp_text( _ref_code,STRING_REGD ) ) selector = REGD;
      // else is not a register,is a mem dir jaja

      memcpy( &memreg,&selector,4 );
      for( j=0;j<4;j++ )
	bvector_push( _ptr_compiler->bytecode_,memreg[j] );

      i++;
      _ref_code = svector_at( _ptr_parse_code,i );
      selector = atoi( _ref_code->buffer_mem_block_ );
      bvector_push( _ptr_compiler->bytecode_,(char)selector );

      bytes_counter += BYTESIZE_INTR_BMOV;
      i++;
      continue;
    }
    // END BMOV


    // BEGIN IMOV
    if( string_cmp_text( _ref_code,STRING_IMOV ) ){
      bvector_push( _ptr_compiler->bytecode_,IMOV );
      i++;
      _ref_code = svector_at( _ptr_parse_code,i );
      char memdir[4];
      int selector = -1;
      if( string_cmp_text( _ref_code,STRING_REGA ) ) selector = REGA;
      else if( string_cmp_text( _ref_code,STRING_REGB ) ) selector = REGB;
      else if( string_cmp_text( _ref_code,STRING_REGC ) ) selector = REGC;
      else if( string_cmp_text( _ref_code,STRING_REGD ) ) selector = REGD;
      

      memcpy( &memdir,&selector,4 );
      for( j=0;j<4;j++ )
	bvector_push( _ptr_compiler->bytecode_,memdir[i] );

      i++;
      _ref_code = svector_at( _ptr_parse_code,i );
      selector = atoi( _ref_code->buffer_mem_block_ );
      memset( &memdir,0,4 );
      memcpy( &memdir,&selector,4 );
      for( j=0;j<4;j++ )
	bvector_push( _ptr_compiler->bytecode_,memdir[j] );

      bytes_counter += BYTESIZE_INTR_IMOV;
      i++;
      continue;
    }
    // END IMOV

    /* BEGIN CMP */
    if( string_cmp_text( _ref_code,STRING_CMP ) ){
      bvector_push( _ptr_compiler->bytecode_,CMP );
      i++;
      _ref_code = svector_at( _ptr_parse_code,i );
      char memdir[4];
      int selector = -1;
      if( string_cmp_text( _ref_code,STRING_REGA ) ) selector = REGA;
      else if( string_cmp_text( _ref_code,STRING_REGB ) ) selector = REGB;
      else if( string_cmp_text( _ref_code,STRING_REGC ) ) selector = REGC;
      else if( string_cmp_text( _ref_code,STRING_REGD ) ) selector = REGD;
      else selector = string_to_int( _ref_code );

      i++;
      continue;
    }
    /* END CMP */

    /* BEGIN RET */
    if( string_cmp_text( _ref_code,STRING_RET ) ){
      bvector_push( _ptr_compiler->bytecode_,RET );
      bytes_counter+=BYTESIZE_INTR_RET;
      i++;
      continue;
    }
    /* END RET */

    // BEGIN HALT
    if( string_cmp_text( _ref_code,STRING_HALT ) ){
      bvector_push( _ptr_compiler->bytecode_,HALT );
      bytes_counter += BYTESIZE_INTR_HALT;
      i++;
      continue;
    }
    // END HALT


    // BEGIN CALL && JMP
    if( string_cmp_text( _ref_code,STRING_CALL ) ||
	string_cmp_text( _ref_code,STRING_JMP ) ){

      if( string_cmp_text( _ref_code,STRING_CALL ) )
	bvector_push( _ptr_compiler->bytecode_,CALL );
      else bvector_push( _ptr_compiler->bytecode_,JMP );

      i++;
      _ref_code = svector_at( _ptr_parse_code,i );
      char memdir[4];
      j = 0;
      while( j<function_table_size ){
	if( string_cmp( svector_at( _ptr_functions_names_table,j ),
			_ref_code ) ){
	  memcpy( &memdir,&j,4 );
	  for( j=0;j<4;j++ )
	    bvector_push( _ptr_compiler->bytecode_,memdir[j] );
	  break;
	}
	j++;
      }
      bytes_counter += BYTESIZE_INTR_CALL; /* The CALL byte size is equal to JMP */
      i++;
      continue;
    }
    // END CALL && JMP

    // BEGIN VM_STACK_DUMP
    if( string_cmp_text( _ref_code,STRING_VM_STACK_DUMP ) ){
      bvector_push( _ptr_compiler->bytecode_,VM_STACK_DUMP );
      bytes_counter += BYTESIZE_INTR_VM_STACK_DUMP;
      i++;
      continue;
    }
    // END VM_STACK_DUMP

    __compiler_function_correction( _ptr_functions_names_table,
				    _functions_names_table_ip,
				    function_table_size,
				    _ref_code,
				    bytes_counter );

    i+=1;
  }

  // Save the code size!.
  bytecodeheader_set_codesize( _ptr_compiler->bytecode_header_,
			       bytes_counter );


   __complier_replace_calldir( _ptr_compiler,_functions_names_table_ip );

#ifdef COMPILER_DEBUGMODE
   __compiler_dump_test( _ptr_compiler->bytecode_,
			 _ptr_functions_names_table );
   #endif

   uivector_delete( _functions_names_table_ip );

  return COMPILER_NOERROR;
}

void compiler_save_bytecode( Compiler* _ptr_compiler,char* _path_file ){
  char final_file[_ptr_compiler->bytecode_header_->code_size_+COMPILER_BYTECODE_HEADERSIZE];
  memcpy( &final_file[0],
	  &_ptr_compiler->bytecode_header_->code_size_,
	  4 );
  memcpy( &final_file[4],
	  &_ptr_compiler->bytecode_header_->entry_point_,
	  4 );
  memcpy( &final_file[8],
	  _ptr_compiler->bytecode_->mem_block_,
	  _ptr_compiler->bytecode_header_->code_size_ );


  file_save( _path_file,
	     _ptr_compiler->bytecode_header_->code_size_+COMPILER_BYTECODE_HEADERSIZE,
	     final_file );
}

void compiler_delete( Compiler* _ptr_compiler ){
  parser_delete( _ptr_compiler->handler_parser_ );
  bvector_delete( _ptr_compiler->bytecode_ );
  bytecodeheader_delete( _ptr_compiler->bytecode_header_ );
  svector_delete( _ptr_compiler->errors_ );
  free( _ptr_compiler );
}



void __compiler_function_correction( SVector* _ptr_functions_names_table,
				     UIVector* _functions_names_table_ip,
				     unsigned int _function_table_size,
				     String* _ref_code,
				     unsigned int _bytes_counter ){
  unsigned int j = 0;
  while( j<_function_table_size ){
    if( string_cmp( svector_at( _ptr_functions_names_table,j ),
		    _ref_code ) ){
      uivector_push( _functions_names_table_ip,_bytes_counter );
      break;
    }
    j++;
  }
}

void __compiler_dump_test( BVector* _ptr_bytecode,SVector* _ptr_table ){
  bvector_dump( _ptr_bytecode );
  svector_dump( _ptr_table );
}

void __complier_replace_calldir( Compiler* _ptr_compiler,
				 UIVector* _ptr_table_id ){
  unsigned int bytecode_size = bvector_get_size( _ptr_compiler->bytecode_ ),
    i = 0,j=0;
  while( i<bytecode_size ){
    if( bvector_cmp_at( _ptr_compiler->bytecode_,i,CALL ) ||
	bvector_cmp_at( _ptr_compiler->bytecode_,i,JMP ) ){
      char memdir[4];
      i++;
      for( j=0;j<4;j++ )
	memdir[j] = bvector_at( _ptr_compiler->bytecode_,i+j );
      memcpy( &j,&memdir,4 );
      j = uivector_at( _ptr_table_id,j );
      memcpy( &memdir,&j,4 );
      bvector_write( _ptr_compiler->bytecode_,i,memdir );
      i+=3;
    }
    i++;
  }
}
