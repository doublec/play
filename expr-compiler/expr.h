#if !defined(EXPR_H)
#define EXPR_H

#include <gc_cpp.h>
#include <nanojit/nanojit.h>

using nanojit::LIns;
using nanojit::LirWriter;

class Object : public gc
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

class Add : public Object 
{
 public:
  Object* lhs;
  Object* rhs;
  
public:
  Add(Object* l, Object* r);
  virtual LIns* compile(LirWriter* writer);
};

class Subtract : public Object {
 public:
  Object* lhs;
  Object* rhs;
  
 public:
  Subtract(Object* l, Object* r);
  virtual LIns* compile(LirWriter* writer);
};

class Multiply : public Object {
 public:
  Object* lhs;
  Object* rhs;
  
 public:
  Multiply(Object* l, Object* r);
  virtual LIns* compile(LirWriter* writer);
};

class Divide : public Object {
 public:
  Object* lhs;
  Object* rhs;
  
 public:
  Divide(Object* l, Object* r);
  virtual LIns* compile(LirWriter* writer);
};

extern Object* parse();

#endif
