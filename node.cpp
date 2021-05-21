#include "node.h"
#include "gAll.h"
#include "symtab.h"
#include "opcodes.h"
#include "helper.h"
#include <iostream>
#include <vector>

using namespace std;

Node::Node(string name) : m_token(name)
{}

string Node::token() const
{
	return m_token;
}

void Node::set_token(const string& name)
{
	m_token = name;
}

void Node::visit(int depth) const
{
	for (int i=0; i < depth; ++i) {
		cout << "  ";
	}
	cout << m_token << endl;
	for (auto n: m_children) {
		n->visit(depth+1);
	}
}

void Node::add_child(Node* const kid)
{
	m_children.push_back(kid);
}

Constant::Constant(string name) : Node(name)
{}

int Constant::value() const
{
	return m_value;
}

void Constant::set_value(const int v) 
{
	m_value = v;
}

void Constant::visit(int depth) const
{
	for (int i=0; i < depth; ++i) {
		cout << "  ";
	}
	cout << m_token << "(" << m_value << ")" << endl;
	for (auto n: m_children) {
		n->visit(depth+1);
	}
}

Identifier::Identifier(string name) : Node(name)
{}

string Identifier::value() const
{
	return m_value;
}

void Identifier::set_value(const string& v) {
	m_value = v;
}

