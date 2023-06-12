#include "./builtins.h"
#include "./value.h"
#include "./error.h"
#include <iostream>
#include <vector>
#include <string>

std::unordered_map<std::string, ValuePtr> total_env;

void add_builtins(){
    total_env["+"] = std::make_shared<BuiltinProcValue>(&add);
    total_env["print"] = std::make_shared<BuiltinProcValue>(&print);
    total_env["-"] = std::make_shared<BuiltinProcValue>(&sub);
    total_env["*"] = std::make_shared<BuiltinProcValue>(&mul);
    total_env["/"] = std::make_shared<BuiltinProcValue>(&divi);
    total_env["abs"] = std::make_shared<BuiltinProcValue>(&abss);
    total_env["="] = std::make_shared<BuiltinProcValue>(&equal);
    total_env["<"] = std::make_shared<BuiltinProcValue>(&less);
    total_env[">"] = std::make_shared<BuiltinProcValue>(&greater);
    total_env["even?"] = std::make_shared<BuiltinProcValue>(&isEven);
    total_env["odd?"] = std::make_shared<BuiltinProcValue>(&isOdd);
    total_env["zero?"] = std::make_shared<BuiltinProcValue>(&isZero);
    total_env["length"] = std::make_shared<BuiltinProcValue>(&length);
    total_env["car"] = std::make_shared<BuiltinProcValue>(&car);
    total_env["cdr"] = std::make_shared<BuiltinProcValue>(&cdr);
}

ValuePtr add(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    double result = 0.000000;
    for (const auto& i : params) {
        if (!i->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*i);
        result += flag.asNumber();
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr print(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    for (const auto& i : params) {
        std::cout << i->toString() << std::endl;
    }
    return std::make_shared<NilValue>();
}
ValuePtr sub(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    double result = 0.000000;
    result += 2*dynamic_cast<NumericValue&>(*params[0]).asNumber();
    for (const auto& i : params) {
        if (!i->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*i);
        result -= flag.asNumber();
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr mul(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    double result = 1.000000;
    for (const auto& i : params) {
        if (!i->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*i);
        result *= flag.asNumber();
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr divi(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    double result = 1.000000;
    if(dynamic_cast<NumericValue&>(*params[0]).asNumber() == 0){
        result = 0;
        return std::make_shared<NumericValue>(result);
    }
    result *= dynamic_cast<NumericValue&>(*params[0]).asNumber();
    result *= dynamic_cast<NumericValue&>(*params[0]).asNumber();
    for (const auto& i : params) {
        if (!i->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*i);
        result /= flag.asNumber();
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr abss(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("abs function only takes one parameter.");
    }
    if (!params[0]->isNumber()) {
        throw LispError("Cannot calculate a non-numeric value.");
    }
    auto flag = dynamic_cast<NumericValue&>(*params[0]);
    double result = flag.asNumber();
    if(result < 0){
        result = -result;
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr equal(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    bool result = true;
    for (const auto& i : params) {
        if (!i->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*i);
        if(flag.asNumber() != dynamic_cast<NumericValue&>(*params[0]).asNumber()){
            result = false;
        }
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr less(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    bool result = true;
    for(int i = 0; i < params.size() - 1; i++){
        if (!params[i]->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*params[i]);
        if(flag.asNumber() >= dynamic_cast<NumericValue&>(*params[i+1]).asNumber()){
            result = false;
        }
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr greater(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    bool result = true;
    for(int i = 0; i < params.size() - 1; i++){
        if (!params[i]->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*params[i]);
        if(flag.asNumber() <= dynamic_cast<NumericValue&>(*params[i+1]).asNumber()){
            result = false;
        }
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isEven(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isEven function only takes one parameter.");
    }
    if (!params[0]->isNumber()) {
        throw LispError("Cannot calculate a non-numeric value.");
    }
    auto flag = dynamic_cast<NumericValue&>(*params[0]);
    bool result = false;
    if((int)flag.asNumber() % 2 == 0){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isOdd(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isOdd function only takes one parameter.");
    }
    if (!params[0]->isNumber()) {
        throw LispError("Cannot calculate a non-numeric value.");
    }
    auto flag = dynamic_cast<NumericValue&>(*params[0]);
    bool result = false;
    if((int)flag.asNumber() % 2 == 1){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isZero(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isZero function only takes one parameter.");
    }
    if (!params[0]->isNumber()) {
        throw LispError("Cannot calculate a non-numeric value.");
    }
    auto flag = dynamic_cast<NumericValue&>(*params[0]);
    bool result = false;
    if(flag.asNumber() == 0){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr length(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("length function only takes one parameter.");
    }
    if (!params[0]->isList()) {
        throw LispError("Cannot calculate a non-list value.");
    }
    auto flag = dynamic_cast<PairValue&>(*params[0]);
    int result = flag.toVector().size();
    return std::make_shared<NumericValue>(result);
}
ValuePtr car(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("car function only takes one parameter.");
    }
    if (!params[0]->isList()) {
        throw LispError("Cannot calculate a non-list value.");
    }
    auto flag = dynamic_cast<PairValue&>(*params[0]);
    return flag.carValue();
}
ValuePtr cdr(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("cdr function only takes one parameter.");
    }
    if (!params[0]->isList()) {
        throw LispError("Cannot calculate a non-list value.");
    }
    auto flag = dynamic_cast<PairValue&>(*params[0]);
    return flag.cdrValue();
}
ValuePtr isAtom(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isAtom function only takes one parameter.");
    }
    bool result = false;
    if(params[0]->isSelfEvaluating() || params[0]->isSymbol() || params[0]->isNil()){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isBoolean(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isBoolean function only takes one parameter.");
    }
    bool result = false;
    if(params[0]->isBoolean()){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isInteger(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isInteger function only takes one parameter.");
    }
    bool result = false;
    if(params[0]->isNumber()){
        auto flag = dynamic_cast<NumericValue&>(*params[0]);
        if((int)flag.asNumber() == flag.asNumber()){
            result = true;
        }
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isList(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isList function only takes one parameter.");
    }
    bool result = false;
    if(params[0]->isList() || params[0]->isNil()){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isNumber(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isNumber function only takes one parameter.");
    }
    bool result = false;
    if(params[0]->isNumber()){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isNull(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isNull function only takes one parameter.");
    }
    bool result = false;
    if(params[0]->isNil()){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isPair(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isPair function only takes one parameter.");
    }
    bool result = false;
    if(params[0]->isList()){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isProcedure(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isProcedure function only takes one parameter.");
    }
    bool result = false;
    if(params[0]->toString() == "#<procedure>"){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isString(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isString function only takes one parameter.");
    }
    bool result = false;
    if(params[0]->isString()){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isSymbol(const std::vector<ValuePtr>& params, const EvalEnv& Env){
    if(params.size() != 1){
        throw LispError("isSymbol function only takes one parameter.");
    }
    bool result = false;
    if(params[0]->isSymbol()){
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}