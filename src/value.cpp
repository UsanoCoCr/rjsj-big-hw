#include "./value.h"

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

#include "./builtins.h"
#include "./error.h"
#include "./eval_env.h"
#include "./forms.h"

using ValuePtr = std::shared_ptr<Value>;

bool Value::isNil() const {
    return false;
}
bool Value::isSelfEvaluating() const {
    return false;
}
bool Value::isList() const {
    return false;
}
std::optional<std::string> Value::asSymbol() const {
    return std::nullopt;
}
bool Value::isSymbol() const {
    return false;
}
bool Value::isBoolean() const {
    return false;
}
bool Value::isString() const {
    return false;
}
bool Value::isNumber() const {
    return false;
}
bool Value::isLambda() const {
    return false;
}
double Value::asNumber() const {
    return 0;
}
std::vector<ValuePtr> Value::toVector() const {
    throw LispError("Not a list or a nil value");
}
/*ValuePtr Value::fromVector(std::vector<ValuePtr> v){
    if(v.size()==0){
        return std::make_shared<NilValue>();
    }
    //;是两个列表之间的分隔符
    ValuePtr result = std::make_shared<NilValue>();
    for(int i=v.size()-1; i>=0; i--){
        if(v[i]->asSymbol() == ";"){
            std::vector<ValuePtr> temp_car,temp_cdr;
            for(int j=0; j<i; j++){
                temp_car.push_back(v[j]);
            }
            for(int j=i+1; j<v.size(); j++){
                temp_cdr.push_back(v[j]);
            }
            result = std::make_shared<PairValue>(Value::fromVector(temp_car),
Value::fromVector(temp_cdr)); return result;
        }
    }
    for(auto it=v.rbegin(); it!=v.rend(); ++it){
        result=std::make_shared<PairValue>(*it, result);
    }
    return result;
}*/
ValuePtr Value::fromVector(std::vector<ValuePtr> v) {
    if (v.size() == 0) {
        return std::make_shared<NilValue>();
    }
    ValuePtr result = std::make_shared<NilValue>();
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        result = std::make_shared<PairValue>(*it, result);
    }
    return result;
}

BooleanValue::BooleanValue(bool v) : value{v} {}
std::string BooleanValue::toString() const {
    if (value) {
        return "#t";
    } else {
        return "#f";
    }
}
bool BooleanValue::isSelfEvaluating() const {
    return true;
}
bool BooleanValue::isBoolean() const {
    return true;
}

NumericValue::NumericValue(double v) : value{v} {}
std::string NumericValue::toString() const {
    if (value == static_cast<int>(value)) {
        return std::to_string(static_cast<int>(value));
    }
    return std::to_string(value);
}
bool NumericValue::isSelfEvaluating() const {
    return true;
}
bool NumericValue::isNumber() const {
    return true;
}
double NumericValue::asNumber() const {
    return value;
}

StringValue::StringValue(const std::string& v) : value{v} {}
std::string StringValue::toString() const {
    std::ostringstream ss;
    ss << std::quoted(value);
    return ss.str();
}
bool StringValue::isSelfEvaluating() const {
    return true;
}
bool StringValue::isString() const {
    return true;
}

NilValue::NilValue() {}
std::string NilValue::toString() const {
    return "()";
}
bool NilValue::isNil() const {
    return true;
}
std::vector<ValuePtr> NilValue::toVector() const {
    std::vector<ValuePtr> result;
    return result;
}

SymbolValue::SymbolValue(const std::string& v) : value{v} {}
std::string SymbolValue::toString() const {
    return value;
}
std::optional<std::string> SymbolValue::asSymbol() const {
    return value;
}
bool SymbolValue::isSymbol() const {
    return true;
}

PairValue::PairValue(ValuePtr input_car, ValuePtr input_cdr)
    : car{input_car}, cdr{input_cdr} {}
std::string PairValue::toString() const {
    std::ostringstream ss;
    ss << "(";
    ss << car->toString();

    ValuePtr temp_cdr = cdr;
    while (typeid(*temp_cdr) == typeid(PairValue)) {
        auto& pair = static_cast<const PairValue&>(*temp_cdr);
        ss << " ";
        ss << pair.car->toString();
        temp_cdr = pair.cdr;
    }

    if (typeid(*temp_cdr) != typeid(NilValue) &&
        typeid(*temp_cdr) != typeid(PairValue)) {
        ss << " . ";
        ss << temp_cdr->toString();
        // std::cout << "ss string is: " << ss.str() << std::endl;
    }

    ss << ")";
    return ss.str();
}
bool PairValue::isList() const {
    return true;
}
std::vector<ValuePtr> PairValue::toVector() const {
    std::vector<ValuePtr> result;
    result.push_back(car);
    ValuePtr temp_cdr = cdr;
    while (typeid(*temp_cdr) == typeid(PairValue)) {
        auto& pair = static_cast<const PairValue&>(*temp_cdr);
        result.push_back(pair.car);
        temp_cdr = pair.cdr;
    }
    if (typeid(*temp_cdr) != typeid(NilValue) &&
        typeid(*temp_cdr) != typeid(PairValue)) {
        // result.push_back(temp_cdr);
        throw LispError("Not a list or a nil value");
    }
    return result;
}
std::shared_ptr<Value> PairValue::cdrValue() const {
    return cdr;
}
std::shared_ptr<Value> PairValue::carValue() const {
    return car;
}
std::shared_ptr<Value> PairValue::setCar(std::shared_ptr<Value> input_car) {
    car = input_car;
    return car;
}
std::shared_ptr<Value> PairValue::setCdr(std::shared_ptr<Value> input_cdr) {
    cdr = input_cdr;
    return cdr;
}

BuiltinProcValue::BuiltinProcValue(BuiltinFuncType* func) : func{func} {}
std::string BuiltinProcValue::toString() const {
    return "#<procedure>";
}

std::string LambdaValue::toString() const {
    return "#<procedure>";
}
LambdaValue::LambdaValue(std::vector<std::string> input_params,
                         std::vector<std::shared_ptr<Value>> input_body,
                         std::shared_ptr<EvalEnv> input_env)
    : params(std::move(input_params)),
      body(std::move(input_body)),
      current_env(std::move(input_env)) {}
bool LambdaValue::isLambda() const {
    return true;
}
ValuePtr LambdaValue::apply(const std::vector<ValuePtr>&
                                args) {  // 这一步相当于是调用的时候把实参贴上去
    if (args.size() != params.size()) {
        throw LispError("LambdaValue::apply : Wrong number of arguments");
    }
    std::shared_ptr<EvalEnv> child = current_env->createChild(params, args);
    // current_env->defineBinding(params,args);
    // 把vector args转成pairValue
    /*ValuePtr PairArgs = PairValue::fromVector(body);
    ValuePtr result = child->eval(PairArgs);
    return result;*/

    std::vector<ValuePtr> result{};
    // std::cout << "body size is: " << body.size() << std::endl;
    for (auto i : body) {
        // std::cout << i->toString() << std::endl;
        result.push_back(child->eval(i));
    }
    return result.back();
}
/* int main() {
    //v=(a.(b.(c.d)))
    ValuePtr v=std::make_shared<PairValue>(
        std::make_shared<SymbolValue>("a"),
        std::make_shared<PairValue>(
            std::make_shared<SymbolValue>("b"),
            std::make_shared<PairValue>(
                std::make_shared<SymbolValue>("c"),
                std::make_shared<SymbolValue>("d")
            )
        )
    );
    std::cout << v->toString() << std::endl;
} */