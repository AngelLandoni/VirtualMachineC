#include "../../include/tools/utilities.h"

char* bool_to_string( bool* _ptr_data ){
  if( *_ptr_data == 1 ) return "true";
  return "false";
}
