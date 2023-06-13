#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

class EvalEnv;

class Value{
public:
    virtual std::string toString() const = 0;
    virtual ~Value() = default;
    virtual bool isNil();
    virtual bool isSelfEvaluating();
    virtual bool isNumber();
    virtual bool isBoolean();
    virtual bool isString();
    virtual bool isList();
    virtual bool isSymbol();
    virtual bool isLambda();
    virtual std::optional<std::string> asSymbol() const;
    virtual double asNumber() const;
    virtual std::vector<std::shared_ptr<Value>> toVector() const;
    static std::shared_ptr<Value> fromVector(std::vector<std::shared_ptr<Value>> v);
};

class BooleanValue : public Value{
private:
    bool value;
public:
    BooleanValue(bool v);
    std::string toString() const override;
    bool isSelfEvaluating() override;
    bool isBoolean() override;
};

class NumericValue : public Value{
private:
    double value;
public:
    NumericValue(double v);
    std::string toString() const override;
    bool isSelfEvaluating() override;
    bool isNumber() override;
    double asNumber() const override;
};

class StringValue : public Value{
private:
    std::string value;
public:
    StringValue(const std::string &v);
    std::string toString() const override;
    bool isSelfEvaluating() override;
    bool isString() override;
};

class NilValue : public Value{
public:
    NilValue();
    std::string toString() const override;
    bool isNil() override;
    std::vector<std::shared_ptr<Value>> toVector() const override;
};

class SymbolValue : public Value{
private:
    std::string value;
public:
    SymbolValue(const std::string &v);
    std::string toString() const override;
    std::optional<std::string> asSymbol() const override;
    bool isSymbol() override;
};

class PairValue : public Value{
private:
    std::shared_ptr<Value> car;
    std::shared_ptr<Value> cdr;
public:
    PairValue(std::shared_ptr<Value> input_car, std::shared_ptr<Value> input_cdr);
    std::string toString() const override;
    bool isList() override;
    std::vector<std::shared_ptr<Value>> toVector() const;
    std::shared_ptr<Value> cdrValue() const;
    std::shared_ptr<Value> carValue() const;
    std::shared_ptr<Value> setCar(std::shared_ptr<Value> input_car);
    std::shared_ptr<Value> setCdr(std::shared_ptr<Value> input_cdr);
};

using BuiltinFuncType = std::shared_ptr<Value>(const std::vector<std::shared_ptr<Value>>&, EvalEnv&);

class BuiltinProcValue : public Value{
public:
    BuiltinProcValue(BuiltinFuncType* f);
    std::string toString() const override;
    BuiltinFuncType* func;
};

class LambdaValue : public Value{
    
public:
    std::vector<std::string> params;//参数列表
    std::vector<std::shared_ptr<Value>> body;//函数体
    std::string toString() const override;
    LambdaValue(std::vector<std::string> input_params, std::vector<std::shared_ptr<Value>> input_body,
                std::shared_ptr<EvalEnv> input_env);
    bool isLambda() override;  
    std::shared_ptr<EvalEnv> current_env;
    std::shared_ptr<Value> apply(const std::vector<std::shared_ptr<Value>>& args);
    
};
#endif