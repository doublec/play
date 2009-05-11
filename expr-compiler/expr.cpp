#include <cassert>
#include <cmath>
#include <iostream>
#include "expr.h"

using namespace std;
using namespace nanojit;

#if defined(NJ_VERBOSE)
void
nanojit::LirNameMap::formatGuard(LIns *i, char *out)
{
}
#endif

void nanojit::Fragment::onDestroy() {
}

int nanojit::StackFilter::getTop(LInsp guard)
{
  return 0;
}

Number::Number(float v) :
  value(v)
{
}

LIns* Number::compile(LirWriter* writer)
{
  return writer->insImmf(value);
}

Add::Add(Object* l, Object* r) :
  lhs(l), rhs(r)
{
}

LIns* Add::compile(LirWriter* writer)
{
  LIns* a = lhs->compile(writer);
  LIns* b = rhs->compile(writer);
  return writer->ins2(LIR_fadd, a, b);
}

Subtract::Subtract(Object* l, Object* r) :
  lhs(l), rhs(r)
{
}

LIns* Subtract::compile(LirWriter* writer)
{
  LIns* a = lhs->compile(writer);
  LIns* b = rhs->compile(writer);
  return writer->ins2(LIR_fsub, a, b);
}

Multiply::Multiply(Object* l, Object* r) :
  lhs(l), rhs(r)
{
}

LIns* Multiply::compile(LirWriter* writer)
{
  LIns* a = lhs->compile(writer);
  LIns* b = rhs->compile(writer);
  return writer->ins2(LIR_fmul, a, b);
}

Divide::Divide(Object* l, Object* r) :
  lhs(l), rhs(r)
{
}

LIns* Divide::compile(LirWriter* writer)
{
  LIns* a = lhs->compile(writer);
  LIns* b = rhs->compile(writer);
  return writer->ins2(LIR_fdiv, a, b);
}

int main() {
  // Setup nanojit objects
  avmplus::GC *gc = new avmplus::GC;
  avmplus::AvmCore core;
#ifdef DEBUG
  core.config.verbose = 1; // Show disassembly of generated traces.
#endif

  Fragmento *fragmento = new (gc) Fragmento(&core, 20);
  LirBuffer *buf = new (gc) LirBuffer(fragmento, NULL);

  Object* result;
  while ((result = parse())) {
    // Create a Fragment to hold some native code.
    Fragment *f = new (gc) Fragment(NULL);
    f->lirbuf = buf;
    f->root = f;
  
    // Create a LIR writer, with verbose output if DEBUG.
    LirBufWriter writer0(buf);
#ifdef DEBUG
    fragmento->labels = new (gc) LabelMap(&core, NULL);
    buf->names = new (gc) LirNameMap(gc, NULL, fragmento->labels);
    VerboseWriter writer(gc, &writer0, buf->names);
#else
    LirBufWriter& writer = writer0;
#endif

    writer.ins0(LIR_start);
    writer.ins1(LIR_ret, result->compile(&writer));

    // Emit a LIR_loop instruction.  It won't be reached, but there's
    // an assertion in Nanojit that trips if a fragment doesn't end with
    // a guard (a bug in Nanojit). 
    LIns *rec_ins = writer0.insSkip(sizeof(GuardRecord) + sizeof(SideExit));
    GuardRecord *guard = (GuardRecord *) rec_ins->payload();
    memset(guard, 0, sizeof(*guard));
    SideExit *exit = (SideExit *)(guard + 1);
    guard->exit = exit;
    guard->exit->target = f;
    f->lastIns = writer.insGuard(LIR_loop, writer.insImm(1), rec_ins);

    // Compile the fragment.
    compile(fragmento->assm(), f);
    if (fragmento->assm()->error() != None) {
      cerr << "error compiling fragment" << endl;
      return 0;
    }

    // Call the compiled function.
    typedef JS_FASTCALL float (*ExprFunction)();
    ExprFunction fn = reinterpret_cast<ExprFunction>(f->code());
    cout << "Result: " << fn() << endl;
  }
  
  return 0;
}
