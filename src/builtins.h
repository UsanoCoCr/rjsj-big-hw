# ifndef BUILTINS_H
# define BUILTINS_H

# include "./value.h"
# include "./error.h"
# include <iostream>
#include <vector>
#include <unordered_map>

using ValuePtr = std::shared_ptr<Value>;

extern std::unordered_map<std::string, ValuePtr> total_env;

void add_builtins();

ValuePtr add(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr print(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr sub(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr mul(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr divi(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr abss(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr equal(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr less(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr greater(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isEven(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isOdd(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isZero(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr length(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr car(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr cdr(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isAtom(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isBoolean(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isInteger(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isList(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isNumber(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isNull(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isPair(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isProcedure(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isString(const std::vector<ValuePtr>& params, const EvalEnv& Env);
ValuePtr isSymbol(const std::vector<ValuePtr>& params, const EvalEnv& Env);




# endif