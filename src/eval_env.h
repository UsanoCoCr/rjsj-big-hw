#ifndef EVAL_ENV_H
#define EVAL_ENV_H

#include "./value.h"
#include <unordered_map>
using ValuePtr = std::shared_ptr<Value>;

class EvalEnv{
public:
    EvalEnv();
    ValuePtr eval(ValuePtr expr);
    std::vector<ValuePtr> evalList(ValuePtr expr);
    static std::unordered_map<std::string, ValuePtr> env;
    ValuePtr apply(ValuePtr proc, std::vector<ValuePtr> args);
};

#endif