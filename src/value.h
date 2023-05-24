#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

class Value{
public:
    virtual std::string toString() const = 0;
    virtual ~Value() = default;
    virtual bool isNil();
    virtual bool isSelfEvaluating();
    virtual bool isNumber();
    virtual bool isList();
    virtual bool isSymbol();
    virtual std::optional<std::string> asSymbol() const;
    virtual double asNumber() const;
    virtual std::vector<std::shared_ptr<Value>> toVector() const;
};

class BooleanValue : public Value{
private:
    bool value;
public:
    BooleanValue(bool v);
    std::string toString() const override;
    bool isSelfEvaluating() override;
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
};

using BuiltinFuncType = std::shared_ptr<Value>(const std::vector<std::shared_ptr<Value>>&);

class BuiltinProcValue : public Value{
public:
    BuiltinProcValue(BuiltinFuncType* f);
    std::string toString() const override;
    BuiltinFuncType* func;
};

class LambdaValue : public Value{
    std::vector<std::string> params;
    std::vector<std::shared_ptr<Value>> body;
public:
    std::string toString() const override;
    LambdaValue(std::vector<std::string> input_params, std::vector<std::shared_ptr<Value>> input_body);
    LambdaValue();
};
#endif