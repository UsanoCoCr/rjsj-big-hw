#ifndef BUILTINS_H
#define BUILTINS_H

#include <iostream>
#include <unordered_map>
#include <vector>

#include "./error.h"
#include "./value.h"

using ValuePtr = std::shared_ptr<Value>;

extern std::unordered_map<std::string, ValuePtr> total_env;

void add_builtins();

ValuePtr add(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr print(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr sub(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr mul(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr divi(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr abss(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr equal(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr less(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr greater(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isEven(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isOdd(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isZero(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr length(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr car(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr cdr(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isAtom(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isBoolean(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isInteger(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isList(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isNumber(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isNull(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isPair(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isProcedure(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isString(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr isSymbol(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr append(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr cons(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr listLength(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr list(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr map(const std::vector<ValuePtr>& params, EvalEnv& Env);     // error
ValuePtr filter(const std::vector<ValuePtr>& params, EvalEnv& Env);  // error
ValuePtr reduce(const std::vector<ValuePtr>& params, EvalEnv& Env);  // error
ValuePtr expt(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr quotient(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr modulo(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr rremainder(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr equalNum(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr eqNum(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr nnot(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr greatereq(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr lesseq(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr apply(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr display(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr displayln(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr error(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr eeval(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr eexit(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr newline(const std::vector<ValuePtr>& params, EvalEnv& Env);

#endif