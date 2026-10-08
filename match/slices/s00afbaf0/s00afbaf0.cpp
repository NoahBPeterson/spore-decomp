// Slice s00afbaf0: teardown of a spatial-object-like class (function 00afbde0). Destroys two element
// vectors at +0x154/+0xf0 and two pointer vectors at +0x140/+0xdc, Dispose()es three refcounted members
// at +0x60/+0x5c/+0x58, frees an EASTL-style hashtable at +0x38, then runs the vector dtor at +0.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern "C" void __cdecl operator_delete__(void* p);  // 0x00f47380

// Virtual placeholders: slots 0..47 are never called from this function. Dispose is slot 48 (+0xc0).
struct VirtObj {
  virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
  virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
  virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
  virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
  virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
  virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
  virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
  virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
  virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
  virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
  virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
  virtual void Dispose();  // slot 48
};

struct Elem24Vec {  // 0x00afb090: destroys 0x18-byte elements (VirtObj* at +4, slot 1), frees buffer
  void DtorElems();
};

struct PtrVec {  // 0x00afb7a0: destroys pointer array (VirtObj* elements, slot 23), frees buffer
  void DtorPtrs();
};

struct Hash38 {  // EASTL-style hashtable state at +0x38
  uint32_t mAllocPad;
  void** mpBuckets;         // +0x3c
  uint32_t mnBucketCount;   // +0x40
  uint32_t mnElementCount;  // +0x44
  void FreeChains(void** buckets, uint32_t n);  // 0x00ba2980 (thiscall; ECX=this, ret 8)
};

struct VecAutoRef {  // 0x00ad92d0: eastl::vector<EA::AutoRefCount<SP::cSpatialObject>> dtor
  ~VecAutoRef();
};

struct SpatialTeardown {
  VecAutoRef vec;            // +0x00
  char pad0[0x37];
  Hash38 ht;                 // +0x38
  char pad1[0x10];           // +0x48
  VirtObj* p58;              // +0x58
  VirtObj* p5c;              // +0x5c
  VirtObj* p60;              // +0x60
  char pad2[0x78];           // +0x64
  PtrVec vdc;                // +0xdc
  char pad3[0x13];
  Elem24Vec vf0;             // +0xf0
  char pad4[0x4b];
  char pad5[4];              // +0x13c
  PtrVec v140;               // +0x140
  char pad6[0x13];
  Elem24Vec v154;            // +0x154

  void Teardown();
};

void SpatialTeardown::Teardown() {
  v154.DtorElems();
  v140.DtorPtrs();
  vf0.DtorElems();
  vdc.DtorPtrs();
  VirtObj* q60 = p60;
  if (q60) q60->Dispose();
  VirtObj* q5c = p5c;
  if (q5c) q5c->Dispose();
  VirtObj* q58 = p58;
  if (q58) q58->Dispose();
  Hash38* h = &ht;
  uint32_t n = h->mnBucketCount;
  void** b = h->mpBuckets;
  h->FreeChains(b, n);
  uint32_t c = h->mnBucketCount;
  h->mnElementCount = 0;
  if (c > 1) operator_delete__(h->mpBuckets);
  vec.~VecAutoRef();
}
