#include "generator.h"
#include "symtab.h"
#include "node.h"

using namespace std;

void Code_Vect::STA_constant(int constant){
	code.push_back(169);
	code.push_back(constant);
}

void Code_Vect::LDA_constant(int constant){
	code.push_back(169);
	code.push_back(constant);
}

int Code_Vect::get_size(){
	return code.size();
}

/*vector<int> CPX_constant(int constant){
	vector<int> bytes;
	if(){
			
	}
	return bytes;
}*/

//void generate_code(){
//	
//}

//vector<int> ADC(){
//	
//}

//vector<int> SBC(){
//	
//}

//vector<int> LDA_variable(int var){
//	return var;
//}

//rts(){
//return arg
//}
