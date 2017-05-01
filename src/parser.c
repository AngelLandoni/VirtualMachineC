#include "../include/parser.h"

Parser* new_parser(  ){
  Parser* temp_parser = malloc( sizeof( Parser ) );
  temp_parser->path_to_file_ = new_string( "" );
  temp_parser->parse_code_ = new_svector(  );
  temp_parser->functions_names_table_ = new_svector(  );
  temp_parser->file_handler_ = NULL;
  return temp_parser;
}

byte parser_parse_file( Parser* _ptr_parser,char* _path_to_file ){
  _ptr_parser->file_handler_ = new_file( _path_to_file );
  string_set( _ptr_parser->path_to_file_,_path_to_file );
  char * buffer_file = file_get_buffer( _ptr_parser->file_handler_ );
  unsigned int file_size = file_get_size( _ptr_parser->file_handler_ ),
    i = 0, j = 0, c = 0, num_functions = 0;

  while( i<file_size ){
    if( PARSER_ALL_TOKENS( buffer_file ) ){
      if( i-j == 0 ){
	i+=1;
	j++;
	continue;
      }
      char* strcontainer = calloc( i-j,1 );
      memcpy( strcontainer,&buffer_file[j],i-j );
      if( buffer_file[i] == PARSER_TOKEN_COLON &&
	  strcmp( strcontainer,PARSER_TOKEN_MAIN ) )
	svector_push_text( _ptr_parser->functions_names_table_,
			   strcontainer );
      c++;
      svector_push_text( _ptr_parser->parse_code_,strcontainer );
      free( strcontainer );
      i+=1;
      j=i;
      continue;
    }
    i++;
  }

#ifdef PARSER_DEBUGMODE
  svector_dump( _ptr_parser->functions_names_table_ );
  #endif

  return PARSER_NOERROR;  
}

byte parser_parse_text( Parser* _ptr_parser,char* _path_to_file ){
  printf( "\nPARSER_PARSE_TEXT is't developed.\n" );
  return PARSER_NOERROR;
}

void parser_delete( Parser* _ptr_parser ){
  free( _ptr_parser->path_to_file_ );
  svector_delete( _ptr_parser->parse_code_ );
  file_delete( _ptr_parser->file_handler_ );
}
