#ifndef FORMS_H
#define FORMS_H

#include "./value.h"
#include "./error.h"
#include "./eval_env.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using SpecialFormType = ValuePtr(const std::vector<ValuePtr>&, EvalEnv&);

extern const std::unordered_map<std::string, SpecialFormType*> special_forms;

ValuePtr defineForm(const std::vector<ValuePtr>& params, EvalEnv& env);

#endif