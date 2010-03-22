#include <cassert>
#include <cmath>
#include <iostream>
#include "expr.h"

using namespace std;
using namespace nanojit;

/* Allocator SPI implementation. */

void*
nanojit::Allocator::allocChunk(size_t nbytes)
{
    void *p = malloc(nbytes);
    if (!p)
        exit(1);
    return p;
}

void
nanojit::Allocator::freeChunk(void *p) {
    free(p);
}

void
nanojit::Allocator::postReset() {
}

/* LIR SPI implementation */

int
nanojit::StackFilter::getTop(LIns*)
{
    return 0;
}

#if defined NJ_VERBOSE
void
nanojit::LInsPrinter::formatGuard(InsBuf *buf, LIns *ins)
{
  // This example doesn't use guards so have a do-nothing implementation here
  if (buf->len > 0)
    *buf->buf = '\0';
}

void
nanojit::LInsPrinter::formatGuardXov(InsBuf *buf, LIns *ins)
{
  // This example doesn't use guards so have a do-nothing implementation here
  if (buf->len > 0)
    *buf->buf = '\0';
}
#endif

Number::Number(float v) :
  value(v)
{
}

LIns* Number::compile(LirWriter* writer)
{
  return writer->insImmf(value);
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

LIns* Add::compile(LirWriter* writer)
{
  LIns* a = lhs->compile(writer);
  LIns* b = rhs->compile(writer);
  return writer->ins2(LIR_fadd, a, b);
}

Subtract::Subtract(Object* l, Object* r) :
  BinOp(l, r)
{
}

LIns* Subtract::compile(LirWriter* writer)
{
  LIns* a = lhs->compile(writer);
  LIns* b = rhs->compile(writer);
  return writer->ins2(LIR_fsub, a, b);
}

Multiply::Multiply(Object* l, Object* r) :
  BinOp(l, r)
{
}

LIns* Multiply::compile(LirWriter* writer)
{
  LIns* a = lhs->compile(writer);
  LIns* b = rhs->compile(writer);
  return writer->ins2(LIR_fmul, a, b);
}

Divide::Divide(Object* l, Object* r) :
  BinOp(l, r)
{
}

LIns* Divide::compile(LirWriter* writer)
{
  LIns* a = lhs->compile(writer);
  LIns* b = rhs->compile(writer);
  return writer->ins2(LIR_fdiv, a, b);
}

SideExit* createSideExit(Fragment* fragment, Allocator& allocator)
{
    SideExit* exit = new (allocator) SideExit();
    memset(exit, 0, sizeof(SideExit));
    exit->from = fragment;
    exit->target = NULL;
    return exit;
}

GuardRecord* createGuardRecord(SideExit *exit, Allocator& allocator)
{
    GuardRecord *rec = new (allocator) GuardRecord;
    memset(rec, 0, sizeof(GuardRecord));
    rec->exit = exit;
    exit->addGuard(rec);
    return rec;
}

int main() {
  avmplus::AvmCore core;
  LogControl log;
  CodeAlloc code_allocator;
  Allocator allocator;
  Assembler assembler(code_allocator, allocator, allocator, &core, &log, nanojit::AvmCore::config);
  LirBuffer *buf = new (allocator) LirBuffer(allocator);
#ifdef DEBUG
  log.lcbits = 0; //LC_ReadLIR | LC_Assembly | LC_RegAlloc | LC_Activation;
  buf->printer = new (allocator) LInsPrinter(allocator);
#endif
  Object* result;
  while ((result = parse())) {
    // Create a Fragment to hold some native code.
    Fragment *f = new (allocator) Fragment(NULL, 0);
    f->lirbuf = buf;
  
    // Create a LIR writer, with verbose output if DEBUG.
    LirBufWriter* writer = new (allocator) LirBufWriter(buf, nanojit::AvmCore::config);

    writer->ins0(LIR_start);
    f->lastIns = writer->ins1(LIR_fret, result->compile(writer));

    // Compile the fragment.
    assembler.compile(f, allocator, false verbose_only(, buf->printer)); 
    if (assembler.error() != None) {
      cerr << "error compiling fragment" << endl;
      return 0;
    }

    // Call the compiled function.
    typedef FASTCALL float (*ExprFunction)();
    ExprFunction fn = reinterpret_cast<ExprFunction>(f->code());
    cout << "Result: " << fn() << endl;
  }

  GarbageCollector::GC.collect();
  
  return 0;
}
