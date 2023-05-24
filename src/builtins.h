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

ValuePtr add(const std::vector<ValuePtr>& params);
ValuePtr print(const std::vector<ValuePtr>& params);
ValuePtr sub(const std::vector<ValuePtr>& params);
ValuePtr mul(const std::vector<ValuePtr>& params);
ValuePtr divi(const std::vector<ValuePtr>& params);
ValuePtr abss(const std::vector<ValuePtr>& params);
ValuePtr equal(const std::vector<ValuePtr>& params);
ValuePtr less(const std::vector<ValuePtr>& params);
ValuePtr greater(const std::vector<ValuePtr>& params);
ValuePtr isEven(const std::vector<ValuePtr>& params);
ValuePtr isOdd(const std::vector<ValuePtr>& params);
ValuePtr isZero(const std::vector<ValuePtr>& params); 
ValuePtr length(const std::vector<ValuePtr>& params);
ValuePtr car(const std::vector<ValuePtr>& params);
ValuePtr cdr(const std::vector<ValuePtr>& params);

# endif