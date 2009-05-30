#if !defined(EXPR_H)
#define EXPR_H

#include "gc/gc.h"
#include <nanojit/nanojit.h>

using nanojit::LIns;
using nanojit::LirWriter;

class Object : public GCObject
{
 public:
  virtual LIns* compile(LirWriter* writer) = 0;
};

class Number : public Object 
{
 public:
  float value;
 
 public:
  Number(float v);
  virtual LIns* compile(LirWriter* writer);
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
  virtual LIns* compile(LirWriter* writer);
};

class Subtract : public BinOp {
 public:
  Subtract(Object* l, Object* r);
  virtual LIns* compile(LirWriter* writer);
};

class Multiply : public BinOp {
 public:
  Multiply(Object* l, Object* r);
  virtual LIns* compile(LirWriter* writer);
};

class Divide : public BinOp {
 public:
  Divide(Object* l, Object* r);
  virtual LIns* compile(LirWriter* writer);
};

extern Object* parse();

#endif
