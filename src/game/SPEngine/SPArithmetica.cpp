// src/game/SPEngine/SPArithmetica.cpp -- migrated from slice(s) s007f2340, s007f1220 by tools/migrate/rewrite.py
// Object file: SPEngine/SPArithmetica.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void EAWriteUint32(void* w, void* s, int n, int f);
#include <new>
#include <intrin.h>

// ---- items of slice s007f1220 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* name, int a, int b, const char* file, int line);
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
struct E16 {
  uint32_t a, b, c, d;
};
bool ArithmeticaWriteResource(void* prog, void* writer);
struct ResBase {
  virtual ~ResBase() {}
  volatile long mRef;  // +0x04
  ResBase() { _InterlockedExchange(&mRef, 0); }
};
struct ResDerived : ResBase {
  virtual ~ResDerived() {}
};
struct Resource {
  virtual void Dummy();
  volatile long mRef;      // +0x04
  int mKey0, mKey1, mKey2; // +0x08
  void* mRelease;          // +0x14
  Resource() {
    _InterlockedExchange(&mRef, 0);
    mKey0 = 0;
    mKey1 = 0;
    mKey2 = 0;
    mRelease = 0;
  }
};
struct VecPtr {
  void* b;  // +0
  void* e;  // +4
  void* c;  // +8
  VecPtr() : b(0), e(0), c(0) {}
};
struct cArithmeticaProgram : Resource {
  VecPtr mTokens;        // +0x18
  int pad24;             // +0x24
  int pad28;
  VecPtr mVariables;     // +0x2c
  int pad38, pad3c;
  VecPtr mInstructions;  // +0x40
  int pad4c, pad50, pad54;
  VecPtr mStack;         // +0x58
  int pad64, pad68;
  VecPtr mGosubStack;    // +0x6c
  int pad78, pad7c;
  VecPtr mLabels;        // +0x80
  int pad8c, pad90;
  cArithmeticaProgram();
  void* CompileToByteCode(void* out);
  void Destroy();
  void Copy(const cArithmeticaProgram& other);
};
struct ProgStub {
  void CompileToByteCode(void* out);  // __thiscall ret 4
};
extern void EAWriteUint32(void* w, void* s, int n, int f);
struct VFactory {
  bool Create(void* param2, void* out, void* param4, void* param5);
};
// ---- items of slice s007f1220 end

// ---- items of slice s007f2340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int ArithReadThing(void* unused, void* reader);
// ---- items of slice s007f2340 end

// @ 0x007f1600
int __stdcall ArithmeticaKeyRead(void** p, unsigned count)
{
  if (p) {
    if (count < 1) return 0;
    *p = (void*)0x0472329b;
  }
  return 1;
}

// @ 0x007f1630
void* cArithmeticaProgram::CompileToByteCode(void* out)
{
  (void)out;
  return 0;
}

// @ 0x007f1820
bool ArithmeticaWriteResource(void* prog, void* writer)
{
  struct Compiled {
    void* data;  // +0
    int size;    // +4
  } c;
  ((ProgStub*)prog)->CompileToByteCode(&c);
  int sz = c.size;
  EAWriteUint32(writer, &sz, 1, 0);
  ((void(__thiscall*)(void*, void*, int))VSLOT(writer, 0x38))(writer, c.data, c.size * 4);
  return true;
}

// @ 0x007f1870
void __stdcall ArithmeticaFactoryWrite(void* prog, void* mgr, int, int)
{
  void* writer = ((void*(__thiscall*)(void*))(*(void***)mgr)[0x18 / 4])(mgr);
  ArithmeticaWriteResource(prog, writer);
}

// @ 0x007f1890
E16** UninitCopy16(E16** result, E16* first, E16* last, E16* dst)
{
  *result = dst;
  if (first != last) {
    do {
      if (dst) *dst = *first;
      ++first;
      ++dst;
    } while (first != last);
    *result = dst;
  }
  return result;
}

// @ 0x007f18e0
ResDerived* CreateResDerived()
{
  return new ("App", 0, 0, 0, 0) ResDerived;
}

// @ 0x007f1ac0
void ArithmeticaAssignLabels(void* self, void* other)
{
  (void)self;
  (void)other;
}

// @ 0x007f1bf0
void ArithmeticaVec16Insert(void* self, void* pos, unsigned count, void* value)
{
  (void)self;
  (void)pos;
  (void)count;
  (void)value;
}

// @ 0x007f1d90
void cArithmeticaProgram::Destroy()
{}

// @ 0x007f1e60
cArithmeticaProgram::cArithmeticaProgram()
{}

// @ 0x007f1ed0
bool VFactory::Create(void* param2, void* out, void* param4, void* param5)
{
  cArithmeticaProgram* prog = new ("App/cArithmeticaFactory", 0, 0, 0, 0) cArithmeticaProgram;
  int* key = (int*)((void*(__thiscall*)(void*))VSLOT(param2, 0x10))(param2);
  prog->mKey0 = key[0];
  prog->mKey1 = key[1];
  prog->mKey2 = key[2];
  if (((bool(__thiscall*)(void*, void*, void*, void*, void*))VSLOT(this, 0x24))(
          this, param2, prog, param4, param5)) {
    *(void**)out = prog;
    ((void(__thiscall*)(void*))VSLOT(prog, 0))(prog);
    return true;
  }
  ((void(__thiscall*)(void*, int))VSLOT(prog, 8))(prog, 1);
  return false;
}

// @ 0x007f1f60
void ArithmeticaVecResize(void* self, unsigned n)
{
  (void)self;
  (void)n;
}

// @ 0x007f1fe0
void ArithmeticaVec16Assign(void* self, void* other)
{
  (void)self;
  (void)other;
}

// @ 0x007f20d0
void ArithmeticaLookupRun(void* self, void* key)
{
  (void)self;
  (void)key;
}

// @ 0x007f21d0
void cArithmeticaProgram::Copy(const cArithmeticaProgram& other)
{
  (void)other;
}

// @ 0x007f2240
bool LoadArithmeticaFile(void* arg1, void* arg2)
{
  (void)arg1;
  (void)arg2;
  return false;
}

// @ 0x007f2500
void ArithReset(void* self)
{
  (void)self;
}

// @ 0x007f29e0
void __stdcall ArithReadWrapper(void* mgr, void* reader, int, int)
{
  ((void(__thiscall*)(void*))VSLOT(mgr, 0x1c))(mgr);
  void* r = ((void*(__thiscall*)(void*))VSLOT(mgr, 0x18))(mgr);
  ArithReadThing(reader, r);
}
