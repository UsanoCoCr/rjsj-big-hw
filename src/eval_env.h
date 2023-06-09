#ifndef EVAL_ENV_H
#define EVAL_ENV_H

#include <unordered_map>

#include "./value.h"
using ValuePtr = std::shared_ptr<Value>;

class EvalEnv : public std::enable_shared_from_this<EvalEnv> {
    EvalEnv();

public:
    static std::shared_ptr<EvalEnv> createGlobal();
    ValuePtr eval(ValuePtr expr);
    std::vector<ValuePtr> evalList(ValuePtr expr);
    std::unordered_map<std::string, ValuePtr> env;
    ValuePtr apply(ValuePtr proc, const std::vector<ValuePtr>& args);
    std::shared_ptr<EvalEnv> parent;
    ValuePtr lookupBinding(std::string name);
    void defineBinding(const std::vector<std::string>& names,
                       const std::vector<ValuePtr>& values);
    std::shared_ptr<EvalEnv> createChild(const std::vector<std::string>& params,
                                         const std::vector<ValuePtr>& args);
};

#endif