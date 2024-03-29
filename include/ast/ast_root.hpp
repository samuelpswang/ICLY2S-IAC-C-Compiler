#ifndef compiler_ast_root
#define compiler_ast_root

#include "ast.hpp"

// use this to point at function declarations & globals later on 
class Root: public Node {
public:
    Root(Node* expr_list){
        this->type="";
        this->name="";
        this->val="";
        this->exprs = {expr_list};
        this->stats = {};
    }

    void print(std::ostream& os,const std::string& indent)const{
        for(int i = 0; i<(this->exprs).size(); i++){
            (this->exprs)[i]->print(os,"");
            os<<std::endl;
        }
    }

    void compile(std::ostream& os,const std::string& dest,MemoryContext& m)const{
        os << ".text" << std::endl;
        os<< ".globl "<<this->exprs[this->exprs.size()-1]->get_name()<<std::endl;
        os<<std::endl;
        for(int i = 0; i<(this->exprs).size(); i++){
            (this->exprs)[i]->compile(os,dest,m);
        }
    }
};

#endif
