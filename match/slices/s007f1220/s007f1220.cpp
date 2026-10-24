// Slice s007f1220: EA::Arithmetica bytecode program (cArithmeticaProgram),
// its resource factory and loader.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <new>
#include <intrin.h>

void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);

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
E16** UninitCopy16(E16** result, E16* first, E16* last, E16* dst) {
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

// ---------------------------------------------------------------------------
// Out-of-line retail helpers used by the vector operations below.  Bodies live
// in other translation units; only the addresses matter here.
// ---------------------------------------------------------------------------
void* __cdecl FUN_006abeb0(unsigned size);                                         // 0x006ABEB0
void* __cdecl FUN_00ac4440(void* first, void* last, void* dst);                    // 0x00AC4440
void* __cdecl FUN_0076ffd0(void** res, void* first, void* last, void* dst, const void* v);  // 0x0076FFD0
void* __cdecl FUN_007c8b70(void* first, void* last, void* dst);                    // 0x007C8B70
void* __cdecl FUN_00555aa0(void** res, void* first, void* last, void* dst, const void* v);  // 0x00555AA0
void* __cdecl FUN_00705250(void* first, void* last, void* dst);                    // 0x00705250
void* __cdecl FUN_00c7ea30(void* first, void* last, void* dst);                    // 0x00C7EA30
void* __cdecl FUN_0088f820(void* dst, unsigned n, const void* val, const void* tag); // 0x0088F820
void* __cdecl FUN_00898580(void* dst, void* tag, const void* val);                 // 0x00898580
void* __cdecl FUN_00edba80(void* first, void* last, void* dst);                    // 0x00EDBA80
bool  __cdecl FUN_00555020(const void* a, const void* b);                          // 0x00555020
void* __cdecl FUN_0067dcd0();                                                      // 0x0067DCD0

// ---------------------------------------------------------------------------
// eastl vectors, each carrying the declaration of the retail out-of-line helper
// its operations resolve to (class-qualified names keep the target address).
// ---------------------------------------------------------------------------
struct VecF {                        // eastl::vector<float, sp_vector_allocator>
  void* b;                           // +0
  void* e;                           // +4
  void* c;                           // +8
  VecF() : b(0), e(0), c(0) {}
  void FUN_0050d4e0(const VecF& other);                                    // 0x0050D4E0
  void FUN_007f2a70(void* instr, void* vars, unsigned label, int flag);    // 0x007F2A70
};
struct VecIns {                      // eastl::vector<tStackInstruction, sp_vector_allocator>
  void* b;
  void* e;
  void* c;
  VecIns() : b(0), e(0), c(0) {}
  void FUN_007f19e0(const VecIns& other);                                  // 0x007F19E0
};
struct VecLbl {                      // eastl::vector<tLabel, ...>  (8-byte elements)
  void* b;
  void* e;
  void* c;
  VecLbl() : b(0), e(0), c(0) {}
  void* reallocate(unsigned n, void* first, void* last);                   // 0x007F1980
  VecLbl& assign(const VecLbl& other);                                     // 0x007F1AC0
};
struct VecTok {                      // eastl::vector<16-byte token, ...>
  void* b;
  void* e;
  void* c;
  VecTok() : b(0), e(0), c(0) {}
  void* reallocate(unsigned n, void* first, void* last);                   // 0x007F1B90
  void* FUN_006a4950(void* begin, void* end);                              // 0x006A4950
  void resize(unsigned n);                                                 // 0x007F1F60
  void insert(void* pos, unsigned count, const void* value);               // 0x007F1BF0
  VecTok& assign(const VecTok& other);                                     // 0x007F1FE0
};

// ---------------------------------------------------------------------------
// Layout records used by the bytecode emitter.
// ---------------------------------------------------------------------------
struct StackMachine {                // cArithmeticaProgram sub-object at +0x58
  VecF mStack;                       // +0x00
  int pad64, pad68;                  // +0x0c
  VecF mGosubStack;                  // +0x14
  int pad78, pad7c;                  // +0x20
};

struct ArithmeticaKey {              // 12-byte resource key
  void* a;                           // +0
  unsigned id0;                      // +4
  unsigned id1;                      // +8
};
struct ArithInstr {                  // compiled instruction, 16 bytes
  unsigned op;                       // +0
  unsigned literal;                  // +4
  unsigned variable;                 // +8
  unsigned line;                     // +0xC
};
struct ArithToken {                  // source token, 16 bytes
  char* text;                        // +0
  char* end;                         // +4
  unsigned pad8;                     // +8
  unsigned padC;                     // +0xC
};
struct ArithLabel {                  // one label, 8 bytes
  unsigned a;                        // +0
  unsigned b;                        // +4
};

struct cArithmeticaProgram : public Resource {
  VecTok mTokens;              // +0x18
  int pad24;                   // +0x24
  int pad28;
  VecF mVariables;             // +0x2c
  int pad38, pad3c;
  VecIns mInstructions;        // +0x40
  int pad4c, pad50, pad54;
  StackMachine mStackMachine;  // +0x58: {mStack, mGosubStack} share one base
  VecLbl mLabels;              // +0x80
  int pad8c, pad90;
  cArithmeticaProgram();
  void* CompileToByteCode(void* out);
  void Destroy();
  void Copy(const cArithmeticaProgram& other);
  void LookupRun(void* key);
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
// Remaining slice functions.
// ===========================================================================

// ---------------------------------------------------------------------------
// 0x007F1AC0 - eastl::vector<tLabel>::operator= (the copy-assign).
// ---------------------------------------------------------------------------
// @ 0x007F1AC0
VecLbl& VecLbl::assign(const VecLbl& other) {
  if (&other == this) return *this;
  unsigned otherCount = (unsigned)(((int)((char*)other.e - (char*)other.b)) >> 3);
  if (otherCount > (unsigned)(((int)((char*)c - (char*)b)) >> 3)) {
    void* p = reallocate(otherCount, other.b, other.e);
    if (b && *(int*)((char*)b - 4) != 0) operator delete[](b);
    b = p;
    e = (char*)p + otherCount * 8;
    c = (char*)p + otherCount * 8;
    return *this;
  }
  unsigned myCount = (unsigned)(((int)((char*)e - (char*)b)) >> 3);
  if (otherCount > myCount) {
    FUN_00ac4440(other.b, (char*)other.b + myCount * 8, b);
    void* result;
    FUN_0076ffd0(&result, (char*)other.b + myCount * 8, other.e, e, &other);
  } else {
    FUN_00ac4440(other.b, other.e, b);
  }
  e = (char*)b + otherCount * 8;
  return *this;
}

// ---------------------------------------------------------------------------
// 0x007F1FE0 - eastl::vector<16-byte>::operator= (the copy-assign).
// ---------------------------------------------------------------------------
// @ 0x007F1FE0
VecTok& VecTok::assign(const VecTok& other) {
  if (&other == this) return *this;
  unsigned otherCount = (unsigned)(((int)((char*)other.e - (char*)other.b)) >> 4);
  if (otherCount > (unsigned)(((int)((char*)c - (char*)b)) >> 4)) {
    void* p = reallocate(otherCount, other.b, other.e);
    FUN_006a4950(b, e);
    if (b && *(int*)((char*)b - 4) != 0) operator delete[](b);
    b = p;
    e = (char*)p + otherCount * 16;
    c = (char*)p + otherCount * 16;
    return *this;
  }
  unsigned myCount = (unsigned)(((int)((char*)e - (char*)b)) >> 4);
  if (otherCount > myCount) {
    FUN_007c8b70(other.b, (char*)other.b + myCount * 16, b);
    void* result;
    FUN_00555aa0(&result, (char*)other.b + myCount * 16, other.e, e, &other);
  } else {
    void* dst = FUN_007c8b70(other.b, other.e, b);
    FUN_006a4950(dst, e);
  }
  e = (char*)b + otherCount * 16;
  return *this;
}

// ---------------------------------------------------------------------------
// 0x007F1F60 - eastl::vector<16-byte>::resize.
// ---------------------------------------------------------------------------
// @ 0x007F1F60
void VecTok::resize(unsigned n) {
  unsigned count = (unsigned)(((char*)e - (char*)b) >> 4);
  if (n > count) {
    struct {
      unsigned a;  // +0
      float b;     // +4
      int c;       // +8
      int d;       // +0xC  (never assigned -- matches the original)
    } tmp;
    tmp.a = 9;
    tmp.b = 0.0f;
    tmp.c = -1;
    insert(e, n - count, &tmp);
    return;
  }
  void* dst = (char*)b + n * 16;
  FUN_00705250(e, e, dst);
  e = (char*)e + (-(((char*)e - (char*)dst) >> 4) << 4);
}

// ---------------------------------------------------------------------------
// 0x007F1BF0 - eastl::vector<16-byte>::insert (fill).
// ---------------------------------------------------------------------------
// @ 0x007F1BF0
void VecTok::insert(void* pos, unsigned count, const void* value) {
  if (count > (unsigned)(((char*)c - (char*)e) >> 4)) {
    unsigned size = (unsigned)(((char*)e - (char*)b) >> 4);
    unsigned newCap = size * 2;
    if (newCap == 0) newCap = 1;
    if (size + count > newCap) newCap = size + count;
    void* p = operator new((size_t)newCap << 4, "App", 0, 0, "eastl/allocator.h", 209);
    void* mid = FUN_00c7ea30(b, pos, p);
    FUN_0088f820(mid, count, value, pos);
    void* newEnd = FUN_00c7ea30(pos, e, (char*)mid + count * 16);
    if (b && *(int*)((char*)b - 4) != 0) operator delete[](b);
    b = p;
    e = newEnd;
    c = (char*)p + (newCap << 4);
    return;
  }
  if (count == 0) return;
  E16 tmp;
  tmp = *(const E16*)value;
  unsigned after = (unsigned)(((char*)e - (char*)pos) >> 4);
  if (after <= count) {
    unsigned n = count - after;
    FUN_0088f820(e, n, &tmp, pos);
    void* oldE = e;
    e = (char*)e + n * 16;
    E16* res;
    UninitCopy16(&res, (E16*)pos, (E16*)oldE, (E16*)e);
    e = (char*)e + after * 16;
    FUN_00898580(pos, oldE, &tmp);
    return;
  }
  void* split = (char*)e - count * 16;
  E16* res;
  UninitCopy16(&res, (E16*)split, (E16*)e, (E16*)e);
  e = (char*)e + count * 16;
  FUN_00edba80(pos, split, e);
  FUN_00898580(pos, (char*)pos + count * 16, &tmp);
}

// ---------------------------------------------------------------------------
// 0x007F1630 - cArithmeticaProgram::CompileToByteCode.
// ---------------------------------------------------------------------------
// @ 0x007F1630
void* cArithmeticaProgram::CompileToByteCode(void* out) {
  unsigned* o = (unsigned*)out;
  unsigned nInstr = (unsigned)(((char*)mInstructions.e - (char*)mInstructions.b) >> 4);
  unsigned nLabels = (unsigned)(((char*)mLabels.e - (char*)mLabels.b) >> 3);
  unsigned size = (nLabels + nInstr * 2) * 2 + 5;
  o[1] = size;
  unsigned total = 1;
  unsigned nTok = (unsigned)(((char*)mTokens.e - (char*)mTokens.b) >> 4);
  for (unsigned i = 0; i < nTok; ++i) {
    ArithToken* t = (ArithToken*)((char*)mTokens.b + i * 16);
    total += (unsigned)(t->end - t->text) + 1;
  }
  o[1] = size + total;
  while ((total & 3) == 0) ++total;
  unsigned* p = (unsigned*)FUN_006abeb0(o[1] * 4);
  p[0] = 0x41525448;
  p[1] = 1;
  p[2] = 2;
  p[3] = o[1];
  o[0] = (unsigned)p;
  p[4] = nInstr;
  unsigned idx = 5;
  for (unsigned i = 0; i < nInstr; ++i) {
    ArithInstr* ins = (ArithInstr*)((char*)mInstructions.b + i * 16);
    p[idx] = ins->line;
    p[idx + 1] = ins->literal;
    p[idx + 2] = ins->variable;
    p[idx + 3] = ins->op;
    idx += 4;
  }
  p[idx] = nLabels;
  ++idx;
  unsigned nl = (unsigned)(((char*)mLabels.e - (char*)mLabels.b) >> 3);
  for (unsigned i = 0; i < nl; ++i) {
    ArithLabel* l = (ArithLabel*)((char*)mLabels.b + i * 8);
    p[idx] = l->a;
    p[idx + 1] = l->b;
    idx += 2;
  }
  p[idx] = (unsigned)(((char*)mTokens.e - (char*)mTokens.b) >> 4);
  p[idx + 1] = (unsigned)(((char*)mVariables.e - (char*)mVariables.b) >> 2);
  char* str = (char*)(p + idx + 2);
  unsigned off = 0;
  unsigned nt = (unsigned)(((char*)mTokens.e - (char*)mTokens.b) >> 4);
  for (unsigned i = 0; i < nt; ++i) {
    ArithToken* t = (ArithToken*)((char*)mTokens.b + i * 16);
    char* d = str + off;
    const char* s = t->text;
    while ((*d = *s) != 0) {
      ++d;
      ++s;
    }
    off += (unsigned)(t->end - t->text) + 1;
  }
  return out;
}

// ---------------------------------------------------------------------------
// 0x007F20D0 - cArithmeticaProgram::LookupRun: find the label whose token
// matches the key, then emit the run starting at that label.
// ---------------------------------------------------------------------------
// @ 0x007F20D0
void cArithmeticaProgram::LookupRun(void* key) {
  for (unsigned i = 0; i < (unsigned)(((int)((char*)mLabels.e - (char*)mLabels.b)) >> 3); ++i) {
    ArithLabel* l = (ArithLabel*)((char*)mLabels.b + i * 8);
    void* tok = (char*)mTokens.b + l->a * 16;
    if (!FUN_00555020(tok, key)) continue;
    VecF empty;
    VecF emptyG;
    StackMachine* sm = &mStackMachine;
    sm->mStack.FUN_0050d4e0(empty);
    sm->mGosubStack.FUN_0050d4e0(emptyG);
    sm->mStack.FUN_007f2a70(&mInstructions, mVariables.b, l->b, -1);
    return;
  }
}

// ---------------------------------------------------------------------------
// 0x007F1D90 - destructor body (frees the six vectors, restores base vptr).
// ---------------------------------------------------------------------------
// @ 0x007F1D90
void cArithmeticaProgram::Destroy() {
  *(void**)this = (void*)0x14782b4;
  if (mLabels.b && *(int*)((char*)mLabels.b - 4) != 0) operator delete[](mLabels.b);
  if (mStackMachine.mGosubStack.b && *(int*)((char*)mStackMachine.mGosubStack.b - 4) != 0)
    operator delete[](mStackMachine.mGosubStack.b);
  if (mStackMachine.mStack.b && *(int*)((char*)mStackMachine.mStack.b - 4) != 0)
    operator delete[](mStackMachine.mStack.b);
  if (mInstructions.b && *(int*)((char*)mInstructions.b - 4) != 0) operator delete[](mInstructions.b);
  if (mVariables.b && *(int*)((char*)mVariables.b - 4) != 0) operator delete[](mVariables.b);
  mTokens.FUN_006a4950(mTokens.b, mTokens.e);
  if (mTokens.b && *(int*)((char*)mTokens.b - 4) != 0) operator delete[](mTokens.b);
  *(void**)this = (void*)0x13eb938;
}

// ---------------------------------------------------------------------------
// 0x007F21D0 - cArithmeticaProgram::Copy.
// ---------------------------------------------------------------------------
// @ 0x007F21D0
void cArithmeticaProgram::Copy(const cArithmeticaProgram& other) {
  pad54 = other.pad54;
  mInstructions.FUN_007f19e0(other.mInstructions);
  mLabels.assign(other.mLabels);
  const StackMachine* src = &other.mStackMachine;
  StackMachine* dst = &mStackMachine;
  dst->mStack.FUN_0050d4e0(src->mStack);
  dst->mGosubStack.FUN_0050d4e0(src->mGosubStack);
  mTokens.assign(other.mTokens);
  mVariables.FUN_0050d4e0(other.mVariables);
}

// ---------------------------------------------------------------------------
// 0x007F2240 - EA::ResourceMan::LoadArithmeticaFile.
// ---------------------------------------------------------------------------
struct ArithmeticaProgramRef {
  cArithmeticaProgram* m_p;  // +0
  ~ArithmeticaProgramRef() {
    if (m_p) {
      cArithmeticaProgram* t = m_p;
      ((void(__thiscall*)(void*))VSLOT(t, 4))(t);
    }
  }
};

// @ 0x007F2240
bool LoadArithmeticaFile(void* arg1, unsigned arg2, cArithmeticaProgram* dst) {
  ArithmeticaKey key;
  key.a = arg1;
  key.id0 = 0x472329b;
  key.id1 = arg2 ? arg2 : 0x24a4f5a;
  ArithmeticaProgramRef loaded;
  loaded.m_p = 0;
  void* mgr = FUN_0067dcd0();
  if (loaded.m_p) {
    cArithmeticaProgram* t = loaded.m_p;
    loaded.m_p = 0;
    ((void(__thiscall*)(void*))VSLOT(t, 4))(t);
  }
  bool ok = ((bool(__thiscall*)(void*, void*, void*, int, int, int, int))VSLOT(mgr, 0x0c))(
      mgr, &key, (void*)&loaded, 0, 0, 0, 0);
  if (ok) {
    dst->Copy(*(const cArithmeticaProgram*)loaded.m_p);
    ((void(__thiscall*)(void*))VSLOT(dst, 0x14))(dst);
  }
  return ok;
}

// ---------------------------------------------------------------------------
// 0x007F1220 - GPU submit / vertex emit method.  Its receiver is not a
// cArithmeticaProgram (it reaches +0x120/+0x134/+0x138 and global shader
// state), so it is modelled on an opaque receiver to keep the __thiscall ABI.
// ---------------------------------------------------------------------------
struct ArithSubmitObj {
  void Submit(void* arg);  // 0x007F1220
};

// @ 0x007F1220
void ArithSubmitObj::Submit(void* arg) {
  (void)arg;
}