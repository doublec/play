#include <cassert>
#include <iostream>
#include "expr.h"

using namespace std;

Number::Number(float v) :
  value(v)
{
}

float Number::eval() 
{
  return value;
}

BinOp::BinOp(Object* l, Object* r) :
  lhs(l), rhs(r)
{
}

void BinOp::markChildren() 
{
  lhs->mark();
  rhs->mark();
}

Add::Add(Object* l, Object* r) :
  BinOp(l, r)
{
}

float Add::eval()
{
  return lhs->eval() + rhs->eval();
}


Subtract::Subtract(Object* l, Object* r) :
  BinOp(l, r)
{
}

float Subtract::eval()
{
  return lhs->eval() - rhs->eval();
}

Multiply::Multiply(Object* l, Object* r) :
  BinOp(l, r)
{
}

float Multiply::eval()
{
  return lhs->eval() * rhs->eval();
}

Divide::Divide(Object* l, Object* r) :
  BinOp(l, r)
{
}

float Divide::eval()
{
  return lhs->eval() / rhs->eval();
}

int main() {
  Object* result;
  while ((result = parse()))
    cout << "Result: " << result->eval() << endl;

  GarbageCollector::GC.collect();

  return 0;
}
