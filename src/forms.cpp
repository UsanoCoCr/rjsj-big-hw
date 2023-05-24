#include "./forms.h"
#include "./value.h"
#include "./value.h"
#include "./error.h"
#include <iostream>
#include <vector>
#include <string>

const std::unordered_map<std::string, SpecialFormType*> special_forms = {
    {"define", defineForm}
};

ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& Env){
    if(auto name = args[0]->asSymbol()){
        Env.env[*name] = Env.eval(args[1]);
        return std::make_shared<NilValue>();    
    }
    else{
        throw LispError("Unimplemented");
    }
}