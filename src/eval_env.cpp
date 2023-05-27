#include "./eval_env.h"
#include "./error.h"
#include "./value.h"
#include "./builtins.h"
#include "./forms.h"
#include <iostream>
#include <vector>
#include <memory>
#include <iterator>
#include <algorithm>

using namespace std::literals;

ValuePtr EvalEnv::eval(ValuePtr expr) {
    if (expr->isSelfEvaluating()) {
        return expr;
    } 
    else if (expr->isNil()) {
        throw LispError("Evaluating nil is prohibited.");
    } 
    else if (expr->isList()){
        std::vector<ValuePtr> v = dynamic_cast<PairValue&>(*expr).toVector();
        PairValue* expr_ptr = dynamic_cast<PairValue*>(expr.get());
        if(auto name = expr_ptr->carValue()->asSymbol()){
            if(special_forms.find(*name) != special_forms.end()){
                return special_forms.at(*name)(expr_ptr->cdrValue()->toVector(), *this);
            }
            else{
                ValuePtr proc = this->eval(v[0]);
                std::vector<ValuePtr> args = this->evalList(dynamic_cast<PairValue&>(*expr).cdrValue());
                return this->apply(proc, args);
            }
        } 
    }
    else if (expr->isSymbol()){
        if(auto name = expr->asSymbol()){
            if(env.find(*name) != env.end()){
                return env[*name];
            }
            else if(parent != nullptr){
                return parent->lookupBinding(*name);
            } 
            else{
                throw LispError("Variable " + *name + " not defined.");
            }
        }
    }
    else {
        throw LispError("Unimplemented");
    }
}

EvalEnv::EvalEnv() {
    parent = nullptr;
    add_builtins();
    for (auto& [name, proc] : total_env) {
        env[name] = proc;
    } 
}

std::vector<ValuePtr> EvalEnv::evalList(ValuePtr expr) {
    std::vector<ValuePtr> result;
    std::ranges::transform(expr->toVector(),
                           std::back_inserter(result),
                           [this](ValuePtr v) { return this->eval(v); });
    return result;
}

ValuePtr EvalEnv::apply(ValuePtr proc, std::vector<ValuePtr> args) {
    if (typeid(*proc) == typeid(BuiltinProcValue)) {
        return dynamic_cast<BuiltinProcValue&>(*proc).func(args);
    } 
    else{
        throw LispError("Unimplemented");
    }
}

ValuePtr EvalEnv::lookupBinding(std::string name) {
    if (env.find(name) != env.end()) {
        return env[name];
    } 
    else if (parent != nullptr) {
        return parent->lookupBinding(name);
    } 
    else {
        throw LispError("Unbound variable: " + name);
    }
}

void EvalEnv::defineBinding(std::vector<std::string> names, std::vector<ValuePtr> values) {
    if (names.size() != values.size()) {
        throw LispError("Wrong number of arguments");
    }
    for (int i = 0; i < names.size(); i++) {
        env[names[i]] = values[i];
    }
}

std::shared_ptr<EvalEnv> EvalEnv::createGlobal() {
    std::shared_ptr<EvalEnv> global(new EvalEnv());
    global->parent = nullptr;
    return global;
}