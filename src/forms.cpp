#include "./forms.h"

#include <cstring>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "./error.h"
#include "./value.h"

const std::unordered_map<std::string, SpecialFormType*> special_forms = {
    {"define", defineForm},  {"quote", quoteForm},
    {"if", ifForm},          {"and", andForm},
    {"or", orForm},          {"lambda", lambdaForm},
    {"cond", condForm},      {"begin", beginForm},
    {"let", letForm},        {"quasiquote", quasiquoteForm},
    {"unquote", unquoteForm}};
ValuePtr lambdaForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr defineForm(const std::vector<ValuePtr>& args, EvalEnv& Env) {
    if (args[0]->isSymbol() == true) {
        if (auto name = args[0]->asSymbol()) {
            Env.env[*name] = Env.eval(args[1]);
            return std::make_shared<NilValue>();
        } else {
            throw LispError("Unimplemented");
        }
    } else if (args[0]->isList() == true) {
        if (auto name =
                dynamic_cast<PairValue&>(*args[0]).carValue()->asSymbol()) {
            std::vector<std::string> params{};
            std::vector<ValuePtr> temp =
                dynamic_cast<PairValue&>(*args[0]).cdrValue()->toVector();
            for (int i = 0; i < temp.size(); i++) {
                if (auto name = temp[i]->asSymbol()) {
                    params.push_back(*name);
                } else {
                    throw LispError("Unimplemented");
                }
            }
            std::vector<ValuePtr> body;
            body.push_back(args[1]);
            for (int i = 2; i < args.size(); i++) {
                body.push_back(args[i]);
            }
            /*for(int i=2;i<args.size();i++){
                //插入提示符
                body.push_back(std::make_shared<SymbolValue>(";"));
                std::vector<ValuePtr> temp =
            dynamic_cast<PairValue&>(*args[i]).toVector();
                body.insert(body.end(), temp.begin(), temp.end());
            }*/
            Env.env[*name] = std::make_shared<LambdaValue>(
                params, body, Env.shared_from_this());
            return std::make_shared<NilValue>();
        } else {
            throw LispError("Unimplemented");
        }
    } else {
        throw LispError("Unimplemented");
    }
}
ValuePtr quoteForm(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("Wrong number of arguments");
    }
    return params[0];
}
ValuePtr ifForm(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 3) {
        throw LispError("Wrong number of arguments");
    }
    if (strcmp(Env.eval(params[0])->toString().c_str(), "#f") == 0) {
        return Env.eval(params[2]);
    } else {
        return Env.eval(params[1]);
    }
}
ValuePtr andForm(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() == 0) {
        return std::make_shared<BooleanValue>(true);
    } else {
        for (int i = 0; i < params.size(); i++) {
            if (strcmp(Env.eval(params[i])->toString().c_str(), "#f") == 0) {
                return std::make_shared<BooleanValue>(false);
            }
            Env.eval(params[i]);
        }
        return Env.eval(params[params.size() - 1]);
    }
}
ValuePtr orForm(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() == 0) {
        return std::make_shared<BooleanValue>(false);
    } else {
        for (int i = 0; i < params.size(); i++) {
            if (strcmp(params[i]->toString().c_str(), "#f") != 0) {
                return Env.eval(params[i]);
            }
        }
        return std::make_shared<BooleanValue>(false);
    }
}
ValuePtr lambdaForm(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("Wrong number of arguments");
    }
    if (params[0]->isList() == false) {
        throw LispError("Unimplemented");
    }
    std::vector<std::string> param{};
    std::unordered_set<std::string> param_set{};
    ValuePtr temp = params[0];
    std::vector<ValuePtr> body;
    for (auto i : params) {
        if (i != params[0]) {
            body.push_back(i);
        }
    }
    while (temp->isList() == true) {
        if (auto name =
                dynamic_cast<PairValue&>(*temp).carValue()->asSymbol()) {
            if (param_set.find(*name) != param_set.end()) {
                throw LispError("Duplicate parameter");
            }
            param_set.insert(*name);
            param.push_back(*name);
        } else {
            throw LispError("LambdaForm::Unimplemented");
        }
        temp = dynamic_cast<PairValue&>(*temp).cdrValue();
    }
    return std::make_shared<LambdaValue>(param, body, Env.shared_from_this());
}
ValuePtr condForm(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() == 0) {
        throw LispError("Wrong number of arguments");
    }
    ValuePtr result;
    for (int i = 0; i < params.size(); i++) {
        if (params[i]->isList() == false) {
            throw LispError("Unimplemented");
        }
        auto temp = params[i]->toVector();
        if (strcmp(temp[0]->toString().c_str(), "else") == 0) {
            if (temp.size() == 1) {
                result = Env.eval(temp[0]);
            } else {
                result = Env.eval(temp[1]);
            }
            return std::move(result);
        }
        if (strcmp(Env.eval(temp[0])->toString().c_str(), "#t") == 0) {
            if (temp.size() == 1) {
                result = Env.eval(temp[0]);
            } else {
                result = Env.eval(temp[1]);
            }
            return std::move(result);
        }
    }
    return std::make_shared<NilValue>();
}
ValuePtr beginForm(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    for (int i = 0; i < params.size(); i++) {
        if (i == params.size() - 1) {
            return Env.eval(params[i]);
        } else {
            Env.eval(params[i]);
        }
    }
}
ValuePtr letForm(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params[0]->isList() == false) {
        throw LispError("Unimplemented");
    }
    std::vector<std::string> param{};
    std::vector<ValuePtr> param_value{};
    ValuePtr temp = params[0];
    std::vector<ValuePtr> body_temp;
    body_temp.assign(params.begin() + 1, params.end());
    ValuePtr body = Value::fromVector(body_temp);
    while (temp->isList()) {
        ValuePtr car = dynamic_cast<PairValue&>(*temp).carValue();
        std::vector<ValuePtr> car_vec = car->toVector();
        if (car_vec.size() != 2) {
            throw LispError("Wrong number of arguments");
        }
        if (auto name = car_vec[0]->asSymbol()) {
            param.push_back(*name);
            param_value.push_back(Env.eval(car_vec[1]));
        } else {
            throw LispError("Unimplemented");
        }
        temp = dynamic_cast<PairValue&>(*temp).cdrValue();
    }
    auto lambda = std::make_shared<LambdaValue>(param, body->toVector(),
                                                Env.shared_from_this());
    return lambda->apply(param_value);
}
ValuePtr quasiquote(ValuePtr param, EvalEnv& Env) {
    if (!param->isList()) {
        return param;
    }
    auto car = dynamic_cast<PairValue&>(*param).carValue();
    auto cdr = dynamic_cast<PairValue&>(*param).cdrValue();
    if (auto name = car->asSymbol()) {
        if (*name == "unquote") {
            if (!cdr->isList()) {
                throw LispError("Unimplemented");
            }
            return Env.eval(param);
        }
    } else {
        auto carson = quasiquote(car, Env);
        auto cdrson = quasiquote(cdr, Env);
        return std::make_shared<PairValue>(std::move(carson),
                                           std::move(cdrson));
    }
}
ValuePtr quasiquoteForm(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("Unimplemented");
    }
    return quasiquote(params[0], Env);
}
ValuePtr unquoteForm(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("Unimplemented");
    }
    return Env.eval(params[0]);
}