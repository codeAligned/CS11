#ifndef COMMAND_HH
#define COMMAND_HH

#include <cassert>
#include <string>
#include <iostream>
#include "environment.hh"
#include "expressions.hh"

using namespace std;

// base class, which declares how all commands are to be run.
class Command {
public:
  virtual void run(Environment &env) const = 0;

  virtual ~Command() { };
};

// a print command is a command, and it simply prints out the value of the expression
class PrintCommand: public Command {
private:
  Expression *mExp;

public:
  PrintCommand(Expression *pExp) 
    : mExp(pExp)
    { assert (pExp != NULL);}
  virtual void run(Environment &env) const {cout << "= "<< mExp->evaluate(env)<< endl;}

  virtual ~PrintCommand() {delete mExp;}
};

// an assign command is a command, which evalutes an expression and sets a symbol to 
// that value
class AssignCommand: public Command {
private:
  Symbol *mSym;
  Expression *mExp;

public:
  AssignCommand(Symbol *pSym, Expression *pExp) 
    : mSym(pSym)
    , mExp(pExp)
    { assert (pSym!= NULL); assert (pExp != NULL);}
  virtual void run(Environment &env) const 
    {
      double val = mExp->evaluate(env);
      env.setSymbolValue(mSym->getSymbolName(), val);
      cout << mSym->getSymbolName() << " = " << val << endl;
    }

  virtual ~AssignCommand() {delete mSym; delete mExp;}
};

#endif // COMMAND_HH
