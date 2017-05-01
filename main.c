#include <stdio.h>

#include "include/compiler.h"
#include "include/virtualmachine.h"
#include "include/tools/stack.h"

int main( int argc,char** argv ){
  Compiler* _comp = new_compiler(  );
  compiler_compile( _comp,"tests/file.txt" );
  compiler_save_bytecode( _comp,"tests/bytecode.bin" );
  compiler_delete( _comp );

  VM* _vm = new_vm(  );
  vm_load_bytecode( _vm,"tests/bytecode.bin" );
  vm_init( _vm );
  vm_run( _vm );
  vm_delete( _vm );
}
