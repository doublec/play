#if !defined(EXPR_H)
#define EXPR_H

#include "gc.h"

class Object : public GCObject
{
 public:
  virtual float eval() = 0;
};

class Number : public Object 
{
 public:
  float value;
 
 public:
  Number(float v);
  virtual float eval(); 
};

class BinOp : public Object
{
 public:
  Object* lhs;
  Object* rhs;

  BinOp(Object* l, Object* r);
  virtual void markChildren();
};

class Add : public BinOp 
{
public:
  Add(Object* l, Object* r);
  virtual float eval();
};

class Subtract : public BinOp {
 public:
  Subtract(Object* l, Object* r);
  virtual float eval();
};

class Multiply : public BinOp {
 public:
  Multiply(Object* l, Object* r);
  virtual float eval();
};

class Divide : public BinOp {
 public:
  Divide(Object* l, Object* r);
  virtual float eval();
};

extern Object* parse();

#endif
