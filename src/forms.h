#ifndef FORMS_H
#define FORMS_H

#include <iostream>
#include <unordered_map>
#include <vector>

#include "./error.h"
#include "./eval_env.h"
#include "./value.h"

using SpecialFormType = ValuePtr(const std::vector<ValuePtr>&, EvalEnv&);

extern const std::unordered_map<std::string, SpecialFormType*> special_forms;

ValuePtr defineForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr quoteForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr ifForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr andForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr orForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr lambdaForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr condForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr beginForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr letForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr quasiquote(ValuePtr param, EvalEnv& Env);
ValuePtr quasiquoteForm(const std::vector<ValuePtr>& params, EvalEnv& Env);
ValuePtr unquoteForm(const std::vector<ValuePtr>& params, EvalEnv& Env);

#endif