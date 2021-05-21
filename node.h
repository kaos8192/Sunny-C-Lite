#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include "symtab.h"

extern SymbolTable slap;
extern std::vector<int> bytes;
extern LabelTable lit;
using namespace std;
//help
class Node {
   protected:
      string m_token;
      vector<Node *> m_children;
   public:
      Node(string name);
      string token() const;
      void set_token(const string& name);
      virtual void visit(int depth) const;
      void add_child(Node* const kid);
      int generate_code();
};

class Constant  : public Node {
   protected:
      int m_value;
   public:
      Constant(string name);
      int value() const;
      void set_value(const int v);
      void visit(int depth) const;
};

class Identifier : public Node {
   protected:
      string m_value;
   public:
      Identifier(string name);
      string value() const;
      void set_value(const string& v);
      void visit(int depth) const;
};

#endif //NODE_H
