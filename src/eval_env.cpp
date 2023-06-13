#include "./eval_env.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

#include "./builtins.h"
#include "./error.h"
#include "./forms.h"
#include "./value.h"

using namespace std::literals;

ValuePtr EvalEnv::eval(ValuePtr expr) {
    if (expr->isSelfEvaluating()) {
        return expr;
    } else if (expr->isNil()) {
        throw LispError("Evaluating nil is prohibited.");
    } else if (expr->isList()) {
        std::vector<ValuePtr> v = dynamic_cast<PairValue&>(*expr).toVector();
        PairValue* expr_ptr = dynamic_cast<PairValue*>(expr.get());
        if (auto name = expr_ptr->carValue()->asSymbol()) {
            if (special_forms.find(*name) != special_forms.end()) {
                return special_forms.at(*name)(expr_ptr->cdrValue()->toVector(),
                                               *this);
            }
            /*else{
                ValuePtr proc = this->eval(v[0]);
                std::vector<ValuePtr> args =
                this->evalList(dynamic_cast<PairValue&>(*expr).cdrValue());
            return this->apply(proc, args);
            }*/
        }
        ValuePtr proc = this->eval(expr_ptr->carValue());
        // try {
        /*std::cout << expr_ptr->cdrValue()->toString() << "    ";*/
        std::vector<ValuePtr> args = this->evalList(expr_ptr->cdrValue());
        /*for (auto i : args) {
            std::cout << i->toString() << " ";
        }
        std::cout << std::endl;*/
        return this->apply(proc, args);
        /*} catch (...) {
            std::cout << "error" << std::endl;
        }*/

    } else if (expr->isSymbol()) {
        if (auto name = expr->asSymbol()) {
            if (env.find(*name) != env.end()) {
                return env[*name];
            } else if (parent != nullptr) {
                return parent->lookupBinding(*name);
            } else {
                throw LispError("Variable " + *name + " not defined.");
            }
        }
    } else {
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
    std::ranges::transform(expr->toVector(), std::back_inserter(result),
                           [this](ValuePtr v) { return this->eval(v); });
    return result;
}

ValuePtr EvalEnv::apply(
    ValuePtr proc,
    const std::vector<ValuePtr>& args) {  // proc是函数名，args是参数列表
    if (typeid(*proc) == typeid(BuiltinProcValue)) {
        // try {
        return dynamic_cast<BuiltinProcValue&>(*proc).func(args, *this);
        /*} catch (...) {
            std::cout << "error error" << std::endl;
        }*/
    } else if (typeid(*proc) == typeid(LambdaValue)) {
        // try {
        auto lambda = dynamic_cast<LambdaValue&>(*proc);
        return lambda.apply(args);
        /*} catch (...) {
            std::cout << "error error error" << std::endl;
        }*/
    }
    // std::shared_ptr<EvalEnv> child = this->createChild(lambda.params, args);
}

ValuePtr EvalEnv::lookupBinding(std::string name) {
    if (env.find(name) != env.end()) {
        return env[name];
    } else if (parent != nullptr) {
        return parent->lookupBinding(name);
    } else {
        throw LispError("Unbound variable: " + name);
    }
}

void EvalEnv::defineBinding(const std::vector<std::string>& names,
                            const std::vector<ValuePtr>& values) {
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

std::shared_ptr<EvalEnv> EvalEnv::createChild(
    const std::vector<std::string>& params, const std::vector<ValuePtr>& args) {
    std::shared_ptr<EvalEnv> child = EvalEnv::createGlobal();
    child->parent = this->shared_from_this();
    if (params.size() != args.size()) {
        throw LispError("Wrong number of arguments");
    }
    for (int i = 0; i < params.size(); i++) {
        child->env[params[i]] = args[i];
    }
    return child;
}