#include "./forms.h"
#include "./value.h"
#include "./value.h"
#include "./error.h"
#include <iostream>
#include <vector>
#include <cstring>

const std::unordered_map<std::string, SpecialFormType*> special_forms = {
    {"define", defineForm},
    {"quote", quoteForm},
    {"if", ifForm},
    {"and", andForm},
    {"or", orForm},
    {"lambda", lambdaForm}
};

ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& Env){
    if(args[0]->isSymbol() == true){
        if(auto name = args[0]->asSymbol()){
            Env.env[*name] = Env.eval(args[1]);
            return std::make_shared<NilValue>();    
        }
        else{
            throw LispError("Unimplemented");
        }
    }
    else if(args[0]->isList() == true){
        if(auto name = dynamic_cast<PairValue&>(*args[0]).carValue()->asSymbol()){
            std::vector<std::string> params{};
            std::vector<ValuePtr> temp = dynamic_cast<PairValue&>(*args[0]).cdrValue()->toVector();
            for(int i = 0; i < temp.size(); i++){
                if(auto name = temp[i]->asSymbol()){
                    params.push_back(*name);
                }
                else{
                    throw LispError("Unimplemented");
                }
            }
            std::vector<ValuePtr> body = dynamic_cast<PairValue&>(*args[1]).toVector();
            Env.env[*name] = std::make_shared<LambdaValue>(params, body);
            return std::make_shared<NilValue>();
        }
        else{
            throw LispError("Unimplemented");
        }
    }
    else{
        throw LispError("Unimplemented");
    }   
}
ValuePtr quoteForm(const std::vector<ValuePtr>& params, EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("Wrong number of arguments");
    }
    return params[0];
}
ValuePtr ifForm(const std::vector<ValuePtr>& params, EvalEnv& Env){
    if(params.size() != 3){
        throw LispError("Wrong number of arguments");
    }
    if(strcmp(Env.eval(params[0])->toString().c_str(), "#f") == 0){
        return Env.eval(params[2]);
    }
    else{
        return Env.eval(params[1]);
    }
}
ValuePtr andForm(const std::vector<ValuePtr>& params, EvalEnv& Env){
    if(params.size() == 0){
        return std::make_shared<BooleanValue>(true);
    }
    else{
        for(int i = 0; i < params.size(); i++){
            if(strcmp(Env.eval(params[i])->toString().c_str(), "#f") == 0){
                return std::make_shared<BooleanValue>(false);
            }
            Env.eval(params[i]);
        }
        return Env.eval(params[params.size() - 1]);
    }
}
ValuePtr orForm(const std::vector<ValuePtr>& params, EvalEnv& Env){
    if(params.size() == 0){
        return std::make_shared<BooleanValue>(false);
    }
    else{
        for(int i = 0; i < params.size(); i++){
            if(strcmp(params[i]->toString().c_str(), "#f") != 0){
                return Env.eval(params[i]);
            }
        }
        return std::make_shared<BooleanValue>(false);
    }
}
ValuePtr lambdaForm(const std::vector<ValuePtr>& params, EvalEnv& Env){

    LambdaValue* lambda = new LambdaValue();
    return std::make_shared<LambdaValue>(*lambda);
}