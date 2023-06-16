#include "./builtins.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "./error.h"
#include "./eval_env.h"
#include "./value.h"

std::unordered_map<std::string, ValuePtr> total_env;

void add_builtins() {
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
    total_env["atom?"] = std::make_shared<BuiltinProcValue>(&isAtom);
    total_env["boolean?"] = std::make_shared<BuiltinProcValue>(&isBoolean);
    total_env["integer?"] = std::make_shared<BuiltinProcValue>(&isInteger);
    total_env["list?"] = std::make_shared<BuiltinProcValue>(&isList);
    total_env["number?"] = std::make_shared<BuiltinProcValue>(&isNumber);
    total_env["null?"] = std::make_shared<BuiltinProcValue>(&isNull);
    total_env["pair?"] = std::make_shared<BuiltinProcValue>(&isPair);
    total_env["procedure?"] = std::make_shared<BuiltinProcValue>(&isProcedure);
    total_env["string?"] = std::make_shared<BuiltinProcValue>(&isString);
    total_env["symbol?"] = std::make_shared<BuiltinProcValue>(&isSymbol);
    total_env["append"] = std::make_shared<BuiltinProcValue>(&append);
    total_env["cons"] = std::make_shared<BuiltinProcValue>(&cons);
    total_env["length"] = std::make_shared<BuiltinProcValue>(&listLength);
    total_env["list"] = std::make_shared<BuiltinProcValue>(&list);
    total_env["map"] = std::make_shared<BuiltinProcValue>(&map);
    total_env["filter"] = std::make_shared<BuiltinProcValue>(&filter);
    total_env["reduce"] = std::make_shared<BuiltinProcValue>(&reduce);
    total_env["expt"] = std::make_shared<BuiltinProcValue>(&expt);
    total_env["quotient"] = std::make_shared<BuiltinProcValue>(&quotient);
    total_env["modulo"] = std::make_shared<BuiltinProcValue>(&modulo);
    total_env["remainder"] = std::make_shared<BuiltinProcValue>(&rremainder);
    total_env["eq?"] = std::make_shared<BuiltinProcValue>(&eqNum);
    total_env["equal?"] = std::make_shared<BuiltinProcValue>(&equalNum);
    total_env[">="] = std::make_shared<BuiltinProcValue>(&greatereq);
    total_env["<="] = std::make_shared<BuiltinProcValue>(&lesseq);
    total_env["not"] = std::make_shared<BuiltinProcValue>(&nnot);
    total_env["apply"] = std::make_shared<BuiltinProcValue>(&apply);
    total_env["display"] = std::make_shared<BuiltinProcValue>(&display);
    total_env["displayln"] = std::make_shared<BuiltinProcValue>(&displayln);
    total_env["error"] = std::make_shared<BuiltinProcValue>(&error);
    total_env["eval"] = std::make_shared<BuiltinProcValue>(&eeval);
    total_env["exit"] = std::make_shared<BuiltinProcValue>(&eexit);
    total_env["newline"] = std::make_shared<BuiltinProcValue>(&newline);
}

