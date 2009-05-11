#if !defined(EXPR_H)
#define EXPR_H

#include <gc_cpp.h>

class Object : public gc
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

class Add : public Object 
{
 public:
  Object* lhs;
  Object* rhs;
  
public:
  Add(Object* l, Object* r);
  virtual float eval();
};

class Subtract : public Object {
 public:
  Object* lhs;
  Object* rhs;
  
 public:
  Subtract(Object* l, Object* r);
  virtual float eval();
};

class Multiply : public Object {
 public:
  Object* lhs;
  Object* rhs;
  
 public:
  Multiply(Object* l, Object* r);
  virtual float eval();
};

class Divide : public Object {
 public:
  Object* lhs;
  Object* rhs;
  
 public:
  Divide(Object* l, Object* r);
  virtual float eval();
};

extern Object* parse();

#endif
