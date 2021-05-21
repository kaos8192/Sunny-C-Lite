#include "gAll.h"
#include "helper.h"
#include "opcodes.h"
#include "symtab.h"

using namespace std;

int add(int x, int y, SymbolTable sym){
	//symtab look up for address
	int w = sym.address(x);
	int z = sym.address(y);
	add_variables(w,z);
	return 0;
}

int sub(int x, int y, SymbolTable sym){
	int a = sym.address(x);
	int b = sym.address(y);
	sub_variables(a,b);
	return 0;
}