ValuePtr add(const std::vector<ValuePtr>& params, EvalEnv& Env) {
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
ValuePtr print(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    for (const auto& i : params) {
        std::cout << i->toString() << std::endl;
    }
    return std::make_shared<NilValue>();
}
ValuePtr sub(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() == 1) {
        auto flag = dynamic_cast<NumericValue&>(*params[0]);
        return std::make_shared<NumericValue>(-flag.asNumber());
    }
    double result = 0.000000;
    result += 2 * dynamic_cast<NumericValue&>(*params[0]).asNumber();
    for (const auto& i : params) {
        if (!i->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*i);
        result -= flag.asNumber();
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr mul(const std::vector<ValuePtr>& params, EvalEnv& Env) {
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
ValuePtr divi(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1 && params.size() != 2) {
        throw LispError("div function only takes one or two parameters.");
    }
    if (params.size() == 1 &&
        dynamic_cast<NumericValue&>(*params[0]).asNumber() == 0) {
        throw LispError("div function cannot divide by zero.");
    }
    if (params.size() == 2 &&
        dynamic_cast<NumericValue&>(*params[1]).asNumber() == 0) {
        throw LispError("div function cannot divide by zero.");
    }
    double result = 1.000000;
    if (params.size() == 1) {
        result = 1 / dynamic_cast<NumericValue&>(*params[0]).asNumber();
        return std::make_shared<NumericValue>(result);
    }
    result = dynamic_cast<NumericValue&>(*params[0]).asNumber() * 1.0 /
             dynamic_cast<NumericValue&>(*params[1]).asNumber();
    return std::make_shared<NumericValue>(result);
}
ValuePtr abss(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("abs function only takes one parameter.");
    }
    if (!params[0]->isNumber()) {
        throw LispError("Cannot calculate a non-numeric value.");
    }
    auto flag = dynamic_cast<NumericValue&>(*params[0]);
    double result = flag.asNumber();
    if (result < 0) {
        result = -result;
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr equal(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    bool result = true;
    for (const auto& i : params) {
        if (!i->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*i);
        if (flag.asNumber() !=
            dynamic_cast<NumericValue&>(*params[0]).asNumber()) {
            result = false;
        }
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr less(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    bool result = true;
    for (int i = 0; i < params.size() - 1; i++) {
        if (!params[i]->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*params[i]);
        if (flag.asNumber() >=
            dynamic_cast<NumericValue&>(*params[i + 1]).asNumber()) {
            result = false;
        }
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr greater(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    bool result = true;
    for (int i = 0; i < params.size() - 1; i++) {
        if (!params[i]->isNumber()) {
            throw LispError("Cannot calculate a non-numeric value.");
        }
        auto flag = dynamic_cast<NumericValue&>(*params[i]);
        if (flag.asNumber() <=
            dynamic_cast<NumericValue&>(*params[i + 1]).asNumber()) {
            result = false;
        }
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isEven(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isEven function only takes one parameter.");
    }
    if (!params[0]->isNumber()) {
        throw LispError("Cannot calculate a non-numeric value.");
    }
    auto flag = dynamic_cast<NumericValue&>(*params[0]);
    bool result = false;
    if (flag.asNumber() != (int)flag.asNumber()) {
        return std::make_shared<BooleanValue>(result);
    }
    if (std::abs((int)flag.asNumber()) % 2 == 0) {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isOdd(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isOdd function only takes one parameter.");
    }
    if (!params[0]->isNumber()) {
        throw LispError("Cannot calculate a non-numeric value.");
    }
    auto flag = dynamic_cast<NumericValue&>(*params[0]);
    bool result = false;
    if (flag.asNumber() != (int)flag.asNumber()) {
        return std::make_shared<BooleanValue>(result);
    }
    if (std::abs((int)flag.asNumber()) % 2 == 1) {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isZero(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isZero function only takes one parameter.");
    }
    if (!params[0]->isNumber()) {
        throw LispError("Cannot calculate a non-numeric value.");
    }
    auto flag = dynamic_cast<NumericValue&>(*params[0]);
    bool result = false;
    if (flag.asNumber() == 0) {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr length(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("length function only takes one parameter.");
    }
    if (!params[0]->isList()) {
        throw LispError("Cannot calculate a non-list value.");
    }
    auto flag = dynamic_cast<PairValue&>(*params[0]);
    int result = flag.toVector().size();
    return std::make_shared<NumericValue>(result);
}
ValuePtr car(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("car function only takes one parameter.");
    }
    if (!params[0]->isList()) {
        throw LispError("Cannot calculate a non-list value.");
    }
    auto flag = dynamic_cast<PairValue&>(*params[0]);
    return flag.carValue();
}
ValuePtr cdr(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("cdr function only takes one parameter.");
    }
    if (!params[0]->isList()) {
        throw LispError("Cannot calculate a non-list value.");
    }
    auto flag = dynamic_cast<PairValue&>(*params[0]);
    return flag.cdrValue();
}
ValuePtr isAtom(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isAtom function only takes one parameter.");
    }
    bool result = false;
    if (params[0]->isSelfEvaluating() || params[0]->isSymbol() ||
        params[0]->isNil()) {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isBoolean(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isBoolean function only takes one parameter.");
    }
    bool result = false;
    if (params[0]->isBoolean()) {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isInteger(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isInteger function only takes one parameter.");
    }
    bool result = false;
    if (params[0]->isNumber()) {
        auto flag = dynamic_cast<NumericValue&>(*params[0]);
        if ((int)flag.asNumber() == flag.asNumber()) {
            result = true;
        }
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isList(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isList function only takes one parameter.");
    }

    bool result = false;
    ValuePtr temp = params[0];
    while (!temp->isNil()) {
        if (!temp->isList()) {
            return std::make_shared<BooleanValue>(result);
        }
        auto flag = dynamic_cast<PairValue&>(*temp);
        temp = flag.cdrValue();
    }
    result = true;
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isNumber(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isNumber function only takes one parameter.");
    }
    bool result = false;
    if (params[0]->isNumber()) {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isNull(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isNull function only takes one parameter.");
    }
    bool result = false;
    if (params[0]->isNil()) {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isPair(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isPair function only takes one parameter.");
    }
    bool result = false;
    if (params[0]->isList()) {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isProcedure(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isProcedure function only takes one parameter.");
    }
    bool result = false;
    if (params[0]->toString() == "#<procedure>") {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isString(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isString function only takes one parameter.");
    }
    bool result = false;
    if (params[0]->isString()) {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr isSymbol(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("isSymbol function only takes one parameter.");
    }
    bool result = false;
    if (params[0]->isSymbol()) {
        result = true;
    }
    return std::make_shared<BooleanValue>(result);
}
ValuePtr append(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() == 0) {
        return std::make_shared<NilValue>();
    }
    std::vector<ValuePtr> result;
    for (auto i : params) {
        auto flag = i->toVector();
        result.insert(result.end(), flag.begin(), flag.end());
    }
    return Value::fromVector(result);
}
ValuePtr cons(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("cons function only takes two parameters.");
    }
    return std::make_shared<PairValue>(params[0], params[1]);
}
ValuePtr listLength(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("length function only takes one parameter.");
    }
    if (params[0]->isNil()) {
        return std::make_shared<NumericValue>(0);
    }
    if (!params[0]->isList()) {
        throw LispError("Cannot calculate a non-list value.");
    }
    auto flag = dynamic_cast<PairValue&>(*params[0]);
    int result = flag.toVector().size();
    return std::make_shared<NumericValue>(result);
}
ValuePtr list(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    return Value::fromVector(params);
}
ValuePtr map(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("map function only takes two parameters.");
    }
    /*if (params[0]->toString() != "#<procedure>") {
        throw LispError("Cannot calculate a non-procedure value.");
    }*/
    if (!params[1]->isList()) {
        throw LispError("Cannot calculate a non-list value.");
    }
    std::vector<ValuePtr> flag = params[1]->toVector();
    auto proc = params[0];
    std::vector<ValuePtr> result;
    for (auto i : flag) {
        std::vector<ValuePtr> temp;
        temp.push_back(i);
        result.push_back(Env.apply(proc, temp));
    }
    return Value::fromVector(result);
}
ValuePtr filter(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("filter function only takes two parameters.");
    }
    if (!params[1]->isList()) {
        throw LispError("Cannot calculate a non-list value.");
    }
    auto param = params[0];
    std::vector<ValuePtr> flag = params[1]->toVector();
    std::vector<ValuePtr> result;
    for (auto i : flag) {
        std::vector<ValuePtr> temp;
        temp.push_back(i);
        if (std::strcmp(Env.apply(param, temp)->toString().c_str(), "#t") ==
            0) {
            result.push_back(i);
        }
    }
    return Value::fromVector(result);
}
ValuePtr reduce(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("reduce function only takes two parameters.");
    }
    if (!params[1]->isList()) {
        throw LispError("Cannot calculate a non-list value.");
    }
    auto param = params[0];
    auto car = dynamic_cast<PairValue&>(*params[1]).carValue();
    auto cdr = dynamic_cast<PairValue&>(*params[1]).cdrValue();
    while (cdr->isList()) {
        auto cadr = dynamic_cast<PairValue&>(*cdr).carValue();
        auto cddr = dynamic_cast<PairValue&>(*cdr).cdrValue();
        car = Env.apply(param, {car, cadr});
        cdr = cddr;
    }
    return car;
}
ValuePtr expt(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("expt function only takes two parameters.");
    }
    if (!params[0]->isNumber() || !params[1]->isNumber()) {
        throw LispError("Cannot calculate a non-number value.");
    }
    if (params[0]->asNumber() == 0 && params[1]->asNumber() == 0) {
        throw LispError("0^0 is undefined.");
    }
    auto flag1 = dynamic_cast<NumericValue&>(*params[0]);
    auto flag2 = dynamic_cast<NumericValue&>(*params[1]);
    double result = std::pow(flag1.asNumber(), flag2.asNumber());
    return std::make_shared<NumericValue>(result);
}
ValuePtr quotient(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("quotient function only takes two parameters.");
    }
    if (!params[0]->isNumber() || !params[1]->isNumber()) {
        throw LispError("Cannot calculate a non-number value.");
    }
    if (params[1]->asNumber() == 0) {
        throw LispError("Cannot divide by zero.");
    }
    auto flag1 = dynamic_cast<NumericValue&>(*params[0]);
    auto flag2 = dynamic_cast<NumericValue&>(*params[1]);
    int result = flag1.asNumber() / flag2.asNumber();
    return std::make_shared<NumericValue>(result);
}
ValuePtr modulo(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("modulo function only takes two parameters.");
    }
    if (!params[0]->isNumber() || !params[1]->isNumber()) {
        throw LispError("Cannot calculate a non-number value.");
    }
    if (params[1]->asNumber() == 0) {
        throw LispError("Cannot divide by zero.");
    }
    int flag1 = dynamic_cast<NumericValue&>(*params[0]).asNumber();
    int flag2 = dynamic_cast<NumericValue&>(*params[1]).asNumber();
    int result = flag1 - flag2 * (int)(flag1 / flag2);
    if ((flag1 > 0 && flag2 < 0) || (flag1 < 0 && flag2 > 0)) {
        result = flag1 - flag2 * (int)(flag1 / flag2) + flag2;
    }
    return std::make_shared<NumericValue>(result);
}
ValuePtr rremainder(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("remainder function only takes two parameters.");
    }
    if (!params[0]->isNumber() || !params[1]->isNumber()) {
        throw LispError("Cannot calculate a non-number value.");
    }
    if (params[1]->asNumber() == 0) {
        throw LispError("Cannot divide by zero.");
    }
    int flag1 = dynamic_cast<NumericValue&>(*params[0]).asNumber();
    int flag2 = dynamic_cast<NumericValue&>(*params[1]).asNumber();
    int result = std::fmod(flag1, flag2);
    return std::make_shared<NumericValue>(result);
}
ValuePtr eqNum(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("eq? function only takes two parameters.");
    }
    auto a = std::move(params[0]);
    auto b = std::move(params[1]);
    if (typeid(*a) != typeid(*b)) {
        return std::make_shared<BooleanValue>(false);
    }
    if (a->isNumber()) {
        if (a->asNumber() == b->asNumber()) {
            return std::make_shared<BooleanValue>(true);
        }
        return std::make_shared<BooleanValue>(false);
    }
    if (a->isNumber()) {
        if (a->asNumber() == b->asNumber()) {
            return std::make_shared<BooleanValue>(true);
        }
        return std::make_shared<BooleanValue>(false);
    }
    if (a->isSymbol()) {
        if (a->asSymbol() == b->asSymbol()) {
            return std::make_shared<BooleanValue>(true);
        }
        return std::make_shared<BooleanValue>(false);
    }
    if (a->isNil()) {
        return std::make_shared<BooleanValue>(true);
    } else {
        return std::make_shared<BooleanValue>(a == b);
    }
    return std::make_shared<BooleanValue>(false);
}
ValuePtr equalNum(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("equal? function only takes two parameters.");
    }
    if (params[0]->toString() == params[1]->toString()) {
        return std::make_shared<BooleanValue>(true);
    }
    return std::make_shared<BooleanValue>(false);
}
ValuePtr nnot(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("not function only takes one parameter.");
    }
    if (typeid(*params[0]) == typeid(BooleanValue)) {
        if (dynamic_cast<BooleanValue&>(*params[0]).toString().c_str() ==
                "#t" ||
            dynamic_cast<BooleanValue&>(*params[0]).toString() == "#t") {
            return std::make_shared<BooleanValue>(false);
        }
        return std::make_shared<BooleanValue>(true);
    }
    return std::make_shared<BooleanValue>(false);
}
ValuePtr greatereq(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError(">= function only takes two parameters.");
    }
    if (!params[0]->isNumber() || !params[1]->isNumber()) {
        throw LispError("Cannot compare a non-number value.");
    }
    if (dynamic_cast<NumericValue&>(*params[0]).asNumber() >=
        dynamic_cast<NumericValue&>(*params[1]).asNumber()) {
        return std::make_shared<BooleanValue>(true);
    }
    return std::make_shared<BooleanValue>(false);
}
ValuePtr lesseq(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("<= function only takes two parameters.");
    }
    if (!params[0]->isNumber() || !params[1]->isNumber()) {
        throw LispError("Cannot compare a non-number value.");
    }
    if (dynamic_cast<NumericValue&>(*params[0]).asNumber() <=
        dynamic_cast<NumericValue&>(*params[1]).asNumber()) {
        return std::make_shared<BooleanValue>(true);
    }
    return std::make_shared<BooleanValue>(false);
}
ValuePtr apply(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 2) {
        throw LispError("apply function only takes two parameters.");
    }
    return Env.apply(params[0], params[1]->toVector());
}
ValuePtr display(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("display function only takes one parameter.");
    }
    std::cout << Env.eval(params[0])->toString();
    return std::make_shared<NilValue>();
}
ValuePtr displayln(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("displayln function only takes one parameter.");
    }
    std::cout << Env.eval(params[0])->toString() << std::endl;
    return std::make_shared<NilValue>();
}
ValuePtr error(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() == 0) {
        throw LispError("error function only takes one parameter.");
    }
    if (params.size() == 1) {
        throw LispError(params[0]->toString());
    }
    return std::make_shared<NilValue>();
}
ValuePtr eeval(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 1) {
        throw LispError("eval function only takes one parameter.");
    }
    ValuePtr result = params[0];
    return Env.eval(result);
}
ValuePtr eexit(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() == 0) {
        exit(0);
    }
    if (params.size() != 1) {
        throw LispError("exit function only takes one parameter.");
    }
    exit(params[0]->asNumber());
    return std::make_shared<NilValue>();
}
ValuePtr newline(const std::vector<ValuePtr>& params, EvalEnv& Env) {
    if (params.size() != 0) {
        throw LispError("newline function only takes zero parameter.");
    }
    std::cout << std::endl;
    return std::make_shared<NilValue>();
}