void Identifier::visit(int depth) const
{
	for (int i=0; i < depth; ++i) {
		cout << "  ";
	}
	cout << m_token << "(" << m_value << ")" << endl;
	for (auto n: m_children) {
		n->visit(depth+1);
	}
}
//help
int Node::generate_code(){
	if(m_token == "start"){
        jsr_abs(0xe544);
		if(m_children.size() == 1){
			m_children[0]->generate_code();
            //rts();
		}else{
			//error
		}
        rts();
    }else if(m_token == "starta"){
        if(m_children.size() == 0){
            return 0;
        }else if(m_children.size() == 1){
			m_children[0]->generate_code();
		}else if(m_children.size() == 2){
			m_children[0]->generate_code();
			m_children[1]->generate_code();
		}else{
			//error
		}

	}else if(m_token == "stmt"){
		if(m_children.size() == 1){
			int a = m_children[0]->generate_code();
            return a;
		}else{
			//error
		}
	}else if(m_token == "shape"){
        if(m_children.size() == 2){
            int x = m_children[0]->generate_code();
            int y = m_children[1]->generate_code();
            make_point(x,y);
        }else if(m_children.size() == 4){
            int tlx = m_children[0]->generate_code();
            int tly = m_children[1]->generate_code();
            int w = m_children[2]->generate_code();           
            int l = m_children[3]->generate_code();
            make_rect(tlx,tly,w,l);
        }else{
            //error
        }
	}else if(m_token == "postant"){
        if(m_children.size() == 0){
            Constant* c = dynamic_cast<Constant*>(this);
            if(c == NULL){
                //error
            }
            else{
                int c_val = c->value();
                int temp_c = slap.temporary();
                lda_imm(low(c_val));
                sta_abs(slap.address(temp_c));
                lda_imm(high(c_val));
                sta_abs(slap.address(temp_c)+1);
                return temp_c;
            }
        }else{
            //error
        }
    }else if(m_token == "value"){
        if(m_children.size() == 1){
            return m_children[0]->generate_code();
    
        }else{
            //error
        }
    }else if(m_token == "identifier"){
        if(m_children.size() == 0){
            Identifier* i = dynamic_cast<Identifier*>(this);
            if(i == NULL){
            }
            else if(slap.address_of(i->value()) != -1){
                //cerr << i->value() << " : FOUND" << endl;
                return slap.id_of(i->value());
            }
            else{
                //cerr << i->value() << " : NEW" << endl;
                string i_val = i->value();
                int temp_i = slap.add(i_val);
                return temp_i;
            }
        }else{
            //error
        }
	}else if(m_token == "iter"){
        if(m_children.size() == 2){
            int place = 0xc000+bytes.size();
            int start = m_children[0]->generate_code();
            ldy_abs(slap.address(start));
            bne(0xc000+bytes.size()+5);
            int end = bytes.size();
            jmp(end);
            int body = m_children[1]->generate_code();
            jmp(place);
            int endit = 0xc000 + bytes.size();
            bytes[end+1] = low(endit);
            bytes[end+2] = high(endit);
        }else{
            //error
        }
	}else if(m_token == "jump"){
        if(m_children.size() == 1){
            int to = m_children[0]->generate_code();
            jmp(slap.address(to));
        }else{
            //error
        }
	}else if(m_token == "jumpstart"){
        if(m_children.size()==1){
            int a = m_children[0]->generate_code();
            sta_abs(slap.address(a));
            sta_abs(slap.address(a)+1);
        }
        else{
            //error
        }
 	}else if(m_token == "select"){
        if(m_children.size() == 2){
            int cond = m_children[0]->generate_code();
            ldy_abs(slap.address(cond));
            bne(0xc000+bytes.size()+5);
            int place = bytes.size();
            jmp(place);
            int body = m_children[1]->generate_code();
            int ifend = 0xc000 + bytes.size();
            bytes[place+1] = low(ifend);
            bytes[place+2] = high(ifend);
        }else if(m_children.size() == 3){
            int cond = m_children[0]->generate_code();
            ldy_abs(slap.address(cond));
            bne(0xc000+bytes.size()+5);
            int place = bytes.size();
            jmp(place);
            m_children[1]->generate_code();
            int ifend = 0xc000 + bytes.size();
            bytes[place+1] = low(ifend);
            bytes[place+2] = high(ifend);
            beq(0xc000+bytes.size()+5);
            int place2 = bytes.size();
            jmp(place2);
            m_children[2]->generate_code();
            int elsend = 0xc000 + bytes.size();
            bytes[place2+1] = low(elsend);
            bytes[place2+2] = high(elsend);
        }else{
            //error
        }
	}else if(m_token == "assignment"){
		if(m_children.size() == 2){
            int id = m_children[0]->generate_code();
            int from = m_children[1]->generate_code();
            lda_abs(slap.address(from));
            sta_abs(slap.address(id));
            lda_abs(slap.address(from)+1);
            sta_abs(slap.address(id)+1);
        }else{
            //error
        }
	}else if(m_token == "bool"){
		if(m_children.size() == 1){
            int a = m_children[0]->generate_code();
            return a;
        }else{
            //error
        }
	}else if(m_token == "not"){
		if(m_children.size() == 1){
            m_children[0]->generate_code();
            return 0;
        }else{
            //error
        }
	}else if(m_token == "or"){
        if(m_children.size() == 2){
            m_children[0]->generate_code();
            m_children[1]->generate_code();
            return 0;
        }else{
            //error
        }
	}else if(m_token == "and"){
        if(m_children.size() == 2){
            m_children[0]->generate_code();
            m_children[1]->generate_code();
            return 0;
        }else{
            //error
        }

	}else if(m_token == "compa"){
		if(m_children.size() == 1){
            int a = m_children[0]->generate_code();
            return a;
        }else{
            //error
        }
	}else if(m_token == "eq"){
		if(m_children.size() == 2){
            int l = m_children[0]->generate_code();
            int r = m_children[1]->generate_code();
            int temp = slap.temporary();
            ldy_imm(1);
            lda_abs(slap.address(l));
            cmp_abs(slap.address(r));
            int equend = 0xc000+bytes.size()+4;
            beq(equend);
            ldy_imm(0);
            sty_abs(slap.address(temp));
            return temp;
        }else{
            //error
        }
	}else if(m_token == "gt"){
		if(m_children.size() == 2){
            int l = m_children[0]->generate_code();
            int r = m_children[1]->generate_code();
            int temp = slap.temporary();
            ldy_imm(1);
            lda_abs(slap.address(l));
            cmp_abs(slap.address(r));
            int equend = 0xc000+bytes.size()+4;
            bcs(equend);
            ldy_imm(0);
            sty_abs(slap.address(temp));
            return temp;
        }else{
            //error
        }
	}else if(m_token == "lt"){
		if(m_children.size() == 2){
            int l = m_children[0]->generate_code();
            int r = m_children[1]->generate_code();
            int temp = slap.temporary();
            ldy_imm(1);
            lda_abs(slap.address(l));
            cmp_abs(slap.address(r));
            int equend = 0xc000+bytes.size()+4;
            bcc(equend);
            ldy_imm(0);
            sty_abs(slap.address(temp));
            return temp;
        }else{
            //error
        }
	}else if(m_token == "arith"){
		if(m_children.size() == 1){
            int a = m_children[0]->generate_code();
            return a;
        }else{
            //error
        }
	}else if(m_token == "mult"){
        if(m_children.size() == 2){
            m_children[0]->generate_code();
            m_children[1]->generate_code();
            return 0;
        }else{
            //error
        }
	}else if(m_token == "div"){
        if(m_children.size() == 2){
            m_children[0]->generate_code();
            m_children[1]->generate_code();
            return 0;
        }else{
            //error
        }
	}else if(m_token == "mod"){
        if(m_children.size() == 2){
            m_children[0]->generate_code();
            m_children[1]->generate_code();
            return 0;
        }else{
            //error
        }
	}else if(m_token == "add"){
        if(m_children.size() == 2){
            int a = m_children[0]->generate_code();
            int b = m_children[1]->generate_code();
            add_variables(slap.address(b), slap.address(a));
            return a;
        }else{
            //error
        }
	}else if(m_token == "sub"){
		if(m_children.size() == 2){
            int a = m_children[0]->generate_code();
            int b = m_children[1]->generate_code();
            add_variables(slap.address(b), slap.address(a));
            return a;
        }else{
            //error
        }
	}else{
		//error
	}
    return 1;
}
