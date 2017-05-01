CC = clang
COPTIONS = -c -o

EXECNAME = vm

BINRELEASEDIR = bin/
OBJDIR = obj/

INCLUDEDIR = include/
INCLUDEDIR_TOOLS = include/tools/

SRCDIR = src/
SRCDIR_TOOLS = src/tools/

OBJ = main.o parser.o compiler.o bytecode.o virtualmachine.o string.o file.o utilities.o vector.o stack.o 
OBJINDIR = obj/*.o

vm: $(OBJ)
	$(CC) $(CFLAGS) $(OBJINDIR) -o $(BINRELEASEDIR)$(EXECNAME)

# THE MAIN FILE!
main.o: main.c
	$(CC) $(CFLAGS) main.c $(COPTIONS) $(OBJDIR)main.o

# VM FILES ########################################################
# PARSER.H COMPILER.H
#
###################################################################
parser.o: $(SRCDIR)parser.c $(INCLUDEDIR)parser.h
	$(CC) $(CFLAGS) $(SRCDIR)parser.c $(COPTIONS) $(OBJDIR)parser.o

compiler.o: $(SRCDIR)compiler.c $(INCLUDEDIR)compiler.h
	$(CC) $(CFLAGS) $(SRCDIR)compiler.c $(COPTIONS) $(OBJDIR)compiler.o

bytecode.o: $(SRCDIR)bytecode.c $(INCLUDEDIR)bytecode.h
	$(CC) $(CFLAGS) $(SRCDIR)bytecode.c $(COPTIONS) $(OBJDIR)bytecode.o

virtualmachine.o: $(SRCDIR)virtualmachine.c $(INCLUDEDIR)virtualmachine.h
	$(CC) $(CFLAGS) $(SRCDIR)virtualmachine.c $(COPTIONS) $(OBJDIR)virtualmachine.o


# TOOLS FOLDER ####################################################
# UTILITIES.H VECTOR.H FILE.H STRING.H
#
###################################################################
utilities.o: $(SRCDIR_TOOLS)utilities.c $(INCLUDEDIR_TOOLS)utilities.h
	$(CC) $(CFLAGS) $(SRCDIR_TOOLS)utilities.c $(COPTIONS) $(OBJDIR)utilities.o

vector.o: $(SRCDIR_TOOLS)vector.c $(INCLUDEDIR_TOOLS)vector.h
	$(CC) $(CFLAGS) $(SRCDIR_TOOLS)vector.c $(COPTIONS) $(OBJDIR)vector.o

file.o: $(SRCDIR_TOOLS)file.c $(INCLUDEDIR_TOOLS)file.h
	$(CC) $(CFLAGS) $(SRCDIR_TOOLS)file.c $(COPTIONS) $(OBJDIR)file.o

string.o: $(SRCDIR_TOOLS)string.c $(INCLUDEDIR_TOOLS)string.h
	$(CC) $(CFLAGS) $(SRCDIR_TOOLS)string.c $(COPTIONS) $(OBJDIR)string.o

stack.o: $(SRCDIR_TOOLS)stack.c $(INCLUDEDIR_TOOLS)stack.h
	$(CC) $(CFLAGS) $(SRCDIR_TOOLS)stack.c $(COPTIONS) $(OBJDIR)stack.o
