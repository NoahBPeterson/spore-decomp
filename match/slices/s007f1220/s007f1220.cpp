// Slice s007f1220: EA::Arithmetica bytecode program (cArithmeticaProgram),
// its resource factory and loader.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <new>
#include <intrin.h>

void* operator new(size_t size, const char* name, int a, int b, const char* file, int line);

#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]

// ---------------------------------------------------------------------------
// 0x007F1600 - resource-read callback: stores a ResourceKey id.
// ---------------------------------------------------------------------------
// @ 0x007F1600
int __stdcall ArithmeticaKeyRead(void** p, unsigned count) {
  if (p) {
    if (count < 1) return 0;
    *p = (void*)0x0472329b;
  }
  return 1;
}

// ---------------------------------------------------------------------------
// 0x007F1890 - eastl uninitialized_copy for 16-byte elements.
// ---------------------------------------------------------------------------
struct E16 {
  uint32_t a, b, c, d;
};

// @ 0x007F1890
void UninitCopy16(E16** result, E16* first, E16* last, E16* dst) {
  *result = dst;
  if (first != last) {
    do {
      if (dst) *dst = *first;
      ++first;
      ++dst;
    } while (first != last);
    *result = dst;
  }
}

// ---------------------------------------------------------------------------
// Forward declaration of the writer used by 0x007F1870.
// ---------------------------------------------------------------------------
bool ArithmeticaWriteResource(void* prog, void* writer);

// @ 0x007F1870
void __stdcall ArithmeticaFactoryWrite(void* prog, void* mgr, int, int) {
  void* writer = ((void*(__thiscall*)(void*))(*(void***)mgr)[0x18 / 4])(mgr);
  ArithmeticaWriteResource(prog, writer);
}

// ---------------------------------------------------------------------------
// 0x007F18E0 - small heap object: base vptr + atomic refcount + derived vptr.
// ---------------------------------------------------------------------------
struct ResBase {
  virtual ~ResBase() {}
  volatile long mRef;  // +0x04
  ResBase() { _InterlockedExchange(&mRef, 0); }
};
struct ResDerived : ResBase {
  virtual ~ResDerived() {}
};

// @ 0x007F18E0
ResDerived* CreateResDerived() {
  return new ("App", 0, 0, 0, 0) ResDerived;
}

// ---------------------------------------------------------------------------
// cArithmeticaProgram (size 0x94): resource base + six pointer-vectors.
// ---------------------------------------------------------------------------
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

// @ 0x007F1E60
cArithmeticaProgram::cArithmeticaProgram() {}

// ---------------------------------------------------------------------------
// 0x007F1820 - cArithmeticaFactory::WriteResource.
// ---------------------------------------------------------------------------
struct ProgStub {
  void CompileToByteCode(void* out);  // __thiscall ret 4
};
extern void EAWriteUint32(void* w, void* s, int n, int f);

// @ 0x007F1820
bool ArithmeticaWriteResource(void* prog, void* writer) {
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

// ---------------------------------------------------------------------------
// 0x007F1ED0 - cArithmeticaFactory::Create.
// ---------------------------------------------------------------------------
struct VFactory {
  bool Create(void* param2, void* out, void* param4, void* param5);
};

// @ 0x007F1ED0
bool VFactory::Create(void* param2, void* out, void* param4, void* param5) {
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

// ===========================================================================
// Remaining slice functions: behaviourally approximate skeletons (partial.txt).
// ===========================================================================

// @ 0x007F1220  (big GPU submit / vertex emit method, 962 bytes)
void ArithmeticaSubmit(void* self) {
  (void)self;
}

// @ 0x007F1630  cArithmeticaProgram::CompileToByteCode
void* cArithmeticaProgram::CompileToByteCode(void* out) {
  (void)out;
  return 0;
}

// @ 0x007F1AC0  vector<tLabel>::operator= / assign
void ArithmeticaAssignLabels(void* self, void* other) {
  (void)self;
  (void)other;
}

// @ 0x007F1BF0  vector<16-byte>::insert (fill)
void ArithmeticaVec16Insert(void* self, void* pos, unsigned count, void* value) {
  (void)self;
  (void)pos;
  (void)count;
  (void)value;
}

// @ 0x007F1D90  cArithmeticaProgram destructor
void cArithmeticaProgram::Destroy() {}

// @ 0x007F1F60  vector resize
void ArithmeticaVecResize(void* self, unsigned n) {
  (void)self;
  (void)n;
}

// @ 0x007F1FE0  vector<16-byte>::operator=
void ArithmeticaVec16Assign(void* self, void* other) {
  (void)self;
  (void)other;
}

// @ 0x007F20D0  token lookup / run emit
void ArithmeticaLookupRun(void* self, void* key) {
  (void)self;
  (void)key;
}

// @ 0x007F21D0  cArithmeticaProgram::Copy
void cArithmeticaProgram::Copy(const cArithmeticaProgram& other) {
  (void)other;
}

// @ 0x007F2240  LoadArithmeticaFile
bool LoadArithmeticaFile(void* arg1, void* arg2) {
  (void)arg1;
  (void)arg2;
  return false;
}
