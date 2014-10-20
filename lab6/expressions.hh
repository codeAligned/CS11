#ifndef EXPRESSION_HH
#define EXPRESSION_HH

#include <cassert>
#include <string>
#include "environment.hh"

using namespace std;

// base class, which declares how all expressions can be evaluated.
class Expression {
public:
  virtual double evaluate(const Environment &env) const = 0;

  virtual ~Expression() { };
};

// a numeric value is an expression, which simply evaluates to itself.
class Value: public Expression {
private:
  double mValue;

public:
  Value(double value) {mValue = value;}
  virtual double evaluate(const Environment &env) const {return mValue;}
};

// a symbols is an expression, which can be evaluated by extracting the symbols's
// value out of the environment.
class Symbol: public Expression {
private:
  string mName;

public:
  Symbol(string name) {mName = name;}
  string getSymbolName() {return mName;}
  virtual double evaluate(const Environment &env) const {return env.getSymbolValue(mName);}
};

// a binary operator is an expression, which actually contains two expressions, one on
// each side of the actual operator.
class BinaryOperator: public Expression {
private:
  Expression *mLHS;
  Expression *mRHS;

public:
  BinaryOperator(Expression *pLHS, Expression *pRHS) 
    : mLHS(pLHS)
    , mRHS(pRHS)
    { assert (pLHS != NULL); assert (pRHS != NULL);}
  const Expression* getLHS() const {return mLHS;}
  const Expression* getRHS() const {return mRHS;}
  virtual ~BinaryOperator() {delete mLHS; delete mRHS;}
};

// an add operator is a binary operator that adds the values of the two expresssions.
class AddOper: public BinaryOperator {
public:
  AddOper(Expression *pLHS, Expression *pRHS) 
    : BinaryOperator(pLHS, pRHS) {}
  virtual double evaluate(const Environment &env) const 
    {return (getLHS()->evaluate(env) + getRHS()->evaluate(env));}
};

// a sub operator is a binary operator that subtracts the value of the right expression
// from the value of the left expression.
class SubOper: public BinaryOperator {
public:
  SubOper(Expression *pLHS, Expression *pRHS) 
    : BinaryOperator(pLHS, pRHS) {}
  virtual double evaluate(const Environment &env) const 
    {return (getLHS()->evaluate(env) - getRHS()->evaluate(env));}
};

// a mul operator is a binary operator that multiplies the values of the two expresssions.
class MulOper: public BinaryOperator {
public:
  MulOper(Expression *pLHS, Expression *pRHS) 
    : BinaryOperator(pLHS, pRHS) {}
  virtual double evaluate(const Environment &env) const 
    {return (getLHS()->evaluate(env) * getRHS()->evaluate(env));}
};

// a div operator is a binary operator that divides the value of the left expression by
// the value of the right expression, throwing an error if we try to divide by 0.
class DivOper: public BinaryOperator {
public:
  DivOper(Expression *pLHS, Expression *pRHS) 
    : BinaryOperator(pLHS, pRHS) {}
  virtual double evaluate(const Environment &env) const 
    {
      double rhs = getRHS()->evaluate(env);
      if (rhs == 0) {
        throw runtime_error("Divide by 0");
      }
      return (getLHS()->evaluate(env) / getRHS()->evaluate(env));
    }
};

// a unary operator is an expression, which actually contains one expression along
// with the operator.
class UnaryOperator: public Expression {
private:
  Expression *mLHS;

public:
  UnaryOperator(Expression *pLHS) 
    : mLHS(pLHS)
    { assert (pLHS != NULL);}
  const Expression* getLHS() const {return mLHS;}
  virtual ~UnaryOperator() {delete mLHS;}
};

// a neg operator is a unary operator that negates the value of the expression.
class NegOper: public UnaryOperator {
public:
  NegOper(Expression *pLHS) 
    : UnaryOperator(pLHS) {}
  virtual double evaluate(const Environment &env) const 
    {return (-1) * (getLHS()->evaluate(env));}
};

#endif // EXPRESSION_HH
